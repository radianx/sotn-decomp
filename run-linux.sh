#!/bin/sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu
repo_dir=$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)
cd "$repo_dir"
executable="$repo_dir/build/local-pc/native/sotn"
if [ ! -x "$executable" ]; then
    echo "Native executable missing. See docs/native_linux.md." >&2
    exit 1
fi
exec "$executable" --disk "$repo_dir/disks/sotn.us.cue" "$@"
