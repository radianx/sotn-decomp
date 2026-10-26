// SPDX-License-Identifier: AGPL-3.0-or-later
// Native definitions for tables retained as PS1 assembly data.

static u16 s_PcData_8017AEA4[];
static u16 s_PcData_8017AEB8[];
static u16 s_PcData_8017AECC[];
static u16 s_PcData_8017AED8[];
static u16 s_PcData_8017AEE4[];
static u16* s_PcData_8017AF28[];
static s8 s_PcData_8017AEF8[];
WeaponAnimation D_B000_8017AF44[];
s16 D_B000_8017AF94[];
u8 D_B000_8017AFB0[];
uvPair D_B000_8017AFB8[];
AnimationFrame D_B000_8017AFC8[];
u16* g_WeaponCluts[];

static u16 s_PcData_8017AEA4[] = {
    512, 1536, 2048, 2048, 2048, 512, 1536, 512, 512, 65535,
};

static u16 s_PcData_8017AEB8[] = {
    512, 2560, 3072, 3072, 3072, 2560, 512, 2560, 65535, 0,
};

static u16 s_PcData_8017AECC[] = {
    3584, 4096, 4096, 4096, 3584, 65535,
};

static u16 s_PcData_8017AED8[] = {
    4608, 5120, 5120, 5120, 4608, 65535,
};

static u16 s_PcData_8017AEE4[] = {
    512, 5632, 512, 512, 512, 512, 512, 512, 512, 65535,
};

static u16* s_PcData_8017AF28[] = {
    s_PcData_8017AEA4, s_PcData_8017AEA4, s_PcData_8017AEB8, s_PcData_8017AEB8,
    s_PcData_8017AECC, s_PcData_8017AED8, s_PcData_8017AEE4,
};

static s8 s_PcData_8017AEF8[] = {
    0,  0,   0,  0, -32, -31, 0,  0, 9,  21, 4,  5, 18, -13, 5,  7,
    18, -11, 17, 7, 11,  5,   5,  7, 12, 7,  16, 7, 15, -14, 5,  7,
    18, -10, 19, 7, 6,   -10, 12, 7, 19, 6,  8,  8, 21, 12,  11, 9,
};

WeaponAnimation D_B000_8017AF44[] = {
    {s_PcData_8017AF28, s_PcData_8017AEF8, 414, 1548, 36, 1, 0},
    {s_PcData_8017AF28, s_PcData_8017AEF8, 353, 1548, 36, 1, 0},
    {s_PcData_8017AF28, s_PcData_8017AEF8, 360, 1548, 36, 1, 0},
    {s_PcData_8017AF28, s_PcData_8017AEF8, 354, 1548, 36, 1, 0},
    {s_PcData_8017AF28, s_PcData_8017AEF8, 354, 1548, 36, 1, 0},
};

s16 D_B000_8017AF94[] = {
    18, -13, 18, -13, 11, 5, 11, 5, 20, -12, 15, 1, 19, 6,
};

u8 D_B000_8017AFB0[] = {
    0, 32, 32, 80, 80, 32, 32, 0,
};

uvPair D_B000_8017AFB8[] = {
    {24, 80}, {40, 80}, {24, 96}, {40, 96},
    {0, 64},  {64, 64}, {0, 112}, {64, 112},
};

AnimationFrame D_B000_8017AFC8[] = {
    {1, 1}, {1, 2}, {1, 3}, {1, 4}, {1, 5}, {1, 6}, {1, 7}, {1, 8}, {0, 0},
};

u16* g_WeaponCluts[] = {
    NULL,
    NULL,
};

s32 g_HandId = HAND_ID;
