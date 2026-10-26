// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rdai.h"

void func_us_801C4B2C(void) {
    Primitive* prim;
    Primitive* next;
    s32 x;
    s32 y;
    s32 deltaX;
    s32 deltaY;
    s32 i;

    prim = g_CurrentEntity->ext.prim;
    for (i = 0; i < 7; i++) {
        next = prim->next;
        x = next->x2 + prim->x0;
        x /= 2;
        y = next->y2 + prim->y0;
        y /= 2;
        deltaX = prim->x2 - x;
        deltaY = prim->y2 - y;
        deltaX = deltaX / 8 + x;
        deltaY = deltaY / 8 + y;
        next->x0 = prim->x2 = deltaX;
        next->y0 = prim->y2 = deltaY;
        x = next->x3 + prim->x1;
        x /= 2;
        y = next->y3 + prim->y1;
        y /= 2;
        deltaX = prim->x3 - x;
        deltaY = prim->y3 - y;
        deltaX = deltaX / 8 + x;
        deltaY = deltaY / 8 + y;
        next->x1 = prim->x3 = deltaX;
        next->y1 = prim->y3 = deltaY;
        prim = next;
    }
}

void UnkPrimHelper(Primitive* prim);
void UnkPolyFunc2(Primitive* prim);

void func_us_801C4C4C(void) {
    Primitive* prim;
    Primitive* previous;
    s32 primIndex;
    s32 i;
    s32 offsetY;

    switch (g_CurrentEntity->step_s) {
    case 0:
        g_CurrentEntity->hitboxState = 0;
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 20);
        if (primIndex == -1) {
            DestroyEntity(g_CurrentEntity);
            return;
        }
        g_CurrentEntity->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        g_CurrentEntity->ext.blackPanther.prim = prim;
        g_CurrentEntity->flags |= FLAG_HAS_PRIMS;
        for (i = 0; i < 8; i++) {
            prim->tpage = 0x12;
            prim->clut = PAL_CC_DARK_EFFECT;
            if (g_CurrentEntity->facingLeft) {
                prim->u0 = 0x40;
                prim->u1 = 0;
                prim->u2 = 0x40;
                prim->u3 = 0;
            } else {
                prim->u0 = 0;
                prim->u1 = 0x40;
                prim->u2 = 0;
                prim->u3 = 0x40;
            }
            prim->v0 = i * 2 + 0xB5;
            prim->v1 = i * 2 + 0xB5;
            prim->v2 = i * 2 + 0xB8;
            prim->v3 = i * 2 + 0xB8;
            PGREY(prim, 0) = 0x80;
            PGREY(prim, 1) = 0x80;
            PGREY(prim, 2) = 0x80;
            PGREY(prim, 3) = 0x80;
            if (g_CurrentEntity->facingLeft) {
                prim->x0 = g_CurrentEntity->posX.i.hi - 0x30;
            } else {
                prim->x0 = g_CurrentEntity->posX.i.hi - 0x10;
            }
            prim->x1 = prim->x0 + 0x40;
            prim->x2 = prim->x0;
            prim->x3 = prim->x1;
            offsetY = i * 2 - 7;
            prim->y0 = g_CurrentEntity->posY.i.hi + offsetY - 3;
            prim->y1 = prim->y0;
            prim->y2 = prim->y0 + 4;
            prim->y3 = prim->y2;
            prim->priority = g_CurrentEntity->zPriority + 2;
            prim->drawMode = DRAW_UNK02;
            previous = prim;
            prim = prim->next;
        }
        g_CurrentEntity->ext.blackPanther.lastPrim = previous;
        prim->tpage = 0x12;
        prim->clut = PAL_CC_DARK_EFFECT;
        prim->u0 = 0;
        prim->u1 = 0x40;
        prim->u2 = 0;
        prim->u3 = 0x40;
        prim->v0 = 0xEE;
        prim->v1 = 0xEE;
        prim->v2 = 0xEF;
        prim->v3 = 0xEF;
        PGREY(prim, 0) = 0x80;
        PGREY(prim, 1) = 0x80;
        PGREY(prim, 2) = 0x80;
        PGREY(prim, 3) = 0x80;
        if (g_CurrentEntity->facingLeft) {
            prim->x0 = g_CurrentEntity->posX.i.hi - 0x30;
        } else {
            prim->x0 = g_CurrentEntity->posX.i.hi - 0x10;
        }
        prim->x1 = prim->x0 + 0x40;
        prim->x2 = prim->x0;
        prim->x3 = prim->x1;
        prim->y0 = g_CurrentEntity->posY.i.hi + 8;
        prim->y1 = prim->y0;
        prim->y3 = prim->y2 = prim->y0;
        prim->priority = g_CurrentEntity->zPriority + 3;
        prim->drawMode = DRAW_HIDE | DRAW_UNK02;
        g_CurrentEntity->ext.blackPanther.prim88 = prim;
        prim = prim->next;
        prim->tpage = 0x12;
        prim->clut = PAL_CC_DARK_EFFECT;
        prim->u0 = 0x40;
        prim->u1 = 0x7F;
        prim->u2 = 0x40;
        prim->u3 = 0x7F;
        prim->v0 = 0xC8;
        prim->v1 = 0xC8;
        prim->v2 = 0xC9;
        prim->v3 = 0xC9;
        PGREY(prim, 0) = 0x80;
        PGREY(prim, 1) = 0x80;
        PGREY(prim, 2) = 0x80;
        PGREY(prim, 3) = 0x80;
        if (g_CurrentEntity->facingLeft) {
            prim->x0 = g_CurrentEntity->posX.i.hi - 0x30;
        } else {
            prim->x0 = g_CurrentEntity->posX.i.hi - 0x10;
        }
        prim->x1 = prim->x0 + 0x40;
        prim->x2 = prim->x0;
        prim->x3 = prim->x1;
        prim->y0 = g_CurrentEntity->posY.i.hi + 8;
        prim->y1 = prim->y0;
        prim->y3 = prim->y2 = prim->y0;
        prim->priority = g_CurrentEntity->zPriority + 2;
        prim->drawMode = DRAW_HIDE | DRAW_UNK02;
        g_CurrentEntity->ext.blackPanther.prim8C = prim;
        prim = prim->next;
        UnkPolyFunc2(prim);
        prim->tpage = 0x12;
        prim->clut = PAL_CC_DARK_EFFECT;
        prim->u0 = 0x5C;
        prim->u1 = 0x64;
        prim->u2 = 0x5C;
        prim->u3 = 0x64;
        prim->v0 = 0xC0;
        prim->v1 = 0xC0;
        prim->v2 = 0xC8;
        prim->v3 = 0xC8;
        if (g_CurrentEntity->facingLeft) {
            prim->next->x1 = g_CurrentEntity->posX.i.hi - 18;
        } else {
            prim->next->x1 = g_CurrentEntity->posX.i.hi + 18;
        }
        prim->next->y0 = g_CurrentEntity->posY.i.hi - 40;
        LOW(prim->next->u0) = 0;
        LOW(prim->next->r1) = 0;
        LOH(prim->next->r2) = 8;
        LOH(prim->next->b2) = 8;
        prim->next->b3 = 0x80;
        prim->priority = g_CurrentEntity->zPriority + 2;
        prim->drawMode = DRAW_HIDE | DRAW_UNK02;
        g_CurrentEntity->ext.blackPanther.prim90 = prim;
        prim = prim->next;
        prim = prim->next;
        UnkPolyFunc2(prim);
        prim->tpage = 0x12;
        prim->clut = PAL_CC_DARK_EFFECT;
        if (g_CurrentEntity->facingLeft) {
            prim->u0 = 0x3C;
            prim->u1 = 0;
            prim->u2 = 0x3C;
            prim->u3 = 0;
        } else {
            prim->u0 = 0;
            prim->u1 = 0x3C;
            prim->u2 = 0;
            prim->u3 = 0x3C;
        }
        prim->v0 = 0xD0;
        prim->v1 = 0xD0;
        prim->v2 = 0xDD;
        prim->v3 = 0xDD;
        if (g_CurrentEntity->facingLeft) {
            prim->next->x1 = g_CurrentEntity->posX.i.hi - 18;
        } else {
            prim->next->x1 = g_CurrentEntity->posX.i.hi + 18;
        }
        prim->next->y0 = g_CurrentEntity->posY.i.hi + 2;
        LOW(prim->next->u0) = 0;
        LOW(prim->next->r1) = 0;
        LOH(prim->next->r2) = 2;
        LOH(prim->next->b2) = 1;
        prim->next->b3 = 0x80;
        prim->priority = g_CurrentEntity->zPriority + 2;
        prim->drawMode = DRAW_HIDE | DRAW_UNK02;
        g_CurrentEntity->ext.blackPanther.prim9C = prim;
        PlaySfxPositional(SFX_NOISE_SWEEP_DOWN_A);
        g_CurrentEntity->ext.blackPanther.timer = 16;
        g_CurrentEntity->animCurFrame = 0;
        g_CurrentEntity->step_s++;
        break;
    case 1:
        if (!--g_CurrentEntity->ext.blackPanther.timer) {
            g_CurrentEntity->ext.blackPanther.state94 = 0;
            g_CurrentEntity->ext.blackPanther.state95 = 0;
            g_CurrentEntity->ext.blackPanther.state96 = 0;
            g_CurrentEntity->ext.blackPanther.unk97 = 0;
            g_CurrentEntity->ext.blackPanther.flashTimer = 0;
            g_CurrentEntity->ext.blackPanther.timer99 = 0x24;
            g_CurrentEntity->ext.blackPanther.timer9A = 0x30;
            g_CurrentEntity->ext.blackPanther.unk9B = 0;
            g_CurrentEntity->step_s++;
        }
        break;
    case 2:
        g_CurrentEntity->ext.blackPanther.timer++;
        switch (g_CurrentEntity->ext.blackPanther.state94) {
        case 0:
            func_us_801C4B2C();
            prim = g_CurrentEntity->ext.blackPanther.prim;
            prim->y0 -= 3;
            prim->y1 -= 3;
            if (g_CurrentEntity->ext.blackPanther.timer & 1) {
                prim->x0++;
                prim->x1--;
            }
            if (prim->x1 - prim->x0 < 32) {
                g_CurrentEntity->ext.blackPanther.timer = 12;
                g_CurrentEntity->ext.blackPanther.state94++;
            }
            prim = prim->next;
            for (i = 0; i < 6; i++) {
                prim->x2 += 2;
                prim->x3 -= 2;
                prim = prim->next;
            }
            break;
        case 1:
            func_us_801C4B2C();
            prim = g_CurrentEntity->ext.blackPanther.prim;
            prim->y0 += 6;
            prim->y1 += 6;
            prim = prim->next;
            for (i = 0; i < 6; i++) {
                prim->x2++;
                prim->x3--;
                prim = prim->next;
            }
            if (g_CurrentEntity->ext.blackPanther.timer & 1) {
                prim = g_CurrentEntity->ext.blackPanther.lastPrim;
                prim->x2++;
                prim->x3 -= 2;
            }
            prim = g_CurrentEntity->ext.blackPanther.prim;
            if (prim->y0 > g_CurrentEntity->posY.i.hi + 8) {
                for (i = 0; i < 8; i++) {
                    prim->drawMode |= DRAW_HIDE;
                    prim = prim->next;
                }
            }
            break;
        }
        switch (g_CurrentEntity->ext.blackPanther.state95) {
        case 0:
            if (!--g_CurrentEntity->ext.blackPanther.timer99) {
                prim = g_CurrentEntity->ext.blackPanther.prim88;
                prim->drawMode &= ~DRAW_HIDE;
                g_CurrentEntity->ext.blackPanther.timer99 = 15;
                g_CurrentEntity->ext.blackPanther.state95++;
            }
            break;
        case 1:
            prim = g_CurrentEntity->ext.blackPanther.prim88;
            prim->v3 = ++prim->v2;
            prim->y1 = prim->y0 -= 2;
            if (!(g_CurrentEntity->ext.blackPanther.timer & 3)) {
                prim->x0--;
                prim->x1++;
            }
            if (!--g_CurrentEntity->ext.blackPanther.timer99) {
                g_CurrentEntity->ext.blackPanther.state95++;
            }
            break;
        case 2:
            prim = g_CurrentEntity->ext.blackPanther.prim88;
            if (!(g_CurrentEntity->ext.blackPanther.timer % 3)) {
                prim->v3 = --prim->v2;
            }
            prim->y1 = ++prim->y0;
            if (prim->y0 > prim->y2) {
                prim->drawMode |= DRAW_HIDE;
                g_CurrentEntity->ext.blackPanther.state95 = 8;
            }
            break;
        }
        switch (g_CurrentEntity->ext.blackPanther.state96) {
        case 0:
            if (!--g_CurrentEntity->ext.blackPanther.timer9A) {
                prim = g_CurrentEntity->ext.blackPanther.prim8C;
                prim->drawMode &= ~DRAW_HIDE;
                g_CurrentEntity->ext.blackPanther.state96++;
            }
            break;
        case 1:
            prim = g_CurrentEntity->ext.blackPanther.prim8C;
            prim->v2 += 4;
            prim->v3 = prim->v2;
            prim->y0 -= 4;
            prim->y1 = prim->y0;
            if (prim->v2 > 0xF8) {
                prim = g_CurrentEntity->ext.blackPanther.prim90;
                prim->drawMode &= ~DRAW_HIDE;
                LOW(prim->next->r1) = FIX(-1);
                prim = g_CurrentEntity->ext.blackPanther.prim9C;
                prim->drawMode &= ~DRAW_HIDE;
                g_CurrentEntity->ext.blackPanther.state96++;
            }
            break;
        case 2:
            prim = g_CurrentEntity->ext.blackPanther.prim8C;
            prim->y1 = ++prim->y0;
            if (prim->y0 == prim->y3) {
                g_CurrentEntity->ext.blackPanther.timer = 1;
                g_CurrentEntity->ext.blackPanther.unk9B = 0;
                prim->drawMode |= DRAW_HIDE;
                g_CurrentEntity->step_s++;
            }
            prim = g_CurrentEntity->ext.blackPanther.prim90;
            UnkPrimHelper(prim);
            LOW(prim->next->r1) += FIX(0.0625);
            prim = g_CurrentEntity->ext.blackPanther.prim9C;
            UnkPrimHelper(prim);
            if (LOH(prim->next->b2) < 13) {
                LOH(prim->next->b2)++;
            }
            if (LOH(prim->next->r2) < 60) {
                LOH(prim->next->r2) += 2;
            }
            break;
        }
        break;
    case 3:
        g_CurrentEntity->ext.blackPanther.timer++;
        prim = g_CurrentEntity->ext.blackPanther.prim9C;
        UnkPrimHelper(prim);
        if (!(g_CurrentEntity->ext.blackPanther.timer & 3)) {
            g_CurrentEntity->ext.blackPanther.unk9B ^= 1;
        }
        if (LOH(prim->next->b2) < 13) {
            LOH(prim->next->b2)++;
        }
        if (LOH(prim->next->r2) < 60) {
            LOH(prim->next->r2)++;
        }
        prim = g_CurrentEntity->ext.blackPanther.prim90;
        UnkPrimHelper(prim);
        LOW(prim->next->r1) += FIX(0.0625);
        if (prim->next->y0 > g_CurrentEntity->posY.i.hi + 6) {
            prim->drawMode |= DRAW_HIDE;
            g_CurrentEntity->step_s++;
        }
        break;
    case 4:
        break;
    }
}

void func_us_801C5AA0(void) {
    Primitive* prim;
    u8 facingLeft;
    s32 i;
    u16 palette;

    switch (g_CurrentEntity->step_s) {
    case 0:
        facingLeft = g_CurrentEntity->facingLeft;
        g_CurrentEntity->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        if (facingLeft != g_CurrentEntity->facingLeft) {
            if (g_CurrentEntity->facingLeft) {
                g_CurrentEntity->posX.i.hi += 24;
            } else {
                g_CurrentEntity->posX.i.hi -= 24;
            }
        }
        prim = g_CurrentEntity->ext.blackPanther.prim;
        for (i = 0; i < 8; i++) {
            prim->tpage = 0x12;
            prim->clut = PAL_CC_DARK_EFFECT;
            if (g_CurrentEntity->facingLeft) {
                prim->u0 = 0x40;
                prim->u1 = 0;
                prim->u2 = 0x40;
                prim->u3 = 0;
            } else {
                prim->u0 = 0;
                prim->u1 = 0x40;
                prim->u2 = 0;
                prim->u3 = 0x40;
            }
            prim->v0 = i * 2 + 0xB5;
            prim->v1 = i * 2 + 0xB5;
            prim->v2 = i * 2 + 0xB5 + 1;
            prim->v3 = i * 2 + 0xB5 + 1;
            PGREY(prim, 0) = 0x80;
            PGREY(prim, 1) = 0x80;
            PGREY(prim, 2) = 0x80;
            PGREY(prim, 3) = 0x80;
            if (g_CurrentEntity->facingLeft) {
                prim->x0 = g_CurrentEntity->posX.i.hi - 0x30;
            } else {
                prim->x0 = g_CurrentEntity->posX.i.hi - 0x10;
            }
            prim->x1 = prim->x0 + 0x40;
            prim->x2 = prim->x0;
            prim->x3 = prim->x1;
            prim->y0 = g_CurrentEntity->posY.i.hi + 8;
            prim->y1 = prim->y0;
            prim->y3 = prim->y2 = prim->y0;
            prim->priority = g_CurrentEntity->zPriority + 2;
            prim->drawMode = DRAW_UNK02;
            prim = prim->next;
        }
        func_us_801C4B2C();
        PlaySfxPositional(SFX_NOISE_SWEEP_DOWN_A);
        g_CurrentEntity->step_s++;
        g_CurrentEntity->ext.blackPanther.timer99 = 8;
        break;
    case 1:
        prim = g_CurrentEntity->ext.blackPanther.prim9C;
        prim->y0 -= 2;
        prim->y1 -= 2;
        if (!--g_CurrentEntity->ext.blackPanther.timer99) {
            g_CurrentEntity->ext.blackPanther.timer99 = 0x10;
            g_CurrentEntity->step_s++;
        }
        break;
    case 2:
        prim = g_CurrentEntity->ext.blackPanther.prim9C;
        prim->y0--;
        prim->y1--;
        prim = g_CurrentEntity->ext.blackPanther.prim;
        prim->y0 -= 4;
        prim->y1 -= 4;
        func_us_801C4B2C();
        if (!--g_CurrentEntity->ext.blackPanther.timer99) {
            g_CurrentEntity->ext.blackPanther.timer99 = 0xF;
            g_CurrentEntity->step_s++;
        }
        break;
    case 3:
        prim = g_CurrentEntity->ext.blackPanther.prim9C;
        prim->y0 += 2;
        prim->y1 += 2;
        if (prim->y0 > g_CurrentEntity->posY.i.hi) {
            prim->drawMode |= DRAW_HIDE;
        }
        prim = g_CurrentEntity->ext.blackPanther.prim;
        prim->y0 -= 2;
        prim->y1 -= 2;
        func_us_801C4B2C();
        if (!--g_CurrentEntity->ext.blackPanther.timer99) {
            g_CurrentEntity->ext.blackPanther.timer99 = 0xF;
            g_CurrentEntity->step_s++;
        }
        break;
    case 4:
        prim = g_CurrentEntity->ext.blackPanther.prim9C;
        prim->y0 += 2;
        prim->y1 += 2;
        if (prim->y0 > g_CurrentEntity->posY.i.hi) {
            prim->drawMode |= DRAW_HIDE;
        }
        prim = g_CurrentEntity->ext.blackPanther.prim;
        prim->y0 += 2;
        prim->y1 += 2;
        func_us_801C4B2C();
        if (prim->y0 > g_CurrentEntity->posY.i.hi - 6) {
            g_CurrentEntity->step_s++;
        }
        break;
    case 5:
        g_CurrentEntity->animCurFrame = 1;
        palette = g_CurrentEntity->palette;
        g_CurrentEntity->palette = PAL_FLAG(PAL_CC_DARK_EFFECT);
        g_CurrentEntity->hitEffect = palette;
        g_CurrentEntity->ext.blackPanther.flashTimer = 0x18;
        g_api.FreePrimitives(g_CurrentEntity->primIndex);
        g_CurrentEntity->flags &= ~FLAG_HAS_PRIMS;
        g_CurrentEntity->step_s++;
        break;
    case 6:
        if (!--g_CurrentEntity->ext.blackPanther.flashTimer) {
            g_CurrentEntity->palette = g_CurrentEntity->hitEffect;
            g_CurrentEntity->hitboxState = 3;
            g_CurrentEntity->step_s++;
        }
        break;
    case 7:
        break;
    }
}

extern EInit g_EInitBlackPanther;
extern s16 D_us_80181AC0[];
extern s16 D_us_80181ACC[];
extern s16 D_us_80181ADC[];
extern u8 D_us_80181AE4[];
extern u8 D_us_80181AF8[];

void EntityBlackPanther(Entity* self) {
    Collider collider;
    Entity* entity;
    Primitive* prim;
    s16 posX;
    s32 side;

    if ((self->flags & FLAG_DEAD) && self->step < 16) {
        self->hitboxState = 0;
        SetStep(16);
    }
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitBlackPanther);
        self->hitboxOffX = 2;
        self->hitboxOffY = -4;
        self->animCurFrame = 1;
        // fallthrough
    case 1:
        if (UnkCollisionFunc3(D_us_80181ACC) & 1) {
            self->step++;
        }
        break;
    case 2:
        self->animCurFrame = 1;
        self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        if (GetDistanceToPlayerX() < 0x70) {
            self->step++;
        }
        break;
    case 3:
        UnkCollisionFunc2(D_us_80181ADC);
        if (self->facingLeft) {
            self->velocityX = FIX(2.5);
        } else {
            self->velocityX = FIX(-2.5);
        }
        if (!AnimateEntity(D_us_80181AE4, self)) {
            PlaySfxPositional(SFX_STOMP_HARD_D);
            if (CheckColliderOffsets(D_us_80181AC0, self->facingLeft ^ 1) !=
                1) {
                SetStep(4);
            }
        }
        side = GetSideToPlayer() & 1;
        if (PLAYER.facingLeft != side && GetDistanceToPlayerX() < 0x50 &&
            (g_Player.status & (PLAYER_STATUS_UNK400 | PLAYER_STATUS_SUBWPN |
                                PLAYER_STATUS_SPELLCAST))) {
            SetStep(7);
        }
        posX = self->posX.i.hi;
        if (self->facingLeft) {
            posX += 24;
        } else {
            posX -= 24;
        }
        g_api.CheckCollision(posX, self->posY.i.hi, &collider, 0);
        if (collider.effects) {
            SetStep(6);
        }
        break;
    case 4:
        switch (self->step_s) {
        case 0:
            if (self->facingLeft) {
                self->velocityX = FIX(2);
            } else {
                self->velocityX = FIX(-2);
            }
            self->velocityY = FIX(-3.5);
            self->step_s++;
            break;
        case 1:
            AnimateEntity(D_us_80181AF8, self);
            if (UnkCollisionFunc3(D_us_80181ACC) & 1) {
                self->step_s++;
            }
            posX = self->posX.i.hi;
            if (self->facingLeft) {
                posX += 24;
            } else {
                posX -= 24;
            }
            g_api.CheckCollision(posX, self->posY.i.hi, &collider, 0);
            if (collider.effects) {
                SetStep(6);
            }
            break;
        case 2:
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            SetStep(3);
            break;
        }
        break;
    case 5:
        switch (self->step_s) {
        case 0:
            self->animCurFrame = 9;
            self->velocityX = 0;
            self->velocityY = FIX(-4);
            self->step_s++;
            break;
        case 1:
            if (UnkCollisionFunc3(D_us_80181ACC) & 1) {
                self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
                SetStep(3);
            }
            break;
        }
        break;
    case 6:
        if (!self->step_s) {
            self->animCurFrame = 0xB;
            if (self->facingLeft) {
                self->velocityX = FIX(-2.5);
            } else {
                self->velocityX = FIX(2.5);
            }
            self->velocityY = FIX(-3);
            self->rotate = 0;
            self->drawFlags |= ENTITY_ROTATE;
            self->step_s++;
        }
        self->rotate += ROT(22.5);
        if (UnkCollisionFunc3(D_us_80181ACC) & 1) {
            self->drawFlags &= ~ENTITY_ROTATE;
            SetStep(3);
        } else {
            self->velocityY -= FIX(0.0625);
        }
        break;
    case 7:
        func_us_801C4C4C();
        if (self->step_s == 4) {
            SetStep(8);
        }
        break;
    case 8:
        if (!self->step_s) {
            if (self->facingLeft) {
                self->velocityX = FIX(4);
            } else {
                self->velocityX = FIX(-4);
            }
            self->ext.blackPanther.timer = 0x30;
            self->step_s++;
        } else {
            UnkCollisionFunc2(D_us_80181ADC);
            prim = self->ext.blackPanther.prim9C;
            if (self->facingLeft) {
                prim->next->x1 = self->posX.i.hi - 18;
            } else {
                prim->next->x1 = self->posX.i.hi + 18;
            }
            prim->next->y0 = self->posY.i.hi + 2;
            UnkPrimHelper(prim);
            if (!--self->ext.blackPanther.timer) {
                SetStep(9);
            }
        }
        break;
    case 9:
        func_us_801C5AA0();
        if (self->step_s == 7) {
            SetStep(3);
        }
        break;
    case 16:
        switch (self->step_s) {
        case 0:
            self->animCurFrame = 0xB;
            self->rotate = 0;
            self->drawFlags |= ENTITY_ROTATE;
            if (self->facingLeft) {
                self->velocityX = FIX(2);
            } else {
                self->velocityX = FIX(-2);
            }
            self->velocityY = FIX(-3.5);
            self->step_s++;
            break;
        case 1:
            self->rotate -= ROT(11.25);
            if (UnkCollisionFunc3(D_us_80181ACC) & 1) {
                self->step_s++;
            }
            break;
        case 2:
            entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (entity != NULL) {
                CreateEntityFromEntity(E_EXPLOSION, self, entity);
                entity->params = 2;
            }
            PlaySfxPositional(SFX_EXPLODE_SMALL);
            DestroyEntity(self);
            return;
        }
        break;
    case 32:
#include "../pad2_anim_debug.h"
    }
    if (self->animCurFrame == 1) {
        self->hitboxOffX = 9;
        self->hitboxOffY = 2;
        self->hitboxWidth = 17;
        self->hitboxHeight = 4;
    }
    if (self->animCurFrame == 2) {
        self->hitboxOffX = 5;
        self->hitboxOffY = -5;
        self->hitboxWidth = 16;
        self->hitboxHeight = 10;
    }
    if (self->animCurFrame >= 3) {
        self->hitboxOffX = 4;
        self->hitboxOffY = -12;
        self->hitboxWidth = 23;
        self->hitboxHeight = 6;
    }
    if (self->animCurFrame >= 6) {
        self->hitboxOffX = -2;
        self->hitboxOffY = -4;
        self->hitboxWidth = 11;
        self->hitboxHeight = 11;
    }
}
