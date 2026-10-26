// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rbo1.h"

extern EInit D_us_801804C4;
extern EInit D_us_801804AC;
extern EInit D_us_801804B8;
extern EInit D_us_801804D0;
extern u8 D_us_80180854[];
extern u8 D_us_80180860[];
extern u8 D_us_80180868[];
extern u8 D_us_80180870[];
extern u8 D_us_80180878[];
extern s32 g_BossMgrState;
#ifdef VERSION_PC
#define D_us_801915F0 sprites_rbo1_2
#endif
extern SpriteParts* D_us_801915F0[];
void func_us_8019D260_from_rcen(void);

void func_us_801936FC(Entity* self) {
    Entity* entity;
    s16 angle;
    s32 targetX;
    s32 targetY;
    s32 dx;
    s32 dy;
    s32 distance;

    self->rotate += 16;
    if (g_BossMgrState & BOSS_MGR_DEFEAT) {
        self->flags |= FLAG_DEAD;
    }
    if (self->flags & FLAG_DEAD) {
        PlaySfxPositional(SFX_QUICK_STUTTER_EXPLODE_A);
        entity = AllocEntity(&g_Entities[192], &g_Entities[248]);
        if (entity != NULL) {
            CreateEntityFromEntity(E_EXPLOSION, self, entity);
            entity->params = 3;
            entity->zPriority = self->zPriority;
        }
        DestroyEntity(self);
        return;
    }
    switch (self->step) {
    case 0:
        InitializeEntity(D_us_801804AC);
        self->animCurFrame = 0;
        self->hitboxState = 0;
        self->drawFlags = ENTITY_SCALEX | ENTITY_SCALEY;
        if (self->params) {
            self->step = 3;
            self->zPriority += 6;
        } else {
            self->step = 2;
            self->zPriority -= 6;
        }
        break;
    case 2:
        AnimateEntity(D_us_80180860, self);
        angle = self->rotate;
        entity = self->ext.beelzebub.parent;
        targetX = entity->posX.i.hi;
        targetY = entity->posY.i.hi;
        targetX += (rcos(angle) * 96) >> 12;
        targetY += (rsin(angle) * 96) >> 12;
        dx = targetX - self->posX.i.hi;
        dy = targetY - self->posY.i.hi;
        angle = ratan2(dy, dx);
        distance = SquareRoot0(dx * dx + dy * dy);
        distance -= 3;
        self->posX.i.hi = targetX - ((distance * rcos(angle)) >> 12);
        self->posY.i.hi = targetY - ((distance * rsin(angle)) >> 12);
        self->scaleX = 256 - distance;
        if (self->scaleX < 64) {
            self->scaleX = 64;
        }
        self->scaleY = self->scaleX;
        if (distance < 2) {
            self->drawFlags = ENTITY_DEFAULT;
            self->zPriority += 12;
            SetStep(4);
        }
        break;
    case 3:
        AnimateEntity(D_us_80180868, self);
        angle = self->rotate;
        entity = self->ext.beelzebub.parent;
        targetX = entity->posX.i.hi;
        targetY = entity->posY.i.hi;
        targetX += (rcos(angle) * 96) >> 12;
        targetY += (rsin(angle) * 96) >> 12;
        dx = targetX - self->posX.i.hi;
        dy = targetY - self->posY.i.hi;
        angle = ratan2(dy, dx);
        distance = SquareRoot0(dx * dx + dy * dy);
        distance -= 3;
        self->posX.i.hi = targetX - ((distance * rcos(angle)) >> 12);
        self->posY.i.hi = targetY - ((distance * rsin(angle)) >> 12);
        self->scaleX = 256 + distance;
        if (self->scaleX > 448) {
            self->scaleX = 448;
        }
        self->scaleY = self->scaleX;
        if (distance < 2) {
            self->drawFlags = ENTITY_DEFAULT;
            SetStep(4);
        }
        break;
    case 4:
        if (!self->step_s) {
            self->ext.beelzebub.timer = 128;
            self->hitboxState = 3;
            self->step_s++;
        }
        if (!AnimateEntity(D_us_80180854, self)) {
            self->facingLeft = GetSideToPlayer() & 1;
        }
        angle = self->rotate;
        entity = self->ext.beelzebub.parent;
        dx = entity->posX.i.hi;
        dy = entity->posY.i.hi;
        dx += (rcos(angle) * 96) >> 12;
        dy += (rsin(angle) * 96) >> 12;
        self->posX.i.hi = dx;
        self->posY.i.hi = dy;
        if (!--self->ext.beelzebub.timer) {
            SetStep(5);
        }
        break;
    case 5:
        angle = GetAngleBetweenEntities(self, &PLAYER);
        self->velocityX = (rcos(angle) * FIX(2.5)) >> 12;
        self->velocityY = (rsin(angle) * FIX(2.5)) >> 12;
        if (self->velocityX > 0) {
            self->facingLeft = 0;
        } else {
            self->facingLeft = 1;
        }
        self->flags |= FLAG_DESTROY_IF_OUT_OF_CAMERA;
        self->step++;
        // fallthrough
    case 6:
        MoveEntity();
        AnimateEntity(D_us_80180854, self);
        break;
    }
}

void func_us_80193C2C(Entity* self) {
    Entity* parent;
    s32 targetX;
    s16 targetY;

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_801804C4);
        self->ext.beelzebub.angle = Random() * 16;
        self->pose = Random() & 1;
        self->poseTimer = Random() & 1;
        Random();
        self->zPriority = 0x92;
        // fallthrough
    case 1:
        parent = self->ext.beelzebub.parent;
        if (parent->flags & FLAG_DEAD) {
            self->ext.beelzebub.parent = parent->ext.beelzebub.parent;
            parent = self->ext.beelzebub.parent;
        }
        targetX = parent->posX.i.hi;
        targetY = parent->posY.i.hi;
        self->rotate =
            ratan2(targetY - self->posY.i.hi, targetX - self->posX.i.hi);
        self->ext.beelzebub.timer = (Random() & 0x1F) + 16;
        self->step++;
        // fallthrough
    case 2:
        AnimateEntity(D_us_80180870, self);
        MoveEntity();
        targetY =
            LimitAngleChange(0x18, self->ext.beelzebub.angle, self->rotate);
        self->velocityX = rcos((s16)targetY) * 24;
        self->velocityY = rsin((s16)targetY) * 24;
        self->ext.beelzebub.angle = targetY;
        if (!--self->ext.beelzebub.timer) {
            self->step--;
        }
        if (g_BossMgrState & BOSS_MGR_DEFEAT) {
            self->step = 3;
        }
        break;
    case 3:
        MoveEntity();
        self->velocityY = FIX(-1.5);
        if (self->posY.i.hi < 0) {
            DestroyEntity(self);
        }
        break;
    }
}

void func_us_80193E24(Entity* self) {
    Collider unused; // !FAKE: Preserves the original stack frame.
    Entity* parent;
    s32 targetX;
    s16 targetY;
    s32 posX;

    if (g_BossMgrState & BOSS_MGR_DEFEAT) {
        self->flags |= FLAG_DEAD;
    }
    if (self->flags & FLAG_DEAD) {
        self->step = 0;
        self->drawFlags = ENTITY_DEFAULT;
        self->pfnUpdate = EntityExplosion;
        self->params = 0;
        return;
    }
    switch (self->step) {
    case 0:
        InitializeEntity(D_us_801804B8);
        self->animCurFrame = 10;
        self->drawFlags = ENTITY_ROTATE;
        self->zPriority = 0x90;
        // fallthrough
    case 1:
        parent = self->ext.beelzebub.parent;
        if (parent->flags & FLAG_DEAD) {
            self->step = 2;
        }
        if (!self->step_s) {
            targetX = parent->posX.i.hi;
            targetY = parent->posY.i.hi;
            self->ext.beelzebub.angle =
                ratan2(targetY - self->posY.i.hi, targetX - self->posX.i.hi);
            self->ext.beelzebub.timer = (Random() & 15) + 4;
            self->step_s++;
        }
        AnimateEntity(D_us_80180878, self);
        MoveEntity();
        targetY =
            LimitAngleChange(0x20, self->rotate, self->ext.beelzebub.angle);
        self->velocityX = rcos((s16)targetY) * 4;
        self->velocityY = rsin((s16)targetY) * 4;
        self->rotate = targetY;
        if (!--self->ext.beelzebub.timer) {
            self->step_s = 0;
            if (!(Random() & 0x7F)) {
                self->step = 2;
            }
        }
        break;
    case 2:
        self->flags |= FLAG_DESTROY_IF_BARELY_OUT_OF_CAMERA;
        MoveEntity();
        self->velocityY += FIX(0.03125);
        if (self->posY.i.hi + g_Tilemap.scrollY.i.hi + 1 > 0x1C0) {
            self->drawFlags = ENTITY_DEFAULT;
            self->velocityX = 0;
            self->velocityY = 0;
            self->posY.i.hi = 0x1BF - g_Tilemap.scrollY.i.hi;
            self->facingLeft = GetSideToPlayer() & 1;
            self->step++;
        }
        break;
    case 3:
        AnimateEntity(D_us_80180878, self);
        MoveEntity();
        if (self->facingLeft) {
            self->velocityX = FIX(-0.25);
        } else {
            self->velocityX = FIX(0.25);
        }
        posX = self->posX.i.hi + g_Tilemap.scrollX.i.hi;
        if (self->velocityX > 0) {
            if (posX > 0x3D0) {
                posX = 0;
            }
        } else if (posX < 0xC0) {
            posX = 0;
        }
        if (!posX) {
            DestroyEntity(self);
        }
        break;
    }
}

void func_us_80194108(Entity* self) {
    Entity* entity;
    SpriteParts* parts;
    s32 posY;
    s32 centerY;
    s16 offsetY;

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_801804D0);
        self->drawFlags = ENTITY_ROTATE;
        self->animCurFrame = self->params;
        self->ext.beelzebub.rotVel = (Random() & 3) + 2;
        PlaySfxPositional(SFX_BO1_UNK_7C7);
        // fallthrough
    case 1:
        MoveEntity();
        self->velocityY += FIX(0.0625);
        self->rotate += self->ext.beelzebub.rotVel;
        parts = D_us_801915F0[self->animCurFrame];
#ifdef VERSION_PC
        // Invisible joints use frame zero, whose sprite pointer is NULL.
        if (!self->animCurFrame) {
            DestroyEntity(self);
            return;
        }
#endif
        posY = parts->parts[0].offsety;
        posY += parts->parts[0].height;
        if (!(g_Timer & 7)) {
            entity = AllocEntity(&g_Entities[192], &g_Entities[248]);
            if (entity != NULL) {
                CreateEntityFromEntity(E_UNK_1D, self, entity);
                entity->posY.i.hi +=
                    parts->parts[0].offsety + parts->parts[0].height / 2;
                entity->posX.i.hi += (Random() & 15) - 8;
                entity->params = 1;
                entity->zPriority = self->zPriority + 1;
            }
        }
        posY += self->posY.i.hi + g_Tilemap.scrollY.i.hi;
        if (posY > 0x1C0) {
            entity = AllocEntity(&g_Entities[192], &g_Entities[248]);
            if (entity != NULL) {
                CreateEntityFromEntity(E_EXPLOSION, self, entity);
                centerY = parts->parts[0].height / 2;
                offsetY = parts->parts[0].offsety;
                entity->params = 3;
                entity->posY.i.hi += offsetY + centerY;
            }
            func_us_8019D260_from_rcen();
            DestroyEntity(self);
        }
        break;
    }
}

void func_us_8019ED80_from_rbo2(Entity* self) {
    s16 angle = self->ext.beelzebub.rotate;
    Entity* src;

    angle += self->ext.beelzebub.angleOffset;
    if (g_CurrentEntity->facingLeft) {
        angle = -angle;
    }

    src = self->ext.beelzebub.parent;
    self->posX.val = src->posX.val;
    self->posY.val = src->posY.val;
    self->posX.val -= self->ext.beelzebub.length * rsin(angle) * 16;
    self->posY.val += self->ext.beelzebub.length * rcos(angle) * 16;
    self->ext.beelzebub.unkA8 |= 1;
}

void polarPlacePartsWithAngvel(s16* entOffsets) {
    Entity* ent;

    while (*entOffsets) {
        if (*entOffsets != 0xFF) {
            ent = g_CurrentEntity + *entOffsets;
            ent->ext.beelzebub.rotate += ent->ext.beelzebub.rotVel;
            func_us_8019ED80_from_rbo2(ent);
        }
        entOffsets++;
    }
}

void func_801CDD00(Entity* entity, s16 arg1, s16 arg2) {
    s16 temp_t0 = arg1 - entity->ext.beelzebub.rotate;

    if (temp_t0 > 0x800) {
        temp_t0 = temp_t0 - 0x1000;
    }

    if (temp_t0 < -0x800) {
        temp_t0 = temp_t0 + 0x1000;
    }

    temp_t0 = temp_t0 / arg2;
    entity->ext.beelzebub.rotVel = temp_t0;
    entity->ext.beelzebub.unkA4 = arg1;
}

void func_801CDD80(s16* entOffsets, unkStr_801CDD80* arg1) {
    Entity* var_s1;
    s16* ptr = arg1->unk4;

    while (*entOffsets) {
        if (*entOffsets != 0xFF) {
            var_s1 = g_CurrentEntity + *entOffsets;
            func_801CDD00(var_s1, *ptr, arg1->unk0);
        }
        ptr++;
        entOffsets++;
    }
}

void func_801CDF1C(s16 entIndices[], unkStr_801CDD80* arg1, s32 arg2) {

    arg1 += (u16)g_CurrentEntity->ext.beelzebub.unkB0[arg2];

    if (!g_CurrentEntity->ext.beelzebub.unkB4[arg2]) {
        func_801CDD80(entIndices, arg1);
        g_CurrentEntity->ext.beelzebub.unkB4[arg2] = arg1->unk0;
    }
    if (!--g_CurrentEntity->ext.beelzebub.unkB4[arg2]) {
        arg1++;
        if (!arg1->unk0) {
            g_CurrentEntity->ext.beelzebub.unkB0[arg2] = 0;
        } else {
            ++g_CurrentEntity->ext.beelzebub.unkB0[arg2];
        }
    }
}

void func_801CE1E8(s32 step) {
    s32 i;

    g_CurrentEntity->step = (u16)step;
    g_CurrentEntity->step_s = 0;
    g_CurrentEntity->pose = 0;
    g_CurrentEntity->poseTimer = 0;
    //! @bug The original loop writes four entries into two-element arrays.
    for (i = 0; i < 4; i++) {
        g_CurrentEntity->ext.beelzebub.unkB0[i] = 0;
        g_CurrentEntity->ext.beelzebub.unkB4[i] = 0;
    }
}

void func_801CE228(void) {
    s32 i;

    //! @bug The original loop writes four entries into two-element arrays.
    for (i = 0; i < 4; i++) {
        g_CurrentEntity->ext.beelzebub.unkB0[i] = 0;
        g_CurrentEntity->ext.beelzebub.unkB4[i] = 0;
    }
}

void polarPlacePartsList(s16* offsets) {
    Entity* entity;

    while (*offsets) {
        entity = g_CurrentEntity + *offsets;
        if (!entity->ext.beelzebub.unkA8) {
            func_us_8019ED80_from_rbo2(entity);
        }
        offsets++;
    }
}

void func_us_8019D260_from_rcen(void) {
    s16 angle;
    s32 i;
    s8 pattern;
    Entity* entity;

    pattern = Random() & 3;
    angle = ((Random() & 0xF) << 8) - 0x800;
    for (i = 0; i < 6; i++) {
        entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (entity != NULL) {
            CreateEntityFromEntity(E_UNK_1D, g_CurrentEntity, entity);
            entity->ext.beelzebubFlame.index = 6 - i;
            entity->ext.beelzebubFlame.pattern = pattern;
            entity->params = 2;
            entity->ext.beelzebubFlame.angle = angle;
            entity->zPriority = g_CurrentEntity->zPriority + 1;
        }
    }
}
