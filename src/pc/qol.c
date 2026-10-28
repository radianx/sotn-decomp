// SPDX-License-Identifier: AGPL-3.0-or-later
#include "qol.h"
#include "pc.h"
#include "../dra/dra.h"
#include "../dra/dra_bss.h"
#include "../dra/menu.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

extern int CastSpell(SpellIds spellId);
extern void PerformDarkMetamorphosis(void), PerformSummonSpirit(void);
extern void PerformHellfire(void), PerformTetraSpirit(void);
extern void PerformSoulSteal(void), PerformSwordBrothers(void);
extern s32 g_PrevEquippedWeapons[2];

PcQolData g_PcQol = {.quickItem = ITEM_POTION, .quickSpell = -1, .loadout = -1};
const char* g_PcQolMessage = "Changes are saved with this adventure profile.";
const char* g_PcWarpNames[5] = {"Entrance", "Abandoned Mine", "Outer Wall",
                                "Castle Keep", "Olrox's Quarters"};
const char* g_PcObstacleNames[10] = {
    "No requirement", "Bat",           "Mist",          "Wolf",
    "Double jump",    "Gravity Boots", "Jewel of Open", "Echo of Bat",
    "Holy Symbol",    "Spike Breaker"};
static const int requirements[9] = {
    RELIC_SOUL_OF_BAT, RELIC_FORM_OF_MIST,  RELIC_SOUL_OF_WOLF,
    RELIC_LEAP_STONE,  RELIC_GRAVITY_BOOTS, RELIC_JEWEL_OF_OPEN,
    RELIC_ECHO_OF_BAT, RELIC_HOLY_SYMBOL,   -1};
static char s_Profile[1024];
static unsigned s_ProfileId;
static int s_QuickItem = -1, s_QuickSpell = -1;
static int s_WarpCurrent = -1, s_WarpDestination = -1, s_WarpStage;
static char s_Dialogue[24][128];
static int s_Line, s_Column;
static bool s_SkipSeen;
bool g_PcSpellPractice;
static char s_Inputs[49];
const char* PcQolInputHistory(void) { return s_Inputs; }

static unsigned Hash(const void* data, size_t size) {
    const u8* bytes = data;
    unsigned hash = 2166136261u;
    while (size--)
        hash = (hash ^ *bytes++) * 16777619u;
    return hash;
}

bool PcQolWrite(const char* path, const void* data, size_t size) {
    char temporary[1200];
    if (snprintf(temporary, sizeof(temporary), "%s.tmp", path) >=
        sizeof(temporary))
        return false;
    FILE* file = fopen(temporary, "wb");
    if (!file)
        return false;
    u32 header[3] = {0x314C4F51, size, Hash(data, size)};
    bool ok = fwrite(header, sizeof(header), 1, file) == 1 &&
              fwrite(data, size, 1, file) == 1;
    if (fclose(file))
        ok = false;
    if (ok)
        ok = SDL_RenamePath(temporary, path);
    if (!ok)
        remove(temporary);
    return ok;
}

bool PcQolRead(const char* path, void* data, size_t size) {
    FILE* file = fopen(path, "rb");
    if (!file)
        return false;
    void* copy = malloc(size);
    u32 header[3];
    bool ok = copy && fread(header, sizeof(header), 1, file) == 1 &&
              header[0] == 0x314C4F51 && header[1] == size &&
              fread(copy, size, 1, file) == 1 && fgetc(file) == EOF &&
              !ferror(file) && header[2] == Hash(copy, size);
    if (ok)
        memcpy(data, copy, size);
    free(copy);
    fclose(file);
    return ok;
}

bool PcQolSave(void) {
    if (!s_Profile[0])
        PcQolSelectSave(NULL, false);
    bool ok = PcQolWrite(s_Profile, &g_PcQol, sizeof(g_PcQol));
    g_PcQolMessage =
        ok ? "Adventure profile saved." : "Could not save adventure profile.";
    return ok;
}

void PcQolNewGame(void) {
    if (s_Profile[0])
        PcQolSave();
    g_PcQol =
        (PcQolData){.quickItem = ITEM_POTION, .quickSpell = -1, .loadout = -1};
    s_Profile[0] = 0;
    s_ProfileId = 0;
    s_QuickItem = s_QuickSpell = s_WarpDestination = -1;
    s_SkipSeen = false;
    memset(s_Dialogue, 0, sizeof(s_Dialogue));
    s_Line = s_Column = 0;
}

unsigned PcQolProfileId(void) {
    if (!s_Profile[0])
        PcQolSelectSave(NULL, false);
    return s_ProfileId;
}

bool PcQolUseProfile(unsigned id) {
    char path[1024];
    if (snprintf(path, sizeof(path), "%s.%08x.qol", g_PcSettingsPath, id) >=
        sizeof(path))
        return false;
    strcpy(s_Profile, path);
    s_ProfileId = id;
    return true;
}

void PcQolValidate(PcQolData* data) {
    for (int i = 0; i < PC_MAP_PINS; i++) {
        PcMapPin* p = &data->pins[i];
        if (p->castle > 1 || p->x > 63 || p->y > 63 || p->requirement > 9 ||
            p->kind > 3 || !memchr(p->note, 0, sizeof(p->note)))
            memset(p, 0, sizeof(*p));
    }
    if (data->quickItem < 0 || data->quickItem >= NUM_HAND_ITEMS)
        data->quickItem = ITEM_POTION;
    if (data->quickSpell < -1 || data->quickSpell >= NUM_SPELLS)
        data->quickSpell = -1;
    data->loadout = SDL_clamp(data->loadout, -1, PC_LOADOUTS - 1);
}

void PcQolSelectSave(const char* identity, bool loading) {
    char fallback[32];
    snprintf(fallback, sizeof(fallback), "%.12s-%d", g_Status.saveName,
             g_PlayableCharacter);
    if (!identity)
        identity = fallback;
    char path[1024];
    if (snprintf(path, sizeof(path), "%s.%08x.qol", g_PcSettingsPath,
                 Hash(identity, strlen(identity))) >= sizeof(path))
        return;
    if (!strcmp(path, s_Profile)) {
        if (!loading)
            PcQolSavePreview(s_ProfileId, s_ProfileId);
        return;
    }
    if (s_Profile[0] && loading)
        PcQolSave();
    unsigned previousId = s_ProfileId;
    strcpy(s_Profile, path);
    s_ProfileId = Hash(identity, strlen(identity));
    if (!loading) {
        if (!PcQolWrite(path, &g_PcQol, sizeof(g_PcQol)))
            g_PcQolMessage = "Could not save adventure profile.";
        PcQolSavePreview(s_ProfileId, previousId);
    }
    if (loading) {
        PcQolData data = {
            .quickItem = ITEM_POTION, .quickSpell = -1, .loadout = -1};
        if (PcQolRead(path, &data, sizeof(data))) {
            PcQolValidate(&data);
        }
        g_PcQol = data;
    }
}

bool PcQolReady(void) {
    return g_GameState == Game_Play && g_GameStep == Play_Default &&
           g_GameEngineStep == Engine_Normal && g_PauseAllowed &&
           !g_CutsceneHasControl && g_DemoMode == Demo_None && !g_IsUsingCd &&
           !D_80097C98 && g_Status.hp > 0;
}

bool PcQolVisited(int castle, int x, int y) {
    return castle >= 0 && castle < 2 && x >= 0 && x < 64 && y >= 0 && y < 64 &&
           (g_CastleMap[castle * 0x400 + y * 16 + x / 4] &
            (1 << ((3 - (x & 3)) * 2)));
}

void PcQolMapPosition(int* castle, int* x, int* y) {
    *castle = !!(g_StageId & STAGE_INVERTEDCASTLE_FLAG);
    *x = SDL_clamp(g_Tilemap.left + (g_PlayerX >> 8), 0, 63);
    *y = SDL_clamp(g_Tilemap.top + (g_PlayerY >> 8), 0, 63);
}

bool PcQolPinReady(const PcMapPin* pin) {
    if (!pin->requirement)
        return false;
    if (pin->requirement == 9)
        return PcQolOwned(true, ITEM_SPIKE_BREAKER) > 0;
    return pin->requirement <= 8 &&
           (g_Status.relics[requirements[pin->requirement - 1]] &
            RELIC_FLAG_FOUND);
}

int PcQolSetPin(
    int castle, int x, int y, int kind, int requirement, const char* note) {
    if (!PcQolVisited(castle, x, y) || kind < 0 || kind > 3 ||
        requirement < 0 || requirement > 9)
        return -1;
    int index = -1;
    for (int i = 0; i < PC_MAP_PINS; i++) {
        PcMapPin* p = &g_PcQol.pins[i];
        if (p->used && p->castle == castle && p->x == x && p->y == y) {
            index = i;
            break;
        }
        if (!p->used && index < 0)
            index = i;
    }
    if (index < 0)
        return -1;
    PcMapPin pin = {.used = 1,
                    .castle = castle,
                    .x = x,
                    .y = y,
                    .kind = kind,
                    .requirement = requirement};
    for (int i = 0; note[i] && i < sizeof(pin.note) - 1; i++)
        pin.note[i] = note[i] >= 32 && note[i] <= 126 ? note[i] : '?';
    g_PcQol.pins[index] = pin;
    return index;
}

static bool Empty(int slot, int id) {
    static const int empty[7] = {
        0,
        0,
        ITEM_EMPTY_HEAD,
        ITEM_NO_ARMOR,
        ITEM_NO_CAPE,
        ITEM_NO_ACCESSORY,
        ITEM_NO_ACCESSORY};
    return id == empty[slot];
}

int PcQolOwned(int body, int id) {
    if (id < 0 || id >= (body ? NUM_BODY_ITEMS : NUM_HAND_ITEMS))
        return 0;
    if ((!body && id == ITEM_EMPTY_HAND) ||
        (body && (id == ITEM_EMPTY_HEAD || id == ITEM_NO_ARMOR ||
                  id == ITEM_NO_CAPE || id == ITEM_NO_ACCESSORY)))
        return 1;
    int count =
        body ? g_Status.equipBodyCount[id] : g_Status.equipHandCount[id];
    for (int slot = body ? 2 : 0; slot < (body ? 7 : 2); slot++) {
        if (g_Status.equipment[slot] == id &&
            !(slot == 1 && g_Status.equipment[0] == id &&
              g_EquipDefs[id].itemCategory == ITEM_TWOHAND))
            count++;
    }
    return count;
}

void PcQolItemText(int item, bool description, char* out, size_t size) {
    if (!size)
        return;
    const char* text =
        item < NUM_HAND_ITEMS
            ? (description ? g_EquipDefs[item].description
                           : g_EquipDefs[item].name)
            : (description ? g_AccessoryDefs[item - NUM_HAND_ITEMS].description
                           : g_AccessoryDefs[item - NUM_HAND_ITEMS].name);
    size_t source = 0, used = 0;
    while (text && used + 1 < size) {
        unsigned ch = (unsigned char)text[source++];
        if (description) {
            if (!ch)
                break;
            if (ch == 0x81 && text[source]) {
                unsigned next = (unsigned char)text[source++];
                ch = next == 0x65 || next == 0x66   ? '\''
                     : next == 0x67 || next == 0x68 ? '"'
                                                    : '-';
            }
        } else {
            // Item names use the game's glyph table and FF terminator.
            if (ch == 0xFF)
                break;
            if (ch == 0)
                ch = ' ';
            else if ((ch >= 0x21 && ch <= 0x3A) || (ch >= 0x41 && ch <= 0x5A) ||
                     (ch >= 0x10 && ch <= 0x19))
                ch += 32;
            else if (ch == 2 || ch == 7)
                ch = '\'';
            else if (ch >= 1 && ch <= 0xF)
                ch += 32;
            else if (ch == 0x1A)
                ch = ':';
            else if (ch == 0x1F)
                ch = '?';
            else
                ch = '?';
        }
        out[used++] = ch >= 32 && ch < 127 ? ch : ' ';
    }
    out[used] = 0;
}

int PcQolInventory(int filter, int sort, bool favorites, int* items) {
    int count = 0;
    for (int item = 0; item < NUM_HAND_ITEMS + NUM_BODY_ITEMS; item++) {
        bool body = item >= NUM_HAND_ITEMS;
        int id = body ? item - NUM_HAND_ITEMS : item;
        if (!PcQolOwned(body, id) || (favorites && !g_PcQol.favorites[item]))
            continue;
        int category = body ? 4 + g_AccessoryDefs[id].equipType
                       : g_EquipDefs[id].itemCategory == ITEM_SHIELD ? 2
                       : g_EquipDefs[id].isConsumable                ? 3
                                                                     : 1;
        if (filter && category != filter)
            continue;
        int pos = count;
        while (pos > 0) {
            int other = items[pos - 1], comparison;
            if (sort == 1)
                comparison =
                    PcQolOwned(body, id) -
                    PcQolOwned(other >= NUM_HAND_ITEMS,
                               other >= NUM_HAND_ITEMS ? other - NUM_HAND_ITEMS
                                                       : other);
            else if (sort == 2)
                comparison =
                    (body ? g_AccessoryDefs[id].defBonus
                          : g_EquipDefs[id].attack) -
                    (other >= NUM_HAND_ITEMS
                         ? g_AccessoryDefs[other - NUM_HAND_ITEMS].defBonus
                         : g_EquipDefs[other].attack);
            else {
                char a[80], b[80];
                PcQolItemText(item, false, a, sizeof(a));
                PcQolItemText(other, false, b, sizeof(b));
                comparison = -SDL_strcasecmp(a, b);
            }
            if (comparison <= 0)
                break;
            items[pos] = other;
            pos--;
        }
        items[pos] = item;
        count++;
    }
    return count;
}

bool PcQolEquip(const u32 equipment[7], bool apply) {
    if (g_PlayableCharacter != PLAYER_ALUCARD || g_StageId == STAGE_ST0 ||
        (g_Player.status & (PLAYER_STATUS_TRANSFORM | PLAYER_STATUS_UNK10)) ||
        g_Player.grabState || g_Player.unk46 ||
        !(PLAYER.step == Player_Stand || PLAYER.step == Player_Walk ||
          PLAYER.step == Player_Crouch))
        return false;
    int hand[NUM_HAND_ITEMS], body[NUM_BODY_ITEMS];
    for (int i = 0; i < NUM_HAND_ITEMS; i++)
        hand[i] = PcQolOwned(false, i);
    for (int i = 0; i < NUM_BODY_ITEMS; i++)
        body[i] = PcQolOwned(true, i);
    if ((equipment[0] < NUM_HAND_ITEMS &&
         g_EquipDefs[equipment[0]].itemCategory == ITEM_TWOHAND) ||
        (equipment[1] < NUM_HAND_ITEMS &&
         g_EquipDefs[equipment[1]].itemCategory == ITEM_TWOHAND))
        if (equipment[0] != equipment[1])
            return false;
    static const int types[5] = {0, 1, 2, 3, 3};
    for (int slot = 0; slot < 7; slot++) {
        unsigned id = equipment[slot];
        if (id >= (slot < 2 ? NUM_HAND_ITEMS : NUM_BODY_ITEMS) ||
            (slot >= 2 && g_AccessoryDefs[id].equipType != types[slot - 2]) ||
            (slot < 2 && (id == ITEM_HAMMER || id == ITEM_LIFE_APPLE)))
            return false;
        if (Empty(slot, id) || (slot == 1 && equipment[0] == id &&
                                g_EquipDefs[id].itemCategory == ITEM_TWOHAND))
            continue;
        int* available = slot < 2 ? &hand[id] : &body[id];
        if (--*available < 0)
            return false;
    }
    if (!apply)
        return true;
    for (int i = 0; i < NUM_HAND_ITEMS; i++)
        g_Status.equipHandCount[i] = SDL_min(hand[i], 99);
    for (int i = 0; i < NUM_BODY_ITEMS; i++)
        g_Status.equipBodyCount[i] = SDL_min(body[i], 99);
    memcpy(g_Status.equipment, equipment, sizeof(g_PcQol.loadouts[0]));
    if (equipment[0] == ITEM_SWORD_FAMILIAR ||
        equipment[1] == ITEM_SWORD_FAMILIAR) {
        g_Status.relics[RELIC_SWORD_CARD] &= ~RELIC_FLAG_ACTIVE;
        g_Servant = 0;
    }
    make_all();
    return true;
}

bool PcQolApplyGear(const u32 equipment[7]) {
    extern bool LoadWeaponPrg(s32 slot);
    extern void InitWeapon(s32 slot), UpdateCapePalette(void);
    extern void CheckWeaponCombo(void), ServantWorkClear(void);
    if (!PcQolReady())
        return false;
    PlayerStatus previous = g_Status;
    int previousServant = g_Servant;
    if (!PcQolEquip(equipment, true))
        return false;
    g_PrevEquippedWeapons[0] = previous.equipment[0];
    g_PrevEquippedWeapons[1] = previous.equipment[1];
    if (previous.equipment[ARMOR_SLOT] == ITEM_AXE_LORD_ARMOR)
        g_PrevEquippedWeapons[0] = g_PrevEquippedWeapons[1] = 0xD8;
    // Native assets are already extracted; load synchronously while paused.
    int useDisk = g_UseDisk;
    g_UseDisk = 0;
    bool ok = LoadWeaponPrg(0) && LoadWeaponPrg(1);
    if (!ok) {
        g_Status = previous;
        g_Servant = previousServant;
        g_EquippedWeaponIds[0] = g_EquippedWeaponIds[1] = -1;
        LoadWeaponPrg(0);
        LoadWeaponPrg(1);
        g_PcQolMessage = "Gear loading failed; previous items restored.";
    }
    g_UseDisk = useDisk;
    InitWeapon(0);
    InitWeapon(1);
    UpdateCapePalette();
    CheckWeaponCombo();
    make_all();
    if (g_Servant != previousServant)
        ServantWorkClear();
    return ok;
}

bool PcQolEquipItem(int item, int slot) {
    if (slot < 0 || slot > 6 || item < 0 ||
        item >= NUM_HAND_ITEMS + NUM_BODY_ITEMS ||
        (slot < 2) != (item < NUM_HAND_ITEMS))
        return false;
    u32 equipment[7];
    memcpy(equipment, g_Status.equipment, sizeof(equipment));
    int id = item < NUM_HAND_ITEMS ? item : item - NUM_HAND_ITEMS;
    if (slot < 2) {
        if (g_EquipDefs[equipment[slot]].itemCategory == ITEM_TWOHAND)
            equipment[1 - slot] = ITEM_EMPTY_HAND;
        if (g_EquipDefs[id].itemCategory == ITEM_TWOHAND)
            equipment[1 - slot] = id;
    }
    equipment[slot] = id;
    return PcQolApplyGear(equipment);
}

bool PcQolUseItem(int item) {
    if (!g_PcSettings.quickItems || !PcQolReady() ||
        g_PlayableCharacter != PLAYER_ALUCARD || g_StageId == STAGE_ST0 ||
        item < 0 || item >= NUM_HAND_ITEMS || !g_Status.equipHandCount[item] ||
        g_EquipDefs[item].unk13 != 55 || g_EquipDefs[item].unk14 == 20 ||
        item == ITEM_HAMMER || item == ITEM_LIFE_APPLE)
        return false;
    s_QuickItem = item;
    return true;
}

bool PcQolCast(int spell) {
    if (!g_PcSettings.spellShortcuts || !PcQolReady() || spell < 0 ||
        spell >= NUM_SPELLS || !(g_Status.spellsLearnt & (1 << spell)) ||
        g_Status.mp < g_SpellDefs[spell].mpUsage ||
        g_PlayableCharacter != PLAYER_ALUCARD || g_StageId == STAGE_ST0)
        return false;
    if (spell == SPELL_WING_SMASH &&
        (!(g_Player.status & PLAYER_STATUS_BAT_FORM) ||
         (PLAYER.step_s != 1 && PLAYER.step_s != 2)))
        return false;
    if (spell == SPELL_WOLF_CHARGE &&
        (!(g_Player.status & PLAYER_STATUS_WOLF_FORM) ||
         !IsRelicActive(RELIC_SKILL_OF_WOLF)))
        return false;
    s_QuickSpell = spell;
    return true;
}

void PcQolBeforePlayer(void) {
    if (g_CurrentEntity != &PLAYER || !PcQolReady()) {
        s_QuickItem = s_QuickSpell = -1;
        return;
    }
    if (s_QuickItem >= 0) {
        int id = s_QuickItem;
        s_QuickItem = -1;
        if (g_Player.unk46 || g_Player.grabState ||
            g_Player.status & PLAYER_STATUS_TRANSFORM ||
            !(PLAYER.step == Player_Stand || PLAYER.step == Player_Walk ||
              PLAYER.step == Player_Crouch))
            return;
        for (int i = 32; i < 64; i++)
            if (g_Entities[i].entityId == 39)
                return;
        if (g_Status.equipHandCount[id] &&
            CreateEntFactoryFromEntity(
                &PLAYER, FACTORY(BP_55, (g_EquipDefs[id].unk14 & 0x7F)), id)) {
            if (!CheckEquipmentItemCount(ITEM_DUPLICATOR, EQUIP_ACCESSORY))
                g_Status.equipHandCount[id]--;
        }
    }
    if (s_QuickSpell >= 0) {
        int id = s_QuickSpell;
        s_QuickSpell = -1;
        if (id == SPELL_WING_SMASH &&
            (g_Player.status & PLAYER_STATUS_BAT_FORM) &&
            (PLAYER.step_s == 1 || PLAYER.step_s == 2)) {
            if (CastSpell(id)) {
                extern s32 g_WingSmashTimer, g_WingSmashButtonCounter;
                SetPlayerAnim(0xC6);
                SetSpeedX(FIX(6));
                PLAYER.step_s = 3;
                CreateEntFactoryFromEntity(
                    &PLAYER, FACTORY(BP_BLINK_WHITE, 0x5c), 0);
                CreateEntFactoryFromEntity(&PLAYER, BP_67, 0);
                g_WingSmashTimer = 0x40;
                g_WingSmashButtonCounter = 0;
            }
            return;
        }
        if (id == SPELL_WOLF_CHARGE &&
            (g_Player.status & PLAYER_STATUS_WOLF_FORM) &&
            IsRelicActive(RELIC_SKILL_OF_WOLF)) {
            g_ButtonCombo[COMBO_QCF].buttonsCorrect = COMBO_COMPLETE;
            g_ButtonCombo[COMBO_QCF].timer = 20;
            func_8012CC30(0);
            return;
        }
        if (g_PlayableCharacter != PLAYER_ALUCARD || g_Player.unk46 ||
            g_Player.unk72 || g_Player.grabState ||
            g_Player.status & PLAYER_STATUS_TRANSFORM ||
            !(PLAYER.step == Player_Stand || PLAYER.step == Player_Walk ||
              PLAYER.step == Player_Crouch))
            return;
        void (*perform[NUM_SPELLS])(void) = {
            PerformDarkMetamorphosis,
            PerformSummonSpirit,
            PerformHellfire,
            PerformTetraSpirit,
            NULL,
            PerformSoulSteal,
            NULL,
            PerformSwordBrothers};
        if (!perform[id] ||
            (id == SPELL_SWORD_BROTHERS &&
             (g_Servant != FAM_ACTIVE_SWORD ||
              g_Status.statsFamiliars[FAM_STATS_SWORD].level < 50)))
            return;
        if (g_Status.spellsLearnt & (1 << id) && CastSpell(id)) {
            perform[id]();
            if (id == SPELL_SWORD_BROTHERS) {
                g_ButtonCombo[COMBO_SWORD_BROTHERS].buttonsCorrect =
                    COMBO_COMPLETE;
                g_ButtonCombo[COMBO_SWORD_BROTHERS].timer = 20;
                g_Player.unk70 = 1;
            }
        }
    }
}

bool PcQolAllowSubweapon(int subweapon) {
    return !g_PcSettings.protectSubweapon || !g_Status.subWeapon ||
           g_Status.subWeapon == subweapon || (g_pads[0].pressed & PAD_DOWN);
}

void PcQolWarpOffer(int current) {
    if (current != s_WarpCurrent || s_WarpStage != g_StageId)
        s_WarpDestination = -1;
    s_WarpCurrent = current;
    s_WarpStage = g_StageId;
}
int PcQolWarpDestination(int current) {
    int chosen = s_WarpStage == g_StageId && s_WarpCurrent == current
                     ? s_WarpDestination
                     : -1;
    s_WarpDestination = -1;
    int flags =
        g_CastleFlags[g_StageId & STAGE_INVERTEDCASTLE_FLAG ? RWRP_UNLOCKS
                                                            : WRP_UNLOCKS];
    return g_PcSettings.warpChooser && chosen >= 0 && chosen < 5 &&
                   (flags & (1 << chosen))
               ? chosen
               : -1;
}
bool PcQolWarpChoose(int destination) {
    if (!g_PcSettings.warpChooser || !PcQolReady() ||
        s_WarpStage != g_StageId ||
        (g_StageId != STAGE_WRP && g_StageId != STAGE_RWRP) ||
        abs(PLAYER.posX.i.hi - 128) > 8 || destination < 0 || destination > 4 ||
        !(g_CastleFlags[g_StageId == STAGE_RWRP ? RWRP_UNLOCKS : WRP_UNLOCKS] &
          (1 << destination)))
        return false;
    s_WarpDestination = destination;
    return true;
}

void PcQolDialogueChar(int ch) {
    if (ch == '\n') {
        s_Line = (s_Line + 1) % 24;
        s_Column = 0;
        s_Dialogue[s_Line][0] = 0;
    } else if (ch >= 32 && ch < 127 && s_Column < 126) {
        s_Dialogue[s_Line][s_Column++] = ch;
        s_Dialogue[s_Line][s_Column] = 0;
    }
}
const char* PcQolDialogueLine(int index) {
    return s_Dialogue[(s_Line + 1 + index) % 24];
}
bool PcQolSceneBegin(unsigned id) {
    PcQolDialogueChar('\n');
    s_SkipSeen = id < 640 && (g_PcQol.seenScenes[id / 8] & (1 << (id & 7)));
    return PcQolSkipWatched();
}
bool PcQolSkipWatched(void) {
    return g_PcSettings.skipSeenDialogue && s_SkipSeen;
}
void PcQolSceneEnd(unsigned id) {
    if (id < 640) {
        g_PcQol.seenScenes[id / 8] |= 1 << (id & 7);
        PcQolSave();
    }
}

void PcQolFrame(void) {
    PcQolResumeFrame();
    if (s_WarpStage != g_StageId)
        s_WarpDestination = -1;
    if (!PcQolReady()) {
        s_QuickItem = s_QuickSpell = -1;
        return;
    }
    if (g_PcSpellPractice && g_pads[0].tapped) {
        static const u16 masks[] = {PAD_UP,     PAD_RIGHT,  PAD_DOWN, PAD_LEFT,
                                    PAD_SQUARE, PAD_CIRCLE, PAD_CROSS};
        const char* names = "URDLABJ";
        for (int i = 0; i < 7; i++)
            if (g_pads[0].tapped & masks[i]) {
                size_t n = strlen(s_Inputs);
                if (n == sizeof(s_Inputs) - 1) {
                    memmove(s_Inputs, s_Inputs + 1, n);
                    n--;
                }
                s_Inputs[n] = names[i];
                s_Inputs[n + 1] = 0;
            }
    }
    if (g_api.o.rooms && g_api.o.tileLayers && g_StageId != STAGE_ST0) {
        for (int i = 0; i < 256 && g_api.o.rooms[i].left != 64; i++) {
            const RoomHeader* room = &g_api.o.rooms[i];
            if (room->left != g_Tilemap.left || room->top != g_Tilemap.top ||
                room->load.tileLayoutId == 255)
                continue;
            LayerDef* layer = g_api.o.tileLayers[room->load.tileLayoutId].fg;
            if (layer && (layer->rect.params & 0x20)) {
                int castle, x, y;
                PcQolMapPosition(&castle, &x, &y);
                int index = y * 8 + x / 8, mask = 1 << (x & 7);
                if (!(g_PcQol.saveRooms[castle][index] & mask)) {
                    g_PcQol.saveRooms[castle][index] |= mask;
                    PcQolSave();
                }
            }
            break;
        }
    }
}
