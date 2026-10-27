# PC upgrades

Local branch `recomp-upgrades` starts at fork master `fdddd84c9`.
`origin` is `radianx/sotn-decomp`; `upstream` is the original repository.
Nothing has been published. Build instructions are in [Native Linux](native_linux.md).
SymphonyRecomp supplied design ideas; implementations use this project's C
code and the pinned PSY-Z renderer. SDK modifications remain in licensed patches.

## Settings and controls

Run `./run-linux.sh`. **F1** opens a keyboard-operated settings window and pauses
the game, its audio streams, and its playback clock. Arrow keys select/change
values; Enter changes a value or starts button capture. F1 resumes the game.
Changes save immediately to `build/local-pc/settings.ini`; use
`--config /path/to/settings.ini` for another profile. Start with
[the sample file](pc_settings.ini). Original gameplay settings are the default.

- **F4:** desktop fullscreen.
- **F2:** pause and inspect all 24 SPU voices, envelopes, registers, and CD mix.
- **F8:** toggle reduced flashes. This suppresses the shared full-screen strobe
  routine; stage-specific effects still require visual review.
- **F9:** cycle original, high contrast, blue/gold, and monochrome palettes.
  Palette uploads preserve source data and transparency; turning assistance off
  restores original palettes.
- Master, effects, and music/voice volumes are separate. Keyboard bindings use
  SDL scancodes; controller bindings support buttons, triggers, and a selected
  device. The left stick also supplies directions.

## Widescreen

Enable Widescreen in F1. The renderer exposes additional game coordinates in a
16:9 canvas without increasing emulated PS1 VRAM or stretching the sprites.
The original top/bottom gameplay border is cropped from wide presentation.
The camera respects room bounds and retains world coordinates when toggled.
Dialogue and narrow rooms retain the wide, vertically cropped presentation;
scripted camera pans keep their original camera logic. Narrow rooms center the
camera when normal gameplay resumes. Menus and movies retain their original
presentation. Tiles, shared spawning/despawning and collision bounds,
HUD anchors, fades, cloud culling, transparent water, and lava glow are adapted.

Widescreen remains experimental: expanded spawning and visibility can change
AI timing and random consumption. Original tactic recordings are useful
regressions but are not guaranteed to play identically. Stage-specific 3D
effects and a complete playthrough still need visual validation.
Use the [visual checklist](widescreen_visual_checklist.md) to report uncovered
artwork, seams, masks, and framebuffer effects by location.

The prologue's dissolving room includes the extended background in its ordered
GPU snapshot, and the following vortex renders into both added margins. The
snapshot uses the original scratch texture space and excludes the HUD. Native
regressions preserve transition timing and gameplay randomness; live checks use
an assisted first-form defeat and cover aspect restoration, not a full fight.

### Extended artwork

Build the native artwork pack from the local verified AI drafts:

```sh
python3 tools/build_widescreen_pack.py
```

The generated PNGs stay under ignored `assets/pc/widescreen/`. Only new outer
strips are installed; original pixels and intentional layer transparency are
protected. The renderer loads edges by stage, room-layer index, foreground or
background, and side. They follow that layer's scrolling, depth, visibility and
palette assistance. The builder also creates matching data PNGs under `indexed/`
so extensions follow live palette changes, per-color transparency and tile depth.
These are metadata; keep the root RGB images for artwork editing. Widescreen
must be enabled; original-aspect mode ignores the additions. Restart or change
rooms after rebuilding the pack.

A content pack can override individual files in its `widescreen/` directory;
missing overrides fall back to the generated default pack. File names use
hexadecimal stage/layer IDs, for example `1F_00_B_L.png` for the prologue's first
background layer, left edge. Include matching `widescreen/indexed/` files when
overriding indexed art; remove stale metadata when replacing an image. RGB-only
packs remain supported. Invalid metadata falls back to the RGB image.
Missing or invalid images leave normal rendering
available. Generated candidates still need runtime visual validation; a pack
build is not evidence that every room has been inspected.

Alternate/demo stage IDs reuse their overlay's canonical artwork. Files are
296-pixel-wide RGBA layer templates at the full layer height, with new art only
in the outer 20-pixel strip(s); the rest must remain transparent. Pack updates
replace each validated file atomically so a running game cannot load a partly
copied PNG.

## Disc input and movies

`./run-linux.sh --disk /path/to/game.chd` uses `chdman` from MAME tools to extract
a SHA-256-keyed CUE/BIN cache under `build/pc-discs/`. Set `CHDMAN` if necessary.
The source stays untouched; this is cached extraction rather than compressed
sector reads during play. Extracted `disks/us` assets are still required.
CUE validation checks readable MODE2/2352 data, ISO9660 directory bounds, and
the US `SLUS_000.67;1` identifier; it is not a full-disc checksum comparison.

FFmpeg streams the original STR video as RGB24; audio is buffered in memory.
`--test movie0` through `movie3` exercise all four movies. Start/Cross skips;
F1 pauses both picture timing and audio. No decoded movie cache is required.

## Optional bug fixes

The F1 bug-fix switch enables Scylla's stuck door correction, Olrox's death-timer
underflow correction, the Clock Tower door's spawn relocation, and safe player
reset when entering the Minotaur/Werewolf sequence while transformed.
The Clock Tower layout stays sorted and restores its original spawn position
on the next room initialization after disabling the option. Already-applied
world changes are not undone immediately by switching a fix off.

A native safety correction also retires Beelzebub flies with no live parent.
These changes are guarded for PC; original PS1 binaries must still match.

## Local content packs

Set `contentPack=packs/my-pack` in the settings file, then restart or reload the
relevant overlay. Files not present in a pack fall back to original content.

```text
packs/my-pack/
  files/disks/us/...                 # Replacement assets by original path
  scripts/1F/80180000.bin             # Stage ID / original script address
  voices/0358.wav                    # Original hexadecimal XA command ID
```

Script files replace a complete registered symbol, using exactly its original
byte length and original font/command encoding. Do not overwrite script opcodes
or address references with plain text. Longer translations require rebuilt
symbol maps; this interface does not provide a Unicode renderer. Asset overrides
must retain the format expected by each loader. WAV voice replacements use
one or two channels and supply their own duration; settings pause/gain apply.
Missing or invalid replacements fall back to the original dialogue.
Only distribute packs containing content you may redistribute; keep game
assets, discs, caches, and saves out of source commits.

## Validation

`ctest --test-dir build/local-pc/native --output-on-failure` covers 13 tests,
including settings rollback, all RGB555 colors, virtual controller remapping,
disc/cache failures, pack fallback, normal/inverted water coverage, optional
bug scenarios, mixer gains, XA gaps, SPU voice release, saves, and 178 modules.
Linux/macOS overlay-symbol scenarios are skipped on Windows.

All four direct movies completed at 143/922/545/740 frames. A captured RGB24
movie frame matched FFmpeg byte for byte. A CHD-backed tactic
demo completed. Desktop checks exercised settings, palette/flash switches,
keyboard rebinding, audio diagnostics, fullscreen, and clean exit. A frame-1000
comparison verified
matching player world coordinates with additional scenery visible in widescreen.

The refreshed original-aspect tactic batch completed 23/24 demos; demo 17 still
dies before Lesser Demon. After correcting the Beelzebub crash, the full
wide-option batch was repeated and completed 20/24, including a repeat with
the cropped presentation. Demos 3, 9, 12, and 17 still die with their
original inputs. A debugger trace of demo 9 shows ordinary combat damage at
valid world positions; accessibility-only runs of demos 9 and 12 complete.
These are retained failures, not claimed passes. Logs and captures are local
under `build/local-pc/`. Neither these
checks nor binary matching establish a complete native playthrough.
