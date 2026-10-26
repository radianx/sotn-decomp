// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rbo1.h"

extern BeelzebubFlameInit D_us_8018094C[];
extern EInit g_EInitParticle;

void func_us_801947E4(Entity* self) {
    s32 index;
    BeelzebubFlameInit* init;
    s16 angle;
    s32 speed;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitParticle);
        index = self->params & 15;
        init = &D_us_8018094C[index];
        self->palette = init->palette + 0x2E0;
        self->blendMode = init->blendMode;
        self->animSet = init->animSet;
        self->unk5A = init->unk5A;
        self->ext.beelzebubFlame.anim = init->anim;
        self->step = index + 1;
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
        MoveEntity();
        self->velocityY = FIX(-1);
        if (!AnimateEntity(self->ext.beelzebubFlame.anim, self)) {
            DestroyEntity(self);
        }
        break;
    case 2:
        if (!AnimateEntity(self->ext.beelzebubFlame.anim, self)) {
            DestroyEntity(self);
        }
        break;
    case 3:
        if (!self->step_s) {
            self->drawFlags |= ENTITY_ROTATE;
            switch (self->ext.beelzebubFlame.pattern) {
            case 1:
                if (self->ext.beelzebubFlame.index > 3) {
                    self->ext.beelzebubFlame.index -= 3;
                    self->ext.beelzebubFlame.angle -= ROT(180);
                }
                break;
            case 2:
                self->ext.beelzebubFlame.angle +=
                    self->ext.beelzebubFlame.index * 0xC0;
                break;
            }
            self->ext.beelzebubFlame.angle &= 0xFFF;
            self->rotate = self->ext.beelzebubFlame.angle;
            speed = (self->ext.beelzebubFlame.index * 320) / 28;
            self->velocityX = speed * rsin((s16)self->ext.beelzebubFlame.angle);
            self->velocityY =
                -(speed * rcos((s16)self->ext.beelzebubFlame.angle));
            self->step_s++;
        }
        if (self->pose >= 13) {
            self->velocityX -= self->velocityX / 4;
            self->velocityY -= self->velocityY / 4;
        }
        MoveEntity();
        if (!AnimateEntity(self->ext.beelzebubFlame.anim, self)) {
            DestroyEntity(self);
        }
        break;
    case 4:
        if (!self->step_s) {
            self->drawFlags = ENTITY_ROTATE | ENTITY_OPACITY;
            self->opacity = 0x80;
            self->facingLeft = Random() & 1;
            angle = self->rotate;
            if (self->facingLeft) {
                angle = -angle;
            }
            self->velocityX = rsin(angle) * 40;
            self->velocityY = -(rcos(angle) * 40);
            self->ext.beelzebubFlame.acceleration = Random() * 16 + FIX(0.0625);
            self->step_s++;
        }
        MoveEntity();
        self->opacity -= 1;
        angle = self->rotate;
        if (self->facingLeft) {
            angle = -angle;
        }
        self->velocityX +=
            (rsin(angle) * self->ext.beelzebubFlame.acceleration) >> 12;
        self->velocityY +=
            (-self->ext.beelzebubFlame.acceleration * rcos(angle)) >> 12;
        if (!AnimateEntity(self->ext.beelzebubFlame.anim, self)) {
            DestroyEntity(self);
        }
        break;
    case 5:
        if (!self->step_s) {
            self->drawFlags = ENTITY_OPACITY;
            self->opacity = 0x80;
            self->facingLeft = Random() & 1;
            self->velocityX = (Random() << 9) - FIX(1);
            self->velocityY = FIX(-2.5);
            self->ext.beelzebubFlame.accelerationY =
                -(Random() * 16) - FIX(0.0625);
            self->step_s++;
        }
        MoveEntity();
        self->velocityY += self->ext.beelzebubFlame.accelerationY;
        self->opacity -= 1;
        if (!AnimateEntity(self->ext.beelzebubFlame.anim, self)) {
            DestroyEntity(self);
        }
        break;
    }
}
