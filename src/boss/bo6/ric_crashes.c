// SPDX-License-Identifier: AGPL-3.0-or-later
#include "bo6.h"

extern s32 D_us_80182A0C[];

// same as RIC func_8016D9C4
void func_us_801C8618(Entity* self) {
    PrimLineG2* prim;
    Primitive* prim2;
    s32 i;
    long angle;
    s32 var_s6;
    s32 var_s5;
    s32 var_s7;
    s32 brightness;

    switch (self->step) {
    case 0:
        self->primIndex = g_api.AllocPrimitives(PRIM_LINE_G2, 20);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags = FLAG_UNK_10000000 | FLAG_HAS_PRIMS;
        prim = (PrimLineG2*)&g_PrimBuf[self->primIndex];
        for (i = 0; i < 4; i++) {
            prim->preciseX.val = RIC.posX.val;
            prim->preciseY.val = RIC.posY.val - FIX(40);
            prim->priority = 194;
            prim->drawMode = DRAW_HIDE;
            prim->x0 = prim->x1 = RIC.posX.i.hi;
            prim->y0 = prim->y1 = RIC.posY.i.hi - 0x1C;
            prim->r0 = prim->g0 = prim->b0 = 0x80;
            prim->r1 = prim->g1 = prim->b1 = 0x70;
            prim->angle = D_us_80182A0C[i];
            prim->delay = 1;
            prim = (PrimLineG2*)prim->next;
        }
        for (brightness = 0x80; i < 20; i++) {
            if (!(i % 4)) {
                brightness -= 0x10;
                switch (i / 4) {
                case 1:
                    self->ext.et_8016D9C4.lines[0] = prim;
                    break;
                case 2:
                    self->ext.et_8016D9C4.lines[1] = prim;
                    break;
                case 3:
                    self->ext.et_8016D9C4.lines[2] = prim;
                    break;
                case 4:
                    self->ext.et_8016D9C4.lines[3] = prim;
                    break;
                }
            }
            prim->priority = 0xC2;
            prim->drawMode = DRAW_HIDE;
            prim->x0 = prim->x1 = RIC.posX.i.hi;
            prim->y0 = prim->y1 = RIC.posY.i.hi - 0x1C;
            prim->r0 = prim->g0 = prim->b0 = brightness;
            prim->r1 = prim->g1 = prim->b1 = brightness - 0x10;
            prim = (PrimLineG2*)prim->next;
        }
        self->ext.et_8016D9C4.unk90 = 4;
        self->ext.et_8016D9C4.unk8C = self->ext.et_8016D9C4.unk8E = 0;
        self->step++;
        break;
    case 1:
        self->ext.et_8016D9C4.unk8E = 1;
        switch (self->ext.et_8016D9C4.unk8C) {
        case 0:
            prim = (PrimLineG2*)&g_PrimBuf[self->primIndex];
            break;
        case 1:
            prim = self->ext.et_8016D9C4.lines[0];
            break;
        case 2:
            prim = self->ext.et_8016D9C4.lines[1];
            break;
        case 3:
            prim = self->ext.et_8016D9C4.lines[2];
            break;
        case 4:
            prim = self->ext.et_8016D9C4.lines[3];
            break;
        }
        for (i = 0; i < 4; i++) {
            prim->drawMode &= ~DRAW_HIDE;
            prim = (PrimLineG2*)prim->next;
        }
        self->ext.et_8016D9C4.unk8C++;
        if (self->ext.et_8016D9C4.unk8C > 4) {
            self->step++;
        }
        break;
    case 2:
        if (!self->ext.et_8016D9C4.unk90) {
            self->step++;
            break;
        }
        break;
    case 3:
        self->ext.et_8016D9C4.unk90++;
        if (self->ext.et_8016D9C4.unk90 > 4) {
            DestroyEntity(self);
            return;
        }
        break;
    }
    if (!self->ext.et_8016D9C4.unk8E) {
        return;
    }
    prim = (PrimLineG2*)&g_PrimBuf[self->primIndex];
    for (i = 0; i < 4; i++) {
        if (prim->delay) {
            prim->x1 = prim->x0;
            prim->y1 = prim->y0;
            prim->x0 = prim->preciseX.i.hi;
            prim->y0 = prim->preciseY.i.hi;
            var_s7 = ratan2(prim->preciseY.val, FIX(128) - prim->preciseX.val) &
                     0xFFF;
            angle = prim->angle - var_s7;
            if (labs(angle) > 0x800) {
                if (angle < 0) {
                    angle += 0x1000;
                } else {
                    angle -= 0x1000;
                }
            }
            if (angle >= 0) {
                if (angle > 0x80) {
                    var_s6 = 0x80;
                } else {
                    var_s6 = angle;
                }
                angle = var_s6;
            } else {
                if (angle < -0x80) {
                    var_s5 = -0x80;
                } else {
                    var_s5 = angle;
                }
                angle = var_s5;
            }
            prim->angle = prim->angle - angle;
            prim->angle &= 0xFFF;
            prim->velocityX.val = (rcos(prim->angle) << 4 << 4);
            prim->velocityY.val = -(rsin(prim->angle) << 4 << 4);
            prim->preciseX.val += prim->velocityX.val;
            prim->preciseY.val += prim->velocityY.val;
            self->posX.i.hi = prim->preciseX.i.hi;
            self->posY.i.hi = prim->preciseY.i.hi;
            RicCreateEntFactoryFromEntity(
                self, BP_CRASH_REBOUND_STONE_PARTICLES, 0);
            if (prim->preciseY.val < 0) {
                prim->delay = 0;
                prim->drawMode |= DRAW_HIDE;
                self->ext.et_8016D9C4.unk90--;
            }
        }
        prim = (PrimLineG2*)prim->next;
    }
    prim = self->ext.et_8016D9C4.lines[0];
    prim2 = &g_PrimBuf[self->primIndex];
    for (i = 0; i < 16; i++) {
        prim->x1 = prim->x0;
        prim->y1 = prim->y0;
        prim->x0 = prim2->x1;
        prim->y0 = prim2->y1;
        prim = (PrimLineG2*)prim->next;
        prim2 = prim2->next;
    }
}

void RicEntityCrashReboundStoneExplosion(Entity* self) {
    Primitive* prim;
    s32 i;

    switch (self->step) {
    case 0:
        self->primIndex = g_api.AllocPrimitives(PRIM_G4, 0x10);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags = FLAG_UNK_10000000 | FLAG_HAS_PRIMS;
        prim = &g_PrimBuf[self->primIndex];
        for (i = 0; i < 0x10; i++) {
            prim->priority = 0xC2;
            prim->drawMode = DRAW_DITHERING | DRAW_TPAGE2 | DRAW_TPAGE |
                             DRAW_COLORS | DRAW_TRANSP;
            prim->x0 = prim->x1 = 0x80;
            prim->y0 = prim->y1 = 0;
            prim = prim->next;
        }
        self->ext.reboundStoneCrashExplosion.unk7C = 0x40;
        self->ext.reboundStoneCrashExplosion.unk7E = 0;
        self->ext.reboundStoneCrashExplosion.unk84 = 0;
        self->ext.reboundStoneCrashExplosion.unk80 = 0x10;
        self->ext.reboundStoneCrashExplosion.unk82 = 8;
        self->step++;
        break;
    case 1:
        self->ext.reboundStoneCrashExplosion.unk84 += 0x20;
        if (self->ext.reboundStoneCrashExplosion.unk84 > 0x120) {
            self->posX.val = FIX(128.0);
            self->posY.val = FIX(128.0);
            self->hitboxWidth = 0x80;
            self->hitboxHeight = 0x80;
            self->step++;
        }
        break;
    case 2:
        self->ext.reboundStoneCrashExplosion.unk86++;
        if (self->ext.reboundStoneCrashExplosion.unk86 == 5) {
            self->ext.reboundStoneCrashExplosion.unk80 = -0x18;
        } else if (self->ext.reboundStoneCrashExplosion.unk86 >= 0xF) {
            self->ext.reboundStoneCrashExplosion.unk82 = -0x18;
            self->step++;
        }
        break;
    case 3:
        break;
    case 4:
        DestroyEntity(self);
        return;
    }
    self->ext.reboundStoneCrashExplosion.unk7C +=
        self->ext.reboundStoneCrashExplosion.unk80;
    if (self->ext.reboundStoneCrashExplosion.unk7C > 0xFF) {
        self->ext.reboundStoneCrashExplosion.unk7C = 0xFF;
        self->ext.reboundStoneCrashExplosion.unk80 = 0;
    } else if (self->ext.reboundStoneCrashExplosion.unk7C < 0) {
        self->ext.reboundStoneCrashExplosion.unk7C =
            self->ext.reboundStoneCrashExplosion.unk80 = 0;
    }
    self->ext.reboundStoneCrashExplosion.unk7E +=
        self->ext.reboundStoneCrashExplosion.unk82;
    if (self->ext.reboundStoneCrashExplosion.unk7E > 0xFF) {
        self->ext.reboundStoneCrashExplosion.unk7E = 0xFF;
        self->ext.reboundStoneCrashExplosion.unk82 = 0;
    } else if (self->ext.reboundStoneCrashExplosion.unk7E < 0) {
        self->ext.reboundStoneCrashExplosion.unk7E =
            self->ext.reboundStoneCrashExplosion.unk82 = 0;
        self->step += 1;
    }
    prim = &g_PrimBuf[self->primIndex];
    for (i = 0; i < 16; i++) {
        prim->b0 = prim->b1 = self->ext.reboundStoneCrashExplosion.unk7C;
        prim->b2 = prim->b3 = self->ext.reboundStoneCrashExplosion.unk7E;
        prim->r0 = prim->r1 = prim->g0 = prim->g1 =
            self->ext.reboundStoneCrashExplosion.unk7C;
        prim->r2 = prim->r3 = prim->g2 = prim->g3 =
            self->ext.reboundStoneCrashExplosion.unk7E;
        if (self->step < 2) {
            prim->x2 =
                ((rcos(i << 7) * self->ext.reboundStoneCrashExplosion.unk84) >>
                 0xC) +
                0x80;
            prim->x3 = ((rcos((i + 1) << 7) *
                         self->ext.reboundStoneCrashExplosion.unk84) >>
                        0xC) +
                       0x80;
            prim->y2 =
                ((rsin(i << 7) * self->ext.reboundStoneCrashExplosion.unk84) >>
                 0xC);
            prim->y3 = ((rsin((i + 1) << 7) *
                         self->ext.reboundStoneCrashExplosion.unk84) >>
                        0xC);
        }
        prim = prim->next;
    }
}

void RicEntityCrashReboundStone(Entity* entity) {
    switch (entity->step) {
    case 0:
        entity->flags = FLAG_UNK_10000000;
        entity->step++;
        entity->ext.timer.t = 0x14;
        // fallthrough
    case 1:
        if (--entity->ext.timer.t) {
            break;
        }
    case 3:
    case 5:
        RicCreateEntFactoryFromEntity(entity, BP_57, 0);
        entity->step++;
    case 2:
    case 4:
    case 6:
        entity->ext.timer.t++;
        if (entity->ext.timer.t > 10) {
            entity->ext.timer.t = 0;
            entity->posX.val = FIX(128.0);
            entity->posY.val = 0;
            RicCreateEntFactoryFromEntity(entity, FACTORY(BP_EMBERS, 1), 0);
            entity->step++;
        }
        break;
    case 7:
        entity->ext.timer.t++;
        if (entity->ext.timer.t > 15) {
            DestroyEntity(entity);
            g_Ric.unk4E = 1;
            RicCreateEntFactoryFromEntity(
                entity, BP_CRASH_REBOUND_STONE_EXPLOSION, 0);
        }
        break;
    }
}

#define BIBLE_PAGE_COUNT 6
extern Point16 D_us_801D10D0[BIBLE_PAGE_COUNT];
extern u16 D_us_801D10E8;
extern EInit D_us_801804CC;

void RicEntityCrashBibleBeam(Entity* self) {
    Primitive* prim;
    s32 i;
    s32 var_s3;
    s32 colorAngle;
    s32 halfwidth;
    s32 hitboxOffX;
    s16 var_s7;

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_801804CC);
        self->ext.bibleBeam.subweaponId = PL_W_BIBLE_BEAM;
        D_us_801D10E8 = self->hitboxState;
        self->hitboxState = 0;
        self->primIndex = g_api.AllocPrimitives(PRIM_G4, BIBLE_PAGE_COUNT);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags |= FLAG_UNK_10000000 | FLAG_HAS_PRIMS;
        if (self->facingLeft) {
            self->ext.bibleBeam.unk7C = -16;
            self->ext.bibleBeam.unk7E = -2;
        } else {
            self->ext.bibleBeam.unk7C = 16;
            self->ext.bibleBeam.unk7E = 2;
        }
        prim = &g_PrimBuf[self->primIndex];
        for (i = 0; i < BIBLE_PAGE_COUNT; i++) {
            var_s3 = i + 2;
            if (var_s3 >= BIBLE_PAGE_COUNT) {
                var_s3 -= 6;
            }
            prim->x0 = prim->x1 = D_us_801D10D0[i].x;
            prim->y0 = prim->y1 = D_us_801D10D0[i].y;
            prim->x2 = prim->x3 = D_us_801D10D0[var_s3].x;
            prim->y2 = prim->y3 = D_us_801D10D0[var_s3].y;
            prim->priority = 0xC2;
            prim->drawMode = DRAW_DITHERING | DRAW_TPAGE2 | DRAW_TPAGE |
                             DRAW_COLORS | DRAW_TRANSP;
            prim = prim->next;
        }
        self->step = 1;
        break;
    case 1:
        self->ext.bibleBeam.unk80++;
        if (self->ext.bibleBeam.unk80 >= 0x3C) {
            g_api.PlaySfx(SFX_WEAPON_APPEAR);
            g_api.PlaySfx(SFX_TELEPORT_BANG_A);
            self->hitboxState = D_us_801D10E8;
            self->step++;
        }
        break;
    case 2:
        self->ext.bibleBeam.unk80++;
        self->ext.bibleBeam.unk7E += self->ext.bibleBeam.unk7C;
        var_s3 = D_us_801D10D0[1].x + self->ext.bibleBeam.unk7E;
        if (var_s3 < -0x50 || var_s3 > 0x150) {
            self->step++;
        }
        break;
    case 3:
        self->ext.bibleBeam.unk80++;
        if (self->ext.bibleBeam.unk80 >= 0x78) {
            DestroyEntity(self);
            return;
        }
        break;
    }
    prim = &g_PrimBuf[self->primIndex];
    var_s7 = 0;
    for (i = 0; i < BIBLE_PAGE_COUNT; i++) {
        var_s3 = i + 2;
        if (var_s3 >= BIBLE_PAGE_COUNT) {
            var_s3 -= 6;
        }
        colorAngle = i * 256;
        prim->r0 = prim->r1 = abs(
            (rsin((self->ext.bibleBeam.unk80 * 20) + colorAngle) * 96) >> 0xc);
        prim->g0 = prim->g1 = abs(
            (rsin((self->ext.bibleBeam.unk80 * 15) + colorAngle) * 96) >> 0xc);
        prim->b0 = prim->b1 = abs(
            (rsin((self->ext.bibleBeam.unk80 * 10) + colorAngle) * 96) >> 0xc);
        colorAngle = var_s3 * 256;
        prim->r2 = prim->r3 = abs(
            (rsin((self->ext.bibleBeam.unk80 * 15) + colorAngle) * 96) >> 0xc);
        prim->g2 = prim->g3 = abs(
            (rsin((self->ext.bibleBeam.unk80 * 10) + colorAngle) * 96) >> 0xc);
        prim->b2 = prim->b3 = abs(
            (rsin((self->ext.bibleBeam.unk80 * 20) + colorAngle) * 96) >> 0xc);
        prim->x1 = D_us_801D10D0[i].x;
        prim->y0 = prim->y1 = D_us_801D10D0[i].y;
        prim->x3 = D_us_801D10D0[var_s3].x;
        prim->y2 = prim->y3 = D_us_801D10D0[var_s3].y;
        prim->x0 = D_us_801D10D0[i].x + self->ext.bibleBeam.unk7E;
        prim->x2 = D_us_801D10D0[var_s3].x + self->ext.bibleBeam.unk7E;
        if (var_s7 < abs(D_us_801D10D0[i].y)) {
            var_s7 = abs(D_us_801D10D0[i].y);
        }
        prim = prim->next;
    }
    self->hitboxOffX = self->facingLeft ? -(self->ext.bibleBeam.unk7E / 2)
                                        : (self->ext.bibleBeam.unk7E / 2);
    self->hitboxWidth = abs(self->hitboxOffX);
    self->hitboxHeight = var_s7 - self->posY.i.hi;
}

extern s16 D_us_80182A1C[BIBLE_PAGE_COUNT];
extern s32 D_us_801D10EC;

void RicEntityCrashBible(Entity* self) {
    Primitive* prim;
    s32 i;
    s32 depth;
    s16 screenX;
    s16 screenY;
    s32 offsetX;
    s32 offsetY;
    s32 sp3C;
    s32 sp48;
    s32 sp40;
    long sp44;
    long sp4C;
    s32 halfWidth;
    s32 halfHeight;

    switch (self->step) {
    case 0:
        self->primIndex = g_api.AllocPrimitives(PRIM_GT4, 1 + BIBLE_PAGE_COUNT);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            g_Ric.unk4E = 1;
            return;
        }
        self->flags = FLAG_UNK_10000000 | FLAG_HAS_PRIMS;
        self->posX.val = RIC.posX.val;
        self->posY.val = RIC.posY.val;
        self->velocityY = FIX(-4);
        if (self->facingLeft) {
            self->velocityX = FIX(12);
            self->ext.et_8016E9E4.unk88 = FIX(1.5);
            self->ext.et_8016E9E4.unk7E = -0x200;
        } else {
            self->velocityX = FIX(-12);
            self->ext.et_8016E9E4.unk88 = FIX(-1.5);
            self->ext.et_8016E9E4.unk7E = 0x200;
        }
        prim = &g_PrimBuf[self->primIndex];
        prim->tpage = 0x1E;
        prim->clut = 0x17F;
        prim->u0 = prim->u2 = 0x98;
        prim->v0 = prim->v1 = 0xD8;
        prim->u1 = prim->u3 = 0xA8;
        prim->v2 = prim->v3 = 0xF0;
        prim->priority = 0xC2;
        prim->drawMode = DRAW_HIDE;
        prim = prim->next;
        for (i = 0; i < BIBLE_PAGE_COUNT; i++) {
            prim->tpage = 0x1C;
            prim->clut = PAL_UNK_1AE;
            prim->u0 = prim->u2 = 0x20;
            prim->u1 = prim->u3 = 0x30;
            prim->v0 = prim->v1 = 0;
            prim->v2 = prim->v3 = 0x10;
            prim->priority = 0xC1;
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }
        D_us_801D10EC = 0x60;
        self->ext.et_8016E9E4.unk84 = 0x40;
        self->step++;
        break;
    case 1:
        prim = &g_PrimBuf[self->primIndex];
        prim->drawMode &= ~DRAW_HIDE;
        self->step++;
    case 2:
        self->posX.val += self->velocityX;
        self->posY.val += self->velocityY;
        self->velocityX -= self->ext.et_8016E9E4.unk88;
        self->velocityY -= FIX(0.5);
        self->ext.et_8016E9E4.unk82++;
        if (self->ext.et_8016E9E4.unk82 >= 8) {
            self->ext.et_8016E9E4.unk82 = 0;
            self->step++;
        }
        break;
    case 3:
        self->ext.et_8016E9E4.unk82++;
        if (self->ext.et_8016E9E4.unk82 > 5) {
            prim = &g_PrimBuf[self->primIndex];
            prim->clut = PAL_UNK_19F;
            prim->drawMode |=
                DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS | DRAW_TRANSP;
            prim = prim->next;
            for (i = 0; i < BIBLE_PAGE_COUNT; i++) {
                prim->drawMode &= ~DRAW_HIDE;
                prim = prim->next;
            }
            self->ext.et_8016E9E4.unk82 = 0;
            self->step++;
        }
        break;
    case 4:
        self->ext.et_8016E9E4.unk84 -= 4;
        if (self->ext.et_8016E9E4.unk84 <= 0) {
            self->step++;
        }
        break;
    case 5:
        prim = &g_PrimBuf[self->primIndex];
        prim->drawMode |= DRAW_HIDE;
        self->step++;
    case 6:
        self->ext.et_8016E9E4.unk7C += 0x80;
        self->ext.et_8016E9E4.unk7C &= 0xFFF;
        self->ext.et_8016E9E4.unk80 += 4;
        if (self->ext.et_8016E9E4.unk80 >= 0x30) {
            self->step++;
        }
        break;
    case 7:
        self->ext.et_8016E9E4.unk7C += 0x80;
        self->ext.et_8016E9E4.unk7C &= 0xFFF;
        self->ext.et_8016E9E4.unk82++;
        if (self->ext.et_8016E9E4.unk82 >= 0x1E) {
            // create bible page beam
            RicCreateEntFactoryFromEntity(self, BP_CRASH_BIBLE_BEAM, 0);
            self->ext.et_8016E9E4.unk82 = 0;
            self->step++;
        }
        break;
    case 8:
        self->ext.et_8016E9E4.unk7C += 0x80;
        self->ext.et_8016E9E4.unk7C &= 0xFFF;
        self->ext.et_8016E9E4.unk82++;
        if (self->ext.et_8016E9E4.unk82 >= 0x60) {
            g_Ric.unk4E = 1;
            self->step++;
        }
        break;
    case 9:
        self->ext.et_8016E9E4.unk7C += 0x80;
        self->ext.et_8016E9E4.unk7C &= 0xFFF;
        self->ext.et_8016E9E4.unk80 -= 2;
        if (self->ext.et_8016E9E4.unk80 <= 0) {
            DestroyEntity(self);
            return;
        }
        break;
    }
    // FAKE, needed for reg match
    if (self->ext.et_8016E9E4.unk7C == 0x100 ||
        self->ext.et_8016E9E4.unk7C == 0x500 ||
        self->ext.et_8016E9E4.unk7C == 0x900 ||
        self->ext.et_8016E9E4.unk7C == 0xD00) {
        if (self->step < 9) {
            g_api.PlaySfxVolPan(SFX_ARROW_SHOT_A, D_us_801D10EC, 0);
            if (self->step >= 5) {
                D_us_801D10EC -= 4;
            }
            if (D_us_801D10EC < 0) {
                D_us_801D10EC = 0;
            }
        }
    }

    prim = &g_PrimBuf[self->primIndex];
    screenX = self->posX.i.hi;
    screenY = self->posY.i.hi;
    prim->x0 = prim->x2 = screenX - 8;
    prim->x1 = prim->x3 = screenX + 8;
    prim->y0 = prim->y1 = screenY - 12;
    prim->y2 = prim->y3 = screenY + 12;
    prim->r0 = prim->g0 = prim->b0 = prim->r1 = prim->g1 = prim->b1 = prim->r2 =
        prim->g2 = prim->b2 = prim->r3 = prim->g3 = prim->b3 =
            self->ext.et_8016E9E4.unk84;
    prim = prim->next;

    sp44 = rsin(self->ext.et_8016E9E4.unk7E);
    sp4C = rcos(self->ext.et_8016E9E4.unk7E);
    for (i = 0; i < BIBLE_PAGE_COUNT; i++) {
        sp3C = 0;
        sp48 = (rsin(self->ext.et_8016E9E4.unk7C + D_us_80182A1C[i]) *
                self->ext.et_8016E9E4.unk80) >>
               0xC;
        sp40 = (rcos(self->ext.et_8016E9E4.unk7C + D_us_80182A1C[i]) *
                self->ext.et_8016E9E4.unk80) >>
               0xC;
        offsetX = (sp4C * sp3C + sp44 * sp40) >> 0xC;
        depth = (sp4C * sp40 - sp44 * sp3C) >> 0xC;
        offsetY = sp48;
        depth += 0x200;
        offsetX = (offsetX * 512) / depth;
        offsetY = (offsetY * 512) / depth;
        screenX = self->posX.i.hi + offsetX;
        screenY = self->posY.i.hi + offsetY;
        D_us_801D10D0[i].x = screenX;
        D_us_801D10D0[i].y = screenY;
        halfWidth = 0x1000 / depth;
        halfHeight = 0x1000 / depth;
        prim->x0 = prim->x2 = screenX - halfWidth;
        prim->x1 = prim->x3 = screenX + halfWidth;
        prim->y0 = prim->y1 = screenY - halfHeight;
        prim->y2 = prim->y3 = screenY + halfHeight;
        prim = prim->next;
    }
}

void func_us_801C9DE8(Entity* self) {
    const int PrimCount = 16;
    const int MaxHeight = 240;
    const int HalfHeight = 120;

    Primitive* prim;
    s32 i;
    s32 tpage;
    s32 angleX;
    s32 angleY;
    s16 startMod;
    s16 endMod;
    s16 sx;
    s16 ex;
    s16 sy;
    s16 ey;

    switch (self->step) {
    case 0:
        self->primIndex = g_api.AllocPrimitives(PRIM_GT4, PrimCount);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            g_Ric.unk4E = 1;

            return;
        }
        self->flags = FLAG_UNK_10000000 | FLAG_HAS_PRIMS;
        prim = &g_PrimBuf[self->primIndex];
        for (i = 0; i < 16; i++) {
            prim->priority = 0xC2;
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }
        self->step++;
        break;
    case 1:
        prim = &g_PrimBuf[self->primIndex];
        for (i = 0; i < 16; i++) {
            prim->drawMode &= ~DRAW_HIDE;
            prim = prim->next;
        }
        self->step++;
    case 2:
        self->ext.factory.unk7C++;
        if (self->ext.factory.unk7C >= 0x18) {
            self->step++;
        }
        break;
    case 3:
        g_Ric.unk4E = 1;

        DestroyEntity(self);
        return;
    }
    if (!self->ext.factory.unk7C) {
        return;
    }
    if (g_CurrentBuffer == g_GpuBuffers

    ) {
        tpage = 0x104;
    } else {
        tpage = 0x100;
    }
    prim = &g_PrimBuf[self->primIndex];
    for (i = 0; i < PrimCount; i++) {
        angleX = rsin(i << 8);
        angleY = rcos(i << 8);
        startMod = self->ext.factory.unk7C * 8;
        endMod = 0;
        if (self->ext.factory.unk7C >= 4) {
            endMod = (self->ext.factory.unk7C - 4) * 8;
        }
        sx = ((angleY * startMod) >> 0xC) + 0x80;
        ex = ((angleY * endMod) >> 0xC) + 0x80;
        sy = ((angleX * startMod) >> 0xC) + HalfHeight;
        ey = ((angleX * endMod) >> 0xC) + HalfHeight;
        prim->x0 = sx = CLAMP(sx, 0, 0xFF);
        prim->x2 = ex = CLAMP(ex, 0, 0xFF);
        prim->y0 = sy = CLAMP(sy, 0, MaxHeight);
        prim->y2 = ey = CLAMP(ey, 0, MaxHeight);
        prim->u0 = 0xFF - prim->x0;
        prim->u2 = 0xFF - prim->x2;
        prim->v0 = MaxHeight - prim->y0;
        prim->v2 = MaxHeight - prim->y2;

        angleX = rsin((i + 1) << 8);
        angleY = rcos((i + 1) << 8);
        sx = ((angleY * startMod) >> 0xC) + 0x80;
        ex = ((angleY * endMod) >> 0xC) + 0x80;
        sy = ((angleX * startMod) >> 0xC) + HalfHeight;
        ey = ((angleX * endMod) >> 0xC) + HalfHeight;
        prim->x1 = sx = CLAMP(sx, 0, 0xFF);
        prim->x3 = ex = CLAMP(ex, 0, 0xFF);
        prim->y1 = sy = CLAMP(sy, 0, MaxHeight);
        prim->y3 = ey = CLAMP(ey, 0, MaxHeight);
        prim->u1 = 0xFF - prim->x1;
        prim->u3 = 0xFF - prim->x3;
        prim->v1 = MaxHeight - prim->y1;
        prim->v3 = MaxHeight - prim->y3;

        prim->tpage = tpage;
        prim = prim->next;
    }
}

void func_us_801CA340(Entity* self) {
    RicCreateEntFactoryFromEntity(self, FACTORY(0x3F, 1), 0);
    DestroyEntity(self);
}

s16 GetAguneaLightningAngle(s16* arg0, s16 arg1, s16 arg2, s16* arg3) {
    arg1 += rand() % 256 - 0x80;
    *arg3 = (rand() % 48) + 0x10;
    arg0[0] = arg0[1];
    arg0[2] = arg0[3];
    if (arg2) {
        arg0[1] += (rcos(arg1) * *arg3) >> 0xC;
        arg0[3] += (rsin(arg1) * *arg3) >> 0xC;
        if (arg2 % 2) {
            return GetAguneaLightningAngle(arg0, arg1 - 0x140, arg2 / 2, arg3);
        } else {
            rand();
            rand();
            return GetAguneaLightningAngle(
                arg0, arg1 + 0x140, (arg2 - 1) / 2, arg3);
        }
    }
    return arg1;
}

void AguneaShuffleParams(s32 bufSize, s32* buf) {
    s32 i, idx, swapTemp;

    for (i = bufSize - 1; i > 0; i--) {
        // Pick random index
        idx = rand() % bufSize;

        // Hold swap value temporarily
        swapTemp = buf[i];
        buf[i] = buf[idx];
        buf[idx] = swapTemp;
    }
}

void RicEntityAguneaLightning(Entity* self) {
    s16 sp20;
    s16 angle;
    s16 sp18;
    s32 randomSeed;
    s16 sp10[4];
    s16 xCoord;
    s16 yCoord;
    s16 startWidth;
    s16 endWidth;
    s32 cosAngle;
    s32 sinAngle;
    s32 i;
    Primitive* prim;

    switch (self->step) {
    case 0:
        self->primIndex = g_api.AllocPrimitives(PRIM_GT4, 0xF);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags =
            FLAG_UNK_10000000 | FLAG_HAS_PRIMS | FLAG_POS_CAMERA_LOCKED;
        prim = &g_PrimBuf[self->primIndex];
        for (i = 0; i < 15; i++) {
            prim->tpage = 0x1A;
            prim->clut = PAL_UNK_194;
            xCoord = (rand() % 5) * 0x10;
            prim->u0 = prim->u2 = xCoord + 0x90;
            prim->u1 = prim->u3 = xCoord + 0xB0;
            if (rand() % 2) {
                prim->v0 = prim->v1 = 0xD0;
                prim->v2 = prim->v3 = 0xE0;
            } else {
                prim->v0 = prim->v1 = 0xE0;
                prim->v2 = prim->v3 = 0xD0;
            }
            prim->r0 = prim->g0 = prim->b0 = prim->r1 = prim->g1 = prim->b1 =
                prim->r2 = prim->g2 = prim->b2 = prim->r3 = prim->g3 =
                    prim->b3 = 0x80;
            prim->priority = 0xC1;
            prim->drawMode = DRAW_HIDE | DRAW_COLORS | DRAW_UNK02;
            prim = prim->next;
        }
        prim = &g_PrimBuf[self->primIndex];
        sp20 = ((self->params & 0xFF00) >> 8) * 0x200;
        sp20 += rand() % 0x200 - 0x100;
        randomSeed = rand() & PSP_RANDMASK;
        for (i = 0; i < 15; i++) {
            srand(randomSeed);
            sp10[1] = self->posX.i.hi;
            sp10[3] = self->posY.i.hi;
            angle = GetAguneaLightningAngle(sp10, sp20, i, &sp18);
            xCoord = sp10[0];
            yCoord = sp10[2];
            startWidth = !i ? 2 : 8;
            endWidth = (i < 7) ? 8 : 2;

            cosAngle = rcos(angle);
            sinAngle = rsin(angle);
            prim->x0 = xCoord + (-(sinAngle * -startWidth) >> 0xC);
            prim->y0 = yCoord + ((cosAngle * -startWidth) >> 0xC);
            prim->x1 =
                xCoord + ((cosAngle * sp18 - (sinAngle * -endWidth)) >> 0xC);
            prim->y1 =
                yCoord + ((sinAngle * sp18 + (cosAngle * -endWidth)) >> 0xC);
            prim->x2 = xCoord + (-(sinAngle * startWidth) >> 0xC);
            prim->y2 = yCoord + ((cosAngle * startWidth) >> 0xC);
            prim->x3 =
                xCoord + ((cosAngle * sp18 - (sinAngle * endWidth)) >> 0xC);
            prim->y3 =
                yCoord + ((sinAngle * sp18 + (cosAngle * endWidth)) >> 0xC);
            prim = prim->next;
        }
        self->ext.et_8017091C.unk7E = 1;
        self->step++;
        break;
    case 1:
        prim = &g_PrimBuf[self->primIndex];
        for (i = 0; i < 15; i++) {
            prim->drawMode &= ~DRAW_HIDE;
            prim = prim->next;
        }
        self->step++;
    case 2:
        self->ext.et_8017091C.unk7C++;
        if (self->ext.et_8017091C.unk7C > 4) {
            prim = &g_PrimBuf[self->primIndex];
            for (i = 0; i < 15; i++) {
                prim->v0 = prim->v1 = prim->v0 - 0x10;
                prim->v2 = prim->v3 = prim->v2 - 0x10;
                prim->clut = PAL_FILL_WHITE;
                prim->r0 = prim->g0 = prim->b0 = prim->r1 = prim->g1 =
                    prim->b1 = prim->r2 = prim->g2 = prim->b2 = prim->r3 =
                        prim->g3 = prim->b3 = 0xFF;
                prim = prim->next;
            }
            self->ext.et_8017091C.unk7C = 0;
            self->step++;
        }
        break;
    case 3:
    case 5:
        prim = &g_PrimBuf[self->primIndex];
        for (i = 0; i < 15; i++) {
            prim->clut = PAL_UNK_194;
            prim = prim->next;
        }
        self->step++;
        break;
    case 4:
        prim = &g_PrimBuf[self->primIndex];
        for (i = 0; i < 15; i++) {
            prim->clut = PAL_FILL_WHITE;
            prim = prim->next;
        }
        self->step++;
        break;
    case 6:
        prim = &g_PrimBuf[self->primIndex];
        for (i = 0; i < 15; i++) {
            prim->r0 = prim->g0 = prim->b0 = prim->r1 = prim->g1 = prim->b1 =
                prim->r2 = prim->g2 = prim->b2 = prim->r3 = prim->g3 =
                    prim->b3 = 0x60 - (self->ext.et_8017091C.unk7C * 4);
            prim = prim->next;
        }
        self->ext.et_8017091C.unk7C++;
        if (self->ext.et_8017091C.unk7C > 15) {
            DestroyEntity(self);
            return;
        }
        break;
    }
}

#define LIGHTNING_COUNT 8
extern s32 D_us_801D10F0[LIGHTNING_COUNT];
extern EInit D_us_801804C0;

void RicEntityAguneaCircle(Entity* self) {
    Primitive* prim;
    s16 randAngle;
    s16 xCoord;
    s16 yCoord;
    s32 quarterSelfY;
    s32 i;
    s16 texOffset;

    switch (self->step) {
    case 0:
        self->primIndex = g_api.AllocPrimitives(PRIM_GT4, 4);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            g_Ric.unk4E = 1;
            return;
        }
        InitializeEntity(D_us_801804C0);
        self->ext.aguneaCrash.subweaponId = PL_W_CRASH_AGUNEA;
        self->flags |= FLAG_UNK_10000000 | FLAG_HAS_PRIMS;
        self->posY.i.hi -= 0x20;
        prim = &g_PrimBuf[self->primIndex];
        quarterSelfY = self->posY.i.hi / 4;
        xCoord = self->posX.i.hi;
        yCoord = 0;
        for (i = 0; i < 4; i++) {
            prim->tpage = 0x1A;
            prim->clut = PAL_UNK_194;
            prim->x0 = xCoord - 8;
            prim->x2 = xCoord + 8;
            prim->y0 = prim->y2 = yCoord;
            if (i < 3) {
                randAngle = rand() % 0x100 + 0x380;
                xCoord += ((rcos(randAngle) * quarterSelfY) >> 0xC);
                yCoord += ((rsin(randAngle) * quarterSelfY) >> 0xC);
                prim->x1 = xCoord - 8;
                prim->x3 = xCoord + 8;
            } else {
                xCoord = self->posX.i.hi;
                yCoord = self->posY.i.hi;
                prim->x1 = xCoord - 4;
                prim->x3 = xCoord + 4;
            }
            prim->y1 = prim->y3 = yCoord;
            texOffset = (rand() % 6) * 0x10;
            prim->u0 = prim->u2 = texOffset + 0x90;
            prim->u1 = prim->u3 = texOffset + 0xA0;
            if (rand() % 2) {
                prim->v0 = prim->v1 = 0xD0;
                prim->v2 = prim->v3 = 0xE0;
            } else {
                prim->v0 = prim->v1 = 0xE0;
                prim->v2 = prim->v3 = 0xD0;
            }
            prim->priority = 0xC2;
            prim->drawMode = DRAW_HIDE | DRAW_UNK02;
            prim = prim->next;
        }
        self->step = 1;
        break;
    case 1:
        prim = &g_PrimBuf[self->primIndex];
        for (i = 0; i < self->ext.aguneaCrash.unk7C; i++) {
            prim = prim->next;
        }
        prim->drawMode &= ~DRAW_HIDE;
        self->ext.aguneaCrash.unk7C++;
        if (self->ext.aguneaCrash.unk7C >= 4) {
            self->ext.aguneaCrash.unk7C = 0;
            self->step++;
        }
        break;
    case 2:
        prim = &g_PrimBuf[self->primIndex];
        for (i = 0; i < self->ext.aguneaCrash.unk7C; i++) {
            prim = prim->next;
        }
        if (!self->ext.aguneaCrash.unk7C) {
            prim->drawMode = DRAW_UNK02 | DRAW_TPAGE2 | DRAW_TPAGE |
                             DRAW_COLORS | DRAW_TRANSP;
            prim->tpage = 0x1A;
            prim->clut = PAL_UNK_19F;
            prim->u0 = prim->u2 = 0;
            prim->u1 = prim->u3 = 0x3F;
            prim->v0 = prim->v1 = 0xC0;
            prim->v2 = prim->v3 = 0xFF;
            prim->r0 = prim->g0 = prim->r1 = prim->g1 = prim->r2 = prim->g2 =
                prim->r3 = prim->g3 = 0x7F;
            prim->b0 = prim->b1 = prim->b2 = prim->b3 = 0xFF;
            self->ext.aguneaCrash.unk7E = 1;
            self->ext.aguneaCrash.unk80 = 2;
            self->ext.aguneaCrash.unk82 = 0x64;
        } else {
            self->ext.aguneaCrash.unk80 += 2;
            prim->drawMode |= DRAW_HIDE;
        }
        self->ext.aguneaCrash.unk7C++;
        if (self->ext.aguneaCrash.unk7C > 3) {
            for (i = 0; i < LIGHTNING_COUNT; i++) {
                D_us_801D10F0[i] = i;
            }
            AguneaShuffleParams(LIGHTNING_COUNT, &D_us_801D10F0[0]);
            self->ext.aguneaCrash.unk7C = 0;
            g_api.PlaySfx(SFX_THUNDER_B);
            self->step++;
        }
        break;
    case 3:
        RicCreateEntFactoryFromEntity(
            self,
            FACTORY(BP_CRASH_AGUNEA_THUNDER,
                    D_us_801D10F0[self->ext.aguneaCrash.unk7C]),
            0);
        self->ext.aguneaCrash.unk7C++;
        if (self->ext.aguneaCrash.unk7C > LIGHTNING_COUNT - 1) {
            self->hitboxWidth = 0x80;
            self->hitboxHeight = 0x80;
            self->ext.aguneaCrash.unk7C = 0;
            self->step++;
        }
        break;
    case 4:
        self->ext.aguneaCrash.unk7C++;
        if (self->ext.aguneaCrash.unk7C > LIGHTNING_COUNT) {
            self->step++;
        }
        break;
    case 5:
        self->ext.aguneaCrash.unk80 += 2;
        self->ext.aguneaCrash.unk82 -= 10;
        if (self->ext.aguneaCrash.unk82 <= 0) {
            self->hitboxWidth = 0;
            self->hitboxHeight = 0;
            self->step++;
        }
        break;
    case 6:
        g_Ric.unk4E = 1;
        DestroyEntity(self);
        return;
    }
    if (self->ext.aguneaCrash.unk7E) {
        prim = &g_PrimBuf[self->primIndex];
        prim->x0 = prim->x2 = self->posX.i.hi - self->ext.aguneaCrash.unk80;
        prim->x1 = prim->x3 = self->posX.i.hi + self->ext.aguneaCrash.unk80;
        prim->y0 = prim->y1 = self->posY.i.hi - self->ext.aguneaCrash.unk80;
        prim->y2 = prim->y3 = self->posY.i.hi + self->ext.aguneaCrash.unk80;
        prim->r0 = prim->g0 = prim->r1 = prim->g1 = prim->r2 = prim->g2 =
            prim->r3 = prim->g3 = (self->ext.aguneaCrash.unk82 * 0x7F) / 100;
        prim->b0 = prim->b1 = prim->b2 = prim->b3 =
            (self->ext.aguneaCrash.unk82 * 0xFF) / 100;
    }
}

void RicEntitySubwpnStopwatchCircle(Entity* self) {
    s16 innerRadius;
    s16 angle;
    s32 sine;
    s32 cosine;
    s16 xCoord;
    s16 yCoord;
    Primitive* prim;
    s32 i;

    switch (self->step) {
    case 0:
        self->primIndex = g_api.AllocPrimitives(PRIM_GT4, 0x10);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags = FLAG_POS_CAMERA_LOCKED | FLAG_HAS_PRIMS;
        prim = &g_PrimBuf[self->primIndex];
        for (i = 0; i < 16; i++) {
            prim->tpage = 0x1A;
            prim->clut = PAL_FILL_WHITE;
            prim->priority = self->zPriority = 0xC2;
            prim->drawMode = DRAW_DITHERING | DRAW_TPAGE2 | DRAW_TPAGE |
                             DRAW_COLORS | DRAW_TRANSP;
            angle = i * 0x100;
            prim->u0 = ((rsin(angle) << 5) >> 0xC) + 0x20;
            prim->v0 = -((rcos(angle) << 5) >> 0xC) + 0xDF;
            angle = (i + 1) * 0x100;
            prim->u1 = ((rsin(angle) << 5) >> 0xC) + 0x20;
            prim->v1 = -((rcos(angle) << 5) >> 0xC) + 0xDF;
            prim->u2 = prim->u3 = 0x20;
            prim->v2 = prim->v3 = 0xE0;
            prim->r0 = prim->r1 = prim->g0 = prim->g1 = prim->b0 = prim->b1 =
                0x40;
            prim->r2 = prim->r3 = prim->g2 = prim->g3 = 0;
            prim->b2 = prim->b3 = 0x20;
            prim = prim->next;
        }
        self->ext.et_stopwatchCircle.size = 0x20;
        self->step++;
        break;
    case 1:
        self->ext.et_stopwatchCircle.size += 0x18;
        self->ext.et_stopwatchCircle.timer++;
        if (self->ext.et_stopwatchCircle.timer > 0x1E) {
            DestroyEntity(self);
            return;
        }
    }
    xCoord = self->posX.i.hi;
    yCoord = self->posY.i.hi;
    prim = &g_PrimBuf[self->primIndex];
    for (i = 0; i < 16; i++) {
        sine = rsin(i * 0x100);
        cosine = rcos(i * 0x100);
        innerRadius = self->ext.et_stopwatchCircle.size - 0x20;
        prim->x0 = xCoord + ((sine * self->ext.et_stopwatchCircle.size) >> 0xC);
        prim->y0 =
            yCoord - ((cosine * self->ext.et_stopwatchCircle.size) >> 0xC);
        prim->x2 = xCoord + ((sine * (innerRadius)) >> 0xC);
        prim->y2 = yCoord - ((cosine * innerRadius) >> 0xC);
        sine = rsin((i + 1) * 0x100);
        cosine = rcos((i + 1) * 0x100);
        prim->x1 = xCoord + ((sine * self->ext.et_stopwatchCircle.size) >> 0xC);
        prim->y1 =
            yCoord - ((cosine * self->ext.et_stopwatchCircle.size) >> 0xC);
        prim->x3 = xCoord + ((sine * innerRadius) >> 0xC);
        prim->y3 = yCoord - ((cosine * innerRadius) >> 0xC);
        prim = prim->next;
    }
}

void EntityStopWatch(Entity* self) {
    s32 var_s7;
    s32 c;
    s32 d;
    s16 offsetX, offsetY;
    s32 y;
    s32 x;
    Primitive* prim;

    if (g_unkGraphicsStruct.pauseEnemies) {
        g_unkGraphicsStruct.D_800973FC = 0;
        if (self->step && (self->step < 4)) {
            self->step = 4;
        }
    }

    switch (self->step) {
    case 0:
        self->primIndex = g_api.AllocPrimitives(PRIM_GT4, 3);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags =
            FLAG_POS_CAMERA_LOCKED | FLAG_UNK_10000000 | FLAG_HAS_PRIMS;
        prim = &g_PrimBuf[self->primIndex];
        prim->tpage = 0x1E;
        prim->clut = 0x17F;
        prim->v0 = prim->v1 = 0xC0;
        prim->v2 = prim->v3 = 0xD8;
        if (self->facingLeft) {
            prim->u0 = prim->u2 = 0x98;
            prim->u1 = prim->u3 = 0xA8;
        } else {
            prim->u0 = prim->u2 = 0xA8;
            prim->u1 = prim->u3 = 0x98;
        }
        prim->priority = RIC.zPriority + 1;
        prim->drawMode = DRAW_UNK_200 | DRAW_UNK_100 | DRAW_HIDE | DRAW_UNK02;

        prim = prim->next;
        prim->tpage = 0x1A;
        prim->clut = 0x186;
        prim->priority = RIC.zPriority + 3;
        prim->drawMode = DRAW_UNK_200 | DRAW_UNK_100 | DRAW_HIDE | DRAW_UNK02;

        prim = prim->next;
        prim->tpage = 0x1A;
        prim->clut = 0x186;
        prim->priority = RIC.zPriority + 3;
        prim->drawMode = DRAW_UNK_200 | DRAW_UNK_100 | DRAW_HIDE | DRAW_UNK02;

        if (self->params & 0xFF00) {
            RicCreateEntFactoryFromEntity(self, BP_66, 0);
        } else {
            RicCreateEntFactoryFromEntity(self, BP_STOPWATCH_CIRCLE, 0);
        }
        g_api.PlaySfx(SFX_UI_ALERT_TINK);
        g_unkGraphicsStruct.D_800973FC = 1;
        self->step++;
        break;
    case 1:
        prim = &g_PrimBuf[self->primIndex];
        prim->drawMode &= ~DRAW_HIDE;

        self->ext.stopwatch.unk84.val += FIX(1.5);
        if (self->ext.stopwatch.unk84.val >= FIX(26)) {
            self->step++;
        }
        break;
    case 2:
        self->ext.stopwatch.unk84.val -= FIX(1);
        if (self->ext.stopwatch.unk84.val <= FIX(16)) {
            self->ext.stopwatch.t = 12;
            g_api.PlaySfx(SFX_STOPWATCH_TICK);
            self->step++;
        }
        break;
    case 3:
        self->ext.stopwatch.unk7E += 1;
        if (self->ext.stopwatch.unk7E > 80) {
            g_api.PlaySfx(SFX_STOPWATCH_TICK);
            self->ext.stopwatch.unk7E = 0;
            self->ext.stopwatch.unk8C = 1;
            self->ext.stopwatch.t -= 1;
            if (self->ext.stopwatch.t < 0) {
                self->step++;
                break;
            }
        }
        if (self->ext.stopwatch.t < 12) {
            prim = &g_PrimBuf[self->primIndex];
            prim = prim->next;
            if (self->ext.stopwatch.t >= 10) {
                self->ext.stopwatch.unk8E = 1;
                x = (self->ext.stopwatch.t / 10) * 8;
                prim->u0 = prim->u2 = x + 0x18;
                prim->v0 = prim->v1 = 0x40;
                prim->u1 = prim->u3 = x + 0x1E;
                prim->v2 = prim->v3 = 0x49;
                prim->drawMode &= ~DRAW_HIDE;
                prim = prim->next;
            } else {
                self->ext.stopwatch.unk8E = 0;
            }
            x = (self->ext.stopwatch.t % 10) * 8;
            if (x == 0) {
                x = 0x50;
            }
            prim->u0 = prim->u2 = x + 0x18;
            prim->v0 = prim->v1 = 0x40;
            prim->u1 = prim->u3 = x + 0x1E;
            prim->v2 = prim->v3 = 0x49;
            prim->drawMode &= ~DRAW_HIDE;
        }
        break;
    case 4:
        // The original preserves this redundant flags store.
        self->flags = self->flags;
        prim = &g_PrimBuf[self->primIndex];
        prim->priority = 0xC2;
        prim->drawMode &= ~DRAW_UNK_200;
        prim = prim->next;
        prim->drawMode |= DRAW_HIDE;
        prim = prim->next;
        prim->drawMode |= DRAW_HIDE;

        self->posX.i.hi += self->facingLeft ? 6 : -6;
        self->posY.i.hi -= self->ext.stopwatch.unk84.val >> 0x10;
        self->ext.stopwatch.t = 0;
        self->step++;
        break;
    case 5:
        self->ext.stopwatch.t += 1;
        if (self->ext.stopwatch.t >= 4) {
            prim = &g_PrimBuf[self->primIndex];
            prim->clut = PAL_FILL_WHITE;
            prim->drawMode |= DRAW_COLORS;
            PRED(prim) = 0x40;
            PGRN(prim) = 0x40;
            PBLU(prim) = 0x60;

            g_api.PlaySfx(SFX_UI_SUBWEAPON_TINK);
            self->step++;
        }
        break;
    case 6:
        self->ext.stopwatch.t += 1;
        if (self->ext.stopwatch.t > 14) {
            RicCreateEntFactoryFromEntity(self, FACTORY(BP_EMBERS, 7), 0);
            self->step++;
        }
        break;
    case 7:
        g_unkGraphicsStruct.D_800973FC = 0;
        DestroyEntity(self);
        return;
    }

    if (self->step) {
        prim = &g_PrimBuf[self->primIndex];
        if (self->step < 5) {
            x = RIC.posX.val + (RIC.facingLeft ? FIX(8) : FIX(-8));
            if (RIC.hitboxOffY == 0 && RIC.hitboxHeight == 0) {
                y = RIC.posY.val - FIX(16);
            } else {
                y = RIC.posY.val - (RIC.hitboxHeight - RIC.hitboxOffY) * FIX(1);
            }
            self->posX.val += (x - self->posX.val) / 12;
            self->posY.val += (y - self->posY.val) / 4;

            if (RIC.facingLeft != self->facingLeft) {
                if (abs(x - self->posX.val) < FIX(1)) {
                    self->facingLeft = RIC.facingLeft;
                } else if (!self->facingLeft && (self->posX.val > x)) {
                    self->facingLeft = RIC.facingLeft;
                } else if (self->facingLeft && (self->posX.val < x)) {
                    self->facingLeft = RIC.facingLeft;
                }
            }
            if (self->facingLeft) {
                prim->u0 = prim->u2 = 0x98;
                prim->u1 = prim->u3 = 0xA8;
            } else {
                prim->u0 = prim->u2 = 0xA8;
                prim->u1 = prim->u3 = 0x98;
            }
        }

        if (self->step < 3) {
            x = (self->facingLeft ? 6 : -6) + self->posX.i.hi;
            y = self->posY.i.hi - (self->ext.stopwatch.unk84.val >> 0x10);
            if (self->ext.stopwatch.unk82 < 100) {
                self->ext.stopwatch.unk82 += 4;
            }
            if (self->ext.stopwatch.unk80 < 0x1000) {
                self->ext.stopwatch.unk80 += 0x80;
            }

            offsetX = (self->ext.stopwatch.unk82 * 8) / 100;
            offsetY = (self->ext.stopwatch.unk82 * 12) / 100;
            c = rsin(self->ext.stopwatch.unk80);
            d = rcos(self->ext.stopwatch.unk80);
            prim->x0 = (x + (((d * -offsetX) - (c * -offsetY)) >> 0xC));
            prim->y0 = (y + (((c * -offsetX) + (d * -offsetY)) >> 0xC));
            prim->x1 = (x + (((d * offsetX) - (c * -offsetY)) >> 0xC));
            prim->y1 = (y + (((c * offsetX) + (d * -offsetY)) >> 0xC));
            prim->x2 = (x + (((d * -offsetX) - (c * offsetY)) >> 0xC));
            prim->y2 = (y + (((c * -offsetX) + (d * offsetY)) >> 0xC));
            prim->x3 = (x + (((d * offsetX) - (c * offsetY)) >> 0xC));
            prim->y3 = (y + (((c * offsetX) + (d * offsetY)) >> 0xC));
        } else if (self->step < 5) {
            if (self->ext.stopwatch.unk84.val <= FIX(16)) {
                if (self->ext.stopwatch.unk8C) {
                    self->ext.stopwatch.unk88.val =
                        ((rand() % 64) + 0x200) << 8;
                    self->ext.stopwatch.unk8C = 0;
                } else {
                    self->ext.stopwatch.unk88.val =
                        ((rand() % 128) + 0x100) << 8;
                }
                if (self->ext.stopwatch.unk80 >= 0) {
                    self->ext.stopwatch.unk80 = -((rand() % 64) + 0x40);
                } else {
                    self->ext.stopwatch.unk80 = (rand() % 64) + 0x40;
                }
            }
            self->ext.stopwatch.unk84.val += self->ext.stopwatch.unk88.val;
            self->ext.stopwatch.unk88.val -= FIX(0.25);

            x = (self->facingLeft ? 6 : -6) + self->posX.i.hi;
            y = self->posY.i.hi - (self->ext.stopwatch.unk84.val >> 0x10);

            c = rsin(self->ext.stopwatch.unk80);
            d = rcos(self->ext.stopwatch.unk80);
            prim->x0 = (x + (((d * -8) - (c * -0xC)) >> 0xC));
            prim->y0 = (y + (((c * -8) + (d * -0xC)) >> 0xC));
            prim->x1 = (x + (((d * 8) - (c * -0xC)) >> 0xC));
            prim->y1 = (y + (((c * 8) + (d * -0xC)) >> 0xC));
            prim->x2 = (x + (((d * -8) - (c * 0xC)) >> 0xC));
            prim->y2 = (y + (((c * -8) + (d * 0xC)) >> 0xC));
            prim->x3 = (x + (((d * 8) - (c * 0xC)) >> 0xC));
            prim->y3 = (y + (((c * 8) + (d * 0xC)) >> 0xC));
        } else {
            offsetX = 8 - self->ext.stopwatch.t;
            if (offsetX < 1) {
                offsetX = 1;
            }
            offsetY = (self->ext.stopwatch.t * 32) + 12;
            if (offsetY >= 0x80) {
                offsetY = 0x80;
            }

            prim->x0 = prim->x2 = self->posX.i.hi - offsetX;
            prim->x1 = prim->x3 = self->posX.i.hi + offsetX;
            prim->y0 = prim->y1 = self->posY.i.hi - offsetY;
            prim->y2 = prim->y3 = self->posY.i.hi + offsetY;
        }
        if (self->step < 4) {
            y = self->posY.i.hi - 14;
            if (self->ext.stopwatch.unk8E) {
                x = self->posX.i.hi - (self->facingLeft ? 10 : -4);

                prim = prim->next;
                if (self->ext.stopwatch.unk7E < 8) {
                    prim->x0 = prim->x2 = x - self->ext.stopwatch.unk7E / 2;
                    prim->x1 = prim->x3 = x + self->ext.stopwatch.unk7E / 2;
                    prim->y0 = prim->y1 =
                        (y - 8) - (7 - self->ext.stopwatch.unk7E);
                    prim->y2 = prim->y3 =
                        (y + 8) + (7 - self->ext.stopwatch.unk7E);
                } else if (self->ext.stopwatch.unk7E >= 0x44) {
                    offsetX = (0x50 - (self->ext.stopwatch.unk7E + 4)) / 2;
                    if (offsetX < 0) {
                        offsetX = 0;
                    }
                    offsetY = self->ext.stopwatch.unk7E - 0x44;
                    if (offsetY > 8) {
                        offsetY = 8;
                    }

                    prim->x0 = prim->x2 = x - offsetX;
                    prim->x1 = prim->x3 = x + offsetX;
                    prim->y0 = prim->y1 = (y - 8) - offsetY;
                    prim->y2 = prim->y3 = (y + 8) + offsetY;
                } else {
                    prim->x0 = prim->x2 = x - 4;
                    prim->x1 = prim->x3 = x + 4;
                    prim->y0 = prim->y1 = y - 8;
                    prim->y2 = prim->y3 = y + 8;
                }

                x = self->posX.i.hi - (self->facingLeft ? 4 : -10);
                prim = prim->next;
                if (self->ext.stopwatch.unk7E < 0xC) {
                    offsetX = (self->ext.stopwatch.unk7E - 4) / 2;
                    if (offsetX < 0) {
                        offsetX = 0;
                    }
                    offsetY = 7 - (self->ext.stopwatch.unk7E - 4);
                    if (offsetY < 0) {
                        offsetY = 0;
                    }

                    prim->x0 = prim->x2 = x - offsetX;
                    prim->x1 = prim->x3 = x + offsetX;
                    prim->y0 = prim->y1 = (y - 8) - offsetY;
                    prim->y2 = prim->y3 = (y + 8) + offsetY;
                    return;
                }
                if (self->ext.stopwatch.unk7E >= 0x48) {
                    prim->x0 = prim->x2 =
                        x - ((0x50 - self->ext.stopwatch.unk7E) / 2);
                    prim->x1 = prim->x3 =
                        x + ((0x50 - self->ext.stopwatch.unk7E) / 2);
                    prim->y0 = prim->y1 =
                        (y - 8) - (self->ext.stopwatch.unk7E - 0x48);
                    prim->y2 = prim->y3 =
                        (y + 8) + (self->ext.stopwatch.unk7E - 0x48);
                    return;
                }
                prim->x0 = prim->x2 = x - 4;
                prim->x1 = prim->x3 = x + 4;
                prim->y0 = prim->y1 = y - 8;
                prim->y2 = prim->y3 = y + 8;
                return;
            }

            x = self->posX.i.hi - (self->facingLeft ? 4 : -4);
            prim = prim->next;
            if (self->ext.stopwatch.unk7E < 8) {
                prim->x0 = prim->x2 = x - (self->ext.stopwatch.unk7E / 2);
                prim->x1 = prim->x3 = x + (self->ext.stopwatch.unk7E / 2);
                prim->y0 = prim->y1 = (y - 8) - (7 - self->ext.stopwatch.unk7E);
                prim->y2 = prim->y3 = (y + 8) + (7 - self->ext.stopwatch.unk7E);
                return;
            }
            if (self->ext.stopwatch.unk7E >= 0x48) {
                prim->x0 = prim->x2 =
                    x - ((0x50 - self->ext.stopwatch.unk7E) / 2);
                prim->x1 = prim->x3 =
                    x + ((0x50 - self->ext.stopwatch.unk7E) / 2);
                prim->y0 = prim->y1 =
                    (y - 8) - (self->ext.stopwatch.unk7E - 0x48);
                prim->y2 = prim->y3 =
                    (y + 8) + (self->ext.stopwatch.unk7E - 0x48);
                return;
            }
            prim->x0 = prim->x2 = x - 5;
            prim->x1 = prim->x3 = x + 5;
            prim->y0 = prim->y1 = y - 8;
            prim->y2 = prim->y3 = y + 8;
        }
    }
}

void RicEntitySubwpnBibleTrail(Entity* entity) {
    Primitive* prim;

    switch (entity->step) {
    case 0:
        entity->primIndex = g_api.AllocPrimitives(PRIM_GT4, 1);
        if (entity->primIndex == -1) {
            DestroyEntity(entity);
            return;
        }
        entity->flags = FLAG_UNK_10000000 | FLAG_HAS_PRIMS;
        prim = &g_PrimBuf[entity->primIndex];
        prim->tpage = 0x1C;
        prim->clut = 0x19D;
        prim->u0 = prim->u2 = 0x20;
        prim->v0 = prim->v1 = 0;
        prim->u1 = prim->u3 = 0x30;
        prim->v2 = prim->v3 = 0x10;
        prim->x0 = prim->x2 = entity->posX.i.hi - 8;
        prim->x1 = prim->x3 = entity->posX.i.hi + 8;
        prim->y0 = prim->y1 = entity->posY.i.hi - 8;
        prim->y2 = prim->y3 = entity->posY.i.hi + 8;
        prim->priority = entity->zPriority;
        prim->drawMode = DRAW_TPAGE | DRAW_COLORS | DRAW_TRANSP;
        entity->ext.et_BibleSubwpn.unk7E = 0x60;
        entity->step++;
        break;
    case 1:
        entity->ext.et_BibleSubwpn.unk7C++;
        if (entity->ext.et_BibleSubwpn.unk7C > 5) {
            entity->step++;
        }
        entity->ext.et_BibleSubwpn.unk7E -= 8;
        break;
    case 2:
        DestroyEntity(entity);
        return;
    }
    prim = &g_PrimBuf[entity->primIndex];
    PCOL(prim) = entity->ext.et_BibleSubwpn.unk7E;
}

void RicEntitySubwpnBible(Entity* self) {
    Primitive* prim;
    s32 sp48;
    s32 sp44;
    s32 sp40;
    s16 selfX;
    s16 selfY;
    s32 sp3C;
    s32 unused;
    s32 offsetX;
    s32 offsetY;
    s32 rotatedX;
    s32 rotatedZ;
    s32 rotatedY;
    s32 sinAngle;
    s32 cosAngle;

// The original PS1 orbit calculation reads this local before assigning it.
#ifdef FIX_UB
    rotatedZ = 0;
#endif
    switch (self->step) {
    case 0:
        self->primIndex = g_api.AllocPrimitives(PRIM_GT4, 1);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags = FLAG_UNK_10000000 | FLAG_HAS_PRIMS;
        prim = &g_PrimBuf[self->primIndex];
        prim->tpage = 0x1E;
        prim->clut = 0x17F;
        prim->u0 = prim->u2 = 0x98;
        prim->v0 = prim->v1 = 0xD8;
        prim->u1 = prim->u3 = 0xA8;
        prim->v2 = prim->v3 = 0xF0;
        prim->priority = RIC.zPriority + 1;
        prim->drawMode = DRAW_HIDE;
        if (self->facingLeft) {
            sp44 = 0x20;
        } else {
            sp44 = -0x20;
        }
        self->ext.et_BibleSubwpn.unk84 = sp44;
        self->hitboxWidth = 6;
        self->hitboxHeight = 6;
        self->step++;
        break;
    case 1:
        prim = &g_PrimBuf[self->primIndex];
        prim->drawMode &= ~DRAW_HIDE;
        self->ext.et_BibleSubwpn.unk86++;
        self->step++;
    case 2:
        self->ext.et_BibleSubwpn.unk7C++;
        self->ext.et_BibleSubwpn.unk7E++;
        if (self->ext.et_BibleSubwpn.unk7E >= 0x30) {
            self->step++;
        }
        break;
    case 3:
        self->ext.et_BibleSubwpn.unk7C++;
        if (self->ext.et_BibleSubwpn.unk7C >= 0x12C) {
            self->flags &= ~FLAG_UNK_10000000;
            if (self->facingLeft) {
                sp40 = FIX(-12);
            } else {
                sp40 = FIX(12);
            }
            self->velocityX = sp40;
            self->velocityY = FIX(-12);
            self->ext.et_BibleSubwpn.unk86++;
            self->step++;
        }
        break;
    }
    switch (self->ext.et_BibleSubwpn.unk86) {
    case 0:
        break;
    case 1:
        sinAngle = rsin(self->ext.et_BibleSubwpn.unk80);
        cosAngle = rcos(self->ext.et_BibleSubwpn.unk80);
        rotatedX = (sinAngle * self->ext.et_BibleSubwpn.unk7E) >> 0xC;
        rotatedY = (cosAngle * self->ext.et_BibleSubwpn.unk7E) >> 0xC;
        offsetX = (cosAngle * rotatedX + sinAngle * rotatedY);
        sp48 = (cosAngle * rotatedY - sinAngle * rotatedX);
        rotatedX = offsetX >> 0xC;
        rotatedY = sp48 >> 0xC;
        sinAngle = rsin(self->ext.et_BibleSubwpn.unk82);
        cosAngle = rcos(self->ext.et_BibleSubwpn.unk82);
        offsetX = ((cosAngle * rotatedX) + (sinAngle * rotatedZ)) >> 0xC;
        offsetY = ((cosAngle * rotatedZ) - (sinAngle * rotatedX)) >> 0xC;
        rotatedZ = offsetY;
        if (self->facingLeft) {
            offsetY = ((cosAngle * rotatedZ) + (sinAngle * rotatedY)) >> 0xC;
        } else {
            offsetY = ((cosAngle * rotatedZ) - (sinAngle * rotatedY)) >> 0xC;
        }
        self->ext.et_BibleSubwpn.unk80 += self->facingLeft ? 0x80 : -0x80;
        self->ext.et_BibleSubwpn.unk80 &= 0xFFF;
        self->ext.et_BibleSubwpn.unk82 += self->ext.et_BibleSubwpn.unk84;
        if (abs(self->ext.et_BibleSubwpn.unk82) >= 0x200) {
            self->ext.et_BibleSubwpn.unk84 *= -1;
        }
        self->posX.i.hi = RIC.posX.i.hi + offsetX;
        self->posY.i.hi = RIC.posY.i.hi + offsetY;
        self->zPriority = RIC.zPriority + (rotatedY < 0 ? 2 : -2);
        break;
    case 2:
        self->posX.val += self->velocityX;
        self->posY.val += self->velocityY;
        self->velocityY -= FIX(2);
        break;
    }
    if (self->ext.et_BibleSubwpn.unk86) {
        selfX = self->posX.i.hi;
        selfY = self->posY.i.hi;
        prim = &g_PrimBuf[self->primIndex];
        prim->x0 = prim->x2 = selfX - 8;
        prim->x1 = prim->x3 = selfX + 8;
        prim->y0 = prim->y1 = selfY - 12;
        prim->y2 = prim->y3 = selfY + 12;
        prim->priority = self->zPriority;
        RicCreateEntFactoryFromEntity(self, BP_BIBLE_TRAIL, 0);
        if (g_GameTimer % 10 == 0) {
            g_api.PlaySfx(SFX_WEAPON_SWISH_C);
        }
    }
}

extern EInit D_us_801804A8;
extern u8 D_us_80182E88[46][5];
extern SVECTOR* D_us_80182BA8[][4];

void RicEntityCrashCrossBeam(Entity* self) {
    MATRIX m;
    SVECTOR rot;
    VECTOR trans1;
    SVECTOR pos = {0, 0, 0};
    SVECTOR sp50 = {-96, 0, 0};
    s32 z;
    s32 nclip;
    Primitive* prim;
    s32 temp_v1;
    s32 i;
    u8* primUVCoords;
    SVECTOR** vectors;
    SVECTOR* vertex0;
    SVECTOR* vertex1;
    SVECTOR* vertex2;
    SVECTOR* vertex3;

    if (self->step == 0) {
        self->ext.giantcross.subweaponId = PL_W_CRASH_CROSS_BEAM;
        InitializeEntity(D_us_801804A8);
        self->primIndex = g_api.func_800EDB58(PRIM_GT4, LEN(D_us_80182E88));
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags |= FLAG_UNK_10000000 | FLAG_HAS_PRIMS;
        prim = &g_PrimBuf[self->primIndex];
        while (prim != NULL) {
            prim->tpage = 0x1C;
            prim->drawMode = DRAW_UNK_100 | DRAW_HIDE;
            prim = prim->next;
        }
        self->hitboxHeight = 0x50;
        self->hitboxWidth = 0xC;
        self->facingLeft = 0;
        self->posY.i.hi = 0x160;
        self->velocityY = FIX(-6.0);
        self->ext.giantcross.unk7C = 0;
        self->ext.giantcross.unk7E = 0x400;
        g_api.PlaySfx(SFX_FIREBALL_SHOT_B);
        prim = &g_PrimBuf[self->primIndex];
        primUVCoords = D_us_80182E88[0];
        for (i = 0; i < LEN(D_us_80182E88); i++, prim = prim->next,
            primUVCoords += 5) {
            prim->clut = (primUVCoords[4] & 0xF) + 0x1A0;
            switch (primUVCoords[4] & 0xF0) {
            case 0x10:
                prim->u0 = primUVCoords[0] + primUVCoords[2];
                prim->v0 = primUVCoords[1];
                prim->u1 = primUVCoords[0];
                prim->v1 = primUVCoords[1];
                prim->u2 = primUVCoords[0] + primUVCoords[2];
                prim->v2 = primUVCoords[1] + primUVCoords[3];
                prim->u3 = primUVCoords[0];
                prim->v3 = primUVCoords[1] + primUVCoords[3];
                break;
            case 0x20:
                prim->u0 = primUVCoords[0];
                prim->v0 = primUVCoords[1] + primUVCoords[3];
                prim->u1 = primUVCoords[0] + primUVCoords[2];
                prim->v1 = primUVCoords[1] + primUVCoords[3];
                prim->u2 = primUVCoords[0];
                prim->v2 = primUVCoords[1];
                prim->u3 = primUVCoords[0] + primUVCoords[2];
                prim->v3 = primUVCoords[1];
                break;
            case 0x30:
                prim->u0 = primUVCoords[0] + primUVCoords[2];
                prim->v0 = primUVCoords[1] + primUVCoords[3];
                prim->u1 = primUVCoords[0];
                prim->v1 = primUVCoords[1] + primUVCoords[3];
                prim->u2 = primUVCoords[0] + primUVCoords[2];
                prim->v2 = primUVCoords[1];
                prim->u3 = primUVCoords[0];
                prim->v3 = primUVCoords[1];
                break;
            case 0x40:
                prim->u3 = primUVCoords[0];
                prim->v3 = primUVCoords[1];
                prim->u1 = primUVCoords[0] + primUVCoords[2];
                prim->v1 = primUVCoords[1];
                prim->u2 = primUVCoords[0];
                prim->v2 = primUVCoords[1] + primUVCoords[3];
                prim->u0 = primUVCoords[0] + primUVCoords[2];
                prim->v0 = primUVCoords[1] + primUVCoords[3];
                break;
            case 0x50:
                prim->u3 = primUVCoords[0] + primUVCoords[2];
                prim->v3 = primUVCoords[1];
                prim->u1 = primUVCoords[0];
                prim->v1 = primUVCoords[1];
                prim->u2 = primUVCoords[0] + primUVCoords[2];
                prim->v2 = primUVCoords[1] + primUVCoords[3];
                prim->u0 = primUVCoords[0];
                prim->v0 = primUVCoords[1] + primUVCoords[3];
                break;
            case 0x60:
                prim->u3 = primUVCoords[0];
                prim->v3 = primUVCoords[1] + primUVCoords[3];
                prim->u1 = primUVCoords[0] + primUVCoords[2];
                prim->v1 = primUVCoords[1] + primUVCoords[3];
                prim->u2 = primUVCoords[0];
                prim->v2 = primUVCoords[1];
                prim->u0 = primUVCoords[0] + primUVCoords[2];
                prim->v0 = primUVCoords[1];
                break;
            case 0x70:
                prim->u3 = primUVCoords[0] + primUVCoords[2];
                prim->v3 = primUVCoords[1] + primUVCoords[3];
                prim->u1 = primUVCoords[0];
                prim->v1 = primUVCoords[1] + primUVCoords[3];
                prim->u2 = primUVCoords[0] + primUVCoords[2];
                prim->v2 = primUVCoords[1];
                prim->u0 = primUVCoords[0];
                prim->v0 = primUVCoords[1];
                break;
            default:
                prim->u0 = primUVCoords[0];
                prim->v0 = primUVCoords[1];
                prim->u1 = primUVCoords[0] + primUVCoords[2];
                prim->v1 = primUVCoords[1];
                prim->u2 = primUVCoords[0];
                prim->v2 = primUVCoords[1] + primUVCoords[3];
                prim->u3 = primUVCoords[0] + primUVCoords[2];
                prim->v3 = primUVCoords[1] + primUVCoords[3];
                break;
            }
        }
        self->step = 1;
    } else {
        if (self->posY.i.hi < -0x40) {
            DestroyEntity(self);
            return;
        }
        if (self->posY.i.hi < 0) {
            self->velocityY -= FIX(0.5);
        }
        self->posY.val += self->velocityY;
        self->ext.giantcross.unk7C += 0x60;
        self->ext.giantcross.unk7E += 0x60;
        trans1.vx = -(rcos(self->ext.giantcross.unk7C) * 0x60) >> 0xC;
        trans1.vy = self->posY.i.hi - 0x80;
        trans1.vz = ((rsin(self->ext.giantcross.unk7C) * 0x60) >> 0xC) + 0x180;
        rot.vy = self->ext.giantcross.unk7E;
        rot.vz = 0x40;
        rot.vx = 0;

        SetGeomOffset(self->posX.i.hi, 120);
        gte_SetGeomScreen(320);
        RotMatrix(&rot, &m);
        TransMatrix(&m, &trans1);
        gte_SetRotMatrix(&m);
        gte_SetTransMatrix(&m);
        gte_ldv0(&pos);
        gte_rtps();
        prim = &g_PrimBuf[self->primIndex];
        vectors = D_us_80182BA8[0];
        gte_stsxy((long*)&prim->x0);
        gte_stszotz((long*)&z);
        self->hitboxOffX = prim->x0 - self->posX.i.hi;
        self->hitboxOffY = prim->y0 - self->posY.i.hi;
        for (i = 0; i < LEN(D_us_80182E88); i++, prim = prim->next,
            vectors += 4) {
            vertex0 = vectors[0];
            vertex1 = vectors[1];
            vertex3 = vectors[3];
            gte_ldv3(vertex0, vertex1, vertex3);
            gte_rtpt();
            vertex2 = vectors[2];
            prim->type = PRIM_GT4;
            gte_nclip();
            prim->drawMode = DRAW_HIDE;
            gte_stopz(&nclip);
            if (nclip < 0) {
                continue;
            }
            gte_stsxy3(&prim->x0, &prim->x1, &prim->x2);
            gte_ldv0(vertex2);
            gte_rtps();
            prim->drawMode = DRAW_DEFAULT;
            if (z < 16) {
                prim->priority = 0x1F6;
            } else if (z > 998) {
                prim->priority = 0x10;
            } else {
                prim->priority = 0xD0 - (z - 0x50);
            }
            gte_stsxy((long*)&prim->x3);
        }
    }
    FntPrint("judge:%02x\n", self->hitboxState);
}
