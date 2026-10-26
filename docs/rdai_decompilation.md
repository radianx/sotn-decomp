# Local RDAI Decompilation Checkpoint

Recorded on 2026-10-25 on `decomp/local-us-expansion`, based on
`7bc54d8157b6bed77e6bd15e5db9461a734fe1e5`. Changes remain local and uncommitted.

## Scope and Result

Recovered **all 14 previously unfinished US functions**, totaling
**20,944 instruction bytes**, in the inverted chapel:

- Tower-exit camera boundaries.
- Stained-glass windows, lighting, and background rendering.
- Archer movement, attachment animation, arrows, and debris.
- Spectral Sword controller, spears, and shields.
- Black Panther movement, shadow transformation and recovery, and primitive
  interpolation.

The renderers adapt the normal chapel's existing C implementation to the
inverted geometry and SDK projection calls. Typed Archer, Spectral Sword, and Black Panther
extensions describe the recovered entity fields. Trigonometric scaling uses
multiplication, preserving the instructions without shifting negative values.

## Validation

```sh
source build/contribution/env.sh
GOMAXPROCS=4 make build VERSION=us
sha1sum --check config/check.us.sha
cmp disks/us/ST/RDAI/RDAI.BIN build/us/RDAI.BIN
```

All **115 US checksums** pass. The complete RDAI binary and every recovered
function's instruction bytes match the disc. New C code passes clang-format
and the project linter. Static assertions verify the recovered PS1 field
offsets and preserve the 32-bit and native 64-bit entity sizes. A focused
native `FIX_UB` syntax check passes with legacy helper declarations supplied.

Evidence and source snapshots are under ignored
`build/local-decomp/rdai/checkpoint-12/`,
`build/local-decomp/rdai/controller-matched/`, and
`build/local-decomp/rdai/checkpoint-14/`. RDAI has **no remaining assembly
markers**; **two remain across the US linker maps** at this checkpoint.

## Matching Details and Limits

The attachment routine retains a one-shot allocation loop and a final state
assignment for compiler register allocation, marked `!FAKE`. Its original
word-sized pose checks have equivalent typed checks under `FIX_UB`.

The original debug prints, debris state behavior, and background color-copy
order are preserved. Emulator gameplay and full PSP, HD, Saturn, and PC builds
were not tested; native syntax checks do not establish gameplay correctness.
