# Local SEL Decompilation Checkpoint

Recorded on 2026-10-25 on `decomp/local-us-expansion`, based on
`7bc54d8157b6bed77e6bd15e5db9461a734fe1e5`.
Changes remain local and uncommitted.

## Scope and Result

Recovered `func_801B9C80`, the US movie playback routine: **504 instructions,
2,016 bytes**. It selects the stream, decodes and displays frames, fades sound
when skipping, and handles disc-error recovery and retry.

This removes the last `.NON_MATCHING` entry from the US build. All **122 US
linker maps** are free of that marker. The existing 37 standalone assembly
objects remain: MAIN's SDK startup/GTE code and SEL's handwritten movie decoder,
totaling 10,044 text bytes. Zero markers does not mean the repository is all C.

## Storage and Matching Details

`stream.h` describes the shared control allocation and the displayed-frame
index followed by the 40-sector CD ring. Conditional linker aliases preserve
the existing PS1 symbol addresses. The ring includes the former trailing BSS
word; the next allocation remains at `0x801D104C`.

Both CD status buffers contain eight bytes. Owner-relative accesses replace
indexing across separately declared objects. Thirteen layout assertions check
the allocation sizes and offsets used by the matching code.

The startup uses three fixed-register locals and an empty compiler barrier,
marked `!FAKE`. It emits no handwritten machine instructions. The explicit
retry dispatch and volatile RGB writes preserve compiler allocation and
scheduling. These are matching choices, not claims about the original source.
The initial error-path frame index must remain a structure-member access;
changing it to a scalar pointer changes GCC 2.6's memory dependencies.

## Validation

```sh
source build/contribution/env.sh
GOMAXPROCS=4 make build VERSION=us
sha1sum --check config/check.us.sha
cmp disks/us/ST/SEL/SEL.BIN build/us/SEL.BIN
```

All **115 US checksums** pass, including after relinking all 122 US images with
the field-alias script. The complete **355,112-byte SEL binary** matches the disc,
and the movie function has a zero instruction diff. Clang-format, the project
linter, and the layout assertions pass. Evidence and source copies are under
ignored `build/local-decomp/ps1-final-gaps/sel-final/matched-layout/`.

## Limits

Emulator playback and non-US builds were not tested. The matching routine uses
PS1 layout offsets and compiler extensions. The PC build retains its separate
movie stub; a complete PC build was not tested.
