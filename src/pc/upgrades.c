// SPDX-License-Identifier: AGPL-3.0-or-later
#include <game.h>
#include "pc.h"
#include "upgrades.h"
#include <SDL3/SDL.h>
#include <psyz.h>
#include <psyz/overlay_sdl3.h>
#include <string.h>

static SDL_Window* s_Window;
static SDL_Renderer* s_Renderer;
static SDL_Gamepad* s_Gamepad;
static int s_Row, s_Capture = -1;
static bool s_PadCapture, s_ShowAudio;
static const char* s_Message = "Settings are saved when changed.";
static const char* buttons[] = {
    "L2",     "R2", "L1", "R1",    "Triangle", "Circle", "Cross", "Square",
    "Select", "L3", "R3", "Start", "Up",       "Right",  "Down",  "Left"};
static const char* palettes[] = {
    "Original", "High contrast", "Blue/Gold", "Monochrome"};

static void Save(void) {
    s_Message = PcSettingsSave(&g_PcSettings, g_PcSettingsPath)
                    ? "Settings saved."
                    : "Could not save settings; check the path.";
}

static void CloseSettings(void) {
    if (s_Renderer)
        SDL_DestroyRenderer(s_Renderer);
    if (s_Window)
        SDL_DestroyWindow(s_Window);
    s_Renderer = NULL;
    s_Window = NULL;
    s_Capture = -1;
}

static void OpenSettings(void) {
    if (s_Window) {
        CloseSettings();
        return;
    }
    s_Window = SDL_CreateWindow("SotN - PC Settings", 880, 900, 0);
    if (s_Window)
        s_Renderer = SDL_CreateRenderer(s_Window, NULL);
    if (!s_Renderer) {
        ERRORF("Settings window: %s", SDL_GetError());
        CloseSettings();
    }
}

static void Change(int delta) {
    int* value = NULL;
    int maximum = 1, step = 1;
    switch (s_Row) {
    case 0:
        value = &g_PcSettings.widescreen;
        break;
    case 1:
        value = &g_PcSettings.reduceFlashes;
        break;
    case 2:
        value = &g_PcSettings.palette;
        maximum = 3;
        break;
    case 3:
        value = &g_PcSettings.bugFixes;
        break;
    case 4:
        value = &g_PcSettings.masterVolume;
        maximum = 100;
        step = 5;
        break;
    case 5:
        value = &g_PcSettings.effectsVolume;
        maximum = 100;
        step = 5;
        break;
    case 6:
        value = &g_PcSettings.musicVolume;
        maximum = 100;
        step = 5;
        break;
    case 7:
        value = &g_PcSettings.controller;
        maximum = 15;
        if (s_Gamepad)
            SDL_CloseGamepad(s_Gamepad);
        s_Gamepad = NULL;
        break;
    case 8:
        s_PadCapture = !s_PadCapture;
        break;
    case 9:
        s_ShowAudio = !s_ShowAudio;
        break;
    default:
        s_Capture = s_Row - 10;
        break;
    }
    if (value) {
        if (step == 5)
            *value = SDL_clamp(*value + delta * step, 0, maximum);
        else
            *value = (*value + delta + maximum + 1) % (maximum + 1);
    }
    Save();
}

static void OnEvent(const SDL_Event* e) {
    if (e->type == SDL_EVENT_KEY_DOWN && !e->key.repeat &&
        e->key.scancode == SDL_SCANCODE_F1) {
        OpenSettings();
        return;
    }
    if (e->type == SDL_EVENT_KEY_DOWN && !e->key.repeat) {
        if (e->key.scancode == SDL_SCANCODE_F8) {
            g_PcSettings.reduceFlashes ^= 1;
            Save();
            return;
        }
        if (e->key.scancode == SDL_SCANCODE_F9) {
            g_PcSettings.palette = (g_PcSettings.palette + 1) % 4;
            Save();
            return;
        }
        if (e->key.scancode == SDL_SCANCODE_F2) {
            s_ShowAudio = !s_ShowAudio;
            if (!s_Window)
                OpenSettings();
            return;
        }
    }
    if (!s_Window)
        return;
    if (e->type == SDL_EVENT_WINDOW_CLOSE_REQUESTED) {
        bool closeGame = e->window.windowID != SDL_GetWindowID(s_Window);
        CloseSettings();
        if (closeGame) {
            SDL_Event quit = {.type = SDL_EVENT_QUIT};
            SDL_PushEvent(&quit);
        }
        return;
    }
    if (s_Capture >= 0 && s_PadCapture &&
        e->type == SDL_EVENT_GAMEPAD_AXIS_MOTION && e->gaxis.value > 16000 &&
        s_Gamepad && e->gaxis.which == SDL_GetGamepadID(s_Gamepad) &&
        (e->gaxis.axis == SDL_GAMEPAD_AXIS_LEFT_TRIGGER ||
         e->gaxis.axis == SDL_GAMEPAD_AXIS_RIGHT_TRIGGER)) {
        g_PcSettings.buttons[s_Capture] =
            e->gaxis.axis == SDL_GAMEPAD_AXIS_LEFT_TRIGGER ? -2 : -3;
        s_Capture = -1;
        Save();
    }
    if (s_Capture >= 0 && s_PadCapture &&
        e->type == SDL_EVENT_GAMEPAD_BUTTON_DOWN && s_Gamepad &&
        e->gbutton.which == SDL_GetGamepadID(s_Gamepad)) {
        g_PcSettings.buttons[s_Capture] = e->gbutton.button;
        s_Capture = -1;
        Save();
    }
    if (e->type != SDL_EVENT_KEY_DOWN || e->key.repeat ||
        e->key.windowID != SDL_GetWindowID(s_Window))
        return;
    SDL_Scancode code = e->key.scancode;
    if (s_Capture >= 0 && !s_PadCapture) {
        if (code != SDL_SCANCODE_ESCAPE && code != SDL_SCANCODE_F4) {
            g_PcSettings.keys[s_Capture] = code;
            s_Capture = -1;
            Save();
        }
        return;
    }
    if (code == SDL_SCANCODE_UP)
        s_Row = (s_Row + 25) % 26;
    if (code == SDL_SCANCODE_DOWN)
        s_Row = (s_Row + 1) % 26;
    if (code == SDL_SCANCODE_LEFT)
        Change(-1);
    if (code == SDL_SCANCODE_RIGHT || code == SDL_SCANCODE_RETURN)
        Change(1);
}

static void DrawSettings(void) {
    SDL_SetRenderDrawColor(s_Renderer, 18, 20, 28, 255);
    SDL_RenderClear(s_Renderer);
    SDL_SetRenderScale(s_Renderer, 2, 2);
    SDL_SetRenderDrawColor(s_Renderer, 230, 235, 245, 255);
    SDL_RenderDebugText(s_Renderer, 12, 10, "PC SETTINGS - F1 returns to game");
    SDL_RenderDebugText(
        s_Renderer, 12, 24, "Up/Down: select   Left/Right/Enter: change");
    char text[220];
    if (s_ShowAudio) {
        SDL_RenderDebugText(
            s_Renderer, 12, 45, "AUDIO SNAPSHOT - F2 returns to settings");
        SDL_RenderDebugText(s_Renderer, 12, 62,
                            "Voice  Envelope  Volume L/R  Pitch  Sample addr");
        Psyz_AudioLock();
        for (int i = 0; i < 24; i++) {
            unsigned reg = i * 16;
            snprintf(
                text, sizeof(text), "%2d     %04X      %04X/%04X   %04X   %05X",
                i, Psyz_SpuRead(reg + 12), Psyz_SpuRead(reg),
                Psyz_SpuRead(reg + 2), Psyz_SpuRead(reg + 4),
                Psyz_SpuRead(reg + 6) * 8);
            SDL_RenderDebugText(s_Renderer, 12, 80 + i * 12, text);
        }
        snprintf(text, sizeof(text),
                 "SPUCNT %04X  Main %04X/%04X  CD %04X/%04X",
                 Psyz_SpuRead(0x1AA), Psyz_SpuRead(0x180), Psyz_SpuRead(0x182),
                 Psyz_SpuRead(0x1B0), Psyz_SpuRead(0x1B2));
        Psyz_AudioUnlock();
        SDL_RenderDebugText(s_Renderer, 12, 386, text);
        SDL_RenderPresent(s_Renderer);
        return;
    }
    for (int row = 0; row < 26; row++) {
        const char* mark = row == s_Row ? ">" : " ";
        switch (row) {
        case 0:
            snprintf(text, sizeof(text), "%s Widescreen: %s", mark,
                     g_PcSettings.widescreen ? "16:9" : "Original");
            break;
        case 1:
            snprintf(text, sizeof(text), "%s Reduce flashes: %s", mark,
                     g_PcSettings.reduceFlashes ? "On" : "Off");
            break;
        case 2:
            snprintf(text, sizeof(text), "%s Color assistance: %s", mark,
                     palettes[g_PcSettings.palette]);
            break;
        case 3:
            snprintf(text, sizeof(text), "%s Original-game bug fixes: %s", mark,
                     g_PcSettings.bugFixes ? "On" : "Off");
            break;
        case 4:
            snprintf(text, sizeof(text), "%s Master volume: %d%%", mark,
                     g_PcSettings.masterVolume);
            break;
        case 5:
            snprintf(text, sizeof(text), "%s Effects volume: %d%%", mark,
                     g_PcSettings.effectsVolume);
            break;
        case 6:
            snprintf(text, sizeof(text), "%s Music/voice volume: %d%%", mark,
                     g_PcSettings.musicVolume);
            break;
        case 7:
            snprintf(
                text, sizeof(text), "%s Controller: %d (%s)", mark,
                g_PcSettings.controller + 1,
                s_Gamepad ? SDL_GetGamepadName(s_Gamepad) : "not connected");
            break;
        case 8:
            snprintf(text, sizeof(text), "%s Rebind mode: %s", mark,
                     s_PadCapture ? "Controller buttons" : "Keyboard");
            break;
        case 9:
            snprintf(text, sizeof(text), "%s Audio diagnostics: %s", mark,
                     s_ShowAudio ? "On" : "Off");
            break;
        default: {
            int i = row - 10;
            int b = g_PcSettings.buttons[i];
            const char* pad =
                b == -2   ? "Left trigger"
                : b == -3 ? "Right trigger"
                : b < 0   ? "Unbound"
                          : SDL_GetGamepadStringForButton(b);
            snprintf(text, sizeof(text), "%s %-8s Key: %-12s Pad: %s%s", mark,
                     buttons[i], SDL_GetScancodeName(g_PcSettings.keys[i]),
                     pad ? pad : "Unknown",
                     s_Capture == i ? " [press button]" : "");
            break;
        }
        }
        SDL_SetRenderDrawColor(s_Renderer, row == s_Row ? 255 : 215,
                               row == s_Row ? 215 : 220, 170, 255);
        SDL_RenderDebugText(s_Renderer, 12, 45 + row * 13, text);
    }
    SDL_SetRenderDrawColor(s_Renderer, 180, 205, 230, 255);
    SDL_RenderDebugText(s_Renderer, 12, 393, s_Message);
    SDL_RenderDebugText(s_Renderer, 12, 409,
                        "F4 fullscreen | F8 flashes | F9 color assistance");
    SDL_RenderPresent(s_Renderer);
}

static void UpdateController(void) {
    if (s_Gamepad && !SDL_GamepadConnected(s_Gamepad)) {
        SDL_CloseGamepad(s_Gamepad);
        s_Gamepad = NULL;
    }
    if (s_Gamepad)
        return;
    int count;
    SDL_JoystickID* ids = SDL_GetGamepads(&count);
    if (ids && g_PcSettings.controller < count) {
        s_Gamepad = SDL_OpenGamepad(ids[g_PcSettings.controller]);
    }
    SDL_free(ids);
}

void PcUpgradesFrame(void) {
    extern u8 D_8013803C;
    if (g_PcSettings.reduceFlashes)
        D_8013803C = 0;
    PcUpdateViewport();
    UpdateController();
    if (s_Window) {
        bool wasPaused = Psyz_AudioIsPaused();
        PcVoicePause(true);
        PcMoviePause(true);
        Psyz_AudioPause();
        Psyz_VideoPauseClock(1);
        while (s_Window && !Psyz_QuitRequested()) {
            SDL_Event e;
            while (SDL_PollEvent(&e)) {
                if (e.type == SDL_EVENT_QUIT) {
                    CloseSettings();
                    SDL_PushEvent(&e);
                    break;
                } else
                    OnEvent(&e);
            }
            UpdateController();
            if (s_Window)
                DrawSettings();
            SDL_Delay(16);
        }
        Psyz_VideoPauseClock(0);
        PcVoicePause(false);
        PcMoviePause(false);
        if (!wasPaused)
            Psyz_AudioUnpause();
    }
    Psyz_SpuSetMixVolume(
        g_PcSettings.masterVolume * g_PcSettings.effectsVolume / 100,
        PcVoiceDuration()
            ? 0
            : g_PcSettings.masterVolume * g_PcSettings.musicVolume / 100);
    PcVoiceUpdate();
    PcMovieUpdate();
    const bool* keys = SDL_GetKeyboardState(NULL);
    unsigned pressed = 0;
    for (int i = 0; i < 16; i++) {
        bool down = keys[g_PcSettings.keys[i]];
        int b = g_PcSettings.buttons[i];
        if (s_Gamepad) {
            if (b >= 0)
                down |= SDL_GetGamepadButton(s_Gamepad, b);
            if (b == -2)
                down |= SDL_GetGamepadAxis(
                            s_Gamepad, SDL_GAMEPAD_AXIS_LEFT_TRIGGER) > 16000;
            if (b == -3)
                down |= SDL_GetGamepadAxis(
                            s_Gamepad, SDL_GAMEPAD_AXIS_RIGHT_TRIGGER) > 16000;
            if (i == 12)
                down |= SDL_GetGamepadAxis(s_Gamepad, SDL_GAMEPAD_AXIS_LEFTY) <
                        -16000;
            if (i == 13)
                down |= SDL_GetGamepadAxis(s_Gamepad, SDL_GAMEPAD_AXIS_LEFTX) >
                        16000;
            if (i == 14)
                down |= SDL_GetGamepadAxis(s_Gamepad, SDL_GAMEPAD_AXIS_LEFTY) >
                        16000;
            if (i == 15)
                down |= SDL_GetGamepadAxis(s_Gamepad, SDL_GAMEPAD_AXIS_LEFTX) <
                        -16000;
        }
        if (down)
            pressed |= 1u << i;
    }
    char pad[PSYZ_PAD_BUF_LEN] = {0, PSYZ_CTRL_DIGITAL_PAD};
    pad[2] = (char)~(pressed >> 8);
    pad[3] = (char)~pressed;
    Psyz_PadsSet(0, pad, sizeof(pad));
}

void PcUpgradesInit(void) { Psyz_OverlayEvent_SDL3(OnEvent); }

void PcUpgradesShutdown(void) {
    PcArtworkShutdown();
    PcVoiceStop();
    CutscenePcAlloc(NULL, 0);
    CloseSettings();
    if (s_Gamepad)
        SDL_CloseGamepad(s_Gamepad);
    s_Gamepad = NULL;
}
