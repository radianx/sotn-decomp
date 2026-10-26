# US PSX completion and publication notes

Snapshot prepared on 2026-10-26 for `radianx/sotn-decomp:psx-us-complete`.
The base is upstream commit
[`7bc54d8157b6bed77e6bd15e5db9461a734fe1e5`](https://github.com/Xeeynamo/sotn-decomp/commit/7bc54d8157b6bed77e6bd15e5db9461a734fe1e5).
PR #1 integrates the fork's newer upstream history through
`e056cb4c907b4433d0cf43d3417025b126e890c0`. The complete BO0 and RNO4 source
layouts are retained; BO5 and the overlapping RDAI routines use upstream's
canonical source layout. The integrated tree is validated again before publication. US-only builds now
build the required string-conversion tool automatically.

## What completion means

The remaining US game-code decompilation is complete. All 122 US linker maps
are free of `.NON_MATCHING` symbols, and the build passes all 115 reference
checksums. The final missing routines are described in the
[MAIN](main_decompilation.md) and [SEL](sel_decompilation.md) checkpoints.

The build still links 37 standalone assembly objects, totaling 10,044 text
bytes: 35 SDK startup/GTE objects in MAIN and two handwritten movie-decoder
objects in SEL. This is not a claim that the repository contains an entirely
C implementation or that all game data has been imported into source.

Only the US release, SLUS-00067, is supported by this fork. HD, PSP, and Saturn
are inherited upstream work outside this fork's maintenance and validation
scope. The native Linux port uses US data and is experimental.

The three-day duration and use of GPT-6-Astra at max reasoning effort are the
maintainer's account of the work. Binary checks establish matching behavior
at the instruction/data level, not the model used or elapsed development time.
The original project's contributors and tool authors made this work possible.

## Reproduce the US checks

First follow the [upstream setup instructions](https://github.com/Xeeynamo/sotn-decomp/wiki/Build)
and extract your own US copy. Then run from the repository root:

```sh
make build VERSION=us
sha1sum --check config/check.us.sha
rg -n '\.NON_MATCHING' build/us -g '*.map'
```

The checksum command must report 115 successful checks. The `rg` command must
print no matches (exit status 1). All 122 maps must exist; an empty or missing
build directory is not evidence of completion. To repeat the full C rebuild
after generating the US build graph, run `ninja -t clean -r psx-cc` followed by
`make build VERSION=us`. This removes generated C objects only.

`tools/progress.py` also looks for assembly files left in `asm/`. In an
incremental checkout, obsolete files from earlier decompilation attempts can
make its percentages undercount the current C code. Its generic module list
also requests `maria`, `fname`, `sd`, and `sttek` configurations that do not
exist for US. Use the linked objects, map symbols, and checksums together;
do not interpret that report alone as an all-editions completion measure.

## Publication contents and licensing

The branch includes C source, headers, layouts, symbol definitions, extraction
manifests, tooling fixes, regression tests, checkpoint notes, and the
experimental native Linux work. Existing AGPL-3.0-or-later notices and the
original copyright attribution are retained. The PSY-Z submodule stays pinned
to its public upstream revision, with the local fixes supplied as
[MPL-2.0 patches](../tools/patches/README.md).

Disc images, extracted graphics, sound, movies, generated assembly, built
executables, local recordings, and scratch work are excluded. RBO5's native
sprite pixels and the additional weapon palettes are generated through
`config/assets.pc.yaml` into ignored `gen/` headers, rather than embedded in
published C source. No game assets
are supplied by the source license; users must provide their own game copy.

The per-overlay checkpoint documents record earlier stages of the work.
Their remaining-gap counts, local-only status, and paths under `build/` are
historical; those scratch artifacts are not included in this branch.

## Validation boundaries

The US C objects were rebuilt for this snapshot and all 115 checksums passed.
The 14 Python symbol tests, Go asset-tool suite, and 182 Rust linter tests
passed, as did all five string-tool tests and a failing-preprocessor diagnostic
check. The native build with `ENABLE_ASAN=OFF` passed all seven CTest cases, including overlay
loading, save/load serialization, and audio regressions. Extraction reproduced
all 217 RBO5 sprite references and 9,536 colors across 47 weapon palette arrays
exactly. The known replay/playthrough limitations are described in
[native_linux.md](native_linux.md). A successful binary match or overlay
load does not establish a complete native playthrough. The separate sanitizer
run exposed system Vulkan driver allocations at shutdown, documented in the
native notes; it is not claimed as a clean sanitizer run. Other game editions
were not built or tested.
