// SPDX-License-Identifier: AGPL-3.0-or-later
#include "weapon_fx.h"
#include "pc.h"
#include "../dra/dra.h"
#include <psyz/module.h>
#include <psyz/gte.h>
#include <SDL3/SDL.h>
#include <string.h>

Entity g_PcFxEntities[TOTAL_ENTITY_COUNT];
Primitive g_PcFxPrimitives[MAX_PRIM_COUNT];
GameApi g_PcFxApi;
PlayerState g_PcFxPlayer;
PlayerStatus g_PcFxStatus;
Entity* g_PcFxCurrentEntity;
u16 g_PcFxClut[3][0x1000], g_PcFxVram[512][1024];
u32 g_PcFxTimer, g_PcFxGameTimer;
unkGraphicsStruct g_PcFxGraphics;
Tilemap g_PcFxTilemap;
GpuBuffer* g_PcFxBuffer;
PlayerDraw g_PcFxPlayerDraw[LEN(g_PlayerDraw)];

static PsyzModule s_Module;
static Weapon s_Weapon;
static bool s_Active, s_PrimitiveUsed[MAX_PRIM_COUNT];
static int s_Hand, s_Item;
static u32 s_Random;
static void NoSound(s32 id) {}
static s32 NoSoundPan(s32 id, s32 volume, s32 pan) { return 0; }
static void NoEntity(Entity* entity) {}
static void NoInt(s32 value) {}
static void NoShake(cameraShakeTypes value) {}
static void NoInventory(u32 item, EquipKind kind) {}
static void NoPlayerEffect(s32 arg0, s16 arg1) {}
static Entity* NoTarget(void) { return NULL; }
static s16 NoHit(Entity* first, Entity* second, s32 facing) { return 0; }

int PcFxRand(void) {
    s_Random = s_Random * 0x41C64E6Du + 0x3039;
    return (s_Random >> 16) & 0x7FFF;
}
void PcFxSrand(unsigned seed) { s_Random = seed; }
int PcFxDrawSync(int mode) { return 0; }
int PcFxVSync(int mode) { return g_PcFxTimer; }
u_long PcFxPadRead(int id) { return 0; }
int PcFxFntPrint(const char* format, ...) { return 0; }
u_long* PcFxFntFlush(int id) { return NULL; }
DRAWENV* PcFxPutDrawEnv(DRAWENV* env) { return env; }
DISPENV* PcFxPutDispEnv(DISPENV* env) { return env; }

int PcFxLoadImage(RECT* rect, u_long* pixels) {
    if (rect->x < 0 || rect->y < 0 || rect->w < 0 || rect->h < 0 ||
        rect->x + rect->w > 1024 || rect->y + rect->h > 512)
        return -1;
    for (int y = 0; y < rect->h; y++)
        memcpy(&g_PcFxVram[rect->y + y][rect->x], (u16*)pixels + y * rect->w,
               rect->w * sizeof(u16));
    return 0;
}

static s16 Alloc(PrimitiveType type, s32 count) {
    if (count <= 0 || count > MAX_PRIM_ALLOC_COUNT)
        return -1;
    int first = -1, previous = -1, available = 0;
    for (int i = 0; i < MAX_PRIM_ALLOC_COUNT; i++)
        available += !s_PrimitiveUsed[i];
    if (available < count)
        return -1;
    for (int i = 0; i < MAX_PRIM_ALLOC_COUNT && count; i++) {
        if (s_PrimitiveUsed[i])
            continue;
        s_PrimitiveUsed[i] = true;
        Primitive* prim = &g_PcFxPrimitives[i];
        memset(prim, 0, sizeof(*prim));
        prim->type = type;
        if (previous >= 0)
            g_PcFxPrimitives[previous].next = prim;
        else
            first = i;
        previous = i;
        count--;
    }
    return first;
}
static void Free(s32 index) {
    if (index < 0 || index >= MAX_PRIM_COUNT)
        return;
    Primitive* prim = &g_PcFxPrimitives[index];
    for (int n = 0; prim && n < MAX_PRIM_COUNT; n++) {
        Primitive* next = prim->next;
        s_PrimitiveUsed[prim - g_PcFxPrimitives] = false;
        memset(prim, 0, sizeof(*prim));
        prim = next;
    }
}
void PcFxDestroyEntity(Entity* entity) {
    if (entity->flags & FLAG_HAS_PRIMS)
        Free(entity->primIndex);
    memset(entity, 0, sizeof(*entity));
}
Entity* PcFxGetFreeEntity(s16 start, s16 end) {
    for (int i = SDL_max(start, 1); i < SDL_min(end, TOTAL_ENTITY_COUNT); i++)
        if (!g_PcFxEntities[i].entityId)
            return &g_PcFxEntities[i];
    return NULL;
}
Entity* PcFxGetFreeEntityReverse(s16 start, s16 end) {
    for (int i = SDL_min(end, TOTAL_ENTITY_COUNT) - 1; i >= SDL_max(start, 1);
         i--)
        if (!g_PcFxEntities[i].entityId)
            return &g_PcFxEntities[i];
    return NULL;
}

static void Equip(s32 hand, Equipment* out, s32 id) {
    *out = g_EquipDefs[id >= 0 && id < LEN(g_EquipDefs) ? id : 0];
}
static void Collision(s32 x, s32 y, Collider* out, s32 unk) {
    memset(out, 0, sizeof(*out));
    if (y >= 192) {
        out->effects = EFFECT_SOLID;
        out->unk18 = 192 - y;
    }
}
static Entity* Factory(Entity* source, u32 flags, s32 arg2) {
    // Stage/player factories are outside this isolated weapon world.
    if (!(flags & 0xF000) || (flags & 0xFFF) >= NUM_BLUEPRINTS)
        return NULL;
    Entity* entity = PcFxGetFreeEntity(8, 16);
    if (!entity)
        return NULL;
    PcFxDestroyEntity(entity);
    entity->entityId = E_FACTORY;
    entity->ext.factory.parent = source;
    entity->posX = source->posX;
    entity->posY = source->posY;
    entity->facingLeft = source->facingLeft;
    entity->zPriority = source->zPriority;
    entity->params = flags & 0xFFF;
    entity->ext.factory.entityIdMod = flags & 0x5000 ? 0xE0 : 0xF0;
    entity->ext.factory.paramsBase = (flags & 0xFF0000) >> 8;
    entity->ext.factory.unk92 = arg2;
    entity->flags = source->flags & FLAG_UNK_10000;
    return entity;
}

void PcWeaponFxStop(void) {
    s_Active = false;
    if (s_Module)
        Psyz_ModuleClose(s_Module);
    s_Module = 0;
}
bool PcWeaponFxActive(void) { return s_Active; }
int PcWeaponFxSpecial(int item) {
    if (item < 0 || item >= NUM_HAND_ITEMS)
        return -1;
    int special = g_EquipDefs[item].specialMove;
    if (!special)
        special = g_EquipDefs[item].unk17;
    return special > 0 && special < LEN(g_EquipDefs) ? special : -1;
}

bool PcWeaponFxStart(int hand, int item, bool special) {
    PcWeaponFxStop();
    if (hand < 0 || hand > 1 || item < 0 || item >= LEN(g_EquipDefs) ||
        g_EquipDefs[item].weaponId >= 59)
        return false;
    s_Hand = hand;
    s_Item = item;
    memset(g_PcFxEntities, 0, sizeof(g_PcFxEntities));
    memset(g_PcFxPrimitives, 0, sizeof(g_PcFxPrimitives));
    memset(s_PrimitiveUsed, 0, sizeof(s_PrimitiveUsed));
    memset(&g_PcFxPlayer, 0, sizeof(g_PcFxPlayer));
    memset(&g_PcFxGraphics, 0, sizeof(g_PcFxGraphics));
    memset(&g_PcFxTilemap, 0, sizeof(g_PcFxTilemap));
    g_PcFxStatus = g_Status;
    memcpy(g_PcFxClut, g_Clut, sizeof(g_PcFxClut));
    g_PcFxTimer = g_PcFxGameTimer = 0;
    s_Random = 1;
    RECT vram = {0, 0, 1024, 512};
    StoreImage(&vram, (u_long*)g_PcFxVram);
    DrawSync(0);
    memset(&g_PcFxApi, 0, sizeof(g_PcFxApi));
    static SpriteParts* banks[32];
    memset(banks, 0, sizeof(banks));
    g_PcFxApi.o.spriteBanks = banks;
    g_PcFxApi.AllocPrimitives = Alloc;
    g_PcFxApi.FreePrimitives = Free;
    g_PcFxApi.GetFreeEntity = PcFxGetFreeEntity;
    g_PcFxApi.GetEquipProperties = Equip;
    g_PcFxApi.CheckCollision = Collision;
    g_PcFxApi.PlaySfx = NoSound;
    g_PcFxApi.PlaySfxVolPan = NoSoundPan;
    g_PcFxApi.AddHearts = NoInt;
    g_PcFxApi.AddToInventory = NoInventory;
    g_PcFxApi.ShakeCamera = NoShake;
    g_PcFxApi.func_80118894 = NoEntity;
    g_PcFxApi.func_80118970 = NoTarget;
    g_PcFxApi.func_80118B18 = NoHit;
    g_PcFxApi.func_80118C28 = NoInt;
    g_PcFxApi.func_8010E168 = NoPlayerEffect;
    g_PcFxApi.CreateEntFactoryFromEntity = Factory;
    g_PcFxApi.PlayAnimation = PcFxPlayAnimation;
    g_PcFxApi.UpdateAnim = (void*)PcFxUpdateAnim;
    g_PcFxApi.UpdateUnarmedAnim = PcFxUpdateUnarmedAnim;
    g_PcFxApi.equipDefs = g_EquipDefs;
    char name[32];
    snprintf(name, sizeof(name), "pw%d_%03d", hand, g_EquipDefs[item].weaponId);
    s_Module = Psyz_ModuleOpen(name, &s_Weapon);
    if (!s_Module)
        return false;
    char path[48];
    snprintf(path, sizeof(path), "disks/us/BIN/WEAPON%d.BIN", hand);
    FILE* pixels = PcOpenAsset(path);
    u8 texture[0x4000];
    bool loaded =
        pixels &&
        fseek(pixels, g_EquipDefs[item].weaponId * 0x7000, SEEK_SET) == 0 &&
        fread(texture, 1, sizeof(texture), pixels) == sizeof(texture);
    if (pixels)
        fclose(pixels);
    if (!loaded) {
        PcWeaponFxStop();
        return false;
    }
    RECT page = {0x240, 0x100 + hand * 128, 64, 128};
    PcFxLoadImage(&page, (u_long*)texture);
    s_Weapon.LoadWeaponPalette(g_EquipDefs[item].palette);
    Entity* entity = &g_PcFxEntities[16];
    entity->entityId = 0xE0 + hand * 16;
    entity->params = ((g_EquipDefs[item].unk14 & 127) << 8) | (hand << 15);
    entity->ext.weapon.equipId = item;
    entity->ext.weapon.parent = &g_PcFxEntities[0];
    entity->posX.val = FIX(128);
    entity->posY.val = FIX(160);
    entity->zPriority = 128;
    int function = special ? 8 : PcFxWeaponFunction(g_EquipDefs[item].unk13);
    if (function < 0 || function >= 16) {
        PcWeaponFxStop();
        return false;
    }
    entity->entityId += function;
    entity->pfnUpdate = ((PfnEntityUpdate*)&s_Weapon)[function];
    s_Active = true;
    return true;
}

void PcWeaponFxStep(const Entity* player) {
    if (!s_Active)
        return;
    g_PcFxEntities[0] = *player;
    g_PcFxEntities[0].posX.val = FIX(128);
    g_PcFxEntities[0].posY.val = FIX(160);
    g_PcFxEntities[0].zPriority = 128;
    g_PcFxPlayer.unk46 = 1;
    g_PcFxPlayer.padPressed = s_Hand ? PAD_CIRCLE : PAD_SQUARE;
    g_PcFxTimer++;
    g_PcFxGameTimer++;
    u32 data[32], control[32];
    for (int i = 0; i < 32; i++) {
        data[i] = Psyz_GteDataRead(i);
        control[i] = Psyz_GteCtrlRead(i);
    }
    for (int i = 1; i < 64; i++) {
        Entity* entity = &g_PcFxEntities[i];
        if (!entity->entityId)
            continue;
        g_PcFxCurrentEntity = entity;
        if (entity->entityId == E_FACTORY)
            PcFxFactoryUpdate(entity);
        else {
            if (!entity->pfnUpdate) {
                int function = entity->entityId - (0xE0 + s_Hand * 16);
                if (function < 0 || function >= 16) {
                    PcFxDestroyEntity(entity);
                    continue;
                }
                entity->pfnUpdate = ((PfnEntityUpdate*)&s_Weapon)[function];
            }
            entity->pfnUpdate(entity);
            if (!(entity->flags & FLAG_KEEP_ALIVE_OFFCAMERA) &&
                (entity->posX.i.hi < -32 || entity->posX.i.hi > 288 ||
                 entity->posY.i.hi > 256 || entity->posY.i.hi < -64))
                PcFxDestroyEntity(entity);
            else if (entity->entityId && (entity->flags & FLAG_UNK_100000))
                PcFxUpdateAnim(NULL, D_800ACFB4);
        }
    }
    for (int i = 0; i < 32; i++)
        Psyz_GteCtrlWrite(i, control[i]);
    // SXYP/IRGB/ORGB/LZCR alias other registers or are derived/read-only.
    for (int i = 0; i < 32; i++)
        if (i != 15 && i != 28 && i != 29 && i != 31)
            Psyz_GteDataWrite(i, data[i]);
}

#ifndef NDEBUG
// Exercise whole effect lifetimes from GDB without advancing the game clock.
int PcWeaponFxCheckSequence(int item, int hand, bool special, int frames) {
    if (item < 0 || item >= NUM_HAND_ITEMS || frames < 1 || frames > 1200)
        return 0;
    bool shield = g_EquipDefs[item].itemCategory == ITEM_SHIELD;
    if (special && !shield && PcWeaponFxSpecial(item) >= 0)
        item = PcWeaponFxSpecial(item);
    if (!PcWeaponFxStart(hand, item, special && shield))
        return 0;
    Entity actor = {0};
    actor.animSet = 1;
    actor.palette = PAL_FLAG(PAL_ALUCARD);
    actor.ext.player.anim = shield ? 6 : g_EquipDefs[item].playerAnim;
    actor.hitboxOffY = -8;
    actor.hitboxHeight = 24;
    actor.hitboxWidth = 8;
    actor.zPriority = 128;
    int result = 1;
    for (int frame = 0; frame < frames; frame++) {
        g_PcFxCurrentEntity = &actor;
        PcFxPlayAnimation(NULL, D_800B01B8);
        PcWeaponFxStep(&actor);
        for (int i = 1; i < 64; i++) {
            if (g_PcFxEntities[i].entityId && g_PcFxEntities[i].animCurFrame)
                result |= 2;
            if (i != 16 && g_PcFxEntities[i].entityId > 1)
                result |= 8;
        }
        for (int i = 0; i < MAX_PRIM_COUNT; i++)
            if (g_PcFxPrimitives[i].type &&
                !(g_PcFxPrimitives[i].drawMode & DRAW_HIDE))
                result |= 4;
    }
    return result;
}
#endif
