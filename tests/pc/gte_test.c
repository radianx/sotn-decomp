// SPDX-License-Identifier: AGPL-3.0-or-later
#undef NDEBUG
#include "gte.h"
#include <assert.h>
#include <string.h>

int main(void) {
    MATRIX first = {{{4096, 0, 0}, {0, 4096, 0}, {0, 0, 4096}},
                    {100, -200, 300}};
    MATRIX second = {{{0, -4096, 0}, {4096, 0, 0}, {0, 0, 4096}},
                     {10, 20, -30}};
    MATRIX result;
    MATRIX savedFirst = first;
    MATRIX savedSecond = second;

    assert(PcCompMatrix(&first, &second, &result) == &result);
    assert(memcmp(result.m, second.m, sizeof(result.m)) == 0);
    assert(result.t[0] == 110 && result.t[1] == -180 && result.t[2] == 270);
    assert(memcmp(&first, &savedFirst, sizeof(first)) == 0);
    assert(memcmp(&second, &savedSecond, sizeof(second)) == 0);
    assert(PcSetMulMatrix(&first, &second) == &first);
    assert(memcmp(&first, &savedFirst, sizeof(first)) == 0);
    assert(memcmp(&second, &savedSecond, sizeof(second)) == 0);
    assert(Psyz_GteCtrlRead(0) == 0xF0000000U);
    assert(Psyz_GteCtrlRead(1) == 0x10000000U);

    second.t[0] = 0x10001;
    second.t[1] = 0xFFFF;
    PcCompMatrix(&first, &second, &first);
    assert(first.t[0] == 101 && first.t[1] == -201 && first.t[2] == 270);
    int depth;
    Psyz_GteDataWrite(8, 0x1234);
    gte_stdp(&depth);
    assert(depth == 0x1234);
    return 0;
}
