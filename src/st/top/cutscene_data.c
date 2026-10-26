// SPDX-License-Identifier: AGPL-3.0-or-later
#include "top.h"
#include <cutscene.h>

u8 cutscene_data[] = {
#include <gen/cutscene_data.h>
#include <gen/cutscene_events.h>
};

#ifdef VERSION_PC
#include "../../pc/pc.h"
extern u8 gfx_portrait_alucard[];
extern u8 gfx_portrait_maria[];
extern u8 gfx_portrait_richter[];

void InitTopCutscenePc(void) {
    static const CutsceneSymbolRange symbols[] = {
        {cutscene_data, 0x80182C08, sizeof(cutscene_data)},
        {gfx_portrait_alucard, 0x80187934, 0xD80},
        {gfx_portrait_maria, 0x801886B4, 0xD80},
        {gfx_portrait_richter, 0x80189434, 0xD80},
    };
    CutscenePcAlloc(symbols, LEN(symbols));
}
#endif
