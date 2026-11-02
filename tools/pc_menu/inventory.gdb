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

def memory(expression):
    address = number('&' + expression)
    length = number('sizeof(' + expression + ')')
    return bytes(gdb.selected_inferior().read_memory(address, length))

def check_weapon_cases():
    cases = [
        ('fire-shield', 'ITEM_FIRE_SHIELD', 'ITEM_ALUCARD_SWORD', 2),
        ('short-sword', 'ITEM_SHORT_SWORD', 'ITEM_LEATHER_SHIELD', 2),
        ('claymore', 'ITEM_CLAYMORE', 'ITEM_CLAYMORE', 2),
        ('sword-of-dawn', 'ITEM_SWORD_OF_DAWN', 'ITEM_SWORD_OF_DAWN', 2),
        ('right-sword', 'ITEM_ALUCARD_SHIELD', 'ITEM_ALUCARD_SWORD', 3),
        ('alucard-sword', 'ITEM_ALUCARD_SWORD', 'ITEM_ALUCARD_SHIELD', 2),
    ]
    for label, left, right, mode in cases:
        run('set $gear = (unsigned int*)calloc(7,4)')
        run('call (void*)memcpy($gear,g_Status.equipment,28)')
        for hand, item in enumerate((left, right)):
            run('set $gear[%d] = %s' % (hand, item))
            run('set g_Status.equipHandCount[%s] = 1' % item)
        assert number('PcQolApplyGear($gear)') == 1, label
        run('call free($gear)')
        run('call PcInventoryPreviewReset()')
        for _ in range(mode):
            run('call PcInventoryPreviewCycle()')
        stable = {name: memory(name) for name in ('g_Status', 'g_Entities', 'g_PrimBuf')}
        for _ in range(5):
            run("set 'inventory.c'::s_LastTick = SDL_GetTicksNS() - 16666667")
            run('call PcInventoryPreviewDraw($renderer,95,345)')
        run("set 'inventory.c'::s_LastTick = 0")
        run('call PcQolUiDraw($renderer)')
        size = number('$surface->pitch * $surface->h')
        address = number('$surface->pixels')
        equipped = bytes(gdb.selected_inferior().read_memory(address, size))
        hand = 1 if mode == 3 else 0
        module = 'D_8017D000' if hand else 'D_8017A000'
        run('set $metadata = %s.preview' % module)
        run('set %s.preview = 0' % module)
        run("set 'weapon_fx.c'::s_Active = 0")
        run("set 'inventory.c'::s_LastTick = 0")
        run('call PcQolUiDraw($renderer)')
        bare = bytes(gdb.selected_inferior().read_memory(address, size))
        run('set %s.preview = $metadata' % module)
        run("set 'weapon_fx.c'::s_Active = 1")
        assert equipped != bare, label + ' is invisible'
        run("set 'inventory.c'::s_LastTick = 0")
        run('call PcQolUiDraw($renderer)')
        run('call SDL_SaveBMP($surface,"@QA@/weapon-%s.bmp")' % label)
        for name, value in stable.items():
            assert memory(name) == value, name + ' changed during ' + label
    print('INVENTORY_WEAPON_FAMILIES_PASS')

def check_inventory(familiar):
    if familiar == 0:
        run('set $surface = SDL_CreateSurface(1200,920,SDL_PIXELFORMAT_RGBA32)')
        run('set $renderer = SDL_CreateSoftwareRenderer($surface)')
        if number('g_PlayableCharacter') == 0:
            run('set $gear = (unsigned int*)calloc(7,4)')
            run('call (void*)memcpy($gear,g_Status.equipment,28)')
            run('set $gear[0] = ITEM_ALUCARD_SWORD')
            run('set $gear[1] = ITEM_ALUCARD_SHIELD')
            run('set g_Status.equipHandCount[ITEM_ALUCARD_SWORD] = 1')
            run('set g_Status.equipHandCount[ITEM_ALUCARD_SHIELD] = 1')
            assert number('PcQolApplyGear($gear)') == 1
            run('call free($gear)')
            run('set g_Status.equipment[CAPE_SLOT] = ITEM_ROYAL_CLOAK')
            run('set g_Status.equipBodyCount[ITEM_ROYAL_CLOAK] = 1')
            run('call UpdateCapePalette()')
            run('call DrawSync(0)')
    run('call PcQolUiOpenPage(1)')
    run("set 'qol_ui.c'::s_Filter = 1")
    before = {name: memory(name) for name in
              ('g_Status', 'g_Entities', 'g_PrimBuf', 'g_Player', 'g_Timer',
               'g_CurrentEntity', 'D_8013AEE4', 'g_EquippedWeaponIds',
               'D_8017A000', 'D_8017D000')}
    run('set $rect = (RECT*)calloc(1,sizeof(RECT))')
    run('set $rect->w = 1024')
    run('set $rect->h = 512')
    run('set $vram = (unsigned short*)calloc(1024*512,2)')
    run('call StoreImage($rect,(unsigned long*)$vram)')
    run('call DrawSync(0)')
    vram = bytes(gdb.selected_inferior().read_memory(number('$vram'), 1024*512*2))
    modes = 6 if number('g_PlayableCharacter') == 0 and familiar == 0 else 1
    poses = set()
    for mode in range(modes):
        for tick in range(60 if modes == 6 else 1):
            run("set 'inventory.c'::s_LastTick = SDL_GetTicksNS() - 16666667")
            run('call PcInventoryPreviewDraw($renderer,95,345)')
            poses.add(number("'inventory.c'::s_Player.animCurFrame"))
            if mode == 2 and tick == 4:
                run("set 'inventory.c'::s_LastTick = 0")
                run('call PcQolUiDraw($renderer)')
                run('call SDL_SaveBMP($surface,"@QA@/equipped-sword.bmp")')
                size = number('$surface->pitch * $surface->h')
                address = number('$surface->pixels')
                equipped = bytes(gdb.selected_inferior().read_memory(address, size))
                run('set $metadata = D_8017A000.preview')
                run('set D_8017A000.preview = 0')
                run("set 'weapon_fx.c'::s_Active = 0")
                run("set 'inventory.c'::s_LastTick = 0")
                run('call PcQolUiDraw($renderer)')
                bare = bytes(gdb.selected_inferior().read_memory(address, size))
                run('set D_8017A000.preview = $metadata')
                run("set 'weapon_fx.c'::s_Active = 1")
                assert equipped != bare, 'Equipped sword is invisible'
                print('INVENTORY_EQUIPPED_WEAPON_PASS')
        run('call PcQolUiDraw($renderer)')
        run('call SDL_SaveBMP($surface,"@QA@/inventory-%d-%d.bmp")' %
            (familiar, mode))
        if modes == 6 and mode in (0, 1, 2):
            # The right-hand shield must be absent while idle, walking,
            # or attacking with the left-hand sword.
            run("set 'inventory.c'::s_LastTick = 0")
            run('call PcQolUiDraw($renderer)')
            size = number('$surface->pitch * $surface->h')
            address = number('$surface->pixels')
            visible = bytes(gdb.selected_inferior().read_memory(address, size))
            run('set $shieldMetadata = D_8017D000.preview')
            run('set D_8017D000.preview = 0')
            run("set 'inventory.c'::s_LastTick = 0")
            run('call PcQolUiDraw($renderer)')
            absent = bytes(gdb.selected_inferior().read_memory(address, size))
            run('set D_8017D000.preview = $shieldMetadata')
            assert visible == absent, 'Shield visible outside its own attack'
        if modes == 6:
            run('call PcInventoryPreviewCycle()')
    if modes == 6:
        assert len(poses) > 8, poses
        print('INVENTORY_ANIMATIONS_PASS')
        print('INVENTORY_SHIELD_VISIBILITY_PASS')
    if familiar:
        run('set g_Servant = 0')
        run("set 'inventory.c'::s_LastTick = 0")
        run('call PcQolUiDraw($renderer)')
        size = number('$surface->pitch * $surface->h')
        address = number('$surface->pixels')
        alone = bytes(gdb.selected_inferior().read_memory(address, size))
        run('set g_Servant = %d' % familiar)
        run("set 'inventory.c'::s_LastTick = 0")
        run('call PcQolUiDraw($renderer)')
        together = bytes(gdb.selected_inferior().read_memory(address, size))
        assert alone != together, 'Familiar %d is invisible' % familiar
        run('call SDL_SaveBMP($surface,"@QA@/inventory-%d-0.bmp")' % familiar)
    for name, value in before.items():
        assert memory(name) == value, name + ' changed during preview'
    run('call StoreImage($rect,(unsigned long*)$vram)')
    run('call DrawSync(0)')
    after = bytes(gdb.selected_inferior().read_memory(number('$vram'), 1024*512*2))
    assert vram == after, 'Preview changed VRAM'
    run('call free($vram)')
    run('call free($rect)')
    print('INVENTORY_STATE_UNCHANGED_PASS familiar=%d' % familiar)
    if familiar == 0 and number('g_PlayableCharacter') == 0:
        check_weapon_cases()
end
set $frame = 100
set $familiar = 0
break RunMainEngine if g_Timer >= $frame
commands
silent
python check_inventory(int(gdb.parse_and_eval('$familiar')))
if g_PlayableCharacter != 0 || $familiar == 7
printf "INVENTORY_PREVIEW_PASS\n"
quit
end
set $familiar = $familiar + 1
call ServantWorkClear()
set g_Servant = $familiar
call HandleServantPrg()
call HandleServantChr()
call g_ServantDesc.Init(MENU_SWITCH_SERVANT)
set g_ServantLoaded = g_Servant
set $frame = g_Timer + 40
continue
end
run
