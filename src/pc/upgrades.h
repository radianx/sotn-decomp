// SPDX-License-Identifier: AGPL-3.0-or-later
#ifndef PC_UPGRADES_H
#define PC_UPGRADES_H
#include <stdbool.h>

#define PC_COPY_DRAW_AREA_OPCODE 0xF1

typedef struct {
    int widescreen;
    int reduceFlashes;
    int palette;
    int bugFixes;
    int masterVolume;
    int effectsVolume;
    int musicVolume;
    int controller;
    int keys[16];
    int buttons[16];
    char contentPack[512];
} PcSettings;

extern PcSettings g_PcSettings;
extern const char* g_PcSettingsPath;
void PcSettingsDefaults(PcSettings* settings);
bool PcSettingsLoad(PcSettings* settings, const char* path);
bool PcSettingsSave(const PcSettings* settings, const char* path);
int PcVoiceStart(int id);
int PcVoiceDuration(void);
void PcVoiceStop(void);
void PcVoicePause(bool paused);
void PcVoiceUpdate(void);
void PcMoviePause(bool paused);
void PcMovieUpdate(void);
void PcUpgradesInit(void);
void PcUpgradesFrame(void);
void PcUpgradesShutdown(void);
int PcViewMargin(void);
int PcViewLeft(void);
int PcViewRight(void);
int PcViewTop(void);
int PcViewBottom(void);
struct Entity;
void PcHoldViewport(struct Entity* entity);
bool PcViewportChangePending(void);
void PcUpdateViewport(void);
void PcClampCamera(void);
void PcArtworkBegin(int layer);
int PcArtworkDrawLayer(int background, int width, int height, int scrollX,
                       int scrollY, int order, int flags);
void PcArtworkShutdown(void);
unsigned short PcPaletteColor(unsigned short color, int mode);
void PcUploadPalette(const void* data, int x, int y);
#endif
