# Local RBO2 Decompilation Checkpoint

Recorded on 2026-10-25 on `decomp/local-us-expansion`, based on
`7bc54d8157b6bed77e6bd15e5db9461a734fe1e5`. Changes remain local and uncommitted.

## Scope and Result

Recovered **all 28 previously unfinished US functions**, totaling **23,520
instruction bytes**. These cover both of Death's form controllers, skull attack,
ball launchers, spinning and returning scythes, body parts, afterimages, flames,
breakables, arena
gates, dialogue playback, cutscene positioning and camera controls, and joint
animation helpers. The dialogue actor-name table and strings are also in C.

| Source | Functions | Bytes |
| --- | ---: | ---: |
| `src/boss/rbo2/unk_1B284.c` | 7 | 8,776 |
| `src/boss/rbo2/e_death_skull.c` | 2 | 1,336 |
| `src/boss/rbo2/e_death_second_form.c` | 14 | 6,824 |
| `src/boss/rbo2/e_debug_cerberus_gate.c` | 1 | 1,380 |
| `src/boss/rbo2/e_cutscene_dialogue.c` | 1 | 4,312 |
| `src/boss/rbo2/e_cutscene_actors.c` | 2 | 196 |
| `src/boss/rbo2/func_us_801a17c8.c` | 1 | 696 |

## Basis and Layout

The local disc assembly is authoritative. Shared breakables and angle helpers,
Beelzebub's joint animation helpers, existing Death flame effects, and the BO7
arena gate and BO5 dialogue handler supplied reference patterns. Local m2c
analysis and compiler comparisons helped recover the remaining logic.
A local decomp-permuter run
provided expression candidates; accepted changes were reviewed and checked
in the complete overlay. No scratchpad code was uploaded or imported.

`ET_DeathFirstForm` describes steering, attack signals, and the transformation
effect. `ET_DeathSecondForm` describes the boss's joint and animation state.
`ET_DeathBossScythe` records the returning scythe's angle, speed, timer,
and owner. `ET_DeathBossProjectile` describes the skull's timer, steering,
owner and return target, projectile speed, and the launcher's ready and
returned-skull flags.
Existing entity IDs and uncertain function names are preserved.

The skull and second-form code now have separate translation units and Splat
segments. Their debug strings and jump tables retain the original binary order.

## Validation

```sh
source build/contribution/env.sh
GOMAXPROCS=4 make build VERSION=us
sha1sum --check config/check.us.sha
cmp disks/us/BOSS/RBO2/RBO2.BIN build/us/RBO2.BIN
```

All **115 US reference checksums** pass. The complete **190,792-byte** RBO2
binary and every recovered function's instruction bytes match the disc.
RBO2 SHA-256:
`8cd235540d1b5967f262e53ef8cdcd0ce0415cbc438a7c29615549a4b56f8719`.

The seven changed C files pass clang-format and the project linter.
PS1 field-offset assertions, native entity-size assertions, and
`git diff --check` pass. Evidence and source snapshots are under ignored
`build/local-decomp/rbo2/checkpoint-27/` and
`build/local-decomp/rbo2/checkpoint-28/`. The US linker maps contain **three
remaining assembly markers** across the project.

## Matching Details and Limits

The ball and spinning-scythe handler reuses its horizontal-coordinate temporary
for trigonometric results after the coordinate is no longer needed. Saving the
limited angle before `rcos` preserves the original register allocation. Its
debug string remains beside the controller so the rodata padding also matches.

The second-form controller and body-part handler retain unused `Collider`
locals for stack-frame matching, marked `!FAKE`.
Two joint animation helpers preserve the original four-entry
writes into two-element arrays, annotated `@bug`; binary equivalence does not
repair those C accesses. The returning scythe preserves the original outbound
angle behavior and its separate turn limits on the return path.

The skull reuses its horizontal-coordinate temporary for the outbound angle
calculation. The controller initializes its previous-part pointer after facing
the player; that placement reproduces the original compiler's register choices.

The dialogue handler preserves Death's bitmask check for the Start button and
its byte-sized script-switch index through `CS_PTR`. Initialization sets player
control before clearing the script flags, and stores the primitive index before
advancing the entity step; this order reproduces the original instructions.

The first-form controller retains two unused extra animation arguments from
the original, including a potentially uninitialized player pointer. Builds with
`FIX_UB` omit those arguments. Its coordinate temporaries and primitive and
child-entity initialization order reproduce the original register allocation
and instruction scheduling.

No emulator playthrough or full PSP, HD, Saturn, or PC build was performed.
