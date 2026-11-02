# Adventure tools

Press **Start** (Return by default) to open the pause menu in the game window.
During Richter's opening prologue, Start uses the original PS1 pause without
a menu. Adventure pages unlock after the prologue; F1 PC settings remain available.
Character opens the original equipment, relic, familiar, cloak and system menus.
The other entries open Map, Inventory, Loadouts, Spells, Saves, Dialogue,
Gameplay options or PC settings. Actions retain their normal state restrictions.
Richter can use the PC pages as well.
PC menu panels use a dark blue Gouraud gradient inspired by the original PS1
menus; title artwork, borders, font and music retain their existing behavior.

**F1** and **F5** remain direct shortcuts to settings and adventure tools.
During gameplay, pages pause the game, voice, music and playback clock.
At the title, the original background, Gothic font, highlights and music remain;
the four visible choices scroll as you move through the list. Title submenus
keep the original loop and music running, and reuse the game background/font.
D-pad/arrows select; A/Enter confirms; B/Escape goes back; Start resumes. Tab/RB changes adventure
pages. Back + right-stick click opens the pause menu. F3 is unchanged.

## Map and exploration

- Arrow keys pan the cursor; `+`/`-` zoom; C changes castle; F filters markers.
  Only tiles actually explored in that castle are displayed.
  Controller D-pad pans, triggers zoom, Y filters, left-stick click changes the
  pin icon, and right-stick click changes its requirement. Back changes castle.
  Notes need a keyboard.
- Enter places a pin, K changes its icon, N writes a short ASCII note, and Delete
  removes a pin. There are 64 pins per adventure profile.
- R tags an encountered obstacle with a requirement such as Bat, Mist, double
  jump or Spike Breaker. A green marker suggests revisiting it after obtaining
  the tagged ability/item. It does not reveal hidden passages automatically.
- Discovered save rooms and unlocked warp rooms have their own filters.
- Enable named warp destinations in Options. On the Map page inside a warp
  room, W cycles destinations and Space selects one. Close the menu and press
  Up on the platform to run the original teleport sequence. Locked destinations
  cannot be selected. Controller X cycles and LB selects a destination.

## Inventory, equipment and spells

- Inventory: F filters categories, S sorts by name, quantity or attack/defense,
  B (controller Back) shows favorites, and V toggles a favorite. Left/Right selects an equipment
  slot; Enter equips, or removes the selected item if already in that slot.
  HP, MP, hearts, level, experience, gold, status, rooms, kills and time remain
  visible. Current attack, defense, STR/CON/INT/LCK (base plus equipment) and
  elemental properties are always shown, even with no matching items or an
  incompatible selection. Compatible choices show the resulting values before
  equipping or removing anything, alongside the original item description.
  The equipment panel places the seven original slots around a body outline,
  using the original item icons. There is no separate boot slot in SotN.
  Below it, Alucard uses his original sprites and equipped cape palette, with
  the active familiar beside him. A / controller RT cycles idle, walk, left/right
  attacks and left/right specials. A special shows the weapon's special move,
  or its Shield Rod spell when a shield is equipped; `No special` means that
  item has none. Shields appear on Alucard only during that hand's attack or
  its shield spell. Fire shield uses its original animated frames and color cycle.
  Projectiles, trails and shield magic run the original weapon code in a private
  preview world with separate entities, polygons, palettes and RNG. No live
  items, MP, audio, enemies or VRAM are changed. Large effects scale to fit the
  preview. Richter retains his current appearance.
- Loadouts: choose one of three slots, S stores current equipment, and Enter
  equips it. L (controller Back) assigns that loadout to F10; press L again to unassign it.
  Missing items reject the whole change; two-handed weapons and duplicate
  accessories retain normal counts.
  Changes require idle Alucard and reload the native weapon code and palettes.
- Enable consumable shortcuts, select a medicine in Inventory and press I to
  assign F6, or U to use it once. Its normal effect and item count apply.
  Library cards, Life Apples and Hammers are excluded. Equipment stays in place.
- Spells lists learned spells, their original inputs and MP costs. S assigns F7;
  Enter casts after closing. Enable spell shortcuts first. Normal form, familiar,
  animation and MP requirements still apply. P toggles a practice input-history
  HUD; it does not grant spells or free MP.
  The HUD uses U/R/D/L for directions, A/B for Square/Circle, and J for Jump.
- Subweapon protection is optional: hold Down while touching a pickup to replace
  your current subweapon. Matching pickups and an empty slot retain normal behavior.

## Saves and dialogue

- The title menu offers **Continue**, **Load game**, **New game**, **Manage
  saves**, settings and suspend/resume. Continue uses the newest valid normal
  slot; backups are selected explicitly. Normal saving still requires save rooms.
- PC slots live in `saves/*.sav`, with no memory-card/block limit. A native slot
  bundles the original game data and its adventure profile snapshot. Overwriting
  retains the previous slot/profile in a three-entry backup ring. Thumbnails and
  original icons appear with character, area, playtime and completion.
- Load imports legacy `bu00/` / `bu10/` files and old backups into new native
  slots before playing; originals are unchanged. Enter/A in Manage saves copies
  to a new slot with an independent profile. F/Y requests archival; Enter confirms.
  Archived files end in `.sav.archived`; remove `.archived` to recover them.
  An active adventure cannot be archived during play. N/R3 at the title opens
  the original name grid to rename a slot. Renaming a legacy save imports it.
- New game retains the original eight-character name grid, punctuation and
  space padding. Blank names become Alucard. Richter and Axe Armor still require
  a prior clear; Luck mode still uses `x-x!v''q`. The original initialization
  performs these checks. Renaming an existing save does not activate a new mode.
- S on Saves suspends and quits. R resumes the separate suspend file, including
  the saved position, equipment, progression, map, timers and adventure profile.
  Suspension requires a quiet, idle room without pending player effects; bosses,
  scripted rooms, warp rooms, transformations and status ailments are excluded.
  Room actors reload on resume. This is not an emulator save state.
- The Dialogue page reviews recent spoken text. Options can add larger subtitles
  and automatically skip scenes recorded as watched by this adventure profile.
  Original scene-skip eligibility still applies. Pausing does not advance
  dialogue or voice playback. Recent dialogue history lasts for this session.

## Readability and storage

Options independently enable the gameplay shortcuts, subweapon protection,
named warps, watched-scene skipping, numerical HP/MP/status and larger subtitles.
HUD scale is 100%, 125% or 150%. Gameplay-changing options default to off.
Reset QoL gameplay options restores those defaults without changing widescreen,
audio, input bindings or palette assistance.

With the default configuration, profiles live beside
`build/local-pc/settings.ini` as `settings.ini.<id>.qol`. Backups live in
`settings.ini.backups/`; suspend uses `settings.ini.suspend` and is retired to
`.resumed` after loading. Keep these local files together with `saves/` and
any legacy `bu00/` / `bu10/` files. Native `.sav` files use a checksummed PC
container; the legacy PS1 files remain readable for import.
Gameplay thumbnails are separate `settings.ini.<id>.png` files; backup previews
live next to their `.qsave` files. Backups retain the old save and preview;
legacy backup profile sidecars remain readable. Native slots, their backups
and suspend files embed an adventure profile snapshot; live sidecars preserve
changes made since the last normal save.

The PC additions are guarded from console builds. Automated checks cover
persistence corruption, profile isolation, explored-only pins, inventory
ownership, backup/thumbnail preservation, shortcut guards, HUD/subtitle bounds
and all seven in-game pages. Full gameplay and
physical-controller coverage still require manual testing.

For live Linux menu, virtual-controller and save-room checks with your local
disc and a debug build, run `python3 tools/pc_menu_smoke.py`. It uses GDB, ImageMagick, dummy
audio, and fresh directories under `build/`; real saves are not used. Logs stay
there for inspection. `--binary /path/to/sotn --only pause` can check another
renderer build. These checks do not assess speaker output or physical gamepads.
`--only inventory` checks Alucard's animations and all seven visible familiars,
Richter, and unchanged player/equipment/entity/VRAM state during the preview.
It also verifies that shields stay hidden during idle, walking and attacks
with the other hand, and saves inventory captures in its isolated output directory.
`--only effects` exercises projectile families and shield spells in both hands,
including full 360-frame sequences. It checks live entities, gear, palettes,
VRAM, RNG and GTE registers, and also raises Fire shield and casts its spell
in a separate running test game. Captures and logs stay under `build/`.
These previews use an empty virtual room; enemy-hit reactions are not tested.
