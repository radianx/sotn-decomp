// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../../st/rare/rare.h"
#include <cutscene.h>

static u8 s_PcData_80180808[];
static u8 s_PcData_8018080C[];
static u8 s_PcData_80180818[];
static u8 s_PcData_8018081C[];
static u8 s_PcData_80180820[];
ObjInit2 BackgroundBlockInit[];
u16 g_RedDoorTiles[2][8];

static u8 s_PcData_80180808[] = {
    16,
    11,
    0,
    0,
};

static u8 s_PcData_8018080C[] = {
    8, 12, 8, 13, 8, 14, 8, 15, 8, 16, 0, 0,
};

static u8 s_PcData_80180818[] = {
    16,
    19,
    255,
    0,
};

static u8 s_PcData_8018081C[] = {
    16,
    13,
    255,
    0,
};

static u8 s_PcData_80180820[] = {
    16,
    14,
    255,
    0,
};

ObjInit2 BackgroundBlockInit[] = {
    {32770, 105, 0, 0, 0, 0, 0, 0, s_PcData_80180808},
    {32770, 105, 0, 0, 0, 0, 48, 0, s_PcData_8018080C},
    {32770, 108, 0, 0, 0, 0, 0, 0, s_PcData_80180818},
    {32770, 108, 0, 0, 0, 0, 0, 0, s_PcData_8018081C},
    {32770, 108, 0, 0, 0, 0, 0, 0, s_PcData_80180820},
};

u16 g_RedDoorTiles[2][8] = {
    50, 51, 50, 49, 456, 614, 456, 449, 53, 54, 53, 52, 459, 617, 459, 452,
};
