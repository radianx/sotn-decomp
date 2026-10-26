# Local BO6 Decompilation Checkpoint

Recorded on 2026-10-25 on `decomp/local-us-expansion`, based on
`7bc54d8157b6bed77e6bd15e5db9461a734fe1e5`. Changes remain local and uncommitted.

## Scope and Result

Recovered **all 77 previously unfinished US functions**, covering
**74,096 original instruction bytes**, in the Richter boss overlay:

- Movement, input, attacks, item crashes, hit recovery, and death states.
- Entity factories, afterimages, damage effects, whip physics, and arm animation.
- All remaining subweapon effects, including Bible, Agunea, and stopwatch.
- Richter/Shaft dialogue selection, script commands, and completion flags.

The implementations reuse playable Richter's existing C where applicable while
preserving boss-specific entity slots, collision checks, sounds, initialization,
and timers. The stopwatch retains its 12-count timer; Agunea retains the
original use of the player's hearts. Original uninitialized locals and invalid
whip palette indexing receive guards only under `FIX_UB`.

Separate state, whip, projectile, subweapon, and crash translation units restore the original
jump-table alignment. The high-jump boundary now includes its two return
instructions, previously assigned to an empty function; those additional eight
bytes are outside the original inventory total.

## Validation

```sh
source build/contribution/env.sh
GOMAXPROCS=4 make build VERSION=us
sha1sum --check config/check.us.sha
cmp disks/us/BOSS/BO6/BO6.BIN build/us/BO6.BIN
```

All **115 US checksums** pass. The complete **333,544-byte BO6 binary** and every
recovered function's original instruction bytes match the disc. Changed C files
pass clang-format and the project linter. A focused native syntax check covers
the recovered functions with `FIX_UB`, supplying legacy helper declarations and
a host-compatible offset macro; it does not build the whole PC overlay.

Evidence and source snapshots are under ignored
`build/local-decomp/bo6/checkpoint-77/`. There are **no remaining BO6 assembly
markers** and **six across the US linker maps** at this checkpoint.

## Remaining Work and Limits

The six remaining US linker markers are in RDAI (two), RBO2 (one), MAIN (two),
and SEL (one). Emulator gameplay and full HD, PSP, Saturn, and PC builds were
not tested. This completes the original BO6 US gap inventory, not the overall
PS1 decompilation goal.
