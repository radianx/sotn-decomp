// SPDX-License-Identifier: AGPL-3.0-or-later
#include "st0.h"
#include <scratchpad.h>

typedef struct {
    Point16 unk0;
    s16 unk4;
    s16 unk6;
    s16 unk8;
    s16 unkA;
    s16 unkC;
    s16 unkE;
    s32 unk10;
    s16 unk14;
} unkstr_801C06B0;

static SVECTOR D_80182690 = {-8, -8, 0};
static SVECTOR D_80182698 = {8, -8, 0};
static SVECTOR D_801826A0 = {-8, 8, 0};
static SVECTOR D_801826A8 = {8, 8, 0};
static SVECTOR unused = {0, 0, 0};
#ifdef VERSION_PC
#define BG_PART_CAPACITY (19 * 15)
static s32 s_WideCapture;
#define BG_PART_COUNT (s_WideCapture ? BG_PART_CAPACITY : 15 * 15)
#else
#define BG_PART_CAPACITY (15 * 15)
#define BG_PART_COUNT (15 * 15)
#endif
static unkstr_801C06B0 D_801C06B0[BG_PART_CAPACITY];

#ifdef VERSION_PC
static const s16 s_EdgeX[] = {-34, -17, 255, 272};
static const s16 s_CaptureBands[] = {20, 64, 112, 160, 208, 227};

static Point16 BackgroundPieceOrigin(s32 i) {
    if (i < 225)
        return (Point16){(i % 15) * 17, (i / 15) * 16};
    return (Point16){s_EdgeX[(i - 225) % 4], ((i - 225) / 4) * 16};
}

static RECT BackgroundPieceRect(s32 i) {
    Point16 p = BackgroundPieceOrigin(i);
    s32 left = MAX(p.x, -20), top = MAX(p.y, 20);
    s32 right = MIN(p.x + 17, 276), bottom = MIN(p.y + 16, 227);
    return (RECT){left, top, right - left, MAX(bottom - top, 0)};
}

static s32 CaptureWideBackground(Entity* self) {
    Primitive* prim = self->ext.prim;
    DR_ENV* env = NULL;
    s32 i, n = 0;
    RECT source;
    s32 x, y;
    // The visible 296x207 pixels fit the original 256x256 scratch texture.
    for (i = 0; i < 11; i++) {
        if (i % 3 == 0) {
            env = g_api.func_800EDB08((POLY_GT4*)prim);
            if (!env)
                return 0;
            prim->type = PRIM_ENV;
            prim->priority = 0x69;
            prim->drawMode = DRAW_DEFAULT;
            setlen(env, 0);
            prim = prim->next;
            n = 0;
        }
        if (!i) {
            source = (RECT){0, 20, 255, 207};
            x = 768;
            y = 0;
        } else {
            s32 band = (i - 1) / 2;
            s32 right = (i - 1) % 2;
            source =
                (RECT){right ? 255 : -20, s_CaptureBands[band], right ? 21 : 20,
                       s_CaptureBands[band + 1] - s_CaptureBands[band]};
            x = 768 + band * 41 + (right ? 20 : 0);
            y = 207;
        }
        env->code[n++] = (u_long)PC_COPY_DRAW_AREA_OPCODE << 24;
        env->code[n++] = ((u16)source.y << 16) | (u16)source.x;
        env->code[n++] = (y << 16) | x;
        env->code[n++] = ((u16)source.h << 16) | (u16)source.w;
        setlen(env, n);
    }
    return 1;
}

static void InitializeWideBackground(Primitive* prim) {
    s32 i, u, v, band;
    for (i = 0; i < BG_PART_COUNT; i++, prim = prim->next) {
        RECT r = BackgroundPieceRect(i);
        prim->type = PRIM_GT4;
        prim->tpage = 0x10C;
        if (i < 225) {
            u = r.x;
            v = r.y - 20;
        } else {
            for (band = 0; band < 4 && r.y >= s_CaptureBands[band + 1];
                 band++) {
            }
            u = band * 41 + (r.x < 0 ? r.x + 20 : 20 + r.x - 255);
            v = 207 + r.y - s_CaptureBands[band];
        }
        prim->u0 = prim->u2 = u;
        prim->u1 = prim->u3 = u + r.w;
        prim->v0 = prim->v1 = v;
        prim->v2 = prim->v3 = v + r.h;
        prim->x0 = prim->x2 = r.x;
        prim->x1 = prim->x3 = r.x + r.w;
        prim->y0 = prim->y1 = r.y;
        prim->y2 = prim->y3 = r.y + r.h;
        prim->r0 = 0x40;
        prim->g0 = prim->b0 = 0x30;
        LOW(prim->r1) = LOW(prim->r0);
        LOW(prim->r2) = LOW(prim->r0);
        LOW(prim->r3) = LOW(prim->r0);
        prim->priority = 0x6C;
        prim->drawMode = r.h ? DRAW_DEFAULT : DRAW_HIDE;
    }
}
#endif

void EntityDematerializeStageBg(Entity* self) {
    DRAWENV drawEnv;
    RECT cliprect;
    DR_ENV* dr_env;
    s16 angle;
    s32 xVar;
    s32 yVar;
    s32 i;
    s32 j;
    s32 var_s5;
    s32 var_s7;
    s32 var_s8;
    Primitive* prim;
    unkstr_801C06B0* unkStr;
    u32 primIndex;
    Entity* entity;
    SVECTOR* sp40;
    VECTOR* vec;
    MATRIX* m;
    SVECTOR* sp34;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInit3DObject);
        g_GpuBuffers[0].draw.r0 = 0;
        g_GpuBuffers[0].draw.g0 = 0;
        g_GpuBuffers[0].draw.b0 = 0;
        g_GpuBuffers[1].draw.r0 = 0;
        g_GpuBuffers[1].draw.g0 = 0;
        g_GpuBuffers[1].draw.b0 = 0;
        // fallthrough
    case 1:
        self->step++;
        break;
    case 2:
#ifdef VERSION_PC
        // shortcut: original-aspect captures lack side pixels; defer aspect
        // changes if hot switching during the breakup must be supported.
        s_WideCapture = PcViewMargin() != 0;
#endif
        primIndex = g_api.func_800EDB58(PRIM_GT4, BG_PART_COUNT);
        if (primIndex == -1) {
            SetStep(7);
            break;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;

        prim = &g_PrimBuf[primIndex];
        self->ext.prim = prim;
        while (prim != NULL) {
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }
        self->step++;
        // fallthrough
    case 3:
#ifdef VERSION_PC
        if (s_WideCapture) {
            self->step = CaptureWideBackground(self) ? 4 : 7;
            break;
        }
#endif
#ifdef VERSION_PSP
        func_psp_0891B0DC(0x300, 0);
#else
        prim = self->ext.prim;
        drawEnv = g_CurrentBuffer->draw;
        if (drawEnv.ofs[0] == 0) {
            prim->tpage = 0x100;
        } else {
            prim->tpage = 0x104;
        }
        prim->type = PRIM_GT4;
        prim->u0 = prim->u2 = 0;
        prim->u1 = prim->u3 = 0xFF;
        prim->v0 = prim->v1 = 0;
        prim->v2 = prim->v3 = 0xEF;
        prim->x0 = prim->x2 = 0;
        prim->x1 = prim->x3 = 0xFF;
        prim->y0 = prim->y1 = 0;
        prim->y2 = prim->y3 = 0xEF;
        prim->priority = 0x69;
        prim->drawMode = DRAW_DEFAULT;
        prim = prim->next;
        dr_env = g_api.func_800EDB08((POLY_GT4*)prim);
        if (dr_env == NULL) {
            SetStep(7);
            return;
        }
        prim->type = PRIM_ENV;
        drawEnv.isbg = 1;
        drawEnv.r0 = 0;
        drawEnv.g0 = 0;
        drawEnv.b0 = 0;
        drawEnv.dtd = 0;
        cliprect.x = 0x300;
        cliprect.y = 0;
        cliprect.w = 0x100;
        cliprect.h = 0x100;
        drawEnv.clip = cliprect;
        drawEnv.ofs[0] = 0x300;
        drawEnv.ofs[1] = 0;
        SetDrawEnv(dr_env, &drawEnv);
        prim->priority = 0x68;
        prim->drawMode = DRAW_DEFAULT;
        prim = prim->next;
        dr_env = g_api.func_800EDB08((POLY_GT4*)prim);
        if (dr_env == NULL) {
            SetStep(7);
            break;
        }
        prim->type = PRIM_ENV;
        prim->priority = 0x6A;
        prim->drawMode = DRAW_UNK_800;
#endif
        self->step++;
        break;
    case 4:
        prim = self->ext.prim;
#ifndef VERSION_PSP
#ifdef VERSION_PC
        if (!s_WideCapture)
#endif
            prim = prim->next;
        for (i = 0; i <
#ifdef VERSION_PC
                    (s_WideCapture ? 4 : 2)
#else
                    2
#endif
                 ;
             i++) {
            dr_env = PRIM_DR_ENV(prim);
            dr_env->tag = 0;
            prim->type = PRIM_GT4;
            prim = prim->next;
        }
        prim = self->ext.prim;
#endif
        for (i = 0; i < 15; i++) {
            for (j = 0; j < 15; j++) {
                xVar = j * 17;
                yVar = i * 16;
#ifdef VERSION_PSP
                prim->tpage = ((yVar & 0x100) >> 4 | 0x100 |
                               ((xVar + 0x300) & 0x3FF) >> 6) |
                              ((yVar & 0x200) << 2);
                var_s5 = xVar % 0x40;
                prim->u0 = prim->u2 = var_s5;
                prim->u1 = prim->u3 = var_s5 + 17;
#else
                prim->tpage = 0x10C;
                prim->u0 = prim->u2 = xVar;
                prim->u1 = prim->u3 = xVar + 17;
#endif
                prim->v0 = prim->v1 = yVar;
                prim->v2 = prim->v3 = yVar + 16;
                prim->x0 = prim->x2 = xVar;
                prim->x1 = prim->x3 = xVar + 17;
                prim->y0 = prim->y1 = yVar;
                prim->y2 = prim->y3 = yVar + 16;
                prim->r0 = 0x40;
                prim->g0 = prim->b0 = 0x30;

                LOW(prim->r1) = LOW(prim->r0);
                LOW(prim->r2) = LOW(prim->r0);
                LOW(prim->r3) = LOW(prim->r0);
                prim->priority = 0x6C;
                prim->drawMode = DRAW_DEFAULT;
                prim = prim->next;
            }
        }
#ifdef VERSION_PC
        if (s_WideCapture)
            InitializeWideBackground(self->ext.prim);
#endif
        self->step++;
        break;
    case 5:
        g_Tilemap.flags &= 0xFFFE;
        g_BgLayers[0].flags &= 0xFFFE;
        prim = self->ext.prim;
        unkStr = D_801C06B0;
        for (i = 0; i < BG_PART_COUNT; i++, unkStr++) {
            xVar = prim->x0 + 8;
            yVar = prim->y0 + 8;
#ifdef VERSION_PC
            if (s_WideCapture) {
                Point16 origin = BackgroundPieceOrigin(i);
                xVar = origin.x + 8;
                yVar = origin.y + 8;
            }
#endif
            xVar -= 0x80;
            yVar -= 0x80;
            unkStr->unkA = xVar;
            unkStr->unkE = yVar;
            unkStr->unk10 = 0x80;
            angle = ratan2(yVar, xVar);
            var_s7 = (xVar * xVar) + (yVar * yVar);
            xVar = rsin(angle) * 0x24;
            yVar = rcos(angle) * 0x24;
            var_s7 = SquareRoot0(var_s7);
            var_s8 = 0xC0 - var_s7;
            xVar = xVar * var_s8 / 0xC0;
            yVar = yVar * var_s8 / 0xC0;
            xVar >>= 0xC;
            yVar >>= 0xC;
            unkStr->unk0.x = xVar;
            unkStr->unk0.y = yVar;
#ifdef VERSION_PC
            if (i >= 225) {
                // Extra edge pieces must not consume gameplay randomness.
                unkStr->unk14 = D_801C06B0[((i - 225) / 4) * 15 +
                                           ((i - 225) % 4 < 2 ? 0 : 14)]
                                    .unk14;
            } else
#endif
                unkStr->unk14 = ((var_s7 * 3) / 2) - (Random() & 0x1F);
            if (unkStr->unk14 < 0) {
                unkStr->unk14 = 0;
            }
            unkStr->unk4 = 0;
            unkStr->unk6 = 0;
            prim = prim->next;
        }
        self->ext.GS_Props.pickupFlag = 1;
        self->step++;
        break;
    case 6:
        SetGeomScreen(0x80);
        SetGeomOffset(0x80, 0x80);
        m = (MATRIX*)SP(0);
        sp40 = (SVECTOR*)SP(sizeof(MATRIX));
        vec = (VECTOR*)SP(sizeof(MATRIX) + sizeof(SVECTOR));
        sp34 = (SVECTOR*)SP(sizeof(MATRIX) + sizeof(SVECTOR) + sizeof(VECTOR));
        sp34[0] = D_80182690;
        sp34[1] = D_80182698;
        sp34[2] = D_801826A0;
        sp34[3] = D_801826A8;
        unkStr = D_801C06B0;
        prim = self->ext.prim;
        for (i = 0; i < BG_PART_COUNT; i++, unkStr++) {
            if ((unkStr->unk14) || (unkStr->unk10 > 0x180)) {
                prim = prim->next;
                continue;
            }
#ifdef VERSION_PC
            if (s_WideCapture) {
                RECT r = BackgroundPieceRect(i);
                Point16 p = BackgroundPieceOrigin(i);
                if (!r.h) {
                    prim->drawMode = DRAW_HIDE;
                    prim = prim->next;
                    continue;
                }
                sp34[0].vx = sp34[2].vx = r.x - p.x - 8;
                sp34[1].vx = sp34[3].vx = MIN(r.x + r.w - p.x - 8, 8);
                sp34[0].vy = sp34[1].vy = r.y - p.y - 8;
                sp34[2].vy = sp34[3].vy = r.y + r.h - p.y - 8;
            }
#endif
            sp40->vx = unkStr->unk4;
            sp40->vy = unkStr->unk6;
            sp40->vz = 0;
            RotMatrixYXZ(sp40, m);
            gte_SetRotMatrix(m);
            vec->vx = unkStr->unkA;
            vec->vy = unkStr->unkE;
            vec->vz = unkStr->unk10;
            gte_SetTransVector(vec);
            gte_ldv3c(sp34);
            gte_rtpt();
            gte_stsxy3_gt3(prim);
            gte_ldv0(&sp34[3]);
            gte_rtps();
            gte_stsxy((long*)&prim->x3);
            prim->drawMode = DRAW_DEFAULT;
            prim = prim->next;
        }
        unkStr = D_801C06B0;
        prim = self->ext.prim;
        var_s8 = 0;
        for (i = 0; i < BG_PART_COUNT; i++, unkStr++) {
            if (unkStr->unk14) {
                unkStr->unk14--;
                prim = prim->next;
                continue;
            }
            unkStr->unk4 += unkStr->unk0.x;
            unkStr->unk6 += unkStr->unk0.y;
            unkStr->unk10 += 3;
            if (unkStr->unk10 > 0x180) {
#ifdef VERSION_PC
                if (i < 15 * 15)
#endif
                    var_s8 += 1;
                prim->drawMode = DRAW_HIDE;
            }
            prim = prim->next;
        }
        if (self->ext.GS_Props.pickupFlag) {
            if (var_s8 > 14) {
                self->ext.GS_Props.pickupFlag = 0;
                entity = self + 1;
                CreateEntityFromCurrentEntity(E_BACKGROUND_VORTEX, entity);
            }
        }
        if (var_s8 == 15 * 15) {
            DestroyEntity(self);
        }
        break;
    case 7:
        entity = self + 1;
        CreateEntityFromCurrentEntity(E_BACKGROUND_VORTEX, entity);
        DestroyEntity(self);
        break;
    }
}
