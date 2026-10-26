// SPDX-License-Identifier: AGPL-3.0-or-later
#include "bo5.h"

extern EInit g_EInitObtainable;
extern s32 D_us_801806DC;
extern s32 D_us_801B5538;
extern u32 g_CutsceneFlags;
extern u8 D_us_80180C24[];
extern u8 D_us_80180C48[];
extern u8 D_us_80180C5C[];
extern u8 D_us_80180C6C[];
extern u8 D_us_80180C74[];
extern u8 D_us_80180C84[];
extern u8 D_us_80180C90[];
extern u8 D_us_80180C98[];
extern u8 D_us_80180CA8[];
extern u8 D_us_80180CC0[];
extern u8 D_us_80180CCC[];
extern u8 D_us_80180CD4[];
extern s16 D_us_80180CF0[];
extern s16 D_us_80180D00[];
extern u8 D_us_80180D10[];
extern u8 D_us_80180D20[];
extern u16 D_us_80180D30[];

void CutsceneCameraPan(s16 target);

void func_us_801A5F88(Entity* self) {
    Tilemap* tilemap = &g_Tilemap;
    Entity* entity = &PLAYER;
    Entity* end;
    s16 x;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitSpawner);
        break;

    case 1:
        switch (self->step_s) {
        case 0:
            entity = &g_Entities[160];
            end = entity + 32;
            while (entity < end) {
                if (entity->entityId == E_ID(PRIZE_DROP)) {
                    self->ext.bo5Cutscene.prizeDrop = entity;
                    self->step_s++;
                }
                entity++;
            }
            break;
        case 1:
            entity = self->ext.bo5Cutscene.prizeDrop;
            if (entity->entityId != E_ID(PRIZE_DROP)) {
                D_us_801806DC = 0;
                self->step_s++;
                g_CutsceneFlags |= 0x8000;
            }
            break;
        case 2:
            SetStep(2);
            break;
        }
        break;

    case 2:
        g_PauseAllowed = false;
        g_unkGraphicsStruct.pauseEnemies = true;
        g_Player.padSim = PAD_RIGHT;
        if (g_Player.status & PLAYER_STATUS_WOLF_FORM) {
            g_Player.padSim = PAD_WOLF;
        }
        g_Player.demo_timer = 1;
        self->step++;
        break;

    case 3:
        g_Player.padSim = PAD_NONE;
        if (g_Player.status & PLAYER_STATUS_WOLF_FORM) {
            if (g_Timer & 1) {
                g_Player.padSim = PAD_WOLF;
            }
        } else {
            g_Player.padSim = PAD_RIGHT;
            x = entity->posX.i.hi + tilemap->scrollX.i.hi;
            if ((x > 288) && !(g_CutsceneFlags & 1)) {
                g_CutsceneFlags |= 1;
            }
            if (x > 320) {
                g_Player.padSim = PAD_NONE;
                entity->posX.i.hi = 320 - tilemap->scrollX.i.hi;
                self->step++;
            }
            if (x < 256) {
                x = 256;
            }
            CutsceneCameraPan(x);
        }
        g_Player.demo_timer = 1;
        break;

    case 4:
        CutsceneCameraPan(320);
        if (g_CutsceneFlags & 2) {
            self->step++;
        }
        g_Player.padSim = PAD_NONE;
        g_Player.demo_timer = 1;
        break;

    case 5:
        CutsceneCameraPan(256);
        if (g_unkGraphicsStruct.unk14 == 128) {
            g_PauseAllowed = true;
            if (g_unkGraphicsStruct.pauseEnemies) {
                g_unkGraphicsStruct.pauseEnemies = false;
            }
            DestroyEntity(self);
        }
        g_Player.padSim = PAD_NONE;
        g_Player.demo_timer = 1;
        break;
    }
}

void func_us_801A62B4(Entity* self) {
    Tilemap* tilemap = &g_Tilemap;

    if (D_us_801B5538 && (self->step < 13)) {
        SetStep(13);
    }
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitObtainable);
        self->animSet = ANIMSET_OVL(4);
        self->animCurFrame = 1;
        self->unk5A = 0x50;
        self->palette = 0x220;
        self->hitboxState = 0;
        self->posX.i.hi = 448 - tilemap->scrollX.i.hi;
        break;

    case 1:
        if (g_CutsceneFlags & 4) {
            self->step++;
        }
        break;

    case 2:
        self->animCurFrame = 2;
        if (g_CutsceneFlags & 8) {
            self->step++;
        }
        break;

    case 3:
        AnimateEntity(D_us_80180C24, self);
        if (g_CutsceneFlags & 0x10) {
            SetStep(4);
        }
        break;

    case 4:
        AnimateEntity(D_us_80180C48, self);
        if (g_CutsceneFlags & 0x20) {
            SetStep(5);
        }
        break;

    case 5:
        AnimateEntity(D_us_80180C5C, self);
        if (g_CutsceneFlags & 0x40) {
            SetStep(6);
        }
        break;

    case 6:
        AnimateEntity(D_us_80180C6C, self);
        if (g_CutsceneFlags & 0x80) {
            SetStep(7);
        }
        break;

    case 7:
        AnimateEntity(D_us_80180C74, self);
        if (g_CutsceneFlags & 0x100) {
            SetStep(8);
        }
        break;

    case 8:
        AnimateEntity(D_us_80180C84, self);
        if (g_CutsceneFlags & 0x200) {
            SetStep(9);
        }
        break;

    case 9:
        AnimateEntity(D_us_80180C90, self);
        if (g_CutsceneFlags & 0x400) {
            SetStep(10);
        }
        break;

    case 10:
        AnimateEntity(D_us_80180C98, self);
        if (g_CutsceneFlags & 0x800) {
            SetStep(11);
        }
        break;

    case 11:
        AnimateEntity(D_us_80180CA8, self);
        if (g_CutsceneFlags & 0x1000) {
            SetStep(12);
        }
        break;

    case 12:
        AnimateEntity(D_us_80180CC0, self);
        if (g_CutsceneFlags & 0x2000) {
            SetStep(13);
        }
        break;

    case 13:
        if (!AnimateEntity(D_us_80180CCC, self)) {
            self->velocityX = FIX(0.75);
            SetStep(14);
        }
        break;

    case 14:
        AnimateEntity(D_us_80180CD4, self);
        MoveEntity();
        if (self->posX.i.hi > 272) {
            g_CutsceneFlags |= 2;
            DestroyEntity(self);
        }
        break;
    }
}

void func_us_801A666C(Primitive* prim, s16 arg1) {
    prim->x0 = prim->x2 -= arg1;
    prim->x1 = prim->x3 += arg1;
    prim->y0 = prim->y1 -= arg1;
    prim->y2 = prim->y3 += arg1;
}

void func_us_801A66B0(Entity* self, u16 arg1) {
    Primitive* prim;
    s16 primIndex;
    s16* positions;
    u8* uv;
    s32 i;

    if (D_us_801B5538) {
        DestroyEntity(self);
    }
    switch (self->step) {
    case 0:
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 4);
        if (primIndex == -1) {
            break;
        }
        InitializeEntity(g_EInitSpawner);
        prim = &g_PrimBuf[primIndex];
        self->animSet = ANIMSET_OVL(0);
        self->primIndex = primIndex;
        self->flags |= FLAG_HAS_PRIMS;
        if (!arg1) {
            positions = D_us_80180CF0;
            uv = D_us_80180D10;
        } else {
            positions = D_us_80180D00;
            uv = D_us_80180D20;
        }
        for (i = 0; i < 4; i++) {
            prim->tpage = 0x14;
            prim->clut = D_us_80180D30[arg1 * 4 + i];
            prim->x0 = prim->x1 = prim->x2 = prim->x3 = *positions++;
            prim->y0 = prim->y1 = prim->y2 = prim->y3 = *positions++;
            prim->u0 = prim->u2 = *uv++;
            prim->v0 = prim->v1 = *uv++;
            prim->u1 = prim->u3 = *uv++;
            prim->v2 = prim->v3 = *uv++;
            prim->priority = self->zPriority;
            prim->drawMode = DRAW_DEFAULT;
            prim = prim->next;
        }
        self->ext.utimer.t = 0;
        break;

    case 1:
        prim = &g_PrimBuf[self->primIndex];
        if (self->ext.utimer.t & 1) {
            func_us_801A666C(prim, 1);
        }
        if (++self->ext.utimer.t >= 8) {
            self->ext.utimer.t = 0;
            self->step++;
        }
        break;

    case 2:
        prim = &g_PrimBuf[self->primIndex];
        prim = prim->next;
        if (self->ext.utimer.t & 1) {
            func_us_801A666C(prim, 1);
        }
        if (++self->ext.utimer.t >= 8) {
            self->ext.utimer.t = 0;
            self->step++;
        }
        break;

    case 3:
        prim = &g_PrimBuf[self->primIndex];
        prim = prim->next;
        func_us_801A666C(prim->next, 1);
        if (++self->ext.utimer.t >= 8) {
            self->ext.utimer.t = 0;
            self->step++;
        }
        break;

    case 4:
        prim = &g_PrimBuf[self->primIndex];
        prim = prim->next;
        prim = prim->next;
        prim = prim->next;
        func_us_801A666C(prim, 2);
        if (self->ext.utimer.t & 1) {
            prim->y0 = --prim->y1;
            prim->y2 = ++prim->y3;
        }
        if (++self->ext.utimer.t >= 8) {
            self->ext.utimer.t = 0;
            self->step++;
        }
        break;

    case 5:
        if (++self->ext.utimer.t >= 192) {
            self->ext.utimer.t = 0;
            self->step++;
        }
        break;

    case 6:
        prim = &g_PrimBuf[self->primIndex];
        prim = prim->next;
        prim = prim->next;
        prim = prim->next;
        func_us_801A666C(prim, -2);
        if (self->ext.utimer.t & 1) {
            prim->y0 = ++prim->y1;
            prim->y2 = --prim->y3;
        }
        if (++self->ext.utimer.t >= 8) {
            self->ext.utimer.t = 0;
            self->step++;
        }
        break;

    case 7:
        prim = &g_PrimBuf[self->primIndex];
        prim = prim->next;
        func_us_801A666C(prim->next, -1);
        if (++self->ext.utimer.t >= 8) {
            self->ext.utimer.t = 0;
            self->step++;
        }
        break;

    case 8:
        prim = &g_PrimBuf[self->primIndex];
        prim = prim->next;
        if (self->ext.utimer.t & 1) {
            func_us_801A666C(prim, -1);
        }
        if (++self->ext.utimer.t >= 8) {
            self->ext.utimer.t = 0;
            self->step++;
        }
        break;

    case 9:
        prim = &g_PrimBuf[self->primIndex];
        if (self->ext.utimer.t & 1) {
            func_us_801A666C(prim, -1);
        }
        if (++self->ext.utimer.t >= 8) {
            DestroyEntity(self);
        }
        break;
    }
}

void func_801B1D68(Entity* self) { func_us_801A66B0(self, 0); }

void BO5_RicSetDeadPrologue(Entity* self) { func_us_801A66B0(self, 1); }
