// SPDX-License-Identifier: AGPL-3.0-or-later
// Native definitions for tables retained as PS1 assembly data.

static u16 s_PcData_8017A7A4[];
static u16 s_PcData_8017A7B8[];
static u16 s_PcData_8017A7C8[];
static u16 s_PcData_8017A7D4[];
static u16* s_PcData_8017A8C0[];
static s8 s_PcData_8017A848[];
static u16 s_PcData_8017A7DC[];
static u16 s_PcData_8017A7F0[];
static u16 s_PcData_8017A804[];
static u16 s_PcData_8017A818[];
static u16 s_PcData_8017A828[];
static u16* s_PcData_8017A8DC[];
WeaponAnimation D_E4000_8017A8F8[];
static u16 s_PcData_8017A704[];
u16* g_WeaponCluts[];

static u16 s_PcData_8017A7A4[] = {
    513, 1026, 1539, 1541, 1539, 1026, 14852, 2054, 65535, 0,
};

static u16 s_PcData_8017A7B8[] = {
    2567, 3081, 3594, 3595, 3594, 3081, 14856, 65535,
};

static u16 s_PcData_8017A7C8[] = {
    1036, 4109, 4110, 4109, 1036, 65535,
};

static u16 s_PcData_8017A7D4[] = {
    4623,
    5136,
    4623,
    65535,
};

static u16* s_PcData_8017A8C0[] = {
    s_PcData_8017A7A4, s_PcData_8017A7A4, s_PcData_8017A7B8, s_PcData_8017A7B8,
    s_PcData_8017A7C8, s_PcData_8017A7D4, s_PcData_8017A7D4,
};

static s8 s_PcData_8017A848[] = {
    0,   0,   0,   0,   12,  -16, 8,   9,   18,  -15, 13,  5,   21,  -13, 22,
    5,   -32, -31, 0,   0,   7,   1,   9,   9,   13,  3,   12,  6,   14,  4,
    22,  5,   23,  -12, 23,  8,   7,   -9,  11,  9,   20,  3,   14,  13,  -5,
    -16, 5,   4,   19,  -14, 24,  5,   24,  -12, 13,  3,   -15, 1,   6,   4,
    13,  3,   24,  5,   16,  5,   13,  3,   9,   13,  16,  9,   20,  21,  18,
    8,   12,  19,  13,  3,   -11, -17, 6,   4,   19,  -16, 22,  8,   22,  -14,
    14,  3,   -20, -19, 5,   4,   16,  -14, 23,  8,   18,  -12, 14,  3,   16,
    -1,  19,  13,  19,  -1,  19,  13,  12,  1,   15,  4,   16,  -12, 5,   4,
};

static u16 s_PcData_8017A7DC[] = {
    5649, 6162, 6163, 6676, 2069, 2070, 2071, 2072, 2073, 65535,
};

static u16 s_PcData_8017A7F0[] = {
    7194, 7707, 7708, 8221, 2078, 2083, 2084, 2085, 2086, 65535,
};

static u16 s_PcData_8017A804[] = {
    7194, 8735, 9248, 9761, 2082, 2083, 2084, 2085, 2086, 65535,
};

static u16 s_PcData_8017A818[] = {
    10279, 10792, 10793, 11306, 2091, 2092, 65535, 0,
};

static u16 s_PcData_8017A828[] = {
    11821, 12334, 12335, 12848, 2097, 2102, 65535, 0,
    11821, 13362, 13875, 14388, 2101, 2102, 65535, 0,
};

static u16* s_PcData_8017A8DC[] = {
    s_PcData_8017A7DC, s_PcData_8017A7DC, s_PcData_8017A7F0, s_PcData_8017A804,
    s_PcData_8017A818, s_PcData_8017A828, s_PcData_8017A828,
};

WeaponAnimation D_E4000_8017A8F8[] = {
    {s_PcData_8017A8C0, s_PcData_8017A848, 0, 1548, 125, 1, 0},
    {s_PcData_8017A8DC, s_PcData_8017A848, 0, 1547, 132, 2, 0},
};

static u16 s_PcData_8017A704[] = {
#include "gen/pc_w_032_clut_8017A704.h"
};

u16* g_WeaponCluts[] = {
    s_PcData_8017A704,
    s_PcData_8017A704,
};

s32 g_HandId = HAND_ID;
