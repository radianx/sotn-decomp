# Widescreen visual checklist

US native port, `recomp-upgrades`, 2026-10-26. This is an inspection inventory,
not a list of confirmed defects or a claim of full-game visual coverage.
Check both castles: similar rooms can use different rendering implementations.

## Reported prologue issues

- [x] Opening reveal: extend its opaque masks to the viewport edges, clamp their
  widths to prevent reversed polygons, preserve the 64-pixel gradients, and
  finish only after the gradients leave the wide view. Source:
  `src/st/st0/title_card.c`, `EntityStageTitleFadeout`.
- [x] Dracula's lair: keep the wide presentation and gameplay border crop while
  dialogue takes control or narrows the camera bounds. Preserve scripted camera
  pans. Source: `src/pc/widescreen.c`.

Regression checks cover mask geometry throughout the reveal, switching aspect
mode during the effect, narrow rooms, and dialogue capture dimensions. Local
fullscreen evidence is in `build/local-pc/reveal-fixed.png` and
`build/local-pc/dracula-dialogue-fixed.png`. Other landmarks below remain open.

- [x] Dracula dialogue left-edge artwork: the generated background strip now
  fills the empty purple area in-game. Evidence:
  `build/local-pc/dracula-artwork-integrated.png`. Disabling widescreen removes
  the additions; re-enabling restores them (`artwork-toggle-check.log`).

The Colosseum fountain (`ARE`, room/layer `09`) also has a runtime capture at
`build/local-pc/are-fountain-artwork-integrated.png`: both edges render while the
foreground opening retains the fountain behind it. A shared draw-mode cursor
bug found here is covered by a three-layer drawing-list regression check.
These captures do not close the broader area checks below.

Additional still-frame checks cover Catacombs room/layer `02` with foreground
and background extensions together (`build/local-pc/cat-room02-artwork-integrated.png`)
and Abandoned Mine room/layer `00` at the dinosaur decoration
(`build/local-pc/chi-dinosaur-artwork-integrated.png`). Both reach frame 120
with the added edges visible. Moving effects, room transitions and the rest of
these areas remain unchecked.

Still-frame checks also cover Chapel `DAI` room/layer `06` (confessional,
`build/local-pc/dai-room06-artwork-integrated.png`) and center `CEN` room/layer
`00` (lift shaft, `build/local-pc/cen-room00-artwork-integrated.png`). Both show
their added edges at frame 120. These do not verify dialogue, moving effects or
room transitions. In the long Chapel room `0B`, normal camera clamping keeps
the outer extension off-screen; its capture does not verify the new strip.

Library `LIB` room/layer `04` and Marble Gallery `NO0` room/layer `01` have
frame-300 captures with visible added edges and downward camera scrolling:
`build/local-pc/lib-room04-artwork-integrated.png` (scroll Y 260) and
`build/local-pc/no0-room01-artwork-integrated.png` (scroll Y 463). The captures
verify these positions only; the area's interactions and full travel paths
remain unchecked.

Further frame-300 checks cover `NO1` room/layer `05`
(`build/local-pc/no1-room05-artwork-integrated.png`) and `NO0` room/layer `0B`
(`build/local-pc/no0-0b-room0b-artwork-integrated.png`). Both show the new edges;
the latter retains foreground railings over the background and character.
These still-frame checks do not close the broader area or transition checks.

`NO2` room/layer `06` was checked during normal falling through the shaft, with
both generated-section boundaries visible: `no2-shaft-join640-artwork-integrated.png`
at scroll Y 544 and `no2-shaft-join1280-artwork-integrated.png` at scroll Y 1181
(both under `build/local-pc/`). These verify scrolling across these two joins.

- [x] `NO3` cave room/layer `01`: remove artificial dark side bands caused by
  tiny AI shade differences crossing PS1 five-bit color bins. Flat, opaque dark
  boundary regions now continue the exact source color in the local artwork
  assembler. Three regression checks protect textured and transparent areas.
  In-game samples on both new edges and the original rock all equal RGB(33,16,33).
  Evidence: `build/local-pc/no3-flat-color-evidence.json` and
  `build/local-pc/no3-room01-artwork-integrated.png`. The full cave route remains open.

`NO4` room/layer `00` was checked during normal falling through its 2816-pixel
shaft, with generated-section joins visible at world rows 1280, 1920 and 2560.
Captures are `build/local-pc/no4-shaft-join{1280,1920,2560}-artwork-integrated.png`.
The earlier join at 640 has a magnified artifact review; the route above the
runtime test's Y=900 spawn remains unchecked. `NO4` room/layer `01` also has a
frame-300 layered-backdrop capture (`build/local-pc/no4-room01-artwork-integrated.png`).
These checks leave waterfalls, underwater views and room transitions open.

Alchemy Laboratory `NZ0` room/layer `00` has a frame-300 capture with visible
edges (`build/local-pc/nz0-room00-artwork-integrated.png`). Its tall room/layer
`0B` was also captured during falling at scroll Y 541, with the generated join
at row 640 visible (`build/local-pc/nz0-shaft-join640-artwork-integrated.png`).
Clock Tower `NZ1` room/layer `08` has a frame-300 capture at scroll Y 516
(`build/local-pc/nz1-water-room08-artwork-integrated.png`): added wall edges,
waterfalls, gears and the translucent foreground pool render together.
This checks that pool position only; other water regions, travel paths and
animated palette changes still need review. All exported `NO4`, `NZ0` and
`NZ1` templates are prepared, which does not close their gameplay checklists.

Further frame-300 captures cover `TOP` room/layer `05`, `WRP` room/layer `00`,
and inverted Colosseum `RARE` room/layer `09`:
`build/local-pc/{top-room05,wrp-room00,rare-room09}-artwork-integrated.png`.
The Keep retains its intentional sky opening; the Colosseum retains the fountain
behind the foreground opening. Warp-room art was checked with the portal visible,
but teleport travel and destination transitions remain unchecked. The tall
`TOP` layer `02` has artifact reviews at section joins 640, 1280 and 1920;
its full travel route still needs a gameplay pass.

Reverse Catacombs `RCAT` room/layer `02` has a frame-300 capture with both
added edges and the background visible through the foreground opening:
`build/local-pc/rcat-room02-artwork-integrated.png`. `RCHI` room/layer `00`
has a dinosaur-shaft capture at scroll Y 279, and room/layer `03` has a cave
capture at scroll Y 512 with the generated join at row 640 visible:
`build/local-pc/rchi-dinosaur-artwork-integrated.png` and
`build/local-pc/rchi-cave-room03-frame300.png`. The latter is a stationary
position; the character landed before the requested scrolling threshold.

- [x] `RCAT` spike room/layer `18`: verify the extension at a physical room
  boundary and adapt palette selection. Static exports show green spike outlines
  and red masonry, while the altered runtime palette uses pale spikes and teal masonry.
  `build/local-pc/rcat-spikes-room18-artwork-integrated.png` shows scroll X 217
  and zero extension spans, so it verifies neither the added strip nor its colors.

  A later stable probe forces scrollX0 starting at frame100 and captures
  frame300. Its 2761 added FG spans are visible: the ON/OFF captures differ
  only in the left margin, bbox0,3..130,1077. The new strip is red beside the
  live teal/gray tiles. Four live palette rows (145,148,150,156) differ from
  the exported palette; runtime foreground flags become0x83 rather than3.
  This diagnosed the original fixed-RGB mismatch. Earlier evidence:
  `build/local-pc/rcat-stable-edge-palette-evidence.json`. Probes that forced
  the camera only at frame298 were too late for the presented capture and
  are not visibility evidence.

  Indexed metadata now resolves each new pixel through the boundary tile's live
  CLUT, preserves its transparency bit, and uses the tile's depth. The frame-300
  retest has 1,910 spans and follows the teal/gray palette; changes are confined
  to the added left margin, with the remaining pixels RGBA-identical.
  Evidence: `build/local-pc/indexed-artwork-validation.json` and
  `build/local-pc/rcat-spikes-indexed-edge-after.png`.
  Nearest-color mapping can leave minor texture/contrast differences. In this
  US reverse-castle room there is no manual light-switch state to test:
  `rcat/unk_32118.c` sets `RCAT_SPIKE_ROOM_LIT` true automatically each frame.
  The layer controller starts in its altered-palette state (`unk_31F1C.c`).
  Normal room approach/exit still needs a route check.

- [x] Reverse Chapel `RDAI` room/layer `06`: fill the two added lower stone
  blocks that the first AI draft left black. The frame-300 retest shows both;
  the original central viewport is pixel-identical before/after correction.
  Evidence: `build/local-pc/rdai-stone-retry-evidence.json` and
  `build/local-pc/rdai-room06-artwork-integrated.png`.

New frame-300 captures also cover `RLIB` room/layer `04` at scroll Y 48 and
`RNO0` room/layer `01` at scroll Y 516, under `build/local-pc/` with names
`rlib-room04-artwork-integrated.png` and `rno0-room01-artwork-integrated.png`.
These positions show the new edges; full travel paths remain open.

- [x] Review possible opaque black gaps flagged in
  `build/local-pc/widescreen-ai-inpaint/unpainted-edge-review.json`.
  Run `python3 build/local-pc/review_unpainted_edges.py` after future batches.
  This heuristic caught the Chapel failure; its flags can also be legitimate
  shadows and must be visually inspected before changing any artwork.

The 2026-10-27 review repaired six older omissions and two new ones using
explicit repair masks. Unselected generated pixels and all original RGBA pixels
were preserved. Five flags were black outlines already present at the actual
source boundary; the scanner now excludes that case, with five self-checks.
The remaining seven foliage/spike/rough-contour flags have frame-300 physical
boundary captures: `DAI` layer `0A`, `NZ1` layers `01`/`02`, and `RCAT` layers
`02`/`04`/`0B`/`10`. Retain them within the overall artwork quality the user
accepted on 2026-10-27; no additional solid-wall repair was warranted by these
stills. The upper foliage is partly covered by the HUD. These forced-camera
checks do not establish normal-route or moving-effect correctness, or classify
every dark pixel as intentional alpha. Captures, settings and hashes:
`build/local-pc/contour-runtime-review.json`.
Decisions: `build/local-pc/widescreen-ai-inpaint/review-20261027-decisions.json`.

- [x] `NO0` room/layer `15`: replace the missing upper wall strips. Before/after
  frame-300 captures show the walls filled, with the central original viewport
  pixel-identical: `build/local-pc/no0-room15-{before,after}-edge-repair.png` and
  `build/local-pc/no0-wall-repair-evidence.json`.

Frame-300 checks also show visible new edges in `RNO0` room/layer `0B`
(`build/local-pc/rno0-room0b.png`) and `RNO1` room/layer `05`
(`build/local-pc/rno1-room05.png`). Full paths remain unchecked. The tall
Gallery and Outer Wall templates have artifact seam reviews; that does not
verify their complete scrolling routes.

- [x] `RNO3` cave room/layer `08`: remove an invented rock border at the
  outer edges. Flat opaque maroon/purple regions now use the source color up
  to RGB channel value 96, with the same eight-column/five-row uniformity
  requirement. Four calibration tests pass. Frame-300 before/after captures
  preserve the central viewport pixel-for-pixel; both added edges render
  RGB(58,8,33). Evidence: `build/local-pc/rno3-flat-color-evidence.json`.

`RNO3` room/layer `03` has a frame-300 staircase capture with both edges:
`build/local-pc/rno3-stairs.png`. Four new trim/wallpaper omissions were
repaired with explicit masks; all other generated pixels were preserved.
Two crops were also regenerated. An initial composition bug cleared earlier
crops when combining multiple edits; the corrected composition preserves all
six crops exactly. The repair helper rejects transparent solid-art repairs,
and the scanner checks black and transparent omissions, with six self-checks.

- [x] `RNO2` room/layer `05`: fill the black patch behind the transparent
  balcony opening. The decorative arch geometry began at x=0; its PC version
  now adds one clipped repeat per row in the left margin. Original quads and
  artwork alpha stay unchanged. Regression checks cover both row layouts and
  original/wide/original/wide toggling through the actual overlay. Before/after
  frame-300 captures are `build/local-pc/rno2-balcony{,-fixed}.png`; central
  background pixels match exactly after excluding Richter's animation bounds.
  Evidence: `build/local-pc/rno2-balcony-repair-evidence.json`. Full-area paths
  remain unchecked.

All exported `RNO2`/`RNO3` templates are prepared. Their four tall originals
reconstruct exactly from overlapping sections, and their section joins have
artifact reviews. Full scrolling routes and weather effects remain unchecked.

All exported inverted Caverns `RNO4` templates are also prepared. Eight tall
originals reconstruct exactly; their 17 section joins have artifact reviews.
Frame-300 captures show cave room/layer `01` and staircase room/layer `06`:
`build/local-pc/rno4-{cave-room01,stairs-room06}.png`. Four small crystal-edge
black bands were repaired with five explicit crop masks, preserving originals
and unselected generated pixels. The heuristic report returns to seven older
contour flags; this does not close their scene-specific checks.

In `RNO4` shaft room/layer `00`, normal falling reaches scroll Y1180 at frame89
and Y1754 at frame171, showing joins1280 and1920 respectively. Captures:
`build/local-pc/rno4-shaft-join{1280,1920}-moving.png`. The first probe timed out
after landing because a competing GDB breakpoint bypassed its fallback; the
corrected single-callback probe stops normally. The game did not hang.
The lower-section capture uses a separate spawn below the platform; it does
not verify the intervening travel route. Other routes and water effects stay open.

All 52 exported stage codes now have their tile-layer templates prepared:
923 generated unique jobs and100 intentionally unchanged transparent jobs,
1218 generated template files and122 unchanged files. Generation is complete;
this does not establish whole-game rendering correctness. No original RGBA
pixels or alpha holes were changed. The native pack installs1790 edge images.

Final frame300 point captures cover `RNZ0` room00 (8055spans), `RNZ1` room08
(5894spans, scrollY516), and `RTOP` room05 (4034spans), under `build/local-pc/`
with names `rnz0-room00.png`, `rnz1-water-room08.png`, and `rtop-room05.png`.
The Keep preserves its sky opening. These captures do not verify full routes.

- [x] `RNZ1` room/layer08: fill the black right-margin patches behind the
  intentional foreground openings. Both Clock Tower gear backdrops now share
  `src/st/e_bg_gears.h`; PC builds use five repeat columns instead of three.
  Original quad positions and UVs stay unchanged, and extra columns stay
  outside the original-aspect viewport. Actual overlay tests cover all128 X/Y
  phase samples in both aspect modes and both castles. Before/after captures
  preserve the entire central viewport pixel-for-pixel; foreground alpha is
  untouched. Evidence: `build/local-pc/gear-backdrop-repair-evidence.json` and
  `build/local-pc/rnz1-water-room08-gears-fixed.png`. Full routes remain open.

Inverted Warp Room `RWRP` room00 has a frame300 capture with4423 added spans
and its portal visible: `build/local-pc/rwrp-room00.png`. Teleport travel and
destination transitions remain unchecked.

- [x] Richter arena `BO5`: extend the blue sky-land backdrop into the left
  margin. The shared `e_background_sky_land.h` adds one repeat in PC builds;
  the original five tiles retain their positions and UVs. Actual `DAI`, `RDAI`
  and `BO5` overlays pass original/wide/original/wide checks. In the arena's
  paired frame-300 captures, only the added left margin changes; the original
  central viewport is RGBA-identical. The two Chapel captures are unchanged
  because the foreground covers the extra tile at those positions. Evidence:
  `build/local-pc/sky-land-repair-evidence.json`. This does not close the
  arena's dialogue, combat or stained-glass checks.

- [x] Dream `DRE`: extend the cloud repeats and dark backing fill past the
  old viewport boundary. New right repeats are clipped outside x=256 so they
  cannot change the original view. The actual overlay passes all 257 initial
  camera offsets and original/wide/original/wide toggles. Paired frame-300
  captures preserve the central viewport exactly; the added edges also match
  after restoring widescreen at frame 600 (1,221/0/1,221 artwork spans).
  Evidence: `build/local-pc/dream-clouds-repair-evidence.json`.

  A later Alucard run with the US disc explicitly mounted reaches combat
  without injected movement, camera or flags. Six captures sample entry,
  camera pans, Lisa's dialogue, the transformation flash and return to combat.
  At the dialogue camera limit (scroll X 256), 2,470 artwork spans render.
  Disc tracks open successfully; dummy audio does not verify listening quality.
  Evidence: `build/local-pc/dre-intro-route-evidence.json`. Intervening frames,
  clone attacks, boss defeat and the exit remain unchecked.

- [x] Chapel/Richter stained glass: use the wide viewport when culling
  recursively subdivided panes. The old bounds dropped fragments visible only
  in the added margins. The regression fails before the fix and passes after
  it. Actual `DAI`/`BO5` overlays cover recursion depths 1–3 and 513 horizontal
  positions in both aspects; original-view primitive geometry, texture/color
  data and order remain identical, within the existing 60-primitive pool.
  Moving `DAI` room `09` captures restore left and right fragments at frames
  400/500 while the central viewport is RGBA-identical. The frame-600 pair has
  different presented animation phases; later frames follow player death.
  These are retained as diagnostics, not strict route comparisons. Room `0A`
  has no active stained-glass entity and cannot validate this effect.
  Evidence: `build/local-pc/stained-glass-repair-evidence.json`.

- [x] Both Libraries: extend distant-shelf culling, parallax repeat bounds,
  and the flat shadow band to the wide viewport. Actual `LIB`/`RLIB` overlays
  cover all four distant-shelf variants across 513 positions/both aspects and
  bookcase/furniture/shadow wrapping across 1,025 positions/four aspect toggles.
  The existing primitive pools and texture phases are retained; original-aspect
  shadows still use the original 255-pixel tile. Wide shadows use a quad and
  also cover the formerly unshaded final logical column.
  Paired `RLIB` room `00` captures restore right-edge shelf detail while the
  central view is exact. Confirmed-active room `09` captures show the shadow
  reaching the right edge in both castles; clean `LIB` pairs preserve the whole
  central view, and the `RLIB` frame-150 pair changes only the added edge plus
  that final column. These are health-assisted diagnostics with a normal camera,
  not combat/full-route checks. Failed or inactive-entity probes and mismatched
  presentation phases are retained separately. Evidence:
  `build/local-pc/library-parallax-repair-evidence.json`.

- [x] Prologue vortex: use wide bounds for every projected quad corner.
  The original 272-node pool and original-view mesh/UVs/motion are retained.
  Actual-overlay regression covers 1,024 animation frames and 7,858 added-edge
  fragments; all 12 paired captures retain an exact original central view.
  Evidence: `build/local-pc/vortex-repair-evidence.json`.

- [x] Prologue room breakup: capture the visible 296×207 background at its
  normal scale, including the generated sides, before the HUD is drawn.
  Eleven ordered GPU copies pack it into the existing 256×256 scratch texture;
  285 pieces replace the wide mode's old 225-piece reconstruction. Original
  aspect retains its original path. The visible crop supplies the boundary
  pieces; unseen pixels outside that crop are not captured.
  The regression checks every captured/reconstructed pixel, non-overlapping
  texture regions, unchanged gameplay randomness and transition timing. GPU
  readback checks both framebuffer origins at 1×/2×/4× internal resolution and
  excludes later overlays. Live disc-backed captures reach the second form,
  then switch to original aspect and restore widescreen successfully. These
  checks use temporary high health and an injected first-form defeat, with a
  normal camera. They do not establish a legitimate boss victory, audible
  audio quality, or post-battle photograph/fire coverage. Evidence:
  `build/local-pc/dematerialize-repair-evidence.json`. Start this transition in
  the intended aspect: a snapshot taken in original aspect has no side pixels
  to reveal if widescreen is enabled during the breakup. That switch remains
  open; the tested live aspect switches occur during the following vortex.

Quick routes (enable widescreen in F1; F4 enters fullscreen):

```sh
./run-linux.sh --demo 0
./run-linux.sh --player ric --spawn-point prologue-dracula-dialogue
```

From the dialogue spawn point, walk left into Dracula's lair. This starts before
the camera setup trigger so that the normal entry sequence runs.

## How to check and report

At each landmark, approach from both directions, stand at both camera limits,
and compare original aspect with widescreen. Include room entry/exit, dialogue
start/end/skip, and any transformation or destruction sequence. For moving
effects, check their beginning, middle, and end. A still image alone can miss a
mask that reverses or disappears too soon.

Record: stage code or area, nearby landmark, direction, character, whether
dialogue was active, screenshot/video, and settings. Classify the problem as
**missing artwork**, **layer seam**, **mask/gradient**, **camera**, or
**framebuffer effect**. Keep the checkbox open until those checks are complete.

## Prioritized landmarks

| Checked | Area / stage | Places and effects to inspect | Source starting point |
| --- | --- | --- | --- |
| [ ] | Prologue `ST0` | Opening reveal on the normal walking route; both screen edges after it finishes | `st/st0/title_card.c` |
| [ ] | Prologue `ST0` | Dracula doorway, camera pan, dialogue, skip, return to combat | `st/st0/2A218.c`, `st/st0/cutscene.c` |
| [ ] | Prologue `ST0` | Exterior stairs, clouds, moon, rotating 3D Clock Tower; reveal extra geometry without gaps | `st/st0/3AB08.c` |
| [ ] | Prologue `ST0` | First-form defeat, dissolving room background, vortex and second-form arena | `st/st0/3D8F0.c`, `st/st0/e_bg_vortex.c` |
| [ ] | Prologue `ST0` | Photograph shrink/rotation and fire transition after the battle | `st/st0/3AB08.c`, `EntityCutscenePhotograph` |
| [ ] | Entrance `NO3` / `NP3` / `RNO3` | Outdoor parallax, trees/bushes, lightning and far ends of backgrounds | `st/e_background_bushes_trees.h`, `st/e_background_lightning.h` |
| [ ] | Entrance `NO3` / `NP3` / `RNO3` | Merman-room transparent water; left/right water edges and camera scrolling | `st/e_transparent_water.h` |
| [ ] | Entrance / reverse entrance | Story camera pans, entrance gates and transition into interior rooms | `st/no3/cutscene.c`, `st/rno3/` |
| [ ] | Caverns `NO4` / `RNO4` | Water surface/body, waterfalls, surfacing bubbles, submerged views | `st/water_effects.h`, `st/water_effects_rev.h` |
| [ ] | Scylla `BO3` | Flood rise, water edges, doors and post-boss room transition | `boss/bo3/water_effects.c` |
| [ ] | Clock Tower `NZ1` / `RNZ1` | Outdoor clouds, gears, foreground water and narrow vertical shafts | `st/nz1/e_bg_gears.c`, `st/nz1/e_water_fg.c` |
| [ ] | Clock Tower `NZ1` | Four-gear secret door: enter/leave through each exit | `st/nz1/e_gear_puzzle.c` |
| [ ] | Keep `TOP` / `RTOP` | Tall cloud layers, outside stairs and warp approach | `st/e_clouds_keep.h`, `st/top/e_warp_trigger.c` |
| [ ] | Chapel `DAI` / `RDAI` | Clouds through windows, stained glass, broken glass and foreground pillars | `st/e_clouds.h`, `st/e_stained_glass.h` |
| [ ] | Richter arena `BO5` | Stained glass, camera framing, dialogue and battle effects | `boss/bo5/e_stained_glass.c`, `boss/bo5/e_clouds.c` |
| [ ] | Catacombs `CAT` / `RCAT` | Lava glow, lava geometry, particles and cavern background edges | `st/cat/e_lava_glow.c`, `st/cat/e_lava.c`, `st/rcat/e_cavern_background.c` |
| [ ] | Marble Gallery `NO0` / `RNO0` | Clock room doors/statues, room limits and camera locks in long rooms | `st/no0/clock_room.c`, `st/rno0/e_clock_room.c` |
| [ ] | Library `LIB` / `RLIB` | Foreground furniture, bookshelf depth layers, shadows and background endpoints | `st/lib/e_library_bg.c` |
| [ ] | Library `LIB` | Librarian interaction and Lesser Demon approach/arena | `st/lib/e_lesser_demon.c`, `st/lib/` |
| [ ] | `NO1` / `RNO1`, `NO2` / `RNO2` | Exterior ledges, distant houses, sky/land layers and camera endpoints | `st/e_background_house.h`, `st/e_background_sky_land.h` |
| [ ] | Colosseum `ARE` / `RARE` | Fountain, foreground/background separation and arena entrances | `st/are/e_fountain_water.h`, `st/rare/e_background_door_rubble.c` |
| [ ] | Mine `CHI` / `RCHI` | Narrow shafts, walls ending at room boundaries and foreground layers | `st/chi/background_block_init.c`, `st/rchi/` |
| [ ] | Dream `DRE` | House/cloud backdrop, Lisa/Succubus dialogue pans, clones and boss defeat | `st/dre/e_background_clouds.c`, `st/dre/e_cutscene_actors.c` |
| [ ] | Warp rooms `WRP` / `RWRP` | Background dimming, teleport distortion, arrival and departure | `st/wrp/warp.c`, `st/rwrp/warp.c` |
| [ ] | Center/final rooms `CEN` / `RCEN` | Clock-room framing, dialogue, transitions and final sequence | `st/cen/cutscene.c`, `st/rcen/` |
| [ ] | Olrox `BO0` | Transformation, explosions and arena edges | `boss/bo0/313A8.c` |
| [ ] | Beelzebub `RBO1` | Large body/chain framing, flies beyond original edges and defeat | `boss/rbo1/e_beelzebub_parts.c`, `boss/rbo1/e_beelzebub_chains.c` |
| [ ] | Every other `BO*` / `RBO*` arena | Enter from each available side; dialogue, camera lock, phase changes and death effects | `src/boss/` |
| [ ] | Every area | Stage-name popup, fade to/from black, save-room entry, doors and vertical/horizontal room handoffs | `st/e_stage_name_us.h`, `dra/624DC.c`, `dra/5087C.c` |
| [ ] | Spells, weapons and familiars | Screen-wide flashes/overlays, expanding attacks, trails and effects crossing an edge | `src/dra/`, `src/weapon/`, `src/servant/` |
| [ ] | UI return paths | Pause, map, game over, movies, then return to gameplay without retaining a smaller viewport | `src/dra/game_handlers.c`, `src/pc/movie.c` |

Source paths abbreviated as `st/`, `boss/`, and `dra/` are relative to `src/`.
Replays exercise some of these paths, but do not mark a visual checkbox complete.

## Choosing the fix

- Extend reusable sky/tiles/parallax only where the original data can tile
  coherently; inspect foreground and background separately.
- Extend masks and effect draw bounds while preserving gradient/texture phase.
  Avoid resizing unrelated scenery polygons based on their size alone.
- Framebuffer capture effects need their capture, draw environment, texture
  coordinates and reconstruction checked together; stretching the captured
  4:3 picture can introduce another seam.
- When artwork really ends, use camera constraints or an intentional matching
  backdrop. Keep gameplay at its normal scale. New artwork would be a separate
  replacement pack, not something the port can recover from absent pixels.

## Single-column room inventory

The appendix is a width-based risk filter from this checkout's extracted US
`src/{st,boss}/*/gen/rooms.c` tables: **750 room entries across 43 tables, 513
single-column entries**. It is not the full room inventory: other overlays
store room data elsewhere. Connector/transition entries are included and may
not be independently playable. A narrow room is not automatically a defect.

Numbers are **zero-based hexadecimal room-table indices**, not object-layout
IDs or map coordinates. Mark each stage after checking its listed rooms and
their entrances, including what appears beyond both original screen edges.

| Checked | Stage table | Single-column room indices |
| --- | --- | --- |
| [ ] | `ARE` | `01`, `03`, `09`, `0A`, `0E`, `0F`, `10`, `11`, `12`, `13` |
| [ ] | `BO1` | `01`, `02` |
| [ ] | `BO3` | `01`, `03`, `04` |
| [ ] | `BO4` | `01`, `02` |
| [ ] | `BO5` | `01`, `02` |
| [ ] | `BO6` | `00` |
| [ ] | `CAT` | `00`, `01`, `02`, `04`, `05`, `06`, `07`, `08`, `09`, `0D`, `0E`, `0F`, `11`, `13`, `16`, `1C`, `1D` |
| [ ] | `CEN` | `00`, `02`, `03`, `04` |
| [ ] | `CHI` | `00`, `03`, `05`, `06`, `08`, `09`, `0A`, `0C`, `0D`, `0E`, `0F`, `10`, `11`, `12` |
| [ ] | `DAI` | `06`, `07`, `08`, `0A`, `0C`, `0F`, `10`, `12`, `13`, `14`, `15`, `16`, `17`, `18`, `19` |
| [ ] | `LIB` | `01`, `02`, `04`, `07`, `08`, `0B`, `0D`, `0E`, `0F` |
| [ ] | `MAD` | `00`, `01`, `02`, `03`, `04`, `05`, `06`, `07`, `08`, `09`, `0A`, `0B`, `0C`, `0D`, `0E`, `0F`, `10`, `11`, `12`, `13` |
| [ ] | `MAR` | `00`, `01`, `02` |
| [ ] | `NO0` | `01`, `03`, `09`, `0B`, `0D`, `0E`, `10`, `11`, `15`, `16`, `17`, `18`, `19`, `1A`, `1B`, `1C`, `1D`, `1E`, `1F`, `20`, `21`, `22`, `23`, `24`, `25`, `26` |
| [ ] | `NO1` | `00`, `05`, `06`, `0A`, `0C`, `0E`, `0F`, `10`, `11`, `12`, `13`, `14`, `15`, `16` |
| [ ] | `NO2` | `00`, `01`, `05`, `06`, `0A`, `10`, `11`, `12`, `13`, `14`, `15`, `16`, `17`, `18` |
| [ ] | `NO3` | `01`, `03`, `04`, `06`, `08`, `0A`, `0B`, `0C`, `0D`, `0E`, `10`, `11`, `13`, `14`, `15`, `16`, `17`, `18`, `19`, `1A`, `1B`, `1C`, `1D`, `1E`, `1F` |
| [ ] | `NO4` | `00`, `01`, `02`, `03`, `04`, `05`, `06`, `07`, `08`, `0A`, `0D`, `0E`, `10`, `11`, `12`, `13`, `15`, `18`, `1C`, `1E`, `1F`, `20`, `21`, `22`, `23`, `24`, `25`, `26`, `27`, `28`, `29` |
| [ ] | `NP3` | `01`, `03`, `04`, `06`, `08`, `0A`, `0B`, `0C`, `0D`, `0E`, `10`, `11`, `12`, `13`, `14`, `15`, `16`, `17`, `18`, `19`, `1A`, `1B`, `1C` |
| [ ] | `NZ0` | `00`, `01`, `04`, `05`, `06`, `08`, `09`, `0B`, `0C`, `0D`, `0E`, `0F`, `16`, `17`, `18`, `19`, `1A`, `1B`, `1C`, `1D`, `1E`, `1F` |
| [ ] | `NZ1` | `00`, `02`, `05`, `06`, `07`, `08`, `0B`, `0C`, `0D`, `0E`, `0F`, `10` |
| [ ] | `RBO0` | `01`, `02` |
| [ ] | `RBO3` | `01`, `02` |
| [ ] | `RBO4` | `01`, `02` |
| [ ] | `RBO5` | `00`, `01`, `02` |
| [ ] | `RBO7` | `01`, `02` |
| [ ] | `RCAT` | `00`, `01`, `02`, `04`, `05`, `06`, `07`, `08`, `09`, `0D`, `0E`, `0F`, `11`, `13`, `16`, `1C`, `1D` |
| [ ] | `RCEN` | `00`, `02`, `03`, `04` |
| [ ] | `RCHI` | `00`, `03`, `05`, `06`, `08`, `09`, `0A`, `0C`, `0D`, `0E`, `0F`, `10`, `11`, `12` |
| [ ] | `RDAI` | `06`, `07`, `08`, `0A`, `0C`, `0F`, `10`, `12`, `13`, `14`, `15`, `16`, `17`, `18`, `19` |
| [ ] | `RLIB` | `01`, `02`, `04`, `07`, `08`, `0B`, `0D`, `0E`, `0F` |
| [ ] | `RNO0` | `01`, `03`, `09`, `0B`, `0D`, `0E`, `10`, `11`, `15`, `16`, `17`, `18`, `19`, `1A`, `1B`, `1C`, `1D`, `1E`, `1F`, `20`, `21`, `22`, `23`, `24`, `25`, `26` |
| [ ] | `RNO1` | `00`, `05`, `06`, `0A`, `0C`, `0E`, `0F`, `10`, `11`, `12`, `13`, `14`, `15`, `16` |
| [ ] | `RNO2` | `00`, `01`, `05`, `06`, `0A`, `10`, `11`, `12`, `13`, `14`, `15`, `16`, `17`, `18` |
| [ ] | `RNO4` | `00`, `01`, `02`, `03`, `04`, `05`, `06`, `07`, `08`, `0A`, `0D`, `0E`, `10`, `11`, `12`, `13`, `15`, `18`, `1C`, `1E`, `1F`, `20`, `21`, `22`, `23`, `24`, `25`, `26`, `27`, `28`, `29` |
| [ ] | `RNZ0` | `00`, `01`, `04`, `05`, `06`, `08`, `09`, `0B`, `0C`, `0D`, `0E`, `0F`, `16`, `17`, `18`, `19`, `1A`, `1B`, `1C`, `1D`, `1E`, `1F` |
| [ ] | `RNZ1` | `00`, `02`, `05`, `06`, `07`, `08`, `0B`, `0C`, `0D`, `0E`, `0F`, `10` |
| [ ] | `RTOP` | `04`, `05`, `06`, `07`, `08`, `09`, `0A`, `0B`, `0C`, `0D`, `0E`, `0F` |
| [ ] | `RWRP` | `00`, `01`, `02`, `03`, `04`, `05`, `06`, `07`, `08`, `09`, `0A`, `0B`, `0C`, `0D`, `0E` |
| [ ] | `ST0` | `02` |
| [ ] | `TOP` | `04`, `05`, `06`, `07`, `08`, `09`, `0A`, `0B`, `0C`, `0D`, `0E`, `0F` |
| [ ] | `WRP` | `00`, `01`, `02`, `03`, `04`, `05`, `06`, `07`, `08`, `09`, `0A`, `0B`, `0C`, `0D`, `0E` |
