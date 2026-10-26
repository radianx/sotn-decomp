// SPDX-License-Identifier: AGPL-3.0-or-later
#include <game.h>
#include "../pc.h"

extern u8 cutscene_data[0x1CB];
extern u8 gfx_15F0[0xD80];
extern u8 gfx_2370[0xD80];

void InitMarCutscenePc(void) {
    static const CutsceneSymbolRange symbols[] = {
        {cutscene_data, 0x80181424, sizeof(cutscene_data)},
        {gfx_15F0, 0x801815F0, sizeof(gfx_15F0)},
        {gfx_2370, 0x80182370, sizeof(gfx_2370)},
    };
    CutscenePcAlloc(symbols, LEN(symbols));
}
