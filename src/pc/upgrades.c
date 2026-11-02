// SPDX-License-Identifier: AGPL-3.0-or-later
#include <game.h>
#include <sfx.h>
#include "pc.h"
#include "upgrades.h"
#include "qol.h"
#include "menu.h"
#include "saves.h"
#include "weapon_fx.h"
#include <SDL3/SDL.h>
#include <psyz.h>
#include <psyz/overlay_sdl3.h>
#include <string.h>
#include <stdlib.h>

static SDL_Window* s_Window;
static SDL_Renderer* s_Renderer;
static SDL_Surface* s_Surface;
static SDL_Texture *s_Backdrop, *s_Font;
static bool s_Open, s_Home, s_OriginalRequested, s_ReleaseInput;
static SDL_Scancode s_FullscreenKey;
static int s_BackdropFrames;
static int s_HomeRow, s_TitleAction;
static bool s_Title;
static PcSaveEntry s_RenameSave;
static SDL_Gamepad* s_Gamepad;
static int s_Row, s_Capture = -1;
static bool s_PadCapture, s_ShowAudio;
static bool s_Qol;
static const char* s_Message = "Settings are saved when changed.";
static const char* buttons[] = {
    "L2",     "R2", "L1", "R1",    "Triangle", "Circle", "Cross", "Square",
    "Select", "L3", "R3", "Start", "Up",       "Right",  "Down",  "Left"};
static const char* palettes[] = {
    "Original", "High contrast", "Blue/Gold", "Monochrome"};
static const char* videoFilters[] = {
    "Original (nearest)", "Bilinear", "CRT (soft)", "xBR level 2", "Synthwave"};

static void Save(void) {
    s_Message = PcSettingsSave(&g_PcSettings, g_PcSettingsPath)
                    ? "Settings saved."
                    : "Could not save settings; check the path.";
}

static void CloseSettings(void) {
    PcWeaponFxStop();
    Psyz_OverlaySetSurface_SDL3(NULL);
    s_ReleaseInput |= s_Open;
    if (s_Window)
        SDL_StopTextInput(s_Window);
    SDL_DestroyTexture(s_Backdrop);
    SDL_DestroyTexture(s_Font);
    s_Backdrop = s_Font = NULL;
    if (s_Renderer)
        SDL_DestroyRenderer(s_Renderer);
    SDL_DestroySurface(s_Surface);
    s_Renderer = NULL;
    s_Surface = NULL;
    s_Window = NULL;
    s_Open = false;
    s_Capture = -1;
}

static void CaptureMenuArtwork(void) {
    int width, height;
    u8* pixels = Psyz_VideoAllocCapturedFrame(&width, &height);
    if (pixels) {
        SDL_Surface* image = SDL_CreateSurfaceFrom(
            width, height, SDL_PIXELFORMAT_RGB24, pixels, width * 3);
        if (image) {
            s_Backdrop = SDL_CreateTextureFromSurface(s_Renderer, image);
            SDL_DestroySurface(image);
        }
        free(pixels);
    }
    // Use the same 8x8 glyph page and palette as MenuDrawChar.
    u16 glyphs[32 * 128], palette[16];
    RECT glyphRect = {896, 256, 32, 128};
    int clut = g_ClutIds[0x196];
    RECT paletteRect = {(clut & 63) * 16, clut >> 6, 16, 1};
    StoreImage(&glyphRect, (u_long*)glyphs);
    StoreImage(&paletteRect, (u_long*)palette);
    DrawSync(0);
    SDL_Surface* atlas = SDL_CreateSurface(128, 128, SDL_PIXELFORMAT_RGBA32);
    if (!atlas)
        return;
    bool visible = false;
    for (int y = 0; y < 128; y++) {
        u8* row = (u8*)atlas->pixels + y * atlas->pitch;
        for (int x = 0; x < 128; x++) {
            int index = (glyphs[y * 32 + x / 4] >> ((x & 3) * 4)) & 15;
            int color = palette[index];
            row[x * 4] = (color & 31) * 255 / 31;
            row[x * 4 + 1] = ((color >> 5) & 31) * 255 / 31;
            row[x * 4 + 2] = ((color >> 10) & 31) * 255 / 31;
            row[x * 4 + 3] = color ? 255 : 0;
            visible |= color != 0;
        }
    }
    if (visible) {
        s_Font = SDL_CreateTextureFromSurface(s_Renderer, atlas);
        if (s_Font)
            SDL_SetTextureBlendMode(s_Font, SDL_BLENDMODE_BLEND);
    }
    SDL_DestroySurface(atlas);
    if (s_Backdrop)
        SDL_SetTextureScaleMode(s_Backdrop, SDL_SCALEMODE_NEAREST);
    if (s_Font)
        SDL_SetTextureScaleMode(s_Font, SDL_SCALEMODE_NEAREST);
}

void PcMenuPanel(
    SDL_Renderer* renderer, float x, float y, float w, float h, float alpha) {
    SDL_Vertex vertices[] = {
        {{x, y}, {0.075f, 0.10f, 0.38f, alpha}, {0, 0}},
        {{x + w, y}, {0.025f, 0.045f, 0.24f, alpha}, {0, 0}},
        {{x, y + h}, {0.015f, 0.025f, 0.10f, alpha}, {0, 0}},
        {{x + w, y + h}, {0.005f, 0.01f, 0.035f, alpha}, {0, 0}}};
    const int indices[] = {0, 1, 2, 2, 1, 3};
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_RenderGeometry(renderer, NULL, vertices, 4, indices, 6);
}

void PcMenuBackground(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 8, 12, 48, 255);
    SDL_RenderClear(renderer);
    bool backdrop = renderer == s_Renderer && s_Backdrop;
    if (backdrop)
        SDL_RenderTexture(renderer, s_Backdrop, NULL, NULL);
    int width, height;
    float sx, sy;
    SDL_GetRenderOutputSize(renderer, &width, &height);
    SDL_GetRenderScale(renderer, &sx, &sy);
    SDL_FRect panel = {4, 4, width / sx - 8, height / sy - 8};
    PcMenuPanel(
        renderer, panel.x, panel.y, panel.w, panel.h, backdrop ? 0.85f : 1.0f);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
    SDL_SetRenderDrawColor(renderer, 185, 180, 140, 255);
    SDL_RenderRect(renderer, &panel);
}

void PcMenuText(SDL_Renderer* renderer, int x, int y, const char* text) {
    if (renderer != s_Renderer || !s_Font) {
        SDL_RenderDebugText(renderer, x, y, text);
        return;
    }
    u8 red, green, blue, alpha;
    SDL_GetRenderDrawColor(renderer, &red, &green, &blue, &alpha);
    SDL_SetTextureColorMod(s_Font, red, green, blue);
    SDL_SetTextureAlphaMod(s_Font, alpha);
    int start = x;
    for (; *text; text++, x += 8) {
        if (*text == '\n') {
            x = start - 8;
            y += 8;
            continue;
        }
        int ch = (u8)*text;
        if (ch < 32 || ch > 126)
            ch = '?';
        ch -= 32;
        SDL_FRect source = {(ch & 15) * 8, (ch >> 4) * 8, 8, 8};
        SDL_FRect destination = {x, y, 8, 8};
        SDL_RenderTexture(renderer, s_Font, &source, &destination);
    }
}

static void OpenMenu(bool home, bool adventure, int page) {
    CloseSettings();
    // The prologue uses the original menu-free Richter pause.
    if ((home || adventure) && g_GameState == Game_Play &&
        g_StageId == STAGE_ST0)
        return;
    s_Window = Psyz_OverlayWindow_SDL3();
    if (!s_Window)
        return;
    s_Home = home;
    s_Qol = adventure;
    s_Surface = SDL_CreateSurface(
        adventure || home ? 1200 : 880, 920, SDL_PIXELFORMAT_RGBA32);
    if (s_Surface)
        s_Renderer = SDL_CreateSoftwareRenderer(s_Surface);
    if (!s_Renderer) {
        ERRORF("Pause menu: %s", SDL_GetError());
        CloseSettings();
        return;
    }
    s_Open = true;
    // Let both PS1 framebuffers shed the previous menu text before capture.
    s_BackdropFrames = g_GameState == Game_MainMenu ? 3 : 0;
    if (adventure)
        PcQolUiOpenPage(page);
}

static void OpenSettings(void) { OpenMenu(false, false, 0); }
static void OpenAdventure(void) { OpenMenu(false, true, 0); }

bool PcMenuPause(void) {
    if (s_OriginalRequested) {
        s_OriginalRequested = false;
        return false;
    }
    OpenMenu(true, false, 0);
    return s_Open;
}

static void HomeKey(SDL_Scancode code);

int PcMenuTitle(void) {
    if (s_TitleAction) {
        int action = s_TitleAction;
        s_TitleAction = 0;
        s_Title = false;
        return action;
    }
    if (!s_Title) {
        s_Title = true;
        g_GameClearFlag = PcSaveClearFlags();
        s_HomeRow = 0;
        s_Message = "Choose an adventure.";
    }
    if (!s_Open) {
        if (g_pads[0].repeat & (PAD_UP | PAD_LEFT)) {
            g_api.PlaySfx(SFX_UI_MP_FULL);
            HomeKey(SDL_SCANCODE_UP);
        }
        if (g_pads[0].repeat & (PAD_DOWN | PAD_RIGHT)) {
            g_api.PlaySfx(SFX_UI_MP_FULL);
            HomeKey(SDL_SCANCODE_DOWN);
        }
        if (g_pads[0].tapped & (PAD_CROSS | PAD_START)) {
            g_api.PlaySfx(SFX_UI_CONFIRM);
            HomeKey(SDL_SCANCODE_RETURN);
        }
        if (g_pads[0].tapped & (PAD_TRIANGLE | PAD_CIRCLE | PAD_SELECT))
            HomeKey(SDL_SCANCODE_ESCAPE);
    }
    return 0;
}

bool PcMenuRename(const char* name) {
    return PcSaveRename(&s_RenameSave, name);
}

static const char* s_TitleEntries[] = {
    "continue",    "load game", "new game", "manage saves",
    "pc settings", "resume",    "back"};

int PcMenuTitleCount(void) { return LEN(s_TitleEntries); }
int PcMenuTitleRow(void) { return s_HomeRow; }
const char* PcMenuTitleLabel(int row) { return s_TitleEntries[row]; }
const char* PcMenuTitleMessage(void) { return s_Message; }
bool PcMenuIsOpen(void) { return s_Open; }

static const char* s_HomeEntries[] = {
    "Character / Relics / Familiars",
    "Map",
    "Inventory",
    "Loadouts",
    "Spells",
    "Saves",
    "Dialogue",
    "Gameplay options",
    "PC settings",
    "Resume game"};

static void HomeKey(SDL_Scancode code) {
    int count = s_Title ? LEN(s_TitleEntries) : LEN(s_HomeEntries);
    if (code == SDL_SCANCODE_UP)
        s_HomeRow = (s_HomeRow + count - 1) % count;
    if (code == SDL_SCANCODE_DOWN)
        s_HomeRow = (s_HomeRow + 1) % count;
    if (code == SDL_SCANCODE_ESCAPE) {
        if (s_Title)
            s_TitleAction = 3;
        CloseSettings();
        return;
    }
    if (code != SDL_SCANCODE_RETURN)
        return;
    if (s_Title) {
        switch (s_HomeRow) {
        case 0:
            if (PcSaveContinue()) {
                s_TitleAction = 2;
                CloseSettings();
            } else
                s_Message =
                    "No valid save to continue. Choose New game or Load game.";
            break;
        case 1:
        case 3:
            OpenMenu(false, true, 4);
            PcQolUiLoadMode(s_HomeRow == 1);
            break;
        case 2:
            s_TitleAction = 1;
            CloseSettings();
            break;
        case 4:
            OpenSettings();
            break;
        case 5:
            if (PcQolResume()) {
                s_Title = false;
                s_TitleAction = 0;
                CloseSettings();
            } else
                s_Message = g_PcQolMessage;
            break;
        case 6:
            s_TitleAction = 3;
            CloseSettings();
            break;
        }
        return;
    }
    if (s_HomeRow == 0) {
        if (PcQolReady() && g_PlayableCharacter == PLAYER_ALUCARD &&
            g_StageId != STAGE_ST0) {
            s_OriginalRequested = true;
            g_pads[0].pressed &= ~PAD_START;
            g_pads[0].previous &= ~PAD_START;
            CloseSettings();
        } else
            s_Message = "Character management requires Alucard in the castle.";
    } else if (s_HomeRow < 8)
        OpenMenu(false, true, s_HomeRow - 1);
    else if (s_HomeRow == 8)
        OpenSettings();
    else
        CloseSettings();
}

static SDL_Scancode MenuButton(int button) {
    switch (button) {
    case SDL_GAMEPAD_BUTTON_DPAD_UP:
        return SDL_SCANCODE_UP;
    case SDL_GAMEPAD_BUTTON_DPAD_DOWN:
        return SDL_SCANCODE_DOWN;
    case SDL_GAMEPAD_BUTTON_DPAD_LEFT:
        return SDL_SCANCODE_LEFT;
    case SDL_GAMEPAD_BUTTON_DPAD_RIGHT:
        return SDL_SCANCODE_RIGHT;
    case SDL_GAMEPAD_BUTTON_SOUTH:
        return SDL_SCANCODE_RETURN;
    case SDL_GAMEPAD_BUTTON_EAST:
        return SDL_SCANCODE_ESCAPE;
    case SDL_GAMEPAD_BUTTON_START:
        return SDL_SCANCODE_ESCAPE;
    default:
        return SDL_SCANCODE_UNKNOWN;
    }
}

static void DrawHome(void) {
    SDL_SetRenderScale(s_Renderer, 2, 2);
    PcMenuBackground(s_Renderer);
    SDL_SetRenderDrawColor(s_Renderer, 185, 180, 140, 255);
    SDL_FRect border = {6, 6, 588, 448};
    SDL_RenderRect(s_Renderer, &border);
    PcMenuText(s_Renderer, 30, 28, "SYMPHONY OF THE NIGHT - PAUSED");
    int count = LEN(s_HomeEntries);
    for (int i = 0; i < count; i++) {
        char line[96];
        snprintf(line, sizeof(line), "%c %s", i == s_HomeRow ? '>' : ' ',
                 s_HomeEntries[i]);
        SDL_SetRenderDrawColor(s_Renderer, 230, i == s_HomeRow ? 215 : 235,
                               i == s_HomeRow ? 150 : 245, 255);
        PcMenuText(s_Renderer, 30, 65 + i * 30, line);
    }
    PcMenuText(s_Renderer, 20, 394, s_Message);
    PcMenuText(s_Renderer, 20, 422,
               "D-pad / arrows: select | A / Enter: open | B / Escape: resume");
    SDL_RenderPresent(s_Renderer);
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
    case 26:
        value = &g_PcSettings.videoFilter;
        maximum = 4;
        break;
    case 27:
        value = &g_PcSettings.filterStrength;
        maximum = 100;
        step = 5;
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
    if ((e->type == SDL_EVENT_KEY_DOWN || e->type == SDL_EVENT_KEY_UP) &&
        (e->key.scancode == SDL_SCANCODE_RETURN ||
         e->key.scancode == SDL_SCANCODE_KP_ENTER) &&
        ((e->key.mod & SDL_KMOD_CTRL) || s_FullscreenKey == e->key.scancode)) {
        Psyz_OverlayConsumeEvent_SDL3();
        if (e->type == SDL_EVENT_KEY_DOWN) {
            s_FullscreenKey = e->key.scancode;
            if (!e->key.repeat)
                Psyz_OverlayToggleFullscreen_SDL3();
        } else
            s_FullscreenKey = SDL_SCANCODE_UNKNOWN;
        return;
    }
    if (s_Open &&
        (e->type == SDL_EVENT_KEY_DOWN || e->type == SDL_EVENT_KEY_UP ||
         e->type == SDL_EVENT_GAMEPAD_BUTTON_DOWN ||
         e->type == SDL_EVENT_GAMEPAD_AXIS_MOTION))
        Psyz_OverlayConsumeEvent_SDL3();
    if (e->type == SDL_EVENT_KEY_DOWN &&
        (e->key.scancode == SDL_SCANCODE_F1 ||
         e->key.scancode == SDL_SCANCODE_F2 ||
         (e->key.scancode >= SDL_SCANCODE_F5 &&
          e->key.scancode <= SDL_SCANCODE_F10)))
        Psyz_OverlayConsumeEvent_SDL3();
    if (s_Open && e->type == SDL_EVENT_KEY_DOWN && !e->key.repeat &&
        e->key.scancode == SDL_SCANCODE_F4) {
        Psyz_OverlayToggleFullscreen_SDL3();
        return;
    }
    if (s_Title && !s_Open && e->type == SDL_EVENT_KEY_DOWN && !e->key.repeat &&
        e->key.scancode == SDL_SCANCODE_ESCAPE) {
        Psyz_OverlayConsumeEvent_SDL3();
        HomeKey(SDL_SCANCODE_ESCAPE);
        return;
    }
    if (s_Open && e->type == SDL_EVENT_WINDOW_CLOSE_REQUESTED) {
        CloseSettings();
        SDL_Event quit = {.type = SDL_EVENT_QUIT};
        SDL_PushEvent(&quit);
        return;
    }
    if (e->type == SDL_EVENT_KEY_DOWN && !e->key.repeat &&
        e->key.scancode == SDL_SCANCODE_F1) {
        if (s_Open && !s_Qol && !s_Home) {
            CloseSettings();
        } else
            OpenSettings();
        return;
    }
    if (e->type == SDL_EVENT_KEY_DOWN && !e->key.repeat &&
        e->key.scancode == SDL_SCANCODE_F5) {
        if (s_Open && s_Qol) {
            CloseSettings();
        } else
            OpenAdventure();
        return;
    }
    if (s_Open && s_Home) {
        if (e->type == SDL_EVENT_KEY_DOWN && !e->key.repeat)
            HomeKey(e->key.scancode);
        if (e->type == SDL_EVENT_GAMEPAD_BUTTON_DOWN && s_Gamepad &&
            e->gbutton.which == SDL_GetGamepadID(s_Gamepad))
            HomeKey(MenuButton(e->gbutton.button));
        return;
    }
    if (s_Open && s_Qol && e->type != SDL_EVENT_WINDOW_CLOSE_REQUESTED) {
        if ((e->type == SDL_EVENT_KEY_DOWN || e->type == SDL_EVENT_KEY_UP) &&
            e->key.windowID != SDL_GetWindowID(s_Window))
            return;
        if (e->type == SDL_EVENT_GAMEPAD_BUTTON_DOWN && s_Gamepad &&
            e->gbutton.which != SDL_GetGamepadID(s_Gamepad))
            return;
        if (e->type == SDL_EVENT_GAMEPAD_AXIS_MOTION && s_Gamepad &&
            e->gaxis.which != SDL_GetGamepadID(s_Gamepad))
            return;
        bool back = (e->type == SDL_EVENT_KEY_DOWN &&
                     e->key.scancode == SDL_SCANCODE_ESCAPE) ||
                    (e->type == SDL_EVENT_GAMEPAD_BUTTON_DOWN &&
                     e->gbutton.button == SDL_GAMEPAD_BUTTON_EAST);
        PcQolUiEvent(e, s_Window);
        if (PcQolUiWantsClose()) {
            int action = PcQolUiSaveAction();
            if (s_Title && g_GameState != Game_MainMenu) {
                s_Title = false;
                s_TitleAction = 0;
                CloseSettings();
            } else if (s_Title && action) {
                if (action == 2)
                    PcQolUiSelectedSave(&s_RenameSave);
                s_TitleAction = action == 1 ? 2 : 5;
                CloseSettings();
            } else if (back) {
                if (g_GameState == Game_MainMenu)
                    CloseSettings();
                else
                    OpenMenu(true, false, 0);
            } else
                CloseSettings();
        }
        return;
    }
    if (!s_Window && e->type == SDL_EVENT_KEY_DOWN && !e->key.repeat) {
        if (e->key.scancode == SDL_SCANCODE_F6)
            PcQolUseItem(g_PcQol.quickItem);
        if (e->key.scancode == SDL_SCANCODE_F7)
            PcQolCast(g_PcQol.quickSpell);
        if (e->key.scancode == SDL_SCANCODE_F10 && g_PcQol.loadout >= 0 &&
            g_PcQol.loadout < PC_LOADOUTS &&
            g_PcQol.loadoutValid[g_PcQol.loadout] && PcQolReady())
            PcQolApplyGear(g_PcQol.loadouts[g_PcQol.loadout]);
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
        CloseSettings();
        SDL_Event quit = {.type = SDL_EVENT_QUIT};
        SDL_PushEvent(&quit);
        return;
    }
    if (s_Capture >= 0 && e->type == SDL_EVENT_KEY_DOWN &&
        e->key.scancode == SDL_SCANCODE_ESCAPE) {
        s_Capture = -1;
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
        return;
    }
    if (s_Capture >= 0 && s_PadCapture &&
        e->type == SDL_EVENT_GAMEPAD_BUTTON_DOWN && s_Gamepad &&
        e->gbutton.which == SDL_GetGamepadID(s_Gamepad)) {
        if (SDL_GetGamepadButton(s_Gamepad, SDL_GAMEPAD_BUTTON_BACK) &&
            SDL_GetGamepadButton(s_Gamepad, SDL_GAMEPAD_BUTTON_EAST)) {
            s_Capture = -1;
            s_Message = "Rebinding cancelled.";
            return;
        }
        g_PcSettings.buttons[s_Capture] = e->gbutton.button;
        s_Capture = -1;
        Save();
        return;
    }
    if (e->type == SDL_EVENT_GAMEPAD_BUTTON_DOWN && s_Capture < 0 &&
        s_Gamepad && e->gbutton.which == SDL_GetGamepadID(s_Gamepad)) {
        SDL_Event key = {.type = SDL_EVENT_KEY_DOWN};
        key.key.windowID = SDL_GetWindowID(s_Window);
        key.key.scancode = MenuButton(e->gbutton.button);
        OnEvent(&key);
        return;
    }
    if (e->type != SDL_EVENT_KEY_DOWN || e->key.repeat ||
        e->key.windowID != SDL_GetWindowID(s_Window))
        return;
    SDL_Scancode code = e->key.scancode;
    if (s_ShowAudio) {
        if (code == SDL_SCANCODE_ESCAPE || code == SDL_SCANCODE_RETURN)
            s_ShowAudio = false;
        return;
    }
    if (s_Capture >= 0 && !s_PadCapture) {
        if (code != SDL_SCANCODE_ESCAPE && code != SDL_SCANCODE_F4) {
            g_PcSettings.keys[s_Capture] = code;
            s_Capture = -1;
            Save();
        }
        return;
    }
    if (code == SDL_SCANCODE_ESCAPE) {
        if (g_GameState == Game_MainMenu)
            CloseSettings();
        else
            OpenMenu(true, false, 0);
        return;
    }
    if (code == SDL_SCANCODE_UP)
        s_Row = (s_Row + 27) % 28;
    if (code == SDL_SCANCODE_DOWN)
        s_Row = (s_Row + 1) % 28;
    if (code == SDL_SCANCODE_LEFT)
        Change(-1);
    if (code == SDL_SCANCODE_RIGHT || code == SDL_SCANCODE_RETURN)
        Change(1);
}

static void DrawSettings(void) {
    PcMenuBackground(s_Renderer);
    SDL_SetRenderScale(s_Renderer, 2, 2);
    SDL_SetRenderDrawColor(s_Renderer, 230, 235, 245, 255);
    PcMenuText(s_Renderer, 12, 10, "SYSTEM - F1 resumes, Escape returns");
    PcMenuText(
        s_Renderer, 12, 24, "Up/Down: select   Left/Right/Enter: change");
    char text[220];
    if (s_ShowAudio) {
        PcMenuText(s_Renderer, 12, 45, "AUDIO SNAPSHOT - B/Escape/Enter: back");
        PcMenuText(s_Renderer, 12, 62,
                   "Voice  Envelope  Volume L/R  Pitch  Sample addr");
        Psyz_AudioLock();
        for (int i = 0; i < 24; i++) {
            unsigned reg = i * 16;
            snprintf(
                text, sizeof(text), "%2d     %04X      %04X/%04X   %04X   %05X",
                i, Psyz_SpuRead(reg + 12), Psyz_SpuRead(reg),
                Psyz_SpuRead(reg + 2), Psyz_SpuRead(reg + 4),
                Psyz_SpuRead(reg + 6) * 8);
            PcMenuText(s_Renderer, 12, 80 + i * 12, text);
        }
        snprintf(text, sizeof(text),
                 "SPUCNT %04X  Main %04X/%04X  CD %04X/%04X",
                 Psyz_SpuRead(0x1AA), Psyz_SpuRead(0x180), Psyz_SpuRead(0x182),
                 Psyz_SpuRead(0x1B0), Psyz_SpuRead(0x1B2));
        Psyz_AudioUnlock();
        PcMenuText(s_Renderer, 12, 386, text);
        SDL_RenderPresent(s_Renderer);
        return;
    }
    for (int row = 0; row < 28; row++) {
        const char* mark = row == s_Row ? ">" : " ";
        switch (row) {
        case 0:
            snprintf(text, sizeof(text), "%s Widescreen: %s%s", mark,
                     g_PcSettings.widescreen ? "16:9" : "Original",
                     PcViewportChangePending() ? " (after transition)" : "");
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
        case 26:
            snprintf(text, sizeof(text), "%s Video filter: %s", mark,
                     videoFilters[g_PcSettings.videoFilter]);
            break;
        case 27:
            snprintf(text, sizeof(text), "%s Filter strength: %d%%", mark,
                     g_PcSettings.filterStrength);
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
        PcMenuText(s_Renderer, 12, 45 + row * 13, text);
    }
    SDL_SetRenderDrawColor(s_Renderer, 180, 205, 230, 255);
    PcMenuText(s_Renderer, 12, 419,
               s_Capture >= 0 ? "Escape or hold pad Back+B: cancel rebind"
                              : s_Message);
    PcMenuText(
        s_Renderer, 12, 435, "F5 adventure | F4 fullscreen | B/Escape: back");
    SDL_RenderPresent(s_Renderer);
}

static void DrawOpenMenu(void) {
    if (s_Home)
        DrawHome();
    else if (s_Qol)
        PcQolUiDraw(s_Renderer);
    else
        DrawSettings();
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
    Psyz_VideoSetFilter(g_PcSettings.videoFilter, g_PcSettings.filterStrength);
    PcQolFrame();
    if (s_Title && g_GameState != Game_MainMenu) {
        s_Title = false;
        s_TitleAction = 0;
    }
    UpdateController();
    if (s_Open && s_BackdropFrames > 0)
        s_BackdropFrames--;
    else if (s_Open) {
        if (!s_Backdrop)
            CaptureMenuArtwork();
        if (g_GameState == Game_MainMenu) {
            DrawOpenMenu();
            Psyz_OverlaySetSurface_SDL3(s_Surface);
        } else {
            bool wasPaused = Psyz_AudioIsPaused();
            PcVoicePause(true);
            PcMoviePause(true);
            Psyz_AudioPause();
            Psyz_VideoPauseClock(1);
            while (s_Open && !Psyz_QuitRequested()) {
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
                if (s_Open) {
                    DrawOpenMenu();
                    if (!Psyz_OverlayPresent_SDL3(s_Surface)) {
                        ERRORF("Menu presentation: %s", SDL_GetError());
                        CloseSettings();
                    }
                }
                SDL_Delay(16);
            }
            Psyz_VideoPauseClock(0);
            PcVoicePause(false);
            PcMoviePause(false);
            if (!wasPaused)
                Psyz_AudioUnpause();
        }
    }
    Psyz_SpuSetMixVolume(
        g_PcSettings.masterVolume * g_PcSettings.effectsVolume / 100,
        PcVoiceDuration()
            ? 0
            : g_PcSettings.masterVolume * g_PcSettings.musicVolume / 100);
    PcVoiceUpdate();
    PcMovieUpdate();
    const bool* keys = SDL_GetKeyboardState(NULL);
    static bool hubHeld;
    bool hub =
        s_Gamepad && SDL_GetGamepadButton(s_Gamepad, SDL_GAMEPAD_BUTTON_BACK) &&
        SDL_GetGamepadButton(s_Gamepad, SDL_GAMEPAD_BUTTON_RIGHT_STICK);
    if (hub && !hubHeld && g_GameState != Game_MainMenu)
        OpenMenu(true, false, 0);
    hubHeld = hub;
    unsigned pressed = 0;
    for (int i = 0; i < 16; i++) {
        bool down = keys[g_PcSettings.keys[i]];
        if (s_FullscreenKey && g_PcSettings.keys[i] == s_FullscreenKey)
            down = false;
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
    if (s_ReleaseInput) {
        if (!pressed)
            s_ReleaseInput = false;
        pressed = 0;
    }
    if (hub || s_Open)
        pressed = 0;
    if (s_OriginalRequested)
        pressed |= PAD_START;
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
