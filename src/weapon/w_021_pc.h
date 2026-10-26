// SPDX-License-Identifier: AGPL-3.0-or-later
// Native definitions for tables retained as PS1 assembly data.

static u16 s_PcData_8017A564[];
u16* g_WeaponCluts[];

static u16 s_PcData_8017A564[] = {
#include "gen/pc_w_021_clut_8017A564.h"
};

u16* g_WeaponCluts[] = {
    s_PcData_8017A564,
    s_PcData_8017A564,
    s_PcData_8017A564,
    s_PcData_8017A564,
};

s32 g_HandId = HAND_ID;
