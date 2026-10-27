// SPDX-License-Identifier: AGPL-3.0-or-later
#include <game.h>
#include "upgrades.h"
#include <psyz.h>

static int s_Left, s_Right = 256, s_Top, s_Bottom = 240;
static bool s_CameraNeedsSync;

int PcViewMargin(void) { return -s_Left; }
int PcViewLeft(void) { return s_Left; }
int PcViewRight(void) { return s_Right; }
int PcViewTop(void) { return s_Top; }
int PcViewBottom(void) { return s_Bottom; }

static int CopyDrawArea(const u_long* words, int available, void* userdata) {
    if (available < 4)
        return -1;
    int x = (short)words[1], y = (short)(words[1] >> 16);
    int w = (unsigned short)words[3], h = words[3] >> 16;
    if (Psyz_VideoCopyDrawArea((PsyzRect){x, y, x + w, y + h}, (short)words[2],
                               (short)(words[2] >> 16)))
        WARNF("Could not capture the current draw area");
    return 4;
}

void PcUpdateViewport(void) {
    Psyz_GpuRegisterCommandHandler(
        PC_COPY_DRAW_AREA_OPCODE, CopyDrawArea, NULL);
    int previousLeft = s_Left;
    DISPENV display;
    GetDispEnv(&display);
    bool active = g_PcSettings.widescreen && g_GameState == Game_Play &&
                  g_GameStep == Play_Default && display.disp.w == 256 &&
                  display.disp.h == 240;
    if (active) {
        Psyz_VideoSetAnchor(PSYZ_ANCHOR_CENTER);
        // The game's visible rows are 20..226; omit their surrounding border.
        Psyz_VideoSetResolution((PsyzSize){207 * 16 / 9, 240});
        Psyz_VideoSetVerticalCrop(20, 207);
        PsyzRect area = Psyz_VideoGetDrawArea();
        s_Left = area.sx;
        s_Right = area.ex;
        s_Top = area.sy;
        s_Bottom = area.ey;
    } else {
        Psyz_VideoSetResolution(PSYZ_DEFAULT_RESOLUTION);
        Psyz_VideoSetVerticalCrop(0, 0);
        s_Left = s_Top = 0;
        s_Right = 256;
        s_Bottom = 240;
    }
    s_CameraNeedsSync |= previousLeft != s_Left;
}

void PcClampCamera(void) {
    if ((!PcViewMargin() && !s_CameraNeedsSync) ||
        g_GameEngineStep != Engine_Normal)
        return;
    int minimum = g_Tilemap.x - s_Left;
    int maximum = g_Tilemap.width - s_Right;
    int old = g_Tilemap.scrollX.i.hi;
    int scroll = old;
    if (!g_CutsceneHasControl) {
        if (minimum > maximum)
            scroll = (minimum + maximum) / 2;
        else if (scroll < minimum)
            scroll = minimum;
        else if (scroll > maximum)
            scroll = maximum;
    }
    g_Tilemap.scrollX.i.hi = scroll;
    // The original edge clamp changes scroll without moving the player.
    PLAYER.posX.i.hi = g_PlayerX - scroll;
    s_CameraNeedsSync = false;
}

void PcAdjustPrimitive(Primitive* prim) {
    if (!PcViewMargin())
        return;
    int kind = prim->type & 0xF;
    if (kind != PRIM_GT4 && kind != PRIM_G4)
        return;
    if (prim->x0 >= -1 && prim->x0 <= 0 && prim->x2 >= -1 && prim->x2 <= 0 &&
        prim->x1 >= 255 && prim->x1 <= 256 && prim->x3 >= 255 &&
        prim->x3 <= 256 && prim->y0 <= 20 && prim->y1 <= 20 &&
        prim->y2 >= 224 && prim->y3 >= 224) {
        prim->x0 = prim->x2 = s_Left;
        prim->x1 = prim->x3 = s_Right;
        if (prim->y0 <= 0)
            prim->y0 = prim->y1 = s_Top;
        if (prim->y2 >= 239)
            prim->y2 = prim->y3 = s_Bottom;
    } else if (prim->priority >= 0x1EF && prim->priority <= 0x1F5 &&
               (prim->y0 < 48 || (prim->priority == 0x1EF && prim->x0 < 64))) {
        int delta = prim->x0 < 128 ? s_Left : s_Right - 256;
        prim->x0 += delta;
        prim->x1 += delta;
        prim->x2 += delta;
        prim->x3 += delta;
    }
}
