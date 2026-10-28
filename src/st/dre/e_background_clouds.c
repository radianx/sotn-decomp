// SPDX-License-Identifier: AGPL-3.0-or-later
#include "dre.h"

extern EInit g_EInitInteractable;

// clouds in the background ID 0x18
void EntityBackgroundClouds(Entity* self) {
    Primitive* prim;
    s32 primIndex;
    s32 camX, camY;
#ifdef VERSION_PC
    s32 column = -1;
#endif

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
#ifdef VERSION_PC
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 8);
#else
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 5);
#endif
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->primIndex = primIndex;
        self->flags |= FLAG_HAS_PRIMS;
        prim = &g_PrimBuf[primIndex];
        self->ext.prim = prim;
        prim->type = PRIM_G4;
        prim->x0 = prim->x2 = 0;
        prim->x1 = prim->x3 = 0x100;
        prim->y0 = prim->y1 = 0x6E - g_Tilemap.scrollY.i.hi;
        prim->y2 = prim->y3 = 0xF0;
        setRGB0(prim, 16, 16, 16);
        LOW(prim->r1) = LOW(prim->r0);
        LOW(prim->r2) = LOW(prim->r0);
        LOW(prim->r3) = LOW(prim->r0);
        prim->priority = 0x20;
        prim->drawMode = DRAW_DEFAULT;
        prim = prim->next;
        camX = -g_Tilemap.scrollX.i.hi;
#ifdef VERSION_PC
        // Retain the original four clouds and cover either initial camera end.
        camX -= 95;
#endif
        camY = 32 - g_Tilemap.scrollY.i.hi;
        while (prim != NULL) {
            prim->tpage = 0xF;
            prim->clut = 5;
            prim->u0 = prim->u2 = 0x84;
            prim->u1 = prim->u3 = 0xE3;
            prim->v0 = prim->v1 = 1;
            prim->v2 = prim->v3 = 0x4F;
            prim->x0 = prim->x2 = camX;
            camX += 95;
            prim->x1 = prim->x3 = camX;
            prim->y0 = prim->y1 = camY;
            prim->y2 = prim->y3 = camY + 0x4E;
            prim->priority = 0x20;
            prim->drawMode = DRAW_DEFAULT;
#ifdef VERSION_PC
            // Additional right repeats must not alter the original viewport.
            if (column >= 4) {
                if (prim->x1 <= 256) {
                    prim->drawMode = DRAW_HIDE;
                } else if (prim->x0 < 256) {
                    prim->u0 = prim->u2 = prim->u0 + 256 - prim->x0;
                    prim->x0 = prim->x2 = 256;
                }
            }
            column++;
#endif
            prim = prim->next;
        }
        break;

    case 255:
#include "../pad2_anim_debug.h"
    }
#ifdef VERSION_PC
    prim = self->ext.prim;
    prim->x0 = prim->x2 = PC_LEFT(0);
    prim->x1 = prim->x3 = PC_RIGHT(0x100);
#endif
    g_GpuBuffers[0].draw.r0 = 40;
    g_GpuBuffers[0].draw.g0 = 24;
    g_GpuBuffers[0].draw.b0 = 24;
    g_GpuBuffers[1].draw.r0 = 40;
    g_GpuBuffers[1].draw.g0 = 24;
    g_GpuBuffers[1].draw.b0 = 24;
}
