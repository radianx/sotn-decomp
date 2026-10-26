// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rdai.h"

s32 SpearGuardCheckCollision(void) {
    Collider collider;
    s32 x;
    s32 y;

    g_CurrentEntity->posX.val += g_CurrentEntity->velocityX;
    g_CurrentEntity->posY.i.hi -= 3;
    x = g_CurrentEntity->posX.i.hi;
    y = g_CurrentEntity->posY.i.hi - 0x1E;
    g_api.CheckCollision(x, y, &collider, 0);

    if (collider.effects & EFFECT_SOLID) {
        y = (g_CurrentEntity->posY.i.hi += collider.unk20);
    } else {
        return false;
    }

    if (g_CurrentEntity->velocityX == 0) {
        return true;
    }

    if (g_CurrentEntity->velocityX > 0) {
        x += 0x20;
        y -= 0x24;
    } else {
        x -= 0x20;
        y += 0x1C;
    }
    g_api.CheckCollision(x, y, &collider, 0);
    if (!(collider.effects & EFFECT_UNK_8000)) {
        return false;
    }
    return true;
}

#include "../approach_s16.h"

extern EInit g_EInitRdaiUnk1F;

extern u8 D_us_801818B4[];
extern u8 D_us_801818BC[];
extern u8 D_us_801818C8[];

void func_us_801BF830(Entity* self) {
    Entity* entity;
    s32 i;
    s32 animStatus;

    if (self->step && (self + 4)->entityId != E_UNK_1C && self->step != 3) {
        SetStep(3);
    }
    switch (self->step) {
    case 0:
        entity = self + 1;
        InitializeEntity(g_EInitRdaiUnk1F);
        for (i = 0; i < 3; i++, entity++) {
            CreateEntityFromEntity(E_UNK_1F, self, entity);
            entity->params = i;
        }
        CreateEntityFromEntity(E_UNK_1C, self, self + 4);
        SetStep(1);
        break;
    case 1:
        if (!self->step_s) {
            self->ext.rdaiArcher.timer = 0x80;
            self->step_s++;
        }
        if (!self->ext.rdaiArcher.direction) {
            self->velocityX += FIX(0.015625);
            if (self->velocityX > FIX(0.75)) {
                self->velocityX = FIX(0.75);
            }
        } else {
            self->velocityX -= FIX(0.015625);
            if (self->velocityX < FIX(-0.75)) {
                self->velocityX = FIX(-0.75);
            }
        }
        AnimateEntity(D_us_801818B4, self);
        SpearGuardCheckCollision();
        if (!(g_Timer & 7)) {
            PlaySfxPositional(SFX_UNK_RDAI_76A);
        }
        if (!--self->ext.rdaiArcher.timer) {
            SetStep(2);
        }
        break;
    case 2:
        switch (self->step_s) {
        case 0:
            SpearGuardCheckCollision();
            self->velocityX -= self->velocityX >> 8;
            if (abs(self->velocityX) < FIX(0.5)) {
                self->velocityX = 0;
                self->ext.rdaiArcher.direction ^= 1;
                self->step_s++;
            }
            break;
        case 2:
            if (!self->ext.rdaiArcher.direction) {
                self->velocityX += FIX(0.015625);
                if (self->velocityX > FIX(0.75)) {
                    self->velocityX = FIX(0.75);
                }
            } else {
                self->velocityX -= FIX(0.015625);
                if (self->velocityX < FIX(-0.75)) {
                    self->velocityX = FIX(-0.75);
                }
            }
            // fallthrough
        case 1:
            SpearGuardCheckCollision();
            if (!self->ext.rdaiArcher.direction) {
                animStatus = AnimateEntity(D_us_801818C8, self);
            } else {
                animStatus = AnimateEntity(D_us_801818BC, self);
            }
            if (self->pose >= 3) {
                self->step_s = 2;
            }
            if (!animStatus) {
                SetStep(1);
            }
            break;
        }
        break;
    case 3:
        PlaySfxPositional(SFX_FLEA_ARMOR_EXPLODE);
        for (i = 0; i < 9; i++) {
            if (i == 7) {
                continue;
            }
            entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (entity != NULL) {
                CreateEntityFromEntity(E_UNK_21, self, entity);
                entity->params = i + 1;
            }
        }
        PreventEntityFromRespawning(self);
        DestroyEntity(self);
        break;
    case 255:
#include "../pad2_anim_debug.h"
    }
}

// Child parts share one implementation; only the fixed EInit address is local.
#include "../e_rdai_unk1f.h"

#include "../e_rdai_archer.h"

extern u8 D_us_801818D4[];
extern u8 D_us_801818DC[];
extern u8 D_us_801818E4[];
extern u8 D_us_801818F4[];

void func_us_801C0240(Entity* self) {
    Entity* entity;
    s32 step = self->step;

    switch (step) {
    case 0:
        InitializeEntity(g_EInitRdaiUnk1F);
        self->drawFlags = ENTITY_ROTATE;
        self->hitboxState = 0;
        self->step = self->params;
        if (self->params == 1) {
            entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
            if (entity != NULL) {
                CreateEntityFromEntity(E_UNK_20, self, entity);
                entity->ext.rdaiArcher.parent = self;
                entity->zPriority = self->zPriority - 1;
            }
        }
        break;
    case 1:
        self->posX.i.hi = (self - 1)->posX.i.hi;
        self->posY.i.hi = (self - 1)->posY.i.hi;
        self->zPriority = (self - 1)->zPriority + 3;
        self->rotate = (self - 1)->rotate;
        entity = self - 1;
        switch (self->ext.rdaiArcher.mode) {
        case 1:
            AnimateEntity(D_us_801818DC, self);
            // The original compares pose and poseTimer as one word.
#ifdef FIX_UB
            if (self->pose == step && self->poseTimer == 0) {
#else
            if (LOW(self->pose) == step) {
#endif
                PlaySfxPositional(SFX_BONE_CREAK);
            }
            break;
        case 2:
            self->animCurFrame = 0x1B;
            goto reset_pose;
        case 3:
            AnimateEntity(D_us_801818F4, self);
#ifdef FIX_UB
            if (self->pose == 6 && self->poseTimer == 0) {
#else
            if (LOW(self->pose) == 6) {
#endif
                // !FAKE: The one-shot loop preserves register allocation.
                do {
                    entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
                    if (entity == NULL) {
                        break;
                    }
                    CreateEntityFromEntity(E_UNK_20, self, entity);
                    entity->ext.rdaiArcher.parent = self;
                    entity->zPriority = self->zPriority - 1;
                } while (0);
                entity = self - 1;
            }
            break;
        default:
            self->animCurFrame = 0x19;
            goto reset_pose;
        }
        goto update_parent;
    case 2:
        entity = self - 2;
        self->animCurFrame = 0x1C;
        self->posX.i.hi = entity->posX.i.hi;
        self->posY.i.hi = entity->posY.i.hi;
        self->zPriority = entity->zPriority - 1;
        self->rotate = entity->rotate;
        if (entity->entityId != E_UNK_1C) {
            DestroyEntity(self);
        }
        break;
    case 3:
        entity = self - 3;
        self->posX.i.hi = entity->posX.i.hi;
        self->posY.i.hi = entity->posY.i.hi;
        self->zPriority = entity->zPriority + 1;
        self->rotate = entity->rotate;
        switch (self->ext.rdaiArcher.mode) {
        case 1:
            AnimateEntity(D_us_801818D4, self);
            if (entity->ext.rdaiArcher.mode == 2) {
                self->pose = 0;
                self->poseTimer = 0;
                self->ext.rdaiArcher.mode = 2;
            }
            break;
        case 2:
            AnimateEntity(D_us_801818E4, self);
            break;
        case 3:
        default:
            self->animCurFrame = 0xB;
        reset_pose:
            self->pose = 0;
            self->poseTimer = 0;
            break;
        }
    update_parent:
        // !FAKE: Retain the initial state in a saved register.
        step = self->ext.rdaiArcher.mode = entity->ext.rdaiArcher.mode;
        if (entity->entityId != E_UNK_1C) {
            DestroyEntity(self);
        }
        break;
    }
}

extern EInit D_us_80180884;

void func_us_801C0528(Entity* self) {
    s32 distance;
    s32 i;
    Entity* entity;
    s16 angle;

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_80180884);
        self->animCurFrame = 0x16;
        self->hitboxState = 0;
        self->drawFlags |= ENTITY_ROTATE;
        if (self->params) {
            self->flags |= FLAG_UNK_2000 | FLAG_UNK_00200000 |
                           FLAG_DESTROY_IF_BARELY_OUT_OF_CAMERA |
                           FLAG_DESTROY_IF_OUT_OF_CAMERA;
            self->animCurFrame += self->params;
            if (self->params == 1) {
                self->velocityX = FIX(0.5);
            } else {
                self->velocityX = FIX(-0.5);
            }
            self->step = 4;
            break;
        }
        // fallthrough
    case 1:
        entity = self->ext.rdaiArcher.parent;
        self->posX.i.hi = entity->posX.i.hi;
        self->posY.i.hi = entity->posY.i.hi;
        angle = entity->rotate;
        self->rotate = angle;
        distance = 0x18;
        if (entity->animCurFrame == 0x1A) {
            distance = 0xE;
        }
        if (entity->animCurFrame == 0x1B) {
            distance = 8;
        }
        self->posX.i.hi += (distance * rcos(angle)) >> 12;
        self->posY.i.hi += (distance * rsin(angle)) >> 12;
        if (entity->entityId != E_UNK_1D) {
            DestroyEntity(self);
            break;
        }
        if (entity->ext.rdaiArcher.mode == 2) {
            self->flags |= FLAG_DESTROY_IF_OUT_OF_CAMERA;
            self->velocityX = (rcos(angle) * FIX(5)) >> 12;
            self->velocityY = (rsin(angle) * FIX(5)) >> 12;
            self->hitboxState = 3;
            self->hitboxOffX = (u32)rcos(angle) >> 9;
            self->hitboxOffY = (u32)rsin(angle) >> 9;
            self->hitboxWidth = self->hitboxHeight = 4;
            self->step = 2;
        }
        break;
    case 2:
        MoveEntity();
        if (self->flags & FLAG_DEAD) {
            for (i = 0; i < 2; i++) {
                entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (entity != NULL) {
                    CreateEntityFromEntity(E_UNK_20, self, entity);
                    entity->params = i + 1;
                    entity->rotate = self->rotate;
                }
            }
            DestroyEntity(self);
            break;
        }
        if (self->hitFlags & 0x80) {
            self->ext.rdaiArcher.offsetX = PLAYER.posX.i.hi - self->posX.i.hi;
            self->ext.rdaiArcher.offsetY = PLAYER.posY.i.hi - self->posY.i.hi;
            self->ext.rdaiArcher.timer = 0x20;
            self->hitboxState = 0;
            self->step++;
        }
        break;
    case 3:
        self->posX.i.hi = PLAYER.posX.i.hi - self->ext.rdaiArcher.offsetX;
        self->posY.i.hi = PLAYER.posY.i.hi - self->ext.rdaiArcher.offsetY;
        if (!--self->ext.rdaiArcher.timer) {
            DestroyEntity(self);
        }
        break;
    case 4:
        MoveEntity();
        self->velocityY += FIX(0.125);
        if (self->params == 1) {
            self->rotate += ROT(2.8125);
        } else {
            self->rotate -= ROT(2.8125);
        }
        break;
    }
}

extern EInit D_us_80180890;
extern SpriteParts* sprites_rdai_2[];

void func_us_801C0898(Entity* self) {
    Entity* entity;
    SpriteParts* sprite;
    s32 offsetX;
    s32 offsetY;
    s16 angle;

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_80180890);
        self->animCurFrame = self->params;
        sprite = sprites_rdai_2[self->animCurFrame];
        offsetX = sprite->parts[0].offsetx;
        offsetY = sprite->parts[0].offsety;
        offsetX += sprite->parts[0].width / 2;
        offsetY += sprite->parts[0].height / 2;
        self->ext.rdaiArcher.offsetX = offsetX;
        self->ext.rdaiArcher.offsetY = offsetY;
        self->ext.rdaiArcher.timer = (Random() & 0xF) + 8;
        angle = ratan2(offsetY, offsetX);
        self->velocityX = (rcos(angle) * FIX(2)) >> 12;
        self->velocityY = (rsin(angle) * FIX(2)) >> 12;
        entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (entity != NULL) {
            CreateEntityFromEntity(E_EXPLOSION, self, entity);
            entity->params = 1;
            entity->posX.i.hi += offsetX;
            entity->posY.i.hi += offsetY;
        }
        if (self->params >= 0x13) {
            self->step = 2;
        }
        break;
    case 1:
        MoveEntity();
        self->velocityY += FIX(0.125);
        if (!--self->ext.rdaiArcher.timer) {
            PlaySfxPositional(SFX_EXPLODE_D);
            entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (entity != NULL) {
                CreateEntityFromEntity(E_EXPLOSION, self, entity);
                entity->posX.i.hi += self->ext.rdaiArcher.offsetX;
                entity->posY.i.hi += self->ext.rdaiArcher.offsetY;
                entity->params = 1;
            }
            DestroyEntity(self);
        }
        break;
    case 2:
        switch (self->params) {
        case 0x13:
            if (!self->step_s) {
                self->velocityY = FIX(-2.5);
                self->ext.rdaiArcher.timer = 0x10;
                self->step_s++;
            }
            MoveEntity();
            self->velocityY += FIX(0.125);
            if (!--self->ext.rdaiArcher.timer) {
                entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (entity != NULL) {
                    CreateEntityFromEntity(E_EXPLOSION, self, entity);
                    entity->posX.i.hi += self->ext.rdaiArcher.offsetX;
                    entity->posY.i.hi += self->ext.rdaiArcher.offsetY;
                    entity->params = 1;
                }
                DestroyEntity(self);
            }
            break;
        case 0x14:
            if (!self->step_s) {
                self->ext.rdaiArcher.timer = 0x18;
                self->velocityX = 0;
                self->velocityY = 0;
                self->step_s++;
            }
            MoveEntity();
            self->velocityY += FIX(0.03125);
            if (!--self->ext.rdaiArcher.timer) {
                entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (entity != NULL) {
                    CreateEntityFromEntity(E_EXPLOSION, self, entity);
                    entity->posX.i.hi += self->ext.rdaiArcher.offsetX;
                    entity->posY.i.hi += self->ext.rdaiArcher.offsetY;
                    entity->params = 1;
                }
                DestroyEntity(self);
            }
            break;
        case 0x15:
            if (!self->step_s) {
                self->ext.rdaiArcher.timer = 0x40;
                self->velocityY = 0;
            }
            MoveEntity();
            self->velocityY += FIX(0.1875);
            break;
        }
        break;
    }
}
