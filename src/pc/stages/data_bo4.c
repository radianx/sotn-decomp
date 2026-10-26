// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../../boss/bo4/bo4.h"
#include <cutscene.h>

static u16 s_PcData_80184098[];
static u16 s_PcData_801840B4[];
static u16 s_PcData_801840D0[];
static u16 s_PcData_801840EC[];
static u16 s_PcData_80184104[];
static u16 s_PcData_8018411C[];
static u16* s_PcData_80184240[];
static s8 s_PcData_80184134[];
static u16 s_PcData_80184198[];
static u16 s_PcData_801841AC[];
static u16 s_PcData_801841C0[];
static u16 s_PcData_801841D4[];
static u16 s_PcData_801841E4[];
static u16 s_PcData_801841F4[];
static u16* s_PcData_8018425C[];
static s8 s_PcData_80184204[];
DopWeaponAnimation D_us_80184278[];
static s16 s_PcData_801B0E9C[];
static s16 s_PcData_801B0EA4[];
static s16 s_PcData_801B0EAC[];
static s16 s_PcData_801B0EB4[];
static s16 s_PcData_801B0EBC[];
static s16 s_PcData_801B0EC4[];
static s16 s_PcData_801B0ECC[];
static s16 s_PcData_801B0ED4[];
static s16 s_PcData_801B0EDC[];
static s16 s_PcData_801B0EE4[];
static s16 s_PcData_801B0EEC[];
static s16 s_PcData_801B0EF4[];
static s16 s_PcData_801B0EFC[];
static s16 s_PcData_801B0F04[];
static s16 s_PcData_801B0F0C[];
static s16 s_PcData_801B0F14[];
static s16 s_PcData_801B0F1C[];
static s16 s_PcData_801B0F24[];
static s16 s_PcData_801B0F2C[];
static s16 s_PcData_801B0F34[];
static s16 s_PcData_801B0F3C[];
static s16 s_PcData_801B0F44[];
static s16 s_PcData_801B0F4C[];
static s16 s_PcData_801B0F54[];
static s16 s_PcData_801B0F5C[];
static s16 s_PcData_801B0F64[];
static s16 s_PcData_801B0F6C[];
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
s16* D_us_801B0A78[];
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
s16* D_us_801B159C[];
static s16 s_PcData_801B17A8[];
static s16 s_PcData_801B17C4[];
static s16 s_PcData_801B17E0[];
static s16 s_PcData_801B17FC[];
static s16 s_PcData_801B1818[];
static s16 s_PcData_801B1834[];
static s16 s_PcData_801B1850[];
static s16 s_PcData_801B186C[];
static s16 s_PcData_801B1888[];
static s16 s_PcData_801B18A4[];
static s16 s_PcData_801B18C0[];
static s16 s_PcData_801B18DC[];
static s16 s_PcData_801B18F8[];
static s16 s_PcData_801B1914[];
static s16 s_PcData_801B1930[];
static s16 s_PcData_801B194C[];
static s16 s_PcData_801B1968[];
static s16 s_PcData_801B1984[];
static s16 s_PcData_801B19A0[];
static s16 s_PcData_801B19BC[];
static s16 s_PcData_801B19D8[];
static s16 s_PcData_801B19F4[];
static s16 s_PcData_801B1A10[];
static s16 s_PcData_801B1A2C[];
static s16 s_PcData_801B1A48[];
static s16 s_PcData_801B1A64[];
static s16 s_PcData_801B1A80[];
static s16 s_PcData_801B1A9C[];
static s16 s_PcData_801B1AB8[];
static s16 s_PcData_801B1AD4[];
static s16 s_PcData_801B1AF0[];
static s16 s_PcData_801B1B0C[];
static s16 s_PcData_801B1B28[];
static s16 s_PcData_801B1B44[];
static s16 s_PcData_801B1B60[];
static s16 s_PcData_801B1B7C[];
static s16 s_PcData_801B1B98[];
static s16 s_PcData_801B1BB4[];
static s16 s_PcData_801B1BD0[];
static s16 s_PcData_801B1BEC[];
static s16 s_PcData_801B1C08[];
static s16 s_PcData_801B1C24[];
static s16 s_PcData_801B1C40[];
static s16 s_PcData_801B1C5C[];
static s16 s_PcData_801B1C78[];
static s16 s_PcData_801B1C94[];
static s16 s_PcData_801B1CB0[];
static s16 s_PcData_801B1CCC[];
static s16 s_PcData_801B1CE8[];
static s16 s_PcData_801B1D04[];
static s16 s_PcData_801B1D20[];
static s16 s_PcData_801B1D3C[];
static s16 s_PcData_801B1D58[];
static s16 s_PcData_801B1D74[];
static s16 s_PcData_801B1D90[];
static s16 s_PcData_801B1DAC[];
static s16 s_PcData_801B1DC8[];
static s16 s_PcData_801B1DE4[];
static s16 s_PcData_801B1E00[];
static s16 s_PcData_801B1E1C[];
static s16 s_PcData_801B1E38[];
static s16 s_PcData_801B1E54[];
static s16 s_PcData_801B1E70[];
static s16 s_PcData_801B1E8C[];
static s16 s_PcData_801B1EA8[];
static s16 s_PcData_801B1EC4[];
static s16 s_PcData_801B1EE0[];
static s16 s_PcData_801B1EFC[];
static s16 s_PcData_801B1F18[];
static s16 s_PcData_801B1F34[];
static s16 s_PcData_801B1F50[];
static s16 s_PcData_801B1F6C[];
static s16 s_PcData_801B1F88[];
static s16 s_PcData_801B1FA4[];
static s16 s_PcData_801B1FC0[];
static s16 s_PcData_801B1FDC[];
static s16 s_PcData_801B1FF8[];
static s16 s_PcData_801B2014[];
static s16 s_PcData_801B2030[];
static s16 s_PcData_801B204C[];
s16* D_us_801B1664[];
static s16 s_PcData_801B2104[];
static s16 s_PcData_801B2120[];
static s16 s_PcData_801B213C[];
static s16 s_PcData_801B2158[];
static s16 s_PcData_801B2174[];
static s16 s_PcData_801B2190[];
static s16 s_PcData_801B21AC[];
static s16 s_PcData_801B21C8[];
static s16 s_PcData_801B21E4[];
static s16 s_PcData_801B2200[];
static s16 s_PcData_801B221C[];
static s16 s_PcData_801B2238[];
static s16 s_PcData_801B2254[];
static s16 s_PcData_801B2270[];
static s16 s_PcData_801B228C[];
static s16 s_PcData_801B22A8[];
static s16 s_PcData_801B22C4[];
static s16 s_PcData_801B22E0[];
static s16 s_PcData_801B22FC[];
static s16 s_PcData_801B2318[];
static s16 s_PcData_801B2334[];
static s16 s_PcData_801B2350[];
static s16 s_PcData_801B236C[];
static s16 s_PcData_801B2388[];
static s16 s_PcData_801B23A4[];
static s16 s_PcData_801B23C0[];
static s16 s_PcData_801B23DC[];
static s16 s_PcData_801B23F8[];
static s16 s_PcData_801B2414[];
static s16 s_PcData_801B2430[];
static s16 s_PcData_801B244C[];
static s16 s_PcData_801B2468[];
static s16 s_PcData_801B2484[];
static s16 s_PcData_801B24A0[];
static s16 s_PcData_801B24BC[];
static s16 s_PcData_801B24D8[];
static s16 s_PcData_801B24F4[];
static s16 s_PcData_801B2510[];
s16* D_us_801B2068[];
static s16 s_PcData_801B2700[];
static s16 s_PcData_801B271C[];
static s16 s_PcData_801B274C[];
static s16 s_PcData_801B277C[];
static s16 s_PcData_801B27AC[];
static s16 s_PcData_801B27DC[];
static s16 s_PcData_801B280C[];
static s16 s_PcData_801B2828[];
static s16 s_PcData_801B2858[];
static s16 s_PcData_801B2888[];
static s16 s_PcData_801B28B8[];
static s16 s_PcData_801B28E8[];
static s16 s_PcData_801B2918[];
static s16 s_PcData_801B2948[];
static s16 s_PcData_801B2978[];
static s16 s_PcData_801B29A8[];
static s16 s_PcData_801B29D8[];
static s16 s_PcData_801B2A08[];
static s16 s_PcData_801B2A50[];
static s16 s_PcData_801B2A98[];
static s16 s_PcData_801B2AE0[];
static s16 s_PcData_801B2B28[];
static s16 s_PcData_801B2B70[];
static s16 s_PcData_801B2BB8[];
static s16 s_PcData_801B2C40[];
static s16 s_PcData_801B2CC8[];
static s16 s_PcData_801B2D50[];
static s16 s_PcData_801B2DD8[];
static s16 s_PcData_801B2E60[];
static s16 s_PcData_801B2EE8[];
static s16 s_PcData_801B2F70[];
static s16 s_PcData_801B2FF8[];
static s16 s_PcData_801B3080[];
static s16 s_PcData_801B30F4[];
static s16 s_PcData_801B3168[];
static s16 s_PcData_801B31DC[];
static s16 s_PcData_801B3224[];
static s16 s_PcData_801B326C[];
static s16 s_PcData_801B32B4[];
static s16 s_PcData_801B32FC[];
static s16 s_PcData_801B3344[];
static s16 s_PcData_801B338C[];
static s16 s_PcData_801B33D4[];
static s16 s_PcData_801B341C[];
static s16 s_PcData_801B3438[];
static s16 s_PcData_801B3454[];
static s16 s_PcData_801B3470[];
static s16 s_PcData_801B348C[];
static s16 s_PcData_801B34D4[];
static s16 s_PcData_801B351C[];
static s16 s_PcData_801B354C[];
static s16 s_PcData_801B357C[];
static s16 s_PcData_801B35C4[];
static s16 s_PcData_801B35E0[];
static s16 s_PcData_801B35FC[];
static s16 s_PcData_801B3618[];
static s16 s_PcData_801B3634[];
static s16 s_PcData_801B3650[];
static s16 s_PcData_801B366C[];
static s16 s_PcData_801B36B4[];
static s16 s_PcData_801B36D0[];
static s16 s_PcData_801B3700[];
static s16 s_PcData_801B3704[];
static s16 s_PcData_801B3708[];
static s16 s_PcData_801B3738[];
static s16 s_PcData_801B3768[];
static s16 s_PcData_801B3798[];
static s16 s_PcData_801B37C8[];
static s16 s_PcData_801B37F8[];
static s16 s_PcData_801B3828[];
static s16 s_PcData_801B3858[];
static s16 s_PcData_801B3874[];
static s16 s_PcData_801B38A4[];
static s16 s_PcData_801B38C0[];
static s16 s_PcData_801B38DC[];
static s16 s_PcData_801B3950[];
static s16 s_PcData_801B39C4[];
static s16 s_PcData_801B3A38[];
static s16 s_PcData_801B3A94[];
static s16 s_PcData_801B3AF0[];
static s16 s_PcData_801B3B20[];
static s16 s_PcData_801B3B3C[];
static s16 s_PcData_801B3B58[];
static s16 s_PcData_801B3B74[];
static s16 s_PcData_801B3B90[];
static s16 s_PcData_801B3BAC[];
static s16 s_PcData_801B3BC8[];
static s16 s_PcData_801B3BE4[];
static s16 s_PcData_801B3C40[];
static s16 s_PcData_801B3C5C[];
static s16 s_PcData_801B3C78[];
static s16 s_PcData_801B3C94[];
static s16 s_PcData_801B3CF0[];
static s16 s_PcData_801B3D4C[];
static s16 s_PcData_801B3D94[];
static s16 s_PcData_801B3DC4[];
static s16 s_PcData_801B3DE0[];
static s16 s_PcData_801B3DFC[];
static s16 s_PcData_801B3E18[];
static s16 s_PcData_801B3E34[];
static s16 s_PcData_801B3E50[];
static s16 s_PcData_801B3E6C[];
static s16 s_PcData_801B3E88[];
static s16 s_PcData_801B3EB8[];
static s16 s_PcData_801B3ED4[];
static s16 s_PcData_801B3EF0[];
static s16 s_PcData_801B3F20[];
static s16 s_PcData_801B3F68[];
static s16 s_PcData_801B3FB0[];
static s16 s_PcData_801B3FCC[];
static s16 s_PcData_801B3FE8[];
static s16 s_PcData_801B4004[];
static s16 s_PcData_801B4020[];
static s16 s_PcData_801B4050[];
static s16 s_PcData_801B406C[];
static s16 s_PcData_801B409C[];
s16* D_us_801B252C[];

static u16 s_PcData_80184098[] = {
    513,  1026, 1027, 1028, 1029, 1542, 1543,
    1544, 1545, 2058, 2059, 2060, 2061, 65535,
};

static u16 s_PcData_801840B4[] = {
    2574, 3087, 3088, 3089, 3090, 3603, 3604,
    3605, 3606, 2079, 2080, 2081, 2082, 65535,
};

static u16 s_PcData_801840D0[] = {
    2574, 4119, 4632, 4121, 4634, 5147, 5148,
    5149, 5150, 2079, 2080, 2081, 2082, 65535,
};

static u16 s_PcData_801840EC[] = {
    5667, 6180, 6181, 6182, 6183, 6696, 6697, 6698, 6699, 2092, 65535, 0,
};

static u16 s_PcData_80184104[] = {
    7213, 7726, 7727, 7728, 7729, 8242, 8243, 8244, 8245, 2110, 65535, 0,
};

static u16 s_PcData_8018411C[] = {
    7213, 8758, 8759, 8760, 8761, 9274, 9275, 9276, 9277, 2110, 65535, 0,
};

static u16* s_PcData_80184240[] = {
    s_PcData_80184098, s_PcData_80184098, s_PcData_801840B4, s_PcData_801840D0,
    s_PcData_801840EC, s_PcData_80184104, s_PcData_8018411C,
};

static s8 s_PcData_80184134[] = {
    0,   0,   0,   0,   4,   -23, 8,  5,  30,  -17, 35, 8,  30,  -14, 18,
    4,   -32, -31, 0,   0,   -4,  -6, 8,  5,   22,  0,  35, 8,   22,  3,
    18,  4,   29,  22,  13,  11,  12, 7,  19,  12,  14, 14, 18,  4,   1,
    -25, 8,   5,   27,  -19, 35,  8,  27, -16, 18,  4,  -8, -26, 8,   5,
    24,  -17, 35,  8,   24,  -14, 18, 4,  23,  0,   27, 14, 18,  2,   21,
    11,  29,  -14, 34,  4,   21,  3,  34, 4,   28,  21, 12, 10,  26,  -16,
    34,  4,   23,  -14, 34,  4,   22, 3,  26,  10,
};

static u16 s_PcData_80184198[] = {
    513, 1026, 1027, 1540, 1541, 1542, 1543, 1544, 1545, 65535,
};

static u16 s_PcData_801841AC[] = {
    2058, 2571, 2572, 1549, 1550, 1555, 1556, 1557, 1558, 65535,
};

static u16 s_PcData_801841C0[] = {
    2058, 3087, 3600, 4113, 1554, 1555, 1556, 1557, 1558, 65535,
};

static u16 s_PcData_801841D4[] = {
    4631, 5144, 5145, 1562, 1563, 1564, 65535, 0,
};

static u16 s_PcData_801841E4[] = {
    5661, 6174, 6175, 1568, 1569, 1574, 65535, 0,
};

static u16 s_PcData_801841F4[] = {
    5661, 6690, 7203, 1572, 1573, 1574, 65535, 0,
};

static u16* s_PcData_8018425C[] = {
    s_PcData_80184198, s_PcData_80184198, s_PcData_801841AC, s_PcData_801841C0,
    s_PcData_801841D4, s_PcData_801841E4, s_PcData_801841F4,
};

static s8 s_PcData_80184204[] = {
    0,   0,  0,  0,  3,   -24, 5,  4,   25, -13, 24, 3,   -32, -31, 0,
    0,   -5, -5, 5,  4,   17,  4,  24,  3,  7,   15, 14,  8,   19,  21,
    15,  7,  13, 18, 17,  5,   -1, -25, 5,  4,   23, -15, 24,  7,   -9,
    -27, 5,  4,  19, -14, 24,  7,  15,  2,  19,  10, 29,  8,   11,  8,
};

DopWeaponAnimation D_us_80184278[] = {
    {s_PcData_80184240, s_PcData_80184134, 1547, 65, 4},
    {s_PcData_8018425C, s_PcData_80184204, 1547, 167, 4},
};

static s16 s_PcData_801B0E9C[] = {
    -32768,
    -16,
    -23,
    0,
};

static s16 s_PcData_801B0EA4[] = {
    -32767,
    -40,
    -31,
    0,
};

static s16 s_PcData_801B0EAC[] = {
    -32766,
    -40,
    -31,
    0,
};

static s16 s_PcData_801B0EB4[] = {
    -32765,
    -40,
    -31,
    0,
};

static s16 s_PcData_801B0EBC[] = {
    -32764,
    -40,
    -31,
    0,
};

static s16 s_PcData_801B0EC4[] = {
    -32763,
    -40,
    -31,
    0,
};

static s16 s_PcData_801B0ECC[] = {
    -32762,
    -40,
    -31,
    0,
};

static s16 s_PcData_801B0ED4[] = {
    -32761,
    -40,
    -31,
    0,
};

static s16 s_PcData_801B0EDC[] = {
    -32760,
    -32,
    -15,
    0,
};

static s16 s_PcData_801B0EE4[] = {
    -32759,
    -32,
    -7,
    0,
};

static s16 s_PcData_801B0EEC[] = {
    -32758,
    -32,
    -7,
    0,
};

static s16 s_PcData_801B0EF4[] = {
    -32757,
    -32,
    -7,
    0,
};

static s16 s_PcData_801B0EFC[] = {
    -32756,
    -32,
    -7,
    0,
};

static s16 s_PcData_801B0F04[] = {
    -32755,
    -24,
    -7,
    0,
};

static s16 s_PcData_801B0F0C[] = {
    -32754,
    -24,
    -7,
    0,
};

static s16 s_PcData_801B0F14[] = {
    -32753,
    -16,
    -15,
    0,
};

static s16 s_PcData_801B0F1C[] = {
    -32752,
    -16,
    -23,
    0,
};

static s16 s_PcData_801B0F24[] = {
    -32751,
    -16,
    -23,
    0,
};

static s16 s_PcData_801B0F2C[] = {
    -32750,
    -16,
    -23,
    0,
};

static s16 s_PcData_801B0F34[] = {
    -32749,
    -16,
    -23,
    0,
};

static s16 s_PcData_801B0F3C[] = {
    -32748,
    -16,
    -23,
    0,
};

static s16 s_PcData_801B0F44[] = {
    -32747,
    -16,
    -23,
    0,
};

static s16 s_PcData_801B0F4C[] = {
    -32746,
    -16,
    -23,
    0,
};

static s16 s_PcData_801B0F54[] = {
    -32745,
    -16,
    -23,
    0,
};

static s16 s_PcData_801B0F5C[] = {
    -32744,
    -16,
    -23,
    0,
};

static s16 s_PcData_801B0F64[] = {
    -32743,
    -16,
    -23,
    0,
};

static s16 s_PcData_801B0F6C[] = {
    -32742,
    -16,
    -23,
    0,
};

static s16 s_PcData_801B0F74[] = {
    -32741,
    -16,
    -23,
    0,
};

static s16 s_PcData_801B0F7C[] = {
    -32740,
    -16,
    -23,
    0,
};

static s16 s_PcData_801B0F84[] = {
    -32739,
    -32,
    -31,
    0,
};

static s16 s_PcData_801B0F8C[] = {
    -32738,
    -32,
    -31,
    0,
};

static s16 s_PcData_801B0F94[] = {
    -32737,
    -32,
    -31,
    0,
};

static s16 s_PcData_801B0F9C[] = {
    -32736,
    -32,
    -31,
    0,
};

static s16 s_PcData_801B0FA4[] = {
    -32735,
    -32,
    -31,
    0,
};

static s16 s_PcData_801B0FAC[] = {
    -32734,
    -32,
    -31,
    0,
};

static s16 s_PcData_801B0FB4[] = {
    -32733,
    -32,
    -31,
    0,
};

static s16 s_PcData_801B0FBC[] = {
    -32732,
    -32,
    -31,
    0,
};

static s16 s_PcData_801B0FC4[] = {
    -32731,
    -32,
    -31,
    0,
};

static s16 s_PcData_801B0FCC[] = {
    -32730,
    -32,
    -31,
    0,
};

static s16 s_PcData_801B0FD4[] = {
    -32729,
    -32,
    -31,
    0,
};

static s16 s_PcData_801B0FDC[] = {
    -32728,
    -24,
    -23,
    0,
};

static s16 s_PcData_801B0FE4[] = {
    -32727,
    -32,
    -31,
    0,
};

static s16 s_PcData_801B0FEC[] = {
    -32726,
    -32,
    -31,
    0,
};

static s16 s_PcData_801B0FF4[] = {
    -32725,
    -32,
    -31,
    0,
};

static s16 s_PcData_801B0FFC[] = {
    -32724,
    -32,
    -31,
    0,
};

static s16 s_PcData_801B1004[] = {
    -32723,
    -32,
    -31,
    0,
};

static s16 s_PcData_801B100C[] = {
    -32722,
    -32,
    -31,
    0,
};

static s16 s_PcData_801B1014[] = {
    -32721,
    -32,
    -31,
    0,
};

static s16 s_PcData_801B101C[] = {
    -32720,
    -32,
    -31,
    0,
};

static s16 s_PcData_801B1024[] = {
    -32719,
    -32,
    -31,
    0,
};

static s16 s_PcData_801B102C[] = {
    -32718,
    -32,
    -31,
    0,
};

static s16 s_PcData_801B1034[] = {
    -32717,
    -32,
    -31,
    0,
};

static s16 s_PcData_801B103C[] = {
    -32716,
    -32,
    -31,
    0,
};

static s16 s_PcData_801B1044[] = {
    -32715,
    -32,
    -31,
    0,
};

static s16 s_PcData_801B104C[] = {
    -32714,
    -32,
    -31,
    0,
};

static s16 s_PcData_801B1054[] = {
    -32713,
    -32,
    -31,
    0,
};

static s16 s_PcData_801B105C[] = {
    -32712,
    -32,
    -31,
    0,
};

static s16 s_PcData_801B1064[] = {
    -32711,
    -32,
    -31,
    0,
};

static s16 s_PcData_801B106C[] = {
    -32710,
    -32,
    -31,
    0,
};

static s16 s_PcData_801B1074[] = {
    -32709,
    -32,
    -31,
    0,
};

static s16 s_PcData_801B107C[] = {
    -32708,
    -32,
    -31,
    0,
};

static s16 s_PcData_801B1084[] = {
    -32707,
    -32,
    -31,
    0,
};

static s16 s_PcData_801B108C[] = {
    -32706,
    -32,
    -31,
    0,
};

static s16 s_PcData_801B1094[] = {
    -32705,
    -32,
    -31,
    0,
};

static s16 s_PcData_801B109C[] = {
    -32704,
    -32,
    -31,
    0,
};

static s16 s_PcData_801B10A4[] = {
    -32703,
    -32,
    -31,
    0,
};

static s16 s_PcData_801B10AC[] = {
    -32702,
    -32,
    -23,
    0,
};

static s16 s_PcData_801B10B4[] = {
    -32701,
    -32,
    -31,
    0,
};

static s16 s_PcData_801B10BC[] = {
    -32700,
    -32,
    -31,
    0,
};

static s16 s_PcData_801B10C4[] = {
    -32699,
    -32,
    -31,
    0,
};

static s16 s_PcData_801B10CC[] = {
    -32698,
    -32,
    -31,
    0,
};

static s16 s_PcData_801B10D4[] = {
    -32697,
    -32,
    -31,
    0,
};

static s16 s_PcData_801B10DC[] = {
    -32696,
    -32,
    -31,
    0,
};

static s16 s_PcData_801B10E4[] = {
    -32695,
    -32,
    -31,
    0,
};

static s16 s_PcData_801B10EC[] = {
    -32694,
    -32,
    -31,
    0,
};

static s16 s_PcData_801B10F4[] = {
    -32693,
    -32,
    -31,
    0,
};

static s16 s_PcData_801B10FC[] = {
    -32692,
    -32,
    -31,
    0,
};

static s16 s_PcData_801B1104[] = {
    -32691,
    -32,
    -31,
    0,
};

static s16 s_PcData_801B110C[] = {
    -32690,
    -32,
    -31,
    0,
};

static s16 s_PcData_801B1114[] = {
    -32689,
    -32,
    -23,
    0,
};

static s16 s_PcData_801B111C[] = {
    -32688,
    -32,
    -31,
    0,
};

static s16 s_PcData_801B1124[] = {
    -32687,
    -32,
    -31,
    0,
};

static s16 s_PcData_801B112C[] = {
    -32686,
    -32,
    -31,
    0,
};

static s16 s_PcData_801B1134[] = {
    -32685,
    -32,
    -31,
    0,
};

static s16 s_PcData_801B113C[] = {
    -32684,
    -32,
    -31,
    0,
};

static s16 s_PcData_801B1144[] = {
    -32683,
    -32,
    -23,
    0,
};

static s16 s_PcData_801B114C[] = {
    -32682,
    -32,
    -31,
    0,
};

static s16 s_PcData_801B1154[] = {
    -32681,
    -32,
    -31,
    0,
};

static s16 s_PcData_801B115C[] = {
    -32680,
    -32,
    -31,
    0,
};

static s16 s_PcData_801B1164[] = {
    -32679,
    -32,
    -31,
    0,
};

static s16 s_PcData_801B116C[] = {
    -32678,
    -32,
    -31,
    0,
};

static s16 s_PcData_801B1174[] = {
    -32677,
    -32,
    -31,
    0,
};

static s16 s_PcData_801B117C[] = {
    -32676,
    -32,
    -31,
    0,
};

static s16 s_PcData_801B1184[] = {
    -32675,
    -32,
    -31,
    0,
};

static s16 s_PcData_801B118C[] = {
    -32674,
    -16,
    -31,
    0,
};

static s16 s_PcData_801B1194[] = {
    -32673,
    -16,
    -31,
    0,
};

static s16 s_PcData_801B119C[] = {
    -32672,
    -16,
    -31,
    0,
};

static s16 s_PcData_801B11A4[] = {
    -32671,
    -16,
    -31,
    0,
};

static s16 s_PcData_801B11AC[] = {
    -32670,
    -32,
    -31,
    0,
};

static s16 s_PcData_801B11B4[] = {
    -32669,
    -32,
    -31,
    0,
};

static s16 s_PcData_801B11BC[] = {
    -32668,
    -32,
    -31,
    0,
};

static s16 s_PcData_801B11C4[] = {
    -32667,
    -32,
    -31,
    0,
};

static s16 s_PcData_801B11CC[] = {
    -32666,
    -16,
    -31,
    0,
};

static s16 s_PcData_801B11D4[] = {
    -32665,
    -16,
    -31,
    0,
};

static s16 s_PcData_801B11DC[] = {
    -32664,
    -16,
    -31,
    0,
};

static s16 s_PcData_801B11E4[] = {
    -32663,
    -40,
    -31,
    0,
};

static s16 s_PcData_801B11EC[] = {
    -32662,
    -40,
    -31,
    0,
};

static s16 s_PcData_801B11F4[] = {
    -32661,
    -40,
    -31,
    0,
};

static s16 s_PcData_801B11FC[] = {
    -32660,
    -40,
    -31,
    0,
};

static s16 s_PcData_801B1204[] = {
    -32659,
    -40,
    -31,
    0,
};

static s16 s_PcData_801B120C[] = {
    -32658,
    -40,
    -31,
    0,
};

static s16 s_PcData_801B1214[] = {
    -32657,
    -40,
    -31,
    0,
};

static s16 s_PcData_801B121C[] = {
    -32656,
    -40,
    -39,
    0,
};

static s16 s_PcData_801B1224[] = {
    -32655,
    -40,
    -39,
    0,
};

static s16 s_PcData_801B122C[] = {
    -32654,
    -40,
    -39,
    0,
};

static s16 s_PcData_801B1234[] = {
    -32653,
    -32,
    -31,
    0,
};

static s16 s_PcData_801B123C[] = {
    -32652,
    -32,
    -31,
    0,
};

static s16 s_PcData_801B1244[] = {
    -32651,
    -32,
    -31,
    0,
};

static s16 s_PcData_801B124C[] = {
    -32650,
    -32,
    -31,
    0,
};

static s16 s_PcData_801B1254[] = {
    -32649,
    -32,
    -31,
    0,
};

static s16 s_PcData_801B125C[] = {
    -32648,
    -16,
    -23,
    0,
};

static s16 s_PcData_801B1264[] = {
    -32647,
    -16,
    -23,
    0,
};

static s16 s_PcData_801B126C[] = {
    -32646,
    -16,
    -23,
    0,
};

static s16 s_PcData_801B1274[] = {
    -32645,
    -8,
    -31,
    0,
};

static s16 s_PcData_801B127C[] = {
    -32644,
    -8,
    -31,
    0,
};

static s16 s_PcData_801B1284[] = {
    -32643,
    -8,
    -31,
    0,
};

static s16 s_PcData_801B128C[] = {
    -32642,
    -8,
    -31,
    0,
};

static s16 s_PcData_801B1294[] = {
    -32641,
    -8,
    -31,
    0,
};

static s16 s_PcData_801B129C[] = {
    -32640,
    -16,
    -7,
    0,
};

static s16 s_PcData_801B12A4[] = {
    -32639,
    -16,
    -7,
    0,
};

static s16 s_PcData_801B12AC[] = {
    -32638,
    -24,
    -5,
    0,
};

static s16 s_PcData_801B12B4[] = {
    -32637,
    -24,
    -5,
    0,
};

static s16 s_PcData_801B12BC[] = {
    -32636,
    -40,
    -31,
    0,
};

static s16 s_PcData_801B12C4[] = {
    -32635,
    -40,
    -31,
    0,
};

static s16 s_PcData_801B12CC[] = {
    -32634,
    -40,
    -31,
    0,
};

static s16 s_PcData_801B12D4[] = {
    -32633,
    -40,
    -39,
    0,
};

static s16 s_PcData_801B12DC[] = {
    -32632,
    -32,
    -39,
    0,
};

static s16 s_PcData_801B12E4[] = {
    -32631,
    -32,
    -39,
    0,
};

static s16 s_PcData_801B12EC[] = {
    -32630,
    -40,
    -39,
    0,
};

static s16 s_PcData_801B12F4[] = {
    -32629,
    -16,
    -31,
    0,
};

static s16 s_PcData_801B12FC[] = {
    -32628,
    -24,
    -39,
    0,
};

static s16 s_PcData_801B1304[] = {
    -32627,
    -16,
    -31,
    0,
};

static s16 s_PcData_801B130C[] = {
    -32626,
    -16,
    -31,
    0,
};

static s16 s_PcData_801B1314[] = {
    -32625,
    -16,
    -31,
    0,
};

static s16 s_PcData_801B131C[] = {
    -32624,
    -16,
    -31,
    0,
};

static s16 s_PcData_801B1324[] = {
    -32623,
    -16,
    -31,
    0,
};

static s16 s_PcData_801B132C[] = {
    -32622,
    -24,
    -23,
    0,
};

static s16 s_PcData_801B1334[] = {
    -32621,
    -24,
    -23,
    0,
};

static s16 s_PcData_801B133C[] = {
    -32620,
    -24,
    -23,
    0,
};

static s16 s_PcData_801B1344[] = {
    -32619,
    -24,
    -23,
    0,
};

static s16 s_PcData_801B134C[] = {
    -32618,
    -32,
    -31,
    0,
};

static s16 s_PcData_801B1354[] = {
    -32617,
    -32,
    -79,
    0,
};

static s16 s_PcData_801B135C[] = {
    -32616,
    -24,
    -31,
    0,
};

static s16 s_PcData_801B1364[] = {
    -32615,
    -32,
    -23,
    0,
};

static s16 s_PcData_801B136C[] = {
    -32614,
    -32,
    -23,
    0,
};

static s16 s_PcData_801B1374[] = {
    -32613,
    -24,
    -23,
    0,
};

static s16 s_PcData_801B137C[] = {
    -32612,
    -16,
    -23,
    0,
};

static s16 s_PcData_801B1384[] = {
    -32611,
    -27,
    -27,
    0,
};

static s16 s_PcData_801B138C[] = {
    -32610,
    -16,
    -31,
    0,
};

static s16 s_PcData_801B1394[] = {
    -32610,
    -16,
    -32,
    0,
};

static s16 s_PcData_801B139C[] = {
    -32609,
    -16,
    -31,
    0,
};

static s16 s_PcData_801B13A4[] = {
    -32608,
    -16,
    -31,
    0,
};

static s16 s_PcData_801B13AC[] = {
    -32607,
    -16,
    -31,
    0,
};

static s16 s_PcData_801B13B4[] = {
    -32607,
    -16,
    -32,
    0,
};

static s16 s_PcData_801B13BC[] = {
    -32606,
    -32,
    -31,
    0,
};

static s16 s_PcData_801B13C4[] = {
    -32606,
    -33,
    -31,
    0,
};

static s16 s_PcData_801B13CC[] = {
    -32605,
    -32,
    -31,
    0,
};

static s16 s_PcData_801B13D4[] = {
    -32605,
    -33,
    -31,
    0,
};

static s16 s_PcData_801B13DC[] = {
    -32604,
    -32,
    -31,
    0,
};

static s16 s_PcData_801B13E4[] = {
    -32604,
    -31,
    -31,
    0,
};

static s16 s_PcData_801B13EC[] = {
    -32603,
    -32,
    -31,
    0,
};

static s16 s_PcData_801B13F4[] = {
    -32603,
    -31,
    -31,
    0,
};

static s16 s_PcData_801B13FC[] = {
    -32602,
    -24,
    -23,
    158,
};

static s16 s_PcData_801B1404[] = {
    -32601,
    -11,
    -23,
    159,
};

static s16 s_PcData_801B140C[] = {
    -32600,
    -73,
    -47,
    158,
};

static s16 s_PcData_801B1414[] = {
    -32599,
    -32,
    -31,
    0,
};

static s16 s_PcData_801B141C[] = {
    -32598,
    -40,
    -31,
    0,
};

static s16 s_PcData_801B1424[] = {
    -32597,
    -40,
    -31,
    0,
};

static s16 s_PcData_801B142C[] = {
    -32596,
    -40,
    -31,
    0,
};

static s16 s_PcData_801B1434[] = {
    -32595,
    -32,
    -31,
    0,
};

static s16 s_PcData_801B143C[] = {
    -32594,
    -32,
    -31,
    0,
};

static s16 s_PcData_801B1444[] = {
    -32593,
    -32,
    -31,
    0,
};

static s16 s_PcData_801B144C[] = {
    -32592,
    -32,
    -31,
    0,
};

static s16 s_PcData_801B1454[] = {
    -32591,
    -32,
    -31,
    0,
};

static s16 s_PcData_801B145C[] = {
    -32590,
    -24,
    -31,
    0,
};

static s16 s_PcData_801B1464[] = {
    -32589,
    -32,
    -23,
    0,
};

static s16 s_PcData_801B146C[] = {
    -32588,
    -24,
    -23,
    0,
};

static s16 s_PcData_801B1474[] = {
    -32587,
    -24,
    -31,
    0,
};

static s16 s_PcData_801B147C[] = {
    -32586,
    -24,
    -31,
    0,
};

static s16 s_PcData_801B1484[] = {
    -32585,
    -16,
    -23,
    0,
};

static s16 s_PcData_801B148C[] = {
    -32584,
    -16,
    -23,
    0,
};

static s16 s_PcData_801B1494[] = {
    -32583,
    -8,
    -23,
    0,
};

static s16 s_PcData_801B149C[] = {
    -32582,
    -8,
    -23,
    0,
};

static s16 s_PcData_801B14A4[] = {
    -32581,
    -16,
    -23,
    0,
};

static s16 s_PcData_801B14AC[] = {
    -32580,
    -16,
    -23,
    0,
};

static s16 s_PcData_801B14B4[] = {
    -32579,
    -24,
    -7,
    0,
};

static s16 s_PcData_801B14BC[] = {
    -32578,
    -32,
    -7,
    0,
};

static s16 s_PcData_801B14C4[] = {
    -32577,
    -32,
    -7,
    0,
};

static s16 s_PcData_801B14CC[] = {
    -32576,
    -32,
    -7,
    0,
};

static s16 s_PcData_801B14D4[] = {
    -32575,
    -32,
    -15,
    0,
};

static s16 s_PcData_801B14DC[] = {
    -32574,
    -24,
    -7,
    0,
};

static s16 s_PcData_801B14E4[] = {
    -32573,
    -24,
    -7,
    0,
};

static s16 s_PcData_801B14EC[] = {
    -32572,
    -24,
    -7,
    0,
};

static s16 s_PcData_801B14F4[] = {
    -32571,
    -16,
    -7,
    0,
};

static s16 s_PcData_801B14FC[] = {
    -32570,
    -16,
    -7,
    0,
};

static s16 s_PcData_801B1504[] = {
    -32569,
    -16,
    -7,
    0,
};

static s16 s_PcData_801B150C[] = {
    -32568,
    -16,
    -7,
    0,
};

static s16 s_PcData_801B1514[] = {
    -32567,
    -32,
    -31,
    0,
};

static s16 s_PcData_801B151C[] = {
    -32566,
    -40,
    -31,
    0,
};

static s16 s_PcData_801B1524[] = {
    -32565,
    -32,
    -23,
    0,
};

static s16 s_PcData_801B152C[] = {
    -32564,
    -32,
    -23,
    0,
};

static s16 s_PcData_801B1534[] = {
    -32563,
    -40,
    -39,
    0,
};

static s16 s_PcData_801B153C[] = {
    -32562,
    -32,
    -39,
    0,
};

static s16 s_PcData_801B1544[] = {
    -32561,
    -32,
    -39,
    0,
};

static s16 s_PcData_801B154C[] = {
    -32560,
    -32,
    -47,
    0,
};

static s16 s_PcData_801B1554[] = {
    -32559,
    -32,
    -47,
    0,
};

static s16 s_PcData_801B155C[] = {
    -32558,
    -24,
    -15,
    0,
};

static s16 s_PcData_801B1564[] = {
    -32557,
    -18,
    -22,
    0,
};

static s16 s_PcData_801B156C[] = {
    -32556,
    -16,
    -22,
    0,
};

static s16 s_PcData_801B1574[] = {
    -32555,
    -14,
    -22,
    0,
};

static s16 s_PcData_801B157C[] = {
    -32554,
    -21,
    -21,
    0,
};

static s16 s_PcData_801B1584[] = {
    -32553,
    -19,
    -21,
    0,
};

static s16 s_PcData_801B158C[] = {
    -32552,
    -19,
    -21,
    0,
};

static s16 s_PcData_801B1594[] = {
    -32551,
    -12,
    -20,
    0,
};

s16* D_us_801B0A78[] = {
    NULL,
    s_PcData_801B0E9C,
    s_PcData_801B0EA4,
    s_PcData_801B0EAC,
    s_PcData_801B0EB4,
    s_PcData_801B0EBC,
    s_PcData_801B0EC4,
    s_PcData_801B0ECC,
    s_PcData_801B0ED4,
    s_PcData_801B0EDC,
    s_PcData_801B0EE4,
    s_PcData_801B0EEC,
    s_PcData_801B0EF4,
    s_PcData_801B0EFC,
    s_PcData_801B0F04,
    s_PcData_801B0F0C,
    s_PcData_801B0F14,
    s_PcData_801B0F1C,
    s_PcData_801B0F24,
    s_PcData_801B0F2C,
    s_PcData_801B0F34,
    s_PcData_801B0F3C,
    s_PcData_801B0F44,
    s_PcData_801B0F4C,
    s_PcData_801B0F54,
    s_PcData_801B0F5C,
    s_PcData_801B0F64,
    s_PcData_801B0F6C,
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
    s_PcData_801B1564,
    s_PcData_801B1564,
    s_PcData_801B1564,
    s_PcData_801B1564,
    s_PcData_801B1564,
    s_PcData_801B1564,
    s_PcData_801B1564,
    s_PcData_801B1564,
    s_PcData_801B1564,
    s_PcData_801B1564,
    s_PcData_801B1564,
    s_PcData_801B1564,
    s_PcData_801B1564,
    s_PcData_801B1564,
    s_PcData_801B1564,
    s_PcData_801B1564,
    s_PcData_801B1564,
    s_PcData_801B1564,
    s_PcData_801B1564,
    s_PcData_801B1564,
    s_PcData_801B1564,
    s_PcData_801B1564,
    s_PcData_801B1564,
    s_PcData_801B1564,
    s_PcData_801B1564,
    s_PcData_801B1564,
    s_PcData_801B1564,
    s_PcData_801B1564,
    s_PcData_801B1564,
    s_PcData_801B1564,
    s_PcData_801B1564,
    s_PcData_801B1564,
    s_PcData_801B1564,
    s_PcData_801B1564,
    s_PcData_801B1564,
    s_PcData_801B1564,
    s_PcData_801B1564,
    s_PcData_801B1564,
    s_PcData_801B1564,
    NULL,
};

static s16 s_PcData_801B15E4[] = {
    -32768,
    -22,
    -48,
    0,
};

static s16 s_PcData_801B15EC[] = {
    -32767,
    -22,
    -47,
    0,
};

static s16 s_PcData_801B15F4[] = {
    -32766,
    -22,
    -40,
    0,
};

static s16 s_PcData_801B15FC[] = {
    -32765,
    -22,
    -41,
    0,
};

static s16 s_PcData_801B1604[] = {
    -32764,
    -22,
    -30,
    0,
};

static s16 s_PcData_801B160C[] = {
    -32764,
    -22,
    -31,
    0,
};

static s16 s_PcData_801B1614[] = {
    -32763,
    -22,
    -30,
    0,
};

static s16 s_PcData_801B161C[] = {
    -32765,
    -22,
    -41,
    0,
};

static s16 s_PcData_801B1624[] = {
    -32766,
    -22,
    -41,
    0,
};

static s16 s_PcData_801B162C[] = {
    -32767,
    -22,
    -49,
    0,
};

static s16 s_PcData_801B1634[] = {
    -32768,
    -22,
    -51,
    0,
};

static s16 s_PcData_801B163C[] = {
    -32767,
    -22,
    -51,
    0,
};

static s16 s_PcData_801B1644[] = {
    -32766,
    -22,
    -42,
    0,
};

static s16 s_PcData_801B164C[] = {
    -32765,
    -22,
    -41,
    0,
};

static s16 s_PcData_801B1654[] = {
    -32764,
    -22,
    -29,
    0,
};

static s16 s_PcData_801B165C[] = {
    -32763,
    -22,
    -29,
    0,
};

s16* D_us_801B159C[] = {
    NULL,
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
    NULL,
};

static s16 s_PcData_801B17A8[] = {
    1, 256, -8, -31, 24, 16, 0, 0, 64, 24, 88, 40, 0, 0,
};

static s16 s_PcData_801B17C4[] = {
    1, 304, -10, -31, 80, 24, 0, 0, 0, 0, 80, 24, 0, 0,
};

static s16 s_PcData_801B17E0[] = {
    1, 304, -10, -31, 80, 24, 1, 0, 0, 0, 80, 24, 0, 0,
};

static s16 s_PcData_801B17FC[] = {
    1, 304, -10, -31, 80, 24, 2, 0, 0, 0, 80, 24, 0, 0,
};

static s16 s_PcData_801B1818[] = {
    1, 304, -10, -31, 80, 24, 3, 0, 0, 0, 80, 24, 0, 0,
};

static s16 s_PcData_801B1834[] = {
    1, 16, 11, -23, 40, 16, 0, 0, 0, 24, 40, 40, 0, 0,
};

static s16 s_PcData_801B1850[] = {
    1, 16, 11, -23, 40, 16, 1, 0, 0, 24, 40, 40, 0, 0,
};

static s16 s_PcData_801B186C[] = {
    1, 16, 11, -23, 40, 16, 2, 0, 0, 24, 40, 40, 0, 0,
};

static s16 s_PcData_801B1888[] = {
    1, 16, 11, -23, 40, 16, 3, 0, 0, 24, 40, 40, 0, 0,
};

static s16 s_PcData_801B18A4[] = {
    1, 0, -21, -15, 16, 16, 0, 0, 40, 24, 56, 40, 0, 0,
};

static s16 s_PcData_801B18C0[] = {
    1, 0, -21, -15, 16, 16, 0, 0, 40, 24, 56, 40, 0, 0,
};

static s16 s_PcData_801B18DC[] = {
    1, 0, -22, -15, 16, 16, 0, 0, 40, 24, 56, 40, 0, 0,
};

static s16 s_PcData_801B18F8[] = {
    1, 0, -22, -15, 16, 16, 0, 0, 40, 24, 56, 40, 0, 0,
};

static s16 s_PcData_801B1914[] = {
    1, 256, -16, -14, 24, 16, 0, 0, 64, 24, 88, 40, 0, 0,
};

static s16 s_PcData_801B1930[] = {
    1, 304, -18, -14, 80, 24, 0, 0, 0, 0, 80, 24, 0, 0,
};

static s16 s_PcData_801B194C[] = {
    1, 304, -18, -14, 80, 24, 1, 0, 0, 0, 80, 24, 0, 0,
};

static s16 s_PcData_801B1968[] = {
    1, 304, -18, -14, 80, 24, 2, 0, 0, 0, 80, 24, 0, 0,
};

static s16 s_PcData_801B1984[] = {
    1, 304, -18, -14, 80, 24, 3, 0, 0, 0, 80, 24, 0, 0,
};

static s16 s_PcData_801B19A0[] = {
    1, 16, 3, -6, 40, 16, 0, 0, 0, 24, 40, 40, 0, 0,
};

static s16 s_PcData_801B19BC[] = {
    1, 16, 3, -6, 40, 16, 1, 0, 0, 24, 40, 40, 0, 0,
};

static s16 s_PcData_801B19D8[] = {
    1, 16, 3, -6, 40, 16, 2, 0, 0, 24, 40, 40, 0, 0,
};

static s16 s_PcData_801B19F4[] = {
    1, 16, 3, -6, 40, 16, 3, 0, 0, 24, 40, 40, 0, 0,
};

static s16 s_PcData_801B1A10[] = {
    1, 272, -16, -15, 64, 56, 0, 0, 0, 40, 64, 96, 0, 0,
};

static s16 s_PcData_801B1A2C[] = {
    1, 272, -16, -15, 64, 56, 1, 0, 0, 40, 64, 96, 0, 0,
};

static s16 s_PcData_801B1A48[] = {
    1, 272, -16, -15, 64, 56, 2, 0, 0, 40, 64, 96, 0, 0,
};

static s16 s_PcData_801B1A64[] = {
    1, 272, -16, -15, 64, 56, 3, 0, 0, 40, 64, 96, 0, 0,
};

static s16 s_PcData_801B1A80[] = {
    1, 0, -12, -2, 48, 32, 0, 0, 64, 40, 112, 72, 0, 0,
};

static s16 s_PcData_801B1A9C[] = {
    1, 0, -12, -2, 48, 32, 1, 0, 64, 40, 112, 72, 0, 0,
};

static s16 s_PcData_801B1AB8[] = {
    1, 0, -12, -2, 48, 32, 2, 0, 64, 40, 112, 72, 0, 0,
};

static s16 s_PcData_801B1AD4[] = {
    1, 0, -12, -2, 48, 32, 3, 0, 64, 40, 112, 72, 0, 0,
};

static s16 s_PcData_801B1AF0[] = {
    1, 0, -29, 2, 16, 16, 0, 0, 40, 24, 56, 40, 0, 0,
};

static s16 s_PcData_801B1B0C[] = {
    1, 0, -29, 2, 16, 16, 0, 0, 40, 24, 56, 40, 0, 0,
};

static s16 s_PcData_801B1B28[] = {
    1, 0, -30, 2, 16, 16, 0, 0, 40, 24, 56, 40, 0, 0,
};

static s16 s_PcData_801B1B44[] = {
    1, 0, -30, 2, 16, 16, 0, 0, 40, 24, 56, 40, 0, 0,
};

static s16 s_PcData_801B1B60[] = {
    1, 256, -11, -33, 24, 16, 0, 0, 64, 24, 88, 40, 0, 0,
};

static s16 s_PcData_801B1B7C[] = {
    1, 304, -13, -33, 80, 24, 0, 0, 0, 0, 80, 24, 0, 0,
};

static s16 s_PcData_801B1B98[] = {
    1, 304, -13, -33, 80, 24, 1, 0, 0, 0, 80, 24, 0, 0,
};

static s16 s_PcData_801B1BB4[] = {
    1, 304, -13, -33, 80, 24, 2, 0, 0, 0, 80, 24, 0, 0,
};

static s16 s_PcData_801B1BD0[] = {
    1, 304, -13, -33, 80, 24, 3, 0, 0, 0, 80, 24, 0, 0,
};

static s16 s_PcData_801B1BEC[] = {
    1, 16, 8, -25, 40, 16, 0, 0, 0, 24, 40, 40, 0, 0,
};

static s16 s_PcData_801B1C08[] = {
    1, 16, 8, -25, 40, 16, 1, 0, 0, 24, 40, 40, 0, 0,
};

static s16 s_PcData_801B1C24[] = {
    1, 16, 8, -25, 40, 16, 2, 0, 0, 24, 40, 40, 0, 0,
};

static s16 s_PcData_801B1C40[] = {
    1, 16, 8, -25, 40, 16, 3, 0, 0, 24, 40, 40, 0, 0,
};

static s16 s_PcData_801B1C5C[] = {
    1, 0, -24, -17, 16, 16, 0, 0, 40, 24, 56, 40, 0, 0,
};

static s16 s_PcData_801B1C78[] = {
    1, 256, -20, -34, 24, 16, 0, 0, 64, 24, 88, 40, 0, 0,
};

static s16 s_PcData_801B1C94[] = {
    1, 304, -16, -31, 80, 24, 0, 0, 0, 0, 80, 24, 0, 0,
};

static s16 s_PcData_801B1CB0[] = {
    1, 304, -16, -31, 80, 24, 1, 0, 0, 0, 80, 24, 0, 0,
};

static s16 s_PcData_801B1CCC[] = {
    1, 304, -16, -31, 80, 24, 2, 0, 0, 0, 80, 24, 0, 0,
};

static s16 s_PcData_801B1CE8[] = {
    1, 304, -16, -31, 80, 24, 3, 0, 0, 0, 80, 24, 0, 0,
};

static s16 s_PcData_801B1D04[] = {
    1, 16, 5, -23, 40, 16, 0, 0, 0, 24, 40, 40, 0, 0,
};

static s16 s_PcData_801B1D20[] = {
    1, 16, 5, -23, 40, 16, 1, 0, 0, 24, 40, 40, 0, 0,
};

static s16 s_PcData_801B1D3C[] = {
    1, 16, 5, -23, 40, 16, 2, 0, 0, 24, 40, 40, 0, 0,
};

static s16 s_PcData_801B1D58[] = {
    1, 16, 5, -23, 40, 16, 3, 0, 0, 24, 40, 40, 0, 0,
};

static s16 s_PcData_801B1D74[] = {
    1, 272, -9, -26, 64, 56, 1, 0, 0, 40, 64, 96, 0, 0,
};

static s16 s_PcData_801B1D90[] = {
    1, 272, -9, -26, 64, 56, 1, 0, 0, 40, 64, 96, 0, 0,
};

static s16 s_PcData_801B1DAC[] = {
    1, 272, -9, -26, 64, 56, 2, 0, 0, 40, 64, 96, 0, 0,
};

static s16 s_PcData_801B1DC8[] = {
    1, 272, -9, -26, 64, 56, 3, 0, 0, 40, 64, 96, 0, 0,
};

static s16 s_PcData_801B1DE4[] = {
    1, 0, -5, -13, 48, 32, 0, 0, 64, 40, 112, 72, 0, 0,
};

static s16 s_PcData_801B1E00[] = {
    1, 0, -5, -13, 48, 32, 1, 0, 64, 40, 112, 72, 0, 0,
};

static s16 s_PcData_801B1E1C[] = {
    1, 0, -5, -13, 48, 32, 2, 0, 64, 40, 112, 72, 0, 0,
};

static s16 s_PcData_801B1E38[] = {
    1, 0, -5, -13, 48, 32, 3, 0, 64, 40, 112, 72, 0, 0,
};

static s16 s_PcData_801B1E54[] = {
    1, 0, -27, -15, 16, 16, 0, 0, 40, 24, 56, 40, 0, 0,
};

static s16 s_PcData_801B1E70[] = {
    1, 304, -10, -31, 80, 24, 4, 0, 0, 0, 80, 24, 0, 0,
};

static s16 s_PcData_801B1E8C[] = {
    1, 304, -10, -31, 80, 24, 5, 0, 0, 0, 80, 24, 0, 0,
};

static s16 s_PcData_801B1EA8[] = {
    1, 304, -10, -31, 80, 24, 6, 0, 0, 0, 80, 24, 0, 0,
};

static s16 s_PcData_801B1EC4[] = {
    1, 304, -18, -14, 80, 24, 4, 0, 0, 0, 80, 24, 0, 0,
};

static s16 s_PcData_801B1EE0[] = {
    1, 304, -18, -14, 80, 24, 5, 0, 0, 0, 80, 24, 0, 0,
};

static s16 s_PcData_801B1EFC[] = {
    1, 304, -18, -14, 80, 24, 6, 0, 0, 0, 80, 24, 0, 0,
};

static s16 s_PcData_801B1F18[] = {
    1, 272, -16, -15, 64, 56, 4, 0, 0, 40, 64, 96, 0, 0,
};

static s16 s_PcData_801B1F34[] = {
    1, 272, -16, -15, 64, 56, 5, 0, 0, 40, 64, 96, 0, 0,
};

static s16 s_PcData_801B1F50[] = {
    1, 272, -16, -15, 64, 56, 6, 0, 0, 40, 64, 96, 0, 0,
};

static s16 s_PcData_801B1F6C[] = {
    1, 304, -13, -33, 80, 24, 4, 0, 0, 0, 80, 24, 0, 0,
};

static s16 s_PcData_801B1F88[] = {
    1, 304, -13, -33, 80, 24, 5, 0, 0, 0, 80, 24, 0, 0,
};

static s16 s_PcData_801B1FA4[] = {
    1, 304, -13, -33, 80, 24, 6, 0, 0, 0, 80, 24, 0, 0,
};

static s16 s_PcData_801B1FC0[] = {
    1, 304, -16, -31, 80, 24, 4, 0, 0, 0, 80, 24, 0, 0,
};

static s16 s_PcData_801B1FDC[] = {
    1, 304, -16, -31, 80, 24, 5, 0, 0, 0, 80, 24, 0, 0,
};

static s16 s_PcData_801B1FF8[] = {
    1, 304, -16, -31, 80, 24, 6, 0, 0, 0, 80, 24, 0, 0,
};

static s16 s_PcData_801B2014[] = {
    1, 272, -9, -26, 64, 56, 4, 0, 0, 40, 64, 96, 0, 0,
};

static s16 s_PcData_801B2030[] = {
    1, 272, -9, -26, 64, 56, 5, 0, 0, 40, 64, 96, 0, 0,
};

static s16 s_PcData_801B204C[] = {
    1, 272, -9, -26, 64, 56, 6, 0, 0, 40, 64, 96, 0, 0,
};

s16* D_us_801B1664[] = {
    NULL,
    s_PcData_801B17A8,
    s_PcData_801B17C4,
    s_PcData_801B17E0,
    s_PcData_801B17FC,
    s_PcData_801B1818,
    s_PcData_801B1834,
    s_PcData_801B1850,
    s_PcData_801B186C,
    s_PcData_801B1888,
    s_PcData_801B18A4,
    s_PcData_801B18C0,
    s_PcData_801B18DC,
    s_PcData_801B18F8,
    s_PcData_801B1914,
    s_PcData_801B1930,
    s_PcData_801B194C,
    s_PcData_801B1968,
    s_PcData_801B1984,
    s_PcData_801B19A0,
    s_PcData_801B19BC,
    s_PcData_801B19D8,
    s_PcData_801B19F4,
    s_PcData_801B1A10,
    s_PcData_801B1A2C,
    s_PcData_801B1A48,
    s_PcData_801B1A64,
    s_PcData_801B1A80,
    s_PcData_801B1A9C,
    s_PcData_801B1AB8,
    s_PcData_801B1AD4,
    s_PcData_801B1AF0,
    s_PcData_801B1B0C,
    s_PcData_801B1B28,
    s_PcData_801B1B44,
    s_PcData_801B1B60,
    s_PcData_801B1B7C,
    s_PcData_801B1B98,
    s_PcData_801B1BB4,
    s_PcData_801B1BD0,
    s_PcData_801B1BEC,
    s_PcData_801B1C08,
    s_PcData_801B1C24,
    s_PcData_801B1C40,
    s_PcData_801B1C5C,
    s_PcData_801B1C78,
    s_PcData_801B1C94,
    s_PcData_801B1CB0,
    s_PcData_801B1CCC,
    s_PcData_801B1CE8,
    s_PcData_801B1D04,
    s_PcData_801B1D20,
    s_PcData_801B1D3C,
    s_PcData_801B1D58,
    s_PcData_801B1D74,
    s_PcData_801B1D90,
    s_PcData_801B1DAC,
    s_PcData_801B1DC8,
    s_PcData_801B1DE4,
    s_PcData_801B1E00,
    s_PcData_801B1E1C,
    s_PcData_801B1E38,
    s_PcData_801B1E54,
    s_PcData_801B1E70,
    s_PcData_801B1E8C,
    s_PcData_801B1EA8,
    s_PcData_801B1EC4,
    s_PcData_801B1EE0,
    s_PcData_801B1EFC,
    s_PcData_801B1F18,
    s_PcData_801B1F34,
    s_PcData_801B1F50,
    s_PcData_801B1F6C,
    s_PcData_801B1F88,
    s_PcData_801B1FA4,
    s_PcData_801B1FC0,
    s_PcData_801B1FDC,
    s_PcData_801B1FF8,
    s_PcData_801B2014,
    s_PcData_801B2030,
    s_PcData_801B204C,
};

static s16 s_PcData_801B2104[] = {
    1, 304, -5, -32, 16, 16, 0, 0, 0, 0, 16, 16, 0, 0,
};

static s16 s_PcData_801B2120[] = {
    1, 272, -10, -17, 56, 8, 0, 0, 0, 16, 56, 24, 0, 0,
};

static s16 s_PcData_801B213C[] = {
    1, 288, 28, -17, 24, 8, 0, 0, 16, 0, 40, 8, 0, 0,
};

static s16 s_PcData_801B2158[] = {
    1, 32, 5, -15, 32, 8, 0, 0, 40, 0, 72, 8, 0, 0,
};

static s16 s_PcData_801B2174[] = {
    1, 0, -12, -12, 16, 8, 0, 0, 16, 8, 32, 16, 0, 0,
};

static s16 s_PcData_801B2190[] = {
    1, 0, -20, -11, 16, 8, 0, 0, 16, 8, 32, 16, 0, 0,
};

static s16 s_PcData_801B21AC[] = {
    1, 256, -21, -11, 16, 8, 0, 0, 16, 8, 32, 16, 0, 0,
};

static s16 s_PcData_801B21C8[] = {
    1, 256, -22, -11, 16, 8, 0, 0, 16, 8, 32, 16, 0, 0,
};

static s16 s_PcData_801B21E4[] = {
    1, 256, -22, -11, 16, 8, 0, 0, 16, 8, 32, 16, 0, 0,
};

static s16 s_PcData_801B2200[] = {
    1, 304, -13, -15, 16, 16, 0, 0, 0, 0, 16, 16, 0, 0,
};

static s16 s_PcData_801B221C[] = {
    1, 272, -18, 0, 56, 8, 0, 0, 0, 16, 56, 24, 0, 0,
};

static s16 s_PcData_801B2238[] = {
    1, 288, 20, 0, 24, 8, 0, 0, 16, 0, 40, 8, 0, 0,
};

static s16 s_PcData_801B2254[] = {
    1, 32, -3, 3, 32, 8, 0, 0, 40, 0, 72, 8, 0, 0,
};

static s16 s_PcData_801B2270[] = {
    1, 0, -19, 5, 16, 8, 0, 0, 16, 8, 32, 16, 0, 0,
};

static s16 s_PcData_801B228C[] = {
    1, 288, -19, -1, 48, 24, 0, 0, 72, 0, 120, 24, 0, 0,
};

static s16 s_PcData_801B22A8[] = {
    1, 272, 14, 13, 24, 16, 0, 0, 0, 24, 24, 40, 0, 0,
};

static s16 s_PcData_801B22C4[] = {
    1, 0, -4, 7, 32, 16, 0, 0, 24, 24, 56, 40, 0, 0,
};

static s16 s_PcData_801B22E0[] = {
    1, 0, -21, 6, 16, 8, 0, 0, 16, 8, 32, 16, 0, 0,
};

static s16 s_PcData_801B22FC[] = {
    1, 0, -27, 6, 16, 8, 0, 0, 16, 8, 32, 16, 0, 0,
};

static s16 s_PcData_801B2318[] = {
    1, 256, -28, 6, 16, 8, 0, 0, 16, 8, 32, 16, 0, 0,
};

static s16 s_PcData_801B2334[] = {
    1, 256, -29, 6, 16, 8, 0, 0, 16, 8, 32, 16, 0, 0,
};

static s16 s_PcData_801B2350[] = {
    1, 256, -30, 6, 16, 8, 0, 0, 16, 8, 32, 16, 0, 0,
};

static s16 s_PcData_801B236C[] = {
    1, 304, -9, -33, 16, 16, 0, 0, 0, 0, 16, 16, 0, 0,
};

static s16 s_PcData_801B2388[] = {
    1, 272, -12, -19, 56, 8, 0, 0, 0, 16, 56, 24, 0, 0,
};

static s16 s_PcData_801B23A4[] = {
    1, 288, 26, -19, 24, 8, 0, 0, 16, 0, 40, 8, 0, 0,
};

static s16 s_PcData_801B23C0[] = {
    1, 32, 1, -16, 32, 8, 0, 0, 40, 0, 72, 8, 0, 0,
};

static s16 s_PcData_801B23DC[] = {
    1, 0, -14, -13, 16, 8, 0, 0, 16, 8, 32, 16, 0, 0,
};

static s16 s_PcData_801B23F8[] = {
    1, 0, -18, -10, 16, 8, 0, 0, 16, 8, 32, 16, 0, 0,
};

static s16 s_PcData_801B2414[] = {
    1, 304, -17, -35, 16, 16, 0, 0, 0, 0, 16, 16, 0, 0,
};

static s16 s_PcData_801B2430[] = {
    1, 272, -17, -17, 56, 8, 0, 0, 0, 16, 56, 24, 0, 0,
};

static s16 s_PcData_801B244C[] = {
    1, 288, 22, -17, 24, 8, 0, 0, 16, 0, 40, 8, 0, 0,
};

static s16 s_PcData_801B2468[] = {
    1, 32, -2, -14, 32, 8, 0, 0, 40, 0, 72, 8, 0, 0,
};

static s16 s_PcData_801B2484[] = {
    1, 0, -17, -11, 16, 8, 0, 0, 16, 8, 32, 16, 0, 0,
};

static s16 s_PcData_801B24A0[] = {
    1, 288, -12, -12, 48, 24, 0, 0, 72, 0, 120, 24, 0, 0,
};

static s16 s_PcData_801B24BC[] = {
    1, 272, 21, 2, 24, 16, 0, 0, 0, 24, 24, 40, 0, 0,
};

static s16 s_PcData_801B24D8[] = {
    1, 0, 0, -4, 32, 16, 0, 0, 24, 24, 56, 40, 0, 0,
};

static s16 s_PcData_801B24F4[] = {
    1, 0, -20, -9, 16, 8, 0, 0, 16, 8, 32, 16, 0, 0,
};

static s16 s_PcData_801B2510[] = {
    1, 256, -27, -11, 16, 8, 0, 0, 16, 8, 32, 16, 0, 0,
};

s16* D_us_801B2068[] = {
    NULL,
    s_PcData_801B2104,
    s_PcData_801B2120,
    s_PcData_801B213C,
    s_PcData_801B2158,
    s_PcData_801B2174,
    s_PcData_801B2190,
    s_PcData_801B21AC,
    s_PcData_801B21C8,
    s_PcData_801B21E4,
    s_PcData_801B2200,
    s_PcData_801B221C,
    s_PcData_801B2238,
    s_PcData_801B2254,
    s_PcData_801B2270,
    s_PcData_801B228C,
    s_PcData_801B22A8,
    s_PcData_801B22C4,
    s_PcData_801B22E0,
    s_PcData_801B22FC,
    s_PcData_801B2318,
    s_PcData_801B2334,
    s_PcData_801B2350,
    s_PcData_801B236C,
    s_PcData_801B2388,
    s_PcData_801B23A4,
    s_PcData_801B23C0,
    s_PcData_801B23DC,
    s_PcData_801B23F8,
    s_PcData_801B2414,
    s_PcData_801B2430,
    s_PcData_801B244C,
    s_PcData_801B2468,
    s_PcData_801B2484,
    s_PcData_801B24A0,
    s_PcData_801B24BC,
    s_PcData_801B24D8,
    s_PcData_801B24F4,
    s_PcData_801B2510,
};

static s16 s_PcData_801B2700[] = {
    1, 36, -44, -48, 88, 96, 58, 60, 168, 0, 256, 96, 0, 0,
};

static s16 s_PcData_801B271C[] = {
    2, 32,  -15, -29, 24, 32, 61, 60,  128, 0,   152, 32,
    0, -13, -3,  32,  24, 61, 60, 128, 96,  160, 120, 0,
};

static s16 s_PcData_801B274C[] = {
    2, 0,   -8, -20, 24, 24, 61, 60,  128, 32,  152, 56,
    0, -13, -4, 32,  24, 61, 60, 128, 96,  160, 120, 0,
};

static s16 s_PcData_801B277C[] = {
    2, 0,   -13, -10, 32, 16, 61, 60,  128, 80,  160, 96,
    0, -13, -5,  32,  24, 61, 60, 128, 96,  160, 120, 0,
};

static s16 s_PcData_801B27AC[] = {
    2, 0,   -8, -6, 24, 24, 61, 60,  128, 56,  152, 80,
    0, -13, -6, 32, 24, 61, 60, 128, 96,  160, 120, 0,
};

static s16 s_PcData_801B27DC[] = {
    2, 32,  -6, -7, 16, 32, 61, 60,  152, 0,   168, 32,
    0, -13, -8, 32, 24, 61, 60, 128, 96,  160, 120, 0,
};

static s16 s_PcData_801B280C[] = {
    1, 0, -16, -8, 32, 16, 61, 60, 96, 144, 128, 160, 0, 0,
};

static s16 s_PcData_801B2828[] = {
    2, 0,  -16, -8, 32, 16, 61, 60,  96,  144, 128, 160,
    0, -8, -12, 16, 16, 61, 60, 112, 160, 128, 176, 0,
};

static s16 s_PcData_801B2858[] = {
    2,  0,   -16, -8, 32, 16, 61, 60, 96,  144, 128, 160,
    16, -10, -28, 24, 32, 61, 60, 0,  184, 24,  216, 0,
};

static s16 s_PcData_801B2888[] = {
    2,  0,   -16, -8, 32, 16, 61, 60, 96,  144, 128, 160,
    16, -10, -28, 24, 32, 61, 60, 0,  216, 24,  248, 0,
};

static s16 s_PcData_801B28B8[] = {
    2, 0,   -16, -8, 32, 16, 61, 60, 96,  144, 128, 160,
    0, -10, -20, 24, 24, 61, 60, 24, 184, 48,  208, 0,
};

static s16 s_PcData_801B28E8[] = {
    2, 0,   -16, -8, 32, 16, 61, 60, 96,  144, 128, 160,
    0, -11, -20, 24, 24, 61, 60, 24, 208, 48,  232, 0,
};

static s16 s_PcData_801B2918[] = {
    2, 0,   -16, -8, 32, 16, 61, 60, 96,  144, 128, 160,
    8, -12, -20, 24, 24, 61, 60, 24, 232, 48,  256, 0,
};

static s16 s_PcData_801B2948[] = {
    2, 0,   -16, -8, 32, 16, 61, 60, 96,  144, 128, 160,
    0, -11, -20, 24, 24, 61, 60, 48, 184, 72,  208, 0,
};

static s16 s_PcData_801B2978[] = {
    2, 0,   -16, -8, 32, 16, 61, 60, 96,  144, 128, 160,
    0, -12, -19, 24, 24, 61, 60, 48, 208, 72,  232, 0,
};

static s16 s_PcData_801B29A8[] = {
    2, 0,   -16, -8, 32, 16, 61, 60, 96,  144, 128, 160,
    8, -12, -19, 24, 24, 61, 60, 48, 232, 72,  256, 0,
};

static s16 s_PcData_801B29D8[] = {
    2, 0,   -16, -8, 32, 16, 61, 60, 96,  144, 128, 160,
    0, -12, -17, 24, 24, 61, 60, 72, 184, 96,  208, 0,
};

static s16 s_PcData_801B2A08[] = {
    3,   0,   -16, -8, 32, 16, 61, 60,  96,  144, 128, 160,
    0,   -8,  -12, 16, 16, 61, 60, 112, 160, 128, 176, 16,
    -10, -28, 24,  32, 61, 60, 0,  184, 24,  216, 0,   0,
};

static s16 s_PcData_801B2A50[] = {
    3,   0,   -16, -8, 32, 16, 61, 60,  96,  144, 128, 160,
    0,   -8,  -12, 16, 16, 61, 60, 112, 160, 128, 176, 16,
    -10, -28, 24,  32, 61, 60, 0,  216, 24,  248, 0,   0,
};

static s16 s_PcData_801B2A98[] = {
    3,   0,   -16, -8, 32, 16, 61, 60,  96,  144, 128, 160,
    0,   -8,  -12, 16, 16, 61, 60, 112, 160, 128, 176, 0,
    -10, -20, 24,  24, 61, 60, 24, 184, 48,  208, 0,   0,
};

static s16 s_PcData_801B2AE0[] = {
    3,   0,   -16, -8, 32, 16, 61, 60,  96,  144, 128, 160,
    0,   -7,  -12, 16, 16, 61, 60, 112, 160, 128, 176, 0,
    -11, -20, 24,  24, 61, 60, 24, 208, 48,  232, 0,   0,
};

static s16 s_PcData_801B2B28[] = {
    3,  0,   -16, -8, 32, 16, 61,  60,  96,  144, 128, 160,
    8,  -12, -20, 24, 24, 61, 60,  24,  232, 48,  256, 0,
    -7, -12, 16,  16, 61, 60, 112, 160, 128, 176, 0,   0,
};

static s16 s_PcData_801B2B70[] = {
    3,  0,   -16, -8, 32, 16, 61,  60,  96,  144, 128, 160,
    0,  -11, -20, 24, 24, 61, 60,  48,  184, 72,  208, 0,
    -7, -12, 16,  16, 61, 60, 112, 160, 128, 176, 0,   0,
};

static s16 s_PcData_801B2BB8[] = {
    6,   8,   4,   -5,  8,   8,   61,  60, 8,   248, 16,  256, 24,  -11,
    -7,  8,   8,   61,  60,  0,   248, 8,  256, 0,   -16, -8,  32,  16,
    61,  60,  96,  144, 128, 160, 0,   -7, -6,  8,   8,   61,  60,  96,
    160, 104, 168, 0,   -2,  -6,  8,   8,  61,  60,  104, 160, 112, 168,
    16,  -10, -28, 24,  32,  61,  60,  0,  184, 24,  216, 0,
};

static s16 s_PcData_801B2C40[] = {
    6,   8,   4,   -5,  8,   8,   61,  60, 8,   248, 16,  256, 24,  -11,
    -7,  8,   8,   61,  60,  0,   248, 8,  256, 0,   -16, -8,  32,  16,
    61,  60,  96,  144, 128, 160, 0,   -2, -6,  8,   8,   61,  60,  104,
    160, 112, 168, 0,   -7,  -6,  8,   8,  61,  60,  96,  160, 104, 168,
    16,  -10, -28, 24,  32,  61,  60,  0,  216, 24,  248, 0,
};

static s16 s_PcData_801B2CC8[] = {
    6,   8,   4,   -5,  8,   8,   61,  60, 8,   248, 16,  256, 24,  -11,
    -7,  8,   8,   61,  60,  0,   248, 8,  256, 0,   -16, -8,  32,  16,
    61,  60,  96,  144, 128, 160, 0,   -2, -6,  8,   8,   61,  60,  104,
    168, 112, 176, 0,   -7,  -6,  8,   8,  61,  60,  96,  168, 104, 176,
    0,   -10, -20, 24,  24,  61,  60,  24, 184, 48,  208, 0,
};

static s16 s_PcData_801B2D50[] = {
    6,   8,   4,   -5,  8,   8,   61,  60, 8,   248, 16,  256, 24,  -11,
    -7,  8,   8,   61,  60,  0,   248, 8,  256, 0,   -16, -8,  32,  16,
    61,  60,  96,  144, 128, 160, 0,   -2, -6,  8,   8,   61,  60,  104,
    160, 112, 168, 0,   -7,  -6,  8,   8,  61,  60,  96,  160, 104, 168,
    0,   -11, -20, 24,  24,  61,  60,  24, 208, 48,  232, 0,
};

static s16 s_PcData_801B2DD8[] = {
    6,   8,   4,   -5,  8,   8,   61,  60, 8,   248, 16,  256, 24, -11,
    -7,  8,   8,   61,  60,  0,   248, 8,  256, 0,   -16, -8,  32, 16,
    61,  60,  96,  144, 128, 160, 0,   -2, -6,  8,   8,   61,  60, 104,
    168, 112, 176, 8,   -12, -20, 24,  24, 61,  60,  24,  232, 48, 256,
    0,   -7,  -6,  8,   8,   61,  60,  96, 160, 104, 168, 0,
};

static s16 s_PcData_801B2E60[] = {
    6,   8,  4,   -5,  8,   8,   61,  60,  8,   248, 16,  256, 24,  -11,
    -7,  8,  8,   61,  60,  0,   248, 8,   256, 0,   -16, -8,  32,  16,
    61,  60, 96,  144, 128, 160, 0,   -11, -20, 24,  24,  61,  60,  48,
    184, 72, 208, 0,   -2,  -6,  8,   8,   61,  60,  104, 160, 112, 168,
    0,   -7, -6,  8,   8,   61,  60,  96,  168, 104, 176, 0,
};

static s16 s_PcData_801B2EE8[] = {
    6,   8,  4,   -5,  8,   8,   61,  60,  8,   248, 16,  256, 24,  -11,
    -7,  8,  8,   61,  60,  0,   248, 8,   256, 0,   -16, -8,  32,  16,
    61,  60, 96,  144, 128, 160, 0,   -12, -19, 24,  24,  61,  60,  48,
    208, 72, 232, 0,   -7,  -6,  8,   8,   61,  60,  96,  160, 104, 168,
    0,   -2, -6,  8,   8,   61,  60,  104, 160, 112, 168, 0,
};

static s16 s_PcData_801B2F70[] = {
    6,   8,  4,   -5,  8,   8,   61,  60,  8,   248, 16,  256, 24,  -11,
    -7,  8,  8,   61,  60,  0,   248, 8,   256, 0,   -16, -8,  32,  16,
    61,  60, 96,  144, 128, 160, 8,   -12, -19, 24,  24,  61,  60,  48,
    232, 72, 256, 0,   -2,  -6,  8,   8,   61,  60,  104, 168, 112, 176,
    0,   -7, -6,  8,   8,   61,  60,  96,  160, 104, 168, 0,
};

static s16 s_PcData_801B2FF8[] = {
    6,   8,  4,   -5,  8,   8,   61,  60,  8,   248, 16,  256, 24,  -11,
    -7,  8,  8,   61,  60,  0,   248, 8,   256, 0,   -16, -8,  32,  16,
    61,  60, 96,  144, 128, 160, 0,   -12, -17, 24,  24,  61,  60,  72,
    184, 96, 208, 0,   -2,  -6,  8,   8,   61,  60,  104, 160, 112, 168,
    0,   -7, -6,  8,   8,   61,  60,  96,  168, 104, 176, 0,
};

static s16 s_PcData_801B3080[] = {
    5,  8,   4,   -5,  8, 8,   61, 60,  8,   248, 16,  256, 24,  -11, -7,
    8,  8,   61,  60,  0, 248, 8,  256, 0,   -16, -8,  32,  16,  61,  60,
    96, 144, 128, 160, 0, -7,  -6, 8,   8,   61,  60,  96,  160, 104, 168,
    0,  -2,  -6,  8,   8, 61,  60, 104, 160, 112, 168, 0,   0,
};

static s16 s_PcData_801B30F4[] = {
    5,  8,   4,   -5,  8, 8,   61, 60,  8,   248, 16,  256, 24,  -11, -7,
    8,  8,   61,  60,  0, 248, 8,  256, 0,   -16, -8,  32,  16,  61,  60,
    96, 144, 128, 160, 0, -2,  -6, 8,   8,   61,  60,  104, 168, 112, 176,
    0,  -7,  -6,  8,   8, 61,  60, 96,  160, 104, 168, 0,   0,
};

static s16 s_PcData_801B3168[] = {
    5,  8,   4,   -5,  8, 8,   61, 60,  8,   248, 16,  256, 24,  -11, -7,
    8,  8,   61,  60,  0, 248, 8,  256, 0,   -16, -8,  32,  16,  61,  60,
    96, 144, 128, 160, 0, -2,  -6, 8,   8,   61,  60,  104, 160, 112, 168,
    0,  -7,  -6,  8,   8, 61,  60, 96,  168, 104, 176, 0,   0,
};

static s16 s_PcData_801B31DC[] = {
    3,   0,   -16, -8, 32, 16, 61, 60,  96,  144, 128, 160,
    0,   -4,  -12, 16, 16, 61, 60, 112, 128, 128, 144, 0,
    -11, -12, 16,  16, 61, 60, 96, 128, 112, 144, 0,   0,
};

static s16 s_PcData_801B3224[] = {
    3,   0,   -16, -8, 32, 16, 61,  60,  96,  144, 128, 160,
    0,   -4,  -12, 16, 16, 61, 60,  96,  128, 112, 144, 0,
    -11, -12, 16,  16, 61, 60, 112, 128, 128, 144, 0,   0,
};

static s16 s_PcData_801B326C[] = {
    3,   0,   -16, -8, 32, 16, 61, 60,  96,  144, 128, 160,
    0,   -4,  -12, 16, 16, 61, 60, 96,  128, 112, 144, 0,
    -11, -12, 16,  16, 61, 60, 96, 128, 112, 144, 0,   0,
};

static s16 s_PcData_801B32B4[] = {
    3,   0,   -16, -8, 32, 16, 61,  60,  96,  144, 128, 160,
    0,   -3,  -20, 16, 24, 61, 60,  192, 128, 208, 152, 0,
    -14, -21, 16,  24, 61, 60, 128, 128, 144, 152, 0,   0,
};

static s16 s_PcData_801B32FC[] = {
    3,   0,   -16, -8, 32, 16, 61,  60,  96,  144, 128, 160,
    0,   -3,  -20, 16, 24, 61, 60,  192, 128, 208, 152, 0,
    -14, -21, 16,  24, 61, 60, 144, 128, 160, 152, 0,   0,
};

static s16 s_PcData_801B3344[] = {
    3,   0,   -16, -8, 32, 16, 61,  60,  96,  144, 128, 160,
    0,   -3,  -20, 16, 24, 61, 60,  208, 128, 224, 152, 0,
    -14, -21, 16,  24, 61, 60, 144, 128, 160, 152, 0,   0,
};

static s16 s_PcData_801B338C[] = {
    3,   0,   -16, -8, 32, 16, 61,  60,  96,  144, 128, 160,
    0,   -3,  -20, 16, 24, 61, 60,  224, 128, 240, 152, 0,
    -14, -21, 16,  24, 61, 60, 160, 128, 176, 152, 0,   0,
};

static s16 s_PcData_801B33D4[] = {
    3,   0,   -16, -8, 32, 16, 61,  60,  96,  144, 128, 160,
    4,   -3,  -20, 16, 24, 61, 60,  240, 128, 256, 152, 0,
    -14, -21, 16,  24, 61, 60, 176, 128, 192, 152, 0,   0,
};

static s16 s_PcData_801B341C[] = {
    1, 16, -14, -12, 24, 32, 61, 60, 0, 184, 24, 216, 0, 0,
};

static s16 s_PcData_801B3438[] = {
    1, 16, -14, -12, 24, 32, 61, 60, 0, 216, 24, 248, 0, 0,
};

static s16 s_PcData_801B3454[] = {
    1, 0, -14, -4, 24, 24, 61, 60, 24, 184, 48, 208, 0, 0,
};

static s16 s_PcData_801B3470[] = {
    1, 0, -15, -3, 24, 24, 61, 60, 24, 208, 48, 232, 0, 0,
};

static s16 s_PcData_801B348C[] = {
    3,   32,  -14, -28, 24, 32, 61,  60,  128, 0,   152, 32,
    0,   -14, -4,  24,  24, 61, 60,  184, 96,  208, 120, 33,
    -10, -26, 16,  32,  61, 60, 152, 0,   168, 32,  0,   0,
};

static s16 s_PcData_801B34D4[] = {
    3,   0,   -5, -20, 24, 24, 61,  60,  128, 32,  152, 56,
    0,   -14, -5, 24,  24, 61, 60,  184, 96,  208, 120, 1,
    -15, -8,  32, 16,  61, 60, 128, 80,  160, 96,  0,   0,
};

static s16 s_PcData_801B351C[] = {
    2, 0,   -14, -8, 32, 16, 61, 60,  128, 80,  160, 96,
    0, -14, -6,  24, 24, 61, 60, 160, 96,  184, 120, 0,
};

static s16 s_PcData_801B354C[] = {
    2, 0,   -8, -4, 24, 24, 61, 60,  208, 96,  232, 120,
    0, -14, -7, 24, 24, 61, 60, 160, 96,  184, 120, 0,
};

static s16 s_PcData_801B357C[] = {
    3,  0,   -6, -4, 16, 32, 61,  60,  152, 32,  168, 64,
    0,  -14, -8, 24, 24, 61, 60,  160, 96,  184, 120, 0,
    -9, -1,  8,  24, 61, 60, 160, 72,  168, 96,  0,   0,
};

static s16 s_PcData_801B35C4[] = {
    1, 0, -8, -4, 16, 8, 62, 56, 160, 168, 176, 176, 0, 0,
};

static s16 s_PcData_801B35E0[] = {
    1, 0, -8, -12, 16, 16, 62, 56, 144, 176, 160, 192, 0, 0,
};

static s16 s_PcData_801B35FC[] = {
    1, 0, -8, -12, 16, 16, 62, 56, 160, 176, 176, 192, 0, 0,
};

static s16 s_PcData_801B3618[] = {
    1, 0, -8, -4, 16, 8, 62, 56, 144, 160, 160, 168, 0, 0,
};

static s16 s_PcData_801B3634[] = {
    1, 0, -8, -4, 16, 8, 62, 56, 160, 160, 176, 168, 0, 0,
};

static s16 s_PcData_801B3650[] = {
    1, 0, -8, -4, 16, 8, 62, 56, 144, 168, 160, 176, 0, 0,
};

static s16 s_PcData_801B366C[] = {
    3,  0,  -5, 90,  8,  8,  61,  60,  160, 64,  168, 72,
    0,  0,  91, 8,   16, 61, 60,  152, 64,  160, 80,  0,
    -6, -1, 16, 112, 61, 56, 128, 128, 144, 240, 0,   0,
};

static s16 s_PcData_801B36B4[] = {
    1, 8, -8, -4, 16, 8, 61, 56, 192, 248, 208, 256, 0, 0,
};

static s16 s_PcData_801B36D0[] = {
    2, 8,   -8,  -14, 16, 48, 65, 56,  224, 208, 240, 256,
    8, -16, -16, 32,  16, 65, 56, 128, 240, 160, 256, 0,
};

static s16 s_PcData_801B3700[] = {
    0,
    0,
};

static s16 s_PcData_801B3704[] = {
    0,
    0,
};

static s16 s_PcData_801B3708[] = {
    2,  0, -16, -36, 32, 80, 47, 56,  176, 128, 208, 208,
    10, 0, -25, 16,  48, 47, 56, 208, 208, 224, 256, 0,
};

static s16 s_PcData_801B3738[] = {
    2, 0, -16, -36, 32, 80, 47, 56,  176, 128, 208, 208,
    8, 0, -25, 16,  48, 47, 60, 112, 208, 128, 256, 0,
};

static s16 s_PcData_801B3768[] = {
    2,  0,  -16, -36, 32, 80, 47, 56, 176, 128, 208, 208,
    10, -8, -25, 24,  48, 47, 60, 72, 208, 96,  256, 0,
};

static s16 s_PcData_801B3798[] = {
    2, 0,   -16, -36, 32, 80, 47, 56, 176, 128, 208, 208,
    8, -16, -25, 32,  48, 47, 60, 96, 208, 128, 256, 0,
};

static s16 s_PcData_801B37C8[] = {
    2, 0,   -16, -17, 32, 32, 2,  56,  144, 128, 176, 160,
    4, -12, -12, 24,  24, 47, 60, 232, 96,  256, 120, 0,
};

static s16 s_PcData_801B37F8[] = {
    2, 0,   -16, -17, 32, 32, 2,  56,  144, 128, 176, 160,
    0, -12, -12, 24,  24, 47, 56, 208, 128, 232, 152, 0,
};

static s16 s_PcData_801B3828[] = {
    2, 0,   -16, -17, 32, 32, 2,  56,  144, 128, 176, 160,
    4, -12, -12, 24,  24, 47, 56, 232, 128, 256, 152, 0,
};

static s16 s_PcData_801B3858[] = {
    1, 4, -4, -9, 8, 24, 47, 56, 248, 192, 256, 216, 0, 0,
};

static s16 s_PcData_801B3874[] = {
    2, 32, -16, -7, 32, 16, 2,  56,  128, 0,   160, 16,
    4, -8, 0,   24, 8,  47, 60, 232, 120, 256, 128, 0,
};

static s16 s_PcData_801B38A4[] = {
    1, 4, -7, -8, 16, 16, 2, 56, 240, 168, 256, 184, 0, 0,
};

static s16 s_PcData_801B38C0[] = {
    1, 0, -16, -8, 32, 16, 2, 56, 144, 192, 176, 208, 0, 0,
};

static s16 s_PcData_801B38DC[] = {
    5,   0,   -18, -41, 40,  24,  2,   56, 128, 80,  168, 104, 0,   -18, -89,
    40,  40,  2,   56,  128, 16,  168, 56, 0,   -18, -57, 40,  24,  2,   56,
    128, 56,  168, 80,  16,  -25, -25, 48, 16,  2,   60,  0,   128, 48,  144,
    16,  -25, -12, 48,  40,  2,   60,  0,  144, 48,  184, 0,   0,
};

static s16 s_PcData_801B3950[] = {
    5,   0,   -18, -57, 40,  24,  2,   56,  128, 104, 168, 128, 0,   -18, -41,
    40,  24,  2,   56,  128, 80,  168, 104, 0,   -18, -89, 40,  40,  2,   56,
    128, 16,  168, 56,  16,  -25, -25, 48,  16,  2,   60,  0,   128, 48,  144,
    16,  -25, -12, 48,  40,  2,   60,  0,   144, 48,  184, 0,   0,
};

static s16 s_PcData_801B39C4[] = {
    5,   0,   -18, -57, 40,  24,  2,   56,  168, 80,  208, 104, 0,   -18, -41,
    40,  24,  2,   56,  128, 80,  168, 104, 0,   -18, -89, 40,  40,  2,   56,
    128, 16,  168, 56,  16,  -25, -25, 48,  16,  2,   60,  0,   128, 48,  144,
    16,  -25, -12, 48,  40,  2,   60,  0,   144, 48,  184, 0,   0,
};

static s16 s_PcData_801B3A38[] = {
    4,   8,  -18, -57, 40,  16, 2,   56, 48,  240, 88,  256, 24,  -25, -25, 48,
    16,  2,  56,  0,   240, 48, 256, 0,  -18, -89, 40,  40,  2,   56,  128, 16,
    168, 56, 16,  -25, -12, 48, 40,  2,  60,  0,   144, 48,  184, 0,
};

static s16 s_PcData_801B3A94[] = {
    4,   8,   -18, -55, 40, 16, 2,   56,  88,  240, 128, 256,
    0,   -18, -41, 40,  24, 2,  56,  128, 80,  168, 104, 16,
    -25, -25, 48,  16,  2,  60, 0,   128, 48,  144, 16,  -25,
    -12, 48,  40,  2,   60, 0,  144, 48,  184, 0,
};

static s16 s_PcData_801B3AF0[] = {
    2,  24,  -25, -25, 48, 16, 2,  56, 0,   240, 48,  256,
    16, -25, -12, 48,  40, 2,  60, 0,  144, 48,  184, 0,
};

static s16 s_PcData_801B3B20[] = {
    1, 0, -25, -32, 48, 56, 2, 60, 48, 128, 96, 184, 0, 0,
};

static s16 s_PcData_801B3B3C[] = {
    1, 32, -16, -21, 40, 24, 68, 56, 208, 0, 248, 24, 0, 0,
};

static s16 s_PcData_801B3B58[] = {
    1, 0, -16, -21, 40, 24, 68, 56, 208, 24, 248, 48, 0, 0,
};

static s16 s_PcData_801B3B74[] = {
    1, 12, 0, 33, 128, 104, 59, 60, 128, 152, 256, 256, 0, 0,
};

static s16 s_PcData_801B3B90[] = {
    1, 48, 0, 137, 128, 48, 60, 60, 0, 0, 128, 48, 0, 0,
};

static s16 s_PcData_801B3BAC[] = {
    1, 16, -65, -33, 128, 72, 64, 60, 0, 56, 128, 128, 0, 0,
};

static s16 s_PcData_801B3BC8[] = {
    1, 0, -17, -13, 40, 32, 2, 56, 168, 40, 208, 72, 0, 0,
};

static s16 s_PcData_801B3BE4[] = {
    4,   0,   30, 8,   40,  24,  71,  56, 168, 104, 208, 128, 0,   -2, -8,  40,
    24,  71,  56, 168, 104, 208, 128, 0,  -34, -24, 40,  24,  71,  56, 168, 104,
    208, 128, 0,  -66, -40, 40,  24,  71, 56,  168, 104, 208, 128, 0,
};

static s16 s_PcData_801B3C40[] = {
    1, 32, -16, -17, 40, 40, 71, 56, 168, 0, 208, 40, 0, 0,
};

static s16 s_PcData_801B3C5C[] = {
    1, 0, -4, -16, 8, 32, 73, 60, 120, 176, 128, 208, 0, 0,
};

static s16 s_PcData_801B3C78[] = {
    1, 0, -12, -1, 24, 32, 54, 60, 96, 176, 120, 208, 0, 0,
};

static s16 s_PcData_801B3C94[] = {
    4,   0,  -9, -17, 24,  24,  2,  56, 208, 96,  232, 120, 0,  -9, -33, 24,
    24,  2,  56, 208, 48,  232, 72, 0,  -9,  -49, 24,  24,  2,  56, 208, 72,
    232, 96, 0,  -9,  -65, 24,  24, 2,  56,  208, 48,  232, 72, 0,
};

static s16 s_PcData_801B3CF0[] = {
    4,   4,  -9, -17, 24,  24,  2,  56, 232, 72,  256, 96,  0,  -9, -65, 24,
    24,  2,  56, 208, 48,  232, 72, 0,  -9,  -33, 24,  24,  2,  56, 208, 48,
    232, 72, 0,  -9,  -49, 24,  24, 2,  56,  208, 72,  232, 96, 0,
};

static s16 s_PcData_801B3D4C[] = {
    3,  4,   -9,  -17, 24, 24, 2,   56,  232, 96,  256, 120,
    0,  -9,  -33, 24,  24, 2,  56,  208, 72,  232, 96,  0,
    -9, -49, 24,  24,  2,  56, 208, 48,  232, 72,  0,   0,
};

static s16 s_PcData_801B3D94[] = {
    2, 4,  -9,  -17, 24, 24, 2,  56,  232, 48,  256, 72,
    0, -9, -33, 24,  24, 2,  56, 208, 48,  232, 72,  0,
};

static s16 s_PcData_801B3DC4[] = {
    1, 4, -9, -17, 24, 24, 2, 56, 232, 96, 256, 120, 0, 0,
};

static s16 s_PcData_801B3DE0[] = {
    1, 0, -16, -1, 32, 16, 74, 56, 208, 192, 240, 208, 0, 0,
};

static s16 s_PcData_801B3DFC[] = {
    1, 16, -63, -55, 120, 56, 79, 56, 0, 8, 120, 64, 0, 0,
};

static s16 s_PcData_801B3E18[] = {
    1, 16, -64, -55, 120, 56, 79, 56, 0, 8, 120, 64, 0, 0,
};

static s16 s_PcData_801B3E34[] = {
    1, 17, -63, -1, 120, 56, 79, 56, 0, 8, 120, 64, 0, 0,
};

static s16 s_PcData_801B3E50[] = {
    1, 17, -64, -1, 120, 56, 79, 56, 0, 8, 120, 64, 0, 0,
};

static s16 s_PcData_801B3E6C[] = {
    1, 0, -16, -8, 32, 16, 75, 56, 144, 208, 176, 224, 0, 0,
};

static s16 s_PcData_801B3E88[] = {
    2, 0, 8, 0,  8,  16, 76, 56,  176, 208, 184, 224,
    0, 0, 0, 16, 16, 76, 56, 144, 224, 160, 240, 0,
};

static s16 s_PcData_801B3EB8[] = {
    1, 0, -2, -4, 16, 16, 76, 56, 144, 224, 160, 240, 0, 0,
};

static s16 s_PcData_801B3ED4[] = {
    1, 0, -4, -6, 16, 16, 76, 56, 144, 224, 160, 240, 0, 0,
};

static s16 s_PcData_801B3EF0[] = {
    2, 0,  0,  -8, 8,  16, 76, 56,  176, 224, 184, 240,
    0, -8, -8, 16, 16, 76, 56, 160, 224, 176, 240, 0,
};

static s16 s_PcData_801B3F20[] = {
    3, 0,  2,  -5, 8,  16, 76,  56,  176, 224, 184, 240,
    8, -8, -8, 16, 16, 76, 56,  160, 240, 176, 256, 8,
    0, -8, 16, 8,  76, 56, 176, 248, 192, 256, 0,   0,
};

static s16 s_PcData_801B3F68[] = {
    3,  0,  11,  -7, 8,  16, 76,  56,  176, 208, 184, 224,
    8,  3,  -12, 16, 8,  76, 56,  176, 248, 192, 256, 8,
    -8, -4, 16,  16, 76, 56, 160, 240, 176, 256, 0,   0,
};

static s16 s_PcData_801B3FB0[] = {
    1, 4, -8, -2, 16, 16, 76, 56, 240, 152, 256, 168, 0, 0,
};

static s16 s_PcData_801B3FCC[] = {
    1, 4, -8, 0, 16, 16, 76, 56, 240, 152, 256, 168, 0, 0,
};

static s16 s_PcData_801B3FE8[] = {
    1, 0, -16, 0, 32, 16, 76, 56, 208, 152, 240, 168, 0, 0,
};

static s16 s_PcData_801B4004[] = {
    1, 0, -16, 0, 32, 16, 76, 56, 208, 168, 240, 184, 0, 0,
};

static s16 s_PcData_801B4020[] = {
    2, 0,  -9,  -1, 24, 40, 14, 56,  184, 208, 208, 248,
    0, -9, -33, 24, 40, 14, 56, 184, 208, 208, 248, 0,
};

static s16 s_PcData_801B4050[] = {
    1, 0, -23, -9, 40, 8, 102, 60, 80, 48, 120, 56, 0, 0,
};

static s16 s_PcData_801B406C[] = {
    2, 0,   -23, -4, 40, 8,   102, 60, 80, 48, 120, 56,
    0, -23, -9,  40, 8,  102, 60,  40, 48, 80, 56,  0,
};

static s16 s_PcData_801B409C[] = {
    3,  0,  -23, 1,  40, 8,  102, 60, 80, 48, 120, 56, 0, -23, -4, 40, 8, 102,
    60, 40, 48,  80, 56, 16, -23, -9, 40, 8,  102, 60, 0, 48,  40, 56, 0, 0,
};

s16* D_us_801B252C[] = {
    NULL,
    s_PcData_801B2700,
    s_PcData_801B271C,
    s_PcData_801B274C,
    s_PcData_801B277C,
    s_PcData_801B27AC,
    s_PcData_801B27DC,
    s_PcData_801B280C,
    s_PcData_801B2828,
    s_PcData_801B2858,
    s_PcData_801B2888,
    s_PcData_801B28B8,
    s_PcData_801B28E8,
    s_PcData_801B2918,
    s_PcData_801B2948,
    s_PcData_801B2978,
    s_PcData_801B29A8,
    s_PcData_801B29D8,
    s_PcData_801B2A08,
    s_PcData_801B2A50,
    s_PcData_801B2A98,
    s_PcData_801B2AE0,
    s_PcData_801B2B28,
    s_PcData_801B2B70,
    s_PcData_801B2BB8,
    s_PcData_801B2C40,
    s_PcData_801B2CC8,
    s_PcData_801B2D50,
    s_PcData_801B2DD8,
    s_PcData_801B2E60,
    s_PcData_801B2EE8,
    s_PcData_801B2F70,
    s_PcData_801B2FF8,
    s_PcData_801B3080,
    s_PcData_801B30F4,
    s_PcData_801B3168,
    s_PcData_801B31DC,
    s_PcData_801B3224,
    s_PcData_801B326C,
    s_PcData_801B32B4,
    s_PcData_801B32FC,
    s_PcData_801B3344,
    s_PcData_801B338C,
    s_PcData_801B33D4,
    s_PcData_801B341C,
    s_PcData_801B3438,
    s_PcData_801B3454,
    s_PcData_801B3470,
    s_PcData_801B348C,
    s_PcData_801B34D4,
    s_PcData_801B351C,
    s_PcData_801B354C,
    s_PcData_801B357C,
    s_PcData_801B35C4,
    s_PcData_801B35E0,
    s_PcData_801B35FC,
    s_PcData_801B3618,
    s_PcData_801B3634,
    s_PcData_801B3650,
    s_PcData_801B366C,
    s_PcData_801B36B4,
    s_PcData_801B36D0,
    s_PcData_801B3700,
    s_PcData_801B3704,
    s_PcData_801B3708,
    s_PcData_801B3738,
    s_PcData_801B3768,
    s_PcData_801B3798,
    s_PcData_801B37C8,
    s_PcData_801B37F8,
    s_PcData_801B3828,
    s_PcData_801B3858,
    s_PcData_801B3874,
    s_PcData_801B38A4,
    s_PcData_801B38C0,
    s_PcData_801B38DC,
    s_PcData_801B3950,
    s_PcData_801B39C4,
    s_PcData_801B3A38,
    s_PcData_801B3A94,
    s_PcData_801B3AF0,
    s_PcData_801B3B20,
    s_PcData_801B3B3C,
    s_PcData_801B3B58,
    s_PcData_801B3B74,
    s_PcData_801B3B90,
    s_PcData_801B3BAC,
    s_PcData_801B3BC8,
    s_PcData_801B3BE4,
    s_PcData_801B3C40,
    s_PcData_801B3C5C,
    s_PcData_801B3C78,
    s_PcData_801B3C94,
    s_PcData_801B3CF0,
    s_PcData_801B3D4C,
    s_PcData_801B3D94,
    s_PcData_801B3DC4,
    s_PcData_801B3DE0,
    s_PcData_801B3DFC,
    s_PcData_801B3E18,
    s_PcData_801B3E34,
    s_PcData_801B3E50,
    s_PcData_801B3E6C,
    s_PcData_801B3E88,
    s_PcData_801B3EB8,
    s_PcData_801B3ED4,
    s_PcData_801B3EF0,
    s_PcData_801B3F20,
    s_PcData_801B3F68,
    s_PcData_801B3FB0,
    s_PcData_801B3FCC,
    s_PcData_801B3FE8,
    s_PcData_801B4004,
    s_PcData_801B4020,
    s_PcData_801B4050,
    s_PcData_801B406C,
    s_PcData_801B409C,
};
