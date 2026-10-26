// SPDX-License-Identifier: AGPL-3.0-or-later
#include "bo6.h"

extern s16 D_us_80182890[][6];

void RicEntitySubwpnHolyWaterBreakGlass(Entity* self) {
    Point16 positions[8];
    Primitive* prim;
    s16 posX;
    s16 posY;
    s16 arrIndex;
    s32 i;

    switch (self->step) {
    case 0:
        self->primIndex = g_api.AllocPrimitives(PRIM_GT4, 16);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        posX = self->posX.i.hi;
        posY = self->posY.i.hi;
        prim = &g_PrimBuf[self->primIndex];
        for (i = 0; prim != NULL; i++, prim = prim->next) {
            if (i < 8) {
                positions[i].x = ((FakePrim*)prim)->posX.i.hi =
                    ((FakePrim*)prim)->x0 = posX;
                positions[i].y = ((FakePrim*)prim)->posY.i.hi =
                    ((FakePrim*)prim)->y0 = posY;
                // Random velocity from 0.25 to 0.5
                ((FakePrim*)prim)->velocityX.val =
                    (rand() & 0x3FFF) + FIX(0.25);
                if (i & 1) {
                    ((FakePrim*)prim)->velocityX.val =
                        -((FakePrim*)prim)->velocityX.val;
                }
                ((FakePrim*)prim)->velocityY.val =
                    -(((rand() & PSP_RANDMASK) * 2) + FIX(2.5));
                ((FakePrim*)prim)->drawMode = DRAW_HIDE | DRAW_UNK02;
                ((FakePrim*)prim)->type = PRIM_TILE;
            } else {
                prim->r0 = prim->r1 = prim->r2 = prim->r3 =
                    (rand() & 0xF) + 0x30;
                prim->b0 = prim->b1 = prim->b2 = prim->b3 =
                    (rand() & 0x7F) + 0x80;
                prim->g0 = prim->g1 = prim->g2 = prim->g3 =
                    (rand() & 0x1F) + 0x30;
                if (rand() & 1) {
                    prim->drawMode = (DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS |
                                      DRAW_UNK02 | DRAW_TRANSP);
                } else {
                    prim->drawMode = (DRAW_COLORS | DRAW_UNK02);
                }
                posX = positions[i - 8].x;
                posY = positions[i - 8].y;
                prim->u0 = arrIndex = i & 3;
                prim->x0 = posX + D_us_80182890[arrIndex][0];
                prim->y0 = posY + D_us_80182890[arrIndex][1];
                prim->x1 = posX + D_us_80182890[arrIndex][2];
                prim->y1 = posY + D_us_80182890[arrIndex][3];
                prim->x3 = prim->x2 = posX + D_us_80182890[arrIndex][4];
                prim->y3 = prim->y2 = posY + D_us_80182890[arrIndex][5];
                prim->type = PRIM_G4;
                prim->priority = RIC.zPriority + 2;
            }
        }
        self->flags = FLAG_POS_CAMERA_LOCKED | FLAG_HAS_PRIMS;
        self->ext.timer.t = 20;
        self->step++;
        break;
    case 1:
        if (--self->ext.timer.t == 0) {
            DestroyEntity(self);
            return;
        }
        prim = &g_PrimBuf[self->primIndex];
        for (i = 0; prim != NULL; i++, prim = prim->next) {
            if (i < 8) {
                ((FakePrim*)prim)->posX.i.hi = ((FakePrim*)prim)->x0;
                ((FakePrim*)prim)->posY.i.hi = ((FakePrim*)prim)->y0;
                ((FakePrim*)prim)->posX.val += ((FakePrim*)prim)->velocityX.val;
                ((FakePrim*)prim)->posY.val += ((FakePrim*)prim)->velocityY.val;
                ((FakePrim*)prim)->velocityY.val += FIX(36.0 / 128);
                positions[i].x = ((FakePrim*)prim)->posX.i.hi;
                positions[i].y = ((FakePrim*)prim)->posY.i.hi;
                ((FakePrim*)prim)->x0 = ((FakePrim*)prim)->posX.i.hi;
                ((FakePrim*)prim)->y0 = ((FakePrim*)prim)->posY.i.hi;
            } else {
                posX = positions[i - 8].x;
                posY = positions[i - 8].y;
                arrIndex = prim->u0;
                prim->x0 = posX + D_us_80182890[arrIndex][0];
                prim->y0 = posY + D_us_80182890[arrIndex][1];
                prim->x1 = posX + D_us_80182890[arrIndex][2];
                prim->y1 = posY + D_us_80182890[arrIndex][3];
                prim->x3 = prim->x2 = posX + D_us_80182890[arrIndex][4];
                prim->y3 = prim->y2 = posY + D_us_80182890[arrIndex][5];
            }
        }
        break;
    }
}

extern EInit D_us_80180484;

void RicEntityCrashHydroStorm(Entity* self) {
    PrimLineG2* line;
    s16 primcount;
    s32 i;

    if (self->params < 24) {
        primcount = 32;
    } else {
        primcount = 33 - (self->params - 32) * 2;
    }

    switch (self->step) {
    case 0:
        self->primIndex = g_api.AllocPrimitives(PRIM_LINE_G2, primcount);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->ext.subweapon.subweaponId = PL_W_HYDROSTORM;
        InitializeEntity(D_us_80180484);
        self->posX.i.hi = 128;
        self->posY.i.hi = 112;
        self->hitboxWidth = 120;
        self->hitboxHeight = 120;
        self->flags |= FLAG_UNK_10000000 | FLAG_HAS_PRIMS;
        self->facingLeft = 0;
        line = (PrimLineG2*)&g_PrimBuf[self->primIndex];
        while (line != NULL) {
            line->r0 = 0x1F;
            line->g0 = 0x1F;
            line->b0 = 0x30;
            line->r1 = 0x3F;
            line->g1 = 0x50;
            line->b1 = 0x7F;
            line->x0 = rand() & 0x1FF;
            line->x1 = line->x0;
            line->y0 = -(rand() & 0xF);
            line->y1 = line->y0;
            line->preciseX.i.hi = line->x1;
            line->preciseY.i.hi = line->y1;

            // both rcos and rsin could be pre-calcualted values
            // PSP and PSX are logically equivalent
#if defined(VERSION_PSP)
            line->velocityX.val = (rcos(ROT(258.75)) * 16) * 12;
#else
            line->velocityX.val = -(rcos(ROT(258.75)) * -16) * 12;
#endif
            line->velocityY.val = -(rsin(ROT(258.75)) * 16) * 12;
            line->timer = 0;
            line->delay = (rand() & 0xF) + 12;
            if (rand() & 1) {
                line->priority = RIC.zPriority + 2;
            } else {
                line->priority = RIC.zPriority - 2;
            }
            line->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_TRANSP;
            line = line->next;
        }
        if (self->params == 1) {
            g_api.SetFadeMode(FADE_BLUE_TINT);
        }
        self->ext.subweapon.timer = 0x160;
        if ((self->params < 16) && !(self->params & 3)) {
            g_api.PlaySfx(SFX_BOSS_RIC_HYDRO_STORM_RAIN);
        }
        self->step = 1;
        break;
    case 1:
        line = (PrimLineG2*)&g_PrimBuf[self->primIndex];
        for (i = 0; line != NULL; i++, line = line->next) {
            if (line->timer == 0) {
                line->preciseX.i.hi = line->x1;
                line->preciseY.i.hi = line->y1;
                line->preciseX.val += line->velocityX.val;
                line->preciseY.val += line->velocityY.val;
                line->x1 = line->preciseX.i.hi;
                line->y1 = line->preciseY.i.hi;
                if (line->y1 > line->delay) {
                    line->timer++;
                    line->xLength = line->x0 - line->x1;
                    line->yLength = line->y0 - line->y1;
                }
            } else {
                line->preciseX.i.hi = line->x1;
                line->preciseY.i.hi = line->y1;
                line->preciseX.val += line->velocityX.val;
                line->preciseY.val += line->velocityY.val;
                line->x1 = line->preciseX.i.hi;
                line->y1 = line->preciseY.i.hi;
                line->y0 = line->y1 + line->yLength;
                line->x0 = line->x1 + line->xLength;
                if (line->y0 >= 0xD8) {
                    self->step = 2;
                }
            }
        }
        self->ext.subweapon.timer++;
        break;
    case 2:
        if (self->params == 24) {
            g_Ric.unk4E = 1;
        }
        DestroyEntity(self);
        break;
    }
    g_Ric.timers[PL_T_3] = 16;
}

extern s32 D_us_801D087C;

void DebugShowWaitInfo(const char* msg) {
    g_CurrentBuffer = g_CurrentBuffer->next;
    FntPrint(msg);
    if (D_us_801D087C++ & 4) {
        FntPrint("\no\n");
    }
    DrawSync(0);
    VSync(0);
    PutDrawEnv(&g_CurrentBuffer->draw);
    PutDispEnv(&g_CurrentBuffer->disp);
    FntFlush(-1);
}

void DebugInputWait(const char* msg) {
    while (PadRead(0))
        DebugShowWaitInfo(msg);
    while (PadRead(0) == 0)
        DebugShowWaitInfo(msg);
}

s32 RicCheckHolyWaterCollision(s16 height, s16 width) {
    Collider collider;
    Collider collider2;
    s16 maskedEffects;
    s16 maskedEffects2;
    s16 posX;
    s16 posY;
    s16 newPosY;

    if ((g_CurrentEntity->posX.val + width) < 0 ||
        (g_CurrentEntity->posX.i.hi + width) > 256) {
        if ((g_CurrentEntity->posY.i.hi + height) >= 212) {
            g_CurrentEntity->posY.i.hi = 212 - height;
            return EFFECT_SOLID;
        }
        return EFFECT_NONE;
    }
    posX = g_CurrentEntity->posX.i.hi + width;
    posY = g_CurrentEntity->posY.i.hi + height;

    g_api.CheckCollision(posX, posY, &collider, 0);
    maskedEffects = collider.effects &
                    (EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_UNK_2000 |
                     EFFECT_UNK_1000 | EFFECT_UNK_0800 | EFFECT_SOLID);
    posY = posY - 1 + collider.unk18;
    g_api.CheckCollision(posX, posY, &collider2, 0);

    newPosY = height + (g_CurrentEntity->posY.i.hi + collider.unk18);
    if ((maskedEffects & (EFFECT_UNK_8000 | EFFECT_UNK_0800 | EFFECT_SOLID)) ==
            EFFECT_SOLID ||
        (maskedEffects & (EFFECT_UNK_8000 | EFFECT_UNK_0800 | EFFECT_SOLID)) ==
            (EFFECT_UNK_0800 | EFFECT_SOLID)) {
        maskedEffects = collider2.effects &
                        (EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_UNK_2000 |
                         EFFECT_UNK_1000 | EFFECT_SOLID);
        if (!(maskedEffects & EFFECT_SOLID)) {
            g_CurrentEntity->posY.i.hi = newPosY;
            return EFFECT_SOLID;
        }
        if (((s32)collider2.effects & (EFFECT_UNK_8000 | EFFECT_SOLID)) ==
            (EFFECT_UNK_8000 | EFFECT_SOLID)) {
            g_CurrentEntity->posY.i.hi = newPosY - 1 + collider2.unk18;
            return maskedEffects;
        }
        return EFFECT_NONE;
    }
    if ((maskedEffects & (EFFECT_UNK_8000 | EFFECT_SOLID)) ==
        (EFFECT_UNK_8000 | EFFECT_SOLID)) {
        g_CurrentEntity->posY.i.hi = newPosY;
        return maskedEffects &
               (EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_UNK_2000 |
                EFFECT_UNK_1000 | EFFECT_SOLID);
    }
    return EFFECT_NONE;
}

static int func_8016840C() { return EFFECT_NONE; }

extern EInit D_us_80180460;

void RicEntitySubwpnHolyWater(Entity* self) {
    s16 xMod;
    s32 colRes;

    if (self->step > 2) {
        self->posY.i.hi += 5;
    }
    switch (self->step) {
    case 0:
        self->ext.holywater.subweaponId = PL_W_HOLYWATER;
        InitializeEntity(D_us_80180460);
        self->flags = FLAG_POS_CAMERA_LOCKED;
        self->animSet = ANIMSET_OVL(3);
        self->animCurFrame = 0x23;
        self->zPriority = RIC.zPriority + 2;
        self->unk5A = 0x24;
        self->palette = PAL_FLAG(0x22F);
        xMod = 0;
        if (self->facingLeft) {
            xMod = -xMod;
        }
        self->posX.i.hi += xMod;
        self->posY.i.hi += -16;
        self->ext.holywater.angle = (rand() & 0x7F) + ROT(309.375);
        if (RIC.facingLeft == true) {
            self->ext.holywater.angle = (rand() & 0x7F) + ROT(219.375);
        }
        self->velocityX =
            (FLT_TO_FIX(rcos(self->ext.holywater.angle)) * FIX(3.0 / 128.0)) >>
            8;
        self->velocityY =
            -(FLT_TO_FIX(rsin(self->ext.holywater.angle)) * FIX(3.0 / 128.0)) >>
            8;
        self->hitboxWidth = 4;
        self->hitboxHeight = 4;
        self->ext.holywater.unk80 = 0x200;
        self->step = 1;
        break;

    case 1:
        self->posY.val += self->velocityY;
        colRes = RicCheckHolyWaterCollision(0, 0);
        self->posX.val += self->velocityX;

        if ((colRes & EFFECT_SOLID) || (self->hitFlags != 0)) {
            RicCreateEntFactoryFromEntity(self, 0x28, 0);
            g_api.PlaySfx(SFX_RIC_HOLY_WATER_ATTACK);
            self->ext.holywater.timer = 80;
            self->animSet = 0;
            self->step = 3;
            self->velocityX >>= 2;
        } else if (self->flags & FLAG_DEAD) {
            RicCreateEntFactoryFromEntity(self, 0x28, 0);
            g_api.PlaySfx(SFX_RIC_HOLY_WATER_ATTACK);
            self->ext.holywater.timer = 80;
            self->animSet = 0;
            self->step = 3;
            self->velocityX = -((s32)self->velocityX >> 2);
        }
        break;
    case 2:
        if (self->flags & FLAG_DEAD) {
            DestroyEntity(self);
            return;
        }
        if (--self->ext.holywater.timer == 0) {
            self->velocityX >>= 2;
            self->ext.holywater.timer = 80;
            self->step++;
        }
        break;
    case 3:
        if (self->flags & FLAG_DEAD) {
            self->velocityX = 0;
        }
        if (!(self->ext.holywater.timer & 3)) {
            RicCreateEntFactoryFromEntity(
                self, FACTORY(BP_HOLYWATER_FIRE, self->ext.holywater.unk82), 0);
            self->ext.holywater.unk82 += 1;
            self->velocityX -= (self->velocityX / 32);
        }

        self->posX.val += self->velocityX;
        colRes = RicCheckHolyWaterCollision(6, 0);
        if (!(colRes & EFFECT_SOLID)) {
            self->velocityX >>= 1;
            self->step++;
        }
        break;
    case 4:
        if (self->flags & FLAG_DEAD) {
            self->velocityX = 0;
        }

        if (!(self->ext.holywater.timer & 3)) {
            RicCreateEntFactoryFromEntity(
                self, FACTORY(BP_HOLYWATER_FIRE, self->ext.holywater.unk82), 0);
            self->ext.holywater.unk82 += 1;
        }
        self->velocityY += FIX(12.0 / 128);
        if (self->velocityY > FIX(4)) {
            self->velocityY = FIX(4);
        }
        self->posY.val += self->velocityY;
        colRes = RicCheckHolyWaterCollision(0, 0);
        self->posX.val += self->velocityX;
        xMod = 4;
        if (self->velocityX < 0) {
            xMod = -xMod;
        }
        colRes |= func_8016840C(-7, xMod);
        if (colRes & EFFECT_SOLID) {
            self->velocityX <<= 1;
            self->step--;
        }
        break;
    case 5:
        break;
    }

    if (self->step > 2) {
        if (--self->ext.holywater.timer < 0) {
            DestroyEntity(self);
            return;
        }
        if (self->ext.holywater.timer == 2) {
            self->step = 5;
        }
        self->posY.i.hi -= 5;
        self->animCurFrame = 0;
    }
    g_Ric.timers[PL_T_3] = 2;
    self->hitFlags = 0;
    self->flags &= ~FLAG_DEAD;
    FntPrint("judge:%02x\n", self->hitboxState);
}

extern s32 D_us_801828C8[];
extern EInit D_us_8018046C;

void RicEntitySubwpnHolyWaterFlame(Entity* self) {
    s16 sp10[5];
    s16 sp20[5];
    s16 xMod;
    s16 variant;
    s16* primYPtr;
    s32 doubleparams;
    u8 randR;
    u8 randG;
    u8 randB;
    s16 flameHeight;
    s16 angle;
    u8 texX;
    u8 texY;
    s32 i;
    Primitive* prim;

    variant = self->params >> 8;
    texX = D_us_801828C8[(g_GameTimer & 7) * 2 + 0];
    texY = D_us_801828C8[(g_GameTimer & 7) * 2 + 1];
    switch (self->step) {
    case 0:
        self->ext.holywater.subweaponId = PL_W_HOLYWATER_FLAMES;
        InitializeEntity(D_us_8018046C);
        self->ext.holywater.hitboxState = self->hitboxState;
        self->hitboxState = 0;
        randR = (rand() & 0x3F) + 0x2F;
        randG = (rand() & 0x3F) + 0x6F;
        randB = (rand() & 0x7F) + 0x6F;
        self->primIndex = g_api.AllocPrimitives(PRIM_GT4, 4);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        prim = &g_PrimBuf[self->primIndex];
        i = 0;
        while (prim) {
            prim->r0 = prim->r1 = prim->r2 = prim->r3 = randR;
            prim->g0 = prim->g1 = prim->g2 = prim->g3 = randG;
            prim->b0 = prim->b1 = prim->b2 = prim->b3 = randB;
            if (i == 0) {
                prim->r0 = prim->r1 = 0;
                prim->g0 = prim->g1 = 0;
                prim->b0 = prim->b1 = 0;
            }
            prim->clut = PAL_UNK_1B0;
            prim->tpage = 0x1A;
            prim->priority = RIC.zPriority + 2;
            prim->drawMode = DRAW_UNK_40 | DRAW_TPAGE2 | DRAW_TPAGE |
                             DRAW_HIDE | DRAW_COLORS | DRAW_UNK02 | DRAW_TRANSP;
            i++;
            prim = prim->next;
        }
        self->flags = FLAG_POS_CAMERA_LOCKED | FLAG_HAS_PRIMS;
        self->ext.holywater.timer = 1;
        self->step = 1;
        break;
    case 1:
        if (--self->ext.holywater.timer == 0) {
            self->hitboxState = self->ext.holywater.hitboxState;
            self->hitboxWidth = 4;
            self->posY.i.hi -= 10;
            RicCreateEntFactoryFromEntity(self, FACTORY(BP_EMBERS, 3), 0);
            self->posY.i.hi += 10;
            self->ext.holywater.timer = 0x50;
            self->ext.holywater.unk80 = (rand() & 0xF) + 0x12;
            self->ext.holywater.angle = rand() & 0xFFF;
            self->step++;
        }
        break;
    case 2:
        if (self->flags & FLAG_DEAD) {
            DestroyEntity(self);
            return;
        }
        xMod = -1;
        if (self->facingLeft) {
            xMod = -xMod;
        }
        angle = self->ext.holywater.angle;
        self->ext.holywater.angle += 0xC0;
        for (i = 0; i < 4; i++) {
            sp10[i] = self->posX.i.hi + (rsin(angle + (i * 1024)) >> 10);
        }
        sp10[4] = self->posX.i.hi;
        sp10[0] = self->posX.i.hi + xMod;
        angle = (self->ext.holywater.timer - 16) * 64 + 0xC00;
        flameHeight = (rsin(angle) >> 8) + self->ext.holywater.unk80;
        flameHeight = flameHeight * 3 >> 1;
        sp20[0] = self->posY.i.hi - flameHeight;
        sp20[4] = self->posY.i.hi;
        sp20[2] = (sp20[0] + sp20[4]) / 2;
        sp20[1] = (sp20[0] + sp20[2]) / 2;
        sp20[3] = (sp20[2] + sp20[4]) / 2;
        prim = &g_PrimBuf[self->primIndex];
        if (--self->ext.holywater.timer < 0) {
            DestroyEntity(self);
            return;
        }
        if (self->ext.holywater.timer & 3) {
            self->hitboxState = 0;
        } else {
            self->hitboxState = self->ext.holywater.hitboxState;
        }
        if (self->ext.holywater.timer < 0x15) {
            self->hitboxState = 0;
        }
        i = 0;
        while (prim) {
            if (self->ext.holywater.timer <= variant * 2 + 0x18) {
                if (prim->g0 >= 10) {
                    prim->g0 -= 5;
                }
                if (prim->b0 >= 10) {
                    prim->b0 -= 5;
                }
                if (prim->r0 >= 16) {
                    prim->r0 -= 8;
                }
                prim->g1 = prim->g2 = prim->g3 = prim->g0;
                prim->r1 = prim->r2 = prim->r3 = prim->r0;
                prim->b1 = prim->b2 = prim->b3 = prim->b0;
            }
            prim->x0 = sp10[i] - 8;
            prim->x1 = sp10[i] + 8;
            prim->y0 = sp20[i];
            prim->y1 = sp20[i];
            prim->x2 = sp10[i + 1] - 8;
            prim->x3 = sp10[i + 1] + 8;
            prim->y2 = sp20[i + 1];
            prim->y3 = sp20[i + 1];
            prim->drawMode &= ~DRAW_HIDE;
            prim->u0 = prim->u1 = texX + 0x80 - i * 7;
            prim->u2 = prim->u3 = texX + 0x80 - ((i + 1) * 7);
            prim->v0 = prim->v2 = texY + 0x80;
            prim->v1 = prim->v3 = texY + 0x90;
            if ((sp20[4] - sp20[0]) < 7) {
                prim->drawMode |= DRAW_HIDE;
                DestroyEntity(self);
                return;
            }
            i++;
            prim = prim->next;
        }
        self->hitboxHeight = flameHeight >> 1;
        self->hitboxOffY = (-flameHeight >> 1);
        break;
    }
    g_Ric.timers[PL_T_3] = 2;
}

extern EInit D_us_8018049C;
extern RECT D_us_80182968;
extern u16 D_us_80182908[];

void RicEntitySubwpnCrashCross(Entity* self) {
    s16 heightStep;
    s16 widthStep;
    s16 right;
    s16 left;
    Primitive* prim;

    heightStep = 3;
    widthStep = 1;
    self->posY.i.hi = 0x78;
    self->posX.i.hi = RIC.posX.i.hi;
    switch (self->step) {
    case 0:
        self->ext.crashcross.subweaponId = PL_W_CRASH_CROSS;
        InitializeEntity(D_us_8018049C);
        self->primIndex = g_api.AllocPrimitives(PRIM_GT4, 1);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags = FLAG_UNK_10000000 | FLAG_HAS_PRIMS;
        self->ext.crashcross.unk80 = 1;
        self->zPriority = 0xC2;
        LoadImage(&D_us_80182968, (u_long*)D_us_80182908);
        g_api.PlaySfx(SFX_CRASH_CROSS);
        g_api.PlaySfx(SFX_TELEPORT_BANG_B);
        self->step = 1;
        break;
    case 1:
        self->ext.crashcross.unk7E.val += heightStep;
        self->ext.crashcross.unk82 += heightStep * 2;
        if (self->ext.crashcross.unk7E.i.lo >= 0x70) {
            RicCreateEntFactoryFromEntity(self, BP_CRASH_CROSSES_ONLY, 0);
            RicCreateEntFactoryFromEntity(self, BP_CRASH_CROSS_PARTICLES, 0);
            self->step++;
        }
        break;
    case 2:
        if (g_Timer & 1) {
            self->ext.crashcross.unk7C += widthStep;
            self->ext.crashcross.unk80 += widthStep * 2;
            if (self->ext.crashcross.unk80 >= 0x2C) {
                self->step++;
                self->ext.crashcross.unk84 = 0x80;
            }
        }
        break;
    case 3:
        if (--self->ext.crashcross.unk84 == 0) {
            g_api.SetFadeMode(FADE_NONE);
            left = self->posX.i.hi - self->ext.crashcross.unk7C;
            if (left < 0) {
                left = 0;
            }
            right = self->posX.i.hi + self->ext.crashcross.unk7C;
            if (right > 0xFF) {
                right = 0xFF;
            }
            g_api.PlaySfx(SFX_WEAPON_APPEAR);
            self->step++;
        }
        break;
    case 4:
        widthStep *= 3;
        left = abs(self->posX.i.hi - 0x80);
        widthStep = widthStep * (left + 0x80) / 112;
        self->ext.crashcross.unk7C += widthStep;

        left = self->posX.i.hi - self->ext.crashcross.unk7C;
        if (left < 0) {
            left = 0;
        }
        right = self->posX.i.hi + self->ext.crashcross.unk7C;
        if (right > 0xFF) {
            right = 0xFF;
        }
        if (right - left > 0xF8) {
            g_Ric.unk4E = 1;
            DestroyEntity(self);
            return;
        }
        break;
    }
    self->hitboxOffY = 0;
    self->hitboxHeight = self->ext.crashcross.unk7E.val;
    if (self->step == 4) {
        self->hitboxWidth = (right - left) >> 1;
        self->hitboxOffX = ((left + right) >> 1) - self->posX.i.hi;
    } else {
        self->hitboxWidth = self->ext.crashcross.unk7C;
        self->hitboxOffX = 0;
    }
    prim = &g_PrimBuf[self->primIndex];
    prim->x0 = prim->x2 = self->posX.i.hi - self->ext.crashcross.unk7C;
    prim->y1 = prim->y0 = self->posY.i.hi - self->ext.crashcross.unk7E.val;
    prim->x1 = prim->x3 = prim->x0 + self->ext.crashcross.unk80;
    prim->y2 = prim->y3 = prim->y0 + self->ext.crashcross.unk82;
    prim->u0 = prim->u2 = 1;
    prim->u1 = prim->u3 = 0x30;
    prim->v0 = prim->v1 = prim->v2 = prim->v3 = 0xF8;
    prim->tpage = 0x11C;
    if (self->step == 4) {
        prim->x0 = prim->x2 = left;
        prim->x1 = prim->x3 = right;
    }
    prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_TRANSP;
    prim->priority = self->zPriority;
    g_Ric.timers[PL_T_3] = 2;
}

extern EInit D_us_80180454;
extern s16 D_us_801D10C8;

extern AnimationFrame anim_cross_boomerang[];
extern Point16 D_us_801D08C4[4][128];
extern s32 D_us_801D10C4;

void RicEntitySubwpnCross(Entity* self) {
    s16 playerHitboxX;
    s16 playerHitboxY;
    s16 rotate;
    s16* psp_s1;
    s32 xAccel;

    rotate = self->rotate;
    switch (self->step) {
    case 0:
        self->ext.crossBoomerang.subweaponId = PL_W_CROSS;
        InitializeEntity(D_us_80180454);
        self->flags =
            FLAG_UNK_20000000 | FLAG_UNK_10000000 | FLAG_POS_CAMERA_LOCKED;
        D_us_801D10C8 = self->hitboxState;
        // gets used by shadow, must align with that entity
        self->ext.crossBoomerang.unk84 = D_us_801D08C4[D_us_801D10C4];
        D_us_801D10C4++;
        D_us_801D10C4 &= 3;
        RicCreateEntFactoryFromEntity(self, BP_5, 0);
        self->animSet = ANIMSET_OVL(4);
        self->unk5A = 0x44;
        self->anim = anim_cross_boomerang;
        self->facingLeft = RIC.facingLeft;
        self->zPriority = RIC.zPriority;
        RicSetSpeedX(FIX(3.5625));
        self->drawFlags = ENTITY_ROTATE;
        self->rotate = ROT(270);
        self->hitboxWidth = 8;
        self->hitboxHeight = 8;
        self->posY.i.hi -= 8;
        g_api.PlaySfx(SFX_RIC_CRASH_CROSS);
        self->step = 1;
        break;
    case 1:
        if (RIC.pose == 1) {
            self->step++;
        }
    case 2:
        // First phase. We spin at 0x80 angle units per frame.
        // Velocity gets decremented by 1/16 per frame until we slow
        // down to less than 0.75.
        self->rotate -= ROT(11.25);
        self->posX.val += self->velocityX;
        if (self->facingLeft) {
            xAccel = FIX(-1.0 / 16);
        } else {
            xAccel = FIX(1.0 / 16);
        }
        self->velocityX -= xAccel;

        if (abs(self->velocityX) < FIX(0.75)) {
            self->step = 3;
        }

        if ((self->hitFlags == 2) || (self->flags & FLAG_DEAD)) {
            if (self->velocityX < 0) {
                self->velocityX = FIX(-0.03125);
            } else {
                self->velocityX = FIX(0.03125);
            }
            self->ext.crossBoomerang.timer = 30;
            self->step = 3;
            self->ext.crossBoomerang.timer = 16;
            self->hitboxState = 0;
        }

        break;
    case 3:
        // Second phase. Once we are slow, we spin twice as fast, and then
        // wait until our speed gets higher once again (turned around).
        self->rotate -= ROT(22.50);
        self->posX.val += self->velocityX;
        if (self->facingLeft) {
            xAccel = FIX(-1.0 / 16);
        } else {
            xAccel = FIX(1.0 / 16);
        }
        if (self->hitFlags == 2 || (self->flags & FLAG_DEAD)) {
            if (self->facingLeft) {
                xAccel = FIX(-1.0 / 16);
            } else {
                xAccel = FIX(1.0 / 16);
            }
        }
        self->velocityX -= xAccel;
        if (abs(self->velocityX) > FIX(0.75)) {
            self->step++;
        }
        break;
    case 4:
        // Third phase. We've now sped up and we're coming back.
        // Increase speed until a terminal velocity of 2.5.
        if (self->facingLeft) {
            xAccel = FIX(-1.0 / 16);
        } else {
            xAccel = FIX(1.0 / 16);
        }
        self->velocityX -= xAccel;
        if (abs(self->velocityX) > FIX(2.5)) {
            self->hitboxState = D_us_801D10C8;
            self->step++;
        }
    case 5:
        if (--self->ext.crossBoomerang.timer < 0 &&
            ((self->hitFlags == 2) || (self->flags & FLAG_DEAD))) {
            self->velocityY = FIX(-3.0);
            self->ext.holywater.timer = 50;
            self->hitboxState = 0;
            self->step = 6;
            self->velocityX = -((s32)self->velocityX / 2);
        }

        // Now we check 2 conditions. If we're within the player's hitbox...
        playerHitboxX = (RIC.posX.i.hi + RIC.hitboxOffX);
        playerHitboxY = (RIC.posY.i.hi + RIC.hitboxOffY);
        if (abs(self->posX.i.hi - playerHitboxX) <
                RIC.hitboxWidth + self->hitboxWidth &&
            abs(self->posY.i.hi - playerHitboxY) <
                RIC.hitboxHeight + self->hitboxHeight) {
            // ... Then we go to step 7 to be destroyed.
            self->step = 7;
            self->ext.crossBoomerang.timer = 32;
            return;
        }
        // Alternatively, if we're offscreen, we will also be destroyed.
        if ((self->facingLeft == 0 && self->posX.i.hi < -32) ||
            (self->facingLeft && self->posX.i.hi > 0x120)) {
            self->step = 7;
            self->ext.crossBoomerang.timer = 32;
            return;
        }
        // Otherwise, we keep trucking. spin at the slower rate again.
        self->rotate -= ROT(11.25);
        self->posX.val += self->velocityX;
        break;
    case 6:
        if (--self->ext.crossBoomerang.timer == 0) {
            DestroyEntity(self);
            return;
        }
        self->velocityY += FIX(0.15625);
        self->posX.val += self->velocityX;
        self->posY.val += self->velocityY;
        self->rotate += ROT(33.75);
        break;
    case 7:
        if (--self->ext.crossBoomerang.timer == 0) {
            DestroyEntity(self);
            return;
        }
        self->hitboxState = 0;
        self->animSet = 0;
        self->posX.val += self->velocityX;
        break;
    }
    // We will increment through these states, creating trails.
    // Factory 3 is entity #4, func_80169C10. Appears to make tiny sparkles.
    // Factory 4 is entity #5, RicEntityHitByCutBlood. Appears to make a
    // "shadow" of the cross boomerang.
    self->ext.crossBoomerang.unk7E++;
    if (1 < self->step && self->step < 6) {
        if ((self->ext.crossBoomerang.unk7E & 0xF) == 1) {
            RicCreateEntFactoryFromEntity(self, BP_SUBWPN_CROSS_PARTICLES, 0);
        }
        if ((self->ext.crossBoomerang.unk7E & 0xF) == 4) {
            RicCreateEntFactoryFromEntity(self, FACTORY(BP_EMBERS, 6), 0);
        }
        if ((self->ext.crossBoomerang.unk7E & 0xF) == 6) {
            RicCreateEntFactoryFromEntity(self, BP_SUBWPN_CROSS_PARTICLES, 0);
        }
        if ((self->ext.crossBoomerang.unk7E & 0xF) == 8) {
            RicCreateEntFactoryFromEntity(self, FACTORY(BP_EMBERS, 6), 0);
        }
        if ((self->ext.crossBoomerang.unk7E & 0xF) == 12) {
            RicCreateEntFactoryFromEntity(self, FACTORY(BP_EMBERS, 6), 0);
        }
        if ((self->ext.crossBoomerang.unk7E & 0xF) == 11) {
            RicCreateEntFactoryFromEntity(self, BP_SUBWPN_CROSS_PARTICLES, 0);
        }
    }
    // Applies a flickering effect
    if ((g_GameTimer >> 1) & 1) {
        self->palette = PAL_FLAG(PAL_UNK_1B0);
    } else {
        self->palette = PAL_FLAG(PAL_UNK_1B1);
    }
    psp_s1 = (s16*)self->ext.crossBoomerang.unk84;
    psp_s1 = &psp_s1[self->ext.crossBoomerang.unk80 * 2];
    *psp_s1 = self->posX.i.hi + g_Tilemap.scrollX.i.hi;
    psp_s1++;
    *psp_s1 = self->posY.i.hi + g_Tilemap.scrollY.i.hi;
    self->ext.crossBoomerang.unk80++;
    self->ext.crossBoomerang.unk80 &= 0x3F;
    rotate ^= self->rotate;
    g_Ric.timers[PL_T_3] = 2;
    self->hitFlags = 0;
    self->flags &= ~FLAG_DEAD;
}

void func_us_801C488C(Entity* self) {
    Primitive* prim;
    s32 posX;
    s32 posY;

    if (self->step == 0) {
        self->primIndex = g_api.AllocPrimitives(PRIM_GT4, 1);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags = FLAG_POS_CAMERA_LOCKED | FLAG_HAS_PRIMS;
        self->velocityY = FIX(0.5);
        self->posX.i.hi += (rand() & 0xF) - 8;
        self->posY.i.hi += (rand() & 0xF) - 4;
#if defined(VERSION_PSP)
        prim = &g_PrimBuf[self->primIndex];
        prim->clut = PAL_UNK_1B0;
#endif
        prim = &g_PrimBuf[self->primIndex];
        prim->clut = PAL_UNK_1B0;
        prim->tpage = 0x1A;
        prim->b0 = 0;
        prim->b1 = 0;
        prim->priority = self->zPriority + 4;
        prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_TRANSP;
        func_us_801BB5BC(prim, self->posX.i.hi, self->posY.i.hi);
        self->step++;
    } else {
        prim = &g_PrimBuf[self->primIndex];
        self->posY.val += self->velocityY;
        if (func_us_801BB5BC(prim, self->posX.i.hi, self->posY.i.hi)) {
            DestroyEntity(self);
        }
    }
}

extern s16 D_us_80182994[];

void RicEntitySubwpnCrossTrail(Entity* self) {
    s16* temp;

    switch (self->step) {
    case 0:
        self->flags = FLAG_UNK_10000000 | FLAG_POS_CAMERA_LOCKED;
        // the parent pointer is set in RicEntityFactory.
        // the value of unk84 is set in RicEntitySubwpnCross
        self->ext.crossBoomerang.unk84 =
            self->ext.crossBoomerang.parent->ext.crossBoomerang.unk84;
        self->animSet = ANIMSET_OVL(4);
        self->animCurFrame = D_us_80182994[self->params];
        self->unk5A = 0x44;
        self->palette = PAL_FLAG(PAL_UNK_1B0);
        self->blendMode = BLEND_TRANSP;
        self->facingLeft = RIC.facingLeft;
        self->zPriority = RIC.zPriority;
        self->drawFlags = ENTITY_ROTATE;
        self->rotate = ROT(270);
        self->step++;
        break;
    case 1:
        self->rotate -= ROT(11.25);
        if (self->ext.crossBoomerang.parent->step == 6 ||
            self->ext.crossBoomerang.parent->step == 7) {
            self->step++;
            self->ext.crossBoomerang.timer = (self->params + 1) * 4;
        }
        break;
    case 2:
        self->rotate -= ROT(11.25);
        if (--self->ext.crossBoomerang.timer == 0) {
            DestroyEntity(self);
            return;
        }
        break;
    }

    // get the x and y position from the parent (must align)
    temp = (s16*)&self->ext.crossBoomerang.unk84[0];
    temp += self->ext.crossBoomerang.unk80 * 2;
    self->posX.i.hi = *temp - g_Tilemap.scrollX.i.hi;
    temp++;
    self->posY.i.hi = *temp - g_Tilemap.scrollY.i.hi;
    self->ext.crossBoomerang.unk80++;
    self->ext.crossBoomerang.unk80 &= 0x3F;
}

extern u8 D_us_80181524[][8];

void RicEntitySubwpnCrashCrossParticles(Entity* self) {
    Primitive* prim;
    s16 posX;
    s16 posY;
    s16 halfSize;
    u8* uv;
    s16 depth;

    if (self->step == 0) {
        self->primIndex = g_api.AllocPrimitives(PRIM_GT4, 0x20);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags = FLAG_UNK_10000000 | FLAG_HAS_PRIMS;
        self->ext.timer.t = 0xC0;
        self->step++;
        return;
    }
    if (--self->ext.timer.t == 0) {
        DestroyEntity(self);
        return;
    }
    if (self->ext.timer.t > 8 && !(self->ext.timer.t & 3)) {
        for (prim = &g_PrimBuf[self->primIndex]; prim; prim = prim->next) {
            if (prim->r0 == 0) {
                prim->r0 = 1;
                prim->r1 = 0;
                break;
            }
        }
    }
    for (prim = &g_PrimBuf[self->primIndex]; prim; prim = prim->next) {
        if (!prim->r0) {
            continue;
        }
        if (prim->r1 == 0) {
            depth = rand() & 0x3F;
            prim->g0 = (rand() % 237) + 9;
            prim->g1 = 0xF0 - (rand() & 0x20);
            prim->clut = PAL_UNK_1B0;
            prim->tpage = 0x1A;
            prim->b0 = 0;
            prim->priority = RIC.zPriority + depth - 0x20;
            prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_TRANSP;
            prim->g3 = ((u8)depth >> 2) + 4;
            prim->r1++;
        } else {
            prim->g1 -= prim->g3;
            if ((u8)prim->b0 >= 6 || (u8)prim->g1 < 0x18) {
                prim->drawMode = DRAW_HIDE;
                prim->r0 = 0;
            }
        }
        if (!prim->r0) {
            continue;
        }
        posX = 0;
        posY = 0;
        posX |= prim->g0;
        posY |= prim->g1;
        uv = D_us_80181524[0];
        uv += prim->b0 * 8; // weird array indexing
        if (prim->b0 >= 3) {
            halfSize = 4;
        } else {
            halfSize = 8;
        }
        prim->x0 = posX - halfSize;
        prim->y0 = posY - halfSize;
        prim->x1 = posX + halfSize;
        prim->y1 = posY - halfSize;
        prim->x2 = posX - halfSize;
        prim->y2 = posY + halfSize;
        prim->x3 = posX + halfSize;
        prim->y3 = posY + halfSize;
        prim->u0 = *uv;
        uv++;
        prim->v0 = *uv;
        uv++;
        prim->u1 = *uv;
        uv++;
        prim->v1 = *uv;
        uv++;
        prim->u2 = *uv;
        uv++;
        prim->v2 = *uv;
        uv++;
        prim->u3 = *uv;
        uv++;
        prim->v3 = *uv;
        uv++;
        if (!(g_GameTimer & 1)) {
            prim->b0++;
        }
    }
}

extern EInit D_us_80180478;
extern u8 D_us_8018299C[];

typedef enum { AXE_INIT, AXE_FLYING, AXE_BOUNCE } AxeSteps;

void RicEntitySubwpnThrownAxe(Entity* self) {
    u8 rVal;
    u8 gVal;
    u8 bVal;
    s16 xVar;
    s16 yVar;
    s32 rgbIdx;
    s16 angle0;
    s16 angle1;
    s16 angle2;
    s16 angle3;
    s16 angleOffset;
    s32 twentyone;
    Primitive* prevPrim;
    s32 i;
    Primitive* prim;
    s32 graphicsTemp;

    twentyone = 21;

    switch (self->step) {
    case AXE_INIT:
        self->ext.subwpnAxe.subweaponId = PL_W_AXE;
        InitializeEntity(D_us_80180478);
        self->primIndex = g_api.AllocPrimitives(PRIM_GT4, 5);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags =
            FLAG_POS_CAMERA_LOCKED | FLAG_UNK_10000000 | FLAG_HAS_PRIMS;
        self->facingLeft = (RIC.facingLeft + 1) & 1;
        RicSetSpeedX(FIX(-2));
        self->velocityY = FIX(-6);
        if (self->facingLeft) {
            self->ext.subwpnAxe.unk7C = 0x400;
        } else {
            self->ext.subwpnAxe.unk7C = 0xC00;
        }

        self->posY.i.hi -= 12;
        for (prim = &g_PrimBuf[self->primIndex], i = 0; prim != NULL; i++,
            prim = prim->next) {
            prim->tpage = 0x1C;
            prim->u0 = 0;
            prim->v0 = 0;
            prim->u1 = 0x18;
            prim->v1 = 0;
            prim->u2 = 0;
            prim->v2 = 0x28;
            prim->u3 = 0x18;
            prim->v3 = 0x28;
            prim->priority = RIC.zPriority - 2;
            if (i != 0) {
                prim->drawMode = DRAW_UNK_100 | DRAW_TPAGE2 | DRAW_TPAGE |
                                 DRAW_HIDE | DRAW_COLORS | DRAW_TRANSP;
                self->ext.subwpnAxe.unk8C[i - 1] = 0;
                self->ext.subwpnAxe.unk90[i - 1] = 0;
                self->ext.subwpnAxe.unk94[i - 1] = 0;
            } else {
                prim->drawMode = DRAW_UNK_100 | DRAW_HIDE;
            }
        }
        self->hitboxWidth = 12;
        self->hitboxHeight = 12;
        g_api.PlaySfx(SFX_WEAPON_SWISH_C);
        self->ext.subwpnAxe.unk98 = 0x7F;
        self->step = 1;
        break;
    case AXE_FLYING:
        if (self->facingLeft) {
            angleOffset = -0x80;
        } else {
            angleOffset = 0x80;
        }
        self->ext.subwpnAxe.unk7C += angleOffset;
        if (!(self->ext.subwpnAxe.unk7C & 0x3FF)) {
            g_api.PlaySfxVolPan(
                SFX_WEAPON_SWISH_C, self->ext.subwpnAxe.unk98, 0);
            self->ext.subwpnAxe.unk98 -= 8;
            if (self->ext.subwpnAxe.unk98 < 0) {
                self->ext.subwpnAxe.unk98 = 0;
            }
        }
        self->velocityY += FIX(34.0 / 128);
        if (self->velocityY > FIX(8)) {
            self->velocityY = FIX(8);
        }
        self->posX.val += self->velocityX;
        self->posY.val += self->velocityY;
        if (self->posY.i.hi > 0x100) {
            DestroyEntity(self);
            return;
        }
        if (self->hitFlags == 2 || (self->flags & FLAG_DEAD)) {
            self->hitboxState = 0;
            self->velocityX = -(self->velocityX / 2);
            self->velocityY = FIX(-3);
            self->step = AXE_BOUNCE;
        }
        break;
    case AXE_BOUNCE:
        if (self->facingLeft) {
            angleOffset = 0xC0;
        } else {
            angleOffset = -0xC0;
        }
        self->ext.subwpnAxe.unk7C += angleOffset;
        self->velocityY += FIX(18.0 / 128);
        if (self->velocityY > FIX(8)) {
            self->velocityY = FIX(8);
        }
        self->posX.val += self->velocityX;
        self->posY.val += self->velocityY;
        if (self->posY.i.hi > 0x100) {
            DestroyEntity(self);
            return;
        }
        break;
    }

    if (self->poseTimer == 0) {
        graphicsTemp = self->pose;
        self->ext.subwpnAxe.unk8C[graphicsTemp] = 0;
        self->ext.subwpnAxe.unk90[graphicsTemp] = 1;
        self->ext.subwpnAxe.unk94[graphicsTemp] = 1;
        graphicsTemp++;
        graphicsTemp &= 3;
        self->pose = graphicsTemp;
        self->poseTimer = 2;
    } else {
        self->poseTimer--;
    }
    for (prim = &g_PrimBuf[self->primIndex], prevPrim = prim,
        graphicsTemp = ((g_GameTimer >> 1) & 1) + 0x1AB, i = 0;
         prim != NULL; i++, prim = prim->next) {
        prim->clut = graphicsTemp;
        if (i == 0) {
            if (self->facingLeft) {
                angle0 = 0x560;
                angle1 = 0x2A0;
                angle2 = 0xAA0;
                angle3 = 0xD60;
            } else {
                angle1 = 0x560;
                angle0 = 0x2A0;
                angle3 = 0xAA0;
                angle2 = 0xD60;
            }

            xVar = self->posX.i.hi;
            yVar = self->posY.i.hi;
            angleOffset = self->ext.subwpnAxe.unk7C;
            angle0 += angleOffset;
            angle1 += angleOffset;
            angle2 += angleOffset;
            angle3 += angleOffset;
            prim->x0 = xVar + (((rcos(angle0) << 4) * twentyone) >> 0x10);
            prim->y0 = yVar + -(((rsin(angle0) << 4) * twentyone) >> 0x10);
            prim->x1 = xVar + (((rcos(angle1) << 4) * twentyone) >> 0x10);
            prim->y1 = yVar + -(((rsin(angle1) << 4) * twentyone) >> 0x10);
            prim->x2 = xVar + (((rcos(angle2) << 4) * twentyone) >> 0x10);
            prim->y2 = yVar + -(((rsin(angle2) << 4) * twentyone) >> 0x10);
            prim->x3 = xVar + (((rcos(angle3) << 4) * twentyone) >> 0x10);
            prim->y3 = yVar + -(((rsin(angle3) << 4) * twentyone) >> 0x10);
            prim->drawMode &= ~DRAW_HIDE;
        } else if (self->ext.subwpnAxe.unk90[i - 1]) {
            if (self->ext.subwpnAxe.unk94[i - 1]) {
                self->ext.subwpnAxe.unk94[i - 1] = 0;
                prim->x0 = prevPrim->x0;
                prim->y0 = prevPrim->y0;
                prim->x1 = prevPrim->x1;
                prim->y1 = prevPrim->y1;
                prim->x2 = prevPrim->x2;
                prim->y2 = prevPrim->y2;
                prim->x3 = prevPrim->x3;
                prim->y3 = prevPrim->y3;
            }
            rgbIdx = self->ext.subwpnAxe.unk8C[i - 1]++;
            if (rgbIdx < 10) {
                rVal = D_us_8018299C[rgbIdx * 4 + 0];
                gVal = D_us_8018299C[rgbIdx * 4 + 1];
                bVal = D_us_8018299C[rgbIdx * 4 + 2];
                prim->r0 = rVal;
                prim->g0 = gVal;
                prim->b0 = bVal;
                prim->r1 = rVal;
                prim->g1 = gVal;
                prim->b1 = bVal;
                prim->r2 = rVal;
                prim->g2 = gVal;
                prim->b2 = bVal;
                prim->r3 = rVal;
                prim->g3 = gVal;
                prim->b3 = bVal;
                prim->drawMode &= ~DRAW_HIDE;
            } else {
                self->ext.subwpnAxe.unk90[i - 1] = 0;
                prim->drawMode |= DRAW_HIDE;
            }
        }
    }
}

extern EInit D_us_80180490;
extern u8 D_us_8018299C[];

void RicEntityCrashAxe(Entity* self) {
    Primitive* primFirst;
    Primitive* prim;
    s16 angle1;
    s16 angle2;
    s16 angle3;
    s16 angle4;
    s32 mod;
    s32 i;
    u8 r;
    u8 g;
    u8 b;
    s16 angleMod;
    s16 x;
    s16 y;
    s16 angle;
    s32 pose;
    s32 velocity;
    s32 colorRef;

    mod = 21;
    switch (self->step) {
    case 0:
        self->ext.subwpnAxe.subweaponId = 2;
        InitializeEntity(D_us_80180490);
        self->primIndex = g_api.AllocPrimitives(PRIM_GT4, 5);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags =
            FLAG_UNK_10000000 | FLAG_POS_CAMERA_LOCKED | FLAG_HAS_PRIMS;
        self->facingLeft = 0;
        self->ext.subwpnAxe.unk7C = ((self->params & 0xFF) << 9) + ROT(270);
        self->posY.i.hi -= 12;
        prim = &g_PrimBuf[self->primIndex];
        i = 0;
        while (prim) {
            prim->tpage = 0x1C;
            prim->u0 = prim->v0 = prim->v1 = prim->u2 = 0;
            prim->u1 = prim->u3 = 0x18;
            prim->v2 = prim->v3 = 0x28;
            prim->priority = RIC.zPriority + 4;
            if (i != 0) {
                prim->drawMode = DRAW_UNK_100 | DRAW_TPAGE2 | DRAW_TPAGE |
                                 DRAW_HIDE | DRAW_COLORS | DRAW_TRANSP;
                self->ext.subwpnAxe.unk8C[i - 1] = 0;
                self->ext.subwpnAxe.unk90[i - 1] = 0;
                self->ext.subwpnAxe.unk94[i - 1] = 0;
            } else {
                prim->drawMode = DRAW_UNK_100 | DRAW_HIDE;
            }
            i++;
            prim = prim->next;
        }
        self->hitboxHeight = self->hitboxWidth = 12;
        self->ext.subwpnAxe.angle = (self->params & 0xFF) << 9;
        self->ext.subwpnAxe.velocity = 16;
        self->step = 1;
        break;
    case 1:
        velocity = self->ext.subwpnAxe.velocity;
        self->ext.subwpnAxe.velocity++;
        if (self->ext.subwpnAxe.velocity > 0x28) {
            self->ext.subwpnAxe.unkA2 = 16;
            self->step++;
        }
        angle = self->ext.subwpnAxe.angle;
        self->ext.subwpnAxe.angle += 0xC0;
        self->ext.subwpnAxe.unk7C += 0x80;
        self->velocityX = velocity * rcos(angle);
        self->velocityY = velocity * -rsin(angle);
        self->posX.val += self->velocityX;
        self->posY.val += self->velocityY;
        break;
    case 2:
        if (--self->ext.subwpnAxe.unkA2 == 0) {
            self->ext.subwpnAxe.unkA2 = 8;
            self->step++;
        }
        velocity = self->ext.subwpnAxe.velocity;
        angle = self->ext.subwpnAxe.angle;
        self->ext.subwpnAxe.angle += 0xC0;
        self->ext.subwpnAxe.unk7C += 0x80;
        self->velocityX = rcos(angle) * velocity;
        self->velocityY = -rsin(angle) * velocity;
        self->posX.val += self->velocityX;
        self->posY.val += self->velocityY;
        break;
    case 3:
        if (--self->ext.subwpnAxe.unkA2 == 0) {
            g_Ric.unk4E = 1;
            self->flags &= ~FLAG_UNK_10000000;
        }
        velocity = self->ext.subwpnAxe.velocity;
        self->ext.subwpnAxe.velocity += 2;
        angle = self->ext.subwpnAxe.angle;
        self->ext.subwpnAxe.angle += 0x28;
        self->ext.subwpnAxe.unk7C += 0x80;
        self->velocityX = rcos(angle) * velocity;
        self->velocityY = -rsin(angle) * velocity;
        self->posX.val += self->velocityX;
        self->posY.val += self->velocityY;
        if (self->poseTimer == 0) {
            pose = self->pose;
            self->ext.subwpnAxe.unk8C[pose] = 0;
            self->ext.subwpnAxe.unk90[pose] = 1;
            self->ext.subwpnAxe.unk94[pose] = 1;
            pose++;
            pose &= 3;
            self->pose = pose;
            self->poseTimer = 2;
        } else {
            self->poseTimer--;
        }
        if ((self->hitFlags == 2) || (self->flags & FLAG_DEAD)) {
            self->velocityY = FIX(-3.0);
            self->hitboxState = 0;
            self->step = 4;
            self->velocityX = -((s32)self->velocityX / 2);
        }

        break;
    case 4:
        if (self->facingLeft) {
            angleMod = 0xC0;
        } else {
            angleMod = -0xC0;
        }
        self->ext.subwpnAxe.unk7C += angleMod;
        self->velocityY += 0x2400;
        if (self->velocityY > FIX(8.0)) {
            self->velocityY = FIX(8.0);
        }
        self->posY.val += self->velocityY;
        self->posX.val += self->velocityX;
        if (self->posY.i.hi > 256) {
            DestroyEntity(self);
            return;
        }
        break;
    }

    prim = &g_PrimBuf[self->primIndex];
    primFirst = prim;
    pose = ((g_GameTimer >> 1) & 1) + 0x1AB;
    i = 0;
    while (prim != NULL) {
        prim->clut = pose;
        if (i == 0) {
            if (self->facingLeft) {
                angle1 = 0x800 - 0x2A0;
                angle2 = 0x2A0;
                angle3 = 0x800 + 0x2A0;
                angle4 = 0x800 + 0x800 - 0x2A0;
            } else {
                angle2 = 0x800 - 0x2A0;
                angle1 = 0x2A0;
                angle4 = 0x800 + 0x2A0;
                angle3 = 0x800 + 0x800 - 0x2A0;
            }
            x = self->posX.i.hi;
            y = self->posY.i.hi;
            angleMod = self->ext.subwpnAxe.unk7C;
            angle1 += angleMod;
            angle2 += angleMod;
            angle3 += angleMod;
            angle4 += angleMod;

            prim->x0 = x + +(((rcos(angle1) << 4) * mod) >> 0x10);
            prim->y0 = y + -(((rsin(angle1) << 4) * mod) >> 0x10);
            prim->x1 = x + +(((rcos(angle2) << 4) * mod) >> 0x10);
            prim->y1 = y + -(((rsin(angle2) << 4) * mod) >> 0x10);
            prim->x2 = x + +(((rcos(angle3) << 4) * mod) >> 0x10);
            prim->y2 = y + -(((rsin(angle3) << 4) * mod) >> 0x10);
            prim->x3 = x + +(((rcos(angle4) << 4) * mod) >> 0x10);
            prim->y3 = y + -(((rsin(angle4) << 4) * mod) >> 0x10);
            prim->drawMode &= ~DRAW_HIDE;
        } else if (self->ext.subwpnAxe.unk90[i - 1]) {
            if (self->ext.subwpnAxe.unk94[i - 1]) {
                self->ext.subwpnAxe.unk94[i - 1] = 0;
                prim->x0 = primFirst->x0;
                prim->y0 = primFirst->y0;
                prim->x1 = primFirst->x1;
                prim->y1 = primFirst->y1;
                prim->x2 = primFirst->x2;
                prim->y2 = primFirst->y2;
                prim->x3 = primFirst->x3;
                prim->y3 = primFirst->y3;
            }
            colorRef = (self->ext.subwpnAxe.unk8C[i - 1]++);
            if (colorRef < 10) {
                r = D_us_8018299C[colorRef * 4 + 0];
                g = D_us_8018299C[colorRef * 4 + 1];
                b = D_us_8018299C[colorRef * 4 + 2];
                prim->r0 = r;
                prim->g0 = g;
                prim->b0 = b;
                prim->r1 = r;
                prim->g1 = g;
                prim->b1 = b;
                prim->r2 = r;
                prim->g2 = g;
                prim->b2 = b;
                prim->r3 = r;
                prim->g3 = g;
                prim->b3 = b;
                prim->drawMode &= ~DRAW_HIDE;
            } else {
                self->ext.subwpnAxe.unk90[i - 1] = 0;
                prim->drawMode |= DRAW_HIDE;
            }
        }
        i++;
        prim = prim->next;
    }
}

extern s16 D_us_801829C4[];
extern s32 D_us_801D10CC;

typedef enum {
    DAGGER_INIT,
    DAGGER_FLYING,
    DAGGER_BOUNCE,
    DAGGER_HIT_ENEMY
} DaggerSteps;

void RicEntitySubwpnKnife(Entity* self) {
    Collider collider;
    Primitive* prim;
    s16 offsetX;
    s16 offsetY;
    s16 angle1;
    s16 angle2;
    s16 angle3;
    s16 angle4;
    s16 x;
    s16 y;
#ifdef FIX_UB
    s16 xCol = 0;
#else
    s16 xCol;
#endif
    s32 modX;
    s32 modY;
    s32 i;

    switch (self->step) {
    case DAGGER_INIT:
        self->primIndex = g_api.AllocPrimitives(PRIM_GT4, 2);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags = FLAG_POS_CAMERA_LOCKED | FLAG_HAS_PRIMS;
        self->facingLeft = RIC.facingLeft;
        self->hitboxWidth = 4;
        self->hitboxHeight = 2;
        self->hitboxOffX = 4;
        self->hitboxOffY = 0;
        if (self->params & 0xFF00) {
            self->posY.i.hi += D_us_801829C4[D_us_801D10CC & 7];
            D_us_801D10CC++;
        } else {
            self->posY.i.hi -= 9;
        }
        prim = &g_PrimBuf[self->primIndex];
        prim->tpage = 0x1C;
        prim->clut = PAL_UNK_1AB;
        prim->u0 = prim->u1 = 0x18;
        prim->v0 = prim->v2 = 0x18;
        prim->u2 = prim->u3 = 0x20;
        prim->v1 = prim->v3 = 0;
        prim->priority = RIC.zPriority + 2;
        prim->drawMode = DRAW_HIDE | DRAW_UNK02;

        prim = prim->next;
        prim->type = PRIM_LINE_G2;
        prim->priority = RIC.zPriority + 2;
        prim->drawMode =
            DRAW_TPAGE2 | DRAW_TPAGE | DRAW_HIDE | DRAW_UNK02 | DRAW_TRANSP;
        prim->r0 = 0x7F;
        prim->g0 = 0x3F;
        prim->b0 = 0;
        RicSetSpeedX(FIX(8));
        g_api.PlaySfx(SFX_WEAPON_SWISH_C);
        self->step++;
        break;
    case DAGGER_FLYING:
        self->ext.subweapon.timer++;
        if (self->velocityX > 0) {
            xCol = 8;
        }
        if (self->velocityX < 0) {
            xCol = -8;
        }
        if (self->hitFlags == 1) {
            self->ext.subweapon.timer = 4;
            self->step = 3;
            self->hitboxState = 0;
            return;
        }
        for (i = 0; i < 8; i++) {
            if (self->velocityX > 0) {
                self->posX.i.hi++;
            }
            if (self->velocityX < 0) {
                self->posX.i.hi--;
            }
            g_api.CheckCollision(
                self->posX.i.hi + xCol, self->posY.i.hi, &collider, 0);
            if ((self->hitFlags == 2) || (collider.effects & EFFECT_BLOCK)) {
                self->ext.subweapon.timer = 64;
                self->velocityX = -(self->velocityX >> 3);
                self->velocityY = FIX(-2.5);
                self->hitboxState = 0;
                self->posX.i.hi += xCol;
                RicCreateEntFactoryFromEntity(self, FACTORY(BP_42, 2), 0);
                self->posX.i.hi -= xCol;
                g_api.PlaySfx(SFX_UI_SUBWEAPON_TINK);
                self->step++;
                return;
            }
        }
        x = self->posX.i.hi;
        y = self->posY.i.hi;
        offsetX = 12;
        offsetY = 8;
        if (self->facingLeft) {
            offsetX = -offsetX;
            offsetY = -offsetY;
        }
        prim = &g_PrimBuf[self->primIndex];
        prim->x0 = x - offsetX;
        prim->y0 = y - 4;
        prim->x1 = x + offsetX;
        prim->y1 = y - 4;
        prim->x2 = x - offsetX;
        prim->y2 = y + 4;
        prim->x3 = x + offsetX;
        prim->y3 = y + 4;
        prim->clut = ((g_GameTimer >> 1) & 1) + 0x1AB;
        prim->drawMode &= ~DRAW_HIDE;
        prim = prim->next;
        prim->x0 = x - offsetY;
        prim->y0 = y - 1;
        prim->x1 = x - (offsetX * (self->ext.subweapon.timer / 2));
        prim->y1 = y - 1;
        prim->drawMode &= ~DRAW_HIDE;
        if (self->step != 1) {
            prim->drawMode |= DRAW_HIDE;
        }
        break;
    case DAGGER_BOUNCE:
        prim = &g_PrimBuf[self->primIndex];
        if (--self->ext.subweapon.timer == 0) {
            DestroyEntity(self);
            return;
        }
        if (self->ext.subweapon.timer == 0x20) {
            prim->drawMode |=
                DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS | DRAW_TRANSP;
            PGREY(prim, 0) = PGREY(prim, 1) = PGREY(prim, 2) = PGREY(prim, 3) =
                0x60;
        }
        self->posX.val += self->velocityX;
        self->posY.val += self->velocityY;
        self->velocityY += FIX(0.125);
        x = self->posX.i.hi;
        y = self->posY.i.hi;
        offsetX = 12;
        if (self->facingLeft == 0) {
            angle1 = 0x800 - 0xD2;
            angle2 = 0xD2;
            angle3 = 0x800 + 0xD2;
            angle4 = -0xD2;
            self->rotate -= ROT(11.25);
        } else {
            angle2 = 0x800 - 0xD2;
            angle1 = 0xD2;
            angle4 = 0x800 + 0xD2;
            angle3 = -0xD2;
            self->rotate += ROT(11.25);
        }
        angle1 += self->rotate;
        angle2 += self->rotate;
        angle3 += self->rotate;
        angle4 += self->rotate;
        // offsetX is not used at all down here, but this block is needed.
        // It doesn't show up in the asm at all, but moves everything else into
        // alignment. Yet another lesson from PSP.
        if (self->facingLeft) {
            offsetX = -offsetX;
        }
        prim = &g_PrimBuf[self->primIndex];
        modX = (rcos(angle1) * 0xCA0) >> 0x14;
        modY = -(rsin(angle1) * 0xCA0) >> 0x14;
        prim->x0 = x + (s16)modX;
        prim->y0 = y - (s16)modY;
        modX = (rcos(angle2) * 0xCA0) >> 0x14;
        modY = -(rsin(angle2) * 0xCA0) >> 0x14;
        prim->x1 = x + (s16)modX;
        prim->y1 = y - (s16)modY;
        modX = (rcos(angle3) * 0xCA0) >> 0x14;
        modY = -(rsin(angle3) * 0xCA0) >> 0x14;
        prim->x2 = x + (s16)modX;
        prim->y2 = y - (s16)modY;
        modX = (rcos(angle4) * 0xCA0) >> 0x14;
        modY = -(rsin(angle4) * 0xCA0) >> 0x14;
        prim->x3 = x + (s16)modX;
        prim->y3 = y - (s16)modY;
        prim->clut = ((g_GameTimer >> 1) & 1) + 0x1AB;
        if (self->ext.subweapon.timer < 0x21) {
            prim->r0 -= 2;
            prim->g0 = prim->b0 = PGREY(prim, 1) = PGREY(prim, 2) =
                PGREY(prim, 3) = prim->r0;
        }
        prim->drawMode &= ~DRAW_HIDE;
        prim = prim->next;
        prim->drawMode |= DRAW_HIDE;
        break;
    case DAGGER_HIT_ENEMY:
        if (--self->ext.subweapon.timer == 0) {
            DestroyEntity(self);
            return;
        }
        break;
    }
}
