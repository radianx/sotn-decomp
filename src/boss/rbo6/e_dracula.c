// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rbo6.h"
#include <scratchpad.h>

void func_us_8019DB9C(Entity* self) {
    extern EInit g_EInitDraculaLvl98;
    // !FAKE: Alias of g_Entities[81] preserves the PS1 address reuse.
#ifdef VERSION_PC
#define D_80076F54 (&g_Entities[81])
#else
    extern Entity D_80076F54[];
#endif
    extern s32 g_CutsceneFlags;
    extern s32 D_us_801806E4;
    extern s32 D_us_801806E8;
    extern s32 D_us_801806EC;
    extern s32 D_us_801806F0;
    extern s32 D_us_801806F4;
    extern s32 D_us_801806F8;
    extern s32 D_us_801806FC;
    extern s32 D_us_80180700;
    extern s32 D_us_80180704;
    extern u8 D_us_80180708[];
    extern u8 D_us_80180710[];
    extern u8 D_us_801807A0[];
    extern u16 D_us_80180830[];
    s16 angle;
    s32 i; // Also used for horizontal displacement to preserve register reuse.
    Entity* entity;
    s32 deltaY;

    if ((self->hitFlags & 3) && !(Random() & 7)) {
        if (Random() & 1) {
            g_api.PlaySfx(SFX_DRACULA_PAIN_A);
        } else {
            g_api.PlaySfx(SFX_DRACULA_PAIN_B);
        }
    }
    if ((self->flags & FLAG_DEAD) && (self->step != 12)) {
        SetStep(12);
    }
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitDraculaLvl98);
        self->zPriority = 0x80;
        self->hitboxOffY = -4;
        entity = D_80076F54;
        for (i = 0; i < 5; i++, entity++) {
            CreateEntityFromCurrentEntity(E_UNK_19, entity);
            entity->zPriority = self->zPriority + 1;
            entity->params = i;
        }
        CreateEntityFromCurrentEntity(E_UNK_1A, &D_80076F54[5]);
        g_Entities[86].params = 0;
        g_Entities[86].zPriority = self->zPriority + 3;
        CreateEntityFromCurrentEntity(E_UNK_1A, &D_80076F54[7]);
        g_Entities[88].params = 1;
        g_Entities[88].zPriority = self->zPriority + 3;
        self->nextPart = &D_80076F54[6];
        self->parent = NULL;
        CreateEntityFromCurrentEntity(E_UNK_18, &D_80076F54[9]);
        g_Entities[90].zPriority = self->zPriority + 1;
        entity = &D_80076F54[10];
        for (i = 0; i < 3; i++, entity += 6) {
            CreateEntityFromCurrentEntity(E_UNK_1C, entity);
            entity->params = i;
            entity->zPriority = self->zPriority + 6;
        }
        CreateEntityFromCurrentEntity(E_UNK_1E, &g_Entities[109]);
        g_Entities[109].zPriority = self->zPriority;
        SetStep(1);
        /* fallthrough */
    case 1:
        self->hitboxState = 0;
        D_us_801806E8 = 1;
        switch (self->step_s) {
        case 0:
            self->drawFlags = ENTITY_OPACITY;
            self->opacity = 0;
            self->animCurFrame = 1;
            if (g_CutsceneFlags & 0x20) {
                self->ext.draculaFinalBoss.timer = 128;
                self->step_s++;
            }
            break;
        case 1:
            AnimateEntity(D_us_80180708, self);
            if (!--self->ext.draculaFinalBoss.timer) {
                self->step_s++;
            }
            break;
        case 2:
            AnimateEntity(D_us_80180708, self);
            self->opacity++;
            if (self->opacity >= 128) {
                self->drawFlags = ENTITY_DEFAULT;
                self->step_s++;
            }
            break;
        case 3:
            AnimateEntity(D_us_80180708, self);
            if (g_CutsceneFlags & 2) {
                g_api.TimeAttackController(
                    TIMEATTACK_EVENT_UNUSED_28, TIMEATTACK_SET_VISITED);
                g_api.PlaySfx(SFX_DRACULA_BEHOLD_MY_TRUE_FORM);
                SetStep(2);
            }
            break;
        }
        break;
    case 12:
        switch (self->step_s) {
        case 0:
            g_api.TimeAttackController(
                TIMEATTACK_EVENT_UNUSED_28, TIMEATTACK_SET_RECORD);
            self->palette = PAL_DRACULA;
            self->hitboxState = 0;
            D_us_801806E4 |= 1;
            self->flags &= ~0xF;
            self->step_s++;
            break;
        case 1:
            CreateEntityFromCurrentEntity(E_UNK_27, &g_Entities[200]);
            g_Entities[200].params = 1;
            g_unkGraphicsStruct.unk28 = 0xFF;
            g_Entities[200].flags |= FLAG_UNK_10000;
            self->step_s++;
            break;
        case 2:
            i = 128 - self->posX.i.hi;
            deltaY = 138 - self->posY.i.hi;
            angle = ratan2(deltaY, i);
            self->velocityX = (rcos(angle) * FIX(0.5)) >> 12;
            self->velocityY = (rsin(angle) * FIX(0.5)) >> 12;
            MoveEntity();
            if (SquareRoot0(i * i + deltaY * deltaY) < 3) {
                self->step_s++;
            }
            break;
        case 3:
            self->velocityX = 0;
            self->velocityY = 0;
            D_us_801806E4 |= 2;
            self->step_s++;
            break;
        case 4:
            break;
        }
        break;
    case 2:
        AnimateEntity(D_us_80180708, self);
        D_us_801806E8 = 1;
        self->hitboxState = 0;
        switch (self->step_s) {
        case 0:
            self->velocityY = FIX(6);
            self->step_s++;
            /* fallthrough */
        case 1:
            MoveEntity();
            self->velocityY -= FIX(0.25);
            if (self->posY.i.hi < -96) {
                SetStep(3);
            }
            break;
        }
        break;
    case 3:
        AnimateEntity(D_us_801807A0, self);
        D_us_801806E8 = 0;
        self->hitboxState = 2;
        switch (self->step_s) {
        case 0:
            self->velocityY = FIX(1.25);
            self->posY.i.hi = -80;
            self->velocityX = 0;
            self->posX.i.hi = 128;
            self->zPriority = 0x80;
            self->ext.draculaFinalBoss.timer = 0;
            self->step_s++;
            /* fallthrough */
        case 1:
            if (!(self->ext.draculaFinalBoss.timer & 0x3F)) {
                g_api.PlaySfx(SFX_DRACULA_FLY_IN);
            }
            self->ext.draculaFinalBoss.timer++;
            MoveEntity();
            if (self->posY.i.hi > 144) {
                SetStep(4);
            }
            break;
        }
        break;
    case 4:
        if (!self->step_s) {
            self->ext.draculaFinalBoss.timer = 64;
            self->step_s++;
        }
        AnimateEntity(D_us_801807A0, self);
        D_us_801806E8 = 0;
        self->hitboxState = 2;
        MoveEntity();
        self->ext.draculaFinalBoss.bobAngle += 0x20;
        self->velocityY =
            (rcos(self->ext.draculaFinalBoss.bobAngle) * FIX(0.5)) >> 12;
        if (!--self->ext.draculaFinalBoss.timer) {
            SetStep(D_us_80180830[self->ext.draculaFinalBoss.attackIndex]);
            self->ext.draculaFinalBoss.attackIndex =
                (self->ext.draculaFinalBoss.attackIndex + 1) & 3;
        }
        break;
    case 5:
        AnimateEntity(D_us_801807A0, self);
        D_us_801806E8 = 0;
        self->hitboxState = 2;
        MoveEntity();
        self->ext.draculaFinalBoss.bobAngle += 0x20;
        self->velocityY =
            (rcos(self->ext.draculaFinalBoss.bobAngle) * FIX(0.5)) >> 12;
        switch (self->step_s) {
        case 0:
            D_us_801806EC = 1;
            CreateEntityFromCurrentEntity(E_UNK_20, &g_Entities[129]);
            g_Entities[129].zPriority = self->zPriority + 3;
            self->step_s++;
            /* fallthrough */
        case 1:
            if (D_us_801806EC == 2) {
                self->step_s++;
            }
            break;
        case 2:
            D_us_801806EC = 3;
            g_api.PlaySfx(SFX_DRACULA_SQUISH_GRUNT);
            self->step_s++;
            /* fallthrough */
        case 3:
            if (D_us_801806EC == 5) {
                self->ext.draculaFinalBoss.timer = 160;
                self->step_s++;
            }
            break;
        case 4:
            if (!--self->ext.draculaFinalBoss.timer) {
                D_us_801806F0++;
                if (D_us_801806F0 >= 8) {
                    D_us_801806F0 = 0;
                }
                D_us_801806EC = 0;
                SetStep(6);
            }
            break;
        }
        break;
    case 6:
        if (!self->step_s) {
            self->velocityX = 0;
            self->velocityY = FIX(1);
            g_api.PlaySfx(SFX_DRACULA_LAUGH_A);
            self->step_s++;
        }
        AnimateEntity(D_us_801807A0, self);
        D_us_801806E8 = 0;
        self->hitboxState = 2;
        MoveEntity();
        self->velocityY -= FIX(0.0625);
        if (self->posY.i.hi < -64) {
            SetStep(7);
        }
        break;
    case 7:
        if (!self->step_s) {
            self->posX.i.hi = 128;
            self->posY.i.hi = -64;
            self->velocityX = 0;
            self->velocityY = FIX(3);
            self->zPriority = 0x80;
            self->step_s++;
        }
        AnimateEntity(D_us_80180708, self);
        D_us_801806E8 = 1;
        self->hitboxState = 0;
        MoveEntity();
        self->velocityY -= self->velocityY >> 6;
        if (self->posY.i.hi > 112) {
            SetStep(8);
        }
        break;
    case 8:
        if (!self->step_s) {
            D_us_801806F4 = 0;
            self->step_s++;
        }
        D_us_801806E8 = 1;
        self->hitboxState = 0;
        if (!AnimateEntity(D_us_80180710, self)) {
            SetStep(2);
        }
        if (LOW(self->pose) == 2) {
            CreateEntityFromEntity(E_UNK_23, self, &g_Entities[132]);
            g_Entities[132].zPriority = self->zPriority + 1;
        }
        if (LOW(self->pose) == 3) {
            g_api.PlaySfx(SFX_DRACULA_MONSTER_MAGIC_ATTACK);
            D_us_801806F4 = 1;
        }
        break;
    case 9:
        AnimateEntity(D_us_801807A0, self);
        D_us_801806E8 = 0;
        self->hitboxState = 2;
        MoveEntity();
        self->ext.draculaFinalBoss.bobAngle += 0x20;
        self->velocityY =
            (rcos(self->ext.draculaFinalBoss.bobAngle) * FIX(0.5)) >> 12;
        switch (self->step_s) {
        case 0:
            self->ext.draculaFinalBoss.attacksRemaining = 4;
            self->step_s++;
            /* fallthrough */
        case 1:
            if (PLAYER.posX.i.hi < 128) {
                D_us_801806F8 = 1;
                self->velocityX = FIX(-0.5);
            } else {
                D_us_801806F8 = 2;
                self->velocityX = FIX(0.5);
            }
            self->ext.draculaFinalBoss.timer = 40;
            self->step_s++;
            /* fallthrough */
        case 2:
            self->velocityX -= self->velocityX >> 4;
            if (!--self->ext.draculaFinalBoss.timer) {
                if (D_us_801806F8 == 1) {
                    self->velocityX = FIX(2);
                } else {
                    self->velocityX = FIX(-2);
                }
                self->step_s++;
            }
            break;
        case 3:
            self->velocityX -= self->velocityX >> 4;
            if (D_us_801806F8 == 3) {
                self->step_s++;
            }
            break;
        case 4:
            i = 128 - self->posX.i.hi;
            if (i > 0) {
                self->velocityX = FIX(1.125);
            }
            if (i < 0) {
                self->velocityX = FIX(-1.125);
            }
            if (abs(i) < 3) {
                self->velocityX = 0;
                if (!--self->ext.draculaFinalBoss.attacksRemaining) {
                    D_us_801806F8 = 0;
                    SetStep(4);
                } else {
                    self->step_s = 1;
                }
            }
            break;
        }
        break;
    case 10:
        AnimateEntity(D_us_801807A0, self);
        D_us_801806E8 = 0;
        self->hitboxState = 2;
        MoveEntity();
        self->ext.draculaFinalBoss.bobAngle += 0x20;
        self->velocityY =
            (rcos(self->ext.draculaFinalBoss.bobAngle) * FIX(0.5)) >> 12;
        switch (self->step_s) {
        case 0:
            D_us_801806FC = 1;
            self->step_s++;
            /* fallthrough */
        case 1:
            if (D_us_801806FC == 4) {
                D_us_801806FC = 0;
                SetStep(4);
            }
            break;
        }
        break;
    case 11:
        AnimateEntity(D_us_801807A0, self);
        D_us_801806E8 = 0;
        self->hitboxState = 2;
        switch (self->step_s) {
        case 0:
            D_us_80180700 = 1;
            self->step_s++;
            /* fallthrough */
        case 1:
            if (D_us_80180700 == 4) {
                self->ext.draculaFinalBoss.timer = 64;
                self->step_s++;
            }
            break;
        case 2:
            if (!(self->ext.draculaFinalBoss.timer & 0xF)) {
                entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
                if (entity != NULL) {
                    CreateEntityFromCurrentEntity(E_UNK_24, entity);
                    entity->zPriority = self->zPriority + 8;
                }
            }
            if (!--self->ext.draculaFinalBoss.timer) {
                self->ext.draculaFinalBoss.timer = 64;
                self->step_s++;
            }
            break;
        case 3:
            if (!--self->ext.draculaFinalBoss.timer) {
                D_us_80180700 = 5;
                self->step_s++;
            }
            break;
        case 4:
            D_us_80180700 = 0;
            SetStep(4);
            break;
        }
        break;
    case 255:
        FntPrint("charal %x\n", self->animCurFrame);
        if (g_pads[1].pressed & PAD_SQUARE) {
            if (!self->params) {
                self->animCurFrame++;
                self->params |= 1;
            } else {
                break;
            }
        } else {
            self->params = 0;
        }
        if (g_pads[1].pressed & PAD_CIRCLE) {
            if (!self->step_s) {
                self->animCurFrame--;
                self->step_s |= 1;
            }
        } else {
            self->step_s = 0;
        }
        break;
    }
    D_us_80180704 = self->palette;
}

void func_us_8019EADC(Entity* self) {
    extern u16 D_us_80180540;
    extern s32 D_us_801806E4;
    extern s32 D_us_801806E8;
    extern s32 D_us_801806EC;
    extern s32 D_us_801806F8;
    extern s32 D_us_80180704;
    extern u8 D_us_8018074C[];
    extern u8 D_us_80180758[];
    extern u8 D_us_80180764[];
    extern u8 D_us_80180770[];

    self->posX.i.hi = g_Entities[E_BOSS_WEAPON].posX.i.hi;
    self->posY.i.hi = g_Entities[E_BOSS_WEAPON].posY.i.hi;
    if (!self->params) {
        self->posX.i.hi -= 52;
        self->posY.i.hi += 16;
    } else {
        self->posX.i.hi += 59;
        self->posY.i.hi += 24;
    }
    self->palette = D_us_80180704;
    if ((D_us_801806E4 & 1) && (self->step != 16)) {
        SetStep(16);
    }
    switch (self->step) {
    case 0:
        InitializeEntity(&D_us_80180540);
        self->facingLeft = self->params;
        CreateEntityFromCurrentEntity(E_UNK_1B, self + 1);
        (self + 1)->params = self->params;
        (self + 1)->zPriority = self->zPriority + 1;
        /* fallthrough */
    case 1:
        self->animCurFrame = 0xC;
        if (D_us_801806EC == 1) {
            SetStep(2);
        }
        if (D_us_801806F8 == self->params + 1) {
            SetStep(3);
        }
        break;
    case 2:
        switch (self->step_s) {
        case 0:
            self->animCurFrame = 0xC;
            if (D_us_801806EC == 3) {
                self->step_s++;
            }
            break;
        case 1:
            if (LOW(self->pose) == 3) {
                D_us_801806EC = 4;
            }
            if (!AnimateEntity(D_us_8018074C, self)) {
                D_us_801806EC = 5;
                SetSubStep(2);
            }
            break;
        case 2:
            if (!AnimateEntity(D_us_80180770, self)) {
                SetStep(1);
            }
            break;
        }
        break;
    case 3:
        switch (self->step_s) {
        case 0:
            if (!AnimateEntity(D_us_80180758, self)) {
                SetSubStep(1);
            }
            if (LOW(self->pose) == 2) {
                PlaySfxPositional(SFX_FIREBALL_SHOT_C);
            }
            break;
        case 1:
            if (!AnimateEntity(D_us_80180770, self)) {
                D_us_801806F8 = 3;
                SetStep(1);
            }
            break;
        }
        break;
    case 8:
        if (!AnimateEntity(D_us_80180764, self)) {
            self->pose = 0;
            self->poseTimer = 0;
        }
        break;
    case 16:
        switch (self->step_s) {
        case 0:
            self->pose = 0x10 - self->animCurFrame;
            self->step_s++;
            /* fallthrough */
        case 1:
            if (!AnimateEntity(D_us_80180770, self)) {
                self->pose = 0;
                self->poseTimer = 0;
                self->step_s++;
            }
            break;
        }
        break;
    }
    if (D_us_801806E8) {
        self->animCurFrame = 0;
        self->hitboxState = 0;
    }
}

void func_us_8019EE30(Entity* self) {
    extern EInit D_us_80180558;
    extern s32 D_us_801806E4;
    extern s32 D_us_801806E8;
    extern s32 D_us_801806EC;
    extern s32 D_us_801806F8;
    extern s32 D_us_80180704;
    extern u8 D_us_8018072C[];
    extern u8 D_us_80180734[];
    extern u8 D_us_80180744[];
    extern s16 D_us_80180808[][2];
    extern u8 D_us_80180838[];
    extern u8 D_us_80180854[];
    Entity* entity;
    s32 i;
    s32 frame;
    u8* hitbox;

    self->palette = D_us_80180704;
    if ((D_us_801806E4 & 1) && (self->step != 16)) {
        SetStep(16);
    }
    switch (self->step) {
    case 0:
        InitializeEntity(D_us_80180558);
        self->parent = &g_Entities[E_BOSS_WEAPON];
        self->facingLeft = self->params;
        if (!self->params) {
            self->nextPart = self + 2;
        } else {
            self->nextPart = &g_Entities[E_BOSS_WEAPON];
        }
        /* fallthrough */
    case 1:
        AnimateEntity(D_us_8018072C, self);
        if (D_us_801806EC == 1) {
            SetStep(2);
        }
        if (D_us_801806F8 == self->params + 1) {
            self->animCurFrame = 0xA;
        }
        break;
    case 2:
        switch (self->step_s) {
        case 0:
            for (i = 0; i < 2; i++) {
                entity = AllocEntity(&g_Entities[144], &g_Entities[152]);
                if (entity != NULL) {
                    CreateEntityFromCurrentEntity(E_UNK_1F, entity);
                    entity->params = self->params;
                    entity->zPriority = self->zPriority + 4;
                }
            }
            self->animCurFrame = 9;
            self->step_s++;
            /* fallthrough */
        case 1:
            if (D_us_801806EC == 3) {
                SetSubStep(2);
            }
            break;
        case 2:
            AnimateEntity(D_us_80180734, self);
            if (D_us_801806EC == 5) {
                SetSubStep(3);
            }
            break;
        case 3:
            if (!AnimateEntity(D_us_80180744, self)) {
                SetStep(1);
            }
            break;
        }
        break;
    case 16:
        if (!self->step_s) {
            self->hitboxState = 0;
            self->animCurFrame = 9;
            self->step_s++;
        }
        break;
    }
    self->posX.i.hi = (self - 1)->posX.i.hi;
    self->posY.i.hi = (self - 1)->posY.i.hi;
    frame = (self - 1)->animCurFrame - 0xC;
    if (frame < 0) {
        frame = 0;
    }
    if (frame >= 5) {
        frame = 4;
    }
    if (!self->params) {
        self->posX.i.hi += D_us_80180808[frame][0];
    } else {
        self->posX.i.hi -= D_us_80180808[frame][0];
    }
    self->posY.i.hi += D_us_80180808[frame][1];
    hitbox = D_us_80180838;
    hitbox += D_us_80180854[self->animCurFrame] * 4;
    self->hitboxOffX = (s8)*hitbox++;
    self->hitboxOffY = (s8)*hitbox++;
    self->hitboxWidth = *hitbox++;
    self->hitboxHeight = *hitbox++;
    if (D_us_801806E8) {
        self->animCurFrame = 0;
        self->hitboxState = 0;
    } else {
        self->hitboxState = 3;
    }
}

void func_us_8019F1CC(Entity* self) {
    extern EInit D_us_8018054C;
    extern s32 D_us_801806E4;
    extern s32 D_us_801806E8;
    extern s32 D_us_801806FC;
    extern s32 D_us_80180700;
    extern s32 D_us_80180704;
    extern u8 D_us_80180780[];
    extern u8 D_us_80180788[];
    extern u8 D_us_80180794[];
    extern s16 D_us_8018081C[][2];
    extern s16 D_us_80180828[];
    Entity* entity;
    s32 deltaX, deltaY;
    Entity* segment;
    s32 anchorX, anchorY;
    s32 i;
    s16 angle;

    self->palette = D_us_80180704;
    if ((D_us_801806E4 & 1) && (self->step != 16)) {
        SetStep(16);
    }
    switch (self->step) {
    case 0:
        entity = self + 1;
        InitializeEntity(D_us_8018054C);
        for (i = 0; i < 5; i++, entity++) {
            CreateEntityFromCurrentEntity(E_UNK_1D, entity);
            entity->zPriority = self->zPriority - i;
        }
        /* fallthrough */
    case 1:
        AnimateEntity(D_us_80180780, self);
        deltaX = g_Entities[E_BOSS_WEAPON].posX.i.hi +
                 D_us_8018081C[self->params][0];
        deltaY = g_Entities[E_BOSS_WEAPON].posY.i.hi +
                 D_us_8018081C[self->params][1];
        self->posX.i.hi = deltaX;
        self->posY.i.hi = deltaY;
        self->zPriority = g_Entities[E_BOSS_WEAPON].zPriority + 2;
        self->hitboxState = 0;
        if (D_us_801806FC == self->params + 1) {
            self->zPriority = g_Entities[E_BOSS_WEAPON].zPriority + 6;
            SetStep(2);
        }
        if (D_us_80180700 == 1) {
            self->zPriority = g_Entities[E_BOSS_WEAPON].zPriority + 6;
            SetStep(3);
        }
        break;
    case 2:
        self->hitboxState = 3;
        switch (self->step_s) {
        case 0:
            deltaX = PLAYER.posX.i.hi - self->posX.i.hi;
            deltaY = PLAYER.posY.i.hi - self->posY.i.hi;
            angle = ratan2(deltaY, deltaX);
            self->velocityX = (rcos(angle) * FIX(4)) >> 12;
            self->velocityY = (rsin(angle) * FIX(4)) >> 12;
            PlaySfxPositional(SFX_DRACULA_MONSTER_ROAR);
            self->step_s++;
            /* fallthrough */
        case 1:
            MoveEntity();
            if (!AnimateEntity(D_us_80180788, self)) {
                SetSubStep(2);
            }
            break;
        case 2:
            AnimateEntity(D_us_80180794, self);
            MoveEntity();
            deltaX = g_Entities[E_BOSS_WEAPON].posX.i.hi +
                     D_us_8018081C[self->params][0];
            deltaY = g_Entities[E_BOSS_WEAPON].posY.i.hi +
                     D_us_8018081C[self->params][1];
            deltaX -= self->posX.i.hi;
            deltaY -= self->posY.i.hi;
            angle = ratan2(deltaY, deltaX);
            self->velocityX = rcos(angle) * 32;
            self->velocityY = rsin(angle) * 32;
            if ((abs(deltaX) < 3) && (abs(deltaY) < 3)) {
                D_us_801806FC++;
                SetStep(1);
            }
            break;
        }
        break;
    case 3:
        switch (self->step_s) {
        case 0:
            angle = D_us_80180828[self->params];
            self->velocityX = (rcos(angle) * FIX(4)) >> 12;
            self->velocityY = (rsin(angle) * FIX(4)) >> 12;
            self->step_s++;
            /* fallthrough */
        case 1:
            MoveEntity();
            if (!AnimateEntity(D_us_80180788, self)) {
                g_api.PlaySfx(SFX_WEAPON_APPEAR);
                entity = AllocEntity(&g_Entities[192], &g_Entities[256]);
                if (entity != NULL) {
                    CreateEntityFromCurrentEntity(E_UNK_25, entity);
                    entity->ext.succubus.real = self;
                    entity->zPriority = self->zPriority + 1;
                }
                D_us_80180700++;
                self->step_s++;
            }
            break;
        case 2:
            if (D_us_80180700 == 5) {
                self->step_s++;
            }
            break;
        case 3:
            AnimateEntity(D_us_80180794, self);
            MoveEntity();
            deltaX = g_Entities[E_BOSS_WEAPON].posX.i.hi +
                     D_us_8018081C[self->params][0];
            deltaY = g_Entities[E_BOSS_WEAPON].posY.i.hi +
                     D_us_8018081C[self->params][1];
            deltaX -= self->posX.i.hi;
            deltaY -= self->posY.i.hi;
            angle = ratan2(deltaY, deltaX);
            self->velocityX = rcos(angle) * 40;
            self->velocityY = rsin(angle) * 40;
            if ((abs(deltaX) < 3) && (abs(deltaY) < 3)) {
                SetStep(1);
            }
            break;
        }
        break;
    case 16:
        switch (self->step_s) {
        case 0:
            self->hitboxState = 0;
            self->animCurFrame = 0x12;
            MoveEntity();
            deltaX = g_Entities[E_BOSS_WEAPON].posX.i.hi +
                     D_us_8018081C[self->params][0];
            deltaY = g_Entities[E_BOSS_WEAPON].posY.i.hi +
                     D_us_8018081C[self->params][1];
            deltaX -= self->posX.i.hi;
            deltaY -= self->posY.i.hi;
            angle = ratan2(deltaY, deltaX);
            self->velocityX = rcos(angle) * 40;
            self->velocityY = rsin(angle) * 40;
            if ((abs(deltaX) < 3) && (abs(deltaY) < 3)) {
                self->zPriority = g_Entities[E_BOSS_WEAPON].zPriority + 2;
                self->step_s++;
            }
            break;
        case 1:
            deltaX = g_Entities[E_BOSS_WEAPON].posX.i.hi +
                     D_us_8018081C[self->params][0];
            deltaY = g_Entities[E_BOSS_WEAPON].posY.i.hi +
                     D_us_8018081C[self->params][1];
            self->posX.i.hi = deltaX;
            self->posY.i.hi = deltaY;
            break;
        }
        break;
    }
    entity = self + 5;
    i = 0;
    anchorX = (D_us_8018081C[self->params][0] << 16) +
              g_Entities[E_BOSS_WEAPON].posX.val;
    anchorY = (D_us_8018081C[self->params][1] << 16) +
              g_Entities[E_BOSS_WEAPON].posY.val;
    do {
        segment = entity - 1;
        anchorX = (anchorX + segment->posX.val) >> 1;
        anchorY = (anchorY + segment->posY.val) >> 1;
        deltaX = anchorX - entity->posX.val;
        deltaY = anchorY - entity->posY.val;
        anchorX += deltaX >> 2;
        anchorY += deltaY >> 2;
        entity->posX.val = anchorX;
        entity->posY.val = anchorY;
        entity->zPriority = self->zPriority + (u16)(i - 5);
        entity = segment;
        i++;
    } while (i < 5);
    segment = self + 5;
    anchorX =
        g_Entities[E_BOSS_WEAPON].posX.i.hi + D_us_8018081C[self->params][0];
    anchorY =
        g_Entities[E_BOSS_WEAPON].posY.i.hi + D_us_8018081C[self->params][1];
    for (i = 0; i < 6; i++, segment--) {
        deltaX = segment->posX.i.hi - anchorX;
        deltaY = segment->posY.i.hi - anchorY;
        angle = ratan2(deltaY, deltaX);
        if (deltaX * deltaX + deltaY * deltaY > 144) {
            segment->posX.i.hi = anchorX + ((rcos(angle) * 12) >> 12);
            segment->posY.i.hi = anchorY + ((rsin(angle) * 12) >> 12);
        }
        anchorX = segment->posX.i.hi;
        anchorY = segment->posY.i.hi;
    }
    if (D_us_801806E8) {
        self->animCurFrame = 0;
        self->hitboxState = 0;
    }
}

void func_us_8019FA78(Entity* self) {
    extern u16 D_us_80180540;
    extern s32 D_us_801806E8;
    extern s32 D_us_80180704;

    self->palette = D_us_80180704;

    switch (self->step) {
    case 0:
        InitializeEntity(&D_us_80180540);
        self->animCurFrame = 0x11;
        /* fall through */
    case 1:
        self->animCurFrame = 0x11;
        break;
    }

    if (D_us_801806E8 != 0) {
        self->animCurFrame = 0;
        self->hitboxState = 0;
    }
}

void func_us_8019FB04(Entity* self) {
    extern s32 D_us_80180704;
    extern s32 D_us_801806E8;
    extern u8* D_us_801807F4[];
    extern u16 D_us_80180540;
    extern void InitializeEntity(u16*);

    u16 value;

    self->palette = D_us_80180704;
    switch (self->step) {
    case 0:
        InitializeEntity(&D_us_80180540);
        /* fall through */
    case 1:
        AnimateEntity(D_us_801807F4[self->params], self);
        value = g_Entities[E_BOSS_WEAPON].posX.i.hi;
        self->posX.i.hi = value;
        value = g_Entities[E_BOSS_WEAPON].posY.i.hi;
        self->posY.i.hi = value;
        break;
    }

    if (D_us_801806E8 != 0) {
        self->animCurFrame = 0;
        self->hitboxState = 0;
    }
}

void func_us_8019FBC0(Entity* self) {
    extern u16 D_us_80180540;
    extern s32 D_us_801806E4;
    extern s32 D_us_801806E8;
    extern s32 D_us_80180704;
    extern u8 D_us_801807A8[];
    u16 palette;

    self->posX.i.hi = g_Entities[E_BOSS_WEAPON].posX.i.hi;
    palette = D_us_80180704;
    self->posY.i.hi = g_Entities[E_BOSS_WEAPON].posY.i.hi;
    self->palette = palette;
    if ((D_us_801806E4 & 1) && self->step != 16) {
        SetStep(16);
    }
    switch (self->step) {
    case 0:
        InitializeEntity(&D_us_80180540);
        /* fallthrough */
    case 1:
        AnimateEntity(D_us_801807A8, self);
        break;
    case 16:
        self->animCurFrame = 0x1B;
        break;
    }
    if (D_us_801806E8) {
        self->animCurFrame = 0;
        self->hitboxState = 0;
    }
}

void func_us_8019FCB4(Entity* self) {
    extern EInit g_EInitInteractable;
    extern s32 D_us_801806E8;
    extern s32 D_us_80180704;
    Primitive* prim;
    s32 i;
    s16 primIndex;
    s16 angle;
    s16 x, y;
    s32 palette;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 4);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.draculaFinalParts.prim = prim;
        self->flags |= FLAG_HAS_PRIMS;
        while (prim != NULL) {
            prim->tpage = 0x14;
            prim->clut = PAL_DRACULA + 1;
            prim->priority = self->zPriority + (u16)-1;
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }
        prim = self->ext.draculaFinalParts.prim;
        for (i = 0; i < 2; i++) {
            prim->u0 = 0xC1;
            prim->u1 = 0xFF;
            prim->u2 = 0xC1;
            prim->u3 = 0xFF;
            prim->v0 = 1;
            prim->v1 = 1;
            prim->v2 = 0x47;
            prim->v3 = 0x47;
            prim->priority = self->zPriority + (u16)-2;
            prim = prim->next;
            prim->u0 = 1;
            prim->u1 = 0xBF;
            prim->u2 = 1;
            prim->u3 = 0xBF;
            prim->v0 = 1;
            prim->v1 = 1;
            prim->v2 = 0xB4;
            prim->v3 = 0xB4;
            prim = prim->next;
        }
        /* fallthrough */
    case 1:
        self->posX.i.hi = g_Entities[E_BOSS_WEAPON].posX.i.hi;
        self->posY.i.hi = g_Entities[E_BOSS_WEAPON].posY.i.hi;
        self->ext.draculaFinalParts.bobAngle += 0x10;
        angle = (rsin(self->ext.draculaFinalParts.bobAngle) * 128) >> 12;
        self->rotate = angle;
        prim = self->ext.draculaFinalParts.prim;
        for (i = 0; i < 2; i++) {
            if (i == 0) {
                x = self->posX.i.hi - 8;
            } else {
                x = self->posX.i.hi + 8;
            }
            y = self->posY.i.hi - 52;
            prim->x1 = x;
            prim->x3 = x;
            prim->y1 = y;
            prim->y3 = y + 70;
            if (i == 0) {
                x -= (rcos(angle) * 62) >> 12;
            } else {
                x += (rcos(angle) * 62) >> 12;
            }
            y += (rsin(angle) * 62) >> 12;
            prim->x0 = x;
            prim->y0 = y;
            if (i == 0) {
                prim->x2 = x + ((rsin(angle) * 70) >> 12);
            } else {
                prim->x2 = x - ((rsin(angle) * 70) >> 12);
            }
            prim->y2 = y + ((rcos(angle) * 70) >> 12);
            prim->drawMode = DRAW_UNK02;
            prim = prim->next;
            if (i == 0) {
                x += 24;
            } else {
                x -= 24;
            }
            y -= 120;
            prim->x1 = x;
            prim->y1 = y;
            prim->x3 = x;
            prim->y3 = y + 179;
            if (i == 0) {
                x -= (rcos(angle) * 190) >> 12;
            } else {
                x += (rcos(angle) * 190) >> 12;
            }
            y += (rsin(angle) * 190) >> 12;
            prim->x0 = x;
            prim->y0 = y;
            if (i == 0) {
                prim->x2 = x + ((rsin(angle) * 179) >> 12);
            } else {
                prim->x2 = x - ((rsin(angle) * 179) >> 12);
            }
            prim->y2 = y + ((rcos(angle) * 179) >> 12);
            prim->drawMode = DRAW_UNK02;
            prim = prim->next;
        }
        break;
    }
    prim = self->ext.draculaFinalParts.prim;
    palette = D_us_80180704 & 0xFFF;
    if (palette == PAL_DRACULA) {
        palette = PAL_DRACULA + 1;
    }
    while (prim != NULL) {
        prim->clut = palette;
        if (D_us_801806E8) {
            prim->drawMode |= DRAW_HIDE;
        }
        prim = prim->next;
    }
    FntPrint("color %x\n", D_us_80180704);
}

void func_us_801A01A4(Entity* self) {
    extern EInit g_EInitInteractable;
    extern s32 D_us_801806E4;
    extern s32 D_us_801806EC;
    Primitive* prim;
    Primitive* nextPrim;
    Entity* entity;
    s32 i;
    s32 deltaX, deltaY;
    s16 primIndex;
    s16 angleDelta;
    s16 angle;
    u8 nearEnd;

    if (D_us_801806E4 & 1) {
        DestroyEntity(self);
        return;
    }
    if (D_us_801806EC == 2) {
        DestroyEntity(self);
        return;
    }
    if (self->params == 0) {
        self->ext.draculaFinalArc.start = &g_Entities[86];
        self->ext.draculaFinalArc.end = &g_Entities[88];
    } else {
        self->ext.draculaFinalArc.end = &g_Entities[86];
        self->ext.draculaFinalArc.start = &g_Entities[88];
    }
    entity = self->ext.draculaFinalArc.start;
    self->posX.i.hi = entity->posX.i.hi;
    self->posY.i.hi = entity->posY.i.hi;
    if (!(g_Timer & 15)) {
#ifdef FIX_UB
        g_api.PlaySfx(SFX_DRACULA_ELECTRICITY);
#else
        // @bug PlaySfx ignores the original volume and pan arguments.
        ((void (*)())g_api.PlaySfx)(SFX_DRACULA_ELECTRICITY, 0x70, 0);
#endif
    }
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 20);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.draculaFinalArc.prim = prim;
        self->ext.draculaFinalArc.currentPrim = prim;
        self->flags |= FLAG_HAS_PRIMS;
        i = 0;
        while (prim != NULL) {
            prim->tpage = 0x1A;
            prim->clut = 0x194;
            prim->u0 = prim->u1 = i * 16 - 0x70;
            prim->u2 = prim->u3 = i * 16 - 0x60;
            prim->v0 = prim->v2 = 0xD0;
            prim->v1 = prim->v3 = 0xC0;
            prim->r0 = prim->g0 = prim->b0 = 80;
            LOW(prim->r1) = LOW(prim->r0);
            LOW(prim->r2) = LOW(prim->r0);
            LOW(prim->r3) = LOW(prim->r0);
            prim->priority = self->zPriority + 1;
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
            i++;
            if (i >= 6) {
                i = 0;
            }
        }
        /* fallthrough */
    case 1:
        prim = self->ext.draculaFinalArc.prim;
        prim->x0 = self->posX.i.hi;
        prim->y0 = self->posY.i.hi;
        prim->x1 = prim->x0;
        // The original updates y1 from its previous value.
        prim->y1 -= 16;
        prim->x2 = self->posX.i.hi;
        prim->y2 = self->posY.i.hi;
        prim->x3 = prim->x2;
        prim->y3 = prim->y2 - 16;
        self->ext.draculaFinalArc.currentPrim = prim;
        self->ext.draculaFinalArc.angle = Random() * 16;
        while (prim != NULL) {
            prim->r0 = prim->g0 = prim->b0 = 80;
            prim->drawMode = DRAW_HIDE;
            LOW(prim->r1) = LOW(prim->r0);
            LOW(prim->r2) = LOW(prim->r0);
            LOW(prim->r3) = LOW(prim->r0);
            prim = prim->next;
        }
        self->ext.draculaFinalArc.turnTimer = 0;
        self->step++;
        /* fallthrough */
    case 2:
        while (true) {
            prim = self->ext.draculaFinalArc.currentPrim;
            entity = self->ext.draculaFinalArc.end;
            angle = self->ext.draculaFinalArc.angle;
            deltaX = entity->posX.i.hi;
            deltaY = entity->posY.i.hi;
            deltaX -= prim->x2;
            deltaY -= prim->y2;
            nearEnd = false;
            if ((abs(deltaX) < 16) && (abs(deltaY) < 16)) {
                break;
            }
            if (abs(deltaX) < 32) {
                nearEnd = abs(deltaY) < 32;
            }
            if (!self->ext.draculaFinalArc.turnTimer) {
                self->ext.draculaFinalArc.turnTimer = 4;
                if (nearEnd) {
                    self->ext.draculaFinalArc.turnTimer = 2;
                }
                angleDelta = ratan2(-deltaY, deltaX) - angle;
                if (angleDelta > 0x800) {
                    angleDelta -= 0x1000;
                }
                if (angleDelta < -0x800) {
                    angleDelta += 0x1000;
                }
                if (!nearEnd) {
                    angleDelta /= 4;
                } else {
                    angleDelta /= 2;
                }
                self->ext.draculaFinalArc.angleDelta = angleDelta;
            }
            angle += self->ext.draculaFinalArc.angleDelta;
            if (!nearEnd) {
                angle += 0x60 - ((Random() & 3) << 6);
            }
            angle &= 0xFFF;
            nextPrim = prim->next;
            if (nextPrim == NULL) {
                break;
            }
            LOW(nextPrim->x0) = LOW(prim->x2);
            LOW(nextPrim->x1) = LOW(prim->x3);
            self->ext.draculaFinalArc.angle = angle;
            self->ext.draculaFinalArc.currentPrim = nextPrim;
            deltaX = (rcos(angle) * 12) >> 12;
            deltaY = rsin(angle);
            nextPrim->x2 = nextPrim->x0 + deltaX;
            nextPrim->y2 = nextPrim->y0 - ((deltaY * 12) >> 12);
            angle -= 0x400;
            deltaX = (rcos(angle) * 16) >> 12;
            deltaY = rsin(angle);
            nextPrim->x3 = nextPrim->x2 + deltaX;
            nextPrim->y3 = nextPrim->y2 - ((deltaY * 16) >> 12);
            nextPrim->drawMode = DRAW_UNK_40 | DRAW_TPAGE2 | DRAW_TPAGE |
                                 DRAW_COLORS | DRAW_UNK02 | DRAW_TRANSP;
            self->ext.draculaFinalArc.turnTimer--;
        }
        self->step = 1;
        return;
    case 3:
        prim = self->ext.draculaFinalArc.prim;
        while (prim != NULL) {
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }
        self->step = 1;
        break;
    }
}

void func_us_801A0710(Entity* self) {
    extern u16 D_us_80180540;
    extern s32 D_us_801806E4;
    extern s32 D_us_801806EC;
    s32 scale;

    if (D_us_801806E4 & 1) {
        DestroyEntity(self);
        return;
    }
    self->posX.i.hi = g_Entities[E_BOSS_WEAPON].posX.i.hi;
    self->posY.i.hi = g_Entities[E_BOSS_WEAPON].posY.i.hi + 0x10;
    switch (self->step) {
    case 0:
        InitializeEntity(&D_us_80180540);
        self->animCurFrame = 0x2A;
        self->drawFlags = ENTITY_SCALEX | ENTITY_SCALEY;
        self->scaleX = self->scaleY = 0;
        /* fallthrough */
    case 1:
        self->scaleX = self->scaleY += 0x10;
        if (self->scaleX > 0x180) {
            self->step++;
        }
        break;
    case 2:
        CreateEntityFromCurrentEntity(E_UNK_21, &g_Entities[130]);
        g_Entities[130].zPriority = self->zPriority + 1;
        self->step++;
        break;
    case 3:
        if (D_us_801806EC == 2) {
            self->step++;
        }
        break;
    case 4:
        scale = self->scaleX - 0x20;
        self->scaleX = self->scaleY = scale;
        if (scale < 0) {
            DestroyEntity(self);
        }
        break;
    }
}

void func_us_801A0860(Entity* self) {
    extern u16 D_us_80180540;
    extern s32 D_us_801806E4;
    extern s32 D_us_801806EC;
    extern s32 D_us_801806F0;
    Entity* entity;
    s32 i;
    s32 scaleY;
    u16 frame;

    if (D_us_801806E4 & 1) {
        DestroyEntity(self);
        return;
    }
    self->posX.i.hi = g_Entities[E_BOSS_WEAPON].posX.i.hi;
    self->posY.i.hi = g_Entities[E_BOSS_WEAPON].posY.i.hi + 16;
    switch (self->step) {
    case 0:
        InitializeEntity(&D_us_80180540);
        frame = D_us_801806F0;
        self->drawFlags = ENTITY_SCALEX | ENTITY_SCALEY;
        self->scaleX = self->scaleY = 0;
        self->opacity = 0;
        self->animCurFrame = frame + 0x2D;
        self->drawFlags |= ENTITY_OPACITY;
        /* fallthrough */
    case 1:
        self->scaleX = self->scaleY += 8;
        if (self->scaleX >= 0x100) {
            self->scaleX = self->scaleY = 0x100;
            self->step++;
        }
        /* fallthrough */
    case 2:
        self->opacity += 2;
        if (self->opacity >= 128) {
            D_us_801806EC = 2;
            self->step = 3;
        }
        break;
    case 3:
        if (D_us_801806EC == 4) {
            g_api.PlaySfx(SFX_DRACULA_KARASUMAN_SQUISH);
            self->step++;
        }
        break;
    case 4:
        scaleY = self->scaleY;
        scaleY -= 0x18;
        self->scaleX += 8;
        if (scaleY < 0) {
            scaleY = 0;
        }
        self->scaleY = scaleY;
        for (i = 0; i < 16; i++) {
            entity = AllocEntity(&g_Entities[192], &g_Entities[256]);
            if (entity != NULL) {
                CreateEntityFromEntity(E_UNK_22, self, entity);
                entity->zPriority = self->zPriority + 1;
            }
        }
        if (!scaleY) {
            self->animCurFrame = 0;
            self->ext.draculaFinalSpell.timer = 80;
            self->step++;
        }
        break;
    case 5:
        if (!--self->ext.draculaFinalSpell.timer) {
            g_api.PlaySfx(SFX_NOISE_SWEEP_DOWN_A);
            DestroyEntity(self);
        }
        break;
    }
}

void func_us_801A0AB4(Entity* self) {
    extern u16 D_us_80180540;
    extern s32 D_us_801806E4;
    extern s32 D_us_801806EC;
    extern u8 D_us_801807E0[];
    s16 angle;
    s32 magnitude;
    s32 deltaX;
    s32 deltaY;
    s32 offsetY;

    if (D_us_801806E4 & 1) {
        DestroyEntity(self);
        return;
    }
    switch (self->step) {
    case 0:
        InitializeEntity(&D_us_80180540);
        self->drawFlags = ENTITY_SCALEX | ENTITY_SCALEY;
        self->scaleX = self->scaleY = (Random() & 0x7F) | 0x80;
        self->blendMode = BLEND_TRANSP;
        angle = rand() & 0xFFF;
        magnitude = (Random() & 0x1F) + 16;
        self->velocityX = magnitude * rcos(angle);
        self->velocityY = magnitude * rsin(angle);
        self->posX.val += self->velocityX * 4;
        self->posY.val += self->velocityY * 4;
        self->ext.draculaFinalSpell.timer = (Random() & 0x1F) + 16;
        /* fallthrough */
    case 1:
        MoveEntity();
        AnimateEntity(D_us_801807E0, self);
        self->velocityX -= self->velocityX >> 5;
        self->velocityY -= self->velocityY >> 5;
        if (D_us_801806EC == 5) {
            self->velocityX = 0;
            self->velocityY = 0;
            self->step++;
        }
        break;
    case 2:
        AnimateEntity(D_us_801807E0, self);
        if (!--self->ext.draculaFinalSpell.timer) {
            self->step++;
        }
        if (!(g_Timer & 7)) {
            g_api.PlaySfx(SFX_NOISE_SWEEP_DOWN_B);
        }
        break;
    case 3:
        MoveEntity();
        if (self->scaleX > 0x20) {
            self->scaleX = self->scaleY -= 2;
        }
        offsetY = self->posY.i.hi + 24;
        deltaY = g_Entities[E_BOSS_WEAPON].posY.i.hi - offsetY;
        deltaX = g_Entities[E_BOSS_WEAPON].posX.i.hi - self->posX.i.hi;
        angle = ratan2(deltaY, deltaX);
        if (self->ext.draculaFinalSpell.speed < FIX(3)) {
            self->ext.draculaFinalSpell.speed += FIX(0.0625);
        }
        magnitude = self->ext.draculaFinalSpell.speed;
        self->velocityX = (magnitude * rcos(angle)) >> 12;
        self->velocityY = (magnitude * rsin(angle)) >> 12;
        magnitude = deltaX * deltaX + deltaY * deltaY;
        if (magnitude < 64) {
            DestroyEntity(self);
        }
        break;
    }
}

void func_us_801A0DC0(Entity* self) {
    extern EInit D_us_80180564;
    extern s32 D_us_801806E4;
    extern s32 D_us_801806F4;
    extern u8 D_us_8018071C[];
    s32 scale;
    s32 radius;
    s32 deltaX;
    s32 deltaY;
    Entity* entity;

    if (D_us_801806E4 & 1) {
        DestroyEntity(self);
        return;
    }
    switch (self->step) {
    case 0:
        InitializeEntity(D_us_80180564);
        self->drawFlags = ENTITY_SCALEX | ENTITY_SCALEY;
        self->opacity = 96;
        self->scaleX = self->scaleY = 0;
        self->hitboxState = 0;
        self->blendMode |= BLEND_TRANSP | BLEND_ADD;
        self->drawFlags |= ENTITY_OPACITY;
        /* fallthrough */
    case 1:
        AnimateEntity(D_us_8018071C, self);
        scale = self->scaleX;
        scale += 0x10;
        if (scale > 0xCC) {
            scale = 0xCC;
        }
        self->scaleX = self->scaleY = scale;
        if (D_us_801806F4) {
            self->ext.draculaFinalSpell.timer = 96;
            entity = &PLAYER;
            deltaX = entity->posX.val - self->posX.val;
            deltaY = entity->posY.val - self->posY.val;
            self->step++;
            self->velocityX = deltaX / 96;
            self->velocityY = deltaY / 96;
        }
        if (!(g_Timer & 0x1F)) {
            g_api.PlaySfxVolPan(SFX_RAPID_SYNTH_BUBBLE_SHORT, 80, 0);
        }
        break;
    case 2:
        AnimateEntity(D_us_8018071C, self);
        MoveEntity();
        scale = 0x6000 / (self->ext.draculaFinalSpell.timer + 24);
        self->scaleX = self->scaleY = scale;
        if (!(self->ext.draculaFinalSpell.timer & 3)) {
            entity = AllocEntity(&g_Entities[192], &g_Entities[256]);
            if (entity != NULL) {
                CreateEntityFromEntity(E_UNK_26, self, entity);
                entity->scaleX = entity->scaleY = self->scaleX;
                entity->zPriority = self->zPriority;
                entity->opacity = self->opacity;
            }
        }
        if (!(self->ext.draculaFinalSpell.timer & 0xF)) {
            g_api.PlaySfxVolPan(SFX_RIC_SUC_REVIVE,
                                128 - self->ext.draculaFinalSpell.timer / 2, 0);
        }
        if (!--self->ext.draculaFinalSpell.timer) {
            g_api.PlaySfx(SFX_FIREBALL_SHOT_B);
            radius = self->scaleX * 20;
            self->zPriority = g_unkGraphicsStruct.g_zEntityCenter + 8;
            entity = &PLAYER;
            deltaX = entity->posX.i.hi - self->posX.i.hi;
            deltaY = entity->posY.i.hi - self->posY.i.hi;
            scale = radius / 256;
            if (deltaX * deltaX + deltaY * deltaY < scale * scale) {
                self->hitboxOffX = deltaX;
                self->hitboxOffY = deltaY;
                self->hitboxState = 1;
            }
            self->step++;
        }
        break;
    case 3:
        DestroyEntity(self);
        break;
    }
}

void func_us_801A1150(Entity* self) {
    extern u16 D_us_80180540;
    extern u8 D_us_80180724[];
    s32 var_v0;

    if (!self->step) {
        InitializeEntity(&D_us_80180540);
        self->drawFlags = ENTITY_OPACITY | ENTITY_SCALEY | ENTITY_SCALEX;
        self->blendMode = BLEND_ADD | BLEND_TRANSP;
    }
    AnimateEntity(D_us_80180724, self);
    var_v0 = self->opacity;
    var_v0 -= 2;
    if (var_v0 < 0) {
        var_v0 = 0;
    }
    self->opacity = (u8)var_v0;
    if (var_v0 == 0) {
        DestroyEntity(self);
    }
}

void func_us_801A11DC(Entity* self) {
    extern EInit D_us_80180570;
    extern s32 D_us_801806E4;
    Primitive* prim;
    s32 i;
    Point16* offsets;
    s32 intensity;
    s16* vertices;
    s32 y, x;
    s16 angle;
    s32 sine, cosine;
    s16 redPhase, greenPhase, bluePhase;
    u8* colors;
    Entity* entity;
    Pos* positions;
    s16 primIndex;

    if (D_us_801806E4 & 1) {
        DestroyEntity(self);
        return;
    }
    switch (self->step) {
    case 0:
        InitializeEntity(D_us_80180570);
        self->hitboxState = 0;
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 10);
        if (primIndex == -1) {
            self->step = 0;
            return;
        }
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.draculaFinalTriangle.prim = prim;
        self->flags |= FLAG_HAS_PRIMS;
        for (i = 0; i < 3; i++) {
            prim->type = PRIM_LINE_G2;
            prim->r0 = prim->g0 = prim->b0 = 192;
            prim->r1 = prim->g1 = prim->b1 = 192;
            prim->priority = self->zPriority;
            prim->drawMode =
                DRAW_TPAGE2 | DRAW_TPAGE | DRAW_UNK02 | DRAW_TRANSP;
            prim = prim->next;
        }
        prim->type = PRIM_GT3;
        prim->r0 = prim->g0 = prim->b0 = 16;
        prim->tpage = 0x1A;
        prim->clut = 0x15F;
        prim->u0 = prim->v0 = 0x10;
        prim->u1 = 0x14;
        prim->v1 = 0x10;
        prim->u2 = prim->v2 = 0x14;
        LOW(prim->r1) = LOW(prim->r0);
        LOW(prim->r2) = LOW(prim->r0);
        prim->priority = self->zPriority;
        prim->drawMode =
            DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS | DRAW_UNK02 | DRAW_TRANSP;
        self->opacity = 0;
        /* fallthrough */
    case 1:
        positions = (Pos*)SP(0);
        entity = &g_Entities[91];
        for (i = 0; i < 3; i++, entity += 6) {
            positions[i].x.i.hi = entity->posX.i.hi;
            positions[i].y.i.hi = entity->posY.i.hi + 12;
        }
        ((Pos*)SP(0))[3].x.i.hi = g_Entities[91].posX.i.hi;
        ((Pos*)SP(0))[3].y.i.hi = g_Entities[91].posY.i.hi + 12;
        prim = self->ext.draculaFinalTriangle.prim;
        for (i = 0; i < 3; i++) {
            prim->x0 = positions[i].x.i.hi;
            prim->y0 = positions[i].y.i.hi;
            prim = prim->next;
        }
        prim = self->ext.draculaFinalTriangle.prim;
        for (i = 1; i < 4; i++) {
            prim->x1 = positions[i].x.i.hi;
            prim->y1 = positions[i].y.i.hi;
            prim = prim->next;
        }
        prim->x0 = ((Pos*)SP(0))[0].x.i.hi;
        prim->y0 = ((Pos*)SP(0))[0].y.i.hi;
        prim->x1 = ((Pos*)SP(0))[1].x.i.hi;
        prim->y1 = ((Pos*)SP(0))[1].y.i.hi;
        prim->x2 = ((Pos*)SP(0))[2].x.i.hi;
        prim->y2 = ((Pos*)SP(0))[2].y.i.hi;
        colors = &prim->r0;
        redPhase = self->ext.draculaFinalTriangle.redPhase += 0x100;
        greenPhase = self->ext.draculaFinalTriangle.greenPhase += 0x40;
        self->opacity += 3;
        intensity = self->opacity;
        bluePhase = self->ext.draculaFinalTriangle.bluePhase += 0x80;
        for (i = 0; i < 3; i++, colors += 12) {
            colors[0] = (intensity + ((intensity * rcos(redPhase)) >> 12)) / 2;
            colors[1] =
                (intensity + ((intensity * rsin(greenPhase)) >> 12)) / 2;
            colors[2] = (intensity + ((intensity * rcos(bluePhase)) >> 12)) / 2;
            redPhase += 0x40;
            greenPhase += 0x280;
            bluePhase += 0x100;
        }
        if (self->opacity > 64) {
            y = x = 0;
            for (i = 0; i < 3; i++) {
                x += positions[i].x.i.hi;
                y += positions[i].y.i.hi;
            }
            self->posX.i.hi = x / 3;
            self->posY.i.hi = y / 3;
            offsets = self->ext.draculaFinalTriangle.offsets;
            for (i = 0; i < 3; i++, offsets++) {
                offsets->x = positions[i].x.i.hi - self->posX.i.hi;
                offsets->y = positions[i].y.i.hi - self->posY.i.hi;
            }
            self->scaleX = 0x100;
            self->step++;
        }
        break;
    case 2:
        prim = self->ext.draculaFinalTriangle.prim;
        for (i = 0; i < 3; i++) {
            if (!PrimDecreaseBrightness(prim, 8)) {
                prim->drawMode = DRAW_HIDE;
            }
            prim = prim->next;
        }
        vertices = &prim->x0;
        offsets = self->ext.draculaFinalTriangle.offsets;
        x = self->posX.i.hi;
        y = self->posY.i.hi;
        intensity = self->scaleX -= 8;
        for (i = 0; i < 3; i++, offsets++, vertices += 6) {
            vertices[0] = x + ((offsets->x * intensity) >> 8);
            vertices[1] = y + ((offsets->y * intensity) >> 8);
        }
        colors = &prim->r0;
        if (self->opacity < 192) {
            self->opacity += 4;
        }
        intensity = self->opacity;
        redPhase = self->ext.draculaFinalTriangle.redPhase += 0x100;
        greenPhase = self->ext.draculaFinalTriangle.greenPhase += 0x40;
        bluePhase = self->ext.draculaFinalTriangle.bluePhase += 0x80;
        for (i = 0; i < 3; i++, colors += 12) {
            colors[0] = (intensity + ((intensity * rcos(redPhase)) >> 12)) / 2;
            colors[1] =
                (intensity + ((intensity * rsin(greenPhase)) >> 12)) / 2;
            colors[2] = (intensity + ((intensity * rcos(bluePhase)) >> 12)) / 2;
            redPhase += 0x40;
            greenPhase += 0x280;
            bluePhase += 0x100;
        }
        if (self->scaleX < 0x60) {
            prim = self->ext.draculaFinalTriangle.prim;
            for (i = 0; i < 3; i++) {
                prim->drawMode = DRAW_HIDE;
                prim = prim->next;
            }
            offsets = self->ext.draculaFinalTriangle.offsets;
            intensity = self->scaleX;
            for (i = 0; i < 3; i++, offsets++) {
                offsets->x = (offsets->x * intensity) >> 8;
                offsets->y = (offsets->y * intensity) >> 8;
            }
            self->step++;
        }
        break;
    case 3:
        x = PLAYER.posX.i.hi - self->posX.i.hi;
        y = PLAYER.posY.i.hi - self->posY.i.hi;
        angle = ratan2(y, x);
        self->velocityX = (rcos(angle) * FIX(4)) >> 12;
        self->velocityY = (rsin(angle) * FIX(4)) >> 12;
        self->hitboxState = 1;
        g_api.PlaySfx(SFX_DRACULA_TRIANGLE_ATTACK);
        self->step++;
        /* fallthrough */
    case 4:
        MoveEntity();
        self->flags |= FLAG_DESTROY_IF_OUT_OF_CAMERA;
        if (self->velocityX > 0) {
            self->rotate += ROT(5.625);
        } else {
            self->rotate -= ROT(5.625);
        }
        prim = self->ext.draculaFinalTriangle.prim;
        for (i = 0; i < 3; i++) {
            prim = prim->next;
        }
        colors = &prim->r0;
        intensity = self->opacity;
        redPhase = self->ext.draculaFinalTriangle.redPhase += 0x100;
        greenPhase = self->ext.draculaFinalTriangle.greenPhase += 0x40;
        bluePhase = self->ext.draculaFinalTriangle.bluePhase += 0x80;
        for (i = 0; i < 3; i++, colors += 12) {
            colors[0] = (intensity + ((intensity * rcos(redPhase)) >> 12)) / 2;
            colors[1] =
                (intensity + ((intensity * rsin(greenPhase)) >> 12)) / 2;
            colors[2] = (intensity + ((intensity * rcos(bluePhase)) >> 12)) / 2;
            redPhase += 0x40;
            greenPhase += 0x280;
            bluePhase += 0x100;
        }
        vertices = &prim->x0;
        offsets = self->ext.draculaFinalTriangle.offsets;
        x = self->posX.i.hi;
        y = self->posY.i.hi;
        angle = self->rotate;
        sine = rsin(angle);
        cosine = rcos(angle);
        for (i = 0; i < 3; i++, offsets++, vertices += 6) {
            vertices[0] = x + ((offsets->x * cosine - offsets->y * sine) >> 12);
            vertices[1] = y + ((offsets->x * sine + offsets->y * cosine) >> 12);
        }
        break;
    }
}

void func_us_801A1B38(Entity* self) {
    Entity* real;
#ifdef VERSION_PC
    extern s32 D_us_801806E4, D_us_80180700;
    extern u16 D_us_80180540;
    extern u8 D_us_801807EC[];
#endif

#ifdef VERSION_PC
    if (D_us_801806E4 & 1) {
#else
    if (*(s32*)0x801806E4 & 1) {
#endif
        DestroyEntity(self);
        return;
    }

    if (!self->step) {
#ifdef VERSION_PC
        InitializeEntity(&D_us_80180540);
#else
        InitializeEntity((u16*)((u32)func_us_801A1B38 - 0x215F8));
#endif
        self->blendMode = BLEND_ADD | BLEND_TRANSP;
    }

#ifdef VERSION_PC
    AnimateEntity(D_us_801807EC, self);
#else
    AnimateEntity((u8*)((u32)func_us_801A1B38 - 0x2134C), self);
#endif

    real = self->ext.succubus.real;
    self->posX.i.hi = real->posX.i.hi;
    self->posY.i.hi = real->posY.i.hi + 0xC;

#ifdef VERSION_PC
    if (D_us_80180700 == 5) {
#else
    if (*(s32*)0x80180700 == 5) {
#endif
        DestroyEntity(self);
    }
}
