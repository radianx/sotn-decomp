// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rbo2.h"

extern s32 g_BossMgrState;
extern EInit D_us_801804B8;
extern EInit D_us_801804C4;
extern u8 D_us_80180770[];

void func_us_8019D4CC(Entity* self) {
    Entity* entity;
    s32 posX;
    s32 posY;
    s16 targetAngle;
    s32 distance;
    s16 angle;

    FntPrint("skull_step %x\n", self->step);
    if (g_BossMgrState & BOSS_MGR_DEATH_FIRST_FORM_DEFEAT) {
        entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (entity != NULL) {
            CreateEntityFromEntity(E_EXPLOSION, self, entity);
            entity->params = 1;
        }
        DestroyEntity(self);
        return;
    }
    switch (self->step) {
    case 0:
        InitializeEntity(D_us_801804B8);
        self->drawFlags = ENTITY_SCALEX | ENTITY_SCALEY;
        self->blendMode = BLEND_TRANSP | BLEND_ADD;
        self->scaleY = 0;
        self->scaleX = 0;
        // fallthrough
    case 1:
        entity = self->ext.deathBossProjectile.owner;
        self->posX.i.hi = entity->posX.i.hi;
        self->posY.i.hi = entity->posY.i.hi;
        AnimateEntity(D_us_80180770, self);
        self->scaleX += 12;
        if (self->scaleX > 0x100) {
            self->hitboxState = 1;
            self->ext.deathBossProjectile.timer = 0x80;
            self->drawFlags = ENTITY_DEFAULT;
            self->ext.deathBossProjectile.angle = 0x400;
            self->step++;
        }
        self->scaleY = self->scaleX;
        if (g_BossMgrState & 4) {
            DestroyEntity(self);
        }
        break;
    case 2:
        AnimateEntity(D_us_80180770, self);
        MoveEntity();
        entity = &PLAYER;
        posX = entity->posX.i.hi;
        posY = entity->posY.i.hi;
        posX = ratan2(posY - self->posY.i.hi, posX - self->posX.i.hi);
        angle = posX;
        angle =
            LimitAngleChange(0x20, self->ext.deathBossProjectile.angle, angle);
        targetAngle = angle;
        self->velocityX = (rcos(angle) * FIX(3)) >> 12;
        self->velocityY = (rsin(angle) * FIX(3)) >> 12;
        self->ext.deathBossProjectile.angle = targetAngle;
        self->ext.deathBossProjectile.timer--;
        posX = PLAYER.posX.i.hi - self->posX.i.hi;
        if (self->facingLeft) {
            posX = -posX;
        }
        if (!self->ext.deathBossProjectile.timer || (posX < 0) ||
            (self->hitFlags & 0x80)) {
            self->step++;
        }
        if (!(g_Timer & 3)) {
            entity = AllocEntity(&g_Entities[208], &g_Entities[256]);
            if (entity != NULL) {
                CreateEntityFromEntity(E_UNK_1A, self, entity);
                entity->params = self->animCurFrame;
                entity->facingLeft = self->facingLeft;
            }
        }
        if (g_BossMgrState & 4) {
            SetStep(5);
        }
        break;
    case 3:
        AnimateEntity(D_us_80180770, self);
        MoveEntity();
        entity = self->ext.deathBossProjectile.target;
        posX = entity->posX.i.hi;
        posY = entity->posY.i.hi;
        posX -= self->posX.i.hi;
        posY -= self->posY.i.hi;
        angle = ratan2(posY, posX);
        targetAngle = angle;
        distance = SquareRoot0(posX * posX + posY * posY);
        if (distance > 0x20) {
            targetAngle = LimitAngleChange(
                0x60, self->ext.deathBossProjectile.angle, (s16)targetAngle);
        }
        self->velocityX = (rcos((s16)targetAngle) * FIX(3)) >> 12;
        self->velocityY = (rsin((s16)targetAngle) * FIX(3)) >> 12;
        self->ext.deathBossProjectile.angle = targetAngle;
        if (distance < 4) {
            self->drawFlags = ENTITY_SCALEX | ENTITY_SCALEY;
            self->scaleY = 0x100;
            self->scaleX = 0x100;
            self->hitboxState = 0;
            self->step++;
        }
        if (!(g_Timer & 3)) {
            entity = AllocEntity(&g_Entities[208], &g_Entities[256]);
            if (entity != NULL) {
                CreateEntityFromEntity(E_UNK_1A, self, entity);
                entity->params = self->animCurFrame;
                entity->facingLeft = self->facingLeft;
            }
        }
        if (g_BossMgrState & 4) {
            SetStep(5);
        }
        break;
    case 4:
        AnimateEntity(D_us_80180770, self);
        entity = self->ext.deathBossProjectile.target;
        self->posX.i.hi = entity->posX.i.hi;
        self->posY.i.hi = entity->posY.i.hi;
        self->scaleX -= 0x10;
        self->scaleY = self->scaleX;
        if (!self->scaleX) {
            entity->ext.deathBossProjectile.skullReturned = 1;
            DestroyEntity(self);
            return;
        }
        if (g_BossMgrState & 4) {
            DestroyEntity(self);
        }
        break;
    case 5:
        self->flags |= FLAG_DESTROY_IF_OUT_OF_CAMERA;
        MoveEntity();
        break;
    }
}

void func_us_8019D950(Entity* self) {
    if (g_BossMgrState & BOSS_MGR_DEATH_FIRST_FORM_DEFEAT) {
        DestroyEntity(self);
        return;
    }
    if (!self->step) {
        InitializeEntity(D_us_801804C4);
        self->animCurFrame = self->params;
        self->drawFlags = ENTITY_OPACITY;
        self->blendMode = BLEND_TRANSP | BLEND_ADD;
        self->opacity = 0x60;
        if (self->rotate) {
            self->drawFlags |= ENTITY_ROTATE;
        }
    }
    self->opacity -= 8;
    if (!self->opacity) {
        DestroyEntity(self);
    }
}
