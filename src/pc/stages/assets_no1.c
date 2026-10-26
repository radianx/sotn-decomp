// SPDX-License-Identifier: AGPL-3.0-or-later
#include <stage.h>

#include "no1/gen/sprite_banks.h"
#include "no1/gen/palette_def.h"
u16 pal_158[] = {
#include "no1/gen/pal_158.h"
};
#include "no1/gen/layers.h"
#include "no1/gen/graphics_banks.h"
u8 gfx_44FC[] = {
#include "no1/gen/gfx_44FC.h"
};
u8 gfx_50D8[] = {
#include "no1/gen/gfx_50D8.h"
};
u8 gfx_5FC8[] = {
#include "no1/gen/gfx_5FC8.h"
};
u8 gfx_6BB8[] = {
#include "no1/gen/gfx_6BB8.h"
};
u8 gfx_8054[] = {
#include "no1/gen/gfx_8054.h"
};
u8 gfx_8720[] = {
#include "no1/gen/gfx_8720.h"
};
u8 gfx_90CC[] = {
#include "no1/gen/gfx_90CC.h"
};
u8 gfx_9FD4[] = {
#include "no1/gen/gfx_9FD4.h"
};
u8 gfx_A704[] = {
#include "no1/gen/gfx_A704.h"
};
u8 gfx_B264[] = {
#include "no1/gen/gfx_B264.h"
};
u8 gfx_B9A0[] = {
#include "no1/gen/gfx_B9A0.h"
};
u8 gfx_C4DC[] = {
#include "no1/gen/gfx_C4DC.h"
};
u8 gfx_D2EC[] = {
#include "no1/gen/gfx_D2EC.h"
};
u8 gfx_DF80[] = {
#include "no1/gen/gfx_DF80.h"
};
u8 gfx_E650[] = {
#include "no1/gen/gfx_E650.h"
};
u8 gfx_F584[] = {
#include "no1/gen/gfx_F584.h"
};
u8 gfx_105E4[] = {
#include "no1/gen/gfx_105E4.h"
};
u8 gfx_111F4[] = {
#include "no1/gen/gfx_111F4.h"
};
u8 gfx_11CB0[] = {
#include "no1/gen/gfx_11CB0.h"
};
u8 gfx_1257C[] = {
#include "no1/gen/gfx_1257C.h"
};
u8 gfx_12D20[] = {
#include "no1/gen/gfx_12D20.h"
};
u8 gfx_137E4[] = {
#include "no1/gen/gfx_137E4.h"
};
u8 gfx_141F0[] = {
#include "no1/gen/gfx_141F0.h"
};
u8 gfx_14460[] = {
#include "no1/gen/gfx_14460.h"
};
u8 gfx_14E14[] = {
#include "no1/gen/gfx_14E14.h"
};
u8 gfx_1519C[] = {
#include "no1/gen/gfx_1519C.h"
};
u16 pal_15490[] = {
#include "no1/gen/pal_15490.h"
};
u16 pal_154B0[] = {
#include "no1/gen/pal_154B0.h"
};
u16 pal_154D0[] = {
#include "no1/gen/pal_154D0.h"
};
u16 pal_154F0[] = {
#include "no1/gen/pal_154F0.h"
};
u16 pal_15510[] = {
#include "no1/gen/pal_15510.h"
};
u16 pal_15530[] = {
#include "no1/gen/pal_15530.h"
};
u16 pal_15550[] = {
#include "no1/gen/pal_15550.h"
};
u16 pal_155B0[] = {
#include "no1/gen/pal_155B0.h"
};
u16 pal_155D0[] = {
#include "no1/gen/pal_155D0.h"
};
u16 pal_15650[] = {
#include "no1/gen/pal_15650.h"
};
u16 pal_156B0[] = {
#include "no1/gen/pal_156B0.h"
};
u16 pal_157B0[] = {
#include "no1/gen/pal_157B0.h"
};
u16 pal_157F0[] = {
#include "no1/gen/pal_157F0.h"
};
u16 pal_15810[] = {
#include "no1/gen/pal_15810.h"
};
u16 pal_15830[] = {
#include "no1/gen/pal_15830.h"
};
u16 pal_158B0[] = {
#include "no1/gen/pal_158B0.h"
};
u16 pal_158F0[] = {
#include "no1/gen/pal_158F0.h"
};
u16 pal_15AD0[] = {
#include "no1/gen/pal_15AD0.h"
};
u16 pal_15B90[] = {
#include "no1/gen/pal_15B90.h"
};
u16 pal_15C50[] = {
#include "no1/gen/pal_15C50.h"
};
u16 pal_15CB0[] = {
#include "no1/gen/pal_15CB0.h"
};
u16 pal_15D10[] = {
#include "no1/gen/pal_15D10.h"
};
u16 pal_15D70[] = {
#include "no1/gen/pal_15D70.h"
};
u16 pal_15DB0[] = {
#include "no1/gen/pal_15DB0.h"
};
u16 pal_15EB0[] = {
#include "no1/gen/pal_15EB0.h"
};

#include "no1/gen/no1_tiledef_load.h"
#include "no1/gen/no1_tiledef_no1.h"
#include "no1/gen/no1_tiledef_save.h"
#include "no1/gen/no1_tilemap_0.h"
#include "no1/gen/no1_tilemap_1.h"
#include "no1/gen/no1_tilemap_10.h"
#include "no1/gen/no1_tilemap_11.h"
#include "no1/gen/no1_tilemap_12.h"
#include "no1/gen/no1_tilemap_13.h"
#include "no1/gen/no1_tilemap_14.h"
#include "no1/gen/no1_tilemap_15.h"
#include "no1/gen/no1_tilemap_2.h"
#include "no1/gen/no1_tilemap_3.h"
#include "no1/gen/no1_tilemap_4.h"
#include "no1/gen/no1_tilemap_5.h"
#include "no1/gen/no1_tilemap_6.h"
#include "no1/gen/no1_tilemap_7.h"
#include "no1/gen/no1_tilemap_8.h"
#include "no1/gen/no1_tilemap_9.h"
