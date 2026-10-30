// SPDX-License-Identifier: AGPL-3.0-or-later
#ifdef NDEBUG
#undef NDEBUG
#endif
#include "qol.h"
#include "saves.h"
#include "menu.h"
#include "inventory.h"
#include "../dra/dra.h"
#include <assert.h>
#include <string.h>
#ifdef _WIN32
#include <direct.h>
#define chdir _chdir
#else
#include <unistd.h>
#endif

static SDL_EnumerationResult RemoveEntry(
    void* data, const char* dir, const char* name) {
    (void)data;
    char path[1200];
    snprintf(path, sizeof(path), "%s%s", dir, name);
    SDL_RemovePath(path);
    return SDL_ENUM_CONTINUE;
}

void PcQolTest(void) {
    PlayerStatus status = g_Status;
    PcSettings settings = g_PcSettings;
    PcQolData profile = g_PcQol;
    char* previous = SDL_GetCurrentDirectory();
    char directory[128];
    snprintf(directory, sizeof(directory), "build/pc-qol-test-%llu",
             (unsigned long long)SDL_GetTicksNS());
    assert(SDL_CreateDirectory(directory) && chdir(directory) == 0);
    const char* oldPath = g_PcSettingsPath;
    g_PcSettingsPath = "settings.ini";
    PcQolSelectSave("test-profile", false);
    memset(&g_PcQol, 0, sizeof(g_PcQol));
    memset(g_CastleMap, 0, sizeof(g_CastleMap));
    assert(!PcQolVisited(0, -1, 0) && !PcQolVisited(2, 0, 0));
    g_CastleMap[0] = 0x80;
    assert(!PcQolVisited(0, 0, 0)); // Purchased map is not an explored room.
    assert(PcQolSetPin(0, 0, 0, 0, 1, "blocked") < 0);
    g_CastleMap[0] = 0x40;
    assert(PcQolVisited(0, 0, 0) && !PcQolVisited(1, 0, 0));
    int pin = PcQolSetPin(0, 0, 0, 2, 1, "Bat ledge");
    assert(pin >= 0);
    g_Status.relics[RELIC_SOUL_OF_BAT] = 0;
    assert(!PcQolPinReady(&g_PcQol.pins[pin]));
    g_Status.relics[RELIC_SOUL_OF_BAT] = RELIC_FLAG_FOUND;
    assert(PcQolPinReady(&g_PcQol.pins[pin]));
    assert(PcQolSave());
    PcQolData loaded;
    char profilePath[128];
    // A separate small record verifies corrupt-file rejection without mutation.
    u32 value = 42, result = 7;
    assert(PcQolWrite("roundtrip", &value, sizeof(value)));
    assert(PcQolRead("roundtrip", &result, sizeof(result)) && result == 42);
    FILE* file = fopen("roundtrip", "r+b");
    assert(file);
    assert(fseek(file, 12, SEEK_SET) == 0);
    fputc(0, file);
    fclose(file);
    result = 7;
    assert(!PcQolRead("roundtrip", &result, sizeof(result)) && result == 7);
    file = fopen("roundtrip", "wb");
    assert(file);
    fclose(file);
    assert(!PcQolRead("roundtrip", &result, sizeof(result)) && result == 7);

    memset(&g_Status, 0, sizeof(g_Status));
    g_Status.hp = g_Status.hpMax = 100;
    g_Status.mp = g_Status.mpMax = 20;
    u32 empty[7] = {0,
                    0,
                    ITEM_EMPTY_HEAD,
                    ITEM_NO_ARMOR,
                    ITEM_NO_CAPE,
                    ITEM_NO_ACCESSORY,
                    ITEM_NO_ACCESSORY};
    memcpy(g_Status.equipment, empty, sizeof(empty));
    g_StageId = STAGE_LIB;
    g_PlayableCharacter = PLAYER_ALUCARD;
    PLAYER.step = Player_Stand;
    g_Player.status = 0;
    g_Player.unk46 = 0;
    g_Player.grabState = 0;
    g_Status.equipHandCount[ITEM_SHORT_SWORD] = 1;
    u32 gear[7];
    memcpy(gear, empty, sizeof(gear));
    gear[0] = gear[1] = ITEM_SHORT_SWORD;
    PlayerStatus before = g_Status;
    assert(
        !PcQolEquip(gear, true) && !memcmp(&before, &g_Status, sizeof(before)));
    g_Status.equipHandCount[ITEM_CLAYMORE] = 1;
    gear[0] = gear[1] = ITEM_CLAYMORE;
    assert(g_EquipDefs[ITEM_CLAYMORE].itemCategory == ITEM_TWOHAND);
    assert(PcQolEquip(gear, true) && PcQolOwned(false, ITEM_CLAYMORE) == 1 &&
           !g_Status.equipHandCount[ITEM_CLAYMORE]);
    assert(
        PcQolEquip(empty, true) && g_Status.equipHandCount[ITEM_CLAYMORE] == 1);
    g_Status.equipBodyCount[ITEM_GAUNTLET] = 1;
    memcpy(gear, empty, sizeof(gear));
    gear[5] = gear[6] = ITEM_GAUNTLET;
    before = g_Status;
    assert(
        !PcQolEquip(gear, true) && !memcmp(&before, &g_Status, sizeof(before)));
    g_Status.equipBodyCount[ITEM_GAUNTLET] = 2;
    assert(PcQolEquip(gear, true) && PcQolOwned(true, ITEM_GAUNTLET) == 2);
    gear[2] = NUM_BODY_ITEMS;
    assert(!PcQolEquip(gear, false));
    int items[NUM_HAND_ITEMS + NUM_BODY_ITEMS];
    char name[80];
    PcQolItemText(ITEM_POTION, false, name, sizeof(name));
    assert(!strcmp(name, "Potion"));
    PcQolItemText(ITEM_SHORT_SWORD, false, name, sizeof(name));
    assert(!strcmp(name, "Short sword"));
    PcQolItemText(ITEM_ALUCARD_SWORD, false, name, sizeof(name));
    assert(!strcmp(name, "Alucard sword"));
    g_PcQol.favorites[ITEM_CLAYMORE] = 1;
    int count = PcQolInventory(0, 0, true, items);
    assert(count == 1 && items[0] == ITEM_CLAYMORE);
    assert(PcQolInventory(7, 1, false, items) == 2 &&
           items[0] == NUM_HAND_ITEMS + ITEM_GAUNTLET);
    assert(items[1] == NUM_HAND_ITEMS + ITEM_NO_ACCESSORY);
    assert(PcQolInventory(2, 2, true, items) == 0);

    g_PcSettings.protectSubweapon = 1;
    g_Status.subWeapon = SUBWPN_AXE;
    g_pads[0].pressed = 0;
    assert(!PcQolAllowSubweapon(SUBWPN_DAGGER));
    assert(PcQolAllowSubweapon(SUBWPN_AXE));
    g_pads[0].pressed = PAD_DOWN;
    assert(PcQolAllowSubweapon(SUBWPN_DAGGER));
    g_PcSettings.protectSubweapon = 0;
    g_pads[0].pressed = 0;
    assert(PcQolAllowSubweapon(SUBWPN_DAGGER));
    g_GameState = Game_Play;
    g_GameStep = Play_Default;
    g_GameEngineStep = Engine_Normal;
    g_PauseAllowed = 1;
    g_CutsceneHasControl = 0;
    g_DemoMode = Demo_None;
    g_IsUsingCd = 0;
    D_80097C98 = 0;
    g_StageId = STAGE_WRP;
    PLAYER.posX.i.hi = 128;
    g_CastleFlags[WRP_UNLOCKS] = (1 << 1) | (1 << 3);
    g_PcSettings.warpChooser = 1;
    PcQolWarpOffer(3);
    assert(!PcQolWarpChoose(2) && PcQolWarpChoose(1));
    assert(PcQolWarpDestination(3) == 1 && PcQolWarpDestination(3) == -1);
    g_PcSettings.warpChooser = 0;
    assert(!PcQolWarpChoose(1));
    g_PcSettings.spellShortcuts = 0;
    assert(!PcQolCast(SPELL_HELLFIRE));
    g_PcSettings.spellShortcuts = 1;
    g_Status.spellsLearnt = 0;
    assert(!PcQolCast(SPELL_HELLFIRE));
    assert(!PcQolUseItem(ITEM_POTION));
    g_PcSettings.quickItems = 1;
    g_Status.equipHandCount[ITEM_POTION] = 2;
    g_CurrentEntity = &PLAYER;
    Entity factories[8];
    memcpy(factories, &g_Entities[8], sizeof(factories));
    memset(&g_Entities[8], 0, sizeof(factories));
    assert(PcQolUseItem(ITEM_POTION));
    PcQolBeforePlayer();
    assert(g_Entities[8].entityId == E_FACTORY);
    assert(g_Entities[8].ext.factory.paramsBase == 0x1000);
    assert(g_Status.equipHandCount[ITEM_POTION] == 1);
    memcpy(&g_Entities[8], factories, sizeof(factories));
    g_PcSettings.skipSeenDialogue = 1;
    assert(!PcQolSceneBegin(24));
    PcQolSceneEnd(24);
    assert(PcQolSceneBegin(24));
    assert(!PcQolSceneBegin(25));
    PcQolDialogueChar('H');
    PcQolDialogueChar('i');
    assert(!strcmp(PcQolDialogueLine(23), "Hi"));
    PcQolData beforeNewGame = g_PcQol;
    PcQolNewGame();
    assert(!g_PcQol.pins[pin].used && g_PcQol.quickSpell == -1 &&
           g_PcQol.loadout == -1 && !*PcQolDialogueLine(23) &&
           !PcQolSkipWatched());
    PcQolSelectSave("test-profile", true);
    assert(!memcmp(&g_PcQol, &beforeNewGame, sizeof(g_PcQol)));

    assert(SDL_CreateDirectory("bu00"));
    union {
        SaveData save;
        u8 raw[8192];
    } block = {0};
    block.save.info.saveSize = sizeof(SaveData);
    block.save.info.stage = STAGE_LIB;
    block.save.info.character = PLAYER_ALUCARD;
    block.save.status = g_Status;
    file = fopen("bu00/test", "wb");
    assert(file);
    assert(fwrite(block.raw, sizeof(block.raw), 1, file) == 1);
    fclose(file);
    PcQolSelectSave("bu00:test", false);
    char previewPath[128];
    snprintf(previewPath, sizeof(previewPath), "settings.ini.%08x.png",
             PcQolProfileId());
    SDL_Surface* preview = SDL_CreateSurface(192, 108, SDL_PIXELFORMAT_RGB24);
    assert(preview && SDL_ClearSurface(preview, 0, 1, 0, 1) &&
           SDL_SavePNG(preview, previewPath));
    SDL_DestroySurface(preview);
    assert(PcQolBackup("bu00:test"));
    PcSaveEntry entries[8];
    assert(PcQolSaveList(entries, 8) == 1);
    preview = PcQolLoadPreview(entries);
    assert(preview && preview->w == 192 && preview->h == 108);
    Uint8 red, green, blue, alpha;
    assert(SDL_ReadSurfacePixel(preview, 0, 0, &red, &green, &blue, &alpha));
    assert(!red && green == 255 && !blue);
    SDL_DestroySurface(preview);
    unsigned sourceProfile = PcQolProfileId();
    assert(PcQolRestore(entries));
    assert(PcQolSaveList(entries, 8) == 2);
    preview = PcQolLoadPreview(entries);
    assert(preview &&
           SDL_ReadSurfacePixel(preview, 0, 0, &red, &green, &blue, &alpha));
    assert(!red && green == 255 && !blue);
    SDL_DestroySurface(preview);
    assert(!PcQolRead(entries[0].path, &loaded, sizeof(loaded)));
    file = fopen("bu00/test", "rb");
    assert(file);
    u8 unchanged[8192];
    assert(fread(unchanged, sizeof(unchanged), 1, file) == 1);
    fclose(file);
    assert(!memcmp(unchanged, block.raw, sizeof(unchanged)));
    // Native slots preserve the original game data and independent QoL
    // snapshots.
    assert(!strncmp(entries[0].path, "saves/", 6));
    PcSaveEntry native = entries[0];
    PcQolData expectedProfile = g_PcQol;
    assert(!PcSaveLoad(&native));
    g_GameState = Game_MainMenu;
    g_Status.hp = 1;
    memset(&g_PcQol, 0, sizeof(g_PcQol));
    assert(PcSaveLoad(&native));
    assert(g_Status.hp == block.save.status.hp);
    assert(PcQolProfileId() != sourceProfile);
    assert(SDL_CopyFile(native.path, "saves/corrupt.sav"));
    file = fopen("saves/corrupt.sav", "r+b");
    assert(file && fseek(file, 12, SEEK_SET) == 0);
    int byte = fgetc(file);
    assert(byte != EOF && fseek(file, 12, SEEK_SET) == 0);
    assert(fputc(byte ^ 1, file) != EOF && !fclose(file));
    PcSaveEntry corrupt = native;
    strcpy(corrupt.path, "saves/corrupt.sav");
    assert(!PcSaveLoad(&corrupt) && g_Status.hp == block.save.status.hp);
    assert(!memcmp(&g_PcQol, &expectedProfile, sizeof(g_PcQol)));
    g_GameState = Game_MainMenu;
    assert(!PcSaveRename(&native, "        "));
    assert(PcSaveRename(&native, "x-x!v''q"));
    assert(PcSaveLoad(&native));
    assert(!memcmp(g_Status.saveName, "x-x!v''q", 8));
    assert(g_PlayableCharacter == PLAYER_ALUCARD);
    assert(
        g_Status.statsBase[STAT_LCK] == block.save.status.statsBase[STAT_LCK]);
    g_GameClearFlag = SAVE_FLAG_CLEAR;
    g_StageId = STAGE_LIB;
    g_Status.gold = 321;
    assert(PcSaveCommit());
    g_Status.gold = 0;
    assert(PcSaveContinue() && g_Status.gold == 321);
    assert(PcSaveClearFlags() & SAVE_FLAG_CLEAR);
    unsigned nativeProfile = PcQolProfileId();
    // Refuse an overwrite if backing up the previous slot is impossible.
    assert(SDL_RenamePath("settings.ini.backups", "backup-hold"));
    file = fopen("settings.ini.backups", "wb");
    assert(file && !fclose(file));
    g_Status.gold = 999;
    assert(!PcSaveCommit());
    assert(SDL_RemovePath("settings.ini.backups"));
    assert(SDL_RenamePath("backup-hold", "settings.ini.backups"));
    assert(PcSaveLoad(&native) && g_Status.gold == 321);
    assert(PcQolProfileId() == nativeProfile);
    // Archiving hides only the native copy; legacy sources remain
    // byte-identical.
    g_GameState = Game_Play;
    assert(!PcSaveArchive(&native));
    g_GameState = Game_MainMenu;
    int listed = PcQolSaveList(NULL, 0);
    assert(PcSaveArchive(&native));
    assert(PcQolSaveList(NULL, 0) == listed - 1);
    assert(!PcSaveArchive(&native));
    file = fopen("bu00/test", "rb");
    assert(file && fread(unchanged, sizeof(unchanged), 1, file) == 1);
    fclose(file);
    assert(!memcmp(unchanged, block.raw, sizeof(unchanged)));
    // The browser is no longer constrained by either card's fifteen blocks.
    for (int i = 0; i < 31; i++)
        assert(PcQolRestore(&entries[1]));
    assert(PcQolSaveList(NULL, 0) >= 32);
    g_GameState = Game_Play;
    g_GameStep = Play_Default;
    g_StageId = STAGE_WRP;

    g_PcSettings.hudScale = 150;
    Primitive hud = {
        .type = PRIM_GT4,
        .drawMode = DRAW_ABSPOS,
        .tpage = 0x1B,
        .priority = 0x1F0,
        .x0 = 4,
        .x1 = 13,
        .x2 = 4,
        .x3 = 13,
        .y0 = 70,
        .y1 = 70,
        .y2 = 115,
        .y3 = 115};
    for (int wide = 0; wide < 2; wide++) {
        g_PcSettings.widescreen = wide;
        PcUpdateViewport();
        Primitive adjusted = hud;
        PcAdjustPrimitive(&adjusted);
        assert(adjusted.x0 == PcViewLeft() + 6);
        assert(adjusted.x1 == PcViewLeft() + 19);
        assert(adjusted.y0 == 95 && adjusted.y2 == 162);
    }
    g_PcSettings.hudScale = 100;
    GpuBuffer* previousBuffer = g_CurrentBuffer;
    g_CurrentBuffer = &g_GpuBuffers[0];
    g_CutsceneHasControl = 1;
    PcQolDialogueChar('\n');
    for (int i = 0; i < 100; i++)
        PcQolDialogueChar('A' + i % 26);
    for (int wide = 0; wide < 2; wide++) {
        g_PcSettings.widescreen = wide;
        PcUpdateViewport();
        for (int scale = 1; scale <= 3; scale++) {
            ClearOTagR(g_CurrentBuffer->ot, OTSIZE);
            void* end = (void*)getaddr(&g_CurrentBuffer->ot[0x1FF]);
            g_PcSettings.subtitleScale = scale;
            PcQolHud();
            DR_MODE* mode = (DR_MODE*)getaddr(&g_CurrentBuffer->ot[0x1FF]);
            assert((void*)mode != end);
            TILE* tile = (TILE*)getaddr(mode);
            int count = 0;
            while ((void*)tile != end) {
                assert(++count <= 4096 && getcode(tile) == 0x60);
                assert(tile->y0 >= 20 && tile->y0 + tile->h <= 227);
                tile = (TILE*)getaddr(tile);
            }
            assert(count > 1);
        }
    }
    g_CurrentBuffer = previousBuffer;
    g_CutsceneHasControl = 0;
    g_PcSettings.subtitleScale = 0;
    SDL_Window* window = SDL_CreateWindow(
        "Adventure UI regression", 1200, 920, SDL_WINDOW_HIDDEN);
    assert(window);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, "software");
    assert(renderer);
    PcMenuBackground(renderer);
    SDL_Surface* gradient = SDL_RenderReadPixels(renderer, NULL);
    u8 topBlue, bottomBlue;
    assert(gradient && SDL_ReadSurfacePixel(gradient, 100, 100, NULL, NULL,
                                          &topBlue, NULL));
    assert(SDL_ReadSurfacePixel(gradient, 100, 800, NULL, NULL,
                               &bottomBlue, NULL));
    assert(topBlue > bottomBlue + 20);
    SDL_DestroySurface(gradient);
    PlayerStatus previewSetup = g_Status;
    g_Status.equipment[0] = ITEM_ALUCARD_SWORD;
    g_Status.equipment[1] = ITEM_ALUCARD_SHIELD;
    PlayerStatus beforePreview = g_Status;
    Entity beforePlayer = PLAYER;
    Entity* beforeCurrent = g_CurrentEntity;
    int beforeTimer = g_Timer;
    int beforeCharacter = g_PlayableCharacter;
    g_PlayableCharacter = PLAYER_ALUCARD;
    PcInventoryPreviewReset();
    assert(!strcmp(PcInventoryPreviewName(), "Idle"));
    const char* animations[] = {
        "Idle", "Walk", "Attack L", "Attack R", "Special L", "Special R"};
    for (int i = 0; i < 6; i++) {
        assert(!strcmp(PcInventoryPreviewName(), animations[i]));
        PcInventoryPreviewDraw(renderer, 100, 100);
        PcInventoryPreviewCycle();
    }
    assert(!strcmp(PcInventoryPreviewName(), "Idle"));
    PcQolUiOpenPage(1);
    SDL_Event animate = {.type = SDL_EVENT_KEY_DOWN};
    animate.key.scancode = SDL_SCANCODE_A;
    PcQolUiEvent(&animate, window);
    assert(!strcmp(PcInventoryPreviewName(), "Walk"));
    animate.type = SDL_EVENT_GAMEPAD_AXIS_MOTION;
    animate.gaxis.axis = SDL_GAMEPAD_AXIS_RIGHT_TRIGGER;
    animate.gaxis.value = 30000;
    PcQolUiEvent(&animate, window);
    assert(!strcmp(PcInventoryPreviewName(), "Attack L"));
    PcQolUiEvent(&animate, window);
    assert(!strcmp(PcInventoryPreviewName(), "Attack L"));
    animate.gaxis.value = 0;
    PcQolUiEvent(&animate, window);
    animate.gaxis.value = 30000;
    PcQolUiEvent(&animate, window);
    assert(!strcmp(PcInventoryPreviewName(), "Attack R"));
    animate.gaxis.value = 0;
    PcQolUiEvent(&animate, window);
    animate.gaxis.value = 30000;
    PcQolUiEvent(&animate, window);
    assert(!strcmp(PcInventoryPreviewName(), "Special L"));
    PcInventoryPreviewCycle();
    PcInventoryPreviewCycle();
    assert(!strcmp(PcInventoryPreviewName(), "Idle"));
    PcQolUiOpenPage(0);
    g_Status.equipment[0] = ITEM_EMPTY_HAND;
    for (int i = 0; i < 4; i++)
        PcInventoryPreviewCycle();
    assert(!strcmp(PcInventoryPreviewName(), "No special L"));
    g_Status.equipment[0] = ITEM_ALUCARD_SWORD;
    PcQolUiOpenPage(0);
    g_PlayableCharacter = PLAYER_RICHTER;
    PcInventoryPreviewCycle();
    assert(!strcmp(PcInventoryPreviewName(), "Richter"));
    g_PlayableCharacter = beforeCharacter;
    assert(!memcmp(&g_Status, &beforePreview, sizeof(g_Status)));
    assert(!memcmp(&PLAYER, &beforePlayer, sizeof(PLAYER)));
    assert(g_CurrentEntity == beforeCurrent && g_Timer == beforeTimer);
    g_Status = previewSetup;
    g_PlayerX = g_PlayerY = 0;
    g_Tilemap.left = g_Tilemap.top = 0;
    PcQolUiOpen();
    SDL_Event placePin = {.type = SDL_EVENT_KEY_DOWN};
    placePin.key.scancode = SDL_SCANCODE_P;
    PcQolUiEvent(&placePin, window);
    assert(!strcmp(g_PcQol.pins[pin].note, "Bat ledge"));
    for (int page = 0; page < 7; page++) {
        PcQolUiDraw(renderer);
        SDL_Surface* image = SDL_RenderReadPixels(renderer, NULL);
        assert(image && image->w == 1200 && image->h == 920);
        SDL_DestroySurface(image);
        SDL_Event tab = {.type = SDL_EVENT_KEY_DOWN};
        tab.key.scancode = SDL_SCANCODE_TAB;
        PcQolUiEvent(&tab, window);
    }
    // Current stats must remain visible even when the item list is empty.
    PcQolUiOpenPage(1);
    memset(g_PcQol.favorites, 0, sizeof(g_PcQol.favorites));
    SDL_Event favoriteFilter = {.type = SDL_EVENT_KEY_DOWN};
    favoriteFilter.key.scancode = SDL_SCANCODE_B;
    PcQolUiEvent(&favoriteFilter, window);
    PcQolUiDraw(renderer);
    SDL_Rect statsRect = {500, 588, 680, 128};
    SDL_Surface* statsBefore = SDL_RenderReadPixels(renderer, &statsRect);
    PlayerStatus statsStatus = g_Status;
    g_Status.statsBase[0]++;
    PcQolUiDraw(renderer);
    assert(g_Status.statsBase[0] == statsStatus.statsBase[0] + 1);
    SDL_Surface* statsAfter = SDL_RenderReadPixels(renderer, &statsRect);
    assert(statsBefore && statsAfter && statsBefore->pitch == statsAfter->pitch);
    assert(memcmp(statsBefore->pixels, statsAfter->pixels,
                  statsBefore->pitch * statsBefore->h));
    g_Status = statsStatus;
    SDL_DestroySurface(statsBefore);
    SDL_DestroySurface(statsAfter);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    assert(!PcQolSuspend()); // Warp rooms are scripted interactions.
    assert(!PcQolResume());  // Missing file leaves the running state intact.
    SDL_EnumerateDirectory("settings.ini.backups", RemoveEntry, NULL);
    SDL_RemovePath("settings.ini.backups");
    SDL_EnumerateDirectory("bu00", RemoveEntry, NULL);
    SDL_RemovePath("bu00");
    SDL_EnumerateDirectory("saves", RemoveEntry, NULL);
    SDL_RemovePath("saves");
    SDL_EnumerateDirectory("bu10", RemoveEntry, NULL);
    SDL_RemovePath("bu10");
    SDL_EnumerateDirectory(".", RemoveEntry, NULL);
    assert(chdir(previous) == 0);
    SDL_free(previous);
    assert(SDL_RemovePath(directory));
    g_PcSettingsPath = oldPath;
    g_Status = status;
    g_PcSettings = settings;
    g_PcQol = profile;
    puts("Adventure: explored pins, inventory ownership, backups, corrupt-file "
         "rollback, guarded shortcuts: PASS");
}
