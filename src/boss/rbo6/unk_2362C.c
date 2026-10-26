// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rbo6.h"

void EntityCutscene(Entity* self);
extern u32 g_CutsceneFlags;
extern EInit g_EInitInteractable;

void func_us_801A362C(Entity* self) {
    if (D_8003C73C) {
        EntityCutscene(self);
    }
    if (self->entityId) {
        EntityCutscene(self);
    }
}

void func_us_801A367C(Entity* self) {
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
        g_PauseAllowed = false;
        g_unkGraphicsStruct.pauseEnemies = true;
        PLAYER.facingLeft = 0;
        if (g_Status.wornEquipment[1] != ITEM_AXE_LORD_ARMOR) {
            PLAYER.animCurFrame = 0xBF;
        }
        PLAYER.posX.i.hi = 0x70;
        g_Player.padSim = PAD_NONE;
        g_Player.demo_timer = 1;
        break;
    case 1:
        if (g_Status.wornEquipment[1] != ITEM_AXE_LORD_ARMOR) {
            PLAYER.animCurFrame = 0xBF;
        }
        PLAYER.posX.i.hi = 0x70;
        if (g_CutsceneFlags & 2) {
            self->step++;
        }
        g_Player.padSim = PAD_NONE;
        g_Player.demo_timer = 1;
        break;
    case 2:
        g_PauseAllowed = true;
        g_unkGraphicsStruct.pauseEnemies = false;
        g_Entities[E_AFTERIMAGE_1].ext.afterImage.disableFlag = 1;
        DestroyEntity(self);
        break;
    }
}

void func_us_801A37B4(Entity* self) {
    Primitive* prim;
    s16 primIndex;

    switch (self->step) {
    case 0:
        primIndex = g_api.AllocPrimitives(PRIM_G4, 1);
        if (primIndex == -1) {
            break;
        }
        InitializeEntity(g_EInitInteractable);
        prim = &g_PrimBuf[primIndex];
        self->primIndex = primIndex;
        self->flags |= FLAG_HAS_PRIMS;
        prim->x0 = prim->x2 = 0;
        prim->x1 = prim->x3 = 0x100;
        prim->y0 = prim->y1 = 0;
        prim->y2 = prim->y3 = 0xF0;
        PCOL(prim) = 0xFF;
        prim->priority = 0x1F8;
        prim->drawMode = DRAW_UNK_40 | DRAW_TPAGE | DRAW_COLORS | DRAW_TRANSP;
        break;
    case 1:
        self->step++;
        break;
    case 2:
        prim = &g_PrimBuf[self->primIndex];
        PCOL(prim) -= 4;
        if (prim->r0 < 4) {
            DestroyEntity(self);
            g_CutsceneFlags |= 1;
        }
        break;
    }
}

void func_us_801A399C(Entity* self) {
    Primitive* prim;
    s16 primIndex;

    switch (self->step) {
    case 0:
        primIndex = g_api.AllocPrimitives(PRIM_G4, 1);
        if (primIndex == -1) {
            break;
        }
        InitializeEntity(g_EInitInteractable);
        prim = &g_PrimBuf[primIndex];
        self->primIndex = primIndex;
        self->flags |= FLAG_HAS_PRIMS;
        prim->x0 = prim->x2 = 0;
        prim->x1 = prim->x3 = 0x100;
        prim->y0 = prim->y1 = 0;
        prim->y2 = prim->y3 = 0xF0;
        PCOL(prim) = 0;
        prim->priority = 0x80;
        prim->drawMode = DRAW_DEFAULT;
        break;
    case 1:
        if (g_CutsceneFlags & 0x100) {
            prim = &g_PrimBuf[self->primIndex];
            PCOL(prim) = 0xFF;
            prim->drawMode =
                DRAW_UNK_40 | DRAW_TPAGE | DRAW_COLORS | DRAW_TRANSP;
            self->step++;
        }
        break;
    case 2:
        prim = &g_PrimBuf[self->primIndex];
        PCOL(prim) -= 4;
        if (prim->r0 < 4) {
            DestroyEntity(self);
        }
        break;
    }
}

void func_us_801A3BE0(Entity* self) {
    Primitive* prim;
    s16 primIndex;

    switch (self->step) {
    case 0:
        primIndex = g_api.AllocPrimitives(PRIM_G4, 1);
        if (primIndex == -1) {
            break;
        }
        InitializeEntity(g_EInitInteractable);
        prim = &g_PrimBuf[primIndex];
        self->primIndex = primIndex;
        self->flags |= FLAG_HAS_PRIMS;
        prim->x0 = prim->x2 = 0x60;
        prim->x1 = prim->x3 = 0xA0;
        prim->y0 = prim->y1 = 0x40;
        prim->y2 = prim->y3 = 0xC0;
        PCOL(prim) = 0xFF;
        prim->drawMode = DRAW_UNK_40 | DRAW_TPAGE | DRAW_COLORS | DRAW_TRANSP;
        prim->priority = 0x82;
        break;
    case 1:
        prim = &g_PrimBuf[self->primIndex];
        if (g_CutsceneFlags & 4) {
            PCOL(prim) -= 1;
            if (!prim->r0) {
                PCOL(prim) = 0;
                g_CutsceneFlags |= 0x200;
                self->step++;
            }
        }
        break;
    case 2:
        prim = &g_PrimBuf[self->primIndex];
        if (g_CutsceneFlags & 0x80) {
            PCOL(prim)++;
            if (prim->r0 > 0xC0) {
                g_CutsceneFlags |= 0x100;
            }
            if (prim->r0 >= 0xFE) {
                PCOL(prim) = 0;
                prim->drawMode = DRAW_DEFAULT;
                SetStep(3);
                g_api.PlaySfx(SFX_WEAPON_APPEAR);
            }
        }
        break;
    case 3:
        prim = &g_PrimBuf[self->primIndex];
        prim->type = PRIM_G4;
        prim->x0 = prim->x2 = 0;
        prim->x1 = prim->x3 = 0x100;
        prim->y0 = prim->y1 = 0x10;
        prim->y2 = prim->y3 = 0xF0;
        prim->priority = 0x7F;
        prim->drawMode = DRAW_DEFAULT;
        if (self->poseTimer & 1) {
            PGREY_ALT(prim, 0, 0x80);
            PGREY_ALT(prim, 1, 0x80);
            PGREY_ALT(prim, 2, 0x80);
            PGREY_ALT(prim, 3, 0x80);
        } else {
            PGREY_ALT(prim, 0, 0);
            PGREY_ALT(prim, 1, 0);
            PGREY_ALT(prim, 2, 0);
            PGREY_ALT(prim, 3, 0);
        }
        self->poseTimer++;
        if (self->poseTimer >= 9) {
            DestroyEntity(self);
            g_CutsceneFlags |= 0x20;
        }
        break;
    }
}

void func_us_801A4028(Entity* self) {
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
        self->animSet = ANIMSET_OVL(1);
        self->palette = PAL_DRACULA;
        self->unk5A = 0x48;
        self->animCurFrame = 0x35;
        self->drawFlags = ENTITY_SCALEX | ENTITY_SCALEY;
        self->scaleY = self->scaleX = 0x100;
        self->zPriority = 0x81;
        break;
    case 1:
        if (g_CutsceneFlags & 0x80) {
            self->velocityY = FIX(0.5);
            self->step++;
        }
        break;
    case 2:
        self->velocityY -= FIX(0.005859375);
        MoveEntity();
        self->scaleX--;
        self->scaleY--;
        if (g_CutsceneFlags & 0x100) {
            DestroyEntity(self);
        }
        break;
    }
}

void func_us_801A9208_from_bo6(Entity* self) {
    Primitive* prim;
    s16 primIndex;

    switch (self->step) {
    case 0:
        primIndex = g_api.AllocPrimitives(PRIM_G4, 1);
        if (primIndex != -1) {
            InitializeEntity(g_EInitInteractable);
            prim = &g_PrimBuf[primIndex];
            g_unkGraphicsStruct.pauseEnemies = true;
            g_PauseAllowed = false;
            self->primIndex = primIndex;
            self->animSet = 0;
            self->flags |= FLAG_HAS_PRIMS;
            prim->x0 = prim->x2 = 0;
            prim->x1 = prim->x3 = 0x100;
            prim->y0 = prim->y1 = 4;
            prim->y2 = prim->y3 = 0xE8;
            PCOL(prim) = 0x80;
            prim->priority = 0x1F8;
            prim->drawMode =
                DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS | DRAW_TRANSP;
            self->ext.utimer.t = 0;
            g_api.PlaySfx(SFX_WEAPON_APPEAR);
        }
        self->flags |= FLAG_UNK_10000;
        break;
    case 1:
        self->ext.utimer.t++;
        prim = &g_PrimBuf[self->primIndex];
        if (self->ext.utimer.t > 8) {
            self->step++;
            prim->drawMode = DRAW_HIDE;
            DestroyEntity(self);
        } else if (self->ext.utimer.t & 1) {
            prim->drawMode = DRAW_HIDE;
        } else {
            prim->drawMode =
                DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS | DRAW_TRANSP;
        }
        break;
    case 2:
        if (g_CutsceneFlags & 0x100) {
            g_unkGraphicsStruct.unk28 = 0;
            self->ext.utimer.t = 0;
            self->step++;
        }
        break;
    case 3:
        prim = &g_PrimBuf[self->primIndex];
        self->step++;
        PCOL(prim) = 0;
        prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS | DRAW_TRANSP;
        break;
    case 4:
        prim = &g_PrimBuf[self->primIndex];
        PCOL(prim) += 1;
        if (prim->r0 == 0xFF) {
            prim->drawMode = DRAW_COLORS;
            self->step++;
        }
        break;
    case 5:
        prim = &g_PrimBuf[self->primIndex];
        PCOL(prim) -= 4;
        if (prim->r0 < 5) {
            g_PauseAllowed = true;
            g_unkGraphicsStruct.pauseEnemies = false;
            if (g_RoomCount >= 0x737) {
                D_800978B4 = 3;
            } else {
                D_800978B4 = 5;
            }
            g_GameState = Game_Ending;
            g_GameStep = Play_Reset;
            self->step++;
        }
        break;
    }
}

s32 DecreaseBrightness(Primitive* prim, s32 brightnessOffset) {
    s32 newColor;
    s32 i;
    s32 j;
    u8* rgbVal;
    u8* rPtr;
    s32 ret;

    ret = 0;

    rPtr = &prim->r0;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 3; j++) {
            rgbVal = &rPtr[j];
            newColor = *rgbVal;
            newColor += brightnessOffset;
            if (newColor > 0xFF) {
                newColor = 0xFF;
            } else {
                ret |= 1;
            }
            *rgbVal = newColor;
        }
        rPtr += 0xC;
    }
    return ret;
}

void func_us_801A4594(Entity* self) {
    extern s32 D_us_80180914;
    extern u32 D_us_8018091C;
    extern s32 D_us_80180920;
    Primitive* prim;
    s32 intensity;
    s32 result;
    Entity* entity;
    s16 primIndex;

    FntPrint("end_step %x\n", self->step);
    g_Player.demo_timer = 0x80;
    g_unkGraphicsStruct.pauseEnemies = true;
    g_Player.padSim = PAD_NONE;
    g_Player.status |= PLAYER_STATUS_UNK100000;
    g_PauseAllowed = false;
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 0x20);
        if (primIndex == -1) {
            self->step = 0;
            return;
        }
        prim = &g_PrimBuf[primIndex];
        self->primIndex = primIndex;
        self->ext.draculaFinalEnding.prim = prim;
        self->flags |= FLAG_HAS_PRIMS;
        while (prim != NULL) {
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }
        if (g_Player.status & PLAYER_STATUS_MIST_FORM) {
            g_Player.padSim = PAD_MIST;
        } else if (g_Player.status & PLAYER_STATUS_WOLF_FORM) {
            g_Player.padSim = PAD_WOLF;
        } else if (g_Player.status & PLAYER_STATUS_BAT_FORM) {
            g_Player.padSim = PAD_BAT;
        }
        // Fallthrough
    case 1:
        prim = self->ext.draculaFinalEnding.prim;
        prim->type = PRIM_GT4;
        prim->r0 = prim->g0 = prim->b0 = 0;
        LOW(prim->r1) = LOW(prim->r0);
        LOW(prim->r2) = LOW(prim->r0);
        LOW(prim->r3) = LOW(prim->r0);
        prim->tpage = 0x1A;
        prim->clut = 0x2E2;
        prim->u0 = prim->u2 = 0;
        prim->u1 = prim->u3 = 0x3F;
        prim->v0 = prim->v1 = 0xC0;
        prim->v2 = prim->v3 = 0xFF;
        prim->x0 = prim->x2 = 0x80;
        prim->x1 = prim->x3 = 0x80;
        prim->y0 = prim->y1 = 0x80;
        // The original assigns y1 twice, leaving y2 unchanged here.
        prim->y1 = prim->y3 = 0x80;
        prim->priority = 0x90;
        prim->drawMode =
            DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS | DRAW_UNK02 | DRAW_TRANSP;
        prim = prim->next;
        self->ext.draculaFinalEnding.backdrop = prim;
        prim->type = PRIM_G4;
        prim->x0 = prim->x2 = 0;
        prim->x1 = prim->x3 = 0x100;
        prim->y0 = prim->y1 = 0x10;
        prim->y2 = prim->y3 = 0xF0;
        prim->priority = 0x50;
        prim->drawMode = DRAW_HIDE;
        prim = prim->next;
        self->ext.draculaFinalEnding.borders = prim;
        prim->type = PRIM_G4;
        prim->x0 = prim->x2 = 0x40;
        prim->x1 = prim->x3 = 0;
        prim->y0 = prim->y1 = 0x10;
        prim->y2 = prim->y3 = 0xF0;
        prim->priority = 0x90;
        prim->drawMode = DRAW_HIDE;
        prim = prim->next;
        prim->type = PRIM_G4;
        prim->x0 = prim->x2 = 0xC0;
        prim->x1 = prim->x3 = 0x100;
        prim->y0 = prim->y1 = 0x10;
        prim->y2 = prim->y3 = 0xF0;
        prim->priority = 0x90;
        prim->drawMode = DRAW_HIDE;
        prim = prim->next;
        self->ext.draculaFinalEnding.fade = prim;
        prim->type = PRIM_G4;
        prim->x0 = prim->x2 = 0;
        prim->x1 = prim->x3 = 0x100;
        prim->y0 = prim->y1 = 0x10;
        prim->y2 = prim->y3 = 0xF0;
        prim->priority = 0x1FF;
        prim->drawMode = DRAW_HIDE;
        self->step++;
        // Fallthrough
    case 2:
        prim = self->ext.draculaFinalEnding.prim;
        intensity = prim->r0;
        prim->x0 = prim->x2 -= 3;
        prim->x1 = prim->x3 += 3;
        prim->y0 = prim->y1 -= 3;
        prim->y2 = prim->y3 += 3;
        intensity += 8;
        if (intensity > 0x60) {
            intensity = 0x60;
            self->ext.draculaFinalEnding.timer = 0x10;
            g_api.PlaySfx(SFX_WEAPON_APPEAR);
            self->step++;
        }
        prim->g0 = prim->b0 = prim->r0 = intensity;
        LOW(prim->r1) = LOW(prim->r0);
        LOW(prim->r2) = LOW(prim->r0);
        LOW(prim->r3) = LOW(prim->r0);
        break;
    case 3:
        prim = self->ext.draculaFinalEnding.prim;
        if (self->ext.draculaFinalEnding.timer & 1) {
            prim->x0 = prim->x2 -= 1;
            prim->x1 = prim->x3 += 1;
            prim->y0 = prim->y1 -= 1;
            prim->y2 = prim->y3 += 1;
        }
        if (!--self->ext.draculaFinalEnding.timer) {
            self->step++;
        }
        break;
    case 4:
        prim = self->ext.draculaFinalEnding.prim;
        result = PrimDecreaseBrightness(prim, 4);
        if (!result) {
            prim->drawMode = DRAW_HIDE;
            self->step++;
        }
        prim = self->ext.draculaFinalEnding.backdrop;
        prim->r0 += 4;
        prim->g0 += 3;
        prim->b0 += 2;
        LOW(prim->r1) = LOW(prim->r0);
        LOW(prim->r2) = LOW(prim->r0);
        LOW(prim->r3) = LOW(prim->r0);
        prim->drawMode = DRAW_COLORS;
        D_us_80180914 = 1;
        // Fallthrough
    case 5:
        prim = self->ext.draculaFinalEnding.borders;
        intensity = prim->r1;
        prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_TRANSP;
        if (intensity < 0xC0) {
            intensity += 4;
        } else {
            self->step++;
        }
        prim->g1 = prim->b1 = prim->r1 = intensity;
        LOW(prim->r3) = LOW(prim->r1);
        prim = prim->next;
        prim->g1 = prim->b1 = prim->r1 = intensity;
        LOW(prim->r3) = LOW(prim->r1);
        prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_TRANSP;
        if (self->step == 5 && D_us_80180914 < 4 && !(g_Timer & 0xF)) {
            D_us_80180914++;
        }
        break;
    case 6:
        prim = self->ext.draculaFinalEnding.backdrop;
        prim->drawMode = DRAW_COLORS;
        if (prim->r0 < 0xA0) {
            prim->r0 += 4;
        }
        if (prim->g0 < 0x80) {
            prim->g0 += 3;
        }
        // The original blue increment tests the green channel.
        if (prim->g0 < 0x30) {
            prim->b0 += 2;
        }
        LOW(prim->r1) = LOW(prim->r0);
        LOW(prim->r2) = LOW(prim->r0);
        LOW(prim->r3) = LOW(prim->r0);
        result = true;
        prim = self->ext.draculaFinalEnding.borders;
        intensity = prim->r1;
        intensity++;
        prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_TRANSP;
        if (intensity > 0xFF) {
            intensity = 0xFF;
        }
        prim->g1 = prim->b1 = prim->r1 = intensity;
        LOW(prim->r3) = LOW(prim->r1);
        if (prim->x0 < 0x80) {
            result = false;
            prim->x0 = ++prim->x2;
        }
        prim = prim->next;
        prim->g1 = prim->b1 = prim->r1 = intensity;
        LOW(prim->r3) = LOW(prim->r1);
        prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_TRANSP;
        if (prim->x0 > 0x80) {
            result = false;
            prim->x0 = --prim->x2;
        }
        if (result) {
            self->step++;
        }
        break;
    case 7:
        prim = self->ext.draculaFinalEnding.borders;
        result = DecreaseBrightness(prim, 2);
        prim = prim->next;
        result += DecreaseBrightness(prim, 2);
        D_us_80180920 = 0x80 - (prim->r0 >> 1);
        entity = AllocEntity(&g_Entities[64], &g_Entities[256]);
        if (entity != NULL) {
            CreateEntityFromCurrentEntity(E_UNK_32, entity);
            intensity = Random();
            if (intensity < 0x20) {
                intensity += 0x60;
            }
            if (intensity > 0xE0) {
                intensity -= 0x80;
            }
            entity->posX.i.hi = intensity;
            entity->posY.i.hi = 0xF0;
            entity->params = 0;
        }
        if (!result) {
            self->step++;
        }
        break;
    case 8:
        if (PLAYER.posX.i.hi > 0x80) {
            D_us_8018091C = PAD_LEFT;
        } else {
            D_us_8018091C = PAD_RIGHT;
        }
        self->step++;
        // Fallthrough
    case 9:
        g_Player.padSim = D_us_8018091C;
        prim = self->ext.draculaFinalEnding.fade;
        prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_TRANSP;
        result = DecreaseBrightness(prim, 4);
        if (!result) {
            self->step++;
        }
        return;
    case 10:
        prim = self->ext.draculaFinalEnding.fade;
        prim->drawMode = DRAW_DEFAULT;
        result = PrimDecreaseBrightness(prim, 8);
        if (!result) {
            self->step++;
        }
        return;
    case 11:
        g_PauseAllowed = true;
        g_unkGraphicsStruct.pauseEnemies = false;
        if (g_RoomCount >= 0x737) {
            D_800978B4 = 3;
        } else {
            D_800978B4 = 5;
        }
        g_GameState = Game_Ending;
        g_GameStep = Play_Reset;
        self->step++;
        // Fallthrough
    case 12:
        g_PauseAllowed = true;
        g_unkGraphicsStruct.pauseEnemies = false;
        return;
    }
    if (D_us_80180914) {
        if (!(g_Timer & 7)) {
            if (D_us_80180920) {
                g_api.PlaySfxVolPan(SFX_MAGIC_SWITCH, D_us_80180920, 0);
            } else {
                g_api.PlaySfx(SFX_MAGIC_SWITCH);
            }
        }
        if (!(g_Timer & 1)) {
            entity = AllocEntity(&g_Entities[64], &g_Entities[256]);
            if (entity != NULL) {
                CreateEntityFromCurrentEntity(E_UNK_32, entity);
                intensity = Random();
                if (intensity < 0x20) {
                    intensity += 0x60;
                }
                if (intensity > 0xE0) {
                    intensity -= 0x80;
                }
                entity->posX.i.hi = intensity;
                entity->posY.i.hi = 0xF0;
                entity->params = 0;
            }
        }
    }
}

void func_us_801A4F14(Entity* self) {
    extern EInit g_EInitParticle;
    extern s32 D_us_80180914;
    s32 random;
    s32 range;
    Primitive* prim;
    s32 i;
    s16* history;
    s32 x, y;
    s16 glowY;
    s16 left, right;
    s32 width;
    s16 primIndex;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitParticle);
        self->animCurFrame = 0;
        random = Random() % D_us_80180914;
        range = random + 2;
        self->hitboxWidth = range;
        self->velocityY = FIX(-1.5) - ((Random() % (random + 3)) << 17);
        self->ext.draculaFinalFlame.accelerationY =
            FIX(-0.0625) - (Random() % range) * FIX(0.1875);
        self->opacity = (Random() % ++random) * 8 + 0x20;
        if (random >= D_us_80180914 / 2) {
            self->zPriority = 0x90;
        } else {
            self->zPriority = 0x54;
        }
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 7);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.draculaFinalFlame.prim = prim;
        self->flags |= FLAG_HAS_PRIMS;
        prim->tpage = 0x1A;
        prim->clut = 0x2EC;
        prim->u1 = prim->u3 = 0x40;
        prim->v0 = prim->v1 = 0xC0;
        prim->u0 = prim->u2 = 0;
        prim->v2 = prim->v3 = 0xE0;
        prim->r0 = prim->g0 = prim->b0 = self->opacity;
        LOW(prim->r1) = LOW(prim->r0);
        LOW(prim->r2) = LOW(prim->r0);
        LOW(prim->r3) = LOW(prim->r0);
        prim->priority = self->zPriority;
        prim->drawMode =
            DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS | DRAW_UNK02 | DRAW_TRANSP;
        prim = prim->next;
        for (i = 0; i < 4; i++) {
            prim->tpage = 0x1A;
            prim->clut = 0x2EC;
            prim->u0 = prim->u2 = 0;
            prim->u1 = prim->u3 = 0x40;
            prim->v0 = prim->v1 = 0xE0;
            prim->v2 = prim->v3 = 0xE2;
            prim->r0 = prim->g0 = prim->b0 = self->opacity;
            LOW(prim->r1) = LOW(prim->r0);
            LOW(prim->r2) = LOW(prim->r0);
            LOW(prim->r3) = LOW(prim->r0);
            prim->priority = self->zPriority + 1;
            prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS |
                             DRAW_UNK02 | DRAW_TRANSP;
            prim = prim->next;
        }
        prim->u1 = prim->u3 = 0x40;
        prim->tpage = 0x1A;
        prim->clut = 0x2EC;
        prim->u0 = prim->u2 = 0;
        prim->v0 = prim->v1 = 0xE0;
        prim->v2 = prim->v3 = 0xFF;
        prim->r0 = prim->g0 = prim->b0 = self->opacity;
        LOW(prim->r1) = LOW(prim->r0);
        LOW(prim->r2) = LOW(prim->r0);
        LOW(prim->r3) = LOW(prim->r0);
        prim->priority = self->zPriority;
        prim->drawMode =
            DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS | DRAW_UNK02 | DRAW_TRANSP;
        prim = prim->next;
        self->ext.draculaFinalFlame.glow = prim;
        prim->u1 = prim->u3 = 0x3F;
        prim->tpage = 0x1A;
        prim->clut = 0x2EC;
        prim->u0 = prim->u2 = 0;
        prim->v0 = prim->v1 = 0xC0;
        prim->v2 = prim->v3 = 0xFF;
        prim->r0 = prim->g0 = prim->b0 = self->opacity + 0x20;
        LOW(prim->r1) = LOW(prim->r0);
        LOW(prim->r2) = LOW(prim->r0);
        LOW(prim->r3) = LOW(prim->r0);
        prim->priority = self->zPriority;
        prim->drawMode = DRAW_UNK_40 | DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS |
                         DRAW_UNK02 | DRAW_TRANSP;
        if (self->hitboxWidth < 4) {
            prim->drawMode = DRAW_HIDE;
        }
        history = self->ext.draculaFinalFlame.yHistory;
        for (i = 0; i < 6; i++) {
            *history++ = self->posY.i.hi;
        }
        break;
    case 1:
        MoveEntity();
        self->velocityY += self->ext.draculaFinalFlame.accelerationY;
        break;
    }
    history = &self->ext.draculaFinalFlame.yHistory[5];
    for (i = 0; i < 5; i++, history--) {
        *history = history[-1];
    }
    history = self->ext.draculaFinalFlame.yHistory;
    *history = self->posY.i.hi;
    width = self->hitboxWidth;
    prim = self->ext.draculaFinalFlame.prim;
    x = self->posX.i.hi;
    y = self->posY.i.hi - width;
    glowY = y - width;
    left = x - width;
    right = x + width;
    prim->y0 = prim->y1 = y;
    prim->x0 = left;
    prim->x1 = right;
    prim = self->ext.draculaFinalFlame.glow;
    prim->x0 = x - width * 2;
    prim->x1 = x + width * 2;
    prim->y0 = prim->y1 = glowY;
    prim = self->ext.draculaFinalFlame.prim;
    for (i = 0; i < 5; i++) {
        y = *history++;
        prim->x2 = x - width;
        prim->x3 = x + width;
        prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS | DRAW_TRANSP;
        prim->y2 = prim->y3 = y;
        prim = prim->next;
        prim->y0 = prim->y1 = y;
        prim->x0 = x - width;
        prim->x1 = x + width;
    }
    y += self->hitboxWidth;
    prim->x2 = x - width;
    prim->x3 = x + width;
    prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS | DRAW_TRANSP;
    prim->y2 = prim->y3 = y;
    prim = self->ext.draculaFinalFlame.glow;
    prim->x2 = x - width * 2;
    prim->x3 = x + width * 2;
    prim->y2 = prim->y3 = y + self->hitboxWidth * 2;
    if (y < 0x10) {
        DestroyEntity(self);
    }
}
