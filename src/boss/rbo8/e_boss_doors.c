// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rbo8.h"

extern s32 D_us_801817B8;
extern EInit D_us_80180A68;
extern u16 D_us_801817A8[];
extern u16 D_us_801817B0[];

void func_us_80199A58(Entity* self) {
    Collider collider;
    s32 i;
    s32 tilePos;
    Entity* entity;
    s16 posX;
    s16 posY;

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_80180A68);
        self->animCurFrame = self->params + 0x10;
        if (self->params) {
            self->posX.i.hi = 7 - g_Tilemap.scrollX.i.hi;
            self->posY.i.hi = 0x141 - g_Tilemap.scrollY.i.hi;
        } else {
            self->posX.i.hi = 0x1F7 - g_Tilemap.scrollX.i.hi;
            self->posY.i.hi = 0x41 - g_Tilemap.scrollY.i.hi;
        }
        tilePos = 0x13F;
        if (self->params) {
            tilePos = 0x320;
        }
        for (i = 0; i < 4; i++) {
            g_Tilemap.fg[tilePos] = D_us_801817B0[i];
            tilePos -= 0x20;
        }
        self->zPriority = 0x5F;
        // fallthrough
    case 1:
        if (D_us_801817B8) {
            self->step++;
        }
        break;
    case 2:
        self->posY.val += self->velocityY;
        self->velocityY += FIX(0.5);
        posX = self->posX.i.hi;
        posY = self->posY.i.hi + 0x20;
        g_api.CheckCollision(posX, posY, &collider, 0);
        if (collider.effects) {
            self->posY.i.hi += collider.unk18;
            self->velocityY = -self->velocityY;
            self->velocityY /= 4;
            if (!(D_us_801817B8 & 0x10)) {
                D_us_801817B8 |= 0x10;
            }
            entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (entity != NULL) {
                CreateEntityFromEntity(E_INTENSE_EXPLOSION, self, entity);
                entity->posX.i.hi += ((Random() & 7) * 2) - 8;
                entity->posY.i.hi += 0x20;
                entity->params = 16;
            }
            if (self->velocityY > FIX(-0.125)) {
                self->step++;
            }
        }
        break;
    case 3:
        tilePos = 0x13F;
        if (self->params) {
            tilePos = 0x320;
        }
        for (i = 0; i < 4; i++) {
            g_Tilemap.fg[tilePos] = D_us_801817A8[i];
            tilePos -= 0x20;
        }
        self->step++;
        break;
    case 4:
        if (!D_us_801817B8) {
            self->step++;
        }
        break;
    case 5:
        tilePos = 0x13F;
        if (self->params) {
            tilePos = 0x320;
        }
        for (i = 0; i < 4; i++) {
            g_Tilemap.fg[tilePos] = D_us_801817B0[i];
            tilePos -= 0x20;
        }
        self->step++;
        break;
    case 6:
        self->flags |= FLAG_DESTROY_IF_OUT_OF_CAMERA;
        posY = self->posY.i.hi;
        self->posY.i.hi = posY - 1;
        break;
    }
}
