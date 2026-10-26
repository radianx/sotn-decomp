# Local MAIN Decompilation Checkpoint

Recorded on 2026-10-25 on `decomp/local-us-expansion`, based on
`7bc54d8157b6bed77e6bd15e5db9461a734fe1e5`.
Changes remain local and uncommitted.

## Scope and Result

Recovered the two remaining US MAIN routines, totaling **1,884 instruction
bytes**:

- `dma_execute`: CD transfer setup and completion (444 bytes).
- `_SsContDataEntry`: sequence loop counts, pitch-bend range, fine and coarse
  tuning, and NRPN tone attributes (1,440 bytes).

The US MAIN linker map contains **no `.NON_MATCHING` entries**. SEL's remaining
movie routine was subsequently matched; see [the SEL checkpoint](sel_decompilation.md).

## Validation

```sh
source build/contribution/env.sh
GOMAXPROCS=4 make build VERSION=us
sha1sum --check config/check.us.sha
cmp disks/us/SLUS_000.67 build/us/main.exe
```

All **115 US checksums** pass. The complete 563,200-byte executable matches the
disc. `_SsContDataEntry` also has a zero instruction diff. Its source passes
clang-format and the project linter. A native `FIX_UB` syntax check passes with
existing SDK helper declarations supplied; static assertions check the program,
tone, and ADSR structure sizes.

Evidence and source snapshots are under ignored
`build/local-decomp/ps1-final-gaps/dma-matched/` and
`build/local-decomp/ps1-final-gaps/seq-final/matched/`.

## Matching Details and Limits

The sound routine retains promoted-byte temporaries and zero high-byte terms,
marked `!FAKE`. These reproduce a redundant byte mask and unused stack spills
in the original compiler. Tone counts and input values are bytes, so those
high-byte terms are always zero.

The original passes uninitialized tone and ADSR structures by value. Matching
PS1 builds preserve this behavior; `FIX_UB` initializes both structures.

Emulator playback and full HD, PSP, Saturn, and PC builds were not tested.
