// SPDX-License-Identifier: AGPL-3.0-or-later
#include "bo2.h"

extern EInit g_EInitInteractable;
extern s32 D_us_80180AAC;
extern s32 D_us_80180AB0;
extern s32 D_us_80180B74;
extern s32 g_CutsceneFlags;
extern s32 D_us_80180AB4[][4];

void func_us_801A3E04(Entity* self) {
    Primitive* prim;
    Entity* entity;
    Entity* werewolf;
    Entity* minotaur;
    s32* pattern;
    s32 scrollX;
    s32 scrollY;
    s16 primIndex;
    s32 distance;

    scrollX = g_Tilemap.scrollX.i.hi;
    scrollY = g_Tilemap.scrollY.i.hi;
    werewolf = self + 1;
    minotaur = self + 4;
    FntPrint("set_step %x\n", self->step);
    FntPrint("boss_go %x\n", D_us_80180AAC);
    if ((self->step >= 5) && (werewolf->flags & FLAG_DEAD) &&
        (minotaur->flags & FLAG_DEAD) && (self->step != 8)) {
        SetStep(8);
    }
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
        primIndex = g_api.AllocPrimitives(PRIM_G4, 1);
        if (primIndex == -1) {
            self->step = 0;
            return;
        }
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.minotaurWerewolf.prim = prim;
        self->flags |= FLAG_HAS_PRIMS;
        prim->r0 = prim->g0 = prim->b0 = 0;
        prim->x0 = prim->x2 = 0;
        prim->x1 = prim->x3 = 0x100;
        prim->y0 = prim->y1 = 0;
        prim->y2 = prim->y3 = 0x100;
        prim->priority = 0x1F0;
        prim->drawMode = DRAW_HIDE;
        LOW(prim->r1) = LOW(prim->r0);
        LOW(prim->r2) = LOW(prim->r0);
        LOW(prim->r3) = LOW(prim->r0);
        self->ext.minotaurWerewolf.patternIndex = 0;
        // fallthrough
    case 1:
        if (g_CastleFlags[RICHTER_CS_AFTER_M_AND_W] ||
            (g_PlayableCharacter != PLAYER_ALUCARD) ||
            (g_DemoMode != Demo_None)) {
            if (GetDistanceToPlayerX() < 0x10) {
                D_us_80180B74 = 1;
                stopMusicFlag = 0;
                currentMusicId = MU_FESTIVAL_OF_SERVANTS;
                g_api.PlaySfx(MU_FESTIVAL_OF_SERVANTS);
                SetStep(2);
            }
        } else if (g_CutsceneFlags & 0x10) {
            SetStep(2);
        }
        break;
    case 2:
        switch (self->step_s) {
        case 0:
            entity = &g_Entities[112];
            CreateEntityFromCurrentEntity(E_UNK_28, entity);
            g_Entities[112].posX.i.hi = 0x150 - scrollX;
            g_Entities[112].posY.i.hi = 0xD0 - scrollY;
            g_Entities[112].params = 0;
            CreateEntityFromCurrentEntity(E_UNK_28, &g_Entities[113]);
            g_Entities[113].posX.i.hi = 0xA0 - scrollX;
            g_Entities[113].posY.i.hi = 0xD0 - scrollY;
            g_Entities[113].params = 1;
            self->ext.minotaurWerewolf.timer = 0x80;
            self->step_s++;
            // fallthrough
        case 1:
            if (!--self->ext.minotaurWerewolf.timer) {
                SetStep(3);
            }
            break;
        }
        break;
    case 3:
        CreateEntityFromCurrentEntity(E_MINOTAUR, minotaur);
        CreateEntityFromCurrentEntity(E_WEREWOLF, werewolf);
        minotaur->posX.i.hi = 0x160 - scrollX;
        minotaur->posY.i.hi = 0xA8 - scrollY;
        werewolf->posX.i.hi = 0xA0 - scrollX;
        werewolf->posY.i.hi = 0xB5 - scrollY;
        g_api.TimeAttackController(
            TIMEATTACK_EVENT_MINOTAUR_WEREWOLF_DEFEAT, TIMEATTACK_SET_VISITED);
        SetStep(4);
        // fallthrough
    case 4:
        switch (self->step_s) {
        case 0:
            self->ext.minotaurWerewolf.timer = 0x100;
            self->step_s++;
            // fallthrough
        case 1:
            if (!--self->ext.minotaurWerewolf.timer) {
                self->step_s++;
            }
            break;
        case 2:
            if (g_CastleFlags[RICHTER_CS_AFTER_M_AND_W] ||
                (g_PlayableCharacter != PLAYER_ALUCARD) ||
                (g_DemoMode != Demo_None)) {
                D_us_80180AAC = 1;
            }
            SetStep(5);
            break;
        }
        break;
    case 5:
        pattern = D_us_80180AB4[0];
        pattern += self->ext.minotaurWerewolf.patternIndex * 4;
        if (!(minotaur->flags & FLAG_DEAD)) {
            distance = pattern[0];
            minotaur->ext.minotaur.deathPuffPosX = distance;
            minotaur->ext.minotaur.nextStep = pattern[1];
        }
        if (!(werewolf->flags & FLAG_DEAD)) {
            distance = pattern[2];
            werewolf->ext.werewolfBoss.targetX = distance;
            werewolf->ext.werewolfBoss.nextStep = pattern[3];
        }
        SetStep(6);
        break;
    case 6:
        if (minotaur->ext.minotaur.isReady &&
            werewolf->ext.werewolfBoss.isReady) {
            pattern = D_us_80180AB4[0];
            pattern += self->ext.minotaurWerewolf.patternIndex * 4;
            if ((pattern[3] == 0xE) && (pattern[1] == 0xC)) {
                distance = minotaur->posX.i.hi - werewolf->posX.i.hi;
                if (abs(distance) < 0x40) {
                    minotaur->ext.minotaur.nextStep = 0xB;
                    werewolf->ext.werewolfBoss.nextStep = 0x18;
                }
            }
            werewolf->ext.werewolfBoss.hasNextStep = true;
            minotaur->ext.minotaur.hasNextStep = true;
            SetStep(7);
        }
        break;
    case 7:
        self->ext.minotaurWerewolf.patternIndex++;
        pattern = D_us_80180AB4[0];
        pattern += self->ext.minotaurWerewolf.patternIndex * 4;
        if (pattern[3] == 0x18) {
            distance = minotaur->posX.i.hi - PLAYER.posX.i.hi;
            if (distance * (werewolf->posX.i.hi - PLAYER.posX.i.hi) < 0) {
                self->ext.minotaurWerewolf.patternIndex++;
                pattern += 4;
            }
        }
        if (pattern[0] == -1) {
            self->ext.minotaurWerewolf.patternIndex = 0;
        }
        SetStep(5);
        break;
    case 8:
        switch (self->step_s) {
        case 0:
            g_api.PlaySfx(SET_UNK_92);
            self->ext.minotaurWerewolf.timer = 0x100;
            g_api.TimeAttackController(
                TIMEATTACK_EVENT_MINOTAUR_WEREWOLF_DEFEAT,
                TIMEATTACK_SET_RECORD);
            self->step_s++;
            // fallthrough
        case 1:
            if (!--self->ext.minotaurWerewolf.timer) {
                self->step_s++;
                if (!g_CastleFlags[RICHTER_CS_AFTER_M_AND_W] &&
                    (g_PlayableCharacter == PLAYER_ALUCARD) &&
                    (g_DemoMode == Demo_None)) {
                    CreateEntityFromCurrentEntity(
                        E_CUTSCENE_DIALOGUE, &g_Entities[200]);
                    g_Entities[200].params = 1;
                    CreateEntityFromCurrentEntity(E_UNK_26, &g_Entities[96]);
                    g_Entities[96].params = 1;
                } else {
                    self->step_s++;
                }
            }
            break;
        case 2:
            if (g_CutsceneFlags & 0x1000) {
                self->step_s++;
            }
            break;
        case 3:
            entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
            if (entity != NULL) {
                CreateEntityFromEntity(E_LIFE_UP_SPAWN, self, entity);
                stopMusicFlag = 1;
                D_us_80180B74 = 0;
                entity->posX.i.hi = 0x100 - g_Tilemap.scrollX.i.hi;
                entity->posY.i.hi = 0x80 - g_Tilemap.scrollY.i.hi;
                entity->params = 2;
                currentMusicId = MU_WANDERING_GHOSTS;
                self->step_s++;
            }
            break;
        case 4:
            if (!g_api.func_80131F68()) {
                stopMusicFlag = 0;
                g_api.PlaySfx(currentMusicId);
                self->step_s++;
            }
            break;
        case 5:
            break;
        }
        break;
    }
}

void func_us_801A460C(Entity* self) {
    DRAWENV drawEnv;
    RECT clipRect;
    RECT unused;
    Primitive* prim;
    DR_ENV* dr_env;
    Entity* entity;
    s32 primIndex;
    s32 left;
    s32 right;
    s32 floorY;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 2);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        prim = &g_PrimBuf[primIndex];
        self->primIndex = primIndex;
        self->ext.et_801A460C.prim = prim;
        self->flags |= FLAG_HAS_PRIMS;
        dr_env = g_api.func_800EDB08((POLY_GT4*)prim);
        if (dr_env == NULL) {
            DestroyEntity(self);
            return;
        }
        prim->type = PRIM_ENV;
        drawEnv = g_CurrentBuffer->draw;
        clipRect.w = 0x100;
        clipRect.y = 0x14;
        drawEnv.isbg = 0;
        drawEnv.r0 = 0;
        drawEnv.g0 = 0;
        drawEnv.b0 = 0;
        drawEnv.dtd = 0;
        drawEnv.ofs[0] = 0;
        clipRect.x = 0;
        clipRect.h = 0xCF;
        drawEnv.clip = clipRect;
        SetDrawEnv(dr_env, &drawEnv);
        prim->priority = self->params * 4 + 0x9F;
        prim->drawMode = DRAW_HIDE;
        prim = prim->next;
        dr_env = g_api.func_800EDB08((POLY_GT4*)prim);
        if (dr_env == NULL) {
            DestroyEntity(self);
            return;
        }
        prim->type = PRIM_ENV;
        prim->drawMode = DRAW_UNK_800 | DRAW_HIDE;
        prim->priority = self->params * 4 + 0xA1;
        self->ext.et_801A460C.halfWidth = 0;
    case 1:
        switch (self->step_s) {
        case 0:
            if (++self->ext.et_801A460C.timer & 1) {
                self->ext.et_801A460C.halfWidth++;
            }
            if (!(g_Timer & 0xF)) {
                g_api.PlaySfx(SFX_FIREBALL_SHOT_B);
            }
            if (self->ext.et_801A460C.halfWidth >= 0x1E) {
                self->step_s++;
            }
            break;
        case 1:
            if (D_us_80180AB0) {
                self->ext.et_801A460C.timer = 0x80;
                self->step_s++;
            }
            if (!(g_Timer & 0xF)) {
                g_api.PlaySfx(SFX_FIREBALL_SHOT_B);
            }
            break;
        case 2:
            if (!--self->ext.et_801A460C.timer) {
                DestroyEntity(self);
                return;
            }
            break;
        }

        left = self->posX.i.hi - self->ext.et_801A460C.halfWidth;
        right = self->ext.et_801A460C.halfWidth + self->posX.i.hi;
        prim = self->ext.et_801A460C.prim;
        floorY = 0xD0 - g_Tilemap.scrollY.i.hi;
        if (left < 0) {
            left = 0;
        }
        if (left > 0x100) {
            left = 0x100;
        }
        if (right < 0) {
            right = 0;
        }
        if (right > 0x100) {
            right = 0x100;
        }
        dr_env = PRIM_DR_ENV(prim);
        drawEnv = g_CurrentBuffer->draw;
        clipRect.w = right - left;
        clipRect.y = 0x14;
        drawEnv.isbg = 0;
        clipRect.h = floorY - 0x15;
        clipRect.x = drawEnv.ofs[0] + left;
        drawEnv.clip = clipRect;
        SetDrawEnv(dr_env, &drawEnv);
        prim->drawMode = DRAW_DEFAULT;
        prim = prim->next;
        prim->drawMode = DRAW_UNK_800;

        if (!D_us_80180AB0 && !(g_Timer & 1)) {
            if (Random() & 1) {
                entity = AllocEntity(&g_Entities[144], &g_Entities[256]);
                if (entity != NULL) {
                    CreateEntityFromCurrentEntity(E_UNK_29, entity);
                    entity->zPriority = self->params * 4 + 0xA0;
                    entity->posX.i.hi =
                        self->posX.i.hi - self->ext.et_801A460C.halfWidth / 2;
                    entity->posX.i.hi -= Random() & 0xF;
                    entity->posY.i.hi = 0xD0;
                    entity->rotate = Random() + 0x40;
                }
            } else {
                entity = AllocEntity(&g_Entities[144], &g_Entities[256]);
                if (entity != NULL) {
                    CreateEntityFromCurrentEntity(E_UNK_29, entity);
                    entity->zPriority = self->params * 4 + 0xA0;
                    entity->posX.i.hi =
                        self->posX.i.hi + self->ext.et_801A460C.halfWidth / 2;
                    entity->posX.i.hi += Random() & 0xF;
                    entity->posY.i.hi = 0xD0;
                    left = Random();
                    entity->rotate = -0x40 - left;
                }
            }
        }
        break;
    }
}

#include "e_unk_29.h"
