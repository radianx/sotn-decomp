# Local BO5 Decompilation Complete

Recorded on 2026-10-23 on `decomp/local-us-expansion`, based on
`7bc54d8157b6bed77e6bd15e5db9461a734fe1e5`. Changes remain local and uncommitted.

## Scope and Result

Recovered all 11 remaining US functions: **18,780 instruction bytes** covering
Hippogryph, its fire and debris effects, arena doors, camera boundaries, music,
Maria's cutscene, and dialogue rendering. Entity extensions in `include/entity.h`
describe the newly recovered fields.

| Source | Functions | Bytes |
| --- | ---: | ---: |
| `src/boss/bo5/e_hippogryph.c` | 4 | 9,692 |
| `src/boss/bo5/e_rbo3door.c` | 1 | 744 |
| `src/boss/bo5/e_unk_16.c` | 1 | 768 |
| `src/boss/bo5/e_unk_29.c` | 1 | 264 |
| `src/boss/bo5/e_richter_prologue.c` | 3 | 2,984 |
| `src/boss/bo5/e_cutscene_dialogue.c` | 1 | 4,328 |

The US linker map contains no BO5 `.NON_MATCHING` markers. The dialogue file
retains its PSP assembly inclusion under `VERSION_PSP`. Data and provisional
symbol names remain outside this code-conversion checkpoint.

## Basis

Implementations were reconstructed from the local US assembly and m2c analysis.
Existing repository code supplied close counterparts: RBO3's doors, ST0's camera
boundaries, BO3's music handling, and TOP's dialogue interpreter. BO5-specific
differences were checked against the original instructions. No public scratch
implementation was imported for these functions.

## Validation

```sh
source build/contribution/env.sh
GOMAXPROCS=4 make build VERSION=us
sha1sum --check config/check.us.sha
cmp disks/us/BOSS/BO5/BO5.BIN build/us/BO5.BIN
cargo test --offline --manifest-path tools/lints/sotn-lint/Cargo.toml
```

All **115 US reference checksums** pass. The complete **218,672-byte** BO5 binary
and each recovered function's instruction bytes match the disc. BO5 SHA-256:
`b3beb8a8d5dfca90d9e60d28a022d78ae2bd75ea1fe2edf501a423904c776228`.

Changed C files pass clang-format and the project linter without transformations.
Layout assertions verify the PS1 field offsets and unchanged entity/extension
sizes; native 64-bit aggregate sizes also remain unchanged. These header checks
do not constitute a PC build.

The binary comparison exposed a linter defect: the highest three player-status
bits were mapped incorrectly. `tools/lints/sotn-lint/src/player_status.rs` now
maps all 32 bits correctly. Its new regression test failed before the correction;
all **182 linter tests** pass afterward.

## Matching Details and Limits

Two inferred constructs are marked `!FAKE`: reserved words retain Hippogryph's
death-effect scratch offsets, and an explicit volatile write retains both
original dialogue-completion flag stores. Neither establishes the original
source spelling. Original gameplay quirks remain intact, including the death
movement override marked `@bug`.

No emulator playthrough or full PSP, HD, Saturn, or PC build was performed.
Evidence, checkpoints, per-function hashes, and experiments are under the ignored
`build/local-decomp/bo5/` directory. Follow `CONTRIBUTING.md` before any future
submission; contributors must author their own commit messages and PRs.
