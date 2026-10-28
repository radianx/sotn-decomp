# Adventure tools

Run `./run-linux.sh`, then press **F5**. This pauses the game, voice, music and
playback clock. The original pause menu, map and Librarian remain available.
Press Tab or controller RB to change pages; F5/Escape or controller B returns.
Controller Back + right-stick click opens the adventure window.

## Map and exploration

- Arrow keys pan the cursor; `+`/`-` zoom; C changes castle; F filters markers.
  Only tiles actually explored in that castle are displayed.
  Controller D-pad pans, triggers zoom, Y filters, left-stick click changes the
  pin icon, and right-stick click changes its requirement. Notes need a keyboard.
- Enter places a pin, K changes its icon, N writes a short ASCII note, and Delete
  removes a pin. There are 64 pins per adventure profile.
- R tags an encountered obstacle with a requirement such as Bat, Mist, double
  jump or Spike Breaker. A green marker suggests revisiting it after obtaining
  the tagged ability/item. It does not reveal hidden passages automatically.
- Discovered save rooms and unlocked warp rooms have their own filters.
- Enable named warp destinations in Options. On the Map page inside a warp
  room, W cycles destinations and Space selects one. Close the window and press
  Up on the platform to run the original teleport sequence. Locked destinations
  cannot be selected. Controller X cycles and LB selects a destination.

## Inventory, equipment and spells

- Inventory: F filters categories, S sorts by name, quantity or attack/defense,
  B shows favorites, and V toggles a favorite. Left/Right selects an equipment
  slot; Enter equips. The comparison shows resulting attack, defense, base-stat
  changes and elemental properties alongside the original item description.
- Loadouts: choose one of three slots, S stores current equipment, and Enter
  equips it. L assigns that loadout to F10; press L again to unassign it.
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

- Overwriting a normal memory-card save first retains its previous contents in
  a three-entry backup ring. The Saves page lists original slots and backups
  with their gameplay thumbnails, save icons, character, area, playtime and
  completion. New saves capture a preview; older saves retain their icon until
  saved again. Enter copies the selected save into an unused slot on memory
  card 2; it never overwrites an existing slot. Load that copy through the normal
  game menu.
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
`.resumed` after loading. Keep these local files with your normal `bu00/` and
`bu10/` saves. Adventure data is separate from the original PS1 save format.
Gameplay thumbnails are separate `settings.ini.<id>.png` files; backup previews
live next to their `.qsave` files. Backups retain the old save and preview;
profile sidecars are separate. Suspend includes the adventure profile.

The PC additions are guarded from console builds. Automated checks cover
persistence corruption, profile isolation, explored-only pins, inventory
ownership, backup/thumbnail preservation, shortcut guards, HUD/subtitle bounds
and all seven window pages. Full gameplay and
physical-controller coverage still require manual testing.
