// SPDX-License-Identifier: AGPL-3.0-or-later
#include "bo7.h"

extern EInit g_EInitParticle;
extern EInit g_EInitInteractable;
extern EntityConfig D_us_801808A4[];
extern s32 D_us_80180848;

void func_us_80195C50(Entity* self) {
    RECT rect;
    DRAWENV drawEnv;
    Primitive* prim;
    Entity* entity;
    DR_ENV* drEnv;
    s16 primIndex;
    s32 x;
    s32 y;
    s32 i;
    s32 brightness;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
        self->flags |= FLAG_UNK_10000;
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 7);
        if (primIndex == -1) {
            self->step = 0;
            return;
        }
        prim = &g_PrimBuf[primIndex];
        self->primIndex = primIndex;
        self->flags |= FLAG_HAS_PRIMS;
        drEnv = g_api.func_800EDB08((POLY_GT4*)prim);
        if (drEnv == NULL) {
            g_api.FreePrimitives(primIndex);
            self->step = 0;
            self->flags &= ~FLAG_HAS_PRIMS;
            return;
        }
        prim->type = PRIM_ENV;
        prim->drawMode = DRAW_HIDE;
        prim = prim->next;
        drEnv = g_api.func_800EDB08((POLY_GT4*)prim);
        // @bug: The original checks prim instead of the allocated draw
        // environment.
        if (prim == NULL) {
            g_api.FreePrimitives(primIndex);
            self->step = 0;
            self->flags &= ~FLAG_HAS_PRIMS;
            return;
        }
        prim->type = PRIM_ENV;
        prim->drawMode = DRAW_HIDE;
        prim = prim->next;
        self->ext.prim = prim;
        prim->type = PRIM_G4;
        prim->r0 = prim->g0 = prim->b0 = 0;
        LOW(prim->r1) = LOW(prim->r0);
        prim->x0 = prim->x2 = 0;
        prim->x1 = prim->x3 = 0x42;
        prim->y0 = prim->y1 = 0;
        prim->y2 = prim->y3 = 0xB0;
        prim->r2 = 0xFF;
        prim->g2 = prim->b2 = 0;
        LOW(prim->r3) = LOW(prim->r2);
        prim->priority = 0xF;
        prim->drawMode = DRAW_DEFAULT;
        prim = prim->next;
        for (i = 0; i < 4; i++) {
            prim->tpage = 0x110;
            if (i & 1) {
                prim->u0 = prim->u2 = 0x3F;
                prim->u1 = prim->u3 = 0;
            } else {
                prim->u0 = prim->u2 = 0;
                prim->u1 = prim->u3 = 0x3F;
            }
            prim->v0 = prim->v1 = 0x10;
            prim->v2 = prim->v3 = 0xF0;
            prim->x0 = prim->x2 = i * 0x40;
            prim->x1 = prim->x3 = i * 0x40 + 0x40;
            prim->y0 = prim->y1 = 0x10;
            prim->y2 = prim->y3 = 0xF0;
            prim->priority = 0x13;
            prim->drawMode = DRAW_DEFAULT;
            prim = prim->next;
        }
        g_api.PlaySfx(SFX_BOSS_LARGE_FLAMES);
        // fallthrough
    case 1:
        x = PLAYER.posX.i.hi + g_Tilemap.scrollX.i.hi;
        if ((u32)(x - 0x41) < 0x17F) {
            D_us_80180848 |= 1;
            self->step++;
        }
        if (!(g_Timer % 95)) {
            g_api.PlaySfx(SFX_BOSS_LARGE_FLAMES);
        }
        break;
    case 2:
        if (!(g_Timer % 95)) {
            g_api.PlaySfx(SFX_BOSS_LARGE_FLAMES);
        }
        x = PLAYER.posX.i.hi + g_Tilemap.scrollX.i.hi;
        if ((u32)(x - 0x81) < 0xFF) {
            g_api.TimeAttackController(
                TIMEATTACK_EVENT_CERBERUS_DEFEAT, TIMEATTACK_SET_VISITED);
            stopMusicFlag = 1;
            currentMusicId = MU_FESTIVAL_OF_SERVANTS;
            D_us_80180848 |= 2;
            self->step++;
        }
        break;
    case 3:
        if (!g_api.func_80131F68()) {
            stopMusicFlag = 0;
            g_api.PlaySfx(currentMusicId);
            self->step++;
        }
        // fallthrough
    case 4:
        if (D_us_80180848 & 4) {
            g_api.TimeAttackController(
                TIMEATTACK_EVENT_CERBERUS_DEFEAT, TIMEATTACK_SET_RECORD);
            g_api.PlaySfx(SET_UNK_90);
            currentMusicId = MU_ABANDONED_PIT;
            self->step++;
        }
        break;
    case 5:
        if (D_us_80180848 & 8) {
            self->step++;
        }
        break;
    case 6:
        x = 0x100 - g_Tilemap.scrollX.i.hi;
        y = 0x80 - g_Tilemap.scrollY.i.hi;
        entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
        if (entity != NULL) {
            CreateEntityFromEntity(E_LIFE_UP_SPAWN, self, entity);
            entity->posX.i.hi = x;
            entity->posY.i.hi = y;
            entity->params = 5;
            stopMusicFlag = 1;
            currentMusicId = MU_ABANDONED_PIT;
            D_us_80180848 |= 0x10;
            self->step++;
        }
        // fallthrough
    case 7:
        if (!g_api.func_80131F68()) {
            stopMusicFlag = 0;
            g_api.PlaySfx(currentMusicId);
            self->step++;
        }
        break;
    }
    prim = &g_PrimBuf[self->primIndex];
    drawEnv = g_CurrentBuffer->draw;
    drawEnv.isbg = 1;
    drawEnv.r0 = 0;
    drawEnv.g0 = 0;
    drawEnv.b0 = 0;
    rect.x = 0;
    rect.y = 0x100;
    rect.w = 0x7F;
    rect.h = 0xFF;
    drawEnv.clip = rect;
    drawEnv.ofs[0] = 0;
    drawEnv.ofs[1] = 0x100;
    SetDrawEnv(PRIM_DR_ENV(prim), &drawEnv);
    prim->priority = 0xE;
    prim->drawMode = DRAW_DEFAULT;
    prim = prim->next;
    prim->priority = 0x11;
    prim->drawMode = DRAW_UNK_800;
    prim = self->ext.prim;
    self->rotate += ROT(22.5);
    if (D_us_80180848 & 4) {
        PrimDecreaseBrightness(prim, 4);
    } else {
        brightness = (rcos(self->rotate) * 0x80) >> 12;
        prim->g2 = abs(brightness);
        LOW(prim->r3) = LOW(prim->r2);
    }
    if (!(D_us_80180848 & 4) && !(g_Timer & 3)) {
        entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (entity != NULL) {
            CreateEntityFromCurrentEntity(E_UNK_20, entity);
            entity->posX.i.hi = (Random() & 0x3F) + 0xA;
            entity->posY.i.hi = 0xB0;
            entity->zPriority = 0x10;
            entity->params = 0;
        }
    }
}

void func_us_801963D8(Entity* self) {
    s32 params;
    EntityConfig* config;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitParticle);
        params = self->params & 0xF;
        config = &D_us_801808A4[params];
        self->palette = config->palette + PAL_UNK_2E0;
        self->blendMode = config->blendMode;
        self->animSet = config->animSet;
        self->unk5A = config->unk5A;
        self->ext.e_80192998.anim = config->animData;
        self->step = params + 1;
        if (self->params & 0xFF00) {
            self->zPriority = (self->params & 0xFF00) >> 8;
        }
        if (self->params & 0xF0) {
            self->palette = PAL_FLAG(PAL_UNK_19F);
            self->blendMode = BLEND_TRANSP;
            self->facingLeft = 1;
        }
        break;
    case 1:
        if (!self->step_s) {
            self->drawFlags = ENTITY_OPACITY;
            self->opacity = 0x50;
            self->flags &= ~FLAG_POS_CAMERA_LOCKED;
            self->facingLeft = Random() & 1;
            self->velocityX = (Random() << 8) - FIX(0.5);
            self->velocityY = FIX(-1.5);
            self->ext.e_80192998.accelY = -(Random() * 16) - FIX(0.0625);
            self->step_s++;
        }
        MoveEntity();
        self->velocityY += self->ext.e_80192998.accelY;
        self->opacity += 0xFF;
        if (!AnimateEntity(self->ext.e_80192998.anim, self)) {
            DestroyEntity(self);
        }
        break;
    case 2:
        if (!self->step_s) {
            self->velocityY = FIX(-0.25);
            self->step_s++;
        }
        MoveEntity();
        if (!AnimateEntity(self->ext.e_80192998.anim, self)) {
            DestroyEntity(self);
        }
        break;
    case 3:
        if (!self->step_s) {
            self->drawFlags = ENTITY_OPACITY;
            self->opacity = 0xC0;
            self->facingLeft = Random() & 1;
            self->velocityX = (Random() << 8) - FIX(0.5);
            self->velocityY = FIX(-0.75);
            self->ext.e_80192998.accelY = -(Random() * 16) - FIX(0.25);
            self->step_s++;
        }
        MoveEntity();
        self->velocityY += self->ext.e_80192998.accelY;
        self->opacity += 0xFF;
        if (!AnimateEntity(self->ext.e_80192998.anim, self)) {
            DestroyEntity(self);
        }
        break;
    }
}
