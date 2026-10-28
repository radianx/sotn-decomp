// SPDX-License-Identifier: AGPL-3.0-or-later

extern EInit g_EInitInteractable;

// Row of blue "land" tiles at the bottom of the sky background.
void EntityBackgroundSkyLand(Entity* self) {
    Primitive* prim;
    s32 primIndex;
    s32 x;

    if (!self->step) {
        InitializeEntity(g_EInitInteractable);
#ifdef VERSION_PC
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 6);
#else
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 5);
#endif
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        for (x = 0; prim != NULL; prim = prim->next) {
            prim->tpage = 15;
            prim->clut = PAL_BACKGROUND_SKY_LAND;
            prim->u0 = prim->u2 = 65;
            prim->u1 = prim->u3 = 127;
            prim->v0 = prim->v1 = 169;
            prim->v2 = prim->v3 = 198;
#ifdef VERSION_PC
            // Append a left repeat without shifting the original five tiles.
            if (x == 310) {
                x = -62;
            }
#endif
            prim->x0 = prim->x2 = x;
            x += 62;
            prim->x1 = prim->x3 = x;
#ifdef STAGE_IS_RDAI
            prim->y0 = prim->y1 = 64;
            prim->y2 = prim->y3 = 18;
#else
            prim->y0 = prim->y1 = 192;
            prim->y2 = prim->y3 = 228;
#endif
            prim->priority = 16;
            prim->drawMode = DRAW_DEFAULT;
        }
    }
}
