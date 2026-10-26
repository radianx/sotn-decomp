// SPDX-License-Identifier: AGPL-3.0-or-later
#include "bo6.h"

extern AnimationFrame D_us_80181F1C[];
extern AnimationFrame D_us_80182130[];
extern AnimationFrame D_us_801822B8[];

void RicStepStand(void) {
    s32 facing;

    if (!RicCheckInput(CHECK_FALL | CHECK_FACING | CHECK_JUMP | CHECK_CRASH |
                       CHECK_ATTACK | CHECK_CROUCH | CHECK_SLIDE)) {
        DecelerateX(FIX(0.125));
        switch (RIC.step_s) {
        case 0:
            if (RicCheckFacing()) {
                func_us_801B9DE4(0);
            } else if (g_Ric.padPressed & PAD_UP) {
                RicSetAnimation(D_us_80181F1C);
                RIC.step_s = 1;
                break;
            }
            break;
        case 1:
            if (RicCheckFacing()) {
                func_us_801B9DE4(0);
            } else if (g_Ric.padPressed & PAD_UP) {
            } else {
                RicSetStand(0);
            }
            break;
        case 64:
            DisableAfterImage(1, 1);
            if (RIC.pose < 3) {
                facing = RicCheckFacing();
                if (g_Ric.padPressed & PAD_DOWN) {
                    RIC.step = PL_S_CROUCH;
                    RIC.anim = D_us_80182130;
                    break;
                }
            }

            if (RIC.poseTimer < 0) {
                if (g_Ric.padPressed & PAD_SQUARE) {
                    RIC.step_s++;
                    g_Ric.unk46 = 2;
                    RicSetAnimation(D_us_801822B8);
                    RicCreateEntFactoryFromEntity(
                        g_CurrentEntity, BP_ARM_BRANDISH_WHIP, 0);
                    break;
                }
                g_Ric.unk46 = 0;
                RicSetStand(0);
            }
            break;
        case 65:
            DisableAfterImage(1, 1);
            if (g_Ric.padPressed & PAD_SQUARE) {
                break;
            }
            g_Ric.unk46 = 0;
            RicSetStand(0);
            break;
        case 66:
            DisableAfterImage(1, 1);
            if (RIC.pose < 3) {
                RicCheckFacing();
            }
            if (RIC.poseTimer < 0) {
                g_Ric.unk46 = 0;
                RicSetStand(0);
            }
            break;
        }
    }
}

void RicStepWalk(void) {
    if (RicCheckInput(CHECK_FALL | CHECK_FACING | CHECK_JUMP | CHECK_CRASH |
                      CHECK_ATTACK | CHECK_CROUCH) == 0) {
        DecelerateX(FIX(0.125));
        if (RicCheckFacing() == 0) {
            RicSetStand(0);
            return;
        }
        if (RIC.step_s == 0) {
            RicSetSpeedX(FIX(1.25));
        }
    }
}

extern AnimationFrame D_us_80181F24[];

void RicStepRun(void) {
    g_Ric.timers[PL_T_8] = 8;
    g_Ric.timers[PL_T_CURSE] = 8;
    if (RicCheckInput(0x305C) == 0) {
        DecelerateX(FIX(0.125));
        if (RicCheckFacing() == 0) {
            RicSetStand(0);
            if (g_Ric.timers[PL_T_RUN] == 0) {
                if (!(g_Ric.vram_flag & (TOUCHING_L_WALL | TOUCHING_R_WALL))) {
                    RicSetAnimation(&D_us_80181F24);
                    RicCreateEntFactoryFromEntity(g_CurrentEntity, 0, 0);
                }
            } else {
                RIC.velocityX = 0;
            }
        } else if (RIC.step_s == 0) {
            RicSetSpeedX(FIX(2.25));
        }
    }
}

extern AnimationFrame D_us_801820E4[];
extern AnimationFrame D_us_801822C8[];
extern AnimationFrame D_us_801820B0[];

void RicStepJump(void) {
    s32 facing;

    if ((g_Ric.vram_flag & TOUCHING_CEILING) && (RIC.velocityY < FIX(-1))) {
        RIC.velocityY = FIX(-0.25);
        g_Ric.unk44 |= 0x20;
    }
    if (RicCheckInput(
            CHECK_GROUND | CHECK_FACING | CHECK_ATTACK | CHECK_GRAVITY_JUMP)) {
        return;
    }
    switch (RIC.step_s) {
    case 0:
        DecelerateX(FIX(0.0625));
        facing = RicCheckFacing();
        if (facing) {
            if (g_Ric.unk44 & 0x10) {
                RicSetSpeedX(FIX(2.25));
            } else {
                RicSetSpeedX(FIX(1.25));
            }
            g_Ric.unk44 &= ~4;
        } else {
            g_Ric.unk44 &= ~0x10;
            if ((RIC.pose < 2) && !(g_Ric.unk44 & 8) && (g_Ric.unk44 & 4) &&
                (g_Ric.padTapped & PAD_CROSS)) {
                RicSetAnimation(D_us_801820E4);
                RicSetSpeedX(FIX(-1.5));
                RIC.velocityY = FIX(-2.625);
                g_Ric.unk44 |= 0xA;
                g_Ric.unk44 &= ~4;
                RIC.step_s = 2;
            }
        }
        break;
    case 2:
        break;
    case 0x40:
        DisableAfterImage(1, 1);
        if (RIC.pose < 3) {
            facing = RicCheckFacing();
            if (facing) {
                if (g_Ric.unk44 & 0x10) {
                    RicSetSpeedX(FIX(2.25));
                } else {
                    RicSetSpeedX(FIX(1.25));
                }
                g_Ric.unk44 &= ~4;
            } else {
                g_Ric.unk44 &= ~0x10;
            }
        } else {
            if (((g_Ric.padPressed & PAD_RIGHT) && RIC.facingLeft == 0) ||
                ((g_Ric.padPressed & PAD_LEFT) && RIC.facingLeft)) {
                if (g_Ric.unk44 & 0x10) {
                    RicSetSpeedX(FIX(2.25));
                } else {
                    RicSetSpeedX(FIX(1.25));
                }
                RicSetSpeedX(FIX(1.25));
                g_Ric.unk44 &= ~4;
            } else {
                g_Ric.unk44 &= ~0x10;
            }
        }
        if (RIC.poseTimer < 0) {
            if (g_Ric.padPressed & PAD_SQUARE) {
                RIC.step_s += 1;
                g_Ric.unk46 = 2;
                RicSetAnimation(D_us_801822C8);
                RicCreateEntFactoryFromEntity(
                    g_CurrentEntity, BP_ARM_BRANDISH_WHIP, 0);
            } else {
                g_Ric.unk46 = 0;
                RIC.step_s = 0;
                RicSetAnimation(D_us_801820B0);
            }
        }
        break;
    case 0x41:
        DisableAfterImage(1, 1);
        if (!(g_Ric.padPressed & PAD_SQUARE)) {
            g_Ric.unk46 = 0;
            RIC.step_s = 0;
            RicSetAnimation(D_us_801820B0);
        }
        break;
    case 0x42:
        DisableAfterImage(1, 1);
        if (RIC.pose < 3) {
            facing = RicCheckFacing();
            if (facing) {
                if (g_Ric.unk44 & 0x10) {
                    RicSetSpeedX(FIX(2.25));
                } else {
                    RicSetSpeedX(FIX(1.25));
                }
                g_Ric.unk44 &= ~4;
            } else {
                g_Ric.unk44 &= ~0x10;
            }
        } else {
            if (((g_Ric.padPressed & PAD_RIGHT) && RIC.facingLeft == 0) ||
                ((g_Ric.padPressed & PAD_LEFT) && RIC.facingLeft)) {
                if (g_Ric.unk44 & 0x10) {
                    RicSetSpeedX(FIX(2.25));
                } else {
                    RicSetSpeedX(FIX(1.25));
                }
                RicSetSpeedX(FIX(1.25));
                g_Ric.unk44 &= ~4;
            } else {
                g_Ric.unk44 &= ~0x10;
            }
        }
        if (RIC.poseTimer < 0) {
            g_Ric.unk46 = 0;
            RIC.step_s = 0;
            RicSetAnimation(D_us_801820B0);
        }
        break;
    }
}

void RicStepFall(void) {
    if (RicCheckInput(
            CHECK_GROUND | CHECK_FACING | CHECK_ATTACK | CHECK_GRAVITY_FALL)) {
        return;
    }
    DecelerateX(FIX(1. / 16));
    if (RIC.step_s == 0) {
        if (g_Ric.timers[PL_T_5] && g_Ric.padTapped & PAD_CROSS) {
            func_us_801B9E70();
            return;
        }
        if (RicCheckFacing()) {
            RicSetSpeedX(FIX(0.75));
        }
    }
}

extern AnimationFrame D_us_80182068[];
extern AnimationFrame D_us_80182048[];
extern AnimationFrame D_us_80182110[];
extern AnimationFrame D_us_801822C0[];

void RicStepCrouch(void) {
    // Retain the original stack frame.
    u8 padding[0x28];
    s32 facing;

    if (RicCheckInput(CHECK_FALL | CHECK_FACING | CHECK_JUMP | CHECK_CRASH |
                      CHECK_ATTACK | CHECK_SLIDE)) {
        return;
    }
    DecelerateX(FIX(0.125));
    switch (RIC.step_s) {
    case 0x0:
        if (!(g_Ric.padPressed & PAD_DOWN)) {
            RicSetAnimation(D_us_80182068);
            RIC.step_s = 2;
            return;
        }
        break;
    case 0x1:
        if (!(g_Ric.padPressed & PAD_DOWN)) {
            if (RicCheckFacing()) {
                func_us_801B9DE4(0);
                return;
            }
            RIC.anim = D_us_80182068;
            RIC.step_s = 2;
            RIC.pose = 2 - RIC.pose;
            RIC.poseTimer = 1;
            break;
        }
    case 0x4:
        if (RIC.poseTimer != -1) {
            return;
        }
        RicSetAnimation(D_us_80182048);
        RIC.step_s = 0;
        break;
    case 0x2:
        if (RicCheckFacing()) {
            func_us_801B9DE4(0);
            return;
        }
        if (RIC.poseTimer == -1) {
            RicSetStand(0);
            return;
        }
        break;
    case 0x3:
        if (RIC.poseTimer < 0) {
            RicSetAnimation(D_us_80182048);
            RIC.step_s = 0;
            return;
        }
        break;
    case 0x40:
        DisableAfterImage(1, 1);
        if (RIC.pose < 3) {
            facing = RicCheckFacing();
            if (!(g_Ric.padPressed & PAD_DOWN)) {
                RIC.step = PL_S_STAND;
                RIC.anim = D_us_80182110;
                return;
            }
        }
        if (RIC.poseTimer < 0) {
            if (g_Ric.padPressed & PAD_SQUARE) {
                RIC.step_s++;
                g_Ric.unk46 = 2;
                RicSetAnimation(D_us_801822C0);
                RicCreateEntFactoryFromEntity(
                    g_CurrentEntity, BP_ARM_BRANDISH_WHIP, 0);
                return;
            }
            g_Ric.unk46 = 0;
            RIC.step_s = 0;
            RicSetAnimation(D_us_80182048);
        }
        break;
    case 0x41:
        DisableAfterImage(1, 1);
        if (!(g_Ric.padPressed & PAD_SQUARE)) {
            g_Ric.unk46 = 0;
            RIC.step_s = 0;
            RicSetAnimation(D_us_80182048);
        }
        break;
    }
}

void RicResetPose(void) {
    RIC.poseTimer = 0;
    RIC.pose = 0;
    g_Ric.unk44 = 0;
    g_Ric.unk46 = 0;
    RIC.drawFlags &= ~ENTITY_ROTATE;
}

void func_us_801B77D8(void) {
    if ((RIC.posX.i.hi - PLAYER.posX.i.hi) <= 0) {
        RIC.entityRoomIndex = 0;
    } else {
        RIC.entityRoomIndex = 1;
    }
}

extern AnimationFrame D_us_8018224C[];
extern AnimationFrame D_us_80182224[];
extern AnimationFrame D_us_8018228C[];
extern AnimationFrame D_us_8018221C[];

void RicStepHit(s32 damageEffect, u32 damageKind, s16 prevStep, s32 prevStepS) {
    switch (RIC.step_s) {
    case 0:
        RicResetPose();
        if (damageKind < DAMAGEKIND_16) {
            func_us_801B77D8();
        } else {
            RIC.entityRoomIndex = RIC.facingLeft;
        }
        if (damageEffect & ELEMENT_THUNDER) {
            RicCreateEntFactoryFromEntity(
                g_CurrentEntity, BP_HIT_BY_THUNDER, 0);
            RIC.velocityY = FIX(-4);
            func_us_801B9ACC(FIX(-1.25));
            RIC.step_s = 1;
            RIC.anim = D_us_8018224C;
            g_Ric.damagePalette = PAL_FLAG(0x220);
            RicCreateEntFactoryFromEntity(
                g_CurrentEntity, BP_HIT_BY_THUNDER, 0);
            RicCreateEntFactoryFromEntity(
                g_CurrentEntity, FACTORY(BP_RIC_BLINK, 0x46), 0);
            g_Ric.timers[PL_T_2] = 6;
            g_api.PlaySfx(SFX_BOSS_RIC_PAIN_F);
            break;
        } else {
            if (damageEffect & ELEMENT_ICE) {
                damageKind = DAMAGEKIND_3;
            }
            switch (damageKind) {
            case 2:
                switch (prevStep) {
                case PL_S_STAND:
                case PL_S_WALK:
                    RIC.velocityY = 0;
                    func_us_801B9ACC(FIX(-1.25));
                    RIC.step_s = 6;
                    RIC.anim = D_us_80182224;
                    g_api.PlaySfx(SFX_BOSS_RIC_PAIN_B);
                    RicCreateEntFactoryFromEntity(
                        g_CurrentEntity, BP_SKID_SMOKE, 0);
                    break;
                case PL_S_CROUCH:
                    RIC.velocityY = 0;
                    func_us_801B9ACC(FIX(-1.25));
                    RIC.step_s = 7;
                    RIC.anim = D_us_8018228C;
                    RicCreateEntFactoryFromEntity(
                        g_CurrentEntity, BP_SKID_SMOKE, 0);
                    g_api.PlaySfx(SFX_BOSS_RIC_PAIN_A);
                    break;
                case PL_S_JUMP:
                case PL_S_FALL:
                    RIC.velocityY = FIX(-3);
                    func_us_801B9ACC(FIX(-1.25));
                    RIC.step_s = 1;
                    RIC.anim = D_us_8018221C;
                    g_api.PlaySfx(SFX_BOSS_RIC_PAIN_C);
                    break;
                }
                break;
            case 4:
            default:
            case 16:
            case 3:
                switch (prevStep) {
                default:
                case PL_S_STAND:
                case PL_S_WALK:
                    RIC.velocityY = FIX(-4);
                    func_us_801B9ACC(FIX(-1.25));
                    RIC.step_s = 1;
                    RIC.anim = D_us_8018221C;
                    g_api.PlaySfx(SFX_BOSS_RIC_PAIN_D);
                    break;
                case PL_S_CROUCH:
                    RIC.velocityY = 0;
                    func_us_801B9ACC(FIX(-1.25));
                    RIC.step_s = 7;
                    RIC.anim = D_us_8018228C;
                    RicCreateEntFactoryFromEntity(
                        g_CurrentEntity, BP_SKID_SMOKE, 0);
                    g_api.PlaySfx(SFX_BOSS_RIC_PAIN_E);
                    break;
                case PL_S_JUMP:
                case PL_S_FALL:
                    RIC.velocityY = FIX(-3);
                    func_us_801B9ACC(FIX(-1.25));
                    RIC.step_s = 1;
                    RIC.anim = D_us_8018221C;
                    g_api.PlaySfx(SFX_VO_RIC_PAIN_B);
                    g_api.PlaySfx(SFX_BOSS_RIC_PAIN_E);
                    break;
                }
                break;
            }
            g_Ric.damagePalette = PAL_FLAG(PAL_CC_RED_EFFECT_A);
            g_Ric.timers[PL_T_2] = 6;
            if (damageEffect & ELEMENT_FIRE) {
                RicCreateEntFactoryFromEntity(
                    g_CurrentEntity, FACTORY(BP_HIT_BY_FIRE, 1), 0);
                RicCreateEntFactoryFromEntity(g_CurrentEntity, 9, 0);
                RicCreateEntFactoryFromEntity(
                    g_CurrentEntity, FACTORY(BP_RIC_BLINK, 0x43), 0);
                g_Ric.damagePalette = PAL_FLAG(PAL_CC_FIRE_EFFECT);
                g_Ric.timers[PL_T_2] = 0x10;
                break;
            } else if (damageEffect & ELEMENT_ICE) {
                RicCreateEntFactoryFromEntity(
                    g_CurrentEntity, BP_HIT_BY_ICE, 0);
                g_Ric.timers[PL_T_2] = 0xC;
                g_Ric.damagePalette = PAL_FLAG(PAL_CC_BLUE_EFFECT_A);
                break;
            } else {
                if (damageEffect & ELEMENT_DARK) {
                    RicCreateEntFactoryFromEntity(
                        g_CurrentEntity, BP_HIT_BY_DARK, 0);
                    RicCreateEntFactoryFromEntity(
                        g_CurrentEntity, FACTORY(BP_RIC_BLINK, 0x56), 0);
                    g_Ric.timers[PL_T_2] = 0x10;
                    g_Ric.damagePalette = PAL_FLAG(PAL_CC_DARK_EFFECT);
                    break;
                }
                if (damageEffect & ELEMENT_HOLY) {
                    RicCreateEntFactoryFromEntity(
                        g_CurrentEntity, BP_HIT_BY_HOLY, 0);
                    RicCreateEntFactoryFromEntity(
                        g_CurrentEntity, FACTORY(BP_RIC_BLINK, 0x57), 0);
                    g_Ric.timers[PL_T_2] = 8;
                    g_Ric.damagePalette = PAL_FLAG(PAL_CC_GREEN_EFFECT_A);
                    break;
                }
                if (!(damageEffect & 0xF840)) {
                    RicCreateEntFactoryFromEntity(
                        g_CurrentEntity, FACTORY(BP_RIC_BLINK, 0x53), 0);
                }
            }
        }
        break;
    case 1:
        if ((g_Ric.vram_flag & TOUCHING_CEILING) && (RIC.velocityY < FIX(-1))) {
            RIC.velocityY = FIX(-1);
        }
        if (RicCheckInput(
                CHECK_80 | CHECK_GRAVITY_HIT | CHECK_GROUND_AFTER_HIT)) {
            return;
        }
        break;
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
        DecelerateX(FIX(0.125));
        if (!(g_Ric.vram_flag & TOUCHING_GROUND)) {
            RicSetFall();
        }
        if (RIC.poseTimer < 0) {
            if (g_Ric.unk5C) {
                if (g_Status.hp < 20) {
                    RicSetDeadPrologue();
                    return;
                }
                RicSetStand(RIC.velocityX);
            } else {
                RicSetStand(RIC.velocityX);
            }
        }
        break;
    case 7:
        DecelerateX(FIX(0.125));
        if (!(g_Ric.vram_flag & TOUCHING_GROUND)) {
            RicSetFall();
        }
        if (RIC.poseTimer < 0) {
            if (g_Ric.unk5C) {
                if (g_Status.hp < 20) {
                    RicSetDeadPrologue();
                    return;
                }
                RicSetCrouch(0, RIC.velocityX);
            } else {
                RicSetCrouch(0, RIC.velocityX);
            }
        }
        break;
    }
}

enum DeathKind { DEATH_GENERIC, DEATH_BY_FIRE, DEATH_BY_THUNDER, DEATH_BY_ICE };
extern u8 D_us_801CF3E8[0x1400];
extern s16 D_us_801D07E8;
extern s16 D_us_801D07EC;
extern enum DeathKind D_us_801D07F0;
extern s32 D_us_801D07F4;
extern s32 D_us_80181278;
extern RECT D_us_8018127C;
extern AnimationFrame D_us_801820CC[];

void RicStepDead(
    s32 damageEffects, s32 damageKind, s32 prevStep, s32 prevStepS) {
    s32 j;
    s32 i;
    u8* s2;
    u8* imgPtr;
    s32 disableColorChange = 0;
    PlayerDraw* playerDraw = &g_PlayerDraw[8];

    switch (RIC.step_s) {
    case 0:
        RicResetPose();
        func_us_801B77D8();
        func_us_801B9ACC(FIX(-0.75));
        RicSetAnimation(D_us_801820CC);
        RIC.velocityY = FIX(-1.625);
        g_api.PlaySfx(SFX_BOSS_RIC_DEATH);
        D_us_801D07F4 = damageEffects;
        RIC.step_s++;
        if (!g_CastleFlags[SHAFT_ORB_DEFEATED] && !g_DemoMode) {
            CreateEntityFromCurrentEntity(E_ID_17, &g_Entities[200]);
            g_Entities[200].params = 2;
            g_Entities[200].flags = FLAG_UNK_10000;
        }
        D_us_80181278 = 10;
        RIC.palette = PAL_FLAG(0x220);
        return;
    case 1:
        if (D_us_801D07F4 & ELEMENT_FIRE) {
            func_us_801BB314(0);
            RicCreateEntFactoryFromEntity(
                g_CurrentEntity, FACTORY(BP_RIC_BLINK, 0x48), 0);
            RicCreateEntFactoryFromEntity(
                g_CurrentEntity, FACTORY(BP_DEATH_BY_FIRE, 2), 0);
            D_us_801D07F0 = DEATH_BY_FIRE;
        } else if (D_us_801D07F4 & ELEMENT_THUNDER) {
            func_us_801BB314(2);
            RicCreateEntFactoryFromEntity(
                g_CurrentEntity, FACTORY(BP_RIC_BLINK, 0x4C), 0);
            RicCreateEntFactoryFromEntity(
                g_CurrentEntity, FACTORY(BP_HIT_BY_THUNDER, 1), 0);
            RicCreateEntFactoryFromEntity(
                g_CurrentEntity, FACTORY(BP_HIT_BY_THUNDER, 2), 0);
            D_us_801D07F0 = DEATH_BY_THUNDER;
        } else if (D_us_801D07F4 & ELEMENT_ICE) {
            func_us_801BB314(3);
            RicCreateEntFactoryFromEntity(
                g_CurrentEntity, FACTORY(BP_RIC_BLINK, 0x4D), 0);
            RicCreateEntFactoryFromEntity(g_CurrentEntity, 47, 0);
            RicCreateEntFactoryFromEntity(
                g_CurrentEntity, FACTORY(BP_HIT_BY_ICE, 1), 0);
            D_us_801D07F0 = DEATH_BY_ICE;
            RIC.blendMode = BLEND_TRANSP | BLEND_ADD;
        } else {
            func_us_801BB314(1);
            RicCreateEntFactoryFromEntity(
                g_CurrentEntity, FACTORY(BP_RIC_BLINK, 0x4A), 0);
            RicCreateEntFactoryFromEntity(
                g_CurrentEntity, FACTORY(BP_MULTIPLE_EMBERS, 5), 0);
            D_us_801D07F0 = DEATH_GENERIC;
        }
        playerDraw->r0 = playerDraw->g0 = playerDraw->b0 = playerDraw->r1 =
            playerDraw->g1 = playerDraw->b1 = playerDraw->r2 = playerDraw->g2 =
                playerDraw->b2 = playerDraw->r3 = playerDraw->g3 =
                    playerDraw->b3 = 0x80;
        playerDraw->enableColorBlend = 1;
        RIC.step_s++;
        break;
    case 2:
        if (RIC.pose != 4) {
            break;
        }
        RIC.step_s++;
        break;
    case 3:
        // Unusual, FIX usually has denominator of 128
        RIC.velocityY += FIX(11.0 / 256);
        if (RIC.velocityY > FIX(1.0 / 16)) {
            RIC.velocityY >>= 2;
            RIC.velocityX >>= 3;
            StoreImage(&D_us_8018127C, (u_long*)D_us_801CF3E8);
            D_us_801D07EC = 0;
            D_us_801D07E8 = 0x40;
            RIC.step_s++;
        }
        break;
    case 4:
        if (g_Timer & 1) {
            break;
        }
        if (D_us_801D07E8 > 16) {
            // Another really weird velocityY value.
            // It's 0x233.
            RIC.velocityY += FIX(0.0086);
        } else {
            RIC.velocityX = 0;
            RIC.velocityY = 0;
        }
        for (i = 0; i < 4; i++) {
            s2 = imgPtr = D_us_801CF3E8;
            s2 += ((D_us_801D07EC >> 1) & 7);
            s2 += ((D_us_801D07EC & 0xFF) >> 4) << 6;
            for (j = 0; j < 0x28; j++) {
                if (D_us_801D07EC & 1) {
                    *(s2 + ((j & 7) * 8) + ((j >> 3) * 0x400)) &= 0xF0;
                } else {
                    *(s2 + ((j & 7) * 8) + ((j >> 3) * 0x400)) &= 0x0F;
                }
            }
            D_us_801D07EC += 0x23;
            D_us_801D07EC &= 0xFF;
        }
        LoadImage(&D_us_8018127C, (u_long*)imgPtr);
        if (--D_us_801D07E8 == 0) {
            RIC.velocityY = 0;
            playerDraw->enableColorBlend = 0;
            RIC.step_s = 0x80;
        }
        break;
    case 0x80:
        break;
    }
    if (!disableColorChange) {
        if (D_us_801D07F0 == DEATH_GENERIC) {
            if (playerDraw->r0 < 0xF8) {
                playerDraw->r0 += 2;
            }
            if (playerDraw->b0 > 8) {
                playerDraw->b0 -= 2;
            }

            playerDraw->r3 = playerDraw->r2 = playerDraw->r1 = playerDraw->r0;
            playerDraw->g0 = playerDraw->g1 = playerDraw->b1 = playerDraw->g2 =
                playerDraw->b2 = playerDraw->g3 = playerDraw->b3 =
                    playerDraw->b0;
        }
        if (D_us_801D07F0 == DEATH_BY_FIRE ||
            D_us_801D07F0 == DEATH_BY_THUNDER) {
            if (playerDraw->b0 > 8) {
                playerDraw->b0 -= 2;
            }
            playerDraw->r3 = playerDraw->r2 = playerDraw->r1 = playerDraw->r0 =
                playerDraw->g0 = playerDraw->g1 = playerDraw->b1 =
                    playerDraw->g2 = playerDraw->b2 = playerDraw->g3 =
                        playerDraw->b3 = playerDraw->b0;
        }
        if (D_us_801D07F0 == DEATH_BY_ICE) {
            if ((playerDraw->r0 > 8) && (g_Timer & 1)) {
                playerDraw->r0 -= 1;
            }
            playerDraw->r3 = playerDraw->r2 = playerDraw->r1 = playerDraw->g3 =
                playerDraw->g2 = playerDraw->g1 = playerDraw->g0 =
                    playerDraw->r0;
        }
    }
}

extern AnimationFrame D_us_801820B0[];

void RicStepStandInAir(void) {
    if (RIC.step_s == 0) {
        RIC.velocityY += FIX(0.21875);
        if (RIC.velocityY > 0) {
            RIC.velocityY = 0;
            RIC.step_s = 1;
        }
    } else if (g_Ric.unk4E != 0) {
        g_Ric.unk46 = 0;
        RicSetStep(PL_S_JUMP);
        RicSetAnimation(D_us_801820B0);
        g_Ric.unk44 = 0;
    }
}

void RicStepEnableFlameWhip(void) {
    if (RIC.animCurFrame == 181 && RIC.poseTimer == 1) {
        RicCreateEntFactoryFromEntity(g_CurrentEntity, BP_35, 0);
        g_api.PlaySfx(SFX_WEAPON_APPEAR);
    }

    if (RIC.poseTimer < 0) {
        RicSetStand(0);
        g_Ric.unk46 = 0;
        RicCreateEntFactoryFromEntity(
            g_CurrentEntity, FACTORY(BP_RIC_BLINK, 0x45), 0);
        g_Ric.timers[PL_T_POISON] = 0x800;
    }
}

void RicStepHydrostorm(void) {
    if (RIC.poseTimer < 0) {
        RicSetStand(0);
        g_Ric.unk46 = 0;
    }
}

void RicStepGenericSubwpnCrash(void) {
    if (g_Ric.unk4E != 0) {
        RicSetStand(0);
        g_Ric.unk46 = 0;
    }
}

extern s32 D_us_801D07F8;

void RicStepThrowDaggers(void) {
    if (RIC.step_s == 0) {
        D_us_801D07F8 = 0x200;
        RIC.step_s++;
    } else {
        RicCheckFacing();
        if (!--D_us_801D07F8) {
            g_Ric.unk46 = 0;
            RicSetStand(0);
            g_Ric.unk4E = 1;
        }
    }
    if (g_Ric.padTapped & PAD_CROSS) {
        func_us_801B9E70();
        g_Ric.unk46 = 0;
        g_Ric.unk4E = 1;
        D_us_801D07F8 = 0;
    }
}

void RicStepSlide(void) {
    // Preserve the unused space in the original stack frame.
    u8 padding[0x28];
    s32 isTouchingGround = 0;

    if (RIC.facingLeft == 0 && g_Ric.vram_flag & TOUCHING_R_WALL) {
        isTouchingGround = 1;
    }
    if (RIC.facingLeft && g_Ric.vram_flag & TOUCHING_L_WALL) {
        isTouchingGround = 1;
    }
    if (RIC.posX.i.hi >= STAGE_WIDTH - 4 && RIC.facingLeft == 0) {
        isTouchingGround = 1;
    }
    if (RIC.posX.i.hi <= 4 && RIC.facingLeft) {
        isTouchingGround = 1;
    }
    // The boss reads the player floor sensors here in the original.
    if ((RIC.facingLeft == 0 &&
         g_Player.colFloor[2].effects & EFFECT_UNK_8000) ||
        (RIC.facingLeft && g_Player.colFloor[3].effects & EFFECT_UNK_8000)) {
        isTouchingGround = 1;
    }
    if (isTouchingGround && RIC.pose < 6) {
        RIC.pose = 6;
        if (RIC.velocityX > FIX(1)) {
            RIC.velocityX = FIX(2);
        }
        if (RIC.velocityX < FIX(-1)) {
            RIC.velocityX = FIX(-2);
        }
        RicCreateEntFactoryFromEntity(g_CurrentEntity, BP_SKID_SMOKE, 0);
    }
    if (RIC.pose < 5) {
        if (RicCheckInput(CHECK_FALL | CHECK_CRASH)) {
            return;
        }
        if (g_Ric.padTapped & PAD_CROSS) {
            RIC.posY.i.hi -= 4;
            RicSetSlideKick();
            return;
        }
    } else if (RIC.pose < 7) {
        if (RicCheckInput(CHECK_FALL | CHECK_CRASH | CHECK_SLIDE)) {
            return;
        }
    } else if (
        RicCheckInput(CHECK_FALL | CHECK_FACING | CHECK_CRASH | CHECK_SLIDE)) {
        return;
    }

    DecelerateX(FIX(0.125));
    switch (RIC.step_s) {
    case 0:
        if (!(g_GameTimer & 3) && RIC.pose < 6 && RIC.pose > 2) {
            RicCreateEntFactoryFromEntity(
                g_CurrentEntity, FACTORY(BP_SLIDE, 2), 0);
        }
        if (RIC.pose == 6 && RIC.poseTimer == 1) {
            RicCreateEntFactoryFromEntity(g_CurrentEntity, BP_SKID_SMOKE, 0);
        }
        if (RIC.poseTimer < 0) {
            RicSetCrouch(0, RIC.velocityX);
        }
        break;
    }
}

extern AnimationFrame D_us_801820E4[];
extern AnimationFrame D_us_80182310[];

void RicStepSlideKick(void) {
    // If we are pressing square while in contact with an enemy
    // (as detected in g_Ric.unk44), we will bounce back.
    if (g_Ric.padPressed & PAD_SQUARE && g_Ric.unk44 & 0x80) {
        RIC.step = PL_S_JUMP;
        RicSetAnimation(D_us_801820E4);
        RicSetSpeedX(FIX(-1.5));
        RIC.velocityY = FIX(-3.5);
        g_Ric.unk44 |= (8 + 2);
        g_Ric.unk44 &= ~4;
        RIC.step_s = 2;
        return;
    }
    DecelerateX(FIX(0.0625));
    RIC.velocityY += 0x1000;

    if (g_Ric.vram_flag & TOUCHING_GROUND) {
        g_CurrentEntity->velocityX /= 2;
        RicCreateEntFactoryFromEntity(g_CurrentEntity, BP_SKID_SMOKE, 0);
        RIC.facingLeft++;
        RIC.facingLeft &= 1;
        RicSetCrouch(3, RIC.velocityX);
        g_api.PlaySfx(SFX_STOMP_SOFT_A);
        return;
    }
    if (RIC.velocityX < 0) {
        if (g_Ric.padPressed & PAD_RIGHT) {
            DecelerateX(FIX(0.125));
        }
        if (RIC.velocityX > FIX(-3) || (g_Ric.vram_flag & TOUCHING_L_WALL)) {
            RIC.facingLeft++;
            RIC.facingLeft &= 1;
            RIC.velocityX /= 2;
            RicSetAnimation(D_us_80182310);
            g_Ric.unk44 = 0xA;
            RIC.step_s = 2;
            RIC.step = PL_S_JUMP;
        }
    }
    if (RIC.velocityX > 0) {
        if (g_Ric.padPressed & PAD_LEFT) {
            DecelerateX(FIX(0.125));
        }
        if (RIC.velocityX < FIX(3) || (g_Ric.vram_flag & TOUCHING_R_WALL)) {
            RIC.facingLeft++;
            RIC.facingLeft &= 1;
            RIC.velocityX /= 2;
            RicSetAnimation(D_us_80182310);
            g_Ric.unk44 = 0xA;
            RIC.step_s = 2;
            RIC.step = PL_S_JUMP;
        }
    }
}

void RicStepBladeDash(void) {
    DecelerateX(0x1C00);

    if (RIC.poseTimer < 0) {
        g_Ric.unk46 = 0;
        RicSetStand(0);
    } else if (RIC.pose >= 0x12 && !(g_Ric.vram_flag & TOUCHING_GROUND)) {
        g_Ric.unk46 = 0;
        RicSetFall();
    } else {
        if (!(g_GameTimer & 3) && RIC.pose < 0x12 &&
            g_Ric.vram_flag & TOUCHING_GROUND) {
            RicCreateEntFactoryFromEntity(
                g_CurrentEntity, FACTORY(BP_SLIDE, 2), 0);
        }

        if (RIC.pose == 18 && RIC.poseTimer == 1 &&
            (g_Ric.vram_flag & TOUCHING_GROUND)) {
            RicCreateEntFactoryFromEntity(g_CurrentEntity, BP_SKID_SMOKE, 0);
        }
    }
}

void func_us_801B8E80(u16 arg0) {
    s16 xMod = 3;
    if (RIC.facingLeft) {
        xMod = -xMod;
    }

    RIC.posY.i.hi -= 16;
    RIC.posX.i.hi += xMod;
    RicCreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(BP_EMBERS, 1), 0);
    RIC.posY.i.hi += 16;
    RIC.posX.i.hi -= xMod;

    if (arg0 & 1) {
        g_api.ShakeCamera(SHAKE_Y_SMALL2);
        g_api.PlaySfx(SFX_WALL_DEBRIS_B);
    }
    if (arg0 & 2) {
        RIC.velocityX = 0;
        RIC.velocityY = 0;
    }
}

extern AnimationFrame D_us_801820BC[];

void RicStepHighJump(void) {
    bool loadAnim;

    loadAnim = false;
    g_Ric.high_jump_timer++;
    switch (RIC.step_s) {
    case 0:
        if (g_Ric.padPressed & (PAD_LEFT | PAD_RIGHT)) {
            if (RIC.facingLeft) {
                if (!(g_Ric.padPressed & PAD_LEFT)) {
                    DecelerateX(FIX(0.0625));
                }
            } else {
                if (!(g_Ric.padPressed & PAD_RIGHT)) {
                    DecelerateX(FIX(0.0625));
                }
            }
        } else {
            DecelerateX(FIX(0.0625));
        }

        if (g_Ric.vram_flag & TOUCHING_CEILING) {
            func_us_801B8E80(3);
            g_Ric.high_jump_timer = 0;
            RIC.step_s = 2;
        } else if (g_Ric.high_jump_timer > 0x1C) {
            RIC.step_s = 1;
            RIC.velocityY = -0x60000;
        }
        break;
    case 1:
        if (g_Ric.vram_flag & TOUCHING_CEILING) {
            RIC.step_s = 2;
            func_us_801B8E80(3);
            g_Ric.high_jump_timer = 0;
        } else {
            RIC.velocityY += 0x6000;
            if (RIC.velocityY > 0x8000) {
                loadAnim = true;
            }
        }
        break;
    case 2:
        if (g_Ric.high_jump_timer > 4) {
            loadAnim = true;
        }
        break;
    }

    if (loadAnim) {
        RicSetAnimation(D_us_801820BC);
        RicSetStep(PL_S_JUMP);
    }
}
