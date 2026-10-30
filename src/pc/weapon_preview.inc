// SPDX-License-Identifier: AGPL-3.0-or-later
// Included after the weapon source to expose its original, read-only tables.
#include "weapon_preview.h"
const PcWeaponPreview* PcGetWeaponPreview(void) {
    static const PcWeaponPreview data = {
#if !defined(PC_PREVIEW_NO_SPRITES) && !defined(PC_PREVIEW_DRA_BANK)
        .sprites = (s16**)g_Animset,
        .spriteCount = LEN(g_Animset),
#endif
#ifdef PC_PREVIEW_ATTACKS
        .attacks = PC_PREVIEW_ATTACKS,
        .attackCount = LEN(PC_PREVIEW_ATTACKS),
#endif
#ifdef PC_PREVIEW_SHIELD
        .shield = PC_PREVIEW_SHIELD,
        .shieldCount = LEN(PC_PREVIEW_SHIELD),
#endif
#ifdef PC_PREVIEW_DRA_BANK
        .draBank = PC_PREVIEW_DRA_BANK,
#else
        .draBank = 0,
#endif
    };
    return &data;
}
