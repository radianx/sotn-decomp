// SPDX-License-Identifier: AGPL-3.0-or-later
#include <game.h>
#include "dra.h"
#include "upgrades.h"
#include <SDL3/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    u16 x, y, width, color;
    u8 page;
} ArtworkSpan;

typedef struct {
    ArtworkSpan* spans;
    int count, height;
    bool indexed;
} ArtworkEdge;

// Four visible 20x240 strips need at most 19,200 one-pixel spans.
#define ARTWORK_TILE_COUNT 32768
typedef union {
    TILE tile;
    POLY_FT4 indexed;
} ArtworkPrimitive;
static ArtworkPrimitive s_Prims[2][ARTWORK_TILE_COUNT];
static ArtworkEdge s_Edges[2][2];
static int s_Stage = -1, s_AssetStage, s_Layer = -1, s_Used;
static char s_Root[768];

void PcArtworkShutdown(void) {
    for (int kind = 0; kind < 2; kind++) {
        for (int side = 0; side < 2; side++) {
            free(s_Edges[kind][side].spans);
        }
    }
    memset(s_Edges, 0, sizeof(s_Edges));
    s_Stage = s_Layer = -1;
    s_Root[0] = 0;
    s_Used = 0;
}

static u32 ReadBigEndian(const u8* p) {
    return (u32)p[0] << 24 | (u32)p[1] << 16 | (u32)p[2] << 8 | p[3];
}

static SDL_Surface* LoadArtworkImage(const char* path) {
    FILE* file = fopen(path, "rb");
    if (!file)
        return NULL;
    u8 header[24];
    bool valid =
        fread(header, 1, sizeof(header), file) == sizeof(header) &&
        !memcmp(header, "\x89PNG\r\n\x1a\n", 8) &&
        !memcmp(header + 12, "IHDR", 4) && ReadBigEndian(header + 16) == 296 &&
        ReadBigEndian(header + 20) > 0 && ReadBigEndian(header + 20) <= 16384;
    fclose(file);
    if (!valid) {
        WARNF("Invalid widescreen artwork dimensions: %s", path);
        return NULL;
    }
    SDL_Surface* loaded = SDL_LoadPNG(path);
    if (!loaded) {
        WARNF("Cannot load widescreen artwork %s: %s", path, SDL_GetError());
        return NULL;
    }
    SDL_Surface* image = SDL_ConvertSurface(loaded, SDL_PIXELFORMAT_RGBA32);
    SDL_DestroySurface(loaded);
    return image;
}

static void LoadEdge(ArtworkEdge* edge, int kind, int side) {
    char path[896];
    const char* root = s_Root;
    snprintf(path, sizeof(path), "%s/%02X_%02X_%c_%c.png", root, s_AssetStage,
             s_Layer, kind ? 'B' : 'F', side ? 'R' : 'L');
    FILE* file = fopen(path, "rb");
    if (file) {
        fclose(file);
    } else if (g_PcSettings.contentPack[0]) {
        root = "assets/pc/widescreen";
        snprintf(path, sizeof(path), "%s/%02X_%02X_%c_%c.png", root,
                 s_AssetStage, s_Layer, kind ? 'B' : 'F', side ? 'R' : 'L');
    }
    SDL_Surface* image = LoadArtworkImage(path);
    if (!image)
        return;
    snprintf(path, sizeof(path), "%s/indexed/%02X_%02X_%c_%c.png", root,
             s_AssetStage, s_Layer, kind ? 'B' : 'F', side ? 'R' : 'L');
    SDL_Surface* indices = LoadArtworkImage(path);
    if (indices) {
        bool valid = indices->h == image->h;
        for (int y = 0; valid && y < image->h; y++) {
            u8* original = (u8*)image->pixels + y * image->pitch;
            u8* row = (u8*)indices->pixels + y * indices->pitch;
            for (int x = 0; x < image->w; x++) {
                u8* p = row + x * 4;
                if (p[3] != original[x * 4 + 3] ||
                    (p[3] && (p[1] >= 16 || p[2] >= 24))) {
                    valid = false;
                    break;
                }
            }
        }
        if (!valid) {
            WARNF("Invalid indexed artwork: %s", path);
            SDL_DestroySurface(indices);
            indices = NULL;
        }
    }
    ArtworkSpan* spans = calloc((size_t)image->h * 20, sizeof(*spans));
    if (!spans) {
        SDL_DestroySurface(image);
        SDL_DestroySurface(indices);
        return;
    }
    int start = side ? 276 : 0;
    for (int y = 0; y < image->h; y++) {
        SDL_Surface* source = indices ? indices : image;
        u8* row = (u8*)source->pixels + y * source->pitch;
        for (int x = 0; x < 20; x++) {
            u8* p = row + (start + x) * 4;
            if (p[3] < 128)
                continue;
            u16 color = indices ? p[0] * 16 + p[1]
                                : (p[0] >> 3) | (p[1] >> 3) << 5 |
                                      (p[2] >> 3) << 10 | 0x8000;
            u8 page = indices ? p[2] : 0;
            ArtworkSpan* previous =
                edge->count ? &spans[edge->count - 1] : NULL;
            if (previous && previous->y == y &&
                previous->x + previous->width == x &&
                previous->color == color && previous->page == page) {
                previous->width++;
            } else {
                spans[edge->count++] = (ArtworkSpan){x, y, 1, color, page};
            }
        }
    }
    edge->height = image->h;
    edge->spans = spans;
    edge->indexed = indices != NULL;
    SDL_DestroySurface(indices);
    SDL_DestroySurface(image);
}

void PcArtworkBegin(int layer) {
    s_Used = 0;
    if (!PcViewMargin())
        return;
    char root[sizeof(s_Root)];
    int length;
    if (g_PcSettings.contentPack[0]) {
        length = snprintf(
            root, sizeof(root), "%s/widescreen", g_PcSettings.contentPack);
    } else {
        length = snprintf(root, sizeof(root), "assets/pc/widescreen");
    }
    if (length < 0 || length >= sizeof(root) || layer < 0 || layer > 255 ||
        g_StageId < 0 || g_StageId >= LEN(g_StagesLba)) {
        PcArtworkShutdown();
        return;
    }
    if (s_Stage == g_StageId && s_Layer == layer && !strcmp(s_Root, root))
        return;
    PcArtworkShutdown();
    s_Stage = g_StageId;
    s_AssetStage = s_Stage;
    // Alternate/demo stage IDs reuse the same overlay's room artwork.
    for (int i = 0; i < s_Stage; i++) {
        if (!strcmp(g_StagesLba[i].ovlName, g_StagesLba[s_Stage].ovlName)) {
            s_AssetStage = i;
            break;
        }
    }
    s_Layer = layer;
    strcpy(s_Root, root);
    for (int kind = 0; kind < 2; kind++) {
        for (int side = 0; side < 2; side++) {
            LoadEdge(&s_Edges[kind][side], kind, side);
        }
    }
}

int PcArtworkDrawLayer(int background, int width, int height, int scrollX,
                       int scrollY, int order, int flags) {
    if (!PcViewMargin() || !(flags & LAYER_SHOW) || (flags & LAYER_WRAP_BG) ||
        order < 0 || order >= OTSIZE || background < 0 || background > 1 ||
        g_GpuUsage.drawModes >= MAX_DRAW_MODES)
        return 0;
    int first = s_Used;
    DR_MODE* modes[24] = {0};
    ArtworkPrimitive* prims = s_Prims[g_CurrentBuffer != &g_GpuBuffers[0]];
    for (int side = 0; side < 2; side++) {
        ArtworkEdge* edge = &s_Edges[background][side];
        if (edge->height != height)
            continue;
        int left = g_cameraOffsetX + (side ? width : -20) - scrollX;
        int top = g_cameraOffsetY - scrollY;
        for (int i = 0; i < edge->count; i++) {
            ArtworkSpan* span = &edge->spans[i];
            int y = top + span->y;
            int x0 = MAX(left + span->x, PcViewLeft());
            int x1 = MIN(left + span->x + span->width, PcViewRight());
            if (y < PcViewTop() || y >= PcViewBottom() || x1 <= x0)
                continue;
            int depth = order + span->page;
            if (depth >= OTSIZE)
                continue;
            if (s_Used == ARTWORK_TILE_COUNT) {
                WARNF("Widescreen artwork primitive capacity exceeded");
                break;
            }
            if (!modes[span->page]) {
                if (g_GpuUsage.drawModes >= MAX_DRAW_MODES)
                    continue;
                modes[span->page] =
                    &g_CurrentBuffer->drawModes[g_GpuUsage.drawModes++];
                RECT window = {0, 0, 0, 0};
                SetDrawMode(
                    modes[span->page], 0, 0, flags & LAYER_TPAGE_ID, &window);
            }
            ArtworkPrimitive* prim = &prims[s_Used++];
            if (edge->indexed) {
                u16 palette = g_ClutIds[(span->color >> 4) +
                                        ((flags & LAYER_CLUT_ALT) ? 256 : 0)];
                int x = (palette & 63) * 16 + (span->color & 15);
                int paletteY = (palette >> 6) & 511;
                POLY_FT4* quad = &prim->indexed;
                setPolyFT4(quad);
                setShadeTex(quad, 1);
                setSemiTrans(quad, flags & LAYER_SEMI_TRANS);
                quad->tpage =
                    GetTPage(2, (flags & LAYER_TPAGE_ID) >> 5, x, paletteY);
                setXYWH(quad, x0, y, x1 - x0, 1);
                // Sample the live palette entry directly, including STP.
                setUV4(quad, x & 63, paletteY & 255, x & 63, paletteY & 255,
                       x & 63, paletteY & 255, x & 63, paletteY & 255);
                AddPrim(&g_CurrentBuffer->ot[depth], quad);
                continue;
            }
            u16 color = span->color;
            TILE* tile = &prim->tile;
            if (g_PcSettings.palette)
                color = PcPaletteColor(color, g_PcSettings.palette);
            setTile(tile);
            setRGB0(tile, (color & 31) << 3, ((color >> 5) & 31) << 3,
                    ((color >> 10) & 31) << 3);
            setSemiTrans(tile, (flags & LAYER_SEMI_TRANS) && (color & 0x8000));
            tile->x0 = x0;
            tile->y0 = y;
            tile->w = x1 - x0;
            tile->h = 1;
            AddPrim(&g_CurrentBuffer->ot[depth], tile);
        }
    }
    for (int page = 0; page < LEN(modes); page++) {
        if (modes[page])
            AddPrim(&g_CurrentBuffer->ot[order + page], modes[page]);
    }
    return s_Used - first;
}
