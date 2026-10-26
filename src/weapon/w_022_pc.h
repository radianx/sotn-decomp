// SPDX-License-Identifier: AGPL-3.0-or-later
// Native definitions for tables retained as PS1 assembly data.

AnimationFrame D_9E000_8017A760[];
AnimationFrame D_9E000_8017A77C[];
AnimationFrame D_9E000_8017A800[];
static u16 s_PcData_8017A540[];
u16* g_WeaponCluts[];

AnimationFrame D_9E000_8017A760[] = {
    {2, 1}, {2, 2}, {2, 3}, {2, 4}, {2, 5}, {2, 6}, {65535, 0},
};

AnimationFrame D_9E000_8017A77C[] = {
    {1, 7},  {1, 8},  {1, 9},  {3, 10}, {1, 8},     {1, 11}, {2, 12},
    {2, 13}, {2, 14}, {2, 15}, {2, 16}, {2, 17},    {2, 18}, {2, 19},
    {2, 20}, {2, 21}, {2, 22}, {3, 23}, {4, 24},    {2, 29}, {15, 25},
    {1, 26}, {1, 27}, {1, 26}, {1, 27}, {2, 26},    {2, 27}, {2, 26},
    {3, 27}, {3, 26}, {4, 27}, {5, 26}, {65535, 0},
};

AnimationFrame D_9E000_8017A800[] = {
    {2, 28},
    {0, 0},
};

static u16 s_PcData_8017A540[] = {
#include "gen/pc_w_022_clut_8017A540.h"
};

u16* g_WeaponCluts[] = {
    s_PcData_8017A540,
    s_PcData_8017A540,
};

s32 g_HandId = HAND_ID;
