// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rno4.h"

extern u8 D_us_80181070[];
extern u8 D_us_80181088[];
extern s16 D_us_80181094[];
extern s16 D_us_80181190[];
extern s16 D_us_80181428[9][3];
extern s16 D_us_80181460[];
extern u16 D_us_80181478[13];
extern s16 D_us_80181494[][5];
extern u16 D_us_801814A8[];
extern s16 D_us_801814BC[];

void func_us_801C12B0_from_no4(Entity* self) {
    u32 var_s8;
    s16* ptr;
    s32 var_s6;
    u8* var_s5;
    s32 var_s4;
    s32 var_s3;
    s32 var_s2;
    s32 var_s1;

    Primitive* prim;
    s32 primIndex;
    s32 scrollX;
    s32 scrollY;
    s32 i;
    s32 xOffset;
    s32 sp38;

    if (!self->step) {
        InitializeEntity(g_EInitInteractable);
        self->animSet = 0;
        self->ext.et_801C12B0.unk80 = 4;
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 16);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.et_801C12B0.prim = prim;
        self->ext.et_801C12B0.unk82 = 0;
        while (prim != NULL) {
            prim->tpage = 0xF;
            prim->clut = 0x5E;
            prim->priority = 0x9E;
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }
    }

    prim = self->ext.et_801C12B0.prim;
    AnimateEntity(D_us_80181088, self);
    i = (self->params >> 8) & 0xFF;
    ptr = &D_us_80181094[(self->params & 0xFF) * 5];
    scrollX = g_Tilemap.scrollX.i.hi - 0x10;
    scrollY = g_Tilemap.scrollY.i.hi;
    xOffset = PC_RIGHT(scrollX + 0x120);
    var_s5 = &D_us_80181070[self->animCurFrame * 4];
    var_s8 = var_s5[1];

    for (; i > 0; i--) {
        var_s3 = *ptr++;
        var_s2 = var_s3 + *ptr++;
        if (PC_LEFT(scrollX) >= var_s2 || xOffset < var_s3) {
            ptr += 3;
            continue;
        }

        var_s6 = *ptr++;
        if (scrollY - 4 > var_s6 || var_s6 > scrollY + 0xE0) {
            ptr += 2;
            continue;
        } else {
            ptr++;
            sp38 = *ptr++;
            var_s6 -= scrollY;
            if (var_s3 < PC_LEFT(scrollX)) {
                var_s3 = PC_LEFT(scrollX);
            }
            if (xOffset < var_s2) {
                var_s2 = xOffset;
            }
            if (sp38 != 0) {
#ifdef VERSION_PC
                if (scrollX < var_s2 && scrollX + 0x120 >= var_s3)
#endif
                    self->ext.et_801C12B0.unk82 += sp38;
                var_s4 = (u32)(var_s3 - self->ext.et_801C12B0.unk82) % 126;
            } else {
                var_s4 = (u32)var_s3 % 126;
            }
#ifdef VERSION_PC
            // Keep the original unsigned phase across an extended left clip.
            s32 originalLeft = MAX(var_s3, scrollX);
            var_s4 =
                (u32)(originalLeft - (sp38 ? self->ext.et_801C12B0.unk82 : 0)) %
                126;
            var_s4 = (var_s4 + var_s3 - originalLeft + 126) % 126;
#endif
            var_s2 -= var_s3;
            var_s3 -= scrollX + 0x10;
            var_s4 += var_s5[0];
            do {
                prim->u0 = prim->u2 = var_s4;
                var_s1 = 0x7E - (var_s4 - var_s5[0]);
                if (var_s2 < var_s1) {
                    var_s1 = var_s2;
                }
                prim->u1 = prim->u3 = var_s4 + var_s1;
                prim->v0 = prim->v1 = var_s8;
                prim->v2 = prim->v3 = var_s8 + 1;
                prim->x0 = prim->x2 = var_s3;
                var_s3 += var_s1;
                prim->x1 = prim->x3 = var_s3;
                var_s2 -= var_s1;
                var_s4 = var_s5[0];
                prim->y0 = prim->y1 = var_s6;
                prim->y2 = prim->y3 = var_s6 + 1;
                prim->drawMode = DRAW_TPAGE | DRAW_UNK02 | DRAW_TRANSP;
                prim = prim->next;
            } while (var_s2 != 0);
        }
    }

    while (prim != NULL) {
        prim->drawMode = DRAW_HIDE;
        prim = prim->next;
    }
}

void func_us_801C15F8_from_no4(Entity* self) {
    s32 scrollX;
    s32 scrollY;
    s16* ptr;
    s32 var_s5;
    s32 var_s4;
    s32 var_s3;
    s32 var_s2;
    s32 var_s1;
    Primitive* prim;

    s32 primIndex;
    s32 xOffset;
    s32 yOffset;
    s32 i;

    if (!self->step) {
        InitializeEntity(g_EInitInteractable);
        self->animSet = 0;
        self->ext.et_801C12B0.unk80 = 4;
        primIndex = g_api.AllocPrimitives(PRIM_TILE, 16);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.et_801C12B0.prim = prim;
        while (prim != NULL) {
            prim->r0 = 0x10;
            prim->g0 = 8;
            prim->b0 = 0x18;
            prim->priority = 0x9D;
            prim = prim->next;
        }
    }

    prim = self->ext.et_801C12B0.prim;
    ptr = &D_us_80181190[(self->params & 0xFF) * 4];
    i = (self->params >> 8) & 0xFF;
    scrollX = g_Tilemap.scrollX.i.hi - 0x10;
    scrollY = g_Tilemap.scrollY.i.hi - 0x10;
    xOffset = PC_RIGHT(scrollX + 0x120);
    yOffset = scrollY + 0x100;

    for (; i > 0; i--) {
        var_s3 = *ptr++;
        var_s2 = var_s3 + *ptr++;
        if (PC_LEFT(scrollX) >= var_s2 || xOffset < var_s3) {
            ptr += 2;
            continue;
        }

        var_s4 = *ptr++;
        var_s5 = *ptr++;
        if (var_s4 > scrollY && yOffset >= var_s5) {
            if (var_s3 < PC_LEFT(scrollX)) {
                var_s3 = PC_LEFT(scrollX);
            }
            if (xOffset < var_s2) {
                var_s2 = xOffset;
            }

            var_s2 -= var_s3;
            var_s3 -= scrollX + 0x10;

            if (var_s5 < scrollY) {
                var_s5 = scrollY;
            }

            if (yOffset < var_s4) {
                var_s4 = yOffset;
            }
            var_s4 -= var_s5;
            var_s5 -= scrollY + 0x10;
            if (var_s4 >= 0x100) {
                var_s4 = 0xFF;
            }

            do {
                var_s1 = var_s2;
                if (var_s1 >= 0x100) {
                    var_s1 = 0xFF;
                }
                prim->u0 = var_s1;
                prim->v0 = var_s4;
                prim->x0 = var_s3;
                prim->y0 = var_s5;
                var_s3 += var_s1;
                var_s2 -= var_s1;
                prim->drawMode = DRAW_TPAGE | DRAW_UNK02 | DRAW_TRANSP;
                prim = prim->next;
            } while (var_s2 != 0);
        }
    }

    while (prim != NULL) {
        prim->drawMode = DRAW_HIDE;
        prim = prim->next;
    }
}

extern u8 D_us_80181084[2];
extern s16 D_us_80181280[50]; // unknown size?

void func_us_801C5364(Entity* self) {
    Primitive* prim;
    u32 subTileX;
    int bgColorValue;
    int tileY1Wrap;
    s32 tileY1;
    s32 tileX0;
    s32 tileX1;
    u8* tilePos;
    s32 tileX1Wrap;
    s32 primIndex;
    s32 x0;
    long y0;
    s32 tileY0;
    s32 x1;
    s32 y1;
    s32 i;
    s16* tileDimensions; // It holds some dimensions of something, I'm guessing
                         // some tile or entity sprite

    if (!self->step) {
        InitializeEntity(g_EInitInteractable);
        self->animSet = 0;
        self->ext.et_801C5364.unk80 = 4;
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 0x10);
        if (primIndex == (-1)) {
            DestroyEntity(self);
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.et_801C5364.prim7C = prim;
        while (prim) {
            prim->tpage = 0xF;
            prim->clut = 0x85;
            prim->priority = 0x18;
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }
    }
    if (g_Timer & 0x80) {
        if (g_Timer & 0x40) {
            bgColorValue = 0x3f - (g_Timer & 0x3f);
        } else {
            bgColorValue = g_Timer & 0x3f;
        }
    } else {
        bgColorValue = 0;
    }
    bgColorValue = bgColorValue + 0x80;
    bgColorValue = 0x80;

    g_GpuBuffers[0].draw.r0 = ((bgColorValue * 24) / 0x80) & 0xf8;
    g_GpuBuffers[0].draw.g0 = 0;
    g_GpuBuffers[0].draw.b0 = ((bgColorValue * 8) / 128) & 0xf8;
    g_GpuBuffers[1].draw.r0 = ((bgColorValue * 24) / 128) & 0xf8;
    g_GpuBuffers[1].draw.g0 = 0;
    g_GpuBuffers[1].draw.b0 = ((bgColorValue * 8) / 0x80) & 0xf8;

    prim = self->ext.et_801C5364.prim7C;

    i = (self->params >> 8) & 0xff;
    tileDimensions = D_us_80181280 + ((self->params & 0xff) * 4);
    x0 = g_Tilemap.scrollX.i.hi - 0x10;
    y0 = g_Tilemap.scrollY.i.hi;
    x1 = PC_RIGHT(x0 + 0x120);
    y1 = y0 + 0xe0;
    tilePos = D_us_80181084;
    tileY1Wrap = tilePos[1];
    while (i > 0) {
        tileX0 = *(tileDimensions++);
        tileX1 = *(tileDimensions++);
        if ((PC_LEFT(x0) >= tileX0) || (x1 < tileX1)) {
            tileDimensions = tileDimensions + 2;
        } else {
            tileY0 = *(tileDimensions++);
            tileY1 = *(tileDimensions++);
            if ((y0 < tileY0) && (!(y1 < tileY1))) {
                {
                    if (PC_LEFT(x0) > tileX1) {
                        tileX1 = PC_LEFT(x0);
                    }
                }
                if (tileX0 > x1) {
                    tileX0 = x1;
                }
                tileX0 -= tileX1;
                tileX1 -= (x0 + 0x10);
                subTileX = ((x0 / 4) + tileX1) % 126;
#ifdef VERSION_PC
                if ((s32)subTileX < 0)
                    subTileX += 126;
#endif
                if (tileY1 < y0) {
                    tileY1 = y0;
                }
                if (y1 < tileY0) {
                    tileY0 = y1;
                }
                tileY1Wrap = 0x63 - ((y0 - (g_Tilemap.height - 0x100)) / 4);
                y1 = y1 + 0x46;
                tileY1 = tileY1 - y0;
                tileY0 -= y0;
                if ((tileY1Wrap < tileY0) && (y1 >= tileY1)) {
                    if (tileY1 < tileY1Wrap) {
                        tileY1 = tileY1Wrap;
                    }
                    if (y1 < tileY0) {
                        tileY0 = y1;
                    }
                    tileY0 -= tileY1;
                    tileY1Wrap = ((y0 - (g_Tilemap.height - 0x100)) / 4) +
                                 (tileY1 - 0x63);
                    subTileX += tilePos[0];
                    do {
                        prim->u0 = prim->u2 = subTileX;
                        tileX1Wrap = 0x7e - (subTileX - tilePos[0]);
                        if (tileX0 < tileX1Wrap) {
                            tileX1Wrap = tileX0;
                        }
                        prim->u1 = prim->u3 = subTileX + tileX1Wrap;
                        prim->x0 = prim->x2 = tileX1;
                        tileX1 = tileX1 + tileX1Wrap;

                        prim->x1 = (prim->x3 = tileX1);
                        tileX0 = tileX0 - tileX1Wrap;
                        subTileX = tilePos[0];

                        // There's this empty statement after all,
                        // I missed it when I thought I'd found the solution
                        // I had permuter running it for ~20 hours and couldn't
                        // find anything else
                        tilePos = tilePos;

                        if (tileY1Wrap > 0x46) {
                            tileX1Wrap = 0;
                        } else {
                            tileX1Wrap = 0x46 - tileY1Wrap;
                        }
                        prim->v0 = prim->v1 = tilePos[1] + tileX1Wrap;
                        prim->v2 = prim->v3 = tilePos[1];
                        prim->y0 = prim->y1 = tileY1;
                        prim->y2 = prim->y3 = tileY1 + tileX1Wrap;
                        prim->drawMode = DRAW_COLORS;
                        prim->r0 = prim->r1 = prim->r2 = prim->r3 = prim->b0 =
                            prim->b1 = prim->b2 = prim->b3 = bgColorValue;
                        prim->g0 = prim->g1 = prim->g2 = prim->g3 = 0x80;
                        prim = prim->next;
                    } while (tileX0);
                }
            }
        }
        i -= 1;
    }

    while (prim) {
        prim->drawMode = DRAW_HIDE;
        prim = prim->next;
    }
}

void EntityBgColumnsParallax_from_no4(Entity* self) {
    s32 primIndex;
    s32 scrollY;
    s32 scrollX;
    s32 flipXY;
    s16* ptr;
    s32 posYBottom;
    s32 posY;
    s32 posX;
    Primitive* prim;

    if (!self->step) {
        InitializeEntity(g_EInitInteractable);
        self->animSet = 0;
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 10);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.et_801C12B0.prim = prim;
        while (prim != NULL) {
            prim->tpage = 0xE;
            prim->clut = 0x84;
            prim->u0 = prim->u2 = 0xE9;
            prim->u1 = prim->u3 = 0xFD;
            prim->v0 = prim->v1 = 0x7F;
            prim->v2 = prim->v3 = 1;
            prim->priority = 0x1C;
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }
    }

    prim = self->ext.et_801C12B0.prim;
    ptr = (s16*)D_us_80181428;
    scrollX = g_Tilemap.scrollX.i.hi;
    scrollX /= 2;
    scrollX &= 0xFF;
    scrollY = g_Tilemap.scrollY.i.hi;
    scrollY /= 2;
    // The final offscreen entry terminates this table.
    while (1) {
        posX = *ptr++;
        posY = (0x7A - *ptr++) + (u32)((g_Tilemap.height - 0x100) / 2);
        flipXY = *ptr++;
        posX -= scrollX;
        posY -= scrollY;
        posYBottom = posY + 0x7E;
        if (posX < -20) {
            continue;
        }
        if (posX >= STAGE_WIDTH) {
            break;
        }
        if (posYBottom >= 0 && posY < 0xE0) {
            if (flipXY & 1) {
                prim->x0 = prim->x2 = posX + 0x14;
                prim->x1 = prim->x3 = posX;
            } else {
                prim->x0 = prim->x2 = posX;
                prim->x1 = prim->x3 = posX + 0x14;
            }
            if (flipXY & 2) {
                prim->y0 = prim->y1 = posY;
                prim->y2 = prim->y3 = posYBottom;
            } else {
                prim->y0 = prim->y1 = posYBottom;
                prim->y2 = prim->y3 = posY;
            }
            prim->drawMode = DRAW_DEFAULT;
            prim = prim->next;
        }
    }
    while (prim != NULL) {
        prim->drawMode = DRAW_HIDE;
        prim = prim->next;
    }
}

void func_us_801C1EE4_from_no4(Entity* self) {
    s32 scrollX;
    s32 clut;
    s32 yOffset;
    s32 var_s5;
    s32 var_s4;
    s32 scrollY;
    s32 var_s2;
    s32 var_s1;
    Primitive* prim;

    s32 primIndex;
    s16* ptr;

    if (!self->step) {
        InitializeEntity(g_EInitInteractable);
        self->animSet = 0;
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 16);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->ext.et_801C12B0.clut = 0;
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.et_801C12B0.prim = prim;
        while (prim != NULL) {
            prim->tpage = 0xE;
            prim->u0 = prim->u2 = 0xFC;
            prim->u1 = prim->u3 = 0xFE;
            prim->priority = 0x1A;
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }
    }

    prim = self->ext.et_801C12B0.prim;
    ptr = D_us_80181460;
    self->ext.et_801C12B0.clut++;
    if (self->ext.et_801C12B0.clut >= 0xE) {
        self->ext.et_801C12B0.clut = 0;
    }
    scrollX = g_Tilemap.scrollX.i.hi;
    scrollX *= 3;
    scrollX /= 8;
    scrollX &= 0xFF;
    scrollY = g_Tilemap.scrollY.i.hi;
    var_s5 = -(scrollY + 0x50) + g_Tilemap.height;
    yOffset = -(scrollY + 0xB0) + g_Tilemap.height;
    if (var_s5 > 0xE0) {
        var_s5 = 0xE0;
    }
    if (var_s5 >= 0) {
        scrollY *= 3;
        scrollY /= 8;
        scrollY += yOffset;
        scrollY %= 0x20;

        var_s5 -= yOffset;
        if (scrollY + var_s5 > 0x60) {
            var_s2 = 0x60 - scrollY;
        } else {
            var_s2 = var_s5;
        }

        var_s4 = var_s5 - var_s2;
        var_s5 = var_s2;
        var_s2 += yOffset;
        clut = self->ext.et_801C12B0.clut + 0x90;

        while (true) {
            var_s1 = *ptr++;
            var_s1 -= scrollX;
            if (var_s1 < -2) {
                continue;
            }

            if (var_s1 >= 0x100) {
                break;
            }

            prim->clut = clut;
            prim->v2 = prim->v3 = scrollY + 0x84;
            // The original adds to the previous v0 rather than the new v2.
            prim->v0 = prim->v1 = prim->v0 + var_s5;
            prim->x0 = prim->x2 = var_s1;
            prim->x1 = prim->x3 = var_s1 + 2;
            prim->y0 = prim->y1 = yOffset;
            prim->y2 = prim->y3 = var_s2;
            prim->drawMode =
                DRAW_UNK_40 | DRAW_TPAGE2 | DRAW_TPAGE | DRAW_TRANSP;
            prim = prim->next;
            if (var_s4 != 0) {
                prim->clut = clut;
                prim->v0 = prim->v1 = 0x84;
                prim->v2 = prim->v3 = var_s4 + 0x84;
                prim->x0 = prim->x2 = var_s1;
                prim->x1 = prim->x3 = var_s1 + 2;
                prim->y0 = prim->y1 = var_s2;
                prim->y2 = prim->y3 = var_s2 + var_s4;
                prim->drawMode =
                    DRAW_UNK_40 | DRAW_TPAGE2 | DRAW_TPAGE | DRAW_TRANSP;
                prim = prim->next;
            }
        }
    }

    while (prim != NULL) {
        prim->drawMode = DRAW_HIDE;
        prim = prim->next;
    }
}

extern Tilemap* D_pspeu_0929B8B8; // This variable is assigned to a different
                                  // var that is never used

void func_us_801C5C78(Entity* self) {
    Primitive* prim;
    Tilemap** tilemap_pp_0;
    u32 primIndex;
    u32 xOffset;
    u16 params;
    u32 clut;
    s32 scrollY;
    s32 posY;
    u32 scrollYModulo;

    params = self->params;
    if (!self->step) {
        InitializeEntity(g_EInitParticle);
        self->animSet = 0;
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 2);
        if (primIndex == (-1)) {
            DestroyEntity(self);
            return;
        }
        self->flags |= FLAG_DESTROY_IF_OUT_OF_CAMERA |
                       FLAG_DESTROY_IF_BARELY_OUT_OF_CAMERA | FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.et_801C5C78.prim = prim;
        while (prim) {
            if (params) {
                prim->tpage = 0xF;
                prim->u0 = (prim->u2 = 0x82);
                prim->u1 = (prim->u3 = 0x9d);
            } else {
                prim->tpage = 0xE;
                prim->u0 = (prim->u2 = 0xe9);
                prim->u1 = (prim->u3 = 0xf7);
            }
            prim->priority = 0x62;
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }
    }

    prim = self->ext.et_801C5C78.prim;
#ifndef VERSION_PC
    tilemap_pp_0 = &D_pspeu_0929B8B8;
#endif
    self->ext.et_801C5C78.unk84 += 1;

    if (self->ext.et_801C5C78.unk84 >= 0xE) {
        self->ext.et_801C5C78.unk84 = 0;
    }

    posY = self->posY.i.hi;
    scrollY = g_Tilemap.scrollY.i.hi;

    if (posY >= 0) {
        scrollY %= 32;
        if (params) {
            clut = 0x90;
        } else {
            clut = 0xB0;
        }
        clut = 0xB0;
        clut += self->ext.et_801C5C78.unk84;

        if (((scrollY + posY) - 0x50) > 0x60) {
            scrollYModulo = 0x60 - scrollY;
        }
        scrollYModulo = 0x60;

        prim->clut = clut;

        if (params) {
            xOffset = self->posX.i.hi - 0xD;
            prim->v2 = (prim->v3 = 3);
            prim->x1 = (prim->x3 = xOffset + 0x1B);
            prim->drawMode = DRAW_UNK_40 | DRAW_TPAGE2 | DRAW_TPAGE |
                             DRAW_UNK02 | DRAW_TRANSP;
        } else {
            xOffset = self->posX.i.hi - 7;
            prim->v2 = (prim->v3 = 0x83);
            prim->x1 = (prim->x3 = xOffset + 0xe);
            prim->drawMode = DRAW_UNK_40 | DRAW_TPAGE2 | DRAW_TPAGE |
                             DRAW_UNK02 | DRAW_TRANSP;
        }

        prim->v0 = (prim->v1 = prim->v2 + 0x60);
        prim->x0 = (prim->x2 = xOffset);
        prim->y0 = (prim->y1 = 0x4C);
        prim->y2 = (prim->y3 = 0xAC);
        prim = prim->next;
        prim->clut = clut;

        if (params) {
            prim->v0 = (prim->v1 = 0x63);
            prim->v2 = (prim->v3 = 0x2f);
            prim->x0 = (prim->x2 = xOffset);
            prim->x1 = (prim->x3 = xOffset + 0x1B);
            prim->drawMode = DRAW_UNK_40 | DRAW_TPAGE2 | DRAW_TPAGE |
                             DRAW_UNK02 | DRAW_TRANSP;
        } else {
            prim->v0 = (prim->v1 = 0xe3);
            prim->v2 = (prim->v3 = 0xaf);
            prim->x0 = (prim->x2 = xOffset);
            prim->x1 = (prim->x3 = xOffset + 0xe);
            prim->drawMode = DRAW_UNK_40 | DRAW_TPAGE2 | DRAW_TPAGE |
                             DRAW_UNK02 | DRAW_TRANSP;
        }

        prim->y0 = (prim->y1 = 0xAC);
        prim->y2 = (prim->y3 = 0xE0);
        prim = prim->next;
    }
}

void func_us_801C5EE4(Entity* self) {
    Primitive* prim;
    Entity* player;
    s32 scrollX;
    s32 clut;
    s32 upperBound;
    int playerPosRelTop;
    int playerPos;
    s32 scrollY;
    s32 scrollYWrap;
    s32 primIndex;

    player = g_Entities;
    scrollX = g_Tilemap.scrollX.i.hi;

    scrollY = g_Tilemap.scrollY.i.hi;
    scrollYWrap = ((0x500 - scrollY) / 24) + 0x4D;
    if (scrollYWrap > 0x7F) {
        scrollYWrap = 0x7F;
    }
    playerPos = (scrollX + player->posX.i.hi) - 0x128;
    if (playerPos > 0) {
        if (playerPos < 32) {
            playerPos = 0;
        } else {
            { playerPos = (playerPos - 32) / (-16); }
        }
        if (playerPos < (-8)) {
            playerPos = -8;
        }
    } else {
        if (playerPos > (-32)) {
            playerPos = 0;
        } else {
            playerPos = (playerPos + 32) / (-24);
        }
        if (playerPos > 8) {
            playerPos = 8;
        }
    }
    if (!self->step) {
        InitializeEntity(g_EInitInteractable);
        self->animSet = 0;
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 4);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->ext.et_801C5EE4.unk84 = 0;
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = (&g_PrimBuf[primIndex]);
        self->ext.et_801C5EE4.prim7C = prim;

        while (prim) {
            prim->priority = 0x9C;
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }
    }
    g_api.SetVolumeCommand22_23(scrollYWrap, playerPos);
    self->ext.et_801C5EE4.unk84 += 1;
    if (self->ext.et_801C5EE4.unk84 >= 0xE) {
        self->ext.et_801C5EE4.unk84 = 0;
    }
    clut = self->ext.et_801C5EE4.unk84 + 0xa0;
    prim = self->ext.et_801C5EE4.prim7C;
    playerPos = 0x50;
    upperBound = 0x550;
    upperBound = upperBound - scrollY;
    playerPos = playerPos - scrollY;
    if (playerPos < 0) {
        playerPos = 0;
    }
    if (upperBound > 0xF0) {
        upperBound = 0xF0;
    }
    playerPosRelTop = upperBound - playerPos;
    while (prim) {
        upperBound = playerPos + scrollY;
        {
            if (upperBound >= 0x452) {
                prim->tpage = 0xE;
                prim->u0 = (prim->u2 = 0x87);
                prim->u1 = (prim->u3 = 0xe7);
                prim->v2 = (prim->v3 = 0x550 - upperBound);
                prim->v0 = (prim->v1 = 0);
                scrollYWrap = 0x550 - upperBound;
                prim->x0 = (prim->x2 = 0x140 - scrollX);
                prim->x1 = (prim->x3 = 0xE0 - scrollX);
            } else {
                prim->tpage = 0xF;

                scrollYWrap = (0x452 - (playerPos + scrollY)) % 126;
                if (!scrollYWrap) {
                    scrollYWrap = 0x7E;
                }
                prim->u0 = (prim->u2 = 0xCC);
                prim->u1 = (prim->u3 = 0xFD);
                prim->v2 = (prim->v3 = scrollYWrap);
                if ((playerPos + 0x7E) < 0xF0) {
                    prim->v0 = (prim->v1 = 0);
                } else {
                    prim->v0 = (prim->v1 = playerPos - 0x72);
                };
                scrollYWrap = prim->v2 - prim->v0;
                if ((upperBound + scrollYWrap) > 0x452) {
                    scrollYWrap = upperBound - 0x452;
                    prim->v0 = (prim->v1 = prim->v2 - scrollYWrap);
                };
                prim->x0 = (prim->x2 = 0x140 - scrollX);
                prim->x1 = (prim->x3 = 0x10F - scrollX);
            }

            prim->y2 = (prim->y3 = playerPos);
            playerPos += scrollYWrap;
            playerPosRelTop -= scrollYWrap;
            prim->y0 = prim->y1 = playerPos;
#if defined(VERSION_PSP)
            prim->y2 -= 1;
            prim->y3 -= 1;
#endif
            prim->clut = clut;
            prim->drawMode = DRAW_TPAGE | DRAW_UNK02 | DRAW_TRANSP;
        }
        prim = prim->next;
        if (playerPosRelTop <= 0) {
            break;
        }
    }

    while (prim) {
        prim->drawMode = DRAW_HIDE;
        prim = prim->next;
    }
}

void func_us_801C2850_from_no4(Entity* self) {
    Primitive* prim;
    s32 primIndex;
    s32 scrollX;
    s32 scrollY;
    s32 var_s4;
    s32 var_s3;
    s32 var_s2;
    s32 var_s1;

    if (!self->step) {
        InitializeEntity(g_EInitInteractable);
        self->animSet = 0;
        primIndex = g_api.AllocPrimitives(PRIM_G4, 3);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.et_801C12B0.prim = prim;

        while (prim != NULL) {
            prim->priority = 0x9E;
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }
    }

    prim = self->ext.et_801C12B0.prim;
    scrollX = g_Tilemap.scrollX.i.hi;
    scrollY = g_Tilemap.scrollY.i.hi;
    self->ext.et_801C12B0.unk80++;
    if (scrollY < 0x410) {
        var_s4 = 0x20;
        var_s3 = 0x220;
        var_s4 -= scrollY;
        var_s3 -= scrollY;
        var_s1 = scrollY & 7;
        if (var_s4 < -0x10) {
            var_s4 = (-var_s1 & 7) - 0x10;
        }
        if (var_s3 > 0xF0) {
            var_s3 = (-var_s1 & 7) + 0xF0;
        }
        var_s1 = 0x220 - (var_s4 + scrollY);
        var_s2 = 0x220 - (var_s3 + scrollY);
        if (self->ext.et_801C12B0.unk80 & 1) {
            var_s1 *= 0x13;
            var_s1 /= 40;
            var_s2 *= 0x13;
            var_s2 /= 40;
        } else {
            var_s1 *= 0x12;
            var_s1 /= 40;
            var_s2 *= 0x12;
            var_s2 /= 40;
        }

        // Prim 1
        prim->r0 = prim->r1 = prim->b0 = prim->b1 = prim->g0 = prim->g1 =
            var_s1;
        prim->r2 = prim->r3 = prim->b2 = prim->b3 = prim->g2 = prim->g3 =
            var_s2;
        prim->x0 = prim->x2 = 0x180 - scrollX;
        prim->x1 = prim->x3 = 0xE0 - scrollX;
        prim->y0 = prim->y1 = var_s4;
        prim->y2 = prim->y3 = var_s3;
        prim->drawMode = DRAW_DITHERING | DRAW_TPAGE2 | DRAW_TPAGE |
                         DRAW_COLORS | DRAW_UNK02 | DRAW_TRANSP;
        prim = prim->next;

        // Prim 2
        prim->r0 = prim->r2 = prim->b0 = prim->b2 = prim->g0 = prim->g2 = 0;
        prim->r1 = prim->b1 = prim->g1 = var_s1;
        prim->r3 = prim->b3 = prim->g3 = var_s2;
        prim->x0 = prim->x2 = 0x1E0 - scrollX;
        prim->x1 = prim->x3 = 0x180 - scrollX;
        prim->y0 = prim->y1 = var_s4;
        prim->y2 = prim->y3 = var_s3;
        prim->drawMode = DRAW_DITHERING | DRAW_TPAGE2 | DRAW_TPAGE |
                         DRAW_COLORS | DRAW_UNK02 | DRAW_TRANSP;
        prim = prim->next;

        // Prim 3
        prim->r0 = prim->b0 = prim->g0 = var_s1;
        prim->r2 = prim->b2 = prim->g2 = var_s2;
        prim->r1 = prim->b1 = prim->g1 = prim->r3 = prim->b3 = prim->g3 = 0;
        prim->x0 = prim->x2 = 0xE0 - scrollX;
        prim->x1 = prim->x3 = 0x80 - scrollX;
        prim->y0 = prim->y1 = var_s4;
        prim->y2 = prim->y3 = var_s3;
        prim->drawMode = DRAW_DITHERING | DRAW_TPAGE2 | DRAW_TPAGE |
                         DRAW_COLORS | DRAW_UNK02 | DRAW_TRANSP;
        prim = prim->next;
    }

    while (prim != NULL) {
        prim->drawMode = DRAW_HIDE;
        prim = prim->next;
    }
}

void func_us_801C2B78_from_no4(Entity* self) {
    Primitive* prim;
    s32 i;
    s32 var_s2;
    s32 var_s3;
    s32 scrollX;
    s32 primIndex;
    s32 scrollY;

    if (!self->step) {
        InitializeEntity(g_EInitInteractable);
        self->animSet = 0;
        primIndex = g_api.AllocPrimitives(PRIM_TILE, 128);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.et_801C12B0.prim = prim;
        while (prim != NULL) {
            prim->priority = 0x6C;
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }
    }

    prim = self->ext.et_801C12B0.prim;
    scrollX = g_Tilemap.scrollX.i.hi;
    scrollY = g_Tilemap.scrollY.i.hi;
    self->ext.et_801C12B0.unk80++;
    if (scrollY < 0x130) {
        var_s3 = 0x50;
        var_s3 -= scrollY;
        for (i = 0; i < 4; i++) {
            while (prim != NULL) {
                if (prim->drawMode == DRAW_HIDE) {
                    prim->r0 = prim->b0 = prim->g0 = 0x80;
                    prim->x0 = ((((rand() % 11) * 4) + 0x115) - scrollX) + i;
                    prim->y0 = var_s3 - 4 + (rand() & 7);
                    prim->x1 = 0;
                    LOH(prim->r1) = 0;
                    prim->u0 = prim->v0 = 2;
                    LOW(prim->r2) = FIX(4);
                    LOW(prim->u1) = 0;
                    LOW(prim->x3) = (0x4000 - (rand() & 0xFF0));
                    LOW(prim->r3) = ((rand() & 0x1F00) - 0xF80);
                    prim->clut = 0x20;
                    prim->drawMode = DRAW_UNK02;
                    break;
                }

                prim = prim->next;
            }
        }
    }

    // This is probably an alternate Primitive
    prim = self->ext.et_801C12B0.prim;
    while (prim != NULL) {
        if (prim->drawMode != DRAW_HIDE) {
            LOH(prim->b1) = prim->x0;
            prim->y1 = prim->y0;
            LOW(prim->x1) -= LOW(prim->r2);
            LOW(prim->r1) += LOW(prim->u1);
            prim->x0 = LOH(prim->b1);
            prim->y0 = prim->y1;

            var_s2 = 0;
            if (LOW(prim->r2) < 0) {

            } else {
                var_s2 = 1;
            }
            LOW(prim->r2) -= LOW(prim->x3);
            LOW(prim->u1) -= LOW(prim->r3);

            if (!--prim->clut) {
                prim->drawMode = DRAW_HIDE;
            }
        }
        prim = prim->next;
    }
}

void func_us_801C2E60_from_no4(Entity* self) {
    s32 var_s5;
    s32 scrollX;
    s32 scrollY;
    s32 var_s2;
    s32 primIndex;
    Primitive* prim;

    if (!self->step) {
        InitializeEntity(g_EInitInteractable);
        self->animSet = 0;
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 32);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.et_801C12B0.prim = prim;
        while (prim != NULL) {
            prim->clut = PAL_CC_STONE_EFFECT;
            prim->tpage = 0x1A;
            prim->u0 = prim->u2 = 0;
            prim->u1 = prim->u3 = 0x1E;
            prim->v0 = prim->v1 = 0x7C;
            prim->v2 = prim->v3 = 0x60;
            prim->priority = 0x9D;
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }
    }

    prim = self->ext.et_801C12B0.prim;
    scrollX = g_Tilemap.scrollX.i.hi;
    scrollY = g_Tilemap.scrollY.i.hi;
    self->ext.et_801C12B0.unk80++;
    if (self->ext.et_801C12B0.unk80 >= LEN(D_us_80181478)) {
        self->ext.et_801C12B0.unk80 = 0;
    }
    if (scrollY < 0x180) {
        var_s2 = 0x50;
        var_s2 -= scrollY;

        while (prim != NULL) {
            if (prim->drawMode == DRAW_HIDE) {
                prim->y0 = prim->y1 = prim->y2 = prim->y3 = var_s2;
                var_s5 = (rand() & 3) - 9;
                prim->x2 = prim->x0 =
                    (D_us_80181478[self->ext.et_801C12B0.unk80] * 4) + 0x111 -
                    scrollX + var_s5;
                prim->x3 = prim->x1 = prim->x0 + 0x12;
                PGREY(prim, 0) = PGREY(prim, 1) = 0xFF;
                PGREY(prim, 2) = PGREY(prim, 3) = 0x80;
                prim->p1 = 0;
                prim->drawMode = DRAW_UNK_40 | DRAW_TPAGE2 | DRAW_TPAGE |
                                 DRAW_COLORS | DRAW_UNK02 | DRAW_TRANSP;
                break;
            }

            prim = prim->next;
        }
    }
    prim = self->ext.et_801C12B0.prim;
    while (prim != NULL) {
        if (prim->drawMode != DRAW_HIDE) {
            prim->y2++;
            if (rand() & 7) {
                prim->y2++;
            }
            prim->y3 = prim->y2;
            prim->p1++;
            prim->b1 -= 0x10;
            PGREY(prim, 0) = PGREY(prim, 1);
            prim->b3 -= 8;
            PGREY(prim, 2) = PGREY(prim, 3);
            if (prim->r0 < 0x11) {
                prim->drawMode = DRAW_HIDE;
            }
        }

        prim = prim->next;
    }
}

void func_us_801C3160_from_no4(Entity* self) {
    s32 scrollY;
    s32 primIndex;
    u16 iterations;
    u16 params;
    s32 scrollX;
    s32 i;
    s32 yOffset;
    s32 randVal;
    Primitive* prim;

    params = self->params;
    if (!self->step) {
        InitializeEntity(g_EInitInteractable);
        self->animSet = 0;
        if (!params) {
            primIndex = g_api.AllocPrimitives(PRIM_TILE, 0x80);
        } else {
            primIndex = g_api.AllocPrimitives(PRIM_TILE, 8);
        }
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = (s32)primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.et_801C12B0.prim = prim;
        while (prim != NULL) {
            prim->priority = 0x6C;
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }
    }

    // This is probably an alternative Primitive type
    scrollX = g_Tilemap.scrollX.i.hi;
    scrollY = g_Tilemap.scrollY.i.hi;
    self->ext.et_801C12B0.unk80++;
    prim = self->ext.et_801C12B0.prim;
    if (scrollY < g_Tilemap.height - 0xF0) {
        if (!params) {
            iterations = 4;
            yOffset = 0x550 - scrollY;
        } else {
            iterations = 1;
            yOffset = 0x12A - scrollY;
        }

        for (i = 0; i < iterations; i++) {
            while (prim != NULL) {
                if (prim->drawMode == DRAW_HIDE) {
                    if (!params) {
                        randVal = rand() & 0x1F;
                        prim->y0 = yOffset - randVal;
                        prim->x0 = (rand() % 40) - (scrollX - 0x100) + randVal;
                        LOW(prim->u1) = FIX(2);
                        prim->u0 = prim->v0 = 2;
                        LOW(prim->r2) = 0;
                        prim->clut = 0x10;
                    } else {
                        prim->y0 = yOffset - (rand() & 3);
                        prim->x0 = 0x1F2 - (rand() & 3);
                        prim->x0 -= scrollX;
                        LOW(prim->u1) = FIX(-1.25);
                        LOW(prim->r2) = ((rand() & 0x1F) << 0xB);
                        prim->u0 = prim->v0 = 1;
                        prim->clut = 8;
                    }
                    prim->r0 = prim->b0 = prim->g0 = 0x80;
                    prim->x1 = 0;
                    LOH(prim->r1) = 0;
                    LOW(prim->x3) = 0x4000;
                    LOW(prim->r3) = 0;
                    prim->drawMode = DRAW_UNK02;
                    break;
                }

                prim = prim->next;
            }
        }
    }

    // This is probably an alternate Primitive
    prim = self->ext.et_801C12B0.prim;
    while (prim != NULL) {
        if (prim->drawMode != DRAW_HIDE) {
            LOH(prim->b1) = prim->x0;
            prim->y1 = prim->y0;
            LOW(prim->x1) = LOW(prim->x1) - LOW(prim->r2);
            LOW(prim->r1) = LOW(prim->r1) + LOW(prim->u1);
            prim->x0 = LOH(prim->b1);
            prim->y0 = prim->y1;
            LOW(prim->r2) = LOW(prim->r2) + LOW(prim->x3);
            prim->r0 = prim->b0 = prim->g0 -= 8;
            if (!--prim->clut) {
                prim->drawMode = DRAW_HIDE;
            }
        }
        prim = prim->next;
    }
}

void func_us_801C34EC_from_no4(Entity* self) {
    s32 scrollX;
    s16 xOffset;
    s16 randX;
    s16 randY;
    s16 tpage;
    s32 yOffset;
    s32 scrollY;
    s32 primIndex;
    s16* ptr;
    Primitive* prim;

    if (!self->step) {
        InitializeEntity(g_EInitInteractable);
        self->animSet = 0;
        primIndex = g_api.AllocPrimitives(PRIM_TILE, 0x40);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.et_801C12B0.prim = prim;
        while (prim != NULL) {
            prim->priority = 0x9B;
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }
    }

    ptr = D_us_80181494[self->params];
    xOffset = *ptr++;
    randX = *ptr++;
    yOffset = *ptr++;
    randY = *ptr++;
    tpage = *ptr;
    prim = self->ext.et_801C12B0.prim;
    scrollX = g_Tilemap.scrollX.i.hi;
    scrollY = g_Tilemap.scrollY.i.hi;
    self->ext.et_801C12B0.unk80++;
    if (scrollY < 0xF0) {
        yOffset -= scrollY;

        while (prim != NULL) {
            if (prim->drawMode == DRAW_HIDE) {
                prim->r0 = prim->b0 = prim->g0 = 0x80;
                prim->y0 = yOffset + (rand() % randY);
                prim->x0 = (xOffset - scrollX) + (rand() % randX);
                prim->x1 = 0;
                LOH(prim->r1) = 0;
                prim->u0 = prim->v0 = 2;
                LOW(prim->u1) = 0;
                prim->tpage = tpage;
                prim->drawMode = DRAW_UNK02;
                break;
            }

            prim = prim->next;
        }
    }

    // This is probably an alternate Primitive
    prim = self->ext.et_801C12B0.prim;
    while (prim != NULL) {
        if (prim->drawMode != DRAW_HIDE) {
            LOH(prim->b1) = prim->x0;
            LOW(prim->r1) += LOW(prim->u1);
            prim->x0 = LOH(prim->b1);
            prim->r0 -= 8;
            prim->b0 = prim->g0 = prim->r0;
            if (prim->r0 < 8) {
                prim->drawMode = DRAW_HIDE;
            }
        }
        prim = prim->next;
    }
}

void func_us_801C37C8_from_no4(Entity* self) {
    Primitive* prim;
    s32 scrollX;
    s32 scrollY;
    s32 xOffset;
    s32 primIndex;
    s32 clut;

    if (!self->step) {
        InitializeEntity(g_EInitInteractable);
        self->animSet = 0;
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 1);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->ext.et_801C12B0.clut = 0;
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.et_801C12B0.prim = prim;
        prim->tpage = 0xF;
        prim->v0 = prim->v1 = 0x7F;
        prim->v2 = prim->v3 = 1;
        prim->priority = 0x9C;
        prim->drawMode = DRAW_HIDE;
    }

    scrollX = (rand() & 0x1F) - 0x10;
    D_us_80181094[40] = scrollX + 0xB30;
    D_us_80181094[41] = 0x180 - scrollX;
    D_us_80181094[36] = scrollX + 0x4C;
    D_us_80181094[25] = scrollX + 0x7C0;
    D_us_80181094[26] = 0x70 - scrollX;
    D_us_80181094[21] = scrollX + 0x2B0;
    self->ext.et_801C12B0.clut++;
    if (self->ext.et_801C12B0.clut >= 0xE) {
        self->ext.et_801C12B0.clut = 0;
    }

    clut = self->ext.et_801C12B0.clut + 0xA0;
    prim = self->ext.et_801C12B0.prim;
    scrollX = g_Tilemap.scrollX.i.hi;
    scrollY = g_Tilemap.scrollY.i.hi;

    if (scrollX < 0x898) {
        xOffset = 0x828 - scrollX;
        if (xOffset < 0x100) {
            prim->u0 = prim->u2 = 0x11;
            prim->u1 = prim->u3 = 0x80;
        } else {
            prim->drawMode = DRAW_HIDE;
            return;
        }
    } else if (scrollX < 0xAE8) {
        xOffset = 0xA78 - scrollX;
        if (xOffset < 0x100) {
            prim->u0 = prim->u2 = 0x80;
            prim->u1 = prim->u3 = 0x11;
        } else {
            prim->drawMode = DRAW_HIDE;
            return;
        }
    } else {
        prim->drawMode = DRAW_HIDE;
        return;
    }

    prim->clut = clut;
    prim->x0 = prim->x2 = xOffset;
    prim->x1 = prim->x3 = xOffset + 0x6F;
    prim->y0 = prim->y1 = 0xD1 - scrollY;
    prim->y2 = prim->y3 = prim->y0 + 0x7F;
    prim->drawMode = DRAW_TPAGE | DRAW_UNK02 | DRAW_TRANSP;
}

void func_us_801C3A04_from_no4(Entity* self) {
    Primitive* prim;
    s32 i;
    s32 var_s2;
    s32 yOffset;
    s32 posX;
    s32 primIndex;
    s32 scrollY;

    if (!self->step) {
        InitializeEntity(g_EInitCommon);
        self->animSet = 0;
        primIndex = g_api.AllocPrimitives(PRIM_TILE, 0x40);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.et_801C12B0.prim = prim;

        while (prim != NULL) {
            prim->priority = 0x6C;
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }
    }

    prim = self->ext.et_801C12B0.prim;
    posX = self->posX.i.hi;
    scrollY = g_Tilemap.scrollY.i.hi;
    self->ext.et_801C12B0.unk80++;
    yOffset = 0xE0;
    yOffset -= scrollY;

    // This is probably an alternate Primitive
    for (i = 0; i < 2; i++) {
        while (prim != NULL) {
            if (prim->drawMode == DRAW_HIDE) {
                prim->r0 = prim->b0 = prim->g0 = 0x80;
                prim->x0 = ((rand() % 0x10) * 2) + i + posX;
                prim->y0 = yOffset - 4 + (rand() & 7);
                prim->x1 = 0;
                LOH(prim->r1) = 0;
                prim->u0 = prim->v0 = 2;
                LOW(prim->r2) = 0x40000;
                LOW(prim->u1) = 0;
                LOW(prim->x3) = 0x4000 - (rand() & 0xFF0);
                LOW(prim->r3) = (rand() & 0x1F00) - 0xF80;
                prim->clut = 0x20;
                prim->drawMode = DRAW_UNK02;
                break;
            }

            prim = prim->next;
        }
    }

    // This is probably an alternate Primitive
    prim = self->ext.et_801C12B0.prim;
    while (prim != NULL) {
        if (prim->drawMode != DRAW_HIDE) {
            LOH(prim->b1) = prim->x0;
            prim->y1 = prim->y0;
            LOW(prim->x1) -= LOW(prim->r2);
            LOW(prim->r1) += LOW(prim->u1);
            prim->x0 = LOH(prim->b1);
            prim->y0 = prim->y1;

            var_s2 = 0;
            if (LOW(prim->r2) >= 0) {
                var_s2 = 1;
            }
            LOW(prim->r2) -= LOW(prim->x3);
            LOW(prim->u1) -= LOW(prim->r3);
            if (!--prim->clut) {
                prim->drawMode = DRAW_HIDE;
            }
        }
        prim = prim->next;
    }
}

void func_us_801C3CC4_from_no4(Entity* self) {
    s32 var_s5;
    s32 posX;
    s32 scrollY;
    s32 var_s2;
    s32 primIndex;
    Primitive* prim;

    if (!self->step) {
        InitializeEntity(g_EInitParticle);
        self->animSet = 0;
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 0x20);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.et_801C12B0.prim = prim;
        while (prim != NULL) {
            prim->clut = PAL_CC_STONE_EFFECT;
            prim->tpage = 0x1A;
            prim->u0 = prim->u2 = 0;
            prim->u1 = prim->u3 = 0x1E;
            prim->v0 = prim->v1 = 0x7C;
            prim->v2 = prim->v3 = 0x60;
            prim->priority = 0x9D;
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }
    }

    prim = self->ext.et_801C12B0.prim;
    posX = self->posX.i.hi;
    scrollY = g_Tilemap.scrollY.i.hi;
    self->ext.et_801C12B0.unk80++;
    if (self->ext.et_801C12B0.unk80 >= 9) {
        self->ext.et_801C12B0.unk80 = 0;
    }
    var_s2 = 0xE0;
    var_s2 -= scrollY;

    while (prim != NULL) {
        if (prim->drawMode == DRAW_HIDE) {
            prim->y0 = prim->y1 = prim->y2 = prim->y3 = var_s2;
            var_s5 = rand() & 3;
            prim->x2 = prim->x0 =
                (D_us_801814A8[self->ext.et_801C12B0.unk80] * 4) + var_s5 -
                0x19 + posX;
            prim->x3 = prim->x1 = prim->x0 + 0x12;
            PGREY(prim, 0) = PGREY(prim, 1) = 0xFF;
            PGREY(prim, 2) = PGREY(prim, 3) = 0x80;
            prim->p1 = 0;
            prim->drawMode = DRAW_UNK_40 | DRAW_TPAGE2 | DRAW_TPAGE |
                             DRAW_COLORS | DRAW_UNK02 | DRAW_TRANSP;
            break;
        }

        prim = prim->next;
    }

    prim = self->ext.et_801C12B0.prim;

    while (prim != NULL) {
        if (prim->drawMode != DRAW_HIDE) {
            prim->y2++;
            if (rand() & 3) {
                prim->y2++;
            }
            prim->y3 = prim->y2;
            prim->p1++;
            prim->b1 -= 0x10;
            PGREY(prim, 0) = PGREY(prim, 1);
            prim->b3 -= 8;
            PGREY(prim, 2) = PGREY(prim, 3);
            if (prim->r0 < 0x11) {
                prim->drawMode = DRAW_HIDE;
            }
        }

        prim = prim->next;
    }
}

void func_us_801C3FB0_from_no4(Entity* self) {
    s32 primIndex;
    s32 scrollX;
    s32 scrollY;
    s16* ptr;
    s32 clut;
    s32 var_s4;
    s32 var_s3;
    s32 var_s2;
    s32 var_s1;
    Primitive* prim;

    if (!self->step) {
        InitializeEntity(g_EInitInteractable);
        self->animSet = 0;
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 0x10);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->ext.et_801C12B0.clut = 0;
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.et_801C12B0.prim = prim;

        while (prim != NULL) {
            prim->tpage = 0xF;
            prim->u0 = prim->u2 = 0x82;
            prim->u1 = prim->u3 = 0x9D;
            prim->priority = 0xC0;
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }
    }

    prim = self->ext.et_801C12B0.prim;
    ptr = D_us_801814BC;
    self->ext.et_801C12B0.clut++;
    if (self->ext.et_801C12B0.clut >= 0xE) {
        self->ext.et_801C12B0.clut = 0;
    }
    scrollX = g_Tilemap.scrollX.i.hi;
    scrollX *= 5;
    scrollX /= 4;

    scrollY = g_Tilemap.scrollY.i.hi;
    scrollY *= 5;
    scrollY /= 4;
    scrollY %= 0x20;

    clut = self->ext.et_801C12B0.clut + 0x90;

    while (prim != NULL) {
        var_s3 = *ptr++;
        var_s3 -= scrollX;
        if (var_s3 < -0x1B) {
            continue;
        }

        if (var_s3 >= 0x100) {
            break;
        }

        var_s4 = scrollY + *ptr++;
        var_s2 = 0x60 - var_s4;
        var_s1 = 0;

        while (prim != NULL) {
            prim->clut = clut;
            prim->v0 = prim->v1 = 0x63 - var_s4;
            prim->v2 = prim->v3 = prim->v0 - var_s2;
            prim->x0 = prim->x2 = var_s3;
            prim->x1 = prim->x3 = var_s3 + 0x1B;
            prim->y0 = prim->y1 = var_s1;
            var_s1 += var_s2;
            prim->y2 = prim->y3 = var_s1;
            prim->drawMode =
                DRAW_UNK_40 | DRAW_TPAGE2 | DRAW_TPAGE | DRAW_TRANSP;
            prim = prim->next;

            if (var_s1 >= 0xE8) {
                break;
            }

            var_s4 = 0;
            if (var_s1 > 0x88) {
                var_s2 = 0xE8 - var_s1;
            } else {
                var_s2 = 0x60;
            }
        }
    }

    while (prim != NULL) {
        prim->drawMode = DRAW_HIDE;
        prim = prim->next;
    }
}

void func_us_801C4228_from_no4(Entity* self) {
    s32 scrollY;
    s32 scrollX;
    s32 primIndex;
    s32 yOffset;
    s32 yMax;
    s32 xOffset;
    Primitive* prim;

    if (!self->step) {
        InitializeEntity(g_EInitInteractable);
        self->animSet = 0;
        primIndex = g_api.AllocPrimitives(PRIM_G4, 4);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.et_801C12B0.prim = prim;

        while (prim != NULL) {
            prim->priority = 0xC0;
            prim->r0 = prim->r2 = prim->g0 = prim->g2 = prim->r1 = prim->r3 =
                prim->g1 = prim->g3 = 0x10;
            prim->b0 = prim->b2 = prim->b1 = prim->b3 = 0;
            prim = prim->next;
        }
    }

    prim = self->ext.et_801C12B0.prim;
    scrollX = g_Tilemap.scrollX.i.hi;
    scrollY = g_Tilemap.scrollY.i.hi;
    if (scrollX < 0x70) {
        xOffset = PLAYER.posX.i.hi - 0x10;
    } else {
        xOffset = 0xE0 - scrollX;
    }
    yOffset = 0x30 - scrollY;
    yMax = yOffset + 0x80;
    if (yMax > 0 && xOffset > -0x10) {
        // Prim 1
        prim->x0 = prim->x2 = xOffset;
        prim->x1 = prim->x3 = xOffset - 0x30;
        prim->y0 = prim->y1 = yOffset;
        prim->y2 = prim->y3 = yMax;
        prim->r1 = prim->r3 = prim->g1 = prim->g3 = prim->b1 = prim->b3 = 0xFF;
        prim->r0 = prim->r2 = prim->g0 = prim->g2 = prim->b0 = prim->b2 = 0;
        prim->drawMode =
            DRAW_UNK_40 | DRAW_TPAGE | DRAW_COLORS | DRAW_UNK02 | DRAW_TRANSP;
        prim = prim->next;

        // Prim 2
        prim->x0 = prim->x2 = xOffset - 1;
        xOffset -= 3;
        prim->x1 = prim->x3 = xOffset;
        prim->y0 = prim->y1 = yOffset;
        prim->y2 = prim->y3 = yMax;
        prim->r0 = prim->r2 = prim->g0 = prim->g2 = 7;
        prim->b0 = prim->b2 = prim->b1 = prim->b3 = 0;
        prim->r1 = prim->r3 = prim->g1 = prim->g3 = 8;
        prim->drawMode =
            DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS | DRAW_UNK02 | DRAW_TRANSP;
        prim->priority = 0xC1;
        prim = prim->next;

        // Prim 3
        prim->x0 = prim->x2 = xOffset;
        xOffset -= 0x2D;
        prim->x1 = prim->x3 = xOffset;
        prim->y0 = prim->y1 = yOffset;
        prim->y2 = prim->y3 = yMax;

        prim->r0 = prim->r2 = prim->g0 = prim->g2 = prim->r1 = prim->r3 =
            prim->g1 = prim->g3 = 0x10;
        prim->b0 = prim->b2 = prim->b1 = prim->b3 = 0;
        prim->drawMode =
            DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS | DRAW_UNK02 | DRAW_TRANSP;
        prim->priority = 0xC1;
        prim = prim->next;

        // Prim 4
        if (xOffset > -0x10) {
            prim->x0 = prim->x2 = -0x10;
            prim->x1 = prim->x3 = xOffset;
            prim->y0 = prim->y1 = yOffset;
            prim->y2 = prim->y3 = yMax;
            prim->drawMode = DRAW_UNK02;
            prim = prim->next;
        }
    }

    while (prim != NULL) {
        prim->drawMode = DRAW_HIDE;
        prim = prim->next;
    }
}
