# Local BO2 Decompilation Complete

Recorded on 2026-10-23 on `decomp/local-us-expansion`, based on
`7bc54d8157b6bed77e6bd15e5db9461a734fe1e5`. Changes remain local and uncommitted.

## Scope and Result

Recovered all 11 remaining US functions: **17,528 instruction bytes** covering
Werewolf's AI, joint attacks with Minotaur, projectiles, death flames, battle
progression, torches, and the two Richter conversations. The US linker map has
no BO2 `.NON_MATCHING` markers, and `src/boss/bo2/` has no assembly inclusions.
Minotaur's main AI was already decompiled.

| Source | Functions | Bytes |
| --- | ---: | ---: |
| `src/boss/bo2/e_boss.c` | 1 | 2,056 |
| `src/boss/bo2/e_boss_torch.c` | 1 | 404 |
| `src/boss/bo2/e_cutscene_dialogue.c` | 1 | 4,396 |
| `src/boss/bo2/unk_26EF8.c` | 3 | 1,912 |
| `src/boss/bo2/unk_337D0.c` | 5 | 8,760 |

`ET_WerewolfBoss` describes movement targets, attack transitions, and shared
signals; `ET_MinotaurWerewolf` describes the battle controller. Two existing
functions moved intact beside that controller into `e_boss.c`. Splat boundaries
assign the recovered torch tables and actor names to their C sources.
Provisional names and other raw data remain.

## Basis

Implementations were reconstructed from local US assembly, with m2c used for
analysis. Existing repository code supplied reusable patterns: ARE's torch
header, RARE's Werewolf effects, BO5's dialogue interpreter, and BO2's Minotaur
movement and signals. No public scratch implementation was imported for this
checkpoint. BO2-specific timings, palette choices, attack coordination,
conversation scripts, skip conditions, and completion flags were retained.

## Validation

```sh
source build/contribution/env.sh
VERSION=us .venv/bin/python3 tools/builds/gen.py
GOMAXPROCS=4 make build VERSION=us
sha1sum --check config/check.us.sha
cmp disks/us/BOSS/BO2/BO2.BIN build/us/BO2.BIN
```

All **115 US reference checksums** pass after the shared-header changes. The
complete **223,540-byte** BO2 binary and each recovered function's instruction
bytes match the disc. BO2 SHA-256:
`7789c62ec7d91163b688a853c1616c467d0a146c412857a10d12fef01f1e429e`.

All six changed BO2 C files are unchanged by the project linter. Changed C files
and headers pass clang-format; `git diff --check` passes. Layout assertions
verify the new PS1 field offsets and unchanged entity/extension sizes on
32-bit and native 64-bit builds. These assertions do not constitute a PC build.

## Matching Details and Limits

The source split at `func_us_801A3E04` is inferred from jump-table alignment;
it does not establish the original filenames. Werewolf's AI retains two unused
stack words, and the dialogue interpreter uses two volatile accesses to preserve
three original completion-flag writes. These matching requirements are marked
`!FAKE`.

Original quirks remain and are marked `@bug`: cutscene input is immediately
cleared in two states, a projectile accesses its primitive after destruction,
and the US flame effect passes an uninitialized address to the GTE output macro.
Binary equivalence preserves these behaviors; it does not repair them.

No emulator playthrough or full PSP, HD, Saturn, or PC build was performed.
Evidence, per-function hashes, layout checks, and source checkpoints are under
ignored `build/local-decomp/bo2/`. The refreshed US linker-map inventory contains
232 remaining assembly markers across other overlays. Follow `CONTRIBUTING.md`
before any future submission; contributors must author their own commit messages
and PRs.
