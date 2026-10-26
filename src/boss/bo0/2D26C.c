// SPDX-License-Identifier: AGPL-3.0-or-later
#include "bo0.h"

extern EInit g_EInitOlroxAfterImage;
extern EInit D_us_801806D8;
extern EInit D_us_801806E4;
extern EInit D_us_801806FC;
extern EInit D_us_801806F0;
extern s16 D_us_80180BF8[];
extern s16 D_us_80180D94[];
extern u8 D_us_80180D48[];
extern u8 D_us_80180D50[];
void EntityExplosion(Entity* self);
extern s32 D_us_80180BA8;
extern u8 D_us_80180D38[];
extern u8 D_us_80180D68[];
extern u8 D_us_80180D74[];
extern u8 D_us_80180D7C[];

s16 func_us_801AD26C(s16 step, s16 angle, s16 target) {
    s16 delta;

    angle &= 0xFFF;
    target &= 0xFFF;
    delta = target - angle;
    if (delta > 0x800) {
        delta -= 0x1000;
    }
    if (delta < -0x800) {
        delta += 0x1000;
    }
    if (delta < -step) {
        delta = -step;
    }
    if (delta > step) {
        delta = step;
    }
    target = angle + delta;
    target &= 0xFFF;
    return target;
}

bool func_us_801AD2F0(s16 x, s16 y) {
    Collider collider;

    g_api.CheckCollision(x, y, &collider, 0);
    return collider.effects & EFFECT_SOLID;
}

extern u8 D_us_80180BAC[];
extern u8 D_us_80180C00[];
extern u8 D_us_80180C0C[];
extern u8 D_us_80180C24[];
extern u8 D_us_80180C40[];
extern u8 D_us_80180C4C[];
extern u8 D_us_80180C58[];
extern u8 D_us_80180C6C[];
extern u8 D_us_80180C80[];
extern u8 D_us_80180CAC[];
extern u8 D_us_80180CBC[];
extern u8 D_us_80180CC4[];
extern u8 D_us_80180CD0[];
extern u8 D_us_80180CDC[];
extern u8 D_us_80180CEC[];
extern u8 D_us_80180D00[];
extern u8 D_us_80180D10[];
extern u8 D_us_80180D20[];
extern u8 D_us_80180D2C[];
extern s16 D_us_80180BBC[];
extern s16 D_us_80180BCC[];
extern s16 D_us_80180BD4[];

void func_us_801AD338(Entity* self) {
    s32 i;
    s32 offsetX;
    u8 count;
    s16 posX;
    s16 deltaX;
    s16 spawnX;
    s16* positions;
    Entity* entity;
    // Unused drawing locals preserve the original stack layout and RECT copy.
    DRAWENV draw;
    RECT rect = {0, 256, 128, 256};

    g_api.func_8010DFF0(1, 2);
    if ((self->flags & FLAG_DEAD) && self->step < 14) {
        self->hitboxState = 0;
        SetStep(14);
    }
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitOlroxAfterImage);
        self->animCurFrame = 14;
        self->hitboxState = 0;
        break;
    case 1:
        if (GetDistanceToPlayerX() < 0x60 &&
            g_Player.vram_flag == TOUCHING_GROUND) {
            g_api.TimeAttackController(
                TIMEATTACK_EVENT_OLROX_DEFEAT, TIMEATTACK_SET_VISITED);
            SetStep(2);
            self->ext.olrox.timer = 192;
        }
        entity = self - 1;
        if (entity->flags & FLAG_DEAD) {
            stopMusicFlag = 0;
            currentMusicId = 0x334;
            g_api.PlaySfx(0x334);
            g_api.TimeAttackController(
                TIMEATTACK_EVENT_OLROX_DEFEAT, TIMEATTACK_SET_VISITED);
            SetStep(13);
            self->hitboxState = 3;
        }
        break;
    case 2:
        entity = self - 1;
        if (entity->flags & FLAG_DEAD) {
            stopMusicFlag = 0;
            currentMusicId = 0x334;
            g_api.PlaySfx(0x334);
            SetStep(13);
            self->hitboxState = 3;
            break;
        }
        switch (self->step_s) {
        case 0:
            if (!AnimateEntity(D_us_80180C00, self)) {
                SetSubStep(1);
            }
            break;
        case 1:
            if (!AnimateEntity(D_us_80180C0C, self)) {
                stopMusicFlag = 0;
                currentMusicId = 0x334;
                g_api.PlaySfx(0x334);
                self->hitboxState = 3;
                SetStep(3);
            }
            break;
        }
        break;
    case 3:
        posX = self->posX.i.hi + g_Tilemap.scrollX.i.hi;
        deltaX = PLAYER.posX.i.hi - self->posX.i.hi;
        if (posX < 0x50 && (u16)deltaX < 0x40) {
            SetStep(13);
            break;
        }
        if (posX > 0x1B0 && (u16)deltaX > 0xFFBF) {
            SetStep(13);
            break;
        }
        if (abs(deltaX) < 0x24) {
            self->facingLeft = GetSideToPlayer() & 1;
            SetStep(5);
            break;
        }
        if (posX < 0x80 && (u16)deltaX < 0x70) {
            SetStep(4);
            break;
        }
        if (posX > 0x180 && (u16)deltaX > 0xFF8F) {
            SetStep(4);
            break;
        }
        if (abs(deltaX) < 0x40) {
            self->facingLeft = GetSideToPlayer() & 1;
            SetStep(6);
            self->step_s = 1;
            break;
        }
        if (abs(deltaX) > 0xB0) {
            self->facingLeft = GetSideToPlayer() & 1;
            SetStep(6);
            break;
        }
        self->facingLeft = GetSideToPlayer() & 1;
        if (self->hitPoints < g_api.enemyDefs[ENEMY_OLROX].hitPoints * 3 / 4) {
            self->ext.olrox.unk88 |= 8;
        }
        SetStep(D_us_80180BAC[self->ext.olrox.unk88]);
        self->ext.olrox.unk88 = (self->ext.olrox.unk88 + 1) & 7;
        break;
    case 13:
        switch (self->step_s) {
        case 0:
            if (!AnimateEntity(D_us_80180CC4, self)) {
                SetSubStep(1);
                self->scaleY = 0x100;
                self->drawFlags |= ENTITY_SCALEY;
                PlaySfxPositional(SFX_BOSS_CLONE_DISAPPEAR);
            }
            if (self->pose >= 2) {
                self->hitboxState = 0;
            }
            break;
        case 1:
            self->scaleY -= 0x20;
            if (!self->scaleY) {
                self->drawFlags = ENTITY_DEFAULT;
                self->animCurFrame = 0;
                SetSubStep(2);
            }
            break;
        case 2:
            posX = self->posX.i.hi + g_Tilemap.scrollX.i.hi;
            if (posX < 0x100) {
                offsetX = (Random() & 0x3F) + 0x20;
                self->posX.i.hi = PLAYER.posX.i.hi + offsetX;
            } else {
                offsetX = (Random() & 0x3F) + 0x20;
                self->posX.i.hi = PLAYER.posX.i.hi - offsetX;
            }
            posX = self->posX.i.hi + g_Tilemap.scrollX.i.hi;
            if (posX < 0x30) {
                self->posX.i.hi = 0x30;
            }
            if (posX > 0x1D0) {
                self->posX.i.hi = 0xD0;
            }
            self->facingLeft = GetSideToPlayer() & 1;
            SetSubStep(3);
            break;
        case 3:
            if (!AnimateEntity(D_us_80180CD0, self)) {
                SetStep(3);
            }
            if (self->pose >= 5) {
                self->hitboxState = 3;
            }
            break;
        }
        break;
    case 12:
        if (!self->step_s) {
            //! @bug Both facing directions move left.
            self->velocityX = -FIX(0.5);
            if (self->facingLeft) {
                self->velocityX = -FIX(0.5);
            }
        }
        UnkCollisionFunc2(D_us_80180BCC);
        if (!AnimateEntity(D_us_80180D20, self)) {
            SetStep(3);
        }
        break;
    case 11:
        switch (self->step_s) {
        case 0:
            entity = self + 11;
            if (!entity->entityId) {
                posX = g_Tilemap.scrollX.i.hi + 0x20;
                spawnX = 0x20;
                if (posX < 0x50) {
                    spawnX = 0x50;
                }
                if (posX > 0x110) {
                    spawnX = 0x110 - g_Tilemap.scrollX.i.hi;
                }
                count = Random() & 3;
                for (i = 0; i < 3; i++, entity++) {
                    CreateEntityFromCurrentEntity(E_UNK_31, entity);
                    entity->posX.i.hi = spawnX;
                    entity->posY.i.hi = self->posY.i.hi + 30;
                    entity->ext.olroxGroundBlast.entity = self;
                    entity->params = count;
                    count = (count + 1) & 3;
                    spawnX += 0x50;
                }
                self->ext.olrox.unk86 = 0;
                self->step_s++;
                g_api.PlaySfx(SFX_FM_THUNDER_EXPLODE);
            } else {
                SetStep(3);
            }
            break;
        case 1:
            if (!AnimateEntity(D_us_80180C80, self)) {
                SetStep(3);
            }
            if (*(s32*)&self->pose == 16) {
                self->ext.olrox.unk86 = 1;
            }
            break;
        }
        break;
    case 10:
        if (!self->step_s) {
            if (self->posX.i.hi & 0x100) {
                SetStep(3);
                break;
            } else {
                self->step_s++;
            }
        }
        if (!AnimateEntity(D_us_80180C24, self)) {
            SetStep(3);
        }
        if (*(s32*)&self->pose == 4) {
            PlaySfxPositional(SFX_SCIFI_BLAST);
            entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
            if (entity != NULL) {
                CreateEntityFromEntity(E_UNK_30, self, entity);
                entity->facingLeft = self->facingLeft;
            }
        }
        break;
    case 9:
        switch (self->step_s) {
        case 0:
            count = 0;
            entity = &g_Entities[160];
            for (i = 7; i >= 0; i--, entity++) {
                if (entity->entityId) {
                    count++;
                }
            }
            if (count < 5) {
                if (!AnimateEntity(D_us_80180CAC, self)) {
                    SetSubStep(1);
                }
            } else {
                SetStep(3);
            }
            break;
        case 1:
            entity = self + 10;
            CreateEntityFromEntity(E_UNK_2E, self, entity);
            self->ext.olrox.timer = 96;
            entity->ext.olroxProjectile.parent = self;
            self->ext.olrox.unk85 = 0;
            entity->posY.i.hi -= 70;
            self->step_s++;
            PlaySfxPositional(SFX_TELEPORT_BANG_B);
            break;
        case 2:
            if (!--self->ext.olrox.timer) {
                self->ext.olrox.unk85 = 1;
                self->step_s++;
            }
            break;
        case 3:
            if (!AnimateEntity(D_us_80180CBC, self)) {
                SetStep(3);
            }
            break;
        }
        break;
    case 8:
        switch (self->step_s) {
        case 0:
            if (!AnimateEntity(D_us_80180C58, self)) {
                SetSubStep(1);
            }
            break;
        case 1:
            entity = self + 1;
            positions = D_us_80180BD4;
            for (i = 0; i < 9; i++, entity++) {
                if (!entity->entityId) {
                    CreateEntityFromCurrentEntity(E_UNK_2D, entity);
                    entity->posX.i.hi = *positions++;
                    entity->posY.i.hi = *positions++;
                    entity->ext.olroxProjectile.parent = self;
                    entity->params = i;
                }
            }
            self->ext.olrox.unk84 = 0;
            self->step_s++;
            PlaySfxPositional(SFX_OLROX_BAT_ATTACK);
            break;
        case 2:
            count = 1;
            entity = self + 1;
            for (i = 0; i < 9; i++, entity++) {
                if (entity->entityId && !entity->hitboxState) {
                    count = 0;
                }
            }
            if (count) {
                self->step_s++;
            }
            break;
        case 3:
            if (!AnimateEntity(D_us_80180C6C, self)) {
                self->step_s++;
            }
            if (self->pose == 5) {
                if (!self->poseTimer) {
                    PlaySfxPositional(SFX_OLROX_ATTACK);
                }
                self->ext.olrox.unk84 = 1;
            }
            break;
        case 4:
            SetStep(3);
            break;
        }
        break;
    case 7:
        switch (self->step_s) {
        case 0:
            if (!AnimateEntity(D_us_80180C40, self)) {
                SetSubStep(1);
            }
            break;
        case 1:
            self->step_s++;
            break;
        case 2:
            if (!AnimateEntity(D_us_80180C4C, self)) {
                SetStep(3);
            }
            break;
        }
        break;
    case 6:
        switch (self->step_s) {
        case 0:
            self->velocityX = FIX(2.25);
            if (self->facingLeft) {
                self->velocityX = -FIX(2.25);
            }
            self->animCurFrame = 0x19;
            self->ext.olrox.timer = 8;
            self->step_s = 2;
            break;
        case 1:
            self->velocityX = -FIX(2.25);
            if (self->facingLeft) {
                self->velocityX = FIX(2.25);
            }
            self->animCurFrame = 0x2D;
            self->ext.olrox.timer = 8;
            self->step_s = 2;
            break;
        case 2:
            UnkCollisionFunc2(D_us_80180BCC);
            if (!--self->ext.olrox.timer) {
                self->ext.olrox.timer = 8;
                entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (entity != NULL) {
                    CreateEntityFromEntity(E_OLROX_AFTER_IMAGE, self, entity);
                    entity->params = self->animCurFrame;
                    entity->facingLeft = self->facingLeft;
                }
            }
            if (self->animCurFrame == 0x2D) {
                if (!self->velocityX || GetDistanceToPlayerX() > 0x60) {
                    self->facingLeft = GetSideToPlayer() & 1;
                    SetStep(3);
                }
            }
            if (self->animCurFrame == 0x19) {
                if (!self->velocityX || GetDistanceToPlayerX() < 0x70) {
                    self->facingLeft = GetSideToPlayer() & 1;
                    SetStep(3);
                }
            }
            break;
        }
        break;
    case 4:
        switch (self->step_s) {
        case 0:
            posX = g_Tilemap.scrollX.i.hi + self->posX.i.hi;
            if (posX < 0x60 && self->facingLeft) {
                SetStep(3);
                break;
            }
            if (posX > 0x1B0 && !self->facingLeft) {
                SetStep(3);
                break;
            }
            if (!AnimateEntity(D_us_80180D00, self)) {
                self->velocityY = -FIX(4.5);
                self->velocityX = 0;
                self->animCurFrame = 0x19;
                if (self->posX.i.hi > PLAYER.posX.i.hi) {
                    self->ext.olrox.unk87 = 1;
                } else {
                    self->ext.olrox.unk87 = 0;
                }
                SetSubStep(1);
            }
            break;
        case 1:
            MoveEntity();
            if (self->velocityY > -FIX(1.5)) {
                self->velocityY += FIX(0.0625);
            } else {
                self->velocityY += FIX(0.125);
            }
            if (self->velocityY >= 0) {
                if (self->ext.olrox.unk87) {
                    self->velocityX = -FIX(3);
                } else {
                    self->velocityX = FIX(3);
                }
                if (self->facingLeft == self->ext.olrox.unk87) {
                    self->animCurFrame = 0x19;
                } else {
                    self->animCurFrame = 0x2D;
                }
                self->ext.olrox.timer = 24;
                self->step_s++;
            }
            break;
        case 2:
            if (!--self->ext.olrox.timer) {
                self->ext.olrox.timer = 8;
                self->step_s++;
            }
            break;
        case 3:
            if (!--self->ext.olrox.timer) {
                self->ext.olrox.timer = 8;
                entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (entity != NULL) {
                    CreateEntityFromEntity(E_OLROX_AFTER_IMAGE, self, entity);
                    entity->params = self->animCurFrame;
                    entity->facingLeft = self->facingLeft;
                }
            }
            MoveEntity();
            self->facingLeft = GetSideToPlayer() & 1;
            if (self->ext.olrox.unk87 == self->facingLeft) {
                self->animCurFrame = 0x19;
            } else {
                self->animCurFrame = 0x2D;
            }
            posX = g_Tilemap.scrollX.i.hi + self->posX.i.hi;
            if (posX < 0x38 && self->velocityX < 0) {
                self->step_s++;
            }
            if (posX > 0x1C8 && self->velocityX > 0) {
                self->step_s++;
            }
            if (GetDistanceToPlayerX() > 0x50) {
                if (self->ext.olrox.unk87 != (GetSideToPlayer() & 1)) {
                    self->step_s++;
                }
            }
            break;
        case 4:
            posX = g_Tilemap.scrollX.i.hi + self->posX.i.hi;
            if (posX < 0x38) {
                self->velocityX = 0;
                self->posX.i.hi = 0x38 - g_Tilemap.scrollX.i.hi;
            }
            if (posX > 0x1C8) {
                self->velocityX = 0;
                self->posX.i.hi = 0x1C8 - g_Tilemap.scrollX.i.hi;
            }
            self->velocityY -= FIX(0.125);
            if (UnkCollisionFunc3(D_us_80180BBC) & 1) {
                self->step_s++;
                PlaySfxPositional(SFX_STOMP_HARD_B);
            }
            break;
        case 5:
            if (!AnimateEntity(D_us_80180D10, self)) {
                SetStep(3);
            }
            break;
        }
        break;
    case 5:
        switch (self->step_s) {
        case 0:
            if (!AnimateEntity(D_us_80180CDC, self)) {
                self->velocityX = -FIX(4);
                if (self->facingLeft) {
                    self->velocityX = FIX(4);
                }
                self->velocityY = -FIX(3);
                self->animCurFrame = 0x2D;
                self->ext.olrox.timer = 8;
                SetSubStep(1);
            }
            break;
        case 1:
            if (!--self->ext.olrox.timer) {
                self->ext.olrox.timer = 8;
                entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (entity != NULL) {
                    CreateEntityFromEntity(E_OLROX_AFTER_IMAGE, self, entity);
                    entity->params = self->animCurFrame;
                    entity->facingLeft = self->facingLeft;
                }
            }
            posX = g_Tilemap.scrollX.i.hi + self->posX.i.hi;
            if (posX < 0x38) {
                self->posX.i.hi = 0x38 - g_Tilemap.scrollX.i.hi;
            }
            if (posX > 0x1C8) {
                self->posX.i.hi = 0x1C8 - g_Tilemap.scrollX.i.hi;
            }
            if (UnkCollisionFunc3(D_us_80180BBC) & 1) {
                self->step_s++;
                PlaySfxPositional(SFX_STOMP_HARD_B);
            }
            break;
        case 2:
            if (!AnimateEntity(D_us_80180CEC, self)) {
                SetStep(3);
            }
            break;
        }
        break;
    case 14:
        switch (self->step_s) {
        case 0:
            self->velocityX = 0;
            if (UnkCollisionFunc3(D_us_80180BBC) & 1) {
                self->step_s++;
            }
            break;
        case 1:
            entity = self - 16;
            for (i = 0; i < 16; i++, entity++) {
                entity->flags |= FLAG_DEAD;
            }
            SetSubStep(4);
            posX = g_Tilemap.scrollX.i.hi + self->posX.i.hi;
            if ((u16)(posX - 0x60) > 0x140) {
                self->scaleY = 0x100;
                self->drawFlags |= ENTITY_SCALEY;
                SetSubStep(2);
            }
            break;
        case 2:
            if (!AnimateEntity(D_us_80180CC4, self)) {
                self->scaleY -= 0x20;
                if (!self->scaleY) {
                    self->drawFlags = ENTITY_DEFAULT;
                    self->animCurFrame = 0;
                    posX = self->posX.i.hi + g_Tilemap.scrollX.i.hi;
                    if (posX < 0x60) {
                        self->posX.i.hi += 0x60;
                    } else {
                        self->posX.i.hi -= 0x60;
                    }
                    SetSubStep(3);
                }
            }
            break;
        case 3:
            if (!AnimateEntity(D_us_80180CD0, self)) {
                SetSubStep(4);
            }
            break;
        case 4:
            D_us_80180BA8 |= 1;
            if (!AnimateEntity(D_us_80180D2C, self)) {
                self->step_s++;
            }
            break;
        case 5:
            entity = self + 1;
            DestroyEntity(entity);
            CreateEntityFromEntity(E_UNK_32, self, entity);
            entity->posY.i.hi = 0x1D0 - g_Tilemap.scrollY.i.hi;
            self->ext.olrox.timer = 3;
            entity->facingLeft = self->facingLeft ^ 1;
            self->ext.olrox.timer = 160;
            self->step_s++;
            break;
        case 6:
            if (!--self->ext.olrox.timer) {
                self->animCurFrame = 0;
                self->step = 64;
            }
            break;
        }
        break;
    case 32:
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
    self->hitboxOffX = 1;
    self->hitboxOffY = 1;
    self->hitboxWidth = 5;
    self->hitboxHeight = 28;
    if ((u16)self->animCurFrame - 0x2DU < 2) {
        self->hitboxWidth = 4;
        self->hitboxOffX = 0;
        self->hitboxOffY = 1;
        self->hitboxHeight = 18;
    }
    if ((u16)self->animCurFrame - 0x30U < 3) {
        self->hitboxOffY = 10;
        self->hitboxWidth = 4;
        self->hitboxOffX = 0;
        self->hitboxHeight = 13;
    }
}

void func_us_801AE858(Entity* self) {
    s32 i;
    s32 j;
    s16 u;
    s16 posX;
    s16 posY;
    s16 unk8A;
    u16 tpage;
    Primitive* prim;
    s32 primIndex;
    Primitive* prim2;
    s16* var_fp;
    Entity* entity;
    s16 var_s6;
    s16 var_s5;
    s16 var_s7;
    s16 var_s8;
    DRAWENV draw;

    entity = self->ext.olroxGroundBlast.entity;

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_801806F0);
        self->hitboxHeight = 0;
        self->hitboxWidth = 16;
        self->drawFlags |= ENTITY_SCALEX;
        self->drawFlags |= ENTITY_SCALEY;
        self->scaleY = 0;
        self->scaleX = 256;
        self->zPriority = self->zPriority + 12;
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 0x18);
        if (primIndex != -1) {
            self->flags |= FLAG_HAS_PRIMS;
            self->primIndex = primIndex;
            prim = &g_PrimBuf[primIndex];
            self->ext.olroxGroundBlast.prim7C = prim;
            for (i = 0; i < 2; i++) {
                prim->tpage = 0x13;
                prim->clut = 0x214;
                prim->u0 = prim->u2 = i * 24;
                prim->u1 = prim->u3 = prim->u0 + 23;
                prim->v0 = prim->v1 = 0x40;
                prim->v2 = prim->v3 = prim->v0 + 0x1E;
                prim->priority = self->zPriority + 0xA;
                prim->drawMode =
                    DRAW_TPAGE2 | DRAW_TPAGE | DRAW_UNK02 | DRAW_TRANSP;
                prim = prim->next;
            }

            for (i = 0; i < 8; i++) {
                prim->tpage = 0x12;
                prim->clut = 0x214;
                prim->u0 = prim->u2 = (i % 2) * 24 + 208;
                prim->u1 = prim->u3 = prim->u0 + 23;
                prim->v0 = prim->v1 = (i / 2) * 31 + 128;
                if (i < 2) {
                    prim->v0 += 1;
                    prim->v1 += 1;
                }

                prim->v2 = prim->v3 = prim->v0 + 31;
                prim->priority = self->zPriority + 0xA;
                prim->drawMode =
                    DRAW_TPAGE2 | DRAW_TPAGE | DRAW_UNK02 | DRAW_TRANSP;
                prim = prim->next;
            }

            for (i = 0; i < 2; i++) {
                prim->tpage = 0x13;
                prim->clut = 0x214;
                prim->u0 = prim->u2 = i * 24;
                prim->u1 = prim->u3 = prim->u0 + 23;
                prim->v0 = prim->v1 = 0x5E;
                prim->v2 = prim->v3 = prim->v0 - 0x1E;
                prim->priority = self->zPriority + 0xA;
                prim->drawMode =
                    DRAW_TPAGE2 | DRAW_TPAGE | DRAW_UNK02 | DRAW_TRANSP;
                prim = prim->next;
            }
            prim = self->ext.olroxGroundBlast.prim7C;
            for (i = 0; i < 6; i++) {
                prim = prim->next;
                u = prim->u0;
                prim->u0 = prim->u1;
                prim->u1 = u;
                u = prim->u2;
                prim->u2 = prim->u3;
                prim->u3 = u;
                prim = prim->next;
            }
            self->ext.olroxGroundBlast.prim = prim;
            while (prim != NULL) {
                prim->priority = self->zPriority + 8;
                prim->drawMode = DRAW_HIDE;
                prim = prim->next;
            }
        } else {
            DestroyEntity(self);
            return;
        }
        self->ext.olroxGroundBlast.timer = D_us_80180BF8[self->params];
        self->ext.olroxGroundBlast.timer2 = 24;
        self->ext.olroxGroundBlast.height = 0;
        break;

    case 1:
        if (AnimateEntity(D_us_80180D48, self) == 0) {
            SetStep(2);
            self->pose = Random() & 7;
        }

        if (self->scaleY < 256) {
            self->scaleY += 16;
        }
        break;

    case 2:
        AnimateEntity(D_us_80180D50, self);
        if (entity->ext.olrox.unk86) {
            if (self->ext.olroxGroundBlast.timer) {
                self->ext.olroxGroundBlast.timer--;
                return;
            }
            self->step++;
        }

        if (self->scaleY < 0x100) {
            self->scaleY += 16;
        }
        if (D_us_80180BA8) {
            DestroyEntity(self);
            return;
        }
        break;

    case 3:
        draw = g_CurrentBuffer->draw;
        tpage = 0x100;
        if (draw.ofs[0]) {
            tpage = 0x104;
        }

        prim = self->ext.olroxGroundBlast.prim;
        posX = self->posX.i.hi;
        posY = self->posY.i.hi;
        if (posY > 0xF0) {
            posY = 0xF0;
        }

        if (self->ext.olroxGroundBlast.timer2) {
            self->ext.olroxGroundBlast.timer2--;
            self->ext.olroxGroundBlast.height += 2;
        }
        prim->tpage = tpage;
        prim->u0 = prim->u2 = posX - 24;
        prim->u1 = prim->u3 = posX;
        prim->v0 = prim->v1 = 0;
        prim->v2 = prim->v3 = posY;
        prim->x0 = prim->x2 = posX - self->ext.olroxGroundBlast.timer2;
        prim->x1 = prim->x3 = posX;
        prim->y0 = prim->y1 = -self->ext.olroxGroundBlast.height;
        prim->y2 = prim->y3 = posY;
        prim->drawMode = DRAW_UNK02;
        prim = prim->next;

        prim->tpage = tpage;
        prim->u0 = prim->u2 = posX;
        prim->u1 = prim->u3 = posX + 0x18;
        prim->v0 = prim->v1 = 0;
        prim->v2 = prim->v3 = posY;
        prim->x0 = prim->x2 = posX;
        prim->x1 = prim->x3 = posX + self->ext.olroxGroundBlast.timer2;
        prim->y0 = prim->y1 = -self->ext.olroxGroundBlast.height;
        prim->y2 = prim->y3 = posY;
        prim->drawMode = DRAW_UNK02;
        prim = prim->next;

        if (!self->ext.olroxGroundBlast.timer2) {
            g_api.PlaySfx(SFX_BO0_UNK_7CA);
            self->ext.olroxGroundBlast.heights[0] = 0;
            self->ext.olroxGroundBlast.heights[1] = -0x20;
            self->ext.olroxGroundBlast.heights[2] = -0x40;
            self->ext.olroxGroundBlast.heights[3] = -0x60;
            self->ext.olroxGroundBlast.heights[4] = -0x80;
            self->ext.olroxGroundBlast.heights[5] = -0xA0;
            self->ext.olroxGroundBlast.heights[6] = -0xC0;
            self->step++;
        }
        break;
    case 4:
        AnimateEntity(D_us_80180D50, self);
        self->ext.olroxGroundBlast.heights[0] += 8;
        self->ext.olroxGroundBlast.heights[1] += 7;
        self->ext.olroxGroundBlast.heights[2] += 6;
        self->ext.olroxGroundBlast.heights[3] += 5;
        self->ext.olroxGroundBlast.heights[4] += 4;
        self->ext.olroxGroundBlast.heights[5] += 3;
        self->ext.olroxGroundBlast.heights[6] += 2;
        var_fp = &self->ext.olroxGroundBlast.heights[0];
        for (i = 0; i < 7; i++, var_fp++) {
            if (*var_fp > 0x280) {
                *var_fp = 0x280;
            }
        }
        var_fp = &self->ext.olroxGroundBlast.heights[0];
        prim = self->ext.olroxGroundBlast.prim7C;
        posX = self->posX.i.hi;
        posY = self->posY.i.hi;
        draw = g_CurrentBuffer->draw;
        if (draw.ofs[0]) {
            tpage = 0x104;
        } else {
            tpage = 0x100;
        }

        prim2 = self->ext.olroxGroundBlast.prim;
        for (i = 0; i < 6; i++) {
            unk8A = *var_fp;
            var_fp++;
            var_s6 = posY - unk8A;
            if (var_s6 > self->posY.i.hi) {
                var_s6 = self->posY.i.hi;
            }
            var_s8 = *var_fp;
            var_s5 = posY - var_s8;
            if (var_s5 > self->posY.i.hi) {
                var_s5 = self->posY.i.hi;
            }
            var_s7 = self->posX.i.hi;
            u = var_s7 - 0x18;
            for (j = 0; j < 2; j++) {
                prim->y0 = prim->y1 = var_s6;
                prim->y2 = prim->y3 = var_s5;
                prim->x1 = prim->x3 = var_s7;
                prim->x0 =
                    u + (4 * rcos((unk8A * 24) + j * ROT(180))) / ROT(360);
                prim->x2 =
                    u + (4 * rcos((var_s8 * 24) + j * ROT(180))) / ROT(360);
                prim2->tpage = tpage;
                prim2->u0 = prim2->u2 = u;
                prim2->u1 = prim2->u3 = var_s7;
                prim2->v0 = prim2->v1 = var_s6;
                prim2->v2 = prim2->v3 = var_s5;
                LOW(prim2->x0) = LOW(prim->x0);
                LOW(prim2->x1) = LOW(prim->x1);
                LOW(prim2->x2) = LOW(prim->x2);
                LOW(prim2->x3) = LOW(prim->x3);
                if (var_s6 < 0) {
                    prim2->v0 = prim2->v1 = 0;
                    prim2->y0 = prim2->y1 = 0;
                }
                if (var_s5 > 0xF0) {
                    prim2->v2 = prim2->v3 = 0xF0;
                    prim2->y2 = prim2->y3 = 0xF0;
                }
                if (prim2->x0 > 0x100) {
                    prim2->x0 = prim2->x2 = 0x100;
                    prim2->u0 = prim2->u2 = 0xFF;
                }
                if (prim2->x1 > 0x100) {
                    prim2->x1 = prim2->x3 = 0x100;
                    prim2->u1 = prim2->u3 = 0xFF;
                }
                if (prim2->x0 < 0) {
                    prim2->x0 = prim2->x2 = 0;
                    prim2->u0 = prim2->u2 = 0;
                }
                if (prim2->x1 < 0) {
                    prim2->x1 = prim2->x3 = 0;
                    prim2->u1 = prim2->u3 = 0;
                }
                prim2->drawMode = DRAW_DEFAULT;
                if (i == 5) {
                    prim2->drawMode = DRAW_HIDE;
                }
                prim2 = prim2->next;
                prim = prim->next;
                u += 48;
            }
        }

        if (self->ext.olroxGroundBlast.heights[1] > 0) {
            if (self->ext.olroxGroundBlast.heights[5] > 0) {
                posY = self->ext.olroxGroundBlast.heights[1] -
                       self->ext.olroxGroundBlast.heights[5];
                if (self->ext.olroxGroundBlast.heights[6] > 0) {
                    posY += ((self->ext.olroxGroundBlast.heights[5] -
                              self->ext.olroxGroundBlast.heights[6]) /
                             2);
                }
            } else {
                posY = self->ext.olroxGroundBlast.heights[1];
            }
            posY /= 2;

            if (posY > 0x100) {
                posY = 0xFF;
            }
            self->hitboxHeight = posY;
            self->hitboxOffY =
                -self->ext.olroxGroundBlast.heights[1] + self->hitboxHeight;
        }
        if (self->ext.olroxGroundBlast.heights[6] > 0) {
            if (self->scaleX) {
                self->scaleX -= 2;
            }
        }
        if (self->ext.olroxGroundBlast.heights[6] > 0x200) {
            DestroyEntity(self);
            return;
        }
        break;
    }
}

void func_us_801AF31C(Entity* self) {
    Primitive* prim;
    s32 primIndex;

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_801806FC);
        if (self->facingLeft) {
            self->posX.i.hi += 0x1C;
        } else {
            self->posX.i.hi -= 0x1C;
        }
        self->posY.i.hi -= 12;
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 1);
        if (primIndex != -1) {
            self->flags |= FLAG_HAS_PRIMS;
            self->primIndex = primIndex;
            prim = &g_PrimBuf[primIndex];
            self->ext.olroxBlast.prim = prim;
            prim->tpage = 0x12;
            prim->clut = 0x212;
            prim->u0 = prim->u2 = 0xA0;
            prim->u1 = prim->u3 = 0xD0;
            prim->v0 = prim->v1 = 0;
            prim->v2 = prim->v3 = 0x10;
            prim->x0 = prim->x2 = self->posX.i.hi;
            prim->x1 = prim->x3 = prim->x0;
            prim->y0 = prim->y1 = self->posY.i.hi;
            prim->y2 = prim->y3 = prim->y0;
            prim->r0 = prim->g0 = prim->b0 = 0;
            LOW(prim->r2) = LOW(prim->r0);
            prim->r1 = prim->g1 = prim->b1 = 0xA0;
            LOW(prim->r3) = LOW(prim->r1);
            prim->priority = self->zPriority + 4;
            prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS |
                             DRAW_UNK02 | DRAW_TRANSP;
        } else {
            DestroyEntity(self);
            return;
        }

        self->velocityY = 0;
        if (self->facingLeft) {
            self->velocityX = FIX(-0.5);
            self->ext.olroxBlast.length.i.hi = -0x30;
        } else {
            self->velocityX = FIX(0.5);
            self->ext.olroxBlast.length.i.hi = 0x30;
        }
        self->hitboxWidth = 0;
        self->hitboxHeight = 5;
        PlaySfxPositional(SFX_SCIFI_BLAST);
        break;

    case 1:
        MoveEntity();
        if (self->facingLeft) {
            self->velocityX -= FIX(0.125);
            self->ext.olroxBlast.length.val -= FIX(5);
        } else {
            self->velocityX += FIX(0.125);
            self->ext.olroxBlast.length.val += FIX(5);
        }
        prim = self->ext.olroxBlast.prim;
        prim->x1 = prim->x3 =
            self->posX.i.hi + self->ext.olroxBlast.length.i.hi;
        prim->x0 = prim->x2 = self->posX.i.hi;
        prim->y0 = prim->y1 = self->posY.i.hi - 8;
        prim->y2 = prim->y3 = prim->y0 + 16;

        self->hitboxWidth = abs(self->ext.olroxBlast.length.i.hi) / 4;
        self->hitboxOffX =
            abs(self->ext.olroxBlast.length.i.hi) - self->hitboxWidth - 4;
        break;
    }

    if (abs(self->posX.i.hi) > 0x280) {
        DestroyEntity(self);
    }
}

void func_us_801AF604(Entity* self) {
    Entity* entity;
    Entity* player;
    s16 angle;
    s16 offX, offY;

    if (D_us_80180BA8 != 0) {
        self->flags |= FLAG_DEAD;
    }

    if (self->flags & FLAG_DEAD) {
        PlaySfxPositional(SFX_EXPLODE_B);
        entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (entity != NULL) {
            CreateEntityFromEntity(E_ID(LASER_EXPLOSION), self, entity);
            entity->params = 2;
        }
        DestroyEntity(self);
        return;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_801806E4);
        self->hitboxState = 0;
        self->hitboxOffY = -1;
        self->drawFlags |= ENTITY_OPACITY;
        self->ext.olroxProjectile.heading = ((Random() & 0x3F) * 0x10) + 0x200;
        if (self->params != 0) {
            self->step = 2;
            self->hitboxState = 0;
            self->zPriority -= 1;
            self->blendMode |= BLEND_ADD | BLEND_TRANSP;
            return;
        }
        entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (entity != NULL) {
            CreateEntityFromEntity(E_UNK_2F, self, entity);
            entity->params = 1;
            entity->ext.olroxProjectile.parent = self;
        }
        break;
    case 1:
        if (self->opacity < 0x80) {
            self->hitboxState = 0;
            self->opacity += 4;
        } else {
            self->hitboxState = 3;
        }
        AnimateEntity(D_us_80180D74, self);
        MoveEntity();
        if (self->velocityX > 0) {
            self->facingLeft = true;
        } else {
            self->facingLeft = false;
        }
        player = &PLAYER;
        offX = player->posX.i.hi - self->posX.i.hi;
        offY = player->posY.i.hi - self->posY.i.hi;
        offY -= 32;
        angle = ratan2(-offY, offX);
        angle = func_us_801AD26C(8, self->ext.olroxProjectile.heading, angle);
        self->velocityX = FLT_TO_FIX(rcos(angle));
        self->velocityY = rsin(angle) * -16;
        self->ext.olroxProjectile.heading = (u16)angle;
        break;
    case 2:
        AnimateEntity(D_us_80180D68, self);
        entity = self->ext.olroxProjectile.parent;
        self->posX.i.hi = entity->posX.i.hi;
        self->posY.i.hi = entity->posY.i.hi;
        self->opacity = entity->opacity;
        if (!entity->entityId) {
            DestroyEntity(self);
        }
        break;
    }
}

void func_us_801AF8C0(Entity* self) {
    Entity* entity;

    entity = self->ext.olroxProjectile.parent;
    if (entity->flags & FLAG_DEAD) {
        self->flags |= FLAG_DEAD;
        self->step = 3;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitOlroxAfterImage);
        self->animCurFrame = 0x54;
        self->drawFlags |= ENTITY_SCALEY | ENTITY_SCALEX;
        self->scaleX = self->scaleY = 0;
        self->zPriority -= 1;
        self->hitboxState = 0;
        break;
    case 1:
        AnimateEntity(D_us_80180D7C, self);
        if (self->scaleX < 256) {
            self->scaleX = self->scaleY += 8;
        } else {
            self->scaleX = self->scaleY = 256;
            self->step++;
        }
        break;
    case 2:
        AnimateEntity(D_us_80180D7C, self);
        if (g_Timer % 12 == 0) {
            entity = AllocEntity(&g_Entities[160], &g_Entities[168]);
            if (entity != NULL) {
                CreateEntityFromEntity(E_ID(UNK_2F), self, entity);
                entity->ext.olroxProjectile.parent = self;
                PlaySfxPositional(SFX_SMALL_FLAME_IGNITE);
            }
        }
        if (g_Timer % 5) {
            self->palette = PAL_FLAG(0x213);
        } else {
            self->palette = PAL_FLAG(0x215);
        }
        entity = self->ext.olroxProjectile.parent;
        if (entity->ext.olrox.unk85) {
            self->step++;
        }
        break;
    case 3:
        AnimateEntity(D_us_80180D7C, self);
        self->scaleX = self->scaleY -= 8;
        if (self->scaleX < 0) {
            DestroyEntity(self);
        }
        break;
    }
}

void func_us_801AFAF4(Entity* self) {
    Entity* entity;
    u8 angle2;
    s32 distX;
    s32 distY;
    s32 posX;
    s16 angle;
    s16 offsetX;
    s16 offsetY;
    s32 distance;

    entity = self->ext.olroxProjectile.parent;
    if (entity->flags & FLAG_DEAD) {
        self->flags |= FLAG_DEAD;
    }
    if (self->flags & FLAG_DEAD) {
        entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (entity) {
            CreateEntityFromEntity(E_EXPLOSION, self, entity);
            entity->params = 2;
        }
        DestroyEntity(self);
        PlaySfxPositional(SFX_BAT_SCREECH);
        return;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_801806D8);
        self->hitboxState = 0;
        self->hitboxOffX = 1;
        self->hitboxOffY = 1;
        entity = self->ext.olroxProjectile.parent;
        self->zPriority = entity->zPriority + 2;
        self->palette = 0x219;
        self->pose = (Random() & 3) * 2;
        self->ext.olroxProjectile.timer = (self->params + 1) * 14;
        self->drawFlags |= ENTITY_SCALEY | ENTITY_SCALEX;
        self->params = Random() & 3;
        break;

    case 1:
        AnimateEntity(D_us_80180D38, self);
        posX = self->posX.i.hi;
        entity = self->ext.olroxProjectile.parent;

        offsetX = entity->posX.i.hi;
        offsetY = entity->posY.i.hi;
        offsetY -= 32;

        distX = self->posX.i.hi - offsetX;
        distY = self->posY.i.hi - offsetY;

        angle = ratan2(-distY, distX);
        if (entity->facingLeft) {
            angle += ROT(45.0 / 32.0);
        } else {
            angle -= ROT(45.0 / 32.0);
        }

        distance = SQ(distX) + SQ(distY);
        distance = SquareRoot0(distance);
        distance -= 2;
        self->posX.i.hi = offsetX + (distance * rcos(angle)) / 4096;
        self->posY.i.hi = offsetY - (distance * rsin(angle) / 4096);
        self->scaleX = (distance * self->params) + 0x100;
        if (self->scaleX > 0x300) {
            self->scaleX = 0x300;
        }
        self->scaleY = self->scaleX;
        posX = self->posX.i.hi - posX;
        if (posX > 0) {
            self->facingLeft = false;
        } else {
            self->facingLeft = true;
        }
        if (distance < 8) {
            self->ext.olroxProjectile.angle = Random();
            self->palette = 0x209;
            self->hitboxState = 3;
            self->drawFlags = ENTITY_DEFAULT;
            self->step++;
        }
        break;

    case 2:
        entity = self->ext.olroxProjectile.parent;
        AnimateEntity(D_us_80180D38, self);
        MoveEntity();
        if (self->velocityX > 0) {
            self->facingLeft = true;
            self->zPriority = entity->zPriority + 2;
        } else {
            self->facingLeft = false;
            self->zPriority = entity->zPriority - 2;
        }
        offsetX = entity->posX.i.hi;
        offsetY = entity->posY.i.hi;
        offsetX = offsetX - self->posX.i.hi;
        offsetY = offsetY - self->posY.i.hi;
        angle2 = Ratan2Shifted(offsetX, offsetY);
        self->ext.olroxProjectile.angle = AdjustValueWithinThreshold(
            2, self->ext.olroxProjectile.angle, angle2);
        SetEntityVelocityFromAngle(self->ext.olroxProjectile.angle, 0x10);
        if (entity->ext.olrox.unk84) {
            if (!--self->ext.olroxProjectile.timer) {
                entity = &PLAYER;
                angle2 = GetAngleBetweenEntitiesShifted(self, entity);
                SetEntityVelocityFromAngle(angle2, 32);
                self->step++;
            }
        }
        break;

    case 3:
        AnimateEntity(D_us_80180D38, self);
        MoveEntity();
        if (self->velocityX > 0) {
            self->facingLeft = false;
        } else {
            self->facingLeft = true;
        }

        if (abs(self->posX.i.hi) > 0x200 || abs(self->posY.i.hi) > 0x200) {
            DestroyEntity(self);
        }
        break;
    }
}

void EntityOlroxAfterImage(Entity* self) {
    if (!self->step) {
        InitializeEntity(g_EInitOlroxAfterImage);
        self->palette = 0x217;
        self->drawFlags = ENTITY_OPACITY;
        self->opacity = 0x80;
        self->hitboxState = 0;
        self->blendMode = BLEND_TRANSP | BLEND_ADD;
        self->animCurFrame = self->params;
        self->zPriority -= 2;
    }
    self->opacity += 0xFE;
    if (!self->opacity) {
        DestroyEntity(self);
    }
}

typedef enum FurnitureType {
    FURNITURE_TABLE = 0x5,
    FURNITURE_FACING_LEFT = 0x100,
} FurnitureType;

// EntityFurniture
void func_us_801B001C(Entity* self) {
    s32 i;
    Entity* entity;
    s32 furnitureType;
    s16* furnitureInit;
    s32 posX;
    s32 posY;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
        self->animSet = -0x7FFA;
        self->unk5A = 0x48;
        self->palette = 0x209;
        self->hitboxState = 2;
        if (self->params & 0x100) {
            self->facingLeft = true;
        }
        self->zPriority -= 4;
        if (self->params == 1) {
            D_us_80180BA8 = 0;
        }
        furnitureType = self->params & 0xFF;
        self->animCurFrame = furnitureType;
        if (furnitureType < 5) {
            furnitureInit = D_us_80180D94;
            furnitureInit += (furnitureType - 1) * 6;
            self->hitboxWidth = *furnitureInit++;
            self->hitboxHeight = *furnitureInit++;
            self->hitboxOffX = *furnitureInit++;
            self->hitboxOffY = *furnitureInit++;
            self->hitPoints = *furnitureInit++;
            self->zPriority = *furnitureInit++;
            return;
        }
        self->step += furnitureType;
        break;

    case 1:
        if (self->flags & FLAG_DEAD) {
            self->hitboxState = 0;
            self->step += self->params & 0xFF;
        }
        break;

    case 2:
        self->animCurFrame = 0xA;
        if (GetSideToPlayer() & 1) {
            self->velocityX = FIX(1.0);
        } else {
            self->velocityX = FIX(-1.0);
        }
        self->step = 11;
        break;
    case 3:
        // when table is destroyed?
        for (i = 0; i < 4; i++) {
            entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (entity != NULL) {
                CreateEntityFromEntity(E_UNK_2A, self, entity);
                entity->params = i + 5;
                entity->posX.i.hi += i * -30 + 48;
            }
        }
        if (entity) {
            entity->params = FURNITURE_FACING_LEFT | FURNITURE_TABLE;
        }

        for (i = 0; i < 4; i++) {
            entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (entity != NULL) {
                CreateEntityFromEntity(E_EXPLOSION, self, entity);
                entity->params = 0x13;
                entity->posX.i.hi += i * -30 + 48;
            }
        }
        entity = self;
        entity++;
        for (i = 0; i < 3; i++, entity++) {
            entity->flags |= FLAG_DEAD;
        }
        self->animCurFrame = 0;
        self->step = 0x20;
        break;
    case 4:
        // chairs?
        for (i = 0; i < 2; i++) {
            entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (entity != NULL) {
                CreateEntityFromEntity(E_UNK_2A, self, entity);
                entity->params = i + 8;
                entity->posY.i.hi += (i * 8);
                if (i != 0) {
                    if (GetSideToPlayer() & 1) {
                        entity->velocityX = FIX(0.5);
                    } else {
                        entity->velocityX = FIX(-0.5);
                    }
                    entity->velocityY = FIX(-1);
                }
            }
        }
        PlaySfxPositional(SFX_SMALL_FLAME_IGNITE);
        self->animCurFrame = 0;
        self->step = 0x20;
        break;
    case 5:
        // candles?
        for (i = 0; i < 3; i++) {
            entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (entity != NULL) {
                CreateEntityFromEntity(E_UNK_2A, self, entity);
                entity->params = i + 0xB;
                entity->posY.i.hi += i * 28 - 28;
            }
        }
        PlaySfxPositional(SFX_CANDLE_HIT_WHOOSH_B);
        self->animCurFrame = 0;
        self->step = 32;
        break;
    case 6:
        self->zPriority = 0x6A;
        break;
    case 7:
    case 8:
        self->zPriority = 0x6A;
        MoveEntity();
        self->velocityY += FIX(0.0625);
        posX = self->posX.i.hi;
        posY = self->posY.i.hi;
        posY += 8;
        if (func_us_801AD2F0(posX, posY)) {
            self->step = 32;
        }
        break;
    case 9:
        self->drawFlags |= ENTITY_ROTATE;
        self->rotate -= 16;
        self->zPriority = 0x6C;
        MoveEntity();
        self->velocityY += FIX(0.09375);
        posX = self->posX.i.hi;
        posY = self->posY.i.hi;
        posY += 4;
        if (func_us_801AD2F0(posX, posY)) {
            self->entityId = 2;
            self->pfnUpdate = EntityExplosion;
            self->params = 0;
            self->step = 0;
        }
        break;
    case 10:
        self->drawFlags |= ENTITY_ROTATE;
        self->rotate += ROT(11.25);
        self->zPriority = 0x6C;
        MoveEntity();
        self->velocityY += FIX(0.125);
        posX = self->posX.i.hi;
        posY = self->posY.i.hi;
        if (func_us_801AD2F0(posX, posY)) {
            self->entityId = 2;
            self->pfnUpdate = EntityExplosion;
            self->step = 0;
            self->params = 0;
        }
        break;
    case 11:
        self->zPriority = 0x6A;
        MoveEntity();
        self->velocityY += FIX(0.0625);
        posX = self->posX.i.hi;
        posY = self->posY.i.hi;
        posY += 10;
        if (func_us_801AD2F0(posX, posY)) {
            self->step = 0x20;
        }
        break;
    case 12:
        self->rotate -= ROT(4.21875);
        // fallthrough
    case 13:
        self->drawFlags |= ENTITY_ROTATE;
        self->rotate += 40;
        self->zPriority = 0x6B;
        MoveEntity();
        self->velocityY += FIX(0.09375);
        posX = self->posX.i.hi;
        posY = self->posY.i.hi;
        posY += 6;
        if (func_us_801AD2F0(posX, posY)) {
            self->entityId = 2;
            self->pfnUpdate = EntityExplosion;
            self->params = 0;
            self->step = 0;
        }
        break;
    case 14:
        self->zPriority = 0x6A;
        break;
    }
}
