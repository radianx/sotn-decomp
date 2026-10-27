#!/bin/sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu
repo_dir=$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)
cd "$repo_dir"
exec python3 "$repo_dir/tools/run_pc.py" "$@"
