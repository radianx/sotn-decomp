// SPDX-License-Identifier: AGPL-3.0-or-later
#include "qol.h"
#include "menu.h"
#include "inventory.h"
#include "../dra/dra.h"
#include <stdarg.h>
#include <string.h>
extern u32 D_8013AEE4;

static int s_Page, s_Row, s_Filter, s_Sort, s_Slot, s_Castle, s_X, s_Y;
static int s_Zoom = 6, s_MapFilter, s_Kind, s_Requirement;
static int s_Warp;
static bool s_Favorites, s_Close, s_Editing;
static bool s_PreviewTrigger;
static bool s_LoadMode, s_ArchiveConfirm;
static int s_SaveAction;
static char s_Note[48];
static PcSaveEntry* s_Saves;
static int s_SaveCount;
static SDL_Surface* s_SavePreview;
static int s_PreviewRow = -1;
static const char* pages[] = {
    "Map", "Inventory", "Loadouts", "Spells", "Saves", "Dialogue", "Options"};
static const char* filters[] = {"All",  "Weapons", "Shields", "Consumables",
                                "Head", "Armor",   "Capes",   "Accessories"};
static const char* slots[] = {"Left hand", "Right hand",  "Head",       "Armor",
                              "Cape",      "Accessory 1", "Accessory 2"};
static const char* AreaName(int stage) {
    static const char* names[16] = {
        "Marble Gallery",      "Outer Wall",       "Long Library",
        "Catacombs",           "Olrox's Quarters", "Abandoned Mine",
        "Royal Chapel",        "Castle Entrance",  "Castle Center",
        "Underground Caverns", "Colosseum",        "Castle Keep",
        "Alchemy Laboratory",  "Clock Tower",      "Warp room",
        "Outer Wall"};
    int index = stage == STAGE_NO3 ? 7 : stage & 31;
    return index < 16 ? names[index] : "Boss arena";
}
static void ElementNames(unsigned mask, char* out, size_t size) {
    static const char* names[] = {
        "Hit",  "Cut",  "Poison", "Curse",   "Stone", "Water",
        "Dark", "Holy", "Ice",    "Thunder", "Fire"};
    out[0] = 0;
    for (int i = 0; i < 11; i++)
        if (mask & (0x20u << i)) {
            if (out[0])
                SDL_strlcat(out, " ", size);
            SDL_strlcat(out, names[i], size);
        }
    if (mask & 31)
        SDL_strlcat(out, " Special", size);
    if (!out[0])
        SDL_strlcpy(out, "None", size);
}
static const char* spellNames[8] = {
    "Dark Metamorphosis", "Summon Spirit", "Hellfire",   "Tetra Spirit",
    "Wolf Charge",        "Soul Steal",    "Wing Smash", "Sword Brothers"};
static const char* combos[8] = {
    "Back, Up-Back, Up, Up-Forward, Forward, Attack",
    "Back, Forward, Up, Down, Attack",
    "Up, Down, Down-Forward, Forward, Attack",
    "Hold Up, Up-Forward, Forward, Down-Forward, Down, Attack",
    "Wolf: Down, Down-Forward, Forward, Attack",
    "Back, Forward, Down-Forward, Down, Down-Back, Back, Forward, Attack",
    "Bat: hold Jump; Up, Up-Back, Back, Down-Back, Down, Down-Forward, "
    "Forward; release",
    "Sword familiar Lv50: Down, Down-Forward, Forward, Up-Forward, hold Up, "
    "Down, Attack"};
static void Text(SDL_Renderer* r, int x, int y, const char* format, ...) {
    char text[256];
    va_list args;
    va_start(args, format);
    vsnprintf(text, sizeof(text), format, args);
    va_end(args);
    PcMenuText(r, x, y, text);
}
static void Wrap(SDL_Renderer* r, int x, int y, const char* text, int columns) {
    while (*text && y < 405) {
        char line[96];
        int n = SDL_min(strlen(text), columns);
        if (text[n]) {
            int end = n;
            while (end > 0 && text[end] != ' ')
                end--;
            if (end)
                n = end;
        }
        memcpy(line, text, n);
        line[n] = 0;
        PcMenuText(r, x, y, line);
        y += 11;
        text += n;
        while (*text == ' ')
            text++;
    }
}
static void RefreshSaves(void) {
    SDL_free(s_Saves);
    int count = PcQolSaveList(NULL, 0);
    s_Saves = SDL_calloc(count ? count : 1, sizeof(*s_Saves));
    s_SaveCount = s_Saves ? PcQolSaveList(s_Saves, count) : 0;
}
void PcQolUiOpen(void) {
    PcInventoryPreviewReset();
    s_PreviewTrigger = false;
    s_Close = s_Editing = s_LoadMode = s_ArchiveConfirm = false;
    s_SaveAction = 0;
    s_Note[0] = 0;
    SDL_DestroySurface(s_SavePreview);
    s_SavePreview = NULL;
    s_PreviewRow = -1;
    PcQolMapPosition(&s_Castle, &s_X, &s_Y);
    RefreshSaves();
    if (g_StageId == STAGE_WRP || g_StageId == STAGE_RWRP) {
        int flags =
            g_CastleFlags[g_StageId == STAGE_RWRP ? RWRP_UNLOCKS : WRP_UNLOCKS];
        for (int i = 0; i < 5; i++)
            if (flags & (1 << i)) {
                s_Warp = i;
                break;
            }
    }
}
void PcQolUiOpenPage(int page) {
    PcQolUiOpen();
    s_Page = SDL_clamp(page, 0, 6);
    s_Row = 0;
}
void PcQolUiLoadMode(bool loading) { s_LoadMode = loading; }
int PcQolUiSaveAction(void) { return s_SaveAction; }
bool PcQolUiSelectedSave(PcSaveEntry* entry) {
    if (s_Row < 0 || s_Row >= s_SaveCount)
        return false;
    *entry = s_Saves[s_Row];
    return true;
}
bool PcQolUiWantsClose(void) { return s_Close; }

static void MapKey(SDL_Scancode key, SDL_Window* window) {
    if (key == SDL_SCANCODE_V)
        key = SDL_SCANCODE_K;
    if (key == SDL_SCANCODE_I)
        key = SDL_SCANCODE_R;
    if (g_PcSettings.warpChooser &&
        (g_StageId == STAGE_WRP || g_StageId == STAGE_RWRP)) {
        if (key == SDL_SCANCODE_W || key == SDL_SCANCODE_S) {
            int flags = g_CastleFlags[g_StageId == STAGE_RWRP ? RWRP_UNLOCKS
                                                              : WRP_UNLOCKS];
            for (int i = 0; i < 5; i++) {
                s_Warp = (s_Warp + 1) % 5;
                if (flags & (1 << s_Warp))
                    break;
            }
        }
        if (key == SDL_SCANCODE_SPACE || key == SDL_SCANCODE_U) {
            s_Close = PcQolWarpChoose(s_Warp);
            g_PcQolMessage =
                s_Close ? "Destination selected. Press Up on the warp platform."
                        : "Destination locked or player is not on the warp "
                          "platform.";
        }
    }
    if (key == SDL_SCANCODE_LEFT)
        s_X = SDL_max(0, s_X - 1);
    if (key == SDL_SCANCODE_RIGHT)
        s_X = SDL_min(63, s_X + 1);
    if (key == SDL_SCANCODE_UP)
        s_Y = SDL_max(0, s_Y - 1);
    if (key == SDL_SCANCODE_DOWN)
        s_Y = SDL_min(63, s_Y + 1);
    if (key == SDL_SCANCODE_EQUALS)
        s_Zoom = SDL_min(24, s_Zoom + 2);
    if (key == SDL_SCANCODE_MINUS)
        s_Zoom = SDL_max(4, s_Zoom - 2);
    if (key == SDL_SCANCODE_C)
        s_Castle ^= 1;
    if (key == SDL_SCANCODE_F)
        s_MapFilter = (s_MapFilter + 1) % 5;
    if (key == SDL_SCANCODE_K)
        s_Kind = (s_Kind + 1) % 4;
    if (key == SDL_SCANCODE_R)
        s_Requirement = (s_Requirement + 1) % 10;
    if (key == SDL_SCANCODE_N && PcQolVisited(s_Castle, s_X, s_Y)) {
        s_Editing = true;
        s_Note[0] = 0;
        SDL_StartTextInput(window);
    }
    if (key == SDL_SCANCODE_RETURN || key == SDL_SCANCODE_P) {
        const char* note = "";
        for (int i = 0; i < PC_MAP_PINS; i++) {
            PcMapPin* p = &g_PcQol.pins[i];
            if (p->used && p->castle == s_Castle && p->x == s_X && p->y == s_Y)
                note = p->note;
        }
        if (PcQolSetPin(s_Castle, s_X, s_Y, s_Kind, s_Requirement, note) >= 0)
            PcQolSave();
        else
            g_PcQolMessage =
                "Pins require an explored tile and an available pin slot.";
    }
    if (key == SDL_SCANCODE_DELETE) {
        for (int i = 0; i < PC_MAP_PINS; i++) {
            PcMapPin* p = &g_PcQol.pins[i];
            if (p->used && p->castle == s_Castle && p->x == s_X && p->y == s_Y)
                p->used = 0;
        }
        PcQolSave();
    }
}

static int InventoryChoice(int item) {
    if ((s_Slot < 2) != (item < NUM_HAND_ITEMS))
        return item;
    int equipped = g_Status.equipment[s_Slot] +
                   (s_Slot < 2 ? 0 : NUM_HAND_ITEMS);
    static const int empty[] = {
        ITEM_EMPTY_HAND, ITEM_EMPTY_HAND, ITEM_EMPTY_HEAD + NUM_HAND_ITEMS,
        ITEM_NO_ARMOR + NUM_HAND_ITEMS, ITEM_NO_CAPE + NUM_HAND_ITEMS,
        ITEM_NO_ACCESSORY + NUM_HAND_ITEMS, ITEM_NO_ACCESSORY + NUM_HAND_ITEMS};
    return item == equipped ? empty[s_Slot] : item;
}

void PcQolUiEvent(const SDL_Event* e, SDL_Window* window) {
    if (s_Editing) {
        if (e->type == SDL_EVENT_TEXT_INPUT &&
            strlen(s_Note) + strlen(e->text.text) < sizeof(s_Note))
            strcat(s_Note, e->text.text);
        if (e->type == SDL_EVENT_KEY_DOWN) {
            if (e->key.scancode == SDL_SCANCODE_BACKSPACE && s_Note[0])
                s_Note[strlen(s_Note) - 1] = 0;
            if (e->key.scancode == SDL_SCANCODE_RETURN ||
                e->key.scancode == SDL_SCANCODE_ESCAPE) {
                s_Editing = false;
                SDL_StopTextInput(window);
                if (e->key.scancode == SDL_SCANCODE_RETURN) {
                    PcQolSetPin(
                        s_Castle, s_X, s_Y, s_Kind, s_Requirement, s_Note);
                    PcQolSave();
                }
            }
        }
        return;
    }
    SDL_Scancode key = SDL_SCANCODE_UNKNOWN;
    if (e->type == SDL_EVENT_GAMEPAD_AXIS_MOTION && s_Page == 0 &&
        (e->gaxis.axis == SDL_GAMEPAD_AXIS_LEFT_TRIGGER ||
         e->gaxis.axis == SDL_GAMEPAD_AXIS_RIGHT_TRIGGER)) {
        static bool held[2];
        int side = e->gaxis.axis == SDL_GAMEPAD_AXIS_RIGHT_TRIGGER;
        bool down = e->gaxis.value > 16000;
        if (down && !held[side])
            key = side ? SDL_SCANCODE_EQUALS : SDL_SCANCODE_MINUS;
        held[side] = down;
    }
    if (e->type == SDL_EVENT_KEY_DOWN)
        key = e->key.scancode;
    if (e->type == SDL_EVENT_GAMEPAD_BUTTON_DOWN) {
        switch (e->gbutton.button) {
        case SDL_GAMEPAD_BUTTON_DPAD_UP:
            key = SDL_SCANCODE_UP;
            break;
        case SDL_GAMEPAD_BUTTON_DPAD_DOWN:
            key = SDL_SCANCODE_DOWN;
            break;
        case SDL_GAMEPAD_BUTTON_DPAD_LEFT:
            key = SDL_SCANCODE_LEFT;
            break;
        case SDL_GAMEPAD_BUTTON_DPAD_RIGHT:
            key = SDL_SCANCODE_RIGHT;
            break;
        case SDL_GAMEPAD_BUTTON_SOUTH:
            key = SDL_SCANCODE_RETURN;
            break;
        case SDL_GAMEPAD_BUTTON_START:
        case SDL_GAMEPAD_BUTTON_EAST:
            key = SDL_SCANCODE_ESCAPE;
            break;
        case SDL_GAMEPAD_BUTTON_RIGHT_SHOULDER:
            key = SDL_SCANCODE_TAB;
            break;
        case SDL_GAMEPAD_BUTTON_NORTH:
            key = SDL_SCANCODE_F;
            break;
        case SDL_GAMEPAD_BUTTON_WEST:
            key = SDL_SCANCODE_S;
            break;
        case SDL_GAMEPAD_BUTTON_LEFT_SHOULDER:
            key = SDL_SCANCODE_U;
            break;
        case SDL_GAMEPAD_BUTTON_RIGHT_STICK:
            key = SDL_SCANCODE_I;
            break;
        case SDL_GAMEPAD_BUTTON_LEFT_STICK:
            key = SDL_SCANCODE_V;
            break;
        case SDL_GAMEPAD_BUTTON_BACK:
            key = s_Page == 0   ? SDL_SCANCODE_C
                  : s_Page == 1 ? SDL_SCANCODE_B
                  : s_Page == 2 ? SDL_SCANCODE_L
                  : s_Page == 4 ? SDL_SCANCODE_R
                                : SDL_SCANCODE_UNKNOWN;
            break;
        }
    }
    if (s_Page == 1 && e->type == SDL_EVENT_GAMEPAD_AXIS_MOTION &&
        e->gaxis.axis == SDL_GAMEPAD_AXIS_RIGHT_TRIGGER) {
        bool down = e->gaxis.value > 16000;
        if (down && !s_PreviewTrigger)
            key = SDL_SCANCODE_A;
        s_PreviewTrigger = down;
    }
    if (key == SDL_SCANCODE_ESCAPE) {
        s_Close = true;
        return;
    }
    if (key == SDL_SCANCODE_TAB && !s_LoadMode) {
        s_Page = (s_Page + 1) % 7;
        s_Row = 0;
        return;
    }
    if (s_Page == 0) {
        MapKey(key, window);
        return;
    }
    if (key == SDL_SCANCODE_UP)
        s_Row = SDL_max(0, s_Row - 1);
    if (key == SDL_SCANCODE_DOWN)
        s_Row++;
    if (s_Page == 1) {
        if (key == SDL_SCANCODE_A)
            PcInventoryPreviewCycle();
        if (key == SDL_SCANCODE_F) {
            s_Filter = (s_Filter + 1) % 8;
            s_Row = 0;
        }
        if (key == SDL_SCANCODE_S)
            s_Sort = (s_Sort + 1) % 3;
        if (key == SDL_SCANCODE_B) {
            s_Favorites ^= 1;
            s_Row = 0;
        }
        if (key == SDL_SCANCODE_LEFT)
            s_Slot = (s_Slot + 6) % 7;
        if (key == SDL_SCANCODE_RIGHT)
            s_Slot = (s_Slot + 1) % 7;
        int items[NUM_HAND_ITEMS + NUM_BODY_ITEMS];
        int count = PcQolInventory(s_Filter, s_Sort, s_Favorites, items);
        if (!count) {
            s_Row = 0;
            return;
        }
        s_Row = SDL_min(s_Row, count - 1);
        int item = items[s_Row];
        if (key == SDL_SCANCODE_V) {
            g_PcQol.favorites[item] ^= 1;
            PcQolSave();
        }
        if (key == SDL_SCANCODE_I && item < NUM_HAND_ITEMS &&
            g_EquipDefs[item].unk13 == 55) {
            g_PcQol.quickItem = item;
            PcQolSave();
        }
        if (key == SDL_SCANCODE_U && item < NUM_HAND_ITEMS)
            s_Close = PcQolUseItem(item);
        if (key == SDL_SCANCODE_RETURN) {
            s_Close = PcQolEquipItem(InventoryChoice(item), s_Slot);
            if (!s_Close)
                g_PcQolMessage = "Cannot equip that item in this slot/state.";
        }
    } else if (s_Page == 2) {
        s_Row %= PC_LOADOUTS;
        if (key == SDL_SCANCODE_S) {
            memcpy(g_PcQol.loadouts[s_Row], g_Status.equipment,
                   sizeof(g_PcQol.loadouts[0]));
            g_PcQol.loadoutValid[s_Row] = 1;
            PcQolSave();
        }
        if (key == SDL_SCANCODE_RETURN && g_PcQol.loadoutValid[s_Row]) {
            s_Close = PcQolApplyGear(g_PcQol.loadouts[s_Row]);
            g_PcQolMessage =
                s_Close ? "Loadout equipped."
                        : "Loadout unavailable: items or player state changed.";
        }
        if (key == SDL_SCANCODE_L) {
            g_PcQol.loadout = g_PcQol.loadout == s_Row ? -1 : s_Row;
            PcQolSave();
        }
    } else if (s_Page == 3) {
        if (key == SDL_SCANCODE_P || key == SDL_SCANCODE_U)
            g_PcSpellPractice ^= 1;
        s_Row %= NUM_SPELLS;
        if (key == SDL_SCANCODE_S && (g_Status.spellsLearnt & (1 << s_Row))) {
            g_PcQol.quickSpell = s_Row;
            PcQolSave();
        }
        if (key == SDL_SCANCODE_RETURN) {
            s_Close = PcQolCast(s_Row);
            if (!s_Close)
                g_PcQolMessage = "Enable spell shortcuts; spell must be "
                                 "learned and casting available.";
        }
    } else if (s_Page == 4) {
        if (key == SDL_SCANCODE_S)
            s_Close = PcQolSuspend();
        if (key == SDL_SCANCODE_R)
            s_Close = PcQolResume();
        PcSaveEntry* entries = s_Saves;
        int count = s_SaveCount;
        s_Row = count ? SDL_min(s_Row, count - 1) : 0;
        if (count && (key == SDL_SCANCODE_F || key == SDL_SCANCODE_DELETE)) {
            s_ArchiveConfirm = true;
            g_PcQolMessage =
                "Archive this save? Enter confirms; navigation cancels.";
        } else if (key == SDL_SCANCODE_RETURN && count) {
            if (s_ArchiveConfirm) {
                g_PcQolMessage =
                    PcSaveArchive(&entries[s_Row])
                        ? "Save archived; its file and profile are recoverable."
                        : "Archive failed. The current adventure cannot be "
                          "archived.";
            } else if (s_LoadMode) {
                if (PcSaveLoad(&entries[s_Row])) {
                    s_SaveAction = 1;
                    s_Close = true;
                } else
                    g_PcQolMessage =
                        "Could not load save; original file is unchanged.";
                return;
            } else
                g_PcQolMessage =
                    PcQolRestore(&entries[s_Row])
                        ? "Save copied to a new PC slot, with its adventure "
                          "profile."
                        : "Copy failed; original files are unchanged.";
            s_ArchiveConfirm = false;
            RefreshSaves();
            SDL_DestroySurface(s_SavePreview);
            s_SavePreview = NULL;
            s_PreviewRow = -1;
        } else if (count && (key == SDL_SCANCODE_N || key == SDL_SCANCODE_I) &&
                   g_GameState == Game_MainMenu) {
            s_SaveAction = 2;
            s_Close = true;
        } else if (key != SDL_SCANCODE_UNKNOWN)
            s_ArchiveConfirm = false;
    } else if (s_Page == 6) {
        s_Row %= 9;
        int* options[] = {
            &g_PcSettings.quickItems,
            &g_PcSettings.spellShortcuts,
            &g_PcSettings.protectSubweapon,
            &g_PcSettings.warpChooser,
            &g_PcSettings.skipSeenDialogue,
            &g_PcSettings.statusHud,
            &g_PcSettings.hudScale,
            &g_PcSettings.subtitleScale,
            NULL};
        if (s_Row == 8) {
            if (key == SDL_SCANCODE_RETURN) {
                int keepWide = g_PcSettings.widescreen;
                g_PcSettings.quickItems = g_PcSettings.spellShortcuts =
                    g_PcSettings.protectSubweapon = 0;
                g_PcSettings.warpChooser = g_PcSettings.skipSeenDialogue =
                    g_PcSettings.statusHud = 0;
                g_PcSettings.hudScale = 100;
                g_PcSettings.subtitleScale = 0;
                g_PcQol.loadout = -1;
                PcQolSave();
                g_PcSettings.widescreen = keepWide;
            }
        } else if (key == SDL_SCANCODE_LEFT || key == SDL_SCANCODE_RIGHT ||
                   key == SDL_SCANCODE_RETURN) {
            if (s_Row == 6)
                *options[s_Row] =
                    100 + (((*options[s_Row] - 100) / 25 +
                            (key == SDL_SCANCODE_LEFT ? 2 : 1)) %
                           3) *
                              25;
            else if (s_Row == 7)
                *options[s_Row] =
                    (*options[s_Row] + (key == SDL_SCANCODE_LEFT ? 3 : 1)) % 4;
            else
                *options[s_Row] ^= 1;
        }
        if (!PcSettingsSave(&g_PcSettings, g_PcSettingsPath))
            g_PcQolMessage = "Could not save options.";
    }
}

static void DrawMap(SDL_Renderer* r) {
    static const char* mapFilters[] = {
        "All", "Pins", "Save rooms", "Warp rooms", "Ready obstacles"};
    Text(r, 12, 39, "%s castle | %s | cursor %02d,%02d",
         s_Castle ? "Inverted" : "Normal", mapFilters[s_MapFilter], s_X, s_Y);
    SDL_Rect clip = {12, 57, 568, 300};
    SDL_SetRenderClipRect(r, &clip);
    int ox = 296 - s_X * s_Zoom, oy = 207 - s_Y * s_Zoom;
    for (int y = 0; y < 64; y++)
        for (int x = 0; x < 64; x++) {
            if (!PcQolVisited(s_Castle, x, y))
                continue;
            SDL_SetRenderDrawColor(r, 45, 75, 115, 255);
            SDL_FRect rect = {ox + x * s_Zoom, oy + y * s_Zoom, s_Zoom - 1,
                              s_Zoom - 1};
            SDL_RenderFillRect(r, &rect);
            if ((!s_MapFilter || s_MapFilter == 2) &&
                (g_PcQol.saveRooms[s_Castle][y * 8 + x / 8] & (1 << (x & 7)))) {
                SDL_SetRenderDrawColor(r, 90, 240, 170, 255);
                Text(r, ox + x * s_Zoom, oy + y * s_Zoom, "S");
            }
        }
    static const int warps[2][5][2] = {
        {{15, 38}, {35, 44}, {59, 17}, {40, 12}, {37, 21}},
        {{48, 25}, {28, 19}, {4, 46}, {23, 51}, {26, 42}}};
    int unlocks = g_CastleFlags[s_Castle ? RWRP_UNLOCKS : WRP_UNLOCKS];
    if (!s_MapFilter || s_MapFilter == 3)
        for (int i = 0; i < 5; i++) {
            int x = warps[s_Castle][i][0], y = warps[s_Castle][i][1];
            if (!(unlocks & (1 << i)) || !PcQolVisited(s_Castle, x, y))
                continue;
            SDL_SetRenderDrawColor(r, 230, 160, 240, 255);
            Text(r, ox + x * s_Zoom, oy + y * s_Zoom, "W");
        }
    for (int i = 0; i < PC_MAP_PINS; i++) {
        PcMapPin* p = &g_PcQol.pins[i];
        bool ready = PcQolPinReady(p);
        if (!p->used || p->castle != s_Castle ||
            !PcQolVisited(p->castle, p->x, p->y) || s_MapFilter == 2 ||
            s_MapFilter == 3 || (s_MapFilter == 4 && !ready))
            continue;
        SDL_SetRenderDrawColor(r, ready ? 80 : 255, ready ? 255 : 190, 80, 255);
        Text(r, ox + p->x * s_Zoom, oy + p->y * s_Zoom, "%c", "!?*+"[p->kind]);
    }
    SDL_SetRenderDrawColor(r, 255, 255, 255, 255);
    SDL_FRect cursor = {296, 207, s_Zoom, s_Zoom};
    SDL_RenderRect(r, &cursor);
    int castle, x, y;
    PcQolMapPosition(&castle, &x, &y);
    if (castle == s_Castle)
        Text(r, ox + x * s_Zoom, oy + y * s_Zoom, "@");
    SDL_SetRenderClipRect(r, NULL);
    SDL_SetRenderDrawColor(r, 230, 235, 245, 255);
    Text(
        r, 12, 365, "Arrows pan | +/- zoom | C castle | F filter | Del remove");
    Text(r, 12, 377, "K icon %c | R requirement: %s", "!?*+"[s_Kind],
         g_PcObstacleNames[s_Requirement]);
    Text(r, 12, 389, "%s",
         s_Editing
             ? "Type note; Enter saves; Escape cancels"
             : "Enter places pin | N writes a note (explored tiles only)");
    if (s_Editing)
        Text(r, 12, 401, "%s_", s_Note);
    else
        for (int i = 0; i < PC_MAP_PINS; i++) {
            PcMapPin* p = &g_PcQol.pins[i];
            if (p->used && p->castle == s_Castle && p->x == s_X && p->y == s_Y)
                Text(r, 12, 401, "%.45s%s", p->note,
                     PcQolPinReady(p) ? " [REVISIT]" : "");
        }
    if (g_PcSettings.warpChooser &&
        (g_StageId == STAGE_WRP || g_StageId == STAGE_RWRP))
        Text(r, 12, 416, "W destination: %s | Space selects; Up activates",
             g_PcWarpNames[s_Warp]);
}

static void InventoryPanel(SDL_Renderer* r, int x, int y, int w, int h) {
    SDL_FRect rect = {x, y, w, h};
    PcMenuPanel(r, x, y, w, h, 0.92f);
    SDL_SetRenderDrawColor(r, 109, 119, 151, 255);
    SDL_RenderRect(r, &rect);
}

static void DrawEquipment(SDL_Renderer* r) {
    InventoryPanel(r, 12, 118, 218, 300);
    SDL_SetRenderDrawColor(r, 54, 64, 93, 255);
    SDL_FRect body = {107, 163, 27, 66};
    SDL_RenderFillRect(r, &body);
    SDL_RenderLine(r, 108, 169, 60, 202);
    SDL_RenderLine(r, 133, 169, 180, 202);
    SDL_RenderLine(r, 113, 226, 95, 260);
    SDL_RenderLine(r, 128, 226, 146, 260);
    static const int positions[7][2] = {
        {30, 174}, {173, 174}, {102, 125}, {102, 174},
        {173, 125}, {57, 223},  {147, 223}};
    static const char* labels[] = {
        "L hand", "R hand", "Head", "Armor", "Cape", "Acc. 1", "Acc. 2"};
    for (int slot = 0; slot < 7; slot++) {
        int x = positions[slot][0], y = positions[slot][1];
        SDL_FRect rect = {x - 3, y - 3, 38, 38};
        SDL_SetRenderDrawColor(r, 14, 19, 43, 255);
        SDL_RenderFillRect(r, &rect);
        SDL_SetRenderDrawColor(
            r, slot == s_Slot ? 245 : 108, slot == s_Slot ? 207 : 119,
            slot == s_Slot ? 122 : 151, 255);
        SDL_RenderRect(r, &rect);
        Text(r, x - (strlen(labels[slot]) * 8 - 32) / 2, y + 38, "%s",
             labels[slot]);
        int item = g_Status.equipment[slot];
        PcInventoryIcon(r, item + (slot < 2 ? 0 : NUM_HAND_ITEMS), x, y, 2);
    }
    char name[64];
    int item = g_Status.equipment[s_Slot] + (s_Slot < 2 ? 0 : NUM_HAND_ITEMS);
    PcQolItemText(item, false, name, sizeof(name));
    SDL_SetRenderDrawColor(r, 245, 207, 122, 255);
    Text(r, 22, 276, "%.25s", name);
    SDL_SetRenderDrawColor(r, 64, 73, 103, 255);
    SDL_RenderLine(r, 22, 290, 220, 290);
    SDL_RenderLine(r, 35, 393, 208, 393);
    SDL_Rect clip = {20, 296, 203, 97};
    SDL_SetRenderClipRect(r, &clip);
    PcInventoryPreviewDraw(r, 95, 345);
    SDL_SetRenderClipRect(r, NULL);
    SDL_SetRenderDrawColor(r, 230, 235, 245, 255);
    Text(r, 23, 402, "A/RT: %s", PcInventoryPreviewName());
}

static void InventorySummary(SDL_Renderer* r) {
    InventoryPanel(r, 12, 72, 576, 40);
    SDL_SetRenderDrawColor(r, 230, 235, 245, 255);
    const char* status = "Normal";
    if (g_Player.status & PLAYER_STATUS_CURSE)
        status = "Curse";
    if (g_Player.status & PLAYER_STATUS_POISON)
        status = "Poison";
    if (g_Player.status & PLAYER_STATUS_STONE)
        status = "Stone";
    if (IsAlucart())
        status = "Alucart";
    Text(r, 20, 77, "Lv %d   HP %d/%d   MP %d/%d   Hearts %d/%d",
         g_Status.level, g_Status.hp, g_Status.hpMax, g_Status.mp,
         g_Status.mpMax, g_Status.hearts, g_Status.heartsMax);
    Text(r, 20, 89, "EXP %d   Next %d   Gold %d   %s", g_Status.exp,
         g_Status.level < 99 ? g_ExpNext[g_Status.level + 1] - g_Status.exp : 0,
         g_Status.gold, status);
    Text(r, 20, 101, "Rooms %d   Kills %d   Time %02d:%02d:%02d", g_RoomCount,
         g_Status.killCount, g_Status.timerHours, g_Status.timerMinutes,
         g_Status.timerSeconds);
}

static void InventoryStat(SDL_Renderer* r, int x, int y, const char* label,
                          int current, int next, bool comparing) {
    SDL_SetRenderDrawColor(r, 230, 235, 245, 255);
    char line[64];
    snprintf(line, sizeof(line), "%s %d", label, current);
    Text(r, x, y, "%s", line);
    if (!comparing)
        return;
    SDL_SetRenderDrawColor(r, next == current ? 230 : next < current ? 255 : 130,
                          next == current ? 235 : next < current ? 130 : 245,
                          next == current ? 245 : 160, 255);
    Text(r, x + strlen(line) * 8, y, " > %d", next);
}

static void DrawInventory(SDL_Renderer* r) {
    PlayerStatus saved = g_Status;
    u32 previousCombo = D_8013AEE4;
    // Recalculate like the original menu, preserving the live cached values.
    make_all();
    PlayerStatus original = g_Status, after = original;
    g_Status = saved;
    D_8013AEE4 = previousCombo;
    int items[NUM_HAND_ITEMS + NUM_BODY_ITEMS];
    int count = PcQolInventory(s_Filter, s_Sort, s_Favorites, items);
    s_Row = count ? SDL_min(s_Row, count - 1) : 0;
    SDL_SetRenderDrawColor(r, 245, 207, 122, 255);
    Text(r, 20, 43, "EQUIPMENT");
    Text(r, 248, 43, "INVENTORY %d/%d", count ? s_Row + 1 : 0, count);
    SDL_SetRenderDrawColor(r, 230, 235, 245, 255);
    Text(r, 20, 58, "Left/Right: slot");
    Text(r, 248, 58, "F:%s S:%s B:%s", filters[s_Filter],
         (const char*[]){"Name", "Count", "Stats"}[s_Sort],
         s_Favorites ? "Fav" : "All");
    InventorySummary(r);
    DrawEquipment(r);
    InventoryPanel(r, 240, 118, 348, 300);
    int start = SDL_max(0, s_Row - 3);
    for (int row = start, y = 129; row < count && row < start + 6;
         row++, y += 18) {
        char name[60];
        PcQolItemText(items[row], false, name, sizeof(name));
        int item = items[row];
        if (row == s_Row) {
            SDL_FRect selected = {244, y - 2, 340, 18};
            SDL_SetRenderDrawColor(r, 57, 55, 86, 255);
            SDL_RenderFillRect(r, &selected);
        }
        PcInventoryIcon(r, item, 249, y - 1, 1);
        SDL_SetRenderDrawColor(
            r, row == s_Row ? 245 : 216, row == s_Row ? 207 : 222,
            row == s_Row ? 122 : 239, 255);
        Text(r, 271, y + 2, "%c%.29s", g_PcQol.favorites[item] ? '*' : ' ',
             name);
        Text(r, 550, y + 2, "%3d",
             PcQolOwned(item >= NUM_HAND_ITEMS,
                        item >= NUM_HAND_ITEMS ? item - NUM_HAND_ITEMS : item));
    }
    SDL_SetRenderDrawColor(r, 230, 235, 245, 255);
    int item = count ? items[s_Row] : -1;
    int choice = count ? InventoryChoice(item) : -1;
    bool removing = choice != item;
    if (!count)
        Text(r, 250, 129, "No items match these filters.");
    if (count) {
        char desc[256];
        PcQolItemText(item, true, desc, sizeof(desc));
        SDL_Rect clip = {248, 239, 332, 34};
        SDL_SetRenderClipRect(r, &clip);
        Wrap(r, 250, 240, desc, 40);
        SDL_SetRenderClipRect(r, NULL);
    }
    bool comparing = false;
    u32 equipment[7];
    memcpy(equipment, original.equipment, sizeof(equipment));
    if (count && (s_Slot < 2) == (choice < NUM_HAND_ITEMS)) {
        int id = choice < NUM_HAND_ITEMS ? choice : choice - NUM_HAND_ITEMS;
        equipment[s_Slot] = id;
        if (s_Slot < 2) {
            if (g_EquipDefs[original.equipment[s_Slot]].itemCategory ==
                ITEM_TWOHAND)
                equipment[1 - s_Slot] = ITEM_EMPTY_HAND;
            if (g_EquipDefs[id].itemCategory == ITEM_TWOHAND)
                equipment[1 - s_Slot] = id;
        }
        if (PcQolEquip(equipment, false)) {
            memcpy(g_Status.equipment, equipment, sizeof(equipment));
            make_all();
            after = g_Status;
            comparing = true;
        }
    }
    g_Status = saved;
    D_8013AEE4 = previousCombo;
    SDL_SetRenderDrawColor(r, 245, 207, 122, 255);
    if (comparing)
        Text(r, 250, 279, "CURRENT > %s (%s)", removing ? "REMOVE" : "EQUIP",
             slots[s_Slot]);
    else
        Text(r, 250, 279, "CURRENT STATS (%s)", slots[s_Slot]);
    InventoryStat(r, 250, 294, "ATK L", original.attackHands[0],
                  after.attackHands[0], comparing);
    InventoryStat(r, 422, 294, "R", original.attackHands[1],
                  after.attackHands[1], comparing);
    InventoryStat(r, 250, 306, "DEF", original.defenseEquip,
                  after.defenseEquip, comparing);
    const char* attributes[] = {"STR", "CON", "INT", "LCK"};
    for (int i = 0; i < 4; i++) {
        InventoryStat(r, 250, 318 + i * 12, attributes[i],
                      original.statsBase[i] + original.statsEquip[i],
                      after.statsBase[i] + after.statsEquip[i], comparing);
        SDL_SetRenderDrawColor(r, 180, 190, 215, 255);
        Text(r, 450, 318 + i * 12, "(%d%+d)", original.statsBase[i],
             original.statsEquip[i]);
    }
    const char* labels[] = {"Weak", "Resist", "Immune", "Absorb"};
    unsigned beforeMasks[] = {original.elementsWeakTo, original.elementsResist,
                              original.elementsImmune, original.elementsAbsorb};
    unsigned afterMasks[] = {after.elementsWeakTo, after.elementsResist,
                             after.elementsImmune, after.elementsAbsorb};
    SDL_SetRenderDrawColor(r, 230, 235, 245, 255);
    for (int i = 0; i < 4; i++) {
        char beforeNames[96], afterNames[96], line[224];
        ElementNames(beforeMasks[i], beforeNames, sizeof(beforeNames));
        ElementNames(afterMasks[i], afterNames, sizeof(afterNames));
        snprintf(line, sizeof(line), "%s: %s%s%s", labels[i], beforeNames,
                 comparing && beforeMasks[i] != afterMasks[i] ? " > " : "",
                 comparing && beforeMasks[i] != afterMasks[i] ? afterNames : "");
        float scale = SDL_min(1.0f, 328.0f / (strlen(line) * 8));
        SDL_SetRenderScale(r, 2 * scale, 2 * scale);
        PcMenuText(r, 250 / scale, (369 + i * 11) / scale, line);
        SDL_SetRenderScale(r, 2, 2);
    }
    Text(r, 12, 421,
         "Enter equip/remove | V fav | I quick | U use | A/RT animate");
}

void PcQolUiDraw(SDL_Renderer* r) {
    SDL_SetRenderScale(r, 2, 2);
    PcMenuBackground(r);
    SDL_SetRenderDrawColor(r, 230, 235, 245, 255);
    Text(r, 12, 10, "ADVENTURE - F5/Escape returns | Tab/RB changes page");
    Text(r, 12, 24, "%s (%d/7)", pages[s_Page], s_Page + 1);
    if (s_Page == 0)
        DrawMap(r);
    if (s_Page == 1)
        DrawInventory(r);
    if (s_Page == 2) {
        Text(r, 12, 48,
             "S stores current gear | Enter equips | L toggles F10 shortcut");
        for (int i = 0; i < PC_LOADOUTS; i++)
            Text(r, 12, 75 + i * 18, "%c Loadout %d: %s%s",
                 i == s_Row ? '>' : ' ', i + 1,
                 g_PcQol.loadoutValid[i] ? "Saved" : "Empty",
                 g_PcQol.loadout == i ? " [F10]" : "");
        if (g_PcQol.loadoutValid[s_Row % PC_LOADOUTS])
            for (int slot = 0; slot < 7; slot++) {
                int id = g_PcQol.loadouts[s_Row % PC_LOADOUTS][slot];
                char name[64];
                if (id < 0 ||
                    id >= (slot < 2 ? NUM_HAND_ITEMS : NUM_BODY_ITEMS))
                    continue;
                PcQolItemText(id + (slot < 2 ? 0 : NUM_HAND_ITEMS), false, name,
                              sizeof(name));
                Text(r, 12, 150 + slot * 15, "%s: %s", slots[slot], name);
            }
    }
    if (s_Page == 3) {
        Text(r, 12, 48, "Enter casts | S assigns F7 | P practice HUD: %s",
             g_PcSpellPractice ? "On" : "Off");
        s_Row %= NUM_SPELLS;
        for (int i = 0; i < 8; i++)
            Text(r, 12, 72 + i * 15, "%c %-21s %s %s", s_Row == i ? '>' : ' ',
                 g_Status.spellsLearnt & (1 << i) ? spellNames[i]
                                                  : "Undiscovered spell",
                 g_Status.spellsLearnt & (1 << i) ? "Known" : "",
                 g_PcQol.quickSpell == i ? "[F7]" : "");
        if (g_Status.spellsLearnt & (1 << s_Row)) {
            Text(r, 12, 215, "%s - %d MP", spellNames[s_Row],
                 g_SpellDefs[s_Row].mpUsage);
            Wrap(r, 12, 238, combos[s_Row], 68);
            Text(r, 12, 295,
                 "Practice these inputs in gameplay. Forward follows facing.");
            Text(r, 12, 310,
                 "Spells retain their MP, form, familiar and animation "
                 "restrictions.");
        }
    }
    if (s_Page == 4) {
        Text(r, 12, 48,
             s_LoadMode
                 ? "Enter/A loads | Escape/B returns"
                 : "Enter/A copies | F/Y archives | N/R3 renames (title)");
        Text(r, 12, 63,
             "S/X suspend & quit | R resume | Normal saves use save rooms.");
        PcSaveEntry* entries = s_Saves;
        int count = s_SaveCount;
        s_Row = count ? SDL_min(s_Row, count - 1) : 0;
        for (int i = SDL_max(0, s_Row - 5), y = 90; i < count && y < 270;
             i++, y += 28) {
            SaveInfo* info = &entries[i].info;
            Text(r, 12, y, "%c %.10s | %s | %.22s | Lv%d",
                 i == s_Row ? '>' : ' ', info->name,
                 info->character == PLAYER_RICHTER ? "Richter" : "Alucard",
                 AreaName(info->stage), info->level);
            Text(r, 28, y + 11, "%02d:%02d:%02d | %.1f%% | %.36s",
                 info->playHours, info->playMinutes, info->playSeconds,
                 info->nRoomsExplored * 100.0 / 942.0, entries[i].origin);
        }
        if (count) {
            PcSaveEntry* entry = &entries[s_Row];
            if (s_PreviewRow != s_Row) {
                SDL_DestroySurface(s_SavePreview);
                s_SavePreview = PcQolLoadPreview(entry);
                s_PreviewRow = s_Row;
            }
            if (s_SavePreview) {
                SDL_Texture* preview =
                    SDL_CreateTextureFromSurface(r, s_SavePreview);
                if (preview) {
                    SDL_SetTextureScaleMode(preview, SDL_SCALEMODE_NEAREST);
                    SDL_FRect area = {12, 280, 192, 108};
                    SDL_RenderTexture(r, preview, NULL, &area);
                    SDL_DestroyTexture(preview);
                }
            }
            for (int y = 0; y < 16; y++)
                for (int x = 0; x < 16; x++) {
                    int index =
                        (entry->icon[y * 8 + x / 2] >> ((x & 1) * 4)) & 15;
                    int color = entry->palette[index * 2] |
                                entry->palette[index * 2 + 1] << 8;
                    SDL_SetRenderDrawColor(
                        r, (color & 31) * 8, ((color >> 5) & 31) * 8,
                        ((color >> 10) & 31) * 8, 255);
                    SDL_FRect pixel = {520 + x * 3, 360 + y * 3, 3, 3};
                    SDL_RenderFillRect(r, &pixel);
                }
            SDL_SetRenderDrawColor(r, 230, 235, 245, 255);
            Text(
                r, 12, 401, "%s | Original save icon at right.",
                s_SavePreview ? "Gameplay preview" : "No gameplay preview yet");
        }
        if (!count)
            Text(r, 12, 100,
                 "No saves found. Backups are made before overwriting a slot.");
    }
    if (s_Page == 5) {
        Text(r, 12, 48,
             "Dialogue is paused with the game. F1/F5 pauses picture and "
             "voice.");
        for (int i = 0; i < 24; i++)
            Text(r, 12, 72 + i * 12, "%.70s", PcQolDialogueLine(i));
    }
    if (s_Page == 6) {
        const char* names[] = {
            "Consumable shortcuts (F6)",
            "Learned spell shortcuts (F7)",
            "Hold Down to replace subweapon",
            "Named warp destinations",
            "Skip watched dialogue",
            "Numerical HP/MP and status HUD",
            "HUD scale",
            "Extra subtitle size",
            "Reset QoL gameplay options"};
        int values[] = {
            g_PcSettings.quickItems,       g_PcSettings.spellShortcuts,
            g_PcSettings.protectSubweapon, g_PcSettings.warpChooser,
            g_PcSettings.skipSeenDialogue, g_PcSettings.statusHud,
            g_PcSettings.hudScale,         g_PcSettings.subtitleScale};
        for (int i = 0; i < 9; i++) {
            Text(r, 12, 65 + i * 23, "%c %-36s", s_Row == i ? '>' : ' ',
                 names[i]);
            if (i < 6)
                Text(r, 345, 65 + i * 23, "%s", values[i] ? "On" : "Off");
            if (i == 6)
                Text(r, 345, 65 + i * 23, "%d%%", values[i]);
            if (i == 7)
                Text(r, 345, 65 + i * 23, "%s",
                     (const char*[]){"Original", "Small", "Medium",
                                     "Large"}[SDL_clamp(values[i], 0, 3)]);
        }
        Text(r, 12, 295,
             "Original gameplay is the default. Each option is independent.");
        Text(
            r, 12, 310,
            "Warp destinations are selected from the map page in a warp room.");
    }
    SDL_SetRenderDrawColor(r, 180, 205, 230, 255);
    Text(r, 12, 432, "%.71s", g_PcQolMessage);
    SDL_RenderPresent(r);
}
