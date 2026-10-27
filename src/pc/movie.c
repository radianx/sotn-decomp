// SPDX-License-Identifier: AGPL-3.0-or-later
#include <game.h>
#include "pc.h"
#include "upgrades.h"
#include <SDL3/SDL.h>
#include <psyz.h>
#include <stdlib.h>

static SDL_AudioStream* s_MovieAudio;
void PcMoviePause(bool paused) {
    if (!s_MovieAudio)
        return;
    if (paused)
        SDL_PauseAudioStreamDevice(s_MovieAudio);
    else
        SDL_ResumeAudioStreamDevice(s_MovieAudio);
}
void PcMovieUpdate(void) {
    if (s_MovieAudio)
        SDL_SetAudioStreamGain(
            s_MovieAudio,
            g_PcSettings.masterVolume * g_PcSettings.musicVolume / 10000.0f);
}

bool PcPlayMovie(int index) {
    static const char* names[] = {"LOGO15XA", "OPN_WS", "TYK_WS", "END_WS"};
    enum { FRAME_BYTES = 320 * 240 * 3 };
    char path[128];
    SDL_Process* videoProcess = NULL;
    SDL_Process* audioProcess = NULL;
    SDL_IOStream* video = NULL;
    unsigned char* frame = NULL;
    unsigned char* savedVram = NULL;
    Uint8* samples = NULL;
    Uint32 sampleBytes = 0;
    SDL_AudioSpec spec;
    SDL_AudioStream* audio = NULL;
    DISPENV previous, display;
    RECT rect = {0, 0, 480, 240};
    bool started = false, ok = false, wasPaused = false;
    unsigned frames = 0;
    Uint64 start;
    PsyzVsyncMode vsync = Psyz_VideoGetVsyncMode();

    if (index < 0 || index >= LEN(names)) {
        return false;
    }
    static const int frameCounts[] = {143, 922, 545, 740};
    snprintf(path, sizeof(path), "disks/us/%s.STR", names[index]);
    char count[16];
    snprintf(count, sizeof(count), "%d", frameCounts[index]);
    const char* videoArgs[] = {
        "ffmpeg", "-v",       "error",     "-nostdin", "-i",       path,
        "-map",   "0:v:0",    "-frames:v", count,      "-pix_fmt", "rgb24",
        "-f",     "rawvideo", "pipe:1",    NULL};
    const char* audioArgs[] = {
        "ffmpeg", "-v", "error", "-nostdin", "-i", path,    "-map",   "0:a:0",
        "-ac",    "2",  "-ar",   "44100",    "-f", "s16le", "pipe:1", NULL};
    videoProcess = SDL_CreateProcess(videoArgs, true);
    audioProcess = SDL_CreateProcess(audioArgs, true);
    if (!videoProcess || !audioProcess) {
        ERRORF("Movie playback requires FFmpeg: %s", SDL_GetError());
        goto cleanup;
    }
    video = SDL_GetProcessOutput(videoProcess);
    size_t decodedBytes = 0;
    int audioExit;
    samples = SDL_ReadProcess(audioProcess, &decodedBytes, &audioExit);
    if (!samples || audioExit || !decodedBytes ||
        decodedBytes > 32 * 1024 * 1024 || decodedBytes % 4) {
        ERRORF("Cannot decode movie audio: %s", SDL_GetError());
        goto cleanup;
    }
    sampleBytes = (Uint32)decodedBytes;
    spec = (SDL_AudioSpec){SDL_AUDIO_S16, 2, 44100};
    if (!SDL_WasInit(SDL_INIT_AUDIO) && !SDL_InitSubSystem(SDL_INIT_AUDIO)) {
        ERRORF("Cannot initialize movie audio: %s", SDL_GetError());
        goto cleanup;
    }
    frame = malloc(FRAME_BYTES);
    savedVram = malloc(FRAME_BYTES);
    audio = SDL_OpenAudioDeviceStream(
        SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, &spec, NULL, NULL);
    if (!frame || !savedVram || !audio ||
        !SDL_PutAudioStreamData(audio, samples, sampleBytes)) {
        ERRORF("Cannot prepare movie playback: %s", SDL_GetError());
        goto cleanup;
    }
    SDL_SetAudioStreamGain(
        audio, g_PcSettings.masterVolume * g_PcSettings.musicVolume / 10000.0f);
    GetDispEnv(&previous);
    StoreImage(&rect, (u_long*)savedVram);
    DrawSync(0);
    SetDefDispEnv(&display, 0, 0, 320, 240);
    display.isrgb24 = 1;
    PutDispEnv(&display);
    SetDispMask(1);
    wasPaused = Psyz_AudioIsPaused();
    Psyz_AudioPause();
    Psyz_VideoSetVsyncMode(PSYZ_VSYNC_OFF);
    started = true;
    s_MovieAudio = audio;
    start = Psyz_VideoClockNS();
    if (!SDL_ResumeAudioStreamDevice(audio)) {
        ERRORF("Cannot start movie audio: %s", SDL_GetError());
        goto cleanup;
    }
    for (;;) {
        size_t size = 0;
        while (size < FRAME_BYTES) {
            size_t read = SDL_ReadIO(video, frame + size, FRAME_BYTES - size);
            if (!read && SDL_GetIOStatus(video) != SDL_IO_STATUS_NOT_READY)
                break;
            if (!read)
                SDL_Delay(1);
            size += read;
        }
        if (!size) {
            int exitCode;
            SDL_WaitProcess(videoProcess, true, &exitCode);
            ok = !exitCode && frames == frameCounts[index];
            break;
        }
        if (size != FRAME_BYTES) {
            ERRORF("Truncated movie %s at frame %u", names[index], frames);
            break;
        }
        LoadImage(&rect, (u_long*)frame);
        DrawSync(0);
        frames++;
        do {
            VSync(0);
            if (Psyz_QuitRequested() ||
                (PadRead(1) & (PAD_START | PAD_CROSS))) {
                ok = true;
                goto cleanup;
            }
        } while (
            Psyz_VideoClockNS() - start < (Uint64)frames * 1000000000 / 15);
    }
cleanup:
    s_MovieAudio = NULL;
    if (audio) {
        SDL_DestroyAudioStream(audio);
    }
    if (started) {
        LoadImage(&rect, (u_long*)savedVram);
        DrawSync(0);
        PutDispEnv(&previous);
        Psyz_VideoSetVsyncMode(vsync);
        if (!wasPaused)
            Psyz_AudioUnpause();
    }
    if (videoProcess) {
        SDL_KillProcess(videoProcess, true);
        SDL_WaitProcess(videoProcess, true, NULL);
        SDL_DestroyProcess(videoProcess);
    }
    if (audioProcess) {
        SDL_KillProcess(audioProcess, true);
        SDL_WaitProcess(audioProcess, true, NULL);
        SDL_DestroyProcess(audioProcess);
    }
    SDL_free(samples);
    free(frame);
    free(savedVram);
    INFOF(
        "Movie %s: %u frames, %s", names[index], frames, ok ? "OK" : "FAILED");
    return ok;
}
