// SPDX-License-Identifier: AGPL-3.0-or-later
// Native definitions for tables retained as PS1 assembly data.

static u16 s_PcData_8017AB3C[];
static u16 s_PcData_8017AB64[];
static u16 s_PcData_8017AB8C[];
static u16 s_PcData_8017AB9C[];
static u16 s_PcData_8017ABAC[];
static u16* s_PcData_8017AC20[];
static s8 s_PcData_8017ABBC[];
WeaponAnimation D_EB000_8017AC3C[];
static u16 s_PcData_8017AA9C[];
u16* g_WeaponCluts[];

static u16 s_PcData_8017AB3C[] = {
    513,  1026, 1027, 1540, 2053, 2566, 1031, 1032, 5137,  5138,
    5651, 5652, 5653, 6166, 6167, 6168, 6169, 6170, 65535, 0,
};

static u16 s_PcData_8017AB64[] = {
    3081, 3594, 3595, 4108, 4621, 3598, 3599, 3600, 6683,  6684,
    7197, 7710, 8223, 6176, 6177, 6178, 6179, 6180, 65535, 0,
};

static u16 s_PcData_8017AB8C[] = {
    8741, 8742, 9255, 9256, 9257, 6186, 6187, 65535,
};

static u16 s_PcData_8017AB9C[] = {
    9772, 9773, 10286, 10287, 10800, 6193, 6198, 65535,
};

static u16 s_PcData_8017ABAC[] = {
    9772, 11314, 11827, 12340, 6197, 6198, 65535, 0,
};

static u16* s_PcData_8017AC20[] = {
    s_PcData_8017AB3C, s_PcData_8017AB3C, s_PcData_8017AB64, s_PcData_8017AB64,
    s_PcData_8017AB8C, s_PcData_8017AB9C, s_PcData_8017ABAC,
};

static s8 s_PcData_8017ABBC[] = {
    0,   0,   0,   0,   13,  -13, 10,  7,   16, -12, 13,  8,   29, -17, 11,
    7,   22,  -11, 20,  5,   17,  -11, 15,  5,  8,   6,   8,   8,  10,  5,
    13,  8,   21,  1,   12,  8,   15,  7,   20, 5,   -5,  -20, 4,  4,   21,
    -13, 22,  4,   -32, -31, 0,   0,   -12, -1, 4,   4,   8,   11, 15,  7,
    15,  19,  18,  7,   11,  17,  15,  4,   -7, -22, 4,   4,   21, -15, 21,
    6,   -18, -24, 4,   4,   13,  -15, 24,  7,  14,  -12, 19,  3,  15,  -2,
    18,  12,  24,  4,   15,  11,  12,  1,   15, 4,
};

WeaponAnimation D_EB000_8017AC3C[] = {
    {s_PcData_8017AC20, s_PcData_8017ABBC, 0, 1600, 139, 4, 0},
};

static u16 s_PcData_8017AA9C[] = {
#include "gen/pc_w_033_clut_8017AA9C.h"
};

u16* g_WeaponCluts[] = {
    s_PcData_8017AA9C,
    s_PcData_8017AA9C,
};

s32 g_HandId = HAND_ID;
