// SPDX-License-Identifier: AGPL-3.0-or-later
// Native definitions for tables retained as PS1 assembly data.

static u16 s_PcData_8017AD8C[];
static u16 s_PcData_8017ADA8[];
static u16 s_PcData_8017ADC4[];
static u16 s_PcData_8017ADE0[];
static u16 s_PcData_8017ADF8[];
static u16 s_PcData_8017AE10[];
static u16* s_PcData_8017AEA8[];
static s8 s_PcData_8017AE28[];
static u16 s_PcData_8017ACE4[];
static u16 s_PcData_8017AD04[];
static u16 s_PcData_8017AD24[];
static u16 s_PcData_8017AD44[];
static u16 s_PcData_8017AD5C[];
static u16 s_PcData_8017AD74[];
static u16* s_PcData_8017AE8C[];
WeaponAnimation D_17E000_8017AEC4[];
u16 D_17E000_8017AEF4[];
u16 D_17E000_8017AEFC[];
static u16 s_PcData_8017AA44[];
u16* g_WeaponCluts[];

static u16 s_PcData_8017AD8C[] = {
    513,  9791, 9792, 9793, 1542, 1543, 1544,
    1545, 2058, 2059, 2060, 2061, 2061, 65535,
};

static u16 s_PcData_8017ADA8[] = {
    2574, 10306, 10307, 10308, 3603, 3604, 3605,
    3606, 2079,  2080,  2081,  2082, 2082, 65535,
};

static u16 s_PcData_8017ADC4[] = {
    2574, 10821, 10822, 10823, 5147, 5148, 5149,
    5150, 2079,  2080,  2081,  2082, 2082, 65535,
};

static u16 s_PcData_8017ADE0[] = {
    5667, 11336, 11337, 11338, 6696, 6697, 6698, 6699, 2092, 2092, 65535, 0,
};

static u16 s_PcData_8017ADF8[] = {
    7213, 11851, 11852, 11853, 8242, 8243, 8244, 8245, 2110, 2110, 65535, 0,
};

static u16 s_PcData_8017AE10[] = {
    7213, 12366, 12367, 12368, 9274, 9275, 9276, 9277, 2110, 2110, 65535, 0,
};

static u16* s_PcData_8017AEA8[] = {
    s_PcData_8017AD8C, s_PcData_8017AD8C, s_PcData_8017ADA8, s_PcData_8017ADC4,
    s_PcData_8017ADE0, s_PcData_8017ADF8, s_PcData_8017AE10,
};

static s8 s_PcData_8017AE28[] = {
    0,   0,   0,   0,   4,   -23, 8,  5,  30,  -17, 35, 8,  30,  -14, 18,
    4,   -32, -31, 0,   0,   -4,  -6, 8,  5,   22,  0,  35, 8,   22,  3,
    18,  4,   29,  22,  13,  11,  12, 7,  19,  12,  14, 14, 18,  4,   1,
    -25, 8,   5,   27,  -19, 35,  8,  27, -16, 18,  4,  -8, -26, 8,   5,
    24,  -17, 35,  8,   24,  -14, 18, 4,  23,  0,   27, 14, 18,  2,   21,
    11,  29,  -14, 34,  4,   21,  3,  34, 4,   28,  21, 12, 10,  26,  -16,
    34,  4,   23,  -14, 34,  4,   22, 3,  26,  10,
};

static u16 s_PcData_8017ACE4[] = {
    513,  1026, 1027, 1028, 1029, 1542, 1543,  1544,
    1545, 2058, 2059, 2060, 2061, 2061, 65535, 0,
};

static u16 s_PcData_8017AD04[] = {
    2574, 3087, 3088, 3089, 3090, 3603, 3604,  3605,
    3606, 2079, 2080, 2081, 2082, 2082, 65535, 0,
};

static u16 s_PcData_8017AD24[] = {
    2574, 4119, 4632, 4121, 4634, 5147, 5148,  5149,
    5150, 2079, 2080, 2081, 2082, 2082, 65535, 0,
};

static u16 s_PcData_8017AD44[] = {
    5667, 6180, 6181, 6182, 6183, 6696, 6697, 6698, 6699, 2092, 2092, 65535,
};

static u16 s_PcData_8017AD5C[] = {
    7213, 7726, 7727, 7728, 7729, 8242, 8243, 8244, 8245, 2110, 2110, 65535,
};

static u16 s_PcData_8017AD74[] = {
    7213, 8758, 8759, 8760, 8761, 9274, 9275, 9276, 9277, 2110, 2110, 65535,
};

static u16* s_PcData_8017AE8C[] = {
    s_PcData_8017ACE4, s_PcData_8017ACE4, s_PcData_8017AD04, s_PcData_8017AD24,
    s_PcData_8017AD44, s_PcData_8017AD5C, s_PcData_8017AD74,
};

WeaponAnimation D_17E000_8017AEC4[] = {
    {s_PcData_8017AEA8, s_PcData_8017AE28, 0, 1547, 65, 4, 0},
    {s_PcData_8017AE8C, s_PcData_8017AE28, 0, 1547, 65, 4, 0},
    {s_PcData_8017AE8C, s_PcData_8017AE28, 0, 1547, 65, 4, 0},
};

u16 D_17E000_8017AEF4[] = {
    65527,
    65518,
    65524,
    65522,
};

u16 D_17E000_8017AEFC[] = {
    65528,
    10,
    65527,
    65528,
};

static u16 s_PcData_8017AA44[] = {
#include "gen/pc_w_054_clut_8017AA44.h"
};

u16* g_WeaponCluts[] = {
    s_PcData_8017AA44,
};

s32 g_HandId = HAND_ID;
