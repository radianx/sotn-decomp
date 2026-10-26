// SPDX-License-Identifier: AGPL-3.0-or-later
// Native definitions for tables retained as PS1 assembly data.

static u16 s_PcData_8017AAA4[];
static u16 s_PcData_8017AAC0[];
static u16 s_PcData_8017AADC[];
static u16 s_PcData_8017AAF8[];
static u16 s_PcData_8017AB10[];
static u16 s_PcData_8017AB28[];
static u16* s_PcData_8017ABA8[];
static s8 s_PcData_8017AB54[];
WeaponAnimation D_2E000_8017ABC4[];
u16 D_2E000_8017ABD4[];
s32 D_2E000_8017ABF0[];
u8 D_2E000_8017AC04[6][8];
static u16 s_PcData_8017A884[];
u16* g_WeaponCluts[];

static u16 s_PcData_8017AAA4[] = {
    513,  514,  1027, 1540, 1541, 2054, 2055,
    2056, 2057, 2570, 2571, 2572, 2573, 65535,
};

static u16 s_PcData_8017AAC0[] = {
    2574, 3087, 3600, 4113, 4114, 4627, 4628,
    5141, 4630, 7198, 7199, 7200, 7201, 65535,
};

static u16 s_PcData_8017AADC[] = {
    2574, 3087, 5655, 6168, 6169, 6682, 6683,
    6684, 6685, 7198, 7199, 7200, 7201, 65535,
};

static u16 s_PcData_8017AAF8[] = {
    546, 547, 1060, 1573, 1574, 2087, 2088, 2089, 2090, 2603, 65535, 0,
};

static u16 s_PcData_8017AB10[] = {
    7724, 7725, 1070, 1583, 1584, 2097, 2098, 2099, 2100, 2620, 65535, 0,
};

static u16 s_PcData_8017AB28[] = {
    7724, 7725, 8245, 8246, 8247, 8760, 8761, 8762, 8763, 2620, 65535,
    0,    4,    9277, 4,    9278, 4,    9279, 4,    9280, 0,    0,
};

static u16* s_PcData_8017ABA8[] = {
    s_PcData_8017AAA4, s_PcData_8017AAA4, s_PcData_8017AAC0, s_PcData_8017AADC,
    s_PcData_8017AAF8, s_PcData_8017AB10, s_PcData_8017AB28,
};

static s8 s_PcData_8017AB54[] = {
    0,  0,  0,  0,   -3, -26, 12, 4,   26, -27, 16,  6,  40,  -18, 8,  8,  17,
    -9, 12, 8,  -15, -4, 4,   4,  -10, -8, 12,  4,   19, -11, 16,  8,  32, -1,
    8,  8,  15, 8,   12, 8,   22, 3,   18, 4,   17,  2,  12,  12,  29, 19, 8,
    8,  11, 18, 12,  8,  -23, 14, 4,   4,  -14, -28, 12, 4,   24,  4,  20, 12,
    6,  -3, 16, 8,   1,  0,   8,  8,   0,  0,   15,  15, 1,   2,   28, 28,
};

WeaponAnimation D_2E000_8017ABC4[] = {
    {s_PcData_8017ABA8, s_PcData_8017AB54, 6, 1673, 72, 3, 0},
};

u16 D_2E000_8017ABD4[] = {
    1, 2, 3, 4, 5, 6, 7, 8, 7, 6, 5, 4, 3, 2,
};

s32 D_2E000_8017ABF0[] = {
    81920, -114688, 32768, -65536, -16384,
};

u8 D_2E000_8017AC04[6][8] = {
    0,   80, 16,  80, 0,   96, 16,  96, 16,  80, 32,  80, 16,  96, 32,  96,
    112, 64, 128, 64, 112, 80, 128, 80, 112, 48, 120, 48, 112, 56, 120, 56,
    120, 48, 128, 48, 120, 56, 128, 56, 112, 56, 120, 56, 119, 64, 120, 64,
};

static u16 s_PcData_8017A884[] = {
#include "gen/pc_w_006_clut_8017A884.h"
};

u16* g_WeaponCluts[] = {
    s_PcData_8017A884,
    s_PcData_8017A884,
};

s32 g_HandId = HAND_ID;
