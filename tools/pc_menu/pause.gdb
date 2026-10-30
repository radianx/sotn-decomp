# SPDX-License-Identifier: AGPL-3.0-or-later
set pagination off
set confirm off
set debuginfod enabled off
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
break RunMainEngine if g_Timer >= 100 && g_Timer <= 104
commands
silent
if g_Timer == 100
set $fullscreenEvent = (SDL_Event*)calloc(1,sizeof(SDL_Event))
set $fullscreenEvent->type = SDL_EVENT_KEY_DOWN
set $fullscreenEvent->key.scancode = SDL_SCANCODE_RETURN
set $fullscreenEvent->key.mod = 0x0040
call SDL_PushEvent($fullscreenEvent)
set $fullscreenEvent->key.repeat = 1
call SDL_PushEvent($fullscreenEvent)
set $fullscreenEvent->type = SDL_EVENT_KEY_UP
set $fullscreenEvent->key.mod = 0
call SDL_PushEvent($fullscreenEvent)
end
if g_Timer == 102
python
assert int(gdb.parse_and_eval('is_fullscreen')) == 1
assert int(gdb.parse_and_eval('g_GameEngineStep')) == 1
assert int(gdb.parse_and_eval('PcMenuIsOpen()')) == 0
end
set $fullscreenEvent->type = SDL_EVENT_KEY_DOWN
set $fullscreenEvent->key.scancode = SDL_SCANCODE_KP_ENTER
set $fullscreenEvent->key.mod = 0x0080
set $fullscreenEvent->key.repeat = 0
call SDL_PushEvent($fullscreenEvent)
set $fullscreenEvent->type = SDL_EVENT_KEY_UP
set $fullscreenEvent->key.mod = 0
call SDL_PushEvent($fullscreenEvent)
end
if g_Timer == 104
python
assert int(gdb.parse_and_eval('is_fullscreen')) == 0
assert int(gdb.parse_and_eval('g_GameEngineStep')) == 1
print('GAMEPLAY_CTRL_ENTER_FULLSCREEN_PASS')
end
call free($fullscreenEvent)
set g_pads[0].tapped = PAD_START
set g_pads[0].pressed = PAD_START
disable 2
end
continue
end
set $draws = 0
break Psyz_OverlayPresent_SDL3
commands
silent
set $draws = $draws + 1
if $draws == 1
set $pausedTimer = g_Timer
set $event = (SDL_Event*)calloc(1,sizeof(SDL_Event))
set $event->type = SDL_EVENT_KEY_DOWN
set $event->key.windowID = SDL_GetWindowID('upgrades.c'::s_Window)
set $count = (int*)calloc(1,4)
set $windows = SDL_GetWindows($count)
python
assert int(gdb.parse_and_eval('*$count')) == 1
assert int(gdb.parse_and_eval("'upgrades.c'::s_Home")) == 1
assert int(gdb.parse_and_eval('g_GameEngineStep')) == 1
print('MENU_SAME_WINDOW_PASS')
end
call SDL_free($windows)
call free($count)
set $desc = (SDL_VirtualJoystickDesc*)calloc(1,sizeof(SDL_VirtualJoystickDesc))
set $desc->version = sizeof(SDL_VirtualJoystickDesc)
set $desc->type = SDL_JOYSTICK_TYPE_GAMEPAD
set $desc->naxes = SDL_GAMEPAD_AXIS_COUNT
set $desc->nbuttons = SDL_GAMEPAD_BUTTON_COUNT
set $desc->button_mask = (1u << SDL_GAMEPAD_BUTTON_COUNT) - 1
set $desc->axis_mask = (1u << SDL_GAMEPAD_AXIS_COUNT) - 1
set $id = SDL_AttachVirtualJoystick($desc)
set $count = (int*)calloc(1,4)
set $ids = SDL_GetGamepads($count)
python
ids = gdb.parse_and_eval('$ids')
for i in range(int(gdb.parse_and_eval('*$count'))):
    if int(ids[i]) == int(gdb.parse_and_eval('$id')):
        gdb.execute('set g_PcSettings.controller = %d' % i)
        break
else:
    raise AssertionError('Virtual controller was not recognized')
end
call SDL_free($ids)
call free($count)
if 'upgrades.c'::s_Gamepad
call SDL_CloseGamepad('upgrades.c'::s_Gamepad)
set 'upgrades.c'::s_Gamepad = 0
end
call UpdateController()
set $padEvent = (SDL_Event*)calloc(1,sizeof(SDL_Event))
set $padEvent->type = SDL_EVENT_GAMEPAD_BUTTON_DOWN
set $padEvent->gbutton.which = $id
set $padEvent->gbutton.button = SDL_GAMEPAD_BUTTON_DPAD_DOWN
call SDL_PushEvent($padEvent)
set $padEvent->gbutton.button = SDL_GAMEPAD_BUTTON_DPAD_UP
call SDL_PushEvent($padEvent)
set $width = (int*)calloc(1,4)
set $height = (int*)calloc(1,4)
set $before = Psyz_VideoAllocCapturedFrame($width,$height)
set $rawWidth = *$width
set $rawHeight = *$height
set $event->key.scancode = SDL_SCANCODE_RETURN
set $event->key.mod = 0x0040
call SDL_PushEvent($event)
set $event->key.repeat = 1
call SDL_PushEvent($event)
set $event->type = SDL_EVENT_KEY_UP
set $event->key.mod = 0
call SDL_PushEvent($event)
set $event->type = SDL_EVENT_KEY_DOWN
set $event->key.repeat = 0
end
if $draws == 3
set $audioPaused = Psyz_AudioIsPaused()
python
assert int(gdb.parse_and_eval('$audioPaused')) == 1
assert int(gdb.parse_and_eval('g_Timer')) == int(gdb.parse_and_eval('$pausedTimer'))
assert int(gdb.parse_and_eval('is_fullscreen')) == 1
assert int(gdb.parse_and_eval("'upgrades.c'::s_Home")) == 1
print('MENU_CTRL_ENTER_FULLSCREEN_PASS')
print('MENU_PAUSE_PASS')
end
set $event->key.scancode = SDL_SCANCODE_F4
call SDL_PushEvent($event)
set $event->key.scancode = SDL_SCANCODE_F1
call SDL_PushEvent($event)
end
if $draws == 6
python
assert int(gdb.parse_and_eval("'upgrades.c'::s_Home")) == 0
assert int(gdb.parse_and_eval("'upgrades.c'::s_Qol")) == 0
assert int(gdb.parse_and_eval('is_fullscreen')) == 0
print('MENU_FULLSCREEN_ROUNDTRIP_PASS')
print('MENU_SYSTEM_PASS')
end
set $step = 0
while $step < 9
set $padEvent->gbutton.button = SDL_GAMEPAD_BUTTON_DPAD_DOWN
call SDL_PushEvent($padEvent)
set $step = $step + 1
end
set $padEvent->gbutton.button = SDL_GAMEPAD_BUTTON_SOUTH
call SDL_PushEvent($padEvent)
end
if $draws == 9
python
assert int(gdb.parse_and_eval("'upgrades.c'::s_ShowAudio")) == 1
print('MENU_AUDIO_DIAGNOSTICS_PASS')
end
set $padEvent->gbutton.button = SDL_GAMEPAD_BUTTON_EAST
call SDL_PushEvent($padEvent)
set $step = 0
while $step < 8
set $padEvent->gbutton.button = SDL_GAMEPAD_BUTTON_DPAD_UP
call SDL_PushEvent($padEvent)
set $step = $step + 1
end
set $padEvent->gbutton.button = SDL_GAMEPAD_BUTTON_SOUTH
call SDL_PushEvent($padEvent)
set $event->key.scancode = SDL_SCANCODE_F5
call SDL_PushEvent($event)
end
if $draws == 12
python
assert int(gdb.parse_and_eval("'upgrades.c'::s_Qol")) == 1
assert int(gdb.parse_and_eval('g_PcSettings.reduceFlashes')) == 1
print('MENU_VIRTUAL_CONTROLLER_SETTINGS_AND_ADVENTURE_PASS')
end
set $padEvent->gbutton.button = SDL_GAMEPAD_BUTTON_EAST
call SDL_PushEvent($padEvent)
end
if $draws == 15
set $after = Psyz_VideoAllocCapturedFrame($width,$height)
set $unchanged = (int)memcmp($before,$after,$rawWidth*$rawHeight*3)
python
assert int(gdb.parse_and_eval('*$width')) == int(gdb.parse_and_eval('$rawWidth'))
assert int(gdb.parse_and_eval('*$height')) == int(gdb.parse_and_eval('$rawHeight'))
assert int(gdb.parse_and_eval('$unchanged')) == 0
assert int(gdb.parse_and_eval("'upgrades.c'::s_HomeRow")) == 0
print('MENU_RAW_CAPTURE_UNCHANGED_PASS')
end
call free($before)
call free($after)
call free($width)
call free($height)
set $joystick = SDL_GetGamepadJoystick('upgrades.c'::s_Gamepad)
call SDL_SetJoystickVirtualButton($joystick,SDL_GAMEPAD_BUTTON_SOUTH,1)
call SDL_UpdateJoysticks()
set $padEvent->gbutton.button = SDL_GAMEPAD_BUTTON_SOUTH
call SDL_PushEvent($padEvent)
end
if $draws == 18 && g_PlayableCharacter == 1
python
assert int(gdb.parse_and_eval("'upgrades.c'::s_Home")) == 1
print('MENU_RICHTER_CHARACTER_GUARD_PASS')
end
set $padEvent->gbutton.button = SDL_GAMEPAD_BUTTON_EAST
call SDL_PushEvent($padEvent)
end
continue
end
break MenuHandle if g_MenuStep == 16
commands
silent
python
assert int(gdb.parse_and_eval('g_GameEngineStep')) == 2
assert int(gdb.parse_and_eval("'upgrades.c'::s_Open")) == 0
print('MENU_ORIGINAL_CHARACTER_TRANSITION_PASS')
end
set $pad = PadRead(1)
python
assert (int(gdb.parse_and_eval('$pad')) & int(gdb.parse_and_eval('PAD_CROSS'))) == 0
end
call SDL_SetJoystickVirtualButton($joystick,SDL_GAMEPAD_BUTTON_SOUTH,0)
call SDL_UpdateJoysticks()
set g_pads[0].tapped = PAD_START
continue
end
break GameLoopCallback if g_Timer == 180
commands
silent
python
assert int(gdb.parse_and_eval('g_GameEngineStep')) == 1
assert int(gdb.parse_and_eval("'upgrades.c'::s_Open")) == 0
print('MENU_GAMEPLAY_RESUMED_PASS')
end
set $pad = PadRead(1)
python
assert (int(gdb.parse_and_eval('$pad')) & int(gdb.parse_and_eval('PAD_CROSS'))) == 0
print('MENU_ACCEPT_BUTTON_DOES_NOT_LEAK_PASS')
end
call SDL_SetJoystickVirtualButton($joystick,SDL_GAMEPAD_BUTTON_SOUTH,0)
call SDL_UpdateJoysticks()
set $event->key.scancode = SDL_SCANCODE_F6
call SDL_PushEvent($event)
disable 5
continue
end
break GameLoopCallback if g_Timer == 181
commands
silent
python
assert int(gdb.parse_and_eval('debug_show_vram')) == 0
print('MENU_SHORTCUT_EVENT_CONSUMED_PASS')
end
quit 0
end
run
