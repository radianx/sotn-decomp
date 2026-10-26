// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rbo2.h"
#include "sfx.h"

extern s32 g_BossMgrState;
extern EInit g_EInitDeath1;
extern u8 D_us_8018066C[];
extern u8 D_us_8018067C[];
extern u8 D_us_80180694[];
extern u8 D_us_801806A8[];
// The transition retains pose and reads into the following animation.
extern u8 D_us_801806B0[32];
extern u8 D_us_801806B8[];
extern u8 D_us_801806D0[];
extern EInit D_us_801804A0;
extern u8 D_us_801806E0[];
extern u8 D_us_801806F8[];

extern u8* g_eBreakableAnimations[];
extern u8 g_eBreakableHitboxes[];
extern u8 g_eBreakableExplosionTypes[];
extern u16 g_eBreakableanimSets[];
extern u8 blend_modes[];

#include "../../st/e_breakable.h"

s16 func_us_8019A98C_from_rcen(s16 delta, s16 base, s16 target) {
    s16 diff;
    s16 ret;

    base &= 0xFFF;
    diff = target - base;
    ret = diff;

    if (diff > ROT(180)) {
        ret = diff - ROT(360);
    }

    if (diff < ROT(-180)) {
        ret = diff + ROT(360);
    }

    // If we exceed the delta, then return a value which differs in the right
    // direction by precisely that delta.
    if (abs(ret) > delta) {
        if (diff < 0) {
            ret = base - delta;
        } else {
            ret = base + delta;
        }
        return ret;
    }

    // If we're not over the delta, then we can directly adopt the target angle.
    return target;
}

void func_us_8019B430(void) {
    s16 posX;
    s16 posY;
    Entity* entity;

    if (!(g_Timer & 15)) {
        entity = AllocEntity(&g_Entities[160], &g_Entities[168]);
        if (entity != NULL) {
            CreateEntityFromCurrentEntity(E_UNK_17, entity);
            posX = rand() & 0xFF;
            posY = (rand() & 0x3F) + 0x20;
            entity->posX.i.hi = posX;
            entity->posY.i.hi = posY;
        }
    }
}

#include "../../st/approach_s16.h"

void func_us_8019B52C(Entity* self) {
    Primitive* prim;
    Entity* player;
    s16 primIndex;
    s32 posX;
    s32 posY;
    s16 angle;
    s32 count;

    if ((self->flags & FLAG_DEAD) && self->step != 9) {
        SetStep(9);
    }
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitDeath1);
        self->hitboxOffY = -5;
        self->hitboxState = 2;
        primIndex = g_api.AllocPrimitives(PRIM_TILE, 3);
        if (primIndex == -1) {
            self->step = 0;
            break;
        }
        prim = &g_PrimBuf[primIndex];
        self->primIndex = primIndex;
        self->ext.deathFirstForm.prim = prim;
        self->flags |= FLAG_HAS_PRIMS;
        while (prim != NULL) {
            prim->u0 = prim->v0 = 0;
            prim->priority = self->zPriority;
            prim->drawMode = DRAW_HIDE | DRAW_UNK02;
            prim = prim->next;
        }
        SetStep(1);
        // fallthrough
    case 1:
#ifdef FIX_UB
        AnimateEntity(D_us_8018066C, self);
#else
        // @bug The original passes an unused, possibly uninitialized argument.
        AnimateEntity(D_us_8018066C, self, player);
#endif
        self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        self->hitboxState = 0;
        if (g_BossMgrState & BOSS_MGR_DEATH_FIGHT_ON) {
            self->hitboxState = 2;
            SetStep(2);
        }
        break;
    case 2:
        if (self->hitFlags & 3) {
            SetStep(8);
            break;
        }
        switch (self->step_s) {
        case 0:
            self->ext.deathFirstForm.timer = ((Random() & 3) << 5) + 0x20;
            player = &PLAYER;
            posX = player->posX.i.hi;
            posY = player->posY.i.hi;
            if (posX < self->posX.i.hi) {
                posX -= 0x60;
            } else {
                posX += 0x60;
            }
            posY -= Random() & 0x3F;
            prim = self->ext.deathFirstForm.prim;
            posX -= self->posX.i.hi;
            posY -= self->posY.i.hi;
            prim->x0 = posX;
            prim->y0 = posY;
            self->ext.deathFirstForm.angle = rand() & 0xFFF;
            self->ext.deathFirstForm.speed = FIX(1.75);
            self->step_s++;
            // fallthrough
        case 1:
#ifdef FIX_UB
            AnimateEntity(D_us_8018066C, self);
#else
            // @bug The original passes an unused, possibly uninitialized
            // argument.
            AnimateEntity(D_us_8018066C, self, player);
#endif
            MoveEntity();
            prim = self->ext.deathFirstForm.prim;
            posX = prim->x0;
            posY = prim->y0;
            angle = ratan2(posY - self->posY.i.hi, posX - self->posX.i.hi);
            angle = func_us_8019A98C_from_rcen(
                0x30, self->ext.deathFirstForm.angle, angle);
            self->velocityX =
                (rcos(angle) * self->ext.deathFirstForm.speed) >> 12;
            self->velocityY =
                (rsin(angle) * self->ext.deathFirstForm.speed) >> 12;
            self->ext.deathFirstForm.angle = angle;
            if (self->ext.deathFirstForm.speed > FIX(0.875)) {
                self->ext.deathFirstForm.speed -=
                    self->ext.deathFirstForm.speed >> 4;
            }
            func_us_8019B430();
            if (!--self->ext.deathFirstForm.timer) {
                self->step_s--;
            }
            if (!self->ext.deathFirstForm.unk88) {
                if (self->hitPoints <
                    g_api.enemyDefs[ENEMY_DEATH].hitPoints -
                        g_api.enemyDefs[ENEMY_DEATH].hitPoints / 4) {
                    SetStep(3);
                }
            } else if (
                self->hitPoints < g_api.enemyDefs[ENEMY_DEATH].hitPoints / 2) {
                SetStep(4);
            }
            break;
        }
        break;
    case 3:
        switch (self->step_s) {
        case 0:
            if (!AnimateEntity(D_us_8018067C, self)) {
                SetSubStep(1);
            }
            break;
        case 1:
            CreateEntityFromEntity(E_UNK_18, self, self + 1);
            (self + 1)->params = 0;
            (self + 1)->ext.deathBossProjectile.owner = self;
            (self + 1)->posX.i.hi -= 0x28;
            (self + 1)->posY.i.hi -= 0x1C;
            (self + 1)->zPriority = self->zPriority + 1;
            CreateEntityFromEntity(E_UNK_18, self, self + 2);
            (self + 2)->params = 1;
            (self + 2)->ext.deathBossProjectile.owner = self;
            (self + 2)->posX.i.hi += 0x28;
            (self + 2)->posY.i.hi -= 0x1C;
            (self + 2)->zPriority = self->zPriority + 1;
            self->ext.deathFirstForm.timer = 0x80;
            self->step_s++;
            // fallthrough
        case 2:
            if (!(self->ext.deathFirstForm.timer & 0xF)) {
                PlaySfxPositional(SFX_RIC_SUC_REVIVE);
            }
            AnimateEntity(D_us_801806A8, self);
            if (!--self->ext.deathFirstForm.timer) {
                SetSubStep(3);
            }
            break;
        case 3:
            if (!AnimateEntity(D_us_80180694, self)) {
                PlaySfxPositional(SFX_DEATH_BALL_ATTACK);
                self->ext.deathFirstForm.unk88 = 1;
                self->step_s++;
            }
            break;
        case 4:
            if (!AnimateEntity(D_us_801806B0, self)) {
                SetStep(2);
            }
            break;
        }
        break;
    case 4:
        switch (self->step_s) {
        case 0:
            self->ext.deathFirstForm.unk89 = 1;
            self->velocityX = 0;
            self->velocityY = 0;
            self->step_s++;
            // fallthrough
        case 1:
            if (!AnimateEntity(D_us_8018067C, self)) {
                PlaySfxPositional(SFX_DEATH_PAIN_A);
                SetSubStep(2);
            }
            break;
        case 2:
            AnimateEntity(D_us_801806A8, self);
            if ((self + 1)->ext.deathBossProjectile.ready &&
                (self + 2)->ext.deathBossProjectile.ready) {
                self->ext.deathFirstForm.unk8B = 1;
                SetStep(5);
            }
            break;
        }
        break;
    case 5:
        AnimateEntity(D_us_801806A8, self);
        MoveEntity();
        self->ext.deathFirstForm.phaseAngle += 0x40;
        self->velocityY =
            (rsin(self->ext.deathFirstForm.phaseAngle) * FIX(0.75)) >> 12;
        if (self->posY.i.hi < 0x68) {
            self->velocityY += FIX(0.0625);
        } else {
            self->velocityY -= FIX(0.0625);
        }
        if (self->posX.i.hi < 0x80) {
            if (self->velocityX < FIX(0.875)) {
                self->velocityX += FIX(0.03125);
            }
        } else if (self->velocityX > FIX(-0.875)) {
            self->velocityX -= FIX(0.03125);
        }
        if (self->hitPoints <
            (s16)(g_api.enemyDefs[ENEMY_DEATH].hitPoints / 3)) {
            SetStep(6);
        }
        break;
    case 6:
        switch (self->step_s) {
        case 0:
            g_BossMgrState |= 4;
            self->step_s++;
            // fallthrough
        case 1:
            AnimateEntity(D_us_801806A8, self);
            if ((self + 1)->ext.deathBossProjectile.ready &&
                (self + 2)->ext.deathBossProjectile.ready) {
                self->ext.deathFirstForm.unk8C = 1;
                self->ext.deathFirstForm.timer = 0x40;
                PlaySfxPositional(SFX_DEATH_SCYTHE_ATTACK);
                self->step_s++;
            }
            break;
        case 2:
            AnimateEntity(D_us_801806A8, self);
            if (!--self->ext.deathFirstForm.timer) {
                self->ext.deathFirstForm.phaseAngle = 0x200;
                SetStep(7);
            }
            break;
        }
        break;
    case 7:
        switch (self->step_s) {
        case 0:
            AnimateEntity(D_us_8018066C, self);
            if ((self + 1)->ext.deathBossProjectile.ready &&
                (self + 2)->ext.deathBossProjectile.ready) {
                SetSubStep(1);
            }
            break;
        case 1:
            if (!AnimateEntity(D_us_801806B8, self)) {
                self->ext.deathFirstForm.unk8D = 1;
                self->ext.deathFirstForm.timer = 0x10;
                SetSubStep(2);
            }
            if (LOW(self->pose) == 4) {
                PlaySfxPositional(SFX_DEATH_ATTACK);
            }
            break;
        case 2:
            self->ext.deathFirstForm.unk8D = 0;
            if (!--self->ext.deathFirstForm.timer) {
                SetSubStep(0);
            }
            break;
        }
        MoveEntity();
        angle = self->ext.deathFirstForm.phaseAngle;
        posX = PLAYER.posX.i.hi + ((rcos(angle) * 0x60) >> 12);
        posY = PLAYER.posY.i.hi - ((rsin(angle) * 0x60) >> 12);
        angle = ratan2(posY - self->posY.i.hi, posX - self->posX.i.hi);
        self->ext.deathFirstForm.speed = FIX(1.75);
        angle = func_us_8019A98C_from_rcen(
            0x30, self->ext.deathFirstForm.angle, angle);
        self->velocityX = (rcos(angle) * self->ext.deathFirstForm.speed) >> 12;
        self->velocityY = (rsin(angle) * self->ext.deathFirstForm.speed) >> 12;
        self->ext.deathFirstForm.angle = angle;
        posX = self->posX.i.hi + g_Tilemap.scrollX.i.hi;
        if (posX > 0x180) {
            self->ext.deathFirstForm.phaseAngle = 0x600;
        }
        if (posX < 0x80) {
            self->ext.deathFirstForm.phaseAngle = 0x200;
        }
        break;
    case 8:
        if (!self->step_s) {
            self->ext.deathFirstForm.timer = 0x40;
            if (GetSideToPlayer() & 1) {
                self->velocityX = FIX(4);
            } else {
                self->velocityX = FIX(-4);
            }
            self->velocityY = FIX(-4);
            if (Random() & 1) {
                PlaySfxPositional(SFX_DEATH_PAIN_B);
            } else {
                PlaySfxPositional(SFX_DEATH_PAIN_C);
            }
            posX = self->posX.i.hi + g_Tilemap.scrollX.i.hi;
            if (posX > 0x180) {
                self->velocityX = FIX(-7);
            }
            if (posX < 0x80) {
                self->velocityX = FIX(7);
            }
            self->step_s++;
        }
        AnimateEntity(D_us_801806D0, self);
        MoveEntity();
        self->velocityX -= self->velocityX >> 5;
        self->velocityY -= self->velocityY >> 5;
        self->velocityY += FIX(0.0625);
        if (!--self->ext.deathFirstForm.timer) {
            SetStep(2);
        }
        break;
    case 9:
        switch (self->step_s) {
        case 0:
            prim = self->ext.deathFirstForm.prim;
            self->hitboxState = 0;
            g_BossMgrState |= BOSS_MGR_DEATH_FIRST_FORM_DEFEAT;
            prim->x0 = 0x90;
            prim->y0 = 0x68;
            PlaySfxPositional(SFX_DEATH_YOURE_STRONG_INDEED);
            self->step_s++;
            // fallthrough
        case 1:
            AnimateEntity(D_us_8018066C, self);
            MoveEntity();
            prim = self->ext.deathFirstForm.prim;
            posX = prim->x0 - self->posX.i.hi;
            posY = prim->y0 - self->posY.i.hi;
            angle = ratan2(posY, posX);
            self->velocityX = rcos(angle) * 16;
            self->velocityY = rsin(angle) * 16;
            if (SquareRoot0(posX * posX + posY * posY) < 8) {
                self->step_s++;
            }
            break;
        case 2:
            prim = self->ext.deathFirstForm.prim;
            self->ext.deathFirstForm.brightness = 0x40;
            self->ext.deathFirstForm.halfWidth = 0;
            self->opacity = 0x80;
            self->drawFlags |= ENTITY_OPACITY;
            prim->type = PRIM_G4;
            prim->x0 = prim->x2 = self->posX.i.hi;
            prim->x1 = prim->x3 = self->posX.i.hi;
            prim->y0 = prim->y1 = 0;
            prim->y2 = prim->y3 = 0x100;
            prim->r0 = prim->g0 = prim->b0 =
                self->ext.deathFirstForm.brightness;
            prim->priority = 0xC0;
            prim->drawMode =
                DRAW_TPAGE2 | DRAW_TPAGE | DRAW_UNK02 | DRAW_TRANSP;
            LOW(prim->r1) = LOW(prim->r0);
            LOW(prim->r2) = LOW(prim->r0);
            LOW(prim->r3) = LOW(prim->r0);
            prim = prim->next;
            prim->type = PRIM_G4;
            prim->x0 = prim->x2 = self->posX.i.hi;
            prim->x1 = prim->x3 = self->posX.i.hi;
            prim->y0 = prim->y1 = 0;
            prim->y2 = prim->y3 = 0x100;
            prim->r0 = prim->g0 = prim->b0 = 0;
            LOW(prim->r2) = LOW(prim->r0);
            prim->r1 = prim->g1 = prim->b1 =
                self->ext.deathFirstForm.brightness;
            prim->priority = 0xC0;
            prim->drawMode =
                DRAW_TPAGE2 | DRAW_TPAGE | DRAW_UNK02 | DRAW_TRANSP;
            LOW(prim->r3) = LOW(prim->r1);
            prim = prim->next;
            prim->type = PRIM_G4;
            prim->x0 = prim->x2 = self->posX.i.hi;
            prim->x1 = prim->x3 = self->posX.i.hi;
            prim->y0 = prim->y1 = 0;
            prim->y2 = prim->y3 = 0x100;
            prim->r0 = prim->g0 = prim->b0 =
                self->ext.deathFirstForm.brightness;
            prim->r1 = prim->g1 = prim->b1 = 0;
            prim->priority = 0xC0;
            prim->drawMode =
                DRAW_TPAGE2 | DRAW_TPAGE | DRAW_UNK02 | DRAW_TRANSP;
            LOW(prim->r2) = LOW(prim->r0);
            LOW(prim->r3) = LOW(prim->r1);
            self->ext.deathFirstForm.timer = 0x20;
            PlaySfxPositional(SFX_TELEPORT_BANG_B);
            self->step_s++;
            // fallthrough
        case 3:
            prim = self->ext.deathFirstForm.prim;
            prim = prim->next;
            prim->x0 = prim->x2 -= 2;
            prim = prim->next;
            prim->x1 = prim->x3 += 2;
            if (self->posX.i.hi == prim->x1 - 0x30) {
                PlaySfxPositional(SFX_DEATH_BUT_NOW_YOU_WILL_DIE);
                self->step_s++;
            }
            break;
        case 4:
            count = 0;
            self->ext.deathFirstForm.halfWidth += 4;
            posX = self->posX.i.hi - self->ext.deathFirstForm.halfWidth;
            if (posX < 0) {
                count = 1;
                posX = 0;
            }
            prim = self->ext.deathFirstForm.prim;
            prim->x0 = prim->x2 = posX;
            prim = prim->next;
            prim->x0 = prim->x2 = posX - 0x30;
            prim->x1 = prim->x3 = posX;
            posX = self->posX.i.hi + self->ext.deathFirstForm.halfWidth;
            if (posX > 0x100) {
                count++;
                posX = 0x100;
            }
            prim = self->ext.deathFirstForm.prim;
            prim->x1 = prim->x3 = posX;
            prim = prim->next;
            prim = prim->next;
            prim->x0 = prim->x2 = posX;
            prim->x1 = prim->x3 = posX + 0x30;
            if (self->opacity) {
                self->opacity -= 8;
            }
            if (self->ext.deathFirstForm.brightness < 0xF0) {
                self->ext.deathFirstForm.brightness += 8;
            }
            prim = self->ext.deathFirstForm.prim;
            prim->r0 = prim->g0 = prim->b0 =
                self->ext.deathFirstForm.brightness;
            LOW(prim->r1) = LOW(prim->r0);
            LOW(prim->r2) = LOW(prim->r0);
            LOW(prim->r3) = LOW(prim->r0);
            prim = prim->next;
            prim->r0 = prim->g0 = prim->b0 = 0;
            LOW(prim->r2) = LOW(prim->r0);
            prim->r1 = prim->g1 = prim->b1 =
                self->ext.deathFirstForm.brightness;
            LOW(prim->r3) = LOW(prim->r1);
            prim = prim->next;
            prim->r0 = prim->g0 = prim->b0 =
                self->ext.deathFirstForm.brightness;
            prim->r1 = prim->g1 = prim->b1 = 0;
            LOW(prim->r2) = LOW(prim->r0);
            LOW(prim->r3) = LOW(prim->r1);
            if (count == 2) {
                self->step_s++;
            }
            break;
        case 5:
            prim = self->ext.deathFirstForm.prim;
            while (prim != NULL) {
                prim->drawMode = DRAW_HIDE;
                prim = prim->next;
            }
            CreateEntityFromEntity(E_UNK_1B, self, &g_Entities[96]);
            self->step_s++;
            break;
        case 6:
            self->animCurFrame = 0;
            break;
        }
        break;
    case 0xFF:
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
            if (!self->step_s) {
                self->animCurFrame--;
                self->step_s |= 1;
            }
        } else {
            self->step_s = 0;
        }
        break;
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
        if (posY < 0x50) {
            self->posY.i.hi = 0x50 - g_Tilemap.scrollY.i.hi;
        }
    } else if (posY > 0xE0) {
        self->posY.i.hi = 0xE0 - g_Tilemap.scrollY.i.hi;
    }
}

void func_us_8019C718(Entity* self) {
    s16 angle;
    s32 posX;
    s32 posY;

    if (g_BossMgrState & BOSS_MGR_DEATH_FIRST_FORM_DEFEAT) {
        self->flags |= FLAG_DEAD;
    }
    if ((self->flags & FLAG_DEAD) && (self->step != 3)) {
        PlaySfxPositional(SFX_METAL_CLANG_C);
        self->hitboxState = 0;
        SetStep(3);
    }
    switch (self->step) {
    case 0:
        InitializeEntity(D_us_801804A0);
        self->facingLeft = Random() & 1;
        self->hitboxState = 0;
        // fallthrough
    case 1:
        if (!AnimateEntity(D_us_801806E0, self)) {
            self->hitboxState = 3;
            self->animCurFrame = 0x4F;
            self->drawFlags = ENTITY_ROTATE;
            SetStep(2);
        }
        break;
    case 2:
        if (!self->step_s) {
            posX = PLAYER.posX.i.hi;
            posY = PLAYER.posY.i.hi;
            posX -= 0x20 - (Random() & 0x3F);
            posY -= 0x20 - (Random() & 0x3F);
            posY = ratan2(posY - self->posY.i.hi, posX - self->posX.i.hi);
            angle = posY;
            self->velocityX = (rcos(angle) * FIX(1)) >> 12;
            self->velocityY = (rsin(angle) * FIX(1)) >> 12;
            PlaySfxPositional(SFX_WEAPON_SCRAPE_ECHO);
            self->step_s++;
        }
        MoveEntity();
        self->rotate += ROT(16.875);
        break;
    case 3:
        if (!AnimateEntity(D_us_801806F8, self)) {
            DestroyEntity(self);
        }
        break;
    }
}

extern EInit D_us_801804AC;
extern u8 D_us_80180708[];
extern u8 D_us_80180718[];
extern u8 D_us_8018072C[];
extern u8 D_us_80180744[];
extern u8 D_us_8018075C[];

void func_us_8019C924(Entity* self) {
    Entity* entity;
    EnemyDef* enemyDef;
    s32 posX;
    s32 posY;
    s32 animStatus;
    s32 targetX;
    s32 targetY;
    s16 angle;
    s16 targetAngle;

    FntPrint("ball_step %x\n", self->step);
    if (g_BossMgrState & BOSS_MGR_DEATH_FIRST_FORM_DEFEAT) {
        entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (entity != NULL) {
            CreateEntityFromEntity(E_EXPLOSION, self, entity);
            entity->params = 3;
        }
        DestroyEntity(self);
        return;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_801804AC);
        self->drawFlags = ENTITY_SCALEX | ENTITY_SCALEY;
        self->scaleY = 0x80;
        self->scaleX = 0x80;
        self->hitboxState = 0;
        self->blendMode = BLEND_TRANSP | BLEND_ADD;
        PlaySfxPositional(SFX_RAPID_SYNTH_BUBBLE_SHORT);
        // fallthrough
    case 1:
        if (!AnimateEntity(D_us_80180708, self)) {
            self->step++;
        }
        // fallthrough
    case 2:
        self->scaleX += 4;
        if (self->scaleX > 0x100) {
            self->hitboxState = 1;
            self->drawFlags = ENTITY_DEFAULT;
            SetStep(3);
        }
        self->scaleY = self->scaleX;
        break;
    case 3:
        AnimateEntity(D_us_80180718, self);
        entity = self->ext.deathBossProjectile.owner;
        if (entity->ext.deathFirstForm.unk88) {
            self->ext.deathBossProjectile.angle = 0x400;
            SetStep(4);
        }
        break;
    case 4:
        AnimateEntity(D_us_80180718, self);
        MoveEntity();
        posX = PLAYER.posX.i.hi;
        posY = PLAYER.posY.i.hi;
        posX -= 0x20 - (Random() & 0x3F);
        posY -= 0x20 - (Random() & 0x3F);
        angle = ratan2(posY - self->posY.i.hi, posX - self->posX.i.hi);
        angle =
            LimitAngleChange(0x40, self->ext.deathBossProjectile.angle, angle);
        targetAngle = angle;
        // Reuse the coordinate temporary to preserve register allocation.
        posX = rcos(angle);
        self->velocityX = (posX * FIX(0.4375)) >> 12;
        posX = rsin(angle);
        self->velocityY = (posX * FIX(0.4375)) >> 12;
        self->ext.deathBossProjectile.angle = targetAngle;
        entity = self->ext.deathBossProjectile.owner;
        if (entity->ext.deathFirstForm.unk89) {
            SetStep(5);
        }
        break;
    case 5:
        AnimateEntity(D_us_80180718, self);
        MoveEntity();
        entity = self->ext.deathBossProjectile.owner;
        if (!self->params) {
            posX = entity->posX.i.hi - 0x20;
        } else {
            posX = entity->posX.i.hi + 0x20;
        }
        posY = entity->posY.i.hi - 0x1C;
        posX -= self->posX.i.hi;
        posY -= self->posY.i.hi;
        angle = ratan2(posY, posX);
        self->velocityX = (rcos(angle) * FIX(1.75)) >> 12;
        self->velocityY = (rsin(angle) * FIX(1.75)) >> 12;
        if (SquareRoot0(posX * posX + posY * posY) < 4) {
            self->ext.deathBossProjectile.ready = 1;
            self->step++;
        }
        break;
    case 6:
        switch (self->step_s) {
        case 0:
            self->hitboxState = 0;
            AnimateEntity(D_us_80180718, self);
            entity = self->ext.deathBossProjectile.owner;
            if (entity->ext.deathFirstForm.unk8B) {
                self->ext.deathBossProjectile.ready = 0;
                SetSubStep(1);
            }
            break;
        case 1:
            if (!AnimateEntity(D_us_8018072C, self)) {
                SetStep(7);
            }
            break;
        }
        break;
    case 7:
        switch (self->step_s) {
        case 0:
            entity = AllocEntity(&g_Entities[176], &g_Entities[184]);
            if (entity != NULL) {
                CreateEntityFromEntity(E_UNK_19, self, entity);
                entity->ext.deathBossProjectile.owner = self;
                if (!self->params) {
                    entity->ext.deathBossProjectile.target = self + 1;
                } else {
                    entity->ext.deathBossProjectile.target = self - 1;
                }
                entity->facingLeft = self->params;
                entity->zPriority = self->zPriority + 1;
                self->ext.deathBossProjectile.skullReturned = 0;
                PlaySfxPositional(SFX_LOW_SYNTH_BUBBLES);
                self->step_s++;
            }
            break;
        case 1:
            self->ext.deathBossProjectile.timer = 0x60;
            self->step_s++;
            break;
        case 2:
            if (!--self->ext.deathBossProjectile.timer) {
                self->step_s = 0;
            }
            break;
        }
        if (g_Timer & 1) {
            self->animCurFrame = 0x39;
        } else {
            self->animCurFrame = 0;
        }
        MoveEntity();
        entity = self->ext.deathBossProjectile.owner;
        posY = entity->posY.i.hi - 0x1C;
        if (!self->params) {
            posX = entity->posX.i.hi - 0x50;
        } else {
            posX = entity->posX.i.hi + 0x50;
        }
        posX -= self->posX.i.hi;
        posY -= self->posY.i.hi;
        angle = ratan2(posY, posX);
        self->velocityX = (rcos(angle) * FIX(0.875)) >> 12;
        self->velocityY = (rsin(angle) * FIX(0.875)) >> 12;
        if (SquareRoot0(posX * posX + posY * posY) < 3) {
            self->velocityX = 0;
            self->velocityY = 0;
        }
        if (g_BossMgrState & 4) {
            SetStep(8);
        }
        break;
    case 8:
        switch (self->step_s) {
        case 0:
            animStatus = AnimateEntity(D_us_80180744, self);
            MoveEntity();
            entity = self->ext.deathBossProjectile.owner;
            if (!self->params) {
                posX = entity->posX.i.hi - 0x20;
            } else {
                posX = entity->posX.i.hi + 0x20;
            }
            posY = entity->posY.i.hi - 0x1C;
            posX -= self->posX.i.hi;
            posY -= self->posY.i.hi;
            angle = ratan2(posY, posX);
            self->velocityX = (rcos(angle) * FIX(1.75)) >> 12;
            self->velocityY = (rsin(angle) * FIX(1.75)) >> 12;
            if ((SquareRoot0(posX * posX + posY * posY) < 4) && !animStatus) {
                self->ext.deathBossProjectile.ready = 1;
                SetSubStep(1);
            }
            break;
        case 1:
            AnimateEntity(D_us_80180718, self);
            entity = self->ext.deathBossProjectile.owner;
            if (entity->ext.deathFirstForm.unk8C) {
                self->facingLeft = self->params;
                SetSubStep(2);
            }
            break;
        case 2:
            if (!AnimateEntity(D_us_8018075C, self)) {
                enemyDef = g_api.enemyDefs;
                self->attackElement =
                    enemyDef[ENEMY_DEATH_UNK_168].attackElement;
                self->attack = enemyDef[ENEMY_DEATH_UNK_168].attack;
                self->hitboxWidth = enemyDef[ENEMY_DEATH_UNK_168].hitboxWidth;
                self->hitboxHeight = enemyDef[ENEMY_DEATH_UNK_168].hitboxHeight;
                self->hitboxState = 1;
                self->blendMode = BLEND_NO;
                self->drawFlags = ENTITY_ROTATE;
                SetStep(9);
            }
            break;
        }
        break;
    case 9:
        switch (self->step_s) {
        case 0:
            self->ext.deathBossProjectile.ready = 1;
            self->step_s++;
            // fallthrough
        case 1:
            MoveEntity();
            func_801CDC80(&self->rotate, 0, 0x40);
            entity = self->ext.deathBossProjectile.owner;
            posY = entity->posY.i.hi - 0x10;
            if (!self->params) {
                posX = entity->posX.i.hi - 0x20;
            } else {
                posX = entity->posX.i.hi + 0x20;
            }
            posX -= self->posX.i.hi;
            posY -= self->posY.i.hi;
            angle = ratan2(posY, posX);
            self->velocityX = (rcos(angle) * FIX(0.875)) >> 12;
            self->velocityY = (rsin(angle) * FIX(0.875)) >> 12;
            if (SquareRoot0(posX * posX + posY * posY) < 3) {
                self->velocityX = 0;
                self->velocityY = 0;
            }
            entity = self->ext.deathBossProjectile.owner;
            if (entity->ext.deathFirstForm.unk8D) {
                self->ext.deathBossProjectile.ready = 0;
                self->step_s++;
            }
            break;
        case 2:
            targetX = PLAYER.posX.i.hi;
            targetY = PLAYER.posY.i.hi;
            self->ext.deathBossProjectile.angle =
                ratan2(targetY - self->posY.i.hi, targetX - self->posX.i.hi);
            self->ext.deathBossProjectile.speed = FIX(6);
            self->step_s++;
            // fallthrough
        case 3:
            MoveEntity();
            self->rotate -= ROT(22.5);
            if (!(self->rotate & 0xF00)) {
                PlaySfxPositional(SFX_DEATH_SCYTHE_SWISH);
            }
            posX = self->ext.deathBossProjectile.angle;
            angle = posX;
            posX = rcos(angle);
            self->velocityX =
                (posX * self->ext.deathBossProjectile.speed) >> 12;
            posX = rsin(angle);
            self->velocityY =
                (posX * self->ext.deathBossProjectile.speed) >> 12;
            self->ext.deathBossProjectile.speed -=
                self->ext.deathBossProjectile.speed >> 4;
            if (self->ext.deathBossProjectile.speed < FIX(0.25)) {
                self->ext.deathBossProjectile.timer = 0x20;
                self->step_s++;
            }
            if (!(g_Timer & 3)) {
                entity = AllocEntity(&g_Entities[208], &g_Entities[256]);
                if (entity != NULL) {
                    CreateEntityFromEntity(E_UNK_1A, self, entity);
                    entity->params = self->animCurFrame;
                    entity->facingLeft = self->facingLeft;
                    entity->rotate = self->rotate;
                }
            }
            break;
        case 4:
            self->rotate = (self->rotate - 0x200) & 0xFFF;
            if (!(self->rotate & 0xF00)) {
                PlaySfxPositional(SFX_DEATH_SCYTHE_SWISH);
            }
            if (!--self->ext.deathBossProjectile.timer) {
                self->step_s++;
            }
            break;
        case 5:
            MoveEntity();
            func_801CDC80(&self->rotate, 0, 0x40);
            entity = self->ext.deathBossProjectile.owner;
            posY = entity->posY.i.hi - 0x10;
            if (!self->params) {
                posX = entity->posX.i.hi - 0x20;
            } else {
                posX = entity->posX.i.hi + 0x20;
            }
            posX -= self->posX.i.hi;
            posY -= self->posY.i.hi;
            angle = ratan2(posY, posX);
            targetAngle = angle;
            posX = SquareRoot0(posX * posX + posY * posY);
            if (posX > 0x20) {
                targetAngle = LimitAngleChange(
                    0x60, self->ext.deathBossProjectile.angle, targetAngle);
            }
            self->velocityX = (rcos(targetAngle) * FIX(3)) >> 12;
            self->velocityY = (rsin(targetAngle) * FIX(3)) >> 12;
            self->ext.deathBossProjectile.angle = targetAngle;
            if (posX < 8) {
                self->step_s = 0;
            }
            break;
        }
        break;
    }
}
