// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rdai.h"

#include "../step_towards.h"

extern EInit g_EInitSpectralSwordRDAI;
extern u8 D_us_80181914[];

void func_us_801C0C44(Entity* self) {
    Entity* entity;
    Primitive* prim;
    s32 i;
    s32 primIndex;
    s32 posX;
    s32 posY;
    s32 offset;
    s32 distance;
    s32 angle;
    s32 spearAngle;
    s32 count;

    if ((self->flags & FLAG_DEAD) && self->step < 8) {
        SetStep(8);
    }
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitSpectralSwordRDAI);
        self->animCurFrame = 1;
        self->blendMode = BLEND_TRANSP | BLEND_ADD;
        self->hitboxOffX = 0;
        self->hitboxOffY = 4;
        primIndex = g_api.AllocPrimitives(PRIM_TILE, 1);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.rdaiSpectralSword.prim = prim;
        self->flags |= FLAG_HAS_PRIMS;
        prim->u0 = prim->v0 = 2;
        PGREY(prim, 0) = 0xC0;
        prim->priority = 0xC0;
        prim->drawMode = DRAW_HIDE | DRAW_UNK02;
        entity = self + 1;
        for (i = 0; i < 6; i++, entity++) {
            CreateEntityFromCurrentEntity(E_UNK_24, entity);
            entity->params = i;
            entity->params = i | (D_us_80181914[i] << 8);
        }
        for (i = 0; i < 4; i++, entity++) {
            CreateEntityFromCurrentEntity(E_UNK_25, entity);
            entity->params = i;
        }
        SetStep(2);
        self->ext.rdaiSpectralSword.closeTimer = 0x40;
        self->ext.rdaiSpectralSword.attackTimer = 0x40;
        self->ext.rdaiSpectralSword.spearCount = 6;
        self->ext.rdaiSpectralSword.shieldCount = 4;
        break;
    case 2:
        distance = GetDistanceToPlayerX();
        if (distance < 0x60) {
            SetStep(3);
        }
        break;
    case 3:
        SetStep(6);
        // Reusing this temporary preserves the original register allocation.
        posY = GetSideToPlayer();
        self->ext.rdaiSpectralSword.direction = posY & 1;
        break;
    case 6:
        if (!self->step_s) {
            angle = Random() * 2;
            if (self->ext.rdaiSpectralSword.direction) {
                angle += 0x100;
            } else {
                angle += 0x500;
            }
            posX = rcos(angle);
            posX = (posX * 0x60) >> 12;
            posY = rsin(angle);
            posY = -(posY * 0x60) >> 12;
            prim = self->ext.rdaiSpectralSword.prim;
            posX = prim->x0 = PLAYER.posX.i.hi + posX;
            posY = prim->y0 = PLAYER.posY.i.hi + posY;
            angle = ratan2(posY - self->posY.i.hi, posX - self->posX.i.hi);
            self->velocityX = rcos(angle) * 12;
            self->velocityY = rsin(angle) * 12;
            self->ext.rdaiSpectralSword.timer = 0x80;
            self->step_s++;
        }
        MoveEntity();
        prim = self->ext.rdaiSpectralSword.prim;
        posX = prim->x0 - self->posX.i.hi;
        posY = prim->y0 - self->posY.i.hi;
        posX = abs(posX);
        posY = abs(posY);
        if ((posX < 8 && posY < 8) || !--self->ext.rdaiSpectralSword.timer) {
            self->step_s = 0;
        }
        posX = PLAYER.posX.i.hi - self->posX.i.hi;
        if (self->ext.rdaiSpectralSword.direction) {
            posX = -posX;
        }
        if (posX > 0x80) {
            self->velocityY = 0;
            if (self->ext.rdaiSpectralSword.direction) {
                self->velocityX = FIX(-0.75);
            } else {
                self->velocityX = FIX(0.75);
            }
        }
        if (posX < 0x40) {
            self->velocityY = 0;
            if (self->ext.rdaiSpectralSword.direction) {
                self->velocityX = FIX(0.75);
            } else {
                self->velocityX = FIX(-0.75);
            }
            if (!--self->ext.rdaiSpectralSword.closeTimer) {
                SetStep(5);
            }
        } else {
            self->ext.rdaiSpectralSword.closeTimer = 0x40;
        }
        if (self->ext.rdaiSpectralSword.spearCount &&
            !--self->ext.rdaiSpectralSword.attackTimer) {
            switch (Random() & 3) {
            case 0:
            case 1:
                self->ext.rdaiSpectralSword.attackTimer = 0x100;
                count = Random() % self->ext.rdaiSpectralSword.spearCount + 1;
                entity = self + 1;
                for (i = 0; i < 6; i++, entity++) {
                    if (!(entity->flags & FLAG_DEAD)) {
                        count--;
                    }
                    if (!count) {
                        break;
                    }
                }
                entity->ext.rdaiSpectralSword.attack = 1;
                break;
            case 2:
                self->ext.rdaiSpectralSword.attackTimer = 0x180;
                angle = GetAngleBetweenEntities(self, &PLAYER);
                entity = self + 1;
                for (i = 0; i < 6; i++, entity++) {
                    entity->ext.rdaiSpectralSword.attack = 3;
                    entity->ext.rdaiSpectralSword.attackAngle = angle;
                }
                break;
            case 3:
                self->ext.rdaiSpectralSword.attackTimer = 0x280;
                count = 0x40;
                entity = self + 1;
                for (i = 0; i < 6; i++, entity++) {
                    if (!(entity->flags & FLAG_DEAD)) {
                        entity->ext.rdaiSpectralSword.attack = 5;
                        entity->ext.rdaiSpectralSword.attackTimer = count;
                        count += 0x40;
                    }
                }
                break;
            }
        }
        break;
    case 5:
        switch (self->step_s) {
        case 0:
            angle = ratan2(0x40 - self->posY.i.hi, 0x80 - self->posX.i.hi);
            self->velocityX = rcos(angle) * 0x30;
            self->velocityY = rsin(angle) * 0x30;
            self->ext.rdaiSpectralSword.direction ^= 1;
            self->step_s++;
            break;
        case 1:
            MoveEntity();
            posX = self->posX.i.hi;
            if (self->ext.rdaiSpectralSword.direction) {
                if (posX > 0x80) {
                    self->velocityX = FIX(3);
                    self->step_s++;
                }
            } else if (posX < 0x80) {
                self->velocityX = FIX(-3);
                self->step_s++;
            }
            break;
        case 2:
            MoveEntity();
            self->velocityY += FIX(0.125);
            posX = PLAYER.posX.i.hi - self->posX.i.hi;
            if (self->ext.rdaiSpectralSword.direction) {
                posX = -posX;
            }
            if (posX > 0x70) {
                SetStep(6);
            }
            break;
        }
        break;
    case 8:
        switch (self->step_s) {
        case 0:
            self->hitboxState = 0;
            entity = self + 1;
            for (i = 0; i < 10; i++, entity++) {
                entity->flags |= FLAG_DEAD;
            }
            self->rotate = 0;
            self->drawFlags |= ENTITY_ROTATE;
            PlaySfxPositional(SFX_STUTTER_EXPLODE_A);
            self->step_s++;
            break;
        case 1:
            MoveEntity();
            self->velocityY += FIX(0.09375);
            self->rotate -= 4;
            if (!(g_Timer & 7)) {
                entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (entity != NULL) {
                    CreateEntityFromEntity(E_EXPLOSION, self, entity);
                    entity->params = 3;
                }
            }
            if (self->posY.i.hi > 0x160) {
                self->animCurFrame = 0;
                self->step_s++;
            }
            break;
        case 2:
            count = 0;
            entity = self + 1;
            for (i = 0; i < 10; i++, entity++) {
                if (!entity->animCurFrame) {
                    count++;
                }
            }
            if (count == 10) {
                entity = self;
                for (i = 0; i < 11; i++, entity++) {
                    DestroyEntity(entity);
                }
                return;
            }
            break;
        }
        break;
    }

    if (!(self->flags & FLAG_DEAD)) {
        posX = PLAYER.posX.i.hi - self->posX.i.hi;
        posY = PLAYER.posY.i.hi - self->posY.i.hi;
        angle = ratan2(posY, posX);
        spearAngle = angle + 0x400;
        distance = SquareRoot0(posX * posX + posY * posY);
        posX = self->posX.val;
        posY = self->posY.val;
        entity = self + 1;
        offset = -0x30;
        for (i = 0; i < 6; i++, entity++) {
            entity->ext.rdaiSpectralSword.targetPos.x.val =
                posX + offset * rcos(spearAngle) * 16;
            entity->ext.rdaiSpectralSword.targetPos.y.val =
                posY + offset * rsin(spearAngle) * 16;
            offset += 0x10;
            if (!offset) {
                offset = 0x10;
            }
        }
        distance /= 2;
        if (distance < 0x20) {
            distance = 0x20;
        }
        if (distance > 0x48) {
            distance = 0x48;
        }
        posX += distance * rcos(angle) * 16;
        posY += distance * rsin(angle) * 16;
        offset = -(self->ext.rdaiSpectralSword.shieldCount >> 1) * 0x18;
        for (i = 0; i < 4; i++, entity++) {
            if (!(entity->flags & FLAG_DEAD)) {
                entity->ext.rdaiSpectralSword.attackAngle = angle;
                entity->ext.rdaiSpectralSword.targetPos.x.val =
                    posX + offset * rcos(angle + 0x400) * 16;
                entity->ext.rdaiSpectralSword.targetPos.y.val =
                    posY + offset * rsin(angle + 0x400) * 16;
                offset += 0x18;
            }
        }
        if (!(self->flags & 0xF)) {
            if (g_Timer & 1) {
                self->palette = PAL_SPECTRAL_SWORD;
            } else {
                self->palette = PAL_SPECTRAL_SWORD + 1;
            }
        }
        if (!(g_Timer & 0xF)) {
            entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (entity != NULL) {
                CreateEntityFromEntity(E_UNK_23, self, entity);
                entity->ext.et_801CEB08.unk80 = self;
                entity->zPriority = self->zPriority + 1;
            }
        }
    }
}

#include "../e_spectral_sword_aura.h"

extern EInit g_EInitSpear;

void func_us_801C17E8(Entity* self) {
    Entity* entity;
    s32 deltaX;
    s32 deltaY;
    s32 distance;
    s32 side;
    s32 velocityX;
    s32 velocityY;
    s16 angle;
    s32 index;
    s32 spearIndex;
    s16 hitboxRadius;

    if ((self->flags & FLAG_DEAD) && self->step < 8) {
        SetStep(8);
    }
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitSpear);
        self->drawFlags = ENTITY_ROTATE;
        if (self->params & 0x100) {
            self->animCurFrame = 4;
        } else {
            self->animCurFrame = 5;
        }
        SetStep(2);
        break;
    case 2:
        MoveEntity();
        deltaX = self->ext.rdaiSpectralSword.targetPos.x.i.hi - self->posX.i.hi;
        deltaY = self->ext.rdaiSpectralSword.targetPos.y.i.hi - self->posY.i.hi;
        distance = SquareRoot0(deltaX * deltaX + deltaY * deltaY);
        if (distance > 0x38) {
            distance = 0x38;
        }
        angle = ratan2(deltaY, deltaX);
        self->velocityX = distance * rcos(angle);
        self->velocityY = distance * rsin(angle);
        angle = GetAngleBetweenEntities(self, &PLAYER) - 0x400;
        StepTowards(&self->rotate, angle, 0x10);
        if (self->ext.rdaiSpectralSword.attack) {
            if (!(self->ext.rdaiSpectralSword.attack & 4) ||
                !--self->ext.rdaiSpectralSword.attackTimer) {
                SetStep(4);
            }
        }
        break;
    case 4:
        switch (self->step_s) {
        case 0:
            if (!(self->ext.rdaiSpectralSword.attack & 2)) {
                self->ext.rdaiSpectralSword.attackAngle =
                    GetAngleBetweenEntities(self, &PLAYER);
            }
            self->velocityX =
                rcos(self->ext.rdaiSpectralSword.attackAngle - 0x800) * 32;
            self->velocityY =
                rsin(self->ext.rdaiSpectralSword.attackAngle - 0x800) * 32;
            index = (u8)self->params;
            spearIndex = index;
            index = (index * 4) / 6;
            entity = (self - spearIndex) + (index + 6);
            if (self->ext.rdaiSpectralSword.attack & 2) {
                entity->ext.rdaiSpectralSword.attack = 2;
            } else {
                entity->ext.rdaiSpectralSword.attack = 1;
            }
            self->step_s++;
            break;
        case 1:
            MoveEntity();
            deltaX = self->velocityX -= self->velocityX / 16;
            deltaY = self->velocityY -= self->velocityY / 16;
            if (abs(deltaX) < FIX(0.125) && abs(deltaY) < FIX(0.125)) {
                self->step_s++;
            }
            angle = ratan2(deltaY, deltaX) - 0x400;
            StepTowards(&self->rotate, angle, 8);
            break;
        case 2:
            angle = self->ext.rdaiSpectralSword.attackAngle;
            if (StepTowards(&self->rotate, angle - 0x400, 0x20)) {
                self->velocityX = rcos(angle) * 128;
                self->velocityY = rsin(angle) * 128;
                self->ext.rdaiSpectralSword.timer = 0x30;
                PlaySfxPositional(SFX_WEAPON_SWISH_A);
                self->step_s++;
            }
            break;
        case 3:
            MoveEntity();
            side = GetSideToPlayer();
            velocityX = self->velocityX;
            velocityY = self->velocityY;
            if (abs(velocityX) > abs(velocityY)) {
                side &= 1;
                if (velocityX < 0) {
                    side ^= 1;
                }
            } else {
                side &= 2;
                if (velocityY < 0) {
                    side ^= 2;
                }
            }
            if (side || !--self->ext.rdaiSpectralSword.timer) {
                self->ext.rdaiSpectralSword.attack = 0;
                SetStep(2);
            }
            break;
        }
        break;
    case 8:
        switch (self->step_s) {
        case 0:
            entity = self - ((u8)self->params + 1);
            entity->ext.rdaiSpectralSword.spearCount += 0xFF;
            self->hitboxState = 0;
            PlaySfxPositional(SFX_QUICK_STUTTER_EXPLODE_B);
            self->step_s++;
            // fallthrough
        case 1:
            MoveEntity();
            self->velocityY += FIX(0.125);
            if (!(g_Timer & 7)) {
                entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (entity != NULL) {
                    CreateEntityFromEntity(E_EXPLOSION, self, entity);
                    entity->params = 1;
                }
            }
            if (self->posY.i.hi > 0x140) {
                self->animCurFrame = 0;
                self->step_s++;
            }
            break;
        case 2:
            self->animCurFrame = 0;
            break;
        }
        break;
    }
    hitboxRadius = 0x16;
    angle = self->rotate + 0x400;
    if (self->params & 0x100) {
        hitboxRadius = 0x18;
    }
    self->hitboxOffX = (hitboxRadius * rcos(angle)) >> 12;
    self->hitboxOffY = (hitboxRadius * rsin(angle)) >> 12;
}

extern EInit g_EInitShield;
extern u8 D_us_8018191C[];
extern u8 D_us_80181924[];
extern u8 D_us_8018192C[];

void func_us_801C1DE8(Entity* self) {
    Entity* entity;
    s32 distance;
    s32 deltaX;
    s32 deltaY;
    s16 angle;
    s32 animStatus;

    if ((self->flags & FLAG_DEAD) && self->step < 8) {
        SetStep(8);
    }
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitShield);
        self->animCurFrame = 7;
        self->zPriority += 2;
        SetStep(3);
        break;
    case 2:
        self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        deltaX = GetDistanceToPlayerX();
        self->animCurFrame = 8;
        if (deltaX < 0x40) {
            self->animCurFrame = 7;
        }
        if (deltaX < 0x20) {
            self->animCurFrame = 6;
        }
        break;
    case 3:
        MoveEntity();
        if (self->animCurFrame != 8) {
            AnimateEntity(D_us_8018192C, self);
        }
        deltaX = self->ext.rdaiSpectralSword.targetPos.x.i.hi - self->posX.i.hi;
        deltaY = self->ext.rdaiSpectralSword.targetPos.y.i.hi - self->posY.i.hi;
        distance = SquareRoot0(deltaX * deltaX + deltaY * deltaY);
        if (distance > 0x38) {
            distance = 0x38;
        }
        angle = ratan2(deltaY, deltaX);
        self->velocityX = distance * rcos(angle);
        self->velocityY = distance * rsin(angle);
        if (self->animCurFrame != 6) {
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        }
        if (self->ext.rdaiSpectralSword.attack) {
            SetStep(4);
        }
        break;
    case 4:
        switch (self->step_s) {
        case 0:
            self->velocityX =
                rcos(self->ext.rdaiSpectralSword.attackAngle - 0x800) * 32;
            self->velocityY =
                rsin(self->ext.rdaiSpectralSword.attackAngle - 0x800) * 32;
            self->step_s++;
            // fallthrough
        case 1:
            MoveEntity();
            if (self->ext.rdaiSpectralSword.attack & 2) {
                animStatus = AnimateEntity(D_us_80181924, self);
            } else {
                animStatus = AnimateEntity(D_us_8018191C, self);
            }
            if (!animStatus) {
                self->ext.rdaiSpectralSword.timer = 0x20;
                self->step_s++;
            }
            break;
        case 2:
            if (!--self->ext.rdaiSpectralSword.timer) {
                self->ext.rdaiSpectralSword.attack = 0;
                SetStep(3);
            }
            break;
        }
        break;
    case 8:
        switch (self->step_s) {
        case 0:
            entity = self - (self->params + 7);
            entity->ext.rdaiSpectralSword.shieldCount += 0xFF;
            self->hitboxState = 0;
            PlaySfxPositional(SFX_METAL_CLANG_C);
            PlaySfxPositional(SFX_QUICK_STUTTER_EXPLODE_B);
            self->step_s++;
            // fallthrough
        case 1:
            MoveEntity();
            self->velocityY += FIX(0.125);
            if (!(g_Timer & 7)) {
                entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (entity != NULL) {
                    CreateEntityFromEntity(E_EXPLOSION, self, entity);
                    entity->params = 1;
                }
            }
            if (self->posY.i.hi > 0x140) {
                self->animCurFrame = 0;
                self->step_s++;
            }
            break;
        case 2:
            self->animCurFrame = 0;
            break;
        }
        break;
    }
}
