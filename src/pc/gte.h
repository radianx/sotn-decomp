// SPDX-License-Identifier: AGPL-3.0-or-later
#ifndef PC_GTE_H
#define PC_GTE_H
#include <libgte.h>
#include <psyz/gte.h>

MATRIX* PcCompMatrix(MATRIX* first, MATRIX* second, MATRIX* result);
MATRIX* PcSetMulMatrix(MATRIX* first, MATRIX* second);

#define CompMatrix PcCompMatrix
#define SetMulMatrix PcSetMulMatrix
#define gte_stdp(value) (*(value) = (int)Psyz_GteDataRead(8))
#endif
