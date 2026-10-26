# Castlevania: Symphony of the Night — US PSX Decompilation

This is [radianx's fork](https://github.com/radianx/sotn-decomp) of the
[original sotn-decomp project](https://github.com/Xeeynamo/sotn-decomp), led by
Luciano Ciccariello (@Xeeynamo) and its contributors. This fork supports only
the US PlayStation release, **SLUS-00067** (`VERSION=us`).

Starting from upstream commit
[`7bc54d815`](https://github.com/Xeeynamo/sotn-decomp/commit/7bc54d8157b6bed77e6bd15e5db9461a734fe1e5),
the remaining US PSX game-code decompilation was completed in **three days**
using **GPT-6-Astra at max reasoning effort**. The model and elapsed time are
the fork maintainer's account of the work; the matching results are documented
in [the completion and validation notes](docs/us_completion.md).

**This was only possible because of the enormous human effort behind the
original repository.** Its contributors established the decompilation,
recovered and named code, built the tooling, and worked out how to reproduce
the original binaries. This project is **standing on the shoulders of those
giants**. The three days describe the work on top of that foundation, not the
time it took to build the original project.

## Scope and status

The US build matches all **115 reference checksums**, and all **122 US linker
maps** are free of `.NON_MATCHING` markers. Completion refers to the remaining
game-code decompilation: **37 standalone assembly objects (10,044 text bytes)**
remain for SDK startup/GTE routines and the handwritten movie decoder. It does
not mean every byte has become C or every game asset has been imported.

HD, PSP (`pspeu`), and Saturn files are inherited from upstream and are outside
this fork's maintenance, support, and validation scope. The additional
[native Linux port](docs/native_linux.md) uses US game data and remains
experimental; a complete playthrough has not been verified.

The `psx-us-complete` branch started from the base above and integrates the
newer upstream work present on this fork's `master` for PR #1.

## Build and licensing

Follow the [upstream build guide](https://github.com/Xeeynamo/sotn-decomp/wiki/Build)
with your own US game copy, then run:

```sh
make build VERSION=us
./sotn.sh check us
```

The source is distributed under **AGPL-3.0-or-later**; see [LICENSE](LICENSE)
and the [original copyright notice](src/LICENSE). Existing attribution and
third-party licenses are retained. Fork modifications are dated **2026-10-26**.
The supplied [PSY-Z patches](tools/patches/README.md) retain MPL-2.0.

Game disc images, extracted artwork, audio, movies, generated assembly, and
compiled game binaries are not distributed here. The source license does not
grant rights to those game assets. Extraction tools generate the required
files locally from your own copy, including the Linux port's sprites and movies.

## Useful links

* [Original repository and contributors](https://github.com/Xeeynamo/sotn-decomp)
* [Build guide](https://github.com/Xeeynamo/sotn-decomp/wiki/Build)
* [Decompilation guide](https://github.com/Xeeynamo/sotn-decomp/wiki/Decompilation)
* [US completion and validation](docs/us_completion.md)
* [Native Linux build and known limitations](docs/native_linux.md)
* [Upstream progress report](https://sotn.xee.dev/)
* [Upstream decomp.dev progress](https://decomp.dev/Xeeynamo/sotn-decomp)

## Special thanks

This project is possible thanks to the hard work of tools provided by the Decompilation community:

* [mips2c](https://github.com/matt-kempster/m2c) from @matt-kempster to decompile MIPS assembly into C. This has proven to be more accurate than Hexrays IDA and Ghidra.
* [splat](https://github.com/ethteck/splat) from @ethteck to disassemble code and extract data with a symbol map. This tool provides the fundamentals of the SOTN decomp.
* [asm-differ](https://github.com/simonlindholm/asm-differ) from @simonlindholm to know how the decompiled code compares to the original binary.
* [decomp-permuter](https://github.com/simonlindholm/decomp-permuter) from @simonlindholm to pick different versions of the same code that better matches the original binary.
* [maspsx](https://github.com/mkst/maspsx) by @mkst to replicate the customized assembler used in the official PSX SDK.
* [decomp.me](https://github.com/decompme/decomp.me/) by @ethteck, @nanaian and @mkst to provide a collaborative decompilation site to share and contribute to work-in-progress decompiled functions.
* [frogress](https://github.com/decompals/frogress) by @ethteck to store and retrieve progression data.
* [esa-new](https://github.com/mkst/esa-new) by @mkst as an inspiration on how to set-up a PS1 decompilation project.
* [oot](https://github.com/zeldaret/oot) as an inspiration of what it is possible to achieve with a complete decompiled video game.
