# SPDX-License-Identifier: AGPL-3.0-or-later
set pagination off
set confirm off
set debuginfod enabled off
set breakpoint pending on
break SpawnPoint_StageForName
commands
silent
set 'spawn_point.c'::s_SpawnPoints[0].stageId = 2
set 'spawn_point.c'::s_SpawnPoints[0].roomIndex = 14
set 'spawn_point.c'::s_SpawnPoints[0].x = 128
set 'spawn_point.c'::s_SpawnPoints[0].y = 128
disable 1
continue
end
break MainGame
commands
silent
call (int)chdir("@QA@")
call Psyz_VideoSetVsyncMode(3)
disable 2
continue
end
break func_8010E334 if g_Timer == 100
commands
silent
set g_Entities[0].step_s = 1
disable 3
continue
end
set $commits = 0
set $retry = 0
set $prompts = 0
break HandleSaveMenu if arg0 == 3
commands
silent
set $prompts = $prompts + 1
if $prompts == 20
if $retry == 0
set '62DEC.c'::D_80137E6C = 1
end
set g_pads[0].tapped = PAD_CROSS
end
continue
end
break PcSaveCommit
commands
silent
set $commits = $commits + 1
printf "SAVE_ROOM_WRITER_REACHED\n"
continue
end
break func_8010E334 if g_Timer > 200 && $retry == 0
commands
silent
set g_Entities[0].step_s = 1
python
assert int(gdb.parse_and_eval('$commits')) == 0
print('NATIVE_DECLINED_SAVE_DID_NOT_WRITE_PASS')
end
set $retry = 1
set $prompts = 0
disable 6
continue
end
break GameLoopCallback if g_Timer > 1000 && $retry == 1 && $commits == 1 && g_PauseAllowed
commands
silent
python
assert int(gdb.parse_and_eval('$commits')) == 1
assert int(gdb.parse_and_eval('$retry')) == 1
assert int(gdb.parse_and_eval('$prompts')) == 20
print('NATIVE_CONFIRMED_SAVE_WRITES_ONCE_PASS')
import os
assert gdb.parse_and_eval("'qol_save.c'::s_CurrentSave[0]") != 0
assert len([x for x in os.listdir('@QA@/saves') if x.endswith('.sav')]) == 1
print('NATIVE_SAVE_ROOM_PASS')
end
call DestroyEntitiesFromIndex(0)
call DestroyAllPrimitives()
call ResetPendingGfxLoad()
call func_800EDAE4()
call func_800EA538(0)
call func_800EAD7C()
call HideAllBackgroundLayers()
call SetGameState(Game_MainMenu)
disable 7
continue
end
set $phase = 0
set $draws = 0
set $titleTicks = 0
break PcMenuTitle
commands
silent
if !'upgrades.c'::s_Open
set $titleTicks = $titleTicks + 1
if $titleTicks == 1
set $titleStart = g_Timer
end
if $titleTicks == 25
set $paused = Psyz_AudioIsPaused()
python
assert int(gdb.parse_and_eval('g_Timer')) >= int(gdb.parse_and_eval('$titleStart')) + 24
assert int(gdb.parse_and_eval("'upgrades.c'::s_Open")) == 0
assert int(gdb.parse_and_eval('$paused')) == 0
print('NATIVE_TITLE_MENU_PASS')
end
end
if $titleTicks == 26
set g_pads[0].repeat = PAD_DOWN
end
if $titleTicks == 27
set g_pads[0].tapped = PAD_CROSS
end
if $phase == 1 && $titleTicks >= 30 && $titleTicks <= 32
set g_pads[0].repeat = PAD_DOWN
end
if $phase == 1 && $titleTicks == 33
set g_pads[0].tapped = PAD_CROSS
end
if $phase == 2 && $titleTicks == 36
python
assert int(gdb.parse_and_eval("'upgrades.c'::s_Title")) == 1
print('NATIVE_RENAME_ORIGINAL_NAME_GRID_PASS')
end
end
if $phase == 2 && $titleTicks >= 36 && $titleTicks <= 37
set g_pads[0].repeat = PAD_DOWN
end
if $phase == 2 && $titleTicks == 38
set g_pads[0].tapped = PAD_CROSS
end
end
continue
end
break Psyz_OverlayPresent_SDL3
commands
silent
set $draws = $draws + 1
if $draws == 3
python
assert int(gdb.parse_and_eval("'qol_ui.c'::s_Page")) == 4
assert int(gdb.parse_and_eval("'qol_ui.c'::s_LoadMode")) == 1
assert int(gdb.parse_and_eval("'qol_ui.c'::s_SaveCount")) == 1
print('NATIVE_LOAD_BROWSER_PASS')
end
set $event = (SDL_Event*)calloc(1,sizeof(SDL_Event))
set $event->type = SDL_EVENT_KEY_DOWN
set $event->key.windowID = SDL_GetWindowID('upgrades.c'::s_Window)
set $event->key.scancode = SDL_SCANCODE_RETURN
call SDL_PushEvent($event)
end
if $draws == 6 && $phase == 1
set $event->key.scancode = SDL_SCANCODE_N
call SDL_PushEvent($event)
end
continue
end
break GameLoopCallback if $draws >= 3 && $phase == 0 && g_StageId == 2 && g_GameEngineStep == 1
commands
silent
python
assert int(gdb.parse_and_eval('D_8003C730')) in (0,1)
assert int(gdb.parse_and_eval("'upgrades.c'::s_Title")) == 0
assert int(gdb.parse_and_eval("'qol_save.c'::s_CurrentSave[0]")) != 0
print('NATIVE_TITLE_LOAD_GAMEPLAY_PASS')
end
set $phase = 1
call DestroyEntitiesFromIndex(0)
call DestroyAllPrimitives()
call ResetPendingGfxLoad()
call func_800EDAE4()
call func_800EA538(0)
call func_800EAD7C()
call HideAllBackgroundLayers()
call SetGameState(Game_MainMenu)
disable 10
continue
end
break UpdateNameEntry if g_GameEngineStep == 0x400 || g_GameEngineStep == 17
commands
silent
python
gdb.selected_inferior().write_memory(int(gdb.parse_and_eval('&g_InputSaveName')), b"x-x!v''q\0")
end
set g_pads[0].tapped = PAD_START
if g_GameEngineStep == 0x400
set $phase = 2
else
set $phase = 3
end
continue
end
break PcQolNewGame if $phase == 3
commands
silent
python
assert gdb.parse_and_eval('g_Status.saveName').string() == "x-x!v''q"
assert int(gdb.parse_and_eval('g_PlayableCharacter')) == 0
print('NATIVE_NEW_GAME_ORIGINAL_NAME_GRID_PASS')
end
quit 0
end
run
