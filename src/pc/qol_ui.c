// SPDX-License-Identifier: AGPL-3.0-or-later
#include "qol.h"
#include "../dra/dra.h"
#include <stdarg.h>
#include <string.h>
extern u32 D_8013AEE4;

static int s_Page, s_Row, s_Filter, s_Sort, s_Slot, s_Castle, s_X, s_Y;
static int s_Zoom = 6, s_MapFilter, s_Kind, s_Requirement;
static int s_Warp;
static bool s_Favorites, s_Close, s_Editing;
static char s_Note[48];
static PcSaveEntry s_Saves[128];
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
    SDL_RenderDebugText(r, x, y, text);
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
        SDL_RenderDebugText(r, x, y, line);
        y += 11;
        text += n;
        while (*text == ' ')
            text++;
    }
}
void PcQolUiOpen(void) {
    s_Close = s_Editing = false;
    s_Note[0] = 0;
    SDL_DestroySurface(s_SavePreview);
    s_SavePreview = NULL;
    s_PreviewRow = -1;
    PcQolMapPosition(&s_Castle, &s_X, &s_Y);
    s_SaveCount = PcQolSaveList(s_Saves, 128);
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
        }
    }
    if (key == SDL_SCANCODE_ESCAPE) {
        s_Close = true;
        return;
    }
    if (key == SDL_SCANCODE_TAB) {
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
            s_Close = PcQolEquipItem(item, s_Slot);
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
        if (key == SDL_SCANCODE_RETURN && count) {
            g_PcQolMessage =
                PcQolRestore(&entries[s_Row])
                    ? "Backup copied to an unused slot on memory card 2."
                    : "Backup restore failed; original slots unchanged.";
            s_SaveCount = PcQolSaveList(s_Saves, 128);
            SDL_DestroySurface(s_SavePreview);
            s_SavePreview = NULL;
            s_PreviewRow = -1;
        }
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

static void DrawInventory(SDL_Renderer* r) {
    int items[NUM_HAND_ITEMS + NUM_BODY_ITEMS];
    int count = PcQolInventory(s_Filter, s_Sort, s_Favorites, items);
    s_Row = count ? SDL_min(s_Row, count - 1) : 0;
    Text(r, 12, 39, "F filter: %s | S sort: %s | B favorites: %s",
         filters[s_Filter],
         (const char*[]){"Name", "Quantity", "Stats"}[s_Sort],
         s_Favorites ? "On" : "Off");
    Text(r, 12, 52,
         "Left/Right slot: %s | Enter equips | V favorite | I quick item",
         slots[s_Slot]);
    for (int row = SDL_max(0, s_Row - 8), y = 73; row < count && y < 285;
         row++, y += 12) {
        char name[60];
        PcQolItemText(items[row], false, name, sizeof(name));
        int item = items[row];
        Text(r, 12, y, "%c %c %-30.30s x%d", row == s_Row ? '>' : ' ',
             g_PcQol.favorites[item] ? '*' : ' ', name,
             PcQolOwned(item >= NUM_HAND_ITEMS,
                        item >= NUM_HAND_ITEMS ? item - NUM_HAND_ITEMS : item));
    }
    if (!count) {
        Text(r, 12, 85, "No owned items match these filters.");
        return;
    }
    int item = items[s_Row];
    char desc[256];
    PcQolItemText(item, true, desc, sizeof(desc));
    Wrap(r, 12, 294, desc, 69);
    PlayerStatus original = g_Status;
    u32 previousCombo = D_8013AEE4;
    int id = item < NUM_HAND_ITEMS ? item : item - NUM_HAND_ITEMS;
    bool compatible = (s_Slot < 2) == (item < NUM_HAND_ITEMS);
    u32 equipment[7];
    memcpy(equipment, g_Status.equipment, sizeof(equipment));
    equipment[s_Slot] = id;
    if (s_Slot < 2 &&
        g_EquipDefs[original.equipment[s_Slot]].itemCategory == ITEM_TWOHAND)
        equipment[1 - s_Slot] = ITEM_EMPTY_HAND;
    if (s_Slot < 2 && item < NUM_HAND_ITEMS &&
        g_EquipDefs[id].itemCategory == ITEM_TWOHAND)
        equipment[1 - s_Slot] = id;
    if (compatible && PcQolEquip(equipment, false)) {
        memcpy(g_Status.equipment, equipment, sizeof(equipment));
        make_all();
        Text(r, 12, 350, "ATK %d/%d -> %d/%d | DEF %d -> %d",
             original.attackHands[0], original.attackHands[1],
             g_Status.attackHands[0], g_Status.attackHands[1],
             original.defenseEquip, g_Status.defenseEquip);
        Text(r, 12, 364, "STR %+d CON %+d INT %+d LCK %+d",
             g_Status.statsTotal[0] - original.statsTotal[0],
             g_Status.statsTotal[1] - original.statsTotal[1],
             g_Status.statsTotal[2] - original.statsTotal[2],
             g_Status.statsTotal[3] - original.statsTotal[3]);
        const char* labels[] = {"Weak", "Resist", "Immune", "Absorb"};
        unsigned masks[] = {g_Status.elementsWeakTo, g_Status.elementsResist,
                            g_Status.elementsImmune, g_Status.elementsAbsorb};
        for (int i = 0; i < 4; i++) {
            char names[80];
            ElementNames(masks[i], names, sizeof(names));
            Text(r, 12, 378 + i * 12, "%s: %s", labels[i], names);
        }
    } else
        Text(r, 12, 350,
             "Select a compatible slot; equipment changes need an idle "
             "Alucard.");
    g_Status = original;
    D_8013AEE4 = previousCombo;
}

void PcQolUiDraw(SDL_Renderer* r) {
    SDL_SetRenderScale(r, 2, 2);
    SDL_SetRenderDrawColor(r, 18, 20, 28, 255);
    SDL_RenderClear(r);
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
             "S suspend & quit | R resume | Enter copies save to free card-2 "
             "slot");
        Text(r, 12, 63,
             "Suspend requires a quiet idle room; enemies reset on resume.");
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
            Text(r, 28, y + 11, "%02d:%02d:%02d | %.1f%% | %s", info->playHours,
                 info->playMinutes, info->playSeconds,
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
