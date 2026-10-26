// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../../boss/rbo5/rbo5.h"
#include <cutscene.h>

AnimationFrame D_us_80183B98[];
u8 D_us_80183CFC[][4];
static AnimationFrame s_PcData_801820B4[];
static AnimationFrame s_PcData_801820CC[];
static AnimationFrame s_PcData_801820D4[];
static AnimationFrame s_PcData_801820E8[];
static AnimationFrame s_PcData_801820F0[];
static AnimationFrame s_PcData_8018214C[];
static AnimationFrame s_PcData_80182180[];
static AnimationFrame s_PcData_801821A0[];
static AnimationFrame s_PcData_801821E4[];
static AnimationFrame s_PcData_80182204[];
static AnimationFrame s_PcData_80182230[];
static AnimationFrame s_PcData_80182238[];
static AnimationFrame s_PcData_8018228C[];
static AnimationFrame s_PcData_80182294[];
static AnimationFrame s_PcData_801822D8[];
static AnimationFrame s_PcData_80182320[];
static AnimationFrame s_PcData_80182364[];
static AnimationFrame s_PcData_801823A4[];
static AnimationFrame s_PcData_801823AC[];
static AnimationFrame s_PcData_801823B4[];
static AnimationFrame s_PcData_801823C4[];
static AnimationFrame s_PcData_801823CC[];
static AnimationFrame s_PcData_801823EC[];
static AnimationFrame s_PcData_801823F8[];
static AnimationFrame s_PcData_80182410[];
static AnimationFrame s_PcData_8018241C[];
static AnimationFrame s_PcData_80182428[];
static AnimationFrame s_PcData_80182434[];
static AnimationFrame s_PcData_80182448[];
static AnimationFrame s_PcData_80182460[];
static AnimationFrame s_PcData_8018249C[];
static AnimationFrame s_PcData_801824BC[];
static AnimationFrame s_PcData_801824C8[];
static AnimationFrame s_PcData_801824F0[];
static AnimationFrame s_PcData_801824FC[];
static AnimationFrame s_PcData_80182810[];
static AnimationFrame s_PcData_8018257C[];
static AnimationFrame s_PcData_801825A4[];
static AnimationFrame s_PcData_801825C8[];
static AnimationFrame s_PcData_801825E0[];
static AnimationFrame s_PcData_801825F8[];
static AnimationFrame s_PcData_80182504[];
static AnimationFrame s_PcData_8018256C[];
static AnimationFrame s_PcData_80182620[];
static AnimationFrame s_PcData_80182628[];
static AnimationFrame s_PcData_80182638[];
static AnimationFrame s_PcData_80182640[];
static AnimationFrame s_PcData_8018266C[];
static AnimationFrame s_PcData_80182698[];
static AnimationFrame s_PcData_801826C0[];
static AnimationFrame s_PcData_801826E8[];
static AnimationFrame s_PcData_801826F4[];
static AnimationFrame s_PcData_80182700[];
static AnimationFrame s_PcData_80182718[];
static AnimationFrame s_PcData_80182720[];
static AnimationFrame s_PcData_80182728[];
static AnimationFrame s_PcData_80182730[];
static AnimationFrame s_PcData_80182868[];
static AnimationFrame s_PcData_801828BC[];
static AnimationFrame s_PcData_80183A44[];
static AnimationFrame s_PcData_80182758[];
static AnimationFrame s_PcData_801827D8[];
static AnimationFrame s_PcData_801828C4[];
static AnimationFrame s_PcData_80182928[];
static AnimationFrame s_PcData_80182958[];
static AnimationFrame s_PcData_801829B4[];
static AnimationFrame s_PcData_801829D4[];
static AnimationFrame s_PcData_80182A04[];
static AnimationFrame s_PcData_80182A34[];
static AnimationFrame s_PcData_80182A4C[];
static AnimationFrame s_PcData_80182A90[];
static AnimationFrame s_PcData_80182A9C[];
static AnimationFrame s_PcData_80182AE0[];
static AnimationFrame s_PcData_80182B00[];
static AnimationFrame s_PcData_80182B1C[];
static AnimationFrame s_PcData_80182B38[];
static AnimationFrame s_PcData_80182B54[];
static AnimationFrame s_PcData_80182BA8[];
static AnimationFrame s_PcData_80182BB4[];
static AnimationFrame s_PcData_80182BE4[];
static AnimationFrame s_PcData_80182C14[];
static AnimationFrame s_PcData_80182C40[];
static AnimationFrame s_PcData_80182C6C[];
static AnimationFrame s_PcData_80182C98[];
static AnimationFrame s_PcData_80182CEC[];
static AnimationFrame s_PcData_80182CF8[];
static AnimationFrame s_PcData_80182D28[];
static AnimationFrame s_PcData_80182D58[];
static AnimationFrame s_PcData_80182D84[];
static AnimationFrame s_PcData_80182DB0[];
static AnimationFrame s_PcData_80182DDC[];
static AnimationFrame s_PcData_80182E1C[];
static AnimationFrame s_PcData_80182E8C[];
static AnimationFrame s_PcData_80182E40[];
static AnimationFrame s_PcData_80182E58[];
static AnimationFrame s_PcData_80182EBC[];
static AnimationFrame s_PcData_80182ED0[];
static AnimationFrame s_PcData_80182EE4[];
static AnimationFrame s_PcData_80182F0C[];
static AnimationFrame s_PcData_80182F34[];
static AnimationFrame s_PcData_80182F78[];
static AnimationFrame s_PcData_80182F84[];
static AnimationFrame s_PcData_80182FC0[];
static AnimationFrame s_PcData_80182FF8[];
static AnimationFrame s_PcData_80183030[];
static AnimationFrame s_PcData_80183068[];
static AnimationFrame s_PcData_801830F0[];
static AnimationFrame s_PcData_80183114[];
static AnimationFrame s_PcData_80183134[];
static AnimationFrame s_PcData_8018314C[];
static AnimationFrame s_PcData_8018315C[];
static AnimationFrame s_PcData_80183190[];
static AnimationFrame s_PcData_8018319C[];
static AnimationFrame s_PcData_801831C8[];
static AnimationFrame s_PcData_801831F4[];
static AnimationFrame s_PcData_80183210[];
static AnimationFrame s_PcData_8018322C[];
static AnimationFrame s_PcData_80183248[];
static AnimationFrame s_PcData_8018326C[];
static AnimationFrame s_PcData_8018328C[];
static AnimationFrame s_PcData_801832C0[];
static AnimationFrame s_PcData_801832CC[];
static AnimationFrame s_PcData_801832F8[];
static AnimationFrame s_PcData_80183324[];
static AnimationFrame s_PcData_80183340[];
static AnimationFrame s_PcData_8018335C[];
static AnimationFrame s_PcData_801833B4[];
static AnimationFrame s_PcData_801833C0[];
static AnimationFrame s_PcData_80183410[];
static AnimationFrame s_PcData_80183430[];
static AnimationFrame s_PcData_80183450[];
static AnimationFrame s_PcData_8018346C[];
static AnimationFrame s_PcData_801834AC[];
static AnimationFrame s_PcData_801834B8[];
static AnimationFrame s_PcData_801834F0[];
static AnimationFrame s_PcData_80183528[];
static AnimationFrame s_PcData_80183550[];
static AnimationFrame s_PcData_80183578[];
static AnimationFrame s_PcData_801835A0[];
static AnimationFrame s_PcData_801835D4[];
static AnimationFrame s_PcData_801835E0[];
static AnimationFrame s_PcData_8018360C[];
static AnimationFrame s_PcData_80183628[];
static AnimationFrame s_PcData_80183644[];
static AnimationFrame s_PcData_80183678[];
static AnimationFrame s_PcData_80183684[];
static AnimationFrame s_PcData_801836B0[];
static AnimationFrame s_PcData_801836CC[];
static AnimationFrame s_PcData_801836E8[];
static AnimationFrame s_PcData_8018371C[];
static AnimationFrame s_PcData_80183728[];
static AnimationFrame s_PcData_80183754[];
static AnimationFrame s_PcData_80183780[];
static AnimationFrame s_PcData_8018379C[];
static AnimationFrame s_PcData_801837B8[];
static AnimationFrame s_PcData_801837D4[];
static AnimationFrame s_PcData_80183820[];
static AnimationFrame s_PcData_8018382C[];
static AnimationFrame s_PcData_80183870[];
static AnimationFrame s_PcData_801838B4[];
static AnimationFrame s_PcData_801838E8[];
static AnimationFrame s_PcData_8018391C[];
static AnimationFrame s_PcData_80183950[];
static AnimationFrame s_PcData_8018397C[];
static AnimationFrame s_PcData_801839A8[];
static AnimationFrame s_PcData_801839CC[];
static AnimationFrame s_PcData_801839D4[];
static AnimationFrame s_PcData_80183A04[];
static AnimationFrame s_PcData_80183A14[];
static AnimationFrame s_PcData_80183A24[];
static AnimationFrame s_PcData_80182838[];
static AnimationFrame s_PcData_80182854[];
static AnimationFrame s_PcData_80183A4C[];
static AnimationFrame s_PcData_80183A78[];
static AnimationFrame s_PcData_80183AC4[];
static AnimationFrame s_PcData_80183AF0[];
static AnimationFrame s_PcData_80183B1C[];
static AnimationFrame s_PcData_80183B24[];
static AnimationFrame s_PcData_80183B4C[];
static AnimationFrame s_PcData_80183B68[];
static AnimationFrame s_PcData_80183BA0[];
static AnimationFrame s_PcData_80183BA8[];
static AnimationFrame s_PcData_80183BB0[];
static AnimationFrame s_PcData_80183BCC[];
static AnimationFrame s_PcData_80183BD8[];
static AnimationFrame s_PcData_80183C0C[];
static AnimationFrame s_PcData_80183C14[];
static AnimationFrame s_PcData_80183C34[];
static AnimationFrame s_PcData_80183C1C[];
static AnimationFrame s_PcData_801830D8[];
static AnimationFrame s_PcData_80183C4C[];
static AnimationFrame s_PcData_80183C94[];
static AnimationFrame s_PcData_80183CEC[];
static AnimationFrame s_PcData_80182348[];
AnimationFrame* D_us_80183D40[];
static u16 s_PcData_80184124[];
static u16 s_PcData_80184140[];
static u16 s_PcData_8018415C[];
static u16 s_PcData_80184178[];
static u16 s_PcData_80184190[];
static u16 s_PcData_801841A8[];
static u16* s_PcData_801842CC[];
static s8 s_PcData_801841C0[];
static u16 s_PcData_80184224[];
static u16 s_PcData_80184238[];
static u16 s_PcData_8018424C[];
static u16 s_PcData_80184260[];
static u16 s_PcData_80184270[];
static u16 s_PcData_80184280[];
static u16* s_PcData_801842E8[];
static s8 s_PcData_80184290[];
DopWeaponAnimation D_us_80184304[];
static s16 s_PcData_801B0F74[];
static s16 s_PcData_801B0F7C[];
static s16 s_PcData_801B0F84[];
static s16 s_PcData_801B0F8C[];
static s16 s_PcData_801B0F94[];
static s16 s_PcData_801B0F9C[];
static s16 s_PcData_801B0FA4[];
static s16 s_PcData_801B0FAC[];
static s16 s_PcData_801B0FB4[];
static s16 s_PcData_801B0FBC[];
static s16 s_PcData_801B0FC4[];
static s16 s_PcData_801B0FCC[];
static s16 s_PcData_801B0FD4[];
static s16 s_PcData_801B0FDC[];
static s16 s_PcData_801B0FE4[];
static s16 s_PcData_801B0FEC[];
static s16 s_PcData_801B0FF4[];
static s16 s_PcData_801B0FFC[];
static s16 s_PcData_801B1004[];
static s16 s_PcData_801B100C[];
static s16 s_PcData_801B1014[];
static s16 s_PcData_801B101C[];
static s16 s_PcData_801B1024[];
static s16 s_PcData_801B102C[];
static s16 s_PcData_801B1034[];
static s16 s_PcData_801B103C[];
static s16 s_PcData_801B1044[];
static s16 s_PcData_801B104C[];
static s16 s_PcData_801B1054[];
static s16 s_PcData_801B105C[];
static s16 s_PcData_801B1064[];
static s16 s_PcData_801B106C[];
static s16 s_PcData_801B1074[];
static s16 s_PcData_801B107C[];
static s16 s_PcData_801B1084[];
static s16 s_PcData_801B108C[];
static s16 s_PcData_801B1094[];
static s16 s_PcData_801B109C[];
static s16 s_PcData_801B10A4[];
static s16 s_PcData_801B10AC[];
static s16 s_PcData_801B10B4[];
static s16 s_PcData_801B10BC[];
static s16 s_PcData_801B10C4[];
static s16 s_PcData_801B10CC[];
static s16 s_PcData_801B10D4[];
static s16 s_PcData_801B10DC[];
static s16 s_PcData_801B10E4[];
static s16 s_PcData_801B10EC[];
static s16 s_PcData_801B10F4[];
static s16 s_PcData_801B10FC[];
static s16 s_PcData_801B1104[];
static s16 s_PcData_801B110C[];
static s16 s_PcData_801B1114[];
static s16 s_PcData_801B111C[];
static s16 s_PcData_801B1124[];
static s16 s_PcData_801B112C[];
static s16 s_PcData_801B1134[];
static s16 s_PcData_801B113C[];
static s16 s_PcData_801B1144[];
static s16 s_PcData_801B114C[];
static s16 s_PcData_801B1154[];
static s16 s_PcData_801B115C[];
static s16 s_PcData_801B1164[];
static s16 s_PcData_801B116C[];
static s16 s_PcData_801B1174[];
static s16 s_PcData_801B117C[];
static s16 s_PcData_801B1184[];
static s16 s_PcData_801B118C[];
static s16 s_PcData_801B1194[];
static s16 s_PcData_801B119C[];
static s16 s_PcData_801B11A4[];
static s16 s_PcData_801B11AC[];
static s16 s_PcData_801B11B4[];
static s16 s_PcData_801B11BC[];
static s16 s_PcData_801B11C4[];
static s16 s_PcData_801B11CC[];
static s16 s_PcData_801B11D4[];
static s16 s_PcData_801B11DC[];
static s16 s_PcData_801B11E4[];
static s16 s_PcData_801B11EC[];
static s16 s_PcData_801B11F4[];
static s16 s_PcData_801B11FC[];
static s16 s_PcData_801B1204[];
static s16 s_PcData_801B120C[];
static s16 s_PcData_801B1214[];
static s16 s_PcData_801B121C[];
static s16 s_PcData_801B1224[];
static s16 s_PcData_801B122C[];
static s16 s_PcData_801B1234[];
static s16 s_PcData_801B123C[];
static s16 s_PcData_801B1244[];
static s16 s_PcData_801B124C[];
static s16 s_PcData_801B1254[];
static s16 s_PcData_801B125C[];
static s16 s_PcData_801B1264[];
static s16 s_PcData_801B126C[];
static s16 s_PcData_801B1274[];
static s16 s_PcData_801B127C[];
static s16 s_PcData_801B1284[];
static s16 s_PcData_801B128C[];
static s16 s_PcData_801B1294[];
static s16 s_PcData_801B129C[];
static s16 s_PcData_801B12A4[];
static s16 s_PcData_801B12AC[];
static s16 s_PcData_801B12B4[];
static s16 s_PcData_801B12BC[];
static s16 s_PcData_801B12C4[];
static s16 s_PcData_801B12CC[];
static s16 s_PcData_801B12D4[];
static s16 s_PcData_801B12DC[];
static s16 s_PcData_801B12E4[];
static s16 s_PcData_801B12EC[];
static s16 s_PcData_801B12F4[];
static s16 s_PcData_801B12FC[];
static s16 s_PcData_801B1304[];
static s16 s_PcData_801B130C[];
static s16 s_PcData_801B1314[];
static s16 s_PcData_801B131C[];
static s16 s_PcData_801B1324[];
static s16 s_PcData_801B132C[];
static s16 s_PcData_801B1334[];
static s16 s_PcData_801B133C[];
static s16 s_PcData_801B1344[];
static s16 s_PcData_801B134C[];
static s16 s_PcData_801B1354[];
static s16 s_PcData_801B135C[];
static s16 s_PcData_801B1364[];
static s16 s_PcData_801B136C[];
static s16 s_PcData_801B1374[];
static s16 s_PcData_801B137C[];
static s16 s_PcData_801B1384[];
static s16 s_PcData_801B138C[];
static s16 s_PcData_801B1394[];
static s16 s_PcData_801B139C[];
static s16 s_PcData_801B13A4[];
static s16 s_PcData_801B13AC[];
static s16 s_PcData_801B13B4[];
static s16 s_PcData_801B13BC[];
static s16 s_PcData_801B13C4[];
static s16 s_PcData_801B13CC[];
static s16 s_PcData_801B13D4[];
static s16 s_PcData_801B13DC[];
static s16 s_PcData_801B13E4[];
static s16 s_PcData_801B13EC[];
static s16 s_PcData_801B13F4[];
static s16 s_PcData_801B13FC[];
static s16 s_PcData_801B1404[];
static s16 s_PcData_801B140C[];
static s16 s_PcData_801B1414[];
static s16 s_PcData_801B141C[];
static s16 s_PcData_801B1424[];
static s16 s_PcData_801B142C[];
static s16 s_PcData_801B1434[];
static s16 s_PcData_801B143C[];
static s16 s_PcData_801B1444[];
static s16 s_PcData_801B144C[];
static s16 s_PcData_801B1454[];
static s16 s_PcData_801B145C[];
static s16 s_PcData_801B1464[];
static s16 s_PcData_801B146C[];
static s16 s_PcData_801B1474[];
static s16 s_PcData_801B147C[];
static s16 s_PcData_801B1484[];
static s16 s_PcData_801B148C[];
static s16 s_PcData_801B1494[];
static s16 s_PcData_801B149C[];
static s16 s_PcData_801B14A4[];
static s16 s_PcData_801B14AC[];
static s16 s_PcData_801B14B4[];
static s16 s_PcData_801B14BC[];
static s16 s_PcData_801B14C4[];
static s16 s_PcData_801B14CC[];
static s16 s_PcData_801B14D4[];
static s16 s_PcData_801B14DC[];
static s16 s_PcData_801B14E4[];
static s16 s_PcData_801B14EC[];
static s16 s_PcData_801B14F4[];
static s16 s_PcData_801B14FC[];
static s16 s_PcData_801B1504[];
static s16 s_PcData_801B150C[];
static s16 s_PcData_801B1514[];
static s16 s_PcData_801B151C[];
static s16 s_PcData_801B1524[];
static s16 s_PcData_801B152C[];
static s16 s_PcData_801B1534[];
static s16 s_PcData_801B153C[];
static s16 s_PcData_801B1544[];
static s16 s_PcData_801B154C[];
static s16 s_PcData_801B1554[];
static s16 s_PcData_801B155C[];
static s16 s_PcData_801B1564[];
static s16 s_PcData_801B156C[];
static s16 s_PcData_801B1574[];
static s16 s_PcData_801B157C[];
static s16 s_PcData_801B1584[];
static s16 s_PcData_801B158C[];
static s16 s_PcData_801B1594[];
static s16 s_PcData_801B159C[];
static s16 s_PcData_801B15A4[];
static s16 s_PcData_801B15AC[];
static s16 s_PcData_801B15B4[];
static s16 s_PcData_801B15BC[];
static s16 s_PcData_801B15C4[];
static s16 s_PcData_801B15CC[];
static s16 s_PcData_801B15D4[];
static s16 s_PcData_801B15DC[];
static s16 s_PcData_801B15E4[];
static s16 s_PcData_801B15EC[];
static s16 s_PcData_801B15F4[];
static s16 s_PcData_801B15FC[];
static s16 s_PcData_801B1604[];
static s16 s_PcData_801B160C[];
static s16 s_PcData_801B1614[];
static s16 s_PcData_801B161C[];
static s16 s_PcData_801B1624[];
static s16 s_PcData_801B162C[];
static s16 s_PcData_801B1634[];
static s16 s_PcData_801B163C[];
static s16 s_PcData_801B1644[];
static s16 s_PcData_801B164C[];
static s16 s_PcData_801B1654[];
static s16 s_PcData_801B165C[];
static s16 s_PcData_801B1664[];
static s16 s_PcData_801B166C[];
s16* D_us_801B0B50[];
static s16 s_PcData_801B16BC[];
static s16 s_PcData_801B16C4[];
static s16 s_PcData_801B16CC[];
static s16 s_PcData_801B16D4[];
static s16 s_PcData_801B16DC[];
static s16 s_PcData_801B16E4[];
static s16 s_PcData_801B16EC[];
static s16 s_PcData_801B16F4[];
static s16 s_PcData_801B16FC[];
static s16 s_PcData_801B1704[];
static s16 s_PcData_801B170C[];
static s16 s_PcData_801B1714[];
static s16 s_PcData_801B171C[];
static s16 s_PcData_801B1724[];
static s16 s_PcData_801B172C[];
static s16 s_PcData_801B1734[];
s16* D_us_801B1674[];
static s16 s_PcData_801B1880[];
static s16 s_PcData_801B189C[];
static s16 s_PcData_801B18B8[];
static s16 s_PcData_801B18D4[];
static s16 s_PcData_801B18F0[];
static s16 s_PcData_801B190C[];
static s16 s_PcData_801B1928[];
static s16 s_PcData_801B1944[];
static s16 s_PcData_801B1960[];
static s16 s_PcData_801B197C[];
static s16 s_PcData_801B1998[];
static s16 s_PcData_801B19B4[];
static s16 s_PcData_801B19D0[];
static s16 s_PcData_801B19EC[];
static s16 s_PcData_801B1A08[];
static s16 s_PcData_801B1A24[];
static s16 s_PcData_801B1A40[];
static s16 s_PcData_801B1A5C[];
static s16 s_PcData_801B1A78[];
static s16 s_PcData_801B1A94[];
static s16 s_PcData_801B1AB0[];
static s16 s_PcData_801B1ACC[];
static s16 s_PcData_801B1AE8[];
static s16 s_PcData_801B1B04[];
static s16 s_PcData_801B1B20[];
static s16 s_PcData_801B1B3C[];
static s16 s_PcData_801B1B58[];
static s16 s_PcData_801B1B74[];
static s16 s_PcData_801B1B90[];
static s16 s_PcData_801B1BAC[];
static s16 s_PcData_801B1BC8[];
static s16 s_PcData_801B1BE4[];
static s16 s_PcData_801B1C00[];
static s16 s_PcData_801B1C1C[];
static s16 s_PcData_801B1C38[];
static s16 s_PcData_801B1C54[];
static s16 s_PcData_801B1C70[];
static s16 s_PcData_801B1C8C[];
static s16 s_PcData_801B1CA8[];
static s16 s_PcData_801B1CC4[];
static s16 s_PcData_801B1CE0[];
static s16 s_PcData_801B1CFC[];
static s16 s_PcData_801B1D18[];
static s16 s_PcData_801B1D34[];
static s16 s_PcData_801B1D50[];
static s16 s_PcData_801B1D6C[];
static s16 s_PcData_801B1D88[];
static s16 s_PcData_801B1DA4[];
static s16 s_PcData_801B1DC0[];
static s16 s_PcData_801B1DDC[];
static s16 s_PcData_801B1DF8[];
static s16 s_PcData_801B1E14[];
static s16 s_PcData_801B1E30[];
static s16 s_PcData_801B1E4C[];
static s16 s_PcData_801B1E68[];
static s16 s_PcData_801B1E84[];
static s16 s_PcData_801B1EA0[];
static s16 s_PcData_801B1EBC[];
static s16 s_PcData_801B1ED8[];
static s16 s_PcData_801B1EF4[];
static s16 s_PcData_801B1F10[];
static s16 s_PcData_801B1F2C[];
static s16 s_PcData_801B1F48[];
static s16 s_PcData_801B1F64[];
static s16 s_PcData_801B1F80[];
static s16 s_PcData_801B1F9C[];
static s16 s_PcData_801B1FB8[];
static s16 s_PcData_801B1FD4[];
static s16 s_PcData_801B1FF0[];
static s16 s_PcData_801B200C[];
static s16 s_PcData_801B2028[];
static s16 s_PcData_801B2044[];
static s16 s_PcData_801B2060[];
static s16 s_PcData_801B207C[];
static s16 s_PcData_801B2098[];
static s16 s_PcData_801B20B4[];
static s16 s_PcData_801B20D0[];
static s16 s_PcData_801B20EC[];
static s16 s_PcData_801B2108[];
static s16 s_PcData_801B2124[];
s16* D_us_801B173C[];
static s16 s_PcData_801B21DC[];
static s16 s_PcData_801B21F8[];
static s16 s_PcData_801B2214[];
static s16 s_PcData_801B2230[];
static s16 s_PcData_801B224C[];
static s16 s_PcData_801B2268[];
static s16 s_PcData_801B2284[];
static s16 s_PcData_801B22A0[];
static s16 s_PcData_801B22BC[];
static s16 s_PcData_801B22D8[];
static s16 s_PcData_801B22F4[];
static s16 s_PcData_801B2310[];
static s16 s_PcData_801B232C[];
static s16 s_PcData_801B2348[];
static s16 s_PcData_801B2364[];
static s16 s_PcData_801B2380[];
static s16 s_PcData_801B239C[];
static s16 s_PcData_801B23B8[];
static s16 s_PcData_801B23D4[];
static s16 s_PcData_801B23F0[];
static s16 s_PcData_801B240C[];
static s16 s_PcData_801B2428[];
static s16 s_PcData_801B2444[];
static s16 s_PcData_801B2460[];
static s16 s_PcData_801B247C[];
static s16 s_PcData_801B2498[];
static s16 s_PcData_801B24B4[];
static s16 s_PcData_801B24D0[];
static s16 s_PcData_801B24EC[];
static s16 s_PcData_801B2508[];
static s16 s_PcData_801B2524[];
static s16 s_PcData_801B2540[];
static s16 s_PcData_801B255C[];
static s16 s_PcData_801B2578[];
static s16 s_PcData_801B2594[];
static s16 s_PcData_801B25B0[];
static s16 s_PcData_801B25CC[];
static s16 s_PcData_801B25E8[];
s16* D_us_801B2140[];
static s16 s_PcData_801B26BC[];
static s16 s_PcData_801B26D8[];
static s16 s_PcData_801B26F4[];
static s16 s_PcData_801B2710[];
static s16 s_PcData_801B2740[];
static s16 s_PcData_801B275C[];
static s16 s_PcData_801B2778[];
static s16 s_PcData_801B2794[];
static s16 s_PcData_801B27B0[];
static s16 s_PcData_801B27CC[];
static s16 s_PcData_801B27E8[];
static s16 s_PcData_801B2804[];
static s16 s_PcData_801B2820[];
static s16 s_PcData_801B283C[];
static s16 s_PcData_801B2858[];
static s16 s_PcData_801B2874[];
static s16 s_PcData_801B2890[];
static s16 s_PcData_801B28AC[];
static s16 s_PcData_801B28C8[];
static s16 s_PcData_801B28E4[];
static s16 s_PcData_801B2900[];
static s16 s_PcData_801B291C[];
static s16 s_PcData_801B2938[];
static s16 s_PcData_801B2954[];
static s16 s_PcData_801B2970[];
static s16 s_PcData_801B298C[];
static s16 s_PcData_801B29A8[];
static s16 s_PcData_801B29C4[];
static s16 s_PcData_801B29E0[];
static s16 s_PcData_801B29FC[];
static s16 s_PcData_801B2A18[];
static s16 s_PcData_801B2A34[];
static s16 s_PcData_801B2A50[];
static s16 s_PcData_801B2A6C[];
static s16 s_PcData_801B2A88[];
static s16 s_PcData_801B2AB8[];
static s16 s_PcData_801B2B00[];
static s16 s_PcData_801B2B1C[];
static s16 s_PcData_801B2B38[];
static s16 s_PcData_801B2B54[];
s16* D_us_801B2604[];
static AnimationFrame s_PcData_80182240[];
static AnimationFrame s_PcData_8018226C[];
static AnimationFrame s_PcData_80182300[];
static AnimationFrame s_PcData_80182384[];
static AnimationFrame s_PcData_80182484[];
static AnimationFrame s_PcData_801828F0[];
static AnimationFrame s_PcData_80182990[];
static AnimationFrame s_PcData_80182A1C[];
static AnimationFrame s_PcData_80182A58[];
static AnimationFrame s_PcData_80182ABC[];
static AnimationFrame s_PcData_801829EC[];
static AnimationFrame s_PcData_80182B60[];
static AnimationFrame s_PcData_80182CA4[];
static AnimationFrame s_PcData_801828D0[];
static AnimationFrame s_PcData_80182934[];
static AnimationFrame s_PcData_80182978[];
static AnimationFrame s_PcData_80182114[];
static AnimationFrame s_PcData_80182130[];
static AnimationFrame s_PcData_80182F40[];
static AnimationFrame s_PcData_80183168[];
static AnimationFrame s_PcData_80183298[];
static AnimationFrame s_PcData_80183368[];
static AnimationFrame s_PcData_80183478[];
static AnimationFrame s_PcData_801835AC[];
static AnimationFrame s_PcData_80183650[];
static AnimationFrame s_PcData_801836F4[];
static AnimationFrame s_PcData_801837E0[];
static AnimationFrame s_PcData_80182784[];
static AnimationFrame s_PcData_8018309C[];
AnimationFrame* g_DopAnimationFrames[];
u8* g_PlOvlDopBatSpritesheet[];
u8* g_SpriteSheet[];

AnimationFrame D_us_80183B98[] = {
    {128, 0},   {65535, 0}, {132, 95},  {65535, 0}, {132, 199}, {65535, 0},
    {3, 513},   {2, 514},   {2, 515},   {3, 516},   {2, 515},   {2, 514},
    {0, 0},     {1, 517},   {16, 518},  {65535, 0}, {128, 515}, {1, 514},
    {16, 514},  {16, 515},  {1, 514},   {16, 514},  {16, 515},  {1, 514},
    {16, 514},  {16, 515},  {1, 514},   {128, 514}, {0, 0},     {128, 514},
    {65535, 0}, {128, 520}, {65535, 0}, {1, 1548},  {1, 1547},  {1, 1546},
    {24, 1666}, {1, 1551},  {65535, 0}, {1, 528},   {1, 529},   {1, 530},
    {20, 637},  {4, 634},   {65534, 4}, {2, 26},    {2, 27},    {2, 28},
    {2, 29},    {2, 30},    {2, 31},    {2, 208},   {4, 209},   {5, 210},
    {16, 211},  {2, 106},   {2, 107},   {2, 108},   {2, 109},   {3, 110},
    {1, 110},   {128, 1},   {65535, 0}, {2, 26},    {2, 27},    {2, 28},
    {2, 29},    {2, 30},    {2, 31},    {2, 208},   {4, 209},   {5, 210},
    {4, 211},   {2, 208},   {4, 209},   {5, 210},   {4, 211},   {2, 106},
    {2, 107},   {2, 108},   {2, 109},   {3, 110},   {1, 110},   {128, 1},
    {65535, 0}, {65533, 2}, {4, 632},   {64, 633},  {65535, 0},
};

u8 D_us_80183CFC[][4] = {
    0, 0,  0,   0, 0,   1,  4,   20,  0,  7, 4,   16,  0,   13, 4,   9,   2,
    3, 5,  13,  5, 255, 8,  9,   254, 4,  6, 16,  0,   253, 4,  16,  5,   251,
    6, 12, 5,   1, 4,   20, 1,   249, 11, 9, 254, 251, 25,  26, 224, 225, 0,
    0, 1,  253, 7, 7,   1,  253, 7,   7,  0, 1,   4,   7,   1,  253, 7,   7,
};

static AnimationFrame s_PcData_801820B4[] = {
    {4, 634}, {80, 635}, {65535, 0}, {8, 635}, {24, 4732}, {0, 1},
};

static AnimationFrame s_PcData_801820CC[] = {
    {80, 633},
    {65535, 0},
};

static AnimationFrame s_PcData_801820D4[] = {
    {255, 513}, {255, 513}, {255, 513}, {255, 513}, {65534, 6},
};

static AnimationFrame s_PcData_801820E8[] = {
    {255, 591},
    {0, 0},
};

static AnimationFrame s_PcData_801820F0[] = {
    {65533, 16}, {65533, 17}, {6, 531}, {6, 532},   {6, 533},
    {6, 534},    {6, 535},    {6, 536}, {65534, 2},
};

static AnimationFrame s_PcData_8018214C[] = {
    {6, 1110}, {6, 599}, {6, 600}, {6, 601}, {6, 602},   {5, 603},   {3, 604},
    {3, 603},  {2, 604}, {2, 605}, {2, 604}, {128, 605}, {65534, 6},
};

static AnimationFrame s_PcData_80182180[] = {
    {192, 605}, {7, 604}, {3, 603},   {4, 604},
    {11, 605},  {8, 606}, {160, 591}, {65534, 3},
};

static AnimationFrame s_PcData_801821A0[] = {
    {3, 537},  {3, 538},  {3, 539},  {3, 540},  {3, 2077},  {3, 2078},
    {3, 2591}, {3, 2592}, {3, 2593}, {3, 2594}, {3, 2595},  {3, 2596},
    {3, 2085}, {3, 2086}, {3, 2087}, {3, 2088}, {65534, 8},
};

static AnimationFrame s_PcData_801821E4[] = {
    {3, 556}, {3, 557}, {3, 558},   {3, 559},
    {3, 560}, {3, 561}, {65533, 1}, {65534, 13},
};

static AnimationFrame s_PcData_80182204[] = {
    {2, 569},  {3, 570},  {3, 571},  {4, 572},  {4, 573},    {5, 2110},
    {7, 2111}, {5, 2624}, {3, 2625}, {3, 2114}, {65534, 12},
};

static AnimationFrame s_PcData_80182230[] = {
    {65533, 0},
    {65534, 4},
};

static AnimationFrame s_PcData_80182238[] = {
    {65533, 0},
    {65534, 5},
};

static AnimationFrame s_PcData_8018228C[] = {
    {65533, 1},
    {65534, 13},
};

static AnimationFrame s_PcData_80182294[] = {
    {3, 553}, {2, 554}, {3, 555}, {2, 556}, {3, 557}, {2, 558},
    {3, 559}, {2, 560}, {3, 561}, {2, 562}, {3, 563}, {2, 564},
    {3, 565}, {2, 566}, {3, 567}, {2, 568}, {0, 0},
};

static AnimationFrame s_PcData_801822D8[] = {
    {65533, 2}, {4, 592}, {4, 593}, {4, 594}, {4, 595},
    {4, 596},   {4, 597}, {4, 596}, {4, 597}, {65534, 4},
};

static AnimationFrame s_PcData_80182320[] = {
    {65533, 2}, {4, 586}, {4, 587}, {4, 588}, {4, 589},
    {4, 590},   {4, 591}, {4, 590}, {4, 591}, {65534, 3},
};

static AnimationFrame s_PcData_80182364[] = {
    {2, 1026}, {4, 1539}, {4, 1540},  {4, 1541},
    {4, 1542}, {4, 1543}, {65533, 3}, {65535, 0},
};

static AnimationFrame s_PcData_801823A4[] = {
    {255, 1551},
    {0, 0},
};

static AnimationFrame s_PcData_801823AC[] = {
    {16, 1551},
    {65535, 0},
};

static AnimationFrame s_PcData_801823B4[] = {
    {3, 1552},
    {3, 1041},
    {3, 530},
    {65535, 0},
};

static AnimationFrame s_PcData_801823C4[] = {
    {65533, 3},
    {65534, 17},
};

static AnimationFrame s_PcData_801823CC[] = {
    {1, 1026}, {1, 1540}, {1, 1542}, {1, 1544},
    {1, 1546}, {1, 1548}, {1, 1550}, {65535, 0},
};

static AnimationFrame s_PcData_801823EC[] = {
    {5, 607},
    {5, 608},
    {65534, 23},
};

static AnimationFrame s_PcData_801823F8[] = {
    {5, 609}, {5, 610}, {5, 615}, {5, 616}, {64, 617}, {65535, 0},
};

static AnimationFrame s_PcData_80182410[] = {
    {5, 3683},
    {5, 4196},
    {65534, 26},
};

static AnimationFrame s_PcData_8018241C[] = {
    {5, 4196},
    {5, 3683},
    {65534, 23},
};

static AnimationFrame s_PcData_80182428[] = {
    {3, 4197},
    {3, 4198},
    {0, 0},
};

static AnimationFrame s_PcData_80182434[] = {
    {3, 3690}, {4, 3691}, {4, 3692}, {4, 3693}, {65534, 28},
};

static AnimationFrame s_PcData_80182448[] = {
    {8, 3694}, {5, 3695}, {5, 3696}, {5, 3697}, {65, 3698}, {65535, 0},
};

static AnimationFrame s_PcData_80182460[] = {
    {65533, 4}, {4, 593}, {4, 594}, {4, 595},   {4, 596},
    {4, 597},   {4, 596}, {4, 597}, {65534, 4},
};

static AnimationFrame s_PcData_8018249C[] = {
    {65533, 4}, {4, 588}, {4, 589}, {4, 590},
    {4, 591},   {4, 590}, {4, 591}, {65534, 3},
};

static AnimationFrame s_PcData_801824BC[] = {
    {3, 3697},
    {66, 3698},
    {65535, 0},
};

static AnimationFrame s_PcData_801824C8[] = {
    {2, 4249}, {2, 4248}, {4, 4249}, {3, 4250}, {3, 4251},
    {3, 4197}, {3, 4198}, {3, 4197}, {3, 4198}, {65535, 0},
};

static AnimationFrame s_PcData_801824F0[] = {
    {5, 607},
    {5, 608},
    {65534, 23},
};

static AnimationFrame s_PcData_801824FC[] = {
    {255, 3699},
    {0, 0},
};

static AnimationFrame s_PcData_80182810[] = {
    {2, 1735}, {2, 1736}, {2, 1737}, {2, 1738}, {16, 1739},
    {2, 1740}, {2, 1741}, {1, 1742}, {1, 1743}, {65535, 0},
};

static AnimationFrame s_PcData_8018257C[] = {
    {2, 4732}, {2, 4733}, {2, 4734}, {2, 4735}, {3, 4734},
    {2, 4732}, {3, 4733}, {4, 4732}, {6, 4736}, {65535, 0},
};

static AnimationFrame s_PcData_801825A4[] = {
    {2, 1665}, {2, 1666}, {2, 1667}, {2, 1668},  {3, 1667},
    {2, 1665}, {3, 1666}, {4, 1665}, {65535, 0},
};

static AnimationFrame s_PcData_801825C8[] = {
    {2, 4229}, {2, 4230}, {2, 4231}, {3, 4230}, {3, 4229}, {65535, 0},
};

static AnimationFrame s_PcData_801825E0[] = {
    {2, 3720}, {2, 3721}, {2, 3722}, {3, 3721}, {3, 3720}, {65535, 0},
};

static AnimationFrame s_PcData_801825F8[] = {
    {3, 3694}, {11, 5259}, {5, 3724}, {5, 3725},   {7, 3694},
    {3, 3695}, {3, 3696},  {3, 3697}, {255, 3698}, {65535, 0},
};

static AnimationFrame s_PcData_80182504[] = {
    {3, 3700},   {3, 3587},  {3, 1540}, {3, 1541}, {3, 1542}, {3, 1543},
    {3, 1544},   {3, 1545},  {3, 1546}, {3, 1547}, {4, 1548}, {4, 1549},
    {5, 1550},   {7, 1548},  {5, 1547}, {4, 1546}, {4, 1545}, {4, 1544},
    {4, 1543},   {4, 1542},  {4, 1541}, {4, 1540}, {4, 1539}, {255, 1652},
    {255, 1652}, {65535, 0},
};

static AnimationFrame s_PcData_8018256C[] = {
    {5, 1692},
    {6, 669},
    {6, 2718},
    {65535, 0},
};

static AnimationFrame s_PcData_80182620[] = {
    {48, 3743},
    {65535, 0},
};

static AnimationFrame s_PcData_80182628[] = {
    {16, 3743},
    {7, 673},
    {28, 674},
    {65535, 0},
};

static AnimationFrame s_PcData_80182638[] = {
    {48, 675},
    {65535, 0},
};

static AnimationFrame s_PcData_80182640[] = {
    {9, 3237},  {2, 3238}, {2, 3237}, {3, 3238}, {3, 3237},  {3, 3238},
    {17, 3237}, {3, 3231}, {4, 3089}, {4, 3090}, {65535, 0},
};

static AnimationFrame s_PcData_8018266C[] = {
    {9, 2215},  {2, 2216}, {2, 2215}, {3, 2216}, {3, 2215},  {3, 2216},
    {17, 2215}, {3, 3231}, {4, 3089}, {4, 3090}, {65535, 0},
};

static AnimationFrame s_PcData_80182698[] = {
    {9, 2217}, {2, 2218},  {2, 2217}, {3, 2218}, {3, 2217},
    {3, 2218}, {17, 2217}, {3, 3089}, {3, 3090}, {65535, 0},
};

static AnimationFrame s_PcData_801826C0[] = {
    {9, 2219}, {2, 2220},  {2, 2219}, {3, 2220}, {3, 2219},
    {3, 2220}, {17, 2219}, {3, 3089}, {3, 3090}, {65535, 0},
};

static AnimationFrame s_PcData_801826E8[] = {
    {2, 3743},
    {2, 3744},
    {0, 0},
};

static AnimationFrame s_PcData_801826F4[] = {
    {2, 675},
    {2, 676},
    {0, 0},
};

static AnimationFrame s_PcData_80182700[] = {
    {5, 3743}, {5, 674}, {5, 675}, {5, 3237}, {5, 2217}, {0, 0},
};

static AnimationFrame s_PcData_80182718[] = {
    {15, 3757},
    {65535, 0},
};

static AnimationFrame s_PcData_80182720[] = {
    {15, 3758},
    {65535, 0},
};

static AnimationFrame s_PcData_80182728[] = {
    {15, 3759},
    {65535, 0},
};

static AnimationFrame s_PcData_80182730[] = {
    {5, 3237}, {2, 3238},  {2, 3237}, {3, 3238}, {3, 3237},
    {3, 3238}, {17, 3237}, {3, 3089}, {3, 3090}, {65535, 0},
};

static AnimationFrame s_PcData_80182868[] = {
    {24, 654}, {4, 655}, {4, 656}, {4, 657}, {6, 658}, {7, 659}, {4, 660},
    {25, 661}, {4, 662}, {4, 663}, {4, 688}, {2, 663}, {2, 662}, {65, 661},
    {9, 659},  {4, 658}, {3, 657}, {4, 656}, {4, 655}, {4, 654}, {65535, 0},
};

static AnimationFrame s_PcData_801828BC[] = {
    {4, 654},
    {65535, 0},
};

static AnimationFrame s_PcData_80183A44[] = {
    {40, 0},
    {65535, 0},
};

static AnimationFrame s_PcData_80182758[] = {
    {9, 3743}, {4, 673},  {4, 674},  {4, 2217},  {4, 2218},  {17, 3761},
    {8, 3762}, {8, 3763}, {5, 3697}, {66, 3698}, {65535, 0},
};

static AnimationFrame s_PcData_801827D8[] = {
    {2, 3765},   {2, 3766},  {2, 3767},  {2, 3768},  {2, 3764},
    {65533, 27}, {7, 3765},  {7, 3766},  {7, 3767},  {8, 3768},
    {9, 3764},   {10, 3765}, {64, 3743}, {65535, 0},
};

static AnimationFrame s_PcData_801828C4[] = {
    {65533, 5},
    {65533, 13},
    {65535, 0},
};

static AnimationFrame s_PcData_80182928[] = {
    {65533, 5},
    {65533, 14},
    {65535, 0},
};

static AnimationFrame s_PcData_80182958[] = {
    {2, 1732}, {1, 1733},  {1, 1733},   {1, 1733},
    {1, 1733}, {65533, 6}, {65533, 15}, {65535, 0},
};

static AnimationFrame s_PcData_801829B4[] = {
    {2, 1732}, {1, 1734},  {1, 1734},   {1, 1734},
    {1, 1734}, {65533, 6}, {65533, 15}, {65535, 0},
};

static AnimationFrame s_PcData_801829D4[] = {
    {2, 3792}, {1, 3793}, {1, 3793}, {2, 3793}, {65533, 10}, {65535, 0},
};

static AnimationFrame s_PcData_80182A04[] = {
    {2, 3796}, {1, 3797}, {1, 3797}, {2, 3797}, {65533, 7}, {65535, 0},
};

static AnimationFrame s_PcData_80182A34[] = {
    {2, 3796}, {1, 3798}, {1, 3798}, {2, 3798}, {65533, 7}, {65535, 0},
};

static AnimationFrame s_PcData_80182A4C[] = {
    {65533, 8},
    {65533, 13},
    {65535, 0},
};

static AnimationFrame s_PcData_80182A90[] = {
    {65533, 8},
    {65533, 14},
    {65535, 0},
};

static AnimationFrame s_PcData_80182A9C[] = {
    {1, 1732}, {1, 1732},  {1, 1733},   {2, 1733},
    {8, 1733}, {65533, 9}, {65533, 15}, {65535, 0},
};

static AnimationFrame s_PcData_80182AE0[] = {
    {1, 1732}, {1, 1732},  {1, 1734},   {2, 1734},
    {8, 1734}, {65533, 9}, {65533, 15}, {65535, 0},
};

static AnimationFrame s_PcData_80182B00[] = {
    {1, 3792}, {1, 3792},   {1, 3793},  {2, 3793},
    {8, 3793}, {65533, 10}, {65535, 0},
};

static AnimationFrame s_PcData_80182B1C[] = {
    {1, 3796}, {1, 3796},  {1, 3797},  {2, 3797},
    {8, 3797}, {65533, 7}, {65535, 0},
};

static AnimationFrame s_PcData_80182B38[] = {
    {1, 3796}, {1, 3796},  {1, 3798},  {2, 3798},
    {8, 3798}, {65533, 7}, {65535, 0},
};

static AnimationFrame s_PcData_80182B54[] = {
    {65533, 11},
    {65533, 13},
    {65535, 0},
};

static AnimationFrame s_PcData_80182BA8[] = {
    {65533, 11},
    {65533, 14},
    {65535, 0},
};

static AnimationFrame s_PcData_80182BB4[] = {
    {1, 1732}, {1, 1732}, {1, 1733}, {2, 1733},  {2, 1733},   {2, 1733},
    {2, 1733}, {1, 1733}, {1, 1733}, {65533, 6}, {65533, 15}, {65535, 0},
};

static AnimationFrame s_PcData_80182BE4[] = {
    {1, 1732}, {1, 1732}, {1, 1734}, {2, 1734},  {2, 1734},   {2, 1734},
    {2, 1734}, {1, 1734}, {1, 1734}, {65533, 6}, {65533, 15}, {65535, 0},
};

static AnimationFrame s_PcData_80182C14[] = {
    {1, 3792}, {1, 3792}, {1, 3793}, {2, 3793},   {2, 3793},  {2, 3793},
    {2, 3793}, {1, 3793}, {1, 3793}, {65533, 10}, {65535, 0},
};

static AnimationFrame s_PcData_80182C40[] = {
    {1, 3796}, {1, 3796}, {1, 3797}, {2, 3797},  {2, 3797},  {2, 3797},
    {2, 3797}, {1, 3797}, {1, 3797}, {65533, 7}, {65535, 0},
};

static AnimationFrame s_PcData_80182C6C[] = {
    {1, 3796}, {1, 3796}, {1, 3798}, {2, 3798},  {2, 3798},  {2, 3798},
    {2, 3798}, {1, 3798}, {1, 3798}, {65533, 7}, {65535, 0},
};

static AnimationFrame s_PcData_80182C98[] = {
    {65533, 12},
    {65533, 13},
    {65535, 0},
};

static AnimationFrame s_PcData_80182CEC[] = {
    {65533, 12},
    {65533, 14},
    {65535, 0},
};

static AnimationFrame s_PcData_80182CF8[] = {
    {2, 1732}, {1, 1732}, {1, 1733}, {2, 1733},  {2, 1733},   {1, 1733},
    {1, 1733}, {1, 1733}, {3, 1733}, {65533, 9}, {65533, 15}, {65535, 0},
};

static AnimationFrame s_PcData_80182D28[] = {
    {2, 1732}, {1, 1732}, {1, 1734}, {2, 1734},  {2, 1734},   {1, 1734},
    {1, 1734}, {1, 1734}, {3, 1734}, {65533, 9}, {65533, 15}, {65535, 0},
};

static AnimationFrame s_PcData_80182D58[] = {
    {2, 3792}, {1, 3792}, {1, 3793}, {2, 3793},   {2, 3793},  {1, 3793},
    {1, 3793}, {1, 3793}, {3, 3793}, {65533, 10}, {65535, 0},
};

static AnimationFrame s_PcData_80182D84[] = {
    {2, 3796}, {1, 3796}, {1, 3797}, {2, 3797},  {2, 3797},  {1, 3797},
    {1, 3797}, {1, 3797}, {3, 3797}, {65533, 7}, {65535, 0},
};

static AnimationFrame s_PcData_80182DB0[] = {
    {2, 3796}, {1, 3796}, {1, 3798}, {2, 3798},  {2, 3798},  {1, 3798},
    {1, 3798}, {1, 3798}, {3, 3798}, {65533, 7}, {65535, 0},
};

static AnimationFrame s_PcData_80182DDC[] = {
    {2, 634},  {2, 635},  {1, 4794},   {1, 4795},  {1, 4796}, {1, 4797},
    {1, 4798}, {3, 4799}, {3, 704},    {3, 705},   {3, 706},  {3, 707},
    {2, 596},  {2, 597},  {65533, 16}, {65534, 2},
};

static AnimationFrame s_PcData_80182E1C[] = {
    {5, 599}, {4, 600}, {3, 601},  {3, 602},   {3, 603},
    {3, 604}, {3, 605}, {16, 633}, {65534, 3},
};

static AnimationFrame s_PcData_80182E8C[] = {
    {1, 1733}, {1, 1735}, {1, 1736}, {1, 1737}, {1, 1738}, {1, 1739},
    {4, 1740}, {3, 1741}, {3, 1742}, {3, 1743}, {1, 1551}, {65535, 0},
};

static AnimationFrame s_PcData_80182E40[] = {
    {4, 634}, {4, 635}, {4, 513}, {65533, 16}, {65533, 17}, {65534, 2},
};

static AnimationFrame s_PcData_80182E58[] = {
    {6, 1110}, {6, 599}, {6, 600}, {6, 601}, {6, 602},   {5, 603},   {3, 604},
    {3, 603},  {2, 604}, {2, 605}, {2, 604}, {128, 605}, {65534, 6},
};

static AnimationFrame s_PcData_80182EBC[] = {
    {2, 634}, {2, 634}, {2, 634}, {64, 635}, {65535, 0},
};

static AnimationFrame s_PcData_80182ED0[] = {
    {2, 1665}, {2, 1665}, {2, 1665}, {64, 1666}, {65535, 0},
};

static AnimationFrame s_PcData_80182EE4[] = {
    {65533, 2}, {4, 592}, {4, 593}, {4, 594}, {4, 595},
    {4, 596},   {4, 597}, {4, 596}, {4, 597}, {65535, 0},
};

static AnimationFrame s_PcData_80182F0C[] = {
    {65533, 2}, {4, 586}, {4, 587}, {4, 588}, {4, 589},
    {4, 590},   {4, 591}, {4, 590}, {4, 591}, {65535, 0},
};

static AnimationFrame s_PcData_80182F34[] = {
    {65533, 18},
    {65533, 13},
    {65535, 0},
};

static AnimationFrame s_PcData_80182F78[] = {
    {65533, 18},
    {65533, 14},
    {65535, 0},
};

static AnimationFrame s_PcData_80182F84[] = {
    {1, 1732}, {1, 1732}, {1, 1733}, {1, 1733},   {1, 1733},
    {1, 1733}, {2, 1735}, {2, 1735}, {2, 1735},   {4, 1736},
    {4, 1737}, {4, 1738}, {8, 1739}, {65533, 15}, {65535, 0},
};

static AnimationFrame s_PcData_80182FC0[] = {
    {1, 1732}, {1, 1732}, {1, 1734},   {2, 1734},  {1, 1734},
    {2, 1735}, {2, 1735}, {2, 1735},   {4, 1736},  {4, 1737},
    {4, 1738}, {8, 1739}, {65533, 15}, {65535, 0},
};

static AnimationFrame s_PcData_80182FF8[] = {
    {1, 3792}, {1, 3792}, {1, 3793}, {1, 3793},  {1, 3793},
    {1, 3793}, {1, 3794}, {1, 3794}, {2, 3794},  {2, 3795},
    {2, 3795}, {2, 3795}, {2, 3795}, {65535, 0},
};

static AnimationFrame s_PcData_80183030[] = {
    {1, 3796}, {1, 3796}, {1, 3797}, {1, 3797},  {1, 3797},
    {1, 3797}, {1, 3799}, {1, 3799}, {2, 3799},  {2, 3800},
    {2, 3800}, {2, 3800}, {2, 3800}, {65535, 0},
};

static AnimationFrame s_PcData_80183068[] = {
    {1, 3796}, {1, 3796}, {1, 3798},  {1, 3798}, {1, 3798},
    {1, 3799}, {1, 3799}, {1, 3799},  {2, 3800}, {2, 3800},
    {2, 3800}, {2, 3800}, {65535, 0},
};

static AnimationFrame s_PcData_801830F0[] = {
    {2, 4732}, {2, 4733}, {1, 4734}, {1, 4735},  {2, 4734},
    {2, 4733}, {4, 4732}, {5, 4736}, {65535, 0},
};

static AnimationFrame s_PcData_80183114[] = {
    {2, 1665}, {2, 1666}, {1, 1667}, {1, 1668},
    {2, 1667}, {2, 1666}, {4, 1665}, {65535, 0},
};

static AnimationFrame s_PcData_80183134[] = {
    {1, 4229}, {1, 4230}, {1, 4231}, {2, 4230}, {2, 4229}, {65535, 0},
};

static AnimationFrame s_PcData_8018314C[] = {
    {1, 3720},
    {4, 3721},
    {2, 3720},
    {65535, 0},
};

static AnimationFrame s_PcData_8018315C[] = {
    {65533, 19},
    {65533, 13},
    {65535, 0},
};

static AnimationFrame s_PcData_80183190[] = {
    {65533, 19},
    {65533, 14},
    {65535, 0},
};

static AnimationFrame s_PcData_8018319C[] = {
    {2, 1732}, {1, 1733}, {3, 1733}, {1, 1735},   {3, 1735},  {4, 1736},
    {4, 1737}, {4, 1738}, {8, 1739}, {65533, 15}, {65535, 0},
};

static AnimationFrame s_PcData_801831C8[] = {
    {2, 1732}, {1, 1734}, {3, 1734}, {1, 1735},   {3, 1735},  {4, 1736},
    {4, 1737}, {4, 1738}, {8, 1739}, {65533, 15}, {65535, 0},
};

static AnimationFrame s_PcData_801831F4[] = {
    {2, 3792}, {1, 3793}, {3, 3793},  {1, 3794},
    {3, 3794}, {8, 3795}, {65535, 0},
};

static AnimationFrame s_PcData_80183210[] = {
    {2, 3796}, {1, 3797}, {3, 3797},  {1, 3799},
    {3, 3799}, {8, 3800}, {65535, 0},
};

static AnimationFrame s_PcData_8018322C[] = {
    {2, 3796}, {1, 3798}, {3, 3798},  {1, 3799},
    {3, 3799}, {8, 3800}, {65535, 0},
};

static AnimationFrame s_PcData_80183248[] = {
    {1, 4732}, {1, 4733}, {1, 4734}, {1, 4735},  {2, 4734},
    {2, 4733}, {4, 4732}, {5, 4736}, {65535, 0},
};

static AnimationFrame s_PcData_8018326C[] = {
    {1, 1665}, {1, 1666}, {1, 1667}, {1, 1668},
    {2, 1667}, {2, 1666}, {4, 1665}, {65535, 0},
};

static AnimationFrame s_PcData_8018328C[] = {
    {65533, 20},
    {65533, 13},
    {65535, 0},
};

static AnimationFrame s_PcData_801832C0[] = {
    {65533, 20},
    {65533, 14},
    {65535, 0},
};

static AnimationFrame s_PcData_801832CC[] = {
    {2, 1732}, {1, 1733}, {2, 1733}, {1, 1735},   {3, 1735},  {4, 1736},
    {4, 1737}, {4, 1738}, {8, 1739}, {65533, 15}, {65535, 0},
};

static AnimationFrame s_PcData_801832F8[] = {
    {2, 1732}, {1, 1734}, {2, 1734}, {1, 1735},   {3, 1735},  {4, 1736},
    {4, 1737}, {4, 1738}, {8, 1739}, {65533, 15}, {65535, 0},
};

static AnimationFrame s_PcData_80183324[] = {
    {2, 3792}, {1, 3793}, {2, 3793},  {1, 3794},
    {3, 3794}, {8, 3795}, {65535, 0},
};

static AnimationFrame s_PcData_80183340[] = {
    {2, 3796}, {1, 3797}, {2, 3797},  {1, 3799},
    {3, 3799}, {8, 3800}, {65535, 0},
};

static AnimationFrame s_PcData_8018335C[] = {
    {65533, 21},
    {65533, 13},
    {65535, 0},
};

static AnimationFrame s_PcData_801833B4[] = {
    {65533, 21},
    {65533, 14},
    {65535, 0},
};

static AnimationFrame s_PcData_801833C0[] = {
    {2, 1665}, {2, 1666}, {1, 1667}, {1, 1668},   {2, 1667},
    {2, 1667}, {2, 1666}, {2, 1665}, {1, 1732},   {1, 1732},
    {1, 1734}, {3, 1734}, {1, 1735}, {3, 1735},   {4, 1736},
    {4, 1737}, {4, 1738}, {4, 1739}, {65533, 15}, {65535, 0},
};

static AnimationFrame s_PcData_80183410[] = {
    {1, 3792}, {1, 3792}, {1, 3793}, {3, 3793},
    {1, 3794}, {3, 3794}, {8, 3795}, {65535, 0},
};

static AnimationFrame s_PcData_80183430[] = {
    {1, 3796}, {1, 3796}, {1, 3797}, {3, 3797},
    {1, 3799}, {3, 3799}, {8, 3800}, {65535, 0},
};

static AnimationFrame s_PcData_80183450[] = {
    {2, 3796}, {1, 3798}, {3, 3798},  {1, 3799},
    {3, 3799}, {8, 3800}, {65535, 0},
};

static AnimationFrame s_PcData_8018346C[] = {
    {65533, 22},
    {65533, 13},
    {65535, 0},
};

static AnimationFrame s_PcData_801834AC[] = {
    {65533, 22},
    {65533, 14},
    {65535, 0},
};

static AnimationFrame s_PcData_801834B8[] = {
    {2, 1732}, {1, 1733}, {1, 1733},   {1, 1733},  {1, 1733},
    {1, 1733}, {1, 1735}, {3, 1735},   {4, 1736},  {4, 1737},
    {4, 1738}, {8, 1739}, {65533, 15}, {65535, 0},
};

static AnimationFrame s_PcData_801834F0[] = {
    {2, 1732}, {1, 1734}, {1, 1734},   {1, 1734},  {1, 1734},
    {1, 1734}, {1, 1735}, {3, 1735},   {4, 1736},  {4, 1737},
    {4, 1738}, {8, 1739}, {65533, 15}, {65535, 0},
};

static AnimationFrame s_PcData_80183528[] = {
    {2, 3792}, {1, 3793}, {1, 3793}, {1, 3793}, {1, 3793},
    {1, 3793}, {1, 3794}, {3, 3794}, {8, 3795}, {65535, 0},
};

static AnimationFrame s_PcData_80183550[] = {
    {2, 3796}, {1, 3797}, {1, 3797}, {1, 3797}, {1, 3797},
    {1, 3797}, {1, 3799}, {3, 3799}, {8, 3800}, {65535, 0},
};

static AnimationFrame s_PcData_80183578[] = {
    {2, 3796}, {1, 3798}, {1, 3798}, {1, 3798}, {1, 3798},
    {1, 3798}, {1, 3799}, {3, 3799}, {8, 3800}, {65535, 0},
};

static AnimationFrame s_PcData_801835A0[] = {
    {65533, 23},
    {65533, 13},
    {65535, 0},
};

static AnimationFrame s_PcData_801835D4[] = {
    {65533, 23},
    {65533, 14},
    {65535, 0},
};

static AnimationFrame s_PcData_801835E0[] = {
    {2, 1732}, {1, 1733}, {3, 1733}, {2, 1735},   {2, 1735},  {4, 1736},
    {4, 1737}, {4, 1738}, {8, 1739}, {65533, 15}, {65535, 0},
};

static AnimationFrame s_PcData_8018360C[] = {
    {2, 3792}, {1, 3793}, {3, 3793},  {2, 3794},
    {2, 3794}, {8, 3795}, {65535, 0},
};

static AnimationFrame s_PcData_80183628[] = {
    {2, 3796}, {1, 3797}, {3, 3797},  {2, 3799},
    {2, 3799}, {8, 3800}, {65535, 0},
};

static AnimationFrame s_PcData_80183644[] = {
    {65533, 24},
    {65533, 13},
    {65535, 0},
};

static AnimationFrame s_PcData_80183678[] = {
    {65533, 24},
    {65533, 14},
    {65535, 0},
};

static AnimationFrame s_PcData_80183684[] = {
    {3, 1732}, {1, 1733}, {4, 1733}, {1, 1735},   {3, 1735},  {4, 1736},
    {4, 1737}, {4, 1738}, {8, 1739}, {65533, 15}, {65535, 0},
};

static AnimationFrame s_PcData_801836B0[] = {
    {3, 3792}, {1, 3793}, {4, 3793},  {1, 3794},
    {3, 3794}, {8, 3795}, {65535, 0},
};

static AnimationFrame s_PcData_801836CC[] = {
    {3, 3796}, {1, 3797}, {4, 3797},  {1, 3799},
    {3, 3799}, {8, 3800}, {65535, 0},
};

static AnimationFrame s_PcData_801836E8[] = {
    {65533, 25},
    {65533, 13},
    {65535, 0},
};

static AnimationFrame s_PcData_8018371C[] = {
    {65533, 25},
    {65533, 14},
    {65535, 0},
};

static AnimationFrame s_PcData_80183728[] = {
    {2, 1732}, {1, 1733}, {3, 1733}, {1, 1735},   {3, 1735},  {4, 1736},
    {4, 1737}, {4, 1738}, {8, 1739}, {65533, 15}, {65535, 0},
};

static AnimationFrame s_PcData_80183754[] = {
    {2, 1732}, {1, 1734}, {3, 1734}, {1, 1735},   {3, 1735},  {4, 1736},
    {4, 1737}, {4, 1738}, {8, 1739}, {65533, 15}, {65535, 0},
};

static AnimationFrame s_PcData_80183780[] = {
    {2, 3792}, {1, 3793}, {3, 3793},  {1, 3794},
    {3, 3794}, {8, 3795}, {65535, 0},
};

static AnimationFrame s_PcData_8018379C[] = {
    {2, 3796}, {1, 3797}, {3, 3797},  {1, 3799},
    {3, 3799}, {8, 3800}, {65535, 0},
};

static AnimationFrame s_PcData_801837B8[] = {
    {2, 3796}, {1, 3798}, {3, 3798},  {1, 3799},
    {3, 3799}, {8, 3800}, {65535, 0},
};

static AnimationFrame s_PcData_801837D4[] = {
    {65533, 26},
    {65533, 13},
    {65535, 0},
};

static AnimationFrame s_PcData_80183820[] = {
    {65533, 26},
    {65533, 14},
    {65535, 0},
};

static AnimationFrame s_PcData_8018382C[] = {
    {1, 1732}, {1, 1732}, {1, 1732}, {1, 1732},   {1, 1733},  {1, 1733},
    {1, 1733}, {1, 1733}, {1, 1733}, {1, 1735},   {3, 1735},  {4, 1736},
    {4, 1737}, {4, 1738}, {8, 1739}, {65533, 15}, {65535, 0},
};

static AnimationFrame s_PcData_80183870[] = {
    {1, 1732}, {1, 1732}, {1, 1732}, {1, 1732},   {1, 1734},  {1, 1734},
    {1, 1734}, {1, 1734}, {1, 1734}, {1, 1735},   {3, 1735},  {4, 1736},
    {4, 1737}, {4, 1738}, {8, 1739}, {65533, 15}, {65535, 0},
};

static AnimationFrame s_PcData_801838B4[] = {
    {1, 3792}, {1, 3792}, {1, 3792},  {1, 3792}, {1, 3793},
    {1, 3793}, {1, 3793}, {1, 3793},  {1, 3793}, {1, 3794},
    {3, 3794}, {8, 3795}, {65535, 0},
};

static AnimationFrame s_PcData_801838E8[] = {
    {1, 3796}, {1, 3796}, {1, 3796},  {1, 3796}, {1, 3797},
    {1, 3797}, {1, 3797}, {1, 3797},  {1, 3797}, {1, 3799},
    {3, 3799}, {8, 3800}, {65535, 0},
};

static AnimationFrame s_PcData_8018391C[] = {
    {1, 3796}, {1, 3796}, {1, 3796},  {1, 3796}, {1, 3798},
    {1, 3798}, {1, 3798}, {1, 3798},  {1, 3798}, {1, 3799},
    {3, 3799}, {8, 3800}, {65535, 0},
};

static AnimationFrame s_PcData_80183950[] = {
    {2, 707}, {2, 706}, {2, 705}, {2, 704},  {2, 703},   {2, 704},
    {2, 703}, {2, 704}, {2, 703}, {36, 704}, {65535, 0},
};

static AnimationFrame s_PcData_8018397C[] = {
    {2, 1735}, {2, 1736}, {2, 1737}, {2, 1738},  {2, 1737},  {2, 1738},
    {2, 1737}, {2, 1738}, {2, 1737}, {24, 1738}, {65535, 0},
};

static AnimationFrame s_PcData_801839A8[] = {
    {2, 3794},  {2, 3795},  {2, 3794}, {2, 3795},  {2, 3794},
    {36, 3795}, {65535, 0}, {48, 635}, {65535, 0},
};

static AnimationFrame s_PcData_801839CC[] = {
    {48, 633},
    {65535, 0},
};

static AnimationFrame s_PcData_801839D4[] = {
    {3, 615}, {3, 616}, {3, 617},  {3, 616}, {3, 617},  {3, 616},
    {3, 617}, {3, 616}, {24, 617}, {4, 632}, {32, 633}, {65535, 0},
};

static AnimationFrame s_PcData_80183A04[] = {
    {6, 633},
    {6, 634},
    {16, 635},
    {65535, 0},
};

static AnimationFrame s_PcData_80183A14[] = {
    {6, 633},
    {6, 634},
    {16, 633},
    {65535, 0},
};

static AnimationFrame s_PcData_80183A24[] = {
    {4, 654}, {4, 655}, {4, 656},  {20, 657},
    {4, 656}, {4, 655}, {16, 654}, {65534, 4},
};

static AnimationFrame s_PcData_80182838[] = {
    {65533, 27}, {7, 3765}, {7, 3766},  {7, 3767},
    {8, 3745},   {1, 3746}, {65535, 0},
};

static AnimationFrame s_PcData_80182854[] = {
    {65533, 27}, {7, 3765}, {7, 3766}, {7, 3767}, {65535, 0},
};

static AnimationFrame s_PcData_80183A4C[] = {
    {2, 7681}, {3, 7682}, {4, 7683}, {4, 7684}, {3, 7685}, {2, 7686},
    {2, 7687}, {2, 7688}, {2, 7689}, {2, 7690}, {0, 0},
};

static AnimationFrame s_PcData_80183A78[] = {
    {1, 7692}, {1, 7693}, {1, 7695}, {1, 7696},    {1, 7694},
    {1, 7693}, {1, 7692}, {1, 7693}, {1, 7695},    {2, 7696},
    {2, 7694}, {2, 7693}, {2, 7692}, {2, 7693},    {2, 7695},
    {3, 7696}, {3, 7694}, {3, 7693}, {65534, 196},
};

static AnimationFrame s_PcData_80183AC4[] = {
    {3, 7681}, {4, 7682}, {6, 7683}, {6, 7684}, {5, 7685}, {4, 7686},
    {4, 7687}, {3, 7688}, {3, 7689}, {3, 7690}, {0, 0},
};

static AnimationFrame s_PcData_80183AF0[] = {
    {4, 7682}, {6, 7683}, {6, 7684}, {5, 7685}, {4, 7686}, {4, 7687},
    {3, 7688}, {3, 7689}, {3, 7690}, {3, 7681}, {0, 9},
};

static AnimationFrame s_PcData_80183B1C[] = {
    {6, 7683},
    {65535, 0},
};

static AnimationFrame s_PcData_80183B24[] = {
    {4, 7879}, {4, 7880}, {4, 7881}, {4, 7882}, {4, 7883},
    {6, 7884}, {5, 7885}, {5, 7886}, {5, 7887}, {65535, 0},
};

static AnimationFrame s_PcData_80183B4C[] = {
    {4, 7886}, {4, 7885}, {6, 7884},  {5, 7885},
    {5, 7886}, {5, 7887}, {65535, 0},
};

static AnimationFrame s_PcData_80183B68[] = {
    {1, 7692}, {1, 7693}, {1, 7695}, {1, 7696}, {1, 7694}, {1, 7693},
    {1, 7692}, {1, 7693}, {1, 7695}, {1, 7696}, {4, 7694}, {65535, 0},
};

static AnimationFrame s_PcData_80183BA0[] = {
    {132, 95},
    {65535, 0},
};

static AnimationFrame s_PcData_80183BA8[] = {
    {132, 199},
    {65535, 0},
};

static AnimationFrame s_PcData_80183BB0[] = {
    {3, 513}, {2, 514}, {2, 515}, {3, 516}, {2, 515}, {2, 514}, {0, 0},
};

static AnimationFrame s_PcData_80183BCC[] = {
    {1, 517},
    {16, 518},
    {65535, 0},
};

static AnimationFrame s_PcData_80183BD8[] = {
    {128, 515}, {1, 514},   {16, 514}, {16, 515}, {1, 514},
    {16, 514},  {16, 515},  {1, 514},  {16, 514}, {16, 515},
    {1, 514},   {128, 514}, {0, 0},
};

static AnimationFrame s_PcData_80183C0C[] = {
    {128, 514},
    {65535, 0},
};

static AnimationFrame s_PcData_80183C14[] = {
    {128, 520},
    {65535, 0},
};

static AnimationFrame s_PcData_80183C34[] = {
    {1, 528}, {1, 529}, {1, 530}, {20, 637}, {4, 634}, {65534, 4},
};

static AnimationFrame s_PcData_80183C1C[] = {
    {1, 1548}, {1, 1547}, {1, 1546}, {24, 1666}, {1, 1551}, {65535, 0},
};

static AnimationFrame s_PcData_801830D8[] = {
    {65533, 28}, {65533, 13}, {65535, 0}, {65533, 28}, {65533, 14}, {65535, 0},
};

static AnimationFrame s_PcData_80183C4C[] = {
    {2, 26},  {2, 27},  {2, 28},  {2, 29},   {2, 30},  {2, 31},
    {2, 208}, {4, 209}, {5, 210}, {16, 211}, {2, 106}, {2, 107},
    {2, 108}, {2, 109}, {3, 110}, {1, 110},  {128, 1}, {65535, 0},
};

static AnimationFrame s_PcData_80183C94[] = {
    {2, 26},  {2, 27},  {2, 28},  {2, 29},    {2, 30},  {2, 31},
    {2, 208}, {4, 209}, {5, 210}, {4, 211},   {2, 208}, {4, 209},
    {5, 210}, {4, 211}, {2, 106}, {2, 107},   {2, 108}, {2, 109},
    {3, 110}, {1, 110}, {128, 1}, {65535, 0},
};

static AnimationFrame s_PcData_80183CEC[] = {
    {65533, 2},
    {4, 632},
    {64, 633},
    {65535, 0},
};

static AnimationFrame s_PcData_80182348[] = {
    {2, 2114}, {2, 2625},  {3, 2624},  {3, 2111},
    {3, 2110}, {65533, 2}, {65535, 0},
};

AnimationFrame* D_us_80183D40[] = {
    s_PcData_801820B4, s_PcData_801820CC, s_PcData_801820D4, s_PcData_801820E8,
    s_PcData_801820F0, s_PcData_8018214C, s_PcData_80182180, s_PcData_801821A0,
    s_PcData_801821E4, s_PcData_80182204, s_PcData_80182230, s_PcData_80182238,
    s_PcData_8018228C, s_PcData_80182294, s_PcData_801822D8, s_PcData_80182320,
    s_PcData_80182364, s_PcData_801823A4, s_PcData_801823AC, s_PcData_801823B4,
    s_PcData_801823C4, s_PcData_801823CC, s_PcData_801823EC, s_PcData_801823F8,
    s_PcData_80182410, s_PcData_8018241C, s_PcData_80182428, s_PcData_80182434,
    s_PcData_80182448, s_PcData_80182460, s_PcData_8018249C, s_PcData_801824BC,
    s_PcData_801824C8, s_PcData_801824F0, s_PcData_801824FC, s_PcData_80182810,
    s_PcData_8018257C, s_PcData_8018257C, s_PcData_801825A4, s_PcData_801825A4,
    s_PcData_801825C8, s_PcData_801825E0, s_PcData_801825F8, s_PcData_80182504,
    s_PcData_80182504, s_PcData_8018256C, s_PcData_80182620, s_PcData_80182628,
    s_PcData_80182638, s_PcData_80182640, s_PcData_8018266C, s_PcData_80182698,
    s_PcData_801826C0, s_PcData_801826E8, s_PcData_801826F4, s_PcData_80182700,
    s_PcData_80182718, s_PcData_80182720, s_PcData_80182728, s_PcData_80182730,
    s_PcData_80182868, s_PcData_801828BC, s_PcData_80183A44, s_PcData_80182758,
    s_PcData_801827D8, s_PcData_801828C4, s_PcData_80182928, s_PcData_80182958,
    s_PcData_801829B4, s_PcData_801829D4, s_PcData_80182A04, s_PcData_80182A34,
    s_PcData_80182A4C, s_PcData_80182A90, s_PcData_80182A9C, s_PcData_80182AE0,
    s_PcData_80182B00, s_PcData_80182B1C, s_PcData_80182B38, s_PcData_80182B54,
    s_PcData_80182BA8, s_PcData_80182BB4, s_PcData_80182BE4, s_PcData_80182C14,
    s_PcData_80182C40, s_PcData_80182C6C, s_PcData_80182C98, s_PcData_80182CEC,
    s_PcData_80182CF8, s_PcData_80182D28, s_PcData_80182D58, s_PcData_80182D84,
    s_PcData_80182DB0, s_PcData_80182DDC, s_PcData_80182E1C, s_PcData_80182E8C,
    s_PcData_80182E40, s_PcData_80182E58, s_PcData_80182E8C, s_PcData_80182EBC,
    s_PcData_80182EBC, s_PcData_80182ED0, s_PcData_80182EE4, s_PcData_80182F0C,
    s_PcData_80182F34, s_PcData_80182F78, s_PcData_80182F84, s_PcData_80182FC0,
    s_PcData_80182FF8, s_PcData_80183030, s_PcData_80183068, s_PcData_801830F0,
    s_PcData_801830F0, s_PcData_80183114, s_PcData_80183114, s_PcData_80183134,
    s_PcData_8018314C, s_PcData_8018314C, s_PcData_8018315C, s_PcData_80183190,
    s_PcData_8018319C, s_PcData_801831C8, s_PcData_801831F4, s_PcData_80183210,
    s_PcData_8018322C, s_PcData_80183248, s_PcData_80183248, s_PcData_8018326C,
    s_PcData_8018326C, s_PcData_80183134, s_PcData_8018314C, s_PcData_8018314C,
    s_PcData_8018328C, s_PcData_801832C0, s_PcData_801832CC, s_PcData_801832F8,
    s_PcData_80183324, s_PcData_80183340, s_PcData_80183340, s_PcData_8018335C,
    s_PcData_801833B4, s_PcData_801833C0, s_PcData_801833C0, s_PcData_80183410,
    s_PcData_80183430, s_PcData_80183450, s_PcData_8018346C, s_PcData_801834AC,
    s_PcData_801834B8, s_PcData_801834F0, s_PcData_80183528, s_PcData_80183550,
    s_PcData_80183578, s_PcData_801835A0, s_PcData_801835D4, s_PcData_801835E0,
    s_PcData_801835E0, s_PcData_8018360C, s_PcData_80183628, s_PcData_80183628,
    s_PcData_80183644, s_PcData_80183678, s_PcData_80183684, s_PcData_80183684,
    s_PcData_801836B0, s_PcData_801836CC, s_PcData_801836CC, s_PcData_801836E8,
    s_PcData_8018371C, s_PcData_80183728, s_PcData_80183754, s_PcData_80183780,
    s_PcData_8018379C, s_PcData_801837B8, s_PcData_801837D4, s_PcData_80183820,
    s_PcData_8018382C, s_PcData_80183870, s_PcData_801838B4, s_PcData_801838E8,
    s_PcData_8018391C, s_PcData_80183950, s_PcData_8018397C, s_PcData_801839A8,
    s_PcData_801839CC, s_PcData_801839CC, s_PcData_801839D4, s_PcData_801839D4,
    s_PcData_80183A04, s_PcData_80183A14, s_PcData_80183A24, s_PcData_80183A24,
    s_PcData_80182838, s_PcData_80182854, s_PcData_80183A4C, s_PcData_80183A78,
    s_PcData_80183AC4, s_PcData_80183AF0, s_PcData_80183B1C, s_PcData_80183B24,
    s_PcData_80183B4C, s_PcData_80183B68, D_us_80183B98,     s_PcData_80183BA0,
    s_PcData_80183BA8, s_PcData_80183BB0, s_PcData_80183BCC, s_PcData_80183BD8,
    s_PcData_80183C0C, s_PcData_80183C14, s_PcData_80183C34, s_PcData_80183C34,
    s_PcData_80183C1C, s_PcData_80183C1C, s_PcData_801830D8, s_PcData_801830D8,
    s_PcData_80183C4C, s_PcData_80183C94, s_PcData_80183CEC, s_PcData_80182348,
};

static u16 s_PcData_80184124[] = {
    513,  1026, 1027, 1028, 1029, 1542, 1543,
    1544, 1545, 2058, 2059, 2060, 2061, 65535,
};

static u16 s_PcData_80184140[] = {
    2574, 3087, 3088, 3089, 3090, 3603, 3604,
    3605, 3606, 2079, 2080, 2081, 2082, 65535,
};

static u16 s_PcData_8018415C[] = {
    2574, 4119, 4632, 4121, 4634, 5147, 5148,
    5149, 5150, 2079, 2080, 2081, 2082, 65535,
};

static u16 s_PcData_80184178[] = {
    5667, 6180, 6181, 6182, 6183, 6696, 6697, 6698, 6699, 2092, 65535, 0,
};

static u16 s_PcData_80184190[] = {
    7213, 7726, 7727, 7728, 7729, 8242, 8243, 8244, 8245, 2110, 65535, 0,
};

static u16 s_PcData_801841A8[] = {
    7213, 8758, 8759, 8760, 8761, 9274, 9275, 9276, 9277, 2110, 65535, 0,
};

static u16* s_PcData_801842CC[] = {
    s_PcData_80184124, s_PcData_80184124, s_PcData_80184140, s_PcData_8018415C,
    s_PcData_80184178, s_PcData_80184190, s_PcData_801841A8,
};

static s8 s_PcData_801841C0[] = {
    0,   0,   0,   0,   4,   -23, 8,  5,  30,  -17, 35, 8,  30,  -14, 18,
    4,   -32, -31, 0,   0,   -4,  -6, 8,  5,   22,  0,  35, 8,   22,  3,
    18,  4,   29,  22,  13,  11,  12, 7,  19,  12,  14, 14, 18,  4,   1,
    -25, 8,   5,   27,  -19, 35,  8,  27, -16, 18,  4,  -8, -26, 8,   5,
    24,  -17, 35,  8,   24,  -14, 18, 4,  23,  0,   27, 14, 18,  2,   21,
    11,  29,  -14, 34,  4,   21,  3,  34, 4,   28,  21, 12, 10,  26,  -16,
    34,  4,   23,  -14, 34,  4,   22, 3,  26,  10,
};

static u16 s_PcData_80184224[] = {
    513, 1026, 1027, 1540, 1541, 1542, 1543, 1544, 1545, 65535,
};

static u16 s_PcData_80184238[] = {
    2058, 2571, 2572, 1549, 1550, 1555, 1556, 1557, 1558, 65535,
};

static u16 s_PcData_8018424C[] = {
    2058, 3087, 3600, 4113, 1554, 1555, 1556, 1557, 1558, 65535,
};

static u16 s_PcData_80184260[] = {
    4631, 5144, 5145, 1562, 1563, 1564, 65535, 0,
};

static u16 s_PcData_80184270[] = {
    5661, 6174, 6175, 1568, 1569, 1574, 65535, 0,
};

static u16 s_PcData_80184280[] = {
    5661, 6690, 7203, 1572, 1573, 1574, 65535, 0,
};

static u16* s_PcData_801842E8[] = {
    s_PcData_80184224, s_PcData_80184224, s_PcData_80184238, s_PcData_8018424C,
    s_PcData_80184260, s_PcData_80184270, s_PcData_80184280,
};

static s8 s_PcData_80184290[] = {
    0,   0,  0,  0,  3,   -24, 5,  4,   25, -13, 24, 3,   -32, -31, 0,
    0,   -5, -5, 5,  4,   17,  4,  24,  3,  7,   15, 14,  8,   19,  21,
    15,  7,  13, 18, 17,  5,   -1, -25, 5,  4,   23, -15, 24,  7,   -9,
    -27, 5,  4,  19, -14, 24,  7,  15,  2,  19,  10, 29,  8,   11,  8,
};

DopWeaponAnimation D_us_80184304[] = {
    {s_PcData_801842CC, s_PcData_801841C0, 1547, 65, 4},
    {s_PcData_801842E8, s_PcData_80184290, 1547, 167, 4},
    {s_PcData_801842CC, s_PcData_801841C0, 1547, 65, 4},
};

static s16 s_PcData_801B0F74[] = {
    -32768,
    -16,
    -23,
    0,
};

static s16 s_PcData_801B0F7C[] = {
    -32767,
    -40,
    -31,
    0,
};

static s16 s_PcData_801B0F84[] = {
    -32766,
    -40,
    -31,
    0,
};

static s16 s_PcData_801B0F8C[] = {
    -32765,
    -40,
    -31,
    0,
};

static s16 s_PcData_801B0F94[] = {
    -32764,
    -40,
    -31,
    0,
};

static s16 s_PcData_801B0F9C[] = {
    -32763,
    -40,
    -31,
    0,
};

static s16 s_PcData_801B0FA4[] = {
    -32762,
    -40,
    -31,
    0,
};

static s16 s_PcData_801B0FAC[] = {
    -32761,
    -40,
    -31,
    0,
};

static s16 s_PcData_801B0FB4[] = {
    -32760,
    -32,
    -15,
    0,
};

static s16 s_PcData_801B0FBC[] = {
    -32759,
    -32,
    -7,
    0,
};

static s16 s_PcData_801B0FC4[] = {
    -32758,
    -32,
    -7,
    0,
};

static s16 s_PcData_801B0FCC[] = {
    -32757,
    -32,
    -7,
    0,
};

static s16 s_PcData_801B0FD4[] = {
    -32756,
    -32,
    -7,
    0,
};

static s16 s_PcData_801B0FDC[] = {
    -32755,
    -24,
    -7,
    0,
};

static s16 s_PcData_801B0FE4[] = {
    -32754,
    -24,
    -7,
    0,
};

static s16 s_PcData_801B0FEC[] = {
    -32753,
    -16,
    -15,
    0,
};

static s16 s_PcData_801B0FF4[] = {
    -32752,
    -16,
    -23,
    0,
};

static s16 s_PcData_801B0FFC[] = {
    -32751,
    -16,
    -23,
    0,
};

static s16 s_PcData_801B1004[] = {
    -32750,
    -16,
    -23,
    0,
};

static s16 s_PcData_801B100C[] = {
    -32749,
    -16,
    -23,
    0,
};

static s16 s_PcData_801B1014[] = {
    -32748,
    -16,
    -23,
    0,
};

static s16 s_PcData_801B101C[] = {
    -32747,
    -16,
    -23,
    0,
};

static s16 s_PcData_801B1024[] = {
    -32746,
    -16,
    -23,
    0,
};

static s16 s_PcData_801B102C[] = {
    -32745,
    -16,
    -23,
    0,
};

static s16 s_PcData_801B1034[] = {
    -32744,
    -16,
    -23,
    0,
};

static s16 s_PcData_801B103C[] = {
    -32743,
    -16,
    -23,
    0,
};

static s16 s_PcData_801B1044[] = {
    -32742,
    -16,
    -23,
    0,
};

static s16 s_PcData_801B104C[] = {
    -32741,
    -16,
    -23,
    0,
};

static s16 s_PcData_801B1054[] = {
    -32740,
    -16,
    -23,
    0,
};

static s16 s_PcData_801B105C[] = {
    -32739,
    -32,
    -31,
    0,
};

static s16 s_PcData_801B1064[] = {
    -32738,
    -32,
    -31,
    0,
};

static s16 s_PcData_801B106C[] = {
    -32737,
    -32,
    -31,
    0,
};

static s16 s_PcData_801B1074[] = {
    -32736,
    -32,
    -31,
    0,
};

static s16 s_PcData_801B107C[] = {
    -32735,
    -32,
    -31,
    0,
};

static s16 s_PcData_801B1084[] = {
    -32734,
    -32,
    -31,
    0,
};

static s16 s_PcData_801B108C[] = {
    -32733,
    -32,
    -31,
    0,
};

static s16 s_PcData_801B1094[] = {
    -32732,
    -32,
    -31,
    0,
};

static s16 s_PcData_801B109C[] = {
    -32731,
    -32,
    -31,
    0,
};

static s16 s_PcData_801B10A4[] = {
    -32730,
    -32,
    -31,
    0,
};

static s16 s_PcData_801B10AC[] = {
    -32729,
    -32,
    -31,
    0,
};

static s16 s_PcData_801B10B4[] = {
    -32728,
    -24,
    -23,
    0,
};

static s16 s_PcData_801B10BC[] = {
    -32727,
    -32,
    -31,
    0,
};

static s16 s_PcData_801B10C4[] = {
    -32726,
    -32,
    -31,
    0,
};

static s16 s_PcData_801B10CC[] = {
    -32725,
    -32,
    -31,
    0,
};

static s16 s_PcData_801B10D4[] = {
    -32724,
    -32,
    -31,
    0,
};

static s16 s_PcData_801B10DC[] = {
    -32723,
    -32,
    -31,
    0,
};

static s16 s_PcData_801B10E4[] = {
    -32722,
    -32,
    -31,
    0,
};

static s16 s_PcData_801B10EC[] = {
    -32721,
    -32,
    -31,
    0,
};

static s16 s_PcData_801B10F4[] = {
    -32720,
    -32,
    -31,
    0,
};

static s16 s_PcData_801B10FC[] = {
    -32719,
    -32,
    -31,
    0,
};

static s16 s_PcData_801B1104[] = {
    -32718,
    -32,
    -31,
    0,
};

static s16 s_PcData_801B110C[] = {
    -32717,
    -32,
    -31,
    0,
};

static s16 s_PcData_801B1114[] = {
    -32716,
    -32,
    -31,
    0,
};

static s16 s_PcData_801B111C[] = {
    -32715,
    -32,
    -31,
    0,
};

static s16 s_PcData_801B1124[] = {
    -32714,
    -32,
    -31,
    0,
};

static s16 s_PcData_801B112C[] = {
    -32713,
    -32,
    -31,
    0,
};

static s16 s_PcData_801B1134[] = {
    -32712,
    -32,
    -31,
    0,
};

static s16 s_PcData_801B113C[] = {
    -32711,
    -32,
    -31,
    0,
};

static s16 s_PcData_801B1144[] = {
    -32710,
    -32,
    -31,
    0,
};

static s16 s_PcData_801B114C[] = {
    -32709,
    -32,
    -31,
    0,
};

static s16 s_PcData_801B1154[] = {
    -32708,
    -32,
    -31,
    0,
};

static s16 s_PcData_801B115C[] = {
    -32707,
    -32,
    -31,
    0,
};

static s16 s_PcData_801B1164[] = {
    -32706,
    -32,
    -31,
    0,
};

static s16 s_PcData_801B116C[] = {
    -32705,
    -32,
    -31,
    0,
};

static s16 s_PcData_801B1174[] = {
    -32704,
    -32,
    -31,
    0,
};

static s16 s_PcData_801B117C[] = {
    -32703,
    -32,
    -31,
    0,
};

static s16 s_PcData_801B1184[] = {
    -32702,
    -32,
    -23,
    0,
};

static s16 s_PcData_801B118C[] = {
    -32701,
    -32,
    -31,
    0,
};

static s16 s_PcData_801B1194[] = {
    -32700,
    -32,
    -31,
    0,
};

static s16 s_PcData_801B119C[] = {
    -32699,
    -32,
    -31,
    0,
};

static s16 s_PcData_801B11A4[] = {
    -32698,
    -32,
    -31,
    0,
};

static s16 s_PcData_801B11AC[] = {
    -32697,
    -32,
    -31,
    0,
};

static s16 s_PcData_801B11B4[] = {
    -32696,
    -32,
    -31,
    0,
};

static s16 s_PcData_801B11BC[] = {
    -32695,
    -32,
    -31,
    0,
};

static s16 s_PcData_801B11C4[] = {
    -32694,
    -32,
    -31,
    0,
};

static s16 s_PcData_801B11CC[] = {
    -32693,
    -32,
    -31,
    0,
};

static s16 s_PcData_801B11D4[] = {
    -32692,
    -32,
    -31,
    0,
};

static s16 s_PcData_801B11DC[] = {
    -32691,
    -32,
    -31,
    0,
};

static s16 s_PcData_801B11E4[] = {
    -32690,
    -32,
    -31,
    0,
};

static s16 s_PcData_801B11EC[] = {
    -32689,
    -32,
    -23,
    0,
};

static s16 s_PcData_801B11F4[] = {
    -32688,
    -32,
    -31,
    0,
};

static s16 s_PcData_801B11FC[] = {
    -32687,
    -32,
    -31,
    0,
};

static s16 s_PcData_801B1204[] = {
    -32686,
    -32,
    -31,
    0,
};

static s16 s_PcData_801B120C[] = {
    -32685,
    -32,
    -31,
    0,
};

static s16 s_PcData_801B1214[] = {
    -32684,
    -32,
    -31,
    0,
};

static s16 s_PcData_801B121C[] = {
    -32683,
    -32,
    -23,
    0,
};

static s16 s_PcData_801B1224[] = {
    -32682,
    -32,
    -31,
    0,
};

static s16 s_PcData_801B122C[] = {
    -32681,
    -32,
    -31,
    0,
};

static s16 s_PcData_801B1234[] = {
    -32680,
    -32,
    -31,
    0,
};

static s16 s_PcData_801B123C[] = {
    -32679,
    -32,
    -31,
    0,
};

static s16 s_PcData_801B1244[] = {
    -32678,
    -32,
    -31,
    0,
};

static s16 s_PcData_801B124C[] = {
    -32677,
    -32,
    -31,
    0,
};

static s16 s_PcData_801B1254[] = {
    -32676,
    -32,
    -31,
    0,
};

static s16 s_PcData_801B125C[] = {
    -32675,
    -32,
    -31,
    0,
};

static s16 s_PcData_801B1264[] = {
    -32674,
    -16,
    -31,
    0,
};

static s16 s_PcData_801B126C[] = {
    -32673,
    -16,
    -31,
    0,
};

static s16 s_PcData_801B1274[] = {
    -32672,
    -16,
    -31,
    0,
};

static s16 s_PcData_801B127C[] = {
    -32671,
    -16,
    -31,
    0,
};

static s16 s_PcData_801B1284[] = {
    -32670,
    -32,
    -31,
    0,
};

static s16 s_PcData_801B128C[] = {
    -32669,
    -32,
    -31,
    0,
};

static s16 s_PcData_801B1294[] = {
    -32668,
    -32,
    -31,
    0,
};

static s16 s_PcData_801B129C[] = {
    -32667,
    -32,
    -31,
    0,
};

static s16 s_PcData_801B12A4[] = {
    -32666,
    -16,
    -31,
    0,
};

static s16 s_PcData_801B12AC[] = {
    -32665,
    -16,
    -31,
    0,
};

static s16 s_PcData_801B12B4[] = {
    -32664,
    -16,
    -31,
    0,
};

static s16 s_PcData_801B12BC[] = {
    -32663,
    -40,
    -31,
    0,
};

static s16 s_PcData_801B12C4[] = {
    -32662,
    -40,
    -31,
    0,
};

static s16 s_PcData_801B12CC[] = {
    -32661,
    -40,
    -31,
    0,
};

static s16 s_PcData_801B12D4[] = {
    -32660,
    -40,
    -31,
    0,
};

static s16 s_PcData_801B12DC[] = {
    -32659,
    -40,
    -31,
    0,
};

static s16 s_PcData_801B12E4[] = {
    -32658,
    -40,
    -31,
    0,
};

static s16 s_PcData_801B12EC[] = {
    -32657,
    -40,
    -31,
    0,
};

static s16 s_PcData_801B12F4[] = {
    -32656,
    -40,
    -39,
    0,
};

static s16 s_PcData_801B12FC[] = {
    -32655,
    -40,
    -39,
    0,
};

static s16 s_PcData_801B1304[] = {
    -32654,
    -40,
    -39,
    0,
};

static s16 s_PcData_801B130C[] = {
    -32653,
    -32,
    -31,
    0,
};

static s16 s_PcData_801B1314[] = {
    -32652,
    -32,
    -31,
    0,
};

static s16 s_PcData_801B131C[] = {
    -32651,
    -32,
    -31,
    0,
};

static s16 s_PcData_801B1324[] = {
    -32650,
    -32,
    -31,
    0,
};

static s16 s_PcData_801B132C[] = {
    -32649,
    -32,
    -31,
    0,
};

static s16 s_PcData_801B1334[] = {
    -32648,
    -16,
    -23,
    0,
};

static s16 s_PcData_801B133C[] = {
    -32647,
    -16,
    -23,
    0,
};

static s16 s_PcData_801B1344[] = {
    -32646,
    -16,
    -23,
    0,
};

static s16 s_PcData_801B134C[] = {
    -32645,
    -8,
    -31,
    0,
};

static s16 s_PcData_801B1354[] = {
    -32644,
    -8,
    -31,
    0,
};

static s16 s_PcData_801B135C[] = {
    -32643,
    -8,
    -31,
    0,
};

static s16 s_PcData_801B1364[] = {
    -32642,
    -8,
    -31,
    0,
};

static s16 s_PcData_801B136C[] = {
    -32641,
    -8,
    -31,
    0,
};

static s16 s_PcData_801B1374[] = {
    -32640,
    -16,
    -7,
    0,
};

static s16 s_PcData_801B137C[] = {
    -32639,
    -16,
    -7,
    0,
};

static s16 s_PcData_801B1384[] = {
    -32638,
    -24,
    -5,
    0,
};

static s16 s_PcData_801B138C[] = {
    -32637,
    -24,
    -5,
    0,
};

static s16 s_PcData_801B1394[] = {
    -32636,
    -40,
    -31,
    0,
};

static s16 s_PcData_801B139C[] = {
    -32635,
    -40,
    -31,
    0,
};

static s16 s_PcData_801B13A4[] = {
    -32634,
    -40,
    -31,
    0,
};

static s16 s_PcData_801B13AC[] = {
    -32633,
    -40,
    -39,
    0,
};

static s16 s_PcData_801B13B4[] = {
    -32632,
    -32,
    -39,
    0,
};

static s16 s_PcData_801B13BC[] = {
    -32631,
    -32,
    -39,
    0,
};

static s16 s_PcData_801B13C4[] = {
    -32630,
    -40,
    -39,
    0,
};

static s16 s_PcData_801B13CC[] = {
    -32629,
    -16,
    -31,
    0,
};

static s16 s_PcData_801B13D4[] = {
    -32628,
    -24,
    -39,
    0,
};

static s16 s_PcData_801B13DC[] = {
    -32627,
    -16,
    -31,
    0,
};

static s16 s_PcData_801B13E4[] = {
    -32626,
    -16,
    -31,
    0,
};

static s16 s_PcData_801B13EC[] = {
    -32625,
    -16,
    -31,
    0,
};

static s16 s_PcData_801B13F4[] = {
    -32624,
    -16,
    -31,
    0,
};

static s16 s_PcData_801B13FC[] = {
    -32623,
    -16,
    -31,
    0,
};

static s16 s_PcData_801B1404[] = {
    -32622,
    -24,
    -23,
    0,
};

static s16 s_PcData_801B140C[] = {
    -32621,
    -24,
    -23,
    0,
};

static s16 s_PcData_801B1414[] = {
    -32620,
    -24,
    -23,
    0,
};

static s16 s_PcData_801B141C[] = {
    -32619,
    -24,
    -23,
    0,
};

static s16 s_PcData_801B1424[] = {
    -32618,
    -32,
    -31,
    0,
};

static s16 s_PcData_801B142C[] = {
    -32617,
    -32,
    -79,
    0,
};

static s16 s_PcData_801B1434[] = {
    -32616,
    -24,
    -31,
    0,
};

static s16 s_PcData_801B143C[] = {
    -32615,
    -32,
    -23,
    0,
};

static s16 s_PcData_801B1444[] = {
    -32614,
    -32,
    -23,
    0,
};

static s16 s_PcData_801B144C[] = {
    -32613,
    -24,
    -23,
    0,
};

static s16 s_PcData_801B1454[] = {
    -32612,
    -16,
    -23,
    0,
};

static s16 s_PcData_801B145C[] = {
    -32611,
    -27,
    -27,
    0,
};

static s16 s_PcData_801B1464[] = {
    -32610,
    -16,
    -31,
    0,
};

static s16 s_PcData_801B146C[] = {
    -32610,
    -16,
    -32,
    0,
};

static s16 s_PcData_801B1474[] = {
    -32609,
    -16,
    -31,
    0,
};

static s16 s_PcData_801B147C[] = {
    -32608,
    -16,
    -31,
    0,
};

static s16 s_PcData_801B1484[] = {
    -32607,
    -16,
    -31,
    0,
};

static s16 s_PcData_801B148C[] = {
    -32607,
    -16,
    -32,
    0,
};

static s16 s_PcData_801B1494[] = {
    -32606,
    -32,
    -31,
    0,
};

static s16 s_PcData_801B149C[] = {
    -32606,
    -33,
    -31,
    0,
};

static s16 s_PcData_801B14A4[] = {
    -32605,
    -32,
    -31,
    0,
};

static s16 s_PcData_801B14AC[] = {
    -32605,
    -33,
    -31,
    0,
};

static s16 s_PcData_801B14B4[] = {
    -32604,
    -32,
    -31,
    0,
};

static s16 s_PcData_801B14BC[] = {
    -32604,
    -31,
    -31,
    0,
};

static s16 s_PcData_801B14C4[] = {
    -32603,
    -32,
    -31,
    0,
};

static s16 s_PcData_801B14CC[] = {
    -32603,
    -31,
    -31,
    0,
};

static s16 s_PcData_801B14D4[] = {
    -32602,
    -24,
    -23,
    158,
};

static s16 s_PcData_801B14DC[] = {
    -32601,
    -11,
    -23,
    159,
};

static s16 s_PcData_801B14E4[] = {
    -32600,
    -73,
    -47,
    158,
};

static s16 s_PcData_801B14EC[] = {
    -32599,
    -32,
    -31,
    0,
};

static s16 s_PcData_801B14F4[] = {
    -32598,
    -40,
    -31,
    0,
};

static s16 s_PcData_801B14FC[] = {
    -32597,
    -40,
    -31,
    0,
};

static s16 s_PcData_801B1504[] = {
    -32596,
    -40,
    -31,
    0,
};

static s16 s_PcData_801B150C[] = {
    -32595,
    -32,
    -31,
    0,
};

static s16 s_PcData_801B1514[] = {
    -32594,
    -32,
    -31,
    0,
};

static s16 s_PcData_801B151C[] = {
    -32593,
    -32,
    -31,
    0,
};

static s16 s_PcData_801B1524[] = {
    -32592,
    -32,
    -31,
    0,
};

static s16 s_PcData_801B152C[] = {
    -32591,
    -32,
    -31,
    0,
};

static s16 s_PcData_801B1534[] = {
    -32590,
    -24,
    -31,
    0,
};

static s16 s_PcData_801B153C[] = {
    -32589,
    -32,
    -23,
    0,
};

static s16 s_PcData_801B1544[] = {
    -32588,
    -24,
    -23,
    0,
};

static s16 s_PcData_801B154C[] = {
    -32587,
    -24,
    -31,
    0,
};

static s16 s_PcData_801B1554[] = {
    -32586,
    -24,
    -31,
    0,
};

static s16 s_PcData_801B155C[] = {
    -32585,
    -16,
    -23,
    0,
};

static s16 s_PcData_801B1564[] = {
    -32584,
    -16,
    -23,
    0,
};

static s16 s_PcData_801B156C[] = {
    -32583,
    -8,
    -23,
    0,
};

static s16 s_PcData_801B1574[] = {
    -32582,
    -8,
    -23,
    0,
};

static s16 s_PcData_801B157C[] = {
    -32581,
    -16,
    -23,
    0,
};

static s16 s_PcData_801B1584[] = {
    -32580,
    -16,
    -23,
    0,
};

static s16 s_PcData_801B158C[] = {
    -32579,
    -24,
    -7,
    0,
};

static s16 s_PcData_801B1594[] = {
    -32578,
    -32,
    -7,
    0,
};

static s16 s_PcData_801B159C[] = {
    -32577,
    -32,
    -7,
    0,
};

static s16 s_PcData_801B15A4[] = {
    -32576,
    -32,
    -7,
    0,
};

static s16 s_PcData_801B15AC[] = {
    -32575,
    -32,
    -15,
    0,
};

static s16 s_PcData_801B15B4[] = {
    -32574,
    -24,
    -7,
    0,
};

static s16 s_PcData_801B15BC[] = {
    -32573,
    -24,
    -7,
    0,
};

static s16 s_PcData_801B15C4[] = {
    -32572,
    -24,
    -7,
    0,
};

static s16 s_PcData_801B15CC[] = {
    -32571,
    -16,
    -7,
    0,
};

static s16 s_PcData_801B15D4[] = {
    -32570,
    -16,
    -7,
    0,
};

static s16 s_PcData_801B15DC[] = {
    -32569,
    -16,
    -7,
    0,
};

static s16 s_PcData_801B15E4[] = {
    -32568,
    -16,
    -7,
    0,
};

static s16 s_PcData_801B15EC[] = {
    -32567,
    -32,
    -31,
    0,
};

static s16 s_PcData_801B15F4[] = {
    -32566,
    -40,
    -31,
    0,
};

static s16 s_PcData_801B15FC[] = {
    -32565,
    -32,
    -23,
    0,
};

static s16 s_PcData_801B1604[] = {
    -32564,
    -32,
    -23,
    0,
};

static s16 s_PcData_801B160C[] = {
    -32563,
    -40,
    -39,
    0,
};

static s16 s_PcData_801B1614[] = {
    -32562,
    -32,
    -39,
    0,
};

static s16 s_PcData_801B161C[] = {
    -32561,
    -32,
    -39,
    0,
};

static s16 s_PcData_801B1624[] = {
    -32560,
    -32,
    -47,
    0,
};

static s16 s_PcData_801B162C[] = {
    -32559,
    -32,
    -47,
    0,
};

static s16 s_PcData_801B1634[] = {
    -32558,
    -24,
    -15,
    0,
};

static s16 s_PcData_801B163C[] = {
    -32557,
    -18,
    -22,
    0,
};

static s16 s_PcData_801B1644[] = {
    -32556,
    -16,
    -22,
    0,
};

static s16 s_PcData_801B164C[] = {
    -32555,
    -14,
    -22,
    0,
};

static s16 s_PcData_801B1654[] = {
    -32554,
    -21,
    -21,
    0,
};

static s16 s_PcData_801B165C[] = {
    -32553,
    -19,
    -21,
    0,
};

static s16 s_PcData_801B1664[] = {
    -32552,
    -19,
    -21,
    0,
};

static s16 s_PcData_801B166C[] = {
    -32551,
    -12,
    -20,
    0,
};

s16* D_us_801B0B50[] = {
    NULL,
    s_PcData_801B0F74,
    s_PcData_801B0F7C,
    s_PcData_801B0F84,
    s_PcData_801B0F8C,
    s_PcData_801B0F94,
    s_PcData_801B0F9C,
    s_PcData_801B0FA4,
    s_PcData_801B0FAC,
    s_PcData_801B0FB4,
    s_PcData_801B0FBC,
    s_PcData_801B0FC4,
    s_PcData_801B0FCC,
    s_PcData_801B0FD4,
    s_PcData_801B0FDC,
    s_PcData_801B0FE4,
    s_PcData_801B0FEC,
    s_PcData_801B0FF4,
    s_PcData_801B0FFC,
    s_PcData_801B1004,
    s_PcData_801B100C,
    s_PcData_801B1014,
    s_PcData_801B101C,
    s_PcData_801B1024,
    s_PcData_801B102C,
    s_PcData_801B1034,
    s_PcData_801B103C,
    s_PcData_801B1044,
    s_PcData_801B104C,
    s_PcData_801B1054,
    s_PcData_801B105C,
    s_PcData_801B1064,
    s_PcData_801B106C,
    s_PcData_801B1074,
    s_PcData_801B107C,
    s_PcData_801B1084,
    s_PcData_801B108C,
    s_PcData_801B1094,
    s_PcData_801B109C,
    s_PcData_801B10A4,
    s_PcData_801B10AC,
    s_PcData_801B10B4,
    s_PcData_801B10BC,
    s_PcData_801B10C4,
    s_PcData_801B10CC,
    s_PcData_801B10D4,
    s_PcData_801B10DC,
    s_PcData_801B10E4,
    s_PcData_801B10EC,
    s_PcData_801B10F4,
    s_PcData_801B10FC,
    s_PcData_801B1104,
    s_PcData_801B110C,
    s_PcData_801B1114,
    s_PcData_801B111C,
    s_PcData_801B1124,
    s_PcData_801B112C,
    s_PcData_801B1134,
    s_PcData_801B113C,
    s_PcData_801B1144,
    s_PcData_801B114C,
    s_PcData_801B1154,
    s_PcData_801B115C,
    s_PcData_801B1164,
    s_PcData_801B116C,
    s_PcData_801B1174,
    s_PcData_801B117C,
    s_PcData_801B1184,
    s_PcData_801B118C,
    s_PcData_801B1194,
    s_PcData_801B119C,
    s_PcData_801B11A4,
    s_PcData_801B11AC,
    s_PcData_801B11B4,
    s_PcData_801B11BC,
    s_PcData_801B11C4,
    s_PcData_801B11CC,
    s_PcData_801B11D4,
    s_PcData_801B11DC,
    s_PcData_801B11E4,
    s_PcData_801B11EC,
    s_PcData_801B11F4,
    s_PcData_801B11FC,
    s_PcData_801B1204,
    s_PcData_801B120C,
    s_PcData_801B1214,
    s_PcData_801B121C,
    s_PcData_801B1224,
    s_PcData_801B122C,
    s_PcData_801B1234,
    s_PcData_801B123C,
    s_PcData_801B1244,
    s_PcData_801B124C,
    s_PcData_801B1254,
    s_PcData_801B125C,
    s_PcData_801B1264,
    s_PcData_801B126C,
    s_PcData_801B1274,
    s_PcData_801B127C,
    s_PcData_801B1284,
    s_PcData_801B128C,
    s_PcData_801B1294,
    s_PcData_801B129C,
    s_PcData_801B12A4,
    s_PcData_801B12AC,
    s_PcData_801B12B4,
    s_PcData_801B12BC,
    s_PcData_801B12C4,
    s_PcData_801B12CC,
    s_PcData_801B12D4,
    s_PcData_801B12DC,
    s_PcData_801B12E4,
    s_PcData_801B12EC,
    s_PcData_801B12F4,
    s_PcData_801B12FC,
    s_PcData_801B1304,
    s_PcData_801B130C,
    s_PcData_801B1314,
    s_PcData_801B131C,
    s_PcData_801B1324,
    s_PcData_801B132C,
    s_PcData_801B1334,
    s_PcData_801B133C,
    s_PcData_801B1344,
    s_PcData_801B134C,
    s_PcData_801B1354,
    s_PcData_801B135C,
    s_PcData_801B1364,
    s_PcData_801B136C,
    s_PcData_801B1374,
    s_PcData_801B137C,
    s_PcData_801B1384,
    s_PcData_801B138C,
    s_PcData_801B1394,
    s_PcData_801B139C,
    s_PcData_801B13A4,
    s_PcData_801B13AC,
    s_PcData_801B13B4,
    s_PcData_801B13BC,
    s_PcData_801B13C4,
    s_PcData_801B13CC,
    s_PcData_801B13D4,
    s_PcData_801B13DC,
    s_PcData_801B13E4,
    s_PcData_801B13EC,
    s_PcData_801B13F4,
    s_PcData_801B13FC,
    s_PcData_801B1404,
    s_PcData_801B140C,
    s_PcData_801B1414,
    s_PcData_801B141C,
    s_PcData_801B1424,
    s_PcData_801B142C,
    s_PcData_801B1434,
    s_PcData_801B143C,
    s_PcData_801B1444,
    s_PcData_801B144C,
    s_PcData_801B1454,
    s_PcData_801B145C,
    s_PcData_801B1464,
    s_PcData_801B146C,
    s_PcData_801B1474,
    s_PcData_801B147C,
    s_PcData_801B1484,
    s_PcData_801B148C,
    s_PcData_801B1494,
    s_PcData_801B149C,
    s_PcData_801B14A4,
    s_PcData_801B14AC,
    s_PcData_801B14B4,
    s_PcData_801B14BC,
    s_PcData_801B14C4,
    s_PcData_801B14CC,
    s_PcData_801B14D4,
    s_PcData_801B14DC,
    s_PcData_801B14E4,
    s_PcData_801B14EC,
    s_PcData_801B14F4,
    s_PcData_801B14FC,
    s_PcData_801B1504,
    s_PcData_801B150C,
    s_PcData_801B1514,
    s_PcData_801B151C,
    s_PcData_801B1524,
    s_PcData_801B152C,
    s_PcData_801B1534,
    s_PcData_801B153C,
    s_PcData_801B1544,
    s_PcData_801B154C,
    s_PcData_801B1554,
    s_PcData_801B155C,
    s_PcData_801B1564,
    s_PcData_801B156C,
    s_PcData_801B1574,
    s_PcData_801B157C,
    s_PcData_801B1584,
    s_PcData_801B158C,
    s_PcData_801B1594,
    s_PcData_801B159C,
    s_PcData_801B15A4,
    s_PcData_801B15AC,
    s_PcData_801B15B4,
    s_PcData_801B15BC,
    s_PcData_801B15C4,
    s_PcData_801B15CC,
    s_PcData_801B15D4,
    s_PcData_801B15DC,
    s_PcData_801B15E4,
    s_PcData_801B15EC,
    s_PcData_801B15F4,
    s_PcData_801B15FC,
    s_PcData_801B1604,
    s_PcData_801B160C,
    s_PcData_801B1614,
    s_PcData_801B161C,
    s_PcData_801B1624,
    s_PcData_801B162C,
    s_PcData_801B1634,
    s_PcData_801B163C,
    s_PcData_801B1644,
    s_PcData_801B164C,
    s_PcData_801B1654,
    s_PcData_801B165C,
    s_PcData_801B1664,
    s_PcData_801B166C,
    s_PcData_801B163C,
    s_PcData_801B163C,
    s_PcData_801B163C,
    s_PcData_801B163C,
    s_PcData_801B163C,
    s_PcData_801B163C,
    s_PcData_801B163C,
    s_PcData_801B163C,
    s_PcData_801B163C,
    s_PcData_801B163C,
    s_PcData_801B163C,
    s_PcData_801B163C,
    s_PcData_801B163C,
    s_PcData_801B163C,
    s_PcData_801B163C,
    s_PcData_801B163C,
    s_PcData_801B163C,
    s_PcData_801B163C,
    s_PcData_801B163C,
    s_PcData_801B163C,
    s_PcData_801B163C,
    s_PcData_801B163C,
    s_PcData_801B163C,
    s_PcData_801B163C,
    s_PcData_801B163C,
    s_PcData_801B163C,
    s_PcData_801B163C,
    s_PcData_801B163C,
    s_PcData_801B163C,
    s_PcData_801B163C,
    s_PcData_801B163C,
    s_PcData_801B163C,
    s_PcData_801B163C,
    s_PcData_801B163C,
    s_PcData_801B163C,
    s_PcData_801B163C,
    s_PcData_801B163C,
    s_PcData_801B163C,
    s_PcData_801B163C,
    NULL,
};

static s16 s_PcData_801B16BC[] = {
    -32768,
    -22,
    -48,
    0,
};

static s16 s_PcData_801B16C4[] = {
    -32767,
    -22,
    -47,
    0,
};

static s16 s_PcData_801B16CC[] = {
    -32766,
    -22,
    -40,
    0,
};

static s16 s_PcData_801B16D4[] = {
    -32765,
    -22,
    -41,
    0,
};

static s16 s_PcData_801B16DC[] = {
    -32764,
    -22,
    -30,
    0,
};

static s16 s_PcData_801B16E4[] = {
    -32764,
    -22,
    -31,
    0,
};

static s16 s_PcData_801B16EC[] = {
    -32763,
    -22,
    -30,
    0,
};

static s16 s_PcData_801B16F4[] = {
    -32765,
    -22,
    -41,
    0,
};

static s16 s_PcData_801B16FC[] = {
    -32766,
    -22,
    -41,
    0,
};

static s16 s_PcData_801B1704[] = {
    -32767,
    -22,
    -49,
    0,
};

static s16 s_PcData_801B170C[] = {
    -32768,
    -22,
    -51,
    0,
};

static s16 s_PcData_801B1714[] = {
    -32767,
    -22,
    -51,
    0,
};

static s16 s_PcData_801B171C[] = {
    -32766,
    -22,
    -42,
    0,
};

static s16 s_PcData_801B1724[] = {
    -32765,
    -22,
    -41,
    0,
};

static s16 s_PcData_801B172C[] = {
    -32764,
    -22,
    -29,
    0,
};

static s16 s_PcData_801B1734[] = {
    -32763,
    -22,
    -29,
    0,
};

s16* D_us_801B1674[] = {
    NULL,
    s_PcData_801B16BC,
    s_PcData_801B16C4,
    s_PcData_801B16CC,
    s_PcData_801B16D4,
    s_PcData_801B16DC,
    s_PcData_801B16E4,
    s_PcData_801B16EC,
    s_PcData_801B16F4,
    s_PcData_801B16FC,
    s_PcData_801B1704,
    s_PcData_801B170C,
    s_PcData_801B1714,
    s_PcData_801B171C,
    s_PcData_801B1724,
    s_PcData_801B172C,
    s_PcData_801B1734,
    NULL,
};

static s16 s_PcData_801B1880[] = {
    1, 256, -8, -31, 24, 16, 0, 0, 64, 24, 88, 40, 0, 0,
};

static s16 s_PcData_801B189C[] = {
    1, 304, -10, -31, 80, 24, 0, 0, 0, 0, 80, 24, 0, 0,
};

static s16 s_PcData_801B18B8[] = {
    1, 304, -10, -31, 80, 24, 1, 0, 0, 0, 80, 24, 0, 0,
};

static s16 s_PcData_801B18D4[] = {
    1, 304, -10, -31, 80, 24, 2, 0, 0, 0, 80, 24, 0, 0,
};

static s16 s_PcData_801B18F0[] = {
    1, 304, -10, -31, 80, 24, 3, 0, 0, 0, 80, 24, 0, 0,
};

static s16 s_PcData_801B190C[] = {
    1, 16, 11, -23, 40, 16, 0, 0, 0, 24, 40, 40, 0, 0,
};

static s16 s_PcData_801B1928[] = {
    1, 16, 11, -23, 40, 16, 1, 0, 0, 24, 40, 40, 0, 0,
};

static s16 s_PcData_801B1944[] = {
    1, 16, 11, -23, 40, 16, 2, 0, 0, 24, 40, 40, 0, 0,
};

static s16 s_PcData_801B1960[] = {
    1, 16, 11, -23, 40, 16, 3, 0, 0, 24, 40, 40, 0, 0,
};

static s16 s_PcData_801B197C[] = {
    1, 0, -21, -15, 16, 16, 0, 0, 40, 24, 56, 40, 0, 0,
};

static s16 s_PcData_801B1998[] = {
    1, 0, -21, -15, 16, 16, 0, 0, 40, 24, 56, 40, 0, 0,
};

static s16 s_PcData_801B19B4[] = {
    1, 0, -22, -15, 16, 16, 0, 0, 40, 24, 56, 40, 0, 0,
};

static s16 s_PcData_801B19D0[] = {
    1, 0, -22, -15, 16, 16, 0, 0, 40, 24, 56, 40, 0, 0,
};

static s16 s_PcData_801B19EC[] = {
    1, 256, -16, -14, 24, 16, 0, 0, 64, 24, 88, 40, 0, 0,
};

static s16 s_PcData_801B1A08[] = {
    1, 304, -18, -14, 80, 24, 0, 0, 0, 0, 80, 24, 0, 0,
};

static s16 s_PcData_801B1A24[] = {
    1, 304, -18, -14, 80, 24, 1, 0, 0, 0, 80, 24, 0, 0,
};

static s16 s_PcData_801B1A40[] = {
    1, 304, -18, -14, 80, 24, 2, 0, 0, 0, 80, 24, 0, 0,
};

static s16 s_PcData_801B1A5C[] = {
    1, 304, -18, -14, 80, 24, 3, 0, 0, 0, 80, 24, 0, 0,
};

static s16 s_PcData_801B1A78[] = {
    1, 16, 3, -6, 40, 16, 0, 0, 0, 24, 40, 40, 0, 0,
};

static s16 s_PcData_801B1A94[] = {
    1, 16, 3, -6, 40, 16, 1, 0, 0, 24, 40, 40, 0, 0,
};

static s16 s_PcData_801B1AB0[] = {
    1, 16, 3, -6, 40, 16, 2, 0, 0, 24, 40, 40, 0, 0,
};

static s16 s_PcData_801B1ACC[] = {
    1, 16, 3, -6, 40, 16, 3, 0, 0, 24, 40, 40, 0, 0,
};

static s16 s_PcData_801B1AE8[] = {
    1, 272, -16, -15, 64, 56, 0, 0, 0, 40, 64, 96, 0, 0,
};

static s16 s_PcData_801B1B04[] = {
    1, 272, -16, -15, 64, 56, 1, 0, 0, 40, 64, 96, 0, 0,
};

static s16 s_PcData_801B1B20[] = {
    1, 272, -16, -15, 64, 56, 2, 0, 0, 40, 64, 96, 0, 0,
};

static s16 s_PcData_801B1B3C[] = {
    1, 272, -16, -15, 64, 56, 3, 0, 0, 40, 64, 96, 0, 0,
};

static s16 s_PcData_801B1B58[] = {
    1, 0, -12, -2, 48, 32, 0, 0, 64, 40, 112, 72, 0, 0,
};

static s16 s_PcData_801B1B74[] = {
    1, 0, -12, -2, 48, 32, 1, 0, 64, 40, 112, 72, 0, 0,
};

static s16 s_PcData_801B1B90[] = {
    1, 0, -12, -2, 48, 32, 2, 0, 64, 40, 112, 72, 0, 0,
};

static s16 s_PcData_801B1BAC[] = {
    1, 0, -12, -2, 48, 32, 3, 0, 64, 40, 112, 72, 0, 0,
};

static s16 s_PcData_801B1BC8[] = {
    1, 0, -29, 2, 16, 16, 0, 0, 40, 24, 56, 40, 0, 0,
};

static s16 s_PcData_801B1BE4[] = {
    1, 0, -29, 2, 16, 16, 0, 0, 40, 24, 56, 40, 0, 0,
};

static s16 s_PcData_801B1C00[] = {
    1, 0, -30, 2, 16, 16, 0, 0, 40, 24, 56, 40, 0, 0,
};

static s16 s_PcData_801B1C1C[] = {
    1, 0, -30, 2, 16, 16, 0, 0, 40, 24, 56, 40, 0, 0,
};

static s16 s_PcData_801B1C38[] = {
    1, 256, -11, -33, 24, 16, 0, 0, 64, 24, 88, 40, 0, 0,
};

static s16 s_PcData_801B1C54[] = {
    1, 304, -13, -33, 80, 24, 0, 0, 0, 0, 80, 24, 0, 0,
};

static s16 s_PcData_801B1C70[] = {
    1, 304, -13, -33, 80, 24, 1, 0, 0, 0, 80, 24, 0, 0,
};

static s16 s_PcData_801B1C8C[] = {
    1, 304, -13, -33, 80, 24, 2, 0, 0, 0, 80, 24, 0, 0,
};

static s16 s_PcData_801B1CA8[] = {
    1, 304, -13, -33, 80, 24, 3, 0, 0, 0, 80, 24, 0, 0,
};

static s16 s_PcData_801B1CC4[] = {
    1, 16, 8, -25, 40, 16, 0, 0, 0, 24, 40, 40, 0, 0,
};

static s16 s_PcData_801B1CE0[] = {
    1, 16, 8, -25, 40, 16, 1, 0, 0, 24, 40, 40, 0, 0,
};

static s16 s_PcData_801B1CFC[] = {
    1, 16, 8, -25, 40, 16, 2, 0, 0, 24, 40, 40, 0, 0,
};

static s16 s_PcData_801B1D18[] = {
    1, 16, 8, -25, 40, 16, 3, 0, 0, 24, 40, 40, 0, 0,
};

static s16 s_PcData_801B1D34[] = {
    1, 0, -24, -17, 16, 16, 0, 0, 40, 24, 56, 40, 0, 0,
};

static s16 s_PcData_801B1D50[] = {
    1, 256, -20, -34, 24, 16, 0, 0, 64, 24, 88, 40, 0, 0,
};

static s16 s_PcData_801B1D6C[] = {
    1, 304, -16, -31, 80, 24, 0, 0, 0, 0, 80, 24, 0, 0,
};

static s16 s_PcData_801B1D88[] = {
    1, 304, -16, -31, 80, 24, 1, 0, 0, 0, 80, 24, 0, 0,
};

static s16 s_PcData_801B1DA4[] = {
    1, 304, -16, -31, 80, 24, 2, 0, 0, 0, 80, 24, 0, 0,
};

static s16 s_PcData_801B1DC0[] = {
    1, 304, -16, -31, 80, 24, 3, 0, 0, 0, 80, 24, 0, 0,
};

static s16 s_PcData_801B1DDC[] = {
    1, 16, 5, -23, 40, 16, 0, 0, 0, 24, 40, 40, 0, 0,
};

static s16 s_PcData_801B1DF8[] = {
    1, 16, 5, -23, 40, 16, 1, 0, 0, 24, 40, 40, 0, 0,
};

static s16 s_PcData_801B1E14[] = {
    1, 16, 5, -23, 40, 16, 2, 0, 0, 24, 40, 40, 0, 0,
};

static s16 s_PcData_801B1E30[] = {
    1, 16, 5, -23, 40, 16, 3, 0, 0, 24, 40, 40, 0, 0,
};

static s16 s_PcData_801B1E4C[] = {
    1, 272, -9, -26, 64, 56, 1, 0, 0, 40, 64, 96, 0, 0,
};

static s16 s_PcData_801B1E68[] = {
    1, 272, -9, -26, 64, 56, 1, 0, 0, 40, 64, 96, 0, 0,
};

static s16 s_PcData_801B1E84[] = {
    1, 272, -9, -26, 64, 56, 2, 0, 0, 40, 64, 96, 0, 0,
};

static s16 s_PcData_801B1EA0[] = {
    1, 272, -9, -26, 64, 56, 3, 0, 0, 40, 64, 96, 0, 0,
};

static s16 s_PcData_801B1EBC[] = {
    1, 0, -5, -13, 48, 32, 0, 0, 64, 40, 112, 72, 0, 0,
};

static s16 s_PcData_801B1ED8[] = {
    1, 0, -5, -13, 48, 32, 1, 0, 64, 40, 112, 72, 0, 0,
};

static s16 s_PcData_801B1EF4[] = {
    1, 0, -5, -13, 48, 32, 2, 0, 64, 40, 112, 72, 0, 0,
};

static s16 s_PcData_801B1F10[] = {
    1, 0, -5, -13, 48, 32, 3, 0, 64, 40, 112, 72, 0, 0,
};

static s16 s_PcData_801B1F2C[] = {
    1, 0, -27, -15, 16, 16, 0, 0, 40, 24, 56, 40, 0, 0,
};

static s16 s_PcData_801B1F48[] = {
    1, 304, -10, -31, 80, 24, 4, 0, 0, 0, 80, 24, 0, 0,
};

static s16 s_PcData_801B1F64[] = {
    1, 304, -10, -31, 80, 24, 5, 0, 0, 0, 80, 24, 0, 0,
};

static s16 s_PcData_801B1F80[] = {
    1, 304, -10, -31, 80, 24, 6, 0, 0, 0, 80, 24, 0, 0,
};

static s16 s_PcData_801B1F9C[] = {
    1, 304, -18, -14, 80, 24, 4, 0, 0, 0, 80, 24, 0, 0,
};

static s16 s_PcData_801B1FB8[] = {
    1, 304, -18, -14, 80, 24, 5, 0, 0, 0, 80, 24, 0, 0,
};

static s16 s_PcData_801B1FD4[] = {
    1, 304, -18, -14, 80, 24, 6, 0, 0, 0, 80, 24, 0, 0,
};

static s16 s_PcData_801B1FF0[] = {
    1, 272, -16, -15, 64, 56, 4, 0, 0, 40, 64, 96, 0, 0,
};

static s16 s_PcData_801B200C[] = {
    1, 272, -16, -15, 64, 56, 5, 0, 0, 40, 64, 96, 0, 0,
};

static s16 s_PcData_801B2028[] = {
    1, 272, -16, -15, 64, 56, 6, 0, 0, 40, 64, 96, 0, 0,
};

static s16 s_PcData_801B2044[] = {
    1, 304, -13, -33, 80, 24, 4, 0, 0, 0, 80, 24, 0, 0,
};

static s16 s_PcData_801B2060[] = {
    1, 304, -13, -33, 80, 24, 5, 0, 0, 0, 80, 24, 0, 0,
};

static s16 s_PcData_801B207C[] = {
    1, 304, -13, -33, 80, 24, 6, 0, 0, 0, 80, 24, 0, 0,
};

static s16 s_PcData_801B2098[] = {
    1, 304, -16, -31, 80, 24, 4, 0, 0, 0, 80, 24, 0, 0,
};

static s16 s_PcData_801B20B4[] = {
    1, 304, -16, -31, 80, 24, 5, 0, 0, 0, 80, 24, 0, 0,
};

static s16 s_PcData_801B20D0[] = {
    1, 304, -16, -31, 80, 24, 6, 0, 0, 0, 80, 24, 0, 0,
};

static s16 s_PcData_801B20EC[] = {
    1, 272, -9, -26, 64, 56, 4, 0, 0, 40, 64, 96, 0, 0,
};

static s16 s_PcData_801B2108[] = {
    1, 272, -9, -26, 64, 56, 5, 0, 0, 40, 64, 96, 0, 0,
};

static s16 s_PcData_801B2124[] = {
    1, 272, -9, -26, 64, 56, 6, 0, 0, 40, 64, 96, 0, 0,
};

s16* D_us_801B173C[] = {
    NULL,
    s_PcData_801B1880,
    s_PcData_801B189C,
    s_PcData_801B18B8,
    s_PcData_801B18D4,
    s_PcData_801B18F0,
    s_PcData_801B190C,
    s_PcData_801B1928,
    s_PcData_801B1944,
    s_PcData_801B1960,
    s_PcData_801B197C,
    s_PcData_801B1998,
    s_PcData_801B19B4,
    s_PcData_801B19D0,
    s_PcData_801B19EC,
    s_PcData_801B1A08,
    s_PcData_801B1A24,
    s_PcData_801B1A40,
    s_PcData_801B1A5C,
    s_PcData_801B1A78,
    s_PcData_801B1A94,
    s_PcData_801B1AB0,
    s_PcData_801B1ACC,
    s_PcData_801B1AE8,
    s_PcData_801B1B04,
    s_PcData_801B1B20,
    s_PcData_801B1B3C,
    s_PcData_801B1B58,
    s_PcData_801B1B74,
    s_PcData_801B1B90,
    s_PcData_801B1BAC,
    s_PcData_801B1BC8,
    s_PcData_801B1BE4,
    s_PcData_801B1C00,
    s_PcData_801B1C1C,
    s_PcData_801B1C38,
    s_PcData_801B1C54,
    s_PcData_801B1C70,
    s_PcData_801B1C8C,
    s_PcData_801B1CA8,
    s_PcData_801B1CC4,
    s_PcData_801B1CE0,
    s_PcData_801B1CFC,
    s_PcData_801B1D18,
    s_PcData_801B1D34,
    s_PcData_801B1D50,
    s_PcData_801B1D6C,
    s_PcData_801B1D88,
    s_PcData_801B1DA4,
    s_PcData_801B1DC0,
    s_PcData_801B1DDC,
    s_PcData_801B1DF8,
    s_PcData_801B1E14,
    s_PcData_801B1E30,
    s_PcData_801B1E4C,
    s_PcData_801B1E68,
    s_PcData_801B1E84,
    s_PcData_801B1EA0,
    s_PcData_801B1EBC,
    s_PcData_801B1ED8,
    s_PcData_801B1EF4,
    s_PcData_801B1F10,
    s_PcData_801B1F2C,
    s_PcData_801B1F48,
    s_PcData_801B1F64,
    s_PcData_801B1F80,
    s_PcData_801B1F9C,
    s_PcData_801B1FB8,
    s_PcData_801B1FD4,
    s_PcData_801B1FF0,
    s_PcData_801B200C,
    s_PcData_801B2028,
    s_PcData_801B2044,
    s_PcData_801B2060,
    s_PcData_801B207C,
    s_PcData_801B2098,
    s_PcData_801B20B4,
    s_PcData_801B20D0,
    s_PcData_801B20EC,
    s_PcData_801B2108,
    s_PcData_801B2124,
};

static s16 s_PcData_801B21DC[] = {
    1, 304, -5, -32, 16, 16, 0, 0, 0, 0, 16, 16, 0, 0,
};

static s16 s_PcData_801B21F8[] = {
    1, 272, -10, -17, 56, 8, 0, 0, 0, 16, 56, 24, 0, 0,
};

static s16 s_PcData_801B2214[] = {
    1, 288, 28, -17, 24, 8, 0, 0, 16, 0, 40, 8, 0, 0,
};

static s16 s_PcData_801B2230[] = {
    1, 32, 5, -15, 32, 8, 0, 0, 40, 0, 72, 8, 0, 0,
};

static s16 s_PcData_801B224C[] = {
    1, 0, -12, -12, 16, 8, 0, 0, 16, 8, 32, 16, 0, 0,
};

static s16 s_PcData_801B2268[] = {
    1, 0, -20, -11, 16, 8, 0, 0, 16, 8, 32, 16, 0, 0,
};

static s16 s_PcData_801B2284[] = {
    1, 256, -21, -11, 16, 8, 0, 0, 16, 8, 32, 16, 0, 0,
};

static s16 s_PcData_801B22A0[] = {
    1, 256, -22, -11, 16, 8, 0, 0, 16, 8, 32, 16, 0, 0,
};

static s16 s_PcData_801B22BC[] = {
    1, 256, -22, -11, 16, 8, 0, 0, 16, 8, 32, 16, 0, 0,
};

static s16 s_PcData_801B22D8[] = {
    1, 304, -13, -15, 16, 16, 0, 0, 0, 0, 16, 16, 0, 0,
};

static s16 s_PcData_801B22F4[] = {
    1, 272, -18, 0, 56, 8, 0, 0, 0, 16, 56, 24, 0, 0,
};

static s16 s_PcData_801B2310[] = {
    1, 288, 20, 0, 24, 8, 0, 0, 16, 0, 40, 8, 0, 0,
};

static s16 s_PcData_801B232C[] = {
    1, 32, -3, 3, 32, 8, 0, 0, 40, 0, 72, 8, 0, 0,
};

static s16 s_PcData_801B2348[] = {
    1, 0, -19, 5, 16, 8, 0, 0, 16, 8, 32, 16, 0, 0,
};

static s16 s_PcData_801B2364[] = {
    1, 288, -19, -1, 48, 24, 0, 0, 72, 0, 120, 24, 0, 0,
};

static s16 s_PcData_801B2380[] = {
    1, 272, 14, 13, 24, 16, 0, 0, 0, 24, 24, 40, 0, 0,
};

static s16 s_PcData_801B239C[] = {
    1, 0, -4, 7, 32, 16, 0, 0, 24, 24, 56, 40, 0, 0,
};

static s16 s_PcData_801B23B8[] = {
    1, 0, -21, 6, 16, 8, 0, 0, 16, 8, 32, 16, 0, 0,
};

static s16 s_PcData_801B23D4[] = {
    1, 0, -27, 6, 16, 8, 0, 0, 16, 8, 32, 16, 0, 0,
};

static s16 s_PcData_801B23F0[] = {
    1, 256, -28, 6, 16, 8, 0, 0, 16, 8, 32, 16, 0, 0,
};

static s16 s_PcData_801B240C[] = {
    1, 256, -29, 6, 16, 8, 0, 0, 16, 8, 32, 16, 0, 0,
};

static s16 s_PcData_801B2428[] = {
    1, 256, -30, 6, 16, 8, 0, 0, 16, 8, 32, 16, 0, 0,
};

static s16 s_PcData_801B2444[] = {
    1, 304, -9, -33, 16, 16, 0, 0, 0, 0, 16, 16, 0, 0,
};

static s16 s_PcData_801B2460[] = {
    1, 272, -12, -19, 56, 8, 0, 0, 0, 16, 56, 24, 0, 0,
};

static s16 s_PcData_801B247C[] = {
    1, 288, 26, -19, 24, 8, 0, 0, 16, 0, 40, 8, 0, 0,
};

static s16 s_PcData_801B2498[] = {
    1, 32, 1, -16, 32, 8, 0, 0, 40, 0, 72, 8, 0, 0,
};

static s16 s_PcData_801B24B4[] = {
    1, 0, -14, -13, 16, 8, 0, 0, 16, 8, 32, 16, 0, 0,
};

static s16 s_PcData_801B24D0[] = {
    1, 0, -18, -10, 16, 8, 0, 0, 16, 8, 32, 16, 0, 0,
};

static s16 s_PcData_801B24EC[] = {
    1, 304, -17, -35, 16, 16, 0, 0, 0, 0, 16, 16, 0, 0,
};

static s16 s_PcData_801B2508[] = {
    1, 272, -17, -17, 56, 8, 0, 0, 0, 16, 56, 24, 0, 0,
};

static s16 s_PcData_801B2524[] = {
    1, 288, 22, -17, 24, 8, 0, 0, 16, 0, 40, 8, 0, 0,
};

static s16 s_PcData_801B2540[] = {
    1, 32, -2, -14, 32, 8, 0, 0, 40, 0, 72, 8, 0, 0,
};

static s16 s_PcData_801B255C[] = {
    1, 0, -17, -11, 16, 8, 0, 0, 16, 8, 32, 16, 0, 0,
};

static s16 s_PcData_801B2578[] = {
    1, 288, -12, -12, 48, 24, 0, 0, 72, 0, 120, 24, 0, 0,
};

static s16 s_PcData_801B2594[] = {
    1, 272, 21, 2, 24, 16, 0, 0, 0, 24, 24, 40, 0, 0,
};

static s16 s_PcData_801B25B0[] = {
    1, 0, 0, -4, 32, 16, 0, 0, 24, 24, 56, 40, 0, 0,
};

static s16 s_PcData_801B25CC[] = {
    1, 0, -20, -9, 16, 8, 0, 0, 16, 8, 32, 16, 0, 0,
};

static s16 s_PcData_801B25E8[] = {
    1, 256, -27, -11, 16, 8, 0, 0, 16, 8, 32, 16, 0, 0,
};

s16* D_us_801B2140[] = {
    NULL,
    s_PcData_801B21DC,
    s_PcData_801B21F8,
    s_PcData_801B2214,
    s_PcData_801B2230,
    s_PcData_801B224C,
    s_PcData_801B2268,
    s_PcData_801B2284,
    s_PcData_801B22A0,
    s_PcData_801B22BC,
    s_PcData_801B22D8,
    s_PcData_801B22F4,
    s_PcData_801B2310,
    s_PcData_801B232C,
    s_PcData_801B2348,
    s_PcData_801B2364,
    s_PcData_801B2380,
    s_PcData_801B239C,
    s_PcData_801B23B8,
    s_PcData_801B23D4,
    s_PcData_801B23F0,
    s_PcData_801B240C,
    s_PcData_801B2428,
    s_PcData_801B2444,
    s_PcData_801B2460,
    s_PcData_801B247C,
    s_PcData_801B2498,
    s_PcData_801B24B4,
    s_PcData_801B24D0,
    s_PcData_801B24EC,
    s_PcData_801B2508,
    s_PcData_801B2524,
    s_PcData_801B2540,
    s_PcData_801B255C,
    s_PcData_801B2578,
    s_PcData_801B2594,
    s_PcData_801B25B0,
    s_PcData_801B25CC,
    s_PcData_801B25E8,
};

static s16 s_PcData_801B26BC[] = {
    1, 8, -16, -16, 32, 32, 95, 60, 192, 224, 224, 256, 0, 0,
};

static s16 s_PcData_801B26D8[] = {
    1, 12, -8, -48, 16, 104, 95, 60, 240, 152, 256, 256, 0, 0,
};

static s16 s_PcData_801B26F4[] = {
    1, 0, -8, -18, 16, 24, 95, 60, 224, 192, 240, 216, 0, 0,
};

static s16 s_PcData_801B2710[] = {
    2, 8,   -8, -4, 16, 32, 95, 60,  224, 224, 240, 256,
    8, -32, 16, 64, 32, 95, 60, 128, 224, 192, 256, 0,
};

static s16 s_PcData_801B2740[] = {
    1, 0, -32, 32, 64, 16, 95, 56, 48, 104, 112, 120, 0, 0,
};

static s16 s_PcData_801B275C[] = {
    1, 0, -20, -20, 40, 40, 28, 60, 200, 152, 240, 192, 0, 0,
};

static s16 s_PcData_801B2778[] = {
    1, 0, -2, -16, 8, 32, 94, 60, 200, 192, 208, 224, 0, 0,
};

static s16 s_PcData_801B2794[] = {
    1, 0, -2, -16, 8, 32, 94, 60, 208, 192, 216, 224, 0, 0,
};

static s16 s_PcData_801B27B0[] = {
    1, 0, -2, -16, 8, 32, 94, 60, 216, 192, 224, 224, 0, 0,
};

static s16 s_PcData_801B27CC[] = {
    1, 0, -36, -8, 72, 16, 28, 60, 16, 232, 88, 248, 0, 0,
};

static s16 s_PcData_801B27E8[] = {
    1, 8, -9, -8, 24, 16, 28, 56, 104, 240, 128, 256, 0, 0,
};

static s16 s_PcData_801B2804[] = {
    1, 16, -8, -3, 16, 8, 135, 60, 0, 232, 16, 240, 0, 0,
};

static s16 s_PcData_801B2820[] = {
    1, 0, -16, -2, 32, 8, 135, 60, 128, 216, 160, 224, 0, 0,
};

static s16 s_PcData_801B283C[] = {
    1, 0, -16, -2, 32, 8, 135, 60, 160, 216, 192, 224, 0, 0,
};

static s16 s_PcData_801B2858[] = {
    1, 24, -8, -8, 16, 16, 51, 60, 0, 240, 16, 256, 0, 0,
};

static s16 s_PcData_801B2874[] = {
    1, 0, -4, -4, 8, 8, 51, 60, 192, 216, 200, 224, 0, 0,
};

static s16 s_PcData_801B2890[] = {
    1, 4, -64, -1, 128, 8, 94, 60, 128, 128, 256, 136, 0, 0,
};

static s16 s_PcData_801B28AC[] = {
    1, 4, -64, -1, 128, 8, 94, 60, 128, 136, 256, 144, 0, 0,
};

static s16 s_PcData_801B28C8[] = {
    1, 4, -64, -1, 128, 8, 94, 60, 128, 144, 256, 152, 0, 0,
};

static s16 s_PcData_801B28E4[] = {
    1, 0, -40, -8, 72, 16, 94, 60, 128, 152, 200, 168, 0, 0,
};

static s16 s_PcData_801B2900[] = {
    1, 0, -40, -8, 72, 16, 94, 60, 128, 168, 200, 184, 0, 0,
};

static s16 s_PcData_801B291C[] = {
    1, 0, -40, -8, 72, 16, 94, 60, 128, 184, 200, 200, 0, 0,
};

static s16 s_PcData_801B2938[] = {
    1, 0, -40, -8, 72, 16, 94, 60, 128, 200, 200, 216, 0, 0,
};

static s16 s_PcData_801B2954[] = {
    1, 32, -20, -56, 40, 120, 95, 60, 160, 0, 200, 120, 0, 0,
};

static s16 s_PcData_801B2970[] = {
    1, 24, -52, -16, 104, 32, 11, 56, 0, 224, 104, 256, 0, 0,
};

static s16 s_PcData_801B298C[] = {
    1, 16, -44, -16, 88, 32, 11, 56, 0, 192, 88, 224, 0, 0,
};

static s16 s_PcData_801B29A8[] = {
    1, 16, -28, -16, 56, 32, 11, 56, 0, 160, 56, 192, 0, 0,
};

static s16 s_PcData_801B29C4[] = {
    1, 0, 24, -45, 48, 64, 137, 56, 80, 128, 128, 192, 0, 0,
};

static s16 s_PcData_801B29E0[] = {
    1, 16, 25, -43, 48, 64, 137, 56, 0, 56, 48, 120, 0, 0,
};

static s16 s_PcData_801B29FC[] = {
    1, 32, 19, -41, 56, 56, 137, 56, 56, 0, 112, 56, 0, 0,
};

static s16 s_PcData_801B2A18[] = {
    1, 0, 15, -38, 64, 48, 137, 56, 48, 56, 112, 104, 0, 0,
};

static s16 s_PcData_801B2A34[] = {
    1, 48, 19, -41, 56, 56, 137, 56, 0, 0, 56, 56, 0, 0,
};

static s16 s_PcData_801B2A50[] = {
    1, 16, -51, -20, 96, 32, 121, 60, 0, 200, 96, 232, 0, 0,
};

static s16 s_PcData_801B2A6C[] = {
    1, 0, 0, 0, 16, 16, 28, 60, 96, 200, 112, 216, 0, 0,
};

static s16 s_PcData_801B2A88[] = {
    2, 10,  -8, 39, 40, 24, 95, 60, 88,  232, 128, 256,
    8, -32, 39, 40, 24, 95, 60, 88, 232, 128, 256, 0,
};

static s16 s_PcData_801B2AB8[] = {
    3,   16, -32, 61, 64, 32, 95, 56,  0,   128, 64,  160,
    2,   -8, 39,  40, 32, 95, 56, 88,  192, 128, 224, 0,
    -32, 39, 40,  32, 95, 56, 88, 192, 128, 224, 0,   0,
};

static s16 s_PcData_801B2B00[] = {
    1, 16, -8, -33, 16, 72, 9, 60, 0, 56, 16, 128, 0, 0,
};

static s16 s_PcData_801B2B1C[] = {
    1, 0, -8, -8, 16, 16, 70, 60, 112, 200, 128, 216, 0, 0,
};

static s16 s_PcData_801B2B38[] = {
    1, 0, -8, -8, 16, 16, 70, 60, 96, 216, 112, 232, 0, 0,
};

static s16 s_PcData_801B2B54[] = {
    1, 0, -8, -16, 16, 32, 9, 56, 64, 128, 80, 160, 0, 0,
};

s16* D_us_801B2604[] = {
    NULL,
    s_PcData_801B26BC,
    s_PcData_801B26D8,
    s_PcData_801B26F4,
    s_PcData_801B2710,
    s_PcData_801B2740,
    s_PcData_801B275C,
    s_PcData_801B2778,
    s_PcData_801B2794,
    s_PcData_801B27B0,
    s_PcData_801B27CC,
    s_PcData_801B27E8,
    s_PcData_801B2804,
    s_PcData_801B2820,
    s_PcData_801B283C,
    s_PcData_801B2858,
    s_PcData_801B2874,
    s_PcData_801B2890,
    s_PcData_801B28AC,
    s_PcData_801B28C8,
    s_PcData_801B28E4,
    s_PcData_801B2900,
    s_PcData_801B291C,
    s_PcData_801B2938,
    s_PcData_801B2954,
    s_PcData_801B2970,
    s_PcData_801B298C,
    s_PcData_801B29A8,
    s_PcData_801B29C4,
    s_PcData_801B29E0,
    s_PcData_801B29FC,
    s_PcData_801B2A18,
    s_PcData_801B2A34,
    s_PcData_801B2A50,
    s_PcData_801B2A6C,
    s_PcData_801B2A88,
    s_PcData_801B2AB8,
    s_PcData_801B2B00,
    s_PcData_801B2B1C,
    s_PcData_801B2B38,
    s_PcData_801B2B54,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
};

s32 D_us_801D36E8[32] = {0};

s32 D_us_801D3768[33] = {0};

u_long D_us_801D37EC[512] = {0};

s32 D_us_801D3FEC = {0};

s32 D_us_801D43C0 = {0};

s32 D_us_801D43C4 = {0};

PlayerState g_Dop = {0};

static AnimationFrame s_PcData_80182240[] = {
    {2, 569},  {2, 570},  {2, 571},  {3, 572},  {3, 573},   {3, 2110},
    {3, 2111}, {3, 2624}, {2, 2625}, {2, 2114}, {65535, 0},
};

static AnimationFrame s_PcData_8018226C[] = {
    {3, 562}, {3, 563}, {3, 564}, {3, 565},
    {3, 566}, {3, 567}, {3, 568}, {65535, 0},
};

static AnimationFrame s_PcData_80182300[] = {
    {4, 3139}, {4, 3140}, {4, 3141}, {4, 3142},
    {4, 3143}, {4, 3144}, {4, 3145}, {65535, 0},
};

static AnimationFrame s_PcData_80182384[] = {
    {4, 1544}, {4, 1545}, {4, 1546}, {4, 1547},
    {4, 1548}, {4, 1549}, {4, 1550}, {65535, 0},
};

static AnimationFrame s_PcData_80182484[] = {
    {5, 2164}, {5, 2165}, {5, 1142}, {5, 631}, {5, 632}, {65535, 0},
};

static AnimationFrame s_PcData_801828F0[] = {
    {2, 4793}, {1, 4794}, {1, 4794}, {1, 4794},  {1, 4794},
    {1, 4795}, {1, 4795}, {1, 4795}, {2, 4795},  {4, 4796},
    {4, 4797}, {4, 4798}, {4, 4799}, {65535, 0},
};

static AnimationFrame s_PcData_80182990[] = {
    {1, 1735}, {1, 1735}, {1, 1735}, {2, 1735},  {4, 1736},
    {4, 1737}, {4, 1738}, {4, 1739}, {65535, 0},
};

static AnimationFrame s_PcData_80182A1C[] = {
    {1, 3799}, {1, 3799}, {1, 3799}, {2, 3799}, {8, 3800}, {65535, 0},
};

static AnimationFrame s_PcData_80182A58[] = {
    {1, 4793}, {1, 4793}, {1, 4794}, {2, 4794},  {8, 4794},
    {1, 4795}, {1, 4795}, {1, 4795}, {1, 4795},  {4, 4796},
    {4, 4797}, {4, 4798}, {4, 4799}, {65535, 0},
};

static AnimationFrame s_PcData_80182ABC[] = {
    {1, 1735}, {1, 1735}, {1, 1735}, {2, 1735},  {4, 1736},
    {4, 1737}, {4, 1738}, {8, 1739}, {65535, 0},
};

static AnimationFrame s_PcData_801829EC[] = {
    {1, 3794}, {1, 3794}, {1, 3794}, {2, 3794}, {8, 3795}, {65535, 0},
};

static AnimationFrame s_PcData_80182B60[] = {
    {1, 4793}, {1, 4793}, {1, 4794}, {2, 4794}, {2, 4794}, {2, 4794},
    {2, 4794}, {1, 4794}, {1, 4794}, {1, 4795}, {1, 4795}, {1, 4795},
    {1, 4795}, {4, 4796}, {4, 4797}, {4, 4798}, {4, 4799}, {65535, 0},
};

static AnimationFrame s_PcData_80182CA4[] = {
    {2, 4793}, {1, 4793}, {1, 4794}, {2, 4794}, {2, 4794}, {1, 4794},
    {1, 4794}, {1, 4794}, {3, 4794}, {1, 4795}, {1, 4795}, {1, 4795},
    {1, 4795}, {4, 4796}, {4, 4797}, {4, 4798}, {8, 4799}, {65535, 0},
};

static AnimationFrame s_PcData_801828D0[] = {
    {4, 4799}, {6, 704}, {5, 705}, {5, 706},
    {4, 707},  {3, 596}, {3, 597}, {65535, 0},
};

static AnimationFrame s_PcData_80182934[] = {
    {4, 4799}, {5, 599}, {4, 600},  {3, 601},   {3, 602},
    {3, 603},  {3, 604}, {64, 605}, {65535, 0},
};

static AnimationFrame s_PcData_80182978[] = {
    {4, 1739}, {6, 1740}, {5, 1741}, {5, 1742}, {5, 1743}, {64, 1551},
};

static AnimationFrame s_PcData_80182114[] = {
    {4, 531}, {4, 532}, {4, 533}, {4, 534}, {4, 535}, {4, 536}, {65535, 0},
};

static AnimationFrame s_PcData_80182130[] = {
    {5, 531}, {5, 532}, {5, 533}, {5, 534}, {5, 535}, {5, 536}, {65535, 0},
};

static AnimationFrame s_PcData_80182F40[] = {
    {1, 4793}, {1, 4793}, {1, 4794}, {1, 4794},  {1, 4794},
    {1, 4794}, {2, 4795}, {2, 4795}, {2, 4795},  {4, 4796},
    {4, 4797}, {4, 4798}, {8, 4799}, {65535, 0},
};

static AnimationFrame s_PcData_80183168[] = {
    {2, 4793}, {1, 4794}, {3, 4794}, {1, 4795}, {3, 4795},
    {4, 4796}, {4, 4797}, {4, 4798}, {8, 4799}, {65535, 0},
};

static AnimationFrame s_PcData_80183298[] = {
    {2, 4793}, {1, 4794}, {2, 4794}, {1, 4795}, {3, 4795},
    {4, 4796}, {4, 4797}, {4, 4798}, {8, 4799}, {65535, 0},
};

static AnimationFrame s_PcData_80183368[] = {
    {2, 4732}, {2, 4733}, {1, 4734}, {1, 4735},  {2, 4734},
    {2, 4734}, {2, 4733}, {2, 4732}, {1, 4793},  {1, 4793},
    {1, 4794}, {3, 4794}, {1, 4795}, {3, 4795},  {4, 4796},
    {4, 4797}, {4, 4798}, {4, 4799}, {65535, 0},
};

static AnimationFrame s_PcData_80183478[] = {
    {2, 4793}, {1, 4794}, {1, 4794},  {1, 4794}, {1, 4794},
    {1, 4794}, {1, 4795}, {3, 4795},  {4, 4796}, {4, 4797},
    {4, 4798}, {8, 4799}, {65535, 0},
};

static AnimationFrame s_PcData_801835AC[] = {
    {2, 4793}, {1, 4794}, {3, 4794}, {2, 4795}, {2, 4795},
    {4, 4796}, {4, 4797}, {4, 4798}, {8, 4799}, {65535, 0},
};

static AnimationFrame s_PcData_80183650[] = {
    {3, 4793}, {1, 4794}, {4, 4794}, {1, 4795}, {3, 4795},
    {4, 4796}, {4, 4797}, {4, 4798}, {8, 4799}, {65535, 0},
};

static AnimationFrame s_PcData_801836F4[] = {
    {4, 4793}, {2, 4794}, {3, 4794}, {1, 4795}, {3, 4795},
    {4, 4796}, {4, 4797}, {4, 4798}, {8, 4799}, {65535, 0},
};

static AnimationFrame s_PcData_801837E0[] = {
    {1, 4793}, {1, 4793}, {1, 4793}, {1, 4793},  {1, 4794}, {1, 4794},
    {1, 4794}, {1, 4794}, {1, 4794}, {1, 4795},  {3, 4795}, {4, 4796},
    {4, 4797}, {4, 4798}, {8, 4799}, {65535, 0},
};

static AnimationFrame s_PcData_80182784[] = {
    {3, 3765}, {3, 3766}, {3, 3767},  {3, 3768}, {3, 3764}, {4, 3765},
    {4, 3766}, {4, 3767}, {4, 3768},  {4, 3764}, {5, 3765}, {5, 3766},
    {5, 3767}, {5, 3768}, {5, 3764},  {6, 3765}, {6, 3766}, {6, 3767},
    {6, 3768}, {6, 3764}, {65535, 0},
};

static AnimationFrame s_PcData_8018309C[] = {
    {1, 720},  {1, 1232}, {1, 9937}, {1, 2257}, {16, 2257},
    {1, 2234}, {1, 2234}, {1, 2747}, {1, 3259}, {1, 3771},
    {2, 4284}, {2, 4285}, {2, 4286}, {2, 4287}, {65535, 0},
};

AnimationFrame* g_DopAnimationFrames[] = {
    s_PcData_80182240, s_PcData_8018226C, s_PcData_80182300, s_PcData_80182384,
    s_PcData_80182484, s_PcData_801828F0, s_PcData_80182990, s_PcData_80182A1C,
    s_PcData_80182A58, s_PcData_80182ABC, s_PcData_801829EC, s_PcData_80182B60,
    s_PcData_80182CA4, s_PcData_801828D0, s_PcData_80182934, s_PcData_80182978,
    s_PcData_80182114, s_PcData_80182130, s_PcData_80182F40, s_PcData_80183168,
    s_PcData_80183298, s_PcData_80183368, s_PcData_80183478, s_PcData_801835AC,
    s_PcData_80183650, s_PcData_801836F4, s_PcData_801837E0, s_PcData_80182784,
    s_PcData_8018309C,
};

#define pc_rbo5_bat_form_sprites g_PlOvlDopBatSpritesheet
#include "rbo5/gen/pc_rbo5_bat_form.h"
#undef pc_rbo5_bat_form_sprites

#define pc_rbo5_doppleganger_sprites g_SpriteSheet
#include "rbo5/gen/pc_rbo5_doppleganger.h"
#undef pc_rbo5_doppleganger_sprites
