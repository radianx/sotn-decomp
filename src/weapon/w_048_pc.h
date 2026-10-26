// SPDX-License-Identifier: AGPL-3.0-or-later
// Native definitions for tables retained as PS1 assembly data.

static u16 s_PcData_8017AEA4[];
static u16 s_PcData_8017AEC0[];
static u16 s_PcData_8017AEDC[];
static u16 s_PcData_8017AEF8[];
static u16 s_PcData_8017AF10[];
static u16 s_PcData_8017AF28[];
static u16* s_PcData_8017AFA4[];
static s8 s_PcData_8017AF40[];
WeaponAnimation D_154000_8017AFC0[];
u16 D_154000_8017AFE0[];
s16 D_154000_8017B000[];
static u16 s_PcData_8017AA44[];
static u16 s_PcData_8017AB24[];
static u16 s_PcData_8017AC04[];
static u16 s_PcData_8017ACE4[];
static u16 s_PcData_8017ADC4[];
u16* g_WeaponCluts[];

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

static u16* s_PcData_8017AFA4[] = {
    s_PcData_8017AEA4, s_PcData_8017AEA4, s_PcData_8017AEC0, s_PcData_8017AEDC,
    s_PcData_8017AEF8, s_PcData_8017AF10, s_PcData_8017AF28,
};

static s8 s_PcData_8017AF40[] = {
    0,   0,   0,   0,   4,   -23, 8,  5,  30,  -17, 35, 8,  30,  -14, 18,
    4,   -32, -31, 0,   0,   -4,  -6, 8,  5,   22,  0,  35, 8,   22,  3,
    18,  4,   29,  22,  13,  11,  12, 7,  19,  12,  14, 14, 18,  4,   1,
    -25, 8,   5,   27,  -19, 35,  8,  27, -16, 18,  4,  -8, -26, 8,   5,
    24,  -17, 35,  8,   24,  -14, 18, 4,  23,  0,   27, 14, 18,  2,   21,
    11,  29,  -14, 34,  4,   21,  3,  34, 4,   28,  21, 12, 10,  26,  -16,
    34,  4,   23,  -14, 34,  4,   22, 3,  26,  10,
};

WeaponAnimation D_154000_8017AFC0[] = {
    {s_PcData_8017AFA4, s_PcData_8017AF40, 0, 1548, 65, 4, 0},
    {s_PcData_8017AFA4, s_PcData_8017AF40, 0, 1548, 65, 2, 0},
};

u16 D_154000_8017AFE0[] = {
    128, 128, 128, 0, 64, 176, 16, 0, 32, 208, 16, 0, 0, 255, 64, 0,
};

s16 D_154000_8017B000[] = {
    24, -14, 64, 0,   24, -14, 64, 0,   20, 2, 64, 0, 18, 14,
    48, 34,  24, -16, 64, 0,   24, -14, 64, 0, 24, 4, 48, 34,
};

static u16 s_PcData_8017AA44[] = {
#include "gen/pc_w_048_clut_8017AA44.h"
};

static u16 s_PcData_8017AB24[] = {
#include "gen/pc_w_048_clut_8017AB24.h"
};

static u16 s_PcData_8017AC04[] = {
#include "gen/pc_w_048_clut_8017AC04.h"
};

static u16 s_PcData_8017ACE4[] = {
#include "gen/pc_w_048_clut_8017ACE4.h"
};

static u16 s_PcData_8017ADC4[] = {
#include "gen/pc_w_048_clut_8017ADC4.h"
};

u16* g_WeaponCluts[] = {
    s_PcData_8017AA44, s_PcData_8017AB24, s_PcData_8017AC04,
    s_PcData_8017ACE4, s_PcData_8017ADC4,
};

s32 g_HandId = HAND_ID;

s32 D_154000_8017C3B4 = {0};
