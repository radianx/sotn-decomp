// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../../boss/bo6/bo6.h"
#include <cutscene.h>

static u8 s_PcData_801804D8[];
static u8 s_PcData_801804DC[];
ObjInit2 BackgroundBlockInit[];
u8 D_us_80180614[];
u16 D_us_80180618[];
u16 D_us_80180620[];
u16 D_us_80180624[];
s16 D_us_8018062C[];
s32 D_us_80181210[];
u16 D_us_80181250[];
u16 D_us_80181270[];
s32 D_us_80181278;
RECT D_us_8018127C;
u8 D_us_80181284[];
u8 D_us_80181298[];
u8 D_us_801812A8[];
u8 D_us_801812B8[][4];
u8 D_us_80181524[][8];
AnimationFrame D_us_80181554[];
void func_us_801BBBC0(Entity*);
void RicEntityFactory(Entity*);
void func_us_801BC678(Entity*);
void RicEntitySubwpnCross(Entity*);
void func_us_801C488C(Entity*);
void RicEntityHitByCutBlood(Entity*);
void RicEntitySubwpnCrossTrail(Entity*);
void RicEntitySubwpnHolyWater(Entity*);
void RicEntitySubwpnHolyWaterFlame(Entity*);
void func_us_801BD0B8(Entity*);
void RicEntityWhip(Entity*);
void RicEntityCrashHydroStorm(Entity*);
void RicEntityCrashCrossBeam(Entity*);
void RicEntitySubwpnCrashCross(Entity*);
void func_us_801BBBC0(Entity*);
void func_us_801BBBC0(Entity*);
void RicEntityArmBrandishWhip(Entity*);
void func_us_801C2688(Entity*);
void func_us_801BBBC0(Entity*);
void func_us_801BD384(Entity*);
void func_us_801C2784(Entity*);
void func_us_801BBBC0(Entity*);
void func_us_801BBBC0(Entity*);
void func_us_801BC2F0(Entity*);
void func_us_801BC4F8(Entity*);
void func_us_801BBBC0(Entity*);
void func_us_801BBBC0(Entity*);
void func_us_801BBBC0(Entity*);
void func_us_801BBBC0(Entity*);
void func_us_801BC5C8(Entity*);
void func_us_801BBBC0(Entity*);
void RicEntityPlayerBlinkWhite(Entity*);
void RicEntitySubwpnCrashCrossParticles(Entity*);
void func_us_801BE79C(Entity*);
void RicEntityShrinkingPowerUpRing(Entity*);
void RicEntitySubwpnHolyWaterBreakGlass(Entity*);
void RicEntitySubwpnThrownAxe(Entity*);
void RicEntityCrashAxe(Entity*);
void RicEntitySubwpnKnife(Entity*);
void func_us_801BC3E0(Entity*);
void RicEntityHitByIce(Entity*);
void RicEntityHitByLightning(Entity*);
void RicEntitySubwpnReboundStone(Entity*);
void RicEntitySubwpnThrownVibhuti(Entity*);
void RicEntitySubwpnAgunea(Entity*);
void RicEntityAguneaHitEnemy(Entity*);
void RicEntityCrashVibhuti(Entity*);
void RicEntityVibhutiCrashCloud(Entity*);
void RicEntityCrashReboundStone(Entity*);
void func_us_801C8618(Entity*);
void RicEntityCrashReboundStoneExplosion(Entity*);
void RicEntityCrashBible(Entity*);
void RicEntityCrashBibleBeam(Entity*);
void RicEntitySubwpnBible(Entity*);
void RicEntitySubwpnBibleTrail(Entity*);
void EntityStopWatch(Entity*);
void RicEntitySubwpnStopwatchCircle(Entity*);
void func_us_801CA340(Entity*);
void func_us_801C9DE8(Entity*);
void RicEntityAguneaCircle(Entity*);
void RicEntityAguneaLightning(Entity*);
void func_us_801C8590(Entity*);
void RicEntityHitByDark(Entity*);
void RicEntityHitByHoly(Entity*);
void func_us_801C03E8(Entity*);
void RicEntityWhip(Entity*);
void func_us_801C0FE8(Entity*);
void func_us_801C13A8(Entity*);
void EntityShaft(Entity*);
PfnEntityUpdate D_us_8018158C[];
FactoryBlueprint D_us_801816A0[];
u8 D_us_80181868[][2];
s16 D_us_80181878[];
s32 D_us_80181884[];
s16 D_us_8018189C[];
AnimationFrame D_us_801818A8[];
static unkStr_8011E4BC s_PcData_8018191C[];
static unkStr_8011E4BC s_PcData_8018192C[];
static unkStr_8011E4BC s_PcData_8018193C[];
static unkStr_8011E4BC s_PcData_8018194C[];
static unkStr_8011E4BC s_PcData_8018195C[];
static unkStr_8011E4BC s_PcData_8018196C[];
static unkStr_8011E4BC s_PcData_8018197C[];
static unkStr_8011E4BC s_PcData_8018198C[];
static unkStr_8011E4BC s_PcData_8018199C[];
unkStr_8011E4BC* D_us_801819AC[];
AnimationFrame D_us_801819D0[];
AnimationFrame D_us_80181A0C[];
AnimationFrame D_us_80181A40[];
s32 D_us_80181A64[];
s16 D_us_80181AA4[][10];
s16 D_us_80181CAC[][6];
static Point16 s_PcData_80181D0C[];
static Point16 s_PcData_80181D1C[];
static Point16 s_PcData_80181D10[];
static Point16 s_PcData_80181D20[];
static Point16 s_PcData_80181D14[];
static Point16 s_PcData_80181D24[];
static Point16 s_PcData_80181D18[];
static Point16 s_PcData_80181D30[];
static Point16 s_PcData_80181D2C[];
static Point16 s_PcData_80181D28[];
static Point16 s_PcData_80181D3C[];
static Point16 s_PcData_80181D40[];
static Point16 s_PcData_80181D34[];
static Point16 s_PcData_80181D38[];
static Point16 s_PcData_80181D44[];
static Point16 s_PcData_80181D48[];
static Point16 s_PcData_80181D4C[];
static Point16 s_PcData_80181D50[];
Point16* D_us_80181D54[72];
u16 D_us_80181E74[];
AnimationFrame D_us_80181E78[];
u8 D_us_80181E9C[];
AnimationFrame D_us_80181EDC[];
static AnimationFrame s_PcData_80181F44[];
AnimationFrame* D_us_80181F14[];
AnimationFrame D_us_80181F1C[];
AnimationFrame D_us_80181F24[];
AnimationFrame D_us_80182008[];
s16 D_us_80182010[];
AnimationFrame D_us_80182038[];
AnimationFrame D_us_80182048[];
AnimationFrame D_us_80182050[];
AnimationFrame D_us_80182058[];
AnimationFrame D_us_80182068[];
s16 D_us_80182078[];
s16 D_us_80182094[];
AnimationFrame D_us_801820B0[];
AnimationFrame D_us_801820BC[];
AnimationFrame D_us_801820CC[];
AnimationFrame D_us_801820E4[];
AnimationFrame D_us_80182110[];
AnimationFrame D_us_80182130[];
AnimationFrame D_us_80182150[];
AnimationFrame D_us_80182170[];
AnimationFrame D_us_80182190[];
AnimationFrame D_us_801821C0[];
AnimationFrame D_us_801821E0[];
s16 D_us_801821F8[];
AnimationFrame D_us_8018221C[];
AnimationFrame D_us_80182224[];
AnimationFrame D_us_8018224C[];
AnimationFrame D_us_8018228C[];
AnimationFrame D_us_801822B8[];
AnimationFrame D_us_801822C0[];
AnimationFrame D_us_801822C8[];
AnimationFrame D_us_801822D8[];
AnimationFrame D_us_80182304[];
AnimationFrame D_us_80182310[];
s16 D_us_80182324[];
AnimationFrame D_us_80182334[];
AnimationFrame D_us_80182360[];
AnimationFrame D_us_801823C8[];
AnimationFrame D_us_8018246C[];
FrameProperty D_us_801824A4[];
Point16 D_us_801824EC[];
Point16 D_us_80182508[];
Point16 D_us_80182524[];
s16 D_us_80182548[];
Point16 D_us_8018255C[];
s16 D_us_80182580[];
Point16 D_us_80182594[];
s16 D_us_801825B8[];
Point32 D_us_801825EC[];
Point32 D_us_80182624[];
s32 D_us_8018266C[];
s32 D_us_80182690[];
s32 D_us_801826B4[];
s32 D_us_801826D8[];
s32 D_us_801826FC[];
s32 D_us_80182720[];
s32 D_us_80182744[];
s32 D_us_80182768[];
s32 D_us_8018278C[];
u16 D_us_801827B0[3];
s16 D_us_801827B8[];
u16 D_us_801827D8[];
s16 D_us_801827F8[];
s16 D_us_8018280C[];
s16 D_us_80182820[];
s16 D_us_80182834[];
s16 D_us_80182848[];
s16 D_us_8018285C[];
s16 D_us_80182870[];
s16 D_us_80182890[][6];
s32 D_us_801828C8[];
u16 D_us_80182908[];
RECT D_us_80182968;
s16 D_us_80182994[];
u8 D_us_8018299C[];
s16 D_us_801829C4[];
AnimationFrame D_us_801829D4[];
s32 D_us_80182A0C[];
s16 D_us_80182A1C[6];
static SVECTOR s_PcData_80182A40[];
static SVECTOR s_PcData_80182A48[];
static SVECTOR s_PcData_80182A68[];
static SVECTOR s_PcData_80182A60[];
static SVECTOR s_PcData_80182B48[];
static SVECTOR s_PcData_80182B50[];
static SVECTOR s_PcData_80182B00[];
static SVECTOR s_PcData_80182B68[];
static SVECTOR s_PcData_80182B58[];
static SVECTOR s_PcData_80182B60[];
static SVECTOR s_PcData_80182B70[];
static SVECTOR s_PcData_80182B08[];
static SVECTOR s_PcData_80182B78[];
static SVECTOR s_PcData_80182B20[];
static SVECTOR s_PcData_80182B90[];
static SVECTOR s_PcData_80182B88[];
static SVECTOR s_PcData_80182B28[];
static SVECTOR s_PcData_80182B80[];
static SVECTOR s_PcData_80182BA0[];
static SVECTOR s_PcData_80182B98[];
static SVECTOR s_PcData_80182A30[];
static SVECTOR s_PcData_80182AF0[];
static SVECTOR s_PcData_80182A98[];
static SVECTOR s_PcData_80182AD8[];
static SVECTOR s_PcData_80182B40[];
static SVECTOR s_PcData_80182A80[];
static SVECTOR s_PcData_80182AA8[];
static SVECTOR s_PcData_80182AB0[];
static SVECTOR s_PcData_80182AE8[];
static SVECTOR s_PcData_80182AF8[];
static SVECTOR s_PcData_80182B18[];
static SVECTOR s_PcData_80182B30[];
static SVECTOR s_PcData_80182B10[];
static SVECTOR s_PcData_80182B38[];
static SVECTOR s_PcData_80182A28[];
static SVECTOR s_PcData_80182A90[];
static SVECTOR s_PcData_80182AD0[];
static SVECTOR s_PcData_80182A78[];
static SVECTOR s_PcData_80182AB8[];
static SVECTOR s_PcData_80182AC0[];
static SVECTOR s_PcData_80182A50[];
static SVECTOR s_PcData_80182A70[];
static SVECTOR s_PcData_80182A38[];
static SVECTOR s_PcData_80182A58[];
SVECTOR* D_us_80182BA8[][4];
u8 D_us_80182E88[46][5];
u8 D_us_8019A0C8;
u8 D_us_8019A0CC;
u8 D_us_8019A0D0[];
u8 D_us_8019A2E1[];
u8 D_us_8019A2FB[];
static s16 s_PcData_801A3D04[];
static s16 s_PcData_801A3D0C[];
static s16 s_PcData_801A3D14[];
static s16 s_PcData_801A3D1C[];
static s16 s_PcData_801A3D24[];
static s16 s_PcData_801A3D2C[];
static s16 s_PcData_801A3D34[];
static s16 s_PcData_801A3D3C[];
static s16 s_PcData_801A3D44[];
static s16 s_PcData_801A3D4C[];
static s16 s_PcData_801A3D54[];
static s16 s_PcData_801A3D5C[];
static s16 s_PcData_801A3D64[];
static s16 s_PcData_801A3D6C[];
static s16 s_PcData_801A3D74[];
static s16 s_PcData_801A3D7C[];
static s16 s_PcData_801A3D84[];
static s16 s_PcData_801A3D8C[];
static s16 s_PcData_801A3D94[];
static s16 s_PcData_801A3D9C[];
static s16 s_PcData_801A3DA4[];
static s16 s_PcData_801A3DAC[];
static s16 s_PcData_801A3DB4[];
static s16 s_PcData_801A3DBC[];
static s16 s_PcData_801A3DC4[];
static s16 s_PcData_801A3DCC[];
static s16 s_PcData_801A3DD4[];
static s16 s_PcData_801A3DDC[];
static s16 s_PcData_801A3DE4[];
static s16 s_PcData_801A3DEC[];
static s16 s_PcData_801A3DF4[];
static s16 s_PcData_801A3DFC[];
static s16 s_PcData_801A3E04[];
static s16 s_PcData_801A3E0C[];
static s16 s_PcData_801A3E14[];
static s16 s_PcData_801A3E1C[];
static s16 s_PcData_801A3E24[];
static s16 s_PcData_801A3E2C[];
static s16 s_PcData_801A3E34[];
static s16 s_PcData_801A3E3C[];
static s16 s_PcData_801A3E44[];
static s16 s_PcData_801A3E4C[];
static s16 s_PcData_801A3E54[];
static s16 s_PcData_801A3E5C[];
static s16 s_PcData_801A3E64[];
static s16 s_PcData_801A3E6C[];
static s16 s_PcData_801A3E74[];
static s16 s_PcData_801A3E7C[];
static s16 s_PcData_801A3E84[];
static s16 s_PcData_801A3E8C[];
static s16 s_PcData_801A3E94[];
static s16 s_PcData_801A3E9C[];
static s16 s_PcData_801A3EA4[];
static s16 s_PcData_801A3EAC[];
static s16 s_PcData_801A3EB4[];
static s16 s_PcData_801A3EBC[];
static s16 s_PcData_801A3EC4[];
static s16 s_PcData_801A3ECC[];
static s16 s_PcData_801A3ED4[];
static s16 s_PcData_801A3EDC[];
static s16 s_PcData_801A3EE4[];
static s16 s_PcData_801A3EEC[];
static s16 s_PcData_801A3EF4[];
static s16 s_PcData_801A3EFC[];
static s16 s_PcData_801A3F04[];
static s16 s_PcData_801A3F0C[];
static s16 s_PcData_801A3F14[];
static s16 s_PcData_801A3F1C[];
static s16 s_PcData_801A3F24[];
static s16 s_PcData_801A3F2C[];
static s16 s_PcData_801A3F34[];
static s16 s_PcData_801A3F3C[];
static s16 s_PcData_801A3F44[];
static s16 s_PcData_801A3F4C[];
static s16 s_PcData_801A3F54[];
static s16 s_PcData_801A3F5C[];
static s16 s_PcData_801A3F64[];
static s16 s_PcData_801A3F6C[];
static s16 s_PcData_801A3F74[];
static s16 s_PcData_801A3F7C[];
static s16 s_PcData_801A3F84[];
static s16 s_PcData_801A3F8C[];
static s16 s_PcData_801A3F94[];
static s16 s_PcData_801A3F9C[];
static s16 s_PcData_801A3FA4[];
static s16 s_PcData_801A3FAC[];
static s16 s_PcData_801A3FB4[];
static s16 s_PcData_801A3FBC[];
static s16 s_PcData_801A3FC4[];
static s16 s_PcData_801A3FCC[];
static s16 s_PcData_801A3FD4[];
static s16 s_PcData_801A3FDC[];
static s16 s_PcData_801A3FE4[];
static s16 s_PcData_801A3FEC[];
static s16 s_PcData_801A3FF4[];
static s16 s_PcData_801A3FFC[];
static s16 s_PcData_801A4004[];
static s16 s_PcData_801A400C[];
static s16 s_PcData_801A4014[];
static s16 s_PcData_801A401C[];
static s16 s_PcData_801A4024[];
static s16 s_PcData_801A402C[];
static s16 s_PcData_801A4034[];
static s16 s_PcData_801A403C[];
static s16 s_PcData_801A4044[];
static s16 s_PcData_801A404C[];
static s16 s_PcData_801A4054[];
static s16 s_PcData_801A405C[];
static s16 s_PcData_801A4064[];
static s16 s_PcData_801A406C[];
static s16 s_PcData_801A4074[];
static s16 s_PcData_801A407C[];
static s16 s_PcData_801A4084[];
static s16 s_PcData_801A408C[];
static s16 s_PcData_801A4094[];
static s16 s_PcData_801A409C[];
static s16 s_PcData_801A40A4[];
static s16 s_PcData_801A40AC[];
static s16 s_PcData_801A40B4[];
static s16 s_PcData_801A40BC[];
static s16 s_PcData_801A40C4[];
static s16 s_PcData_801A40CC[];
static s16 s_PcData_801A40D4[];
static s16 s_PcData_801A40DC[];
static s16 s_PcData_801A40E4[];
static s16 s_PcData_801A40EC[];
static s16 s_PcData_801A40F4[];
static s16 s_PcData_801A40FC[];
static s16 s_PcData_801A4104[];
static s16 s_PcData_801A410C[];
static s16 s_PcData_801A4114[];
static s16 s_PcData_801A411C[];
static s16 s_PcData_801A4124[];
static s16 s_PcData_801A412C[];
static s16 s_PcData_801A4134[];
static s16 s_PcData_801A413C[];
static s16 s_PcData_801A4144[];
static s16 s_PcData_801A414C[];
static s16 s_PcData_801A4154[];
static s16 s_PcData_801A415C[];
static s16 s_PcData_801A4164[];
static s16 s_PcData_801A416C[];
static s16 s_PcData_801A4174[];
static s16 s_PcData_801A417C[];
static s16 s_PcData_801A4184[];
static s16 s_PcData_801A418C[];
static s16 s_PcData_801A4194[];
static s16 s_PcData_801A419C[];
static s16 s_PcData_801A41A4[];
static s16 s_PcData_801A41AC[];
static s16 s_PcData_801A41B4[];
static s16 s_PcData_801A41BC[];
static s16 s_PcData_801A41C4[];
static s16 s_PcData_801A41CC[];
static s16 s_PcData_801A41D4[];
static s16 s_PcData_801A41DC[];
static s16 s_PcData_801A41E4[];
static s16 s_PcData_801A41EC[];
static s16 s_PcData_801A41F4[];
static s16 s_PcData_801A41FC[];
static s16 s_PcData_801A4204[];
static s16 s_PcData_801A420C[];
static s16 s_PcData_801A4214[];
static s16 s_PcData_801A421C[];
static s16 s_PcData_801A4224[];
static s16 s_PcData_801A422C[];
static s16 s_PcData_801A4234[];
static s16 s_PcData_801A423C[];
static s16 s_PcData_801A4244[];
static s16 s_PcData_801A424C[];
static s16 s_PcData_801A4254[];
static s16 s_PcData_801A425C[];
static s16 s_PcData_801A4264[];
static s16 s_PcData_801A426C[];
static s16 s_PcData_801A4274[];
static s16 s_PcData_801A427C[];
static s16 s_PcData_801A4284[];
static s16 s_PcData_801A428C[];
static s16 s_PcData_801A4294[];
static s16 s_PcData_801A429C[];
static s16 s_PcData_801A42A4[];
static s16 s_PcData_801A42AC[];
static s16 s_PcData_801A42B4[];
static s16 s_PcData_801A42BC[];
static s16 s_PcData_801A42C4[];
static s16 s_PcData_801A42CC[];
static s16 s_PcData_801A42D4[];
static s16 s_PcData_801A42DC[];
static s16 s_PcData_801A42E4[];
static s16 s_PcData_801A42EC[];
static s16 s_PcData_801A42F4[];
static s16 s_PcData_801A42FC[];
static s16 s_PcData_801A4304[];
static s16 s_PcData_801A430C[];
static s16 s_PcData_801A4314[];
static s16 s_PcData_801A431C[];
static s16 s_PcData_801A4324[];
static s16 s_PcData_801A432C[];
static s16 s_PcData_801A4334[];
static s16 s_PcData_801A433C[];
static s16 s_PcData_801A4344[];
static s16 s_PcData_801A434C[];
static s16 s_PcData_801A4354[];
static s16 s_PcData_801A435C[];
static s16 s_PcData_801A4364[];
static s16 s_PcData_801A436C[];
static s16 s_PcData_801A4374[];
static s16 s_PcData_801A437C[];
static s16 s_PcData_801A4384[];
static s16 s_PcData_801A438C[];
static s16 s_PcData_801A4394[];
static s16 s_PcData_801A439C[];
s16* D_us_801A39B0[];
static s16 s_PcData_801A43F8[];
static s16 s_PcData_801A4414[];
static s16 s_PcData_801A4430[];
static s16 s_PcData_801A444C[];
static s16 s_PcData_801A4468[];
static s16 s_PcData_801A4484[];
static s16 s_PcData_801A44A0[];
static s16 s_PcData_801A44BC[];
static s16 s_PcData_801A44D8[];
static s16 s_PcData_801A44F4[];
static s16 s_PcData_801A4510[];
static s16 s_PcData_801A452C[];
static s16 s_PcData_801A4548[];
static s16 s_PcData_801A4564[];
static s16 s_PcData_801A4580[];
static s16 s_PcData_801A459C[];
static s16 s_PcData_801A45B8[];
static s16 s_PcData_801A45D4[];
static s16 s_PcData_801A45F0[];
static s16 s_PcData_801A460C[];
s16* D_us_801A43A4[];
static s16 s_PcData_801A46BC[];
static s16 s_PcData_801A46D8[];
static s16 s_PcData_801A46F4[];
static s16 s_PcData_801A4710[];
static s16 s_PcData_801A472C[];
static s16 s_PcData_801A4748[];
static s16 s_PcData_801A4764[];
static s16 s_PcData_801A4780[];
static s16 s_PcData_801A479C[];
static s16 s_PcData_801A47B8[];
static s16 s_PcData_801A47D4[];
static s16 s_PcData_801A47F0[];
static s16 s_PcData_801A480C[];
static s16 s_PcData_801A4828[];
static s16 s_PcData_801A4844[];
static s16 s_PcData_801A4860[];
static s16 s_PcData_801A487C[];
static s16 s_PcData_801A4898[];
static s16 s_PcData_801A48B4[];
static s16 s_PcData_801A48D0[];
static s16 s_PcData_801A48EC[];
static s16 s_PcData_801A4908[];
static s16 s_PcData_801A4924[];
static s16 s_PcData_801A4940[];
static s16 s_PcData_801A495C[];
static s16 s_PcData_801A4978[];
static s16 s_PcData_801A4994[];
static s16 s_PcData_801A49B0[];
static s16 s_PcData_801A49CC[];
static s16 s_PcData_801A49E8[];
static s16 s_PcData_801A4A04[];
static s16 s_PcData_801A4A20[];
static s16 s_PcData_801A4A3C[];
static s16 s_PcData_801A4A58[];
static s16 s_PcData_801A4A74[];
static s16 s_PcData_801A4A90[];
s16* D_us_801A4628[];
static s16 s_PcData_801A4CE0[];
static s16 s_PcData_801A4CFC[];
static s16 s_PcData_801A4D18[];
static s16 s_PcData_801A4D34[];
static s16 s_PcData_801A4D50[];
static s16 s_PcData_801A4D6C[];
static s16 s_PcData_801A4D88[];
static s16 s_PcData_801A4DA4[];
static s16 s_PcData_801A4DC0[];
static s16 s_PcData_801A4DDC[];
static s16 s_PcData_801A4DF8[];
static s16 s_PcData_801A4E14[];
static s16 s_PcData_801A4E30[];
static s16 s_PcData_801A4E4C[];
static s16 s_PcData_801A4E68[];
static s16 s_PcData_801A4E84[];
static s16 s_PcData_801A4EA0[];
static s16 s_PcData_801A4EBC[];
static s16 s_PcData_801A4ED8[];
static s16 s_PcData_801A4EF4[];
static s16 s_PcData_801A4F10[];
static s16 s_PcData_801A4F2C[];
static s16 s_PcData_801A4F48[];
static s16 s_PcData_801A4F64[];
static s16 s_PcData_801A4F80[];
static s16 s_PcData_801A4F9C[];
static s16 s_PcData_801A4FB8[];
static s16 s_PcData_801A4FD4[];
static s16 s_PcData_801A4FF0[];
static s16 s_PcData_801A500C[];
static s16 s_PcData_801A5028[];
static s16 s_PcData_801A5044[];
static s16 s_PcData_801A5060[];
static s16 s_PcData_801A507C[];
static s16 s_PcData_801A5098[];
static s16 s_PcData_801A50B4[];
static s16 s_PcData_801A50D0[];
static s16 s_PcData_801A50EC[];
static s16 s_PcData_801A5108[];
static s16 s_PcData_801A5124[];
static s16 s_PcData_801A5140[];
static s16 s_PcData_801A515C[];
static s16 s_PcData_801A5178[];
static s16 s_PcData_801A5194[];
static s16 s_PcData_801A51C4[];
static s16 s_PcData_801A51F4[];
static s16 s_PcData_801A5224[];
static s16 s_PcData_801A5254[];
static s16 s_PcData_801A5284[];
static s16 s_PcData_801A52B4[];
static s16 s_PcData_801A52E4[];
static s16 s_PcData_801A5314[];
static s16 s_PcData_801A5344[];
static s16 s_PcData_801A5374[];
static s16 s_PcData_801A53A4[];
static s16 s_PcData_801A53D4[];
static s16 s_PcData_801A5404[];
static s16 s_PcData_801A5434[];
static s16 s_PcData_801A5464[];
static s16 s_PcData_801A5494[];
static s16 s_PcData_801A54C4[];
static s16 s_PcData_801A54E0[];
static s16 s_PcData_801A5510[];
static s16 s_PcData_801A5558[];
static s16 s_PcData_801A55CC[];
static s16 s_PcData_801A5640[];
static s16 s_PcData_801A56B4[];
static s16 s_PcData_801A5728[];
static s16 s_PcData_801A5784[];
static s16 s_PcData_801A57E0[];
static s16 s_PcData_801A583C[];
static s16 s_PcData_801A5898[];
static s16 s_PcData_801A58C8[];
static s16 s_PcData_801A58F8[];
static s16 s_PcData_801A5928[];
static s16 s_PcData_801A5958[];
static s16 s_PcData_801A5974[];
static s16 s_PcData_801A5990[];
static s16 s_PcData_801A59AC[];
static s16 s_PcData_801A59C8[];
static s16 s_PcData_801A59E4[];
static s16 s_PcData_801A5A00[];
static s16 s_PcData_801A5A1C[];
static s16 s_PcData_801A5A38[];
static s16 s_PcData_801A5A54[];
static s16 s_PcData_801A5A70[];
static s16 s_PcData_801A5A8C[];
static s16 s_PcData_801A5AA8[];
static s16 s_PcData_801A5AC4[];
static s16 s_PcData_801A5AE0[];
static s16 s_PcData_801A5AFC[];
static s16 s_PcData_801A5B18[];
static s16 s_PcData_801A5B34[];
static s16 s_PcData_801A5B64[];
static s16 s_PcData_801A5B94[];
static s16 s_PcData_801A5BC4[];
static s16 s_PcData_801A5BF4[];
static s16 s_PcData_801A5C24[];
static s16 s_PcData_801A5C54[];
static s16 s_PcData_801A5C84[];
static s16 s_PcData_801A5CB4[];
static s16 s_PcData_801A5CE4[];
static s16 s_PcData_801A5D14[];
static s16 s_PcData_801A5D44[];
static s16 s_PcData_801A5D74[];
static s16 s_PcData_801A5DA4[];
static s16 s_PcData_801A5DD4[];
static s16 s_PcData_801A5E04[];
static s16 s_PcData_801A5E34[];
static s16 s_PcData_801A5E64[];
static s16 s_PcData_801A5E94[];
static s16 s_PcData_801A5EC4[];
static s16 s_PcData_801A5EF4[];
static s16 s_PcData_801A5F24[];
static s16 s_PcData_801A5F54[];
static s16 s_PcData_801A5F84[];
static s16 s_PcData_801A5FB4[];
static s16 s_PcData_801A5FE4[];
static s16 s_PcData_801A6014[];
static s16 s_PcData_801A6044[];
static s16 s_PcData_801A6074[];
static s16 s_PcData_801A60A4[];
static s16 s_PcData_801A60D4[];
static s16 s_PcData_801A60F0[];
static s16 s_PcData_801A610C[];
static s16 s_PcData_801A6128[];
static s16 s_PcData_801A6144[];
static s16 s_PcData_801A6174[];
static s16 s_PcData_801A61A4[];
static s16 s_PcData_801A61D4[];
static s16 s_PcData_801A6204[];
static s16 s_PcData_801A6220[];
static s16 s_PcData_801A623C[];
static s16 s_PcData_801A6258[];
static s16 s_PcData_801A6274[];
static s16 s_PcData_801A6290[];
static s16 s_PcData_801A62AC[];
static s16 s_PcData_801A62C8[];
static s16 s_PcData_801A62E4[];
s16* D_us_801A4AAC[];
static char s_PcData_801A6314[];
static char s_PcData_801A6308[];
static char s_PcData_801A6300[];
char* actor_names[];
AnimationFrame anim_cross_boomerang[];
SubweaponDef subweapons_def[];

static u8 s_PcData_801804D8[] = {
    16,
    11,
    0,
    0,
};

static u8 s_PcData_801804DC[] = {
    8, 12, 8, 13, 8, 14, 8, 15, 8, 16, 0, 0,
};

ObjInit2 BackgroundBlockInit[] = {
    {32769, 105, 0, 0, 0, 0, 0, 0, s_PcData_801804D8},
    {32769, 105, 0, 0, 0, 0, 48, 0, s_PcData_801804DC},
};

u8 D_us_80180614[] = {
    0,
    0,
    0,
    0,
};

u16 D_us_80180618[] = {
    608,
    616,
    624,
    536,
};

u16 D_us_80180620[] = {
    256,
    288,
};

u16 D_us_80180624[] = {
    417,
    417,
    417,
    417,
};

s16 D_us_8018062C[] = {
    8,  19, 17, 49, 79, 38, 54, 29, 27, 51, 44, 33, 25, 10, 51, 31, 72, 47,
    19, 25, 77, 75, 23, 29, 18, 2,  27, 42, 80, 69, 50, 13, 42, 77, 6,  39,
    7,  72, 47, 27, 54, 34, 57, 20, 57, 29, 10, 53, 16, 27, 61, 23, 46, 11,
    73, 66, 61, 42, 1,  12, 27, 52, 65, 53, 8,  14, 77, 17, 52, 65, 41, 72,
};

s32 D_us_80181210[] = {
    32,  64, 32768, 8192, 16384, 4096, 2048, 512,
    256, 32, 32,    32,   32,    32,   32,   32,
};

u16 D_us_80181250[] = {
    33327, 33327, 33312, 33327, 33327, 33312, 33327, 33327,
    33312, 33327, 33326, 33327, 33326, 33327, 33312, 0,
};

u16 D_us_80181270[] = {
    33312,
    33323,
    33324,
    33325,
};

s32 D_us_80181278 = 0;

RECT D_us_8018127C = {0, 256, 32, 80};

u8 D_us_80181284[] = {
    10, 8, 8, 6, 6, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 255, 255, 0, 0,
};

u8 D_us_80181298[] = {
    4, 4, 4, 4, 6, 6, 6, 6, 8, 8, 16, 16, 16, 16, 16, 16,
};

u8 D_us_801812A8[] = {
    8, 12, 16, 20, 24, 28, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
};

u8 D_us_801812B8[][4] = {
    16, 127, 63, 0,  16,  127, 0,  0,  16, 63,
    63, 127, 16, 63, 127, 63,  16, 47, 63, 127,
};

u8 D_us_80181524[][8] = {
    0,   80, 16,  80, 0,   96, 16,  96, 16,  80, 32,  80, 16,  96, 32,  96,
    112, 64, 128, 64, 112, 80, 128, 80, 112, 48, 120, 48, 112, 56, 120, 56,
    120, 48, 128, 48, 120, 56, 128, 56, 112, 56, 120, 56, 119, 64, 120, 64,
};

AnimationFrame D_us_80181554[] = {
    {2, 1}, {2, 2}, {2, 3},  {2, 4},  {2, 5},  {2, 6},  {2, 7},
    {2, 8}, {2, 9}, {2, 10}, {2, 11}, {2, 12}, {2, 13}, {65535, 0},
};

PfnEntityUpdate D_us_8018158C[] = {
    func_us_801BBBC0,
    RicEntityFactory,
    func_us_801BC678,
    RicEntitySubwpnCross,
    func_us_801C488C,
    RicEntityHitByCutBlood,
    RicEntitySubwpnCrossTrail,
    RicEntitySubwpnHolyWater,
    RicEntitySubwpnHolyWaterFlame,
    func_us_801BD0B8,
    RicEntityWhip,
    RicEntityCrashHydroStorm,
    RicEntityCrashCrossBeam,
    RicEntitySubwpnCrashCross,
    func_us_801BBBC0,
    func_us_801BBBC0,
    RicEntityArmBrandishWhip,
    func_us_801C2688,
    func_us_801BBBC0,
    func_us_801BD384,
    func_us_801C2784,
    func_us_801BBBC0,
    func_us_801BBBC0,
    func_us_801BC2F0,
    func_us_801BC4F8,
    func_us_801BBBC0,
    func_us_801BBBC0,
    func_us_801BBBC0,
    func_us_801BBBC0,
    func_us_801BC5C8,
    func_us_801BBBC0,
    RicEntityPlayerBlinkWhite,
    RicEntitySubwpnCrashCrossParticles,
    func_us_801BE79C,
    RicEntityShrinkingPowerUpRing,
    RicEntitySubwpnHolyWaterBreakGlass,
    RicEntitySubwpnThrownAxe,
    RicEntityCrashAxe,
    RicEntitySubwpnKnife,
    func_us_801BC3E0,
    RicEntityHitByIce,
    RicEntityHitByLightning,
    RicEntitySubwpnReboundStone,
    RicEntitySubwpnThrownVibhuti,
    RicEntitySubwpnAgunea,
    RicEntityAguneaHitEnemy,
    RicEntityCrashVibhuti,
    RicEntityVibhutiCrashCloud,
    RicEntityCrashReboundStone,
    func_us_801C8618,
    RicEntityCrashReboundStoneExplosion,
    RicEntityCrashBible,
    RicEntityCrashBibleBeam,
    RicEntitySubwpnBible,
    RicEntitySubwpnBibleTrail,
    EntityStopWatch,
    RicEntitySubwpnStopwatchCircle,
    func_us_801CA340,
    func_us_801C9DE8,
    RicEntityAguneaCircle,
    RicEntityAguneaLightning,
    func_us_801C8590,
    RicEntityHitByDark,
    RicEntityHitByHoly,
    func_us_801C03E8,
    RicEntityWhip,
    func_us_801C0FE8,
    func_us_801C13A8,
    EntityShaft,
};

FactoryBlueprint D_us_801816A0[] = {
    {2, 5, 193, 2, 0, 0},     {2, 3, 193, 4, 32, 0},   {3, 1, 193, 0, 25, 8},
    {4, 3, 193, 2, 0, 0},     {5, 1, 193, 0, 0, 0},    {6, 4, 193, 4, 0, 4},
    {7, 1, 193, 0, 25, 8},    {8, 1, 193, 0, 1, 0},    {9, 6, 193, 12, 56, 0},
    {9, 128, 193, 3, 56, 8},  {10, 15, 207, 0, 26, 0}, {5, 72, 193, 2, 19, 0},
    {11, 32, 193, 6, 17, 48}, {13, 1, 193, 0, 9, 0},   {12, 6, 193, 24, 9, 0},
    {0, 16, 208, 0, 24, 0},   {0, 15, 207, 0, 24, 0},  {16, 1, 193, 0, 28, 0},
    {17, 1, 193, 0, 8, 0},    {36, 1, 193, 0, 25, 8},  {19, 1, 193, 0, 64, 0},
    {20, 1, 193, 0, 0, 0},    {0, 1, 193, 0, 3, 0},    {0, 4, 193, 24, 3, 0},
    {2, 1, 193, 0, 0, 0},     {23, 1, 193, 0, 1, 0},   {24, 1, 193, 0, 1, 0},
    {0, 1, 193, 0, 3, 0},     {0, 1, 193, 0, 3, 0},    {0, 1, 193, 0, 5, 0},
    {0, 4, 193, 4, 3, 0},     {39, 1, 193, 0, 1, 0},   {0, 1, 193, 0, 0, 0},
    {31, 1, 193, 0, 0, 0},    {32, 1, 193, 0, 0, 0},   {33, 1, 193, 0, 0, 0},
    {34, 1, 193, 0, 0, 0},    {34, 1, 193, 0, 0, 4},   {34, 1, 193, 0, 0, 8},
    {34, 1, 193, 0, 0, 12},   {35, 1, 193, 0, 0, 0},   {37, 8, 200, 0, 17, 32},
    {5, 3, 193, 3, 0, 0},     {38, 1, 193, 0, 25, 8},  {38, 128, 193, 4, 78, 8},
    {29, 1, 193, 0, 1, 0},    {5, 12, 193, 2, 56, 0},  {40, 1, 193, 0, 0, 0},
    {41, 1, 193, 0, 0, 0},    {43, 1, 193, 0, 17, 8},  {42, 1, 193, 0, 17, 4},
    {44, 1, 193, 0, 17, 4},   {45, 1, 193, 0, 16, 0},  {9, 72, 193, 2, 19, 16},
    {46, 1, 193, 0, 0, 18},   {47, 1, 193, 0, 6, 0},   {48, 1, 193, 0, 0, 0},
    {49, 1, 193, 0, 1, 0},    {50, 1, 193, 0, 1, 0},   {51, 1, 193, 0, 1, 0},
    {52, 1, 193, 0, 1, 0},    {53, 1, 193, 0, 1, 0},   {54, 1, 193, 0, 0, 0},
    {55, 1, 193, 0, 1, 0},    {56, 1, 193, 0, 0, 0},   {57, 1, 193, 0, 0, 0},
    {58, 2, 193, 2, 0, 0},    {59, 1, 193, 0, 1, 20},  {60, 1, 193, 0, 0, 0},
    {61, 1, 193, 0, 3, 0},    {62, 96, 193, 4, 24, 0}, {63, 1, 193, 0, 0, 0},
    {64, 1, 65, 0, 5, 0},     {66, 16, 80, 0, 3, 0},   {67, 1, 193, 0, 3, 0},
    {68, 1, 65, 0, 3, 0},
};

u8 D_us_80181868[][2] = {
    128, 143, 96, 127, 80, 94, 80, 143, 95, 95, 128, 128, 80, 111, 0, 0,
};

s16 D_us_80181878[] = {
    0, -4, -8, -12, -16, -20,
};

s32 D_us_80181884[] = {
    -12288, -16384, -24576, -32768, -40960, -49152,
};

s16 D_us_8018189C[] = {
    48, 64, 80, 96, 112, 128,
};

AnimationFrame D_us_801818A8[] = {
    {1, 1},       {1, 2},         {1, 3},         {1, 4},         {1, 5},
    {1, 6},       {1, 7},         {1, 8},         {1, 9},         {1, 10},
    {1, 11},      {1, 12},        {1, 13},        {1, 14},        {1, 15},
    {1, 16},      {1, 17},        {1, 18},        {1, 19},        {1, 20},
    {1, 21},      {1, 22},        {1, 23},        {1, 24},        {65535, 0},
    {2306, 2563}, {2049, 2820},   {1792, 3077},   {3334, 0},      {49160, 96},
    {257, 4},     {51, 3},        {0, 2176},      {32528, 32639}, {257, 2},
    {51, 1},      {0, 6272},      {32520, 32639}, {514, 2},       {51, 0},
    {0, 2176},    {32518, 65535}, {257, 4},       {115, 3},       {0, 2176},
    {49164, 96},  {257, 4},       {51, 3},        {0, 2176},      {32524, 0},
    {771, 2},     {2, 4},         {0, 6272},      {7944, 32543},  {257, 4},
    {51, 6},      {0, 6272},      {32532, 49279}, {257, 65534},   {51, 7},
    {0, 6272},    {49158, 49344}, {514, 2},       {123, 8},       {0, 2176},
};

static unkStr_8011E4BC s_PcData_8018191C[] = {
    {8, 192, 96, 0, 1, 1, 4, 51, 3, 142606336},
};

static unkStr_8011E4BC s_PcData_8018192C[] = {
    {16, 127, 127, 127, 1, 1, 2, 51, 1, 411041792},
};

static unkStr_8011E4BC s_PcData_8018193C[] = {
    {8, 127, 127, 127, 2, 2, 2, 51, 0, 142606336},
};

static unkStr_8011E4BC s_PcData_8018194C[] = {
    {6, 127, 255, 255, 1, 1, 4, 115, 3, 142606336},
};

static unkStr_8011E4BC s_PcData_8018195C[] = {
    {12, 192, 96, 0, 1, 1, 4, 51, 3, 142606336},
};

static unkStr_8011E4BC s_PcData_8018196C[] = {
    {12, 127, 0, 0, 3, 3, 2, 2, 4, 411041792},
};

static unkStr_8011E4BC s_PcData_8018197C[] = {
    {8, 31, 31, 127, 1, 1, 4, 51, 6, 411041792},
};

static unkStr_8011E4BC s_PcData_8018198C[] = {
    {20, 127, 127, 192, 1, 1, -2, 51, 7, 411041792},
};

static unkStr_8011E4BC s_PcData_8018199C[] = {
    {6, 192, 192, 192, 2, 2, 2, 123, 8, 142606336},
};

unkStr_8011E4BC* D_us_801819AC[] = {
    s_PcData_8018191C, s_PcData_8018192C, s_PcData_8018193C,
    s_PcData_8018194C, s_PcData_8018195C, s_PcData_8018196C,
    s_PcData_8018197C, s_PcData_8018198C, s_PcData_8018199C,
};

AnimationFrame D_us_801819D0[] = {
    {2, 1}, {2, 2}, {2, 3}, {2, 4}, {2, 5}, {2, 4}, {2, 3},     {2, 4},
    {2, 3}, {2, 4}, {2, 5}, {1, 6}, {1, 7}, {1, 8}, {65535, 0},
};

AnimationFrame D_us_80181A0C[] = {
    {1, 9},  {2, 10}, {2, 11}, {2, 12}, {2, 13}, {2, 14},    {2, 15},
    {2, 16}, {2, 17}, {2, 18}, {3, 19}, {4, 20}, {65535, 0},
};

AnimationFrame D_us_80181A40[] = {
    {2, 1}, {2, 2}, {2, 3}, {2, 4}, {2, 5}, {2, 6}, {2, 7}, {2, 8}, {65535, 0},
};

s32 D_us_80181A64[] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};

s16 D_us_80181AA4[][10] = {
    0,     0,     0,     351,   256,   256,   256,   96,    49,    512,   0,
    2,     6,     351,   256,   256,   256,   64,    49,    512,   0,     0,
    0,     351,   256,   28672, 28672, 64,    49,    512,   0,     0,     0,
    351,   256,   28672, 512,   16,    49,    512,   0,     0,     0,     351,
    256,   28672, 28672, 16,    49,    512,   0,     0,     0,     351,   256,
    28672, 512,   28672, 49,    512,   0,     0,     0,     351,   256,   28672,
    256,   28674, 49,    256,   0,     0,     0,     351,   256,   256,   28672,
    112,   49,    512,   0,     0,     0,     351,   256,   28672, 512,   28678,
    49,    512,   0,     0,     0,     351,   512,   512,   1024,  28673, 49,
    512,   0,     0,     0,     358,   256,   256,   256,   28677, 49,    512,
    0,     0,     0,     258,   256,   28672, 28672, 64,    49,    512,   0,
    0,     0,     351,   256,   28928, 256,   28677, 49,    512,   0,     0,
    0,     351,   256,   256,   256,   28677, 49,    512,   0,     0,     0,
    258,   256,   28672, 512,   64,    49,    512,   0,     0,     0,     258,
    256,   28672, 256,   64,    49,    512,   0,     0,     0,     258,   256,
    256,   28672, 0,     49,    512,   0,     0,     0,     258,   1024,  256,
    1024,  0,     49,    512,   0,     0,     0,     351,   256,   256,   28672,
    0,     49,    512,   0,     0,     0,     351,   512,   2048,  2048,  28679,
    49,    512,   0,     0,     0,     258,   256,   256,   256,   0,     49,
    512,   0,     0,     0,     351,   192,   192,   256,   16,    49,    512,
    8,     0,     8,     357,   256,   256,   256,   28679, 81,    512,   0,
    0,     0,     360,   28928, 28928, 512,   28679, 49,    512,   0,     0,
    0,     351,   512,   2048,  2048,  28680, 49,    512,   0,     0,     0,
    351,   256,   128,   256,   8,     49,    512,
};

s16 D_us_80181CAC[][6] = {
    0,     0,    256,   256,  256,   256,   1280,  2560, 256, 256,   256,
    0,     0,    0,     256,  28672, 28672, 512,   0,    0,   28928, 28928,
    256,   4096, 0,     0,    28928, 256,   28672, 2048, 0,   0,     256,
    28928, 256,  1024,  1280, 2560,  256,   256,   256,  256, 1280,  2560,
    256,   512,  28928, 256,  -2,    -24,   0,     -8,   2,   8,     0,
    24,    6,    -12,   8,    0,     7,     12,    -8,   -12, -9,    0,
    -7,    12,   -14,   -6,   -15,   7,     13,    -7,   16,  8,     -7,
    -22,   6,    -21,   -8,   21,    7,     22,
};

static Point16 s_PcData_80181D0C[] = {
    {-2, -24},
};

static Point16 s_PcData_80181D1C[] = {
    {6, -12},
};

static Point16 s_PcData_80181D10[] = {
    {0, -8},
};

static Point16 s_PcData_80181D20[] = {
    {8, 0},
};

static Point16 s_PcData_80181D14[] = {
    {2, 8},
};

static Point16 s_PcData_80181D24[] = {
    {7, 12},
};

static Point16 s_PcData_80181D18[] = {
    {0, 24},
};

static Point16 s_PcData_80181D30[] = {
    {-7, 12},
};

static Point16 s_PcData_80181D2C[] = {
    {-9, 0},
};

static Point16 s_PcData_80181D28[] = {
    {-8, -12},
};

static Point16 s_PcData_80181D3C[] = {
    {13, -7},
};

static Point16 s_PcData_80181D40[] = {
    {16, 8},
};

static Point16 s_PcData_80181D34[] = {
    {-14, -6},
};

static Point16 s_PcData_80181D38[] = {
    {-15, 7},
};

static Point16 s_PcData_80181D44[] = {
    {-7, -22},
};

static Point16 s_PcData_80181D48[] = {
    {6, -21},
};

static Point16 s_PcData_80181D4C[] = {
    {-8, 21},
};

static Point16 s_PcData_80181D50[] = {
    {7, 22},
};

Point16* D_us_80181D54[72] = {
    s_PcData_80181D0C, s_PcData_80181D1C, s_PcData_80181D10, s_PcData_80181D1C,
    s_PcData_80181D20, s_PcData_80181D10, s_PcData_80181D20, s_PcData_80181D14,
    s_PcData_80181D10, s_PcData_80181D20, s_PcData_80181D24, s_PcData_80181D14,
    s_PcData_80181D24, s_PcData_80181D18, s_PcData_80181D14, s_PcData_80181D14,
    s_PcData_80181D18, s_PcData_80181D30, s_PcData_80181D14, s_PcData_80181D30,
    s_PcData_80181D2C, s_PcData_80181D10, s_PcData_80181D14, s_PcData_80181D2C,
    s_PcData_80181D10, s_PcData_80181D2C, s_PcData_80181D28, s_PcData_80181D10,
    s_PcData_80181D28, s_PcData_80181D0C, s_PcData_80181D1C, s_PcData_80181D3C,
    s_PcData_80181D20, s_PcData_80181D3C, s_PcData_80181D40, s_PcData_80181D20,
    s_PcData_80181D40, s_PcData_80181D24, s_PcData_80181D20, s_PcData_80181D28,
    s_PcData_80181D2C, s_PcData_80181D34, s_PcData_80181D2C, s_PcData_80181D38,
    s_PcData_80181D34, s_PcData_80181D2C, s_PcData_80181D30, s_PcData_80181D38,
    s_PcData_80181D0C, s_PcData_80181D28, s_PcData_80181D44, s_PcData_80181D0C,
    s_PcData_80181D48, s_PcData_80181D1C, s_PcData_80181D18, s_PcData_80181D4C,
    s_PcData_80181D30, s_PcData_80181D24, s_PcData_80181D50, s_PcData_80181D18,
    s_PcData_80181D44, s_PcData_80181D28, s_PcData_80181D34, s_PcData_80181D48,
    s_PcData_80181D3C, s_PcData_80181D1C, s_PcData_80181D38, s_PcData_80181D30,
    s_PcData_80181D4C, s_PcData_80181D40, s_PcData_80181D50, s_PcData_80181D24,
};

u16 D_us_80181E74[] = {
    404,
    409,
};

AnimationFrame D_us_80181E78[] = {
    {9, 36}, {8, 37}, {7, 38},  {6, 39}, {5, 40},
    {4, 41}, {3, 42}, {21, 43}, {0, 0},
};

u8 D_us_80181E9C[] = {
    10, 10, 14, 10, 18, 10, 22, 10, 10, 14, 14, 14, 18,  14,  22, 14,
    10, 18, 14, 18, 18, 18, 22, 18, 10, 22, 14, 22, 18,  22,  22, 22,
    1,  0,  1,  0,  1,  0,  3,  0,  1,  0,  5,  0,  1,   0,   7,  0,
    1,  0,  9,  0,  1,  0,  11, 0,  1,  0,  13, 0,  255, 255, 0,  0,
};

AnimationFrame D_us_80181EDC[] = {
    {1, 1}, {1, 2}, {1, 3},  {1, 4},  {1, 5},  {1, 6},  {1, 7},
    {1, 8}, {1, 9}, {1, 10}, {1, 11}, {1, 12}, {1, 13}, {65535, 0},
};

static AnimationFrame s_PcData_80181F44[] = {
    {7, 513},   {7, 514},   {7, 515},  {7, 514},  {7, 513},  {7, 514},
    {7, 515},   {7, 514},   {7, 513},  {7, 514},  {7, 515},  {7, 514},
    {7, 513},   {7, 514},   {7, 515},  {7, 514},  {7, 513},  {7, 514},
    {7, 515},   {7, 514},   {8, 513},  {8, 514},  {8, 515},  {8, 514},
    {9, 513},   {9, 514},   {9, 515},  {9, 514},  {10, 513}, {10, 514},
    {10, 515},  {10, 514},  {11, 513}, {11, 514}, {11, 515}, {11, 514},
    {12, 513},  {12, 514},  {13, 515}, {13, 514}, {15, 513}, {15, 514},
    {15, 515},  {128, 514}, {4, 516},  {4, 517},  {4, 518},  {64, 519},
    {65535, 0},
};

AnimationFrame* D_us_80181F14[] = {
    s_PcData_80181F44,
    s_PcData_80181F44,
};

AnimationFrame D_us_80181F1C[] = {
    {64, 550},
    {0, 0},
};

AnimationFrame D_us_80181F24[] = {
    {2, 567}, {1, 656},  {2, 657}, {3, 656},
    {4, 657}, {12, 656}, {4, 528}, {65534, 1},
};

AnimationFrame D_us_80182008[] = {
    {64, 519},
    {0, 0},
};

s16 D_us_80182010[] = {
    3, 520, 6, 521, 5, 522, 6, 523, 7, 524,
    6, 525, 5, 526, 6, 527, 4, 520, 0, 0,
};

AnimationFrame D_us_80182038[] = {
    {1, 1040},
    {1, 1553},
    {16, 1554},
    {65535, 0},
};

AnimationFrame D_us_80182048[] = {
    {64, 1554},
    {65535, 0},
};

AnimationFrame D_us_80182050[] = {
    {16, 1688},
    {65535, 0},
};

AnimationFrame D_us_80182058[] = {
    {1, 1040},
    {1, 1553},
    {1, 1554},
    {65535, 0},
};

AnimationFrame D_us_80182068[] = {
    {1, 1554},
    {1, 1553},
    {1, 1040},
    {65535, 0},
};

s16 D_us_80182078[] = {
    8, 2067, 3, 1045, 5, 1046, 3, 1045, 6, 1047, 80, 1048, -1, 0,
};

s16 D_us_80182094[] = {
    8, 2068, 3, 1045, 5, 1046, 3, 1045, 6, 1047, 80, 1048, -1, 0,
};

AnimationFrame D_us_801820B0[] = {
    {6, 1047},
    {80, 1048},
    {65535, 0},
};

AnimationFrame D_us_801820BC[] = {
    {2, 2067},
    {6, 1047},
    {80, 1048},
    {65535, 0},
};

AnimationFrame D_us_801820CC[] = {
    {4, 2080}, {3, 3105}, {2, 3106}, {16, 3106}, {1, 3106}, {65535, 0},
};

AnimationFrame D_us_801820E4[] = {
    {4, 2080}, {3, 3105},  {3, 3106},  {3, 3107},  {2, 3108},  {1, 2588},
    {1, 2587}, {32, 1061}, {18, 2073}, {48, 1048}, {65535, 0},
};

AnimationFrame D_us_80182110[] = {
    {2, 550}, {2, 551}, {2, 552},  {2, 553},
    {2, 554}, {2, 555}, {16, 556}, {65535, 0},
};

AnimationFrame D_us_80182130[] = {
    {2, 1583}, {2, 1584}, {2, 1585},  {2, 1586},
    {2, 1587}, {2, 1588}, {16, 1589}, {65535, 0},
};

AnimationFrame D_us_80182150[] = {
    {2, 2102}, {2, 2103}, {2, 1064},  {2, 1065},
    {2, 1066}, {2, 1067}, {16, 1068}, {65535, 0},
};

AnimationFrame D_us_80182170[] = {
    {2, 550}, {2, 551},  {2, 552}, {2, 553},
    {3, 554}, {16, 557}, {6, 558}, {65535, 0},
};

AnimationFrame D_us_80182190[] = {
    {2, 550}, {2, 551}, {2, 552}, {2, 553}, {2, 554}, {6, 557},
    {2, 558}, {2, 552}, {2, 553}, {3, 554}, {2, 557}, {0, 7},
};

AnimationFrame D_us_801821C0[] = {
    {2, 2102}, {2, 2103},  {2, 1064}, {2, 1065},
    {3, 1066}, {16, 1069}, {6, 1070}, {65535, 0},
};

AnimationFrame D_us_801821E0[] = {
    {5, 19}, {1, 26}, {1, 25}, {6, 125}, {32, 126}, {0, 4},
};

s16 D_us_801821F8[] = {
    3,    4737, 3,    4738, 3,    4739, 3,    4740, 3,
    4741, 3,    4742, 3,    4735, 3,    4736, 0,    0,
};

AnimationFrame D_us_8018221C[] = {
    {64, 2080},
    {65535, 0},
};

AnimationFrame D_us_80182224[] = {
    {1, 718}, {1, 719}, {1, 718}, {3, 719},  {3, 718},
    {5, 719}, {1, 550}, {1, 558}, {32, 514}, {65535, 0},
};

AnimationFrame D_us_8018224C[] = {
    {1, 2231}, {2, 2232}, {1, 2230},  {1, 2231},  {1, 2233}, {1, 2230},
    {1, 2231}, {1, 2234}, {1, 2230},  {1, 2231},  {1, 2236}, {1, 2231},
    {1, 2235}, {1, 2231}, {32, 2230}, {65535, 0},
};

AnimationFrame D_us_8018228C[] = {
    {1, 1736}, {1, 1737}, {1, 1736}, {2, 1737}, {2, 1736},  {3, 1737},
    {3, 1736}, {5, 1737}, {1, 1583}, {1, 1553}, {65535, 0},
};

AnimationFrame D_us_801822B8[] = {
    {128, 720},
    {65535, 0},
};

AnimationFrame D_us_801822C0[] = {
    {128, 1745},
    {65535, 0},
};

AnimationFrame D_us_801822C8[] = {
    {128, 2258},
    {65535, 0},
    {128, 17},
    {65535, 0},
};

AnimationFrame D_us_801822D8[] = {
    {2, 536},  {2, 1159}, {2, 1160}, {1, 1602}, {8, 5257},  {16, 5258},
    {8, 5257}, {2, 1602}, {2, 1601}, {2, 1553}, {65535, 0},
};

AnimationFrame D_us_80182304[] = {
    {22, 8844},
    {128, 8845},
    {65535, 0},
};

AnimationFrame D_us_80182310[] = {
    {3, 2075}, {3, 2074}, {3, 2073}, {48, 1048}, {65535, 0},
};

s16 D_us_80182324[] = {
    1, 2203, 1, 2204, 16, 2203, -1, 0,
};

AnimationFrame D_us_80182334[] = {
    {2, 164}, {2, 165}, {1, 164},   {1, 165}, {13, 164},  {2, 166},
    {3, 167}, {2, 166}, {128, 166}, {2, 38},  {65535, 0},
};

AnimationFrame D_us_80182360[] = {
    {1, 8},   {1, 56},  {1, 146},  {1, 147},  {1, 148},   {1, 149}, {1, 150},
    {1, 151}, {1, 148}, {1, 149},  {1, 150},  {1, 151},   {1, 147}, {1, 148},
    {1, 149}, {1, 150}, {1, 151},  {16, 146}, {2, 55},    {1, 144}, {2, 145},
    {3, 144}, {4, 145}, {12, 144}, {4, 16},   {65535, 0},
};

AnimationFrame D_us_801823C8[] = {
    {4, 674},   {1, 680},  {2, 681},   {24, 680},  {4, 684},   {1, 682},
    {2, 683},   {24, 682}, {8, 684},   {5, 685},   {4, 684},   {3, 685},
    {2, 686},   {2, 685},  {1, 686},   {1, 687},   {1, 686},   {12, 687},
    {1, 688},   {2, 689},  {1, 690},   {1, 691},   {1, 692},   {1, 693},
    {1, 692},   {1, 691},  {1, 690},   {48, 688},  {65535, 0}, {5, 19},
    {1, 26},    {1, 25},   {6, 125},   {131, 126}, {128, 126}, {128, 25},
    {65535, 0}, {12, 25},  {65535, 0}, {6, 26},    {65535, 0},
};

AnimationFrame D_us_8018246C[] = {
    {2, 567}, {1, 656}, {2, 657}, {3, 656}, {4, 657},  {5, 657},  {5, 656},
    {5, 657}, {5, 657}, {5, 656}, {5, 657}, {12, 656}, {16, 550}, {65535, 0},
};

FrameProperty D_us_801824A4[] = {
    {0, 0, 0, 0},   {1, 3, 6, 20},   {2, 5, 7, 12},   {3, 12, 8, 12},
    {0, -1, 6, 16}, {0, 1, 8, 8},    {0, -5, 7, 5},   {-64, -88, 0, 0},
    {-4, 0, 6, 17}, {0, 0, 9, 16},   {-1, 17, 12, 7}, {-7, 10, 8, 5},
    {-2, 6, 8, 8},  {-6, 6, 7, 17},  {4, 6, 10, 9},   {-3, 3, 9, 20},
    {0, 8, 8, 8},   {-1, 10, 12, 7},
};

Point16 D_us_801824EC[] = {
    {7, -2}, {16, -2}, {5, -18}, {-14, -18}, {-23, -6}, {-24, -6}, {-25, -6},
};

Point16 D_us_80182508[] = {
    {7, 11}, {16, 11}, {5, -5}, {-14, -5}, {-23, 11}, {-24, 11}, {-25, 11},
};

Point16 D_us_80182524[] = {
    {-15, -4}, {-14, -14}, {-9, -6}, {-18, -6}, {-9, 2},
    {-11, -9}, {-16, -10}, {-7, 0},  {-14, 0},
};

s16 D_us_80182548[] = {
    15, 14, 18, 9, 9, 16, 11, 14, 7, 0,
};

Point16 D_us_8018255C[] = {
    {-15, 9}, {-14, -1}, {-9, 7},  {-18, 9},  {-9, 15},
    {-11, 4}, {-16, 3},  {-7, 13}, {-14, 13},
};

s16 D_us_80182580[] = {
    15, 14, 18, 9, 9, 16, 11, 14, 7, 0,
};

Point16 D_us_80182594[] = {
    {-15, -6},  {-14, -16}, {-9, -8}, {-18, -6}, {-9, 0},
    {-11, -11}, {-16, -12}, {-7, -2}, {-14, -2},
};

s16 D_us_801825B8[] = {
    15, 14, 18, 9, 9, 16, 11, 14, 7, 0, 1, 0, 5,
    0,  2,  0,  7, 0, 4,  0,  8,  0, 3, 0, 6, 0,
};

Point32 D_us_801825EC[] = {
    {262144, 131072}, {262144, -163840}, {1048576, 0},  {1048576, 0},
    {-1310720, 0},    {-2097152, 0},     {-3407872, 0},
};

Point32 D_us_80182624[] = {
    {0, 0},          {-163840, 0},     {-8192, 131072},   {-8192, -131072},
    {32768, 0},      {-131072, 98304}, {-131072, -98304}, {32768, 98304},
    {32768, -98304},
};

s32 D_us_8018266C[] = {
    1, 1, 5, 6, 0, 1, 1, 0, 0,
};

s32 D_us_80182690[] = {
    2, 5, 2, 0, 7, 2, 0, 2, 0,
};

s32 D_us_801826B4[] = {
    3, 6, 0, 3, 8, 0, 3, 0, 3,
};

s32 D_us_801826D8[] = {
    4, 0, 7, 8, 4, 0, 0, 4, 4,
};

s32 D_us_801826FC[] = {
    5, 5, 5, 0, 0, 5, 1, 2, 0,
};

s32 D_us_80182720[] = {
    6, 6, 0, 6, 0, 1, 6, 0, 3,
};

s32 D_us_80182744[] = {
    7, 0, 7, 0, 7, 1, 0, 7, 4,
};

s32 D_us_80182768[] = {
    8, 0, 0, 8, 8, 4, 3, 7, 8,
};

s32 D_us_8018278C[] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0,
};

u16 D_us_801827B0[3] = {
    33337,
    33338,
    33339,
};

s16 D_us_801827B8[] = {
    16, 14, 12, 10, 8, 6, 4, 2, 15, 13, 11, 9, 7, 5, 3, 255,
};

u16 D_us_801827D8[] = {
    0, 2, 4, 6, 8, 10, 12, 14, 1, 3, 5, 7, 9, 11, 13, 15,
};

s16 D_us_801827F8[] = {
    10, 11, 13, 17, 15, 12, 18, 14, 16, 0,
};

s16 D_us_8018280C[] = {
    10, 11, 17, 13, 15, 18, 12, 16, 14, 0,
};

s16 D_us_80182820[] = {
    1, 2, 4, 8, 6, 3, 9, 5, 7, 0,
};

s16 D_us_80182834[] = {
    1, 2, 8, 4, 6, 9, 3, 7, 5, 0,
};

s16 D_us_80182848[] = {
    19, 20, 22, 26, 24, 21, 27, 23, 25, 0,
};

s16 D_us_8018285C[] = {
    19, 20, 26, 22, 24, 27, 21, 25, 23, 0,
};

s16 D_us_80182870[] = {
    80, 88, 81, 89, 82, 90, 83, 91, 84, 92, 85, 93, 86, 94, 87, 0,
};

s16 D_us_80182890[][6] = {
    2, -2, 0,  -4, 0,  0, -3, -3, -1, 1, 2,  0, -4, -3,
    2, -2, -2, 2,  -1, 0, 0,  -4, 3,  3, 16, 0, -1, 0,
};

s32 D_us_801828C8[] = {
    28, 0, 28, 16, 28, 32, 28, 48, 60, 0, 60, 16, 60, 32, 60, 48,
};

u16 D_us_80182908[] = {
    38053, 39110, 40167, 41224, 42281, 43338, 44395, 45452, 46509, 47566,
    48623, 49680, 50737, 51794, 52851, 53908, 54965, 56022, 57079, 58136,
    58136, 58136, 58136, 58136, 58136, 58136, 58136, 58136, 58136, 57079,
    56022, 54965, 53908, 52851, 51794, 50737, 49680, 48623, 47566, 46509,
    45452, 44395, 43338, 42281, 41224, 40167, 39110, 38053,
};

RECT D_us_80182968 = {769, 504, 48, 1};

s16 D_us_80182994[] = {
    9,
    10,
    11,
    12,
};

u8 D_us_8018299C[] = {
    79, 79, 79,  0,  79, 79, 79,  0,  79, 79, 79,  0,  63,  63,
    95, 0,  63,  63, 95, 0,  63,  63, 95, 0,  47,  47, 111, 0,
    47, 47, 111, 0,  31, 31, 127, 0,  31, 31, 127, 0,
};

s16 D_us_801829C4[] = {
    -5, -9, -3, -13, -5, 1, -7, -1,
};

AnimationFrame D_us_801829D4[] = {
    {3, 1}, {3, 2}, {3, 3},  {3, 4},  {3, 5},  {3, 6},  {3, 7},
    {3, 8}, {3, 9}, {3, 10}, {3, 11}, {3, 12}, {3, 13}, {0, 0},
};

s32 D_us_80182A0C[] = {
    3968,
    256,
    1792,
    2176,
};

s16 D_us_80182A1C[6] = {
    1024, 1707, 2389, 3072, 3755, 4437,
};

static SVECTOR s_PcData_80182A40[] = {
    {-8, -32, -4, 0},
};

static SVECTOR s_PcData_80182A48[] = {
    {8, -32, -4, 0},
};

static SVECTOR s_PcData_80182A68[] = {
    {8, -16, -4, 0},
};

static SVECTOR s_PcData_80182A60[] = {
    {-8, -16, -4, 0},
};

static SVECTOR s_PcData_80182B48[] = {
    {-24, -48, 4, 0},
};

static SVECTOR s_PcData_80182B50[] = {
    {-8, -48, 4, 0},
};

static SVECTOR s_PcData_80182B00[] = {
    {-8, -32, 4, 0},
};

static SVECTOR s_PcData_80182B68[] = {
    {-24, -32, 4, 0},
};

static SVECTOR s_PcData_80182B58[] = {
    {8, -48, 4, 0},
};

static SVECTOR s_PcData_80182B60[] = {
    {24, -48, 4, 0},
};

static SVECTOR s_PcData_80182B70[] = {
    {24, -32, 4, 0},
};

static SVECTOR s_PcData_80182B08[] = {
    {8, -32, 4, 0},
};

static SVECTOR s_PcData_80182B78[] = {
    {-24, -16, 4, 0},
};

static SVECTOR s_PcData_80182B20[] = {
    {-8, -16, 4, 0},
};

static SVECTOR s_PcData_80182B90[] = {
    {-8, 0, 4, 0},
};

static SVECTOR s_PcData_80182B88[] = {
    {-24, 0, 4, 0},
};

static SVECTOR s_PcData_80182B28[] = {
    {8, -16, 4, 0},
};

static SVECTOR s_PcData_80182B80[] = {
    {24, -16, 4, 0},
};

static SVECTOR s_PcData_80182BA0[] = {
    {24, 0, 4, 0},
};

static SVECTOR s_PcData_80182B98[] = {
    {8, 0, 4, 0},
};

static SVECTOR s_PcData_80182A30[] = {
    {8, -72, -4, 0},
};

static SVECTOR s_PcData_80182AF0[] = {
    {8, -72, 4, 0},
};

static SVECTOR s_PcData_80182A98[] = {
    {8, -48, -4, 0},
    {24, -48, -4, 0},
};

static SVECTOR s_PcData_80182AD8[] = {
    {8, 0, -4, 0},
    {24, 0, -4, 0},
};

static SVECTOR s_PcData_80182B40[] = {
    {8, 72, 4, 0},
};

static SVECTOR s_PcData_80182A80[] = {
    {8, 72, -4, 0},
    {-24, -48, -4, 0},
};

static SVECTOR s_PcData_80182AA8[] = {
    {-24, -32, -4, 0},
};

static SVECTOR s_PcData_80182AB0[] = {
    {24, -32, -4, 0},
};

static SVECTOR s_PcData_80182AE8[] = {
    {-8, -72, 4, 0},
};

static SVECTOR s_PcData_80182AF8[] = {
    {-48, -32, 4, 0},
};

static SVECTOR s_PcData_80182B18[] = {
    {-48, -16, 4, 0},
};

static SVECTOR s_PcData_80182B30[] = {
    {48, -16, 4, 0},
};

static SVECTOR s_PcData_80182B10[] = {
    {48, -32, 4, 0},
};

static SVECTOR s_PcData_80182B38[] = {
    {-8, 72, 4, 0},
};

static SVECTOR s_PcData_80182A28[] = {
    {-8, -72, -4, 0},
};

static SVECTOR s_PcData_80182A90[] = {
    {-8, -48, -4, 0},
};

static SVECTOR s_PcData_80182AD0[] = {
    {-8, 0, -4, 0},
};

static SVECTOR s_PcData_80182A78[] = {
    {-8, 72, -4, 0},
};

static SVECTOR s_PcData_80182AB8[] = {
    {-24, -16, -4, 0},
};

static SVECTOR s_PcData_80182AC0[] = {
    {24, -16, -4, 0},
    {-24, 0, -4, 0},
};

static SVECTOR s_PcData_80182A50[] = {
    {48, -32, -4, 0},
};

static SVECTOR s_PcData_80182A70[] = {
    {48, -16, -4, 0},
};

static SVECTOR s_PcData_80182A38[] = {
    {-48, -32, -4, 0},
};

static SVECTOR s_PcData_80182A58[] = {
    {-48, -16, -4, 0},
};

SVECTOR* D_us_80182BA8[][4] = {
    s_PcData_80182A40, s_PcData_80182A48, s_PcData_80182A68, s_PcData_80182A60,
    s_PcData_80182B48, s_PcData_80182B50, s_PcData_80182B00, s_PcData_80182B68,
    s_PcData_80182B58, s_PcData_80182B60, s_PcData_80182B70, s_PcData_80182B08,
    s_PcData_80182B78, s_PcData_80182B20, s_PcData_80182B90, s_PcData_80182B88,
    s_PcData_80182B28, s_PcData_80182B80, s_PcData_80182BA0, s_PcData_80182B98,
    s_PcData_80182B00, s_PcData_80182B50, s_PcData_80182B48, s_PcData_80182B68,
    s_PcData_80182B70, s_PcData_80182B60, s_PcData_80182B58, s_PcData_80182B08,
    s_PcData_80182B90, s_PcData_80182B20, s_PcData_80182B78, s_PcData_80182B88,
    s_PcData_80182BA0, s_PcData_80182B80, s_PcData_80182B28, s_PcData_80182B98,
    s_PcData_80182B08, s_PcData_80182B58, s_PcData_80182B50, s_PcData_80182B00,
    s_PcData_80182B20, s_PcData_80182B00, s_PcData_80182B68, s_PcData_80182B78,
    s_PcData_80182B80, s_PcData_80182B70, s_PcData_80182B08, s_PcData_80182B28,
    s_PcData_80182B98, s_PcData_80182B28, s_PcData_80182B20, s_PcData_80182B90,
    s_PcData_80182B28, s_PcData_80182B08, s_PcData_80182B00, s_PcData_80182B20,
    s_PcData_80182A30, s_PcData_80182AF0, s_PcData_80182B58, s_PcData_80182A98,
    s_PcData_80182A98, s_PcData_80182B58, s_PcData_80182B08, s_PcData_80182A48,
    s_PcData_80182A68, s_PcData_80182B28, s_PcData_80182B98, s_PcData_80182AD8,
    s_PcData_80182AD8, s_PcData_80182B98, s_PcData_80182B40, s_PcData_80182A80,
    s_PcData_80182B68, s_PcData_80182B00, s_PcData_80182A40, s_PcData_80182AA8,
    s_PcData_80182B08, s_PcData_80182B70, s_PcData_80182AB0, s_PcData_80182A48,
    s_PcData_80182B58, s_PcData_80182AF0, s_PcData_80182AE8, s_PcData_80182B50,
    s_PcData_80182B78, s_PcData_80182B68, s_PcData_80182AF8, s_PcData_80182B18,
    s_PcData_80182B30, s_PcData_80182B10, s_PcData_80182B70, s_PcData_80182B80,
    s_PcData_80182B40, s_PcData_80182B98, s_PcData_80182B90, s_PcData_80182B38,
    s_PcData_80182B50, s_PcData_80182AE8, s_PcData_80182A28, s_PcData_80182A90,
    s_PcData_80182B00, s_PcData_80182B50, s_PcData_80182A90, s_PcData_80182A40,
    s_PcData_80182B90, s_PcData_80182B20, s_PcData_80182A60, s_PcData_80182AD0,
    s_PcData_80182B38, s_PcData_80182B90, s_PcData_80182AD0, s_PcData_80182A78,
    s_PcData_80182A60, s_PcData_80182B20, s_PcData_80182B78, s_PcData_80182AB8,
    s_PcData_80182AC0, s_PcData_80182B80, s_PcData_80182B28, s_PcData_80182A68,
    s_PcData_80182A60, s_PcData_80182A68, s_PcData_80182AD8, s_PcData_80182AD0,
    s_PcData_80182AD0, s_PcData_80182AD8, s_PcData_80182A80, s_PcData_80182A78,
    s_PcData_80182A28, s_PcData_80182A30, s_PcData_80182A98, s_PcData_80182A90,
    s_PcData_80182A90, s_PcData_80182A98, s_PcData_80182A48, s_PcData_80182A40,
    s_PcData_80182A50, s_PcData_80182B10, s_PcData_80182B30, s_PcData_80182A70,
    s_PcData_80182AE8, s_PcData_80182AF0, s_PcData_80182A30, s_PcData_80182A28,
    s_PcData_80182B18, s_PcData_80182AF8, s_PcData_80182A38, s_PcData_80182A58,
    s_PcData_80182A80, s_PcData_80182B40, s_PcData_80182B38, s_PcData_80182A78,
    s_PcData_80182AF8, s_PcData_80182B68, s_PcData_80182AA8, s_PcData_80182A38,
    s_PcData_80182AB8, s_PcData_80182B78, s_PcData_80182B18, s_PcData_80182A58,
    s_PcData_80182B70, s_PcData_80182B10, s_PcData_80182A50, s_PcData_80182AB0,
    s_PcData_80182A70, s_PcData_80182B30, s_PcData_80182B80, s_PcData_80182AC0,
    s_PcData_80182AA8, s_PcData_80182A40, s_PcData_80182A60, s_PcData_80182AB8,
    s_PcData_80182A48, s_PcData_80182AB0, s_PcData_80182AC0, s_PcData_80182A68,
    s_PcData_80182A38, s_PcData_80182AA8, s_PcData_80182AB8, s_PcData_80182A58,
    s_PcData_80182AB0, s_PcData_80182A50, s_PcData_80182A70, s_PcData_80182AC0,
};

u8 D_us_80182E88[46][5] = {
    56,  8,  16, 16, 13,  88,  8,  16, 16, 14,  88,  8,  16, 16, 30,
    88,  8,  16, 16, 46,  88,  8,  16, 16, 62,  88,  8,  16, 16, 78,
    88,  8,  16, 16, 94,  88,  8,  16, 16, 110, 88,  8,  16, 16, 126,
    104, 8,  16, 16, 78,  104, 8,  16, 16, 46,  104, 8,  16, 16, 14,
    104, 8,  16, 16, 110, 104, 24, 16, 16, 78,  104, 48, 16, 16, 14,
    104, 48, 16, 16, 14,  104, 48, 16, 16, 14,  104, 48, 16, 16, 14,
    104, 48, 16, 16, 14,  104, 48, 16, 16, 14,  104, 48, 16, 16, 78,
    104, 48, 16, 16, 78,  104, 48, 16, 16, 78,  104, 48, 16, 16, 78,
    104, 48, 16, 16, 78,  104, 48, 16, 16, 78,  104, 48, 16, 16, 78,
    104, 48, 16, 16, 78,  104, 48, 16, 16, 78,  104, 48, 16, 16, 78,
    56,  24, 16, 16, 15,  56,  40, 16, 72, 15,  80,  32, 16, 24, 15,
    80,  56, 16, 16, 15,  112, 72, 8,  8,  15,  112, 72, 8,  8,  15,
    112, 72, 8,  8,  79,  112, 72, 8,  8,  79,  80,  80, 24, 8,  15,
    80,  80, 24, 8,  79,  80,  80, 24, 8,  31,  80,  80, 24, 8,  95,
    104, 88, 16, 16, 15,  104, 88, 16, 16, 31,  80,  88, 24, 16, 15,
    80,  88, 24, 16, 31,
};

u8 D_us_8019A0C8 = 0;

u8 D_us_8019A0CC = 0;

u8 D_us_8019A0D0[] = {
    12,  154, 164, 76,  199, 16,  0,   7,   60,  28,  19,  156, 194, 42,  168,
    0,   5,   1,   0,   11,  9,   61,  211, 10,  2,   2,   73,  39,  118, 101,
    32,  98,  101, 101, 110, 32,  119, 97,  105, 116, 105, 110, 103, 1,   3,
    8,   102, 111, 114, 32,  121, 111, 117, 46,  3,   48,  6,   19,  155, 181,
    82,  40,  1,   5,   0,   129, 11,  14,  154, 160, 12,  200, 154, 161, 18,
    32,  154, 161, 24,  133, 9,   61,  212, 10,  2,   3,   83,  111, 32,  105,
    116, 32,  105, 115, 32,  121, 111, 117, 46,  46,  46,  1,   3,   16,  2,
    2,   66,  117, 116, 32,  119, 104, 121, 32,  105, 115, 32,  97,  32,  66,
    101, 108, 109, 111, 110, 116, 1,   3,   4,   112, 108, 97,  110, 110, 105,
    110, 103, 32,  116, 104, 101, 1,   3,   4,   114, 101, 115, 117, 114, 114,
    101, 99,  116, 105, 111, 110, 32,  111, 102, 1,   3,   4,   67,  111, 117,
    110, 116, 32,  68,  114, 97,  99,  117, 108, 97,  63,  15,  154, 161, 29,
    220, 9,   61,  214, 10,  2,   3,   65,  110, 115, 119, 101, 114, 32,  109,
    101, 33,  1,   3,   16,  2,   2,   87,  104, 121, 32,  105, 115, 32,  97,
    32,  66,  101, 108, 109, 111, 110, 116, 1,   3,   4,   112, 108, 97,  110,
    110, 105, 110, 103, 32,  116, 104, 101, 1,   3,   8,   114, 101, 115, 117,
    114, 114, 101, 99,  116, 105, 111, 110, 32,  111, 102, 1,   3,   4,   67,
    111, 117, 110, 116, 32,  68,  114, 97,  99,  117, 108, 97,  63,  3,   48,
    6,   5,   1,   0,   11,  9,   61,  215, 10,  2,   3,   67,  111, 117, 110,
    116, 32,  68,  114, 97,  99,  117, 108, 97,  32,  114, 105, 115, 101, 115,
    1,   3,   4,   98,  117, 116, 32,  111, 110, 99,  101, 32,  101, 118, 101,
    114, 121, 1,   3,   4,   99,  101, 110, 116, 117, 114, 121, 32,  3,   40,
    97,  110, 100, 32,  109, 121, 32,  114, 111, 108, 101, 1,   3,   4,   105,
    115, 32,  111, 118, 101, 114, 46,  32,  2,   2,   3,   28,  73,  102, 32,
    73,  32,  99,  97,  110, 1,   3,   4,   114, 101, 115, 117, 114, 114, 101,
    99,  116, 32,  104, 105, 109, 44,  1,   3,   20,  116, 104, 101, 110, 32,
    116, 104, 101, 32,  98,  97,  116, 116, 108, 101, 32,  119, 105, 108, 108,
    1,   3,   4,   108, 97,  115, 116, 32,  102, 111, 114, 32,  101, 116, 101,
    114, 110, 105, 116, 121, 33,  3,   48,  6,   14,  154, 160, 12,  204, 154,
    162, 45,  217, 154, 162, 40,  138, 5,   0,   129, 2,   4,   46,  46,  46,
    46,  46,  46,  46,  46,  46,  1,   3,   8,   11,  9,   61,  216, 10,  2,
    2,   73,  102, 32,  116, 104, 111, 115, 101, 32,  97,  114, 101, 32,  121,
    111, 117, 114, 1,   3,   4,   116, 114, 117, 101, 32,  102, 101, 101, 108,
    105, 110, 103, 115, 32,  116, 104, 101, 110, 1,   3,   4,   2,   3,   115,
    111, 32,  98,  101, 32,  105, 116, 46,  3,   48,  6,   8,   11,  17,  1,
    20,  51,  54,  0,
};

u8 D_us_8019A2E1[] = {
    12, 154, 164, 78,  232, 9, 9,  145, 11, 9,  62, 225, 10,
    3,  128, 3,   128, 17,  2, 11, 17,  3,  20, 51, 54,  0,
};

u8 D_us_8019A2FB[] = {
    14,  154, 160, 12,  204, 154, 163, 48,  8,   154, 164, 67,  50,  12,  154,
    164, 77,  221, 9,   9,   145, 3,   32,  11,  7,   60,  28,  19,  155, 181,
    82,  40,  1,   5,   0,   129, 11,  9,   62,  234, 10,  2,   3,   73,  116,
    39,  115, 32,  111, 118, 101, 114, 46,  46,  46,  66,  101, 108, 109, 111,
    110, 116, 46,  3,   48,  6,   19,  156, 194, 42,  168, 0,   5,   1,   0,
    11,  9,   62,  235, 10,  2,   3,   83,  111, 32,  3,   16,  116, 104, 101,
    32,  119, 97,  114, 32,  98,  101, 116, 119, 101, 101, 110, 1,   3,   4,
    2,   4,   104, 117, 109, 97,  110, 115, 32,  97,  110, 100, 32,  118, 97,
    109, 112, 105, 114, 101, 115, 1,   3,   4,   102, 105, 110, 97,  108, 108,
    121, 32,  101, 110, 100, 115, 32,  104, 101, 114, 101, 46,  46,  46,  3,
    48,  6,   5,   0,   129, 11,  2,   4,   46,  46,  46,  46,  46,  46,  46,
    46,  46,  46,  3,   56,  6,   5,   1,   0,   11,  9,   62,  236, 10,  2,
    2,   87,  104, 97,  116, 32,  110, 101, 101, 100, 32,  102, 111, 114, 32,
    116, 104, 101, 1,   3,   4,   115, 104, 101, 112, 104, 101, 114, 100, 32,
    3,   32,  119, 104, 101, 110, 32,  116, 104, 101, 1,   3,   4,   119, 111,
    108, 118, 101, 115, 32,  104, 97,  118, 101, 32,  97,  108, 108, 1,   3,
    4,   103, 111, 110, 101, 46,  46,  46,  1,   3,   28,  77,  121, 32,  116,
    105, 109, 101, 32,  111, 110, 32,  116, 104, 105, 115, 1,   3,   4,   119,
    111, 114, 108, 100, 32,  3,   36,  2,   3,   104, 97,  115, 32,  99,  111,
    109, 101, 32,  3,   32,  116, 111, 1,   3,   4,   97,  110, 32,  101, 110,
    100, 46,  46,  46,  3,   48,  6,   8,   17,  8,   0,   12,  154, 164, 77,
    210, 9,   9,   145, 3,   32,  11,  7,   60,  28,  19,  157, 208, 2,   40,
    0,   5,   2,   0,   11,  9,   62,  239, 10,  2,   4,   89,  111, 117, 39,
    118, 101, 32,  100, 101, 102, 101, 97,  116, 101, 100, 32,  109, 101, 46,
    1,   3,   24,  66,  117, 116, 32,  97,  108, 108, 32,  105, 115, 32,  2,
    3,   110, 111, 116, 32,  121, 101, 116, 1,   3,   4,   108, 111, 115, 116,
    46,  1,   3,   40,  2,   3,   84,  104, 101, 32,  114, 101, 115, 117, 114,
    114, 101, 99,  116, 105, 111, 110, 32,  111, 102, 1,   3,   4,   67,  111,
    117, 110, 116, 32,  68,  114, 97,  99,  117, 108, 97,  32,  2,   2,   105,
    115, 32,  97,  116, 1,   3,   4,   104, 97,  110, 100, 33,  3,   48,  6,
    8,   3,   96,  17,  5,   3,   32,  17,  6,   0,   0,   0,   0,   137, 24,
    8,   128, 8,   128, 255, 255, 0,   0,   0,   137, 25,  8,   128, 8,   128,
    255, 255, 0,   0,   0,   137, 26,  8,   128, 8,   128, 255, 255, 0,   0,
    0,   137, 27,  8,   128, 8,   128, 255, 255, 0,
};

static s16 s_PcData_801A3D04[] = {
    -32768,
    -16,
    -24,
    0,
};

static s16 s_PcData_801A3D0C[] = {
    -32767,
    -16,
    -24,
    0,
};

static s16 s_PcData_801A3D14[] = {
    -32766,
    -16,
    -24,
    0,
};

static s16 s_PcData_801A3D1C[] = {
    -32765,
    -16,
    -24,
    0,
};

static s16 s_PcData_801A3D24[] = {
    -32764,
    -16,
    -24,
    0,
};

static s16 s_PcData_801A3D2C[] = {
    -32763,
    -16,
    -24,
    0,
};

static s16 s_PcData_801A3D34[] = {
    -32762,
    -16,
    -24,
    0,
};

static s16 s_PcData_801A3D3C[] = {
    -32761,
    -16,
    -24,
    0,
};

static s16 s_PcData_801A3D44[] = {
    -32760,
    -16,
    -24,
    0,
};

static s16 s_PcData_801A3D4C[] = {
    -32759,
    -16,
    -24,
    0,
};

static s16 s_PcData_801A3D54[] = {
    -32758,
    -16,
    -24,
    0,
};

static s16 s_PcData_801A3D5C[] = {
    -32757,
    -16,
    -24,
    0,
};

static s16 s_PcData_801A3D64[] = {
    -32756,
    -16,
    -24,
    0,
};

static s16 s_PcData_801A3D6C[] = {
    -32755,
    -16,
    -24,
    0,
};

static s16 s_PcData_801A3D74[] = {
    -32754,
    -16,
    -24,
    0,
};

static s16 s_PcData_801A3D7C[] = {
    -32753,
    -16,
    -16,
    0,
};

static s16 s_PcData_801A3D84[] = {
    -32752,
    -16,
    -24,
    0,
};

static s16 s_PcData_801A3D8C[] = {
    -32751,
    -16,
    -24,
    0,
};

static s16 s_PcData_801A3D94[] = {
    -32750,
    -16,
    -24,
    0,
};

static s16 s_PcData_801A3D9C[] = {
    -32749,
    -16,
    -24,
    0,
};

static s16 s_PcData_801A3DA4[] = {
    -32748,
    -16,
    -32,
    0,
};

static s16 s_PcData_801A3DAC[] = {
    -32747,
    -16,
    -24,
    0,
};

static s16 s_PcData_801A3DB4[] = {
    -32746,
    -16,
    -24,
    0,
};

static s16 s_PcData_801A3DBC[] = {
    -32745,
    -16,
    -24,
    0,
};

static s16 s_PcData_801A3DC4[] = {
    -32744,
    -16,
    -24,
    0,
};

static s16 s_PcData_801A3DCC[] = {
    -32743,
    -16,
    -24,
    0,
};

static s16 s_PcData_801A3DD4[] = {
    -32742,
    -32,
    -16,
    0,
};

static s16 s_PcData_801A3DDC[] = {
    -32741,
    -24,
    -24,
    0,
};

static s16 s_PcData_801A3DE4[] = {
    -32740,
    -13,
    -38,
    0,
};

static s16 s_PcData_801A3DEC[] = {
    -32739,
    -16,
    -24,
    0,
};

static s16 s_PcData_801A3DF4[] = {
    -32738,
    -16,
    -16,
    0,
};

static s16 s_PcData_801A3DFC[] = {
    -32737,
    -16,
    -24,
    0,
};

static s16 s_PcData_801A3E04[] = {
    -32736,
    -24,
    -16,
    0,
};

static s16 s_PcData_801A3E0C[] = {
    -32735,
    -24,
    -24,
    0,
};

static s16 s_PcData_801A3E14[] = {
    -32734,
    -16,
    -32,
    0,
};

static s16 s_PcData_801A3E1C[] = {
    -32733,
    -16,
    -32,
    0,
};

static s16 s_PcData_801A3E24[] = {
    -32732,
    -24,
    -16,
    0,
};

static s16 s_PcData_801A3E2C[] = {
    -32731,
    -16,
    -24,
    0,
};

static s16 s_PcData_801A3E34[] = {
    -32730,
    -24,
    -24,
    0,
};

static s16 s_PcData_801A3E3C[] = {
    -32729,
    -16,
    -24,
    0,
};

static s16 s_PcData_801A3E44[] = {
    -32728,
    -16,
    -24,
    0,
};

static s16 s_PcData_801A3E4C[] = {
    -32727,
    -16,
    -24,
    0,
};

static s16 s_PcData_801A3E54[] = {
    -32726,
    -16,
    -24,
    0,
};

static s16 s_PcData_801A3E5C[] = {
    -32725,
    -16,
    -24,
    0,
};

static s16 s_PcData_801A3E64[] = {
    -32724,
    -16,
    -24,
    0,
};

static s16 s_PcData_801A3E6C[] = {
    -32723,
    -16,
    -24,
    0,
};

static s16 s_PcData_801A3E74[] = {
    -32722,
    -16,
    -8,
    0,
};

static s16 s_PcData_801A3E7C[] = {
    -32721,
    -24,
    -8,
    0,
};

static s16 s_PcData_801A3E84[] = {
    -32720,
    -16,
    -8,
    0,
};

static s16 s_PcData_801A3E8C[] = {
    -32719,
    -16,
    -8,
    0,
};

static s16 s_PcData_801A3E94[] = {
    -32718,
    -16,
    -8,
    0,
};

static s16 s_PcData_801A3E9C[] = {
    -32717,
    -16,
    -8,
    0,
};

static s16 s_PcData_801A3EA4[] = {
    -32716,
    -13,
    -12,
    0,
};

static s16 s_PcData_801A3EAC[] = {
    -32715,
    -16,
    -24,
    0,
};

static s16 s_PcData_801A3EB4[] = {
    -32714,
    -24,
    -24,
    0,
};

static s16 s_PcData_801A3EBC[] = {
    -32713,
    -16,
    -24,
    0,
};

static s16 s_PcData_801A3EC4[] = {
    -32712,
    -11,
    -20,
    0,
};

static s16 s_PcData_801A3ECC[] = {
    -32711,
    -22,
    -21,
    0,
};

static s16 s_PcData_801A3ED4[] = {
    -32710,
    -24,
    -24,
    0,
};

static s16 s_PcData_801A3EDC[] = {
    -32709,
    -24,
    -24,
    0,
};

static s16 s_PcData_801A3EE4[] = {
    -32708,
    -16,
    -24,
    0,
};

static s16 s_PcData_801A3EEC[] = {
    -32707,
    -16,
    -24,
    0,
};

static s16 s_PcData_801A3EF4[] = {
    -32706,
    -16,
    -24,
    0,
};

static s16 s_PcData_801A3EFC[] = {
    -32705,
    -16,
    -24,
    0,
};

static s16 s_PcData_801A3F04[] = {
    -32704,
    -16,
    -8,
    0,
};

static s16 s_PcData_801A3F0C[] = {
    -32703,
    -16,
    -8,
    0,
};

static s16 s_PcData_801A3F14[] = {
    -32702,
    -16,
    -16,
    0,
};

static s16 s_PcData_801A3F1C[] = {
    -32701,
    -14,
    -18,
    0,
};

static s16 s_PcData_801A3F24[] = {
    -32700,
    -16,
    -24,
    0,
};

static s16 s_PcData_801A3F2C[] = {
    -32699,
    -16,
    -24,
    0,
};

static s16 s_PcData_801A3F34[] = {
    -32698,
    -16,
    -24,
    0,
};

static s16 s_PcData_801A3F3C[] = {
    -32697,
    -16,
    -24,
    0,
};

static s16 s_PcData_801A3F44[] = {
    -32696,
    -16,
    -24,
    0,
};

static s16 s_PcData_801A3F4C[] = {
    -32695,
    -16,
    -32,
    0,
};

static s16 s_PcData_801A3F54[] = {
    -32694,
    -8,
    -24,
    0,
};

static s16 s_PcData_801A3F5C[] = {
    -32693,
    -8,
    -24,
    0,
};

static s16 s_PcData_801A3F64[] = {
    -32692,
    -16,
    -24,
    0,
};

static s16 s_PcData_801A3F6C[] = {
    -32691,
    -8,
    -24,
    0,
};

static s16 s_PcData_801A3F74[] = {
    -32690,
    -8,
    -24,
    0,
};

static s16 s_PcData_801A3F7C[] = {
    -32689,
    -8,
    -24,
    0,
};

static s16 s_PcData_801A3F84[] = {
    -32688,
    -16,
    -24,
    0,
};

static s16 s_PcData_801A3F8C[] = {
    -32687,
    -8,
    -24,
    0,
};

static s16 s_PcData_801A3F94[] = {
    -32686,
    -8,
    -24,
    0,
};

static s16 s_PcData_801A3F9C[] = {
    -32685,
    -8,
    -24,
    0,
};

static s16 s_PcData_801A3FA4[] = {
    -32684,
    -8,
    -24,
    0,
};

static s16 s_PcData_801A3FAC[] = {
    -32683,
    -16,
    -24,
    0,
};

static s16 s_PcData_801A3FB4[] = {
    -32682,
    -24,
    -24,
    0,
};

static s16 s_PcData_801A3FBC[] = {
    -32681,
    -16,
    -24,
    0,
};

static s16 s_PcData_801A3FC4[] = {
    -32680,
    -16,
    -24,
    0,
};

static s16 s_PcData_801A3FCC[] = {
    -32679,
    -16,
    -24,
    0,
};

static s16 s_PcData_801A3FD4[] = {
    -32678,
    -16,
    -24,
    0,
};

static s16 s_PcData_801A3FDC[] = {
    -32677,
    -7,
    -20,
    0,
};

static s16 s_PcData_801A3FE4[] = {
    -32676,
    -16,
    -16,
    0,
};

static s16 s_PcData_801A3FEC[] = {
    -32675,
    -16,
    -24,
    0,
};

static s16 s_PcData_801A3FF4[] = {
    -32674,
    -12,
    -28,
    0,
};

static s16 s_PcData_801A3FFC[] = {
    -32673,
    -19,
    -27,
    0,
};

static s16 s_PcData_801A4004[] = {
    -32712,
    -16,
    -20,
    0,
};

static s16 s_PcData_801A400C[] = {
    -32711,
    -28,
    -21,
    0,
};

static s16 s_PcData_801A4014[] = {
    -32710,
    -32,
    -24,
    0,
};

static s16 s_PcData_801A401C[] = {
    -32672,
    -32,
    -24,
    0,
};

static s16 s_PcData_801A4024[] = {
    -32708,
    -21,
    -24,
    0,
};

static s16 s_PcData_801A402C[] = {
    -32708,
    -22,
    -24,
    0,
};

static s16 s_PcData_801A4034[] = {
    -32706,
    -20,
    -24,
    0,
};

static s16 s_PcData_801A403C[] = {
    -32706,
    -21,
    -24,
    0,
};

static s16 s_PcData_801A4044[] = {
    -32671,
    -16,
    -24,
    0,
};

static s16 s_PcData_801A404C[] = {
    -32670,
    -16,
    -24,
    0,
};

static s16 s_PcData_801A4054[] = {
    -32669,
    -16,
    -24,
    0,
};

static s16 s_PcData_801A405C[] = {
    -32668,
    -16,
    -24,
    0,
};

static s16 s_PcData_801A4064[] = {
    -32667,
    -16,
    -24,
    0,
};

static s16 s_PcData_801A406C[] = {
    -32666,
    -16,
    -24,
    0,
};

static s16 s_PcData_801A4074[] = {
    -32665,
    -16,
    -24,
    0,
};

static s16 s_PcData_801A407C[] = {
    -32664,
    -16,
    -24,
    0,
};

static s16 s_PcData_801A4084[] = {
    -32663,
    -16,
    -24,
    0,
};

static s16 s_PcData_801A408C[] = {
    -32662,
    -16,
    -24,
    0,
};

static s16 s_PcData_801A4094[] = {
    -32661,
    -8,
    -24,
    0,
};

static s16 s_PcData_801A409C[] = {
    -32660,
    -13,
    -19,
    0,
};

static s16 s_PcData_801A40A4[] = {
    -32712,
    -10,
    -20,
    0,
};

static s16 s_PcData_801A40AC[] = {
    -32711,
    -20,
    -21,
    0,
};

static s16 s_PcData_801A40B4[] = {
    -32710,
    -25,
    -24,
    0,
};

static s16 s_PcData_801A40BC[] = {
    -32709,
    -26,
    -24,
    0,
};

static s16 s_PcData_801A40C4[] = {
    -32659,
    -15,
    -24,
    0,
};

static s16 s_PcData_801A40CC[] = {
    -32659,
    -16,
    -24,
    0,
};

static s16 s_PcData_801A40D4[] = {
    -32658,
    -14,
    -24,
    0,
};

static s16 s_PcData_801A40DC[] = {
    -32658,
    -15,
    -24,
    0,
};

static s16 s_PcData_801A40E4[] = {
    -32657,
    -8,
    -24,
    0,
};

static s16 s_PcData_801A40EC[] = {
    -32656,
    -16,
    -32,
    0,
};

static s16 s_PcData_801A40F4[] = {
    -32655,
    -24,
    -24,
    0,
};

static s16 s_PcData_801A40FC[] = {
    -32654,
    -24,
    -24,
    0,
};

static s16 s_PcData_801A4104[] = {
    -32653,
    -16,
    -24,
    0,
};

static s16 s_PcData_801A410C[] = {
    -32652,
    -24,
    -24,
    0,
};

static s16 s_PcData_801A4114[] = {
    -32651,
    -24,
    -24,
    0,
};

static s16 s_PcData_801A411C[] = {
    -32650,
    -24,
    -24,
    0,
};

static s16 s_PcData_801A4124[] = {
    -32649,
    -16,
    -24,
    0,
};

static s16 s_PcData_801A412C[] = {
    -32648,
    -16,
    -24,
    0,
};

static s16 s_PcData_801A4134[] = {
    -32647,
    -16,
    -24,
    0,
};

static s16 s_PcData_801A413C[] = {
    -32646,
    -16,
    -8,
    0,
};

static s16 s_PcData_801A4144[] = {
    -32645,
    -16,
    0,
    0,
};

static s16 s_PcData_801A414C[] = {
    -32644,
    -24,
    0,
    0,
};

static s16 s_PcData_801A4154[] = {
    -32643,
    -16,
    -8,
    0,
};

static s16 s_PcData_801A415C[] = {
    -32642,
    -24,
    0,
    0,
};

static s16 s_PcData_801A4164[] = {
    -32641,
    -24,
    0,
    0,
};

static s16 s_PcData_801A416C[] = {
    -32640,
    -16,
    -8,
    0,
};

static s16 s_PcData_801A4174[] = {
    -32639,
    -24,
    -8,
    0,
};

static s16 s_PcData_801A417C[] = {
    -32638,
    -24,
    -16,
    0,
};

static s16 s_PcData_801A4184[] = {
    -32637,
    -24,
    -16,
    0,
};

static s16 s_PcData_801A418C[] = {
    -32636,
    -24,
    -7,
    0,
};

static s16 s_PcData_801A4194[] = {
    -32635,
    -32,
    -24,
    0,
};

static s16 s_PcData_801A419C[] = {
    -32634,
    -32,
    -24,
    0,
};

static s16 s_PcData_801A41A4[] = {
    -32633,
    -32,
    -16,
    0,
};

static s16 s_PcData_801A41AC[] = {
    -32632,
    -32,
    -24,
    0,
};

static s16 s_PcData_801A41B4[] = {
    -32631,
    -32,
    -16,
    0,
};

static s16 s_PcData_801A41BC[] = {
    -32630,
    -16,
    -8,
    0,
};

static s16 s_PcData_801A41C4[] = {
    -32629,
    -8,
    -16,
    0,
};

static s16 s_PcData_801A41CC[] = {
    -32628,
    -8,
    -16,
    0,
};

static s16 s_PcData_801A41D4[] = {
    -32627,
    -8,
    -48,
    0,
};

static s16 s_PcData_801A41DC[] = {
    -32626,
    -8,
    -48,
    0,
};

static s16 s_PcData_801A41E4[] = {
    -32625,
    -16,
    -24,
    0,
};

static s16 s_PcData_801A41EC[] = {
    -32624,
    -16,
    -8,
    0,
};

static s16 s_PcData_801A41F4[] = {
    -32623,
    -16,
    -8,
    0,
};

static s16 s_PcData_801A41FC[] = {
    -32622,
    -16,
    -8,
    0,
};

static s16 s_PcData_801A4204[] = {
    -32621,
    -16,
    -24,
    0,
};

static s16 s_PcData_801A420C[] = {
    -32620,
    -16,
    -24,
    0,
};

static s16 s_PcData_801A4214[] = {
    -32619,
    -16,
    -24,
    0,
};

static s16 s_PcData_801A421C[] = {
    -32618,
    -16,
    -24,
    0,
};

static s16 s_PcData_801A4224[] = {
    -32617,
    -16,
    -24,
    0,
};

static s16 s_PcData_801A422C[] = {
    -32616,
    -16,
    -32,
    0,
};

static s16 s_PcData_801A4234[] = {
    -32615,
    -16,
    -32,
    0,
};

static s16 s_PcData_801A423C[] = {
    -32614,
    -16,
    -24,
    0,
};

static s16 s_PcData_801A4244[] = {
    -32613,
    -16,
    -24,
    0,
};

static s16 s_PcData_801A424C[] = {
    -32612,
    -16,
    -24,
    0,
};

static s16 s_PcData_801A4254[] = {
    -32611,
    -16,
    -24,
    0,
};

static s16 s_PcData_801A425C[] = {
    -32610,
    -16,
    -24,
    0,
};

static s16 s_PcData_801A4264[] = {
    -32609,
    -16,
    -24,
    0,
};

static s16 s_PcData_801A426C[] = {
    -32608,
    -16,
    -24,
    0,
};

static s16 s_PcData_801A4274[] = {
    -32607,
    -16,
    -24,
    0,
};

static s16 s_PcData_801A427C[] = {
    -32606,
    -16,
    -24,
    0,
};

static s16 s_PcData_801A4284[] = {
    -32605,
    -16,
    -24,
    0,
};

static s16 s_PcData_801A428C[] = {
    -32604,
    -16,
    -24,
    11,
};

static s16 s_PcData_801A4294[] = {
    -32603,
    -16,
    -24,
    12,
};

static s16 s_PcData_801A429C[] = {
    -32602,
    -16,
    -24,
    13,
};

static s16 s_PcData_801A42A4[] = {
    -32601,
    -16,
    -24,
    0,
};

static s16 s_PcData_801A42AC[] = {
    -32600,
    -16,
    -24,
    0,
};

static s16 s_PcData_801A42B4[] = {
    -32599,
    -16,
    -24,
    15,
};

static s16 s_PcData_801A42BC[] = {
    -32598,
    -16,
    -24,
    15,
};

static s16 s_PcData_801A42C4[] = {
    -32597,
    -24,
    -24,
    15,
};

static s16 s_PcData_801A42CC[] = {
    -32596,
    -16,
    -40,
    15,
};

static s16 s_PcData_801A42D4[] = {
    -32595,
    -16,
    -24,
    14,
};

static s16 s_PcData_801A42DC[] = {
    -32594,
    -24,
    -24,
    14,
};

static s16 s_PcData_801A42E4[] = {
    -32593,
    -19,
    -25,
    17,
};

static s16 s_PcData_801A42EC[] = {
    -32593,
    -19,
    -25,
    18,
};

static s16 s_PcData_801A42F4[] = {
    -32593,
    -19,
    -25,
    19,
};

static s16 s_PcData_801A42FC[] = {
    -32592,
    -16,
    -24,
    16,
};

static s16 s_PcData_801A4304[] = {
    -32591,
    -16,
    -24,
    16,
};

static s16 s_PcData_801A430C[] = {
    -32590,
    -16,
    -24,
    16,
};

static s16 s_PcData_801A4314[] = {
    -32589,
    -16,
    -24,
    16,
};

static s16 s_PcData_801A431C[] = {
    -32588,
    -16,
    -24,
    0,
};

static s16 s_PcData_801A4324[] = {
    -32587,
    -16,
    -24,
    0,
};

static s16 s_PcData_801A432C[] = {
    -32586,
    -16,
    -24,
    0,
};

static s16 s_PcData_801A4334[] = {
    -32585,
    -16,
    -24,
    0,
};

static s16 s_PcData_801A433C[] = {
    -32584,
    -16,
    -8,
    0,
};

static s16 s_PcData_801A4344[] = {
    -32583,
    -16,
    -8,
    0,
};

static s16 s_PcData_801A434C[] = {
    -32582,
    -16,
    0,
    0,
};

static s16 s_PcData_801A4354[] = {
    -32581,
    -16,
    -8,
    0,
};

static s16 s_PcData_801A435C[] = {
    -32580,
    -16,
    0,
    0,
};

static s16 s_PcData_801A4364[] = {
    -32579,
    -16,
    -8,
    0,
};

static s16 s_PcData_801A436C[] = {
    -32578,
    -16,
    -24,
    0,
};

static s16 s_PcData_801A4374[] = {
    -32577,
    -16,
    -24,
    0,
};

static s16 s_PcData_801A437C[] = {
    -32576,
    -16,
    -24,
    0,
};

static s16 s_PcData_801A4384[] = {
    -32575,
    -16,
    -24,
    0,
};

static s16 s_PcData_801A438C[] = {
    -32574,
    -8,
    -24,
    0,
};

static s16 s_PcData_801A4394[] = {
    -32573,
    -8,
    -24,
    0,
};

static s16 s_PcData_801A439C[] = {
    -32572,
    -16,
    -24,
    0,
};

s16* D_us_801A39B0[] = {
    NULL,
    s_PcData_801A3D04,
    s_PcData_801A3D0C,
    s_PcData_801A3D14,
    s_PcData_801A3D1C,
    s_PcData_801A3D24,
    s_PcData_801A3D2C,
    s_PcData_801A3D34,
    s_PcData_801A3D3C,
    s_PcData_801A3D44,
    s_PcData_801A3D4C,
    s_PcData_801A3D54,
    s_PcData_801A3D5C,
    s_PcData_801A3D64,
    s_PcData_801A3D6C,
    s_PcData_801A3D74,
    s_PcData_801A3D7C,
    s_PcData_801A3D84,
    s_PcData_801A3D8C,
    s_PcData_801A3D94,
    s_PcData_801A3D9C,
    s_PcData_801A3DA4,
    s_PcData_801A3DAC,
    s_PcData_801A3DB4,
    s_PcData_801A3DBC,
    s_PcData_801A3DC4,
    s_PcData_801A3DCC,
    s_PcData_801A3DD4,
    s_PcData_801A3DDC,
    s_PcData_801A3DE4,
    s_PcData_801A3DEC,
    s_PcData_801A3DF4,
    s_PcData_801A3DFC,
    s_PcData_801A3E04,
    s_PcData_801A3E0C,
    s_PcData_801A3E14,
    s_PcData_801A3E1C,
    s_PcData_801A3E24,
    s_PcData_801A3E2C,
    s_PcData_801A3E34,
    s_PcData_801A3E3C,
    s_PcData_801A3E44,
    s_PcData_801A3E4C,
    s_PcData_801A3E54,
    s_PcData_801A3E5C,
    s_PcData_801A3E64,
    s_PcData_801A3E6C,
    s_PcData_801A3E74,
    s_PcData_801A3E7C,
    s_PcData_801A3E84,
    s_PcData_801A3E8C,
    s_PcData_801A3E94,
    s_PcData_801A3E9C,
    s_PcData_801A3EA4,
    s_PcData_801A3EAC,
    s_PcData_801A3EB4,
    s_PcData_801A3EBC,
    s_PcData_801A3EC4,
    s_PcData_801A3ECC,
    s_PcData_801A3ED4,
    s_PcData_801A3EDC,
    s_PcData_801A3EE4,
    s_PcData_801A3EEC,
    s_PcData_801A3EF4,
    s_PcData_801A3EFC,
    s_PcData_801A3F04,
    s_PcData_801A3F0C,
    s_PcData_801A3F14,
    s_PcData_801A3F1C,
    s_PcData_801A3F24,
    s_PcData_801A3F2C,
    s_PcData_801A3F34,
    s_PcData_801A3F3C,
    s_PcData_801A3F44,
    s_PcData_801A3F4C,
    s_PcData_801A3F54,
    s_PcData_801A3F5C,
    s_PcData_801A3F64,
    s_PcData_801A3F6C,
    s_PcData_801A3F74,
    s_PcData_801A3F7C,
    s_PcData_801A3F84,
    s_PcData_801A3F8C,
    s_PcData_801A3F94,
    s_PcData_801A3F9C,
    s_PcData_801A3FA4,
    s_PcData_801A3FAC,
    s_PcData_801A3FB4,
    s_PcData_801A3FBC,
    s_PcData_801A3FC4,
    s_PcData_801A3FCC,
    s_PcData_801A3FD4,
    s_PcData_801A3FDC,
    s_PcData_801A3FE4,
    s_PcData_801A3FEC,
    s_PcData_801A3FF4,
    s_PcData_801A3FFC,
    s_PcData_801A4004,
    s_PcData_801A400C,
    s_PcData_801A4014,
    s_PcData_801A401C,
    s_PcData_801A4024,
    s_PcData_801A402C,
    s_PcData_801A4034,
    s_PcData_801A403C,
    s_PcData_801A4044,
    s_PcData_801A404C,
    s_PcData_801A4054,
    s_PcData_801A405C,
    s_PcData_801A4064,
    s_PcData_801A406C,
    s_PcData_801A4074,
    s_PcData_801A407C,
    s_PcData_801A4084,
    s_PcData_801A408C,
    s_PcData_801A4094,
    s_PcData_801A409C,
    s_PcData_801A40A4,
    s_PcData_801A40AC,
    s_PcData_801A40B4,
    s_PcData_801A40BC,
    s_PcData_801A40C4,
    s_PcData_801A40CC,
    s_PcData_801A40D4,
    s_PcData_801A40DC,
    s_PcData_801A40E4,
    s_PcData_801A40EC,
    s_PcData_801A40F4,
    s_PcData_801A40FC,
    s_PcData_801A4104,
    s_PcData_801A410C,
    s_PcData_801A4114,
    s_PcData_801A411C,
    s_PcData_801A4124,
    s_PcData_801A412C,
    s_PcData_801A4134,
    s_PcData_801A413C,
    s_PcData_801A4144,
    s_PcData_801A414C,
    s_PcData_801A4154,
    s_PcData_801A415C,
    s_PcData_801A4164,
    s_PcData_801A416C,
    s_PcData_801A4174,
    s_PcData_801A417C,
    s_PcData_801A4184,
    s_PcData_801A418C,
    s_PcData_801A4194,
    s_PcData_801A419C,
    s_PcData_801A41A4,
    s_PcData_801A41AC,
    s_PcData_801A41B4,
    s_PcData_801A41BC,
    s_PcData_801A41C4,
    s_PcData_801A41CC,
    s_PcData_801A41D4,
    s_PcData_801A41DC,
    s_PcData_801A41E4,
    s_PcData_801A41EC,
    s_PcData_801A41F4,
    s_PcData_801A41FC,
    s_PcData_801A4204,
    s_PcData_801A420C,
    s_PcData_801A4214,
    s_PcData_801A421C,
    s_PcData_801A4224,
    s_PcData_801A422C,
    s_PcData_801A4234,
    s_PcData_801A423C,
    s_PcData_801A4244,
    s_PcData_801A424C,
    s_PcData_801A4254,
    s_PcData_801A425C,
    s_PcData_801A4264,
    s_PcData_801A426C,
    s_PcData_801A4274,
    s_PcData_801A427C,
    s_PcData_801A4284,
    s_PcData_801A428C,
    s_PcData_801A4294,
    s_PcData_801A429C,
    s_PcData_801A42A4,
    s_PcData_801A42AC,
    s_PcData_801A42B4,
    s_PcData_801A42BC,
    s_PcData_801A42C4,
    s_PcData_801A42CC,
    s_PcData_801A42D4,
    s_PcData_801A42DC,
    s_PcData_801A42E4,
    s_PcData_801A42EC,
    s_PcData_801A42F4,
    s_PcData_801A42FC,
    s_PcData_801A4304,
    s_PcData_801A430C,
    s_PcData_801A4314,
    s_PcData_801A431C,
    s_PcData_801A4324,
    s_PcData_801A432C,
    s_PcData_801A4334,
    s_PcData_801A433C,
    s_PcData_801A4344,
    s_PcData_801A434C,
    s_PcData_801A4354,
    s_PcData_801A435C,
    s_PcData_801A4364,
    s_PcData_801A436C,
    s_PcData_801A4374,
    s_PcData_801A437C,
    s_PcData_801A4384,
    s_PcData_801A438C,
    s_PcData_801A4394,
    s_PcData_801A439C,
};

static s16 s_PcData_801A43F8[] = {
    1, 48, -11, -11, 24, 24, 0, 0, 0, 0, 24, 24, 0, 0,
};

static s16 s_PcData_801A4414[] = {
    1, 32, -11, -11, 24, 24, 0, 0, 24, 0, 48, 24, 0, 0,
};

static s16 s_PcData_801A4430[] = {
    1, 32, -11, -11, 24, 24, 0, 0, 48, 0, 72, 24, 0, 0,
};

static s16 s_PcData_801A444C[] = {
    1, 32, -11, -11, 24, 24, 0, 0, 72, 0, 96, 24, 0, 0,
};

static s16 s_PcData_801A4468[] = {
    1, 16, -11, -11, 24, 24, 0, 0, 0, 24, 24, 48, 0, 0,
};

static s16 s_PcData_801A4484[] = {
    1, 35, -11, -11, 24, 24, 0, 0, 72, 0, 96, 24, 0, 0,
};

static s16 s_PcData_801A44A0[] = {
    1, 35, -11, -11, 24, 24, 0, 0, 48, 0, 72, 24, 0, 0,
};

static s16 s_PcData_801A44BC[] = {
    1, 35, -11, -11, 24, 24, 0, 0, 24, 0, 48, 24, 0, 0,
};

static s16 s_PcData_801A44D8[] = {
    1, 0, -11, -11, 24, 24, 0, 0, 24, 24, 48, 48, 0, 0,
};

static s16 s_PcData_801A44F4[] = {
    1, 0, -11, -11, 24, 24, 1, 0, 24, 24, 48, 48, 0, 0,
};

static s16 s_PcData_801A4510[] = {
    1, 0, -11, -11, 24, 24, 0, 0, 48, 24, 72, 48, 0, 0,
};

static s16 s_PcData_801A452C[] = {
    1, 0, -11, -11, 24, 24, 1, 0, 48, 24, 72, 48, 0, 0,
};

static s16 s_PcData_801A4548[] = {
    1, 16, -7, -7, 16, 16, 0, 25, 0, 64, 16, 80, 0, 0,
};

static s16 s_PcData_801A4564[] = {
    1, 0, -7, -7, 16, 16, 0, 25, 16, 64, 32, 80, 0, 0,
};

static s16 s_PcData_801A4580[] = {
    1, 16, -7, -7, 16, 16, 0, 25, 0, 80, 16, 96, 0, 0,
};

static s16 s_PcData_801A459C[] = {
    1, 0, -7, -7, 16, 16, 0, 25, 16, 80, 32, 96, 0, 0,
};

static s16 s_PcData_801A45B8[] = {
    1, 4, -7, -7, 16, 16, 0, 25, 112, 64, 128, 80, 0, 0,
};

static s16 s_PcData_801A45D4[] = {
    1, 0, -3, -3, 8, 8, 0, 25, 112, 48, 120, 56, 0, 0,
};

static s16 s_PcData_801A45F0[] = {
    1, 4, -3, -3, 8, 8, 0, 25, 120, 48, 128, 56, 0, 0,
};

static s16 s_PcData_801A460C[] = {
    1, 0, -3, -3, 8, 8, 0, 25, 112, 56, 120, 64, 0, 0,
};

s16* D_us_801A43A4[] = {
    NULL,
    s_PcData_801A43F8,
    s_PcData_801A4414,
    s_PcData_801A4430,
    s_PcData_801A444C,
    s_PcData_801A4468,
    s_PcData_801A4484,
    s_PcData_801A44A0,
    s_PcData_801A44BC,
    s_PcData_801A44D8,
    s_PcData_801A44F4,
    s_PcData_801A4510,
    s_PcData_801A452C,
    s_PcData_801A4548,
    s_PcData_801A4564,
    s_PcData_801A4580,
    s_PcData_801A459C,
    s_PcData_801A45B8,
    s_PcData_801A45D4,
    s_PcData_801A45F0,
    s_PcData_801A460C,
};

static s16 s_PcData_801A46BC[] = {
    1, 0, 0, -14, 16, 16, 0, 32, 112, 16, 128, 32, 0, 0,
};

static s16 s_PcData_801A46D8[] = {
    1, 32, 0, -18, 16, 16, 0, 32, 112, 0, 128, 16, 0, 0,
};

static s16 s_PcData_801A46F4[] = {
    1, 0, -3, -16, 24, 16, 0, 32, 64, 48, 88, 64, 0, 0,
};

static s16 s_PcData_801A4710[] = {
    1, 0, -3, -16, 24, 16, 0, 32, 88, 48, 112, 64, 0, 0,
};

static s16 s_PcData_801A472C[] = {
    1, 0, 0, -13, 16, 16, 0, 32, 80, 32, 96, 48, 0, 0,
};

static s16 s_PcData_801A4748[] = {
    1, 0, -2, -17, 16, 24, 0, 32, 112, 32, 128, 56, 0, 0,
};

static s16 s_PcData_801A4764[] = {
    1, 0, -2, -14, 16, 16, 0, 32, 96, 32, 112, 48, 0, 0,
};

static s16 s_PcData_801A4780[] = {
    1, 0, -2, -14, 16, 16, 0, 32, 96, 16, 112, 32, 0, 0,
};

static s16 s_PcData_801A479C[] = {
    1, 32, -1, -15, 16, 16, 0, 32, 96, 0, 112, 16, 0, 0,
};

static s16 s_PcData_801A47B8[] = {
    1, 0, 1, -1, 16, 16, 0, 32, 112, 16, 128, 32, 0, 0,
};

static s16 s_PcData_801A47D4[] = {
    1, 32, 1, -5, 16, 16, 0, 32, 112, 0, 128, 16, 0, 0,
};

static s16 s_PcData_801A47F0[] = {
    1, 0, -2, -3, 24, 16, 0, 32, 64, 48, 88, 64, 0, 0,
};

static s16 s_PcData_801A480C[] = {
    1, 0, -2, -3, 24, 16, 0, 32, 88, 48, 112, 64, 0, 0,
};

static s16 s_PcData_801A4828[] = {
    1, 0, 1, 0, 16, 16, 0, 32, 80, 32, 96, 48, 0, 0,
};

static s16 s_PcData_801A4844[] = {
    1, 0, -1, -4, 16, 24, 0, 32, 112, 32, 128, 56, 0, 0,
};

static s16 s_PcData_801A4860[] = {
    1, 0, -1, -1, 16, 16, 0, 32, 96, 32, 112, 48, 0, 0,
};

static s16 s_PcData_801A487C[] = {
    1, 0, -1, -1, 16, 16, 0, 32, 96, 16, 112, 32, 0, 0,
};

static s16 s_PcData_801A4898[] = {
    1, 32, 0, -2, 16, 16, 0, 32, 96, 0, 112, 16, 0, 0,
};

static s16 s_PcData_801A48B4[] = {
    1, 0, 0, -16, 16, 16, 0, 32, 112, 16, 128, 32, 0, 0,
};

static s16 s_PcData_801A48D0[] = {
    1, 32, 0, -20, 16, 16, 0, 32, 112, 0, 128, 16, 0, 0,
};

static s16 s_PcData_801A48EC[] = {
    1, 0, -3, -18, 24, 16, 0, 32, 64, 48, 88, 64, 0, 0,
};

static s16 s_PcData_801A4908[] = {
    1, 0, -3, -18, 24, 16, 0, 32, 88, 48, 112, 64, 0, 0,
};

static s16 s_PcData_801A4924[] = {
    1, 0, 0, -15, 16, 16, 0, 32, 80, 32, 96, 48, 0, 0,
};

static s16 s_PcData_801A4940[] = {
    1, 0, -2, -19, 16, 24, 0, 32, 112, 32, 128, 56, 0, 0,
};

static s16 s_PcData_801A495C[] = {
    1, 0, -2, -16, 16, 16, 0, 32, 96, 32, 112, 48, 0, 0,
};

static s16 s_PcData_801A4978[] = {
    1, 0, -2, -16, 16, 16, 0, 32, 96, 16, 112, 32, 0, 0,
};

static s16 s_PcData_801A4994[] = {
    1, 32, -1, -17, 16, 16, 0, 32, 96, 0, 112, 16, 0, 0,
};

static s16 s_PcData_801A49B0[] = {
    1, 16, -3, -3, 8, 8, 24, 32, 0, 48, 8, 56, 0, 0,
};

static s16 s_PcData_801A49CC[] = {
    1, 0, -3, -3, 8, 8, 24, 32, 8, 48, 16, 56, 0, 0,
};

static s16 s_PcData_801A49E8[] = {
    1, 0, -3, -3, 8, 8, 24, 32, 16, 48, 24, 56, 0, 0,
};

static s16 s_PcData_801A4A04[] = {
    1, 0, -3, -3, 8, 8, 24, 32, 24, 48, 32, 56, 0, 0,
};

static s16 s_PcData_801A4A20[] = {
    1, 0, -3, -3, 8, 8, 24, 32, 32, 48, 40, 56, 0, 0,
};

static s16 s_PcData_801A4A3C[] = {
    1, 0, -3, -3, 8, 8, 24, 32, 40, 48, 48, 56, 0, 0,
};

static s16 s_PcData_801A4A58[] = {
    1, 0, -3, -3, 8, 8, 176, 32, 72, 24, 80, 32, 0, 0,
};

static s16 s_PcData_801A4A74[] = {
    1, 0, -3, -3, 8, 8, 15, 32, 80, 24, 88, 32, 0, 0,
};

static s16 s_PcData_801A4A90[] = {
    1, 0, -3, -3, 8, 8, 17, 32, 88, 24, 96, 32, 0, 0,
};

s16* D_us_801A4628[] = {
    NULL,
    s_PcData_801A46BC,
    s_PcData_801A46D8,
    s_PcData_801A46F4,
    s_PcData_801A4710,
    s_PcData_801A472C,
    s_PcData_801A4748,
    s_PcData_801A4764,
    s_PcData_801A4780,
    s_PcData_801A479C,
    s_PcData_801A47B8,
    s_PcData_801A47D4,
    s_PcData_801A47F0,
    s_PcData_801A480C,
    s_PcData_801A4828,
    s_PcData_801A4844,
    s_PcData_801A4860,
    s_PcData_801A487C,
    s_PcData_801A4898,
    s_PcData_801A48B4,
    s_PcData_801A48D0,
    s_PcData_801A48EC,
    s_PcData_801A4908,
    s_PcData_801A4924,
    s_PcData_801A4940,
    s_PcData_801A495C,
    s_PcData_801A4978,
    s_PcData_801A4994,
    s_PcData_801A49B0,
    s_PcData_801A49CC,
    s_PcData_801A49E8,
    s_PcData_801A4A04,
    s_PcData_801A4A20,
    s_PcData_801A4A3C,
    s_PcData_801A4A58,
    s_PcData_801A4A74,
    s_PcData_801A4A90,
};

static s16 s_PcData_801A4CE0[] = {
    1, 48, -32, -32, 64, 64, 4, 9, 0, 0, 64, 64, 0, 0,
};

static s16 s_PcData_801A4CFC[] = {
    1, 48, -32, -32, 64, 64, 5, 9, 0, 0, 64, 64, 0, 0,
};

static s16 s_PcData_801A4D18[] = {
    1, 48, -32, -32, 64, 64, 6, 9, 0, 0, 64, 64, 0, 0,
};

static s16 s_PcData_801A4D34[] = {
    1, 48, -32, -32, 64, 64, 7, 9, 0, 0, 64, 64, 0, 0,
};

static s16 s_PcData_801A4D50[] = {
    1, 48, -32, -32, 64, 64, 8, 9, 0, 0, 64, 64, 0, 0,
};

static s16 s_PcData_801A4D6C[] = {
    1, 48, -32, -32, 64, 64, 9, 9, 0, 0, 64, 64, 0, 0,
};

static s16 s_PcData_801A4D88[] = {
    1, 48, -32, -32, 64, 64, 10, 9, 0, 0, 64, 64, 0, 0,
};

static s16 s_PcData_801A4DA4[] = {
    1, 48, -32, -32, 64, 64, 11, 9, 0, 0, 64, 64, 0, 0,
};

static s16 s_PcData_801A4DC0[] = {
    1, 48, -32, -32, 64, 64, 12, 9, 0, 0, 64, 64, 0, 0,
};

static s16 s_PcData_801A4DDC[] = {
    1, 48, -32, -32, 64, 64, 13, 9, 0, 0, 64, 64, 0, 0,
};

static s16 s_PcData_801A4DF8[] = {
    1, 48, -32, -32, 64, 64, 14, 9, 0, 0, 64, 64, 0, 0,
};

static s16 s_PcData_801A4E14[] = {
    1, 48, -32, -32, 64, 64, 15, 9, 0, 0, 64, 64, 0, 0,
};

static s16 s_PcData_801A4E30[] = {
    1, 36, -32, -32, 64, 64, 15, 9, 64, 0, 128, 64, 0, 0,
};

static s16 s_PcData_801A4E4C[] = {
    1, 36, -32, -32, 64, 64, 11, 9, 64, 0, 128, 64, 0, 0,
};

static s16 s_PcData_801A4E68[] = {
    1, 24, -32, -32, 64, 64, 15, 9, 0, 64, 64, 128, 0, 0,
};

static s16 s_PcData_801A4E84[] = {
    1, 24, -32, -32, 64, 64, 11, 9, 0, 64, 64, 128, 0, 0,
};

static s16 s_PcData_801A4EA0[] = {
    1, 12, -32, -32, 64, 64, 15, 9, 64, 64, 128, 128, 0, 0,
};

static s16 s_PcData_801A4EBC[] = {
    1, 12, -32, -32, 64, 64, 11, 9, 64, 64, 128, 128, 0, 0,
};

static s16 s_PcData_801A4ED8[] = {
    1, 48, -32, -32, 64, 64, 15, 10, 0, 0, 64, 64, 0, 0,
};

static s16 s_PcData_801A4EF4[] = {
    1, 48, -32, -32, 64, 64, 11, 10, 0, 0, 64, 64, 0, 0,
};

static s16 s_PcData_801A4F10[] = {
    1, 36, -32, -32, 64, 64, 15, 10, 64, 0, 128, 64, 0, 0,
};

static s16 s_PcData_801A4F2C[] = {
    1, 36, -32, -32, 64, 64, 11, 10, 64, 0, 128, 64, 0, 0,
};

static s16 s_PcData_801A4F48[] = {
    1, 24, -32, -32, 64, 64, 15, 10, 0, 64, 64, 128, 0, 0,
};

static s16 s_PcData_801A4F64[] = {
    1, 24, -32, -32, 64, 64, 11, 10, 0, 64, 64, 128, 0, 0,
};

static s16 s_PcData_801A4F80[] = {
    1, 12, -32, -32, 64, 64, 15, 10, 64, 64, 128, 128, 0, 0,
};

static s16 s_PcData_801A4F9C[] = {
    1, 12, -32, -32, 64, 64, 11, 10, 64, 64, 128, 128, 0, 0,
};

static s16 s_PcData_801A4FB8[] = {
    1, 48, -32, -32, 64, 64, 15, 11, 0, 0, 64, 64, 0, 0,
};

static s16 s_PcData_801A4FD4[] = {
    1, 48, -32, -32, 64, 64, 11, 11, 0, 0, 64, 64, 0, 0,
};

static s16 s_PcData_801A4FF0[] = {
    1, 36, -32, -32, 64, 64, 15, 11, 64, 0, 128, 64, 0, 0,
};

static s16 s_PcData_801A500C[] = {
    1, 36, -32, -32, 64, 64, 11, 11, 64, 0, 128, 64, 0, 0,
};

static s16 s_PcData_801A5028[] = {
    1, 24, -32, -32, 64, 64, 15, 11, 0, 64, 64, 128, 0, 0,
};

static s16 s_PcData_801A5044[] = {
    1, 24, -32, -32, 64, 64, 11, 11, 0, 64, 64, 128, 0, 0,
};

static s16 s_PcData_801A5060[] = {
    1, 12, -32, -32, 64, 64, 15, 11, 64, 64, 128, 128, 0, 0,
};

static s16 s_PcData_801A507C[] = {
    1, 12, -32, -32, 64, 64, 11, 11, 64, 64, 128, 128, 0, 0,
};

static s16 s_PcData_801A5098[] = {
    1, 48, -32, -32, 64, 64, 0, 5, 0, 0, 64, 64, 0, 0,
};

static s16 s_PcData_801A50B4[] = {
    1, 48, -16, -16, 32, 32, 2, 0, 0, 0, 32, 32, 0, 0,
};

static s16 s_PcData_801A50D0[] = {
    1, 32, -16, -16, 32, 32, 2, 0, 32, 0, 64, 32, 0, 0,
};

static s16 s_PcData_801A50EC[] = {
    1, 32, -16, -16, 32, 32, 2, 0, 64, 0, 96, 32, 0, 0,
};

static s16 s_PcData_801A5108[] = {
    1, 36, -16, -16, 32, 32, 2, 0, 96, 0, 128, 32, 0, 0,
};

static s16 s_PcData_801A5124[] = {
    1, 16, -16, -16, 32, 32, 2, 0, 0, 32, 32, 64, 0, 0,
};

static s16 s_PcData_801A5140[] = {
    1, 0, -16, -16, 32, 32, 2, 0, 32, 32, 64, 64, 0, 0,
};

static s16 s_PcData_801A515C[] = {
    1, 0, -16, -16, 32, 32, 2, 0, 64, 32, 96, 64, 0, 0,
};

static s16 s_PcData_801A5178[] = {
    1, 4, -16, -16, 32, 32, 2, 0, 96, 32, 128, 64, 0, 0,
};

static s16 s_PcData_801A5194[] = {
    2, 24,  -16, -16, 16, 16, 3, 0,  0,  112, 16, 128,
    4, -16, -16, 32,  32, 2,  0, 96, 32, 128, 64, 0,
};

static s16 s_PcData_801A51C4[] = {
    2, 8,   -16, 0,  16, 16, 3, 0,  16, 112, 32, 128,
    4, -16, -16, 32, 32, 2,  0, 96, 32, 128, 64, 0,
};

static s16 s_PcData_801A51F4[] = {
    2, 8,   0,   0,  16, 16, 3, 0,  32, 112, 48, 128,
    4, -16, -16, 32, 32, 2,  0, 96, 32, 128, 64, 0,
};

static s16 s_PcData_801A5224[] = {
    2, 8,   0,   -16, 16, 16, 3, 0,  48, 112, 64, 128,
    4, -16, -16, 32,  32, 2,  0, 96, 32, 128, 64, 0,
};

static s16 s_PcData_801A5254[] = {
    2, 8,   -16, -8, 16, 16, 3, 0,  64, 112, 80, 128,
    4, -16, -16, 32, 32, 2,  0, 96, 32, 128, 64, 0,
};

static s16 s_PcData_801A5284[] = {
    2, 8,   -16, -24, 16, 16, 3, 0,  80, 112, 96, 128,
    4, -16, -16, 32,  32, 2,  0, 96, 32, 128, 64, 0,
};

static s16 s_PcData_801A52B4[] = {
    2, 8,   0,   -24, 16, 16, 3, 0,  96, 112, 112, 128,
    4, -16, -16, 32,  32, 2,  0, 96, 32, 128, 64,  0,
};

static s16 s_PcData_801A52E4[] = {
    2, 12,  0,   -8, 16, 16, 3, 0,  112, 112, 128, 128,
    4, -16, -16, 32, 32, 2,  0, 96, 32,  128, 64,  0,
};

static s16 s_PcData_801A5314[] = {
    2, 4,   -16, 0,  32, 16, 3, 0,  96, 64,  128, 80,
    4, -16, -16, 32, 32, 2,  0, 96, 32, 128, 64,  0,
};

static s16 s_PcData_801A5344[] = {
    2, 4,   -16, 0,  32, 16, 3, 0,  96, 80,  128, 96,
    4, -16, -16, 32, 32, 2,  0, 96, 32, 128, 64,  0,
};

static s16 s_PcData_801A5374[] = {
    2, 4,   -16, 0,  32, 16, 3, 0,  96, 96,  128, 112,
    4, -16, -16, 32, 32, 2,  0, 96, 32, 128, 64,  0,
};

static s16 s_PcData_801A53A4[] = {
    2, 32,  -16, -8, 32, 16, 3, 1,  48, 0,   80, 16,
    4, -16, -16, 32, 32, 2,  0, 96, 32, 128, 64, 0,
};

static s16 s_PcData_801A53D4[] = {
    2, 0,   -16, -8, 32, 16, 3, 1,  48, 16,  80, 32,
    4, -16, -16, 32, 32, 2,  0, 96, 32, 128, 64, 0,
};

static s16 s_PcData_801A5404[] = {
    2, 0,   -16, -8, 32, 16, 3, 1,  48, 32,  80, 48,
    4, -16, -16, 32, 32, 2,  0, 96, 32, 128, 64, 0,
};

static s16 s_PcData_801A5434[] = {
    2, 32,  -16, -16, 32, 16, 3, 1,  80, 0,   112, 16,
    4, -16, -16, 32,  32, 2,  0, 96, 32, 128, 64,  0,
};

static s16 s_PcData_801A5464[] = {
    2, 0,   -16, -16, 32, 16, 3, 1,  80, 16,  112, 32,
    4, -16, -16, 32,  32, 2,  0, 96, 32, 128, 64,  0,
};

static s16 s_PcData_801A5494[] = {
    2, 0,   -16, -16, 32, 16, 3, 1,  80, 32,  112, 48,
    4, -16, -16, 32,  32, 2,  0, 96, 32, 128, 64,  0,
};

static s16 s_PcData_801A54C4[] = {
    1, 16, -24, -24, 48, 48, 3, 0, 0, 64, 48, 112, 0, 0,
};

static s16 s_PcData_801A54E0[] = {
    2, 0,   -8,  8,  16, 48, 3, 1,  48, 48, 64,  96,
    0, -24, -24, 48, 48, 3,  0, 48, 64, 96, 112, 0,
};

static s16 s_PcData_801A5510[] = {
    3, 4,  -8, 40,  16, 48, 3,   1,   112, 48, 128, 96, 0, -8, 8,  16, 48, 3,
    1, 96, 48, 112, 96, 48, -24, -24, 48,  48, 3,   1,  0, 0,  48, 48, 0,  0,
};

static s16 s_PcData_801A5558[] = {
    5,  0,   -8,  104, 16, 48, 3,  1,  48, 48, 64,  96, 0,  -8, 72,
    16, 48,  3,   1,   32, 48, 48, 96, 0,  -8, 40,  16, 48, 3,  1,
    16, 48,  32,  96,  16, -8, 8,  16, 48, 3,  1,   0,  48, 16, 96,
    0,  -24, -24, 48,  48, 3,  0,  48, 64, 96, 112, 0,  0,
};

static s16 s_PcData_801A55CC[] = {
    5,  0,   -8,  104, 16, 48, 3,  1,  32, 48, 48, 96, 0,  -8, 72,
    16, 48,  3,   1,   16, 48, 32, 96, 16, -8, 40, 16, 48, 3,  1,
    0,  48,  16,  96,  0,  -8, 8,  16, 48, 3,  1,  48, 48, 64, 96,
    48, -24, -24, 48,  48, 3,  1,  0,  0,  48, 48, 0,  0,
};

static s16 s_PcData_801A5640[] = {
    5,  0,   -8,  104, 16, 48, 3,  1,  16, 48, 32,  96, 16, -8, 72,
    16, 48,  3,   1,   0,  48, 16, 96, 0,  -8, 40,  16, 48, 3,  1,
    48, 48,  64,  96,  0,  -8, 8,  16, 48, 3,  1,   32, 48, 48, 96,
    0,  -24, -24, 48,  48, 3,  0,  48, 64, 96, 112, 0,  0,
};

static s16 s_PcData_801A56B4[] = {
    5,  4,   -8,  104, 16, 48, 3,   1,  112, 48, 128, 96, 0,  -8, 72,
    16, 48,  3,   1,   96, 48, 112, 96, 0,   -8, 40,  16, 48, 3,  1,
    80, 48,  96,  96,  0,  -8, 8,   16, 48,  3,  1,   64, 48, 80, 96,
    48, -24, -24, 48,  48, 3,  1,   0,  0,   48, 48,  0,  0,
};

static s16 s_PcData_801A5728[] = {
    4,  16, -16, 8,   32,  24, 3,  1,  0,   96, 32, 120, 48,  -16, 72, 32,
    80, 3,  2,   0,   0,   32, 80, 48, -16, 8,  32, 80,  3,   2,   0,  0,
    32, 80, 16,  -24, -24, 48, 48, 3,  0,   0,  64, 48,  112, 0,
};

static s16 s_PcData_801A5784[] = {
    4,  0,  -16, 8,   32,  24, 3,  1,  32,  96, 64, 120, 35, -16, 72, 32,
    80, 3,  2,   32,  0,   64, 80, 35, -16, 8,  32, 80,  3,  2,   32, 0,
    64, 80, 48,  -24, -24, 48, 48, 3,  1,   0,  0,  48,  48, 0,
};

static s16 s_PcData_801A57E0[] = {
    4,  32,  -16, 72,  32,  80, 3,  2, 64,  0,  96, 80, 32,  -16, 8,  32,
    80, 3,   2,   64,  0,   96, 80, 0, -16, 8,  32, 24, 3,   1,   64, 96,
    96, 120, 0,   -24, -24, 48, 48, 3, 0,   48, 64, 96, 112, 0,
};

static s16 s_PcData_801A583C[] = {
    4,   36,  -16, 72,  32,  80,  3,  2, 96,  0, 128, 80, 36, -16, 8,  32,
    80,  3,   2,   96,  0,   128, 80, 4, -16, 8, 32,  24, 3,  1,   96, 96,
    128, 120, 48,  -24, -24, 48,  48, 3, 1,   0, 0,   48, 48, 0,
};

static s16 s_PcData_801A5898[] = {
    2, 12,  0,   0,  16, 16, 3, 2,  112, 112, 128, 128,
    4, -16, -16, 32, 32, 2,  0, 96, 32,  128, 64,  0,
};

static s16 s_PcData_801A58C8[] = {
    2, 0,   -8,  -8, 24, 24, 3, 2,  16, 80,  40, 104,
    4, -16, -16, 32, 32, 2,  0, 96, 32, 128, 64, 0,
};

static s16 s_PcData_801A58F8[] = {
    2, 0,   -8,  -16, 24, 32, 3, 2,  40, 80,  64, 112,
    4, -16, -16, 32,  32, 2,  0, 96, 32, 128, 64, 0,
};

static s16 s_PcData_801A5928[] = {
    2, 0,   -16, -16, 32, 32, 3, 2,  64, 80,  96, 112,
    4, -16, -16, 32,  32, 2,  0, 96, 32, 128, 64, 0,
};

static s16 s_PcData_801A5958[] = {
    1, 4, -16, -16, 32, 32, 3, 2, 96, 80, 128, 112, 0, 0,
};

static s16 s_PcData_801A5974[] = {
    1, 48, -16, -40, 32, 56, 3, 3, 0, 0, 32, 56, 0, 0,
};

static s16 s_PcData_801A5990[] = {
    1, 32, -16, -40, 32, 56, 3, 3, 32, 0, 64, 56, 0, 0,
};

static s16 s_PcData_801A59AC[] = {
    1, 32, -16, -40, 32, 56, 3, 3, 64, 0, 96, 56, 0, 0,
};

static s16 s_PcData_801A59C8[] = {
    1, 36, -16, -40, 32, 56, 3, 3, 96, 0, 128, 56, 0, 0,
};

static s16 s_PcData_801A59E4[] = {
    1, 4, -16, -40, 32, 56, 3, 3, 96, 56, 128, 112, 0, 0,
};

static s16 s_PcData_801A5A00[] = {
    1, 0, -16, -40, 32, 56, 3, 3, 64, 56, 96, 112, 0, 0,
};

static s16 s_PcData_801A5A1C[] = {
    1, 0, -16, -40, 32, 56, 3, 3, 32, 56, 64, 112, 0, 0,
};

static s16 s_PcData_801A5A38[] = {
    1, 16, -16, -40, 32, 56, 3, 3, 0, 56, 32, 112, 0, 0,
};

static s16 s_PcData_801A5A54[] = {
    1, 32, -16, -24, 32, 32, 3, 4, 64, 0, 96, 32, 0, 0,
};

static s16 s_PcData_801A5A70[] = {
    1, 36, -16, -24, 32, 32, 3, 4, 96, 0, 128, 32, 0, 0,
};

static s16 s_PcData_801A5A8C[] = {
    1, 0, -16, -24, 32, 32, 3, 4, 64, 32, 96, 64, 0, 0,
};

static s16 s_PcData_801A5AA8[] = {
    1, 4, -16, -24, 32, 32, 3, 4, 96, 32, 128, 64, 0, 0,
};

static s16 s_PcData_801A5AC4[] = {
    1, 0, -16, -24, 32, 32, 3, 4, 64, 64, 96, 96, 0, 0,
};

static s16 s_PcData_801A5AE0[] = {
    1, 4, -16, -24, 32, 32, 3, 4, 96, 64, 128, 96, 0, 0,
};

static s16 s_PcData_801A5AFC[] = {
    1, 8, -16, -24, 32, 32, 3, 4, 64, 96, 96, 128, 0, 0,
};

static s16 s_PcData_801A5B18[] = {
    1, 12, -16, -24, 32, 32, 3, 4, 96, 96, 128, 128, 0, 0,
};

static s16 s_PcData_801A5B34[] = {
    2, 48,  -16, -24, 32, 64, 2, 6,  0,  0,   32, 64,
    4, -16, -16, 32,  32, 2,  0, 96, 32, 128, 64, 0,
};

static s16 s_PcData_801A5B64[] = {
    2,  4,   -16, -16, 32, 32, 2, 0,  96, 32, 128, 64,
    32, -16, -16, 32,  48, 2,  6, 64, 0,  96, 48,  0,
};

static s16 s_PcData_801A5B94[] = {
    2, 32,  -16, -24, 32, 64, 2, 6,  32, 0,   64, 64,
    4, -16, -16, 32,  32, 2,  0, 96, 32, 128, 64, 0,
};

static s16 s_PcData_801A5BC4[] = {
    2,  4,   -16, -16, 32, 32, 2, 0,  96, 32,  128, 64,
    36, -16, -16, 32,  48, 2,  6, 96, 0,  128, 48,  0,
};

static s16 s_PcData_801A5BF4[] = {
    2, 48,  -24, -24, 48, 48, 2, 4,  0,  0,   48, 48,
    4, -16, -16, 32,  32, 2,  0, 96, 32, 128, 64, 0,
};

static s16 s_PcData_801A5C24[] = {
    2, 16,  -24, -20, 48, 32, 2, 4,  0,  48,  48, 80,
    4, -16, -16, 32,  32, 2,  0, 96, 32, 128, 64, 0,
};

static s16 s_PcData_801A5C54[] = {
    2, 24,  -16, -9, 32, 16, 2, 2,  0,  112, 32, 128,
    4, -16, -16, 32, 32, 2,  0, 96, 32, 128, 64, 0,
};

static s16 s_PcData_801A5C84[] = {
    2, 8,   -16, -7, 32, 16, 2, 2,  32, 112, 64, 128,
    4, -16, -16, 32, 32, 2,  0, 96, 32, 128, 64, 0,
};

static s16 s_PcData_801A5CB4[] = {
    2, 8,   -16, -9, 32, 16, 2, 2,  64, 112, 96, 128,
    4, -16, -16, 32, 32, 2,  0, 96, 32, 128, 64, 0,
};

static s16 s_PcData_801A5CE4[] = {
    2, 24,  -16, -16, 32, 16, 2, 3,  0,  112, 32, 128,
    4, -16, -16, 32,  32, 2,  0, 96, 32, 128, 64, 0,
};

static s16 s_PcData_801A5D14[] = {
    2, 8,   -16, -16, 32, 16, 2, 3,  32, 112, 64, 128,
    4, -16, -16, 32,  32, 2,  0, 96, 32, 128, 64, 0,
};

static s16 s_PcData_801A5D44[] = {
    2, 48,  -16, -24, 32, 64, 3, 6,  0,  0,   32, 64,
    4, -16, -16, 32,  32, 2,  0, 96, 32, 128, 64, 0,
};

static s16 s_PcData_801A5D74[] = {
    2,  4,   -16, -16, 32, 32, 2, 0,  96, 32, 128, 64,
    32, -16, -16, 32,  48, 3,  6, 64, 0,  96, 48,  0,
};

static s16 s_PcData_801A5DA4[] = {
    2, 32,  -16, -24, 32, 64, 3, 6,  32, 0,   64, 64,
    4, -16, -16, 32,  32, 2,  0, 96, 32, 128, 64, 0,
};

static s16 s_PcData_801A5DD4[] = {
    2,  4,   -16, -16, 32, 32, 2, 0,  96, 32,  128, 64,
    36, -16, -16, 32,  48, 3,  6, 96, 0,  128, 48,  0,
};

static s16 s_PcData_801A5E04[] = {
    2, 48,  -24, -24, 48, 48, 3, 4,  0,  0,   48, 48,
    4, -16, -16, 32,  32, 2,  0, 96, 32, 128, 64, 0,
};

static s16 s_PcData_801A5E34[] = {
    2, 16,  -24, -20, 48, 32, 3, 4,  0,  48,  48, 80,
    4, -16, -16, 32,  32, 2,  0, 96, 32, 128, 64, 0,
};

static s16 s_PcData_801A5E64[] = {
    2, 24,  -16, -9, 32, 16, 3, 2,  0,  112, 32, 128,
    4, -16, -16, 32, 32, 2,  0, 96, 32, 128, 64, 0,
};

static s16 s_PcData_801A5E94[] = {
    2, 8,   -16, -7, 32, 16, 3, 2,  32, 112, 64, 128,
    4, -16, -16, 32, 32, 2,  0, 96, 32, 128, 64, 0,
};

static s16 s_PcData_801A5EC4[] = {
    2, 8,   -16, -9, 32, 16, 3, 2,  64, 112, 96, 128,
    4, -16, -16, 32, 32, 2,  0, 96, 32, 128, 64, 0,
};

static s16 s_PcData_801A5EF4[] = {
    2, 24,  -16, -16, 32, 16, 3, 3,  0,  112, 32, 128,
    4, -16, -16, 32,  32, 2,  0, 96, 32, 128, 64, 0,
};

static s16 s_PcData_801A5F24[] = {
    2, 8,   -16, -16, 32, 16, 3, 3,  32, 112, 64, 128,
    4, -16, -16, 32,  32, 2,  0, 96, 32, 128, 64, 0,
};

static s16 s_PcData_801A5F54[] = {
    2, 24,  -16, -40, 32, 64, 2, 6,  0,  64,  32, 128,
    4, -16, -16, 32,  32, 2,  0, 96, 32, 128, 64, 0,
};

static s16 s_PcData_801A5F84[] = {
    2, 4,   -16, -16, 32, 32, 2, 0,  96, 32, 128, 64,
    0, -16, -32, 32,  48, 2,  6, 64, 48, 96, 96,  0,
};

static s16 s_PcData_801A5FB4[] = {
    2, 8,   -16, -40, 32, 64, 2, 6,  32, 64,  64, 128,
    4, -16, -16, 32,  32, 2,  0, 96, 32, 128, 64, 0,
};

static s16 s_PcData_801A5FE4[] = {
    2, 4,   -16, -16, 32, 32, 2, 0,  96, 32,  128, 64,
    4, -16, -32, 32,  48, 2,  6, 96, 48, 128, 96,  0,
};

static s16 s_PcData_801A6014[] = {
    2, 24,  -16, -40, 32, 64, 3, 6,  0,  64,  32, 128,
    4, -16, -16, 32,  32, 2,  0, 96, 32, 128, 64, 0,
};

static s16 s_PcData_801A6044[] = {
    2, 4,   -16, -16, 32, 32, 2, 0,  96, 32, 128, 64,
    0, -16, -32, 32,  48, 3,  6, 64, 48, 96, 96,  0,
};

static s16 s_PcData_801A6074[] = {
    2, 8,   -16, -40, 32, 64, 3, 6,  32, 64,  64, 128,
    4, -16, -16, 32,  32, 2,  0, 96, 32, 128, 64, 0,
};

static s16 s_PcData_801A60A4[] = {
    2, 4,   -16, -16, 32, 32, 2, 0,  96, 32,  128, 64,
    4, -16, -32, 32,  48, 3,  6, 96, 48, 128, 96,  0,
};

static s16 s_PcData_801A60D4[] = {
    1, 36, -32, -32, 64, 64, 0, 5, 64, 0, 128, 64, 0, 0,
};

static s16 s_PcData_801A60F0[] = {
    1, 36, -8, -8, 16, 16, 3, 1, 112, 0, 128, 16, 0, 0,
};

static s16 s_PcData_801A610C[] = {
    1, 4, -8, -8, 16, 16, 3, 1, 112, 16, 128, 32, 0, 0,
};

static s16 s_PcData_801A6128[] = {
    1, 4, -8, -8, 16, 16, 3, 1, 112, 32, 128, 48, 0, 0,
};

static s16 s_PcData_801A6144[] = {
    2, 16,  -18, -16, 32, 32, 2, 4,  0,  80,  32, 112,
    4, -16, -16, 32,  32, 2,  0, 96, 32, 128, 64, 0,
};

static s16 s_PcData_801A6174[] = {
    2,  4,   -16, -16, 32, 32, 2, 0, 96, 32, 128, 64,
    16, -16, -16, 32,  32, 3,  4, 0, 80, 32, 112, 0,
};

static s16 s_PcData_801A61A4[] = {
    2, 0,   -15, -16, 32, 32, 2, 4,  32, 80,  64, 112,
    4, -16, -16, 32,  32, 2,  0, 96, 32, 128, 64, 0,
};

static s16 s_PcData_801A61D4[] = {
    2, 4,   -16, -16, 32, 32, 2, 0,  96, 32, 128, 64,
    0, -16, -16, 32,  32, 3,  4, 32, 80, 64, 112, 0,
};

static s16 s_PcData_801A6204[] = {
    1, 24, -32, -32, 64, 64, 0, 5, 0, 64, 64, 128, 0, 0,
};

static s16 s_PcData_801A6220[] = {
    1, 12, -32, -32, 64, 64, 0, 5, 64, 64, 128, 128, 0, 0,
};

static s16 s_PcData_801A623C[] = {
    1, 48, -32, -32, 64, 64, 0, 7, 0, 0, 64, 64, 0, 0,
};

static s16 s_PcData_801A6258[] = {
    1, 36, -32, -32, 64, 64, 0, 7, 64, 0, 128, 64, 0, 0,
};

static s16 s_PcData_801A6274[] = {
    1, 48, -32, -32, 64, 64, 0, 8, 0, 0, 64, 64, 0, 0,
};

static s16 s_PcData_801A6290[] = {
    1, 36, -32, -32, 64, 64, 0, 8, 64, 0, 128, 64, 0, 0,
};

static s16 s_PcData_801A62AC[] = {
    1, 12, -32, -32, 64, 64, 0, 8, 64, 64, 128, 128, 0, 0,
};

static s16 s_PcData_801A62C8[] = {
    1, 24, -32, -32, 64, 64, 0, 8, 0, 64, 64, 128, 0, 0,
};

static s16 s_PcData_801A62E4[] = {
    1, 0, -16, -24, 32, 40, 0, 7, 16, 72, 48, 112, 0, 0,
};

s16* D_us_801A4AAC[] = {
    NULL,
    s_PcData_801A4CE0,
    s_PcData_801A4CFC,
    s_PcData_801A4D18,
    s_PcData_801A4D34,
    s_PcData_801A4D50,
    s_PcData_801A4D6C,
    s_PcData_801A4D88,
    s_PcData_801A4DA4,
    s_PcData_801A4DC0,
    s_PcData_801A4DDC,
    s_PcData_801A4DF8,
    s_PcData_801A4E14,
    s_PcData_801A4E30,
    s_PcData_801A4E4C,
    s_PcData_801A4E68,
    s_PcData_801A4E84,
    s_PcData_801A4EA0,
    s_PcData_801A4EBC,
    s_PcData_801A4ED8,
    s_PcData_801A4EF4,
    s_PcData_801A4F10,
    s_PcData_801A4F2C,
    s_PcData_801A4F48,
    s_PcData_801A4F64,
    s_PcData_801A4F80,
    s_PcData_801A4F9C,
    s_PcData_801A4FB8,
    s_PcData_801A4FD4,
    s_PcData_801A4FF0,
    s_PcData_801A500C,
    s_PcData_801A5028,
    s_PcData_801A5044,
    s_PcData_801A5060,
    s_PcData_801A507C,
    s_PcData_801A5098,
    s_PcData_801A50B4,
    s_PcData_801A50D0,
    s_PcData_801A50EC,
    s_PcData_801A5108,
    s_PcData_801A5124,
    s_PcData_801A5140,
    s_PcData_801A515C,
    s_PcData_801A5178,
    s_PcData_801A5194,
    s_PcData_801A51C4,
    s_PcData_801A51F4,
    s_PcData_801A5224,
    s_PcData_801A5254,
    s_PcData_801A5284,
    s_PcData_801A52B4,
    s_PcData_801A52E4,
    s_PcData_801A5314,
    s_PcData_801A5344,
    s_PcData_801A5374,
    s_PcData_801A53A4,
    s_PcData_801A53D4,
    s_PcData_801A5404,
    s_PcData_801A5434,
    s_PcData_801A5464,
    s_PcData_801A5494,
    s_PcData_801A54C4,
    s_PcData_801A54E0,
    s_PcData_801A5510,
    s_PcData_801A5558,
    s_PcData_801A55CC,
    s_PcData_801A5640,
    s_PcData_801A56B4,
    s_PcData_801A5728,
    s_PcData_801A5784,
    s_PcData_801A57E0,
    s_PcData_801A583C,
    s_PcData_801A5898,
    s_PcData_801A58C8,
    s_PcData_801A58F8,
    s_PcData_801A5928,
    s_PcData_801A5958,
    s_PcData_801A5974,
    s_PcData_801A5990,
    s_PcData_801A59AC,
    s_PcData_801A59C8,
    s_PcData_801A59E4,
    s_PcData_801A5A00,
    s_PcData_801A5A1C,
    s_PcData_801A5A38,
    s_PcData_801A5A54,
    s_PcData_801A5A70,
    s_PcData_801A5A8C,
    s_PcData_801A5AA8,
    s_PcData_801A5AC4,
    s_PcData_801A5AE0,
    s_PcData_801A5AFC,
    s_PcData_801A5B18,
    s_PcData_801A5B34,
    s_PcData_801A5B64,
    s_PcData_801A5B94,
    s_PcData_801A5BC4,
    s_PcData_801A5BF4,
    s_PcData_801A5C24,
    s_PcData_801A5C54,
    s_PcData_801A5C84,
    s_PcData_801A5CB4,
    s_PcData_801A5CE4,
    s_PcData_801A5D14,
    s_PcData_801A5D44,
    s_PcData_801A5D74,
    s_PcData_801A5DA4,
    s_PcData_801A5DD4,
    s_PcData_801A5E04,
    s_PcData_801A5E34,
    s_PcData_801A5E64,
    s_PcData_801A5E94,
    s_PcData_801A5EC4,
    s_PcData_801A5EF4,
    s_PcData_801A5F24,
    s_PcData_801A5F54,
    s_PcData_801A5F84,
    s_PcData_801A5FB4,
    s_PcData_801A5FE4,
    s_PcData_801A6014,
    s_PcData_801A6044,
    s_PcData_801A6074,
    s_PcData_801A60A4,
    s_PcData_801A60D4,
    s_PcData_801A60F0,
    s_PcData_801A610C,
    s_PcData_801A6128,
    s_PcData_801A6144,
    s_PcData_801A6174,
    s_PcData_801A61A4,
    s_PcData_801A61D4,
    s_PcData_801A6204,
    s_PcData_801A6220,
    s_PcData_801A623C,
    s_PcData_801A6258,
    s_PcData_801A6274,
    s_PcData_801A6290,
    s_PcData_801A62AC,
    s_PcData_801A62C8,
    s_PcData_801A62E4,
    NULL,
};

s32 D_us_801CF3C8 = {0};

s32 D_us_801CF3CC = {0};

s32 D_us_801CF3D0 = {0};

s32 D_us_801CF3D8 = {0};

s32 D_us_801CF3E0 = {0};

s32 D_us_801CF3E4 = {0};

u8 D_us_801CF3E8[0x1400] = {0};

s16 D_us_801D07E8 = {0};

s16 D_us_801D07EC = {0};

s32 D_us_801D07F0 = {0};

s32 D_us_801D07F4 = {0};

s32 D_us_801D07F8 = {0};

u8 D_us_801D07FC = {0};

u8 D_us_801D0800 = {0};

u8 D_us_801D0804 = {0};

u8 D_us_801D0808 = {0};

Point16 D_us_801D080C[16] = {0};

s32 D_us_801D084C = {0};

s32 D_us_801D0850 = {0};

s32 D_us_801D0854[8] = {0};

s32 D_us_801D0874 = {0};

s32 D_us_801D0878 = {0};

s32 D_us_801D087C = {0};

Point16 D_us_801D08C4[4][128] = {0};

s32 D_us_801D10C4 = {0};

s16 D_us_801D10C8 = {0};

s32 D_us_801D10CC = {0};

Point16 D_us_801D10D0[6] = {0};

u16 D_us_801D10E8 = {0};

s32 D_us_801D10EC = {0};

s32 D_us_801D10F0[8] = {0};

s32 D_us_801D11C0 = {0};

s32 D_us_801D11C8[32] = {0};

s32 D_us_801D1248[32] = {0};

s32 D_us_801D169C = {0};

u32 D_us_801D16A4 = {0};

static char s_PcData_801A6314[] = {
    33, 76, 85, 67, 65, 82, 68, -1, 0, 0, 0, 0,
};

static char s_PcData_801A6308[] = {
    50, 73, 67, 72, 84, 69, 82, -1, 0, 0, 0, 0,
};

static char s_PcData_801A6300[] = {
    51, 72, 65, 70, 84, -1, 0, 0,
};

char* actor_names[] = {
    s_PcData_801A6314,
    s_PcData_801A6308,
    s_PcData_801A6300,
};

AnimationFrame anim_cross_boomerang[] = {
    {36, 1}, {1, 2}, {1, 3}, {1, 4}, {1, 5}, {1, 6}, {1, 7}, {1, 8}, {0, 0},
};

u32 g_CutsceneFlags = {0};

Dialogue g_Dialogue = {0};

s32 g_IsCutsceneDone = {0};

PlayerState g_Ric = {0};

s32 g_SkipCutscene = {0};

SubweaponDef subweapons_def[] = {
    {0, 30000, 0, 0, 0, 0, 0, 0, 2, 1, 15, 0, 0},
    {20, 1, 4160, 3, 2, 4, 0, 43, 2, 129, 21, 0, 32},
    {50, 1, 4160, 3, 20, 4, 0, 19, 2, 129, 20, 0, 32},
    {5, 1, 32, 1, 1, 4, 0, 6, 2, 1, 16, 0, 0},
    {40, 1, 4128, 4, 20, 4, 0, 2, 2, 129, 12, 0, 0},
    {5, 1, 4096, 2, 10, 4, 0, 61, 2, 1, 26, 0, 0},
    {0, 10, 0, 1, 0, 0, 0, 63, 0, 0, 27, 0, 0},
    {40, 1, 4128, 3, 8, 4, 0, 50, 2, 1, 25, 0, 0},
    {20, 1, 4096, 3, 4, 2, 0, 49, 2, 1, 24, 0, 0},
    {20, 10, 20480, 1, 10, 4, 0, 51, 2, 129, 28, 0, 0},
    {15, 30000, 4096, 1, 10, 4, 0, 0, 2, 1, 10, 0, 0},
    {8, 1, 36864, 2, 4, 2, 0, 9, 2, 1, 0, 0, 0},
    {40, 20, 4128, 1, 16, 16, 0, 13, 2, 1, 0, 0, 0},
    {60, 0, 4128, 1, 8, 8, 0, 0, 2, 1, 0, 0, 0},
    {32, 5, 4128, 1, 32, 8, 0, 0, 2, 1, 0, 0, 0},
    {64, 15, 36896, 1, 32, 8, 0, 0, 2, 1, 0, 0, 32},
    {80, 15, 4128, 1, 32, 16, 0, 12, 130, 1, 0, 0, 0},
    {80, 0, 32, 1, 16, 4, 0, 0, 2, 1, 0, 0, 32},
    {20, 0, 32, 1, 16, 4, 0, 0, 2, 1, 0, 0, 0},
    {5, 0, 4128, 1, 16, 8, 0, 0, 2, 1, 0, 0, 0},
    {40, 10, 4160, 1, 16, 4, 0, 41, 2, 129, 0, 0, 32},
    {20, 10, 4160, 1, 4, 4, 0, 44, 2, 129, 0, 0, 32},
    {80, 0, 32, 1, 16, 4, 0, 0, 2, 1, 0, 0, 32},
    {60, 0, 32, 1, 16, 4, 0, 0, 2, 1, 0, 0, 128},
    {20, 10, 4128, 1, 16, 4, 0, 54, 2, 1, 0, 0, 0},
    {20, 0, 32, 1, 4, 4, 0, 56, 2, 1, 0, 0, 0},
    {80, 15, 4128, 1, 16, 4, 0, 59, 2, 1, 0, 0, 0},
    {0, 30000, 32, 1, 4, 4, 0, 65, 2, 1, 0, 0, 0},
    {80, 20, 16416, 1, 16, 4, 0, 67, 2, 1, 0, 0, 0},
    {10, 30000, 32, 1, 4, 4, 0, 0, 2, 1, 0, 0, 0},
};
