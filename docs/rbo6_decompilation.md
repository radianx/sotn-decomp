# Local RBO6 Decompilation Checkpoint

Recorded on 2026-10-25 on `decomp/local-us-expansion`, based on
`7bc54d8157b6bed77e6bd15e5db9461a734fe1e5`. Changes remain local and uncommitted.

## Scope and Result

Recovered **all 29 previously unfinished US functions**, totaling **36,568
instruction bytes**, in the final Dracula encounter. These cover camera
controls, breakables, a particle burst, two attached sprite effects, player
control during dialogue, screen fades, a shrinking sprite, an ending transition,
primitive brightness adjustment, Dracula's main controller, paired attack
entities, a dispersing spell effect, returning particles, and a projectile with
afterimages and an expanding hit area, a textured-part renderer, and an electrical
arc between the paired attack entities, a segmented attack, and a rotating
triangle projectile, the background vortex, and the ending controller and its
rising flames, the ending's 3D mesh and rotating ribbons, and the dialogue
controller.

| Source | Functions | Bytes |
| --- | ---: | ---: |
| `src/boss/rbo6/e_lock_camera.c` | 2 | 1,228 |
| `src/boss/rbo6/unk_1D690.c` | 2 | 516 |
| `src/boss/rbo6/e_dracula.c` | 12 | 15,816 |
| `src/boss/rbo6/e_cutscene_dialogue.c` | 1 | 4,276 |
| `src/boss/rbo6/unk_2362C.c` | 10 | 7,824 |
| `src/boss/rbo6/unk_30D68.c` | 2 | 6,908 |

The US RBO6 linker map has no remaining nonmatching assembly markers.

The main controller (`func_us_8019DB9C`, 976 instructions) covers the opening
appearance, movement, attack sequencing, subordinate-entity signals, defeat
transition, and controller-2 animation debugging. Its animation event checks
read the combined pose and timer word, so they require a zero pose timer.

The latest two functions add **8,672 bytes / 2,168 instructions**.
`EntityCutscene` selects the script, handles text and portraits, waits for sound
and event flags, checks skip permissions, and records dialogue completion.
Its two skip paths retain separate conditional calls to reproduce the original
compiler's register allocation.

`func_us_801B1738` contains **4,396 bytes / 1,099 instructions**.
It draws a 20-triangle mesh and four rotating ribbons into an off-screen buffer,
spawns particles, and sequences the ending's rotation, depth, and fade effects.
It adapts ST0's geometry renderer with RBO6's state machine and scratchpad layout.

Previously recovered functions include `EntityBackgroundVortex`,
`func_us_801A4594`, and `func_us_801A4F14`.
The vortex builds a rotating mesh, scrolls
its texture, and fades in when the cutscene signals it. It reuses ST0's vortex
pattern with RBO6's opacity scaling. The flame accelerates upward and uses six
stored vertical positions to shape a textured trail, plus a wider glow for
larger particles. Their allocation failures destroy the affected entity.
The controller allocates the ending's screen effects, fades and closes the
side panels, spawns flames, simulates player movement, and selects the ending
from the explored-room count. Its allocation failure resets state zero to retry.

## Basis and Layout

The local disc assembly is authoritative. Existing camera and breakable headers,
the BO1 particle burst, BO6 cutscene effects, existing dialogue controllers,
ST0's vortex and 3D geometry, and local m2c drafts supplied reference patterns.
A local permuter helped resolve the flame's
coordinate register allocation. No scratchpad source was uploaded or imported.

Dracula's code now occupies `e_dracula.c`, with Splat boundaries at text offset
`0x1DB9C` and rodata offset `0x1CD48`. Separating it from the generic particle
code reproduces the original jump-table alignment. The four previously matched
C functions moved into this file are not included in the recovered-function
count. Palette extern declarations now use the controller's 32-bit storage
type; the existing halfword loads still match. `ET_DraculaFinalBoss` names the
timer, bob angle, attack index, and repetition counter without changing `Entity`
or `Ext` sizes on either checked architecture. `ET_DraculaFinalSpell` names the
spell timer at `0x80` and particle return speed at `0x8C`.
`ET_DraculaFinalParts` and `ET_DraculaFinalArc` now describe the primitive
pointers, rotation state, steering timer, and arc endpoints. Their PS1 offsets
are asserted, and neither changes the checked native `Entity` or `Ext` size.
`ET_DraculaFinalTriangle` names the primitive pointer, three vertex offsets,
and color phases, with the same layout checks.
`ET_DraculaFinalFlame` names the trail and glow pointers, vertical acceleration,
and six-position history. Its PS1 offsets and the existing vortex extension's
offsets are asserted; native entity sizes remain unchanged.
`ET_DraculaFinalEnding` names the screen-effect pointers and signed timer,
with the same layout assertions.
`ET_DraculaFinal3D` names the mesh and ribbon pointers, four angles, timer,
rotation speeds, and depth. Its PS1 fields and the renderer's `0xB8`-byte
scratchpad layout are asserted; native entity sizes remain unchanged.

## Validation

```sh
source build/contribution/env.sh
GOMAXPROCS=4 make build VERSION=us
sha1sum --check config/check.us.sha
cmp disks/us/BOSS/RBO6/RBO6.BIN build/us/RBO6.BIN
```

All **115 US reference checksums** pass. The complete **213,060-byte** RBO6
binary and each recovered function's instruction bytes match the disc.
RBO6 SHA-256:
`1ca1182854a2f0ebddb6598b376501342e02e902df36a20bc90043302f49b286`.

The six changed C files pass clang-format. The project linter makes no rewrites
but reports **seven warnings for one entity-slot alias**, detailed below.
Existing and new PS1 layout assertions, native entity-size assertions, and
`git diff --check` pass. The vortex, flame, ending controller, 3D renderer, and dialogue controller
also pass focused `FIX_UB` syntax checks. Native GCC reports the existing
unnamed `EntityID` typedef warning and pointer-size warnings for the renderer's
PS1 draw-environment and scratchpad macros.
Evidence and source snapshots are under ignored
`build/local-decomp/rbo6/checkpoint-29/` and `build/local-decomp/rbo6/evidence.json`.
The US linker maps contain **147 remaining assembly markers** across the project.

## Matching Caveat

The controller currently retains `D_80076F54`, an alias beginning at
`g_Entities[81]`. Direct array indexing changes address reuse and register
allocation in the original compiler. This is explicitly marked `!FAKE` in the
source and flagged by `EntityRangeLinter`; the warning has not been suppressed.
The controller is binary-matched but still has this source-cleanup issue before
contribution review. Tested variants are preserved in ignored
`build/local-decomp/rbo6/main-variants/`.

## Preserved Behavior and Limits

The ending helper retains its original destruction in state 1 and its subsequent
states. `DecreaseBrightness` retains its existing name despite adding the signed
offset and clamping only the upper bound. Existing hardcoded accesses in the
moved C code remain unchanged.

The ending controller preserves two original quirks: its first quad assigns
`y1` twice instead of initializing `y2`, and its blue-channel increment tests
the green channel. These are documented in the recovered source.

The 3D renderer preserves the second draw-environment allocation check against
the primitive pointer and the ribbon brightness write immediately overwritten
with zero. Both behaviors are documented in the source.

The arc retains the original update of `y1` from its previous value. Its original
`PlaySfx` call passes unused volume and pan arguments; the matching build keeps
them, while `FIX_UB` uses the declared one-argument signature.

No emulator playthrough or full PSP, HD, Saturn, or PC build was performed.
