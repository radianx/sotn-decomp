// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rbo2.h"
#include <cutscene.h>

extern Dialogue g_Dialogue;
static const char* actor_names[] = {_S("Alucard"), _S("Death")};

#include "../../st/cutscene_unk1.h"

#include "../../st/set_cutscene_script.h"

#include "../../st/cutscene_unk3.h"

#include "../../st/cutscene_unk4.h"

#include "../../st/cutscene_actor_name.h"

#include "../../st/set_cutscene_events.h"

#define CUTSCENE_TILEMAP_SCROLL
#include "../../st/cutscene_events.h"

#include "../../st/cutscene_scale_avatar.h"

extern s32 D_us_801AE904;
extern s32 D_us_801AE850;
extern u8 D_us_80181878[];
extern u8 D_us_80180B60[];
extern u8 D_us_80180B64[];
extern u16 D_us_80180B68[];
extern u16 D_us_80180B6C[];
extern u16 D_us_80180B70[];
extern s16 D_us_80180B78[];

void EntityCutsceneDialogue(Entity* self) {
    RECT rect;
    Primitive* prim;
    s16 primIndex;
    s32 i;
    s16 j;
    s16 uCoord;
    s16 vCoord;
    u16 nextChar;
    s32 nextChar2;
    u_long ptr;

    if (self->step) {
        if (D_us_801AE904 && !D_us_801AE850 &&
            ((g_Settings.D_8003CB04 & 0x40000) || g_GameClearFlag) &&
            (g_pads[0].tapped & PAD_START)) {
            D_us_801AE850 = true;
            g_api.FreePrimitives(self->primIndex);
            self->flags ^= FLAG_HAS_PRIMS;
            if (g_Dialogue.primIndex[1] != -1) {
                g_api.FreePrimitives(g_Dialogue.primIndex[1]);
            }
            if (g_Dialogue.primIndex[0] != -1) {
                g_api.FreePrimitives(g_Dialogue.primIndex[0]);
            }
            g_api.PlaySfx(SET_STOP_MUSIC);
            self->step = 1;
            self->step_s = 0;
        }
        if (self->step && g_Dialogue.hasEvents) {
            RunCutsceneEvents();
        }
    }

    switch (self->step) {
    case 0:
        if (g_CastleFlags[DEATH_FIGHT_CS] ||
            (g_PlayableCharacter != PLAYER_ALUCARD) ||
            (g_DemoMode != Demo_None)) {
            DestroyEntity(self);
            return;
        }
        if (SetCutsceneScript(D_us_80181878)) {
            g_CutsceneHasControl = true;
            g_CutsceneFlags = 0;
            D_us_801AE904 = false;
            D_us_801AE850 = false;
            self->flags |= FLAG_HAS_PRIMS | FLAG_UNK_2000;
            self->primIndex = g_Dialogue.primIndex[2];
            self->step++;
        }
        break;
    case 1:
        while (1) {
            if ((g_Dialogue.nextCharTimer != 0) && !D_us_801AE850) {
                g_Dialogue.nextCharTimer--;
                return;
            }
            nextChar = *g_Dialogue.scriptCur++;
            switch (nextChar) {
            case CSOP_END_CUTSCENE:
#ifdef VERSION_PC
                PcQolSceneEnd(g_StageId * 8 + (g_CurrentEntity->params & 7));
#endif
                self->step = 7;
                return;
            case CSOP_LINE_BREAK:
#ifdef VERSION_PC
                PcQolDialogueChar('\n');
#endif
                if (D_us_801AE850) {
                    continue;
                }
                g_Dialogue.nextCharX = g_Dialogue.nextLineX;
                if (!(g_Dialogue.unk12 & 1)) {
                    g_Dialogue.nextLineY += 12;
                }
                g_Dialogue.nextCharY++;
                if (g_Dialogue.nextCharY >= 5) {
                    g_Dialogue.nextCharY = 0;
                }
                CutsceneUnk4();
                if (!(g_Dialogue.unk12 & 1)) {
                    if (g_Dialogue.nextCharY >= 4) {
                        g_Dialogue.unk12 |= 1;
                        g_Dialogue.portraitAnimTimer = 0;
                        self->step_s = 0;
                        self->step++;
                        return;
                    }
                    continue;
                }
                g_Dialogue.portraitAnimTimer = 0;
                self->step_s = 0;
                self->step++;
                return;
            case CSOP_SET_SPEED:
                g_Dialogue.unk17 = *g_Dialogue.scriptCur++;
                continue;
            case CSOP_SET_WAIT:
                g_Dialogue.nextCharTimer = *g_Dialogue.scriptCur++;
                if (D_us_801AE850) {
                    continue;
                }
                return;
            case CSOP_HIDE_DIALOG:
                if (D_us_801AE850) {
                    continue;
                }
                prim = g_Dialogue.prim[0];
                for (i = 0; i < 5; i++) {
                    prim->drawMode = DRAW_HIDE;
                    prim = prim->next;
                }
                return;
            case CSOP_SET_PORTRAIT:
                if (D_us_801AE850) {
                    g_Dialogue.scriptCur += 2;
                    continue;
                }
                i = *g_Dialogue.scriptCur++;
                nextChar2 = *g_Dialogue.scriptCur++;
                prim = g_Dialogue.prim[5];
                uCoord = D_us_80180B60[nextChar2 & 1];
                vCoord = D_us_80180B64[nextChar2 & 1];
                prim->clut = D_us_80180B68[i];
                prim->tpage = 0x90;
                if (nextChar2 & 0x80) {
                    prim->u0 = prim->u2 = uCoord + 0x2F;
                    prim->u1 = prim->u3 = uCoord;
                } else {
                    prim->u0 = prim->u2 = uCoord;
                    prim->u1 = prim->u3 = uCoord + 0x2F;
                }
                prim->v0 = prim->v1 = vCoord;
                prim->v2 = prim->v3 = vCoord + 0x48;
                prim->x0 = prim->x1 = prim->x2 = prim->x3 =
                    g_Dialogue.startX - 0x1E;
                prim->y0 = prim->y1 = prim->y2 = prim->y3 =
                    g_Dialogue.startY + 0x24;
                g_Dialogue.clutIndex = D_us_80180B70[i];
                CutsceneUnk1();
                CutsceneUnk4();
                prim->priority = 0x1FE;
                prim->drawMode = DRAW_DEFAULT;
                DrawCutsceneActorName(i, self);
                g_Dialogue.portraitAnimTimer = 6;
                self->step = 3;
                return;
            case CSOP_NEXT_DIALOG:
                if (D_us_801AE850) {
                    continue;
                }
                for (prim = g_Dialogue.prim[0], i = 0; i < 5; i++) {
                    prim->drawMode = DRAW_HIDE;
                    prim = prim->next;
                }
                g_api.FreePrimitives(g_Dialogue.primIndex[1]);
                g_Dialogue.primIndex[1] = -1;
                g_Dialogue.portraitAnimTimer = 6;
                self->step = 4;
                return;
            case CSOP_SET_POS:
                if (D_us_801AE850) {
                    g_Dialogue.scriptCur++;
                    g_Dialogue.scriptCur++;
                    continue;
                }
                g_Dialogue.startX = *g_Dialogue.scriptCur++;
                g_Dialogue.startY = *g_Dialogue.scriptCur++;
                prim = g_Dialogue.prim[5];
                prim = prim->next;
                prim->y0 = prim->y1 = g_Dialogue.startY;
                prim->y2 = prim->y3 = g_Dialogue.startY + 0x48;
                prim = prim->next;
                prim->y0 = g_Dialogue.startY - 1;
                prim->u0 = 0xF6;
                g_Dialogue.portraitAnimTimer = 0x18;
                self->step = 5;
                self->step_s = 0;
                return;
            case CSOP_CLOSE_DIALOG:
                if (D_us_801AE850) {
                    continue;
                }
                g_Dialogue.portraitAnimTimer = 0x18;
                self->step = 6;
                return;
            case CSOP_PLAY_SOUND:
                if (D_us_801AE850) {
                    g_Dialogue.scriptCur++;
                    g_Dialogue.scriptCur++;
                    continue;
                }
                nextChar = *g_Dialogue.scriptCur++;
                nextChar <<= 4;
                nextChar |= *g_Dialogue.scriptCur++;
                g_api.PlaySfx(nextChar);
                continue;
            case CSOP_WAIT_FOR_SOUND:
                if (D_us_801AE850) {
                    continue;
                }
                if (g_api.func_80131F68() != false) {
                    continue;
                }
                *g_Dialogue.scriptCur--;
                return;
            case CSOP_SCRIPT_UNKNOWN_11:
                if (D_us_801AE850) {
                    continue;
                }
                if (g_api.func_80131F68() != true) {
                    continue;
                }
                *g_Dialogue.scriptCur--;
                return;
            case CSOP_SET_EVENTS:
                ptr = (u_long)*g_Dialogue.scriptCur++;
                ptr <<= 4;
                ptr |= (u_long)*g_Dialogue.scriptCur++;
                ptr <<= 4;
                ptr |= (u_long)*g_Dialogue.scriptCur++;
                ptr <<= 4;
                ptr |= (u_long)*g_Dialogue.scriptCur++;
                SetCutsceneEvents((u8*)ptr);
                continue;
            case CSOP_SCRIPT_UNKNOWN_13:
                continue;
            case CSOP_SCRIPT_SWITCH:
                ptr = (u_long)*g_Dialogue.scriptCur++;
                ptr <<= 4;
                ptr |= (u_long)*g_Dialogue.scriptCur++;
                ptr <<= 4;
                ptr |= (u_long)*g_Dialogue.scriptCur++;
                ptr <<= 4;
                ptr |= (u_long)*g_Dialogue.scriptCur++;
                g_Dialogue.scriptCur += *CS_PTR(ptr) << 2;

                ptr = (u_long)*g_Dialogue.scriptCur++;
                ptr <<= 4;
                ptr |= (u_long)*g_Dialogue.scriptCur++;
                ptr <<= 4;
                ptr |= (u_long)*g_Dialogue.scriptCur++;
                ptr <<= 4;
                ptr |= (u_long)*g_Dialogue.scriptCur;
                g_Dialogue.scriptCur = CS_PTR(ptr);
                continue;
            case CSOP_SCRIPT_UNKNOWN_15:
                ptr = (u_long)*g_Dialogue.scriptCur++;
                ptr <<= 4;
                ptr |= (u_long)*g_Dialogue.scriptCur++;
                ptr <<= 4;
                ptr |= (u_long)*g_Dialogue.scriptCur++;
                ptr <<= 4;
                ptr |= (u_long)*g_Dialogue.scriptCur;
                g_Dialogue.scriptCur = CS_PTR(ptr);
                continue;
            case CSOP_WAIT_FOR_FLAG:
                if (!((g_CutsceneFlags >> *g_Dialogue.scriptCur) & 1)) {
                    g_Dialogue.scriptCur--;
                    return;
                }
                g_CutsceneFlags &= ~(1 << *g_Dialogue.scriptCur);
                *g_Dialogue.scriptCur++;
                continue;
            case CSOP_SET_FLAG:
                g_CutsceneFlags |= 1 << *g_Dialogue.scriptCur++;
                continue;
            case CSOP_STOP_EVENTS:
                g_Dialogue.hasEvents = 0;
                continue;
            case CSOP_LOAD_PORTRAIT:
                if (D_us_801AE850) {
                    g_Dialogue.scriptCur += 5;
                } else {
                    ptr = (u_long)*g_Dialogue.scriptCur++;
                    ptr <<= 4;
                    ptr |= (u_long)*g_Dialogue.scriptCur++;
                    ptr <<= 4;
                    ptr |= (u_long)*g_Dialogue.scriptCur++;
                    ptr <<= 4;
                    ptr |= (u_long)*g_Dialogue.scriptCur++;
#ifdef VERSION_PC
                    ptr = (uintptr_t)CS_PTR(ptr);
#else
                    ptr += 0x100000;
#endif
                    nextChar2 = g_Dialogue.scriptCur++[0];
                    LoadTPage((u_long*)ptr, 1, 0, D_us_80180B6C[nextChar2],
                              0x100, 48, 72);
                }
                continue;
            case CSOP_SCRIPT_UNKNOWN_20:
                nextChar = *g_Dialogue.scriptCur++;
                nextChar <<= 4;
                nextChar |= *g_Dialogue.scriptCur++;
                g_api.PlaySfx(nextChar);
                continue;
            case CSOP_SCRIPT_UNKNOWN_21:
                g_CutsceneFlags = 0;
                D_us_801AE850 = 0;
                D_us_801AE904 = 0;
                continue;
            case CSOP_SCRIPT_UNKNOWN_22:
                g_CutsceneFlags &= ~(1 << *g_Dialogue.scriptCur++);
                continue;
            case CSOP_SCRIPT_UNKNOWN_23:
                return;
            case CSOP_WAIT_FOR_FLAG_RESET:
                if (!((g_CutsceneFlags >> *g_Dialogue.scriptCur) & 1)) {
                    *g_Dialogue.scriptCur--;
                    return;
                }
                *g_Dialogue.scriptCur++;
                continue;
            default:
                if (D_us_801AE850) {
                    continue;
                }
                g_Dialogue.nextCharTimer = g_Dialogue.unk17;
            }
            break;
        }

#ifdef VERSION_PC
        PcQolDialogueChar(nextChar);
#endif
        if (nextChar == 0x20) {
            g_Dialogue.nextCharX += 2;
            return;
        }
        rect.x = ((nextChar & 0xF) * 2) + 0x380;
        rect.y = ((u32)(nextChar & 0xF0) >> 1) + 0xF0;
        rect.w = 2;
        rect.h = 8;
        vCoord = (g_Dialogue.nextCharY * 0xC) + 0x180;
        MoveImage(&rect, g_Dialogue.nextCharX, vCoord);
        g_Dialogue.nextCharX += 2;
        break;
    case 2:
        ScaleCutsceneAvatar(2);
        if (g_Dialogue.portraitAnimTimer >= 6) {
            self->step -= 1;
            return;
        }
        break;
    case 3:
        prim = g_Dialogue.prim[5];
        prim->x0 = prim->x2 -= 4;
        prim->x1 = prim->x3 += 4;
        prim->y0 = prim->y1 -= 6;
        prim->y2 = prim->y3 += 6;
        g_Dialogue.portraitAnimTimer--;
        if (!g_Dialogue.portraitAnimTimer) {
            self->step = 1;
            for (prim = &g_PrimBuf[g_Dialogue.primIndex[1]]; prim != NULL;
                 prim = prim->next) {
                prim->drawMode = DRAW_DEFAULT;
            }
        }
        break;
    case 4:
        prim = g_Dialogue.prim[5];
        prim->x0 = prim->x2 += 4;
        prim->x1 = prim->x3 -= 4;
        prim->y0 = prim->y1 += 6;
        prim->y2 = prim->y3 -= 6;
        if (prim->x1 >= (g_Dialogue.startX - 2)) {
            prim->x1 = prim->x3 = g_Dialogue.startX - 3;
        }
        g_Dialogue.portraitAnimTimer--;
        if (!g_Dialogue.portraitAnimTimer) {
            self->step = 1;
            return;
        }
        break;
    case 5:
        switch (self->step_s) {
        case 0:
            D_us_801AE904 = 1;
            primIndex = g_api.AllocPrimitives(PRIM_LINE_G2, 0x48);
            if (primIndex == -1) {
                DestroyEntity(self);
                return;
            }
            g_Dialogue.primIndex[0] = primIndex;
            for (prim = &g_PrimBuf[primIndex], j = 0; prim != NULL;
                 prim = prim->next) {
                prim->r0 = prim->r1 = 0x7F;
                prim->b0 = prim->b1 = prim->g0 = prim->g1 = 0;
                prim->x0 = prim->x1 = 0xF7;
                prim->y0 = prim->y1 = g_Dialogue.startY + j;
                prim->priority = 0x1FE;
                prim->drawMode = DRAW_DEFAULT;
                prim->x2 = D_us_80180B78[j];
                prim->x3 = 0xF70;

                j++;
            }
            self->step_s++;
            return;
        case 1:
            for (j = 0, prim = &g_PrimBuf[g_Dialogue.primIndex[0]];
                 prim != NULL; prim = prim->next) {
                prim->x3 -= prim->x2;
                prim->x2 += 2;
                prim->x0 = prim->x3 / 16;
                if (prim->x0 < 5) {
                    prim->x0 = 4;
                } else {
                    j = 1;
                }
            }
            if (j == 0) {
                g_api.FreePrimitives(g_Dialogue.primIndex[0]);
                g_Dialogue.primIndex[0] = -1;
                prim = g_Dialogue.prim[5];
                prim = prim->next;
                prim->drawMode = DRAW_TPAGE | DRAW_TRANSP;
                prim = prim->next;
                prim->drawMode = DRAW_UNK_40 | DRAW_TPAGE | DRAW_TRANSP;
                self->step_s++;
                return;
            }
            break;
        case 2:
            j = 0;
            prim = g_Dialogue.prim[5];
            prim = prim->next;
            if (prim->r0 < 0x10) {
                prim->r0 = prim->r1 = prim->r2 = prim->r3 = 0;
            } else {
                prim->r0 = prim->r1 = prim->r2 = prim->r3 -= 0x10;
                j = 1;
            }
            if (prim->b0 >= 0x7F) {
                prim->b0 = prim->b1 = 0x7F;
            } else {
                prim->b0 = prim->b1 += 8;
                j = 1;
            }

            prim = prim->next;
            if (prim->r0 < 0x10) {
                prim->r0 = prim->g0 = prim->b0 = 0x10;
            } else {
                prim->r0 = prim->g0 = prim->b0 -= 0xF;
                j = 1;
            }
            if (j == 0) {
                self->step = 1;
            }
        }
        break;
    case 6:
        prim = g_Dialogue.prim[5];
        prim = prim->next;
        g_Dialogue.portraitAnimTimer--;
        if (g_Dialogue.portraitAnimTimer >= 0xC) {
            prim = prim->next;
            prim->u0 -= 20;
            if (g_Dialogue.portraitAnimTimer & 1) {
                prim->u0--;
                return;
            }
        } else {
            if (!g_Dialogue.portraitAnimTimer) {
                self->step = 1;
                prim->drawMode = DRAW_HIDE;
            } else {
                prim->y2 = (prim->y3 -= 6);
            }
            prim = prim->next;
            prim->drawMode = DRAW_HIDE;
            return;
        }
        break;

    case 7:
        DestroyEntity(self);
        g_CastleFlags[DEATH_FIGHT_CS] = 1;
        g_CutsceneHasControl = false;
        g_Settings.D_8003CB04 |= 0x40000;
        break;
    }
}
