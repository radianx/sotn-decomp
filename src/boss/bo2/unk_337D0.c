// SPDX-License-Identifier: AGPL-3.0-or-later
#include "bo2.h"

extern EInit g_EInitWerewolfARE;
extern s32 D_us_80180AAC;
extern s32 D_us_80180AB0;
extern s8 D_us_80181958[][4];
extern u8 D_us_801819F8[];
extern s16 D_us_80181850[];
extern s16 D_us_80181858[];
extern u8 D_us_80181868[];
extern u8 D_us_80181874[];
extern u8 D_us_80181884[];
extern u8 D_us_801818A4[];
extern u8 D_us_801818AC[];
extern u8 D_us_801818BC[];
extern u8 D_us_801818D0[];
extern u8 D_us_801818D8[];
extern u8 D_us_801818E0[];
extern u8 D_us_801818EC[];
extern u8 D_us_801818FC[];
extern u8 D_us_80181908[];
extern u8 D_us_80181930[];

extern EInit D_us_80180578;
extern EInit D_us_80180584;
extern EInit g_EInitInteractable;
extern SVECTOR D_us_80181ACC[];
extern s16* D_us_801A16F0[];

void func_us_801B37D0(void) {
    s32 posX;

    posX = g_CurrentEntity->posX.i.hi + g_Tilemap.scrollX.i.hi;
    if (g_CurrentEntity->velocityX > 0) {
        posX += 8;
        if (posX > 0x1B0) {
            g_CurrentEntity->posX.i.hi = 0x1A8 - g_Tilemap.scrollX.i.hi;
        }
    }
    if (g_CurrentEntity->velocityX < 0) {
        posX -= 8;
        if (posX < 0x50) {
            g_CurrentEntity->posX.i.hi = 0x58 - g_Tilemap.scrollX.i.hi;
        }
    }
}

void func_us_801B385C(Entity* self) {
    s32 unused[2]; // !FAKE: preserves the original stack frame.
    Entity* entity;
    s32 i;
    s8* hitbox;
    s32 arrived;
    s32 posY;
    s16 angle;
    u16 rotation;

    FntPrint("wolf_step %x\n", self->step);
    FntPrint("wolf_set_step %x\n", self->ext.werewolfBoss.nextStep);
    if ((self->flags & FLAG_DEAD) && (self->step < 0x20)) {
        SetStep(0x20);
    }
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitWerewolfARE);
        self->hitboxState = 0;
        self->zPriority += 8;
        entity = self + 1;
        CreateEntityFromCurrentEntity(E_WEREWOLF_ATTACK_HITBOX, entity);
        // fallthrough
    case 1:
        AnimateEntity(D_us_80181868, self);
        self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        UnkCollisionFunc3(D_us_80181858);
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
                self->palette = g_EInitWerewolfARE[3];
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
            if (!self->ext.werewolfBoss.moveTimer) {
                self->ext.werewolfBoss.moveTimer = 0x20;
            }
            self->ext.werewolfBoss.isReady = false;
            self->step_s++;
        }
        AnimateEntity(D_us_80181868, self);
        self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        if (self->ext.werewolfBoss.moveTimer) {
            self->ext.werewolfBoss.moveTimer--;
        } else {
            self->ext.werewolfBoss.isReady = true;
        }
        if (self->ext.werewolfBoss.targetX) {
            self->ext.werewolfBoss.isReady = false;
            SetStep(4);
        } else if (self->ext.werewolfBoss.hasNextStep) {
            self->ext.werewolfBoss.isReady = false;
            self->ext.werewolfBoss.hasNextStep = false;
            SetStep(self->ext.werewolfBoss.nextStep);
        } else {
            i = PLAYER.velocityX;
            if (self->facingLeft) {
                i = -i;
            }
            if ((self->facingLeft == PLAYER.facingLeft) &&
                (GetDistanceToPlayerX() < 0x38) && (i > 0)) {
                self->ext.werewolfBoss.isReady = false;
                SetStep(6);
            }
        }
        break;
    case 4:
        if (!self->step_s) {
            i = self->ext.werewolfBoss.targetX;
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
            self->ext.werewolfBoss.targetX = i;
            i = self->posX.i.hi + g_Tilemap.scrollX.i.hi;
            i = self->ext.werewolfBoss.targetX - i;
            if (i > 0) {
                self->velocityX = FIX(1.125);
            } else {
                self->velocityX = FIX(-1.125);
            }
            self->step_s++;
        }
        self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        AnimateEntity(D_us_80181874, self);
        UnkCollisionFunc2(D_us_80181850);
        arrived = false;
        i = self->posX.i.hi + g_Tilemap.scrollX.i.hi -
            self->ext.werewolfBoss.targetX;
        if (self->velocityX > 0) {
            if (i > 0) {
                arrived = true;
            }
        } else if (i < 0) {
            arrived = true;
        }
        if (arrived) {
            self->ext.werewolfBoss.targetX = 0;
            SetStep(2);
        }
        break;
    case 6:
        if (!AnimateEntity(D_us_80181884, self)) {
            SetStep(2);
        }
        if (*(s32*)&self->pose == 6) {
            PlaySfxPositional(SFX_WHIP_TWIRL_SWISH);
        }
        break;
    case 8:
        switch (self->step_s) {
        case 0:
            entity = self + 3;
            i = (self + 3)->posX.i.hi - self->posX.i.hi;
            if ((self->facingLeft == (self + 3)->facingLeft) &&
                (abs(i) < 0x20)) {
                self->ext.werewolfBoss.signal = true;
            } else {
                self->ext.werewolfBoss.signal = false;
            }
            entity->ext.minotaur.signal = self->ext.werewolfBoss.signal ^ 1;
            self->step_s++;
            // fallthrough
        case 1:
            if (!AnimateEntity(D_us_801818A4, self)) {
                self->animCurFrame = 0x2F;
                self->velocityX = FIX(-2);
                if (self->facingLeft) {
                    self->velocityX = FIX(2);
                }
                self->velocityY = FIX(-2);
                SetSubStep(3);
            }
            break;
        case 3:
            if (UnkCollisionFunc3(D_us_80181858) & 1) {
                self->step_s++;
            }
            break;
        case 4:
            if (!AnimateEntity(D_us_801818AC, self)) {
                SetStep(4);
            }
            if (*(s32*)&self->pose == 4) {
                PlaySfxPositional(SFX_EXPLODE_F);
                entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
                if (entity != NULL) {
                    CreateEntityFromEntity(E_UNK_1D, self, entity);
                    entity->facingLeft = self->facingLeft;
                    entity->ext.werewolfBoss.parent = self + 3;
                    entity->posY.i.hi -= 0x10;
                    entity->ext.werewolfBoss.signal =
                        self->ext.werewolfBoss.signal;
                }
            }
            break;
        }
        break;
    case 0xA:
        if (!self->step_s) {
            self->velocityX = 0;
            self->velocityY = 0;
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            self->step_s++;
        }
        UnkCollisionFunc2(D_us_80181850);
        if (!AnimateEntity(D_us_801818BC, self)) {
            SetStep(2);
        }
        self->velocityX -= self->velocityX / 16;
        if (*(s32*)&self->pose == 3) {
            PlaySfxPositional(SFX_SCRAPE_B);
            if (self->facingLeft) {
                self->velocityX = FIX(4);
            } else {
                self->velocityX = FIX(-4);
            }
        }
        break;
    case 0xC:
        if (!self->step_s) {
            if (!AnimateEntity(D_us_801818D0, self)) {
                self->ext.werewolfBoss.timer = 0x80;
                self->step_s++;
            }
        } else {
            AnimateEntity(D_us_801818D8, self);
            if (!--self->ext.werewolfBoss.timer) {
                SetStep(0xE);
            }
        }
        break;
    case 0xE:
        if (self->flags & 0xF) {
            self->blendMode = BLEND_NO;
        } else if (g_Timer & 1) {
            self->blendMode = BLEND_ADD | BLEND_TRANSP;
        } else {
            self->blendMode = BLEND_QUARTER | BLEND_TRANSP;
        }
        switch (self->step_s) {
        case 0:
            self->velocityX = 0;
            self->velocityY = 0;
            self->ext.werewolfBoss.signal = false;
            self->step_s++;
            // fallthrough
        case 1:
            if (self->ext.werewolfBoss.signal) {
                self->step_s++;
            }
            break;
        case 2:
            if (!AnimateEntity(D_us_801818E0, self)) {
                SetSubStep(3);
            }
            if (*(s32*)&self->pose == 1) {
                if (self->facingLeft) {
                    self->velocityX = FIX(6);
                } else {
                    self->velocityX = FIX(-6);
                }
                self->ext.werewolfBoss.timer = 0x30;
            }
            break;
        case 3:
            UnkCollisionFunc2(D_us_80181850);
            self->velocityX -= self->velocityX / 64;
            self->animCurFrame = 0x2B;
            if (!--self->ext.werewolfBoss.timer) {
                SetSubStep(4);
            }
            break;
        case 4:
            UnkCollisionFunc2(D_us_80181850);
            self->velocityX -= self->velocityX / 16;
            if (!AnimateEntity(D_us_801818EC, self)) {
                self->blendMode = BLEND_NO;
                SetStep(4);
            }
            break;
        }
        break;
    case 0x12:
        switch (self->step_s) {
        case 0:
            if (self->facingLeft) {
                self->velocityX = FIX(3.5);
            } else {
                self->velocityX = FIX(-3.5);
            }
            self->ext.werewolfBoss.timer = 0x20;
            self->animCurFrame = 0x17;
            self->velocityY = 0;
            self->drawFlags |= ENTITY_ROTATE;
            self->step_s++;
            // fallthrough
        case 1:
            UnkCollisionFunc2(D_us_80181850);
            self->rotate -= ROT(22.5);
            if (!(g_Timer & 8)) {
                PlaySfxPositional(SFX_WEREWOLF_SPIN_ATTACK);
            }
            if (!(self->ext.werewolfBoss.timer & 3)) {
                entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (entity != NULL) {
                    CreateEntityFromEntity(
                        E_WEREWOLF_SPIN_ATTACK_AFTER_IMAGE, self, entity);
                    entity->facingLeft = self->facingLeft;
                    entity->rotate = self->rotate;
                    entity->params = self->animCurFrame;
                }
            }
            if (!--self->ext.werewolfBoss.timer) {
                self->step_s = 2;
            }
            break;
        case 2:
            self->drawFlags = ENTITY_DEFAULT;
            SetStep(4);
            break;
        }
        break;
    case 0x16:
        switch (self->step_s) {
        case 0:
            entity = self + 3;
            self->ext.werewolfBoss.signal = false;
            if (self->posX.i.hi > (self + 3)->posX.i.hi) {
                self->facingLeft = 0;
            } else {
                self->facingLeft = 1;
            }
            if (self->facingLeft) {
                self->velocityX = FIX(3.5);
            } else {
                self->velocityX = FIX(-3.5);
            }
            self->velocityY = 0;
            if (entity->flags & FLAG_DEAD) {
                SetStep(0xA);
                return;
            }
            self->step_s++;
            // fallthrough
        case 1:
            if (!AnimateEntity(D_us_80181930, self)) {
                self->animCurFrame = 0x17;
                self->drawFlags |= ENTITY_ROTATE;
                self->step_s++;
            }
            break;
        case 2:
            UnkCollisionFunc2(D_us_80181850);
            self->rotate -= ROT(22.5);
            if (!(g_Timer & 7)) {
                PlaySfxPositional(SFX_WEREWOLF_SPIN_ATTACK);
            }
            if (!(self->ext.werewolfBoss.timer & 3)) {
                entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (entity != NULL) {
                    CreateEntityFromEntity(
                        E_WEREWOLF_SPIN_ATTACK_AFTER_IMAGE, self, entity);
                    entity->facingLeft = self->facingLeft;
                    entity->rotate = self->rotate;
                    entity->params = self->animCurFrame;
                }
            }
            i = self->posX.i.hi - (self + 3)->posX.i.hi;
            if (self->facingLeft) {
                i = -i;
            }
            if (i < 0x20) {
                (self + 3)->ext.minotaur.signal = true;
                self->rotate = 0;
                self->step_s++;
            }
            if ((self + 3)->flags & FLAG_DEAD) {
                SetSubStep(7);
            }
            break;
        case 3:
            self->velocityY = FIX(-8.5);
            i = PLAYER.posX.val - self->posX.val;
            i /= 64;
            self->velocityX = i;
            self->animCurFrame = 8;
            if (self->velocityX > 0) {
                self->facingLeft = 1;
            } else {
                self->facingLeft = 0;
            }
            self->step_s++;
            break;
        case 4:
            MoveEntity();
            self->velocityY += FIX(0.25);
            posY = self->posY.i.hi + g_Tilemap.scrollY.i.hi;
            if (posY < 0x2C) {
                posY = 0x2C - g_Tilemap.scrollY.i.hi;
                self->posY.i.hi = posY;
                self->ext.werewolfBoss.timer = 8;
                self->step_s++;
            }
            break;
        case 5:
            self->animCurFrame = 0x17;
            self->rotate -= ROT(33.75);
            if (!--self->ext.werewolfBoss.timer) {
                self->ext.werewolfBoss.timer = 0xC;
                self->step_s++;
            }
            break;
        case 6:
            self->animCurFrame = 0x1B;
            self->rotate = 0;
            if (!--self->ext.werewolfBoss.timer) {
                angle = GetAngleBetweenEntities(self, &PLAYER);
                self->velocityX = rcos(angle) * 0x50;
                self->velocityY = rsin(angle) * 0x50;
                self->ext.werewolfBoss.attack = self->attack;
                self->attack *= 2;
                self->step_s++;
            }
            break;
        case 7:
            self->animCurFrame = 0x17;
            self->rotate -= ROT(33.75);
            if (!(g_Timer & 7)) {
                PlaySfxPositional(SFX_WEREWOLF_SPIN_ATTACK);
            }
            if (UnkCollisionFunc3(D_us_80181858) & 1) {
                PlaySfxPositional(SFX_STOMP_HARD_B);
                self->ext.werewolfBoss.timer = 0x10;
                self->attack = self->ext.werewolfBoss.attack;
                self->step_s++;
            }
            if (!(self->ext.werewolfBoss.timer & 3)) {
                entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (entity != NULL) {
                    CreateEntityFromEntity(
                        E_WEREWOLF_SPIN_ATTACK_AFTER_IMAGE, self, entity);
                    entity->facingLeft = self->facingLeft;
                    entity->rotate = self->rotate;
                    entity->params = self->animCurFrame;
                }
            }
            break;
        case 8:
            self->drawFlags = ENTITY_DEFAULT;
            self->animCurFrame = 0xC;
            if (!--self->ext.werewolfBoss.timer) {
                SetStep(4);
            }
            break;
        }
        break;
    case 0x18:
        switch (self->step_s) {
        case 0:
            self->ext.werewolfBoss.signal = false;
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            self->step_s++;
            // fallthrough
        case 1:
            if (self->ext.werewolfBoss.signal) {
                self->step_s++;
            }
            break;
        case 2:
            if (!AnimateEntity(D_us_80181930, self)) {
                self->animCurFrame = 0x17;
                self->drawFlags |= ENTITY_ROTATE;
                if (self->facingLeft) {
                    self->velocityX = FIX(3.5);
                } else {
                    self->velocityX = FIX(-3.5);
                }
                self->ext.werewolfBoss.timer = 0x40;
                self->step_s++;
            }
            break;
        case 3:
            UnkCollisionFunc2(D_us_80181850);
            self->rotate -= ROT(22.5);
            if (!(g_Timer & 7)) {
                PlaySfxPositional(SFX_WEREWOLF_SPIN_ATTACK);
            }
            if (!(self->ext.werewolfBoss.timer & 3)) {
                entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (entity != NULL) {
                    CreateEntityFromEntity(
                        E_WEREWOLF_SPIN_ATTACK_AFTER_IMAGE, self, entity);
                    entity->facingLeft = self->facingLeft;
                    entity->rotate = self->rotate;
                    entity->params = self->animCurFrame;
                }
            }
            if (!((self + 3)->flags & FLAG_DEAD)) {
                entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
                if (entity != NULL) {
                    CreateEntityFromEntity(
                        E_MINOTAUR_SPIT_LIQUID, self, entity);
                    rotation = self->rotate;
                    entity->rotate = rotation;
                    angle = rotation;
                    if (self->facingLeft) {
                        angle = -rotation;
                    }
                    entity->posX.val += rsin(angle) * 0xC0;
                    entity->posY.val -= rcos(angle) * 0xC0;
                    entity->facingLeft = self->facingLeft;
                    entity->zPriority = self->zPriority + 1;
                }
            }
            if (!--self->ext.werewolfBoss.timer) {
                self->step_s++;
            }
            break;
        case 4:
            self->drawFlags = ENTITY_DEFAULT;
            SetStep(4);
            break;
        }
        break;
    case 0x14:
        if (self->flags & 0xF) {
            self->blendMode = BLEND_NO;
        } else if (g_Timer & 1) {
            self->blendMode = BLEND_ADD | BLEND_TRANSP;
        } else {
            self->blendMode = BLEND_QUARTER | BLEND_TRANSP;
        }
        switch (self->step_s) {
        case 0:
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            self->ext.werewolfBoss.signal = false;
            self->step_s++;
            // fallthrough
        case 1:
            if (!AnimateEntity(D_us_80181930, self)) {
                self->step_s++;
            }
            break;
        case 2:
            self->velocityY = FIX(-4);
            self->velocityX = 0;
            self->drawFlags = ENTITY_ROTATE;
            self->step_s++;
            // fallthrough
        case 3:
            MoveEntity();
            self->rotate -= ROT(22.5);
            if (!(g_Timer & 7)) {
                PlaySfxPositional(SFX_WEREWOLF_SPIN_ATTACK);
            }
            if (g_Timer & 1) {
                self->animCurFrame = 0x18;
            } else {
                self->animCurFrame = 0x19;
            }
            if (!(self->ext.werewolfBoss.timer & 3)) {
                entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (entity != NULL) {
                    CreateEntityFromEntity(
                        E_WEREWOLF_SPIN_ATTACK_AFTER_IMAGE, self, entity);
                    entity->facingLeft = self->facingLeft;
                    entity->rotate = self->rotate;
                    entity->params = self->animCurFrame;
                }
            }
            if (self->posY.i.hi + g_Tilemap.scrollY.i.hi < 0x28) {
                self->step_s++;
            }
            break;
        case 4:
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            if (self->facingLeft) {
                self->velocityX = FIX(2.5);
            } else {
                self->velocityX = FIX(-2.5);
            }
            self->velocityY = 0;
            self->step_s++;
            // fallthrough
        case 5:
            MoveEntity();
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            if (self->facingLeft) {
                self->velocityX = FIX(2.5);
            } else {
                self->velocityX = FIX(-2.5);
            }
            self->rotate -= ROT(22.5);
            if (!(g_Timer & 7)) {
                PlaySfxPositional(SFX_WEREWOLF_SPIN_ATTACK);
            }
            if (g_Timer & 1) {
                self->animCurFrame = 0x18;
            } else {
                self->animCurFrame = 0x19;
            }
            if (self->ext.werewolfBoss.signal) {
                self->animCurFrame = 0xA;
                self->drawFlags = ENTITY_DEFAULT;
                self->velocityX = 0;
                self->velocityY = FIX(2);
                self->step_s++;
            }
            break;
        case 6:
            if (UnkCollisionFunc3(D_us_80181858) & 1) {
                self->animCurFrame = 0xB;
                entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
                if (entity != NULL) {
                    CreateEntityFromEntity(E_UNK_1F, self, entity);
                    entity->posY.i.hi += 0x1B;
                    entity->zPriority = self->zPriority - 1;
                }
                PlaySfxPositional(SFX_FIREBALL_SHOT_A);
                self->ext.werewolfBoss.timer = 0x40;
                self->step_s++;
            }
            break;
        case 7:
            if (!--self->ext.werewolfBoss.timer) {
                self->blendMode = BLEND_NO;
                SetStep(4);
            }
            break;
        }
        break;
    case 0x20:
        self->ext.werewolfBoss.isReady = true;
        (self + 3)->ext.minotaur.signal = true;
        switch (self->step_s) {
        case 0:
            self->hitboxState = 0;
            self->rotate = 0;
            self->velocityX = 0;
            self->velocityY = 0;
            self->step_s++;
            // fallthrough
        case 1:
            if (UnkCollisionFunc3(D_us_80181858) & 1) {
                self->step_s++;
            }
            // fallthrough
        case 2:
            if (!AnimateEntity(D_us_801818FC, self)) {
                PlaySfxPositional(SFX_EXPLODE_A);
                entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (entity != NULL) {
                    CreateEntityFromEntity(
                        E_WEREWOLF_DEATH_FLAMES, self, entity);
                    entity->posY.i.hi += 0x1B;
                    entity->zPriority = self->zPriority;
                }
                SetSubStep(3);
            }
            break;
        case 3:
            if (!AnimateEntity(D_us_80181908, self)) {
                SetSubStep(4);
            }
            break;
        case 4:
            self->ext.werewolfBoss.targetX = 0;
            self->animCurFrame = 0;
            break;
        }
        break;
    case 0xFF:
#include "../../st/pad2_anim_debug.h"
    }
    hitbox = D_us_80181958[0];
    hitbox += D_us_801819F8[self->animCurFrame] * 4;
    self->hitboxOffX = *hitbox++;
    self->hitboxOffY = *hitbox++;
    self->hitboxWidth = *hitbox++;
    self->hitboxHeight = *hitbox++;
    func_us_801B37D0();
}

#include "e_werewolf_attack_hitbox.h"

void func_us_801B503C(Entity* self) {
    Entity* parent;
    s32 velocityX;
    s16 angle;

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_80180578);
        self->animCurFrame = 0x39;
        if (self->facingLeft) {
            self->velocityX = FIX(4.5);
        } else {
            self->velocityX = FIX(-4.5);
        }
        self->velocityY = 0;
        parent = self->ext.werewolfBoss.parent;
        velocityX = parent->velocityX;
        if (self->facingLeft) {
            velocityX = -velocityX;
        }
        if ((velocityX > 0) || (parent->flags & FLAG_DEAD)) {
            self->ext.werewolfBoss.signal = false;
            parent->ext.minotaur.signal = true;
        }
        // fallthrough
    case 1:
        MoveEntity();
        self->velocityY -= FIX(5.0 / 64);
        angle = ratan2(-self->velocityY, abs(self->velocityX));
        if (angle > 0x200) {
            self->animCurFrame = 0x3A;
        }
        if (angle > 0x280) {
            self->animCurFrame = 0x3B;
        }
        if (angle > 0x300) {
            self->animCurFrame = 0x3C;
        }
        if (angle > 0x380) {
            self->animCurFrame = 0x3D;
        }
        if (self->ext.werewolfBoss.signal) {
            PlaySfxPositional(SFX_ANIME_SWORD_B);
            parent = self->ext.werewolfBoss.parent;
            velocityX = self->posX.i.hi - parent->posX.i.hi;
            if (abs(velocityX) < 0x10) {
                parent->ext.minotaur.signal = true;
                self->velocityY = FIX(2);
                self->animCurFrame = 0x39;
                self->facingLeft ^= 1;
                self->velocityX = -self->velocityX * 2;
                self->step++;
            }
        }
        break;
    case 2:
        MoveEntity();
        break;
    }
}

#include "e_werewolf_after_image.h"

void func_us_801B52FC(Entity* self) {
    Primitive* prim;
    Entity* entity;
    s16 primIndex;
    s32 i;
    s32 size;

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_80180584);
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 3);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.prim = prim;
        self->flags |= FLAG_HAS_PRIMS;
        while (prim != NULL) {
            prim->tpage = 0x16;
            prim->clut = 0x211;
            prim->u0 = prim->u2 = 0x80;
            prim->u1 = prim->u3 = 0xA0;
            prim->v0 = prim->v1 = 0;
            prim->v2 = prim->v3 = 0;
            if (!self->params) {
                prim->x0 = prim->x2 = self->posX.i.hi - 0x18;
                prim->x1 = prim->x3 = self->posX.i.hi + 0x18;
            } else {
                prim->x0 = prim->x2 = self->posX.i.hi - 0xC;
                prim->x1 = prim->x3 = self->posX.i.hi + 0xC;
            }
            prim->y0 = prim->y1 = prim->y2 = prim->y3 = self->posY.i.hi;
            prim->priority = self->zPriority;
            prim->drawMode = DRAW_UNK02;
            prim = prim->next;
        }
        if (!self->params) {
            for (i = -1; i < 2; i += 2) {
                entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
                if (entity != NULL) {
                    CreateEntityFromEntity(E_UNK_1F, self, entity);
                    entity->params = 1;
                    entity->posX.i.hi += i * 0x24;
                }
            }
        }
        // fallthrough
    case 1:
        prim = self->ext.prim;
        i = 4;
        if (self->params) {
            i = 2;
        }
        prim->y0 = prim->y1 = prim->y1 - i * 2;
        prim->v2 = prim->v3 = prim->v3 + i;
        size = prim->v2 - prim->v0;
        if (size >= 0x40) {
            self->step++;
        }
        break;
    case 2:
        prim = self->ext.prim;
        i = 4;
        if (self->params) {
            i = 2;
        }
        prim->y0 = prim->y1 = prim->y1 + i;
        prim->v2 = prim->v3 = prim->v3 - i / 2;
        size = prim->y2 - prim->y0;
        if (size <= 0) {
            self->step++;
        }
        break;
    case 3:
        DestroyEntity(self);
        break;
    }
#ifdef VERSION_PC
    if (!self->entityId) {
        return;
    }
#endif
    // @bug The original still updates the primitive after destroying the
    // entity.
    prim = self->ext.prim;
    self->hitboxWidth = (abs(prim->x0 - prim->x1) - 8) / 2;
    self->hitboxHeight = abs(prim->y0 - prim->y2) * 3 / 10;
    self->hitboxOffY = -self->hitboxHeight + 14;
    if (g_Timer & 1) {
        prim->u0 = prim->u2 = 0x80;
        prim->u1 = prim->u3 = 0xA0;
    } else {
        prim->u0 = prim->u2 = 0xA0;
        prim->u1 = prim->u3 = 0x80;
    }
}

void EntityWerewolfDeathFlames(Entity* self) {
    long otz;
    SVECTOR svecTwo;
    VECTOR vec;
    MATRIX matrix;

    Primitive* prim;
    s16* ptr;
    s32 posY;
    s32 i;
    SVECTOR* sVec;
    s32 color;
    s16 primIndex;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 0x80);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.werewolf.prim = prim;
        self->flags |= FLAG_HAS_PRIMS;
        while (prim != NULL) {
            prim->tpage = 0x17;
            prim->clut = 0x223;
            prim->priority = self->zPriority;
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }
        self->ext.werewolf.timer = 0x140;
    case 1:
        if (!--self->ext.werewolf.timer) {
            DestroyEntity(self);
            return;
        }
        if (!(self->ext.werewolf.timer & 0x1F)) {
            PlaySfxPositional(SFX_FIREBALL_SHOT_B);
        }

        if (!(self->ext.werewolf.timer & 3)) {
            self->ext.werewolf.unk9C -= 0x20;
            color = self->ext.werewolf.timer;
            if (color > 0x80) {
                color = 0x80;
            }

            for (i = 0; i < 3; i++) {
                prim = self->ext.werewolf.prim;
                prim = FindFirstUnkPrim2(prim, 2);
                if (prim != NULL) {
                    UnkPolyFunc2(prim);
                    prim->next->x2 = 0;
                    prim->next->y2 = 0;
                    prim->next->x1 =
                        self->ext.werewolf.unk9C + (i * 0x555) + Random();
                    prim->next->y1 = 0;
                    PGREY(prim, 0) = PGREY(prim, 1) = PGREY(prim, 2) =
                        PGREY(prim, 3) = color;

                    prim = prim->next;
                    prim->drawMode = DRAW_HIDE;
                }
            }
        }

        SetGeomScreen(0x200);
        SetGeomOffset(self->posX.i.hi, self->posY.i.hi);
        prim = self->ext.werewolf.prim;
        sVec = D_us_80181ACC;
        posY = self->posY.i.hi + 8;
        while (prim != NULL) {
            if (prim->p3 == 8) {
                vec.vx = 0;
                vec.vy = prim->next->y1;
                vec.vz = 0x200;
                TransMatrix(&matrix, &vec);
                SetTransMatrix(&matrix);
                svecTwo.vx = 0;
                svecTwo.vy = prim->next->x1;
                svecTwo.vz = 0x180;
                RotMatrix(&svecTwo, &matrix);
                SetRotMatrix(&matrix);
                gte_ldv3c(sVec);
                gte_rtpt();
                gte_stsxy3_gt3(prim);
                gte_ldv0(&sVec[3]);
                gte_rtps();
                gte_stsxy((long*)&prim->x3);
                gte_avsz4();
#if defined(VERSION_US) && !defined(VERSION_PC)
                // @bug The US original passes an uninitialized address.
                gte_stszotz(otz);
#else
                gte_stszotz(&otz);
#endif

                if (otz > 0x80) {
                    prim->priority = self->zPriority - 1;
                } else {
                    prim->priority = self->zPriority + 1;
                }

                if (posY < prim->y2) {
                    prim->y2 = posY;
                }

                if (posY < prim->y3) {
                    prim->y3 = posY;
                }
                prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS |
                                 DRAW_UNK02 | DRAW_TRANSP;
            }
            prim = prim->next;
        }

        prim = self->ext.werewolf.prim;
        while (prim != NULL) {
            if (prim->p3 == 8) {
                prim->next->y1 -= 3;
                prim->next->x1 += 0x30;
                prim->r0 -= 2;
                if (!prim->r0) {
                    UnkPolyFunc0(prim);
                    continue;
                }

                prim->g0 = prim->b0 = prim->r0;
                PGREY(prim, 1) = PGREY(prim, 2) = PGREY(prim, 3) = prim->r0;
                if (!prim->next->y2) {
                    prim->next->x2++;
                    if (prim->next->x2 > 0xD) {
                        UnkPolyFunc0(prim);
                        continue;
                    }

                    ptr = D_us_801A16F0[prim->next->x2];
                    ptr += 8;
                    prim->u0 = prim->u2 = *ptr++;
                    prim->v0 = prim->v1 = *ptr++;
                    prim->u1 = prim->u3 = *ptr++;
                    prim->v2 = prim->v3 = *ptr++;
                    prim->next->y2 = 3;
                } else {
                    prim->next->y2--;
                }
            }
            prim = prim->next;
        }
        break;
    }
}
