# Local BO7 Decompilation Complete

Recorded on 2026-10-23 on `decomp/local-us-expansion`, based on
`7bc54d8157b6bed77e6bd15e5db9461a734fe1e5`. Changes remain local and uncommitted.

## Scope and Result

Recovered all 21 remaining US functions: **18,312 instruction bytes** covering
Cerberus, projectiles, death effects, battle progression, arena gates, secret
walls, breakables, and shared effects. The US linker map contains no BO7
`.NON_MATCHING` markers, and `src/boss/bo7/` contains no assembly inclusions.

| Source | Functions | Bytes |
| --- | ---: | ---: |
| `src/boss/bo7/unk_14CE0.c` | 4 | 3,952 |
| `src/boss/bo7/e_boss.c` | 2 | 2,552 |
| `src/boss/bo7/unk_13258.c` | 2 | 1,672 |
| `src/boss/bo7/e_demon_switch_wall.c` | 3 | 1,552 |
| `src/boss/bo7/e_breakable_wall.c` | 2 | 2,188 |
| `src/boss/bo7/e_debug_cerberus_gate.c` | 1 | 1,380 |
| `src/boss/bo7/e_misc.c` | 7 | 5,016 |

`ET_Cerberus` describes the boss's timer, retreat direction, projectile selection,
and shot counter. Existing shared effect and breakable headers replace duplicated
implementations. Splat data boundaries now assign the recovered tables to their
C sources. Provisional symbol names and other raw data remain.

## Basis

Implementations were reconstructed from the local US assembly, with m2c used
for analysis. Existing repository counterparts supplied the arena code:
`src/st/chi/en_demon_switch_wall.c`, `en_breakable_wall.c`, and
`en_debug_cerberus_gate.c`. RBO0's floor-collision helper and RBO3/RBO4's flame
effects supplied additional patterns. No public scratch implementation was
imported for this checkpoint.

BO7-specific differences were retained: its switch accepts any hit, breakables
play two sounds, and the gate follows battle flags rather than controller input.
The gate also resets after allocation failure and has a separate wait for the
boss's defeat before rising.

## Validation

```sh
source build/contribution/env.sh
VERSION=us .venv/bin/python3 tools/builds/gen.py
GOMAXPROCS=4 make build VERSION=us
sha1sum --check config/check.us.sha
cmp disks/us/BOSS/BO7/BO7.BIN build/us/BO7.BIN
```

All **115 US reference checksums** pass after the shared-header changes. The
complete **144,480-byte** BO7 binary and each recovered function's instruction
bytes match the disc. BO7 SHA-256:
`325969e00975cfc36c4d26aa6c702f7dc76465087d5fe4df75cb4c66e8b8baa8`.

All seven changed BO7 C files are unchanged by the project linter. Changed C
files and headers pass clang-format; `git diff --check` passes. Layout assertions
verify Cerberus's PS1 field offsets and unchanged entity/extension sizes on
32-bit and native 64-bit builds. These assertions do not constitute a PC build.

## Matching Details and Limits

The source split at `func_us_80195C50` is inferred from the required jump-table
packing: compiling both controllers in one translation unit adds four padding
bytes. This is not proof of the original filenames or source layout.

The original battle controller checks the primitive pointer instead of the
second draw-environment allocation result. That behavior is retained and marked
`@bug`. Binary equivalence preserves original quirks; it does not repair them.

No emulator playthrough or full PSP, HD, Saturn, or PC build was performed.
Evidence, per-function hashes, layout checks, and source checkpoints are under
the ignored `build/local-decomp/bo7/` directory. The refreshed US linker-map
inventory contains 243 remaining assembly markers across other overlays.
Follow `CONTRIBUTING.md` before any future submission; contributors must author
their own commit messages and PRs.
