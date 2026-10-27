// SPDX-License-Identifier: AGPL-3.0-or-later
#ifdef NDEBUG
#undef NDEBUG
#endif
#include "video_layout.h"
#include <assert.h>
#include <stdio.h>

int main(void) {
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
