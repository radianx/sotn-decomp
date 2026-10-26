// SPDX-License-Identifier: AGPL-3.0-or-later
#include "bo5.h"

extern EInit g_EInitInteractable;
extern EInit D_us_801804F0;
extern s32 D_us_801806E0;
extern u8 D_us_80180A00[];
extern u8 D_us_80180A0C[];
extern u8 D_us_80180B0C[];

void func_us_801A19CC(u8 arg0) {
    g_CurrentEntity->poseTimer = 0;
    g_CurrentEntity->pose = 0;
    g_CurrentEntity->ext.et_801A19CC.unk7D = 0;
    g_CurrentEntity->step = arg0;
    g_CurrentEntity->step_s = 0;
}

void func_us_801A19FC(u8 count, s16 yOffset) {
    Entity* entity;
    s32 i;
    s32 offsetY;

    for (i = 0; i < count; i++) {
        entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (entity != NULL) {
            DestroyEntity(entity);
            MakeEntityFromId(E_UNK_22, g_CurrentEntity, entity);
            entity->flags =
                FLAG_DESTROY_IF_OUT_OF_CAMERA |
                FLAG_DESTROY_IF_BARELY_OUT_OF_CAMERA | FLAG_POS_CAMERA_LOCKED |
                FLAG_UNK_00200000 | FLAG_UNK_2000;
            entity->posX.i.hi += (Random() & 0x3F) - 0x20;
            offsetY = Random() & 0x3F;
            entity->posY.i.hi += offsetY + (s16)(yOffset - 0x20);
            entity->velocityY = -FIX(0.25);
            if (Random() & 1) {
                entity->zPriority++;
            }
            entity->step = 48;
            entity->params = Random() & 1;
            if (entity->params) {
                entity->step = 50;
                if (Random() & 1) {
                    entity->ext.et_801A19CC.accelerationX = 0xD00;
                    entity->velocityX = FIX(-0.8125);
                } else {
                    entity->ext.et_801A19CC.accelerationX = -0xD00;
                    entity->velocityX = FIX(0.8125);
                }
            }
            if (g_CurrentEntity->step == 22) {
                if (g_CurrentEntity->facingLeft) {
                    g_CurrentEntity->velocityX += FIX(0.25);
                } else {
                    g_CurrentEntity->velocityX -= FIX(0.25);
                }
            }
        }
    }
}

bool CheckHippogryphFloorCollision(s16* sensors) {
    s32 posY;

    if (UnkCollisionFunc3(sensors) & 1) {
        return true;
    } else {
        posY = g_CurrentEntity->posY.i.hi + g_Tilemap.scrollY.i.hi;
        if (posY > 183) {
            g_CurrentEntity->posY.i.hi = 183 - g_Tilemap.scrollY.i.hi;
            g_CurrentEntity->velocityX = 0;
            g_CurrentEntity->velocityY = 0;
            return true;
        }
        return false;
    }
}

extern EInit g_EInitHippogryph;
extern s32 D_us_801806DC;
extern s32 D_us_801806E4[];
extern s32 D_us_801807E4[];
extern u8 D_us_80180804[];
extern u8 D_us_80180824[];
extern u8 D_us_80180830[];
extern u8 D_us_80180844[];
extern u8 D_us_80180858[];
extern u8 D_us_80180884[];
extern u8 D_us_8018088C[];
extern u8 D_us_80180894[];
extern u8 D_us_8018089C[];
extern u8 D_us_801808AC[];
extern u8 D_us_801808BC[];
extern u8 D_us_801808D4[];
extern u8 D_us_801808FC[];
extern u8 D_us_8018091C[];
extern u8 D_us_80180928[];
extern u8 D_us_80180938[];
extern u8 D_us_80180944[];
extern u8 D_us_80180950[];
extern u8 D_us_8018096C[];
extern u8 D_us_8018098C[];
extern u8 D_us_801809D8[];
extern u8 D_us_80180A2C[];
extern u8 D_us_80180A48[];
extern s16 D_us_80180AAC[];
extern s16 D_us_80180ACC[];
extern s16 D_us_80180ADC[];
extern s16 D_us_80180AE4[];
extern u8 D_us_80180AEC[];
extern s32 D_us_80180B74;
void func_us_801A3B88(Entity* self);

// !FAKE: Reserved words preserve the original fixed-point scratch offsets.
typedef struct {
    s32 radialVelocity;
    s32 : 32;
    s32 : 32;
    s32 radius;
    s32 posX;
    s32 posY;
    s32 velocityX;
    s32 velocityY;
} HippogryphDeathScratch;

void func_us_801A1C14(Entity* self) {
    HippogryphDeathScratch scratch;
    Entity* entity;
    Entity* pool;
    Primitive* prim;
    s32 i;
    s32 x;
    s32 y;
    s16 primIndex;
    u8 count;
    s32 value;
    s32 angle;

    entity = &PLAYER;

    if (self->hitParams && (self->step & 1)) {
        if (self->facingLeft) {
            self->velocityX = -FIX(1.5);
        } else {
            self->velocityX = FIX(1.5);
        }
        self->velocityY = -FIX(4);
        func_us_801A19CC(32);
    }
    if ((self->flags & FLAG_DEAD) && self->step < 34) {
        self->hitboxState = 0;
        HIH(self->velocityX) = 0;
        HIH(self->velocityY) = 0;
        self->ext.et_801A19CC.unk7C = 0;
        self->animCurFrame = 0x6E;
        if (self->ext.et_801A19CC.entity != NULL) {
            DestroyEntity(self->ext.et_801A19CC.entity);
        }
        if (self->flags & FLAG_HAS_PRIMS) {
            g_api.FreePrimitives(self->primIndex);
            self->flags &= ~FLAG_HAS_PRIMS;
        }
        func_us_801A19CC(36);
    }
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitHippogryph);
        self->ext.et_801A19CC.originalPriority = self->zPriority;
        self->zPriority = entity->zPriority + 1;
        self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        self->ext.et_801A19CC.unk7D = 1;
        break;
    case 1:
        self->hitboxState = 0;
        AnimateEntity(D_us_8018091C, self);
        if (self->ext.et_801A19CC.unk7D && GetDistanceToPlayerX() < 128) {
            func_us_801A19CC(3);
            if (!D_us_801806DC) {
                g_api.TimeAttackController(
                    TIMEATTACK_EVENT_HYPPOGRYPH_DEFEAT, TIMEATTACK_SET_VISITED);
            }
            self->hitboxState = 3;
            self->nextPart = self + 1;
            D_us_801806DC |= 1;
            CreateEntityFromEntity(E_UNK_23, self, self + 1);
        }
        break;
    case 3:
        if (!AnimateEntity(D_us_80180804, self)) {
            func_us_801A19CC(4);
        }
        break;
    case 4:
        switch (self->step_s) {
        case 0:
            if (!AnimateEntity(D_us_801808BC, self)) {
                self->animCurFrame = 0x31;
                self->velocityY = -FIX(5);
                self->ext.et_801A19CC.unk7C = 4;
                self->ext.et_801A19CC.unk7D = 0;
                self->step_s++;
            }
            if (self->animCurFrame == 0x29 && !self->ext.et_801A19CC.unk7D) {
                func_us_801A19FC(4, 0);
                self->ext.et_801A19CC.unk7D = 1;
                if (self->facingLeft) {
                    self->velocityX = FIX(0.375);
                } else {
                    self->velocityX = -FIX(0.375);
                }
                self->posY.i.hi -= 4;
            }
            if (self->ext.et_801A19CC.unk7D) {
                MoveEntity();
                if (self->animCurFrame >= 0x2A && self->animCurFrame <= 0x2B) {
                    self->velocityY -= FIX(0.375);
                }
            }
            y = self->posY.i.hi + g_Tilemap.scrollY.i.hi;
            if (y < 114) {
                self->animCurFrame = 0x31;
                self->velocityY = -FIX(4.5);
                self->ext.et_801A19CC.unk7D = 0;
                self->step_s = 2;
            }
            break;
        case 1:
            MoveEntity();
            self->velocityY += FIX(0.1171875);
            if (!--self->ext.et_801A19CC.unk7C) {
                self->pose = 0;
                self->ext.et_801A19CC.unk7C = 0;
                self->step_s++;
            }
            y = self->posY.i.hi + g_Tilemap.scrollY.i.hi;
            if (y < 114) {
                self->animCurFrame = 0x31;
                self->velocityY = -FIX(4.5);
                self->ext.et_801A19CC.unk7D = 0;
                self->step_s = 2;
            }
            break;
        case 2:
            MoveEntity();
            self->velocityY += FIX(0.125);
            if (!AnimateEntity(D_us_801808D4, self)) {
                func_us_801A19CC(6);
            }
            break;
        }
        break;
    case 6:
        if (!self->step_s) {
            self->ext.et_801A19CC.unk7C = 80;
            if (self->facingLeft) {
                self->velocityX = FIX(1.75);
            } else {
                self->velocityX = -FIX(1.75);
            }
            self->velocityY = 0;
            self->step_s++;
        }
        MoveEntity();
        AnimateEntity(D_us_80180830, self);
        if (*(s32*)&self->pose == 1) {
            PlaySfxPositional(SFX_HIPPOGRYPH_WING_FLAP);
        }
        if (self->animCurFrame >= 6 && self->animCurFrame <= 7) {
            self->velocityY -= FIX(0.15625);
        } else {
            self->velocityY += FIX(0.0546875);
        }
        if (!--self->ext.et_801A19CC.unk7C) {
            x = self->posX.i.hi + g_Tilemap.scrollX.i.hi;
            if (self->velocityX < 0) {
                x = 512 - x;
            }
            if (GetDistanceToPlayerX() > 80 && x < 144) {
                self->velocityX = 0;
                self->velocityY = 0;
                func_us_801A19CC(22);
            } else if (x < 384) {
                func_us_801A19CC(8);
            } else {
                self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
                func_us_801A19CC(6);
            }
        }
        break;
    case 8:
        switch (self->step_s) {
        case 0:
            if (self->facingLeft) {
                self->velocityX = FIX(0.5);
            } else {
                self->velocityX = -FIX(0.5);
            }
            self->velocityY = FIX(3.5);
            self->step_s++;
            // fallthrough
        case 1:
            if (!AnimateEntity(D_us_80180938, self)) {
                self->pose = 0;
                self->poseTimer = 0;
                self->step_s++;
            }
            MoveEntity();
            if ((y = self->posY.i.hi + g_Tilemap.scrollY.i.hi) > 136) {
                self->pose = 0;
                self->poseTimer = 0;
                self->step_s = 2;
            }
            break;
        case 2:
            AnimateEntity(D_us_80180944, self);
            MoveEntity();
            if (CheckColliderOffsets(D_us_80180ADC, 0)) {
                self->pose = 0;
                self->poseTimer = 0;
                self->ext.et_801A19CC.unk7D = 0;
                self->step_s++;
            }
            break;
        case 3:
            if ((CheckHippogryphFloorCollision(D_us_80180AAC) & 1) &&
                !self->ext.et_801A19CC.unk7D) {
                self->ext.et_801A19CC.unk7D = 1;
            }
            self->velocityY -= FIX(0.484375);
            if (self->velocityY <= FIX(0.5)) {
                self->velocityY = FIX(0.5);
            }
            if (!AnimateEntity(D_us_80180950, self) &&
                self->ext.et_801A19CC.unk7D) {
                func_us_801A19CC(10);
                self->ext.et_801A19CC.unk7D = 0;
            }
            break;
        }
        break;
    case 10:
        self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        x = Random() & 7;
        count = x;
        value = GetDistanceToPlayerX();
        if (value > 80) {
            count += 4;
        }
        if (value > 128) {
            count += 4;
        }
        func_us_801A19CC(D_us_80180AEC[count]);
        break;
    case 12:
        switch (self->step_s) {
        case 0:
            if (!AnimateEntity(D_us_80180858, self)) {
                self->ext.et_801A19CC.unk7C = 64;
                self->step_s++;
                PlaySfxPositional(SFX_HIPPOGRYPH_FIRE_ATTACK);
            }
            if (*(s32*)&self->pose == 4) {
                PlaySfxPositional(SFX_ELECTRICITY);
            }
            break;
        case 1:
            if (self->ext.et_801A19CC.unk7C & 1) {
                entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (entity != NULL) {
                    CreateEntityFromEntity(E_UNK_27, self, entity);
                    entity->pfnUpdate = func_us_801A3B88;
                    entity->facingLeft = self->facingLeft;
                    if (self->facingLeft) {
                        entity->posX.i.hi += 29;
                    } else {
                        entity->posX.i.hi -= 29;
                    }
                    entity->posY.i.hi -= 2;
                    entity->params = self->ext.et_801A19CC.unk7D;
                }
                pool = &g_Entities[224];
                if (self->ext.et_801A19CC.unk7D) {
                    pool = g_Entities;
                    pool += 160;
                }
                entity = AllocEntity(pool, pool + 32);
                if (entity != NULL) {
                    DestroyEntity(entity);
                    CreateEntityFromEntity(E_UNK_27, self, entity);
                    entity->pfnUpdate = func_us_801A3B88;
                    entity->facingLeft = self->facingLeft;
                    if (self->facingLeft) {
                        entity->posX.i.hi += 29;
                    } else {
                        entity->posX.i.hi -= 29;
                    }
                    entity->params = 2;
                    entity->posY.i.hi -= 2;
                    entity->params = self->ext.et_801A19CC.unk7D + 2;
                }
                self->ext.et_801A19CC.unk7D ^= 1;
            }
            if (!--self->ext.et_801A19CC.unk7C) {
                self->ext.et_801A19CC.unk7D = 0;
                func_us_801A19CC(10);
            }
            break;
        }
        break;
    case 13:
        if (!self->ext.et_801A19CC.unk7D) {
            self->ext.et_801A19CC.unk7D = 1;
            self->ext.et_801A19CC.unk7C = 128;
            if (self->facingLeft) {
                self->velocityX = FIX(1.25);
            } else {
                self->velocityX = -FIX(1.25);
            }
            self->velocityY = 0;
        }
        MoveEntity();
        AnimateEntity(D_us_80180824, self);
        if (self->animCurFrame == 5) {
            if (!self->poseTimer) {
                PlaySfxPositional(SFX_STOMP_HARD_A);
            }
            if (self->facingLeft) {
                self->velocityX -= FIX(0.109375);
            } else {
                self->velocityX += FIX(0.109375);
            }
        }
        if (self->animCurFrame == 1) {
            if (self->facingLeft) {
                self->velocityX += FIX(0.109375);
            } else {
                self->velocityX -= FIX(0.109375);
            }
        }
        x = self->posX.i.hi + g_Tilemap.scrollX.i.hi;
        if (self->facingLeft) {
            if (x > 384) {
                self->facingLeft = 0;
                self->velocityX = -FIX(1.25);
                self->pose = 0;
                self->poseTimer = 0;
            }
        } else if (x < 128) {
            self->facingLeft = 1;
            self->velocityX = FIX(1.25);
            self->pose = 0;
            self->poseTimer = 0;
        }
        if (!CheckColliderOffsets(D_us_80180AE4, self->facingLeft)) {
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            func_us_801A19CC(4);
        }
        if (!--self->ext.et_801A19CC.unk7C) {
            func_us_801A19CC(10);
        }
        break;
    case 16:
        switch (self->step_s) {
        case 0:
            if (!AnimateEntity(D_us_801808FC, self)) {
                func_us_801A19FC(4, 0);
                self->ext.et_801A19CC.unk7C = 64;
                if (self->facingLeft) {
                    self->velocityX = FIX(4.5);
                } else {
                    self->velocityX = -FIX(4.5);
                }
                self->velocityY = 0;
                self->pose = 0;
                self->poseTimer = 0;
                self->animCurFrame = 0x21;
                self->step_s++;
            }
            break;
        case 1:
            if (self->ext.et_801A19CC.unk7C < 32) {
                AnimateEntity(D_us_80180884, self);
            }
            MoveEntity();
            self->velocityY -= FIX(0.0625);
            if ((y = self->posY.i.hi + g_Tilemap.scrollY.i.hi) < 72) {
                self->step_s++;
            }
            break;
        case 2:
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            func_us_801A19CC(6);
            break;
        }
        break;
    case 20:
        if (!AnimateEntity(D_us_8018098C, self)) {
            self->ext.et_801A19CC.unk7D = 0;
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            func_us_801A19CC(4);
        }
        if (self->animCurFrame == 0x4D && !self->ext.et_801A19CC.unk7D) {
            self->ext.et_801A19CC.unk7D = 1;
            count = (Random() & 1) | 2;
            for (i = 0; i < count; i++) {
                entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
                if (entity != NULL) {
                    CreateEntityFromEntity(E_UNK_25, self, entity);
                    entity->ext.et_801A3FD4.timer = (Random() & 0x1F) - 0x40;
                    if (self->facingLeft) {
                        entity->velocityX = i * -FIX(0.5) + FIX(0.5);
                        entity->posX.i.hi -= 16;
                    } else {
                        entity->velocityX = -FIX(0.5) + i * FIX(0.5);
                        entity->posX.i.hi += 16;
                    }
                }
            }
        }
        break;
    case 18:
        switch (self->step_s) {
        case 0:
            AnimateEntity(D_us_8018088C, self);
            MoveEntity();
            if (GetDistanceToPlayerY() < 80) {
                self->step_s++;
            }
            break;
        case 1:
            MoveEntity();
            if (!AnimateEntity(D_us_80180894, self)) {
                self->step_s++;
            }
            self->velocityY -= FIX(0.03125);
            if (!g_Player.grabState) {
                x = self->posX.i.hi + g_Tilemap.scrollX.i.hi;
                if (self->facingLeft) {
                    x = 512 - x;
                }
                if (x >= 128) {
                    x = F(PLAYER.posX).i.hi - self->posX.i.hi;
                    y = F(PLAYER.posY).i.hi - self->posY.i.hi;
                    if (y < 0) {
                        y = 128;
                    }
                    if (abs(x) < 12 && y < 56 &&
                        !(g_Player.status &
                          (PLAYER_STATUS_UNK40000000 | PLAYER_STATUS_UNK800000 |
                           PLAYER_STATUS_UNK400000 | PLAYER_STATUS_DEAD |
                           PLAYER_STATUS_INVINCIBLE | PLAYER_STATUS_STONE |
                           PLAYER_STATUS_UNK40 | PLAYER_STATUS_UNK10 |
                           PLAYER_STATUS_MIST_FORM))) {
                        PlaySfxPositional(SFX_HIPPOGRYPH_SQUAWK);
                        g_Player.grabState = 1;
                        g_Player.grabDamage = 16;
                        g_Player.grabReactionEffect = 0;
                        self->posX.i.hi = F(PLAYER.posX).i.hi;
                        self->posY.i.hi = F(PLAYER.posY).i.hi - 32;
                    }
                }
            }
            break;
        case 2:
            MoveEntity();
            self->velocityY -= FIX(0.375);
            if (!AnimateEntity(D_us_8018089C, self)) {
                self->ext.et_801A19CC.unk7C = 64;
                self->step_s++;
                if (!g_Player.grabState) {
                    self->velocityY -= FIX(0.375);
                }
            }
            break;
        case 3:
            if (g_Player.grabState) {
                AnimateEntity(D_us_801808AC, self);
                if (!(u8)(--self->ext.et_801A19CC.unk7C % 47)) {
                    func_us_801A19FC(8, -8);
                    g_Player.grabState = 3;
                    g_Player.grabDamage = 16;
                }
            } else {
                AnimateEntity(D_us_80180830, self);
                if (*(s32*)&self->pose == 1) {
                    PlaySfxPositional(SFX_HIPPOGRYPH_WING_FLAP);
                }
            }
            MoveEntity();
            if ((y = self->posY.i.hi + g_Tilemap.scrollY.i.hi) < 72) {
                g_Player.grabState = 0;
                self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
                func_us_801A19CC(6);
            }
            break;
        }
        if (g_Player.grabState) {
            entity->posX.i.hi = self->posX.i.hi;
            entity->posY.i.hi = self->posY.i.hi + 32;
        }
        break;
    case 22:
        switch (self->step_s) {
        case 0:
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            if (!AnimateEntity(D_us_80180844, self)) {
                self->ext.et_801A19CC.unk7D++;
            }
            if (*(s32*)&self->pose == 1) {
                PlaySfxPositional(SFX_HIPPOGRYPH_WING_FLAP);
            }
            MoveEntity();
            if (self->animCurFrame >= 6 && self->animCurFrame <= 7) {
                self->velocityY -= FIX(0.15625);
            } else {
                self->velocityY += FIX(0.0625);
            }
            if (self->ext.et_801A19CC.unk7D >= 2) {
                self->ext.et_801A19CC.unk7D = 0;
                self->pose = 0;
                self->poseTimer = 0;
                self->step_s++;
                if (self->facingLeft) {
                    self->velocityX = FIX(4);
                } else {
                    self->velocityX = -FIX(4);
                }
                self->velocityY = FIX(4.5);
            }
            break;
        case 1:
            MoveEntity();
            AnimateEntity(D_us_80180884, self);
            self->velocityY -= FIX(0.09375);
            if (self->velocityY <= FIX(0.5)) {
                self->velocityY = FIX(0.5);
            }
            if (CheckColliderOffsets(D_us_80180ADC, 0)) {
                self->pose = 0;
                self->poseTimer = 0;
                self->ext.et_801A19CC.unk7D = 0;
                self->step_s++;
            }
            break;
        case 2:
            self->velocityY -= FIX(0.21875);
            if (CheckHippogryphFloorCollision(D_us_80180AAC) & 1) {
                self->ext.et_801A19CC.unk7D = 1;
            }
            if (self->facingLeft) {
                self->velocityX -= FIX(0.0625);
            } else {
                self->velocityX += FIX(0.0625);
            }
            if (self->animCurFrame == 0x5E) {
                func_us_801A19FC(2, -2);
            }
            if (!AnimateEntity(D_us_8018096C, self) &&
                self->ext.et_801A19CC.unk7D) {
                func_us_801A19CC(10);
            }
            break;
        }
        break;
    case 32:
        AnimateEntity(D_us_80180928, self);
        if (CheckHippogryphFloorCollision(D_us_80180AAC) & 1) {
            self->animCurFrame = 0x50;
            func_us_801A19CC(10);
        }
        break;
    case 36:
        switch (self->step_s) {
        case 0:
            if (g_Player.grabState) {
                g_Player.grabState = 0;
            }
            g_api.TimeAttackController(
                TIMEATTACK_EVENT_HYPPOGRYPH_DEFEAT, TIMEATTACK_SET_RECORD);
            self->velocityY = 0;
            x = self->posX.i.hi + g_Tilemap.scrollX.i.hi;
            D_us_801806E0 |= 2;
            if (x < 56) {
                self->velocityX = FIX(0.5);
            }
            //! @bug This also overrides rightward motion when x < 56.
            if (x < 472) {
                self->velocityX = -FIX(0.5);
            }
            self->step_s++;
            // fallthrough
        case 1:
            MoveEntity();
            self->velocityY += FIX(0.25);
            if ((y = self->posY.i.hi + g_Tilemap.scrollY.i.hi) > 128) {
                self->step_s++;
            }
            break;
        case 2:
            if (CheckHippogryphFloorCollision(D_us_80180AAC) & 1) {
                func_us_801A19FC(22, -32);
                self->step_s = 3;
            } else if ((y = self->posY.i.hi + g_Tilemap.scrollY.i.hi) > 183) {
                func_us_801A19FC(22, -32);
                self->posY.i.hi = 183 - g_Tilemap.scrollY.i.hi;
                self->step_s = 3;
                self->velocityX = 0;
                self->velocityY = 0;
            }
            break;
        case 3:
            primIndex = g_api.AllocPrimitives(PRIM_LINE_G2, 2);
            if (primIndex != -1) {
                self->primIndex = primIndex;
                prim = &g_PrimBuf[primIndex];
                self->ext.et_801A19CC.prim = prim;
                self->flags |= FLAG_HAS_PRIMS;
                while (prim != NULL) {
                    prim->r0 = 0x80;
                    prim->r1 = 0x40;
                    prim->g0 = 0x60;
                    prim->g1 = 0x20;
                    prim->b0 = 0x60;
                    prim->b1 = 0x20;
                    prim->x0 = prim->x1 = self->posX.i.hi;
                    prim->y0 = prim->y1 = self->posY.i.hi;
                    prim->priority = self->zPriority + 2;
                    prim->drawMode =
                        DRAW_TPAGE2 | DRAW_TPAGE | DRAW_UNK02 | DRAW_TRANSP;
                    prim = prim->next;
                }
                self->step_s++;
            } else {
                self->ext.et_801A19CC.prim = NULL;
                self->step_s = 5;
            }
            self->zPriority = self->ext.et_801A19CC.originalPriority - 8;
            break;
        case 4:
            self->ext.et_801A19CC.unk7C += 6;
            i = 6;
            if (self->ext.et_801A19CC.unk7C > 128) {
                i = -8;
            }
            prim = self->ext.et_801A19CC.prim;
            prim->x1 += i;
            prim = prim->next;
            prim->x1 -= i;
            if (self->ext.et_801A19CC.unk7C > 240) {
                g_api.FreePrimitives(self->primIndex);
                self->ext.et_801A19CC.unk7C = 0;
                self->flags &= ~FLAG_HAS_PRIMS;
                self->step_s++;
            }
            break;
        case 5:
            i = 0;
            primIndex = g_api.AllocPrimitives(PRIM_LINE_G2, 111);
            if (primIndex != -1) {
                self->primIndex = primIndex;
                prim = &g_PrimBuf[primIndex];
                self->ext.et_801A19CC.prim = prim;
                self->flags |= FLAG_HAS_PRIMS;
                for (; i < 31; i++) {
                    prim->type = PRIM_LINE_G2;
                    prim->r0 = 0x60;
                    prim->g0 = 0x40;
                    prim->b0 = 0x40;
                    prim->r1 = 0x10;
                    prim->g1 = 8;
                    prim->b1 = 8;
                    prim->x0 = prim->x1 = self->posX.i.hi;
                    prim->y0 = prim->y1 = self->posY.i.hi;
                    F(scratch.radialVelocity).val = D_us_801806E4[i];
                    prim->x2 = F(scratch.radialVelocity).i.hi;
                    prim->x3 = F(scratch.radialVelocity).i.lo;
                    prim->y2 = 0;
                    prim->y3 = 0;
                    prim->priority = self->zPriority + 2;
                    prim->drawMode =
                        DRAW_TPAGE2 | DRAW_TPAGE | DRAW_UNK02 | DRAW_TRANSP;
                    prim = prim->next;
                }
                self->ext.et_801A19CC.particles = prim;
                for (i = 0; i < 80; i++) {
                    prim->type = PRIM_TILE;
                    prim->r0 = 0x70;
                    prim->g0 = 0x70;
                    prim->b0 = 0x70;
                    prim->u0 = 2;
                    prim->v0 = 2;
                    prim->priority = self->zPriority + 2;
                    prim->drawMode =
                        DRAW_TPAGE2 | DRAW_TPAGE | DRAW_UNK02 | DRAW_TRANSP;
                    prim->x0 = self->posX.i.hi;
                    prim->y0 = self->posY.i.hi;
                    prim->x1 = 0;
                    prim->y1 = 0;
                    y = Random() & 7;
                    angle = Random() & 15;
                    angle <<= 8;
                    value = (rsin(angle) * D_us_801807E4[y]) >> 12;
                    F(scratch.velocityX).val = value;
                    prim->x2 = F(scratch.velocityX).i.hi;
                    prim->x3 = F(scratch.velocityX).i.lo;
                    value = (rcos(angle) * D_us_801807E4[y]) >> 12;
                    F(scratch.velocityY).val = value;
                    prim->y2 = F(scratch.velocityY).i.hi;
                    prim->y3 = F(scratch.velocityY).i.lo;
                    prim->r1 = Random() & 0x17;
                    prim->r2 = 0;
                    prim = prim->next;
                }
                self->step_s++;
            } else {
                self->step_s = 8;
            }
            break;
        case 6:
            AnimateEntity(D_us_801809D8, self);
            prim = self->ext.et_801A19CC.particles;
            for (i = 0; i < 80; i++) {
                if (prim->r1) {
                    prim->r1--;
                } else {
                    F(scratch.posX).i.hi = prim->x0;
                    F(scratch.posX).i.lo = prim->x1;
                    F(scratch.posY).i.hi = prim->y0;
                    F(scratch.posY).i.lo = prim->y1;
                    F(scratch.velocityX).i.hi = prim->x2;
                    F(scratch.velocityX).i.lo = prim->x3;
                    F(scratch.velocityY).i.hi = prim->y2;
                    F(scratch.velocityY).i.lo = prim->y3;
                    scratch.posX += scratch.velocityX;
                    scratch.posY += scratch.velocityY;
                    prim->x0 = F(scratch.posX).i.hi;
                    prim->x1 = F(scratch.posX).i.lo;
                    prim->y0 = F(scratch.posY).i.hi;
                    prim->y1 = F(scratch.posY).i.lo;
                    prim->r2++;
                    if (prim->r2 > 32) {
                        prim->u0 = prim->v0 = 1;
                    }
                    if (prim->r2 > 48) {
                        prim->u0 = prim->v0 = 0;
                    }
                }
                prim = prim->next;
            }
            prim = self->ext.et_801A19CC.prim;
            for (i = 0; i < 31; i++) {
                F(scratch.radialVelocity).i.hi = prim->x2;
                F(scratch.radialVelocity).i.lo = prim->x3;
                F(scratch.radius).i.hi = prim->y2;
                F(scratch.radius).i.lo = prim->y3;
                if (self->ext.et_801A19CC.unk7C < 12) {
                    scratch.radius += scratch.radialVelocity;
                }
                prim->x1 =
                    prim->x0 +
                    ((F(scratch.radius).i.hi *
                      rcos((i << 7) + self->ext.et_801A19CC.unk7C * 16)) >>
                     12);
                prim->y1 =
                    prim->y0 +
                    ((F(scratch.radius).i.hi *
                      rsin((i << 7) + self->ext.et_801A19CC.unk7C * 16)) >>
                     12);
                prim->y2 = F(scratch.radius).i.hi;
                prim->y3 = F(scratch.radius).i.lo;
                prim = prim->next;
            }
            if (self->ext.et_801A19CC.unk7C++ > 48) {
                self->blendMode = BLEND_ADD | BLEND_TRANSP;
                self->opacity = 0x80;
                self->drawFlags |= ENTITY_OPACITY;
                self->step_s++;
            }
            if (!(g_Timer & 7)) {
                PlaySfxPositional(SFX_GUARD_TINK);
            }
            break;
        case 7:
            prim = self->ext.et_801A19CC.particles;
            for (i = 0; i < 80; i++) {
                if (prim->r1) {
                    prim->r1--;
                } else {
                    F(scratch.posX).i.hi = prim->x0;
                    F(scratch.posX).i.lo = prim->x1;
                    F(scratch.posY).i.hi = prim->y0;
                    F(scratch.posY).i.lo = prim->y1;
                    F(scratch.velocityX).i.hi = prim->x2;
                    F(scratch.velocityX).i.lo = prim->x3;
                    F(scratch.velocityY).i.hi = prim->y2;
                    F(scratch.velocityY).i.lo = prim->y3;
                    scratch.posX += scratch.velocityX;
                    scratch.posY += scratch.velocityY;
                    prim->x0 = F(scratch.posX).i.hi;
                    prim->x1 = F(scratch.posX).i.lo;
                    prim->y0 = F(scratch.posY).i.hi;
                    prim->y1 = F(scratch.posY).i.lo;
                    prim->r2++;
                    if (prim->r2 > 32) {
                        prim->u0 = prim->v0 = 1;
                    }
                    if (prim->r2 > 48) {
                        prim->u0 = prim->v0 = 0;
                    }
                }
                prim = prim->next;
            }
            prim = self->ext.et_801A19CC.prim;
            for (i = 0; i < 31; i++) {
                prim->r0 -= 2;
                prim->g0--;
                prim->b0--;
                F(scratch.radialVelocity).i.hi = -prim->x2;
                F(scratch.radialVelocity).i.lo = -prim->x3;
                F(scratch.radius).i.hi = prim->y2;
                F(scratch.radius).i.lo = prim->y3;
                if (self->ext.et_801A19CC.unk7C < 20) {
                    scratch.radius += scratch.radialVelocity;
                }
                prim->x1 =
                    prim->x0 +
                    ((F(scratch.radius).i.hi *
                      rcos((i << 7) + self->ext.et_801A19CC.unk7C * 16)) >>
                     12);
                prim->y1 =
                    prim->y0 +
                    ((F(scratch.radius).i.hi *
                      rsin((i << 7) + self->ext.et_801A19CC.unk7C * 16)) >>
                     12);
                prim->y2 = F(scratch.radius).i.hi;
                prim->y3 = F(scratch.radius).i.lo;
                prim = prim->next;
            }
            self->opacity -= 4;
            if (self->opacity > 224) {
                self->opacity = 0;
            }
            if (!(g_Timer & 7)) {
                PlaySfxPositional(SFX_GUARD_TINK);
            }
            if (self->ext.et_801A19CC.unk7C++ > 77) {
                self->ext.et_801A19CC.unk7C = 0;
                g_api.FreePrimitives(self->primIndex);
                self->flags &= ~FLAG_HAS_PRIMS;
                self->step_s++;
            }
            break;
        case 8:
            x = 256 - g_Tilemap.scrollX.i.hi;
            y = 128 - g_Tilemap.scrollY.i.hi;
            entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
            if (entity != NULL) {
                CreateEntityFromCurrentEntity(E_LIFE_UP_SPAWN, entity);
                entity->posX.i.hi = x;
                entity->posY.i.hi = y;
                entity->params = 6;
                D_us_80180B74 = 0;
                CreateEntityFromCurrentEntity(E_CUTSCENE, &g_Entities[200]);
                self->step_s++;
            }
            break;
        case 9:
            break;
        }
        break;
    case 48:
        AnimateEntity(D_us_80180A2C, self);
        self->velocityY -= FIX(0.21875);
        if (UnkCollisionFunc3(D_us_80180ACC) & 1) {
            DestroyEntity(self);
        }
        break;
    case 50:
        AnimateEntity(D_us_80180A48, self);
        self->velocityX += self->ext.et_801A19CC.accelerationX;
        if (self->velocityX > 0xD000 || self->velocityX < FIX(-0.8125)) {
            self->ext.et_801A19CC.accelerationX =
                -self->ext.et_801A19CC.accelerationX;
        }
        self->velocityY -= FIX(0.21875);
        if (UnkCollisionFunc3(D_us_80180ACC) & 1) {
            DestroyEntity(self);
        }
        break;
    case 130:
        FntPrint("charal %x\n", self->animCurFrame);
        if (g_pads[0].pressed & PAD_SQUARE) {
            if (!self->params) {
                self->animCurFrame++;
                self->params |= 1;
            }
        } else {
            self->params = 0;
        }
        break;
    }
    count = self->animCurFrame;
    if (count >= 14 && count <= 24) {
        self->hitboxWidth = 6;
        self->hitboxHeight = 20;
        self->hitboxOffX = 8;
        self->hitboxOffY = -8;
    } else {
        if ((u8)(count - 58) < 6) {
            self->hitboxWidth = 6;
            self->hitboxHeight = 20;
            self->hitboxOffX = 0;
            self->hitboxOffY = -8;
        } else {
            self->hitboxWidth = 20;
            self->hitboxHeight = 8;
            self->hitboxOffX = 0;
            self->hitboxOffY = -2;
        }
    }
}

void func_us_801A3B88(Entity* self) {
    Entity* entity;

    if (D_us_801806E0 & 2) {
        DestroyEntity(self);
        return;
    }
    switch (self->step) {
    case 0:
        InitializeEntity(D_us_801804F0);
        self->animSet = 2;
        self->animCurFrame = 1;
        self->opacity = 0x80;
        self->rotate = ROT(315);
        self->drawFlags |=
            ENTITY_SCALEX | ENTITY_SCALEY | ENTITY_ROTATE | ENTITY_OPACITY;
        self->hitboxState = 0;
        self->scaleX = self->scaleY = 0x20;
        self->blendMode |= BLEND_TRANSP | BLEND_ADD;
        if (self->facingLeft) {
            self->velocityX = FIX(4.40625);
        } else {
            self->velocityX = -FIX(4.40625);
        }
        if (self->params) {
            self->velocityY = FIX(0.1875);
        } else {
            self->velocityY = -FIX(0.375);
        }
        if (self->params >= 2) {
            self->opacity = 0x7C;
            self->velocityY = 0;
            if (self->params == 3) {
                self->hitboxState = 1;
            }
        }
        break;
    case 1:
        AnimateEntity(D_us_80180A00, self);
        MoveEntity();
        self->velocityY -= FIX(0.078125);
        self->opacity -= 5;
        self->scaleY = self->scaleX += 0x18;
        if (self->scaleX > 0xF0) {
            self->velocityX /= 4;
            self->pose = 0;
            self->poseTimer = 0;
            self->step++;
        }
        if (self->params == 3 && (Random() & 1)) {
            entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (entity != NULL) {
                DestroyEntity(entity);
                CreateEntityFromEntity(E_UNK_26, self, entity);
                entity->facingLeft = self->facingLeft;
                entity->params = self->params;
                entity->scaleX = self->scaleX;
                entity->scaleY = self->scaleY;
            }
        }
        if (self->params == 0 && (Random() & 7)) {
            entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (entity != NULL) {
                DestroyEntity(entity);
                CreateEntityFromEntity(E_UNK_26, self, entity);
                entity->facingLeft = self->facingLeft;
                entity->params = self->params;
                entity->scaleX = self->scaleX;
                entity->scaleY = self->scaleY;
            }
        }
        break;
    case 2:
        MoveEntity();
        if (!AnimateEntity(D_us_80180A0C, self)) {
            DestroyEntity(self);
        }
        break;
    }
}

extern EInit g_EInitParticle;
extern AnimateEntityFrame D_us_80180A18[];

void func_us_801A3E78(Entity* self) {
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitParticle);
        self->animSet = 2;
        self->animCurFrame = 1;
        self->drawFlags |= ENTITY_SCALEX | ENTITY_SCALEY | ENTITY_OPACITY;
        self->drawFlags |= ENTITY_ROTATE;
        self->blendMode |= BLEND_TRANSP | BLEND_ADD;
        self->opacity = 0x80;
        if (self->facingLeft) {
            self->velocityX = FIX(1);
        } else {
            self->velocityX = -FIX(1);
        }
        if (self->params) {
            self->velocityY = FIX(0.5);
            return;
        }
        self->velocityY = -FIX(1);
        return;

    case 1:
        MoveEntity();
        if (self->facingLeft) {
            self->velocityX -= FIX(0.125);
        } else {
            self->velocityX += FIX(0.125);
        }
        self->velocityY -= FIX(0.0625);
        if (self->params) {
            self->rotate -= ROT(5.625);
        } else {
            self->rotate += ROT(5.625);
        }
        self->scaleX -= 0xA;
        self->opacity -= 6;
        if (!AnimateEntity(D_us_80180A18, self)) {
            DestroyEntity(self);
        }
        return;
    }
}

extern EInit D_us_801804E4;
extern s16 D_us_80180ABC[];
extern AnimateEntityFrame D_us_801809F0[];
extern AnimateEntityFrame D_us_801809F8[];

void func_us_801A3FD4(Entity* self) {
    Entity* entity;

    if (D_us_801806E0 & 2) {
        self->flags |= FLAG_DEAD;
    }

    if (self->flags & FLAG_DEAD) {
        entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
        if (entity != NULL) {
            DestroyEntity(entity);
            CreateEntityFromEntity(E_EXPLOSION, self, entity);
            entity->params = 0;
        }
        DestroyEntity(self);
        return;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_801804E4);
        self->hitboxState = 2;
        self->drawFlags |= ENTITY_ROTATE;
        self->rotate = ((Random() & 3) << 9) - 0x300;
        self->ext.et_801A3FD4.rotateDir = 1;
        return;

    case 1:
        if (UnkCollisionFunc3(D_us_80180ABC) & 1) {
            self->step++;
        }

    case 2:
        if (!self->ext.et_801A3FD4.timer) {
            if (AnimateEntity(D_us_801809F0, self)) {
                return;
            }
            entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
            if (entity != NULL) {
                DestroyEntity(entity);
                CreateEntityFromEntity(E_EXPLOSION, self, entity);
                entity->params = 0;
            }
            self->facingLeft = GetSideToPlayer() & 1;
            self->drawFlags = ENTITY_DEFAULT;
            if (self->facingLeft) {
                self->velocityX = -FIX(2.5);
            } else {
                self->velocityX = FIX(2.5);
            }
            self->velocityY = -FIX(0.25);
            self->pose = 0;
            self->poseTimer = 0;
            self->hitboxState = 3;
            PlaySfxPositional(SFX_NO1_BIRD_CYCLE);
            self->step++;
            return;
        } else if (self->ext.et_801A3FD4.timer-- < 8) {
            self->rotate += self->ext.et_801A3FD4.rotateDir << 9;
            self->ext.et_801A3FD4.rotateDir = -self->ext.et_801A3FD4.rotateDir;
            return;
        }
        break;

    case 3:
        AnimateEntity(D_us_801809F8, self);
        MoveEntity();
        self->velocityY -= FIX(0.0390625);
        break;
    }
}

void func_us_801A425C(Entity* self) {
    Entity* entity;
    u8 frame;

    if (!self->step) {
        InitializeEntity(g_EInitInteractable);
        self->hitPoints = 0x7FFE;
        self->hitboxState = 2;
        self->nextPart = self->parent = self - 1;
        self->attack = 0;
        self->attackElement = ELEMENT_NONE;
        self->flags |= FLAG_SUPPRESS_STUN;
    }
    entity = self - 1;
    frame = entity->animCurFrame;
    if (frame >= 0x68) {
        frame = 0;
    }
    switch (D_us_80180B0C[frame]) {
    case 0:
        self->hitboxOffX = 0;
        self->hitboxOffY = 0;
        self->hitboxWidth = 0;
        self->hitboxHeight = 0;
        break;
    case 1:
        self->hitboxOffX = 8;
        self->hitboxOffY = -24;
        self->hitboxWidth = 20;
        self->hitboxHeight = 18;
        break;
    case 2:
        self->hitboxOffX = 12;
        self->hitboxOffY = -8;
        self->hitboxWidth = 18;
        self->hitboxHeight = 8;
        break;
    case 3:
        self->hitboxOffX = -2;
        self->hitboxOffY = 24;
        self->hitboxWidth = 8;
        self->hitboxHeight = 18;
        break;
    case 4:
        self->hitboxOffX = 6;
        self->hitboxOffY = 10;
        self->hitboxWidth = 16;
        self->hitboxHeight = 10;
        break;
    case 5:
        self->hitboxOffX = 16;
        self->hitboxOffY = -32;
        self->hitboxWidth = 22;
        self->hitboxHeight = 22;
        break;
    case 6:
        self->hitboxOffX = 2;
        self->hitboxOffY = -32;
        self->hitboxWidth = 12;
        self->hitboxHeight = 24;
        break;
    }
    self->facingLeft = entity->facingLeft;
    self->posX.i.hi = entity->posX.i.hi;
    self->posY.i.hi = entity->posY.i.hi;
    if (entity->entityId != E_UNK_22) {
        DestroyEntity(self);
    }
}

void EntityFireDamageHitbox(Entity* self) {
    if (!self->step) {
        InitializeEntity(D_us_801804F0);
        self->hitboxWidth = 24;
        self->hitboxHeight = 4;
        self->hitboxOffX = -48;
        self->hitboxOffY = -2;
    }
}
