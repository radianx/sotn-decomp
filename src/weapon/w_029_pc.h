// SPDX-License-Identifier: AGPL-3.0-or-later
// Native definitions for tables retained as PS1 assembly data.

s8 D_CF000_8017AC78[];
AnimationFrame* D_CF000_8017ACC0[];
u16 D_CF000_8017ACF8[];
u16 D_CF000_8017AD04[];
u16 D_CF000_8017AD10[];
AnimationFrame D_CF000_8017AD24[];
static u16 s_PcData_8017A884[];
u16* g_WeaponCluts[];

s8 D_CF000_8017AC78[] = {
    0,  0,  0,   0,   14, -7, 4,  12, 14, 13, 4,  12, -11, -7, 4,  12, 1,  -5,
    4,  12, -32, -31, 0,  0,  22, -6, 4,  12, 15, -6, 4,   12, 16, -5, 4,  12,
    17, -4, 4,   12,  18, -3, 4,  12, 19, -2, 4,  12, 20,  -1, 4,  12, 21, 0,
    4,  12, 22,  1,   4,  12, 12, -5, 4,  12, 10, -3, 4,   12, 8,  -1, 4,  12,
};

static AnimationFrame s_Fire_8017AAC4[] = {
    {2, 513},
    {0, 0},
};

static AnimationFrame s_Fire_8017AACC[] = {
    {2, 1026},
    {0, 0},
};

static AnimationFrame s_Fire_8017AAD4[] = {
    {2, 1539}, {2, 1540}, {2, 1541}, {2, 1542}, {2, 1543}, {2, 1544},
    {2, 2057}, {2, 522},  {2, 523},  {2, 524},  {0, 0},
};

static AnimationFrame s_Fire_8017AB00[] = {
    {3, 525},  {3, 3598}, {3, 4111}, {3, 4624}, {3, 5137}, {3, 5650},
    {3, 6163}, {3, 6676}, {3, 7189}, {3, 6678}, {3, 6167}, {3, 5656},
    {3, 5145}, {3, 4634}, {3, 4123}, {3, 3612}, {0, 0},
};

static AnimationFrame s_Fire_8017AB44[] = {
    {1, 548}, {1, 549}, {1, 550}, {1, 551}, {1, 552}, {1, 553}, {1, 554},
    {1, 555}, {1, 556}, {1, 557}, {1, 558}, {1, 559}, {1, 560}, {0, 0},
};

static AnimationFrame s_Fire_8017AB7C[] = {
    {1, 554}, {1, 555}, {1, 556}, {1, 557},
    {1, 558}, {1, 559}, {1, 560}, {0, 0},
};

static AnimationFrame s_Fire_8017AB9C[] = {
    {2, 545}, {2, 546}, {2, 547}, {2, 548}, {2, 549}, {2, 550},
    {2, 551}, {2, 552}, {2, 553}, {2, 554}, {2, 555}, {2, 556},
    {2, 557}, {2, 558}, {2, 559}, {2, 560}, {0, 0},
};

static AnimationFrame s_Fire_8017ABE0[] = {
    {2, 561},
    {2, 562},
    {2, 563},
    {65535, 0},
};

static AnimationFrame s_Fire_8017ABF0[] = {
    {2, 1076},
    {2, 1077},
    {2, 1078},
    {65535, 0},
};

static AnimationFrame s_Fire_8017AC00[] = {
    {2, 563},
    {2, 562},
    {2, 561},
    {65535, 0},
};

static AnimationFrame s_Fire_8017AC10[] = {
    {2, 1078},
    {2, 1077},
    {2, 1076},
    {65535, 0},
};

static AnimationFrame s_Fire_8017AC20[] = {
    {4, 541},
    {4, 542},
    {0, 0},
};

static AnimationFrame s_Fire_8017AC2C[] = {
    {2, 3103},
    {2, 3104},
    {0, 0},
};

static AnimationFrame s_Fire_8017AC38[] = {
    {3, 8759}, {3, 8760}, {3, 8760}, {3, 8248}, {3, 7736}, {3, 569},
    {3, 570},  {3, 571},  {3, 572},  {3, 573},  {3, 513},  {3, 513},
    {3, 513},  {3, 513},  {3, 513},  {0, 0},
};

AnimationFrame* D_CF000_8017ACC0[] = {
    s_Fire_8017AAC4, s_Fire_8017AACC, s_Fire_8017AC2C, s_Fire_8017AC38,
    s_Fire_8017AC20, s_Fire_8017AB9C, s_Fire_8017AB7C, s_Fire_8017AB44,
    s_Fire_8017AB00, s_Fire_8017AAD4, s_Fire_8017ABE0, s_Fire_8017ABF0,
    s_Fire_8017AC00, s_Fire_8017AC10,
};

u16 D_CF000_8017ACF8[] = {
    0, 1, 2, 3, 4, 0,
};

u16 D_CF000_8017AD04[] = {
    5, 6, 7, 8, 9, 0,
};

u16 D_CF000_8017AD10[] = {
    10, 15, 11, 15, 12, 15, 13, 15, 14, 15,
};

AnimationFrame D_CF000_8017AD24[] = {
    {3, 3135}, {3, 3136}, {3, 3135}, {3, 3136}, {3, 3137},
    {3, 3138}, {3, 3137}, {3, 3138}, {0, 0},
};

static u16 s_PcData_8017A884[] = {
#include "gen/pc_w_029_clut_8017A884.h"
};

u16* g_WeaponCluts[] = {
    s_PcData_8017A884,
    s_PcData_8017A884,
};

s32 g_HandId = HAND_ID;

FireShieldDragon D_CF000_8017C9A0[3][20] = {0};
