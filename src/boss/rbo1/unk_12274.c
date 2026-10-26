// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rbo1.h"

extern EInit g_EInitBeezelbub801804A0;
extern s16 D_us_801806D8[];
extern u8 D_us_8018084C[];
extern EInit g_EInitBeezelbub;
extern s32 D_us_80180630;
extern s32 D_us_80180634;
extern s16 D_us_8018063C[];
extern s16 D_us_801806F0[];
extern s16 D_us_8018070C[];
extern unkStr_801CDD80 D_us_80180770[];
extern unkStr_801CDD80 D_us_801807D0[];
extern u8 D_us_80180840[];
extern u8 D_us_8018088C[][4];
extern u8 D_us_801808D0[];
void func_801CDF1C(s16*, unkStr_801CDD80*, s32);
void func_801CE1E8(s32);
void polarPlacePartsWithAngvel(s16*);
void polarPlacePartsList(s16*);

extern s32 g_BossMgrState;
void func_us_8019D260_from_rcen(void);

extern u8* g_eBreakableAnimations[];
extern u8 g_eBreakableHitboxes[];
extern u8 g_eBreakableExplosionTypes[];
extern u16 g_eBreakableanimSets[];
extern u8 blend_modes[];

#include "../../st/e_breakable.h"

void func_us_801923A8(Entity* self) {
    Collider unused; // !FAKE: Preserves the original stack frame.
    Entity* entity;
    Entity* previous;
    u8* hitbox;
    s16* init;
    s16* offsets;
    s32 i;
    s32 value;
    s32 posY;

    FntPrint("boss_life %x\n", D_us_80180630);
    if ((self->flags & FLAG_DEAD) && self->step != 4) {
        func_801CE1E8(4);
    }
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitBeezelbub);
        self->animCurFrame = 20;
        D_us_80180634 = 0;
        self->ext.beelzebub.previousHitPoints = self->hitPoints;
        D_us_80180630 = self->hitPoints;
        hitbox = D_us_8018088C[0];
        hitbox += D_us_801808D0[self->animCurFrame] * 4;
        init = D_us_8018063C;
        self->hitboxOffX = (s8)hitbox[0];
        previous = self;
        self->hitboxOffY = (s8)hitbox[1];
        self->hitboxWidth = hitbox[2];
        self->hitboxHeight = hitbox[3];
        i = 0;
        while (*init) {
            entity = self + init[0];
            CreateEntityFromCurrentEntity(E_UNK_17, entity);
            entity->ext.beelzebub.length = init[2];
            entity->ext.beelzebub.parent = self + init[1];
            entity->ext.beelzebub.angleOffset = init[5];
            entity->params = i;
            i++;
            entity->zPriority = self->zPriority + init[4];
            entity->nextPart = previous;
            previous = entity;
            init += 6;
        }
        self->nextPart = previous;
        CreateEntityFromCurrentEntity(E_UNK_18, self + 24);
        (self + 24)->ext.beelzebub.parent = self;
        func_801CE1E8(1);
        // fallthrough
    case 1:
        polarPlacePartsList(D_us_801806F0);
        if (g_BossMgrState & BOSS_MGR_FIGHT_ON) {
            func_801CE1E8(2);
        }
        break;
    case 2:
    case 3:
        if (!self->ext.beelzebub.timer) {
            g_api.PlaySfx(SFX_BEELZEBUB_FLY_BUZZ);
            value = D_us_80180634 + 2;
            self->ext.beelzebub.timer = 384;
            for (i = 0; i < value; i++) {
                entity = AllocEntity(&g_Entities[128], &g_Entities[152]);
                if (entity != NULL) {
                    CreateEntityFromCurrentEntity(E_UNK_19, entity);
                    entity->params = i & 1;
                    entity->ext.beelzebub.parent = self;
                    entity->posY.i.hi = (i / 2) << 6;
                    entity->rotate = (0x1000 / value) * i;
                    if (i & 1) {
                        entity->posX.i.hi = self->posX.i.hi + 192;
                    } else {
                        entity->posX.i.hi = self->posX.i.hi - 192;
                    }
                    entity->zPriority = self->zPriority;
                }
            }
        }
        offsets = D_us_8018070C;
        self->ext.beelzebub.timer--;
        switch (self->step) {
        case 2:
            AnimateEntity(D_us_80180840, self);
            func_801CDF1C(offsets, D_us_801807D0, 0);
            polarPlacePartsWithAngvel(offsets);
            polarPlacePartsList(D_us_801806F0);
            if (self->hitFlags & 3) {
                g_api.PlaySfx(SFX_BEELZEBUB_PAIN);
                func_801CE1E8(3);
            }
            break;
        case 3:
            func_801CDF1C(offsets, D_us_80180770, 0);
            polarPlacePartsWithAngvel(offsets);
            polarPlacePartsList(D_us_801806F0);
            if (!self->ext.beelzebub.unkB4[0] &&
                !self->ext.beelzebub.unkB0[0]) {
                func_801CE1E8(2);
            }
            break;
        }
        break;
    case 4:
        switch (self->step_s) {
        case 0:
            D_us_80180630 = -1;
            self->hitboxState = 0;
            g_BossMgrState |= BOSS_MGR_DEFEAT;
            self->step_s++;
            self->drawFlags |= ENTITY_ROTATE;
            // fallthrough
        case 1:
            MoveEntity();
            self->velocityY += FIX(0.015625);
            self->rotate += 1;
            if (!(g_Timer & 7)) {
                PlaySfxPositional(SFX_EXPLODE_A);
            }
            if (!(g_Timer & 3)) {
                entity = AllocEntity(&g_Entities[80], &g_Entities[248]);
                if (entity != NULL) {
                    CreateEntityFromEntity(E_UNK_1D, self, entity);
                    entity->posY.i.hi -= Random() & 15;
                    entity->posX.i.hi += (Random() & 0x3F) - 32;
                    entity->zPriority = self->zPriority + 1;
                }
                func_us_8019D260_from_rcen();
            }
            posY = g_Tilemap.scrollY.i.hi + 24;
            if (self->posY.i.hi + posY > 0x1C0) {
                self->ext.beelzebub.timer = 128;
                PlaySfxPositional(SFX_BOSS_LARGE_FLAMES);
                self->step_s++;
            }
            break;
        case 2:
            if (!(g_Timer & 7)) {
                PlaySfxPositional(SFX_EXPLODE_A);
                for (i = 0; i < 12; i++) {
                    entity = AllocEntity(&g_Entities[80], &g_Entities[248]);
                    if (entity != NULL) {
                        CreateEntityFromEntity(E_UNK_1D, self, entity);
                        entity->rotate = ((Random() & 0x7F) * 16) - ROT(90);
                        entity->zPriority = self->zPriority + 1;
                        entity->params = 3;
                    }
                }
            }
            if (!--self->ext.beelzebub.timer) {
                self->ext.beelzebub.timer = 64;
                self->step_s++;
            }
            break;
        case 3:
            if (self->ext.beelzebub.timer < 48) {
                self->animCurFrame = 0;
            }
            entity = AllocEntity(&g_Entities[80], &g_Entities[248]);
            if (entity != NULL) {
                CreateEntityFromEntity(E_UNK_1D, self, entity);
                entity->zPriority = self->zPriority + 1;
                entity->params = 4;
                entity->posY.i.hi += 16;
            }
            if (!--self->ext.beelzebub.timer) {
                self->step_s++;
            }
            break;
        case 4:
            g_BossMgrState |= BOSS_MGR_TERMINATED;
            break;
        }
        break;
    case 255:
        FntPrint("charal %x\n", self->animCurFrame);
        if (g_pads[1].pressed & PAD_SQUARE) {
            if (self->params) {
                break;
            }
            self->animCurFrame++;
            self->params |= 1;
        } else {
            self->params = 0;
        }
        if (g_pads[1].pressed & PAD_CIRCLE) {
            if (self->step_s) {
                break;
            }
            self->animCurFrame--;
            self->step_s |= 1;
        } else {
            self->step_s = 0;
        }
        break;
    }
    offsets = D_us_801806F0;
    while (*offsets) {
        entity = self + *offsets;
        entity->ext.beelzebub.unkA8 = 0;
        offsets++;
    }
    if (!(self->flags & FLAG_DEAD)) {
        if (D_us_80180630 < 0) {
            D_us_80180630 = 1;
        }
        if (D_us_80180630 != self->ext.beelzebub.previousHitPoints &&
            self->step != 3) {
            func_801CE1E8(3);
        }
        value = self->hitPoints - self->ext.beelzebub.previousHitPoints;
        D_us_80180630 += value;
        self->hitPoints = D_us_80180630;
        self->ext.beelzebub.previousHitPoints = self->hitPoints;
    }
}

void func_us_80192C5C(Entity* self) {
    Collider unused; // !FAKE: Preserves the original stack frame.
    Entity* entity;
    u8* hitbox;
    s32 i;
    s32 value;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitBeezelbub801804A0);
        self->ext.beelzebub.previousHitPoints = self->hitPoints;
        self->animCurFrame = D_us_8018063C[self->params * 6 + 3];
        self->drawFlags |= ENTITY_ROTATE;
        hitbox = D_us_8018088C[0];
        hitbox += D_us_801808D0[self->animCurFrame] * 4;
        self->hitboxOffX = (s8)hitbox[0];
        self->hitboxOffY = (s8)hitbox[1];
        self->hitboxWidth = hitbox[2];
        self->hitboxHeight = hitbox[3];
        for (i = 0; i < 3; i++) {
            entity = AllocEntity(&g_Entities[216], &g_Entities[248]);
            if (entity != NULL) {
                CreateEntityFromEntity(E_UNK_1A, self, entity);
                entity->ext.beelzebub.parent = self;
                entity->zPriority = self->zPriority;
            }
        }
        break;
    case 1:
        self->rotate = self->ext.beelzebub.rotate;
        if (!(Random() & 0x3F)) {
            entity = AllocEntity(&g_Entities[112], &g_Entities[128]);
            if (entity != NULL) {
                CreateEntityFromEntity(E_UNK_1B, self, entity);
                entity->zPriority = self->zPriority + 1;
                entity->ext.beelzebub.parent = self;
                entity->posX.i.hi += (Random() & 15) - 8;
                entity->posY.i.hi += (Random() & 15) - 8;
            }
        }
        value = self->hitPoints - self->ext.beelzebub.previousHitPoints;
        D_us_80180630 = value + D_us_80180630;
        self->ext.beelzebub.previousHitPoints = self->hitPoints;
        value = D_us_801806D8[self->params];
        if (D_us_80180630 < value) {
            entity = self->ext.beelzebub.parent;
            if ((entity->flags & FLAG_DEAD) || (self->hitFlags & 3)) {
                D_us_80180634++;
                SetStep(2);
            }
        }
        break;
    case 2:
        entity = AllocEntity(&g_Entities[192], &g_Entities[248]);
        if (entity != NULL) {
            CreateEntityFromEntity(E_UNK_1C, self, entity);
            entity->params = self->animCurFrame;
            entity->zPriority = self->zPriority;
            entity->rotate = self->rotate;
        }
        self->animCurFrame = 0;
        self->hitboxState = 0;
        self->flags |= FLAG_DEAD;
        self->step++;
        return;
    case 3:
        return;
    }
    if (!self->params) {
        AnimateEntity(D_us_8018084C, self);
    }
}
