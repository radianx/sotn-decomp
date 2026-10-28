// SPDX-License-Identifier: AGPL-3.0-or-later
#ifndef ST0_PC_WIDE_CAPTURE_H
#define ST0_PC_WIDE_CAPTURE_H
#ifdef VERSION_PC

static const s16 s_CaptureBands[] = {20, 64, 112, 160, 208, 227};

static s32 CaptureWideFrame(Primitive* prim, s32 priority) {
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
            prim->priority = priority;
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

#endif
#endif
