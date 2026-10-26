# Local BO0 Decompilation Complete

Recorded on 2026-10-23 on local branch `decomp/local-us-expansion`, based on
`7bc54d8157b6bed77e6bd15e5db9461a734fe1e5`. Nothing has been committed or pushed.

## Scope and Result

Replaced all 46 remaining assembly inclusions with matching C in
`src/boss/bo0/2D26C.c` and `src/boss/bo0/313A8.c`: 42,612 bytes covering both
Olrox forms, attack selection, projectiles, portals, limbs, rendering, furniture,
and death effects. `include/entity.h` describes their entity extensions.

Including the earlier 72-byte collision helper `func_us_801AD2F0`, this is
47 recovered functions and 42,684 code bytes relative to the base commit.
That helper's separate patch remains in
`build/contribution/bo0-collision-helper.patch`.

There are no remaining `INCLUDE_ASM` or `INCLUDE_RODATA` statements under
`src/boss/bo0/`. This completes BO0's US code conversion; it does not mean every
asset or unknown symbol has been named. The local US assembly-inclusion
inventory fell from 316 to 270, not a whole-project completion percentage.

## Scratchpad Attribution

The public [SotN preset](https://decomp.me/preset/14) supplied valuable existing
work. The linked scratches are owned by **hohle**, except `zfw8E`, owned by
**AldemarBernal** and based on hohle's `qvA3g`, according to export metadata.
Most implementations adapt that work to the current headers,
entity layouts, symbols, and project constants. They should retain this credit
in any later contribution. Scratch scores were not used as proof of a match;
each accepted function was compiled and compared locally.

“Local” means reconstructed from the original assembly, m2c output, and local
code patterns before consulting the corresponding scratch source. Those links
are retained as related work.

| Function | Scratch | Basis |
| --- | --- | --- |
| `func_us_801AD26C` | [2plDG](https://decomp.me/scratch/2plDG) | Adapted |
| `EntityOlroxAfterImage` | [RrK6S](https://decomp.me/scratch/RrK6S) | Local |
| `func_us_801B13A8` | [A6tNd](https://decomp.me/scratch/A6tNd) | Adapted |
| `func_us_801B1590` | [OYrS7](https://decomp.me/scratch/OYrS7) | Adapted |
| `func_us_801B15BC` | No scratch found by symbol name | Local |
| `func_us_801B163C` | [ibVXE](https://decomp.me/scratch/ibVXE) | Adapted |
| `func_us_801B171C` | [v8shO](https://decomp.me/scratch/v8shO) | Adapted |
| `func_us_801B17BC` | [8awRg](https://decomp.me/scratch/8awRg) | Adapted |
| `func_us_801B1864` | [hQLgp](https://decomp.me/scratch/hQLgp) | Adapted |
| `func_us_801B1950` | [IesFn](https://decomp.me/scratch/IesFn) | Adapted |
| `func_us_801B19FC` | [AULD8](https://decomp.me/scratch/AULD8) | Adapted |
| `func_us_801B1B30` | [mw53E](https://decomp.me/scratch/mw53E) | Adapted |
| `func_us_801B1C60` | [vgtEI](https://decomp.me/scratch/vgtEI) | Adapted |
| `func_us_801B1CE0` | [0vhtG](https://decomp.me/scratch/0vhtG) | Adapted |
| `func_us_801B1DDC` | [PI98f](https://decomp.me/scratch/PI98f) | Adapted |
| `func_us_801B1E5C` | [GeUZe](https://decomp.me/scratch/GeUZe) | Adapted |
| `func_us_801B1EDC` | [Eg1tl](https://decomp.me/scratch/Eg1tl) | Adapted |
| `func_us_801B1F5C` | [5Trfj](https://decomp.me/scratch/5Trfj) | Adapted |
| `func_us_801B2044` | [Uk53a](https://decomp.me/scratch/Uk53a) | Local |
| `func_us_801B20F4` | [k2ZIi](https://decomp.me/scratch/k2ZIi) | Adapted |
| `func_us_801B2178` | [Zw98V](https://decomp.me/scratch/Zw98V) | Adapted |
| `func_us_801B21F0` | [gX37r](https://decomp.me/scratch/gX37r) | Adapted |
| `func_us_801B24CC` | [ifdwV](https://decomp.me/scratch/ifdwV) | Adapted |
| `func_us_801B2690` | [ktE3I](https://decomp.me/scratch/ktE3I) | Adapted |
| `func_us_801B30AC` | [76DnU](https://decomp.me/scratch/76DnU) | Adapted |
| `func_us_801B5470` | [T9nXf](https://decomp.me/scratch/T9nXf) | Adapted |
| `func_us_801B5D6C` | [LuDmn](https://decomp.me/scratch/LuDmn) | Local |
| `func_us_801B5E08` | [VYh2R](https://decomp.me/scratch/VYh2R) | Adapted |
| `func_us_801B65C0` | [ojve3](https://decomp.me/scratch/ojve3) | Adapted |
| `func_us_801B76E4` | [jLvgc](https://decomp.me/scratch/jLvgc) | Adapted |
| `func_us_801B7BAC` | [yyqc2](https://decomp.me/scratch/yyqc2) | Adapted |
| `func_us_801B7C44` | [JpZe4](https://decomp.me/scratch/JpZe4) | Adapted |
| `func_us_801B7CC8` | [0c949](https://decomp.me/scratch/0c949) | Adapted |
| `func_us_801AD338` | No scratch found by US or PSP symbol name | Local |
| `func_us_801AE858` | [jzcBO](https://decomp.me/scratch/jzcBO) | Adapted |
| `func_us_801AF31C` | [cmBXV](https://decomp.me/scratch/cmBXV) | Adapted |
| `func_us_801AF604` | [zR2dP](https://decomp.me/scratch/zR2dP) | Adapted |
| `func_us_801AF8C0` | [kwGNw](https://decomp.me/scratch/kwGNw) | Adapted |
| `func_us_801AFAF4` | [2rRqK](https://decomp.me/scratch/2rRqK) | Adapted |
| `func_us_801B001C` | [P4G4a](https://decomp.me/scratch/P4G4a) | Adapted |
| `func_us_801B365C` | [zfw8E](https://decomp.me/scratch/zfw8E), [qvA3g](https://decomp.me/scratch/qvA3g) | Adapted with local reconstruction |
| `func_us_801B551C` | [uEjDz](https://decomp.me/scratch/uEjDz) | Adapted |
| `func_us_801B5E8C` | [oOJTS](https://decomp.me/scratch/oOJTS) | Adapted with local reconstruction |
| `func_us_801B619C` | [pNuXG](https://decomp.me/scratch/pNuXG) | Adapted |
| `func_us_801B6520` | [ujIvr](https://decomp.me/scratch/ujIvr) | Adapted; stack-layout caveat below |
| `func_us_801B6CA4` | [uqKOt](https://decomp.me/scratch/uqKOt) | Adapted |

## Validation

Run from the repository root with the local toolchain environment:

```sh
source build/contribution/env.sh
GOMAXPROCS=4 make build VERSION=us
sha1sum --check config/check.us.sha
cmp disks/us/BOSS/BO0/BO0.BIN build/us/BO0.BIN
```

The full US build passed all **115 reference checksums**. The complete 320,948-byte
BO0 binary is byte-identical to the supplied US disc's binary. Its SHA-256 is
`23fe0511babfd91ed9e99b8c7ec02c9c5b6de8709f6bd77bd6d046244e3c5009`.
All 46 additional function addresses and instruction bytes were also checked individually.

The changed C files pass the project linter without further transformations;
all three changed source/header files pass clang-format and `git diff --check`.
Local GCC layout assertions verify the new 32-bit entity offsets and preserve
`sizeof(Entity) == 0xBC` and `sizeof(Ext) == 0x3C`. A separate 64-bit header check
finds unchanged aggregate sizes (`0x100` and `0x68` respectively); this is not a
PC build or runtime test.

Logs, scratch exports, per-function hashes, and failed experiments are kept in
the ignored `build/local-decomp/` directory. Build cleanup can remove these;
this document preserves the source links and checkpoint results.

## Matching Details and Limits

The first-form controller was reconstructed locally from the US assembly and
m2c output. Its unused drawing locals retain the original stack layout and
initialized `RECT` copy. The true-form controller and tail renderer required
substantial corrections to the public scratch implementations.

The arm helper `func_us_801B6520` uses the scratch's unused aggregate to reproduce
the original `0x28`-byte stack frame. This is marked `!FAKE` in the source; the
aggregate's original purpose is unknown. A direct translation otherwise uses a
`0x20`-byte frame. All resulting instruction bytes still match.

Original behavior is preserved, including the same-direction movement in state
12 and the head controller's allocation-failure behavior. This is decompilation,
not a gameplay bug fix. Unknown symbols and fields retain provisional names.

No emulator playthrough or full PSP, HD, Saturn, or PC build was performed.
Before any future upstream submission, follow `CONTRIBUTING.md`, preserve scratch
authorship, and review the changes manually. The broader local goal continues
with the remaining US PS1 modules.
