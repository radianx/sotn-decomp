// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rno4.h"

void EntityWaterBox(Entity* self) {
    Entity* player;
    u16 collision;
    if (!self->step) {
        InitializeEntity(g_EInitInteractable);
        self->animSet = ANIMSET_OVL(1);
        self->animCurFrame = 6;
        if (g_CastleFlags[NO4_WATER_BLOCKED]) {
            self->posX.i.hi = 0x720 - g_Tilemap.scrollX.i.hi;
        } else {
            self->posX.i.hi = 0x760 - g_Tilemap.scrollX.i.hi;
        }
    }

    player = &PLAYER;
    collision = GetPlayerCollisionWith(self, 0x10, 0x11, 5);
    if ((collision & 1) && (g_Player.vram_flag & TOUCHING_GROUND)) {
        if (self->posX.i.hi > player->posX.i.hi) {
            if ((g_pads[0].pressed & PAD_RIGHT) && (PLAYER.step == 1)) {
                if (self->ext.timer.t) {
                    self->ext.timer.t--;
                    return;
                }
                if (self->posX.i.hi + g_Tilemap.scrollX.i.hi < 0x7A0) {
                    self->posX.i.hi++;
                    player->posX.i.hi++;
                }
                self->ext.timer.t = 3;
            }
        } else {
            if ((g_pads[0].pressed & PAD_LEFT) && (PLAYER.step == 1)) {
                if (self->ext.timer.t) {
                    self->ext.timer.t--;
                    return;
                }
                if (self->posX.i.hi + g_Tilemap.scrollX.i.hi > 0x720) {
                    self->posX.i.hi--;
                    player->posX.i.hi--;
                    if (self->posX.i.hi + g_Tilemap.scrollX.i.hi == 0x720) {
                        g_CastleFlags[NO4_WATER_BLOCKED] = 1;
                    }
                }
                self->ext.timer.t = 3;
            }
        }
    }
}

#ifdef VERSION_PSP
extern s32 E_ID(UNK_26);
extern s32 E_ID(UNK_27);
#endif
extern s16 D_us_801814D4;

void func_us_801C81C8(Entity* self) {
    Entity* child;

    if (!self->step) {
        InitializeEntity(g_EInitInteractable);
        self->animSet = -0x7FFE;
        self->palette = 0x44;
        self->drawFlags = ENTITY_MASK_R;
        self->posX.i.hi = (0x1EF - g_Tilemap.scrollX.i.hi);
        child = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (child) {
            CreateEntityFromCurrentEntity(E_ID(UNK_27), child);
            child->params = 1;
        }
        self->ext.et_801C81C8.unk80 = child;
        child = AllocEntity(child, &g_Entities[256]);
        if (child) {
            CreateEntityFromCurrentEntity(E_ID(UNK_26), child);
            child->params = 1;
        }
        self->ext.et_801C81C8.unk84 = child;
        self->ext.et_801C81C8.unk7C = 0;
    }
    AnimateEntity(&D_us_801814D4, self);
}

void EntityFloatingIcePlatform(Entity* self) {
    extern u16 g_FloatingIcePlatformHitbox[];
    u16* hitboxPtr;
    u16 collision;
    Entity* player;
    s16 prevPosY;
    s16 dx, dy;
    u16 hitboxIndex;

    player = &PLAYER;
    hitboxIndex = self->params;

    if (!self->step) {
        InitializeEntity(g_EInitCommon);
        self->animSet = ANIMSET_OVL(1);
        self->animCurFrame = hitboxIndex + 25;
        self->drawFlags = ENTITY_ROTATE;
        self->ext.floatingIcePlatform.baseY =
            self->posY.i.hi + g_Tilemap.scrollY.i.hi;
    }

    hitboxPtr = &g_FloatingIcePlatformHitbox[hitboxIndex * 2];

    prevPosY = self->posY.i.hi;
    self->posY.i.hi =
        self->ext.floatingIcePlatform.baseY - g_Tilemap.scrollY.i.hi +
        self->ext.floatingIcePlatform.bobOffset;
#ifdef VERSION_PSP
    collision = GetPlayerCollisionWith(self, hitboxPtr[0], hitboxPtr[1], 4);
#else
    collision = GetPlayerCollisionWith(self, *hitboxPtr++, *hitboxPtr, 4);
#endif
    self->posY.i.hi = prevPosY;
    self->ext.floatingIcePlatform.previousBobOffset =
        self->ext.floatingIcePlatform.bobOffset;

    dx = self->posX.i.hi - player->posX.i.hi;

    if (collision) {
        if (self->ext.floatingIcePlatform.bobOffset < 4) {
            self->ext.floatingIcePlatform.bobOffset++;
        }
    } else {
        if (self->ext.floatingIcePlatform.bobOffset) {
            self->ext.floatingIcePlatform.bobOffset--;
        }
    }

    dy = self->ext.floatingIcePlatform.bobOffset;
    if (dx < 0) {
        prevPosY = (dx * dy * -0x100) / 56;
    } else {
        prevPosY = (dx * dy * 0x100) / 56;
    }

    self->posY.i.hi = self->ext.floatingIcePlatform.baseY -
                      g_Tilemap.scrollY.i.hi + (dy - prevPosY / 256);

    if (collision) {
        dy = dy - self->ext.floatingIcePlatform.previousBobOffset;
        player->posY.i.hi += dy;
        g_unkGraphicsStruct.shoveX.i.hi += dy;
    }

    prevPosY = -prevPosY;
    if (collision || dy) {
        if (dx < 0) {
            self->rotate = ratan2(prevPosY, -0x3800);
            self->rotate = (self->rotate - 0x800) & 0xFFF;
            return;
        }
        self->rotate = ratan2(prevPosY, 0x3800);
    } else {
        self->rotate = 0;
    }
}

extern bool D_us_8018104C;
extern s16 D_us_801814E8[];

void func_us_801C4BD8_from_no4(Entity* self) {
    Entity* player;
    s16* dataPtr;
    s32 volume;

    if (!self->step) {
        InitializeEntity(g_EInitInteractable);
        self->animSet = 0;
    }

    player = &PLAYER;
    dataPtr = &D_us_801814E8[self->params * 4];

    volume = player->posX.i.hi + g_Tilemap.scrollX.i.hi - *dataPtr++;
    volume = (volume * *dataPtr++) / 0x1000;
    volume += *dataPtr++;

    if (volume < 0) {
        volume = 0;
    } else if (volume > 0x7F) {
        volume = 0x7F;
    }

    if (!volume) {
        if (D_us_8018104C) {
            D_us_8018104C = false;
            g_api.PlaySfx(SET_UNK_A6);
            return;
        }
    }
    if (D_us_8018104C) {
        g_api.SetVolumeCommand22_23(volume, *dataPtr++);
        return;
    }

    g_api.PlaySfxVolPan(SFX_WATERFALL_LOOP, volume, *dataPtr++);
    D_us_8018104C = true;
}

void func_us_801C8668(Entity* self) {
    s32 i;
    u16* tile;
    Tilemap* tilemap;

    tilemap = &g_Tilemap;

    if (!self->step) {
        InitializeEntity(g_EInitInteractable);
        self->animSet = 0;
        tile = tilemap->fg + 0x1052;

        for (i = 0; i < 5; ++i) {
            *tile = 0xac7;
            tile += 1;
        }
        *tile = 0x59D;
        tile = tilemap->fg + 0x1062;

        for (i = 0; i < 0xA; ++i) {
            *tile = 0xAC7;
            tile += 1;
        }
    }
}

void RNO4_Unused801C8704(void) {}

void func_us_801C870C(Entity* self) {
    s16 i;
    u16* tilePtr;

    if (self->params == 0) {
        tilePtr = g_Tilemap.fg + 0x143;
    } else {
        tilePtr = g_Tilemap.fg + 0x53;
    }

    for (i = 0; i < 0xA; ++i) {
        tilePtr[0] = 0;
        ++tilePtr;
    }
}

void RNO4_Unused801C8768(void) {}

void RNO4_Unused801C8770(void) {}

extern u16 D_us_80181508[];
extern u8 D_us_80181528[2][4];
extern s16 D_us_80181530[];
extern s16 D_us_80181548[];

void EntityBoatElevatorChains(Entity* self) {
    u32 primIndex;
    u32 scrollX;

    u32 scrollY;
    s16 cos;
    u8* ptr;
    s32 i;
    s16* ptrTwo;
    s16 sin;
    s16 xOffset;
    s16 yOffset;
    Primitive* prim;

    scrollX = g_Tilemap.scrollX.i.hi;
    scrollY = g_Tilemap.scrollY.i.hi;
    if (!self->step) {
        InitializeEntity(g_EInitInteractable);
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 13);
        if (primIndex != -1) {
            self->flags |= FLAG_HAS_PRIMS;
            self->primIndex = primIndex;
            prim = &g_PrimBuf[primIndex];

            i = 0;
            while (prim != NULL) {
                prim->tpage = 0xF;
                prim->clut = 0x5F;
                ptr = *D_us_80181528;
                ptr += D_us_80181508[i] * 4;
                prim->u0 = prim->u2 = *ptr++;
                prim->u1 = prim->u3 = *ptr++;
                prim->v0 = prim->v1 = *ptr++;
                prim->v2 = prim->v3 = *ptr;
                prim->priority = 0x80;
                prim->drawMode = DRAW_HIDE;
                prim = prim->next;
                i++;
            }
            self->rotate = ROT(45);
        } else {
            self->step = 0;
            return;
        }
    }

    if (self->ext.boatElevator_child.unk7C) {
        if (self->ext.boatElevator_child.unk7C < 0) {
            self->ext.boatElevator_child.unk7E++;
            self->rotate += ROT(1.40625);
        } else {
            self->ext.boatElevator_child.unk7E--;
            self->rotate -= ROT(1.40625);
        }
    }
    self->ext.boatElevator_child.unk7E &= 0xF;
    prim = &g_PrimBuf[self->primIndex];
    i = 0;
    while (prim != NULL) {
        if (i < 3) {
            ptrTwo = &D_us_80181530[(self->params * 6) + (i * 2)];
            xOffset = *ptrTwo++ - scrollX;
            yOffset = *ptrTwo - scrollY;
            if (self->params) {
                sin = (rsin(-self->rotate) * 0x1A) >> 0xC;
                cos = (rcos(-self->rotate) * 0x1A) >> 0xC;
            } else {
                sin = (rsin(self->rotate) * 0x1A) >> 0xC;
                cos = (rcos(self->rotate) * 0x1A) >> 0xC;
            }

            prim->x0 = xOffset - cos;
            prim->x1 = xOffset + sin;
            prim->x2 = xOffset - sin;
            prim->x3 = xOffset + cos;
            prim->y0 = yOffset - sin;
            prim->y1 = yOffset - cos;
            prim->y2 = yOffset + cos;
            prim->y3 = yOffset + sin;
            prim->drawMode = DRAW_UNK02;
            prim = prim->next;
        } else {
            ptrTwo = &D_us_80181548[(self->params * 3) * 10 + ((i - 3) * 3)];
            sin = *ptrTwo++;
            xOffset = *ptrTwo++ - scrollX;
            yOffset = *ptrTwo - scrollY;
            switch (sin) {
            case 0:
                prim->x0 = prim->x2 = xOffset - 4;
                prim->x1 = prim->x3 = xOffset + 4;
                yOffset += self->ext.boatElevator_child.unk7E;
                prim->y0 = prim->y1 = yOffset;
                prim->y2 = prim->y3 = yOffset + 0x60;
                break;
            case 1:
                prim->x0 = prim->x2 = xOffset - 4;
                prim->x1 = prim->x3 = xOffset + 4;
                yOffset -= self->ext.boatElevator_child.unk7E;
                prim->y0 = prim->y1 = yOffset;
                prim->y2 = prim->y3 = yOffset + 0x60;
                break;
            case 2:
                xOffset -= self->ext.boatElevator_child.unk7E;
                prim->x0 = prim->x1 = xOffset;
                prim->x2 = prim->x3 = xOffset + 0x60;
                prim->y1 = prim->y3 = yOffset - 4;
                prim->y0 = prim->y2 = yOffset + 4;
                break;
            case 3:
                xOffset += self->ext.boatElevator_child.unk7E;
                prim->x0 = prim->x1 = xOffset;
                prim->x2 = prim->x3 = xOffset + 0x60;
                prim->y1 = prim->y3 = yOffset - 4;
                prim->y0 = prim->y2 = yOffset + 4;
                break;
            }
            prim->drawMode = DRAW_UNK02;
            prim = prim->next;
        }
        i++;
    }
}

void RNO4_Unused801C8BD4(void) {}

void RNO4_Unused801C8BDC(void) {}

extern u16 D_us_801815C0[7][2];

void LoadFerrymanGateTiles(void) {
    u16* tileLayoutPtr;
    Tilemap* tileMap;
    s32 i;
    s16 offset;

    tileMap = &g_Tilemap;
    offset = 0xF89;
    tileLayoutPtr = *D_us_801815C0;

    for (i = 0; i < LEN(D_us_801815C0); i++) {
        tileMap->fg[offset] = *tileLayoutPtr++;
        offset++;
        tileMap->fg[offset] = *tileLayoutPtr++;
        offset += 0xCF;
    }
}

void func_us_801C8C54(Entity* self) {
    LoadFerrymanGateTiles();
    DestroyEntity(self);
}

extern s16 D_us_801815DC;
extern s16 D_us_801815E0[];
extern s16 D_us_80181190[];
extern s16 D_us_80181094[];

void func_us_801A071C_from_bo3(void) {
    s16* data;
    s16* tileRects;
    s16* surfaceLines;
    s16 value;

    data = D_us_801815E0;
    tileRects = D_us_80181190;
    surfaceLines = D_us_80181094;
    data += 2;
    tileRects += 0x6E;
    surfaceLines += 0x70;

    value = 0xD8 - D_us_801815DC;
    if (value < 0x18) {
        value = 0;
    }
    *data = value;
    *tileRects = value;
    *surfaceLines = value;
    data += 4;
    tileRects += 4;
    surfaceLines += 5;

    if (D_us_801815DC < 0xC0) {
        value = 0xF0;
    } else {
        value = 0x1A8 - D_us_801815DC;
    }
    *data = value;
    data += 4;
    *data = value;
    if (value > 0xE8) {
        value = 0xE8;
    }
    *surfaceLines = value;
    surfaceLines += 5;
    *surfaceLines = value;
    value++;
    *tileRects = value;
    tileRects += 4;
    *tileRects = value;
}

extern s16 D_us_801DCF54;

void func_us_801A07CC_from_bo3(Entity* self) {
    Entity* player;

    player = &PLAYER;
    D_us_801DCF54 = 0;
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
        if (D_us_801815DC) {
            if (g_CastleFlags[SCYLLA_DEFEATED]) {
                self->step = 5;
            } else {
                self->step = 3;
            }
        } else if (g_CastleFlags[SCYLLA_DEFEATED]) {
            self->step = 6;
        }
        break;

    case 1:
        if (player->posX.i.hi >= 0x38) {
            self->ext.timer.t = 0x10;
            self->step++;
        }
        break;

    case 2:
        if (!--self->ext.timer.t) {
            self->step++;
        }
        break;

    case 3:
        if (self->ext.timer.t) {
            --self->ext.timer.t;
        } else {
            self->ext.timer.t = 3;
            if (D_us_801815DC < 0xD0) {
                D_us_801815DC++;
                D_us_801DCF54 = -1;
            } else {
                self->ext.timer.t = 128;
                self->step++;
            }
        }
        func_us_801A071C_from_bo3();
        break;

    case 4:
        if (!--self->ext.timer.t) {
            g_CastleFlags[SCYLLA_DEFEATED] = 1;
            self->step++;
        }
        break;

    case 5:
        if (self->ext.timer.t) {
            --self->ext.timer.t;
        } else {
            self->ext.timer.t = 1;
            if (D_us_801815DC > 0) {
                D_us_801815DC--;
                D_us_801DCF54 = 1;
            } else {
                self->step++;
            }
        }
        func_us_801A071C_from_bo3();
        break;

    case 6:
        break;
    }
}

extern s16 D_us_801815F8[];
#define water_slow_zones D_us_801815F8
#define func_us_801C5518 func_us_801C5518_from_no4
#include "../water_slow_zone.h"
#undef func_us_801C5518
#undef water_slow_zones

extern u16 D_us_80181610[];

static void func_us_801C9048(s32 arg0) {
    s16 tilePos;
    s32 i;
    u16* tileLayoutPtr;

    Tilemap* tilemap;
    tilemap = &g_Tilemap;

    tilePos = 0x1E0;
    tileLayoutPtr = &(D_us_80181610[arg0 * 4]);

    for (i = 0; i < 4; ++i) {
        tilemap->fg[tilePos] = *(tileLayoutPtr++);
        tilePos += 0x50;
    }
}

void func_us_801C909C(Entity* self) {
    s16 screen_pos;
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitCommon);
        self->animSet = ANIMSET_OVL(1);
        self->animCurFrame = 0x25;
        if (D_us_801815DC) {
            func_us_801C9048(1);
            self->step = 0x4;
            break;
        }
        func_us_801C9048(0);
        self->posY.i.hi -= 0x40;
        break;

    case 1:
        if (D_us_801815DC) {
            self->step += 1;
            self->velocityY = FIX(4.0);
        }

        break;

    case 2:
        self->posX.i.hi -= 8;
        GetPlayerCollisionWith(self, 0x10, 0x20, 9);
        self->posX.i.hi += 8;
        MoveEntity();
        screen_pos = self->posY.i.hi + g_Tilemap.scrollY.i.hi;
        if (screen_pos >= 0x80) {
            g_api.PlaySfxVolPan(SFX_EXPLODE_B, 0x7F, -6);
            func_us_801C9048(1);
            self->velocityY = FIX(-1.0);
            self->step += 1;
        }
        break;

    case 3:
        self->velocityY += FIX(0.125);
        MoveEntity();
        screen_pos = self->posY.i.hi + g_Tilemap.scrollY.i.hi;
        if (screen_pos >= 0x80) {
            self->posY.i.hi = 0x80 - g_Tilemap.scrollY.i.hi;
            self->step = 6;
        }
        break;

    case 4:
        if (!D_us_801815DC) {
            self->step += 1;
            self->velocityY = FIX(-1.0);
        }
        break;

    case 5:
        self->posX.i.hi -= 8;
        GetPlayerCollisionWith(self, 0x10, 0x20, 0xB);
        self->posX.i.hi += 8;
        MoveEntity();
        screen_pos = self->posY.i.hi + g_Tilemap.scrollY.i.hi;
        if (screen_pos < 0x41) {
            func_us_801C9048(0);
            self->step += 1;
        }
        break;

    case 6:
        break;
    }
}

extern s32 g_ExplosionVariantVelocity[];
extern u8 g_ExplosionVariantFrames[];
extern u16 g_ExplosionVariantDurations[];

void EntityExplosionVariants(Entity* self) {
    if (!self->step) {
        self->velocityY =
            g_ExplosionVariantVelocity[self->ext.destructAnim.index];
        self->flags =
            FLAG_UNK_2000 | FLAG_KEEP_ALIVE_OFFCAMERA | FLAG_POS_CAMERA_LOCKED;
        self->palette = PAL_FLAG(PAL_UNK_195);
        self->animSet = ANIMSET_DRA(2);
        self->animCurFrame = g_ExplosionVariantFrames[self->params];
        self->blendMode = BLEND_TRANSP;
        self->step++;
        return;
    }

    self->posY.val -= self->velocityY;
    ++self->poseTimer;
    if ((self->poseTimer % 2) == 0) {
        self->animCurFrame++;
    }
    if (self->poseTimer > g_ExplosionVariantDurations[self->params]) {
        DestroyEntity(self);
    }
}

void EntityGreyPuff(Entity* self) {
    extern s16 g_GreyPuffScale[];
    extern s32 g_GreyPuffVelocity[];

    if (!self->step) {
        self->flags =
            FLAG_UNK_2000 | FLAG_KEEP_ALIVE_OFFCAMERA | FLAG_POS_CAMERA_LOCKED;
        self->palette = PAL_FLAG(PAL_UNK_195);
        self->animSet = ANIMSET_DRA(5);
        self->animCurFrame = 1;
        self->blendMode = BLEND_TRANSP;
        self->drawFlags = ENTITY_SCALEX | ENTITY_SCALEY;
        self->scaleX = g_GreyPuffScale[self->params];
        self->scaleY = self->scaleX;
        self->velocityY = g_GreyPuffVelocity[self->params];
        self->step++;
    } else {
        self->posY.val -= self->velocityY;
        self->poseTimer++;
        if ((self->poseTimer % 2) == 0) {
            self->animCurFrame++;
        }
        if (self->poseTimer > 36) {
            DestroyEntity(self);
        }
    }
}

void EntityIntenseExplosion(Entity* self) {
    if (!self->step) {
        InitializeEntity(g_EInitParticle);
        self->palette = PAL_FLAG(PAL_UNK_170);
        self->animSet = 5;
        self->animCurFrame = 1;
        self->blendMode = BLEND_ADD | BLEND_TRANSP;
        if (self->params & 0xF0) {
            self->palette = PAL_FLAG(PAL_UNK_195);
            self->blendMode = BLEND_TRANSP;
        }
        if (self->params & 0xFF00) {
            self->zPriority = (u16)((self->params & 0xFF00) >> 8);
        }
        self->zPriority += 8;
        return;
    }

    self->poseTimer++;
    self->posY.val -= FIX(0.25);

    if (!((u16)self->poseTimer & 1)) {
        self->animCurFrame++;
    }

    if (self->poseTimer >= 0x25) {
        DestroyEntity(self);
    }
}

void PlaySfxPositional(s16 sfxId) {
    s32 posX, posY;
    s16 sfxPan;
    s16 sfxVol;

    posX = g_CurrentEntity->posX.i.hi - 128;
    sfxPan = (abs(posX) - 32) >> 5;
    if (sfxPan > 8) {
        sfxPan = 8;
    } else if (sfxPan < 0) {
        sfxPan = 0;
    }
    if (posX < 0) {
        sfxPan = -sfxPan;
    }
    sfxVol = abs(posX) - 96;
    posY = abs(g_CurrentEntity->posY.i.hi - 128) - 112;
    if (posY > 0) {
        sfxVol += posY;
    }
    if (sfxVol < 0) {
        sfxVol = 0;
    }
    sfxVol = 127 - (sfxVol >> 1);
    if (sfxVol > 0) {
        g_api.PlaySfxVolPan(sfxId, sfxVol, sfxPan);
    }
}

void EntityBreakableCrystalFloor(Entity* self) {
    extern s16 g_BreakableCrystalFloorTiles[];
    Entity* newEntity;
    s16* tileLayoutPtr;
    s32 tilePos;
    s32 i;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
        self->hitboxWidth = 0x10;
        self->hitboxHeight = 0x10;
        self->hitboxState = 2;
        if (g_CastleFlags[RNO4_SECRET_CEILING_OPEN]) {
            i = 0x12;
        } else {
            i = 0;
        }
        tileLayoutPtr = &g_BreakableCrystalFloorTiles[i];
        tilePos = 0x2C;
        tilePos = 0x2C;
        (&g_BgLayers[0].layout[tilePos])[-1] = 0x3FE;
        (&g_BgLayers[0].layout[tilePos])[-2] = 0x3FF;
        (&g_BgLayers[0].layout[tilePos])[-17] = 0x401;
        (&g_BgLayers[0].layout[tilePos])[-18] = 0x402;
        for (i = 0; i < 2; i++, tileLayoutPtr += 3) {
            (&g_Tilemap.fg[tilePos])[0] = tileLayoutPtr[0];
            (&g_Tilemap.fg[tilePos])[-1] = tileLayoutPtr[1];
            (&g_Tilemap.fg[tilePos])[-2] = tileLayoutPtr[2];
            tilePos -= 0x10;
        }
        if (g_CastleFlags[RNO4_SECRET_CEILING_OPEN]) {
            DestroyEntity(self);
            return;
        }
        /* fallthrough */
    case 1:
        if (self->hitFlags) {
            PlaySfxPositional(SFX_WALL_DEBRIS_B);
            self->step++;
        }
        break;
    case 2:
        self->ext.breakable.breakCount++;
        tileLayoutPtr =
            &g_BreakableCrystalFloorTiles[self->ext.breakable.breakCount * 6];
        tilePos = 0x2C;
        for (i = 0; i < 2; i++, tileLayoutPtr += 3) {
            (&g_Tilemap.fg[tilePos])[0] = tileLayoutPtr[0];
            (&g_Tilemap.fg[tilePos])[-1] = tileLayoutPtr[1];
            (&g_Tilemap.fg[tilePos])[-2] = tileLayoutPtr[2];
            tilePos -= 0x10;
        }
        newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (newEntity != NULL) {
            CreateEntityFromEntity(E_EXPLOSION, self, newEntity);
            newEntity->params = 0x11;
        }
        self->ext.breakable.resetTimer = 0x20;
        self->step += 1;
        if (self->ext.breakable.breakCount == 3) {
            newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (newEntity != NULL) {
                CreateEntityFromEntity(E_EXPLOSION, self, newEntity);
                newEntity->params = 0x13;
            }
            g_CastleFlags[RNO4_SECRET_CEILING_OPEN] = 1;
            g_api.RevealSecretPassageAtPlayerPositionOnMap(0xCA);
            DestroyEntity(self);
            return;
        }
        break;
    case 3:
        if (!--self->ext.breakable.resetTimer) {
            self->step = 1;
            return;
        }
        break;
    }
}

extern s16 D_us_801816EC[];

void EntityBreakableWall(Entity* self) {
    Entity* newEntity;
    s32 i;
    s32 tilePos;
    s16* tileLayoutPtr;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
        self->hitboxWidth = 8;
        self->hitboxHeight = 0x20;
        self->hitboxState = 2;
        if (g_CastleFlags[RNO4_SECRET_WALL_OPEN]) {
            i = 0x18;
        } else {
            i = 0;
        }
        tileLayoutPtr = &D_us_801816EC[i];
        tilePos = 0x9F;

        for (i = 0; i < 4; tilePos -= 0x10, i++, tileLayoutPtr += 2) {
            (&g_Tilemap.fg[tilePos])[0] = tileLayoutPtr[0];
        }

        if (g_CastleFlags[RNO4_SECRET_WALL_OPEN]) {
            DestroyEntity(self);
            break;
        }
        // fallthrough
    case 1:
        if (self->hitFlags) {
            PlaySfxPositional(SFX_WALL_DEBRIS_B);
            self->step++;
        }
        break;
    case 2:
        self->ext.breakable.breakCount++;
        tileLayoutPtr = &D_us_801816EC[self->ext.breakable.breakCount * 8];
        tilePos = 0x9F;

        for (i = 0; i < 4; tilePos -= 0x10, i++, tileLayoutPtr += 2) {
            (&g_Tilemap.fg[tilePos])[0] = tileLayoutPtr[0];
        }
        newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (newEntity != NULL) {
            CreateEntityFromEntity(E_EXPLOSION, self, newEntity);
            newEntity->params = 0x11;
        }
        self->ext.breakable.resetTimer = 0x14;
        self->step++;
        if (self->ext.breakable.breakCount == 3) {
            for (i = 0; i < 0x10; i++) {
                newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (newEntity != NULL) {
                    CreateEntityFromEntity(
                        E_ID(BREAKABLE_WALL_DEBRIS), self, newEntity);
                    newEntity->posX.i.hi += 4 - (Random() & 0xF);
                    newEntity->posY.i.hi += 0x1F - (i * 4);
                    newEntity->velocityX = FIX(0.5) - (Random() << 8);
                    newEntity->params = 1;
                }
            }

            g_api.PlaySfx(SFX_WALL_DEBRIS_B);
            g_CastleFlags[RNO4_SECRET_WALL_OPEN] = 1;
            g_api.RevealSecretPassageAtPlayerPositionOnMap(
                RNO4_SECRET_WALL_OPEN);
            DestroyEntity(self);
        }
        break;
    case 3:
        if (!--self->ext.breakable.resetTimer) {
            self->step = 1;
        }
        break;
    }
}
