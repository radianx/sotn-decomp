#!/usr/bin/env python3
# SPDX-License-Identifier: AGPL-3.0-or-later
"""Build local, native-only widescreen edge assets from verified AI drafts."""

import argparse
import functools
import hashlib
import io
import json
import re
import struct
import tempfile
from pathlib import Path

from PIL import Image

REPO = Path(__file__).resolve().parents[1]
TEMPLATE = re.compile(
    r"stages/([A-Z0-9]+)/layer_([0-9A-F]{2})_(fg|bg)_(left|right|both)_paint\.png"
)


def stage_ids():
    source = (REPO / "src/pc/main.c").read_text()
    array = source.split("allowed_stages[] = {", 1)[1].split("};", 1)[0]
    return {
        name.upper(): i
        for i, name in enumerate(re.findall(r'"([^\"]*)"', array))
        if name
    }


def validate_extension(original, extension, bounds):
    if original.size != extension.size or extension.width != 296:
        raise ValueError("Extension dimensions differ from the native template")
    if not 0 < extension.height <= 16384:
        raise ValueError("Invalid extension height")
    original = original.convert("RGBA")
    alpha = extension.convert("RGBA").getchannel("A")
    for y in range(extension.height):
        allowed = []
        for start, end in zip(bounds[::2], bounds[1::2]):
            edge = end if start == 0 else start - 1
            if original.getpixel((edge, y))[3]:
                allowed.append((start, end))
        for x in range(296):
            if alpha.getpixel((x, y)) and not any(a <= x < b for a, b in allowed):
                raise ValueError(
                    "Extension covers protected artwork or intentional alpha"
                )


@functools.lru_cache(maxsize=65536)
def nearest_color(palette, color):
    best, distance = None, 1 << 30
    for index, entry in enumerate(palette):
        if not entry:
            continue
        r = (entry & 31) - (color & 31)
        g = ((entry >> 5) & 31) - ((color >> 5) & 31)
        b = ((entry >> 10) & 31) - ((color >> 10) & 31)
        error = r * r + g * g + b * b
        if error < distance:
            best, distance = index, error
    if best is None:
        raise ValueError("Boundary palette has no opaque colors")
    return best


def index_extension(image, layout, pages, cluts, palette, width, bounds):
    """R=palette, G=color index, B=tile page, A=unchanged artist alpha."""
    image = image.convert("RGBA")
    columns = width // 16
    if width < 256 or width % 256 or len(layout) != columns * image.height // 16:
        raise ValueError("Tile layout dimensions do not match artwork")
    result = Image.new("RGBA", image.size)
    result.putalpha(image.getchannel("A"))
    for start, end in zip(bounds[::2], bounds[1::2]):
        column = 0 if start == 0 else columns - 1
        for y in range(image.height):
            tile = layout[(y // 16) * columns + column]
            pixels = [
                (x, image.getpixel((x, y)))
                for x in range(start, end)
                if image.getpixel((x, y))[3]
            ]
            if not pixels:
                continue
            if not tile or tile >= min(len(pages), len(cluts)):
                raise ValueError("Artwork has no valid boundary tile")
            page, clut = pages[tile], cluts[tile]
            colors = tuple(palette[clut * 16 : clut * 16 + 16])
            if page >= 24 or len(colors) != 16:
                raise ValueError("Invalid boundary tile page or palette")
            for x, (r, g, b, alpha) in pixels:
                color = (r >> 3) | (g >> 3) << 5 | (b >> 3) << 10
                result.putpixel(
                    (x, y), (clut, nearest_color(colors, color), page, alpha)
                )
    return result


def build(artwork_dir, template_dir, output_dir):
    jobs = json.loads((artwork_dir / "jobs.json").read_text())["jobs"]
    ids = stage_ids()
    manifest = template_dir / "manifest.json"
    layers = (
        {
            t["file"]: layer
            for layer in json.loads(manifest.read_text())["layers"]
            for t in layer.get("templates", [])
        }
        if manifest.exists()
        else None
    )
    palettes, definitions, ready, indexed = {}, {}, [], []
    for job in jobs:
        if job["status"] != "draft-verified-size-pixels-alpha":
            continue
        for filename in job["outputs"]:
            match = TEMPLATE.fullmatch(filename)
            if not match:
                # Composite screenshot examples are not individual room layers.
                continue
            stage, layer, kind, side = match.groups()
            if stage not in ids:
                raise ValueError(f"Unknown native stage: {stage}")
            original_path = template_dir / filename
            if (
                hashlib.sha256(original_path.read_bytes()).hexdigest()
                != job["source_sha256"]
            ):
                raise ValueError(f"Template changed since generation: {filename}")
            extension = (
                artwork_dir
                / "completed"
                / Path(filename).with_name(Path(filename).stem + "_extension.png")
            )
            with Image.open(original_path) as original, Image.open(extension) as image:
                validate_extension(original, image, job["edit_x_bounds"])
                data = None
                if layers is not None:
                    layer_info = layers[filename]
                    info = layer_info["metadata"]
                    folder = REPO / layer_info["source"]
                    key = (stage, bool(info["flags"] & 0x200))
                    if key not in palettes:
                        if key[1]:
                            raw = (
                                template_dir.parent / "art-shared-clut.bin"
                            ).read_bytes()
                            palettes[key] = struct.unpack("<12288H", raw)[4096:8192]
                        else:
                            path = next(
                                (
                                    REPO / "assets" / base / f"{stage.lower()}_clut.png"
                                    for base in ("st", "boss")
                                    if (
                                        REPO
                                        / "assets"
                                        / base
                                        / f"{stage.lower()}_clut.png"
                                    ).exists()
                                ),
                                None,
                            )
                            if path is None:
                                raise ValueError(f"Missing baseline palette: {stage}")
                            with Image.open(path) as colors:
                                if colors.size != (16, 256):
                                    raise ValueError(
                                        f"Invalid baseline palette: {path}"
                                    )
                                palettes[key] = tuple(
                                    (r >> 3)
                                    | (g >> 3) << 5
                                    | (b >> 3) << 10
                                    | (0x8000 if a == 0 else 0)
                                    for r, g, b, a in colors.convert("RGBA").getdata()
                                )
                    path = folder / info["tiledef"]
                    if path not in definitions:
                        definition = json.loads(path.read_text())
                        definitions[path] = tuple(
                            (folder / definition[k]).read_bytes()
                            for k in ("tiles", "cluts")
                        )
                    pages, cluts = definitions[path]
                    raw = (folder / info["data"]).read_bytes()
                    layout = struct.unpack(f"<{len(raw) // 2}H", raw)
                    mapped = index_extension(
                        image,
                        layout,
                        pages,
                        cluts,
                        palettes[key],
                        (info["right"] - info["left"] + 1) * 256,
                        job["edit_x_bounds"],
                    )
                    encoded = io.BytesIO()
                    mapped.save(encoded, format="PNG")
                    data = encoded.getvalue()
            for edge in ("L", "R") if side == "both" else (side[0].upper(),):
                name = f"{ids[stage]:02X}_{layer}_{'B' if kind == 'bg' else 'F'}_{edge}.png"
                ready.append((extension, name, filename))
                if data is not None:
                    indexed.append((data, f"indexed/{name}", filename))
    output_dir.mkdir(parents=True, exist_ok=True)
    for source, name, _ in ready + indexed:
        destination = output_dir / name
        destination.parent.mkdir(parents=True, exist_ok=True)
        with tempfile.NamedTemporaryFile(dir=destination.parent, delete=False) as file:
            temporary = Path(file.name)
        try:
            temporary.write_bytes(
                source if isinstance(source, bytes) else source.read_bytes()
            )
            temporary.replace(destination)
        finally:
            temporary.unlink(missing_ok=True)
    indexed_names = {name for _, name, _ in indexed}
    for _, name, _ in ready:
        if f"indexed/{name}" not in indexed_names:
            (output_dir / "indexed" / name).unlink(missing_ok=True)
    report = {
        "edges": len(ready),
        "indexed_maps": len(indexed),
        "files": [dict(file=n, template=t) for _, n, t in ready],
    }
    (output_dir / "index.json").write_text(json.dumps(report, indent=2) + "\n")
    return report


def main():
    parser = argparse.ArgumentParser(__doc__)
    parser.add_argument(
        "--artwork-dir",
        type=Path,
        default=REPO / "build/local-pc/widescreen-ai-inpaint",
    )
    parser.add_argument(
        "--template-dir",
        type=Path,
        default=REPO / "build/local-pc/widescreen-artwork-kit",
    )
    parser.add_argument(
        "--output-dir", type=Path, default=REPO / "assets/pc/widescreen"
    )
    args = parser.parse_args()
    report = build(args.artwork_dir, args.template_dir, args.output_dir)
    print(f"Prepared {report['edges']} native widescreen edges in {args.output_dir}")


if __name__ == "__main__":
    main()
