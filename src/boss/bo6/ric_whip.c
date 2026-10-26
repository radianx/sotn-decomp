// SPDX-License-Identifier: AGPL-3.0-or-later
#include "bo6.h"

extern EInit D_us_8018040C;
extern EInit D_us_80180418;
extern Point16 D_us_801824EC[];
extern Point16 D_us_80182508[];
extern Point16 D_us_80182524[];
extern s16 D_us_80182548[];
extern Point16 D_us_8018255C[];
extern s16 D_us_80182580[];
extern Point16 D_us_80182594[];
extern s16 D_us_801825B8[];
extern Point32 D_us_801825EC[];
extern Point32 D_us_80182624[];
extern s32 D_us_8018266C[];
extern s32 D_us_80182690[];
extern s32 D_us_801826B4[];
extern s32 D_us_801826D8[];
extern s32 D_us_801826FC[];
extern s32 D_us_80182720[];
extern s32 D_us_80182744[];
extern s32 D_us_80182768[];
extern s32 D_us_8018278C[];
extern u16 D_us_801827B0[3];
extern s16 D_us_801827B8[];
extern u16 D_us_801827D8[];
extern s32 D_us_801D0874;
extern s32 D_us_801D0878;

void RicEntityWhip(Entity* self) {
    byte stackpad[40];
    s16 sp4E;
    s16 radius;
    s32 sp44;
    s32 sp40;
    s32 prevX;
    s32 prevY;
    s16 sp4A;
    s32 aimPath;
    s32 newY;
    s16 angle;
    s32 diffY;
    s16 segmentIndex;
    s32 diffX;
    s32 newX;
    Primitive* prim;
    s32 direction;

#ifdef FIX_UB
    sp40 = 0;
    direction = 0;
#endif

    segmentIndex = self->params & 0xFF;
    sp4A = self->params & 0xFF00;
    if (segmentIndex == 0) {
        if (self->ext.whip.unkA6) {
            self->ext.whip.unkA6--;
        }
    }
    if (g_Ric.unk46 == 0) {
        DestroyEntity(self);
        return;
    }
    if (self->step == 2 && g_Ric.unk46 == 2) {
        self->step = 1;
        self->velocityX = 0;
        self->velocityY = 0;
        self->palette = PAL_FLAG(0x248);
        if (RIC.facingLeft == 0) {
            self->ext.whip.unk88 = 2;
        } else {
            self->ext.whip.unk88 = 3;
        }
        self->ext.whip.unk8C = 0x600;
    }
    if (self->step) {
        diffX = self->posX.val - self->ext.whip.curX;
        diffY = self->posY.val - self->ext.whip.curY;
        self->ext.whip.prevX += diffX;
        self->ext.whip.prevY += diffY;
    }
    aimPath = g_Ric.padPressed & (PAD_UP | PAD_RIGHT | PAD_DOWN | PAD_LEFT);
    // Opposing directions leave the original direction variable uninitialized.
    ASSERT(aimPath != (PAD_UP | PAD_DOWN));
    ASSERT(aimPath != (PAD_LEFT | PAD_RIGHT));
    if (aimPath == PAD_UP) {
        direction = D_us_8018266C[self->ext.whip.unk88];
    }
    if (aimPath == PAD_DOWN) {
        direction = D_us_801826D8[self->ext.whip.unk88];
    }
    if (aimPath == PAD_RIGHT) {
        direction = D_us_80182690[self->ext.whip.unk88];
    }
    if (aimPath == PAD_LEFT) {
        direction = D_us_801826B4[self->ext.whip.unk88];
    }
    if (aimPath == (PAD_UP + PAD_RIGHT)) {
        direction = D_us_801826FC[self->ext.whip.unk88];
    }
    if (aimPath == (PAD_UP + PAD_LEFT)) {
        direction = D_us_80182720[self->ext.whip.unk88];
    }
    if (aimPath == (PAD_DOWN + PAD_RIGHT)) {
        direction = D_us_80182744[self->ext.whip.unk88];
    }
    if (aimPath == (PAD_DOWN + PAD_LEFT)) {
        direction = D_us_80182768[self->ext.whip.unk88];
    }
    if (aimPath == 0) {
        direction = D_us_8018278C[self->ext.whip.unk88];
    }

    self->ext.whip.unk86 = 0;
    if (segmentIndex == 0) {
        if (self->step == 1) {
            if (RIC.step == PL_S_CROUCH) {
                if (RIC.facingLeft == 0) {
                    newX = D_us_80182580[direction];
                } else {
                    newX = D_us_8018255C[direction].x;
                }
                newY = D_us_8018255C[direction].y;
            } else if (RIC.step == PL_S_STAND) {
                if (RIC.facingLeft == 0) {
                    newX = D_us_80182548[direction];
                } else {
                    newX = D_us_80182524[direction].x;
                }
                newY = D_us_80182524[direction].y;
            } else {
                if (RIC.facingLeft == 0) {
                    newX = D_us_801825B8[direction];
                } else {
                    newX = D_us_80182594[direction].x;
                }
                newY = D_us_80182524[direction].y;
            }
        } else {
            if (RIC.step == PL_S_CROUCH) {
                newX = D_us_80182508[RIC.pose].x;
                newY = D_us_80182508[RIC.pose].y;
            } else {
                newX = D_us_801824EC[RIC.pose].x;
                newY = D_us_801824EC[RIC.pose].y;
            }
            if (RIC.facingLeft == 0) {
                newX = -newX;
            }
        }
        newX *= FIX(1);
        newY *= FIX(1);
        newX += RIC.posX.val;
        newY += RIC.posY.val;
    } else {
        self--;
        newX = self->posX.val;
        newY = self->posY.val;
        self++;
    }
    switch (self->step) {
    case 0:
        InitializeEntity(sp4A ? D_us_80180418 : D_us_8018040C);
        self->animSet = ANIMSET_OVL(3);
        self->animCurFrame = 0x1D;
        self->animCurFrame = 0x1E;
        self->palette = PAL_FLAG(0x238);
        self->unk5A = 0x24;
        if (segmentIndex < 8) {
            self->hitboxWidth = 3;
            self->hitboxHeight = 3;
            self->hitboxOffX = 0;
            self->hitboxOffY = 0;
        }
        if (segmentIndex == 0) {
            self->zPriority = RIC.zPriority - 2;
        }
        if (segmentIndex == 7) {
            self->animCurFrame = 0x1F;
            self->hitboxWidth++;
            self->hitboxHeight++;
        }
        self->zPriority = RIC.zPriority + 4;
        self->flags = FLAG_POS_CAMERA_LOCKED | FLAG_UNK_10000000;
        self->posX.val = newX;
        self->posY.val = newY;
        self->ext.whip.prevX = self->posX.val;
        self->ext.whip.prevY = self->posY.val;
        self->ext.whip.curX = self->ext.whip.prevX;
        self->ext.whip.curY = self->ext.whip.prevY;
        self->ext.whip.unk8C = 0x500;
        self->primIndex = g_api.AllocPrimitives(PRIM_LINE_G2, 1);
        if (self->primIndex != -1) {
            self->flags |= FLAG_HAS_PRIMS;
            prim = &g_PrimBuf[self->primIndex];
            PGREY(prim, 0) = 0x7F;
            PGREY(prim, 1) = 0x1F;
            prim->priority = RIC.zPriority + 2;
            prim->drawMode =
                DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS | DRAW_TRANSP;
        }
        self->step = 2;
        RicEntityWhip(self);
        break;
    case 1:
        if (sp4A == 0) {
            if (self->palette < PAL_FLAG(0x248) &&
                self->palette >= PAL_FLAG(0x240)) {
                if (self->ext.whip.unkA4) {
                    self->ext.whip.unkA4--;
                } else {
                    self->palette++;
                }
            }
        } else if (self->ext.whip.unkA4) {
            if (!(segmentIndex & 1)) {
                RicCreateEntFactoryFromEntity(self, BP_20, 0);
                self->ext.whip.unkA4 = 0;
            }
        }
        if (segmentIndex < 8) {
            if (self->ext.whip.unk84) {
                if (--self->ext.whip.unk84 == 0) {
                    if (self->velocityY < 0) {
                        self->velocityY = 0;
                    }
                    self->velocityX = 0;
                }
            } else {
                self->velocityX = self->velocityX * 3 / 4;
            }
            if (self->ext.whip.unk88 == direction) {
                break;
            }
            if (segmentIndex == 0) {
                if (sp4A) {
                    if (self->ext.whip.unkA6 == 0) {
                        g_api.PlaySfx(SFX_RIC_WHIP_RATTLE_A);
                        self->ext.whip.unkA6 = 0x20;
                    }
                } else {
                    if (self->ext.whip.unkA6 == 0) {
                        g_api.PlaySfx(SFX_RIC_WHIP_RATTLE_A);
                        self->ext.whip.unkA6 = 0x20;
                    }
                }
                if (sp4A == 0) {
                    RicCreateEntFactoryFromEntity(self, FACTORY(BP_18, 0), 0);
                } else {
                    RicCreateEntFactoryFromEntity(self, FACTORY(BP_18, 1), 0);
                }
            }

            self->ext.whip.unk84 = 6;
            if (direction == 0) {
                if (RIC.facingLeft == 0) {
                    diffX = D_us_80182548[0];
                } else {
                    diffX = D_us_80182524[0].x;
                }
                diffY = D_us_80182524[0].y;
                diffX += RIC.posX.i.hi;
                diffY += RIC.posY.i.hi;
                diffX *= FIX(1);
                diffY *= FIX(1);

                diffX -= self->posX.val;
                diffY -= self->posY.val;
                angle = ratan2(-diffY, diffX);
                radius = 0x80;
                self->velocityX = (radius * rcos(angle)) >> 4;
                self->velocityY = -(radius * rsin(angle)) >> 4;
            } else {
                self->velocityY = D_us_80182624[direction].x;
                self->velocityX = D_us_80182624[direction].y;
            }
            self->ext.whip.unk88 = direction;
        }
        break;
    case 2:
        if (segmentIndex > 7) {
            if (self->flags & FLAG_HAS_PRIMS) {
                if (RIC.pose == 5) {
                    g_api.FreePrimitives(self->primIndex);
                    self->flags &= ~FLAG_HAS_PRIMS;
                }
            }
            if (RIC.pose == 6) {
                if (RIC.poseTimer > 14) {
                    self->palette = PAL_FLAG(0x238);
                } else if (RIC.poseTimer == 0) {
                    self->palette = PAL_FLAG(0x238);
                } else if ((RIC.poseTimer == 11 || RIC.poseTimer == 12) ||
                           (RIC.poseTimer == 13 || RIC.poseTimer == 14)) {
                    self->palette = PAL_FLAG(0x23C);
                } else {
#ifdef FIX_UB
                    // The original can index before the table when poseTimer is
                    // -1.
                    if (RIC.poseTimer >= 0) {
                        self->palette =
                            D_us_801827B0[RIC.poseTimer % LEN(D_us_801827B0)];
                    }
#else
                    self->palette =
                        D_us_801827B0[RIC.poseTimer % LEN(D_us_801827B0)];
#endif
                }
            }
        } else {
            self->velocityX = D_us_801825EC[RIC.pose].x;
            self->velocityY = D_us_801825EC[RIC.pose].y;
            switch (RIC.pose) {
            case 0:
                radius = 0x800;
                angle = (rand() & 0x3FF) - 0x200;
                self->velocityX = (radius * rcos(angle)) >> 4;
                self->velocityY = -(radius * rsin(angle)) >> 4;
                break;
            case 1:
                radius = 0x800;
                angle = (rand() & 0x3FF) - 0x400;
                self->velocityX = (radius * rcos(angle)) >> 4;
                self->velocityY = -(radius * rsin(angle)) >> 3;
                self->ext.whip.unk8C = 0x600;
                break;
            case 4:
                self->ext.whip.unk8C = 0x3C0;
                if (RIC.poseTimer == 1) {
                    self->velocityX = FIX(-8);
                }
                break;
            case 5:
                self->ext.whip.unk8C += 0xC0;
                if (self->flags & FLAG_HAS_PRIMS) {
                    g_api.FreePrimitives(self->primIndex);
                    self->flags &= ~FLAG_HAS_PRIMS;
                }
                break;
            case 6:
                if (sp4A) {
                    if (RIC.poseTimer == D_us_801827B8[segmentIndex]) {
                        RicCreateEntFactoryFromEntity(self, BP_20, 0);
                    }
                }
                if (segmentIndex == (0x10 - RIC.poseTimer)) {
                    self->ext.whip.unk8C = 0x600;
                }
                if (RIC.poseTimer > 14) {
                    self->palette = PAL_FLAG(0x238);
                } else if (RIC.poseTimer == 0) {
                    self->palette = PAL_FLAG(0x238);
                } else if (RIC.poseTimer == 11 || RIC.poseTimer == 12 ||
                           RIC.poseTimer == 13 || RIC.poseTimer == 14) {
                    self->palette = PAL_FLAG(0x23C);
                } else {
#ifdef FIX_UB
                    // The original can index before the table when poseTimer is
                    // -1.
                    if (RIC.poseTimer >= 0) {
                        self->palette = D_us_801827B0[RIC.poseTimer % 3];
                    }
#else
                    self->palette = D_us_801827B0[RIC.poseTimer % 3];
#endif
                }
                break;
            }
            if (RIC.facingLeft == 0) {
                self->velocityX = -self->velocityX;
            }
            self->velocityX = self->velocityX / 2;
            self->velocityY = self->velocityY / 2;
        }
        break;
    }
    sp4E = self->ext.whip.unk8C;
    prevX = self->posX.val;
    prevY = self->posY.val;
    if (segmentIndex == 0) {
        self->posX.val = newX;
        self->posY.val = newY;
    } else if (segmentIndex > 7) {
        diffX = (self - 8)->posX.val;
        diffY = (self - 8)->posY.val;
        sp44 = (self - 7)->posX.val;
        sp40 = (self - 7)->posY.val;
        self->posX.val = (diffX + sp44) / 2;
        self->posY.val = (diffY + sp40) / 2;
    } else {
        sp44 = self->posX.val - self->ext.whip.prevX;
        sp40 = self->posY.val - self->ext.whip.prevY;
        if (self->step == 1) {
            if (self->velocityY < FIX(0.5)) {
                self->posX.val += sp44 * 16 / 16;
                self->posY.val += sp40 * 16 / 16;
            }
            if (self->velocityY >= FIX(0.5) && self->velocityY < FIX(1.25)) {
                self->posX.val += sp44 * 15 / 16;
                self->posY.val += sp40 * 15 / 16;
            }
            if (self->velocityY >= FIX(1.25) || self->velocityY < 0) {
                self->posX.val += sp44 * 13 / 16;
                self->posY.val += sp40 * 13 / 16;
            }
        } else {
            self->posX.val += sp44 * 3 / 4;
            self->posY.val += sp40 * 3 / 4;
        }
        if (self->velocityY < FIX(8) || self->velocityY < 0) {
            self->velocityY += 0xA00;
        }
        self->posX.val += self->velocityX;
        self->posY.val += self->velocityY;
        diffY = self->posY.val - newY;
        diffX = self->posX.val - newX;
        if (((sp4E * sp4E) >> 0x10) < ((diffY * (diffY >> 0x10)) >> 0x10) +
                                          ((diffX * (diffX >> 0x10)) >> 0x10)) {
            angle = ratan2(-diffY, diffX);
            diffX = (rcos(angle) * sp4E) >> 4;
            diffY = -(rsin(angle) * sp4E) >> 4;
            self->posX.val = newX + diffX;
            self->posY.val = newY + diffY;
        }
    }
    self->ext.whip.prevX = prevX;
    self->ext.whip.prevY = prevY;
    self->ext.whip.curX = self->posX.val;
    self->ext.whip.curY = self->posY.val;
    self->ext.whip.unkA0 = sp40;
    if (segmentIndex == 0) {
        D_us_801D0874 = direction;
        D_us_801D0878 = self->ext.whip.unk88;
    }
    if (self->primIndex != -1 && (self->flags & FLAG_HAS_PRIMS)) {
        prim = &g_PrimBuf[self->primIndex];
        prim->x0 = self->posX.i.hi;
        prim->y0 = self->posY.i.hi;
        prim->x1 = self->ext.whip.prevX >> 0x10;
        prim->y1 = self->ext.whip.prevY >> 0x10;
        if (RIC.pose == 4) {
            prim->priority = RIC.zPriority + 4;
        } else {
            prim->priority = RIC.zPriority + 2;
        }
    }
    if (sp4A) {
        if (segmentIndex != 7) {
            angle =
                (((g_GameTimer >> 2) & 7) + D_us_801827D8[segmentIndex]) * 512;
            self->opacity = (rsin(angle) >> 6) + 0x80;
            self->drawFlags |= DRAW_HIDE;
            self->blendMode = BLEND_TRANSP | BLEND_ADD;
        }
        self->palette = PAL_FLAG(PAL_CC_FIRE_EFFECT);
    }
}

extern s32 D_us_801D0874;
extern s16 D_us_8018280C[];
extern s16 D_us_801827F8[];
extern s16 D_us_80182834[];
extern s16 D_us_80182820[];
extern s16 D_us_8018285C[];
extern s16 D_us_80182848[];

void RicEntityArmBrandishWhip(Entity* entity) {
    if (g_Ric.unk46 == 0) {
        DestroyEntity(entity);
        return;
    }
    entity->facingLeft = RIC.facingLeft;
    if (entity->step == 0) {
        entity->flags = FLAG_UNK_10000000 | FLAG_POS_CAMERA_LOCKED;
        entity->animSet = ANIMSET_OVL(3);
        entity->unk5A = 0x24;
        entity->palette = PAL_FLAG(0x220);
        entity->zPriority = RIC.zPriority + 2;
    }
    if (RIC.step == PL_S_CROUCH) {
        if (RIC.facingLeft) {
            entity->animCurFrame = D_us_8018280C[D_us_801D0874];
        } else {
            entity->animCurFrame = D_us_801827F8[D_us_801D0874];
        }
    } else if (RIC.step == PL_S_STAND) {
        if (RIC.facingLeft) {
            entity->animCurFrame = D_us_80182834[D_us_801D0874];
        } else {
            entity->animCurFrame = D_us_80182820[D_us_801D0874];
        }
    } else if (RIC.facingLeft) {
        entity->animCurFrame = D_us_8018285C[D_us_801D0874];
    } else {
        entity->animCurFrame = D_us_80182848[D_us_801D0874];
    }
    entity->posX.val = RIC.posX.val;
    entity->posY.val = RIC.posY.val;
}

extern s16 D_us_80182870[];
// same as `ric` `func_80167964` except `g_Ric`/`g_Player` reference and lookup
// table
void func_us_801C2688(Entity* entity) {
    if (g_Ric.unk46 == 0) {
        DestroyEntity(entity);
        return;
    }
    if (entity->step == 0) {
        entity->flags = FLAG_UNK_10000000 | FLAG_POS_CAMERA_LOCKED;
    }
    if (!(entity->params & 0xFF00)) {
        g_Entities[D_us_80182870[entity->poseTimer]].palette = PAL_FLAG(0x240);
    }
    g_Entities[D_us_80182870[entity->poseTimer]].ext.player.unkA4 = 4;
    entity->poseTimer++;
    if (entity->poseTimer == 15) {
        DestroyEntity(entity);
    }
}

void func_us_801C277C(void) {}

void func_us_801C2784(void) {}
