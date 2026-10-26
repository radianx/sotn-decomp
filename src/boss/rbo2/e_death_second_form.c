// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rbo2.h"
#include "sfx.h"

extern s32 g_BossMgrState;
extern EInit D_us_801804DC;
extern EInit D_us_801804E8;
extern EInit g_EInitDeath2;
extern EInit g_EInitParticle;
extern s32 D_us_80180784;
extern s32 D_us_80180788;
extern s16 D_us_8018078C[][6];
extern s16 D_us_8018081C[];
extern s16 D_us_80180834[];
extern s16 D_us_80180844[];
extern s16 D_us_80180A9C[];
extern unkStr_801CDD80 D_us_801808A4[];
extern unkStr_801CDD80 D_us_801808E4[];
extern unkStr_801CDD80 D_us_8018095C[];
extern unkStr_801CDD80 D_us_801809E4[];
extern unkStr_801CDD80 D_us_80180A34[];
extern unkStr_801CDD80 D_us_80180A84[];
extern unkStr_801CDD80 D_us_80180AB8[];
s16 func_us_8019A98C_from_rcen(s16, s16, s16);
void func_801CDF1C(s16*, unkStr_801CDD80*, s32);
void func_801CE1E8(s32);
void polarPlacePartsWithAngvel(s16*);
void polarPlacePartsList(s16*);

void func_us_8019DA04(Entity* self) {
    Collider unused; // !FAKE: Preserves the original stack frame.
    Entity* entity;
    Entity* previous;
    s16* init;
    s16* offsets;
    s32 posX;
    s32 posY;
    s16 angle;
    s32 facing;
    u16 i;
    s32 zPriority;
    s32 priorityOffset;

    if ((self->flags & FLAG_DEAD) && (self->step != 6)) {
        func_801CE1E8(6);
    }
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitDeath2);
        self->animCurFrame = 2;
        self->hitboxHeight = 12;
        self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        previous = self;
        init = D_us_8018078C[0];
        i = 0;
        while (*init) {
            entity = self + init[0];
            CreateEntityFromCurrentEntity(E_UNK_1C, entity);
            entity->ext.deathSecondForm.length = init[2];
            entity->ext.deathSecondForm.parent = self + init[1];
            entity->ext.deathSecondForm.angleOffset = init[5];
            entity->params = i;
            i++;
            entity->zPriority = self->zPriority + init[4];
            entity->nextPart = previous;
            previous = entity;
            previous->parent = self;
            init += 6;
        }
        self->parent = NULL;
        self->nextPart = previous;
        polarPlacePartsList(D_us_8018081C);
        self->ext.deathSecondForm.targetAngle = 0x200;
        func_801CE1E8(1);
        // fallthrough
    case 1:
        offsets = D_us_80180844;
        func_801CDF1C(offsets, D_us_801808A4, 0);
        polarPlacePartsWithAngvel(offsets);
        if (!self->ext.deathSecondForm.unkB4[0] &&
            !self->ext.deathSecondForm.unkB0[0]) {
            func_801CE1E8(2);
        }
        break;
    case 2:
        if (!self->step_s) {
            self->ext.deathSecondForm.timer = ((Random() & 3) << 5) + 0x40;
            self->step_s++;
        }
        MoveEntity();
        facing = (GetSideToPlayer() & 1) ^ 1;
        if (self->facingLeft != facing) {
            if (self->facingLeft) {
                self->posX.i.hi += 12;
            } else {
                self->posX.i.hi -= 12;
            }
            self->facingLeft = facing;
        }
        angle = self->ext.deathSecondForm.targetAngle;
        posX = PLAYER.posX.i.hi + ((rcos(angle) * 96) >> 12);
        posY = PLAYER.posY.i.hi - ((rsin(angle) * 96) >> 12);
        angle = ratan2(posY - self->posY.i.hi, posX - self->posX.i.hi);
        angle = func_us_8019A98C_from_rcen(
            0x30, self->ext.deathSecondForm.angle, angle);
        self->velocityX = (rcos(angle) * FIX(1)) >> 12;
        self->velocityY = (rsin(angle) * FIX(1)) >> 12;
        self->ext.deathSecondForm.angle = angle;
        posX = self->posX.i.hi + g_Tilemap.scrollX.i.hi;
        if (posX > 0x180) {
            self->ext.deathSecondForm.targetAngle = 0x600;
        }
        if (posX < 0x80) {
            self->ext.deathSecondForm.targetAngle = 0x200;
        }
        offsets = D_us_80180834;
        func_801CDF1C(offsets, D_us_801808E4, 0);
        polarPlacePartsWithAngvel(offsets);
        offsets = D_us_80180A9C;
        func_801CDF1C(offsets, D_us_80180AB8, 1);
        polarPlacePartsWithAngvel(offsets);
        polarPlacePartsList(D_us_8018081C);
        if (!self->ext.deathSecondForm.timer) {
            facing = (GetSideToPlayer() & 1) ^ 1;
            if ((facing == self->facingLeft) &&
                (GetDistanceToPlayerX() > 0x50)) {
                func_801CE1E8(4);
            } else {
                func_801CE1E8(3);
            }
        } else {
            self->ext.deathSecondForm.timer--;
            if (self->hitFlags & 3) {
                func_801CE1E8(5);
            }
        }
        break;
    case 3:
        if (!self->step_s) {
            self->velocityX = 0;
            self->velocityY = 0;
            self->step_s++;
        }
        MoveEntity();
        self->velocityY -= self->velocityY / 16;
        offsets = D_us_80180834;
        func_801CDF1C(offsets, D_us_8018095C, 0);
        polarPlacePartsWithAngvel(offsets);
        offsets = D_us_80180A9C;
        func_801CDF1C(offsets, D_us_80180AB8, 1);
        polarPlacePartsWithAngvel(offsets);
        polarPlacePartsList(D_us_8018081C);
        if ((u32)(self->ext.deathSecondForm.unkB0[0] - 2) < 3) {
            D_us_80180788 = 1;
        } else {
            D_us_80180788 = 0;
        }
        if (!self->ext.deathSecondForm.unkB4[0]) {
            if (self->ext.deathSecondForm.unkB0[0] == 2) {
                self->velocityY = FIX(4);
                PlaySfxPositional(SFX_BONE_SWORD_SWISH_A);
            }
            if (!self->ext.deathSecondForm.unkB4[0] &&
                !self->ext.deathSecondForm.unkB0[0]) {
                func_801CE1E8(2);
            }
        }
        break;
    case 4:
        switch (self->step_s) {
        case 0:
            offsets = D_us_80180834;
            func_801CDF1C(offsets, D_us_801809E4, 0);
            polarPlacePartsWithAngvel(offsets);
            if (!self->ext.deathSecondForm.unkB4[0]) {
                if (!self->ext.deathSecondForm.unkB0[0]) {
                    self->step_s++;
                }
                if (!self->ext.deathSecondForm.unkB4[0] &&
                    self->ext.deathSecondForm.unkB0[0] == 3) {
                    D_us_80180784 = 1;
                }
            }
            break;
        case 1:
            if (!D_us_80180784) {
                func_801CE1E8(2);
            }
            break;
        }
        offsets = D_us_80180A9C;
        func_801CDF1C(offsets, D_us_80180AB8, 1);
        polarPlacePartsWithAngvel(offsets);
        polarPlacePartsList(D_us_8018081C);
        break;
    case 5:
        if (!self->step_s) {
            if (GetSideToPlayer() & 1) {
                self->velocityX = FIX(2);
            } else {
                self->velocityX = FIX(-2);
            }
            self->velocityY = 0;
            self->step_s++;
        }
        MoveEntity();
        self->velocityX -= self->velocityX >> 4;
        offsets = D_us_80180834;
        func_801CDF1C(offsets, D_us_80180A34, 0);
        polarPlacePartsWithAngvel(offsets);
        polarPlacePartsList(D_us_8018081C);
        if (!self->ext.deathSecondForm.unkB4[0] &&
            !self->ext.deathSecondForm.unkB0[0]) {
            func_801CE1E8(2);
            facing = (GetSideToPlayer() & 1) ^ 1;
            if ((facing == self->facingLeft) &&
                (GetDistanceToPlayerX() > 0x50)) {
                func_801CE1E8(4);
            } else {
                func_801CE1E8(3);
            }
        }
        break;
    case 6:
        switch (self->step_s) {
        case 0:
            self->hitboxState = 0;
            g_BossMgrState |= BOSS_MGR_DEATH_DEFEAT;
            if (GetSideToPlayer() & 1) {
                self->velocityX = FIX(2);
            } else {
                self->velocityX = FIX(-2);
            }
            self->velocityY = 0;
            self->step_s++;
            // fallthrough
        case 1:
            MoveEntity();
            self->velocityX -= self->velocityX >> 4;
            offsets = D_us_80180834;
            func_801CDF1C(offsets, D_us_80180A34, 0);
            polarPlacePartsWithAngvel(offsets);
            polarPlacePartsList(D_us_8018081C);
            if (!self->ext.deathSecondForm.unkB4[0] &&
                !self->ext.deathSecondForm.unkB0[0]) {
                self->step_s++;
            }
            break;
        case 2:
            offsets = D_us_80180844;
            func_801CDF1C(offsets, D_us_80180A84, 0);
            polarPlacePartsWithAngvel(offsets);
            if (!self->ext.deathSecondForm.unkB4[0] &&
                !self->ext.deathSecondForm.unkB0[0]) {
                self->ext.deathSecondForm.timer = 0x40;
                self->velocityX = 0;
                g_BossMgrState |= 0x20;
                self->step_s++;
            }
            break;
        case 3:
            if (!--self->ext.deathSecondForm.timer) {
                self->ext.deathSecondForm.timer = 0x80;
                self->step_s++;
                g_api.PlaySfx(SFX_BOSS_LARGE_FLAMES);
            }
            break;
        case 4:
            entity = AllocEntity(&g_Entities[64], &g_Entities[256]);
            if (entity != NULL) {
                CreateEntityFromEntity(E_UNK_1F, self, entity);
                entity->params = 1;
                entity->posY.i.hi = 0xF0;
                entity->posX.i.hi -= 0x10 - (rand() & 0x1F);
                priorityOffset =
                    (self->ext.deathSecondForm.timer >> 4) + 0xFFF8;
                zPriority = self->zPriority;
                entity->zPriority = zPriority - priorityOffset;
            }
            if (!--self->ext.deathSecondForm.timer) {
                self->animCurFrame = 0;
                self->hitboxState = 0;
                g_BossMgrState |= BOSS_MGR_DEATH_REWARD_READY;
                self->step_s++;
            }
            break;
        case 5:
            break;
        }
        break;
    case 0xFF:
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

    for (offsets = D_us_8018081C; *offsets; offsets++) {
        entity = self + *offsets;
        entity->facingLeft = self->facingLeft;
        entity->ext.deathSecondForm.unkA8 = 0;
    }
    posX = self->posX.i.hi + g_Tilemap.scrollX.i.hi;
    posY = self->posY.i.hi + g_Tilemap.scrollY.i.hi;
    if (self->velocityX < 0) {
        if (posX < 0x20) {
            self->posX.i.hi = 0x20 - g_Tilemap.scrollX.i.hi;
        }
    } else if (posX > 0x1E0) {
        self->posX.i.hi = 0x1E0 - g_Tilemap.scrollX.i.hi;
    }
    if (self->velocityY < 0) {
        if (posY < 0x30) {
            self->posY.i.hi = 0x30 - g_Tilemap.scrollY.i.hi;
        }
    } else if (posY > 0xB0) {
        self->posY.i.hi = 0xB0 - g_Tilemap.scrollY.i.hi;
    }
}

void func_us_8019E558(Entity* self) {
    // !FAKE: Preserve the unused stack space in the original function.
    Collider unused;
    Entity* entity;
    s16 angle;

    switch (self->step) {
    case 0:
        if ((self->params == 3) || (self->params == 6)) {
            InitializeEntity(D_us_801804E8);
        } else {
            InitializeEntity(g_EInitDeath2);
        }
        self->animCurFrame = D_us_8018078C[self->params][3];
        self->drawFlags |= ENTITY_ROTATE;
        // fallthrough
    case 1:
        self->rotate = self->ext.deathSecondForm.rotate;
        if (g_BossMgrState & BOSS_MGR_DEATH_DEFEAT) {
            self->step = 2;
        }
        break;
    case 2:
        self->rotate = self->ext.deathSecondForm.rotate;
        if (!(Random() & 0x3F)) {
            PlaySfxPositional(SFX_EXPLODE_A);
            entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (entity != NULL) {
                CreateEntityFromEntity(E_UNK_1F, self, entity);
                entity->params = 0;
                entity->zPriority = self->zPriority + 1;
            }
        }
        if (g_BossMgrState & BOSS_MGR_DEATH_REWARD_READY) {
            self->animCurFrame = 0;
            self->step = 3;
        }
        break;
    case 3:
        self->animCurFrame = 0;
        self->hitboxState = 0;
        return;
    }

    switch (self->params) {
    case 3:
        switch (self->step_s) {
        case 0:
            self->animCurFrame = 0xA;
            if (D_us_80180784) {
                entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
                if (entity != NULL) {
                    CreateEntityFromEntity(E_UNK_1D, self, entity);
                    entity->facingLeft = self->facingLeft;
                    entity->ext.deathBossScythe.owner = self;
                    self->ext.deathSecondForm.unk90 = 0;
                    self->step_s++;
                } else {
                    D_us_80180784 = 0;
                }
            }
            break;
        case 1:
            self->animCurFrame = 9;
            if (self->ext.deathSecondForm.unk90) {
                D_us_80180784 = 0;
                self->step_s = 0;
            }
            break;
        }
        if ((g_BossMgrState & 0x20) && (self->animCurFrame == 0xA)) {
            entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
            if (entity != NULL) {
                CreateEntityFromEntity(E_UNK_1D, self, entity);
                entity->facingLeft = self->facingLeft;
                entity->rotate = self->rotate;
                entity->zPriority = self->zPriority;
                self->animCurFrame = 9;
                self->step_s = 8;
            }
        }
        // fallthrough
    case 6:
        angle = self->rotate;
        self->hitboxOffX = -(rsin(angle) * 12) >> 12;
        self->hitboxOffY = (rcos(angle) * 12) >> 12;
        if (D_us_80180788) {
            self->hitboxState = 1;
        } else {
            self->hitboxState = 0;
        }
        if ((g_BossMgrState & 0x20) && (self->animCurFrame == 0xE)) {
            entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
            if (entity != NULL) {
                CreateEntityFromEntity(E_UNK_1D, self, entity);
                entity->facingLeft = self->facingLeft;
                entity->rotate = self->rotate;
                entity->zPriority = self->zPriority;
                self->animCurFrame = 0xD;
            }
        }
        break;
    case 7:
    case 8:
    case 9:
    case 10:
        self->hitboxState = 0;
        break;
    }
}

void func_us_8019E920(Entity* self) {
    Entity* entity;
    s32 posY;
    s32 posX;
    s32 targetAngle;
    s32 distance;
    s16 angle;

    if ((g_BossMgrState & BOSS_MGR_DEATH_DEFEAT) && (self->step != 3)) {
        self->hitboxState = 0;
        if (self->step) {
            SetStep(3);
        }
    }
    switch (self->step) {
    case 0:
        InitializeEntity(D_us_801804E8);
        self->animCurFrame = 0xF;
        self->drawFlags = ENTITY_ROTATE;
        if (self->facingLeft) {
            self->ext.deathBossScythe.angle = 0;
        } else {
            self->ext.deathBossScythe.angle = 0x800;
        }
        self->ext.deathBossScythe.speed = FIX(8);
        // fallthrough
    case 1:
        MoveEntity();
        self->rotate -= ROT(22.5);
        if (!(g_Timer & 7)) {
            PlaySfxPositional(SFX_BONE_SWORD_SWISH_C);
        }
        posX = PLAYER.posX.i.hi;
        posY = PLAYER.posY.i.hi;
        angle = ratan2(posY - self->posY.i.hi, posX - self->posX.i.hi);
        angle = LimitAngleChange(0x10, self->ext.deathBossScythe.angle, angle);
        self->velocityX = (rcos(angle) * self->ext.deathBossScythe.speed) >> 12;
        self->velocityY = (rsin(angle) * self->ext.deathBossScythe.speed) >> 12;
        if (!(g_Timer & 3)) {
            entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (entity != NULL) {
                CreateEntityFromEntity(E_UNK_1E, self, entity);
                entity->params = self->animCurFrame;
                entity->facingLeft = self->facingLeft;
                entity->rotate = self->rotate;
            }
        }
        self->ext.deathBossScythe.speed -= self->ext.deathBossScythe.speed >> 4;
        if (self->ext.deathBossScythe.speed < FIX(0.25)) {
            self->ext.deathBossScythe.timer = 0x20;
            self->step++;
        }
        break;
    case 2:
        MoveEntity();
        self->rotate -= ROT(22.5);
        if (!(g_Timer & 7)) {
            PlaySfxPositional(SFX_BONE_SWORD_SWISH_C);
        }
        entity = self->ext.deathBossScythe.owner;
        posX = entity->posX.i.hi;
        posY = entity->posY.i.hi;
        posX -= self->posX.i.hi;
        posY -= self->posY.i.hi;
        targetAngle = ratan2(posY, posX);
        distance = SquareRoot0(posX * posX + posY * posY);
        if (distance > 0x20) {
            angle = LimitAngleChange(
                0x60, self->ext.deathBossScythe.angle, (s16)targetAngle);
        } else {
            angle = LimitAngleChange(
                0x30, self->ext.deathBossScythe.angle, (s16)targetAngle);
        }
        self->velocityX = (rcos(angle) * FIX(4)) >> 12;
        posX = rsin(angle);
        self->velocityY = (posX * FIX(4)) >> 12;
        self->ext.deathBossScythe.angle = angle;
        if (distance < 8) {
            PlaySfxPositional(SFX_SWITCH_CLICK);
            entity->ext.deathSecondForm.unk90 = 1;
            DestroyEntity(self);
        }
        break;
    case 3:
        switch (self->step_s) {
        case 0:
            self->hitboxState = 0;
            self->velocityX = 0;
            self->velocityY = 0;
            self->flags |= FLAG_DESTROY_IF_OUT_OF_CAMERA;
            self->step_s++;
            // fallthrough
        case 1:
            MoveEntity();
            self->velocityY += FIX(0.25);
            self->rotate -= ROT(11.25);
            break;
        }
        break;
    }
}

void func_us_8019ECCC(Entity* self) {
    if (g_BossMgrState & BOSS_MGR_DEATH_DEFEAT) {
        DestroyEntity(self);
        return;
    }
    if (!self->step) {
        InitializeEntity(D_us_801804DC);
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

void func_us_8019ED80(Entity* self) {
    s16 angle = self->ext.deathSecondForm.rotate;
    Entity* src;

    angle += self->ext.deathSecondForm.angleOffset;
    if (g_CurrentEntity->facingLeft) {
        angle = -angle;
    }

    src = self->ext.deathSecondForm.parent;
    self->posX.val = src->posX.val;
    self->posY.val = src->posY.val;
    self->posX.val -= self->ext.deathSecondForm.length * rsin(angle) * 16;
    self->posY.val += self->ext.deathSecondForm.length * rcos(angle) * 16;
    self->ext.deathSecondForm.unkA8 |= 1;
}

void polarPlacePartsWithAngvel(s16* entOffsets) {
    Entity* ent;

    while (*entOffsets) {
        if (*entOffsets != 0xFF) {
            ent = g_CurrentEntity + *entOffsets;
            ent->ext.deathSecondForm.rotate += ent->ext.deathSecondForm.rotVel;
            func_us_8019ED80(ent);
        }
        entOffsets++;
    }
}

void func_801CDD00(Entity* entity, s16 arg1, s16 arg2) {
    s16 temp_t0 = arg1 - entity->ext.deathSecondForm.rotate;

    if (temp_t0 > 0x800) {
        temp_t0 = temp_t0 - 0x1000;
    }

    if (temp_t0 < -0x800) {
        temp_t0 = temp_t0 + 0x1000;
    }

    temp_t0 = temp_t0 / arg2;
    entity->ext.deathSecondForm.rotVel = temp_t0;
    entity->ext.deathSecondForm.unkA4 = arg1;
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

    arg1 += (u16)g_CurrentEntity->ext.deathSecondForm.unkB0[arg2];

    if (!g_CurrentEntity->ext.deathSecondForm.unkB4[arg2]) {
        func_801CDD80(entIndices, arg1);
        g_CurrentEntity->ext.deathSecondForm.unkB4[arg2] = arg1->unk0;
    }
    if (!--g_CurrentEntity->ext.deathSecondForm.unkB4[arg2]) {
        arg1++;
        if (!arg1->unk0) {
            g_CurrentEntity->ext.deathSecondForm.unkB0[arg2] = 0;
        } else {
            ++g_CurrentEntity->ext.deathSecondForm.unkB0[arg2];
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
        g_CurrentEntity->ext.deathSecondForm.unkB0[i] = 0;
        g_CurrentEntity->ext.deathSecondForm.unkB4[i] = 0;
    }
}

void func_801CE228(void) {
    s32 i;

    //! @bug The original loop writes four entries into two-element arrays.
    for (i = 0; i < 4; i++) {
        g_CurrentEntity->ext.deathSecondForm.unkB0[i] = 0;
        g_CurrentEntity->ext.deathSecondForm.unkB4[i] = 0;
    }
}

void polarPlacePartsList(s16* offsets) {
    Entity* entity;

    while (*offsets) {
        entity = g_CurrentEntity + *offsets;
        if (!entity->ext.deathSecondForm.unkA8) {
            func_us_8019ED80(entity);
        }
        offsets++;
    }
}

// decompiled in src/boss/bo1/e_explosion_flame.c
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
            CreateEntityFromEntity(E_UNK_1F, g_CurrentEntity, entity);
            entity->ext.deathFlames.unk89 = 6 - i;
            entity->ext.deathFlames.unk88 = pattern;
            entity->params = 2;
            entity->ext.deathFlames.angle = angle;
            entity->zPriority = g_CurrentEntity->zPriority + 1;
        }
    }
}

extern DeathFlamesInit D_us_80180B44[];

void func_us_8019F260(Entity* self) {
    DeathFlamesInit* init;
    s32 params;
    Entity* entity;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitParticle);
        params = self->params & 0xF;
        init = &D_us_80180B44[params];
        self->palette = init->palette + 0x2E0;
        self->blendMode = init->blendMode;
        self->animSet = init->animSet;
        self->unk5A = init->unk5A;
        self->ext.deathFlames.frames = init->frames;
        self->step = params + 1;
        if (self->params & 0xFF00) {
            self->zPriority = (self->params & 0xFF00) >> 8;
        }
        if (self->params & 0xF0) {
            self->palette = PAL_FLAG(PAL_UNK_19F);
            self->blendMode = BLEND_TRANSP;
            self->facingLeft = true;
        }
        break;
    case 1:
        if (!self->step_s) {
            self->velocityY = FIX(-0.25);
            self->step_s++;
        }
        MoveEntity();
        if (!AnimateEntity(self->ext.deathFlames.frames, self)) {
            DestroyEntity(self);
        }
        break;
    case 2:
        if (!self->step_s) {
            self->drawFlags = ENTITY_OPACITY;
            self->opacity = 0x60;
            self->facingLeft = Random() & 1;
            self->velocityX = (Random() << 8) - FIX(0.5);
            self->velocityY = FIX(-2.5);
            self->ext.deathFlames.unk8C = -(Random() * 16) - FIX(0.0625);
            self->step_s++;
        }
        MoveEntity();
        self->velocityY += self->ext.deathFlames.unk8C;
        self->opacity -= 1;
        if (LOW(self->pose) == 8) {
            entity = AllocEntity(&g_Entities[64], &g_Entities[256]);
            if (entity != NULL) {
                CreateEntityFromEntity(E_UNK_1F, self, entity);
                entity->params = 1;
                entity->zPriority = self->zPriority - 1;
            }
        }
        if (!AnimateEntity(self->ext.deathFlames.frames, self)) {
            DestroyEntity(self);
        }
        break;
    }
}

extern EInit g_EInitInteractable;
extern u32 g_CutsceneFlags;

void EntityBossFightManager(Entity* self) {
    Entity* entity;
    u32 posX;
    s32 posY;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
        self->flags |= FLAG_UNK_10000;
        // fallthrough

    case 1:
        posX = PLAYER.posX.i.hi + g_Tilemap.scrollX.i.hi;
        if ((posX - 0x41) < 0x17F) {
            g_BossMgrState |= BOSS_MGR_ROOM_ENTERED;
            self->step++;
        }
        break;

    case 2:
        if (g_CastleFlags[DEATH_FIGHT_CS] ||
            (g_PlayableCharacter != PLAYER_ALUCARD) ||
            (g_DemoMode != Demo_None)) {
            posX = PLAYER.posX.i.hi + g_Tilemap.scrollX.i.hi;
            if ((posX - 0x81) >= 0xFF) {
                break;
            }
        } else if (!(g_CutsceneFlags & 2)) {
            break;
        }
        g_api.TimeAttackController(
            TIMEATTACK_EVENT_DEATH_DEFEAT, TIMEATTACK_SET_VISITED);
        stopMusicFlag = true;
        currentMusicId = MU_DEATH_BALLAD;
        g_BossMgrState |= BOSS_MGR_DEATH_FIGHT_ON;
        self->step++;
        break;

    case 3:
        if (g_api.func_80131F68() == false) {
            stopMusicFlag = false;
            g_api.PlaySfx(currentMusicId);
            self->step++;
        }
        // fallthrough

    case 4:
        if (g_BossMgrState & BOSS_MGR_DEATH_DEFEAT) {
            g_api.TimeAttackController(
                TIMEATTACK_EVENT_DEATH_DEFEAT, TIMEATTACK_SET_RECORD);
            g_api.PlaySfx(SET_UNK_90);
            currentMusicId = MU_ABANDONED_PIT;
            self->step++;
        }
        break;

    case 5:
        if (g_BossMgrState & BOSS_MGR_DEATH_REWARD_READY) {
            self->step++;
        }
        break;

    case 6:
        posX = 0x100 - g_Tilemap.scrollX.i.hi;
        posY = 0x80 - g_Tilemap.scrollY.i.hi;
        entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
        if (entity != NULL) {
            CreateEntityFromEntity(E_LIFE_UP_SPAWN, self, entity);
            entity->posX.i.hi = posX;
            entity->posY.i.hi = posY;
            entity->params = 0x15;
            stopMusicFlag = true;
            currentMusicId = MU_ABANDONED_PIT;
            g_BossMgrState |= BOSS_MGR_DEATH_REWARD_SPAWNED;
            self->step++;
        }
        break;

    case 7:
        if (g_api.func_80131F68() == false) {
            stopMusicFlag = false;
            g_api.PlaySfx(currentMusicId);
            self->step++;
        }
        break;
    }

    FntPrint("set_step %x\n", self->step);
    FntPrint("boss_flag %x\n", g_BossMgrState);
}
