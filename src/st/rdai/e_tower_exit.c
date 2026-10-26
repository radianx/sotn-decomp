// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rdai.h"

extern EInit g_EInitCommon;

void func_us_801B1C34(Entity* self) {
    s16 params = self->params;
    s16 playerX;
    s16 offsetY;
    s16 distanceY;

    FntPrint("set:%04x\n", params);
    FntPrint("sx:%04x\n", g_Tilemap.left);
    FntPrint("ex:%04x\n", g_Tilemap.right);
    playerX = g_PlayerX;
    playerX -= g_Player.unk7C - PLAYER.posX.i.hi;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitCommon);
        self->animCurFrame = 1;
        self->animSet = 0;
        self->zPriority = 0xB0;
        break;
    case 1:
        offsetY = self->posY.i.hi - PLAYER.posY.i.hi;
        distanceY = abs(offsetY);
        if (distanceY < 48) {
            if (g_Player.status & PLAYER_STATUS_DEAD) {
                PLAYER.velocityX = 0;
                return;
            }
            switch (params) {
            case 0:
                if (playerX < 384 && g_PlayerX < 384) {
                    g_Tilemap.x = 384;
                    g_Tilemap.left++;
                    self->step++;
                }
                break;
            case 1:
                if (playerX > 640 && g_PlayerX > 640) {
                    g_Tilemap.width = 640;
                    g_Tilemap.right--;
                    self->step++;
                }
                break;
            case 3:
                if (playerX > 768 && g_PlayerX > 768) {
                    g_Tilemap.width = 768;
                    g_Tilemap.right--;
                    self->step++;
                }
                break;
            case 5:
                if (playerX > 1152 && g_PlayerX > 1152) {
                    g_Tilemap.width = 1152;
                    self->step++;
                }
                break;
            case 6:
                if (playerX < 128 && g_PlayerX < 128) {
                    g_Tilemap.x = 128;
                    self->step++;
                }
                break;
            case 7:
                if (playerX < 128 && g_PlayerX < 128) {
                    g_Tilemap.x = 128;
                    self->step++;
                }
                break;
            case 8:
                if (playerX > 640 && g_PlayerX > 640) {
                    g_Tilemap.width = 640;
                    self->step++;
                }
                break;
            case 9:
                if (playerX < 128 && g_PlayerX < 128) {
                    g_Tilemap.x = 128;
                    self->step++;
                }
                break;
            case 10:
                if (playerX > 640 && g_PlayerX > 640) {
                    g_Tilemap.width = 640;
                    g_Tilemap.right--;
                    self->step++;
                }
                break;
            case 11:
                if (playerX < 384 && g_PlayerX < 384) {
                    g_Tilemap.x = 384;
                    g_Tilemap.left++;
                    self->step++;
                }
                break;
            case 12:
                if (playerX > 640 && g_PlayerX > 640) {
                    g_Tilemap.width = 640;
                    g_Tilemap.right--;
                    self->step++;
                }
                break;
            case 2:
            case 4:
            case 13:
            case 14:
                if (playerX < 256 && g_PlayerX < 256) {
                    g_Tilemap.x = 256;
                    g_Tilemap.left++;
                    self->step++;
                }
                break;
            }
        }
        break;
    }
}
