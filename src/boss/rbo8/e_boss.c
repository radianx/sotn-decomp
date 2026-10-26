// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rbo8.h"

extern EInit g_EInitInteractable;
extern s32 D_us_801817B8;
// !FAKE: The boss treats the two prize-drop entries as one flag word.
extern s32 PrizeDrops;

void func_us_8019953C(Entity* self) {
    Entity* entity;
    s32 posX;
    s32 posY;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
        CreateEntityFromCurrentEntity(E_UNK_16, &g_Entities[80]);
        g_Entities[80].posX.i.hi = 0x190 - g_Tilemap.scrollX.i.hi;
        g_Entities[80].posY.i.hi = 0x1A3 - g_Tilemap.scrollY.i.hi;
        // fallthrough
    case 1:
        posX = PLAYER.posX.i.hi + g_Tilemap.scrollX.i.hi;
        if (posX > 0x100) {
            PrizeDrops |= 1;
        }
        if (PrizeDrops & 1) {
            D_us_801817B8 = 1;
            g_api.TimeAttackController(
                TIMEATTACK_EVENT_GALAMOTH_DEFEAT, TIMEATTACK_SET_VISITED);
            stopMusicFlag = 1;
            currentMusicId = MU_DEATH_BALLAD;
            self->step++;
        }
        break;
    case 3:
        if (PrizeDrops & 2) {
            g_api.TimeAttackController(
                TIMEATTACK_EVENT_GALAMOTH_DEFEAT, TIMEATTACK_SET_RECORD);
            g_api.PlaySfx(SET_UNK_90);
            currentMusicId = MU_CURSE_ZONE;
            self->step++;
        }
        break;
    case 4:
        if (PrizeDrops & 4) {
            self->step++;
        }
        break;
    case 5:
        posX = 0x100 - g_Tilemap.scrollX.i.hi;
        posY = 0x180 - g_Tilemap.scrollY.i.hi;
        entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
        if (entity != NULL) {
            CreateEntityFromEntity(E_LIFE_UP_SPAWN, self, entity);
            entity->params = 5;
            entity->posX.i.hi = posX;
            entity->posY.i.hi = posY;
            stopMusicFlag = 1;
            D_us_801817B8 = 0;
            currentMusicId = MU_CURSE_ZONE;
            self->step++;
        }
        break;
    case 2:
    case 6:
        if (!g_api.func_80131F68()) {
            stopMusicFlag = 0;
            g_api.PlaySfx(currentMusicId);
            self->step++;
        }
        break;
    }
}

extern EInit g_EInitParticle;
extern Point32 D_us_80181758[];

void func_us_801BA164_from_cat(Entity* self) {
    Primitive* prim;
    s32 velocity;
    s32 i;
    s32 temp;
    s16 posX;
    s16 posY;
    s16 primIndex;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitParticle);
        self->ext.et_801BA164.unk80 = 0x40;
        primIndex = g_api.func_800EDB58(PRIM_TILE_ALT, 8);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.et_801BA164.prim = prim;
        for (i = 0; prim->next != NULL; i++, prim = prim->next) {
            prim->u0 = 2;
            prim->v0 = 2;
            prim->x0 = self->posX.i.hi;
            prim->y0 = self->posY.i.hi;
            prim->r0 = 0x60;
            prim->g0 = 0x40;
            prim->b0 = 0x60;
            LOW(prim->r2) = D_us_80181758[i].x;
            LOW(prim->x2) = D_us_80181758[i].y;
            if (self->params & 0x10) {
                temp = LOW(prim->r2);
                LOW(prim->r2) = LOW(prim->x2);
                LOW(prim->x2) = -temp;
            }
            if (self->params & 1) {
                LOW(prim->r2) = -LOW(prim->r2);
            }
            LOW(prim->r1) = 0;
            LOW(prim->x1) = 0;
            prim->priority = self->zPriority;
            prim->drawMode = DRAW_DEFAULT;
        }
        prim->x0 = prim->y0 = prim->u0 = prim->v0 = 0;
        prim->priority = self->zPriority;
        prim->drawMode = DRAW_UNK02;
        // fallthrough
    case 1:
        posX = self->posX.i.hi;
        posY = self->posY.i.hi;
        prim = self->ext.et_801BA164.prim;
        while (prim->next != NULL) {
            velocity = (LOH(prim->b1) << 16) + LOH(prim->r1);
            velocity += LOW(prim->r2);
            LOW(prim->r1) = velocity;
            velocity = (prim->y1 << 16) + prim->x1;
            velocity += LOW(prim->x2);
            LOW(prim->x1) = velocity;
            prim->x0 = posX + LOH(prim->b1);
            prim->y0 = posY + prim->y1;
            LOW(prim->x2) += 0x1000;
            prim = prim->next;
        }
        prim->x0 = prim->y0 = prim->u0 = prim->v0 = 0;
        prim->priority = self->zPriority;
        prim->drawMode = DRAW_UNK02;
        if (!--self->ext.et_801BA164.unk80) {
            DestroyEntity(self);
        }
        break;
    }
}
