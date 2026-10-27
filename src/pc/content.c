// SPDX-License-Identifier: AGPL-3.0-or-later
#include "pc.h"
#include "upgrades.h"
#include <SDL3/SDL.h>
#include <psyz.h>
#include <string.h>

static SDL_AudioStream* s_Voice;
static int s_VoiceTicks;

FILE* PcOpenPackFile(const char* relative) {
    if (!g_PcSettings.contentPack[0] || !relative || relative[0] == '/' ||
        relative[0] == '\\' || strchr(relative, ':') ||
        strstr(relative, "..")) {
        return NULL;
    }
    char path[1200];
    int size = snprintf(
        path, sizeof(path), "%s/%s", g_PcSettings.contentPack, relative);
    if (size < 0 || size >= sizeof(path))
        return NULL;
    return fopen(path, "rb");
}

FILE* PcOpenAsset(const char* filename) {
    char path[1024];
    if (snprintf(path, sizeof(path), "files/%s", filename) < sizeof(path)) {
        FILE* replacement = PcOpenPackFile(path);
        if (replacement)
            return replacement;
    }
    return fopen(filename, "rb");
}

void PcVoiceStop(void) {
    if (s_Voice)
        SDL_DestroyAudioStream(s_Voice);
    s_Voice = NULL;
    s_VoiceTicks = 0;
    Psyz_SpuSetMixVolume(
        g_PcSettings.masterVolume * g_PcSettings.effectsVolume / 100,
        g_PcSettings.masterVolume * g_PcSettings.musicVolume / 100);
}

int PcVoiceStart(int id) {
    PcVoiceStop();
    if (id <= 0x300 || id >= 0x533)
        return 0;
    char path[40];
    snprintf(path, sizeof(path), "voices/%04X.wav", id);
    FILE* file = PcOpenPackFile(path);
    if (!file)
        return 0;
    fclose(file);
    char full[1200];
    snprintf(full, sizeof(full), "%s/%s", g_PcSettings.contentPack, path);
    SDL_AudioSpec spec;
    Uint8* samples;
    Uint32 bytes;
    if (!SDL_LoadWAV(full, &spec, &samples, &bytes)) {
        ERRORF("Replacement voice %04X: %s", id, SDL_GetError());
        return 0;
    }
    int frameBytes = SDL_AUDIO_FRAMESIZE(spec);
    if (!bytes || bytes > 64 * 1024 * 1024 || spec.freq <= 0 ||
        frameBytes <= 0 || bytes % frameBytes || spec.channels > 2) {
        SDL_free(samples);
        return 0;
    }
    s_Voice = SDL_OpenAudioDeviceStream(
        SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, &spec, NULL, NULL);
    bool ok = s_Voice && SDL_PutAudioStreamData(s_Voice, samples, bytes) &&
              SDL_ResumeAudioStreamDevice(s_Voice);
    SDL_free(samples);
    if (!ok) {
        PcVoiceStop();
        return 0;
    }
    s_VoiceTicks =
        (int)(((Uint64)bytes / frameBytes * 60 + spec.freq - 1) / spec.freq);
    Psyz_SpuSetMixVolume(
        g_PcSettings.masterVolume * g_PcSettings.effectsVolume / 100, 0);
    PcVoiceUpdate();
    return s_VoiceTicks;
}

int PcVoiceDuration(void) { return s_VoiceTicks; }
void PcVoicePause(bool paused) {
    if (!s_Voice)
        return;
    if (paused)
        SDL_PauseAudioStreamDevice(s_Voice);
    else
        SDL_ResumeAudioStreamDevice(s_Voice);
}
void PcVoiceUpdate(void) {
    if (s_Voice)
        SDL_SetAudioStreamGain(
            s_Voice,
            g_PcSettings.masterVolume * g_PcSettings.musicVolume / 10000.0f);
}
