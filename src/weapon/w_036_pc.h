// SPDX-License-Identifier: AGPL-3.0-or-later
// Native definitions for tables retained as PS1 assembly data.

static u16 s_PcData_8017A4A4[];
static u16 s_PcData_8017A4B8[];
static u16 s_PcData_8017A4CC[];
static u16 s_PcData_8017A4DC[];
static u16* s_PcData_8017A524[];
static s8 s_PcData_8017A4EC[];
WeaponAnimation D_100000_8017A540[];
static u16 s_PcData_8017A404[];
u16* g_WeaponCluts[];

static u16 s_PcData_8017A4A4[] = {
    513, 1026, 1539, 2052, 2053, 2054, 2055, 2056, 2057, 65535,
};

static u16 s_PcData_8017A4B8[] = {
    2570, 3083, 3596, 2061, 2062, 2063, 2064, 2065, 2066, 65535,
};

static u16 s_PcData_8017A4CC[] = {
    4115, 4628, 5141, 2070, 2071, 2072, 65535, 0,
};

static u16 s_PcData_8017A4DC[] = {
    5657, 6170, 6683, 2076, 2077, 2078, 65535, 0,
};

static u16* s_PcData_8017A524[] = {
    s_PcData_8017A4A4, s_PcData_8017A4A4, s_PcData_8017A4B8, s_PcData_8017A4B8,
    s_PcData_8017A4CC, s_PcData_8017A4DC, s_PcData_8017A4DC,
};

static s8 s_PcData_8017A4EC[] = {
    0,  0, 0,   0,   5, -23, 7,  4,   25, -20, 22, 10,  27, -13,
    22, 3, -32, -31, 0, 0,   -3, -7,  6,  4,   17, -5,  22, 10,
    20, 3, 22,  3,   1, -25, 6,  4,   23, -23, 22, 10,  25, -15,
    22, 3, -7,  -27, 6, 4,   19, -22, 22, 10,  22, -14, 22, 3,
};

WeaponAnimation D_100000_8017A540[] = {
    {s_PcData_8017A524, s_PcData_8017A4EC, 0, 1547, 160, 4, 0},
};

static u16 s_PcData_8017A404[] = {
#include "gen/pc_w_036_clut_8017A404.h"
};

u16* g_WeaponCluts[] = {
    s_PcData_8017A404,
    s_PcData_8017A404,
};

s32 g_HandId = HAND_ID;
