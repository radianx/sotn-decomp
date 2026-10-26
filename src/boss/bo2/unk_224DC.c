// SPDX-License-Identifier: AGPL-3.0-or-later
#include "bo2.h"

extern u8* g_eBreakableAnimations[];
extern u8 g_eBreakableHitboxes[];
extern u8 g_eBreakableExplosionTypes[];
extern u16 g_eBreakableanimSets[];
extern u8 blend_modes[];
extern EInit g_EInitInteractable;
extern s32 D_us_80180AB0;
extern EInit g_EInitMinotaurus;
extern s32 D_us_80180AAC;
extern s16 D_us_801806C8[];
extern s16 D_us_801806D0[];
extern s8 D_us_80180880[][4];
extern u8 D_us_80180908[];
extern u8 D_us_801806E0[];
extern u8 D_us_801806F4[];
extern u8 D_us_80180704[];
extern u8 D_us_80180714[];
extern u8 D_us_80180724[];
extern u8 D_us_80180734[];
extern u8 D_us_8018073C[];
extern u8 D_us_80180750[];
extern u8 D_us_80180770[];
extern u8 D_us_8018077C[];
extern u8 D_us_80180790[];
extern u8 D_us_80180798[];
extern u8 D_us_801807AC[];
extern u8 D_us_801807B4[];
extern u8 D_us_801807D0[];
extern u8 D_us_801807F4[];
extern u8 D_us_801807FC[];
extern u8 D_us_80180808[];
extern u8 D_us_80180810[];
extern u8 D_us_80180818[];
extern u8 D_us_80180824[];
extern u8 D_us_80180850[];
extern u8 D_us_80180858[];

#include "../../st/e_breakable.h"

void func_us_801A2610(void) {
    s32 posX;

    posX = g_CurrentEntity->posX.i.hi + g_Tilemap.scrollX.i.hi;
    if (g_CurrentEntity->velocityX > 0) {
        posX += 0x10;
        if (posX > 0x1B0) {
            g_CurrentEntity->posX.i.hi = 0x1A0 - g_Tilemap.scrollX.i.hi;
        }
    }
    if (g_CurrentEntity->velocityX < 0) {
        posX -= 0x10;
        if (posX < 0x50) {
            g_CurrentEntity->posX.i.hi = 0x60 - g_Tilemap.scrollX.i.hi;
        }
    }
}

void func_us_801A269C(Entity* self) {
    Entity* entity;
    s32 i;
    s8* ptr;
    s32 playerVelocityX;
    s32 arrived;

    if (self->flags & FLAG_DEAD && self->step < 0x40) {
        SetStep(0x40);
    }

    FntPrint("mino_step %x\n", self->step);
    FntPrint("mino_set_step %x\n", self->ext.minotaur.nextStep);
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitMinotaurus);
        self->hitboxState = 0;
        entity = self + 1;
        CreateEntityFromCurrentEntity(E_MINOTAUR_ATTACK_HITBOX, entity);
        // fallthrough
    case 1:
        AnimateEntity(D_us_801806F4, self);
        self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        UnkCollisionFunc3(D_us_801806D0);
        switch (self->step_s) {
        case 0:
            self->palette = PAL_FLAG(PAL_FILL_WHITE);
            self->blendMode = BLEND_SUB | BLEND_TRANSP;
            self->opacity = 0;
            self->drawFlags |= ENTITY_OPACITY;
            self->step_s++;
            // fallthrough
        case 1:
            self->opacity += 4;
            if (self->opacity == 0x80) {
                self->palette = g_EInitMinotaurus[3];
                self->blendMode = BLEND_NO;
                self->opacity = 0;
                self->step_s++;
            }
            break;
        case 2:
            self->opacity += 4;
            if (self->opacity == 0x80) {
                self->drawFlags = ENTITY_DEFAULT;
                D_us_80180AB0 = 1;
                self->step_s++;
            }
            break;
        case 3:
            if (D_us_80180AAC) {
                self->hitboxState = 3;
                SetStep(2);
            }
            break;
        }
        break;
    case 2:
        if (!self->step_s) {
            if (!self->ext.minotaur.moveTimer) {
                self->ext.minotaur.moveTimer = 0x20;
            }
            self->ext.minotaur.isReady = false;
            self->step_s++;
        }

        AnimateEntity(D_us_801806F4, self);
        self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        if (self->ext.minotaur.moveTimer) {
            self->ext.minotaur.moveTimer--;
        } else {
            self->ext.minotaur.isReady = true;
        }

        if (self->ext.minotaur.deathPuffPosX) {
            self->ext.minotaur.isReady = false;
            SetStep(7);
        } else if (self->ext.minotaur.hasNextStep) {
            self->ext.minotaur.hasNextStep = false;
            self->ext.minotaur.isReady = false;
            SetStep(self->ext.minotaur.nextStep);
        } else {
            entity = &PLAYER;
            playerVelocityX = entity->velocityX;
            if (self->facingLeft) {
                playerVelocityX = -playerVelocityX;
            }
            if (self->facingLeft == entity->facingLeft) {
                if (GetDistanceToPlayerX() > 0x48 &&
                    GetDistanceToPlayerX() < 0x60 &&
                    g_Player.status & PLAYER_STATUS_UNK400 &&
                    playerVelocityX > 0) {
                    self->ext.minotaur.isReady = false;
                    SetStep(0x12);
                }
                if (self->facingLeft == entity->facingLeft &&
                    g_Player.status & PLAYER_STATUS_SUBWPN) {
                    self->ext.minotaur.isReady = false;
                    SetStep(0x10);
                }
            }
        }
        break;
    case 7:
        if (!self->step_s) {
            i = self->ext.minotaur.deathPuffPosX;
            if (self->posX.i.hi > PLAYER.posX.i.hi) {
                i += PLAYER.posX.i.hi;
                i += g_Tilemap.scrollX.i.hi;
                if (i > 0x190) {
                    i = 0x190;
                }
            } else {
                i = PLAYER.posX.i.hi - i;
                i += g_Tilemap.scrollX.i.hi;
                if (i < 0x70) {
                    i = 0x70;
                }
            }
            self->ext.minotaur.deathPuffPosX = i;
            i = self->posX.i.hi + g_Tilemap.scrollX.i.hi;
            i = self->ext.minotaur.deathPuffPosX - i;
            if (i > 0) {
                self->velocityX = FIX(1.0);
            } else {
                self->velocityX = FIX(-1.0);
            }
            self->step_s++;
        }
        self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        AnimateEntity(D_us_801806E0, self);
        UnkCollisionFunc2(D_us_801806C8);
        arrived = false;
        i = self->posX.i.hi + g_Tilemap.scrollX.i.hi -
            self->ext.minotaur.deathPuffPosX;
        if (self->velocityX > 0) {
            if (i > 0) {
                arrived = true;
            }
        } else if (i < 0) {
            arrived = true;
        }
        if (arrived) {
            self->ext.minotaur.deathPuffPosX = 0;
            SetStep(2);
        }
        break;
    case 0xB:
        switch (self->step_s) {
        case 0:
            if (!AnimateEntity(D_us_80180724, self)) {
                self->step_s++;
            }
            break;
        case 1:
            (self - 3)->ext.werewolf.signal = true;
            self->ext.minotaur.timer = 0x40;
            PlaySfxPositional(SFX_MINOTAUR_BREATH_ATTACK);
            self->step_s++;
            // fallthrough
        case 2:
            if (!(g_Timer & 3)) {
                entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
                if (entity != NULL) {
                    CreateEntityFromEntity(
                        E_MINOTAUR_SPIT_LIQUID, self, entity);
                    if (self->facingLeft) {
                        entity->posX.i.hi += 0x26;
                    } else {
                        entity->posX.i.hi -= 0x26;
                    }
                    entity->posY.i.hi -= 4;
                    entity->facingLeft = self->facingLeft;
                    entity->rotate = ROT(-112.5);
                    entity->zPriority = self->zPriority + 1;
                }
            }
            if (!--self->ext.minotaur.timer) {
                SetStep(7);
            }
            break;
        }
        break;
    case 0xC:
        switch (self->step_s) {
        case 0:
            if (!AnimateEntity(D_us_80180734, self)) {
                (self - 3)->ext.werewolf.signal = true;
                SetSubStep(1);
            }
            break;
        case 1:
            if (self->facingLeft) {
                self->velocityX = FIX(4.5);
            } else {
                self->velocityX = FIX(-4.5);
            }
            self->velocityY = 0;
            self->animCurFrame = 0x19;
            PlaySfxPositional(SFX_SCRAPE_A);
            self->step_s++;
            // fallthrough
        case 2:
            if (UnkCollisionFunc2(D_us_801806C8) & 0xF0) {
                self->ext.minotaur.timer = 1;
                self->step_s++;
            }
            break;
        case 3:
            AnimateEntity(D_us_8018073C, self);
            if (!--self->ext.minotaur.timer) {
                SetSubStep(4);
            }
            break;
        case 4:
            SetStep(7);
            break;
        }
        break;
    case 0xE:
        if (!AnimateEntity(D_us_80180750, self)) {
            SetStep(7);
        }
        if (!self->poseTimer && self->pose == 8) {
            for (i = 0; i < 8; i++) {
                entity = AllocEntity(
                    &g_Entities[224], &g_Entities[TOTAL_ENTITY_COUNT]);
                if (entity != NULL) {
                    CreateEntityFromEntity(E_MINOTAUR_FIREBALL, self, entity);
                    entity->posY.i.hi += 0x28;
                    entity->facingLeft = self->facingLeft;
                    entity->params = i;
                }
            }
        }
        break;
    case 0x22:
        switch (self->step_s) {
        case 0:
            entity = self - 3;
            self->ext.minotaur.signal = false;
            if (self->posX.i.hi > entity->posX.i.hi) {
                self->facingLeft = 0;
            } else {
                self->facingLeft = 1;
            }
            if (entity->flags & FLAG_DEAD) {
                SetStep(0x12);
                return;
            }
            self->step_s++;
            // fallthrough
        case 1:
            if (!AnimateEntity(D_us_80180770, self)) {
                SetSubStep(2);
            }
            break;
        case 2:
            if (self->ext.minotaur.signal) {
                PlaySfxPositional(SFX_MINOTAUR_ATTACK);
                self->step_s++;
            }
            if ((self - 3)->flags & FLAG_DEAD) {
                SetSubStep(3);
                return;
            }
            break;
        case 3:
            if (!AnimateEntity(D_us_8018077C, self)) {
                SetStep(7);
            }
            break;
        }
        break;
    case 0x10:
        if (!AnimateEntity(D_us_80180790, self)) {
            SetStep(2);
        }
        break;
    case 0x12:
        if (!self->step_s) {
            self->velocityX = 0;
            self->velocityY = 0;
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            self->step_s++;
        }
        UnkCollisionFunc2(D_us_801806C8);
        if (!AnimateEntity(D_us_80180798, self)) {
            SetStep(2);
        }
        if ((self - 3)->flags & FLAG_DEAD) {
            self->velocityX -= self->velocityX / 8;
            if (!self->poseTimer && self->pose == 7) {
                PlaySfxPositional(SFX_MINOTAUR_ATTACK);
                if (self->facingLeft) {
                    self->velocityX = FIX(4.0);
                } else {
                    self->velocityX = FIX(-4.0);
                }
            }
        }
        break;
    case 8:
        switch (self->step_s) {
        case 0:
            self->velocityY = FIX(-6.5);
            if (self->facingLeft) {
                self->velocityX = FIX(3.0);
            } else {
                self->velocityX = FIX(-3.0);
            }
            self->ext.minotaur.signal = false;
            self->step_s++;
            // fallthrough
        case 1:
            AnimateEntity(D_us_80180704, self);
            UnkCollisionFunc3(D_us_801806D0);
            if (self->velocityY > 0) {
                PlaySfxPositional(SFX_BOSS_WING_FLAP);
                SetSubStep(2);
            }
            break;
        case 2:
            AnimateEntity(D_us_80180714, self);
            if (UnkCollisionFunc3(D_us_801806D0) & 1) {
                if (!((self - 3)->flags & FLAG_DEAD) &&
                    (self - 3)->ext.werewolf.signal) {
                    if (self->posX.i.hi > (self - 3)->posX.i.hi) {
                        self->facingLeft = 0;
                    } else {
                        self->facingLeft = 1;
                    }
                    SetSubStep(3);
                } else {
                    SetStep(7);
                }
            }
            break;
        case 3:
            if (!AnimateEntity(D_us_80180850, self)) {
                SetSubStep(4);
            }
            break;
        case 4:
            if (self->ext.minotaur.signal) {
                if (!AnimateEntity(D_us_80180858, self)) {
                    SetStep(7);
                }
            }
            break;
        }
        break;
    case 0x14:
        if (!AnimateEntity(D_us_801807AC, self)) {
            SetStep(0x18);
        }
        break;
    case 0x18:
        if (!AnimateEntity(D_us_801807B4, self)) {
            SetStep(0x16);
        }
        break;
    case 0x16:
        switch (self->step_s) {
        case 0:
            if (!AnimateEntity(D_us_801807D0, self)) {
                SetSubStep(1);
            }
            if (!self->poseTimer && self->pose == 5) {
                PlaySfxPositional(SFX_UNK_BO2_789);
            }
            if (!self->poseTimer && self->pose == 3) {
                (self + 1)->ext.minotaur.axeThrown = true;
                self->ext.minotaur.axeThrown = false;
                self->ext.minotaur.attack = self->attack;
                self->attack *= 2;
            }
            break;
        case 1:
            if (self->facingLeft) {
                self->velocityX = FIX(2.5);
            } else {
                self->velocityX = FIX(-2.5);
            }
            self->velocityY = 0;
            self->step_s++;
            // fallthrough
        case 2:
            AnimateEntity(D_us_801807F4, self);
            if (UnkCollisionFunc2(D_us_801806C8) & 0xF0) {
                (self - 3)->ext.werewolf.signal = true;
                SetSubStep(3);
                break;
            }
            if (GetDistanceToPlayerX() < 8) {
                (self - 3)->ext.werewolf.signal = true;
                PlaySfxPositional(SFX_MINOTAURUS_JUMP_ATTACK);
                SetSubStep(3);
            }
            break;
        case 3:
            if (!AnimateEntity(D_us_801807FC, self)) {
                self->velocityX = 0;
                self->velocityY = FIX(-7.0);
                SetSubStep(4);
            }
            break;
        case 4:
            if (self->velocityY < 0) {
                AnimateEntity(D_us_80180808, self);
            } else {
                AnimateEntity(D_us_80180810, self);
            }
            if (UnkCollisionFunc3(D_us_801806D0) & 1) {
                PlaySfxPositional(SFX_STOMP_HARD_A);
                (self + 1)->ext.minotaur.axeThrown = false;
                self->attack = self->ext.minotaur.attack;
                SetSubStep(5);
            }
            break;
        case 5:
            AnimateEntity(D_us_80180818, self);
            if (self->ext.minotaur.axeThrown) {
                SetStep(7);
            }
            break;
        }
        break;
    case 0x21:
        switch (self->step_s) {
        case 0:
            self->animCurFrame = 0x2B;
            self->step_s++;
            break;
        case 1:
            self->facingLeft ^= 1;
            self->step_s++;
            break;
        case 2:
            self->animCurFrame = 1;
            SetStep(7);
            break;
        }
        break;
    case 0x40:
        self->ext.minotaur.isReady = true;
        (self - 3)->ext.werewolf.signal = true;
        switch (self->step_s) {
        case 0:
            self->hitboxState = 0;
            self->velocityX = 0;
            self->velocityY = 0;
            self->step_s++;
            // fallthrough
        case 1:
            if (UnkCollisionFunc3(D_us_801806D0) & 1) {
                self->ext.minotaur.deathPuffPosX = -0x10;
                self->ext.minotaur.timer = 0;
                PlaySfxPositional(SFX_EXPLODE_A);
                self->step_s++;
            }
            break;
        case 2:
            if (!AnimateEntity(D_us_80180824, self)) {
                self->step_s = 3;
            }
            self->ext.minotaur.timer &= 1;
            // fallthrough
        case 3:
            if (self->ext.minotaur.timer & 1) {
                entity = AllocEntity(
                    &g_Entities[224], &g_Entities[TOTAL_ENTITY_COUNT]);
                if (entity != NULL) {
                    CreateEntityFromEntity(E_MINOTAUR_DEATH_PUFF, self, entity);
                    entity->posX.i.hi += self->ext.minotaur.deathPuffPosX;
                    entity->posY.i.hi += 0x20;
                    entity->zPriority = self->zPriority + 1;
                    entity->params = abs(self->ext.minotaur.deathPuffPosX) +
                                     (self->ext.minotaur.timer >> 1);
                }
                self->ext.minotaur.deathPuffPosX += 8;
                if (self->ext.minotaur.deathPuffPosX > 0x10) {
                    self->ext.minotaur.deathPuffPosX = -0x10;
                }
            }
            if (!(g_Timer & 0x1F)) {
                PlaySfxPositional(SFX_FIREBALL_SHOT_B);
            }
            if (self->ext.minotaur.timer++ > 0x40) {
                self->step_s++;
            }
            break;
        case 4:
            self->animCurFrame = 0;
            self->ext.minotaur.deathPuffPosX = 0;
            break;
        }
        break;
    case 0xFF:
#include "../../st/pad2_anim_debug.h"
    }

    ptr = *D_us_80180880;
    ptr += D_us_80180908[self->animCurFrame] * 4;
    self->hitboxOffX = *ptr++;
    self->hitboxOffY = *ptr++;
    self->hitboxWidth = *ptr++;
    self->hitboxHeight = *ptr++;
    func_us_801A2610();
}

#include "e_minotaur.h"
