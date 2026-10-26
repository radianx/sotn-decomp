// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rno4.h"

#define EntityBombKnight func_us_801BBE58_from_rnz1
#define EntityThrownBomb func_us_801BC650_from_rnz1
#define EntityBombFuseSparks func_us_801BCA5C_from_rnz1
#define EntityThrownRock func_us_801BCB9C_from_rnz1
#define EntityRockPiece func_us_801BCD80_from_rnz1
#define EntityKnightDeathParts func_us_801BCE4C_from_rnz1
#define EntityBombKnightArm func_us_801BCFC8_from_rnz1
#define E_BOMB_KNIGHT E_UNK_48
#define E_THROWN_BOMB E_UNK_49
#define E_DEATH_PARTS E_UNK_4A
#define E_FUSE_SPARKS E_UNK_4B
#define E_THROWN_ROCK E_UNK_4C
#define E_ROCK_PIECE E_UNK_4D
#define E_BOMB_KNIGHT_ARM E_UNK_4E
#define g_EInitBomb D_us_80180BCC
#define g_EInitKnightDebris D_us_80180BD8
#define g_EInitRock D_us_80180BE4
#define BOMB_EXPLOSION_ANIMSET ANIMSET_OVL(6)
#define BOMB_EXPLOSION_SPRITE_BANK 0x4E
#include "../e_bomb_knight.h"
