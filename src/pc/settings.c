// SPDX-License-Identifier: AGPL-3.0-or-later
#include "upgrades.h"
#include <SDL3/SDL.h>
#include <ctype.h>
#include <errno.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

PcSettings g_PcSettings;
const char* g_PcSettingsPath = "build/local-pc/settings.ini";

static const struct {
    const char* name;
    size_t offset;
    int minimum, maximum;
} fields[] = {
#define FIELD(name, low, high) {#name, offsetof(PcSettings, name), low, high}
    FIELD(widescreen, 0, 1),       FIELD(reduceFlashes, 0, 1),
    FIELD(palette, 0, 3),          FIELD(bugFixes, 0, 1),
    FIELD(masterVolume, 0, 100),   FIELD(effectsVolume, 0, 100),
    FIELD(musicVolume, 0, 100),    FIELD(controller, 0, 15),
    FIELD(quickItems, 0, 1),       FIELD(spellShortcuts, 0, 1),
    FIELD(protectSubweapon, 0, 1), FIELD(warpChooser, 0, 1),
    FIELD(skipSeenDialogue, 0, 1), FIELD(hudScale, 100, 150),
    FIELD(statusHud, 0, 1),        FIELD(subtitleScale, 0, 3),
    FIELD(videoFilter, 0, 3),      FIELD(filterStrength, 0, 100),
#undef FIELD
};

void PcSettingsDefaults(PcSettings* s) {
    static const int keys[16] = {
        SDL_SCANCODE_W,   SDL_SCANCODE_E,     SDL_SCANCODE_Q,
        SDL_SCANCODE_R,   SDL_SCANCODE_S,     SDL_SCANCODE_D,
        SDL_SCANCODE_X,   SDL_SCANCODE_Z,     SDL_SCANCODE_BACKSPACE,
        SDL_SCANCODE_1,   SDL_SCANCODE_2,     SDL_SCANCODE_RETURN,
        SDL_SCANCODE_UP,  SDL_SCANCODE_RIGHT, SDL_SCANCODE_DOWN,
        SDL_SCANCODE_LEFT};
    static const int buttons[16] = {
        -2,
        -3,
        SDL_GAMEPAD_BUTTON_LEFT_SHOULDER,
        SDL_GAMEPAD_BUTTON_RIGHT_SHOULDER,
        SDL_GAMEPAD_BUTTON_NORTH,
        SDL_GAMEPAD_BUTTON_EAST,
        SDL_GAMEPAD_BUTTON_SOUTH,
        SDL_GAMEPAD_BUTTON_WEST,
        SDL_GAMEPAD_BUTTON_BACK,
        SDL_GAMEPAD_BUTTON_LEFT_STICK,
        SDL_GAMEPAD_BUTTON_RIGHT_STICK,
        SDL_GAMEPAD_BUTTON_START,
        SDL_GAMEPAD_BUTTON_DPAD_UP,
        SDL_GAMEPAD_BUTTON_DPAD_RIGHT,
        SDL_GAMEPAD_BUTTON_DPAD_DOWN,
        SDL_GAMEPAD_BUTTON_DPAD_LEFT};
    memset(s, 0, sizeof(*s));
    s->masterVolume = s->effectsVolume = s->musicVolume = 100;
    s->hudScale = 100;
    s->filterStrength = 75;
    memcpy(s->keys, keys, sizeof(keys));
    memcpy(s->buttons, buttons, sizeof(buttons));
}

static char* Trim(char* s) {
    while (isspace((unsigned char)*s))
        s++;
    char* end = s + strlen(s);
    while (end > s && isspace((unsigned char)end[-1]))
        *--end = 0;
    return s;
}

bool PcSettingsLoad(PcSettings* s, const char* path) {
    FILE* f = fopen(path, "r");
    if (!f)
        return errno == ENOENT;
    PcSettings result = *s;
    char line[1024];
    bool ok = true;
    while (fgets(line, sizeof(line), f)) {
        char* name = Trim(line);
        if (!*name || *name == '#')
            continue;
        char* equal = strchr(name, '=');
        if (!equal) {
            ok = false;
            break;
        }
        *equal = 0;
        char* value = Trim(equal + 1);
        name = Trim(name);
        if (!strcmp(name, "contentPack")) {
            if (strlen(value) >= sizeof(result.contentPack)) {
                ok = false;
                break;
            }
            strcpy(result.contentPack, value);
            continue;
        }
        char* end;
        errno = 0;
        long number = strtol(value, &end, 10);
        if (errno || end == value || *end) {
            ok = false;
            break;
        }
        bool found = false;
        for (unsigned i = 0; i < sizeof(fields) / sizeof(*fields); i++) {
            if (strcmp(name, fields[i].name))
                continue;
            if (number < fields[i].minimum || number > fields[i].maximum) {
                ok = false;
                break;
            }
            *(int*)((char*)&result + fields[i].offset) = (int)number;
            found = true;
            break;
        }
        int index, used = 0;
        if (!found && sscanf(name, "key%d%n", &index, &used) == 1 &&
            name[used] == 0 && index >= 0 && index < 16 && number > 0 &&
            number < SDL_SCANCODE_COUNT) {
            result.keys[index] = (int)number;
            found = true;
        }
        used = 0;
        if (!found && sscanf(name, "button%d%n", &index, &used) == 1 &&
            name[used] == 0 && index >= 0 && index < 16 && number >= -3 &&
            number < SDL_GAMEPAD_BUTTON_COUNT) {
            result.buttons[index] = (int)number;
            found = true;
        }
        if (!found || !ok) {
            ok = false;
            break;
        }
    }
    ok = ok && !ferror(f);
    fclose(f);
    if (ok)
        *s = result;
    return ok;
}

bool PcSettingsSave(const PcSettings* s, const char* path) {
    char temporary[1024];
    if (snprintf(temporary, sizeof(temporary), "%s.tmp", path) >=
        sizeof(temporary))
        return false;
    FILE* f = fopen(temporary, "w");
    if (!f)
        return false;
    bool ok = true;
    for (unsigned i = 0; i < sizeof(fields) / sizeof(*fields); i++) {
        int value = *(const int*)((const char*)s + fields[i].offset);
        if (fprintf(f, "%s=%d\n", fields[i].name, value) < 0)
            ok = false;
    }
    for (int i = 0; i < 16; i++) {
        if (fprintf(f, "key%d=%d\nbutton%d=%d\n", i, s->keys[i], i,
                    s->buttons[i]) < 0)
            ok = false;
    }
    if (fprintf(f, "contentPack=%s\n", s->contentPack) < 0)
        ok = false;
    if (fclose(f))
        ok = false;
    if (!ok || !SDL_RenamePath(temporary, path)) {
        remove(temporary);
        return false;
    }
    return true;
}
