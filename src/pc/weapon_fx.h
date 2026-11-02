// SPDX-License-Identifier: AGPL-3.0-or-later
#ifndef PC_WEAPON_FX_H
#define PC_WEAPON_FX_H
#include <weapon.h>
extern Entity g_PcFxEntities[TOTAL_ENTITY_COUNT];
extern Primitive g_PcFxPrimitives[MAX_PRIM_COUNT];
extern GameApi g_PcFxApi;
extern u16 g_PcFxVram[512][1024];
bool PcWeaponFxStart(int hand, int item, bool special);
void PcWeaponFxStep(const Entity* player);
void PcWeaponFxStop(void);
bool PcWeaponFxActive(void);
int PcWeaponFxSpecial(int item);
int PcFxWeaponFunction(int blueprint);
void PcFxDestroyEntity(Entity* entity);
Entity* PcFxGetFreeEntity(s16 start, s16 end);
Entity* PcFxGetFreeEntityReverse(s16 start, s16 end);
void PcFxFactoryUpdate(Entity* entity);
void PcFxPlayAnimation(s8* props, AnimationFrame** frames);
s32 PcFxUpdateUnarmedAnim(s8* props, u16** frames);
u32 PcFxUpdateAnim(s8* props, AnimationFrame** frames);
#endif
