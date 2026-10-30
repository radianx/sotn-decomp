// SPDX-License-Identifier: AGPL-3.0-or-later
#ifndef PC_MENU_H
#define PC_MENU_H
#include <stdbool.h>
struct SDL_Renderer;
bool PcMenuPause(void);
int PcMenuTitle(void);
int PcMenuTitleCount(void);
int PcMenuTitleRow(void);
const char* PcMenuTitleLabel(int row);
const char* PcMenuTitleMessage(void);
bool PcMenuIsOpen(void);
void PcMenuPanel(struct SDL_Renderer* renderer, float x, float y, float w,
                 float h, float alpha);
void PcMenuBackground(struct SDL_Renderer* renderer);
void PcMenuText(struct SDL_Renderer* renderer, int x, int y, const char* text);
bool PcMenuRename(const char* name);
void PcQolUiLoadMode(bool loading);
int PcQolUiSaveAction(void);
void PcQolUiOpenPage(int page);
#endif
