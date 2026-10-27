// SPDX-License-Identifier: AGPL-3.0-or-later
#include <game.h>
#include "upgrades.h"

unsigned short PcPaletteColor(unsigned short color, int mode) {
    if (!mode || !(color & 0x7FFF))
        return color;
    int r = color & 31, g = (color >> 5) & 31, b = (color >> 10) & 31;
    int light = (r * 3 + g * 6 + b + 5) / 10;
    if (mode == 1) {
        r = r < 16 ? r * 3 / 4 : 31 - (31 - r) * 3 / 4;
        g = g < 16 ? g * 3 / 4 : 31 - (31 - g) * 3 / 4;
        b = b < 16 ? b * 3 / 4 : 31 - (31 - b) * 3 / 4;
    } else if (mode == 2) {
        if (r >= b) {
            r = light;
            g = light * 3 / 4;
            b = light / 5;
        } else {
            r = light / 4;
            g = light * 3 / 4;
            b = light;
        }
    } else if (mode == 3) {
        r = g = b = light;
    }
    if (!(r | g | b))
        r = g = b = 1;
    return (color & 0x8000) | r | (g << 5) | (b << 10);
}

void PcUploadPalette(const void* data, int x, int y) {
    if (!g_PcSettings.palette) {
        LoadClut((u_long*)data, x, y);
        return;
    }
    u32 aligned[128];
    u16* filtered = (u16*)aligned;
    const u16* original = data;
    for (int i = 0; i < 256; i++) {
        filtered[i] = PcPaletteColor(original[i], g_PcSettings.palette);
    }
    LoadClut((u_long*)aligned, x, y);
}
