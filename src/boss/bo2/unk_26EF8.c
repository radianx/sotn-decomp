// SPDX-License-Identifier: AGPL-3.0-or-later
#include "bo2.h"
#ifdef VERSION_PC
#include "../../pc/upgrades.h"
#endif

extern s32 D_us_80180AAC;
extern s32 D_us_80180B74;
extern u8 D_us_80180C28[];
extern u8 D_us_80180C30[];
extern u8 D_us_80180C50[];
extern u8 D_us_80180C8C[];
extern u8 D_us_80180C98[];
extern s32 g_CutsceneFlags;
extern s32 g_SkipCutscene;
extern EInit g_EInitCommon;

void func_us_801A6EF8(Entity* self) {
    Tilemap* tilemap = &g_Tilemap;
    Entity* entity = &PLAYER;
    s16 posX = PLAYER.posX.i.hi + g_Tilemap.scrollX.i.hi;

#ifdef VERSION_PC
    if (g_PcSettings.bugFixes && self->step < 4 && entity->posX.i.hi > 0x40 &&
        (g_Player.status & (PLAYER_STATUS_BAT_FORM | PLAYER_STATUS_MIST_FORM |
                            PLAYER_STATUS_WOLF_FORM))) {
        entity->step = 0;
        entity->step_s = 0;
        entity->animSet = ANIMSET_OVL(0x100);
        entity->animCurFrame = 0;
    }
#endif
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitSpawner);
        self->animSet = 0;
        break;
    case 1:
        if ((posX > 0x60) || self->params) {
            if (!self->params) {
                D_us_80180B74 = 1;
                entity->posX.i.hi = 0x60;
            }
            g_PauseAllowed = false;
            g_unkGraphicsStruct.pauseEnemies = true;
            if (g_Player.status & PLAYER_STATUS_BAT_FORM) {
                g_Player.padSim = PAD_R1;
            } else if (g_Player.status & PLAYER_STATUS_MIST_FORM) {
                g_Player.padSim = PAD_L1;
            } else if (g_Player.status & PLAYER_STATUS_WOLF_FORM) {
                g_Player.padSim = PAD_R2;
            } else {
                g_Player.padSim = 0;
            }
            g_Player.demo_timer = 1;
            if (self->params) {
                self->step = 6;
            } else {
                g_CutsceneFlags |= 1;
                self->step++;
            }
        }
        break;
    case 2:
        g_Player.padSim = 0;
        if (g_Player.status & PLAYER_STATUS_WOLF_FORM) {
            if (g_Timer & 1) {
                g_Player.padSim = PAD_R2;
            }
        } else if (g_CutsceneFlags & 0x80) {
            g_Player.padSim = PAD_RIGHT;
            self->step++;
        }
        g_Player.demo_timer = 1;
        break;
    case 3:
        if (posX < 0xE8) {
            g_Player.padSim = PAD_RIGHT;
        } else {
            g_Player.padSim = 0;
            entity->posX.i.hi = 0xE8 - tilemap->scrollX.i.hi;
            if (g_Status.wornEquipment[RIGHT_HAND_SLOT] != ITEM_MAGIC_MISSILE) {
                AnimateEntity(D_us_80180C8C, self);
                entity->animCurFrame = self->animCurFrame;
            }
            self->step = 4;
        }
        g_Player.demo_timer = 1;
        break;
    case 4:
        if (g_Status.wornEquipment[RIGHT_HAND_SLOT] != ITEM_MAGIC_MISSILE) {
            AnimateEntity(D_us_80180C8C, self);
            entity->animCurFrame = self->animCurFrame;
        }
        g_Player.padSim = 0;
        g_Player.demo_timer = 1;
        if (g_CutsceneFlags & 0x40) {
            SetStep(5);
        }
        break;
    case 5:
        if (!AnimateEntity(D_us_80180C98, self)) {
            g_PauseAllowed = true;
            g_unkGraphicsStruct.pauseEnemies = false;
            D_us_80180AAC = 1;
            DestroyEntity(self);
            return;
        }
        if (g_Status.wornEquipment[RIGHT_HAND_SLOT] != ITEM_MAGIC_MISSILE) {
            entity->animCurFrame = self->animCurFrame;
        }
        g_Player.padSim = 0;
        g_Player.demo_timer = 1;
        break;
    case 6:
        if ((g_Player.status & PLAYER_STATUS_WOLF_FORM) && (g_Timer & 1)) {
            g_Player.padSim = PAD_R2;
        }
        if (g_Player.vram_flag & TOUCHING_GROUND) {
            g_CutsceneFlags |= 1;
            self->step++;
        }
        // @bug The simulated transformation input is cleared immediately.
        g_Player.padSim = 0;
        g_Player.demo_timer = 1;
        break;
    case 7:
        if ((g_Player.status & PLAYER_STATUS_WOLF_FORM) && (g_Timer & 1)) {
            g_Player.padSim = PAD_R2;
        }
        if (g_CutsceneFlags & 0x1000) {
            g_PauseAllowed = true;
            g_unkGraphicsStruct.pauseEnemies = false;
            DestroyEntity(self);
            return;
        }
        // @bug The simulated transformation input is cleared immediately.
        g_Player.padSim = 0;
        g_Player.demo_timer = 1;
        break;
    }
}

void func_us_801A7340(Entity* self) {
    if (g_SkipCutscene && ((u32)(self->step - 3) < 3)) {
        SetStep(6);
    }
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitCommon);
        self->animSet = ANIMSET_OVL(5);
        self->animCurFrame = 1;
        self->unk5A = 0x5A;
        self->palette = 0x22A;
        self->drawFlags = ENTITY_OPACITY;
        self->opacity = 0;
        break;
    case 1:
        if (g_CutsceneFlags & 0x80) {
            SetStep(2);
        }
        break;
    case 2:
        if (self->opacity < 0x80) {
            self->opacity++;
        }
        AnimateEntity(D_us_80180C28, self);
        if (g_CutsceneFlags & 4) {
            self->animCurFrame = 1;
            SetStep(3);
        }
        break;
    case 3:
        if (g_CutsceneFlags & 8) {
            SetStep(4);
        }
        break;
    case 4:
        AnimateEntity(D_us_80180C30, self);
        if (g_CutsceneFlags & 0x20) {
            SetStep(5);
        }
        break;
    case 5:
        AnimateEntity(D_us_80180C50, self);
        if (g_CutsceneFlags & 0x100) {
            self->animCurFrame = 1;
            SetStep(6);
        }
        break;
    case 6:
        AnimateEntity(D_us_80180C28, self);
        if (self->opacity > 8) {
            self->opacity--;
        } else {
            self->step = 7;
            self->palette = PAL_FILL_WHITE;
            self->blendMode = BLEND_SUB | BLEND_TRANSP;
            self->opacity = 0x60;
        }
        break;
    case 7:
        AnimateEntity(D_us_80180C28, self);
        if (self->opacity) {
            self->opacity -= 2;
        } else {
            DestroyEntity(self);
        }
        break;
    }
}

void func_us_801A75B4(Entity* self) {
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitSpawner);
        break;
    case 1:
        if (g_pads[1].tapped & PAD_TRIANGLE) {
            CreateEntityFromCurrentEntity(
                E_CUTSCENE_DIALOGUE, &g_Entities[200]);
            g_Entities[200].params = 1;
            CreateEntityFromCurrentEntity(E_UNK_26, &g_Entities[96]);
            g_Entities[96].params = 1;
            self->step++;
        }
        break;
    }
}
