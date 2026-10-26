// SPDX-License-Identifier: AGPL-3.0-or-later
// Native definitions for tables retained as PS1 assembly data.

static u16 s_PcData_8017A7A4[];
static u16 s_PcData_8017A7B8[];
static u16 s_PcData_8017A7C8[];
static u16 s_PcData_8017A7D4[];
static u16* s_PcData_8017A8B4[];
static s8 s_PcData_8017A848[];
static u16 s_PcData_8017A7DC[];
static u16 s_PcData_8017A7F0[];
static u16 s_PcData_8017A804[];
static u16 s_PcData_8017A818[];
static u16 s_PcData_8017A828[];
static u16 s_PcData_8017A838[];
static u16* s_PcData_8017A8D0[];
WeaponAnimation D_DD000_8017A8EC[];
static u16 s_PcData_8017A704[];
u16* g_WeaponCluts[];

static u16 s_PcData_8017A7A4[] = {
    513, 1026, 1539, 1541, 1539, 1026, 2052, 2566, 65535, 0,
};

static u16 s_PcData_8017A7B8[] = {
    3079, 4105, 4618, 4619, 4618, 4105, 3592, 65535,
};

static u16 s_PcData_8017A7C8[] = {
    5132, 5645, 5646, 5645, 5132, 65535,
};

static u16 s_PcData_8017A7D4[] = {
    6159,
    6672,
    6159,
    65535,
};

static u16* s_PcData_8017A8B4[] = {
    s_PcData_8017A7A4, s_PcData_8017A7A4, s_PcData_8017A7B8, s_PcData_8017A7B8,
    s_PcData_8017A7C8, s_PcData_8017A7D4, s_PcData_8017A7D4,
};

static s8 s_PcData_8017A848[] = {
    0,   0,   0,  0,  12,  -15, 8,  8,  17,  -15, 12, 5, 20, -13, 21, 4,
    16,  -12, 5,  4,  -32, -31, 0,  0,  6,   3,   8,  8, 8,  6,   5,  4,
    11,  3,   11, 5,  13,  4,   21, 4,  14,  -15, 14, 5, 21, -12, 21, 8,
    7,   -9,  11, 9,  19,  1,   12, 13, -9,  -15, 4,  4, 17, -14, 22, 4,
    -15, 1,   6,  4,  11,  3,   22, 4,  8,   11,  15, 7, 13, 18,  17, 5,
    -11, -17, 6,  4,  18,  -16, 21, 7,  -20, -19, 5,  4, 14, -14, 21, 7,
    15,  -2,  18, 12, 21,  0,   15, 11, 12,  1,   15, 4,
};

static u16 s_PcData_8017A7DC[] = {
    7185, 7698, 7699, 2580, 2581, 2582, 2583, 2584, 2073, 65535,
};

static u16 s_PcData_8017A7F0[] = {
    8218, 8731, 8732, 8733, 2590, 2595, 2596, 2597, 2598, 65535,
};

static u16 s_PcData_8017A804[] = {
    8218, 9247, 9760, 9761, 2594, 2595, 2596, 2597, 2598, 65535,
};

static u16 s_PcData_8017A818[] = {
    10279, 10792, 10793, 10794, 2603, 2604, 65535, 0,
};

static u16 s_PcData_8017A828[] = {
    11309, 11822, 11823, 11824, 2609, 2614, 65535, 0,
};

static u16 s_PcData_8017A838[] = {
    11309, 12338, 12851, 13364, 2613, 2614, 65535, 0,
};

static u16* s_PcData_8017A8D0[] = {
    s_PcData_8017A7DC, s_PcData_8017A7DC, s_PcData_8017A7F0, s_PcData_8017A804,
    s_PcData_8017A818, s_PcData_8017A828, s_PcData_8017A838,
};

WeaponAnimation D_DD000_8017A8EC[] = {
    {s_PcData_8017A8B4, s_PcData_8017A848, 0, 1547, 111, 2, 0},
    {s_PcData_8017A8D0, s_PcData_8017A848, 0, 1547, 118, 3, 0},
};

static u16 s_PcData_8017A704[] = {
#include "gen/pc_w_031_clut_8017A704.h"
};

u16* g_WeaponCluts[] = {
    s_PcData_8017A704,
    s_PcData_8017A704,
};

s32 g_HandId = HAND_ID;
