// SPDX-License-Identifier: AGPL-3.0-or-later
#include <game.h>
#include "../pc.h"

extern u8 cutscene_script[0x243];
extern u8 gfx_A928[0xD80];
extern u8 gfx_B6A8[0xD80];

void InitBo5CutscenePc(void) {
    static const CutsceneSymbolRange symbols[] = {
        {cutscene_script, 0x80181D5C, sizeof(cutscene_script)},
        {gfx_A928, 0x8018A928, sizeof(gfx_A928)},
        {gfx_B6A8, 0x8018B6A8, sizeof(gfx_B6A8)},
    };
    CutscenePcAlloc(symbols, LEN(symbols));
}
