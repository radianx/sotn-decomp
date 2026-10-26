// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rbo1.h"

extern EInit g_EInitInteractable;
extern s16 D_us_801807F8[][5];
extern s32 D_us_80180638;

void func_us_80192F84(Entity* self) {
    s32 i;
    s32 used;
    s16* counts;
    s16* init;
    s32 dx;
    s32 dy;
    s16 angle;
    s32 sine;
    s32 cosine;
    s32 endpointX;
    s32 endpointY;
    s32 anchorX;
    s32 anchorY;
    s32 j;
    s32 offsetX;
    s32 offsetY;
    Entity* body;
    Primitive* prim;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
        used = g_api.func_800EDB58(PRIM_SPRT | 0x10, 256);
        if (used == -1) {
            DestroyEntity(self);
            return;
        }
        prim = &g_PrimBuf[used];
        self->primIndex = used;
        self->ext.beelzebubChain.prim = prim;
        self->flags |= FLAG_HAS_PRIMS;
        while (prim != NULL) {
            prim->tpage = 0x12;
            prim->clut = PAL_BEEZELBUB;
            prim->u0 = 0xD0;
            prim->v0 = 0x70;
            prim->u1 = prim->v1 = 8;
            prim->priority = self->zPriority;
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }
        break;
    case 1:
        init = D_us_801807F8[0];
        counts = self->ext.beelzebubChain.segmentCounts;
        for (i = 0; i < 7;) {
            body = self->ext.beelzebubChain.parent;
            body += init[0];
            angle = body->rotate;
            dx = init[1];
            dy = init[2];
            sine = rsin(angle);
            cosine = rcos(angle);
            endpointX = (dx * cosine - dy * sine) >> 12;
            endpointY = (dx * sine + dy * cosine) >> 12;
            endpointX += body->posX.i.hi;
            endpointY += body->posY.i.hi;
            anchorX = init[3] - g_Tilemap.scrollX.i.hi;
            anchorY = init[4] - g_Tilemap.scrollY.i.hi;
            dx = anchorX - endpointX;
            dy = anchorY - endpointY;
            j = SquareRoot0(dx * dx + dy * dy);
            i++;
            *counts = j / 6 + 2;
            init += 5;
            counts++;
        }
        self->step++;
        // fallthrough
    case 2:
        init = D_us_801807F8[0];
        prim = self->ext.beelzebubChain.prim;
        used = 0;
        counts = self->ext.beelzebubChain.segmentCounts;
        for (i = 0; i < 7; i++, init += 5, counts++) {
            body = self->ext.beelzebubChain.parent;
            body += init[0];
            if (body->flags & FLAG_DEAD) {
                if (!((D_us_80180638 >> i) & 1)) {
                    g_api.PlaySfx(SFX_RIC_WHIP_RATTLE_A);
                    D_us_80180638 |= 1 << i;
                }
                anchorX = init[3] - g_Tilemap.scrollX.i.hi;
                anchorY = init[4] - g_Tilemap.scrollY.i.hi;
                anchorX <<= 8;
                anchorY <<= 8;
                for (j = 0; j < *counts; j++) {
                    dx = prim->x0 << 8;
                    dy = prim->y0 << 8;
                    dx |= prim->x1;
                    dy |= prim->y1;
                    dx -= anchorX;
                    dy -= anchorY;
                    dy += 0x800;
                    angle = ratan2(dy, dx);
                    if (dx * dx + dy * dy > 0x240000) {
                        dx = (rcos(angle) * 6) >> 4;
                        dy = (rsin(angle) * 6) >> 4;
                    }
                    anchorX += dx;
                    anchorY += dy;
                    dx = prim->x0 = anchorX >> 8;
                    dy = prim->y0 = anchorY >> 8;
                    prim->x1 = anchorX & 0xFF;
                    prim->y1 = anchorY & 0xFF;
                    prim->drawMode = DRAW_UNK02;
                    if ((u32)dx > 256 || (u32)(dy - 16) > 224) {
                        prim->drawMode = DRAW_UNK02 | DRAW_HIDE;
                    }
                    prim = prim->next;
                }
            } else {
                angle = body->rotate;
                dx = init[1];
                dy = init[2];
                sine = rsin(angle);
                cosine = rcos(angle);
                endpointX = (dx * cosine - dy * sine) >> 12;
                endpointY = (dx * sine + dy * cosine) >> 12;
                endpointX += body->posX.i.hi;
                endpointY += body->posY.i.hi;
                anchorX = init[3] - g_Tilemap.scrollX.i.hi;
                anchorY = init[4] - g_Tilemap.scrollY.i.hi;
                angle = ratan2(endpointY - anchorY, endpointX - anchorX);
                sine = rsin(angle);
                cosine = rcos(angle);
                for (j = 0; j < *counts;) {
                    j++;
                    offsetX = cosine * 6;
                    offsetY = sine * 6;
                    dx = anchorX + ((offsetX * j) >> 12);
                    dy = anchorY + ((offsetY * j) >> 12);
                    prim->drawMode = DRAW_UNK02;
                    prim->x0 = dx;
                    prim->y0 = dy;
                    if ((u32)dx > 256 || (u32)(dy - 16) > 224) {
                        prim->drawMode = DRAW_UNK02 | DRAW_HIDE;
                    }
                    if (dy > endpointY) {
                        prim->drawMode |= DRAW_HIDE;
                    }
                    used++;
                    prim = prim->next;
                }
            }
        }
        FntPrint("used_work %x\n", used);
        while (prim->next != NULL) {
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }
        prim->tpage = 0x12;
        prim->clut = PAL_BEEZELBUB;
        prim->x0 = prim->y0 = 0;
        prim->drawMode = DRAW_UNK02;
        break;
    }
}
