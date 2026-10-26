// SPDX-License-Identifier: AGPL-3.0-or-later
// Native definitions for tables retained as PS1 assembly data.

static u16 s_PcData_8017AEE0[];
static u16 s_PcData_8017AEFC[];
static u16 s_PcData_8017AF18[];
static u16 s_PcData_8017AF34[];
static u16 s_PcData_8017AF4C[];
static u16 s_PcData_8017AF64[];
static u16* s_PcData_8017AFE0[];
static s8 s_PcData_8017AF7C[];
WeaponAnimation D_15B000_8017AFFC[];
s16 D_15B000_8017B03C[];
AnimationFrame D_15B000_8017B074[];
AnimationFrame D_15B000_8017B0D4[];
AnimationFrame D_15B000_8017B10C[];
static u16 s_PcData_8017AC00[];
u16* g_WeaponCluts[];

static u16 s_PcData_8017AEE0[] = {
    513,  1026, 1027, 1028, 1029, 1542, 1543,
    1544, 1545, 2058, 2059, 2060, 2061, 65535,
};

static u16 s_PcData_8017AEFC[] = {
    2574, 3087, 3088, 3089, 3090, 3603, 3604,
    3605, 3606, 2079, 2080, 2081, 2082, 65535,
};

static u16 s_PcData_8017AF18[] = {
    2574, 4119, 4632, 4121, 4634, 5147, 5148,
    5149, 5150, 2079, 2080, 2081, 2082, 65535,
};

static u16 s_PcData_8017AF34[] = {
    5667, 6180, 6181, 6182, 6183, 6696, 6697, 6698, 6699, 2092, 65535, 0,
};

static u16 s_PcData_8017AF4C[] = {
    7213, 7726, 7727, 7728, 7729, 8242, 8243, 8244, 8245, 2110, 65535, 0,
};

static u16 s_PcData_8017AF64[] = {
    7213, 8758, 8759, 8760, 8761, 9274, 9275, 9276, 9277, 2110, 65535, 0,
};

static u16* s_PcData_8017AFE0[] = {
    s_PcData_8017AEE0, s_PcData_8017AEE0, s_PcData_8017AEFC, s_PcData_8017AF18,
    s_PcData_8017AF34, s_PcData_8017AF4C, s_PcData_8017AF64,
};

static s8 s_PcData_8017AF7C[] = {
    0,   0,   0,   0,   4,   -23, 8,  5,  30,  -17, 35, 8,  30,  -14, 18,
    4,   -32, -31, 0,   0,   -4,  -6, 8,  5,   22,  0,  35, 8,   22,  3,
    18,  4,   29,  22,  13,  11,  12, 7,  19,  12,  14, 14, 18,  4,   1,
    -25, 8,   5,   27,  -19, 35,  8,  27, -16, 18,  4,  -8, -26, 8,   5,
    24,  -17, 35,  8,   24,  -14, 18, 4,  23,  0,   27, 14, 18,  2,   21,
    11,  29,  -14, 34,  4,   21,  3,  34, 4,   28,  21, 12, 10,  26,  -16,
    34,  4,   23,  -14, 34,  4,   22, 3,  26,  10,
};

WeaponAnimation D_15B000_8017AFFC[] = {
    {s_PcData_8017AFE0, s_PcData_8017AF7C, 0, 1548, 65, 4, 0},
    {s_PcData_8017AFE0, s_PcData_8017AF7C, 0, 1548, 65, 2, 0},
    {s_PcData_8017AFE0, s_PcData_8017AF7C, 0, 1580, 65, 4, 0},
    {s_PcData_8017AFE0, s_PcData_8017AF7C, 0, 1580, 65, 4, 0},
};

s16 D_15B000_8017B03C[] = {
    24, -14, 64, 0,   24, -14, 64, 0,   20, 2, 64, 0, 18, 14,
    48, 34,  24, -16, 64, 0,   24, -14, 64, 0, 24, 4, 48, 34,
};

AnimationFrame D_15B000_8017B074[] = {
    {1, 1}, {1, 2}, {1, 3}, {1, 4}, {1, 5}, {1, 6}, {1, 7}, {1, 8},
    {0, 0}, {1, 1}, {1, 2}, {1, 3}, {1, 4}, {1, 5}, {1, 4}, {1, 3},
    {1, 4}, {1, 3}, {1, 4}, {1, 5}, {1, 6}, {1, 7}, {1, 8}, {65535, 0},
};

AnimationFrame D_15B000_8017B0D4[] = {
    {3, 1}, {3, 2}, {3, 3},  {3, 4},  {3, 5},  {3, 6},  {3, 7},
    {3, 8}, {3, 9}, {3, 10}, {3, 11}, {3, 12}, {3, 13}, {65535, 0},
};

AnimationFrame D_15B000_8017B10C[] = {
    {2, 1}, {2, 2}, {2, 3},  {2, 4},  {2, 5},  {2, 6},  {2, 7},
    {2, 8}, {2, 9}, {2, 10}, {2, 11}, {2, 12}, {2, 13}, {65535, 0},
};

static u16 s_PcData_8017AC00[] = {
#include "gen/pc_w_049_clut_8017AC00.h"
};

u16* g_WeaponCluts[] = {
    s_PcData_8017AC00,
};

s32 g_HandId = HAND_ID;

s32 D_15B000_8017C8CC = {0};
