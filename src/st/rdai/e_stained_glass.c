// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rdai.h"
#include <scratchpad.h>

#include "../e_stained_glass_blend.h"

#include "../stained_glass_recurse.h"

extern EInit g_EInitInteractable;
extern SVECTOR D_us_80180B1C;
extern SVECTOR D_us_80180B24;
extern SVECTOR D_us_80180B2C;
extern SVECTOR D_us_80180B34;
extern SVECTOR D_us_80180B3C;
extern SVECTOR D_us_80180B44;
extern SVECTOR D_us_80180B4C;
extern SVECTOR D_us_80180B54;
extern SVECTOR D_us_80180C64;
extern VECTOR D_us_80180B5C[];
extern s16 D_us_80180C1C[];
extern CVECTOR D_us_80180C34[];

void func_us_801B2C28(Entity* self) {
    s16 midpointX, midpointY;
    s32 primIndex;
    SVECTOR rotVector;
    VECTOR transVector;
    MATRIX mtx;
    long p;
    long flag;
    u8 transparent; // u8, but used as bool
    s32 iterations;
    s16* yValsPtr;
    VECTOR* paramsPtr;
    CVECTOR* colorPtr;
    s32 count;
    Primitive* glassPrim;
    Primitive* lightPrim;
    Primitive* tempPrim;

    switch (self->step) {
    case 0: // init
        InitializeEntity(g_EInitInteractable);
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 60);
        if (primIndex != -1) {
            self->flags |= FLAG_HAS_PRIMS;
            self->primIndex = primIndex;
            glassPrim = &g_PrimBuf[primIndex];
            self->ext.stainedGlass.glassPrim = glassPrim;
            for (count = 0; count < 12; count++) {
                glassPrim->tpage = 15;
                glassPrim->clut = 0xE;
                glassPrim->u0 = glassPrim->u2 = 4;
                glassPrim->u1 = glassPrim->u3 = 28;
                glassPrim->v0 = glassPrim->v1 = 1;
                glassPrim->v2 = glassPrim->v3 = 174;
                PGREY(glassPrim, 0) = 96;
                LOW(glassPrim->r1) = LOW(glassPrim->r0);
                LOW(glassPrim->r2) = LOW(glassPrim->r0);
                LOW(glassPrim->r3) = LOW(glassPrim->r0);
                glassPrim->priority = 86;
                glassPrim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_TRANSP;
                glassPrim = glassPrim->next;
            }
            for (self->ext.stainedGlass.lightPrim = glassPrim;
                 glassPrim != NULL; glassPrim = glassPrim->next) {
                glassPrim->drawMode = DRAW_HIDE;
            }
            return;
        }
        DestroyEntity(self);
        return;
    case 1: // render
        SetGeomScreen(1024);
        SetGeomOffset(128, 160);
        glassPrim = self->ext.stainedGlass.glassPrim;
        lightPrim = self->ext.stainedGlass.lightPrim;
        paramsPtr = D_us_80180B5C;
        yValsPtr = D_us_80180C1C;
        colorPtr = D_us_80180C34;
        for (count = 0; count < 12; count++) {
            rotVector.vx = 0;
            rotVector.vy = *yValsPtr;
            rotVector.vz = 0;
            RotMatrix(&rotVector, &mtx);
            RotMatrixZ(ROT(180), &mtx);
            transVector = *paramsPtr;
            if (transVector.vx > 0) {
                transparent = true;
                glassPrim->drawMode =
                    DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS | DRAW_TRANSP;
            } else {
                transparent = false;
                glassPrim->drawMode = DRAW_COLORS;
            }
            iterations = paramsPtr->pad;
            transVector.vx += self->posX.i.hi - 128;
            transVector.vy += self->posY.i.hi - 160;
            transVector.vz += 1024;
            TransMatrix(&mtx, &transVector);
            SetRotMatrix(&mtx);
            SetTransMatrix(&mtx);
            CVEC(glassPrim->r0) = *colorPtr;
            LOW(glassPrim->r1) = LOW(glassPrim->r0);
            LOW(glassPrim->r2) = LOW(glassPrim->r0);
            LOW(glassPrim->r3) = LOW(glassPrim->r0);
            glassPrim->type = PRIM_GT4;
            if (iterations) {
                lightPrim = StainedGlassRecurse(
                    &D_us_80180B1C, &D_us_80180B24, &D_us_80180B2C,
                    &D_us_80180B34, glassPrim, iterations, lightPrim,
                    (u8*)SP(0));
                glassPrim->drawMode = DRAW_HIDE;
            }
            RotTransPers4(
                &D_us_80180B1C, &D_us_80180B24, &D_us_80180B2C, &D_us_80180B34,
                (long*)&glassPrim->x0, (long*)&glassPrim->x1,
                (long*)&glassPrim->x2, (long*)&glassPrim->x3, &p, &flag);
            // Renders the light "coming through" the right side glass
            if (transparent) {
                tempPrim = lightPrim->next;
                *lightPrim = *glassPrim;
                lightPrim->next = tempPrim;

                lightPrim->clut = PAL_FILL_WHITE;
                lightPrim->priority = glassPrim->priority - 1;
                lightPrim->drawMode = DRAW_COLORS;
                lightPrim->r0 = lightPrim->g0 = lightPrim->b0 = colorPtr->cd;
                LOW(lightPrim->r1) = LOW(lightPrim->r0);
                lightPrim->r2 = lightPrim->g2 = lightPrim->b2 =
                    colorPtr->cd / 2;
                LOW(lightPrim->r3) = LOW(lightPrim->r2);

                lightPrim = lightPrim->next;
                tempPrim = lightPrim->next;
                *lightPrim = *glassPrim;
                lightPrim->next = tempPrim;

                rotVector.vx = 0;
                rotVector.vy = *yValsPtr;
                rotVector.vz = 1024;
                RotMatrix(&D_us_80180C64, &mtx);
                RotMatrixY(rotVector.vy, &mtx);
                RotMatrixZ(rotVector.vz, &mtx);
                RotMatrixZ(ROT(180), &mtx);
                transVector = *paramsPtr;
                transVector.vx = 96;
                transVector.vy = -256;
                transVector.vx += self->posX.i.hi - 128;
                transVector.vy += self->posY.i.hi - 160;
                transVector.vz += 1024;
                TransMatrix(&mtx, &transVector);
                SetRotMatrix(&mtx);
                SetTransMatrix(&mtx);
                CVEC(lightPrim->r0) = *colorPtr;
                LOW(lightPrim->r1) = LOW(lightPrim->r0);
                LOW(lightPrim->r2) = LOW(lightPrim->r0);
                LOW(lightPrim->r3) = LOW(lightPrim->r0);
                lightPrim->type = PRIM_GT4;
                RotTransPers4(&D_us_80180B3C, &D_us_80180B44, &D_us_80180B4C,
                              &D_us_80180B54, (long*)&lightPrim->x0,
                              (long*)&lightPrim->x1, (long*)&lightPrim->x2,
                              (long*)&lightPrim->x3, &p, &flag);
                lightPrim->clut = 0x200;
                lightPrim->drawMode = DRAW_UNK_40 | DRAW_TPAGE2 | DRAW_TPAGE |
                                      DRAW_COLORS | DRAW_TRANSP;
                midpointX = (lightPrim->x0 + lightPrim->x2) / 2;
                midpointY = (lightPrim->y0 + lightPrim->y1) / 2;
                lightPrim = lightPrim->next;
                tempPrim = lightPrim->next;
                *lightPrim = *glassPrim;
                lightPrim->next = tempPrim;
                lightPrim->clut = PAL_FILL_WHITE;
                lightPrim->priority = glassPrim->priority + 1;
                lightPrim->drawMode =
                    DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS | DRAW_TRANSP;
                lightPrim->r0 = 24;
                lightPrim->g0 = 8;
                lightPrim->b0 = 32;
                LOW(lightPrim->r1) = LOW(lightPrim->r0);
                lightPrim->r2 = 8;
                lightPrim->g2 = 24;
                lightPrim->b2 = 8;
                lightPrim->r3 = lightPrim->g3 = lightPrim->b3 = 0;
                LOW(lightPrim->x0) = LOW(glassPrim->x1);
                LOW(lightPrim->x1) = LOW(glassPrim->x0);
                LOW(lightPrim->x2) = LOW(glassPrim->x3);
                lightPrim->x3 = midpointX;
                lightPrim->y3 = midpointY;
                lightPrim = lightPrim->next;
            }
            colorPtr++;
            yValsPtr++;
            paramsPtr++;
            glassPrim = glassPrim->next;
        }
        for (count = 0; lightPrim; lightPrim = lightPrim->next) {
            count++;
            lightPrim->drawMode = DRAW_HIDE;
        }
        FntPrint("rest %x\n", count);
    }
}

extern SVECTOR D_us_80180C6C;
extern SVECTOR D_us_80180C74;
extern SVECTOR D_us_80180C7C;
extern SVECTOR D_us_80180C84;
extern SVECTOR D_us_80180C8C;
extern SVECTOR D_us_80180D24;
extern VECTOR D_us_80180C94[];

void func_us_801B3368(Entity* self) {
    VECTOR transVector;
    MATRIX mtx;
    RECT rect;
    CVECTOR color;
    long point0;
    long p;
    long flag;
    long point1, point2, point3;
    s32 primIndex;
    VECTOR* transVectorPtr;
    s32 midindex1, midindex2;
    s32 idx;
    Primitive* prim;
    s16 tempY, tempX;
    s32 point0xy, point1xy, point2xy, point3xy;

    g_GpuBuffers[0].draw.r0 = 8;
    g_GpuBuffers[0].draw.g0 = 0;
    g_GpuBuffers[0].draw.b0 = 0x38;
    g_GpuBuffers[1].draw.r0 = 8;
    g_GpuBuffers[1].draw.g0 = 0;
    g_GpuBuffers[1].draw.b0 = 0x38;
    switch (self->step) {
    case 0: // init
        InitializeEntity(g_EInitInteractable);
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 19);
        if (primIndex != -1) {
            self->flags |= FLAG_HAS_PRIMS;
            self->primIndex = primIndex;
            prim = &g_PrimBuf[primIndex];
            for (self->ext.stainedGlass.glassPrim = prim; prim != NULL;
                 prim = prim->next) {
                prim->tpage = 15;
                prim->clut = 0xF;
                prim->u0 = prim->u2 = 35;
                prim->u1 = prim->u3 = 92;
                prim->v0 = prim->v1 = 1;
                prim->v2 = prim->v3 = 62;
                PGREY(prim, 0) = 128;
                LOW(prim->r1) = LOW(prim->r0);
                LOW(prim->r2) = LOW(prim->r0);
                LOW(prim->r3) = LOW(prim->r0);
                prim->priority = 84;
                prim->drawMode = DRAW_DEFAULT;
            }
            for (prim = self->ext.stainedGlass.glassPrim, idx = 0; idx < 4;
                 prim = prim->next, idx++) {
                prim->clut = 5;
                prim->u0 = prim->u2 = 129;
                prim->u1 = prim->u3 = 174;
                prim->v0 = prim->v1 = 1;
                prim->v2 = prim->v3 = 126;
                prim->priority = 80;
            }
            prim = self->ext.stainedGlass.glassPrim;
            PGREY(prim, 0) = 32;
            PGREY(prim, 1) = 48;
            PGREY(prim, 2) = 64;
            PGREY(prim, 3) = 48;
            prim = prim->next;
            prim->clut = PAL_FILL_WHITE;
            prim->r0 = 16;
            prim->g0 = 0;
            prim->b0 = 56;
            LOW(prim->r1) = LOW(prim->r0);
            LOW(prim->r2) = LOW(prim->r0);
            LOW(prim->r3) = LOW(prim->r0);
            prim->priority = 81;
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
            PGREY(prim, 0) = 64;
            PGREY(prim, 1) = 48;
            PGREY(prim, 2) = 80;
            PGREY(prim, 3) = 48;
            prim = prim->next;
            prim->clut = PAL_FILL_WHITE;
            prim->r0 = 16;
            prim->g0 = 0;
            prim->b0 = 56;
            LOW(prim->r1) = LOW(prim->r0);
            LOW(prim->r2) = LOW(prim->r0);
            LOW(prim->r3) = LOW(prim->r0);
            prim->priority = 81;
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
            prim->type = PRIM_G4;
            prim->r0 = 64;
            prim->g0 = 24;
            prim->b0 = 72;
            LOW(prim->r1) = LOW(prim->r0);
            prim->r2 = 200;
            prim->g2 = 24;
            prim->b2 = 104;
            LOW(prim->r2) = LOW(prim->r3);
            prim->priority = 82;
            prim->drawMode = DRAW_COLORS | DRAW_UNK02;
        } else {
            DestroyEntity(self);
            return;
        }
        rect.x = 0;
        rect.y = 256;
        rect.w = 16;
        rect.h = 1;
        color.r = 8;
        color.g = 0;
        color.b = 56;
        StainedGlassBlendPalette(&rect, 0xF, 0x201, COLORS_PER_PAL, &color);
        break;
    case 1: // render
        SetGeomScreen(1024);
        SetGeomOffset(128, 160);
        prim = self->ext.stainedGlass.glassPrim;
        for (transVectorPtr = D_us_80180C94, idx = 0; idx < 8; idx++,
            transVectorPtr++) {
            RotMatrix(&D_us_80180D24, &mtx);
            RotMatrixZ(ROT(180), &mtx);
            transVector = *transVectorPtr;
            transVector.vx += self->posX.i.hi - 128;
            transVector.vy += self->posY.i.hi - 160;
            transVector.vz += 1024;
            TransMatrix(&mtx, &transVector);
            SetRotMatrix(&mtx);
            SetTransMatrix(&mtx);
            if (idx == 0) {
                RotTransPers(&D_us_80180C8C, (long*)&point0, &p, &flag);
                prim->drawMode = DRAW_COLORS;
                tempX = point0;
                tempY = point0 >> 16;

                prim->x0 = prim->x2 = tempX - 45;
                prim->x1 = prim->x3 = tempX;
                prim->y0 = prim->y1 = tempY + 62;
                prim->y2 = prim->y3 = tempY - 62;
                prim = prim->next;
                prim->x0 = prim->x2 = tempX - 45;
                prim->x1 = prim->x3 = tempX;
                prim->y0 = prim->y1 = tempY + 62;
                prim->y2 = prim->y3 = tempY - 62;
                prim->drawMode = DRAW_TPAGE | DRAW_COLORS | DRAW_TRANSP;
                prim = prim->next;
                prim->x0 = prim->x2 = tempX + 45;
                prim->x1 = prim->x3 = tempX;
                prim->y0 = prim->y1 = tempY + 62;
                prim->y2 = prim->y3 = tempY - 62;
                prim->drawMode = DRAW_COLORS;
                prim = prim->next;
                prim->x0 = prim->x2 = tempX + 45;
                prim->x1 = prim->x3 = tempX;
                prim->y0 = prim->y1 = tempY + 62;
                prim->y2 = prim->y3 = tempY - 62;
                prim->drawMode = DRAW_TPAGE | DRAW_COLORS | DRAW_TRANSP;
                prim = prim->next;
                prim->x0 = tempX - 8;
                prim->x1 = tempX + 8;
                prim->x2 = self->posX.i.hi - 24;
                prim->x3 = self->posX.i.hi + 24;
                prim->y0 = prim->y1 = tempY - 56;
                prim->y2 = prim->y3 = self->posY.i.hi - 194;
                prim->drawMode = DRAW_COLORS;
                prim = prim->next;
            } else {
                RotTransPers4(&D_us_80180C6C, &D_us_80180C74, &D_us_80180C7C,
                              &D_us_80180C84, (long*)&point0, (long*)&point1,
                              (long*)&point2, (long*)&point3, &p, &flag);
                if (((Point16*)&point2)->y < 241) {
                    point0xy = point0;
                    point1xy = point1;
                    prim->clut = (idx * 2) + 0x201;
                    prim->drawMode = DRAW_DEFAULT;
                    point2xy = point2;
                    point3xy = point3;
                    midindex1 = ((point0xy + point1xy) / 2) & 0xFFFF0000;
                    midindex1 |=
                        (((Point16*)&point0)->x + ((Point16*)&point1)->x) >> 1;
                    midindex2 = (((point2xy + point3xy) / 2) & 0xFFFF0000);
                    midindex2 |=
                        ((((Point16*)&point2)->x + ((Point16*)&point3)->x) >>
                         1);
                    LOW(prim->x0) = point0xy;
                    LOW(prim->x1) = midindex1;
                    LOW(prim->x2) = point2xy;
                    LOW(prim->x3) = midindex2;
                    prim = prim->next;
                    prim->clut = (idx * 2) + 0x201;
                    LOW(prim->x0) = point1xy;
                    LOW(prim->x1) = midindex1;
                    LOW(prim->x2) = point3xy;
                    LOW(prim->x3) = midindex2;
                    prim->drawMode = DRAW_DEFAULT;
                    prim = prim->next;
                }
            }
        }
        for (; prim != NULL; prim = prim->next) {
            prim->drawMode = DRAW_HIDE;
        }
        break;
    }
}
