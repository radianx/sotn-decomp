// SPDX-License-Identifier: AGPL-3.0-or-later
// Native definitions for tables retained as PS1 assembly data.

static u16 s_PcData_8017AF40[];
static u16 s_PcData_8017AF5C[];
static u16 s_PcData_8017AF78[];
static u16 s_PcData_8017AF94[];
static u16 s_PcData_8017AFA8[];
static u16 s_PcData_8017AFBC[];
static u16* s_PcData_8017B050[];
static s8 s_PcData_8017AFD0[];
static u16 s_PcData_8017AEA4[];
static u16 s_PcData_8017AEC0[];
static u16 s_PcData_8017AEDC[];
static u16 s_PcData_8017AEF8[];
static u16 s_PcData_8017AF10[];
static u16 s_PcData_8017AF28[];
static u16* s_PcData_8017B034[];
WeaponAnimation D_193000_8017B06C[];
static u16 s_PcData_8017AB24[];
u16* g_WeaponCluts[];

static u16 s_PcData_8017AF40[] = {
    513,  9791, 9792, 9793, 1542, 1543,  1544,
    1545, 2058, 2059, 2060, 2061, 65535, 0,
};

static u16 s_PcData_8017AF5C[] = {
    2574, 10306, 10307, 10308, 3603, 3604,  3605,
    3606, 2079,  2080,  2081,  2082, 65535, 0,
};

static u16 s_PcData_8017AF78[] = {
    2574, 10821, 10822, 10823, 5147, 5148,  5149,
    5150, 2079,  2080,  2081,  2082, 65535, 0,
};

static u16 s_PcData_8017AF94[] = {
    5667, 11336, 11337, 11338, 6696, 6697, 6698, 6699, 2092, 65535,
};

static u16 s_PcData_8017AFA8[] = {
    7213, 11851, 11852, 11853, 8242, 8243, 8244, 8245, 2110, 65535,
};

static u16 s_PcData_8017AFBC[] = {
    7213, 12366, 12367, 12368, 9274, 9275, 9276, 9277, 2110, 65535,
};

static u16* s_PcData_8017B050[] = {
    s_PcData_8017AF40, s_PcData_8017AF40, s_PcData_8017AF5C, s_PcData_8017AF78,
    s_PcData_8017AF94, s_PcData_8017AFA8, s_PcData_8017AFBC,
};

static s8 s_PcData_8017AFD0[] = {
    0,   0,   0,   0,   4,   -23, 8,  5,  30,  -17, 35, 8,  30,  -14, 18,
    4,   -32, -31, 0,   0,   -4,  -6, 8,  5,   22,  0,  35, 8,   22,  3,
    18,  4,   29,  22,  13,  11,  12, 7,  19,  12,  14, 14, 18,  4,   1,
    -25, 8,   5,   27,  -19, 35,  8,  27, -16, 18,  4,  -8, -26, 8,   5,
    24,  -17, 35,  8,   24,  -14, 18, 4,  23,  0,   27, 14, 18,  2,   21,
    11,  29,  -14, 34,  4,   21,  3,  34, 4,   28,  21, 12, 10,  26,  -16,
    34,  4,   23,  -14, 34,  4,   22, 3,  26,  10,
};

static u16 s_PcData_8017AEA4[] = {
    513,  1026, 1027, 1028, 1029, 1542, 1543,
    1544, 1545, 2058, 2059, 2060, 2061, 65535,
};

static u16 s_PcData_8017AEC0[] = {
    2574, 3087, 3088, 3089, 3090, 3603, 3604,
    3605, 3606, 2079, 2080, 2081, 2082, 65535,
};

static u16 s_PcData_8017AEDC[] = {
    2574, 4119, 4632, 4121, 4634, 5147, 5148,
    5149, 5150, 2079, 2080, 2081, 2082, 65535,
};

static u16 s_PcData_8017AEF8[] = {
    5667, 6180, 6181, 6182, 6183, 6696, 6697, 6698, 6699, 2092, 65535, 0,
};

static u16 s_PcData_8017AF10[] = {
    7213, 7726, 7727, 7728, 7729, 8242, 8243, 8244, 8245, 2110, 65535, 0,
};

static u16 s_PcData_8017AF28[] = {
    7213, 8758, 8759, 8760, 8761, 9274, 9275, 9276, 9277, 2110, 65535, 0,
};

static u16* s_PcData_8017B034[] = {
    s_PcData_8017AEA4, s_PcData_8017AEA4, s_PcData_8017AEC0, s_PcData_8017AEDC,
    s_PcData_8017AEF8, s_PcData_8017AF10, s_PcData_8017AF28,
};

WeaponAnimation D_193000_8017B06C[] = {
    {s_PcData_8017B050, s_PcData_8017AFD0, 0, 1547, 65, 4, 0},
    {s_PcData_8017B034, s_PcData_8017AFD0, 0, 1547, 65, 4, 0},
    {s_PcData_8017B034, s_PcData_8017AFD0, 0, 1548, 65, 4, 0},
    {s_PcData_8017B034, s_PcData_8017AFD0, 0, 1704, 65, 4, 0},
};

static u16 s_PcData_8017AB24[] = {
#include "gen/pc_w_057_clut_8017AB24.h"
};

u16* g_WeaponCluts[] = {
    s_PcData_8017AB24,
};

s32 g_HandId = HAND_ID;
