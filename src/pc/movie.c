// SPDX-License-Identifier: AGPL-3.0-or-later
#include <game.h>
#include "pc.h"
#include <SDL3/SDL.h>
#include <psyz.h>
#include <stdlib.h>

bool PcPlayMovie(int index) {
    static const char* names[] = {"LOGO15XA", "OPN_WS", "TYK_WS", "END_WS"};
    enum { FRAME_BYTES = 320 * 240 * 3 };
    char path[128];
    FILE* video = NULL;
    unsigned char* frame = NULL;
    unsigned char* savedVram = NULL;
    u16* pixels = NULL;
    Uint8* samples = NULL;
    Uint32 sampleBytes = 0;
    SDL_AudioSpec spec;
    SDL_AudioStream* audio = NULL;
    DISPENV previous, display;
    RECT rect = {0, 0, 320, 240};
    bool started = false, ok = false;
    unsigned frames = 0;
    Uint64 start;
    PsyzVsyncMode vsync = Psyz_VideoGetVsyncMode();

    if (index < 0 || index >= LEN(names)) {
        return false;
    }
    snprintf(path, sizeof(path), "build/pc-movies/%s.rgb", names[index]);
    video = fopen(path, "rb");
    if (!video) {
        ERRORF(
            "Movie missing: %s. Run python3 tools/prepare_pc_movies.py", path);
        goto cleanup;
    }
    snprintf(path, sizeof(path), "build/pc-movies/%s.wav", names[index]);
    if (!SDL_LoadWAV(path, &spec, &samples, &sampleBytes)) {
        ERRORF("Movie audio: %s", SDL_GetError());
        goto cleanup;
    }
    if (!SDL_WasInit(SDL_INIT_AUDIO) && !SDL_InitSubSystem(SDL_INIT_AUDIO)) {
        ERRORF("Cannot initialize movie audio: %s", SDL_GetError());
        goto cleanup;
    }
    frame = malloc(FRAME_BYTES);
    savedVram = malloc(320 * 240 * sizeof(u16));
    pixels = malloc(320 * 240 * sizeof(u16));
    audio = SDL_OpenAudioDeviceStream(
        SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, &spec, NULL, NULL);
    if (!frame || !savedVram || !pixels || !audio ||
        !SDL_PutAudioStreamData(audio, samples, sampleBytes)) {
        ERRORF("Cannot prepare movie playback: %s", SDL_GetError());
        goto cleanup;
    }
    GetDispEnv(&previous);
    StoreImage(&rect, (u_long*)savedVram);
    DrawSync(0);
    SetDefDispEnv(&display, 0, 0, 320, 240);
    display.isrgb24 = 0;
    PutDispEnv(&display);
    SetDispMask(1);
    Psyz_AudioPause();
    Psyz_VideoSetVsyncMode(PSYZ_VSYNC_OFF);
    started = true;
    start = SDL_GetTicksNS();
    if (!SDL_ResumeAudioStreamDevice(audio)) {
        ERRORF("Cannot start movie audio: %s", SDL_GetError());
        goto cleanup;
    }
    for (;;) {
        size_t size = fread(frame, 1, FRAME_BYTES, video);
        if (!size && !ferror(video)) {
            ok = frames > 0;
            break;
        }
        if (size != FRAME_BYTES) {
            ERRORF("Truncated movie %s at frame %u", names[index], frames);
            break;
        }
        // shortcut: PSY-Z ignores RGB24; use RGB555 until it supports RGB24.
        for (int i = 0; i < 320 * 240; i++) {
            pixels[i] = (frame[i * 3] >> 3) | ((frame[i * 3 + 1] >> 3) << 5) |
                        ((frame[i * 3 + 2] >> 3) << 10);
        }
        LoadImage(&rect, (u_long*)pixels);
        DrawSync(0);
        frames++;
        do {
            VSync(0);
            if (Psyz_QuitRequested() ||
                (PadRead(1) & (PAD_START | PAD_CROSS))) {
                ok = true;
                goto cleanup;
            }
        } while (SDL_GetTicksNS() - start < (Uint64)frames * 1000000000 / 15);
    }
cleanup:
    if (audio) {
        SDL_DestroyAudioStream(audio);
    }
    if (started) {
        LoadImage(&rect, (u_long*)savedVram);
        DrawSync(0);
        PutDispEnv(&previous);
        Psyz_VideoSetVsyncMode(vsync);
        Psyz_AudioUnpause();
    }
    if (video) {
        fclose(video);
    }
    SDL_free(samples);
    free(frame);
    free(savedVram);
    free(pixels);
    INFOF(
        "Movie %s: %u frames, %s", names[index], frames, ok ? "OK" : "FAILED");
    return ok;
}
