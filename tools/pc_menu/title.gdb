# SPDX-License-Identifier: AGPL-3.0-or-later
set pagination off
set confirm off
set debuginfod enabled off
set breakpoint pending on
break MainGame
commands
silent
call (int)chdir("@QA@")
call Psyz_VideoSetVsyncMode(3)
continue
end
break GameLoopCallback if g_Timer == 100
commands
silent
call DestroyEntitiesFromIndex(0)
call DestroyAllPrimitives()
call ResetPendingGfxLoad()
call func_800EDAE4()
call func_800EA538(0)
call func_800EAD7C()
call HideAllBackgroundLayers()
call SetGameState(Game_MainMenu)
disable 2
continue
end
set $ticks = 0
break PcMenuTitle
commands
silent
set $ticks = $ticks + 1
if $ticks == 1
set $start = g_Timer
end
if $ticks == 90
python
assert int(gdb.parse_and_eval('g_Timer')) > int(gdb.parse_and_eval('$start')) + 80
assert int(gdb.parse_and_eval("'upgrades.c'::s_Open")) == 0
print('NATIVE_TITLE_RUNNING_PASS')
end
set $paused = Psyz_AudioIsPaused()
python
assert int(gdb.parse_and_eval('$paused')) == 0
end
call Psyz_AudioLock()
set $samples = (short*)calloc(4096,2)
call Psyz_SpuPullSamples($samples,2048)
call Psyz_AudioUnlock()
python
import struct
samples=struct.unpack('<4096h',gdb.selected_inferior().read_memory(int(gdb.parse_and_eval('$samples')),8192))
assert int(gdb.parse_and_eval('g_PlayingXaBgmId')) == 0x32
print('TITLE_MUSIC_PCM_PEAK',max(map(abs,samples)))
assert max(map(abs,samples)) > 100
print('TITLE_MUSIC_NONZERO_PASS')
end
call free($samples)
end
if $ticks >= 91 && $ticks <= 96
set g_pads[0].repeat = PAD_DOWN
end
if $ticks == 101
python
assert int(gdb.parse_and_eval("'upgrades.c'::s_HomeRow")) == 6
print('TITLE_SCROLL_LAST_ITEM_PASS')
end
set g_pads[0].repeat = PAD_UP
end
if $ticks == 103
set g_pads[0].repeat = PAD_UP
end
if $ticks == 104
set g_pads[0].tapped = PAD_CROSS
end
if $ticks >= 109 && $draws >= 3
python
assert int(gdb.parse_and_eval("'upgrades.c'::s_Open")) == 0
print('TITLE_RETURNS_TO_ORIGINAL_MENU_PASS')
end
quit 0
end
continue
end
set $draws = 0
break Psyz_OverlayPresent_SDL3
commands
silent
set $draws = $draws + 1
if $draws == 1
set $childStart = g_Timer
end
if $draws == 3
set $paused = Psyz_AudioIsPaused()
python
assert int(gdb.parse_and_eval('$paused')) == 0
assert int(gdb.parse_and_eval('g_Timer')) >= int(gdb.parse_and_eval('$childStart')) + 2
assert int(gdb.parse_and_eval("'upgrades.c'::s_Backdrop")) != 0
assert int(gdb.parse_and_eval("'upgrades.c'::s_Font")) != 0
print('TITLE_CHILD_MUSIC_NOT_PAUSED_PASS')
end
set $event = (SDL_Event*)calloc(1,sizeof(SDL_Event))
set $event->type = SDL_EVENT_KEY_DOWN
set $event->key.windowID = SDL_GetWindowID('upgrades.c'::s_Window)
set $event->key.scancode = SDL_SCANCODE_ESCAPE
call SDL_PushEvent($event)
end
continue
end
run
