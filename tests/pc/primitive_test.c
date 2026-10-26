// SPDX-License-Identifier: AGPL-3.0-or-later
#undef NDEBUG
#include <game.h>
#include <assert.h>
#include <string.h>

int main(void) {
    Primitive prim = {0};
    DR_ENV env = {0};

    PRIM_DR_ENV(&prim) = &env;
    prim.x1 = 123;
    prim.y1 = -456;
    prim.r1 = prim.g1 = prim.b1 = 255;
    assert(PRIM_DR_ENV(&prim) == &env);
    assert(prim.x1 == 123 && prim.y1 == -456);
    memset(&prim, 0, sizeof(prim));
    assert(PRIM_DR_ENV(&prim) == NULL);
    return 0;
}
