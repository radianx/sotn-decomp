// SPDX-License-Identifier: AGPL-3.0-or-later
#undef NDEBUG
#include <assert.h>
#include <stdlib.h>

int main(void) {
    assert(rand() == 16838);
    assert(rand() == 5758);
    assert(rand() == 10113);
    srand(1);
    assert(rand() == 16838);
    srand(0);
    assert(rand() == 0);
    assert(rand() == 21468);
    return 0;
}
