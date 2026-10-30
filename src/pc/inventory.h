// SPDX-License-Identifier: AGPL-3.0-or-later
#ifndef PC_INVENTORY_H
#define PC_INVENTORY_H
#include <SDL3/SDL.h>
void PcInventoryIcon(SDL_Renderer* renderer, int item, int x, int y, int scale);
void PcInventoryPreviewReset(void);
void PcInventoryPreviewCycle(void);
const char* PcInventoryPreviewName(void);
void PcInventoryPreviewDraw(SDL_Renderer* renderer, int x, int y);
#endif
