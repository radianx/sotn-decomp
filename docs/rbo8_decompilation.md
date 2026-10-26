# Local RBO8 Decompilation Checkpoint

Recorded on 2026-10-23 on `decomp/local-us-expansion`, based on
`7bc54d8157b6bed77e6bd15e5db9461a734fe1e5`. Changes remain local and uncommitted.

## Scope and Result

Recovered **all ten remaining US functions**, totaling **15,196 instruction
bytes**. These cover Galamoth's main AI, body parts, boundary check, body
polygon, lightning sweep, branching lightning, lightning anchor, battle
progression, particles, and arena gates.

| Source | Functions | Bytes |
| --- | ---: | ---: |
| `src/boss/rbo8/unk_1546C.c` | 1 | 76 |
| `src/boss/rbo8/unk_15868.c` | 6 | 12,980 |
| `src/boss/rbo8/e_boss.c` | 2 | 1,308 |
| `src/boss/rbo8/e_boss_doors.c` | 1 | 832 |

No `INCLUDE_ASM` calls remain in `src/boss/rbo8/`, and the US RBO8 linker map
has no remaining nonmatching markers.

## Basis and Layout

Local US assembly is the authority, with m2c used for analysis. Existing Shaft
lightning, Catacombs particles and gates, and giant-brother helpers supplied
reference patterns. Galamoth-specific timings, trajectories, tile positions,
damage hitboxes, and battle signals were retained. Local decomp-permuter and
focused source-variant checks helped resolve body-part register allocation.
No public scratch implementation was imported or uploaded.

`ET_Galamoth` describes the boss and body-part state; `ET_GalamothLightning`
describes the primitive chain, steering, firing flag, sweep offset, and parent
pointer. The main AI's debug strings now belong to C rodata starting at
`0x80194EC8`. Source splits at `0x8019953C` and `0x80199A58` preserve the
original jump-table packing; the filenames are inferred, not evidence of
original source boundaries.

## Validation

```sh
source build/contribution/env.sh
VERSION=us .venv/bin/python3 tools/builds/gen.py
GOMAXPROCS=4 make build VERSION=us
sha1sum --check config/check.us.sha
cmp disks/us/BOSS/RBO8/RBO8.BIN build/us/RBO8.BIN
```

All **115 US reference checksums** pass. The complete **161,212-byte** RBO8
binary and each recovered function's instruction bytes match the disc.
RBO8 SHA-256:
`e3c97b9c2d17a5502634b244ff142336ae1e71e5379ea5491e772e1ade37efc9`.

All four changed C files pass the project linter and clang-format.
`git diff --check` and PS1 field-offset assertions pass. Native 64-bit entity
and extension sizes remain unchanged; this is not a full PC build.
Evidence, source snapshots, and per-function hashes are under ignored
`build/local-decomp/rbo8/`, including `checkpoint-10/`. The US linker maps
contain 222 remaining assembly markers across the project.

## Matching Details and Limits

The boundary helper retains an unused `Collider` to match its stack frame.
The battle controller views the two 16-bit prize-drop entries as a 32-bit flag
word; its different declaration is marked `!FAKE` and needs review for ports
or link-time optimization. Both choices preserve the PS1 binary.

Original lightning quirks remain annotated `@bug`: `y1` is updated without
initialization from `y0`, and `closeToTarget` can be read uninitialized after
firing. Binary equivalence preserves these behaviors rather than repairing
them. No emulator playthrough or full PSP, HD, Saturn, or PC build was performed.
