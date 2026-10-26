#!/usr/bin/env python3
# SPDX-License-Identifier: AGPL-3.0-or-later
"""Decode the user's extracted US movies for the native player (requires FFmpeg)."""

import json
from pathlib import Path
import subprocess

ROOT = Path(__file__).resolve().parent.parent
DEST = ROOT / "build/pc-movies"
MOVIES = {"LOGO15XA": 143, "OPN_WS": 922, "TYK_WS": 545, "END_WS": 740}


def main():
    DEST.mkdir(parents=True, exist_ok=True)
    for name, frames in MOVIES.items():
        source = ROOT / "disks/us" / (name + ".STR")
        info = json.loads(
            subprocess.check_output(
                ["ffprobe", "-v", "error", "-show_streams", "-of", "json", str(source)]
            )
        )
        video = next(s for s in info["streams"] if s["codec_type"] == "video")
        if (video["width"], video["height"], video["r_frame_rate"]) != (
            320,
            240,
            "15/1",
        ):
            raise ValueError(f"Unexpected movie format: {source}")
        for suffix, options in (
            (
                "rgb",
                [
                    "-map",
                    "0:v:0",
                    "-frames:v",
                    str(frames),
                    "-pix_fmt",
                    "rgb24",
                    "-f",
                    "rawvideo",
                ],
            ),
            (
                "wav",
                [
                    "-map",
                    "0:a:0",
                    "-ac",
                    "2",
                    "-ar",
                    "44100",
                    "-c:a",
                    "pcm_s16le",
                    "-f",
                    "wav",
                ],
            ),
        ):
            target = DEST / f"{name}.{suffix}"
            temporary = target.with_suffix(target.suffix + ".tmp")
            result = subprocess.run(
                [
                    "ffmpeg",
                    "-v",
                    "error",
                    "-y",
                    "-i",
                    str(source),
                    *options,
                    str(temporary),
                ],
                check=True,
                stderr=subprocess.PIPE,
                text=True,
            )
            target.with_suffix("." + suffix + ".decode.log").write_text(result.stderr)
            if not temporary.stat().st_size or (
                suffix == "rgb" and temporary.stat().st_size != frames * 320 * 240 * 3
            ):
                raise ValueError(f"Invalid decoded movie: {temporary}")
            temporary.replace(target)
        print(f"Prepared {name}", flush=True)


if __name__ == "__main__":
    main()
