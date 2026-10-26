// SPDX-License-Identifier: AGPL-3.0-or-later
// Native definitions for tables retained as PS1 assembly data.

static u16 s_PcData_8017ACA8[];
static u16 s_PcData_8017ACC8[];
static u16 s_PcData_8017ACE8[];
static u16 s_PcData_8017AD08[];
static u16 s_PcData_8017AD24[];
static u16 s_PcData_8017AD40[];
static u16* s_PcData_8017ADA4[];
static s8 s_PcData_8017AD5C[];
WeaponAnimation D_10E000_8017ADC0[];
static u16 s_PcData_8017AC08[];
u16* g_WeaponCluts[];

static u16 s_PcData_8017ACA8[] = {
    513,  1026, 1027, 1028, 1541, 2054, 2055, 2056,
    2057, 522,  523,  524,  525,  526,  527,  65535,
};

static u16 s_PcData_8017ACC8[] = {
    528,  2577, 2578, 2579, 3092, 3605, 3606, 3607,
    3608, 537,  538,  549,  550,  551,  552,  65535,
};

static u16 s_PcData_8017ACE8[] = {
    528,  2587, 2588, 2589, 4126, 4639, 4640, 4641,
    4642, 547,  548,  549,  550,  551,  552,  65535,
};

static u16 s_PcData_8017AD08[] = {
    553,  5162, 5163, 5164, 5677, 6190,  6191,
    6192, 6193, 562,  563,  564,  65535, 0,
};

static u16 s_PcData_8017AD24[] = {
    565,  6710, 6711, 6712, 7225, 7738,  7739,
    7740, 7741, 574,  575,  583,  65535, 0,
};

static u16 s_PcData_8017AD40[] = {
    565,  6710, 6711, 6712, 8256, 8769,  8770,
    8771, 8772, 581,  582,  583,  65535, 0,
};

static u16* s_PcData_8017ADA4[] = {
    s_PcData_8017ACA8, s_PcData_8017ACA8, s_PcData_8017ACC8, s_PcData_8017ACE8,
    s_PcData_8017AD08, s_PcData_8017AD24, s_PcData_8017AD40,
};

static s8 s_PcData_8017AD5C[] = {
    0,  0,  0,  0,   -32, -31, 0,  0,   3,  -24, 5,  4, 16, -14, 32, 3, 26, -14,
    23, 2,  -5, -5,  5,   4,   9,  3,   33, 3,   20, 3, 22, 2,   5,  9, 13, 10,
    16, 19, 18, 8,   -3,  -21, 6,  7,   14, -16, 32, 3, 25, -16, 22, 3, -9, -23,
    5,  8,  16, -15, 27,  4,   23, -14, 20, 3,   18, 1, 23, 10,  24, 4, 18, 10,
};

WeaponAnimation D_10E000_8017ADC0[] = {
    {s_PcData_8017ADA4, s_PcData_8017AD5C, 0, 1547, 174, 4, 0},
    {s_PcData_8017ADA4, s_PcData_8017AD5C, 0, 1547, 174, 4, 0},
};

static u16 s_PcData_8017AC08[] = {
#include "gen/pc_w_038_clut_8017AC08.h"
};

u16* g_WeaponCluts[] = {
    s_PcData_8017AC08,
    s_PcData_8017AC08,
};

s32 g_HandId = HAND_ID;

s32 D_10E000_8017B844 = {0};
