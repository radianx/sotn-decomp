#!/usr/bin/env python3
# SPDX-License-Identifier: AGPL-3.0-or-later
"""Native launcher with CHD preparation and predictable repository paths."""

import os
from pathlib import Path
import sys
from prepare_pc_disc import prepare

ROOT = Path(__file__).resolve().parent.parent


def main():
    executable = ROOT / "build/local-pc/native/sotn"
    if not executable.is_file():
        sys.exit("Native executable missing. See docs/native_linux.md.")
    args = sys.argv[1:]
    if "--help" in args:
        os.execv(executable, [str(executable), *args])
    disc = ROOT / "disks/sotn.us.cue"
    # Match the executable's last --disk argument precedence.
    for i, arg in enumerate(args):
        if arg == "--disk" and i + 1 < len(args):
            disc = Path(args[i + 1])
    try:
        cue = prepare(disc)
    except Exception as error:
        sys.exit(str(error))
    for i, arg in enumerate(args):
        if arg == "--disk" and i + 1 < len(args):
            args[i + 1] = str(cue)
    os.chdir(ROOT)
    os.execv(executable, [str(executable), "--disk", str(cue), *args])


if __name__ == "__main__":
    main()
