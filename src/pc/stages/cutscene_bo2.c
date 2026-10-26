// SPDX-License-Identifier: AGPL-3.0-or-later
#include <game.h>
#include "../pc.h"

extern u8 D_us_80181CCC[0xF9];
extern u8 D_us_80181DC5[0x87];
extern u8 gfx_11E14[0xD80];
extern u8 gfx_12B94[0xD80];

void InitBo2CutscenePc(void) {
    static const CutsceneSymbolRange symbols[] = {
        {D_us_80181CCC, 0x80181CCC, sizeof(D_us_80181CCC)},
        {D_us_80181DC5, 0x80181DC5, sizeof(D_us_80181DC5)},
        {gfx_11E14, 0x80191E14, sizeof(gfx_11E14)},
        {gfx_12B94, 0x80192B94, sizeof(gfx_12B94)},
    };
    CutscenePcAlloc(symbols, LEN(symbols));
}
