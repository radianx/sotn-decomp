// SPDX-License-Identifier: AGPL-3.0-or-later
#ifdef NDEBUG
#undef NDEBUG
#endif
#include "video_layout.h"
#include "../../tools/psyz/psyz/src/texture_read.h"
#include <assert.h>
#include <stdio.h>

static void CheckConstantTexel(void) {
    PsyzRect texel;
    assert(!Psyz_ConstantTexel(NULL, 0, false, 0, &texel));
    for (int gouraud = 0; gouraud < 2; gouraud++) {
        for (int quad = 0; quad < 2; quad++) {
            u_long packet[12] = {0};
            int stride = gouraud ? 3 : 2;
            int vertices = quad ? 4 : 3;
            int len = 3 + (vertices - 1) * stride;
            packet[0] = quad ? 0x08000000 : 0;
            for (int i = 0; i < vertices; i++)
                packet[2 + i * stride] = (i << 16) | 0xF3E5;
            assert(
                !Psyz_ConstantTexel(packet, len - 1, gouraud, 0xFFFF, &texel));
            assert(Psyz_ConstantTexel(packet, len, gouraud, 0xFFFF, &texel));
            assert(texel.sx == 229 && texel.sy == 243);
            assert(texel.ex == 230 && texel.ey == 244);
            assert(
                Psyz_ConstantTexel(packet, len, gouraud, 0x1020C0C0, &texel));
            assert(texel.sx == 224 && texel.sy == 208);
            packet[2 + (vertices - 1) * stride] ^= 1;
            assert(!Psyz_ConstantTexel(packet, len, gouraud, 0xFFFF, &texel));
        }
    }
    puts("Constant texture reads respect packets and texture windows: PASS");
}

int main(void) {
    CheckConstantTexel();
    const PsyzSize sizes[] = {{1280, 720}, {1920, 1080}, {2560, 1440},
                              {1280, 960}, {1366, 768},  {3840, 2160}};
    for (unsigned i = 0; i < sizeof(sizes) / sizeof(*sizes); i++) {
        VideoLayoutIn input = {.display = sizes[i],
                               .fb = {256, 240},
                               .request = sizes[i],
                               .anchor = PSYZ_ANCHOR_CENTER,
                               .aspect = PSYZ_ASPECT_DISPLAY};
        VideoLayout layout;
        VideoLayout_Resolve(&input, &layout);
        assert(layout.present.sx >= 0 && layout.present.sy >= 0);
        assert(layout.present.ex <= sizes[i].w);
        assert(layout.present.ey <= sizes[i].h);
        assert(layout.present.ex > layout.present.sx);
        assert(layout.present.ey > layout.present.sy);
    }
    puts("Rounded widescreen canvases fit the display: PASS");
    return 0;
}
