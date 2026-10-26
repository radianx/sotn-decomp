// SPDX-License-Identifier: AGPL-3.0-or-later
// Native definitions for tables retained as PS1 assembly data.

AnimationFrame D_82000_8017A6A8[];
AnimationFrame D_82000_8017A6E4[];
AnimationFrame D_82000_8017A724[];
static u16 s_PcData_8017A488[];
u16* g_WeaponCluts[];

AnimationFrame D_82000_8017A6A8[] = {
    {1, 1}, {1, 2},  {2, 3},  {2, 4},  {2, 5},  {2, 6},  {2, 7},     {2, 8},
    {2, 9}, {2, 10}, {2, 11}, {4, 10}, {2, 12}, {2, 13}, {65535, 0},
};

AnimationFrame D_82000_8017A6E4[] = {
    {1, 14}, {1, 15}, {1, 14}, {1, 16}, {1, 14}, {1, 20}, {1, 17}, {1, 14},
    {1, 18}, {1, 14}, {1, 19}, {1, 14}, {1, 20}, {0, 0},  {1, 21}, {0, 0},
};

AnimationFrame D_82000_8017A724[] = {
    {1, 22},
    {1, 23},
    {0, 0},
};

static u16 s_PcData_8017A488[] = {
#include "gen/pc_w_018_clut_8017A488.h"
};

u16* g_WeaponCluts[] = {
    s_PcData_8017A488,
    s_PcData_8017A488,
};

s32 g_HandId = HAND_ID;
