# SPDX-License-Identifier: AGPL-3.0-or-later
import unittest
import hashlib
import json
import tempfile
import struct
from pathlib import Path
from unittest.mock import patch

from PIL import Image

from build_widescreen_pack import (
    build,
    index_extension,
    nearest_color,
    stage_ids,
    validate_extension,
)


class WidescreenPackTest(unittest.TestCase):
    def test_native_stage_ids(self):
        ids = stage_ids()
        self.assertEqual((ids["ST0"], ids["ARE"], ids["NO3"]), (31, 10, 65))

    def test_layer_holes_and_existing_art_are_protected(self):
        original = Image.new("RGBA", (296, 256))
        original.putpixel((20, 10), (40, 80, 24, 255))
        extension = Image.new("RGBA", original.size)
        extension.putpixel((0, 10), (32, 64, 24, 255))
        validate_extension(original, extension, [0, 20])
        extension.putpixel((0, 11), (32, 64, 24, 255))
        with self.assertRaisesRegex(ValueError, "intentional alpha"):
            validate_extension(original, extension, [0, 20])
        extension.putpixel((0, 11), (0, 0, 0, 0))
        extension.putpixel((20, 10), (32, 64, 24, 255))
        with self.assertRaisesRegex(ValueError, "protected artwork"):
            validate_extension(original, extension, [0, 20])

    def test_dimensions_are_not_rescaled(self):
        with self.assertRaisesRegex(ValueError, "dimensions"):
            validate_extension(
                Image.new("RGBA", (296, 256)), Image.new("RGBA", (296, 255)), [0, 20]
            )

    def test_index_map_uses_each_physical_boundary_and_preserves_alpha(self):
        image = Image.new("RGBA", (296, 256))
        image.putpixel((0, 32), (32, 0, 0, 255))
        image.putpixel((295, 32), (0, 0, 0, 128))
        before = image.tobytes()
        layout = [0] * (32 * 16)
        for row in range(16):
            layout[row * 32], layout[row * 32 + 31] = 1, 2
        palette = [0] * 4096
        palette[2 * 16 + 1] = 4
        palette[3 * 16 + 1] = 0x3E0
        palette[3 * 16 + 2] = 0x8000
        result = index_extension(
            image, layout, [0, 4, 7], [0, 2, 3], palette, 512, [0, 20, 276, 296]
        )
        self.assertEqual(result.getpixel((0, 32)), (2, 1, 4, 255))
        self.assertEqual(result.getpixel((295, 32)), (3, 2, 7, 128))
        self.assertEqual(
            result.getchannel("A").tobytes(), image.getchannel("A").tobytes()
        )
        self.assertEqual(image.tobytes(), before)

    def test_invalid_index_source_is_rejected(self):
        image = Image.new("RGBA", (296, 256))
        image.putpixel((0, 0), (0, 0, 0, 255))
        palette = [0x8000] * 4096
        with self.assertRaisesRegex(ValueError, "layout dimensions"):
            index_extension(image, [], [0, 1], [0, 2], palette, 256, [0, 20])
        with self.assertRaisesRegex(ValueError, "boundary tile"):
            index_extension(image, [0] * 256, [0, 1], [0, 2], palette, 256, [0, 20])
        with self.assertRaisesRegex(ValueError, "tile page"):
            index_extension(image, [1] * 256, [0, 24], [0, 2], palette, 256, [0, 20])
        with self.assertRaisesRegex(ValueError, "no opaque colors"):
            nearest_color((0,) * 16, 0)

    def test_invalid_replacement_preserves_the_installed_pack(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            filename = "stages/ST0/layer_00_fg_left_paint.png"
            original_path = root / "templates" / filename
            original_path.parent.mkdir(parents=True)
            original = Image.new("RGBA", (296, 256))
            original.putpixel((20, 10), (40, 80, 24, 255))
            original.save(original_path)
            source_hash = hashlib.sha256(original_path.read_bytes()).hexdigest()
            job = dict(
                status="draft-verified-size-pixels-alpha",
                outputs=[filename],
                source_sha256=source_hash,
                edit_x_bounds=[0, 20],
            )
            artwork = root / "artwork"
            extension_path = (
                artwork
                / "completed"
                / Path(filename).with_name(Path(filename).stem + "_extension.png")
            )
            extension_path.parent.mkdir(parents=True)
            (artwork / "jobs.json").write_text(json.dumps(dict(jobs=[job])))
            extension = Image.new("RGBA", original.size)
            extension.putpixel((0, 10), (32, 64, 24, 255))
            extension.save(extension_path)
            output = root / "installed"
            self.assertEqual(build(artwork, root / "templates", output)["edges"], 1)
            installed = (output / "1F_00_F_L.png").read_bytes()
            extension.putpixel((20, 10), (32, 64, 24, 255))
            extension.save(extension_path)
            with self.assertRaises(ValueError):
                build(artwork, root / "templates", output)
            self.assertEqual((output / "1F_00_F_L.png").read_bytes(), installed)
            self.assertEqual(
                hashlib.sha256(original_path.read_bytes()).hexdigest(), source_hash
            )
            self.assertEqual(len(list(output.iterdir())), 2)

    def test_indexed_install_is_validated_before_replacing_the_pack(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            filename = "stages/ST0/layer_00_fg_both_paint.png"
            template = root / "templates" / filename
            template.parent.mkdir(parents=True)
            original = Image.new("RGBA", (296, 256))
            for x in (20, 275):
                original.putpixel((x, 10), (32, 64, 24, 255))
            original.save(template)
            artwork = root / "artwork"
            extension = (
                artwork / "completed/stages/ST0/layer_00_fg_both_paint_extension.png"
            )
            extension.parent.mkdir(parents=True)
            image = Image.new("RGBA", original.size)
            for x in (0, 295):
                image.putpixel((x, 10), (32, 64, 24, 255))
            image.save(extension)
            job = dict(
                status="draft-verified-size-pixels-alpha",
                outputs=[filename],
                source_sha256=hashlib.sha256(template.read_bytes()).hexdigest(),
                edit_x_bounds=[0, 20, 276, 296],
            )
            (artwork / "jobs.json").write_text(json.dumps(dict(jobs=[job])))
            folder = root / "assets/st/st0"
            folder.mkdir(parents=True)
            (folder / "map.bin").write_bytes(struct.pack("<256H", *([1] * 256)))
            (folder / "pages.bin").write_bytes(bytes([0, 4]))
            (folder / "cluts.bin").write_bytes(bytes([0, 2]))
            (folder / "defs.json").write_text(
                json.dumps(dict(tiles="pages.bin", cluts="cluts.bin"))
            )
            palette = Image.new("RGBA", (16, 256), (0, 0, 0, 255))
            palette.putpixel((1, 2), (32, 64, 24, 255))
            palette.save(root / "assets/st/st0_clut.png")
            manifest = root / "templates/manifest.json"
            manifest.write_text(
                json.dumps(
                    dict(
                        layers=[
                            dict(
                                stage="ST0",
                                source="assets/st/st0",
                                metadata=dict(
                                    flags=1,
                                    tiledef="defs.json",
                                    data="map.bin",
                                    left=0,
                                    right=0,
                                ),
                                templates=[dict(file=filename)],
                            )
                        ]
                    )
                )
            )
            output = root / "installed"
            with patch("build_widescreen_pack.REPO", root), patch(
                "build_widescreen_pack.stage_ids", return_value={"ST0": 31}
            ):
                report = build(artwork, root / "templates", output)
                self.assertEqual((report["edges"], report["indexed_maps"]), (2, 2))
                self.assertEqual(
                    (output / "1F_00_F_L.png").read_bytes(), extension.read_bytes()
                )
                with Image.open(output / "indexed/1F_00_F_L.png") as data:
                    self.assertEqual(data.getpixel((0, 10)), (2, 1, 4, 255))
                    self.assertEqual(
                        data.getchannel("A").tobytes(), image.getchannel("A").tobytes()
                    )
                installed = {
                    p.relative_to(output): p.read_bytes()
                    for p in output.rglob("*")
                    if p.is_file()
                }
                (folder / "pages.bin").write_bytes(bytes([0, 24]))
                with self.assertRaisesRegex(ValueError, "tile page"):
                    build(artwork, root / "templates", output)
                self.assertEqual(
                    installed,
                    {
                        p.relative_to(output): p.read_bytes()
                        for p in output.rglob("*")
                        if p.is_file()
                    },
                )
                manifest.unlink()
                self.assertEqual(
                    build(artwork, root / "templates", output)["indexed_maps"], 0
                )
                self.assertFalse(list((output / "indexed").iterdir()))


if __name__ == "__main__":
    unittest.main()
