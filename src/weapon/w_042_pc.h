// SPDX-License-Identifier: AGPL-3.0-or-later
// Native definitions for tables retained as PS1 assembly data.

AnimationFrame D_12A000_8017A604[];
AnimationFrame D_12A000_8017A620[];
AnimationFrame D_12A000_8017A684[];
AnimationFrame D_12A000_8017A6AC[];
AnimationFrame D_12A000_8017A6B4[];
AnimationFrame D_12A000_8017A6BC[];
FrameProperty D_12A000_8017A6DC[];
s32 D_12A000_8017A6F4[];
AnimationFrame D_12A000_8017A704[];
s32 D_12A000_8017A740[];
s32 D_12A000_8017A74C[];
static u16 s_PcData_8017A3E4[];
u16* g_WeaponCluts[];

AnimationFrame D_12A000_8017A604[] = {
    {6, 513}, {4, 514}, {4, 515}, {6, 516}, {5, 517}, {6, 518}, {0, 0},
};

AnimationFrame D_12A000_8017A620[] = {
    {5, 513},  {5, 514}, {5, 519},  {6, 520},   {5, 521}, {5, 522},  {5, 523},
    {16, 524}, {5, 525}, {5, 526},  {5, 521},   {5, 522}, {5, 523},  {16, 524},
    {5, 525},  {5, 526}, {5, 521},  {5, 522},   {5, 523}, {31, 524}, {4, 516},
    {4, 517},  {4, 518}, {64, 513}, {65535, 0},
};

AnimationFrame D_12A000_8017A684[] = {
    {2, 23}, {1, 24}, {2, 25}, {1, 26}, {1, 27},
    {1, 28}, {1, 29}, {1, 25}, {1, 24}, {65535, 0},
};

AnimationFrame D_12A000_8017A6AC[] = {
    {128, 2581},
    {65535, 0},
};

AnimationFrame D_12A000_8017A6B4[] = {
    {128, 22},
    {65535, 0},
};

AnimationFrame D_12A000_8017A6BC[] = {
    {8, 513}, {6, 6}, {5, 5}, {6, 4}, {4, 3}, {4, 2}, {6, 1}, {0, 1},
};

FrameProperty D_12A000_8017A6DC[] = {
    {0, 0, 0, 0},     {-1, 0, 4, 18}, {-64, -40, 0, 0},
    {-64, -64, 0, 0}, {0, 0, 7, 7},   {0, 0, 3, 3},
};

s32 D_12A000_8017A6F4[] = {
    57344,
    65536,
    49152,
    73728,
};

AnimationFrame D_12A000_8017A704[] = {
    {2, 1}, {2, 2}, {2, 3}, {2, 4}, {2, 5}, {2, 4}, {2, 3},     {2, 4},
    {2, 3}, {2, 4}, {2, 5}, {1, 6}, {1, 7}, {1, 8}, {65535, 0},
};

s32 D_12A000_8017A740[] = {
    -65536,
    -98304,
    -131072,
};

s32 D_12A000_8017A74C[] = {
    -262144,
    -294912,
    -327680,
};

static u16 s_PcData_8017A3E4[] = {
#include "gen/pc_w_042_clut_8017A3E4.h"
};

u16* g_WeaponCluts[] = {
    s_PcData_8017A3E4,
};

s32 g_HandId = HAND_ID;
