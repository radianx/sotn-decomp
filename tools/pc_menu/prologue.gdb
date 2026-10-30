# SPDX-License-Identifier: AGPL-3.0-or-later
set pagination off
set confirm off
set debuginfod enabled off
break RunMainEngine if g_Timer >= 100 && g_GameEngineStep == Engine_Normal && g_PauseAllowed && g_PlayerHud.unk24 == 0
commands
silent
set g_pads[0].tapped = PAD_START
set g_pads[0].pressed = PAD_START
disable 1
continue
end
break RunMainEngine if g_GameEngineStep == Engine_0x70
commands
silent
python
assert int(gdb.parse_and_eval('g_StageId')) == int(gdb.parse_and_eval('STAGE_ST0'))
assert int(gdb.parse_and_eval('g_PlayableCharacter')) == 1
assert int(gdb.parse_and_eval('PcMenuIsOpen()')) == 0
print('PROLOGUE_ORIGINAL_PAUSE_PASS')
end
set $x = g_Entities[0].posX.val
set $y = g_Entities[0].posY.val
set $pose = g_Entities[0].animCurFrame
set $pausedAt = g_Timer
call OpenAdventure()
python
assert int(gdb.parse_and_eval('PcMenuIsOpen()')) == 0
end
disable 2
continue
end
break RunMainEngine if g_GameEngineStep == Engine_0x70 && g_Timer >= $pausedAt + 30 && g_PlayerHud.unk24 == 0x15
commands
silent
python
assert int(gdb.parse_and_eval('g_Entities[0].posX.val')) == int(gdb.parse_and_eval('$x'))
assert int(gdb.parse_and_eval('g_Entities[0].posY.val')) == int(gdb.parse_and_eval('$y'))
assert int(gdb.parse_and_eval('g_Entities[0].animCurFrame')) == int(gdb.parse_and_eval('$pose'))
assert int(gdb.parse_and_eval('PcMenuIsOpen()')) == 0
print('PROLOGUE_PAUSED_PLAYER_UNCHANGED_PASS')
end
set g_pads[0].tapped = PAD_START
set g_pads[0].pressed = PAD_START
disable 3
continue
end
break RunMainEngine if g_GameEngineStep == Engine_Normal && $pausedAt > 0
commands
silent
python
assert int(gdb.parse_and_eval('PcMenuIsOpen()')) == 0
assert int(gdb.parse_and_eval('D_800974A4')) == 0
print('PROLOGUE_RESUME_PASS')
end
quit
end
set $pausedAt = -1
run
