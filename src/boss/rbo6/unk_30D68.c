// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rbo6.h"
#include <scratchpad.h>

void EntityBackgroundVortex(Entity* self) {
    extern SVECTOR D_us_801B3634[0x100];
    extern u8 D_us_801B3E34[0x100];
    extern u16 g_EInitInteractable;
    extern s32 g_CutsceneFlags;
    u8 brightness; // writes into an array, later that array is used for colors
    u8 leftV;
    u8 rightV;
    s32 primIndex;
    s32 scale;
    s32 xSize;
    s32 ySize;
    s32 zSize;
    SVECTOR rotVector;
    VECTOR transVector;
    MATRIX m;
    DRAWENV draw_env;
    DR_ENV* dr_env;
    RECT tw_rect;
    CVECTOR unused_Cvector;

    s32 size;
    s16 angle;
    s32 vectorIndex1;
    s32 vectorIndex2;
    s32 j;
    CVECTOR* scratchColor;
    s32 var_s2;
    s32 i;
    Primitive* prim;

    switch (self->step) {
    case 0:
        InitializeEntity(&g_EInitInteractable);
        self->posX.i.hi = 0x80;
        self->posY.i.hi = 0x1A0;
        self->opacity = 0;
        primIndex = g_api.func_800EDB58(PRIM_GT4, 0x110);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.bgVortex.prim = prim;
        while (prim != NULL) {
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }
        self->ext.bgVortex.unk9C = 0x5F0;
        self->ext.bgVortex.unk9E = 0xB0;
        self->ext.bgVortex.unkA0 = 0;
        self->ext.bgVortex.unkAE = 0xD0;
        // Fallthrough
    case 1:
        size = 0x60;
        scale = 0;
        brightness = 0x10;
        var_s2 = 0;
        angle = 0;
        for (j = 0; j < 16; j++) {
            scale = SquareRoot0(j * 0x120) * 4;
            for (i = 0; i < 16; i++) {
                xSize = (size * rcos(angle + i * 0x100)) >> 0xC;
                ySize = (size * rsin(angle + i * 0x100)) >> 0xC;
                zSize = scale;
                D_us_801B3634[var_s2].vx = xSize;
                D_us_801B3634[var_s2].vy = ySize;
                D_us_801B3634[var_s2].vz = zSize;
                var_s2++;
            }
            D_us_801B3E34[j] = brightness;
            angle += 0x80;
            size += 0x1C;
            brightness += 0x28;
            if (brightness > 0xA0) {
                brightness = 0xA0;
            }
        }
        self->step++;
        break;
    case 2:
        prim = self->ext.bgVortex.prim;
        while (prim != NULL) {
            prim->tpage = 0x16;
            prim->clut = PAL_UNK_19E;
            prim->u0 = prim->u2 = 0x40;
            prim->u1 = prim->u3 = 0x80;
            prim->v0 = prim->v1 = 0;
            prim->v2 = prim->v3 = 0x40;
            prim->priority = 0x80;
            prim->drawMode = DRAW_DEFAULT;
            prim = prim->next;
        }
        prim = self->ext.bgVortex.prim;
        draw_env = g_CurrentBuffer->draw;

        dr_env = g_api.func_800EDB08((POLY_GT4*)prim);
        if (dr_env == NULL) {
            DestroyEntity(self);
            return;
        }
        prim->type = PRIM_ENV;
        draw_env.isbg = 0;
        draw_env.r0 = 0;
        draw_env.g0 = 0;
        draw_env.b0 = 0;
        draw_env.dtd = 0;
        draw_env.clip.x = 0;
        draw_env.ofs[0] = 0;
        tw_rect.x = 0;
        tw_rect.y = 0;
        tw_rect.w = 0x40;
        tw_rect.h = 0x40;
        draw_env.tw = tw_rect;
        SetDrawEnv(dr_env, &draw_env);
        prim->priority = 2;
        prim->drawMode = DRAW_UNK_1000;
        prim = prim->next;
        dr_env = g_api.func_800EDB08((POLY_GT4*)prim);
        if (dr_env == NULL) {
            DestroyEntity(self);
            return;
        }
        prim->type = PRIM_ENV;
        prim->priority = 0x59;
        prim->drawMode = DRAW_UNK_800;
        prim = prim->next;
        self->step++;
        break;
    case 3:
        if (g_CutsceneFlags & 0x20) {
            if (self->opacity < 0x80) {
                self->opacity++;
            }
        }
        switch (self->step_s) {
        case 0:
            self->posY.val -= FIX(0.75);
            if (self->posY.i.hi < 0xA0) {
                self->posY.i.hi = 0xA0;
                self->step_s++;
            }
            break;
        case 1:
            self->ext.bgVortex.unkA4 += 16;
            self->ext.bgVortex.unkA6 += 8;
            self->ext.bgVortex.unkA8 += 32;
            self->ext.bgVortex.unkAA += 2;
            self->ext.bgVortex.unk9C =
                ((rsin(self->ext.bgVortex.unkA4) << 6) >> 0xC) + 0x5F0;
            self->ext.bgVortex.unk9E =
                ((rsin(self->ext.bgVortex.unkA6) << 7) >> 0xC) + 0xB0;
            self->ext.bgVortex.unkA0 =
                ((rsin(self->ext.bgVortex.unkA8) << 4) >> 0xC);
            self->ext.bgVortex.unkAE =
                ((rsin(self->ext.bgVortex.unkAA) * 24) >> 0xC) + 0xD0;
            break;
        }
        prim = self->ext.bgVortex.prim;
        prim = prim->next;
        prim = prim->next;
        leftV = prim->v0;
        rightV = prim->v2;
        leftV += 2;
        rightV += 2;

        if (rightV < leftV) {
            leftV = rightV;
            rightV = leftV + 0x40;
        }
        while (prim != NULL) {
            prim->v0 = prim->v1 = leftV;
            prim->v2 = prim->v3 = rightV;
            prim = prim->next;
        }
        self->ext.bgVortex.unk80 -= 4;
        SetGeomScreen(0xC0);
        SetGeomOffset(self->posX.i.hi, self->posY.i.hi);
        SetFarColor(0, 0, 0);
        SetFogNear(0x128, 0xC0);
        rotVector.vx = 0;
        rotVector.vy = 0;
        rotVector.vz = self->ext.bgVortex.unk80;
        rotVector.vx += self->ext.bgVortex.unk9C;
        rotVector.vy += self->ext.bgVortex.unk9E;
        rotVector.vz += self->ext.bgVortex.unkA0;

        RotMatrix(&rotVector, &m);
        SetRotMatrix(&m);
        transVector.vx = 0;
        transVector.vy = 0;
        transVector.vz = 0xC0;
        transVector.vz += self->ext.bgVortex.unkAE;
        TransMatrix(&m, &transVector);
        SetTransMatrix(&m);
        // scratchpad memory
        scratchColor = (CVECTOR*)SP(0);
        scale = self->opacity;
        for (i = 0; i < 16; i++, scratchColor++) {
            var_s2 = ((i & 1) * 2) + 1;
            scratchColor->b = ((D_us_801B3E34[i] / var_s2) * scale) / 0x80;
            scratchColor->r = scratchColor->g =
                (((D_us_801B3E34[i] / 2) / var_s2) * scale) / 0x80;
            scratchColor->cd = 4;
        }
        prim = self->ext.bgVortex.prim;
        prim = prim->next;
        prim = prim->next;
        unused_Cvector.r = 0x80;
        unused_Cvector.g = 0x80;
        unused_Cvector.b = 0x80;
        unused_Cvector.cd = 4;
        scratchColor = (CVECTOR*)SP(0);
        for (i = 0; i < 15; i++) {
            for (j = 0; j < 16; j++) {
                var_s2 = i * 0x10;
                vectorIndex1 = var_s2 + j;
                vectorIndex2 = var_s2 + ((j + 1) & 0xF);
                gte_ldv0(&D_us_801B3634[vectorIndex1]);
                gte_rtps();
                gte_stsxy((long*)&prim->x0);
                gte_ldrgb(&scratchColor[i]);
                gte_dpcs();
                gte_strgb(&prim->r0);
                prim->type = PRIM_GT4;
                gte_ldv0(&D_us_801B3634[vectorIndex2]);
                gte_rtps();
                gte_stsxy((long*)&prim->x1);
                gte_ldrgb(&scratchColor[i]);
                gte_dpcs();
                if ((prim->y0 >= 0) || (prim->y1 >= 0)) {
                    gte_strgb(&prim->r1);
                    gte_ldv0(&D_us_801B3634[vectorIndex1] + 0x10);
                    gte_rtps();
                    if (prim->y0 <= 0x100 || prim->y1 <= 0x100) {
                        gte_stsxy((long*)&prim->x2);
                        gte_ldrgb(&scratchColor[i] + 1);
                        gte_dpcs();
                        gte_strgb(&prim->r2);
                        gte_ldv0(&D_us_801B3634[vectorIndex2] + 0x10);
                        gte_rtps();
                        gte_stsxy((long*)&prim->x3);
                        gte_ldrgb(&scratchColor[i] + 1);
                        gte_dpcs();
                        if (prim->x0 <= 0x100 || prim->x1 <= 0x100 ||
                            prim->x2 <= 0x100 || prim->x3 <= 0x100) {
                            gte_strgb(&prim->r3);
                            if (prim->x0 >= 0 || prim->x1 >= 0 ||
                                prim->x2 >= 0 || prim->x3 >= 0) {
                                gte_stszotz((long*)&zSize);
                                if (zSize < 0x55) {
                                    prim->priority = 0x58 - zSize;
                                } else {
                                    prim->priority = 3;
                                }
                                prim->drawMode = DRAW_COLORS;
                                prim = prim->next;
                            }
                        }
                    }
                }
            }
        }
        while (prim != NULL) {
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }
    }
}

INCLUDE_RODATA("boss/rbo6/nonmatchings/unk_30D68", D_us_8019D0AC);

typedef struct {
    MATRIX matrices[2];
    SVECTOR rotation;
    SVECTOR edges[2];
    s32 positions[14];
    s32 depths[7];
    CVECTOR color;
    u8 brightness[7];
} DraculaFinalScratchpad;

#define offsetof(st, m) (size_t)((size_t) & (((st*)0)->m))

void func_us_801B1738(Entity* self) {
    extern u16 g_EInitInteractable;
    extern s32 g_CutsceneFlags;
    extern s32 D_us_801806E4;
    extern s32 D_us_80181484;
    extern s32 D_us_80181488;
    extern SVECTOR D_us_8018148C[4];
    extern SVECTOR* D_us_8018150C[];
    extern s16 D_us_8018162C[][3];
    extern SVECTOR D_us_801B3F34;
    extern s16 D_us_801B3F3C;
    extern s16 D_us_801B3F40;
    extern s16 D_us_801B3F44;
    extern s32 D_us_801B3F48;
    s16 angle;
    s16 radius;
    u8* brightness;
    MATRIX* m;
    s32* positions;
    u8 fade;
    s32 j;
    Primitive* prim;
    s32 primIndex;
    s32 i;
    s32 depthOffset;
    s16* angles;
    s32* depths;
    SVECTOR* ring;
    CVECTOR* color;
    SVECTOR* edges;
    SVECTOR** vectors;
    SVECTOR* rotation;
    Entity* entity;
    s16* spawn;
    s32 result;
    s32 xMask, yMask;
    DR_ENV* drEnv;
    VECTOR translation;
    RECT rect;
    DRAWENV drawEnv;

    FntPrint("d_step %x\n", self->step);
    switch (self->step) {
    case 0:
        InitializeEntity(&g_EInitInteractable);
        self->zPriority = 0x80;
        self->flags |= FLAG_UNK_10000;
        g_Tilemap.flags &= 0xFFFE;
        g_BgLayers[0].flags &= 0xFFFE;
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 0x2E);
        if (primIndex == -1) {
            self->step = 0;
            return;
        }
        prim = &g_PrimBuf[primIndex];
        self->primIndex = primIndex;
        self->flags |= FLAG_HAS_PRIMS;
        drEnv = g_api.func_800EDB08((POLY_GT4*)prim);
        if (drEnv == NULL) {
            g_api.FreePrimitives(primIndex);
            self->step = 0;
            self->flags &= ~FLAG_HAS_PRIMS;
            return;
        }
        prim->type = PRIM_ENV;
        prim->drawMode = DRAW_HIDE;
        prim = prim->next;
        drEnv = g_api.func_800EDB08((POLY_GT4*)prim);
        // The original checks the primitive, not the second environment result.
        if (prim == NULL) {
            g_api.FreePrimitives(primIndex);
            self->step = 0;
            self->flags &= ~FLAG_HAS_PRIMS;
            return;
        }
        prim->type = PRIM_ENV;
        prim->drawMode = DRAW_HIDE;
        prim = prim->next;
        self->ext.draculaFinal3D.mesh = prim;
        for (i = 0; i < 20; i++) {
            prim->type = PRIM_GT3;
            prim->tpage = 0x114;
            prim->clut = PAL_UNK_194;
            prim->u0 = 0xC0;
            prim->v0 = 0xD;
            prim->u1 = 0x90;
            prim->v1 = 0x60;
            prim->u2 = 0xF0;
            prim->v2 = 0x60;
            prim->priority = 0x80;
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }
        self->ext.draculaFinal3D.ribbons = prim;
        while (prim != NULL) {
            prim->priority = 0x80;
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }
        angles = self->ext.draculaFinal3D.angles;
        ring = D_us_8018148C;
        for (i = 0; i < 4; i++, angles++, ring++) {
            *angles = ring->pad;
        }
        self->scaleX = 0x100;
        D_us_801B3F3C = 0x100;
        D_us_801B3F40 = 0x200;
        D_us_801B3F44 = 0x700;
        self->ext.draculaFinal3D.rotationSpeedX = 4;
        self->ext.draculaFinal3D.rotationSpeedY = 8;
        D_us_801B3F48 = 0;
        self->rotate = 2;
        self->ext.draculaFinal3D.depth = 0;
        break;
    case 1:
        if (g_CutsceneFlags & 0x20) {
            D_us_80181484 = 1;
            D_us_801B3F48 = 0x10;
            self->step++;
        }
        break;
    case 2:
        D_us_801B3F48++;
        if (D_us_801B3F48 > 0x80) {
            D_us_801B3F48 = 0x80;
            self->step++;
        }
        break;
    case 3:
        if (D_us_801806E4 & 2) {
            self->step++;
        }
        break;
    case 4:
        if (self->ext.draculaFinal3D.rotationSpeedX < 0x18) {
            self->ext.draculaFinal3D.rotationSpeedX += 2;
        }
        if (self->ext.draculaFinal3D.rotationSpeedY < 0x18) {
            self->ext.draculaFinal3D.rotationSpeedY += 2;
        }
        if (self->rotate < ROT(45)) {
            self->rotate += 2;
        }
        self->ext.draculaFinal3D.depth += 0x50;
        if (self->ext.draculaFinal3D.depth > 0x1200) {
            D_us_80181488 = 1;
            self->ext.draculaFinal3D.timer = 0x40;
            CreateEntityFromCurrentEntity(E_UNK_31, &g_Entities[159]);
            self->step++;
        }
        break;
    case 5:
        if (D_us_801B3F48 < 0xA0) {
            D_us_801B3F48 += 2;
        }
        if (self->ext.draculaFinal3D.rotationSpeedX > 0x10) {
            self->ext.draculaFinal3D.rotationSpeedX -= 6;
        }
        if (self->ext.draculaFinal3D.rotationSpeedY > 0x10) {
            self->ext.draculaFinal3D.rotationSpeedY -= 6;
        }
        if (self->rotate > ROT(1.40625)) {
            self->rotate -= 12;
        }
        if (!--self->ext.draculaFinal3D.timer) {
            self->step++;
        }
        break;
    case 6:
        D_us_801B3F48 -= 10;
        if (D_us_801B3F48 < 0x10) {
            D_us_801B3F48 = 0;
            self->ext.draculaFinal3D.timer = 0x60;
            self->step++;
        }
        break;
    case 7:
        prim = self->ext.draculaFinal3D.mesh;
        while (prim != NULL) {
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }
        if (!--self->ext.draculaFinal3D.timer) {
            DestroyEntity(self);
        }
        return;
    }

    prim = &g_PrimBuf[self->primIndex];
    drawEnv = g_CurrentBuffer->draw;
    drawEnv.isbg = 1;
    drawEnv.r0 = 0;
    drawEnv.g0 = 0;
    drawEnv.b0 = 0;
    rect.x = 0x180;
    rect.y = 0x100;
    rect.w = 0x7F;
    rect.h = 0x80;
    drawEnv.clip = rect;
    drawEnv.ofs[0] = 0x180;
    drawEnv.ofs[1] = 0x100;
    drEnv = PRIM_DR_ENV(prim);
    SetDrawEnv(drEnv, &drawEnv);
    prim->priority = 0x27;
    prim->drawMode = DRAW_DEFAULT;
    prim = prim->next;
    prim->priority = 0x29;
    prim->drawMode = DRAW_UNK_800;
    i = g_Timer & 3;
    if (i < 3 && (rand() & 3)) {
        spawn = D_us_8018162C[i];
        entity = AllocEntity(&g_Entities[192], &g_Entities[219]);
        if (entity != NULL) {
            CreateEntityFromCurrentEntity(E_UNK_30, entity);
            entity->zPriority = 0x28;
            entity->rotate = spawn[2];
            if (D_us_80181488) {
                entity->rotate += Random() * 2 - 0x100;
            } else {
                entity->rotate += Random() - 0x80;
            }
            entity->posX.i.hi = spawn[0];
            entity->posY.i.hi = spawn[1];
        }
    }
    D_us_801B3F34.vx += self->ext.draculaFinal3D.rotationSpeedX;
    D_us_801B3F34.vy += self->ext.draculaFinal3D.rotationSpeedY;
    D_us_801B3F34.vz += self->rotate;
    D_us_801B3F3C += 2;
    D_us_801B3F40 += 4;
    D_us_801B3F44 += 3;
    if (self->ext.draculaFinal3D.depth) {
        D_us_801B3F3C += 8;
        D_us_801B3F40 += 16;
        D_us_801B3F44 += 12;
    }
    color = (CVECTOR*)SP(offsetof(DraculaFinalScratchpad, color));
    color->r = color->g = color->b = 0x80;
    color->r =
        D_us_801B3F48 + (((D_us_801B3F48 / 2) * rcos(D_us_801B3F3C)) >> 12);
    color->g =
        D_us_801B3F48 + (((D_us_801B3F48 / 2) * rsin(D_us_801B3F40)) >> 12);
    color->b =
        D_us_801B3F48 + (((D_us_801B3F48 / 2) * rcos(D_us_801B3F44)) >> 12);
    color->cd = 5;
    m = (MATRIX*)SP(offsetof(DraculaFinalScratchpad, matrices));
    rotation = (SVECTOR*)SP(offsetof(DraculaFinalScratchpad, rotation));
    depths = (s32*)SP(offsetof(DraculaFinalScratchpad, depths));
    SetGeomScreen(0x600);
    SetGeomOffset(0x80, 0x80);
    SetFarColor(0, 0, 0);
    SetFogNear(0x200, 0x600);
    *rotation = D_us_801B3F34;
    RotMatrix(rotation, m);
    SetRotMatrix(m);
    translation.vx = 0;
    translation.vy = 0;
    translation.vz = -0x18;
    translation.vz += self->ext.draculaFinal3D.depth;
    depthOffset = translation.vz >> 2;
    gte_ldtr(0, 0, translation.vz);
    prim = self->ext.draculaFinal3D.mesh;
    vectors = D_us_8018150C;
    for (i = 0; i < 20; i++) {
        gte_ldv3(vectors[0], vectors[1], vectors[2]);
        gte_rtpt();
        gte_stsxy3_gt3(prim);
        *(CVECTOR*)&prim->r0 = *color;
        LOW(prim->r1) = LOW(prim->r0);
        LOW(prim->r2) = LOW(prim->r0);
        prim->drawMode = DRAW_COLORS | DRAW_UNK02;
        gte_nclip();
        gte_stopz(depths);
        if (!self->ext.draculaFinal3D.depth && *depths > 0) {
            prim->drawMode = DRAW_HIDE;
        }
        xMask = (prim->x0 & 0x100) + (prim->x1 & 0x100) + (prim->x2 & 0x100);
        yMask = (prim->y0 & 0x100) + (prim->y1 & 0x100) + (prim->y2 & 0x100);
        if (xMask > 0x300 || yMask > 0x300) {
            prim->drawMode = DRAW_HIDE;
        }
        gte_avsz3();
        gte_stszotz((long*)depths);
        prim->type = PRIM_GT3;
        result = 0x80 - ((*depths - depthOffset) >> 2);
        if (!self->ext.draculaFinal3D.depth) {
            result -= 2;
        }
        if (result > 0x1F8) {
            result = 0x1F8;
        }
        if (result < 4) {
            result = 4;
        }
        prim->priority = result;
        vectors += 3;
        prim = prim->next;
    }
    if (!D_us_80181484 || (D_us_801806E4 & 1)) {
        while (prim != NULL) {
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }
        return;
    }
    angles = self->ext.draculaFinal3D.angles;
    for (i = 0; i < 4; i++, angles++) {
        *angles += 0x38;
        if (*angles > 0 && *angles <= 0x38) {
            g_api.PlaySfx(SFX_ELECTRICITY);
        }
        if (*angles > 0x2000) {
            *angles = -(*angles & 0xFFF);
        }
    }
    prim = self->ext.draculaFinal3D.ribbons;
    angles = self->ext.draculaFinal3D.angles;
    ring = D_us_8018148C;
    m = (MATRIX*)SP(offsetof(DraculaFinalScratchpad, matrices));
    rotation = (SVECTOR*)SP(offsetof(DraculaFinalScratchpad, rotation));
    edges = (SVECTOR*)SP(offsetof(DraculaFinalScratchpad, edges));
    brightness = (u8*)SP(offsetof(DraculaFinalScratchpad, brightness));
    depths = (s32*)SP(offsetof(DraculaFinalScratchpad, depths));
    SetGeomScreen(0x600);
    SetGeomOffset(0x80, 0x80);
    gte_ldtr(0, 0, 0x600);
    edges[0].vx = 0;
    edges[0].vy = -12;
    edges[1].vx = 0;
    edges[1].vy = 12;
    for (i = 0; i < 4; i++, angles++, ring++) {
        angle = *angles;
        if (angle >= 0) {
            rotation->vx += ring->vx;
            rotation->vy += ring->vy;
            rotation->vz += ring->vz;
            RotMatrix(rotation, &m[1]);
            gte_SetColorMatrix(&m[1]);
            fade = 0;
            positions = (s32*)SP(offsetof(DraculaFinalScratchpad, positions));
            for (j = 0; j < 7; j++) {
                radius = 0x90 - (angle * 0x78) / 0x1800;
                if (radius < 0x18) {
                    radius = 0x18;
                }
                edges[0].vz = -radius;
                edges[1].vz = -radius;
                LOW(m->m[0][0]) = 0;
                LOW(m->m[0][2]) = 0;
                LOW(m->m[1][1]) = 0;
                LOW(m->m[2][0]) = 0;
                LOW(m->m[2][2]) = 0;
                m->m[0][0] = 0x1000;
                m->m[1][1] = 0x1000;
                m->m[2][2] = 0x1000;
                RotMatrixY(angle, m);
                gte_ldclmv(m);
                gte_lcir();
                gte_stclmv(m);
                gte_ldclmv(&m->m[0][1]);
                gte_lcir();
                gte_stclmv(&m->m[0][1]);
                gte_ldclmv(&m->m[0][2]);
                gte_lcir();
                gte_stclmv(&m->m[0][2]);
                gte_SetRotMatrix(m);
                gte_ldv01c(edges);
                gte_rtpt();
                gte_stsxy01c(&positions[j * 2]);
                gte_stszotz((long*)&depths[j]);
                if (angle < 0) {
                    fade++;
                    if (fade > 4) {
                        fade = 4;
                    }
                    brightness[j] = 0x80 - fade * 0x20;
                } else {
                    fade = 0;
                    brightness[j] = 0x80;
                }
                angle -= ratan2(0x10, radius);
                if (angle > 0x1800) {
                    brightness[j] = 0x60;
                }
                // The original overwrites the brightness for this angle range.
                result = angle <= 0x1800;
                if (!result) {
                    brightness[j] = 0;
                }
            }
            positions = (s32*)SP(offsetof(DraculaFinalScratchpad, positions));
            for (j = 0; j < 6; j++) {
                prim->tpage = 0x1A;
                prim->clut = PAL_UNK_194;
                prim->u0 = prim->u2 = j * 0x10 + 0x90;
                prim->u1 = prim->u3 = prim->u0 + 0xF;
                if (g_Timer & 2) {
                    prim->v0 = prim->v1 = 0xC0;
                    prim->v2 = prim->v3 = 0xD0;
                } else {
                    prim->v0 = prim->v1 = 0xD0;
                    prim->v2 = prim->v3 = 0xC0;
                }
                LOW(prim->x0) = positions[0];
                LOW(prim->x1) = positions[2];
                LOW(prim->x2) = positions[1];
                LOW(prim->x3) = positions[3];
                prim->priority = depths[j] - 0x100;
                prim->drawMode = DRAW_UNK02;
                fade = (brightness + j)[1];
                if (fade != 0x80) {
                    prim->r0 = prim->g0 = prim->b0 = brightness[j];
                    LOW(prim->r2) = LOW(prim->r0);
                    prim->r1 = prim->g1 = prim->b1 = (brightness + j)[1];
                    LOW(prim->r3) = LOW(prim->r1);
                    prim->drawMode |=
                        DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS | DRAW_TRANSP;
                }
                prim = prim->next;
                positions += 2;
            }
        }
    }
    while (prim != NULL) {
        prim->drawMode = DRAW_HIDE;
        prim = prim->next;
    }
}

void func_us_801B2864(Entity* self) {
    extern u16 g_EInitInteractable;
    extern s32 D_us_80181488;
    extern u8 D_us_80181648[];
    u16 angle;

    switch (self->step) {
    case 0:
        InitializeEntity(&g_EInitInteractable);
        self->palette = 0x2E5;
        self->animSet = 0xE;
        self->unk5A = 0x79;
        self->drawFlags = ENTITY_ROTATE;
        self->flags |= FLAG_UNK_10000;
        self->blendMode = BLEND_QUARTER | BLEND_TRANSP;
        self->flags &= ~FLAG_POS_CAMERA_LOCKED;
        self->facingLeft = Random() & 1;
        angle = self->rotate;
        if (self->facingLeft != 0) {
            self->rotate = -angle;
        }
        self->velocityX = rsin((s32)(s16)angle) * 0x28;
        self->velocityY = -(rcos((s32)(s16)angle) * 0x28);
        self->scaleX = 0xE0;
        self->drawFlags |= ENTITY_SCALEY | ENTITY_SCALEX;
        self->scaleY = 0x140;
        if (D_us_80181488 != 0) {
            self->scaleX = 0x120;
            self->scaleY = 0x120;
        }
        /* fall through */
    case 1:
        MoveEntity();
        if (AnimateEntity(D_us_80181648, self) == 0) {
            DestroyEntity(self);
        }
        break;
    }
}
