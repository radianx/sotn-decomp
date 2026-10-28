// SPDX-License-Identifier: AGPL-3.0-or-later
#ifdef NDEBUG
#undef NDEBUG
#endif
#include "upgrades.h"
#include <assert.h>
#include <stdio.h>
int main(void) {
    for (unsigned color = 0; color < 65536; color++) {
        assert(PcPaletteColor(color, 0) == color);
        for (int mode = 1; mode <= 3; mode++) {
            unsigned result = PcPaletteColor(color, mode);
            assert((result & 0x8000) == (color & 0x8000));
            if (!(color & 0x7FFF))
                assert(result == color);
            else
                assert(result & 0x7FFF);
            if (mode == 3) {
                assert((result & 31) == ((result >> 5) & 31));
                assert((result & 31) == ((result >> 10) & 31));
            }
        }
    }
    assert(PcPaletteColor(0x001F, 2) != PcPaletteColor(0x7C00, 2));
    puts("Palette toggles preserve original colors, transparency and mask "
         "bits: PASS");
    return 0;
}
