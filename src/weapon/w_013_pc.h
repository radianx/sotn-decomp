// SPDX-License-Identifier: AGPL-3.0-or-later
// Native definitions for tables retained as PS1 assembly data.

u8 D_5F000_8017A5B0[6][8];
s16 D_5F000_8017A5E0[];
static u16 s_PcData_8017A2B0[];
u16* g_WeaponCluts[];

u8 D_5F000_8017A5B0[6][8] = {
    0,   80, 16,  80, 0,   96, 16,  96, 16,  80, 32,  80, 16,  96, 32,  96,
    112, 64, 128, 64, 112, 80, 128, 80, 112, 48, 120, 48, 112, 56, 120, 56,
    120, 48, 128, 48, 120, 56, 128, 56, 112, 56, 120, 56, 119, 64, 120, 64,
};

s16 D_5F000_8017A5E0[] = {
    1, 2, 3, 4, 5, 6, 7, 8, 7, 6, 5, 4, 3, 2,
};

static u16 s_PcData_8017A2B0[] = {
#include "gen/pc_w_013_clut_8017A2B0.h"
};

u16* g_WeaponCluts[] = {
    s_PcData_8017A2B0,
    s_PcData_8017A2B0,
};

s32 g_HandId = HAND_ID;
