# Widescreen visual checklist

US native port, `recomp-upgrades`, 2026-10-27. This is an inspection inventory,
not a list of confirmed defects or a claim of full-game visual coverage.
Check both castles: similar rooms can use different rendering implementations.

## Artwork delivery status

The exported artwork set is generated and integrated: 1,340 output templates
retain their original dimensions and protected RGBA, including intentional layer
openings. The installed pack has 1,790 RGB edges and matching indexed metadata
for 984 layers across 52 overlays. Every installed edge section has native GPU
reference coverage. Runtime checks and the backdrop repairs below supplement
that pipeline validation. The open route checkboxes track broader manual
gameplay QA; they do not mean those rooms lack generated artwork. Minor accepted
AI details remain, and this is not evidence of a complete native playthrough.

## Shared interface checks

- [x] Pickup, gold and enemy-name banners keep their border, corners, background
  and text aligned. HUD anchoring requires `DRAW_ABSPOS`; banner polygons share
  HUD priorities but are not HUD elements. The regression fails before the fix
  and covers both alignments, both aspects and 100/125/150% HUD scales. Live
  Badelaire captures confirm the repair. Evidence:
  `build/local-pc/pickup-banner-repair-evidence.json`.

## Reported prologue issues

- [x] Richter HP fill stays inside its frame at every health level. The shared
  HUD adjustment now identifies Richter's screen-positioned HUD textures without
  a top-row cutoff; boss fills and falling frame pieces use the same anchor.
  The regression fails before the fix, then covers full-to-empty HP, boss frame
  animation and repeated aspect switches. Five paired live captures confirm
  half/1-HP alignment, unchanged full HP and exact original-aspect rendering.
  All 13 native tests and US checksums pass. HP is assigned diagnostically;
  a live boss fight and OpenGL are not rechecked. Evidence:
  `build/local-pc/richter-hud-repair-evidence.json`.

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
behind the foreground opening. Warp-room art was checked with the portal visible.
Later checks below verify one departure/arrival route in each castle; other
routes remain open. The tall
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
  `build/local-pc/dematerialize-repair-evidence.json`. Aspect changes now wait
  until the effect finishes, so an original-aspect snapshot is never asked to
  supply uncaptured side pixels. The saved choice is preserved and F1 labels
  the queued change; native tests cover both directions and lifecycle cleanup.

- [x] Prologue photograph capture/projection: preserve the complete wide scene
  and HUD during sepia tint, shrink and rotation. The shared ordered capture
  packs the visible pixels into the existing scratch texture. Twelve textured
  pieces keep their original pixel scale, with a separate paper border. The
  later framebuffer copy is split so fullscreen expansion cannot stretch it;
  its burn mask covers the larger projected photograph.
  Actual-overlay tests cover every visible pixel, projection without automatic
  stretching, unchanged randomness/phase timing, and safe partial ENV failure.
  Eighteen disc-backed captures reach the fire effect, final fade and following
  game state. Relative phase timings match the checkpoint exactly (461 frames
  from the first observed tint state through exit). Both boss defeats are
  injected with temporary high health; no legitimate victory or audio listening
  claim. Aspect changes now wait for the photograph to finish; native tests
  exercise both starting aspects and retain the same timing. Evidence:
  `build/local-pc/photograph-repair-evidence.json`.

- [x] Capture-aspect changes and prologue handoff: queue aspect changes until
  the owning room-breakup or photograph effect ends. Keep the saved choice;
  clear the hold when the entity is destroyed/replaced or stage/game state
  changes. Native tests cover both directions and lifecycle exits; 25 live
  captures confirm both directions for both effects without invalid copies.
  The natural story scroll reaches Alucard's `NO3` entrance with a wide view,
  then continues for 600 frames (camera X 0→3616) with no hold retained.
  The probe exposed a diagnostic spawn flag leaking into the next stage;
  restoring its previous value fixes that crash. The new regression fails
  against the checkpoint helper and passes for all four prior load modes.
  Boss defeats/health are injected; later combat and routes remain unchecked.
  The F1 pending label uses the tested query; its window was not visually tested.
  Evidence: `build/local-pc/capture-aspect-repair-evidence.json`.

- [x] Indexed-edge palette remapping: sample the actual GPU palette selected by
  `g_ClutIds`, including per-color blending and custom VRAM palettes. Native
  comparisons cover all three standard banks, four blend modes and four
  accessibility palettes. A disc-backed `NO3` room `0D` lightning cycle has
  matching simulation states and unchanged renderer flush counts. Across 12
  consecutive-frame comparisons the central image is pixel-identical; four
  bright frames correct 30,290 pixels in the left extension. Diagnostic spawn
  only; other Entrance routes remain unchecked.
  Evidence: `build/local-pc/live-lightning-repair-evidence.json`.

- [x] Keep `TOP` room `06` elevator and lion lighting: board the elevator from
  a diagnostic spawn at `(128,380)`, then let the original entities run without
  injected input, health, camera or castle flags. The platform ascends, all four
  lion pairs ignite, their palettes flicker and the platform descends. Both
  runs reach frame 800 with identical simulation records. Ten matching captures
  preserve the original central image exactly while correcting both outer
  strips. A compositor delay resolves one earlier adjacent-frame capture;
  comparison assertions remain exact. A normal full jump reaches the raised
  right doorway, enters adjoining room `0A` and returns. Three more captures
  cover the adjoining room, closing door and settled return; the door reaches
  idle at frame 956 with HP 70, all lamp flags and the wide viewport preserved.
  Other Keep and reverse-Keep routes remain separate checks. Evidence:
  `build/local-pc/keep-lighting-repair-evidence.json`.

- [x] Entrance transparent-water integration: exercise `NO3`, `NP3` and `RNO3`
  full/partial pools across scroll positions 0–1024 and both aspects. The former
  regression only tested two normal-castle overlays despite claiming inverted
  coverage. Its replacement checks contiguous coverage, original central
  primitive data, texture phase, partial endpoints and the 16-node pool bound.
  Twelve disc-backed runs provide 52 image pairs: original central pixels stay
  identical, normal edges follow water palette cycling and inverted ceiling
  pools retain their endpoints. All water remains visible in these captures.
  A `NO3` room `07` direction/jump route covers camera X=20→492→20 and returns
  at frame 3553, with nine captures. This route uses Holy Symbol/high-health
  assistance; enemy collision remains active. It stays inside the room and
  does not verify entrances/exits or other areas' water effects. All 13 native
  tests pass. Evidence: `build/local-pc/entrance-water-integration-evidence.json`.
  Bright Merman sprite colors during collisions also occur in the earlier
  renderer: three complete-image comparisons are exact. Their original-console
  correctness remains open; see `build/local-pc/entrance-water-sprite-triage.json`.

- [x] Caverns/Scylla water clipping: extend water surfaces, body tint and
  underwater shimmer from the old `[-16,272]` clip to cover the native margins.
  Preserve the original coordinate origin, unsigned texture phase, flow timing
  and actual wet/dry endpoints. Regression checks cover `NO4`, `BO3` and `RNO4`,
  both aspects, partial pools and flowing regions visible only in a new margin.
  The clipping-only attempt failed central-phase comparison; the repaired
  version passes all 13 native checks and the US binary-matching gate.
  Four before/after scenes yield 20 paired images with identical original
  central pixels. Fifteen pairs show water/shimmer; the reverse waterfall view
  has water offscreen and counts only as a negative control. The 46 static
  Caverns water groups need at most 7 of 16 nodes under conservative counting;
  later script-mutated tables and full routes still require checks.
  Evidence: `build/local-pc/cavern-water-repair-evidence.json`.

- [x] Scylla live flood and shaft return: a diagnostic start in lower room `02`
  lets the original controller raise water from 0 to 208. Actual jump/bat inputs
  reach upper room `00`, sustain the main encounter, then return below after an
  assisted defeat, all death-flame phases and natural drainage. Both old/current
  runs finish at frame 3052 with identical phase/gameplay records. Eighteen image
  pairs preserve the original center exactly; the repaired margins fill the old
  water gutters. Returned water level is 0, gate flags are clear and the wide
  viewport persists. Health/MP and three relics are enabled in the child, with
  one injected main-boss death flag. No forced camera, room or water level.
  This does not verify the preceding Wyrm miniboss, side-gate traversal or
  intermediate drainage views in the lower room; drain-phase captures are in
  the upper arena. No new source/art changes were needed after the water repair.
  Evidence: `build/local-pc/scylla-flood-route-evidence.json`.

- [x] Complete extracted tile-layer inventory and native loader audit: all 984
  layers across 52 overlays match the compiled layouts, tile definitions,
  dimensions, flags and priorities. All 825 room records agree with the native
  overlays: 691 actual rooms and 134 transition records. Every actual room has
  exported references. The 1,339 layer templates have completed jobs; the extra
  1,340th job output is a composite Dracula preview. The 18 wrapping layers
  require no static edge extension. All 1,790 installed RGB/indexed edge pairs
  preserve dimensions and alpha, and the native loader selects the expected
  indexed span counts through 1,038 layer selections across 70 stage IDs,
  including aliases. Original pixels and intentional transparent rows remain
  protected; 122 templates correctly remain entirely unextended. This verifies
  inventory and loading, not every scene's rendered appearance or moving route.
  Evidence: `build/local-pc/artwork-inventory-audit.json` and
  `build/local-pc/runtime-artwork-inventory-audit.json`.

- [x] ST0 layer `00` background right: diagnostic upper/lower boundary renders
  confirm a two-column transparent fade exposes sky beside the solid wall.
  A built-in imagegen edit supplies replacement opacity only for those 800
  generated pixels. Both output files remain 296×512; every RGB value, original
  pixel and intentional transparent area is unchanged. Two before/after pairs
  preserve the original central image exactly and change only screen columns
  1907–1919 at 1920×1080. All seven pack tests and the full inventory/native
  loader audit pass after rebuilding the pack. This is a forced-boundary render
  check, not a normal traversal claim. Evidence:
  `build/local-pc/st0-alpha-repair-evidence.json`.

- [x] Review the other four ST0 extension-alpha candidates. Native boundary
  renders confirm solid-wall fades in layer `01` foreground right and layer
  `03` foreground left/right. Three built-in imagegen edits provide wall
  opacity for only those 448/224/448 generated pixels; all existing RGB and
  protected RGBA remain identical. Three paired 1920×1080 captures preserve the
  original center exactly, with changes confined to the outer 6 or 13 screen
  columns. All seven pack tests, the complete asset audit and native loading
  across 70 stage IDs pass. Direct layer selection and the existing debug
  freeze isolate these renders; they do not verify normal travel or collision.
  The single partially transparent layer `00` foreground pixel remains within
  the user's accepted minor contour differences. An allowed painting strip
  does not require every pixel to be opaque; no general alpha fill is applied.
  Evidence: `build/local-pc/st0-alpha-v2-repair-evidence.json`. The remaining
  pixel is still reported by `artwork-inventory-audit.json` under `partial_alpha`.

- [x] Full installed-edge GPU sweep: render all 1,790 indexed edge files through
  every vertical section at native 1x. The 4,551 frames match independent
  original 4-bit indexed-sprite references exactly: 18,841,140 edge pixels,
  including transparent rows and padding, with 241,166,592 original-width
  center pixels unchanged. Custom opaque CLUTs isolate artist alpha, palette
  indexing and alternate-bank selection; natural palette transparency and
  blending remain covered separately by `pc_upgrades`. A deliberately wrong
  expected pixel is rejected. This covers installed edge rasterization, not
  script-mutated boundaries, animated scenery or room travel. Source review
  also confirms only background slot zero receives the room's edge artwork.
  Evidence: `build/local-pc/artwork-gpu-sweep-evidence.json`.

- [x] Keep cloud integration in `TOP` and `RTOP`: check individual horizontal
  and depth phases at 17 camera heights, then the complete natural 65,536-tick
  counter cycle at the maximum-visible-row camera position. Across 1,046,528
  updates and original/wide/original/wide logical bounds, the original central
  geometry and counter increments remain identical, including integer wrap.
  The peak is 88 of 112 primitives. This is phase sampling plus a full natural
  cycle, not every Cartesian combination of independently assigned counters.
  Ten disc-backed child runs yield 21 paired 1920×1080 captures with identical
  original centers and recorded gameplay/cloud state. Nineteen pairs reveal
  added clouds in the margins; two occluded TOP views are unchanged controls.
  Both narrow room `05` scenes combine clouds with generated artwork (2,682 TOP
  and 3,004 RTOP spans). A natural RTOP room `02` fall changes camera Y from 493
  to 607 between captures. Initial spawns and one health increase are assisted;
  movement and camera positions are not injected. Existing cloud textures and
  clipping cover these cases; no new art or game-source changes are needed.
  Room approaches, exits, outside stairs and warp travel remain open.
  Evidence: `build/local-pc/keep-cloud-integration-evidence.json`.

- [x] Shared 3D-house culling: the fixed entity-X cutoff at 512 hides far-house
  faces that still project into the wide view at X=274. Use `PC_RIGHT(0x200)`
  in the shared helper, preserving original-aspect and console behavior. The
  new regression fails before the fix, then passes in `NO2`, `RNO2`, `DRE`
  and `BO0`, including aspect reversal and the unchanged 16-node allocation.
  All 13 native tests and the US checksum gate pass. Four disc-backed NO2
  Courtyard runs produce 28 paired captures with identical original centers
  and recorded gameplay fields. Ground-level houses are occluded controls;
  an assisted bat route exposes the roof fringe higher up. Three pairs restore
  216–252 pixels in the last six screen columns; the other 25 are unchanged.
  Existing model/textures supply the detail, with no bitmap edits. Movement and
  camera remain normal after the initial spawn; health/MP/relics are assisted
  and enemy collisions remain active. DRE/BO0 activation at this cutoff is not
  established by their function-level checks. The reverse-room feedback shader,
  full routes and room transitions remain open. Evidence:
  `build/local-pc/house-cull-repair-evidence.json`.

- [x] Catacombs projected cave panels in `CAT` and `RCAT`: add one repeated
  column per side on PC (27 primitives instead of 21), using existing textures.
  All four variants cover both margins across all 64 horizontal phases; extra
  columns stay outside the original picture. The reverse caves also had native
  coordinate corruption from indexing the 32-bit scratchpad through 64-bit
  `long*`; use the existing `SPAD` indexing consistently. The corrected original
  seven columns retain identical complete primitive payloads after expansion.
  The regression covers aspect reversal, panel joins, texture/color stability
  and allocation bounds. All 13 native tests and US checksums pass. Eight
  disc-backed runs provide 12 paired 1920×1080 captures in rooms `0A` and `0B`:
  three normal lava-cave pairs restore edge pixels with an identical center;
  three normal bridge pairs are occluded controls; six inverted pairs correct
  the malformed central ice panels as well as their margins. Recorded player,
  camera and health values match. Initial spawns and health are assisted;
  full traversal, room transitions and audio remain unchecked. No bitmap edits.
  Evidence: `build/local-pc/catacomb-panels-repair-evidence.json`.

- [x] CAT lava glow follows aspect changes after initialization. Its original
  state reaches step `2`, while the existing PC resize code handled only the
  allocation fallthrough and step `3`. Add the PC-only step `2` label. The new
  regression fails before the repair, then passes through original/wide/
  original/wide with one primitive and unchanged Y, colors and blending. Two
  disc-backed room `0A` runs provide four paired captures: each wide view restores
  106,600 margin pixels; both original views are identical. The original central
  image and recorded player/camera/health remain exact in every pair. All 13
  native tests and US checksums pass; no bitmap edits. Initial spawn/health are
  assisted and aspect settings use normal game updates.
  Evidence: `build/local-pc/catacomb-liquid-glow-evidence.json`.

- [x] Investigate CAT/RCAT liquid geometry separately from the glow. Across
  24,576 synthetic moving-camera/wave updates, opaque and main transparent
  surfaces cover both margins wherever a visible row has full original-width
  coverage. Each actor retains 26 nodes. The far bridge layer (`params=2`) is
  narrower at some phases; this is a geometry finding, not yet a confirmed
  visible gap behind foreground arches. Eight early room `0B` captures verify
  both actual actors are present, but fade-in and falling camera positions leave
  exposure unresolved. Do not count these probes as bridge traversal or exact
  GPU rasterization. No liquid geometry changes; bridge exposure, particles,
  transitions and audio remain open. Evidence: the same JSON above.

- [x] CAT/RCAT thin bridge liquid exposure is confirmed and repaired. Four
  PC-only quads repeat the existing edge texture outward; the original 26-node
  simulation, wave state, palettes and blending remain unchanged. Repeats use
  the nominal depth ratio, since animated adjacent-edge widths can compress.
  They hide in original-aspect mode; other liquid variants still use 26 nodes.
  A regression fails before the change, then verifies both castles over 1,024
  synthetic moving-camera/wave steps and four aspect modes per step. All 13
  native tests and US checksum checks pass.
  Eight disc-backed runs yield 31 paired wide captures and six original-aspect
  pairs. Twenty-two wide pairs restore 65–2,243 display pixels; nine are unchanged
  controls. RCAT flies from camera X=20 to 236 and back with normal inputs after
  assisted spawn/health/MP/relic setup, completing at frame 678. CAT has static
  bridge views with Discus Lord active. Original quad payloads and recorded
  player/camera/health match. Thirty wide centers are exact; one view fills a
  60-pixel old mesh hole just inside the central area, verified outside existing
  liquid geometry. All six complete original-aspect frames are pixel-identical.
  Combining both liquid layers with foreground alpha removes all 940 sampled
  exposed margin positions along this route. This is a geometry exposure audit,
  not exhaustive GPU rasterization. Isolated far-layer near-wave rows are not
  evidence of visible gaps without the paired front surface and foreground.
  CAT travel, further wave phases, transitions and OpenGL remain open.
  No bitmap edits. Evidence: `build/local-pc/bridge-liquid-repair-evidence.json`.

- [x] Restore the projected swivel bookcases in `LIB` and `RLIB`. Four source
  lines used host-sized `long*` indexing for packed scratchpad coordinates and
  lighting colors, overlapping the buffers on 64-bit Linux. Use 32-bit `SPAD`
  indexing, preserving the console layout. Corrupted packed colors also changed
  primitive types, allowing master nodes to be reused between models. The new
  regression fails before the repair; separate GTE projection arrays then agree
  through 2,048 sampled updates: four model variants, 64 rotation phases and
  original/wide/original/wide settings in both overlays. Vertex-light multipliers
  remain grayscale, master types stay GT4 and allocations remain 37 nodes.
  All 13 native tests and US checksums pass.
  Eight disc-backed room `01` runs give 12 paired captures, covering both castles
  and both aspects. All restore visible bookcase artwork; four models now own
  148 independent primitives instead of sharing 12 duplicate node visits.
  Recorded player/camera/HP/secret state matches in each pair. Only initial
  spawns are assisted. A separate RLIB test starts beside the chair, uses normal
  leftward input, unlocks the secret at frame 173 and rotates the bookcase from
  −192 to −525 by frame 238. No forced angle, flag, camera, health or position
  after spawn. Earlier probes of the neighboring shelf entity and a chair-blocked
  approach are excluded. Normal-castle pushing, full passage traversal, shadow
  endpoints and further room approaches remain open. Existing textures suffice;
  no bitmap edits. Evidence: `build/local-pc/projected-bookcase-repair-evidence.json`.

- [x] Movable Library bookcase shadows follow the wide right edge on every
  update. Two PC-only assignments use `PcViewRight()` with the existing quad,
  allocation, Y anchors and angle-dependent colors. The aspect-switch regression
  fails before the fix; all 13 native tests and US checksums pass afterward.
  Four disc-backed runs provide eight original/wide/original/wide capture pairs:
  each wide view restores 49,815 LIB or 40,430 RLIB display pixels, while all four
  complete original-aspect images remain exact. Player/camera/HP/secret state and
  shadow colors/blending match. The sloped LIB shadow edge adapts with its new
  endpoint; wide central pixels are not claimed identical. Separate normal-castle
  tests use ordinary rightward input from beside the chair, unlock at frame 163
  and rotate from -192 to -525 by frame 228. Every recorded interaction field
  agrees before/after the cosmetic repair. Initial spawns/settings are assisted;
  no forced flag, angle, health, camera or position after spawn. Full passage
  traversal and room approaches remain open. No bitmap edits. Evidence:
  `build/local-pc/bookcase-shadow-repair-evidence.json`.

- [x] Entrance bushes and trees retain the preceding repeat cycle in the wide
  left margin. Two PC-only conditions start one cycle earlier when necessary,
  preserving original phase and the existing 72/32-node allocations. The new
  regression fails before the repair, then checks 15,480 updates across three
  overlays, ten variants, sampled X positions and four aspect settings. A wider
  245,790-update geometry sweep finds no missing preceding bush pieces or tree
  bounds. All emitted counts agree with the complete repeat model; an existing
  theoretical 73rd bush piece remains wholly beyond the viewport. All 13 native
  tests and US checksums pass. Nine paired live views preserve original centers,
  central primitives and gameplay fields: three NP3 views restore 2,040 display
  pixels each; six NO3/RNO3 views are unchanged controls. Initial spawns/health
  are assisted; RNO3 also uses MP/relic assistance and normal upward bat input.
  No bitmap edits. Evidence: `build/local-pc/shared-scenery-integration-evidence.json`.

- [x] Audit Clock Tower model generation in TOP/RTOP: 25 active pieces of 40
  allocated remain identical through four logical aspect bounds at 82,818
  sampled entity positions (331,272 updates). Texture metadata is retained and
  no width-based cull or allocation loss is found. This is geometry evidence,
  not a full raster or traversal check. Subsequent normal bat approaches from
  actual layout markers complete in both castles. Twenty-one paired captures
  compare normal drawing with a diagnostic hidden-model control: ten TOP views
  expose 54,743–94,153 display pixels in the wide margin; nine RTOP views expose
  13,962–125,851, with two earlier unchanged controls. Geometry, camera, player,
  health and update counts agree. All 25 textured pieces remain present. Initial
  spawns/health/MP/relic are assisted; movement uses normal inputs. A missed
  advanced-spawn marker and a lower RTOP wall-corner stall are excluded. No
  model/source changes or additional bitmap artwork needed. Evidence:
  `build/local-pc/clock-model-margin-evidence.json`.

- [x] Reverse courtyard local framebuffer effect: four disc-backed RNO2 room
  `08` runs compare its normal drawing against a diagnostic hidden-shader
  control in both aspects. Ten paired views show the feedback texture while
  ordinary right/left input moves the camera from X=117 to 297 and back. Every
  changed pixel stays inside the authored `57..129`, `135..207` composite;
  margins and the rest of each frame remain exact. All eight primitives,
  player/camera/health and update counts agree. The `80×192` scratch target and
  local `72×72` composite need no wider artwork. Only initial spawn/health are
  assisted. Other markers, full room approaches, OpenGL and audio remain open.
  No source or bitmap edits. Evidence:
  `build/local-pc/house-shader-integration-evidence.json`.

- [x] Warp-room fades retain the full wide viewport during departure and
  arrival. Four disc-backed runs complete Keep-to-Olrox warps in both castles,
  using emulated global UP input after assisted spawn/unlock setup. Twenty-four
  paired captures compare the normal full-screen fade with a diagnostic hidden
  fade: 16 visibly cover both margins and eight are unchanged controls. At peak
  white, every sampled visible margin color channel is at least 240. Destination
  views return exactly to the hidden-fade control. All 24 primitive payloads and
  recorded gameplay fields agree apart from the intended hide bit. The reverse
  platform raises/lowers normally, reaching ready at count 454; normal warp is
  ready at 358. A player-only input probe and a reverse spawn below the platform
  failed to activate and are excluded. No forced script steps or positions after
  spawn. No source or bitmap edits needed; other destinations, mid-warp aspect
  switches, OpenGL and audio remain open. Evidence:
  `build/local-pc/warp-backdrop-integration-evidence.json`.

Quick routes (enable widescreen in F1; F4 enters fullscreen):

```sh
./run-linux.sh --demo 0
./run-linux.sh --player alu --spawn-point prologue-dracula-dialogue
```

From the dialogue spawn point, walk left into Dracula's lair. This starts before
the camera setup trigger so that the normal entry sequence runs. Alucard story
mode still plays Richter in the prologue and can continue into Alucard's game;
`--player ric` instead selects the debug Richter route.

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

For diagnostic spawns in long rooms, confirm environmental controllers and
their visible primitives are present. Starting beyond their entry positions can
omit water or parallax that a normal approach would have initialized.

## Prioritized landmarks

| Checked | Area / stage | Places and effects to inspect | Source starting point |
| --- | --- | --- | --- |
| [ ] | Prologue `ST0` | Opening reveal on the normal walking route; both screen edges after it finishes | `st/st0/title_card.c` |
| [ ] | Prologue `ST0` | Dracula doorway, camera pan, dialogue, skip, return to combat | `st/st0/2A218.c`, `st/st0/cutscene.c` |
| [ ] | Prologue `ST0` | Exterior stairs, clouds, moon, rotating 3D Clock Tower; reveal extra geometry without gaps | `st/st0/3AB08.c` |
| [ ] | Prologue `ST0` | First-form defeat, dissolving room background, vortex and second-form arena | `st/st0/3D8F0.c`, `st/st0/e_bg_vortex.c` |
| [ ] | Prologue `ST0` | Photograph shrink/rotation and fire transition after the battle | `st/st0/3AB08.c`, `EntityCutscenePhotograph` |
| [ ] | Entrance `NO3` / `NP3` / `RNO3` | Foliage left repeats repaired and indexed-edge lightning remaps verified; broader outdoor routes and background endpoints remain open | `st/e_background_bushes_trees.h`, `st/e_background_lightning.h` |
| [ ] | Entrance `NO3` / `NP3` / `RNO3` | Full/partial transparent pools checked in all three overlays; NO3 `07` camera sweep/return checked. Other routes, vertical views and entrances/exits remain open | `st/e_transparent_water.h` |
| [ ] | Entrance / reverse entrance | Story camera pans, entrance gates and transition into interior rooms | `st/no3/cutscene.c`, `st/rno3/` |
| [ ] | Caverns `NO4` / `RNO4` | Water/shimmer edge clipping repaired; normal waterfall and both pool views checked. Reverse ceiling-water, ferryman/crate scripts, bubbles and routes remain open | `st/cavern_bg_effects.h`, `st/rno4/e_cavern_bg.c`, `st/water_effects.h` |
| [ ] | Scylla `BO3` | Live lower flood, main encounter/death, natural drain and shaft return checked; Wyrm approach, side gates and lower-room intermediate drainage views remain open | `boss/bo3/water_effects.c`, `boss/bo3/cavern_bg_effects.c` |
| [ ] | Clock Tower `NZ1` / `RNZ1` | Outdoor clouds, gears, foreground water and narrow vertical shafts | `st/nz1/e_bg_gears.c`, `st/nz1/e_water_fg.c` |
| [ ] | Clock Tower `NZ1` | Four-gear secret door: enter/leave through each exit | `st/nz1/e_gear_puzzle.c` |
| [ ] | Keep `TOP` / `RTOP` | Cloud geometry/counter cycle and narrow-room artwork overlap verified in both castles; outside stairs, room approaches and warp travel remain open | `st/e_clouds_keep.h`, `st/top/e_warp_trigger.c` |
| [ ] | Keep `TOP` / `RTOP` | Clock Tower geometry and normal bat approaches to margin-crossing views verified in both castles; full room routes remain open | `st/e_clock_tower.h` |
| [ ] | Keep `TOP` / `RTOP` | Elevator-room doors and approaches; TOP room `06` ride, all four lamp pairs and `06`↔`0A` doorway verified, remaining routes open | `st/top/e_lion_lamp.c`, `st/top/e_elevator.c` |
| [ ] | Chapel `DAI` / `RDAI` | Clouds through windows, stained glass, broken glass and foreground pillars | `st/e_clouds.h`, `st/e_stained_glass.h` |
| [ ] | Richter arena `BO5` | Stained glass, camera framing, dialogue and battle effects | `boss/bo5/e_stained_glass.c`, `boss/bo5/e_clouds.c` |
| [ ] | Catacombs `CAT` / `RCAT` | Cave panels, glow and far bridge margins repaired; RCAT bridge flight/return verified; CAT bridge travel, particles and room transitions remain open | `st/cat/e_lava_glow.c`, `st/cat/e_lava.c`, `st/rcat/e_cavern_background.c` |
| [ ] | Marble Gallery `NO0` / `RNO0` | Clock room doors/statues, room limits and camera locks in long rooms | `st/no0/clock_room.c`, `st/rno0/e_clock_room.c` |
| [ ] | Library `LIB` / `RLIB` | Projected bookcases/shadow widths repaired and both unlock/swivel interactions verified; full passage traversal and remaining room endpoints open | `st/lib/e_library_bg.c` |
| [ ] | Library `LIB` | Librarian interaction and Lesser Demon approach/arena | `st/lib/e_lesser_demon.c`, `st/lib/` |
| [ ] | `NO1` / `RNO1`, `NO2` / `RNO2` | House right cutoff repaired; NO2 boundary and RNO2 lower-courtyard feedback verified; other markers, ledges and endpoints remain open | `st/e_background_house.h`, `st/e_background_sky_land.h` |
| [ ] | Colosseum `ARE` / `RARE` | Fountain, foreground/background separation and arena entrances | `st/are/e_fountain_water.h`, `st/rare/e_background_door_rubble.c` |
| [ ] | Mine `CHI` / `RCHI` | Narrow shafts, walls ending at room boundaries and foreground layers | `st/chi/background_block_init.c`, `st/rchi/` |
| [ ] | Dream `DRE` | House/cloud backdrop, Lisa/Succubus dialogue pans, clones and boss defeat | `st/dre/e_background_clouds.c`, `st/dre/e_cutscene_actors.c` |
| [ ] | Warp rooms `WRP` / `RWRP` | Keep-to-Olrox departure/arrival fades and reverse platform verified in both castles; other destinations and aspect switches remain open | `st/wrp/warp.c`, `st/rwrp/warp.c` |
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
