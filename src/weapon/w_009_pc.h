// SPDX-License-Identifier: AGPL-3.0-or-later
// Native definitions for tables retained as PS1 assembly data.

s8 D_43000_8017A9F8[];
static AnimationFrame s_PcData_8017A844[];
static AnimationFrame s_PcData_8017A84C[];
static AnimationFrame s_PcData_8017A9AC[];
static AnimationFrame s_PcData_8017A9B8[];
static AnimationFrame s_PcData_8017A9A0[];
static AnimationFrame s_PcData_8017A91C[];
static AnimationFrame s_PcData_8017A8FC[];
static AnimationFrame s_PcData_8017A8C4[];
static AnimationFrame s_PcData_8017A880[];
static AnimationFrame s_PcData_8017A854[];
static AnimationFrame s_PcData_8017A960[];
static AnimationFrame s_PcData_8017A970[];
static AnimationFrame s_PcData_8017A980[];
static AnimationFrame s_PcData_8017A990[];
AnimationFrame* D_43000_8017AA40[];
s32 D_43000_8017AA78[];
static u16 s_PcData_8017A804[];
u16* g_WeaponCluts[];

s8 D_43000_8017A9F8[] = {
    0,  0,  0,   0,   14, -7, 4,  12, 14, 13, 4,  12, -11, -7, 4,  12, 1,  -5,
    4,  12, -32, -31, 0,  0,  22, -6, 4,  12, 15, -6, 4,   12, 16, -5, 4,  12,
    17, -4, 4,   12,  18, -3, 4,  12, 19, -2, 4,  12, 20,  -1, 4,  12, 21, 0,
    4,  12, 22,  1,   4,  12, 12, -5, 4,  12, 10, -3, 4,   12, 8,  -1, 4,  12,
};

static AnimationFrame s_PcData_8017A844[] = {
    {2, 513},
    {0, 0},
};

static AnimationFrame s_PcData_8017A84C[] = {
    {2, 1026},
    {0, 0},
};

static AnimationFrame s_PcData_8017A9AC[] = {
    {2, 3103},
    {2, 3104},
    {0, 0},
};

static AnimationFrame s_PcData_8017A9B8[] = {
    {3, 8759}, {3, 8760}, {3, 8760}, {3, 8248}, {3, 7736}, {3, 569},
    {3, 570},  {3, 571},  {3, 572},  {3, 573},  {3, 513},  {3, 513},
    {3, 513},  {3, 513},  {3, 513},  {0, 0},
};

static AnimationFrame s_PcData_8017A9A0[] = {
    {4, 541},
    {4, 542},
    {0, 0},
};

static AnimationFrame s_PcData_8017A91C[] = {
    {2, 545}, {2, 546}, {2, 547}, {2, 548}, {2, 549}, {2, 550},
    {2, 551}, {2, 552}, {2, 553}, {2, 554}, {2, 555}, {2, 556},
    {2, 557}, {2, 558}, {2, 559}, {2, 560}, {0, 0},
};

static AnimationFrame s_PcData_8017A8FC[] = {
    {1, 554}, {1, 555}, {1, 556}, {1, 557},
    {1, 558}, {1, 559}, {1, 560}, {0, 0},
};

static AnimationFrame s_PcData_8017A8C4[] = {
    {1, 548}, {1, 549}, {1, 550}, {1, 551}, {1, 552}, {1, 553}, {1, 554},
    {1, 555}, {1, 556}, {1, 557}, {1, 558}, {1, 559}, {1, 560}, {0, 0},
};

static AnimationFrame s_PcData_8017A880[] = {
    {3, 525},  {3, 3598}, {3, 4111}, {3, 4624}, {3, 5137}, {3, 5650},
    {3, 6163}, {3, 6676}, {3, 7189}, {3, 6678}, {3, 6167}, {3, 5656},
    {3, 5145}, {3, 4634}, {3, 4123}, {3, 3612}, {0, 0},
};

static AnimationFrame s_PcData_8017A854[] = {
    {2, 1539}, {2, 1540}, {2, 1541}, {2, 1542}, {2, 1543}, {2, 1544},
    {2, 2057}, {2, 522},  {2, 523},  {2, 524},  {0, 0},
};

static AnimationFrame s_PcData_8017A960[] = {
    {2, 561},
    {2, 562},
    {2, 563},
    {65535, 0},
};

static AnimationFrame s_PcData_8017A970[] = {
    {2, 1076},
    {2, 1077},
    {2, 1078},
    {65535, 0},
};

static AnimationFrame s_PcData_8017A980[] = {
    {2, 563},
    {2, 562},
    {2, 561},
    {65535, 0},
};

static AnimationFrame s_PcData_8017A990[] = {
    {2, 1078},
    {2, 1077},
    {2, 1076},
    {65535, 0},
};

AnimationFrame* D_43000_8017AA40[] = {
    s_PcData_8017A844, s_PcData_8017A84C, s_PcData_8017A9AC, s_PcData_8017A9B8,
    s_PcData_8017A9A0, s_PcData_8017A91C, s_PcData_8017A8FC, s_PcData_8017A8C4,
    s_PcData_8017A880, s_PcData_8017A854, s_PcData_8017A960, s_PcData_8017A970,
    s_PcData_8017A980, s_PcData_8017A990,
};

s32 D_43000_8017AA78[] = {
    0,    512,  1024, 1536, 2048, 2560, 3072, 3584,
    4096, 4608, 5120, 5632, 6144, 6656, 7168, 7680,
};

static u16 s_PcData_8017A804[] = {
#include "gen/pc_w_009_clut_8017A804.h"
};

u16* g_WeaponCluts[] = {
    s_PcData_8017A804,
    s_PcData_8017A804,
};

s32 g_HandId = HAND_ID;
