// SPDX-License-Identifier: AGPL-3.0-or-later
#ifdef NDEBUG
#undef NDEBUG
#endif
#include <game.h>
#include <stage.h>
#include "../dra/dra.h"
#include "pc.h"
#include "upgrades.h"
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
                       g_Clut[1][50]};
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
    assert(DrawIndexedArtwork(flags) == 2 && g_GpuUsage.drawModes == 2);
    TILE* tile = ArtworkTileAt(0x82);
    assert(tile->r0 == 248 && tile->g0 == 0 && getcode(tile) == 0x60);
    tile = ArtworkTileAt(0x84);
    assert(tile->g0 == 248 && getcode(tile) == 0x62);

    // Palette edits must work from the cache, even without the metadata file.
    assert(!remove(indexPath));
    g_Clut[0][49] = 0xFC00;
    g_Clut[0][50] = 0;
    assert(DrawIndexedArtwork(flags) == 1 && g_GpuUsage.drawModes == 1);
    tile = ArtworkTileAt(0x82);
    assert(tile->b0 == 248 && tile->r0 == 0 && getcode(tile) == 0x62);
    g_PcSettings.palette = 2;
    assert(DrawIndexedArtwork(flags) == 1);
    tile = ArtworkTileAt(0x82);
    u16 filtered = PcPaletteColor(g_Clut[0][49], 2);
    assert(tile->r0 == (filtered & 31) << 3);
    assert(tile->g0 == ((filtered >> 5) & 31) << 3);
    assert(tile->b0 == ((filtered >> 10) & 31) << 3);
    g_PcSettings.palette = 0;
    assert(DrawIndexedArtwork(flags | LAYER_CLUT_ALT) == 1);
    tile = ArtworkTileAt(0x82);
    assert(tile->r0 == 248 && tile->g0 == 248 && tile->b0 == 0 &&
           getcode(tile) == 0x60);
    g_Clut[0][49] = 0x8000;
    assert(DrawIndexedArtwork(flags) == 1);
    tile = ArtworkTileAt(0x82);
    assert(!tile->r0 && !tile->g0 && !tile->b0 && getcode(tile) == 0x62);

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
    g_PcSettings.widescreen = 0;
    PcUpdateViewport();
    ClearOTagR(g_CurrentBuffer->ot, OTSIZE);
    g_CurrentBuffer = oldBuffer;
    SDL_DestroySurface(rgb);
    SDL_DestroySurface(indices);
    assert(!remove(rgbPath) && !remove(indexPath));
    assert(SDL_RemovePath("pack/widescreen/indexed"));
    assert(SDL_RemovePath("pack/widescreen"));
    puts("Indexed artwork follows live palettes, STP, depth and accessibility; "
         "invalid metadata falls back: PASS");
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
    const char* stages[] = {"no3", "np3"};
    for (int i = 0; i < 2; i++) {
        SDL_SharedObject* module = OpenOverlay(stages[i]);
        void (*update)(Entity*) =
            (void*)SDL_LoadFunction(module, "EntityTransparentWater");
        assert(update);
        DestroyAllPrimitives();
        Entity* self = g_CurrentEntity = &g_Entities[64];
        memset(self, 0, sizeof(*self));
        g_Tilemap.scrollX.val = 0;
        update(self);
        assert(self->ext.transparentWater.prim);
        int left = 1000, right = -1000;
        for (Primitive* p = self->ext.transparentWater.prim; p; p = p->next) {
            if (p->drawMode & DRAW_HIDE)
                continue;
            left = MIN(left, MIN(p->x0, p->x1));
            right = MAX(right, MAX(p->x0, p->x1));
        }
        assert(left <= PcViewLeft() && right >= PcViewRight());
        DestroyAllPrimitives();
        SDL_UnloadObject(module);
    }
    g_PcSettings.widescreen = 0;
    g_Tilemap.width = 1280;
    g_Tilemap.scrollX.i.hi = 1024;
    g_PlayerX = 1143;
    PLAYER.posX.i.hi = 163;
    PcUpdateViewport();
    PcClampCamera();
    assert(PLAYER.posX.i.hi == 119);
    PcUpdateViewport();
    puts("Normal and inverted water cover the widened viewport: PASS");
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
        g_randomNext = 0x12345678;
        update(self);
        update(self);
        assert(self->step == 4);
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
            if (self[1].entityId && !vortexFrame[wide])
                vortexFrame[wide] = lifetime[wide];
        }
        assert(vortexFrame[wide]);
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
    CheckBackgroundGears();
    CheckBackgroundSkyLand();
    CheckDreamClouds();
    CheckStainedGlassEdges();
    CheckDistantBookshelves();
    CheckLibraryParallax();
    CheckBackgroundArches();
    CheckBackgroundVortex();
    CheckBackgroundDematerialize();
    CheckDrawAreaCapture();
    CheckTitleReveal();
#endif
    puts("Viewport, camera, full-screen dialogue and content pack integration: "
         "PASS");
    return true;
}
