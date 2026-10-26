// SPDX-License-Identifier: AGPL-3.0-or-later
// Native definitions for tables retained as PS1 assembly data.

s8 D_C8000_8017AA98[];
static AnimationFrame s_PcData_8017A8E4[];
static AnimationFrame s_PcData_8017A8EC[];
static AnimationFrame s_PcData_8017AA4C[];
static AnimationFrame s_PcData_8017AA58[];
static AnimationFrame s_PcData_8017AA40[];
static AnimationFrame s_PcData_8017A9BC[];
static AnimationFrame s_PcData_8017A99C[];
static AnimationFrame s_PcData_8017A964[];
static AnimationFrame s_PcData_8017A920[];
static AnimationFrame s_PcData_8017A8F4[];
static AnimationFrame s_PcData_8017AA00[];
static AnimationFrame s_PcData_8017AA10[];
static AnimationFrame s_PcData_8017AA20[];
static AnimationFrame s_PcData_8017AA30[];
AnimationFrame* D_C8000_8017AAE0[];
s16 D_C8000_8017AB18;
s16 D_C8000_8017AB1A;
s32 D_C8000_8017AB1C[];
static u16 s_PcData_8017A804[];
u16* g_WeaponCluts[];

s8 D_C8000_8017AA98[] = {
    0,  0,  0,   0,   14, -7, 4,  12, 14, 13, 4,  12, -11, -7, 4,  12, 1,  -5,
    4,  12, -32, -31, 0,  0,  22, -6, 4,  12, 15, -6, 4,   12, 16, -5, 4,  12,
    17, -4, 4,   12,  18, -3, 4,  12, 19, -2, 4,  12, 20,  -1, 4,  12, 21, 0,
    4,  12, 22,  1,   4,  12, 12, -5, 4,  12, 10, -3, 4,   12, 8,  -1, 4,  12,
};

static AnimationFrame s_PcData_8017A8E4[] = {
    {2, 513},
    {0, 0},
};

static AnimationFrame s_PcData_8017A8EC[] = {
    {2, 1026},
    {0, 0},
};

static AnimationFrame s_PcData_8017AA4C[] = {
    {2, 3103},
    {2, 3104},
    {0, 0},
};

static AnimationFrame s_PcData_8017AA58[] = {
    {3, 8759}, {3, 8760}, {3, 8760}, {3, 8248}, {3, 7736}, {3, 569},
    {3, 570},  {3, 571},  {3, 572},  {3, 573},  {3, 513},  {3, 513},
    {3, 513},  {3, 513},  {3, 513},  {0, 0},
};

static AnimationFrame s_PcData_8017AA40[] = {
    {4, 541},
    {4, 542},
    {0, 0},
};

static AnimationFrame s_PcData_8017A9BC[] = {
    {2, 545}, {2, 546}, {2, 547}, {2, 548}, {2, 549}, {2, 550},
    {2, 551}, {2, 552}, {2, 553}, {2, 554}, {2, 555}, {2, 556},
    {2, 557}, {2, 558}, {2, 559}, {2, 560}, {0, 0},
};

static AnimationFrame s_PcData_8017A99C[] = {
    {1, 554}, {1, 555}, {1, 556}, {1, 557},
    {1, 558}, {1, 559}, {1, 560}, {0, 0},
};

static AnimationFrame s_PcData_8017A964[] = {
    {1, 548}, {1, 549}, {1, 550}, {1, 551}, {1, 552}, {1, 553}, {1, 554},
    {1, 555}, {1, 556}, {1, 557}, {1, 558}, {1, 559}, {1, 560}, {0, 0},
};

static AnimationFrame s_PcData_8017A920[] = {
    {3, 525},  {3, 3598}, {3, 4111}, {3, 4624}, {3, 5137}, {3, 5650},
    {3, 6163}, {3, 6676}, {3, 7189}, {3, 6678}, {3, 6167}, {3, 5656},
    {3, 5145}, {3, 4634}, {3, 4123}, {3, 3612}, {0, 0},
};

static AnimationFrame s_PcData_8017A8F4[] = {
    {2, 1539}, {2, 1540}, {2, 1541}, {2, 1542}, {2, 1543}, {2, 1544},
    {2, 2057}, {2, 522},  {2, 523},  {2, 524},  {0, 0},
};

static AnimationFrame s_PcData_8017AA00[] = {
    {2, 561},
    {2, 562},
    {2, 563},
    {65535, 0},
};

static AnimationFrame s_PcData_8017AA10[] = {
    {2, 1076},
    {2, 1077},
    {2, 1078},
    {65535, 0},
};

static AnimationFrame s_PcData_8017AA20[] = {
    {2, 563},
    {2, 562},
    {2, 561},
    {65535, 0},
};

static AnimationFrame s_PcData_8017AA30[] = {
    {2, 1078},
    {2, 1077},
    {2, 1076},
    {65535, 0},
};

AnimationFrame* D_C8000_8017AAE0[] = {
    s_PcData_8017A8E4, s_PcData_8017A8EC, s_PcData_8017AA4C, s_PcData_8017AA58,
    s_PcData_8017AA40, s_PcData_8017A9BC, s_PcData_8017A99C, s_PcData_8017A964,
    s_PcData_8017A920, s_PcData_8017A8F4, s_PcData_8017AA00, s_PcData_8017AA10,
    s_PcData_8017AA20, s_PcData_8017AA30,
};

s16 D_C8000_8017AB18 = 0;

s16 D_C8000_8017AB1A = 0;

s32 D_C8000_8017AB1C[] = {
    0,    512,  1024, 1536, 2048, 2560, 3072, 3584,
    4096, 4608, 5120, 5632, 6144, 6656, 7168, 7680,
};

static u16 s_PcData_8017A804[] = {
#include "gen/pc_w_028_clut_8017A804.h"
};

u16* g_WeaponCluts[] = {
    s_PcData_8017A804,
    s_PcData_8017A804,
};

s32 g_HandId = HAND_ID;
