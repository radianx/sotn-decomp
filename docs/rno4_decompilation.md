# Local RNO4 Decompilation Checkpoint

Recorded on 2026-10-25 on `decomp/local-us-expansion`, based on
`7bc54d8157b6bed77e6bd15e5db9461a734fe1e5`. Changes remain local and uncommitted.

## Scope and Result

Recovered **all 52 previously unfinished US functions**, totaling **42,004
instruction bytes**, in the inverted caverns:

- Seven water-effect functions and six Blue Venus Weed functions.
- `StepTowards`, three Jack O'Bones functions, three Nova Skeleton helpers,
  and the Imp controller.
- Seven Bomb Knight / Rock Knight functions, including projectiles and debris.
- The Cave Troll effect, breakables, boat chains, water-level controls, and
  secret wall.
- Fourteen cavern background, parallax, and water-rendering functions.

Existing shared implementations supply the water, plant, and enemy code.
Bomb Knight's implementation moved from RNZ1 into `src/st/e_bomb_knight.h`;
both stages select their own palettes, sprite banks, initializers, and entity
IDs. The breakables reuse the existing cavern implementation; background
renderers adapt the normal cavern routines to the inverted geometry. Splat
assigns the corresponding data, text, and jump tables to C.
Previously matched functions moved alongside these routines are not counted
as new recoveries.

## Validation

```sh
source build/contribution/env.sh
GOMAXPROCS=4 make build VERSION=us
sha1sum --check config/check.us.sha
cmp disks/us/ST/RNO4/RNO4.BIN build/us/RNO4.BIN
cmp disks/us/ST/RNZ1/RNZ1.BIN build/us/RNZ1.BIN
```

All **115 US checksums** pass. The complete **384,020-byte** RNO4 binary,
the RNZ1, NO4, BO3, RNO3, and CHI binaries, and all recovered instruction bytes
match the disc.
RNO4 SHA-256:
`537975521babbdd462d4662a49fd23a5f7688ddcc1601b4a335aa450ba733ad2`.

The changed files pass the project linter, and new code passes formatting;
unrelated legacy formatting remains. Focused `FIX_UB` syntax checks for both
Bomb Knight wrappers and the background renderers pass with declarations
supplied for existing stage helpers; legacy animation-pointer and enum
warnings remain.
Evidence and source snapshots are under ignored
`build/local-decomp/rno4/checkpoint-52/`. RNO4 has **no remaining assembly
markers**; the US linker maps have **95** in total at this checkpoint.

## Preserved Behavior and Limits

Reflected bombs retain the original hardcoded `0x43` entity ID, including in
RNO4. The US bomb explosion writes through an uninitialized pointer; matching
builds preserve this, while `FIX_UB` uses the intended entity pointer.
Blue Venus Weed's palette cap now follows its stage's `PLANT_CLUT`; the existing
RNO3 and CHI builds also pass their reference checksums.

The Cave Troll effect retains its repeated horizontal-distance call and
animation fallthrough. A waterfall layer retains its previous texture
coordinate accumulation. The parallax-column table ends with an offscreen
sentinel, so the copied normal-cavern bounds workaround is unnecessary here.

Emulator gameplay and full PSP, HD, Saturn, and PC builds were not tested.
