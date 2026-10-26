// SPDX-License-Identifier: AGPL-3.0-or-later
#include <game.h>
#include "pc.h"
#include <SDL3/SDL.h>
#include <libapi.h>
#include <string.h>
#include <sys/stat.h>
#ifdef _WIN32
#include <direct.h>
#define chdir _chdir
#define rmdir _rmdir
#define MAKE_DIR(path) _mkdir(path)
#else
#include <unistd.h>
#define MAKE_DIR(path) mkdir(path, 0700)
#endif

extern void SetupEvents(void);
extern void StoreSaveData(SaveData*, s32, s32);
extern s32 ApplySaveData(SaveData*);
extern s32 MemcardWriteFile(s32, s32, const char*, void*, s32, bool);
extern s32 MemcardReadFile(s32, s32, const char*, void*, s32);
extern s32 MemcardClose(s32);

bool PcTestSave(void) {
    const char* name = "NATIVE-ROUNDTRIP";
    u32 written[2048], loaded[2048];
    char directory[128];
    char* previous = SDL_GetCurrentDirectory();
    bool ok = false;
    FILE* truncated;
    snprintf(directory, sizeof(directory), "build/pc-save-test-%llu",
             (unsigned long long)SDL_GetTicksNS());
    if (!previous || MAKE_DIR(directory) != 0) {
        SDL_free(previous);
        return false;
    }
    if (chdir(directory) != 0) {
        rmdir(directory);
        SDL_free(previous);
        return false;
    }
    _bu_init();
    SetupEvents();
    strcpy(g_Status.saveName, "native  ");
    g_Status.hp = 73;
    g_Status.hpMax = 120;
    g_Status.gold = 12345;
    g_Status.level = 17;
    g_Status.equipment[0] = 88;
    g_Settings.windowColors[0] = 3;
    g_CastleFlags[42] = 7;
    g_CastleMap[99] = 0xA5;
    g_StageId = STAGE_LIB;
    g_RoomCount = 31;
    g_randomNext = 0x12345678;
    StoreSaveData((SaveData*)written, 0, 0);
    if (MemcardWriteFile(0, 0, name, written, 1, true) != 0 ||
        MemcardClose(0) != 1) {
        ERRORF("Save test failed at line %d", __LINE__);
        goto cleanup;
    }
    memset(loaded, 0, sizeof(loaded));
    if (MemcardReadFile(0, 0, name, loaded, 1) != 0 || MemcardClose(0) != 1 ||
        memcmp(written, loaded, sizeof(written))) {
        ERRORF("Save test failed at line %d", __LINE__);
        goto cleanup;
    }
    memset(&g_Status, 0, sizeof(g_Status));
    memset(g_CastleFlags, 0, sizeof(g_CastleFlags));
    memset(g_CastleMap, 0, sizeof(g_CastleMap));
    g_Settings.windowColors[0] = 0;
    g_StageId = STAGE_NO0;
    g_randomNext = 0;
    if (ApplySaveData((SaveData*)loaded) != 0 || g_Status.hp != 73 ||
        g_Status.hpMax != 120 || g_Status.gold != 12345 ||
        g_Status.level != 17 || g_Status.equipment[0] != 88 ||
        g_Settings.windowColors[0] != 3 ||
        strcmp(g_Status.saveName, "native  ") || g_CastleFlags[42] != 7 ||
        g_CastleMap[99] != 0xA5 || g_StageId != STAGE_LIB ||
        g_RoomCount != 31 || g_randomNext != 0x12345678) {
        ERRORF("Save test failed at line %d", __LINE__);
        goto cleanup;
    }
    ((SaveData*)loaded)->info.saveSize = 0;
    if (ApplySaveData((SaveData*)loaded) != -1 || g_Status.hp != 73) {
        goto cleanup;
    }
    truncated = fopen("bu00/NATIVE-ROUNDTRIP", "wb");
    if (!truncated) {
        goto cleanup;
    }
    fclose(truncated);
    ok = MemcardReadFile(0, 0, name, loaded, 1) == -1;
cleanup:
    remove("bu00/NATIVE-ROUNDTRIP");
    rmdir("bu00");
    rmdir("bu10");
    if (chdir(previous) != 0) {
        ok = false;
    } else {
        rmdir(directory);
    }
    SDL_free(previous);
    printf(
        "Save/load round trip, invalid-size and truncated-file rejection: %s\n",
        ok ? "PASS" : "FAIL");
    return ok;
}
