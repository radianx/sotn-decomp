// SPDX-License-Identifier: AGPL-3.0-or-later
#ifndef PC_QOL_H
#define PC_QOL_H
#include <game.h>
#include <SDL3/SDL.h>
#include "upgrades.h"

#define PC_MAP_PINS 64
#define PC_LOADOUTS 3
typedef struct {
    u8 used, castle, x, y, kind, requirement;
    char note[48];
} PcMapPin;
typedef struct {
    PcMapPin pins[PC_MAP_PINS];
    u8 favorites[NUM_HAND_ITEMS + NUM_BODY_ITEMS];
    u8 loadoutValid[PC_LOADOUTS];
    u32 loadouts[PC_LOADOUTS][7];
    s32 quickItem, quickSpell, loadout;
    u8 seenScenes[80];
    u8 saveRooms[2][512];
} PcQolData;
extern PcQolData g_PcQol;
extern const char* g_PcQolMessage;
extern const char* g_PcWarpNames[5];
extern const char* g_PcObstacleNames[10];
extern bool g_PcSpellPractice;
const char* PcQolInputHistory(void);
bool PcQolSave(void);
void PcQolSelectSave(const char* identity, bool loading);
unsigned PcQolProfileId(void);
bool PcQolUseProfile(unsigned id);
void PcQolValidate(PcQolData* data);
bool PcQolReady(void);
bool PcQolVisited(int castle, int x, int y);
bool PcQolPinReady(const PcMapPin* pin);
int PcQolSetPin(
    int castle, int x, int y, int kind, int requirement, const char* note);
void PcQolMapPosition(int* castle, int* x, int* y);
int PcQolOwned(int body, int id);
int PcQolInventory(int filter, int sort, bool favorites, int* items);
void PcQolItemText(int item, bool description, char* out, size_t size);
bool PcQolEquip(const u32 equipment[7], bool apply);
bool PcQolApplyGear(const u32 equipment[7]);
bool PcQolEquipItem(int item, int slot);
bool PcQolUseItem(int item);
bool PcQolCast(int spell);
void PcQolFrame(void);
void PcQolBeforePlayer(void);
bool PcQolAllowSubweapon(int subweapon);
void PcQolWarpOffer(int current);
int PcQolWarpDestination(int current);
bool PcQolWarpChoose(int destination);
bool PcQolSuspend(void);
bool PcQolResume(void);
void PcQolResumeFrame(void);
bool PcQolBackup(const char* path);
void PcQolSavePreview(unsigned id, unsigned previousId);
typedef struct {
    char path[1024];
    char origin[64];
    SaveInfo info;
    u8 palette[32], icon[128];
} PcSaveEntry;
int PcQolSaveList(PcSaveEntry* entries, int capacity);
bool PcQolRestore(const PcSaveEntry* entry);
SDL_Surface* PcQolLoadPreview(const PcSaveEntry* entry);
void PcQolDialogueChar(int ch);
bool PcQolSceneBegin(unsigned id);
void PcQolSceneEnd(unsigned id);
const char* PcQolDialogueLine(int index);
void PcQolHud(void);
void PcQolUiOpen(void);
void PcQolUiEvent(const SDL_Event* event, SDL_Window* window);
void PcQolUiDraw(SDL_Renderer* renderer);
bool PcQolUiWantsClose(void);
bool PcQolWrite(const char* path, const void* data, size_t size);
bool PcQolRead(const char* path, void* data, size_t size);
void PcQolTest(void);
#endif
