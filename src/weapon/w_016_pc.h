// SPDX-License-Identifier: AGPL-3.0-or-later
// Native definitions for tables retained as PS1 assembly data.

AnimationFrame D_74000_8017A5B0[];
static u16 s_PcData_8017A2B0[];
u16* g_WeaponCluts[];

AnimationFrame D_74000_8017A5B0[] = {
    {1, 1}, {1, 2}, {1, 3}, {1, 4}, {1, 5}, {1, 4}, {1, 3},     {1, 4},
    {1, 3}, {1, 4}, {1, 5}, {1, 6}, {1, 7}, {1, 8}, {65535, 0},
};

static u16 s_PcData_8017A2B0[] = {
#include "gen/pc_w_016_clut_8017A2B0.h"
};

u16* g_WeaponCluts[] = {
    s_PcData_8017A2B0,
    s_PcData_8017A2B0,
};

s32 g_HandId = HAND_ID;

s32 D_74000_8017BD74 = {0};
