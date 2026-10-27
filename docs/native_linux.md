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
must contain the extracted `disks/us` files. `--disk` accepts a **CUE file**
with accessible referenced tracks, or a **CHD** prepared by the launcher using
`chdman` (MAME tools). The US executable identifier is checked before starting.

Press **F4** to toggle fullscreen and **F1** for PC settings. Widescreen,
accessibility, controls, volumes, and optional bug fixes are described in
[PC upgrades](recomp_upgrades.md). The original aspect ratio remains the
default; original sprites retain their resolution.

## Build

Follow the repository's US asset setup and the dependency setup in
`.github/workflows/picci.yaml`, including the pinned PSY-Z/SDL submodules.
The local PSY-Z checkout also includes fixes for Unix file opening and audio emulation.
On a fresh checkout of the pinned submodule, apply both supplied patches once:

```sh
git -C tools/psyz apply "$PWD/tools/patches/psyz-audio-stream-voices.patch"
git -C tools/psyz apply "$PWD/tools/patches/psyz-pc-upgrades.patch"
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

The build loads **178/178 modules**. CTest also checks settings, disc validation,
CHD caching, viewport layout, remapping, palettes, packs, and selected bug
scenarios. Overlay-symbol bug/effect scenarios run on Linux/macOS.
In the initial snapshot, 23 of 24 distinct tactic demos completed; demo 17
(Lesser Demon) ended with
early player death on the Library route before the boss activates. The cause of
that replay divergence is still unknown. Demo 12 (Death) passed separately after
exceeding the 180-second batch limit while builds were running. All 115 US binary checksums
and the Go asset-tool tests pass. Selected bosses were also checked with
AddressSanitizer; this was not a fully instrumented game run. That full demo
batch was repeated on `recomp-upgrades`: 23/24 completed, with demo 17 still
failing. Widescreen replay results are tracked in [PC upgrades](recomp_upgrades.md).

A crash, timeout, or early player death remains a failure. Remaining work includes
Lesser Demon, full cutscene validation, all weapon and familiar behaviors, stage
transitions, and a full save/load playthrough.
Changes to shared game code must also pass `make build VERSION=us` checksums.

## Original movies

Install FFmpeg, then play your extracted US STR files directly:

```sh
./run-linux.sh --test movie0
```

The four movies are wired into the original game calls. `movie0` through `movie3`
play the logo, opening, intermediate movie, and ending independently. Start/Cross
skips playback (Enter is keyboard Start). Video streams through an FFmpeg pipe;
audio is decoded into memory. No decoded RGB/WAV cache is required.
Missing movies log an error and let
the game continue; the standalone test returns failure.

All four direct streams completed with their original frame counts: 143, 922,
545, and 740. The pinned renderer supports RGB24, preserving movie color
precision. FFmpeg reports trailing STR demux warnings; playback still checks
decoder exit status and exact frame counts. The optional legacy
`tools/prepare_pc_movies.py` cache is no longer used by the player.

Fullscreen shutdown previously raised X11 `BadWindow`. The PC patch leaves
fullscreen and synchronizes the window before destroying it; the settings and
fullscreen exit scenario now exits successfully on this desktop.

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

### Widescreen artwork integration

The native renderer can load generated foreground/background edge strips from
`assets/pc/widescreen/` while widescreen is enabled. Build the local pack with
`python3 tools/build_widescreen_pack.py`; see
[the upgrade guide](recomp_upgrades.md#extended-artwork) for layout and overrides.

Initial runtime checks cover Dracula's dialogue, toggling original aspect and
back, and the Colosseum fountain's foreground/background composition. Captures
are under `build/local-pc/`: `dracula-artwork-integrated.png`,
`dracula-artwork-original-aspect.png`, `dracula-artwork-restored.png`, and
`are-fountain-artwork-integrated.png`. A shared draw-mode cursor bug found in the
fountain check is covered by a three-layer regression test. These checks do not
establish whole-game artwork coverage. Generation is complete for the 52 exported
stage codes (1,790 installed edge files); the widescreen checklist tracks remaining
visual checks. Indexed metadata now follows live palette changes and per-color
transparency. Frame-300 rechecks cover the reverse Catacombs' altered palette,
reverse Entrance cave, reverse Clock Tower water/gears, and Colosseum fountain.
Original central viewport pixels match the previous build in the three paired
captures; this is representative validation, not a full playthrough.

Procedural backdrops also need wider draw bounds. Local checks found and fixed
the Richter arena's blue sky-land strip and the Dream scene's cloud/dark backing
cutoff. The shared Chapel backdrop retains its original five tiles; the Dream
additions are clipped outside the original view. Paired captures preserve the
central viewport exactly. Native regressions cover all three sky-land overlays
and 257 Dream camera offsets, including repeated aspect toggles.
Stained-glass subdivision now also uses the wide culling bounds. Both affected
overlays retain identical original-view primitive data over 513 horizontal
positions; moving Chapel captures show the repaired fragments only in the new
margins. Alucard's disc-backed Dream intro reaches combat through the normal
dialogue and camera pan. These sampled states leave full battle/route checks open.
Both Libraries also extend distant shelves, repeating furniture/bookcases and
shadow bands to the wide view. Original-aspect shadows retain their old tile;
wide shadows use a quad to exceed the tile's 255-pixel width limit. Tests cover
all shelf variants, parallax phases and aspect restoration. Live comparisons
use active background entities and temporary diagnostic health; they do not
establish combat or full-area coverage.

The prologue's room breakup now captures the full visible widescreen background
before the HUD, packed into its existing scratch texture. Original-aspect mode
keeps the original capture path; wide mode adds matching edge fragments without
changing gameplay randomness or transition timing. The following vortex also
uses wide culling bounds. Native tests cover full pixel reconstruction and GPU
capture ordering on both framebuffer origins at 1×/2×/4× resolution. A disc-backed,
health-assisted transition probe reaches the second form and restores widescreen
after an aspect switch. Full fights and end-to-end route coverage remain open.

The post-battle photograph also captures the complete wide view and HUD. Its
sepia image keeps the same pixel scale while shrinking/rotating; a separate
paper border and wider burn mask follow its projected bounds. Native regressions
check complete image reconstruction, resource failure and unchanged phase timing.
An assisted disc-backed probe reaches the fire, fade and following game state;
all relative effect timings match the previous implementation. Aspect
changes now wait for captured effects to finish; F1 indicates a queued change.
The hold clears when the effect is destroyed or the stage/game state changes.
Diagnostic spawn placement also restores its temporary room-loading mode so it
cannot carry prologue room coordinates into the entrance. A disc-backed probe
follows the complete story scroll into Alucard's entrance, then 600 frames of
normal scripted movement with widescreen restored. Both boss deaths and the
prologue health are diagnostic overrides; combat and later routes remain open.
