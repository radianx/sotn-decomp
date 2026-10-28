#!/usr/bin/env python3
# SPDX-License-Identifier: AGPL-3.0-or-later
"""Prepare a CHD as a cached CUE/BIN using MAME's chdman; never alter the source."""

import hashlib
import os
from pathlib import Path
import shutil
import subprocess
import sys
import tempfile

ROOT = Path(__file__).resolve().parent.parent


def prepare(source: Path) -> Path:
    source = source.resolve(strict=True)
    if source.suffix.lower() != ".chd":
        return source
    chdman = os.environ.get("CHDMAN") or shutil.which("chdman")
    if not chdman:
        local = ROOT / "build/local-pc/deps/usr/bin/chdman"
        if local.is_file():
            chdman = str(local)
    if not chdman:
        raise RuntimeError(
            "CHD input requires chdman (MAME tools); install mame-tools or set CHDMAN"
        )
    digest = hashlib.sha256()
    with source.open("rb") as stream:
        for chunk in iter(lambda: stream.read(1024 * 1024), b""):
            digest.update(chunk)
    cache = ROOT / "build/pc-discs" / digest.hexdigest()
    cue = cache / "disc.cue"
    if cue.is_file() and (cache / "disc.bin").is_file():
        return cue
    cache.parent.mkdir(parents=True, exist_ok=True)
    with tempfile.TemporaryDirectory(prefix="decode-", dir=cache.parent) as tmp:
        temporary = Path(tmp)
        subprocess.run(
            [
                chdman,
                "extractcd",
                "-i",
                str(source),
                "-o",
                str(temporary / "disc.cue"),
                "-ob",
                str(temporary / "disc.bin"),
            ],
            check=True,
            stdout=sys.stderr,
        )
        if (
            not (temporary / "disc.cue").is_file()
            or not (temporary / "disc.bin").stat().st_size
        ):
            raise RuntimeError("chdman did not produce a complete disc")
        # Publish the pair only after extraction succeeds.
        if not cache.exists():
            temporary.rename(cache)
    return cue


if __name__ == "__main__":
    try:
        print(prepare(Path(sys.argv[1])))
    except (OSError, RuntimeError, subprocess.CalledProcessError, IndexError) as error:
        sys.exit(str(error))
