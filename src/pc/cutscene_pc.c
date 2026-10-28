// SPDX-License-Identifier: AGPL-3.0-or-later
#include <game.h>
#include "pc.h"
#include <stdlib.h>

static const CutsceneSymbolRange* _symbols = NULL;
static int _symbolCount = 0;
static u8** s_Replacements;

// normalize 0x8018xxxx ptr to 0x0018xxxx
#define NORMALIZE_PSX_ADDR(x) ((x) & 0x0FFFFFFF)

void CutscenePcAlloc(const CutsceneSymbolRange* symbols, int count) {
    int i;
    for (i = 0; i < _symbolCount; i++)
        free(s_Replacements ? s_Replacements[i] : NULL);
    free(s_Replacements);
    s_Replacements = NULL;

    if (!symbols || count <= 0) {
        _symbols = NULL;
        _symbolCount = 0;
        return;
    }

    _symbols = symbols;
    _symbolCount = count;
    s_Replacements = calloc(count, sizeof(*s_Replacements));
    if (s_Replacements)
        for (i = 0; i < count; i++) {
            char path[80];
            snprintf(path, sizeof(path), "scripts/%02X/%08X.bin", g_StageId,
                     symbols[i].psxAddr);
            FILE* f = PcOpenPackFile(path);
            if (!f)
                continue;
            // shortcut: fixed symbol spans; longer translations need rebuilt
            // maps.
            if (symbols[i].size > 1024 * 1024) {
                fclose(f);
                continue;
            }
            u8* replacement = malloc(symbols[i].size);
            if (replacement &&
                fread(replacement, 1, symbols[i].size, f) == symbols[i].size &&
                fgetc(f) == EOF && !ferror(f)) {
                s_Replacements[i] = replacement;
            } else {
                ERRORF("Invalid replacement script size: %s", path);
                free(replacement);
            }
            fclose(f);
        }
    for (i = 1; i < count; i++) {
        // catch overlapping symbols
        u32 prevEnd =
            NORMALIZE_PSX_ADDR(symbols[i - 1].psxAddr) + symbols[i - 1].size;
        if (NORMALIZE_PSX_ADDR(symbols[i].psxAddr) < prevEnd) {
            ERRORF("cutscene symbol at 0x%08x overlaps the previous entry "
                   "ending at 0x%08x; a registered size is wrong",
                   symbols[i].psxAddr, prevEnd);
        }
    }
}

u8* CutsceneAddrToPc(u32 psxAddr) {
    u32 addr = NORMALIZE_PSX_ADDR(psxAddr);
    for (int i = 0; i < _symbolCount; i++) {
        u32 base = NORMALIZE_PSX_ADDR(_symbols[i].psxAddr);
        if (addr >= base && addr < base + _symbols[i].size) {
            return (s_Replacements && s_Replacements[i]
                        ? s_Replacements[i]
                        : (u8*)_symbols[i].pcAddr) +
                   (addr - base);
        }
    }
    ERRORF("address 0x%08x not found", psxAddr);
    return NULL;
}
