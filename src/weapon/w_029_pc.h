// SPDX-License-Identifier: AGPL-3.0-or-later
// Native definitions for tables retained as PS1 assembly data.

s32 D_CF000_8017AC78;
s32 D_CF000_8017ACC0;
u16 D_CF000_8017ACF8[];
u16 D_CF000_8017AD04[];
u16 D_CF000_8017AD10[];
AnimationFrame D_CF000_8017AD24[];
static u16 s_PcData_8017A884[];
u16* g_WeaponCluts[];

s32 D_CF000_8017AC78 = 0;

s32 D_CF000_8017ACC0 = -2145932604;

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
