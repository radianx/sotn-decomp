// SPDX-License-Identifier: AGPL-3.0-or-later
#include "qol.h"
#include <ctype.h>
#include <string.h>

// Small native overlay font; its private draw lists do not consume game tiles.
static const u8 letters[36][7] = {
    {14, 17, 17, 31, 17, 17, 17}, {30, 17, 17, 30, 17, 17, 30},
    {14, 17, 16, 16, 16, 17, 14}, {30, 17, 17, 17, 17, 17, 30},
    {31, 16, 16, 30, 16, 16, 31}, {31, 16, 16, 30, 16, 16, 16},
    {14, 17, 16, 23, 17, 17, 15}, {17, 17, 17, 31, 17, 17, 17},
    {14, 4, 4, 4, 4, 4, 14},      {7, 2, 2, 2, 2, 18, 12},
    {17, 18, 20, 24, 20, 18, 17}, {16, 16, 16, 16, 16, 16, 31},
    {17, 27, 21, 21, 17, 17, 17}, {17, 25, 21, 19, 17, 17, 17},
    {14, 17, 17, 17, 17, 17, 14}, {30, 17, 17, 30, 16, 16, 16},
    {14, 17, 17, 17, 21, 18, 13}, {30, 17, 17, 30, 20, 18, 17},
    {15, 16, 16, 14, 1, 1, 30},   {31, 4, 4, 4, 4, 4, 4},
    {17, 17, 17, 17, 17, 17, 14}, {17, 17, 17, 17, 17, 10, 4},
    {17, 17, 17, 21, 21, 21, 10}, {17, 17, 10, 4, 10, 17, 17},
    {17, 17, 10, 4, 4, 4, 4},     {31, 1, 2, 4, 8, 16, 31},
    {14, 17, 19, 21, 25, 17, 14}, {4, 12, 4, 4, 4, 4, 14},
    {14, 17, 1, 2, 4, 8, 31},     {30, 1, 1, 14, 1, 1, 30},
    {2, 6, 10, 18, 31, 2, 2},     {31, 16, 16, 30, 1, 1, 30},
    {14, 16, 16, 30, 17, 17, 14}, {31, 1, 2, 4, 8, 8, 8},
    {14, 17, 17, 14, 17, 17, 14}, {14, 17, 17, 15, 1, 1, 14}};
static TILE tiles[2][4096];
static DR_MODE modes[2];
static int used;
static void Rect(int x, int y, int w, int h, int color) {
    if (used >= 4096)
        return;
    TILE* tile = &tiles[g_CurrentBuffer != &g_GpuBuffers[0]][used++];
    setTile(tile);
    setRGB0(tile, color, color, color);
    tile->x0 = x;
    tile->y0 = y;
    tile->w = w;
    tile->h = h;
    AddPrim(&g_CurrentBuffer->ot[0x1FF], tile);
}
static void Text(int x, int y, int scale, const char* text, int columns) {
    int start = x, row = 0, column = 0, widest = 0;
    for (; *text && row < 4; text++) {
        if (column == columns || *text == '\n') {
            widest = SDL_max(widest, column);
            row++;
            column = 0;
            x = start;
            if (*text == '\n')
                continue;
        }
        if (row >= 4)
            break;
        int ch = toupper((unsigned char)*text),
            index = ch >= 'A' && ch <= 'Z'   ? ch - 'A'
                    : ch >= '0' && ch <= '9' ? ch - '0' + 26
                                             : -1;
        for (int gy = 0; gy < 7; gy++) {
            int mask = index >= 0  ? letters[index][gy]
                       : ch == '/' ? 1 << SDL_clamp(gy - 1, 0, 4)
                       : ch == ':' && (gy == 2 || gy == 5) ? 4
                       : ch == '-' && gy == 3              ? 14
                                                           : 0;
            if (ch == '?')
                mask = (const u8[]){14, 17, 1, 2, 4, 0, 4}[gy];
            if (ch == '!')
                mask = gy == 5 ? 0 : 4;
            if (ch == '.')
                mask = gy == 6 ? 4 : 0;
            if (ch == ',')
                mask = gy == 5 ? 4 : gy == 6 ? 8 : 0;
            if (ch == '\'' || ch == '"')
                mask = gy < 2 ? (ch == '"' ? 10 : 4) : 0;
            for (int gx = 0; gx < 5;) {
                if (!(mask & (16 >> gx))) {
                    gx++;
                    continue;
                }
                int end = gx + 1;
                while (end < 5 && (mask & (16 >> end)))
                    end++;
                Rect(x + gx * scale, y + (row * 8 + gy) * scale,
                     (end - gx) * scale, scale, 240);
                gx = end;
            }
        }
        column++;
        x += 6 * scale;
    }
    widest = SDL_max(widest, column);
    Rect(start - 1, y - 1, widest * 6 * scale + 2,
         SDL_min(row + 1, 4) * 8 * scale + 2, 0);
}
void PcQolHud(void) {
    if (g_GameState != Game_Play || g_GameStep != Play_Default ||
        g_GameEngineStep != Engine_Normal)
        return;
    used = 0;
    // Gameplay presents rows 20..226; the draw area also includes border rows.
    int bottom = SDL_min(PcViewBottom(), 227);
    if (g_PcSpellPractice && !g_CutsceneHasControl)
        Text(PcViewLeft() + 3, bottom - 43, 1, PcQolInputHistory(), 45);
    if (g_PcSettings.statusHud && !g_CutsceneHasControl) {
        char text[96];
        snprintf(text, sizeof(text), "HP %d/%d  MP %d/%d%s%s%s", g_Status.hp,
                 g_Status.hpMax, g_Status.mp, g_Status.mpMax,
                 g_Player.status & PLAYER_STATUS_POISON ? "\nPOISON" : "",
                 g_Player.status & PLAYER_STATUS_CURSE ? " CURSE" : "",
                 g_Player.status & PLAYER_STATUS_STONE ? " STONE" : "");
        Text(PcViewLeft() + 3, bottom - 19, 1, text, 45);
    }
    if (g_PcSettings.subtitleScale && g_CutsceneHasControl) {
        int scale = g_PcSettings.subtitleScale;
        const char* line = PcQolDialogueLine(23);
        if (!*line)
            line = PcQolDialogueLine(22);
        int columns = (PcViewRight() - PcViewLeft() - 8) / (6 * scale);
        int lines = SDL_min(4, (strlen(line) + columns - 1) / columns);
        if (*line)
            Text(PcViewLeft() + 4, bottom - lines * 8 * scale - 2, scale, line,
                 columns);
    }
    if (used) {
        DR_MODE* mode = &modes[g_CurrentBuffer != &g_GpuBuffers[0]];
        SetDrawMode(mode, 0, 0, 0, NULL);
        AddPrim(&g_CurrentBuffer->ot[0x1FF], mode);
    }
}
