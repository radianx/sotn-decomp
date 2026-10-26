// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rbo2.h"

void CutsceneCameraPan(s16 arg0) {
    s16 target = arg0;
    s16 delta;

    delta = target - g_unkGraphicsStruct.unk14;

    if (delta > 1) { // pan left
        // Appears to be Alucard's X coordinates in screen space
        g_unkGraphicsStruct.unk14++;
    } else if (delta < -1) { // pan right
        g_unkGraphicsStruct.unk14--;
    } else {
        g_unkGraphicsStruct.unk14 = target;
    }
}

bool func_us_801A8FC0_from_bo6(void) {
    if (g_Player.status & PLAYER_STATUS_TRANSFORM) {
        g_Player.padSim = PAD_NONE;
        if (g_Timer & 1) {
            if (g_Player.status & PLAYER_STATUS_BAT_FORM) {
                g_Player.padSim = PAD_R1;
            } else if (g_Player.status & PLAYER_STATUS_MIST_FORM) {
                g_Player.padSim = PAD_L1;
            } else if (g_Player.status & PLAYER_STATUS_WOLF_FORM) {
                g_Player.padSim = PAD_R2;
            }
        }
        return true;
    }
    return false;
}
