// SPDX-License-Identifier: AGPL-3.0-or-later
#include <game.h>
#include "../pc.h"

extern u8 D_us_80181878[0x118];
extern u8 gfx_D224[0xD80];
extern u8 gfx_DFA4[0xD80];

void InitRbo2CutscenePc(void) {
    static const CutsceneSymbolRange symbols[] = {
        {D_us_80181878, 0x80181878, sizeof(D_us_80181878)},
        {gfx_D224, 0x8018D224, sizeof(gfx_D224)},
        {gfx_DFA4, 0x8018DFA4, sizeof(gfx_DFA4)},
    };
    CutscenePcAlloc(symbols, LEN(symbols));
}
