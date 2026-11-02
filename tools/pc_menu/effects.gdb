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
python
import gdb

def run(command):
    return gdb.execute(command, to_string=True)

def number(expression):
    return int(gdb.parse_and_eval(expression))

def memory(name):
    return bytes(gdb.selected_inferior().read_memory(number('&' + name), number('sizeof(' + name + ')')))

def check_effects():
    run('set $surface = SDL_CreateSurface(1200,920,SDL_PIXELFORMAT_RGBA32)')
    run('set $renderer = SDL_CreateSoftwareRenderer($surface)')
    run('call SDL_SetRenderScale($renderer,2,2)')
    cases = [
        ('runesword', 'ITEM_RUNESWORD', False),
        ('heaven-sword', 'ITEM_HEAVEN_SWORD', False),
        ('chakram', 'ITEM_CHAKRAM', False),
        ('crissaegrim', 'ITEM_CRISSAEGRIM', False),
        ('vorpal-blade', 'ITEM_VORPAL_BLADE', False),
        ('shuriken', 'ITEM_SHURIKEN', False),
        ('boomerang', 'ITEM_BOOMERANG', False),
        ('iron-ball', 'ITEM_IRON_BALL', False),
        ('magic-missile', 'ITEM_MAGIC_MISSILE', False),
        ('fire-shield', 'ITEM_FIRE_SHIELD', False),
        ('fire-shield-spell', 'ITEM_FIRE_SHIELD', True),
        ('alucard-shield-spell', 'ITEM_ALUCARD_SHIELD', True),
        ('iron-shield-spell', 'ITEM_IRON_SHIELD', True),
        ('leather-shield-spell', 'ITEM_LEATHER_SHIELD', True),
        ('alucard-sword-special', 'ITEM_ALUCARD_SWORD', True),
    ]
    names = ('g_Status', 'g_Player', 'g_Entities', 'g_PrimBuf', 'g_Clut', 'g_Timer',
             'g_GameTimer', 'g_api', 'g_EquippedWeaponIds', 'D_8017A000', 'D_8017D000',
             'g_CurrentEntity', 'g_unkGraphicsStruct', "'rand.c'::s_RandomSeed")
    original = {name: memory(name) for name in names}
    run('set $rect = (RECT*)calloc(1,sizeof(RECT))')
    run('set $rect->w = 1024')
    run('set $rect->h = 512')
    run('set $vram = (unsigned short*)calloc(1024*512,2)')
    run('call StoreImage($rect,(unsigned long*)$vram)')
    run('call DrawSync(0)')
    before_vram = bytes(gdb.selected_inferior().read_memory(number('$vram'), 1024*512*2))
    for label, item, special in cases:
        for hand in (0, 1):
            control = [number('Psyz_GteCtrlRead(%d)' % i) for i in range(32)]
            data = [number('Psyz_GteDataRead(%d)' % i) for i in range(32)]
            result = number('PcWeaponFxCheckSequence(%s,%d,%d,360)' % (item, hand, special))
            assert result & 6, label + ' did not produce visual entities/primitives'
            assert control == [number('Psyz_GteCtrlRead(%d)' % i) for i in range(32)], label + ' changed GTE control'
            assert data == [number('Psyz_GteDataRead(%d)' % i) for i in range(32)], label + ' changed GTE data'
            for name, value in original.items():
                assert memory(name) == value, label + ' changed ' + name
            for frame in (8, 80, 160):
                run('call PcWeaponFxCheckSequence(%s,%d,%d,%d)' % (item, hand, special, frame))
                run('call SDL_SetRenderDrawColor($renderer,8,12,32,255)')
                run('call SDL_RenderClear($renderer)')
                run('call DrawWeaponFx($renderer,95,345)')
                run('call SDL_RenderPresent($renderer)')
                run('call SDL_SaveBMP($surface,"@QA@/%s-%d-%d.bmp")' % (label, hand, frame))
            print('EFFECT_SEQUENCE_PASS %s hand=%d result=%d' % (label, hand, result), flush=True)
    run('call PcWeaponFxStop()')
    run('call StoreImage($rect,(unsigned long*)$vram)')
    run('call DrawSync(0)')
    after_vram = bytes(gdb.selected_inferior().read_memory(number('$vram'), 1024*512*2))
    assert before_vram == after_vram, 'Effect preview wrote to live VRAM'
    for name, value in original.items():
        assert memory(name) == value, 'Capture changed ' + name
    run('call free($vram)')
    run('call free($rect)')
    print('EFFECTS_GAME_STATE_VRAM_RNG_GTE_UNCHANGED_PASS', flush=True)
end
break RunMainEngine if g_Timer == 100
commands
silent
python check_effects()
set $gear = (unsigned int*)calloc(7,4)
call (void*)memcpy($gear,g_Status.equipment,28)
set $gear[0] = ITEM_FIRE_SHIELD
set $gear[1] = ITEM_SHIELD_ROD
set g_Status.equipHandCount[ITEM_FIRE_SHIELD] = 1
set g_Status.equipHandCount[ITEM_SHIELD_ROD] = 1
set $equipped = PcQolApplyGear($gear)
python
assert int(gdb.parse_and_eval('$equipped')) == 1
end
call free($gear)
set g_Status.mpMax = 100
set g_Status.mp = 100
set $guard = 0
set $spell = 0
set $lastFrame = -1
set $changes = 0
disable 2
continue
end
break RunMainEngine if g_Timer >= 101
commands
silent
set g_pads[0].pressed = PAD_SQUARE
set g_pads[0].tapped = 0
if g_Timer == 101
set g_pads[0].tapped = PAD_SQUARE
end
if g_Timer >= 190 && g_Timer < 200
set g_pads[0].pressed = 0
end
if g_Timer == 200
printf "Casting shield spell: MP=%d combo=%u demo=%u maskL=%u maskR=%u\n", g_Status.mp, D_8013AEE4, g_Player.demo_timer, g_Settings.buttonMask[0], g_Settings.buttonMask[1]
set g_pads[0].pressed = PAD_SQUARE | PAD_CIRCLE
set g_pads[0].tapped = PAD_SQUARE | PAD_CIRCLE
end
set $entity = 8
while $entity < 64
if g_Entities[$entity].entityId && g_Entities[$entity].pfnUpdate == D_8017A000.EntityWeaponAttack
set $guard = 1
if g_Entities[$entity].animCurFrame != $lastFrame
set $changes = $changes + 1
set $lastFrame = g_Entities[$entity].animCurFrame
end
end
if g_Entities[$entity].entityId && g_Entities[$entity].pfnUpdate == D_8017A000.EntityWeaponShieldSpell
set $spell = 1
end
set $entity = $entity + 1
end
if g_Timer >= 600
python
print('Live shield: guard=%s changes=%s spell=%s playerStep=%s pads=%s' % tuple(str(gdb.parse_and_eval(e)) for e in ('$guard', '$changes', '$spell', 'g_Entities[0].step', 'g_Player.padPressed')), flush=True)
assert int(gdb.parse_and_eval('$guard')) == 1, 'Fire shield guard never spawned'
assert int(gdb.parse_and_eval('$changes')) > 2, 'Fire shield guard did not animate'
assert int(gdb.parse_and_eval('$spell')) == 1, 'Fire shield spell never spawned'
print('LIVE_FIRE_SHIELD_GUARD_AND_SPELL_PASS')
end
quit
end
continue
end
run
