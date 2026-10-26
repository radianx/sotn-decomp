# Native Linux port

This local branch builds a native executable using PSY-Z and SDL3. It is an
experimental port: loading every overlay does not establish that a complete
playthrough works. Keep original game files and saves backed up.

## Run this checkout

From the repository root:

```sh
./run-linux.sh
./run-linux.sh --demo 0 --replay-and-exit
./run-linux.sh --disk /path/to/game.cue
```

The launcher uses `build/local-pc/native/sotn` and `disks/sotn.us.cue` by default.
Keep the shared overlay libraries beside the executable. The working directory
must contain the extracted `disks/us` files. `--disk` accepts the **CUE file**,
with its referenced tracks accessible beside it.

Press **F4** to toggle fullscreen. On the tested 1920×1080 desktop, fullscreen
fills the desktop while preserving the original aspect ratio with black bars.
This does not add widescreen gameplay or replace the original sprite artwork.

## Build

Follow the repository's US asset setup and the dependency setup in
`.github/workflows/picci.yaml`, including the pinned PSY-Z/SDL submodules.
The local PSY-Z checkout also includes fixes for Unix file opening and audio emulation.
On a fresh checkout of the pinned submodule, apply the supplied audio patch once:

```sh
git -C tools/psyz apply "$PWD/tools/patches/psyz-audio-stream-voices.patch"
```

Generate both the original assets and the additional native assets:

```sh
make extract_assets VERSION=us
make build_assets VERSION=us
./sotn.sh extract-assets config/assets.pc.yaml
./sotn.sh build-assets config/assets.pc.yaml
cmake -S . -B build/local-pc/native -DENABLE_ASAN=OFF
cmake --build build/local-pc/native -j 8
ctest --test-dir build/local-pc/native --output-on-failure
```

The native extraction manifest also generates RBO5's sprite sheets and the
additional weapon palettes. Those pixels and colors are extracted from your
own disc into ignored `gen/` headers and are not embedded in this fork's source.

This machine's build uses development dependencies extracted under
`build/local-pc/deps`; its existing CMake cache contains those paths. A fresh
machine needs the corresponding development packages or equivalent CMake paths.

## Validation boundaries

`pc_overlays` opens every compiled stage, boss, weapon, and familiar module and
checks that its symbols resolve. It does not execute every entity or effect.
`pc_gte` checks the native matrix helpers against the original SDK semantics.
`pc_primitive` checks that a native draw-environment pointer survives updates to
primitive vertex coordinates. Compile-time checks also keep weapon parent and
animation fields aligned. `pc_rand` verifies the PS1 BIOS random sequence,
including reseeding, independently of the host C library.

Run replay regressions with:

```sh
SDL_VIDEODRIVER=offscreen SDL_AUDIODRIVER=dummy \
  ./run-linux.sh --demo 0 --replay-fast --replay-and-exit
```

The current build loads **178/178 modules** and passes **7/7 native tests**.
In the initial snapshot, 23 of 24 distinct tactic demos completed; demo 17
(Lesser Demon) ended with
early player death on the Library route before the boss activates. The cause of
that replay divergence is still unknown. Demo 12 (Death) passed separately after
exceeding the 180-second batch limit while builds were running. All 115 US binary checksums
and the Go asset-tool tests pass. Selected bosses were also checked with
AddressSanitizer; this was not a fully instrumented game run. That full demo
batch has not been repeated after integrating the newer upstream history.

A crash, timeout, or early player death remains a failure. Remaining work includes
Lesser Demon, full cutscene validation, all weapon and familiar behaviors, stage
transitions, and a full save/load playthrough.
Changes to shared game code must also pass `make build VERSION=us` checksums.

## Original movies

Install FFmpeg (including `ffprobe`), then decode your extracted US disc files:

```sh
python3 tools/prepare_pc_movies.py
./run-linux.sh --test movie0
```

The four movies are wired into the original game calls. `movie0` through `movie3`
play the logo, opening, intermediate movie, and ending independently. Start/Cross
skips playback (Enter is keyboard Start). Generated RGB/WAV files stay under
`build/pc-movies/` and require about 570 MB. Missing movies log an error and let
the game continue; the standalone test returns failure.

All four streams played to their original frame counts: 143, 922, 545, and 740.
The logo was visually checked at 1920×1080, and normal startup returned to the
title screen. Enter skipped the opening successfully. One automated fullscreen
capture completed playback but then exited with an X11 `BadWindow` error;
headless full playback and the windowed skip test exited successfully. This
fullscreen shutdown issue remains unverified. The renderer ignores RGB24, so
playback converts to RGB555;
this reduces color precision. FFmpeg reports trailing STR demux warnings; decode
logs are retained and the script verifies the exact video byte counts.

## Save/load and audio checks

```sh
SDL_VIDEODRIVER=offscreen SDL_AUDIODRIVER=dummy ./run-linux.sh --test save
```

`pc_save` writes and reads an actual 8192-byte card file, compares every byte,
and restores health, equipment, gold, settings, map, stage, and random state.
It also rejects an invalid save size and a truncated file. It uses a temporary
directory under `build/`, leaving normal card files untouched. This checks the
storage and serialization path, not menu navigation or a complete playthrough.
The Unix backend previously opened writes read-only; the supplied PSY-Z patch
fixes that, and PC card operations now reject short reads/writes.

A system-output capture confirmed game and movie audio through the USB GK51
sink. The approximately 15-second demo capture measured -14 dBFS RMS, with about
0.076% of samples clipped per channel; the logo capture had no clipped samples.
These measurements establish output, not subjective quality or physical-speaker
confirmation. Evidence is under `build/local-pc/audio-check/`.

The audio regression tests cover two bugs found during manual play:
`pc_cd_audio` preserves the time occupied by filtered-out disc sectors, preventing
later clips with the same XA filter from playing immediately after a phrase. It
checks silence, subsequent clip playback, and pause at both drive speeds.
`pc_spu_audio` checks that completed, non-looping samples clear their envelope
and free all 24 voices, while looping samples continue. Both tests failed before
the fixes. A controlled lethal hit in demo 0 reproduced Maria's revival; after
the fix, finished effect voices report zero envelopes and can be reused.
The user's manual run confirmed physical sound output and movie playback;
listening to these corrected dialogue and revival sequences remains pending.

### PR integration checks (2026-10-26)

The integrated native build loads all 178 overlays. With AddressSanitizer
enabled, the geometry, primitive, random, SPU, XA, and overlay tests passed.
The save/load assertions also passed, but LeakSanitizer reported two 128-byte
allocations after graphics shutdown. Dynamic-loader address mapping traced
the allocation stacks to this machine's system `libvulkan_radeon.so` and
`libvulkan_nouveau.so`; no sanitizer suppression was added. The documented
`ENABLE_ASAN=OFF` build is checked separately. This is not a clean sanitizer
result for the full application.
