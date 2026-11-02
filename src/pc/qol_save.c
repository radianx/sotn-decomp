// SPDX-License-Identifier: AGPL-3.0-or-later
#include "qol.h"
#include "saves.h"
#include "pc.h"
#include "spawn_point.h"
#include "../dra/dra.h"
#include <psyz.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

extern void StoreSaveData(SaveData*, s32, s32);
extern s32 ApplySaveData(SaveData*);
extern bool g_IsQuitRequested;
typedef union {
    SaveData save;
    u8 raw[8192];
} SaveBlock;
typedef struct {
    SaveBlock block;
    PcQolData profile;
    s32 room, x, y, facing;
    s16 timers[16];
    u32 gameTimer, profileId;
} Suspend;
typedef struct {
    SaveBlock block;
    char origin[64];
} LegacyBackup;
typedef struct {
    SaveBlock block;
    char origin[64];
    PcQolData profile;
    unsigned profileId;
} Backup;
static char s_CurrentSave[64];
static bool ReadEntry(const char* path, Backup* backup);
static void FindCurrentSave(unsigned id);
static Suspend s_Resume;
static bool s_Resuming;

static bool Valid(const SaveData* save) {
    if (!memchr(save->info.name, 0, sizeof(save->info.name)) ||
        !memchr(save->status.saveName, 0, sizeof(save->status.saveName)) ||
        save->info.saveSize != sizeof(SaveData) || save->info.stage < 0 ||
        save->info.stage >= 80 || save->info.roomX > 63 ||
        save->info.roomY > 63 ||
        (save->info.character != PLAYER_ALUCARD &&
         save->info.character != PLAYER_RICHTER) ||
        save->status.hpMax <= 0 || save->status.hp < 0 ||
        save->status.hp > save->status.hpMax || save->status.mpMax < 0 ||
        save->status.mp < 0 || save->status.mp > save->status.mpMax)
        return false;
    for (int i = 0; i < 7; i++)
        if (save->status.equipment[i] >=
            (i < 2 ? NUM_HAND_ITEMS : NUM_BODY_ITEMS))
            return false;
    return true;
}

static void SuspendPath(char* path, size_t size) {
    snprintf(path, size, "%s.suspend", g_PcSettingsPath);
}

bool PcQolSuspend(void) {
    if (!PcQolReady() || (g_StageId & 0x10) || g_StageId == STAGE_WRP ||
        g_StageId == STAGE_RWRP || g_StageId == STAGE_DRE ||
        g_StageId == STAGE_CEN || g_StageId == STAGE_RCEN ||
        g_Player.status & (PLAYER_STATUS_TRANSFORM | PLAYER_STATUS_POISON |
                           PLAYER_STATUS_CURSE | PLAYER_STATUS_STONE) ||
        g_Player.unk46 || g_Player.grabState || PLAYER.step != Player_Stand) {
        g_PcQolMessage =
            "Suspend needs a safe, idle position outside a scripted encounter.";
        return false;
    }
    for (int i = 64; i < 256; i++)
        if ((g_Entities[i].hitboxState & 2) && g_Entities[i].hitPoints > 0 &&
            g_Entities[i].attack > 0) {
            g_PcQolMessage = "Clear nearby enemies before suspending.";
            return false;
        }
    for (int i = 8; i < 64; i++)
        if (g_Entities[i].entityId) {
            g_PcQolMessage = "Wait for weapon, spell and item effects to "
                             "finish before suspending.";
            return false;
        }
    Suspend state = {0};
    StoreSaveData(&state.block.save, 0, 0);
    state.profile = g_PcQol;
    state.profileId = PcQolProfileId();
    state.x = g_PlayerX;
    state.y = g_PlayerY;
    state.facing = PLAYER.facingLeft;
    state.gameTimer = g_GameTimer;
    memcpy(state.timers, g_Player.timers, sizeof(state.timers));
    state.room = -1;
    for (int i = 0; i < 256 && g_api.o.rooms[i].left != 64; i++) {
        const RoomHeader* room = &g_api.o.rooms[i];
        if (room->left == g_Tilemap.left && room->top == g_Tilemap.top &&
            room->load.tileLayoutId != 0xFF) {
            state.room = i;
            break;
        }
    }
    if (state.room < 0)
        return false;
    char path[1100];
    SuspendPath(path, sizeof(path));
    if (!PcQolWrite(path, &state, sizeof(state))) {
        g_PcQolMessage = "Suspend could not be written. Game is still running.";
        return false;
    }
    PcQolSave();
    g_IsQuitRequested = true;
    return true;
}

static bool BeginResume(const Suspend* state) {
    if (!Valid(&state->block.save) || state->room < 0 || state->room >= 256 ||
        state->x < 0 || state->x > 16383 || state->y < 0 || state->y > 16383)
        return false;
    s_Resume = *state;
    s_CurrentSave[0] = 0;
    if (!PcQolUseProfile(state->profileId))
        return false;
    FindCurrentSave(state->profileId);
    if (ApplySaveData(&s_Resume.block.save))
        return false;
    g_PcQol = state->profile;
    PcQolValidate(&g_PcQol);
    SpawnPoint_Request(g_StageId, state->room, state->x, state->y);
    D_8003C730 = 1;
    D_80097C98 = 0;
    g_DemoMode = Demo_None;
    g_GameState = Game_Play;
    g_GameStep = Play_PrepareNextStage;
    g_GameEngineStep = Engine_Init;
    s_Resuming = true;
    return true;
}

bool PcQolResume(void) {
    char path[1100];
    SuspendPath(path, sizeof(path));
    Suspend state;
    if (!PcQolRead(path, &state, sizeof(state)) || !BeginResume(&state)) {
        g_PcQolMessage = "No valid suspend file. Normal saves are unchanged.";
        return false;
    }
    return true;
}

void PcQolResumeFrame(void) {
    if (!s_Resuming || g_GameState != Game_Play || g_GameStep != Play_Default ||
        g_GameEngineStep != Engine_Normal)
        return;
    PlayerStatus status = s_Resume.block.save.status;
    g_Status = status;
    g_GameTimer = s_Resume.gameTimer;
    PLAYER.facingLeft = s_Resume.facing;
    memcpy(g_Player.timers, s_Resume.timers, sizeof(s_Resume.timers));
    make_all();
    s_Resuming = false;
    char path[1100], consumed[1120];
    SuspendPath(path, sizeof(path));
    snprintf(consumed, sizeof(consumed), "%s.resumed", path);
    if (!SDL_RenamePath(path, consumed))
        g_PcQolMessage = "Resumed; suspend file could not be retired.";
}

static unsigned PathHash(const char* text) {
    unsigned hash = 2166136261u;
    while (*text)
        hash = (hash ^ (unsigned char)*text++) * 16777619u;
    return hash;
}

static void PreviewPath(char* path, size_t size, unsigned id) {
    snprintf(path, size, "%s.%08x.png", g_PcSettingsPath, id);
}

static bool WritePreview(const char* path, SDL_Surface* image) {
    char temporary[1200];
    snprintf(temporary, sizeof(temporary), "%s.tmp", path);
    bool ok = SDL_SavePNG(image, temporary) && SDL_RenamePath(temporary, path);
    if (!ok)
        SDL_RemovePath(temporary);
    return ok;
}

static void CopyPreview(const char* source, const char* target) {
    SDL_Surface* image = SDL_LoadPNG(source);
    if (image) {
        if (!WritePreview(target, image))
            SDL_RemovePath(target);
        SDL_DestroySurface(image);
    } else
        SDL_RemovePath(target);
}

void PcQolSavePreview(unsigned id, unsigned previousId) {
    char path[1120];
    PreviewPath(path, sizeof(path), id);
    if (g_GameState == Game_MainMenu && id != previousId) {
        char source[1120];
        PreviewPath(source, sizeof(source), previousId);
        CopyPreview(source, path);
    }
    if (g_GameState != Game_Play || g_GameStep != Play_Default)
        return;
    int w, h;
    u8* pixels = Psyz_VideoAllocCapturedFrame(&w, &h);
    if (!pixels || w <= 0 || h <= 0) {
        free(pixels);
        SDL_RemovePath(path);
        return;
    }
    SDL_Surface* source =
        SDL_CreateSurfaceFrom(w, h, SDL_PIXELFORMAT_RGB24, pixels, w * 3);
    SDL_Surface* image = SDL_CreateSurface(192, 108, SDL_PIXELFORMAT_RGB24);
    bool ok = false;
    if (source && image) {
        SDL_ClearSurface(image, 0, 0, 0, 1);
        int width = SDL_min(192, 108 * w / h), height = width * h / w;
        SDL_Rect area = {(192 - width) / 2, (108 - height) / 2, width, height};
        if (SDL_BlitSurfaceScaled(
                source, NULL, image, &area, SDL_SCALEMODE_NEAREST))
            ok = WritePreview(path, image);
    }
    if (!ok)
        SDL_RemovePath(path);
    SDL_DestroySurface(image);
    SDL_DestroySurface(source);
    free(pixels);
}

SDL_Surface* PcQolLoadPreview(const PcSaveEntry* entry) {
    char path[1120];
    if (strstr(entry->path, ".qsave"))
        snprintf(path, sizeof(path), "%s.png", entry->path);
    else {
        char identity[64];
        SDL_strlcpy(identity, entry->origin, sizeof(identity));
        char* slash = strchr(identity, '/');
        if (slash)
            *slash = ':';
        Backup backup;
        unsigned id = ReadEntry(entry->path, &backup) ? backup.profileId
                                                      : PathHash(identity);
        PreviewPath(path, sizeof(path), id);
    }
    return SDL_LoadPNG(path);
}

bool PcQolBackup(const char* psxPath) {
    char source[64], directory[1100], path[1200];
    if (strlen(psxPath) >= sizeof(source))
        return false;
    strcpy(source, psxPath);
    char* colon = strchr(source, ':');
    if (colon)
        *colon = '/';
    FILE* probe = fopen(source, "rb");
    if (!probe)
        return errno == ENOENT;
    fclose(probe);
    Backup backup;
    if (!ReadEntry(source, &backup))
        return false;
    SDL_strlcpy(backup.origin, source, sizeof(backup.origin));
    snprintf(directory, sizeof(directory), "%s.backups", g_PcSettingsPath);
    if (!SDL_CreateDirectory(directory))
        return false;
    unsigned hash = PathHash(source);
    // Write the next ring slot first, preserving the other two backups on
    // error.
    u64 newest = 0;
    int slot = 0;
    for (int i = 0; i < 3; i++) {
        SDL_PathInfo info;
        snprintf(path, sizeof(path), "%s/%08x-%d.qsave", directory, hash, i);
        if (!SDL_GetPathInfo(path, &info)) {
            slot = i;
            newest = 0;
            break;
        }
        if (!newest || info.modify_time < newest) {
            newest = info.modify_time;
            slot = i;
        }
    }
    snprintf(path, sizeof(path), "%s/%08x-%d.qsave", directory, hash, slot);
    if (!PcQolWrite(path, &backup, sizeof(backup)))
        return false;
    char preview[1120], copy[1220];
    PreviewPath(preview, sizeof(preview), backup.profileId);
    snprintf(copy, sizeof(copy), "%s.png", path);
    CopyPreview(preview, copy);
    return true;
}

typedef struct {
    PcSaveEntry* entries;
    int count, capacity;
} SaveList;
static bool ReadEntry(const char* path, Backup* backup) {
    memset(backup, 0, sizeof(*backup));
    if (PcQolRead(path, backup, sizeof(*backup))) {
        if (!Valid(&backup->block.save) ||
            !memchr(backup->origin, 0, sizeof(backup->origin)))
            return false;
        if (!strstr(path, ".qsave")) {
            char profile[1100];
            snprintf(profile, sizeof(profile), "%s.%08x.qol", g_PcSettingsPath,
                     backup->profileId);
            PcQolRead(profile, &backup->profile, sizeof(backup->profile));
        }
        PcQolValidate(&backup->profile);
        return true;
    }
    LegacyBackup legacy;
    if (PcQolRead(path, &legacy, sizeof(legacy))) {
        backup->block = legacy.block;
        memcpy(backup->origin, legacy.origin, sizeof(legacy.origin));
        if (!Valid(&backup->block.save) ||
            !memchr(backup->origin, 0, sizeof(backup->origin)))
            return false;
    } else {
        if (strncmp(path, "bu00/", 5) && strncmp(path, "bu10/", 5))
            return false;
        FILE* file = fopen(path, "rb");
        if (!file)
            return false;
        bool ok =
            fread(backup->block.raw, sizeof(backup->block.raw), 1, file) == 1 &&
            fgetc(file) == EOF && !ferror(file);
        fclose(file);
        if (!ok || !Valid(&backup->block.save))
            return false;
        SDL_strlcpy(backup->origin, path, sizeof(backup->origin));
    }
    char identity[64], profile[1100];
    SDL_strlcpy(identity, backup->origin, sizeof(identity));
    char* slash = strchr(identity, '/');
    if (slash)
        *slash = ':';
    backup->profileId = PathHash(identity);
    backup->profile =
        (PcQolData){.quickItem = ITEM_POTION, .quickSpell = -1, .loadout = -1};
    snprintf(profile, sizeof(profile), "%s.%08x.qol", g_PcSettingsPath,
             backup->profileId);
    PcQolRead(profile, &backup->profile, sizeof(backup->profile));
    PcQolValidate(&backup->profile);
    return true;
}
static SDL_EnumerationResult FindSlot(
    void* userdata, const char* dirname, const char* name) {
    size_t length = strlen(name);
    if (length <= 4 || strcmp(name + length - 4, ".sav"))
        return SDL_ENUM_CONTINUE;
    char path[64];
    if (snprintf(path, sizeof(path), "%s%s", dirname, name) >= sizeof(path))
        return SDL_ENUM_CONTINUE;
    Backup save;
    if (ReadEntry(path, &save) && save.profileId == *(unsigned*)userdata) {
        SDL_strlcpy(s_CurrentSave, path, sizeof(s_CurrentSave));
        return SDL_ENUM_SUCCESS;
    }
    return SDL_ENUM_CONTINUE;
}

static void FindCurrentSave(unsigned id) {
    s_CurrentSave[0] = 0;
    SDL_EnumerateDirectory("saves", FindSlot, &id);
}

static SDL_EnumerationResult ListEntry(
    void* userdata, const char* dirname, const char* name) {
    SaveList* list = userdata;
    size_t length = strlen(name);
    bool native = length > 4 && !strcmp(name + length - 4, ".sav");
    bool backupFile = length > 6 && !strcmp(name + length - 6, ".qsave");
    if ((list->entries && list->count == list->capacity) ||
        (!backupFile && !native && strncmp(name, "BASLUS", 6)))
        return SDL_ENUM_CONTINUE;
    PcSaveEntry entry = {0};
    Backup backup;
    snprintf(entry.path, sizeof(entry.path), "%s%s", dirname, name);
    if (ReadEntry(entry.path, &backup)) {
        entry.info = backup.block.save.info;
        memcpy(entry.palette, backup.block.save.header.Clut,
               sizeof(entry.palette));
        memcpy(entry.icon, backup.block.save.header.Icon, sizeof(entry.icon));
        SDL_strlcpy(entry.origin, backup.origin, sizeof(entry.origin));
        if (list->entries)
            list->entries[list->count] = entry;
        list->count++;
    }
    return SDL_ENUM_CONTINUE;
}
int PcQolSaveList(PcSaveEntry* entries, int capacity) {
    SaveList list = {entries, 0, capacity};
    char directory[1100];
    snprintf(directory, sizeof(directory), "%s.backups", g_PcSettingsPath);
    SDL_EnumerateDirectory("saves", ListEntry, &list);
    SDL_EnumerateDirectory("bu00", ListEntry, &list);
    SDL_EnumerateDirectory("bu10", ListEntry, &list);
    SDL_EnumerateDirectory(directory, ListEntry, &list);
    return list.count;
}
static bool NewPath(char* path, size_t size) {
    static unsigned sequence;
    SDL_Time now;
    if (!SDL_CreateDirectory("saves") || !SDL_GetCurrentTime(&now))
        return false;
    snprintf(path, size, "saves/%016llx-%04x.sav", (unsigned long long)now,
             sequence++);
    return true;
}

void PcSaveNewGame(void) { s_CurrentSave[0] = 0; }

bool PcSaveCommit(void) {
    Backup save = {0};
    StoreSaveData(&save.block.save, 0, rand() & 15);
    if (!Valid(&save.block.save))
        return false;
    char path[64];
    bool fresh = !s_CurrentSave[0];
    if (fresh) {
        if (!NewPath(path, sizeof(path)))
            return false;
        FILE* reservation = fopen(path, "wbx");
        if (!reservation)
            return false;
        if (fclose(reservation)) {
            SDL_RemovePath(path);
            return false;
        }
    } else {
        SDL_strlcpy(path, s_CurrentSave, sizeof(path));
        if (!PcQolBackup(path))
            return false;
    }
    save.profile = g_PcQol;
    save.profileId = fresh ? PathHash(path) : PcQolProfileId();
    SDL_strlcpy(save.origin, path, sizeof(save.origin));
    if (!PcQolWrite(path, &save, sizeof(save))) {
        if (fresh)
            SDL_RemovePath(path);
        return false;
    }
    SDL_strlcpy(s_CurrentSave, path, sizeof(s_CurrentSave));
    if (fresh)
        PcQolUseProfile(save.profileId);
    PcQolSave();
    PcQolSavePreview(save.profileId, save.profileId);
    return true;
}

static bool CopySave(const PcSaveEntry* entry, char path[64]) {
    Backup save;
    if (!ReadEntry(entry->path, &save) || !NewPath(path, 64))
        return false;
    FILE* reservation = fopen(path, "wbx");
    if (!reservation)
        return false;
    if (fclose(reservation)) {
        SDL_RemovePath(path);
        return false;
    }
    SDL_Surface* image = PcQolLoadPreview(entry);
    // The copy gets its own profile; the embedded snapshot survives missing
    // sidecars.
    save.profileId = PathHash(path);
    SDL_strlcpy(save.origin, path, sizeof(save.origin));
    bool ok = PcQolWrite(path, &save, sizeof(save));
    if (!ok)
        SDL_RemovePath(path);
    if (ok && image) {
        char preview[1120];
        PreviewPath(preview, sizeof(preview), save.profileId);
        WritePreview(preview, image);
    }
    SDL_DestroySurface(image);
    return ok;
}

bool PcQolRestore(const PcSaveEntry* entry) {
    char path[64];
    return CopySave(entry, path);
}

bool PcSaveLoad(const PcSaveEntry* entry) {
    if (g_GameState != Game_MainMenu)
        return false;
    Backup save;
    char path[64];
    if (!ReadEntry(entry->path, &save))
        return false;
    if (strncmp(entry->path, "saves/", 6) || strstr(entry->path, ".qsave")) {
        if (!CopySave(entry, path) || !ReadEntry(path, &save))
            return false;
    } else if (SDL_strlcpy(path, entry->path, sizeof(path)) >= sizeof(path))
        return false;
    char profilePath[1024];
    if (snprintf(profilePath, sizeof(profilePath), "%s.%08x.qol",
                 g_PcSettingsPath, save.profileId) >= sizeof(profilePath))
        return false;
    PcQolSave();
    if (!PcQolUseProfile(save.profileId) || ApplySaveData(&save.block.save))
        return false;
    g_PcQol = save.profile;
    char profile[1100];
    snprintf(profile, sizeof(profile), "%s.%08x.qol", g_PcSettingsPath,
             save.profileId);
    PcQolRead(profile, &g_PcQol, sizeof(g_PcQol));
    PcQolValidate(&g_PcQol);
    SDL_strlcpy(s_CurrentSave, path, sizeof(s_CurrentSave));
    return true;
}

static PcSaveEntry* AllSaves(int* count) {
    int capacity = PcQolSaveList(NULL, 0);
    PcSaveEntry* entries =
        SDL_calloc(capacity ? capacity : 1, sizeof(*entries));
    *count = entries ? PcQolSaveList(entries, capacity) : 0;
    return entries;
}

unsigned PcSaveClearFlags(void) {
    int count;
    PcSaveEntry* entries = AllSaves(&count);
    unsigned flags = 0;
    for (int i = 0; i < count; i++)
        if (!strstr(entries[i].path, ".qsave"))
            flags |= entries[i].info.endGameFlags;
    SDL_free(entries);
    return flags;
}

bool PcSaveContinue(void) {
    int count, selected = -1;
    SDL_Time newest = 0;
    PcSaveEntry* entries = AllSaves(&count);
    for (int i = 0; i < count; i++) {
        SDL_PathInfo info;
        if (!strstr(entries[i].path, ".qsave") &&
            SDL_GetPathInfo(entries[i].path, &info) &&
            (selected < 0 || info.modify_time > newest)) {
            newest = info.modify_time;
            selected = i;
        }
    }
    bool ok = selected >= 0 && PcSaveLoad(&entries[selected]);
    SDL_free(entries);
    return ok;
}

bool PcSaveRename(const PcSaveEntry* entry, const char* name) {
    if (g_GameState != Game_MainMenu || !name || strlen(name) != 8)
        return false;
    bool empty = true;
    for (int i = 0; i < 8; i++) {
        if (!strchr("abcdefghijklmnopqrstuvwxyz&!-.' ", name[i]))
            return false;
        empty &= name[i] == ' ';
    }
    if (empty)
        return false;
    Backup save;
    if (!ReadEntry(entry->path, &save))
        return false;
    char path[64];
    if (strncmp(entry->path, "saves/", 6)) {
        if (!CopySave(entry, path) || !ReadEntry(path, &save))
            return false;
    } else if (SDL_strlcpy(path, entry->path, sizeof(path)) >= sizeof(path))
        return false;
    if (!PcQolBackup(path))
        return false;
    memset(save.block.save.info.name, 0, sizeof(save.block.save.info.name));
    memset(save.block.save.status.saveName, 0,
           sizeof(save.block.save.status.saveName));
    memcpy(save.block.save.info.name, name, 8);
    memcpy(save.block.save.status.saveName, name, 8);
    return PcQolWrite(path, &save, sizeof(save));
}

bool PcSaveArchive(const PcSaveEntry* entry) {
    if (strncmp(entry->path, "saves/", 6) ||
        (g_GameState == Game_Play && !strcmp(entry->path, s_CurrentSave)))
        return false;
    char archive[1100];
    snprintf(archive, sizeof(archive), "%s.archived", entry->path);
    SDL_PathInfo info;
    if (SDL_GetPathInfo(archive, &info))
        return false;
    return SDL_RenamePath(entry->path, archive);
}
