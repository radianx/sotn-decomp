// SPDX-License-Identifier: AGPL-3.0-or-later
#include "qol.h"
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
} Backup;
static Suspend s_Resume;
static bool s_Resuming;

static bool Valid(const SaveData* save) {
    if (save->info.saveSize != sizeof(SaveData) || save->info.stage < 0 ||
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
    if (!PcQolUseProfile(state->profileId))
        return false;
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
        PreviewPath(path, sizeof(path), PathHash(identity));
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
    FILE* file = fopen(source, "rb");
    if (!file)
        return errno == ENOENT;
    Backup backup = {0};
    bool ok = fread(backup.block.raw, sizeof(backup.block.raw), 1, file) == 1 &&
              fgetc(file) == EOF && !ferror(file);
    fclose(file);
    if (!ok || !Valid(&backup.block.save))
        return false;
    strcpy(backup.origin, source);
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
    PreviewPath(preview, sizeof(preview), PathHash(psxPath));
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
    if (PcQolRead(path, backup, sizeof(*backup)))
        return Valid(&backup->block.save) &&
               memchr(backup->origin, 0, sizeof(backup->origin));
    if (!strstr(path, "/BASLUS"))
        return false;
    FILE* file = fopen(path, "rb");
    if (!file)
        return false;
    bool ok =
        fread(backup->block.raw, sizeof(backup->block.raw), 1, file) == 1 &&
        fgetc(file) == EOF && !ferror(file);
    fclose(file);
    if (ok && Valid(&backup->block.save)) {
        snprintf(backup->origin, sizeof(backup->origin), "%s", path);
        return true;
    }
    return false;
}
static SDL_EnumerationResult ListEntry(
    void* userdata, const char* dirname, const char* name) {
    SaveList* list = userdata;
    if (list->count == list->capacity ||
        (!SDL_strstr(name, ".qsave") && strncmp(name, "BASLUS", 6)))
        return SDL_ENUM_CONTINUE;
    PcSaveEntry entry = {0};
    Backup backup;
    snprintf(entry.path, sizeof(entry.path), "%s%s", dirname, name);
    if (ReadEntry(entry.path, &backup)) {
        entry.info = backup.block.save.info;
        memcpy(entry.palette, backup.block.save.header.Clut,
               sizeof(entry.palette));
        memcpy(entry.icon, backup.block.save.header.Icon, sizeof(entry.icon));
        strcpy(entry.origin, backup.origin);
        list->entries[list->count++] = entry;
    }
    return SDL_ENUM_CONTINUE;
}
int PcQolSaveList(PcSaveEntry* entries, int capacity) {
    SaveList list = {entries, 0, capacity};
    char directory[1100];
    snprintf(directory, sizeof(directory), "%s.backups", g_PcSettingsPath);
    SDL_EnumerateDirectory("bu00", ListEntry, &list);
    SDL_EnumerateDirectory("bu10", ListEntry, &list);
    SDL_EnumerateDirectory(directory, ListEntry, &list);
    return list.count;
}
bool PcQolRestore(const PcSaveEntry* entry) {
    Backup backup;
    if (!ReadEntry(entry->path, &backup))
        return false;
    extern void MakeMemcardPath(char* name, s32 block);
    if (!SDL_CreateDirectory("bu10"))
        return false;
    for (int slot = 0; slot < 15; slot++) {
        char name[32], path[64];
        MakeMemcardPath(name, slot);
        snprintf(path, sizeof(path), "bu10/%s", name);
        FILE* file = fopen(path, "wbx");
        if (!file) {
            if (errno == EEXIST)
                continue;
            return false;
        }
        bool ok =
            fwrite(backup.block.raw, sizeof(backup.block.raw), 1, file) == 1;
        if (fclose(file))
            ok = false;
        if (!ok)
            remove(path);
        else {
            SDL_Surface* image = PcQolLoadPreview(entry);
            char identity[64], preview[1120];
            snprintf(identity, sizeof(identity), "bu10:%s", name);
            PreviewPath(preview, sizeof(preview), PathHash(identity));
            if (image) {
                WritePreview(preview, image);
                SDL_DestroySurface(image);
            } else
                SDL_RemovePath(preview);
        }
        return ok;
    }
    return false;
}
