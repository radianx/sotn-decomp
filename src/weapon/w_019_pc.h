// SPDX-License-Identifier: AGPL-3.0-or-later
// Native definitions for tables retained as PS1 assembly data.

AnimationFrame D_89000_8017A52C[];
static u16 s_PcData_8017A30C[];
u16* g_WeaponCluts[];

AnimationFrame D_89000_8017A52C[] = {
    {1, 1}, {1, 2}, {1, 3}, {1, 4}, {2, 5}, {64, 6}, {65535, 0},
};

static u16 s_PcData_8017A30C[] = {
#include "gen/pc_w_019_clut_8017A30C.h"
};

u16* g_WeaponCluts[] = {
    s_PcData_8017A30C,
    s_PcData_8017A30C,
};

s32 g_HandId = HAND_ID;
