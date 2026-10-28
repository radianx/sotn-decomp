// SPDX-License-Identifier: AGPL-3.0-or-later
#ifdef NDEBUG
#undef NDEBUG
#endif
#include <game.h>
#include <stage.h>
#include "../dra/dra.h"
#include "pc.h"
#include "upgrades.h"
#include "qol.h"
#include "spawn_point.h"
#include <SDL3/SDL.h>
#include <psyz.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#ifdef _WIN32
#include <direct.h>
#define chdir _chdir
#else
#include <unistd.h>
#endif

static void WriteFile(const char* path, const void* data, size_t size) {
    FILE* f = fopen(path, "wbx");
    assert(f);
    assert(fwrite(data, 1, size, f) == size);
    assert(!fclose(f));
}

static void CheckArtwork(void) {
    assert(SDL_CreateDirectory("pack/widescreen"));
    SDL_Surface* image = SDL_CreateSurface(296, 256, SDL_PIXELFORMAT_RGBA32);
    assert(image);
    assert(SDL_ClearSurface(image, 0, 0, 0, 0));
    SDL_Rect row = {0, 40, 20, 1};
    assert(SDL_FillSurfaceRect(
        image, &row, SDL_MapSurfaceRGBA(image, 0, 255, 0, 255)));
    row = (SDL_Rect){0, 42, 10, 1};
    assert(SDL_FillSurfaceRect(
        image, &row, SDL_MapSurfaceRGBA(image, 0, 255, 0, 255)));
    assert(SDL_SavePNG(image, "pack/widescreen/1F_00_F_L.png"));
    assert(SDL_SavePNG(image, "pack/widescreen/01_00_F_L.png"));
    assert(SDL_ClearSurface(image, 0, 0, 0, 0));
    row = (SDL_Rect){276, 40, 20, 1};
    assert(SDL_FillSurfaceRect(
        image, &row, SDL_MapSurfaceRGBA(image, 0, 0, 255, 255)));
    assert(SDL_SavePNG(image, "pack/widescreen/1F_00_B_R.png"));
    SDL_DestroySurface(image);
    image = SDL_CreateSurface(1, 1, SDL_PIXELFORMAT_RGBA32);
    assert(image && SDL_SavePNG(image, "pack/widescreen/1F_00_F_R.png"));
    SDL_DestroySurface(image);
    GpuBuffer* previousBuffer = g_CurrentBuffer;
    g_CurrentBuffer = &g_GpuBuffers[0];
    ClearOTagR(g_CurrentBuffer->ot, OTSIZE);
    g_GpuUsage.drawModes = 0;
    g_cameraOffsetX = g_cameraOffsetY = 0;
    g_PcSettings.widescreen = 1;
    PcUpdateViewport();
    PcArtworkBegin(0);
    assert(PcArtworkDrawLayer(0, 256, 256, 0, 0, 0x80, LAYER_SHOW) == 2);
    DR_MODE* mode = (DR_MODE*)getaddr(&g_CurrentBuffer->ot[0x80]);
    TILE* tile = (TILE*)getaddr(mode);
    assert(getcode(tile) == 0x60 && tile->x0 == -20 && tile->y0 == 42);
    assert(tile->w == 10 && tile->h == 1 && tile->g0 == 248);
    assert(PcArtworkDrawLayer(0, 256, 256, 20, 0, 0x80, LAYER_SHOW) == 0);
    assert(PcArtworkDrawLayer(0, 256, 512, 0, 0, 0x80, LAYER_SHOW) == 0);
    assert(PcArtworkDrawLayer(1, 256, 256, 0, 10, 0x60, LAYER_SHOW) == 1);
    mode = (DR_MODE*)getaddr(&g_CurrentBuffer->ot[0x60]);
    tile = (TILE*)getaddr(mode);
    assert(tile->x0 == 256 && tile->y0 == 30 && tile->b0 == 248);
    assert(PcArtworkDrawLayer(0, 256, 256, 0, 0, 0x80, 0) == 0);
    assert(PcArtworkDrawLayer(
               0, 256, 256, 0, 0, 0x80, LAYER_SHOW | LAYER_WRAP_BG) == 0);
    g_PcSettings.palette = 3;
    assert(PcArtworkDrawLayer(
               0, 256, 256, 0, 0, 0x80, LAYER_SHOW | LAYER_SEMI_TRANS) == 2);
    mode = (DR_MODE*)getaddr(&g_CurrentBuffer->ot[0x80]);
    tile = (TILE*)getaddr(mode);
    assert(
        getcode(tile) == 0x62 && tile->r0 == tile->g0 && tile->g0 == tile->b0);
    g_PcSettings.palette = 0;
    g_StageId = STAGE_NO1_ALT;
    ClearOTagR(g_CurrentBuffer->ot, OTSIZE);
    PcArtworkBegin(0);
    assert(PcArtworkDrawLayer(0, 256, 256, 0, 0, 0x80, LAYER_SHOW) == 2);
    g_StageId = STAGE_ST0;

    Tilemap previousTilemap = g_Tilemap;
    BgLayer previousBackgrounds[MAX_BG_LAYER_COUNT];
    memcpy(previousBackgrounds, g_BgLayers, sizeof(previousBackgrounds));
    RoomDef* previousLayers = g_api.o.tileLayers;
    u16 emptyTiles[256] = {0};
    u8 emptyDefinitions[256] = {0};
    TileDefinition definition = {
        emptyDefinitions, emptyDefinitions, emptyDefinitions, emptyDefinitions};
    LayerDef foreground = {.layout = emptyTiles,
                           .tileDef = &definition,
                           .zPriority = 0x80,
                           .flags = LAYER_SHOW};
    LayerDef background = foreground;
    background.zPriority = 0x60;
    RoomDef room = {&foreground, &background};
    g_api.o.tileLayers = &room;
    LoadRoomLayer(0);
    g_Tilemap.hideTimer = g_BgLayers[0].hideTimer = 0;
    g_BgLayers[1] = g_BgLayers[0];
    g_GpuUsage.drawModes = g_GpuUsage.sp16 = 0;
    ClearOTagR(g_CurrentBuffer->ot, OTSIZE);
    RenderTilemap();
    void* node = &g_CurrentBuffer->ot[OTSIZE - 1];
    int visited = 0, artworkTiles = 0;
    while (!isendprim(node)) {
        assert(++visited < OTSIZE + 128);
        if (getlen(node) == 3 && getcode(node) == 0x60)
            artworkTiles++;
        node = nextPrim(node);
    }
    assert(g_GpuUsage.drawModes == 74 && artworkTiles == 3);
    g_api.o.tileLayers = previousLayers;
    g_Tilemap = previousTilemap;
    memcpy(g_BgLayers, previousBackgrounds, sizeof(previousBackgrounds));
    ClearOTagR(g_CurrentBuffer->ot, OTSIZE);
    g_PcSettings.widescreen = 0;
    PcUpdateViewport();
    assert(PcArtworkDrawLayer(0, 256, 256, 0, 0, 0x80, LAYER_SHOW) == 0);
    PcArtworkShutdown();
    g_CurrentBuffer = previousBuffer;
    assert(!remove("pack/widescreen/1F_00_F_L.png"));
    assert(!remove("pack/widescreen/01_00_F_L.png"));
    assert(!remove("pack/widescreen/1F_00_F_R.png"));
    assert(!remove("pack/widescreen/1F_00_B_R.png"));
    assert(SDL_RemovePath("pack/widescreen"));
    puts(
        "Artwork edge placement, layer alpha holes and camera scrolling: PASS");
}

static int DrawIndexedArtwork(int flags) {
    ClearOTagR(g_CurrentBuffer->ot, OTSIZE);
    g_GpuUsage.drawModes = 0;
    PcArtworkBegin(0);
    return PcArtworkDrawLayer(0, 256, 256, 0, 0, 0x80, flags);
}

static TILE* ArtworkTileAt(int depth) {
    DR_MODE* mode = (DR_MODE*)getaddr(&g_CurrentBuffer->ot[depth]);
    assert(getcode(mode) == 0xE1);
    return (TILE*)getaddr(mode);
}

static void CheckArtworkPalettePixels(int flags) {
    DRAWENV oldDraw, draw;
    GetDrawEnv(&oldDraw);
    SetDefDrawEnv(&draw, 0, 0, 256, 240);
    draw.isbg = 0;
    PutDrawEnv(&draw);
    RECT clear = {0, 0, 256, 240};
    ClearImage(&clear, 64, 64, 64);
    RECT texture = {640, 256, 5, 2};
    u16 pixels[10] = {0x1111, 0x1111, 0x1111, 0x1111, 0x1111,
                      0x2222, 0x2222, 0x2222, 0x2222, 0x2222};
    LoadImage(&texture, (u_long*)pixels);
    SPRT reference[2];
    for (int i = 0; i < 2; i++) {
        setSprt(&reference[i]);
        setShadeTex(&reference[i], 1);
        setSemiTrans(&reference[i], flags & LAYER_SEMI_TRANS);
        setXY0(&reference[i], 8, 40 + i * 2);
        setWH(&reference[i], i ? 10 : 20, 1);
        setUV0(&reference[i], 0, i);
        reference[i].clut = g_ClutIds[3 + ((flags & LAYER_CLUT_ALT) ? 256 : 0)];
        addPrim(&g_CurrentBuffer->ot[0x90], &reference[i]);
    }
    DR_MODE mode;
    RECT window = {0, 0, 0, 0};
    SetDrawMode(&mode, 0, 0,
                GetTPage(0, (flags & LAYER_TPAGE_ID) >> 5, 640, 256), &window);
    addPrim(&g_CurrentBuffer->ot[0x90], &mode);
    DrawOTag(&g_CurrentBuffer->ot[OTSIZE - 1]);
    DrawSync(0);
    int width, height;
    u8* frame = Psyz_VideoAllocCapturedFrame(&width, &height);
    unsigned scale = Psyz_VideoGetInternalResolution();
    assert(frame && width == (PcViewRight() - PcViewLeft()) * scale &&
           height == 207 * scale);
    for (int row = 0; row < 2; row++) {
        int y = (40 + row * 2 - 20) * scale + scale / 2;
        for (int x = 0; x < 20; x++) {
            u8* edge = frame + (y * width + x * scale + scale / 2) * 3;
            u8* original =
                frame +
                (y * width + (8 - PcViewLeft() + x) * scale + scale / 2) * 3;
            if (memcmp(edge, original, 3))
                fprintf(stderr,
                        "Palette pixel row%d x%d: edge %u,%u,%u reference "
                        "%u,%u,%u\n",
                        row, x, edge[0], edge[1], edge[2], original[0],
                        original[1], original[2]);
            assert(!memcmp(edge, original, 3));
        }
    }
    free(frame);
    PutDrawEnv(&oldDraw);
    DrawSync(0);
}

static void CheckIndexedArtwork(void) {
    assert(SDL_CreateDirectory("pack/widescreen/indexed"));
    SDL_Surface* rgb = SDL_CreateSurface(296, 256, SDL_PIXELFORMAT_RGBA32);
    SDL_Surface* indices = SDL_CreateSurface(296, 256, SDL_PIXELFORMAT_RGBA32);
    assert(rgb && indices);
    assert(SDL_ClearSurface(rgb, 0, 0, 0, 0));
    assert(SDL_ClearSurface(indices, 0, 0, 0, 0));
    SDL_Rect rows[] = {{0, 40, 20, 1}, {0, 42, 10, 1}};
    for (int i = 0; i < 2; i++) {
        assert(SDL_FillSurfaceRect(
            rgb, &rows[i], SDL_MapSurfaceRGBA(rgb, 0, 255, 0, 255)));
        assert(SDL_FillSurfaceRect(
            indices, &rows[i],
            SDL_MapSurfaceRGBA(indices, 3, i + 1, i * 2 + 2, 255)));
    }
    const char* rgbPath = "pack/widescreen/1F_00_F_L.png";
    const char* indexPath = "pack/widescreen/indexed/1F_00_F_L.png";
    assert(SDL_SavePNG(rgb, rgbPath) && SDL_SavePNG(indices, indexPath));
    u16 oldColors[] = {g_Clut[0][49], g_Clut[0][50], g_Clut[1][49],
                       g_Clut[1][50], g_Clut[2][49], g_Clut[2][50]};
    u16 oldIds[0x300];
    memcpy(oldIds, g_ClutIds, sizeof(oldIds));
    func_800EAD7C();
    GpuBuffer* oldBuffer = g_CurrentBuffer;
    g_CurrentBuffer = &g_GpuBuffers[0];
    g_cameraOffsetX = g_cameraOffsetY = 0;
    g_StageId = STAGE_ST0;
    g_PcSettings.widescreen = 1;
    PcUpdateViewport();
    g_Clut[0][49] = 31;
    g_Clut[0][50] = 0x83E0;
    g_Clut[1][49] = 0x3FF;
    g_Clut[1][50] = 0;
    int flags = LAYER_SHOW | LAYER_SEMI_TRANS;
    g_Clut[2][49] = 0xFC00;
    g_Clut[2][50] = 31;
    PcUploadPalette(g_Clut[2], 256, 240);
    g_ClutIds[3] = GetClut(304, 240);
    assert(DrawIndexedArtwork(flags) == 2);
    CheckArtworkPalettePixels(flags);
    g_ClutIds[3] = GetClut(560, 240);
    PcUploadPalette(g_Clut[0], 512, 240);
    PcUploadPalette(g_Clut[1], 0, 240);
    assert(DrawIndexedArtwork(flags) == 2 && g_GpuUsage.drawModes == 2);
    CheckArtworkPalettePixels(flags);

    // Palette edits and remaps must work without reloading the metadata file.
    assert(!remove(indexPath));
    g_Clut[0][49] = 0xFC00;
    g_Clut[0][50] = 0;
    PcUploadPalette(g_Clut[0], 512, 240);
    assert(DrawIndexedArtwork(flags) == 2 && g_GpuUsage.drawModes == 2);
    CheckArtworkPalettePixels(flags);
    for (int mode = 0; mode < 4; mode++) {
        g_PcSettings.palette = mode;
        for (int bank = 0; bank < 3; bank++) {
            PcUploadPalette(g_Clut[bank],
                            bank == 0   ? 512
                            : bank == 1 ? 0
                                        : 256,
                            240);
            g_ClutIds[3] = g_ClutIds[0x103] = GetClut(
                bank == 0   ? 560
                : bank == 1 ? 48
                            : 304,
                240);
            for (int blend = 0; blend < 4; blend++) {
                for (int alternate = 0; alternate < 2; alternate++) {
                    int layer =
                        flags | (blend << 5) | (alternate ? LAYER_CLUT_ALT : 0);
                    assert(DrawIndexedArtwork(layer) == 2);
                    CheckArtworkPalettePixels(layer);
                }
            }
        }
    }
    g_PcSettings.palette = 0;
    g_ClutIds[3] = GetClut(560, 240);
    g_Clut[0][49] = 0x8000;
    PcUploadPalette(g_Clut[0], 512, 240);
    assert(DrawIndexedArtwork(flags) == 2);
    CheckArtworkPalettePixels(flags);
    // A valid CLUT may also live outside the standard CPU palette banks.
    u16 custom[16] = {0};
    custom[1] = 0x801F;
    custom[2] = 0x03E0;
    RECT customRect = {800, 300, 16, 1};
    LoadImage(&customRect, (u_long*)custom);
    g_ClutIds[3] = GetClut(800, 300);
    assert(DrawIndexedArtwork(flags) == 2);
    CheckArtworkPalettePixels(flags);
    TILE* tile;

    for (int bad = 0; bad < 3; bad++) {
        PcArtworkShutdown();
        SDL_Rect pixel = {0, 40, 1, 1};
        assert(SDL_FillSurfaceRect(
            indices, &pixel,
            SDL_MapSurfaceRGBA(indices, 3, bad == 0 ? 16 : 1, bad == 1 ? 24 : 2,
                               bad == 2 ? 0 : 255)));
        assert(SDL_SavePNG(indices, indexPath));
        assert(DrawIndexedArtwork(flags) == 2);
        tile = ArtworkTileAt(0x80);
        assert(tile->g0 == 248 && getcode(tile) == 0x62);
    }
    PcArtworkShutdown();
    g_Clut[0][49] = oldColors[0];
    g_Clut[0][50] = oldColors[1];
    g_Clut[1][49] = oldColors[2];
    g_Clut[1][50] = oldColors[3];
    g_Clut[2][49] = oldColors[4];
    g_Clut[2][50] = oldColors[5];
    memcpy(g_ClutIds, oldIds, sizeof(oldIds));
    g_PcSettings.widescreen = 0;
    PcUpdateViewport();
    ClearOTagR(g_CurrentBuffer->ot, OTSIZE);
    g_CurrentBuffer = oldBuffer;
    SDL_DestroySurface(rgb);
    SDL_DestroySurface(indices);
    assert(!remove(rgbPath) && !remove(indexPath));
    assert(SDL_RemovePath("pack/widescreen/indexed"));
    assert(SDL_RemovePath("pack/widescreen"));
    puts(
        "Indexed artwork matches original GPU palette pixels across all banks, "
        "remaps, blends, accessibility modes and custom VRAM CLUTs: PASS");
}

#ifndef _WIN32
static SDL_SharedObject* OpenOverlay(const char* name) {
    char path[1024];
#ifdef __APPLE__
    const char* suffix = ".dylib";
#else
    const char* suffix = ".so";
#endif
    snprintf(path, sizeof(path), "%s%s%s", SDL_GetBasePath(), name, suffix);
    SDL_SharedObject* module = SDL_LoadObject(path);
    assert(module);
    void (*start)(void*) = (void*)SDL_LoadFunction(module, "psyz_module_start");
    assert(start);
    start(&g_api.o);
    return module;
}

static void CheckBugFixes(void) {
    extern GameApi g_ApiInit;
    extern LayoutEntity** g_pStObjLayoutHorizontal;
    g_api = g_ApiInit;
    Entity* self = g_CurrentEntity = &g_Entities[64];
    SDL_SharedObject* module = OpenOverlay("bo3");
    void (*update)(Entity*) =
        (void*)SDL_LoadFunction(module, "func_us_801A1BE8");
    u16* doors = (void*)SDL_LoadFunction(module, "D_us_80180C66");
    assert(update && doors);
    memset(self, 0, sizeof(*self));
    self->step = 99;
    g_CastleFlags[SCYLLA_DEFEATED] = 1;
    for (int enabled = 0; enabled <= 1; enabled++) {
        g_PcSettings.bugFixes = enabled;
        *doors = 5;
        update(self);
        assert(*doors == (enabled ? 4 : 5));
    }
    g_CastleFlags[SCYLLA_DEFEATED] = 0;
    SDL_UnloadObject(module);

    module = OpenOverlay("bo2");
    update = (void*)SDL_LoadFunction(module, "func_us_801A6EF8");
    assert(update);
    for (int enabled = 0; enabled <= 1; enabled++) {
        memset(self, 0, sizeof(*self));
        g_CurrentEntity = self;
        g_PcSettings.bugFixes = enabled;
        PLAYER.step = 5;
        PLAYER.step_s = 3;
        PLAYER.posX.i.hi = 96;
        PLAYER.animCurFrame = 9;
        g_Player.status = PLAYER_STATUS_BAT_FORM;
        update(self);
        assert(PLAYER.step == (enabled ? 0 : 5));
        if (enabled)
            assert(PLAYER.step_s == 0 && PLAYER.animCurFrame == 0 &&
                   PLAYER.animSet == (s16)ANIMSET_OVL(0x100));
    }
    g_Player.status = 0;
    SDL_UnloadObject(module);

    module = OpenOverlay("nz1");
    g_Tilemap.scrollX.i.hi = g_Tilemap.scrollY.i.hi = 0;
    for (int enabled = 0; enabled <= 1; enabled++) {
        g_PcSettings.bugFixes = enabled;
        g_api.o.InitRoomEntities(8);
        LayoutEntity* layout = g_pStObjLayoutHorizontal[8] + 1;
        int found = 0, previous = 0;
        for (; layout->posX != 0xFFFF; layout++) {
            assert(layout->posX >= previous);
            previous = layout->posX;
            if ((layout->entityRoomIndex & 255) == 10) {
                assert(layout->posX == (enabled ? 128 : 16));
                found++;
            }
        }
        assert(found == 1);
    }
    SDL_UnloadObject(module);

    module = OpenOverlay("bo0");
    update = (void*)SDL_LoadFunction(module, "func_us_801B365C");
    assert(update);
    memset(g_Entities, 0, sizeof(g_Entities));
    g_CurrentEntity = self;
    DestroyAllPrimitives();
    update(self);
    assert(self->ext.olroxTrueForm.prim);
    for (int enabled = 0; enabled <= 1; enabled++) {
        g_PcSettings.bugFixes = enabled;
        g_CurrentEntity = self;
        self->step = 16;
        self->step_s = 2;
        self->ext.olroxTrueForm.timer = -1;
        update(self);
        assert(self->ext.olroxTrueForm.timer == (enabled ? 95 : -2));
    }
    DestroyAllPrimitives();
    memset(g_Entities, 0, sizeof(g_Entities));
    SDL_UnloadObject(module);
    g_PcSettings.bugFixes = 0;
    module = OpenOverlay("rbo1");
    update = (void*)SDL_LoadFunction(module, "func_us_80193C2C");
    assert(update);
    memset(self, 0, sizeof(*self));
    self->step = 1;
    update(self);
    assert(self->step == 3);
    Entity* dead = self + 1;
    memset(dead, 0, sizeof(*dead));
    dead->flags = FLAG_DEAD;
    self->ext.beelzebub.parent = dead;
    self->step = 1;
    update(self);
    assert(self->step == 3);
    SDL_UnloadObject(module);
    puts("Original-game bug scenarios with fixes off/on: PASS");
}

static void CheckWaterCoverage(void) {
    extern GameApi g_ApiInit;
    g_api = g_ApiInit;
    g_PcSettings.widescreen = 1;
    g_GameState = Game_Play;
    g_GameStep = Play_Default;
    g_GameEngineStep = Engine_Normal;
    g_CutsceneHasControl = 0;
    g_Tilemap.width = 1024;
    g_Tilemap.x = 0;
    PcUpdateViewport();
    assert(PcViewMargin() > 0);
    u16 originalIds[768];
    memcpy(originalIds, g_ClutIds, sizeof(originalIds));
    const char* stages[] = {"no3", "np3", "rno3"};
    for (int stage = 0; stage < LEN(stages); stage++) {
        bool inverted = stage == 2;
        SDL_SharedObject* module = OpenOverlay(stages[stage]);
        void (*update)(Entity*) =
            (void*)SDL_LoadFunction(module, "EntityTransparentWater");
        assert(update);
        for (int partial = 0; partial < 2; partial++) {
            DestroyAllPrimitives();
            Entity* self = g_CurrentEntity = &g_Entities[64];
            memset(self, 0, sizeof(*self));
            self->params = partial;
            self->posY.i.hi = inverted ? 72 : 184;
            update(self);
            assert(self->ext.transparentWater.prim);
            for (int scroll = 0; scroll <= 1024; scroll++) {
                g_Tilemap.scrollX.val = FIX(scroll);
                Entity before = *self;
                Primitive snapshots[2][16] = {0};
                int central[2] = {0};
                for (int wide = 0; wide < 2; wide++) {
                    g_PcSettings.widescreen = wide;
                    PcUpdateViewport();
                    *self = before;
                    update(self);
                    int nodes = 0, live = 0, left = 1000, right = -1000;
                    int previousLeft = 0, previousRight = 0;
                    for (Primitive* prim = self->ext.transparentWater.prim;
                         prim; prim = prim->next) {
                        assert(++nodes <= 16);
                        if (prim->drawMode & DRAW_HIDE)
                            continue;
                        int l = MIN(prim->x0, prim->x1);
                        int r = MAX(prim->x0, prim->x1);
                        assert(r - l == (inverted ? 37 : 38));
                        assert(abs(prim->y2 - prim->y0) == 62);
                        assert(prim->u1 - prim->u0 == r - l);
                        assert(prim->v2 - prim->v0 == 62);
                        assert(prim->tpage == 15 && prim->clut == 24);
                        assert(prim->priority == 176);
                        assert(prim->drawMode == (DRAW_TPAGE2 | DRAW_TPAGE |
                                                  DRAW_UNK02 | DRAW_TRANSP));
                        if (live++)
                            assert(inverted ? l == previousRight
                                            : r == previousLeft);
                        previousLeft = l;
                        previousRight = r;
                        left = MIN(left, l);
                        right = MAX(right, r);
                        if (r > 0 && l < 256) {
                            Primitive* copy = &snapshots[wide][central[wide]++];
                            memcpy(&copy->r0, &prim->r0,
                                   offsetof(Primitive, drawMode) +
                                       sizeof(prim->drawMode) -
                                       offsetof(Primitive, r0));
                            copy->p1 = copy->p2 = copy->p3 = 0;
                        }
                    }
                    assert(nodes == 16 && live);
                    if (partial && inverted)
                        assert(left == 160);
                    else
                        assert(left <= PcViewLeft());
                    if (partial && !inverted)
                        assert(right == 96);
                    else
                        assert(right >= PcViewRight());
                }
                assert(central[0] == central[1]);
                assert(!memcmp(snapshots[0], snapshots[1],
                               central[0] * sizeof(Primitive)));
            }
            DestroyAllPrimitives();
        }
        SDL_UnloadObject(module);
    }
    memcpy(g_ClutIds, originalIds, sizeof(originalIds));
    g_PcSettings.widescreen = 0;
    g_Tilemap.width = 1280;
    g_Tilemap.scrollX.i.hi = 1024;
    g_PlayerX = 1143;
    PLAYER.posX.i.hi = 163;
    PcUpdateViewport();
    PcClampCamera();
    assert(PLAYER.posX.i.hi == 119);
    PcUpdateViewport();
    puts("All Entrance water overlays preserve center phase, partial-pool "
         "endpoints and gap-free coverage through scrolling/aspect toggles: "
         "PASS");
}

static void CheckCavernWaterCoverage(void) {
    extern GameApi g_ApiInit;
    g_api = g_ApiInit;
    const char* stages[] = {"no4", "bo3", "rno4"};
    for (int stage = 0; stage < LEN(stages); stage++) {
        SDL_SharedObject* module = OpenOverlay(stages[stage]);
        for (int body = 0; body < 2; body++) {
            const char* function =
                stage == 2 ? (body ? "func_us_801C15F8_from_no4"
                                   : "func_us_801C12B0_from_no4")
                           : (body ? "func_us_801C15F8" : "func_us_801C12B0");
            const char* symbol =
                stage == 2
                    ? (body ? "D_us_80181190" : "D_us_80181094")
                    : (body ? "water_tile_rects" : "water_surface_lines");
            void (*update)(Entity*) = (void*)SDL_LoadFunction(module, function);
            s16* table = (void*)SDL_LoadFunction(module, symbol);
            assert(update && table);
            int stride = body ? 4 : 5;
            s16 original[10];
            memcpy(original, table, sizeof(original));
            for (int region = 0; region < 4; region++) {
                DestroyAllPrimitives();
                Entity* self = g_CurrentEntity = &g_Entities[64];
                memset(self, 0, sizeof(*self));
                self->params = (region < 2 ? 1 : 2) << 8;
                g_Tilemap.scrollX.val = g_Tilemap.scrollY.val = 0;
                update(self);
                for (int scroll = 0; scroll <= 512; scroll++) {
                    int starts[] = {region == 0 ? -1024 : -4, scroll + 32};
                    int widths[] = {region == 0 ? 4096 : 258, 200};
                    if (region >= 2) {
                        starts[0] = scroll + (region == 2 ? -35 : 273);
                        widths[0] = region == 2 ? 18 : 6;
                    }
                    int pools = region < 2 ? 1 : 2;
                    for (int i = 0; i < pools; i++) {
                        table[i * stride] = starts[i];
                        table[i * stride + 1] = widths[i];
                        table[i * stride + 2] = body && stage == 2 ? 220 : 180;
                        table[i * stride + 3] = body && stage == 2 ? 180 : 220;
                        if (!body)
                            table[i * stride + 4] = i ? 1 : -2;
                    }
                    g_Tilemap.scrollX.val = FIX(scroll);
                    g_Tilemap.scrollY.val = 0;
                    Entity before = *self;
                    int samples[2][256] = {0}, phases[2];
                    for (int wide = 0; wide < 2; wide++) {
                        g_PcSettings.widescreen = wide;
                        PcUpdateViewport();
                        *self = before;
                        update(self);
                        assert(self->flags & FLAG_HAS_PRIMS);
                        bool covered[296] = {0};
                        int nodes = 0;
                        for (Primitive* prim = self->ext.et_801C12B0.prim; prim;
                             prim = prim->next) {
                            assert(++nodes <= 16);
                            if (prim->drawMode & DRAW_HIDE)
                                continue;
                            int left = prim->x0;
                            int right = body ? left + prim->u0 : prim->x1;
                            assert(right >= left);
                            assert(prim->drawMode ==
                                   (DRAW_TPAGE | DRAW_UNK02 | DRAW_TRANSP));
                            for (int x = MAX(left, -20); x < MIN(right, 276);
                                 x++) {
                                covered[x + 20] = true;
                                if (x >= 0 && x < 256) {
                                    samples[wide][x] =
                                        body ? 1 + prim->r0 + (prim->g0 << 8) +
                                                   (prim->b0 << 16)
                                             : 1 + prim->u0 + x - left +
                                                   (prim->v0 << 8);
                                }
                            }
                        }
                        assert(nodes == 16);
                        for (int x = PcViewLeft(); x < PcViewRight(); x++) {
                            bool expected = false;
                            for (int i = 0; i < pools; i++)
                                expected |= x + scroll >= starts[i] &&
                                            x + scroll < starts[i] + widths[i];
                            assert(covered[x + 20] == expected);
                        }
                        phases[wide] = self->ext.et_801C12B0.unk82;
                    }
                    assert(phases[0] == phases[1]);
                    assert(!memcmp(samples[0], samples[1], sizeof(samples[0])));
                }
                DestroyAllPrimitives();
            }
            memcpy(table, original, sizeof(original));
        }
        SDL_UnloadObject(module);
    }
    g_PcSettings.widescreen = 0;
    PcUpdateViewport();
    puts("Caverns/Scylla water covers both margins, preserves dry endpoints "
         "and original central texture/flow phase: PASS");
}

static void CheckCavernShimmer(void) {
    extern GameApi g_ApiInit;
    g_api = g_ApiInit;
    const char* stages[] = {"no4", "bo3", "rno4"};
    for (int stage = 0; stage < LEN(stages); stage++) {
        SDL_SharedObject* module = OpenOverlay(stages[stage]);
        void (*update)(Entity*) = (void*)SDL_LoadFunction(
            module, stage == 2 ? "func_us_801C5364" : "func_us_801C1844");
        assert(update);
        for (int region = 0; region < 2; region++) {
            int left =
                stage == 2 ? (region ? 360 : 2984) : (region ? 104 : 296);
            int right = left + 48;
            DestroyAllPrimitives();
            Entity* self = g_CurrentEntity = &g_Entities[64];
            memset(self, 0, sizeof(*self));
            self->params = 0x100 | (region ? 10 : 0);
            g_Tilemap.height = stage == 2 && region ? 1536 : 512;
            g_Tilemap.scrollY.val = FIX(stage == 2 ? (region ? 1280 : 256) : 0);
            g_Tilemap.scrollX.val = 0;
            update(self);
            for (int scroll = 0; scroll <= right + 32; scroll++) {
                g_Tilemap.scrollX.val = FIX(scroll);
                Entity before = *self;
                int samples[2][256] = {0};
                for (int wide = 0; wide < 2; wide++) {
                    g_PcSettings.widescreen = wide;
                    PcUpdateViewport();
                    *self = before;
                    update(self);
                    bool covered[296] = {0};
                    int nodes = 0;
                    for (Primitive* prim = &g_PrimBuf[self->primIndex]; prim;
                         prim = prim->next) {
                        assert(++nodes <= 16);
                        if (prim->drawMode & DRAW_HIDE)
                            continue;
                        assert(prim->x1 >= prim->x0);
                        for (int x = MAX(-20, prim->x0); x < MIN(276, prim->x1);
                             x++) {
                            covered[x + 20] = true;
                            if (x >= 0 && x < 256)
                                samples[wide][x] = 1 + prim->u0 + x - prim->x0 +
                                                   (prim->v0 << 8);
                        }
                    }
                    assert(nodes == 16);
                    for (int x = PcViewLeft(); x < PcViewRight(); x++)
                        assert(covered[x + 20] ==
                               (x + scroll >= left && x + scroll < right));
                }
                assert(!memcmp(samples[0], samples[1], sizeof(samples[0])));
            }
            DestroyAllPrimitives();
        }
        SDL_UnloadObject(module);
    }
    g_PcSettings.widescreen = 0;
    PcUpdateViewport();
    puts("Caverns/Scylla shimmer covers visible edge fragments without "
         "changing original central texture phase: PASS");
}

static void CheckBackgroundGears(void) {
    extern GameApi g_ApiInit;
    g_api = g_ApiInit;
    const char* stages[] = {"nz1", "rnz1"};
    for (int stage = 0; stage < LEN(stages); stage++) {
        SDL_SharedObject* module = OpenOverlay(stages[stage]);
        void (*update)(Entity*) =
            (void*)SDL_LoadFunction(module, "EntityBackgroundGears");
        assert(update);
        DestroyAllPrimitives();
        Entity* self = g_CurrentEntity = &g_Entities[64];
        memset(self, 0, sizeof(*self));
        update(self);
        assert(self->step && self->primIndex >= 0);
        for (int wide = 0; wide < 2; wide++) {
            g_PcSettings.widescreen = wide;
            PcUpdateViewport();
            for (int phase = 0; phase < 128; phase++) {
                self->posX.i.hi = phase;
                self->posY.i.hi = 127 - phase;
                update(self);
                Primitive* prim = self->ext.prim;
                int u = self->animCurFrame == 2 ? 128 : 0;
                int v = self->animCurFrame == 3 ? 128 : 0;
                for (int row = 0; row < 3; row++) {
                    int left = 1000, right = -1000;
                    for (int column = -1; column < 4;
                         column++, prim = prim->next) {
                        assert(prim && prim->drawMode == DRAW_DEFAULT);
                        assert(prim->x0 == phase - 128 + column * 128);
                        assert(prim->x1 == prim->x0 + 128);
                        assert(prim->y0 == -1 - phase + row * 128);
                        assert(prim->y2 == prim->y0 + 128);
                        assert(prim->u0 == u && prim->u1 == u + 127);
                        assert(prim->v0 == v && prim->v2 == v + 127);
                        assert(prim->tpage == 0xF && prim->clut == 8);
                        if (!wide && (column == -1 || column == 3)) {
                            assert(prim->x1 <= 0 || prim->x0 >= 256);
                        }
                        left = MIN(left, prim->x0);
                        right = MAX(right, prim->x1);
                    }
                    assert(left <= PcViewLeft() && right >= PcViewRight());
                }
                assert(!prim);
            }
        }
        DestroyAllPrimitives();
        SDL_UnloadObject(module);
    }
    g_PcSettings.widescreen = 0;
    PcUpdateViewport();
    puts("Both gear backdrops cover every wrap phase without moving original "
         "quads: PASS");
}

static void CheckBackgroundSkyLand(void) {
    extern GameApi g_ApiInit;
    g_api = g_ApiInit;
    const char* stages[] = {"dai", "rdai", "bo5"};
    for (int stage = 0; stage < LEN(stages); stage++) {
        SDL_SharedObject* module = OpenOverlay(stages[stage]);
        void (*update)(Entity*) =
            (void*)SDL_LoadFunction(module, "EntityBackgroundSkyLand");
        assert(update);
        DestroyAllPrimitives();
        Entity* self = g_CurrentEntity = &g_Entities[64];
        memset(self, 0, sizeof(*self));
        update(self);
        assert(self->step && self->primIndex >= 0);
        for (int toggle = 0; toggle < 4; toggle++) {
            g_PcSettings.widescreen = toggle & 1;
            PcUpdateViewport();
            update(self);
            Primitive* prim = &g_PrimBuf[self->primIndex];
            int left = 1000, right = -1000;
            for (int tile = 0; tile < 6; tile++, prim = prim->next) {
                assert(prim && prim->drawMode == DRAW_DEFAULT);
                int x = tile < 5 ? tile * 62 : -62;
                assert(prim->x0 == x && prim->x2 == x);
                assert(prim->x1 == x + 62 && prim->x3 == x + 62);
                assert(prim->y0 == (stage == 1 ? 64 : 192));
                assert(prim->y2 == (stage == 1 ? 18 : 228));
                assert(prim->u0 == 65 && prim->u2 == 65);
                assert(prim->u1 == 127 && prim->u3 == 127);
                assert(prim->v0 == 169 && prim->v1 == 169);
                assert(prim->v2 == 198 && prim->v3 == 198);
                assert(prim->tpage == 15 && prim->priority == 16);
                if (tile == 5 && !g_PcSettings.widescreen) {
                    assert(prim->x1 <= PcViewLeft());
                }
                left = MIN(left, prim->x0);
                right = MAX(right, prim->x1);
            }
            assert(!prim && left <= PcViewLeft() && right >= PcViewRight());
        }
        DestroyAllPrimitives();
        SDL_UnloadObject(module);
    }
    g_PcSettings.widescreen = 0;
    PcUpdateViewport();
    puts("Chapel and Richter arena sky-land tiles cover both aspects: PASS");
}

static void CheckEntranceFoliage(void) {
    extern GameApi g_ApiInit;
    g_api = g_ApiInit;
    const char* stages[] = {"no3", "np3", "rno3"};
    for (int stage = 0; stage < LEN(stages); stage++) {
        SDL_SharedObject* module = OpenOverlay(stages[stage]);
        for (int trees = 0; trees < 2; trees++) {
            void (*update)(Entity*) = (void*)SDL_LoadFunction(
                module,
                trees ? "EntityBackgroundTrees" : "EntityBackgroundBushes");
            assert(update);
            for (int variant = 0; variant < (trees ? 8 : 2); variant++) {
                DestroyAllPrimitives();
                Entity* self = g_CurrentEntity = &g_Entities[64];
                memset(self, 0, sizeof(*self));
                self->params =
                    trees ? (variant & 3) | (variant / 4) * 256 : variant;
                self->posY.i.hi = stage == 2 ? 104 : 152;
                update(self);
                assert(self->step && self->ext.prim);
                for (int x = -1024; x <= 1024; x += 16) {
                    self->posX.i.hi = x;
                    Primitive reference[72];
                    int referenceCount = 0;
                    for (int mode = 0; mode < 4; mode++) {
                        g_PcSettings.widescreen = mode & 1;
                        PcUpdateViewport();
                        assert(!!PcViewMargin() == (mode & 1));
                        update(self);
                        int nodes = 0, center = 0, left = 10000, right = -10000;
                        Primitive* p = self->ext.prim;
                        for (; p; p = p->next) {
                            assert(++nodes <= (trees ? 32 : 72));
                            if (p->drawMode & DRAW_HIDE)
                                continue;
                            left = MIN(left, p->x0);
                            right = MAX(right, p->x1);
                            if (p->x1 <= 0 || p->x0 >= 256)
                                continue;
                            Primitive copy = *p;
                            Primitive* normalized = &copy;
                            PCOL(normalized) = 0;
                            copy.p1 = copy.p2 = copy.p3 = 0;
                            if (mode == 0)
                                reference[center] = copy;
                            else {
                                assert(center < referenceCount);
                                assert(!memcmp(&reference[center].r0, &copy.r0,
                                               offsetof(Primitive, drawMode) +
                                                   sizeof(copy.drawMode) -
                                                   offsetof(Primitive, r0)));
                            }
                            center++;
                        }
                        assert(nodes == (trees ? 32 : 72));
                        if (mode == 0)
                            referenceCount = center;
                        else
                            assert(center == referenceCount);
                        if (trees)
                            assert(
                                left <= PcViewLeft() && right >= PcViewRight());
                        else if (mode & 1) {
                            SVECTOR zero = {0};
                            VECTOR t = {variant ? x - 512 : x + 512, 0, 1216};
                            MATRIX m;
                            int packed, fog, flags;
                            RotMatrix(&zero, &m);
                            TransMatrix(&m, &t);
                            SetRotMatrix(&m);
                            SetTransMatrix(&m);
                            SetGeomScreen(1024);
                            SetGeomOffset(128, 152);
                            RotTransPers(&zero, &packed, &fog, &flags);
                            int phase = (s16)packed % 128 - 128;
                            if (phase > PcViewLeft()) {
                                bool found = false;
                                for (p = self->ext.prim; p; p = p->next)
                                    if (!(p->drawMode & DRAW_HIDE) &&
                                        p->priority == 0x5E && p->u0 == 0x30 &&
                                        p->x0 == phase - 32 && p->x1 == phase)
                                        found = true;
                                assert(found);
                            }
                        }
                    }
                }
            }
        }
        DestroyAllPrimitives();
        SDL_UnloadObject(module);
    }
    g_PcSettings.widescreen = 0;
    PcUpdateViewport();
    puts("All three Entrance foliage variants retain preceding wide-edge "
         "repeats without shifting the original central image: PASS");
}

static void CheckProjectedBookcases(void) {
    extern GameApi g_ApiInit;
    g_api = g_ApiInit;
    const char* stages[] = {"lib", "rlib"};
    const char* functions[] = {"func_us_801AE8E8", "EntityThickBookcase"};
    SVECTOR vertices[] = {
        {-12, -96, -32}, {12, -96, -32}, {-12, 0, -32}, {12, 0, -32},
        {12, -96, 32},   {-12, -96, 32}, {12, 0, 32},   {-12, 0, 32}};
    const int faces[4][4] = {
        {0, 1, 2, 3}, {4, 5, 6, 7}, {1, 4, 3, 6}, {5, 0, 7, 2}};
    const int depth[] = {0, 60, 64, 88};
    for (int stage = 0; stage < LEN(stages); stage++) {
        SDL_SharedObject* module = OpenOverlay(stages[stage]);
        void (*update)(Entity*) =
            (void*)SDL_LoadFunction(module, functions[stage]);
        assert(update);
        for (int params = 0; params < 4; params++) {
            DestroyAllPrimitives();
            Entity* self = g_CurrentEntity = &g_Entities[64];
            memset(self, 0, sizeof(*self));
            self->params = params;
            self->posX.i.hi = self->posY.i.hi = 128;
            update(self);
            assert(self->flags & FLAG_HAS_PRIMS);
            self->step = 4; // Isolate projection from the push interaction.
            for (int mode = 0; mode < 4; mode++) {
                g_PcSettings.widescreen = mode & 1;
                PcUpdateViewport();
                for (int angle = 0; angle < 4096; angle += 64) {
                    self->ext.et_801AE8E8.unk80 = angle;
                    update(self);
                    if (!params) {
                        Primitive* shadow = self->ext.et_801AE8E8.unk94;
                        assert(shadow && shadow->type == PRIM_G4);
                        assert(shadow->x0 == 128 && shadow->x2 == 128);
                        assert(shadow->x1 == PcViewRight() &&
                               shadow->x3 == PcViewRight());
                        assert(shadow->y0 == 40 && shadow->y1 == 64 &&
                               shadow->y2 == 128 && shadow->y3 == 128);
                    }
                    SVECTOR rotation = {stage ? 2048 : 0, angle, 0};
                    VECTOR translation = {0, 0, 552 + depth[params]};
                    MATRIX matrix;
                    RotMatrix(&rotation, &matrix);
                    TransMatrix(&matrix, &translation);
                    SetRotMatrix(&matrix);
                    SetTransMatrix(&matrix);
                    SetGeomScreen(512);
                    SetGeomOffset(128, 128);
                    int projected[8], fog, flags;
                    for (int i = 0; i < LEN(vertices); i++)
                        RotTransPers(&vertices[i], &projected[i], &fog, &flags);
                    Primitive* p = self->ext.et_801AE8E8.unk7C;
                    int nodes = 0;
                    for (; p; p = p->next, nodes++) {
                        assert(nodes < 37);
                        if (nodes >= 4)
                            continue;
                        assert(p->type == PRIM_GT4);
                        int points[] = {LOW(p->x0), LOW(p->x1), LOW(p->x2),
                                        LOW(p->x3)};
                        const u8* colors[] = {&p->r0, &p->r1, &p->r2, &p->r3};
                        for (int corner = 0; corner < 4; corner++) {
                            assert(points[corner] ==
                                   projected[faces[nodes][corner]]);
                            assert(colors[corner][0] == colors[corner][1] &&
                                   colors[corner][1] == colors[corner][2]);
                        }
                    }
                    assert(nodes == 37);
                }
            }
        }
        DestroyAllPrimitives();
        SDL_UnloadObject(module);
    }
    g_PcSettings.widescreen = 0;
    PcUpdateViewport();
    puts("Both Library bookcases preserve all eight projected vertices and "
         "grayscale lighting through rotation and aspect reversal: PASS");
}

static void CheckBridgeLiquidMargins(void) {
    extern GameApi g_ApiInit;
    g_api = g_ApiInit;
    const char* stages[] = {"cat", "rcat"};
    Tilemap previousTilemap = g_Tilemap;
    int previousTimer = g_Timer;
    for (int stage = 0; stage < LEN(stages); stage++) {
        SDL_SharedObject* module = OpenOverlay(stages[stage]);
        void (*update)(Entity*) = (void*)SDL_LoadFunction(module, "EntityLava");
        assert(update);
        DestroyAllPrimitives();
        Entity* self = g_CurrentEntity = &g_Entities[64];
        memset(self, 0, sizeof(*self));
        self->params = 2;
        self->posY.i.hi = stage ? 64 : 192;
        g_Tilemap.scrollY.val = 0;
        g_Timer = 1;
        update(self);
        assert(self->step == 3 && self->ext.lava.prim);
        Primitive* nodes[30];
        int count = 0;
        for (Primitive* p = self->ext.lava.prim; p; p = p->next) {
            assert(count < LEN(nodes));
            nodes[count++] = p;
        }
        assert(count == LEN(nodes));
        for (int tick = 0; tick < 1024; tick++) {
            for (int i = 1; i < 26; i += 2)
                nodes[i]->x1 += tick < 512 ? -2 : 2;
            g_Timer = tick;
            update(self);
            Entity before = *self;
            Primitive saved[30], reference[26];
            for (int i = 0; i < count; i++)
                saved[i] = *nodes[i];
            for (int mode = 0; mode < 4; mode++) {
                g_PcSettings.widescreen = mode & 1;
                PcUpdateViewport();
                assert(!!PcViewMargin() == (mode & 1));
                *self = before;
                for (int i = 0; i < count; i++)
                    *nodes[i] = saved[i];
                update(self);
                for (int i = 0; i < 26; i++) {
                    if (mode == 0)
                        reference[i] = *nodes[i];
                    else
                        assert(!memcmp(&reference[i].r0, &nodes[i]->r0,
                                       offsetof(Primitive, drawMode) +
                                           sizeof(nodes[i]->drawMode) -
                                           offsetof(Primitive, r0)));
                }
                for (int i = 26; i < count; i++)
                    assert(!!(nodes[i]->drawMode & DRAW_HIDE) == !(mode & 1));
                if (mode & 1) {
                    Primitive* left = nodes[27];
                    Primitive* right = nodes[29];
                    assert(MAX(left->x0, left->x2) <= PcViewLeft());
                    assert(MIN(right->x1, right->x3) >= PcViewRight());
                }
            }
        }
        DestroyAllPrimitives();
        SDL_UnloadObject(module);
    }
    g_Timer = previousTimer;
    g_Tilemap = previousTilemap;
    g_PcSettings.widescreen = 0;
    PcUpdateViewport();
    puts("Both bridge liquid far layers cover wide margins without changing "
         "the original mesh, waves or aspect reversals: PASS");
}

static void CheckLavaGlow(void) {
    extern GameApi g_ApiInit;
    g_api = g_ApiInit;
    SDL_SharedObject* module = OpenOverlay("cat");
    void (*update)(Entity*) = (void*)SDL_LoadFunction(module, "EntityLavaGlow");
    assert(update);
    DestroyAllPrimitives();
    Entity* self = g_CurrentEntity = &g_Entities[64];
    memset(self, 0, sizeof(*self));
    g_PcSettings.widescreen = 0;
    PcUpdateViewport();
    update(self);
    update(self);
    assert(self->step == 2 && self->ext.prim && !self->ext.prim->next);
    Primitive reference = *self->ext.prim;
    for (int mode = 0; mode < 4; mode++) {
        g_PcSettings.widescreen = mode & 1;
        PcUpdateViewport();
        assert(!!PcViewMargin() == (mode & 1));
        update(self);
        Primitive* p = self->ext.prim;
        assert(p->x0 == PcViewLeft() && p->x2 == PcViewLeft());
        assert(p->x1 == PcViewRight() && p->x3 == PcViewRight());
        Primitive normalized = *p;
        normalized.x0 = normalized.x2 = 0;
        normalized.x1 = normalized.x3 = 256;
        assert(!memcmp(&reference.r0, &normalized.r0,
                       offsetof(Primitive, drawMode) + sizeof(p->drawMode) -
                           offsetof(Primitive, r0)));
    }
    DestroyAllPrimitives();
    SDL_UnloadObject(module);
    g_PcSettings.widescreen = 0;
    PcUpdateViewport();
    puts("Lava glow follows aspect reversal without changing its vertical "
         "gradient or blend: PASS");
}

static void CheckCatacombPanels(void) {
    extern GameApi g_ApiInit;
    g_api = g_ApiInit;
    const char* stages[] = {"cat", "rcat"};
    const char* functions[2][2] = {
        {"EntityCavernBackgroundLossoth", "EntityCavernBackgroundDiscusLord"},
        {"EntityCavernBackgroundIce", "EntityCavernBackgroundIceBridge"}};
    Tilemap previousTilemap = g_Tilemap;
    int previousTimer = g_Timer;
    for (int stage = 0; stage < LEN(stages); stage++) {
        SDL_SharedObject* module = OpenOverlay(stages[stage]);
        for (int variant = 0; variant < 2; variant++) {
            void (*update)(Entity*) =
                (void*)SDL_LoadFunction(module, functions[stage][variant]);
            assert(update);
            DestroyAllPrimitives();
            Entity* self = g_CurrentEntity = &g_Entities[64];
            memset(self, 0, sizeof(*self));
            g_Tilemap.scrollY.val = 0;
            g_Timer = 1;
            update(self);
            assert(self->step == 2 && self->ext.prim);
            Primitive* nodes[27];
            Primitive reference[64][27];
            int count = 0;
            for (Primitive* p = self->ext.prim; p; p = p->next) {
                assert(count < LEN(nodes));
                nodes[count++] = p;
            }
            assert(count == LEN(nodes));
            for (int mode = 0; mode < 4; mode++) {
                g_PcSettings.widescreen = mode & 1;
                PcUpdateViewport();
                for (int phase = 0; phase < 64; phase++) {
                    self->posX.i.hi = phase;
                    update(self);
                    for (int row = 0; row < 3; row++) {
                        assert(MAX(nodes[row]->x0, nodes[row]->x2) <= -20);
                        assert(MAX(nodes[row]->x1, nodes[row]->x3) <= 0);
                        assert(MIN(nodes[24 + row]->x0, nodes[24 + row]->x2) >=
                               256);
                        assert(MIN(nodes[24 + row]->x1, nodes[24 + row]->x3) >=
                               276);
                    }
                    for (int i = 0; i < count; i++) {
                        Primitive* p = nodes[i];
                        assert(!(p->drawMode & DRAW_HIDE));
                        assert(p->x0 < p->x1 && p->x2 < p->x3);
                        if (i < count - 3) {
                            Primitive* next = nodes[i + 3];
                            assert(p->x1 == next->x0 && p->y1 == next->y0);
                            assert(p->x3 == next->x2 && p->y3 == next->y2);
                        }
                        if (mode == 0)
                            reference[phase][i] = *p;
                        else
                            assert(!memcmp(&reference[phase][i].r0, &p->r0,
                                           offsetof(Primitive, drawMode) +
                                               sizeof(p->drawMode) -
                                               offsetof(Primitive, r0)));
                    }
                }
            }
        }
        DestroyAllPrimitives();
        SDL_UnloadObject(module);
    }
    g_Timer = previousTimer;
    g_Tilemap = previousTilemap;
    g_PcSettings.widescreen = 0;
    PcUpdateViewport();
    puts("All four Catacombs cave panels cover the wide view through every "
         "horizontal phase and aspect reversal: PASS");
}

static void CheckHouseCulling(void) {
    extern GameApi g_ApiInit;
    g_api = g_ApiInit;
    const char* stages[] = {"no2", "rno2", "dre", "bo0"};
    const int ids[] = {STAGE_NO2, STAGE_RNO2, STAGE_DRE, STAGE_BO0};
    int oldStage = g_StageId;
    for (int stage = 0; stage < LEN(stages); stage++) {
        SDL_SharedObject* module = OpenOverlay(stages[stage]);
        void (*update)(Entity*) =
            (void*)SDL_LoadFunction(module, "Entity3DBackgroundHouse");
        assert(update);
        g_StageId = ids[stage];
        DestroyAllPrimitives();
        Entity* self = g_CurrentEntity = &g_Entities[64];
        memset(self, 0, sizeof(*self));
        self->params = 1;
        self->posY.i.hi = stage == 1 ? 48 : 192;
        update(self);
        assert(self->step && (self->flags & FLAG_HAS_PRIMS));
        for (int mode = 0; mode < 4; mode++) {
            g_PcSettings.widescreen = mode & 1;
            PcUpdateViewport();
            for (int x = 513; x <= 533; x++) {
                self->posX.i.hi = x;
                update(self);
                int nodes = 0, visible = 0;
                for (Primitive* prim = self->ext.bghouse.prim; prim;
                     prim = prim->next) {
                    assert(++nodes <= 16);
                    if (prim->drawMode & DRAW_HIDE)
                        continue;
                    assert((mode & 1) && x <= 532);
                    int left =
                        MIN(MIN(prim->x0, prim->x1), MIN(prim->x2, prim->x3));
                    int right =
                        MAX(MAX(prim->x0, prim->x1), MAX(prim->x2, prim->x3));
                    int top =
                        MIN(MIN(prim->y0, prim->y1), MIN(prim->y2, prim->y3));
                    int bottom =
                        MAX(MAX(prim->y0, prim->y1), MAX(prim->y2, prim->y3));
                    assert(left >= 256);
                    visible += left < PcViewRight() && right > PcViewLeft() &&
                               top < 227 && bottom > 20;
                }
                assert(nodes == 16);
                if ((mode & 1) && x == 513)
                    assert(visible > 0);
            }
        }
        DestroyAllPrimitives();
        SDL_UnloadObject(module);
    }
    g_StageId = oldStage;
    g_PcSettings.widescreen = 0;
    PcUpdateViewport();
    puts("All four house overlays retain far-house faces in the wide margin "
         "without changing original-aspect culling: PASS");
}

static void CheckDreamClouds(void) {
    extern GameApi g_ApiInit;
    g_api = g_ApiInit;
    SDL_SharedObject* module = OpenOverlay("dre");
    void (*update)(Entity*) =
        (void*)SDL_LoadFunction(module, "EntityBackgroundClouds");
    assert(update);
    for (int scroll = 0; scroll <= 256; scroll++) {
        DestroyAllPrimitives();
        Entity* self = g_CurrentEntity = &g_Entities[64];
        memset(self, 0, sizeof(*self));
        g_Tilemap.scrollX.val = FIX(scroll);
        g_Tilemap.scrollY.val = FIX(4);
        update(self);
        assert(self->step && self->primIndex >= 0);
        for (int toggle = 0; toggle < 4; toggle++) {
            g_PcSettings.widescreen = toggle & 1;
            PcUpdateViewport();
            update(self);
            Primitive* prim = self->ext.prim;
            assert(prim && prim->type == PRIM_G4);
            assert(prim->x0 == PcViewLeft() && prim->x1 == PcViewRight());
            assert(prim->y0 == 106 && prim->y2 == 240);
            assert(prim->r0 == 16 && prim->g0 == 16 && prim->b0 == 16);
            prim = prim->next;
            for (int column = -1; column < 6; column++, prim = prim->next) {
                assert(prim);
                int x0 = column * 95 - scroll;
                int x1 = x0 + 95;
                int clipped = column >= 4 && x1 > 256 ? MAX(0, 256 - x0) : 0;
                assert(prim->drawMode ==
                       (column >= 4 && x1 <= 256 ? DRAW_HIDE : DRAW_DEFAULT));
                assert(prim->x0 == x0 + clipped && prim->x1 == x1);
                assert(prim->y0 == 28 && prim->y2 == 106);
                assert(prim->u0 == 132 + clipped && prim->u1 == 227);
                assert(prim->v0 == 1 && prim->v2 == 79);
                assert(prim->tpage == 15 && prim->clut == 5);
                assert(prim->priority == 32);
            }
            assert(!prim && -95 - scroll <= PcViewLeft());
            assert(570 - scroll >= PcViewRight());
        }
    }
    DestroyAllPrimitives();
    SDL_UnloadObject(module);
    g_PcSettings.widescreen = 0;
    g_Tilemap.scrollX.val = g_Tilemap.scrollY.val = 0;
    PcUpdateViewport();
    puts("Dream clouds cover every initial camera offset and aspect toggle: "
         "PASS");
}

static void CheckStainedGlassEdges(void) {
    extern GameApi g_ApiInit;
    g_api = g_ApiInit;
    const char* stages[] = {"dai", "bo5"};
    for (int stage = 0; stage < LEN(stages); stage++) {
        SDL_SharedObject* module = OpenOverlay(stages[stage]);
        Primitive* (*recurse)(SVECTOR*, SVECTOR*, SVECTOR*, SVECTOR*,
                              Primitive*, s32, Primitive*, u8*) =
            (void*)SDL_LoadFunction(module, "StainedGlassRecurseDepth");
        assert(recurse);
        for (int wide = 0; wide < 2; wide++) {
            g_PcSettings.widescreen = wide;
            PcUpdateViewport();
            for (int side = -1; side <= 1; side++) {
                SVECTOR zero = {0};
                VECTOR translation = {0, 0, 1024};
                MATRIX matrix;
                RotMatrix(&zero, &matrix);
                TransMatrix(&matrix, &translation);
                SetRotMatrix(&matrix);
                SetTransMatrix(&matrix);
                SetGeomScreen(1024);
                SetGeomOffset(128, 160);
                SVECTOR points[] = {{side * 138 - 5, 0, 0},
                                    {side * 138 + 5, 0, 0},
                                    {side * 138 - 5, 16, 0},
                                    {side * 138 + 5, 16, 0}};
                for (int depth = 1; depth <= 3; depth++) {
                    Primitive source = {0}, output[9] = {0};
                    u_long scratch[1024];
                    source.type = PRIM_GT4;
                    source.clut = 123;
                    source.u1 = source.u3 = 32;
                    source.v2 = source.v3 = 32;
                    for (int i = 0; i < LEN(output) - 1; i++) {
                        output[i].next = &output[i + 1];
                    }
                    int count = wide || !side ? 1 << depth : 0;
                    assert(recurse(&points[0], &points[1], &points[2],
                                   &points[3], &source, depth, output,
                                   (u8*)scratch) == &output[count]);
                    for (int i = 0; i < count; i++) {
                        assert(output[i].clut == 123);
                        assert(output[i].x0 >= PcViewLeft());
                        assert(output[i].x1 <= PcViewRight());
                        if (side) {
                            assert(output[i].x1 < 0 || output[i].x0 > 256);
                        }
                    }
                }
            }
        }
        void (*update)(Entity*) =
            (void*)SDL_LoadFunction(module, "EntityStainedGlass");
        assert(update);
        DestroyAllPrimitives();
        Entity* self = g_CurrentEntity = &g_Entities[64];
        memset(self, 0, sizeof(*self));
        update(self);
        assert(self->step && self->primIndex >= 0);
        for (int x = -128; x <= 384; x++) {
            Primitive snapshots[2][60];
            int visible[2] = {0};
            for (int wide = 0; wide < 2; wide++) {
                g_PcSettings.widescreen = wide;
                PcUpdateViewport();
                self->posX.i.hi = x;
                self->posY.i.hi = 160;
                update(self);
                int count = 0;
                for (Primitive* prim = &g_PrimBuf[self->primIndex]; prim;
                     prim = prim->next) {
                    assert(++count <= 60);
                    int left =
                        MIN(MIN(prim->x0, prim->x1), MIN(prim->x2, prim->x3));
                    int right =
                        MAX(MAX(prim->x0, prim->x1), MAX(prim->x2, prim->x3));
                    if ((prim->drawMode & DRAW_HIDE) || right < 0 ||
                        left > 256) {
                        continue;
                    }
                    Primitive* copy = &snapshots[wide][visible[wide]++];
                    memset(copy, 0, sizeof(*copy));
                    memcpy(
                        &copy->r0, &prim->r0,
                        offsetof(Primitive, drawMode) + sizeof(prim->drawMode) -
                            offsetof(Primitive, r0));
                    copy->p1 = copy->p2 = copy->p3 = 0;
                }
                assert(count == 60);
            }
            assert(visible[0] == visible[1]);
            assert(!memcmp(
                snapshots[0], snapshots[1], visible[0] * sizeof(Primitive)));
        }
        DestroyAllPrimitives();
        SDL_UnloadObject(module);
    }
    g_PcSettings.widescreen = 0;
    PcUpdateViewport();
    puts("Stained glass keeps wide-edge fragments within its primitive pool: "
         "PASS");
}

static void CheckDistantBookshelves(void) {
    extern GameApi g_ApiInit;
    g_api = g_ApiInit;
    const char* stages[] = {"lib", "rlib"};
    for (int stage = 0; stage < LEN(stages); stage++) {
        SDL_SharedObject* module = OpenOverlay(stages[stage]);
        void (*update)(Entity*) =
            (void*)SDL_LoadFunction(module, "EntityDistantBookshelves");
        assert(update);
        for (int params = 0; params < 4; params++) {
            DestroyAllPrimitives();
            Entity* self = g_CurrentEntity = &g_Entities[64];
            memset(self, 0, sizeof(*self));
            self->params = params;
            update(self);
            assert(self->step && self->primIndex >= 0);
            for (int x = -256; x <= 768; x += 2) {
                for (int wide = 0; wide < 2; wide++) {
                    g_PcSettings.widescreen = wide;
                    PcUpdateViewport();
                    self->posX.i.hi = x;
                    self->posY.i.hi = 128;
                    update(self);
                    Primitive* prim = self->ext.prim;
                    for (int tile = 0; tile < 16; tile++, prim = prim->next) {
                        assert(prim);
                        int x0 = 64 + x / 2 + (tile % 4) * 120 - 240;
                        int hidden =
                            x0 > PcViewRight() || x0 + 120 < PcViewLeft();
                        assert(prim->drawMode ==
                               (hidden ? DRAW_HIDE
                                       : DRAW_DITHERING | DRAW_COLORS));
                        assert(prim->x0 == x0 && prim->x2 == x0);
                        assert(prim->x1 == x0 + 120 && prim->x3 == x0 + 120);
                        assert(prim->y0 == (tile / 4) * 128 - 128);
                        assert(prim->y2 == (tile / 4) * 128);
                        assert(prim->u0 == (tile % 2 ? 136 : 254));
                        assert(prim->u1 == (tile % 2 ? 254 : 136));
                        assert(prim->v0 == (stage ? 254 : 129));
                        assert(prim->v2 == (stage ? 128 : 255));
                        assert(prim->tpage == 15 && prim->clut == 47);
                        assert(prim->priority == 32);
                    }
                    assert(!prim);
                }
            }
        }
        DestroyAllPrimitives();
        SDL_UnloadObject(module);
    }
    g_PcSettings.widescreen = 0;
    PcUpdateViewport();
    puts("Both Libraries keep distant shelves visible across wide margins: "
         "PASS");
}

static void CheckLibraryParallax(void) {
    extern GameApi g_ApiInit;
    g_api = g_ApiInit;
    const char* stages[] = {"lib", "rlib"};
    const char* functions[] = {
        "EntityBackgroundBookcase", "EntityBackgroundFurniture",
        "EntityBackgroundShadow"};
    for (int stage = 0; stage < LEN(stages); stage++) {
        SDL_SharedObject* module = OpenOverlay(stages[stage]);
        for (int kind = 0; kind < LEN(functions); kind++) {
            void (*update)(Entity*) =
                (void*)SDL_LoadFunction(module, functions[kind]);
            assert(update);
            DestroyAllPrimitives();
            Entity* self = g_CurrentEntity = &g_Entities[64];
            memset(self, 0, sizeof(*self));
            update(self);
            assert(self->step && self->primIndex >= 0);
            for (int x = -256; x <= 768; x++) {
                for (int toggle = 0; toggle < 4; toggle++) {
                    g_PcSettings.widescreen = toggle & 1;
                    PcUpdateViewport();
                    self->posX.i.hi = x;
                    self->posY.i.hi = 160;
                    update(self);
                    Primitive* prim = kind == 2 ? self->ext.libraryShadow.prim
                                                : self->ext.prim;
                    int start = prim->x0, right = start;
                    int stride = kind == 0 ? 124 : kind == 1 ? 120 : 56;
                    int count = kind == 2 ? 9 : 4;
                    for (int tile = 0; tile < count;
                         tile++, prim = prim->next) {
                        assert(prim);
                        if (start + tile * stride > PcViewRight()) {
                            assert(prim->drawMode == DRAW_HIDE);
                            continue;
                        }
                        assert(!(prim->drawMode & DRAW_HIDE));
                        assert(prim->x0 == start + tile * stride);
                        if (kind != 2) {
                            assert(prim->x1 == prim->x0 + stride);
                            right = prim->x1;
                        } else {
                            assert(prim->u0 == 24 && prim->v0 == 64);
                        }
                    }
                    assert(start <= PcViewLeft());
                    if (kind != 2) {
                        assert(!prim && right >= PcViewRight());
                    } else {
                        assert(prim == self->ext.libraryShadow.lastPrim);
                        assert(!prim->next && prim->y0 == (stage ? 224 : 48));
                        assert(prim->drawMode & DRAW_TRANSP);
                        if (g_PcSettings.widescreen) {
                            assert(prim->type == PRIM_G4_ALT);
                            assert(prim->x0 == PcViewLeft());
                            assert(prim->x1 == PcViewRight());
                            assert(prim->y2 == prim->y0 + 48);
                            assert(
                                !(prim->r0 | prim->g0 | prim->b0 | prim->r1 |
                                  prim->g1 | prim->b1 | prim->r2 | prim->g2 |
                                  prim->b2 | prim->r3 | prim->g3 | prim->b3));
                        } else {
                            assert(prim->type == PRIM_TILE_ALT);
                            assert(prim->x0 == 0 && prim->u0 == 255);
                            assert(prim->v0 == 48);
                        }
                    }
                }
            }
        }
        DestroyAllPrimitives();
        SDL_UnloadObject(module);
    }
    g_PcSettings.widescreen = 0;
    PcUpdateViewport();
    puts("Library bookcases, furniture and shadows cover all parallax phases: "
         "PASS");
}

static void CheckBackgroundArches(void) {
    extern GameApi g_ApiInit;
    g_api = g_ApiInit;
    SDL_SharedObject* module = OpenOverlay("rno2");
    void (*update)(Entity*) =
        (void*)SDL_LoadFunction(module, "EntityDeepBackgroundArch");
    assert(update);
    for (int params = 0; params < 2; params++) {
        DestroyAllPrimitives();
        Entity* self = g_CurrentEntity = &g_Entities[64];
        memset(self, 0, sizeof(*self));
        self->params = params;
        g_PcSettings.widescreen = 0;
        PcUpdateViewport();
        update(self);
        assert(self->step && self->primIndex >= 0);
        int count = params ? 32 : 8;
        Primitive originals[32];
        Primitive* prim = &g_PrimBuf[self->primIndex];
        for (int i = 0; i < count; i++, prim = prim->next) {
            assert(prim);
            originals[i] = *prim;
        }
        const int modes[] = {1, 0, 1};
        for (int mode = 0; mode < LEN(modes); mode++) {
            g_PcSettings.widescreen = modes[mode];
            PcUpdateViewport();
            update(self);
            prim = &g_PrimBuf[self->primIndex];
            for (int i = 0; i < count; i++, prim = prim->next) {
                assert(!memcmp(prim, &originals[i], sizeof(*prim)));
            }
            for (int row = 0; row < (params ? 4 : 1);
                 row++, prim = prim->next) {
                assert(prim && prim->x0 == PcViewLeft() && prim->x1 == 0);
                assert(prim->x2 == prim->x0 && prim->x3 == 0);
                assert(prim->u0 - prim->u1 == PcViewMargin());
                assert(prim->u2 == prim->u0 && prim->u3 == prim->u1);
                assert(prim->y0 == (params ? -128 : 48) + row * 100);
                assert(prim->y2 - prim->y0 == 108);
                assert(
                    prim->drawMode == (modes[mode] ? DRAW_DEFAULT : DRAW_HIDE));
            }
            assert(!prim);
        }
    }
    DestroyAllPrimitives();
    SDL_UnloadObject(module);
    g_PcSettings.widescreen = 0;
    PcUpdateViewport();
    puts("Background arches fill the left margin and preserve original "
         "geometry: PASS");
}

static void CheckBackgroundVortex(void) {
    extern GameApi g_ApiInit;
    g_api = g_ApiInit;
    SDL_SharedObject* module = OpenOverlay("st0");
    void (*update)(Entity*) =
        (void*)SDL_LoadFunction(module, "EntityBackgroundVortex");
    assert(update);
    GpuBuffer* oldBuffer = g_CurrentBuffer;
    g_CurrentBuffer = &g_GpuBuffers[0];
    DRAWENV oldDraw = g_CurrentBuffer->draw;
    SetDefDrawEnv(&g_CurrentBuffer->draw, 0, 0, 256, 240);
    DestroyAllPrimitives();
    func_800EDAE4();
    Entity* self = g_CurrentEntity = &g_Entities[64];
    memset(self, 0, sizeof(*self));
    update(self);
    update(self);
    assert(self->step == 3 && self->primIndex >= 0);
    Primitive* nodes[272];
    Primitive originals[272];
    Primitive* prim = self->ext.bgVortex.prim;
    for (int i = 0; i < LEN(nodes); i++, prim = prim->next) {
        assert(prim);
        nodes[i] = prim;
    }
    assert(!prim && nodes[0]->type == PRIM_ENV && nodes[1]->type == PRIM_ENV);
    int margins = 0;
    for (int frame = 0; frame < 1024; frame++) {
        Entity before = *self;
        for (int i = 0; i < LEN(nodes); i++) {
            originals[i] = *nodes[i];
        }
        Primitive core[2][240];
        int count[2] = {0};
        for (int wide = 0; wide < 2; wide++) {
            *self = before;
            for (int i = 0; i < LEN(nodes); i++) {
                *nodes[i] = originals[i];
            }
            g_PcSettings.widescreen = wide;
            PcUpdateViewport();
            update(self);
            for (int i = 2; i < LEN(nodes); i++) {
                prim = nodes[i];
                if (prim->drawMode & DRAW_HIDE) {
                    continue;
                }
                assert(prim->type == PRIM_GT4);
                int left =
                    MIN(MIN(prim->x0, prim->x1), MIN(prim->x2, prim->x3));
                int right =
                    MAX(MAX(prim->x0, prim->x1), MAX(prim->x2, prim->x3));
                if (right < 0 || left > 256) {
                    assert(
                        wide && right >= PcViewLeft() && left <= PcViewRight());
                    margins++;
                    continue;
                }
                assert(count[wide] < LEN(core[wide]));
                Primitive* copy = &core[wide][count[wide]++];
                memset(copy, 0, sizeof(*copy));
                memcpy(&copy->r0, &prim->r0,
                       offsetof(Primitive, drawMode) + sizeof(prim->drawMode) -
                           offsetof(Primitive, r0));
                copy->p1 = copy->p2 = copy->p3 = 0;
            }
        }
        assert(count[0] == count[1]);
        assert(!memcmp(core[0], core[1], count[0] * sizeof(Primitive)));
    }
    assert(margins > 0);
    DestroyAllPrimitives();
    func_800EDAE4();
    SDL_UnloadObject(module);
    g_CurrentBuffer->draw = oldDraw;
    g_CurrentBuffer = oldBuffer;
    g_PcSettings.widescreen = 0;
    PcUpdateViewport();
    printf("Vortex preserves its original mesh over 1024 frames with %d "
           "extra wide-edge fragments: PASS\n",
           margins);
}

static void CheckDrawAreaCapture(void) {
    DISPENV oldDisplay, display;
    DRAWENV oldDraw, draw;
    GetDispEnv(&oldDisplay);
    GetDrawEnv(&oldDraw);
    unsigned previousResolution = Psyz_VideoGetInternalResolution();
    for (int resolution = 1; resolution <= 4; resolution *= 2) {
        assert(!Psyz_VideoSetInternalResolution(resolution));
        for (int fb = 0; fb < 2; fb++) {
            SetDefDispEnv(&display, fb * 256, 0, 256, 240);
            SetDefDrawEnv(&draw, fb * 256, 0, 256, 240);
            draw.isbg = 0;
            PutDispEnv(&display);
            PutDrawEnv(&draw);
            g_PcSettings.widescreen = 1;
            PcUpdateViewport();
            TILE bands[3];
            const int starts[] = {-20, 0, 256}, widths[] = {20, 256, 20};
            const u16 expected[] = {0x001F, 0x03E0, 0x7C00};
            for (int i = 0; i < 3; i++) {
                setTile(&bands[i]);
                setXY0(&bands[i], starts[i], 20);
                setWH(&bands[i], widths[i], 207);
                setRGB0(&bands[i], i == 0 ? 248 : 0, i == 1 ? 248 : 0,
                        i == 2 ? 248 : 0);
            }
            DR_ENV capture;
            setlen(&capture, 12);
            for (int i = 0; i < 3; i++) {
                int x = i == 2 ? 271 : starts[i];
                capture.code[i * 4] = (u_long)PC_COPY_DRAW_AREA_OPCODE << 24;
                capture.code[i * 4 + 1] = (20 << 16) | (u16)x;
                capture.code[i * 4 + 2] = 768 + i * 16;
                capture.code[i * 4 + 3] = (6 << 16) | 5;
            }
            // A later overlay must not appear in the saved background.
            TILE overlay;
            setTile(&overlay);
            setXY0(&overlay, -20, 20);
            setWH(&overlay, 296, 207);
            setRGB0(&overlay, 248, 248, 248);
            OT_TYPE ot[1];
            ClearOTagR(ot, 1);
            addPrim(ot, &overlay);
            addPrim(ot, &capture);
            for (int i = 2; i >= 0; i--)
                addPrim(ot, &bands[i]);
            DrawOTag(ot);
            DrawSync(0);
            u16 pixels[48 * 6];
            RECT saved = {768, 0, 48, 6};
            StoreImage(&saved, (u_long*)pixels);
            DrawSync(0);
            for (int i = 0; i < 3; i++)
                for (int y = 0; y < 6; y++)
                    for (int x = 0; x < 5; x++) {
                        assert((pixels[y * 48 + i * 16 + x] & 0x7FFF) ==
                               expected[i]);
                    }
            assert(Psyz_VideoCopyDrawArea((PsyzRect){-21, 20, 0, 26}, 768, 0) ==
                   -1);
            assert(Psyz_VideoCopyDrawArea((PsyzRect){0, 20, 5, 26}, 1020, 0) ==
                   -1);
        }
    }
    assert(!Psyz_VideoSetInternalResolution(previousResolution));
    PutDrawEnv(&oldDraw);
    PutDispEnv(&oldDisplay);
    DrawSync(0);
    g_PcSettings.widescreen = 0;
    PcUpdateViewport();
    puts("Ordered GPU capture includes both native margins and excludes later "
         "overlays on both framebuffers at 1x/2x/4x: PASS");
}

static void CheckBackgroundDematerialize(void) {
    extern GameApi g_ApiInit;
    g_api = g_ApiInit;
    SDL_SharedObject* module = OpenOverlay("st0");
    void (*update)(Entity*) =
        (void*)SDL_LoadFunction(module, "EntityDematerializeStageBg");
    assert(update);
    GpuBuffer* oldBuffer = g_CurrentBuffer;
    g_CurrentBuffer = &g_GpuBuffers[0];
    DRAWENV oldDraw = g_CurrentBuffer->draw;
    SetDefDrawEnv(&g_CurrentBuffer->draw, 0, 0, 256, 240);
    u32 randomAfter[2];
    int lifetime[2], vortexFrame[2] = {0};
    for (int wide = 0; wide < 2; wide++) {
        g_PcSettings.widescreen = wide;
        PcUpdateViewport();
        DestroyAllPrimitives();
        func_800EDAE4();
        Entity* self = g_CurrentEntity = &g_Entities[64];
        memset(self, 0, sizeof(*self) * 2);
        self->entityId = 35;
        g_randomNext = 0x12345678;
        update(self);
        update(self);
        assert(self->step == 4);
        g_PcSettings.widescreen = !wide;
        PcUpdateViewport();
        assert(PcViewportChangePending() && !!PcViewMargin() == wide);
        int atlas[256][256];
        memset(atlas, -1, sizeof(atlas));
        if (wide) {
            unsigned char covered[207][296] = {0};
            Primitive* prim = self->ext.prim;
            int commands = 0;
            for (int n = 0; n < 4; n++, prim = prim->next) {
                assert(
                    prim && prim->type == PRIM_ENV && prim->priority == 0x69);
                DR_ENV* env = PRIM_DR_ENV(prim);
                int length = getlen(env);
                assert(length == (n == 3 ? 8 : 12));
                for (int j = 0; j < length; j += 4) {
                    assert(
                        env->code[j] == (u_long)PC_COPY_DRAW_AREA_OPCODE << 24);
                    int sx = (short)env->code[j + 1];
                    int sy = (short)(env->code[j + 1] >> 16);
                    int dx = (unsigned short)env->code[j + 2] - 768;
                    int dy = (unsigned short)(env->code[j + 2] >> 16);
                    int w = (unsigned short)env->code[j + 3];
                    int h = (unsigned short)(env->code[j + 3] >> 16);
                    assert(sx >= -20 && sx + w <= 276 && sy >= 20 &&
                           sy + h <= 227);
                    assert(
                        dx >= 0 && dx + w <= 256 && dy >= 0 && dy + h <= 256);
                    for (int y = 0; y < h; y++) {
                        for (int x = 0; x < w; x++) {
                            assert(!covered[sy + y - 20][sx + x + 20]++);
                            assert(atlas[dy + y][dx + x] == -1);
                            atlas[dy + y][dx + x] =
                                (sy + y) * 296 + sx + x + 20;
                        }
                    }
                    commands++;
                }
            }
            assert(commands == 11);
            for (int y = 0; y < 207; y++)
                for (int x = 0; x < 296; x++)
                    assert(covered[y][x] == 1);
        }
        update(self);
        assert(self->step == 5);
        Primitive* prim = self->ext.prim;
        int count = 0;
        unsigned char reconstructed[207][296] = {0};
        for (; prim; prim = prim->next, count++) {
            assert(prim->type == PRIM_GT4 && prim->tpage == 0x10C);
            if (!wide || (prim->drawMode & DRAW_HIDE))
                continue;
            assert(prim->x0 >= -20 && prim->x1 <= 276);
            assert(prim->y0 >= 20 && prim->y2 <= 227);
            assert(prim->u1 - prim->u0 == prim->x1 - prim->x0);
            assert(prim->v2 - prim->v0 == prim->y2 - prim->y0);
            for (int y = prim->y0; y < prim->y2; y++) {
                for (int x = prim->x0; x < prim->x1; x++) {
                    int u = prim->u0 + x - prim->x0;
                    int v = prim->v0 + y - prim->y0;
                    assert(atlas[v][u] == y * 296 + x + 20);
                    assert(!reconstructed[y - 20][x + 20]++);
                }
            }
        }
        assert(count == (wide ? 285 : 225));
        if (wide)
            for (int y = 0; y < 207; y++)
                for (int x = 0; x < 296; x++)
                    assert(reconstructed[y][x] == 1);
        update(self);
        assert(self->step == 6);
        randomAfter[wide] = g_randomNext;
        for (lifetime[wide] = 1; self->step; lifetime[wide]++) {
            assert(lifetime[wide] < 512);
            update(self);
            PcUpdateViewport();
            assert(!!PcViewMargin() == (self->step ? wide : !wide));
            if (self[1].entityId && !vortexFrame[wide])
                vortexFrame[wide] = lifetime[wide];
        }
        assert(vortexFrame[wide] && !PcViewportChangePending());
    }
    assert(randomAfter[0] == randomAfter[1]);
    assert(lifetime[0] == lifetime[1] && vortexFrame[0] == vortexFrame[1]);
    g_PcSettings.widescreen = 1;
    PcUpdateViewport();
    for (int freeEnvs = 0; freeEnvs < 4; freeEnvs++) {
        DestroyAllPrimitives();
        func_800EDAE4();
        for (int i = freeEnvs; i < LEN(D_800974AC); i++)
            D_800974AC[i].tag = 1;
        Entity* self = g_CurrentEntity = &g_Entities[64];
        memset(self, 0, sizeof(*self) * 2);
        update(self);
        update(self);
        assert(self->step == 7);
        update(self);
        assert(!self->step && self[1].entityId);
        for (int i = 0; i < MAX_PRIM_COUNT; i++)
            assert(!g_PrimBuf[i].type);
        for (int i = 0; i < LEN(D_800974AC); i++)
            assert(D_800974AC[i].tag == (i < freeEnvs ? 0 : 1));
    }
    DestroyAllPrimitives();
    func_800EDAE4();
    SDL_UnloadObject(module);
    g_CurrentBuffer->draw = oldDraw;
    g_CurrentBuffer = oldBuffer;
    g_PcSettings.widescreen = 0;
    PcUpdateViewport();
    puts("Room breakup captures and reconstructs all 61272 visible pixels, "
         "preserving RNG and transition timing: PASS");
}

static void CheckWidePhotograph(void) {
    extern GameApi g_ApiInit;
    g_api = g_ApiInit;
    SDL_SharedObject* module = OpenOverlay("st0");
    void (*update)(Entity*) =
        (void*)SDL_LoadFunction(module, "EntityCutscenePhotograph");
    assert(update);
    GpuBuffer* oldBuffer = g_CurrentBuffer;
    g_CurrentBuffer = &g_GpuBuffers[0];
    DRAWENV oldDraw = g_CurrentBuffer->draw;
    SetDefDrawEnv(&g_CurrentBuffer->draw, 0, 0, 256, 240);
    int transitions[2][13];
    memset(transitions, -1, sizeof(transitions));
    u32 randomAfter[2];
    for (int wide = 0; wide < 2; wide++) {
        DestroyEntitiesFromIndex(1);
        DestroyAllPrimitives();
        func_800EDAE4();
        g_PcSettings.widescreen = wide;
        g_GameEngineStep = Engine_Normal;
        PcUpdateViewport();
        Entity* self = g_CurrentEntity = &g_Entities[255];
        memset(self, 0, sizeof(*self));
        self->entityId = 44;
        g_randomNext = 0x12345678;
        int atlas[256][256];
        memset(atlas, -1, sizeof(atlas));
        for (int frame = 0; g_GameEngineStep != Engine_10; frame++) {
            assert(frame < 1024);
            update(self);
            assert(self->step <= 12);
            if (!frame) {
                g_PcSettings.widescreen = !wide;
                PcUpdateViewport();
            }
            PcUpdateViewport();
            assert(PcViewportChangePending() && !!PcViewMargin() == wide);
            int first = transitions[wide][self->step] < 0;
            if (first)
                transitions[wide][self->step] = frame;
            Primitive* nodes[24];
            Primitive* prim = self->ext.cutscenePhoto.prim;
            int count = 0;
            for (; prim; prim = prim->next) {
                assert(count < LEN(nodes));
                nodes[count++] = prim;
            }
            assert(count == (wide ? 24 : 8));
            if (wide && self->step == 2 && first) {
                unsigned char covered[207][296] = {0};
                for (int i = 8; i < 12; i++) {
                    assert(nodes[i]->type == PRIM_ENV &&
                           nodes[i]->priority == 0x1F7);
                    DR_ENV* env = PRIM_DR_ENV(nodes[i]);
                    int length = getlen(env);
                    assert(length == (i == 11 ? 8 : 12));
                    for (int j = 0; j < length; j += 4) {
                        assert(env->code[j] ==
                               (u_long)PC_COPY_DRAW_AREA_OPCODE << 24);
                        int sx = (short)env->code[j + 1],
                            sy = (short)(env->code[j + 1] >> 16);
                        int dx = (unsigned short)env->code[j + 2] - 768;
                        int dy = (unsigned short)(env->code[j + 2] >> 16);
                        int w = (unsigned short)env->code[j + 3],
                            h = (unsigned short)(env->code[j + 3] >> 16);
                        assert(sx >= -20 && sx + w <= 276 && sy >= 20 &&
                               sy + h <= 227);
                        assert(dx >= 0 && dx + w <= 256 && dy >= 0 &&
                               dy + h <= 256);
                        for (int y = 0; y < h; y++)
                            for (int x = 0; x < w; x++) {
                                assert(atlas[dy + y][dx + x] == -1);
                                atlas[dy + y][dx + x] =
                                    (sy + y) * 296 + sx + x + 20;
                            }
                    }
                }
                for (int i = 0; i < 12; i++) {
                    prim = nodes[i ? 12 + i - 1 : 0];
                    assert(prim->u1 - prim->u0 == prim->x1 - prim->x0);
                    assert(prim->v2 - prim->v0 == prim->y2 - prim->y0);
                    for (int y = prim->y0; y < prim->y2; y++)
                        for (int x = prim->x0; x < prim->x1; x++) {
                            int u = prim->u0 + x - prim->x0,
                                v = prim->v0 + y - prim->y0;
                            assert(atlas[v][u] == y * 296 + x + 20);
                            assert(!covered[y - 20][x + 20]++);
                        }
                }
                for (int y = 0; y < 207; y++)
                    for (int x = 0; x < 296; x++)
                        assert(covered[y][x] == 1);
            }
            if (wide &&
                (self->step == 2 || self->step == 5 || self->step == 6)) {
                for (int i = 0; i < 12; i++) {
                    prim = nodes[i ? 12 + i - 1 : 0];
                    Primitive adjusted = *prim;
                    PcAdjustPrimitive(&adjusted);
                    assert(!memcmp(prim, &adjusted, sizeof(*prim)));
                    assert(prim->tpage == 0x10C && prim->priority == 0x1F8);
                    assert(prim->r0 == nodes[0]->r0 &&
                           prim->g0 == nodes[0]->g0 &&
                           prim->b0 == nodes[0]->b0);
                }
            }
            if (wide && self->step == 5 && first) {
                for (int i = 8; i < 12; i++)
                    assert(nodes[i]->type == PRIM_GT4 &&
                           nodes[i]->drawMode == DRAW_HIDE);
                assert(nodes[23]->x0 == -26 && nodes[23]->x1 == 282);
                assert(nodes[23]->y0 == 14 && nodes[23]->y2 == 233);
            }
            if (wide && self->step == 7 && first) {
                assert(nodes[1]->x1 == 128 && nodes[5]->x0 == 128);
                for (int i = 1; i <= 5; i += 4) {
                    Primitive adjusted = *nodes[i];
                    PcAdjustPrimitive(&adjusted);
                    assert(!memcmp(nodes[i], &adjusted, sizeof(adjusted)));
                }
            }
            if (wide && self->step == 8 && first) {
                assert(nodes[5]->drawMode == DRAW_HIDE);
                prim = nodes[0];
                assert(prim->tpage == 0x110);
                assert(prim->u0 == prim->x0 && prim->u1 == prim->x1);
                assert(prim->u2 == prim->x2 && prim->u3 == prim->x3);
                for (int i = 12; i < 24; i++)
                    assert(nodes[i]->drawMode == DRAW_HIDE);
                int left =
                    MIN(MIN(prim->x0, prim->x1), MIN(prim->x2, prim->x3));
                int right =
                    MAX(MAX(prim->x0, prim->x1), MAX(prim->x2, prim->x3));
                int top = MIN(MIN(prim->y0, prim->y1), MIN(prim->y2, prim->y3));
                int bottom =
                    MAX(MAX(prim->y0, prim->y1), MAX(prim->y2, prim->y3));
                assert(left >= 0 && right < 256 && top >= 0 && bottom < 256);
                assert(nodes[4]->x0 == left && nodes[4]->y0 == top);
                assert(nodes[4]->u0 == right - left &&
                       nodes[4]->v0 == bottom - top);
            }
        }
        randomAfter[wide] = g_randomNext;
    }
    assert(!memcmp(transitions[0], transitions[1], sizeof(transitions[0])));
    assert(randomAfter[0] == randomAfter[1]);
    g_PcSettings.widescreen = 1;
    PcUpdateViewport();
    for (int freeEnvs = 0; freeEnvs < 4; freeEnvs++) {
        DestroyEntitiesFromIndex(1);
        DestroyAllPrimitives();
        func_800EDAE4();
        for (int i = freeEnvs; i < LEN(D_800974AC); i++)
            D_800974AC[i].tag = 1;
        g_GameEngineStep = Engine_Normal;
        Entity* self = g_CurrentEntity = &g_Entities[255];
        memset(self, 0, sizeof(*self));
        self->entityId = 44;
        update(self);
        assert(self->step == 12);
        for (int i = 0; i < LEN(D_800974AC); i++)
            assert(D_800974AC[i].tag == (i < freeEnvs ? 0 : 1));
        update(self);
        assert(g_GameEngineStep == Engine_10);
    }
    DestroyEntitiesFromIndex(1);
    DestroyAllPrimitives();
    func_800EDAE4();
    SDL_UnloadObject(module);
    g_CurrentBuffer->draw = oldDraw;
    g_CurrentBuffer = oldBuffer;
    g_GameEngineStep = Engine_Normal;
    g_PcSettings.widescreen = 0;
    PcUpdateViewport();
    puts("Photograph preserves every wide-view pixel, projection, burn bounds, "
         "randomness and original phase timing: PASS");
}

static void CheckCaptureViewportLifetime(void) {
    Entity* owner = &g_Entities[254];
    Entity oldOwner = *owner;
    int oldStage = g_StageId, oldState = g_GameState, oldStep = g_GameStep;
    for (int wide = 0; wide < 2; wide++) {
        for (int invalidation = 0; invalidation < 5; invalidation++) {
            memset(owner, 0, sizeof(*owner));
            PcUpdateViewport();
            g_StageId = STAGE_ST0;
            g_GameState = Game_Play;
            g_GameStep = Play_Default;
            g_PcSettings.widescreen = wide;
            PcUpdateViewport();
            owner->entityId = 35;
            PcHoldViewport(owner);
            g_PcSettings.widescreen = !wide;
            PcUpdateViewport();
            assert(!!PcViewMargin() == wide && PcViewportChangePending());
            assert(g_PcSettings.widescreen == !wide);
            g_PcSettings.widescreen = wide;
            assert(!PcViewportChangePending());
            g_PcSettings.widescreen = !wide;
            switch (invalidation) {
            case 0:
                owner->entityId = 0;
                break;
            case 1:
                owner->entityId = 36;
                break;
            case 2:
                g_StageId = STAGE_NO3;
                break;
            case 3:
                g_GameState = Game_GameOver;
                break;
            case 4:
                g_GameStep = 0;
                break;
            }
            PcUpdateViewport();
            assert(!PcViewportChangePending());
            g_StageId = STAGE_ST0;
            g_GameState = Game_Play;
            g_GameStep = Play_Default;
            owner->entityId = 35;
            PcUpdateViewport();
            assert(!!PcViewMargin() == !wide && !PcViewportChangePending());
        }
    }
    *owner = oldOwner;
    g_StageId = oldStage;
    g_GameState = oldState;
    g_GameStep = oldStep;
    g_PcSettings.widescreen = 0;
    PcUpdateViewport();
    puts("Capture aspect changes defer in both directions and release on "
         "entity, stage or game-state exit: PASS");
}

static int s_SpawnLoadMode, s_SpawnCallbacks;

static void CheckSpawnRoomInit(s32 layoutId) {
    assert(layoutId == 7 && D_8003C730 == s_SpawnLoadMode);
    assert(g_PlayerX == 600 && g_PlayerY == 168);
    s_SpawnCallbacks++;
}

static void CheckSpawnLoadMode(void) {
    RoomHeader rooms[2] = {{0}, {.left = 64}};
    RoomHeader* oldRooms = g_api.o.rooms;
    Tilemap oldTilemap = g_Tilemap;
    Entity oldPlayer = PLAYER;
    Point32 oldCell = D_8009791C;
    int oldX = g_PlayerX, oldY = g_PlayerY;
    int oldPrevX = g_PrevScrollX, oldPrevY = g_PrevScrollY;
    int oldMode = D_8003C730, oldStage = g_StageId;
    int oldState = g_GameState, oldStep = g_GameStep;
    g_StageId = STAGE_ST0;
    g_GameState = Game_Play;
    g_GameStep = Play_Default;
    g_api.o.rooms = rooms;
    struct InitGameParams params = {.spawnPoint = "prologue-dracula-dialogue"};
    s_SpawnCallbacks = 0;
    for (int mode = 0; mode < 4; mode++) {
        D_8003C730 = s_SpawnLoadMode = mode;
        SpawnPoint_Init(&params);
        Overlay overlay = {.InitRoomEntities = CheckSpawnRoomInit};
        SpawnPoint_HookOverlay(&overlay);
        SpawnPoint_OnFrame();
        assert(D_8003C730 == 1);
        overlay.InitRoomEntities(7);
        assert(D_8003C730 == mode);
    }
    assert(s_SpawnCallbacks == 4);
    params.spawnPoint = NULL;
    SpawnPoint_Init(&params);
    g_api.o.rooms = oldRooms;
    g_Tilemap = oldTilemap;
    PLAYER = oldPlayer;
    D_8009791C = oldCell;
    g_PlayerX = oldX;
    g_PlayerY = oldY;
    g_PrevScrollX = oldPrevX;
    g_PrevScrollY = oldPrevY;
    D_8003C730 = oldMode;
    g_StageId = oldStage;
    g_GameState = oldState;
    g_GameStep = oldStep;
    puts("Diagnostic spawn restores its temporary load mode before normal "
         "room/entity initialization: PASS");
}

static void CheckRichterHud(void) {
    extern void DrawHud(void);
    extern void DrawRichterHudSubweapon(void);
    DestroyAllPrimitives();
    g_StageId = STAGE_ST0;
    g_Status.hp = g_Status.hpMax = 100;
    g_Status.subWeapon = 0;
    g_Status.hearts = 10;
    DrawHud();
    g_Entities[80].hitPoints = 100;
    g_Entities[85].hitPoints = 0;
    for (s32 tick = 0; tick < 260; tick++) {
        if (tick <= 100) {
            g_Status.hp = g_Entities[80].hitPoints = 100 - tick;
            D_8003C744 = 1;
        } else {
            D_8003C744 = 3;
        }
        DrawRichterHudSubweapon();
        for (s32 mode = 0; mode < 4; mode++) {
            g_PcSettings.widescreen = mode & 1;
            PcUpdateViewport();
            assert(!!PcViewMargin() == (mode & 1));
            for (s32 i = 0; i < MAX_PRIM_COUNT; i++) {
                Primitive original = g_PrimBuf[i];
                if (!original.type || !(original.drawMode & DRAW_ABSPOS)) {
                    continue;
                }
                Primitive adjusted = original;
                PcAdjustPrimitive(&adjusted);
                s32 delta =
                    original.x0 < 128 ? PcViewLeft() : PcViewRight() - 256;
                assert(adjusted.x0 == original.x0 + delta);
                assert(adjusted.x1 == original.x1 + delta);
                assert(adjusted.x2 == original.x2 + delta);
                assert(adjusted.x3 == original.x3 + delta);
                adjusted.x0 -= delta;
                adjusted.x1 -= delta;
                adjusted.x2 -= delta;
                adjusted.x3 -= delta;
                assert(!memcmp(&adjusted, &original, sizeof(original)));
            }
        }
    }
    DestroyAllPrimitives();
    g_PcSettings.widescreen = 0;
    PcUpdateViewport();
    puts("Richter HP/boss fills and falling frame retain HUD anchors: PASS");
}

static void CheckCornerPopups(void) {
    extern GameApi g_ApiInit;
    GameApi previousApi = g_api;
    int previousStage = g_StageId;
    g_api = g_ApiInit;
    g_StageId = STAGE_LIB;
    SDL_SharedObject* module = OpenOverlay("lib");
    void (*popup)(u8*, u8) =
        (void*)SDL_LoadFunction(module, "BottomCornerText");
    const char** gold = (void*)SDL_LoadFunction(module, "g_goldCollectTexts");
    assert(popup && gold);
    const char* names[] = {g_EquipDefs[ITEM_BADELAIRE].name,
                           g_EquipDefs[ITEM_POTION].name, gold[0]};
    for (int name = 0; name < LEN(names); name++) {
        for (int align = 0; align < 2; align++) {
            DestroyAllPrimitives();
            popup((u8*)names[name], align);
            assert(g_unkGraphicsStruct.BottomCornerTextTimer);
            for (int wide = 0; wide < 2; wide++) {
                g_PcSettings.widescreen = wide;
                PcUpdateViewport();
                for (int scale = 100; scale <= 150; scale += 25) {
                    g_PcSettings.hudScale = scale;
                    Primitive* prim =
                        &g_PrimBuf[g_unkGraphicsStruct.BottomCornerTextPrims];
                    int count = 0;
                    for (; prim; prim = prim->next) {
                        Primitive adjusted = *prim;
                        PcAdjustPrimitive(&adjusted);
                        assert(!memcmp(&adjusted, prim, sizeof(adjusted)));
                        count++;
                    }
                    assert(count > 4);
                }
            }
        }
    }
    DestroyAllPrimitives();
    g_unkGraphicsStruct.BottomCornerTextTimer = 0;
    g_PcSettings.hudScale = 100;
    g_PcSettings.widescreen = 0;
    PcUpdateViewport();
    SDL_UnloadObject(module);
    g_api = previousApi;
    g_StageId = previousStage;
    puts("Pickup/gold and enemy-name banners retain their frame, background "
         "and text alignment at every HUD scale and aspect: PASS");
}

static void CheckTitleReveal(void) {
    extern GameApi g_ApiInit;
    g_api = g_ApiInit;
    SDL_SharedObject* module = OpenOverlay("st0");
    void (*update)(Entity*) =
        (void*)SDL_LoadFunction(module, "EntityStageTitleFadeout");
    assert(update);
    DestroyAllPrimitives();
    Entity* self = g_CurrentEntity = &g_Entities[64];
    memset(self, 0, sizeof(*self));
    self->entityId = 25;
    self->step = 5;
    int index = AllocPrimitives(PRIM_G4, 5);
    assert(index >= 0);
    self->primIndex = index;
    self->flags = FLAG_HAS_PRIMS;
    self->ext.stageTitleCard.prim = &g_PrimBuf[index];
    PLAYER.posX.i.hi = 128;
    g_CutsceneHasControl = 0;
    for (int frame = 0; frame < 80 && self->entityId; frame++) {
        g_PcSettings.widescreen = frame < 10 || frame >= 20;
        PcUpdateViewport();
        update(self);
        if (!self->entityId)
            break;
        Primitive* left = self->ext.stageTitleCard.prim;
        Primitive* leftGradient = left->next;
        Primitive* right = leftGradient->next;
        Primitive* rightGradient = right->next;
        assert(left->x0 == PcViewLeft() && left->x1 >= left->x0);
        assert(right->x1 == PcViewRight() && right->x0 <= right->x1);
        assert(leftGradient->x1 - leftGradient->x0 == 64);
        assert(rightGradient->x1 - rightGradient->x0 == 64);
        assert(leftGradient->r0 == 255 && leftGradient->r1 == 0);
        assert(rightGradient->r0 == 0 && rightGradient->r1 == 255);
    }
    assert(!self->entityId);
    DestroyAllPrimitives();
    SDL_UnloadObject(module);
    g_PcSettings.widescreen = 0;
    PcUpdateViewport();
    puts("Opening reveal masks cover the viewport without reversing: PASS");
}
#endif

bool PcTestUpgrades(void) {
    Psyz_VideoPauseClock(1);
    uint64_t paused = Psyz_VideoClockNS();
    SDL_Delay(10);
    assert(Psyz_VideoClockNS() == paused);
    Psyz_VideoPauseClock(0);
    assert(Psyz_VideoClockNS() >= paused);
    ResetGraph(0);
    SetDefDispEnv(&g_GpuBuffers[0].disp, 0, 0, 256, 240);
    PutDispEnv(&g_GpuBuffers[0].disp);
    g_GameState = Game_Play;
    g_GameStep = Play_Default;
    g_GameEngineStep = Engine_Normal;
    g_CutsceneHasControl = 0;
    g_Tilemap.width = 1024;
    g_Tilemap.x = 0;
    g_PcSettings.widescreen = 1;
    PcUpdateViewport();
    assert(PcViewLeft() < 0 && PcViewRight() > 256);
    assert(Psyz_VideoSetVerticalCrop(-1, 207) == -1);
    assert(Psyz_VideoSetVerticalCrop(20, 240) == -1);
    int capturedWidth, capturedHeight;
    unsigned char* captured =
        Psyz_VideoAllocCapturedFrame(&capturedWidth, &capturedHeight);
    unsigned renderScale = Psyz_VideoGetInternalResolution();
    assert(captured && capturedWidth > 256 * renderScale &&
           capturedHeight == 207 * renderScale);
    for (int filter = 0; filter < 4; filter++) {
        assert(Psyz_VideoSetFilter(filter, 75) == 0);
        assert(Psyz_VideoGetFilter() == filter &&
               Psyz_VideoGetFilterStrength() == 75);
        int width, height;
        u8* raw = Psyz_VideoAllocCapturedFrame(&width, &height);
        assert(raw && width == capturedWidth && height == capturedHeight);
        assert(!memcmp(raw, captured, (size_t)width * height * 3));
        free(raw);
    }
    assert(Psyz_VideoSetFilter(-1, 75) == -1);
    assert(Psyz_VideoSetFilter(4, 75) == -1);
    assert(Psyz_VideoSetFilter(2, -1) == -1);
    assert(Psyz_VideoSetFilter(2, 101) == -1);
    assert(Psyz_VideoGetFilter() == 3 && Psyz_VideoGetFilterStrength() == 75);
    assert(Psyz_VideoSetFilter(0, 75) == 0);
    free(captured);
    g_Tilemap.x = 0;
    g_Tilemap.width = 1024;
    g_Tilemap.scrollX.i.hi = 0;
    PLAYER.posX.i.hi = 128;
    g_PlayerX = 128;
    PcClampCamera();
    assert(g_Tilemap.scrollX.i.hi == PcViewMargin());
    assert(PLAYER.posX.i.hi + g_Tilemap.scrollX.i.hi == 128);
    PcClampCamera();
    assert(PLAYER.posX.i.hi + g_Tilemap.scrollX.i.hi == 128);
    Primitive flash = {
        .type = PRIM_G4,
        .x0 = 0,
        .x1 = 256,
        .x2 = 0,
        .x3 = 256,
        .y0 = 0,
        .y1 = 0,
        .y2 = 240,
        .y3 = 240};
    PcAdjustPrimitive(&flash);
    assert(flash.x0 == PcViewLeft() && flash.x3 == PcViewRight());
    Primitive scenery = flash;
    scenery.x0 = scenery.x2 = 0;
    scenery.x1 = scenery.x3 = 4096;
    scenery.priority = 0xB0;
    PcAdjustPrimitive(&scenery);
    assert(scenery.x1 == 4096 && scenery.x0 == 0);
    g_Tilemap.width = 256;
    PcClampCamera();
    assert(g_Tilemap.scrollX.i.hi == 0);
    PcUpdateViewport();
    assert(PcViewMargin() > 0);
    g_Tilemap.width = 1024;
    PcUpdateViewport();
    assert(PcViewMargin() > 0);
    g_CutsceneHasControl = 1;
    PcUpdateViewport();
    assert(PcViewMargin() > 0);
    g_Tilemap.scrollX.i.hi = 0;
    PcClampCamera();
    assert(g_Tilemap.scrollX.i.hi == 0 && PLAYER.posX.i.hi == g_PlayerX);
    captured = Psyz_VideoAllocCapturedFrame(&capturedWidth, &capturedHeight);
    assert(
        captured && capturedWidth > 256 && capturedHeight == 207 * renderScale);
    free(captured);
    g_PcSettings.widescreen = 0;
    PcUpdateViewport();
    captured = Psyz_VideoAllocCapturedFrame(&capturedWidth, &capturedHeight);
    assert(captured && capturedWidth == 256 && capturedHeight == 240);
    free(captured);

    assert(SDL_InitSubSystem(SDL_INIT_GAMEPAD));
    SDL_VirtualJoystickDesc device;
    SDL_INIT_INTERFACE(&device);
    device.type = SDL_JOYSTICK_TYPE_GAMEPAD;
    device.naxes = SDL_GAMEPAD_AXIS_COUNT;
    device.nbuttons = SDL_GAMEPAD_BUTTON_COUNT;
    device.button_mask = (1u << SDL_GAMEPAD_BUTTON_COUNT) - 1;
    device.axis_mask = (1u << SDL_GAMEPAD_AXIS_COUNT) - 1;
    device.name = "SotN input regression device";
    SDL_JoystickID id = SDL_AttachVirtualJoystick(&device);
    assert(id);
    SDL_Joystick* joystick = SDL_OpenJoystick(id);
    assert(joystick);
    int padCount;
    SDL_JoystickID* pads = SDL_GetGamepads(&padCount);
    assert(pads);
    int selected = -1;
    for (int i = 0; i < padCount; i++)
        if (pads[i] == id)
            selected = i;
    SDL_free(pads);
    assert(selected >= 0);
    g_PcSettings.controller = selected;
    g_PcSettings.buttons[6] = SDL_GAMEPAD_BUTTON_EAST;
    assert(
        SDL_SetJoystickVirtualButton(joystick, SDL_GAMEPAD_BUTTON_EAST, true));
    SDL_UpdateJoysticks();
    PcUpgradesFrame();
    assert(PadRead(1) & PAD_CROSS);
    assert(
        SDL_SetJoystickVirtualButton(joystick, SDL_GAMEPAD_BUTTON_EAST, false));
    SDL_UpdateJoysticks();
    PcUpgradesFrame();
    assert(!(PadRead(1) & PAD_CROSS));
    g_PcSettings.buttons[6] = -2;
    assert(SDL_SetJoystickVirtualAxis(
        joystick, SDL_GAMEPAD_AXIS_LEFT_TRIGGER, 32767));
    SDL_UpdateJoysticks();
    PcUpgradesFrame();
    assert(PadRead(1) & PAD_CROSS);
    PcUpgradesShutdown();
    SDL_CloseJoystick(joystick);
    assert(SDL_DetachVirtualJoystick(id));
    PcSettingsDefaults(&g_PcSettings);

    char directory[128];
    snprintf(directory, sizeof(directory), "build/pc-pack-test-%llu",
             (unsigned long long)SDL_GetTicksNS());
    assert(SDL_CreateDirectory(directory));
    char* previous = SDL_GetCurrentDirectory();
    assert(previous && (chdir(directory) == 0));
    assert(SDL_CreateDirectory("pack/files"));
    assert(SDL_CreateDirectory("pack/scripts/1F"));
    assert(SDL_CreateDirectory("pack/voices"));
    strcpy(g_PcSettings.contentPack, "pack");
    const unsigned char original[] = {0, 1, 2, 3};
    const unsigned char replacement[] = {8, 9, 10, 11};
    WriteFile("original.bin", original, 4);
    WriteFile("pack/files/original.bin", replacement, 4);
    FILE* f = PcOpenAsset("original.bin");
    assert(f && fgetc(f) == 8);
    fclose(f);
    assert(!PcOpenPackFile("../original.bin"));
    g_StageId = STAGE_ST0;
    CheckArtwork();
    CheckIndexedArtwork();
    WriteFile("pack/scripts/1F/80180000.bin", replacement, 4);
    CutsceneSymbolRange symbol = {original, 0x80180000, 4};
    CutscenePcAlloc(&symbol, 1);
    assert(*CutsceneAddrToPc(0x80180002) == 10);
    CutscenePcAlloc(NULL, 0);
    assert(!remove("pack/scripts/1F/80180000.bin"));
    WriteFile("pack/scripts/1F/80180000.bin", replacement, 3);
    CutscenePcAlloc(&symbol, 1);
    assert(CutsceneAddrToPc(0x80180002) == original + 2);
    CutscenePcAlloc(NULL, 0);

    unsigned char wav[44 + 200] = {0};
    memcpy(wav, "RIFF", 4);
    wav[4] = sizeof(wav) - 8;
    memcpy(wav + 8, "WAVEfmt ", 8);
    wav[16] = 16;
    wav[20] = 1;
    wav[22] = 1;
    wav[24] = 0x44;
    wav[25] = 0xAC;
    wav[28] = 0x88;
    wav[29] = 0x58;
    wav[30] = 1;
    wav[32] = 2;
    wav[34] = 16;
    memcpy(wav + 36, "data", 4);
    wav[40] = 200;
    WriteFile("pack/voices/0358.wav", wav, sizeof(wav));
    assert(Psyz_AudioInit() == 0);
    assert(PcVoiceStart(0x358) == 1);
    assert(PcVoiceDuration() == 1);
    PcVoicePause(true);
    PcVoicePause(false);
    PcVoiceStop();
    assert(PcVoiceDuration() == 0);
    assert(PcVoiceStart(0x359) == 0);
    assert(!remove("pack/voices/0358.wav"));
    assert(!remove("pack/scripts/1F/80180000.bin"));
    assert(!remove("pack/files/original.bin"));
    assert(!remove("original.bin"));
    const char* directories[] = {
        "pack/voices", "pack/scripts/1F", "pack/scripts", "pack/files", "pack"};
    for (unsigned i = 0; i < sizeof(directories) / sizeof(*directories); i++) {
        assert(SDL_RemovePath(directories[i]));
    }
    assert(chdir(previous) == 0);
    SDL_free(previous);
    assert(SDL_RemovePath(directory));
#ifndef _WIN32
    CheckBugFixes();
    CheckWaterCoverage();
    CheckCavernWaterCoverage();
    CheckCavernShimmer();
    CheckBackgroundGears();
    CheckBackgroundSkyLand();
    CheckEntranceFoliage();
    CheckProjectedBookcases();
    CheckBridgeLiquidMargins();
    CheckLavaGlow();
    CheckCatacombPanels();
    CheckHouseCulling();
    CheckDreamClouds();
    CheckStainedGlassEdges();
    CheckDistantBookshelves();
    CheckLibraryParallax();
    CheckBackgroundArches();
    CheckBackgroundVortex();
    CheckBackgroundDematerialize();
    CheckDrawAreaCapture();
    CheckWidePhotograph();
    CheckCaptureViewportLifetime();
    CheckSpawnLoadMode();
    CheckTitleReveal();
    CheckRichterHud();
    CheckCornerPopups();
    PcQolTest();
#endif
    puts("Viewport, camera, full-screen dialogue and content pack integration: "
         "PASS");
    return true;
}
