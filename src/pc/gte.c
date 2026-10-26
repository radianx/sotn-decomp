// SPDX-License-Identifier: AGPL-3.0-or-later
#include "gte.h"
#include <stdint.h>

MATRIX* PcCompMatrix(MATRIX* first, MATRIX* second, MATRIX* result) {
    MATRIX composed = *first;
    MulMatrix(&composed, second);
    SetRotMatrix(first);
    // The retail SDK transforms the low 16 bits of each translation component.
    Psyz_GteDataWrite(
        0, (uint16_t)second->t[0] | ((uint32_t)(uint16_t)second->t[1] << 16));
    Psyz_GteDataWrite(1, (uint16_t)second->t[2]);
    Psyz_GteCommand(0x486012);
    for (int i = 0; i < 3; i++) {
        composed.t[i] =
            (int32_t)(Psyz_GteDataRead(25 + i) + (uint32_t)first->t[i]);
    }
    *result = composed;
    return result;
}

MATRIX* PcSetMulMatrix(MATRIX* first, MATRIX* second) {
    MATRIX composed = *first;
    MulMatrix(&composed, second);
    SetRotMatrix(&composed);
    return first;
}
