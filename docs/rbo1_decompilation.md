# Local RBO1 Decompilation Checkpoint

Recorded on 2026-10-23 on `decomp/local-us-expansion`, based on
`7bc54d8157b6bed77e6bd15e5db9461a734fe1e5`. Changes remain local and uncommitted.

## Scope and Result

Recovered **all 19 previously unfinished US functions**, totaling **11,092
instruction bytes**. These cover Beelzebub's main controller, shared health,
body parts, attached and falling chains, flies, maggots, flame effects,
breakables, arena gates, and positioning and animation helpers.

| Source | Functions | Bytes |
| --- | ---: | ---: |
| `src/boss/rbo1/unk_12274.c` | 3 | 3,344 |
| `src/boss/rbo1/e_beelzebub_chains.c` | 1 | 1,912 |
| `src/boss/rbo1/e_beelzebub_parts.c` | 13 | 4,328 |
| `src/boss/rbo1/e_explosion_flame.c` | 1 | 1,132 |
| `src/boss/rbo1/e_boss_room.c` | 1 | 376 |

No `.NON_MATCHING` markers remain in the US RBO1 linker map. This completes
this overlay's outstanding US functions, not the entire game.

## Basis and Layout

The local disc assembly is authoritative. Existing giant-brother helpers,
Galamoth code, shared breakables, and particle effects supplied reference
patterns. Local m2c analysis and bounded compiler comparisons helped recover
types and instruction ordering. No public scratch implementation was imported
or uploaded.

`ET_Beelzebub` describes body-part and movement state. `ET_BeelzebubChain`
stores seven segment counts and the parent entity. `ET_BeelzebubFlame`
preserves the flame handler's unsigned particle index and acceleration fields.

The inferred source splits at `0x80192F84`, `0x801936FC`, and `0x801947E4`
preserve string and jump-table order. Four bytes of original rodata padding
at `0x80191E28` remain unchanged. Separating the chain spacing calculation
into intermediate values and keeping the outer loop's updates in its header
reproduces the original compiler's arithmetic and branch layout.

## Validation

```sh
source build/contribution/env.sh
VERSION=us .venv/bin/python3 tools/builds/gen.py
GOMAXPROCS=4 make build VERSION=us
sha1sum --check config/check.us.sha
cmp disks/us/BOSS/RBO1/RBO1.BIN build/us/RBO1.BIN
```

All **115 US reference checksums** pass. The complete **139,104-byte** RBO1
binary and every recovered function's instruction bytes match the disc.
RBO1 SHA-256:
`b7451826ff30b3ce3fceff61170efd82c03e83898d34c31ed34de536e5026e19`.

The five changed C files pass clang-format and the project linter.
PS1 field-offset assertions, native entity-size assertions, and
`git diff --check` pass. Evidence and source snapshots are under ignored
`build/local-decomp/rbo1/checkpoint-19/` and `build/local-decomp/rbo1/evidence.json`.
The US linker maps contain **203 remaining assembly markers** across the project.

## Matching Details and Limits

The main controller, body-part handler, and maggot handler retain unused
`Collider` variables for stack-frame matching, marked `!FAKE`. Two
animation-state helpers retain the original four-entry writes into two-element
arrays, annotated `@bug`; binary equivalence does not repair those C accesses.

No emulator playthrough or full PSP, HD, Saturn, or PC build was performed.
