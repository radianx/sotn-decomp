// SPDX-License-Identifier: AGPL-3.0-or-later
// Native definitions for tables retained as PS1 assembly data.

s8 D_19A000_8017AB3C[];
static AnimationFrame s_PcData_8017A988[];
static AnimationFrame s_PcData_8017A990[];
static AnimationFrame s_PcData_8017AAF0[];
static AnimationFrame s_PcData_8017AAFC[];
static AnimationFrame s_PcData_8017AAE4[];
static AnimationFrame s_PcData_8017AA60[];
static AnimationFrame s_PcData_8017AA40[];
static AnimationFrame s_PcData_8017AA08[];
static AnimationFrame s_PcData_8017A9C4[];
static AnimationFrame s_PcData_8017A998[];
static AnimationFrame s_PcData_8017AAA4[];
static AnimationFrame s_PcData_8017AAB4[];
static AnimationFrame s_PcData_8017AAC4[];
static AnimationFrame s_PcData_8017AAD4[];
AnimationFrame* D_19A000_8017AB84[];
static u16 s_PcData_8017A808[];
u16* g_WeaponCluts[];

s8 D_19A000_8017AB3C[] = {
    0,  0,  0,   0,   14, -7, 4,  12, 14, 13, 4,  12, -11, -7, 4,  12, 1,  -5,
    4,  12, -32, -31, 0,  0,  22, -6, 4,  12, 15, -6, 4,   12, 16, -5, 4,  12,
    17, -4, 4,   12,  18, -3, 4,  12, 19, -2, 4,  12, 20,  -1, 4,  12, 21, 0,
    4,  12, 22,  1,   4,  12, 12, -5, 4,  12, 10, -3, 4,   12, 8,  -1, 4,  12,
};

static AnimationFrame s_PcData_8017A988[] = {
    {2, 513},
    {0, 0},
};

static AnimationFrame s_PcData_8017A990[] = {
    {2, 1026},
    {0, 0},
};

static AnimationFrame s_PcData_8017AAF0[] = {
    {2, 3103},
    {2, 3104},
    {0, 0},
};

static AnimationFrame s_PcData_8017AAFC[] = {
    {3, 8759}, {3, 8760}, {3, 8760}, {3, 8248}, {3, 7736}, {3, 569},
    {3, 570},  {3, 571},  {3, 572},  {3, 573},  {3, 513},  {3, 513},
    {3, 513},  {3, 513},  {3, 513},  {0, 0},
};

static AnimationFrame s_PcData_8017AAE4[] = {
    {4, 541},
    {4, 542},
    {0, 0},
};

static AnimationFrame s_PcData_8017AA60[] = {
    {2, 545}, {2, 546}, {2, 547}, {2, 548}, {2, 549}, {2, 550},
    {2, 551}, {2, 552}, {2, 553}, {2, 554}, {2, 555}, {2, 556},
    {2, 557}, {2, 558}, {2, 559}, {2, 560}, {0, 0},
};

static AnimationFrame s_PcData_8017AA40[] = {
    {1, 554}, {1, 555}, {1, 556}, {1, 557},
    {1, 558}, {1, 559}, {1, 560}, {0, 0},
};

static AnimationFrame s_PcData_8017AA08[] = {
    {1, 548}, {1, 549}, {1, 550}, {1, 551}, {1, 552}, {1, 553}, {1, 554},
    {1, 555}, {1, 556}, {1, 557}, {1, 558}, {1, 559}, {1, 560}, {0, 0},
};

static AnimationFrame s_PcData_8017A9C4[] = {
    {3, 525},  {3, 3598}, {3, 4111}, {3, 4624}, {3, 5137}, {3, 5650},
    {3, 6163}, {3, 6676}, {3, 7189}, {3, 6678}, {3, 6167}, {3, 5656},
    {3, 5145}, {3, 4634}, {3, 4123}, {3, 3612}, {0, 0},
};

static AnimationFrame s_PcData_8017A998[] = {
    {2, 1539}, {2, 1540}, {2, 1541}, {2, 1542}, {2, 1543}, {2, 1544},
    {2, 2057}, {2, 522},  {2, 523},  {2, 524},  {0, 0},
};

static AnimationFrame s_PcData_8017AAA4[] = {
    {2, 561},
    {2, 562},
    {2, 563},
    {65535, 0},
};

static AnimationFrame s_PcData_8017AAB4[] = {
    {2, 1076},
    {2, 1077},
    {2, 1078},
    {65535, 0},
};

static AnimationFrame s_PcData_8017AAC4[] = {
    {2, 563},
    {2, 562},
    {2, 561},
    {65535, 0},
};

static AnimationFrame s_PcData_8017AAD4[] = {
    {2, 1078},
    {2, 1077},
    {2, 1076},
    {65535, 0},
};

AnimationFrame* D_19A000_8017AB84[] = {
    s_PcData_8017A988,
    s_PcData_8017A990,
    s_PcData_8017AAF0,
    s_PcData_8017AAFC,
    s_PcData_8017AAE4,
    s_PcData_8017AA60,
    s_PcData_8017AA40,
    s_PcData_8017AA08,
    s_PcData_8017A9C4,
    s_PcData_8017A998,
    s_PcData_8017AAA4,
    s_PcData_8017AAB4,
    s_PcData_8017AAC4,
    s_PcData_8017AAD4,
    NULL,
    NULL,
};

static u16 s_PcData_8017A808[] = {
#include "gen/pc_w_058_clut_8017A808.h"
};

u16* g_WeaponCluts[] = {
    s_PcData_8017A808,
};

s32 g_HandId = HAND_ID;

s32 D_19A000_8017BB40 = {0};
