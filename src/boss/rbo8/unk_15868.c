// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rbo8.h"

void func_801CE3FC(s16* offsets) {
    Entity* entity;
    s32 i;

    for (i = 0; i < 4; i++) {
        entity = g_CurrentEntity + offsets[i];
        polarPlacePart(entity);
    }
    offsets += 4;

    while (*offsets) {
        if (*offsets != 0xFF) {
            entity = g_CurrentEntity + *offsets;
            polarPlacePart(entity);
        }
        offsets++;
    }
}

void func_us_80195938(void) {
    Primitive* prim;
    s16 angle;
    s16 hide;
    u16 drawMode;

    prim = g_CurrentEntity->ext.prim;
    prim->x0 = (g_CurrentEntity + 1)->posX.i.hi;
    prim->y0 = (g_CurrentEntity + 1)->posY.i.hi;
    prim->x1 = (g_CurrentEntity + 12)->posX.i.hi;
    prim->y1 = (g_CurrentEntity + 12)->posY.i.hi;
    prim->x2 = (g_CurrentEntity + 15)->posX.i.hi;
    prim->y2 = (g_CurrentEntity + 15)->posY.i.hi;
    angle = (g_CurrentEntity + 15)->ext.GH_Props.rotate;
    if (g_CurrentEntity->facingLeft) {
        prim->x2 -= (rcos(angle) * 11) >> 12;
    } else {
        prim->x2 += (rcos(angle) * 11) >> 12;
    }
    prim->y2 += (rsin(angle) * 10) >> 12;
    prim->clut = g_CurrentEntity->palette & 0xFFF;
    drawMode = prim->drawMode & ~DRAW_COLORS;
    prim->drawMode = drawMode;
    if (g_CurrentEntity->facingLeft) {
        hide = prim->x1 < prim->x2;
    } else {
        hide = prim->x1 > prim->x2;
    }
    if (hide) {
        prim->drawMode = drawMode | DRAW_COLORS;
    }
}

static void func_801D0B40(void) {
    Entity* ent;
    Entity* parent;

    ent = g_CurrentEntity + 7;
    parent = ent->ext.GH_Props.parent;
    ent->ext.GH_Props.rotate = parent->ext.GH_Props.rotate + 0x100;

    ent = g_CurrentEntity + 11;
    parent = ent->ext.GH_Props.parent;
    ent->ext.GH_Props.rotate = parent->ext.GH_Props.rotate + 0x180;
}

extern s32 abs(s32 value);

#include "func_us_80195ad8.h"

extern EInit g_EInitGalamothLvl50;
extern s32 D_us_80180C0C;
extern s16 D_us_80180C10[];
extern u8 D_us_80180C88[][4];
extern s16 D_us_80180CD0[];
extern s16 D_us_80180D70[];
extern s16 D_us_80180D90[];
extern s16 D_us_80180DB0[];
extern s16 D_us_80180DD0[];
extern s16 D_us_80180DE8[];
extern s16 D_us_80180E00[];
extern s16 D_us_80180E10[];
extern s16 D_us_80180F28[];
extern s16 D_us_801811D8[];
// !FAKE: The boss treats the two prize-drop entries as one flag word.
extern s32 PrizeDrops;
void func_801CDD00(Entity* entity, s16 angle, s16 frames);
void func_801CDE10(s16* offsets);
void func_801CDF1C(s16* offsets, unkStr_801CDD80* animation, s32 index);
void func_801CE1E8(s32 step);
void func_801CE228(void);
void func_801D0A00(s16* offsets);
void func_us_801955A0(Entity* self, Collider* collider);
s32 func_us_801955F8(Entity* self, s32 facingLeft);
void polarPlacePartsList(s16* offsets);
void polarPlacePartsWithAngvel(s16* offsets);
extern unkStr_801CDD80 D_us_80180EBC[];
extern unkStr_801CDD80 D_us_80180ECC[];
extern unkStr_801CDD80 D_us_80180F10[];
extern unkStr_801CDD80 D_us_80180F40[];
extern unkStr_801CDD80 D_us_80181014[];
extern unkStr_801CDD80 D_us_801810E8[];
extern unkStr_801CDD80 D_us_80181120[];
extern unkStr_801CDD80 D_us_801811A8[];
extern unkStr_801CDD80 D_us_80181208[];
extern unkStr_801CDD80 D_us_80181258[];
extern unkStr_801CDD80 D_us_801812B0[];
extern unkStr_801CDD80 D_us_801812C8[];
extern unkStr_801CDD80 D_us_80181318[];
extern unkStr_801CDD80 D_us_80181378[];
extern unkStr_801CDD80 D_us_801813B0[];
extern unkStr_801CDD80 D_us_801814A8[];
extern unkStr_801CDD80 D_us_801814C8[];
extern unkStr_801CDD80 D_us_80181518[];
extern unkStr_801CDD80 D_us_80181588[];
extern unkStr_801CDD80 D_us_801815DC[];
extern unkStr_801CDD80 D_us_801816D4[];
extern unkStr_801CDD80 D_us_801816EC[];
extern unkStr_801CDD80 D_us_80181714[];
extern unkStr_801CDD80 D_us_80181734[];
extern unkStr_801CDD80 D_us_80181744[];

void func_us_80195D80(Entity* self) {
    Collider collider;
    Entity* entity;
    Entity* previous;
    Primitive* prim;
    s16* offsets;
    s16* parts;
    s16 angle;
    s16 tempAngle;
    s32 primIndex;
    s32 value;

    FntPrint("step %x\n", self->step);
    FntPrint("step_s %x\n", self->step_s);
    if ((self->step & 1) && (self->hitFlags & 3)) {
        func_801CE1E8(24);
    }
    if ((self->flags & FLAG_DEAD) && self->step < 32) {
        for (offsets = D_us_80180D70; *offsets; offsets++) {
            entity = self + *offsets;
            entity->hitboxState = 0;
        }
        self->hitboxState = 0;
        D_us_80180C0C = 1;
        if ((self + 16)->ext.galamoth.collision ||
            (self + 13)->ext.galamoth.collision) {
            func_801CE1E8(32);
        }
    }
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitGalamothLvl50);
        self->hitboxOffX = (s8)D_us_80180C88[7][0];
        self->animCurFrame = 7;
        self->hitboxOffY = (s8)D_us_80180C88[7][1];
        self->hitboxWidth = D_us_80180C88[7][2];
        self->hitboxHeight = D_us_80180C88[7][3];
        primIndex = g_api.AllocPrimitives(PRIM_GT3, 1);
        if (primIndex == -1) {
            self->step = 0;
            return;
        }
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.galamoth.prim = prim;
        self->flags |= FLAG_HAS_PRIMS;
        prim->tpage = 0x12;
        prim->clut = 0x200;
        prim->u0 = 0xF9;
        prim->v0 = 2;
        prim->u1 = 0xD1;
        prim->v1 = 0x2B;
        prim->u2 = 0xF9;
        prim->v2 = 0x2B;
        PGREY(prim, 0) = 0x10;
        PGREY(prim, 1) = 0x40;
        PGREY(prim, 2) = 0x40;
        prim->priority = self->zPriority;
        prim->drawMode = DRAW_UNK02;
        // fallthrough
    case 1:
        if (UnkCollisionFunc3(D_us_80180C10) & 1) {
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            self->step++;
        }
        break;
    case 2:
        parts = D_us_80180CD0;
        previous = self;
        while (*parts) {
            entity = self + parts[0];
            CreateEntityFromCurrentEntity(E_UNK_17, entity);
            entity->ext.galamoth.length = parts[2];
            entity->ext.galamoth.parent = self + parts[1];
            entity->params = parts[3];
            entity->zPriority = self->zPriority + parts[4];
            entity->nextPart = previous;
            previous = entity;
            previous->parent = self;
            parts += 5;
        }
        self->nextPart = previous;
        self->parent = NULL;
        self->step++;
        // fallthrough
    case 3:
        func_801CE228();
        self->ext.galamoth.activeFoot = 0;
        func_801CE1E8(4);
        break;
    case 4:
        offsets = D_us_80180DB0;
        self->ext.galamoth.unk8B = 0;
        switch (self->step_s) {
        case 0:
            func_801CDF1C(offsets, D_us_80180EBC, 0);
            func_801CDE10(offsets);
            func_801D0A00(offsets);
            polarPlacePartsList(D_us_80180D70);
            self->step_s++;
            break;
        case 1:
            if (self->hitFlags || (PrizeDrops & 1)) {
                self->step_s++;
            }
            break;
        case 2:
            PrizeDrops |= 1;
            self->step_s++;
            break;
        case 3:
            func_801CDF1C(offsets, D_us_80180ECC, 0);
            func_801CDE10(offsets);
            func_801D0A00(offsets);
            polarPlacePartsList(D_us_80180D70);
            if (!self->ext.galamoth.unkB4[0] && !self->ext.galamoth.unkB0[0]) {
                func_us_80195AD8();
            }
            break;
        }
        break;
    case 5:
        self->ext.galamoth.unk8B = 0;
        offsets = D_us_80180DE8;
        if (self->ext.galamoth.activeFoot == 1) {
            offsets = D_us_80180DD0;
        }
        func_801CDF1C(offsets, D_us_80181378, 0);
        func_801CDE10(offsets);
        func_801D0A00(offsets);
        func_801D0B40();
        polarPlacePartsList(D_us_80180D70);
        if (self->ext.galamoth.unkB0[0] >= 2) {
            collider.unk18 = 0x1D;
            entity = self + offsets[3];
            func_us_801955A0(entity, &collider);
            if (entity->ext.galamoth.collision) {
                g_api.PlaySfx(SFX_STOMP_HARD_B);
                entity->posY.i.hi += collider.unk18;
                self->ext.galamoth.activeFoot ^= 1;
                func_801CE228();
                if (func_us_801955F8(entity, self->facingLeft)) {
                    func_801CE1E8(7);
                } else {
                    func_us_80195AD8();
                }
            }
        }
        break;
    case 18:
        self->ext.galamoth.unk8B = 0;
        offsets = D_us_80180DB0;
        if (self->ext.galamoth.activeFoot == 1) {
            offsets = D_us_80180D90;
        }
        func_801CDF1C(offsets, D_us_80181014, 0);
        func_801CDE10(offsets);
        func_801D0A00(offsets);
        polarPlacePartsList(D_us_80180D70);
        if (self->ext.galamoth.unkB0[0] == 3 && !self->ext.galamoth.unkB4[0]) {
            self->ext.galamoth.activeFoot ^= 1;
        }
        if (self->ext.galamoth.unkB0[0] == 6 && !self->ext.galamoth.unkB4[0]) {
            g_api.ShakeCamera(1);
            g_api.PlaySfx(SFX_START_SLAM_B);
        }
        if (!self->ext.galamoth.unkB0[0] && !self->ext.galamoth.unkB4[0]) {
            func_us_80195AD8();
        }
        break;
    case 7:
        self->ext.galamoth.unk8B = 0;
        if (!self->step_s) {
            self->ext.galamoth.unkB0[0] = 1;
            self->step_s++;
        }
        offsets = D_us_80180E10;
        if (self->ext.galamoth.activeFoot == 1) {
            offsets = D_us_80180E00;
        }
        func_801CDF1C(offsets, D_us_801813B0, 0);
        func_801CDE10(offsets);
        func_801D0A00(offsets);
        func_801D0B40();
        polarPlacePartsList(D_us_80180D70);
        if (self->ext.galamoth.unkB0[0] >= 2) {
            collider.unk18 = 0x1D;
            entity = self + offsets[3];
            func_us_801955A0(entity, &collider);
            if (entity->ext.galamoth.collision) {
                g_api.PlaySfx(SFX_STOMP_HARD_B);
                entity->posY.i.hi += collider.unk18;
                self->ext.galamoth.activeFoot ^= 1;
                func_801CE228();
                if (func_us_801955F8(entity, self->facingLeft ^ 1)) {
                    func_801CE1E8(5);
                } else {
                    func_us_80195AD8();
                }
            }
        }
        break;
    case 10:
        offsets = D_us_80180DE8;
        if (self->ext.galamoth.activeFoot == 1) {
            offsets = D_us_80180DD0;
        }
        switch (self->step_s) {
        case 0:
            self->step_s++;
            break;
        case 1:
            func_801CDF1C(offsets, D_us_801814A8, 0);
            func_801CDE10(offsets);
            func_801D0A00(offsets);
            if (!self->ext.galamoth.unkB4[0] && !self->ext.galamoth.unkB0[0]) {
                self->step_s++;
            }
            break;
        case 2:
            if (self->facingLeft) {
                self->velocityX = FIX(3);
            } else {
                self->velocityX = FIX(-3);
            }
            self->velocityY = FIX(-7);
            func_801CE228();
            self->step_s++;
            // fallthrough
        case 3:
            MoveEntity();
            self->velocityY += FIX(0.25);
            func_801CDF1C(offsets, D_us_801814C8, 0);
            func_801CDE10(offsets);
            func_801CE3FC(offsets);
            entity = self + offsets[3];
            collider.unk18 = 0x1D;
            func_us_801955A0(entity, &collider);
            if (entity->ext.galamoth.collision) {
                entity->posY.i.hi += collider.unk18;
                self->ext.galamoth.activeFoot ^= 1;
                func_801CE228();
                self->step_s = 1;
                func_us_801955F8(entity, self->facingLeft);
                func_801CE1E8(7);
            }
            break;
        }
        func_801D0B40();
        polarPlacePartsList(D_us_80180D70);
        break;
    case 26:
        self->ext.galamoth.unk8B = 1;
        offsets = D_us_80180DB0;
        if (self->ext.galamoth.activeFoot == 1) {
            offsets = D_us_80180D90;
        }
        func_801CDF1C(offsets, D_us_80181588, 0);
        func_801CDE10(offsets);
        func_801D0A00(offsets);
        func_801D0B40();
        polarPlacePartsList(D_us_80180D70);
        entity = self + offsets[5];
        entity->ext.galamoth.boostAttack = 1;
        if (!self->ext.galamoth.unkB0[0] && !self->ext.galamoth.unkB4[0]) {
            self->ext.galamoth.unk8B = 0;
            entity = self + offsets[5];
            entity->ext.galamoth.boostAttack = 0;
            func_us_80195AD8();
        }
        if (self->ext.galamoth.unkB0[0] == 3 && !self->ext.galamoth.unkB4[0]) {
            g_api.PlaySfx(SFX_MEDUSA_WEAPON_SWING);
        }
        break;
    case 9:
        switch (self->step_s) {
        case 0:
            offsets = D_us_80180DB0;
            if (self->ext.galamoth.activeFoot == 1) {
                offsets = D_us_80180D90;
            }
            func_801CDF1C(offsets, D_us_80180F10, 0);
            func_801CDE10(offsets);
            func_801D0A00(offsets);
            if (!self->ext.galamoth.unkB0[0] && !self->ext.galamoth.unkB4[0]) {
                self->ext.galamoth.unk8A = 4;
                self->step_s++;
            }
            break;
        case 1:
            value = PLAYER.posX.i.hi;
            angle = ratan2((self + 3)->posX.i.hi - value,
                           PLAYER.posY.i.hi - (self + 3)->posY.i.hi);
            if (self->facingLeft) {
                angle = -angle;
            }
            if (angle > 0x700) {
                angle = 0x700;
            }
            if (angle < 0x200) {
                angle = 0x200;
            }
            func_801CDD00(self + 8, angle, 12);
            func_801CDD00(self + 10, angle, 12);
            func_801CDD00(self + 11, angle, 12);
            tempAngle = angle - ROT(90);
            func_801CDD00(self + 2, tempAngle, 12);
            func_801CDD00(self + 3, tempAngle / 2, 12);
            self->ext.galamoth.timer = 12;
            self->step_s++;
            // fallthrough
        case 2:
            polarPlacePartsWithAngvel(D_us_80180F28);
            if (!--self->ext.galamoth.timer) {
                self->step_s++;
            }
            break;
        case 3:
            offsets = D_us_80180F28;
            func_801CDF1C(offsets, D_us_80180F40, 0);
            func_801CDE10(offsets);
            if (!self->ext.galamoth.unkB0[0] && !self->ext.galamoth.unkB4[0]) {
                if (--self->ext.galamoth.unk8A) {
                    self->step_s = 1;
                } else {
                    func_us_80195AD8();
                }
            }
            break;
        }
        polarPlacePartsList(D_us_80180D70);
        break;
    case 11:
        self->ext.galamoth.unk8B = 0;
        offsets = D_us_80180DE8;
        if (self->ext.galamoth.activeFoot == 1) {
            offsets = D_us_80180DD0;
        }
        func_801CDF1C(offsets, D_us_80181518, 0);
        func_801CDE10(offsets);
        func_801D0A00(offsets);
        func_801D0B40();
        polarPlacePartsList(D_us_80180D70);
        if (!self->ext.galamoth.unkB4[0]) {
            self->facingLeft ^= 1;
            func_us_80195AD8();
        }
        break;
    case 12:
        offsets = D_us_80180DB0;
        if (self->ext.galamoth.activeFoot == 1) {
            offsets = D_us_80180D90;
        }
        switch (self->step_s) {
        case 0:
            self->ext.galamoth.unk8B = 0;
            func_801CDF1C(offsets, D_us_801810E8, 0);
            func_801CDE10(offsets);
            func_801D0A00(offsets);
            self->ext.galamoth.timer = 0x20;
            if (!self->ext.galamoth.unkB4[0] && !self->ext.galamoth.unkB0[0]) {
                self->step_s++;
            }
            // fallthrough
        case 1:
            if (!(g_Timer % 5)) {
                entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (entity != NULL) {
                    CreateEntityFromCurrentEntity(E_UNK_18, entity);
                    entity->ext.et_801980E4.source = self + 7;
                }
            }
            if (!--self->ext.galamoth.timer) {
                self->ext.galamoth.timer = 0x100;
                self->ext.galamoth.unk8B = 1;
                self->step_s++;
            }
            break;
        case 2:
            if (!(self->ext.galamoth.timer & 0x1F)) {
                g_api.PlaySfx(SFX_EXPLODE_B);
                entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
                if (entity != NULL) {
                    CreateEntityFromEntity(E_UNK_19, self + 7, entity);
                }
            }
            if (!--self->ext.galamoth.timer) {
                self->ext.galamoth.unk8B = 0;
                self->step_s++;
            }
            break;
        case 3:
            func_801CDF1C(offsets, D_us_80181120, 0);
            func_801CDE10(offsets);
            func_801D0A00(offsets);
            if (!self->ext.galamoth.unkB4[0] && !self->ext.galamoth.unkB0[0]) {
                func_us_80195AD8();
            }
            break;
        }
        polarPlacePartsList(D_us_80180D70);
        break;
    case 14:
        offsets = D_us_80180DB0;
        if (self->ext.galamoth.activeFoot == 1) {
            offsets = D_us_80180D90;
        }
        switch (self->step_s) {
        case 0:
            self->ext.galamoth.unk8B = 0;
            func_801CDF1C(offsets, D_us_801811A8, 0);
            func_801CDE10(offsets);
            func_801D0A00(offsets);
            self->ext.galamoth.timer = 0x20;
            if (!self->ext.galamoth.unkB4[0] && !self->ext.galamoth.unkB0[0]) {
                self->step_s++;
            }
            if (!self->ext.galamoth.unkB4[0] &&
                self->ext.galamoth.unkB0[0] == 3) {
                g_api.PlaySfx(SFX_BOSS_WING_FLAP);
            }
            // fallthrough
        case 1:
            if (!(g_Timer % 5)) {
                entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (entity != NULL) {
                    CreateEntityFromCurrentEntity(E_UNK_18, entity);
                    entity->ext.et_801980E4.source = self + 7;
                }
            }
            if (!--self->ext.galamoth.timer) {
                g_api.PlaySfx(SFX_GALAMOTH_ELECTRICITY);
                self->ext.galamoth.unk8B = 1;
                self->ext.galamoth.timer = 0x100;
                self->step_s++;
            }
            break;
        case 2:
            offsets = D_us_801811D8;
            func_801CDF1C(offsets, D_us_80181208, 0);
            polarPlacePartsWithAngvel(offsets);
            if (!(self->ext.galamoth.timer & 0xF)) {
                entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
                if (entity != NULL) {
                    CreateEntityFromEntity(E_UNK_1A, self + 7, entity);
                    entity->facingLeft = self->facingLeft;
                }
            }
            if (!(self->ext.galamoth.timer & 0x1F)) {
                g_api.PlaySfx(SFX_GALAMOTH_ELECTRICITY);
            }
            if (!--self->ext.galamoth.timer) {
                func_801CE228();
                self->ext.galamoth.timer = 0x80;
                self->step_s++;
            }
            break;
        case 3:
            offsets = D_us_801811D8;
            func_801CDF1C(offsets, D_us_80181208, 0);
            polarPlacePartsWithAngvel(offsets);
            if (!(self->ext.galamoth.timer & 0x1F)) {
                g_api.PlaySfx(SFX_GALAMOTH_ELECTRICITY);
            }
            if (!--self->ext.galamoth.timer) {
                func_801CE228();
                self->ext.galamoth.unk8B = 0;
                self->step_s++;
            }
            break;
        case 4:
            func_801CDF1C(offsets, D_us_80181258, 0);
            func_801CDE10(offsets);
            func_801D0A00(offsets);
            if (!self->ext.galamoth.unkB4[0] && !self->ext.galamoth.unkB0[0]) {
                func_us_80195AD8();
            }
            break;
        }
        polarPlacePartsList(D_us_80180D70);
        break;
    case 24:
        offsets = D_us_80180DB0;
        if (self->ext.galamoth.activeFoot == 1) {
            offsets = D_us_80180D90;
        }
        func_801CDF1C(offsets, D_us_801815DC, 0);
        func_801CDE10(offsets);
        func_801D0A00(offsets);
        polarPlacePartsList(D_us_80180D70);
        self->ext.galamoth.unk8B = 1;
        if (!self->ext.galamoth.unkB0[0] && !self->ext.galamoth.unkB4[0]) {
            self->ext.galamoth.unk8B = 0;
            func_us_80195AD8();
        }
        break;
    case 22:
        offsets = D_us_80180DB0;
        if (self->ext.galamoth.activeFoot == 1) {
            offsets = D_us_80180D90;
        }
        switch (self->step_s) {
        case 0:
            self->ext.galamoth.unk8B = 0;
            func_801CDF1C(offsets, D_us_801812B0, 0);
            func_801CDE10(offsets);
            func_801D0A00(offsets);
            if (!(g_Timer % 5)) {
                entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (entity != NULL) {
                    CreateEntityFromCurrentEntity(E_UNK_18, entity);
                    entity->ext.et_801980E4.source = self + 7;
                }
            }
            if (!self->ext.galamoth.unkB4[0] && !self->ext.galamoth.unkB0[0]) {
                self->step_s++;
            }
            break;
        case 1:
            entity = self + 20;
            DestroyEntity(entity);
            CreateEntityFromCurrentEntity(E_UNK_1C, entity);
            entity->ext.galamothLightning.parent = self + 7;
            entity->params = 0;
            entity->facingLeft = self->facingLeft;
            entity = self + 21;
            DestroyEntity(entity);
            CreateEntityFromCurrentEntity(E_UNK_1C, entity);
            entity->ext.galamothLightning.parent = self + 11;
            entity->params = 1;
            entity->facingLeft = self->facingLeft;
            g_api.PlaySfx(SFX_GALAMOTH_ELECTRICITY);
            self->step_s++;
            // fallthrough
        case 2:
            if (!(g_Timer % 5)) {
                g_api.PlaySfx(SFX_GALAMOTH_ELECTRICITY);
                entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (entity != NULL) {
                    CreateEntityFromCurrentEntity(E_UNK_18, entity);
                    entity->ext.et_801980E4.source = self + 7;
                }
            }
            func_801CDF1C(offsets, D_us_801812C8, 0);
            func_801CDE10(offsets);
            if (++self->ext.galamoth.timer & 1) {
                (self + 1)->ext.galamoth.rotate += 0x18;
            } else {
                (self + 1)->ext.galamoth.rotate -= 0x18;
            }
            func_801D0A00(offsets);
            if (!self->ext.galamoth.unkB4[0] && !self->ext.galamoth.unkB0[0]) {
                (self + 1)->ext.galamoth.rotate = 0;
                self->ext.galamoth.unk8B = 1;
                self->step_s++;
            }
            break;
        case 3:
            func_801CDF1C(offsets, D_us_80181318, 0);
            func_801CDE10(offsets);
            func_801D0A00(offsets);
            if (self->ext.galamoth.unkB4[0] &&
                self->ext.galamoth.unkB0[0] == 1) {
                (self + 21)->ext.galamothLightning.fired = 1;
                (self + 20)->ext.galamothLightning.fired = 1;
            }
            if (!(g_Timer & 0x1F)) {
                g_api.PlaySfx(SFX_THUNDER_B);
            }
            if (!self->ext.galamoth.unkB4[0] && !self->ext.galamoth.unkB0[0]) {
                g_api.PlaySfx(SFX_EXPLODE_FAST_B);
                self->step_s++;
            }
            break;
        case 4:
            self->ext.galamoth.unk8B = 0;
            func_us_80195AD8();
            break;
        }
        polarPlacePartsList(D_us_80180D70);
        break;
    case 32:
        self->ext.galamoth.unk8B = 1;
        offsets = D_us_80180DB0;
        if (self->ext.galamoth.activeFoot == 1) {
            offsets = D_us_80180D90;
        }
        if (++self->ext.galamoth.timer & 1) {
            (self + 1)->ext.galamoth.rotate += 0x18;
        } else {
            (self + 1)->ext.galamoth.rotate -= 0x18;
        }
        if (!(g_Timer & 0x1F)) {
            g_api.PlaySfx(SFX_EXPLODE_B);
        }
        switch (self->step_s) {
        case 0:
            (self + 2)->step = 32;
            (self + 2)->ext.galamoth.bleed = 1;
            (self + 2)->step_s = 0;
            self->step_s = 2;
            PrizeDrops |= 2;
            break;
        case 1:
            func_801CDF1C(offsets, D_us_801816D4, 0);
            func_801CDE10(offsets);
            func_801D0A00(offsets);
            polarPlacePartsList(D_us_80180D70);
            if (!self->ext.galamoth.unkB4[0] && !self->ext.galamoth.unkB0[0]) {
                self->ext.galamoth.activeFoot = 1;
                self->step_s++;
            }
            break;
        case 2:
            func_801CDF1C(offsets, D_us_801816EC, 0);
            func_801CDE10(offsets);
            func_801D0A00(offsets);
            polarPlacePartsList(D_us_80180D70);
            if (!self->ext.galamoth.unkB4[0] && !self->ext.galamoth.unkB0[0]) {
                g_api.PlaySfx(SFX_BOSS_LARGE_FLAMES);
                g_api.PlaySfx(SFX_BO1_UNK_7C7);
                (self + 2)->ext.galamoth.detach = 1;
                (self + 4)->step = 32;
                (self + 4)->ext.galamoth.bleed = 1;
                (self + 6)->step = 32;
                (self + 7)->step = 32;
                self->step_s++;
            }
            break;
        case 3:
            func_801CDF1C(offsets, D_us_80181714, 0);
            func_801CDE10(offsets);
            func_801D0A00(offsets);
            polarPlacePartsList(D_us_80180D70);
            if (!self->ext.galamoth.unkB4[0] && !self->ext.galamoth.unkB0[0]) {
                g_api.PlaySfx(SFX_BOSS_LARGE_FLAMES);
                g_api.PlaySfx(SFX_BO1_UNK_7C7);
                (self + 4)->ext.galamoth.detach = 1;
                (self + 6)->ext.galamoth.detach = 1;
                (self + 7)->ext.galamoth.detach = 1;
                entity = self + offsets[2];
                entity->step = 32;
                entity->ext.galamoth.bleed = 1;
                entity->ext.galamoth.invertSpurt = 1;
                entity = self + offsets[3];
                entity->step = 32;
                entity = self + offsets[5];
                entity->step = 32;
                self->step_s++;
            }
            break;
        case 4:
            func_801CDF1C(offsets, D_us_80181734, 0);
            func_801CDE10(offsets);
            func_801D0A00(offsets);
            polarPlacePartsList(D_us_80180D70);
            if (!self->ext.galamoth.unkB4[0] && !self->ext.galamoth.unkB0[0]) {
                g_api.PlaySfx(SFX_BOSS_LARGE_FLAMES);
                g_api.PlaySfx(SFX_BO1_UNK_7C7);
                entity = self + offsets[2];
                entity->ext.galamoth.detach = 1;
                entity = self + offsets[3];
                entity->ext.galamoth.detach = 1;
                entity = self + offsets[5];
                entity->ext.galamoth.detach = 1;
                (self + 8)->step = 32;
                (self + 10)->step = 32;
                (self + 11)->step = 32;
                (self + 8)->ext.galamoth.bleed = 1;
                (self + 8)->ext.galamoth.invertSpurt = 1;
                prim = self->ext.galamoth.prim;
                prim->drawMode = DRAW_HIDE;
                self->step_s++;
            }
            break;
        case 5:
            func_801CDF1C(offsets, D_us_80181744, 0);
            func_801CDE10(offsets);
            func_801D0A00(offsets);
            polarPlacePartsList(D_us_80180D70);
            if (!self->ext.galamoth.unkB4[0] && !self->ext.galamoth.unkB0[0]) {
                g_api.PlaySfx(SFX_BOSS_LARGE_FLAMES);
                (self + 8)->ext.galamoth.detach = 1;
                (self + 10)->ext.galamoth.detach = 1;
                (self + 11)->ext.galamoth.detach = 1;
                self->step_s++;
            }
            break;
        case 6:
            for (offsets = D_us_80180D70; *offsets; offsets++) {
                entity = self + *offsets;
                entity->drawFlags |= ENTITY_OPACITY;
            }
            value = 32;
            (self + 3)->step = value;
            (self + 1)->step = value;
            (self + 12)->step = value;

            self->opacity = 0x80;
            (self + 1)->ext.galamoth.bleed = 1;
            (self + 1)->ext.galamoth.invertSpurt = 1;
            self->drawFlags |= ENTITY_OPACITY;
            self->step_s++;
            // fallthrough
        case 7:
            self->opacity -= 2;
            for (offsets = D_us_80180D70; *offsets; offsets++) {
                entity = self + *offsets;
                entity->opacity = self->opacity;
            }
            if (!self->opacity) {
                self->step_s++;
            }
            break;
        case 8:
            self->palette = PAL_FLAG(0x20A);
            self->step_s++;
            // fallthrough
        case 9:
            if (!(self->ext.galamoth.timer & 7)) {
                self->palette++;
            }
            self->posY.i.hi++;
            for (offsets = D_us_80180D70; *offsets; offsets++) {
                entity = self + *offsets;
                entity->palette = self->palette;
                entity->posY.val += FIX(0.25);
            }
            if (self->palette > PAL_FLAG(0x216)) {
                self->step_s++;
            }
            break;
        case 10:
            for (offsets = D_us_80180D70; *offsets; offsets++) {
                DestroyEntity(self + *offsets);
            }
            g_api.PlaySfx(SFX_EXPLODE_A);
            PrizeDrops |= 4;
            DestroyEntity(self);
            return;
        case 11:
            return;
        }
        break;
    }
    func_us_80195938();
    for (offsets = D_us_80180D70; *offsets; offsets++) {
        entity = self + *offsets;
        entity->facingLeft = self->facingLeft;
        entity->ext.galamoth.unkA8 = 0;
    }
    D_8006C384.y = self->ext.galamoth.unkB0[0];
    D_8006C38C.y = self->ext.galamoth.unkB4[0];
}

extern EInit g_EInitGalamothLvl0;

void func_us_80197B1C(Entity* self) {
    Collider collider;
    Entity* entity;
    s16 angle;
    s32 hitboxOffset;
    s32 length;
    u8* hitbox;
    u16 entityId;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitGalamothLvl50);
        if (self->params == 9) {
            InitializeEntity(g_EInitGalamothLvl0);
        }
        if ((self->params == 3) || (self->params == 16)) {
            self->hitboxState = 1;
        }
        self->animCurFrame = self->params;
        hitbox = D_us_80180C88[0];
        self->drawFlags |= ENTITY_ROTATE;
        hitbox += self->animCurFrame * 4;
        self->hitboxWidth = hitbox[2];
        self->hitboxHeight = hitbox[3];
        self->step = 1;
        break;
    case 1:
        angle = self->rotate = self->ext.galamoth.rotate;
        hitboxOffset = (s8)D_us_80180C88[self->animCurFrame][1];
        self->hitboxOffX = (-hitboxOffset * rsin(angle)) >> 12;
        self->hitboxOffY = (hitboxOffset * rcos(angle)) >> 12;
        if (self->ext.galamoth.flip) {
            self->ext.galamoth.flip = false;
            self->facingLeft ^= 1;
            self->rotate = -self->rotate;
        }
        break;
    case 32:
        switch (self->step_s) {
        case 0:
            if (!(g_Timer & 7)) {
                entity = AllocEntity(&g_Entities[160], &g_Entities[256]);
                if (entity != NULL) {
                    entityId = E_UNK_20;
                    if (self->ext.galamoth.bleed) {
                        entityId = E_MINOTAUR_SPIT_LIQUID;
                    }
                    CreateEntityFromEntity(entityId, self, entity);
                    entity->zPriority = self->zPriority + 1;
                    entity->rotate = self->rotate;
                    entity->facingLeft = self->facingLeft;
                    length = self->ext.galamoth.length;
                    angle = self->ext.galamoth.rotate;
                    if (self->facingLeft) {
                        angle = -angle;
                    }
                    entity->posX.val -= -length * rsin(angle) * 16;
                    entity->posY.val += -length * rcos(angle) * 16;
                    if (self->ext.galamoth.invertSpurt) {
                        entity->rotate += ROT(180);
                    }
                }
            }
            self->rotate = self->ext.galamoth.rotate;
            if (self->ext.galamoth.detach) {
                self->step_s++;
            }
            break;
        case 1:
            entity = AllocEntity(&g_Entities[64], &g_Entities[256]);
            if (entity != NULL) {
                CreateEntityFromEntity(E_UNK_1F, self, entity);
                entity->params = self->animCurFrame;
                entity->facingLeft = self->facingLeft;
                entity->rotate = self->rotate;
            }
            self->animCurFrame = 0;
            self->step_s++;
            if (!self->ext.galamoth.bleed) {
                self->step_s++;
            }
            // fallthrough
        case 2:
            if (!(g_Timer & 3)) {
                entity = AllocEntity(&g_Entities[160], &g_Entities[256]);
                if (entity != NULL) {
                    CreateEntityFromEntity(
                        E_MINOTAUR_SPIT_LIQUID, self, entity);
                    entity->zPriority = self->zPriority + 1;
                    entity->rotate = self->ext.galamoth.rotate;
                    entity->facingLeft = self->facingLeft;
                    length = self->ext.galamoth.length;
                    angle = self->ext.galamoth.rotate;
                    if (self->facingLeft) {
                        angle = -angle;
                    }
                    entity->posX.val -= -length * rsin(angle) * 16;
                    entity->posY.val += -length * rcos(angle) * 16;
                    if (self->ext.galamoth.invertSpurt) {
                        entity->rotate += ROT(180);
                    }
                }
            }
            break;
        }
        break;
    }
    switch (self->animCurFrame) {
    case 5:
    case 12:
        collider.unk18 = 0x1D;
        func_us_801955A0(self, &collider);
        break;
    case 6:
    case 13:
        entity = self->ext.galamoth.parent;
        if (entity->ext.galamoth.collision == 2) {
            self->ext.galamoth.rotate = ROT(45);
        } else if (entity->ext.galamoth.collision == 4) {
            self->ext.galamoth.rotate = ROT(-45);
        } else if (entity->ext.galamoth.collision == 1) {
            self->ext.galamoth.rotate = 0;
        }
        if (self->ext.galamoth.boostAttack) {
            angle = self->rotate;
            self->hitboxOffX += -(rsin(angle) * 16) >> 12;
            self->hitboxOffY += (rcos(angle) * 16) >> 12;
            self->attack = g_api.enemyDefs[ENEMY_GALAMOTH_UNK_CA].attack;
            self->attackElement =
                g_api.enemyDefs[ENEMY_GALAMOTH_UNK_CA].attackElement;
        } else {
            self->attack = g_api.enemyDefs[ENEMY_GALAMOTH].attack;
            self->attackElement = g_api.enemyDefs[ENEMY_GALAMOTH].attackElement;
        }
        FntPrint("attack %x\n", self->attackElement);
        break;
    case 9:
    case 17:
        if ((self - 2)->ext.galamoth.unk8B) {
            self->animCurFrame = 17;
        } else {
            self->animCurFrame = 9;
        }
        break;
    }
}

extern EInit g_EInitGalamothLvl50;
extern s32 D_us_80180C0C;

void func_us_801980E4(Entity* self) {
    Entity* source;

    if (D_us_80180C0C != 0) {
        DestroyEntity(self);
        return;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitGalamothLvl50);
        self->hitboxState = 0;
        self->animCurFrame = 0x10;
        self->blendMode = BLEND_ADD | BLEND_TRANSP;
        self->drawFlags = ENTITY_SCALEY | ENTITY_SCALEX;
        self->scaleX = self->scaleY = 0x100;
        self->drawFlags |= ENTITY_OPACITY;
        self->opacity = 0xC0;
        self->drawFlags |= ENTITY_ROTATE;
        /* fall through */
    case 1:
        if (g_Timer & 1) {
            self->palette = PAL_FLAG(0x206);
        } else {
            self->palette = PAL_FLAG(0x207);
        }
        source = self->ext.et_801980E4.source;
        self->facingLeft = source->facingLeft;
        self->rotate = source->rotate;
        self->posX.i.hi = source->posX.i.hi;
        self->posY.i.hi = source->posY.i.hi;
        self->scaleX = self->scaleY += 0x20;
        self->opacity -= 8;
        if (!self->opacity) {
            DestroyEntity(self);
        }
        break;
    }
}

extern EInit D_us_80180A8C;
extern u8 D_us_80180C20[];

void func_us_80198210(Entity* self) {
    Entity* entities;
    s16 angle;

    if ((self->flags & FLAG_DEAD) || D_us_80180C0C != 0) {
        self->velocityX = 0;
        self->velocityY = 0;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_80180A8C);
        self->blendMode = BLEND_ADD | BLEND_TRANSP;
        entities = g_Entities;
        angle = GetAngleBetweenEntities(self, entities);
        self->velocityX = rcos(angle) * 0x140;
        self->velocityY = rsin(angle) * 0x140;
        /* fall through */

    case 1:
        AnimateEntity(D_us_80180C20, self);
        MoveEntity();
        self->velocityX -= self->velocityX / 0x10;
        self->velocityY -= self->velocityY / 0x10;
        if (abs(self->velocityX) < 0x4000 && abs(self->velocityY) < 0x4000) {
            self->drawFlags = ENTITY_SCALEY | ENTITY_SCALEX;
            self->scaleX = self->scaleY = 0x100;
            self->hitboxState = 0;
            self->step++;
        }
        break;

    case 2:
        AnimateEntity(D_us_80180C20, self);
        self->scaleX = self->scaleY -= 0x10;
        if (!self->scaleX) {
            DestroyEntity(self);
        }
        break;
    }
}

extern EInit g_EInitInteractable;

void func_us_801983EC(Entity* self) {
    Primitive* prim;
    Primitive* primTwo;
    s32 posX;
    Entity* entity;
    s32 posY;
    s16 tempAngle;
    s16 boltAngle;
    s32 i;
    u8 closeToTarget;
    s16 angle;
    s16 primIndex;
    s32 sp34;

    if (D_us_80180C0C) {
        DestroyEntity(self);
        return;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
        self->ext.galamothLightning.sweepOffset = -0x80;
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 0x28);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.galamothLightning.prim = prim;
        self->ext.galamothLightning.primTwo = prim;

        i = 0;
        while (prim != NULL) {
            prim->tpage = 0x1A;
            prim->clut = 0x194;
            prim->u0 = prim->u1 = (i * 0x10) + 0x90;
            prim->u2 = prim->u3 = prim->u0 + 0x10;
            prim->v0 = prim->v2 = 0xD0;
            prim->v1 = prim->v3 = 0xC0;
            PGREY(prim, 0) = 0x50;
            LOW(prim->r1) = LOW(prim->r0);
            LOW(prim->r2) = LOW(prim->r0);
            LOW(prim->r3) = LOW(prim->r0);
            prim->priority = self->zPriority - 1;
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;

            if (++i > 5) {
                i = 0;
            }
        }
        // fallthrough
    case 1:
        prim = self->ext.galamothLightning.prim;
        prim->x0 = self->posX.i.hi;
        prim->y0 = self->posY.i.hi;
        prim->x1 = prim->x0;
        // @bug: Updates y1 without first initializing it from y0.
        prim->y1 = prim->y1 - 0x10;
        prim->x2 = self->posX.i.hi;
        prim->y2 = self->posY.i.hi;
        prim->x3 = prim->x2;
        prim->y3 = prim->y2 - 0x10;
        self->ext.galamothLightning.primTwo = prim;

        self->ext.galamothLightning.boltAngle = ROT(270);
        self->ext.galamothLightning.segmentsBeforeAim = 0;
        self->step++;
        // fallthrough
    case 2:
        for (i = 0; i < 6; i++) {
            prim = self->ext.galamothLightning.primTwo;
            boltAngle = self->ext.galamothLightning.boltAngle;
            if (self->facingLeft) {
                posX =
                    self->posX.i.hi + self->ext.galamothLightning.sweepOffset;
            } else {
                posX =
                    self->posX.i.hi - self->ext.galamothLightning.sweepOffset;
            }
            posY = 0x1C0 - g_Tilemap.scrollY.i.hi;
            posX -= prim->x2;
            posY -= prim->y2;
            if (posY < 0) {
                prim->y2 = prim->y3 = 0x1C0 - g_Tilemap.scrollY.i.hi;
                self->step = 3;
                return;
            }
            if (abs(posX) < 0x40 && abs(posY) < 0x40) {
                closeToTarget = true;
            } else {
                closeToTarget = false;
            }

            if (!self->ext.galamothLightning.segmentsBeforeAim) {
                self->ext.galamothLightning.segmentsBeforeAim = 4;

                if (closeToTarget) {
                    self->ext.galamothLightning.segmentsBeforeAim = 2;
                }

                angle = ratan2(-posY, posX);
                tempAngle = angle - boltAngle;
                if (tempAngle > ROT(180)) {
                    tempAngle = tempAngle - ROT(360);
                }

                if (tempAngle < ROT(-180)) {
                    tempAngle = tempAngle + ROT(360);
                }

                // Turn more sharply when approaching the target.
                if (!closeToTarget) {
                    tempAngle /= 4;
                } else {
                    tempAngle /= 2;
                }
                self->ext.galamothLightning.angleStep = tempAngle;
            }

            boltAngle += self->ext.galamothLightning.angleStep;
            if (!closeToTarget) {
                // Add jitter while the bolt is far from its target.
                boltAngle += (0xC0 - ((Random() & 3) << 7));
            }
            boltAngle &= 0xFFF;

            primTwo = prim->next;
            if (primTwo == NULL) {
                self->step = 3;
                return;
            }

            LOW(primTwo->x0) = LOW(prim->x2);
            LOW(primTwo->x1) = LOW(prim->x3);
            self->ext.galamothLightning.boltAngle = boltAngle;
            self->ext.galamothLightning.primTwo = primTwo;
            posX = (rcos(boltAngle) * 0xC) >> 0xC;
            posY = -((rsin(boltAngle) * 0xC) >> 0xC);
            primTwo->x2 = primTwo->x0 + posX;
            primTwo->y2 = primTwo->y0 + posY;

            tempAngle = boltAngle - ROT(90);
            sp34 = 0x10;
            posX = (sp34 * rcos(tempAngle)) >> 0xC;
            posY = -((sp34 * rsin(tempAngle)) >> 0xC);
            primTwo->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS |
                                DRAW_UNK02 | DRAW_TRANSP;
            posX = primTwo->x3 = primTwo->x2 + posX;
            posY = primTwo->y3 = primTwo->y2 + posY;

            entity = &PLAYER;
            posX = posX - entity->posX.i.hi;
            posY = posY - entity->posY.i.hi;

            // If the player comes within 12px of the lightning, spawn a
            // damaging hitbox entity
            if (abs(posX) < 12 && abs(posY) < 12) {
                entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
                if (entity != NULL) {
                    CreateEntityFromCurrentEntity(E_UNK_1D, entity);
                    entity->posX.i.hi = primTwo->x3;
                    entity->posY.i.hi = primTwo->y3;
                }
            }
            self->ext.galamothLightning.segmentsBeforeAim--;
        }
        break;
    case 3:
        prim = self->ext.galamothLightning.prim;
        while (prim != NULL) {
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }
        self->ext.galamothLightning.sweepOffset += 8;
        self->step = 1;
        if (self->ext.galamothLightning.sweepOffset > 0x80) {
            DestroyEntity(self);
        }
        break;
    }
}

extern EInit g_EInitInteractable;

void func_us_80198964(Entity* self) {
    Entity* entity;
    s32 i;

    entity = self->ext.galamothLightning.parent;
    if (entity->entityId != E_UNK_17) {
        DestroyEntity(self);
        return;
    }
    if (D_us_80180C0C) {
        DestroyEntity(self);
        return;
    }
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
        if (!self->params) {
            for (i = 0; i < 6; i++) {
                entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (entity != NULL) {
                    CreateEntityFromCurrentEntity(E_UNK_1B, entity);
                    entity->ext.galamothLightning.parent = self;
                    entity->facingLeft = self->facingLeft;
                    entity->params = i;
                }
            }
        }
        // fallthrough
    case 1:
        entity = self->ext.galamothLightning.parent;
        self->posX.i.hi = entity->posX.i.hi;
        self->posY.i.hi = entity->posY.i.hi;
        if (self->ext.galamothLightning.fired) {
            self->step++;
        }
        break;
    case 2:
        if (self->facingLeft) {
            self->velocityX = FIX(6);
        } else {
            self->velocityX = FIX(-6);
        }
        self->velocityY = 0;
        self->step++;
        // fallthrough
    case 3:
        MoveEntity();
        self->velocityX += self->velocityX / 128;
        if ((u32)(self->posX.i.hi + g_Tilemap.scrollX.i.hi + 0x40) > 0x280) {
            DestroyEntity(self);
        }
        break;
    }
}

void func_us_8019C7B8_from_rcen(Entity* self) {
    Primitive* prim;
    Primitive* primTwo;
    s32 posX;
    Entity* entity;
    s32 posY;
    s16 tempAngle;
    s16 boltAngle;
    s32 i;
    // @bug: Uninitialized when the lightning has already fired.
    u8 closeToTarget;
    s16 angle;
    s16 primIndex;
    s32 sp34;

    if (D_us_80180C0C) {
        DestroyEntity(self);
        return;
    }

    entity = self->ext.galamothLightning.parent;
    self->posX.i.hi = entity->posX.i.hi;
    self->posY.i.hi = entity->posY.i.hi;
    self->ext.galamothLightning.fired = entity->ext.galamothLightning.fired;
    if (entity->entityId != E_UNK_1C) {
        DestroyEntity(self);
        return;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 0x10);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.galamothLightning.prim = prim;
        self->ext.galamothLightning.primTwo = prim;

        i = 0;
        while (prim != NULL) {
            prim->tpage = 0x1A;
            prim->clut = 0x194;
            prim->u0 = prim->u1 = (i * 0x10) + 0x90;
            prim->u2 = prim->u3 = prim->u0 + 0x10;
            prim->v0 = prim->v2 = 0xD0;
            prim->v1 = prim->v3 = 0xC0;
            PGREY(prim, 0) = 0x50;
            LOW(prim->r1) = LOW(prim->r0);
            LOW(prim->r2) = LOW(prim->r0);
            LOW(prim->r3) = LOW(prim->r0);
            prim->priority = self->zPriority - 1;
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;

            if (++i > 5) {
                i = 0;
            }
        }
        // fallthrough
    case 1:
        prim = self->ext.galamothLightning.prim;
        prim->x0 = self->posX.i.hi;
        prim->y0 = self->posY.i.hi;
        prim->x1 = prim->x0;
        // @bug: Updates y1 without first initializing it from y0.
        prim->y1 = prim->y1 - 0x10;
        prim->x2 = self->posX.i.hi;
        prim->y2 = self->posY.i.hi;
        prim->x3 = prim->x2;
        prim->y3 = prim->y2 - 0x10;
        self->ext.galamothLightning.primTwo = prim;

        self->ext.galamothLightning.boltAngle = Random() * 16;
        if (self->ext.galamothLightning.fired) {
            if (self->facingLeft) {
                self->ext.galamothLightning.boltAngle = 0x100;
                self->ext.galamothLightning.boltAngle += self->params << 7;
                self->ext.galamothLightning.boltAngle += Random() * 2;
            } else {
                self->ext.galamothLightning.boltAngle = 0x700;
                self->ext.galamothLightning.boltAngle -= self->params << 7;
                self->ext.galamothLightning.boltAngle -= Random() * 2;
            }
        }

        while (prim != NULL) {
            PGREY(prim, 0) = 0x50;
            if (self->ext.galamothLightning.fired) {
                PGREY(prim, 0) = 0x50 - self->params * 8;
            }
            LOW(prim->r1) = LOW(prim->r0);
            LOW(prim->r2) = LOW(prim->r0);
            LOW(prim->r3) = LOW(prim->r0);
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }
        self->ext.galamothLightning.segmentsBeforeAim = 0;
        self->step++;
        // fallthrough
    case 2:
        // nb. loop indefinitely until break
        for (i = 0;; i = i + 1) {
            prim = self->ext.galamothLightning.primTwo;
            boltAngle = self->ext.galamothLightning.boltAngle;
            entity = self->ext.galamothLightning.parent;
            entity++;
            posX = entity->posX.i.hi;
            posY = entity->posY.i.hi;
            posX = posX - prim->x2;
            posY = posY - prim->y2;

            if (abs(posX) < 0x10 && abs(posY) < 0x10) {
                self->step = 1;
                return;
            }

            if (!self->ext.galamothLightning.fired) {
                if (abs(posX) < 0x20 && abs(posY) < 0x20) {
                    closeToTarget = true;
                } else {
                    closeToTarget = false;
                }
            }

            if (!self->ext.galamothLightning.segmentsBeforeAim) {
                self->ext.galamothLightning.segmentsBeforeAim = 4;

                if (closeToTarget) {
                    self->ext.galamothLightning.segmentsBeforeAim = 2;
                }

                angle = ratan2(-posY, posX);
                tempAngle = angle - boltAngle;
                if (tempAngle > ROT(180)) {
                    tempAngle = tempAngle - ROT(360);
                }

                if (tempAngle < ROT(-180)) {
                    tempAngle = tempAngle + ROT(360);
                }

                // Turn more sharply when approaching the target.
                if (self->ext.galamothLightning.fired) {
                    self->ext.galamothLightning.segmentsBeforeAim = 16;
                    tempAngle /= 8;
                } else if (!closeToTarget) {
                    tempAngle /= 4;
                } else {
                    tempAngle /= 2;
                }
                self->ext.galamothLightning.angleStep = tempAngle;
            }

            boltAngle += self->ext.galamothLightning.angleStep;
            if (!closeToTarget && !self->ext.galamothLightning.fired) {
                // Add jitter while the bolt is far from its target.
                boltAngle += (0x120 - ((Random() & 3) * 0xC0));
            }
            boltAngle &= 0xFFF;

            primTwo = prim->next;
            if (primTwo == NULL) {
                self->step = 1;
                return;
            }

            LOW(primTwo->x0) = LOW(prim->x2);
            LOW(primTwo->x1) = LOW(prim->x3);
            self->ext.galamothLightning.boltAngle = boltAngle;
            self->ext.galamothLightning.primTwo = primTwo;
            posX = (rcos(boltAngle) * 0xC) >> 0xC;
            posY = -((rsin(boltAngle) * 0xC) >> 0xC);
            primTwo->x2 = primTwo->x0 + posX;
            primTwo->y2 = primTwo->y0 + posY;

            tempAngle = boltAngle - ROT(90);
            sp34 = 0x10;
            posX = (sp34 * rcos(tempAngle)) >> 0xC;
            posY = -((sp34 * rsin(tempAngle)) >> 0xC);
            posX = primTwo->x3 = primTwo->x2 + posX;
            posY = primTwo->y3 = primTwo->y2 + posY;

            entity = &PLAYER;
            posX = posX - entity->posX.i.hi;
            posY = posY - entity->posY.i.hi;

            // If the player comes within 12px of the lightning, spawn a
            // damaging hitbox entity
            if (abs(posX) < 12 && abs(posY) < 12) {
                entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
                if (entity != NULL) {
                    CreateEntityFromCurrentEntity(E_UNK_1D, entity);
                    entity->posX.i.hi = primTwo->x3;
                    entity->posY.i.hi = primTwo->y3;
                }
            }
            primTwo->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS |
                                DRAW_UNK02 | DRAW_TRANSP;
            self->ext.galamothLightning.segmentsBeforeAim--;
        }
        // fallthrough
    case 3:
        prim = self->ext.galamothLightning.prim;
        while (prim != NULL) {
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }
        self->step = 1;
        break;
    }
}

extern EInit D_us_80180A98;

void func_us_801991D4(Entity* self) {
    if (!self->step) {
        InitializeEntity(D_us_80180A98);
        return;
    }
    DestroyEntity(self);
}

void func_us_8019921C(Entity* self) {
    s32 args[9];

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitGalamothLvl50);
        self->animCurFrame = self->params;
        self->drawFlags = ENTITY_ROTATE;
        /* fall through */
    case 1:
        MoveEntity();
        self->rotate -= ROT(2.8125);
        self->velocityY += FIX(0.125);
        if (self->facingLeft) {
            self->velocityX = FIX(0.5);
        } else {
            self->velocityX = FIX(-0.5);
        }
        args[6] = 0x20;
        func_us_801955A0(self, args);
        if (self->ext.et_8019921C.hitFloor) {
            self->flags |= FLAG_DESTROY_IF_OUT_OF_CAMERA;
            self->zPriority = 0x5F;
        }
        break;
    }
}

extern EInit D_us_80180AA4;
extern AnimationFrame D_us_80180C4C[];

void EntityMinotaurSpitLiquid(Entity* self) {
    s16 angle;

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_80180AA4);
        if (self->facingLeft) {
            self->rotate = -self->rotate;
        }
        self->facingLeft = 0;
        self->rotate += 0x100 - Random() * 2;

        angle = self->rotate;
        self->velocityX = rsin(angle) * 0x28;
        self->velocityY = rcos(angle) * -0x28;
        self->blendMode = BLEND_ADD | BLEND_TRANSP;
        self->drawFlags =
            ENTITY_OPACITY | ENTITY_ROTATE | ENTITY_SCALEY | ENTITY_SCALEX;
        self->scaleX = 0x20;
        self->scaleY = 0x100;
        self->opacity = 0x80;
        /* fall through */

    case 1:
        MoveEntity();
        self->scaleX += 0xC;
        self->scaleY += 2;
        self->opacity -= 1;
        if (!AnimateEntity(D_us_80180C4C, self)) {
            DestroyEntity(self);
        }
        break;
    }
}

extern EInit D_us_80180AB0;
extern u8 D_us_80180C68[];

void func_us_8019943C(Entity* self) {
    s16 angle;

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_80180AB0);
        if (self->facingLeft) {
            self->rotate = -self->rotate;
        }
        self->facingLeft = 0;
        self->rotate += 0x100 - Random() * 2;

        angle = self->rotate;
        self->velocityX = rsin(angle) * 0x20;
        self->velocityY = rcos(angle) * -0x20;
        self->blendMode = BLEND_ADD | BLEND_TRANSP;
        /* fall through */
    case 1:
        MoveEntity();
        self->posY.i.hi--;
        if (AnimateEntity(D_us_80180C68, self) == 0) {
            DestroyEntity(self);
        }
        break;
    }
}
