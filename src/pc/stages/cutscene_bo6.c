// SPDX-License-Identifier: AGPL-3.0-or-later
#include <game.h>
#include "../pc.h"

extern u8 D_us_8019A0D0[0x211];
extern u8 D_us_8019A2E1[0x1A];
extern u8 D_us_8019A2FB[0x1F9];
extern u8 gfx_1B528[0xD80];
extern u8 gfx_1C2A8[0xD80];
extern u8 gfx_1D028[0xD80];

void InitBo6CutscenePc(void) {
    static const CutsceneSymbolRange symbols[] = {
        {D_us_8019A0D0, 0x8019A0D0, sizeof(D_us_8019A0D0)},
        {D_us_8019A2E1, 0x8019A2E1, sizeof(D_us_8019A2E1)},
        {D_us_8019A2FB, 0x8019A2FB, sizeof(D_us_8019A2FB)},
        {gfx_1B528, 0x8019B528, sizeof(gfx_1B528)},
        {gfx_1C2A8, 0x8019C2A8, sizeof(gfx_1C2A8)},
        {gfx_1D028, 0x8019D028, sizeof(gfx_1D028)},
    };
    CutscenePcAlloc(symbols, LEN(symbols));
}
