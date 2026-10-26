// SPDX-License-Identifier: AGPL-3.0-or-later
#include "bo7.h"

extern EInit D_us_8018046C;
extern EInit D_us_80180478;
extern EInit g_EInitCerberos;
extern s16 D_us_801806D8[];
extern s16 D_us_801806F0[][2];
extern s8 D_us_801807E4[];
extern u8 D_us_8018081C[];
extern u8 D_us_801806FC[];
extern u8 D_us_80180708[];
extern u8 D_us_8018071C[];
extern u8 D_us_8018072C[];
extern u8 D_us_8018073C[];
extern u8 D_us_80180748[];
extern u8 D_us_80180754[];
extern u8 D_us_80180760[];
extern u8 D_us_8018076C[];
extern u8 D_us_80180778[];
extern u8 D_us_80180788[];

extern u16 D_us_801806E8[];
extern u8* D_us_801807BC[];
extern u8 D_us_801807C8[];
extern s32 D_us_80180848;

bool func_us_80194338_from_rbo0(s16* offsets) {
    s32 posY;

    offsets++;
    posY = g_CurrentEntity->posY.i.hi + *offsets + g_Tilemap.scrollY.i.hi;
    posY = 0xD0 - posY;
    if (posY <= 0) {
        g_CurrentEntity->posY.i.hi += posY;
        g_CurrentEntity->velocityX = 0;
        g_CurrentEntity->velocityY = 0;
        return true;
    }
    return false;
}

void func_us_80194D3C(Entity* self) {
    Entity* entity;
    s32 posX;
    s32 side;
    s32 i;
    s8* hitbox;

    if (self->flags & FLAG_DEAD) {
        if (self->step != 8) {
            SetStep(8);
        }
    }
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitCerberos);
        self->hitboxState = 0;
        SetStep(2);
        // fallthrough
    case 2:
        AnimateEntity(D_us_801806FC, self);
        if (D_us_80180848 & 2) {
            self->hitboxState = 3;
            SetStep(3);
        }
        break;
    case 3:
        if (!self->step_s) {
            self->ext.cerberus.timer = 0x40;
            self->step_s++;
        }
        if (!AnimateEntity(D_us_80180708, self)) {
            PlaySfxPositional(SFX_WARG_GROWL);
        }
        if (GetDistanceToPlayerX() < 0x68) {
            self->ext.cerberus.backOff = 1;
        }
        if (GetDistanceToPlayerX() > 0x80) {
            self->ext.cerberus.backOff = 0;
        }
        if (GetDistanceToPlayerX() > 0x30) {
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        }
        MoveEntity();
        if (self->facingLeft != self->ext.cerberus.backOff) {
            self->velocityX = FIX(0.5);
        } else {
            self->velocityX = FIX(-0.5);
        }
        if (!--self->ext.cerberus.timer) {
            entity = &PLAYER;
            posX = self->posX.i.hi + g_Tilemap.scrollX.i.hi;
            SetStep(10);
            if (self->facingLeft) {
                posX = 0x200 - posX;
            }
            side = (GetSideToPlayer() & 1) ^ 1;
            if (posX < 0xD0 && self->facingLeft == side) {
                SetStep(9);
            }
            if (abs(posX) > 0x50 && self->facingLeft != side) {
                SetStep(9);
            }
            if (posX > 0x140 && self->facingLeft == side) {
                SetStep(6);
            }
            if (posX > 0x180 && self->facingLeft == side) {
                SetStep(4);
            }
            if ((g_Player.status & PLAYER_STATUS_BAT_FORM) ||
                (entity->posY.i.hi < 0xA0 &&
                 g_Player.vram_flag & TOUCHING_GROUND)) {
                SetStep(5);
            }
        }
        break;
    case 11:
        switch (self->step_s) {
        case 0:
            if (!AnimateEntity(D_us_8018071C, self)) {
                if (self->facingLeft) {
                    self->velocityX = FIX(-6);
                } else {
                    self->velocityX = FIX(6);
                }
                self->ext.cerberus.timer = 0x40;
                self->step_s++;
            }
            break;
        case 1:
            MoveEntity();
            self->velocityX -= self->velocityX >> 6;
            if (!--self->ext.cerberus.timer) {
                SetStep(3);
            }
            break;
        }
        break;
    case 5:
        switch (self->step_s) {
        case 0:
            if (!AnimateEntity(D_us_80180754, self)) {
                SetSubStep(1);
            }
            break;
        case 1:
            if (!AnimateEntity(D_us_80180748, self)) {
                PlaySfxPositional(SFX_WARG_ATTACK);
                PlaySfxPositional(SFX_SHAFT_FIRE_ATTACK);
                self->ext.cerberus.timer = 0x80;
                SetSubStep(2);
            }
            break;
        case 2:
            if (!(self->ext.cerberus.timer & 3)) {
                for (i = 0; i < 3; i++) {
                    entity = AllocEntity(&g_Entities[128], &g_Entities[224]);
                    if (entity != NULL) {
                        CreateEntityFromEntity(E_UNK_1E, self, entity);
                        if (self->facingLeft) {
                            entity->posX.i.hi -= D_us_801806F0[i][0];
                        } else {
                            entity->posX.i.hi += D_us_801806F0[i][0];
                        }
                        entity->posY.i.hi += D_us_801806F0[i][1];
                        entity->params = i;
                        entity->zPriority = self->zPriority + 1;
                        entity->facingLeft = self->facingLeft;
                    }
                }
            }
            if (!--self->ext.cerberus.timer) {
                self->step_s++;
            }
            break;
        case 3:
            if (AnimateEntity(D_us_80180760, self)) {
                SetStep(3);
            }
            break;
        }
        break;
    case 10:
        if (!AnimateEntity(D_us_8018073C, self)) {
            SetStep(3);
        }
        if (*(s32*)&self->pose == 3) {
            PlaySfxPositional(SFX_B07_STOMP);
            PlaySfxPositional(SFX_WARG_ATTACK);
            entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
            if (entity != NULL) {
                CreateEntityFromEntity(E_UNK_1D, self, entity);
                entity->facingLeft = self->facingLeft;
                if (self->facingLeft) {
                    entity->posX.i.hi += 0x18;
                } else {
                    entity->posX.i.hi -= 0x18;
                }
                entity->params = self->ext.cerberus.projectileType;
                entity->zPriority = self->zPriority + 1;
            }
        }
        break;
    case 9:
        switch (self->step_s) {
        case 0:
            if (!AnimateEntity(D_us_80180778, self)) {
                SetSubStep(1);
            }
            break;
        case 1:
            self->velocityY = FIX(-6);
            if (self->facingLeft) {
                self->velocityX = FIX(-2.5);
            } else {
                self->velocityX = FIX(2.5);
            }
            self->step_s++;
            // fallthrough
        case 2:
            MoveEntity();
            self->velocityY += FIX(0.21875);
            if (func_us_80194338_from_rbo0(D_us_801806D8) & 1) {
                PlaySfxPositional(SFX_START_SLAM_B);
                g_api.ShakeCamera(1);
                self->step_s++;
            }
            break;
        case 3:
            if (!AnimateEntity(D_us_80180788, self)) {
                SetStep(3);
            }
            break;
        }
        break;
    case 4:
        switch (self->step_s) {
        case 0:
            if (!AnimateEntity(D_us_80180778, self)) {
                SetSubStep(1);
            }
            break;
        case 1:
            self->velocityY = FIX(-6);
            if (self->facingLeft) {
                self->velocityX = FIX(2.5);
            } else {
                self->velocityX = FIX(-2.5);
            }
            self->step_s++;
            // fallthrough
        case 2:
            MoveEntity();
            self->velocityY += FIX(0.21875);
            if (func_us_80194338_from_rbo0(D_us_801806D8) & 1) {
                PlaySfxPositional(SFX_START_SLAM_B);
                g_api.ShakeCamera(1);
                self->step_s++;
            }
            break;
        case 3:
            if (!AnimateEntity(D_us_80180788, self)) {
                SetStep(3);
            }
            break;
        }
        break;
    case 6:
        switch (self->step_s) {
        case 0:
            self->ext.cerberus.shotsRemaining = 8;
            self->step_s++;
            // fallthrough
        case 1:
            if (!AnimateEntity(D_us_8018072C, self)) {
                if (!--self->ext.cerberus.shotsRemaining) {
                    SetStep(3);
                }
            }
            if (*(s32*)&self->pose == 5) {
                PlaySfxPositional(SFX_B07_STOMP);
                PlaySfxPositional(SFX_WARG_ATTACK);
                entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
                if (entity != NULL) {
                    CreateEntityFromEntity(E_UNK_1D, self, entity);
                    entity->facingLeft = self->facingLeft;
                    if (self->facingLeft) {
                        entity->posX.i.hi += 0x18;
                    } else {
                        entity->posX.i.hi -= 0x18;
                    }
                    entity->params = self->ext.cerberus.projectileType;
                    entity->zPriority = self->zPriority + 1;
                }
                self->ext.cerberus.projectileType++;
                if (self->ext.cerberus.projectileType > 2) {
                    self->ext.cerberus.projectileType = 0;
                }
            }
            break;
        }
        break;
    case 8:
        switch (self->step_s) {
        case 0:
            self->hitboxState = 0;
            D_us_80180848 |= 4;
            PlaySfxPositional(SFX_WARG_DEATH_HOWL);
            self->step_s++;
            // fallthrough
        case 1:
            if (!(g_Timer & 7)) {
                PlaySfxPositional(SFX_EXPLODE_B);
                entity = AllocEntity(&g_Entities[192], &g_Entities[256]);
                if (entity != NULL) {
                    CreateEntityFromEntity(E_UNK_20, self, entity);
                    entity->params = 1;
                    entity->zPriority = self->zPriority + 1;
                    entity->posX.i.hi += -0x20 + (Random() & 0x3F);
                    entity->posY.i.hi += -0xC + (Random() & 0x1F);
                }
            }
            if (!AnimateEntity(D_us_8018076C, self)) {
                PlaySfxPositional(SFX_BOSS_LARGE_FLAMES);
                self->ext.cerberus.timer = 0x50;
                self->step_s++;
            }
            break;
        case 2:
            entity = AllocEntity(&g_Entities[192], &g_Entities[256]);
            if (entity != NULL) {
                CreateEntityFromEntity(E_UNK_20, self, entity);
                entity->params = 2;
                entity->zPriority = self->zPriority + 1;
                entity->posX.i.hi += -0x20 + (Random() & 0x3F);
                if (self->facingLeft) {
                    entity->posX.i.hi -= 0xC;
                } else {
                    entity->posX.i.hi += 0xC;
                }
                entity->posY.i.hi += 0x18;
            }
            if (!--self->ext.cerberus.timer) {
                self->animCurFrame = 0;
                self->step_s++;
            }
            break;
        case 3:
            D_us_80180848 |= 8;
            self->step_s++;
            break;
        case 4:
            break;
        }
        break;
    case 255:
        FntPrint("charal %x\n", self->animCurFrame);
        if (g_pads[1].pressed & PAD_SQUARE) {
            if (self->params) {
                break;
            }
            self->animCurFrame++;
            self->params |= 1;
        } else {
            self->params = 0;
        }
        if (g_pads[1].pressed & PAD_CIRCLE) {
            if (self->step_s) {
                break;
            }
            self->animCurFrame--;
            self->step_s |= 1;
        } else {
            self->step_s = 0;
        }
        break;
    }
    posX = self->posX.i.hi + g_Tilemap.scrollX.i.hi;
    if (self->velocityX < 0) {
        if (posX < 0x68) {
            self->posX.i.hi = 0x68 - g_Tilemap.scrollX.i.hi;
        }
    } else if (posX > 0x1A0) {
        self->posX.i.hi = 0x1A0 - g_Tilemap.scrollX.i.hi;
    }
    hitbox = D_us_801807E4;
    hitbox += D_us_8018081C[self->animCurFrame] * 4;
    self->hitboxOffX = *hitbox++;
    self->hitboxOffY = *hitbox++;
    self->hitboxWidth = *hitbox++;
    self->hitboxHeight = *hitbox++;
}

void func_us_801959E0(Entity* self) {
    Entity* entity;

    if (D_us_80180848 & 4) {
        DestroyEntity(self);
        return;
    }
    if (self->flags & FLAG_DEAD) {
        entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
        if (entity != NULL) {
            CreateEntityFromEntity(E_EXPLOSION, self, entity);
            entity->params = 1;
        }
        DestroyEntity(self);
        return;
    }
    switch (self->step) {
    case 0:
        InitializeEntity(D_us_8018046C);
        if (self->facingLeft) {
            self->velocityX = FIX(6);
        } else {
            self->velocityX = FIX(-6);
        }
        // fallthrough
    case 1:
        MoveEntity();
        AnimateEntity(D_us_801807BC[self->params], self);
        break;
    }
}

void func_us_80195AF0(Entity* self) {
    s16 angle;
    Entity* entity;

    if (D_us_80180848 & 4) {
        DestroyEntity(self);
        return;
    }
    if (!self->step) {
        InitializeEntity(D_us_80180478);
        self->drawFlags = ENTITY_SCALEX | ENTITY_ROTATE;
        self->scaleX = 0x80;
        self->palette = D_us_801806E8[self->params];
        self->rotate = ROT(-56.25);
        angle = -0x680;
        if (self->facingLeft) {
            angle = -0x180;
        }
        self->velocityX = (rcos(angle) * FIX(6)) >> 12;
        self->velocityY = (rsin(angle) * FIX(6)) >> 12;
    }
    MoveEntity();
    if (!AnimateEntity(D_us_801807C8, self)) {
        DestroyEntity(self);
    }
    if (*(s32*)&self->pose == 8) {
        entity = AllocEntity(&g_Entities[128], &g_Entities[224]);
        if (entity != NULL) {
            CreateEntityFromEntity(E_UNK_1E, self, entity);
            entity->params = self->params;
            entity->facingLeft = self->facingLeft;
        }
    }
}
