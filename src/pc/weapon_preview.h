// SPDX-License-Identifier: AGPL-3.0-or-later
#ifndef PC_WEAPON_PREVIEW_H
#define PC_WEAPON_PREVIEW_H
#include <game.h>
typedef struct PcWeaponPreview {
    s16** sprites;
    int spriteCount;
    const WeaponAnimation* attacks;
    int attackCount;
    AnimationFrame** shield;
    int shieldCount;
    int draBank;
} PcWeaponPreview;
const PcWeaponPreview* PcGetWeaponPreview(void);
#endif
