// SPDX-License-Identifier: AGPL-3.0-or-later
#include "inventory.h"
#include "menu.h"
#include "weapon_preview.h"
#include "weapon_fx.h"
#include <weapon.h>
#include "../dra/dra.h"
#include <string.h>

extern u8 g_GfxEquipIcon[];
extern u16 g_PalEquipIcon[];

static Entity s_Player;
static int s_Animation;
static Uint64 s_LastTick;
static int s_AttackWait, s_EffectAge;
static bool s_FxPixels;
extern Weapon D_8017A000, D_8017D000;

static SDL_Texture* Texture(SDL_Renderer* r, const u8* data, int width,
                            int height, int pitch, const u16* palette) {
    SDL_Surface* image =
        SDL_CreateSurface(width, height, SDL_PIXELFORMAT_RGBA32);
    if (!image)
        return NULL;
    for (int y = 0; y < height; y++) {
        u8* row = (u8*)image->pixels + y * image->pitch;
        for (int x = 0; x < width; x++) {
            int color =
                palette[(data[y * pitch + x / 2] >> ((x & 1) * 4)) & 15];
            row[x * 4] = (color & 31) * 255 / 31;
            row[x * 4 + 1] = ((color >> 5) & 31) * 255 / 31;
            row[x * 4 + 2] = ((color >> 10) & 31) * 255 / 31;
            row[x * 4 + 3] = color ? 255 : 0;
        }
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(r, image);
    SDL_DestroySurface(image);
    if (texture) {
        SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
        SDL_SetTextureScaleMode(texture, SDL_SCALEMODE_NEAREST);
    }
    return texture;
}

static void Palette(int clut, u16 palette[16]) {
    RECT rect = {(clut & 63) * 16, clut >> 6, 16, 1};
    if (s_FxPixels)
        memcpy(palette, &g_PcFxVram[rect.y][rect.x], 16 * sizeof(u16));
    else {
        StoreImage(&rect, (u_long*)palette);
        DrawSync(0);
    }
}

void PcInventoryIcon(SDL_Renderer* r, int item, int x, int y, int scale) {
    if (item < 0 || item >= NUM_HAND_ITEMS + NUM_BODY_ITEMS)
        return;
    int icon, palette;
    if (item < NUM_HAND_ITEMS) {
        icon = g_EquipDefs[item].icon;
        palette = g_EquipDefs[item].iconPalette;
    } else {
        icon = g_AccessoryDefs[item - NUM_HAND_ITEMS].icon;
        palette = g_AccessoryDefs[item - NUM_HAND_ITEMS].iconPalette;
    }
    SDL_Texture* texture = Texture(r, &g_GfxEquipIcon[icon * 128], 16, 16, 8,
                                   &g_PalEquipIcon[palette * 16]);
    if (texture) {
        SDL_FRect dest = {x, y, 16 * scale, 16 * scale};
        SDL_RenderTexture(r, texture, NULL, &dest);
        SDL_DestroyTexture(texture);
    }
}

static bool HasSpecial(int hand) {
    int item = g_Status.equipment[hand];
    return item >= 0 && item < NUM_HAND_ITEMS &&
           (g_EquipDefs[item].itemCategory == ITEM_SHIELD ||
            PcWeaponFxSpecial(item) >= 0);
}

static void StartAnimation(void) {
    memset(&s_Player, 0, sizeof(s_Player));
    s_Player.animSet = 1;
    s_Player.palette = PAL_FLAG(PAL_ALUCARD);
    int hand =
        s_Animation == 3 || s_Animation == 5 ? RIGHT_HAND_SLOT : LEFT_HAND_SLOT;
    int item = g_Status.equipment[hand];
    bool spell = s_Animation >= 4 && item < NUM_HAND_ITEMS &&
                 g_EquipDefs[item].itemCategory == ITEM_SHIELD;
    if (s_Animation >= 4 && !spell && PcWeaponFxSpecial(item) >= 0)
        item = PcWeaponFxSpecial(item);
    int attack =
        item >= 0 && item < LEN(g_EquipDefs) ? g_EquipDefs[item].playerAnim : 0;
    if (spell || (s_Animation >= 4 && !HasSpecial(hand)) ||
        (item >= 0 && item < LEN(g_EquipDefs) &&
         g_EquipDefs[item].itemCategory == ITEM_SHIELD))
        attack = 6;
    s_Player.ext.player.anim =
        s_Animation == 0   ? 6
        : s_Animation == 1 ? 7
                           : attack;
    s_AttackWait = s_EffectAge = 0;
    Entity* previous = g_CurrentEntity;
    g_CurrentEntity = &s_Player;
    PlayAnimation(D_800B0130, D_800B01B8);
    g_CurrentEntity = previous;
    PcWeaponFxStop();
    if (g_PlayableCharacter == PLAYER_ALUCARD && s_Animation >= 2 &&
        (s_Animation < 4 || HasSpecial(hand)) && item != ITEM_EMPTY_HAND &&
        PcWeaponFxStart(hand, item, spell))
        PcWeaponFxStep(&s_Player);
}

void PcInventoryPreviewReset(void) {
    s_Animation = 0;
    s_LastTick = 0;
    StartAnimation();
}
void PcInventoryPreviewCycle(void) {
    if (g_PlayableCharacter != PLAYER_ALUCARD)
        return;
    s_Animation = (s_Animation + 1) % 6;
    s_LastTick = 0;
    StartAnimation();
}
const char* PcInventoryPreviewName(void) {
    if (g_PlayableCharacter != PLAYER_ALUCARD)
        return "Richter";
    if (s_Animation >= 4 && !HasSpecial(s_Animation == 5))
        return s_Animation == 5 ? "No special R" : "No special L";
    return (const char*[]){"Idle",     "Walk",      "Attack L",
                           "Attack R", "Special L", "Special R"}[s_Animation];
}

static int Clut(const Entity* entity, int offset) {
    int index = entity->palette;
    index = index & PAL_UNK_FLAG ? index & 0x7FFF : index + offset;
    return index < 0x400 ? g_ClutIds[index] : 0;
}

static SDL_Texture* Page(SDL_Renderer* r, int tpage, int clut) {
    u16 pixels[64 * 256], palette[16];
    RECT rect = {(tpage & 15) * 64, (tpage & 16) * 16, 64, 256};
    if (tpage & 0x180)
        return NULL;
    if (s_FxPixels) {
        for (int row = 0; row < 256; row++)
            memcpy(&pixels[row * 64], &g_PcFxVram[rect.y + row][rect.x], 128);
    } else
        StoreImage(&rect, (u_long*)pixels);
    Palette(clut, palette);
    return Texture(r, (u8*)pixels, 256, 256, 128, palette);
}

static void SpriteTexture(
    SDL_Renderer* r, SDL_Texture* texture, const SDL_FRect* source,
    SDL_FRect dest, const Entity* entity, float x, float y, SDL_FlipMode flip) {
    float sx = entity->drawFlags & ENTITY_SCALEX ? entity->scaleX / 256.0f : 1;
    float sy = entity->drawFlags & ENTITY_SCALEY ? entity->scaleY / 256.0f : 1;
    dest.x = x + (dest.x - x) * sx;
    dest.y = y + (dest.y - y) * sy;
    dest.w *= sx;
    dest.h *= sy;
    SDL_FPoint pivot = {x - dest.x, y - dest.y};
    double angle =
        entity->drawFlags & ENTITY_ROTATE ? entity->rotate * 360.0 / 4096 : 0;
    if (entity->drawFlags & ENTITY_OPACITY)
        SDL_SetTextureAlphaMod(texture, entity->opacity);
    if (entity->blendMode & BLEND_TRANSP)
        SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_ADD);
    SDL_RenderTextureRotated(r, texture, source, &dest, angle, &pivot, flip);
}

static void Sprite(SDL_Renderer* r, const Entity* entity, float x, float y,
                   float scale, s16** override) {
    int bank = entity->animSet;
    int pose = entity->animCurFrame & 0x7FFF;
    if (!bank || !pose)
        return;
    s16** frames = override;
    if (!frames) {
        if (bank > 0 && bank < LEN(D_800A3B70))
            frames = D_800A3B70[bank];
        else if ((bank & 0x7FFF) < 32 && g_api.o.spriteBanks)
            frames = (s16**)g_api.o.spriteBanks[bank & 0x7FFF];
    }
    if (!frames || !frames[pose])
        return;
    s16* frame = frames[pose];
    int parts = *frame++;
    if (parts & 0x8000) {
        int index = parts & 0x7FFF;
        if (index >= 256 || !g_PlOvlSpritesheet[index])
            return;
        u8* data = g_PlOvlSpritesheet[index];
        u16 palette[16];
        Palette(Clut(entity, frame[2]), palette);
        SDL_Texture* texture =
            Texture(r, data + 4, data[0], data[1], data[0] / 2, palette);
        if (texture) {
            int w = data[0], h = data[1];
            int dx = frame[0] + data[2], dy = frame[1] + data[3];
            SDL_FRect dest = {x + (entity->facingLeft ? -dx - w : dx) * scale,
                              y + dy * scale, w * scale, h * scale};
            SpriteTexture(r, texture, NULL, dest, entity, x, y,
                          entity->facingLeft ? SDL_FLIP_HORIZONTAL : 0);
            SDL_DestroyTexture(texture);
        }
    } else {
        for (int i = 0; i < parts; i++, frame += 11) {
            int page = frame[6] + entity->unk5A;
            SDL_Texture* texture = Page(r, page >> 2, Clut(entity, frame[5]));
            if (!texture)
                continue;
            SDL_FRect source = {frame[7] + ((page & 1) ? 128 : 0),
                                frame[8] + ((page & 2) ? 128 : 0),
                                frame[9] - frame[7], frame[10] - frame[8]};
            int dx = frame[1], dy = frame[2], w = frame[3], h = frame[4];
            if (frame[0] & 4) {
                w--;
                source.w--;
                dx += (frame[0] & 2) != 0;
            }
            if (frame[0] & 8) {
                h--;
                source.h--;
                dy += (frame[0] & 1) != 0;
            }
            if (frame[0] & 0x10) {
                w--;
                source.x++;
                source.w--;
                dx += (frame[0] & 2) == 0;
            }
            if (frame[0] & 0x20) {
                h--;
                source.y++;
                source.h--;
                dy += (frame[0] & 1) == 0;
            }
            SDL_FRect dest = {x + (entity->facingLeft ? -dx - w : dx) * scale,
                              y + dy * scale, w * scale, h * scale};
            SDL_FlipMode flip = ((frame[0] & 2) != 0) ^ entity->facingLeft
                                    ? SDL_FLIP_HORIZONTAL
                                    : SDL_FLIP_NONE;
            if (frame[0] & 1)
                flip |= SDL_FLIP_VERTICAL;
            SpriteTexture(r, texture, &source, dest, entity, x, y, flip);
            SDL_DestroyTexture(texture);
        }
    }
}

static void EquippedHand(
    SDL_Renderer* r, int hand, float x, float y, float scale) {
    int id = g_Status.equipment[hand];
    if (id < 0 || id >= NUM_HAND_ITEMS || id == ITEM_EMPTY_HAND)
        return;
    const Equipment* equip = &g_EquipDefs[id];
    const Weapon* module = hand ? &D_8017D000 : &D_8017A000;
    const PcWeaponPreview* data = module->preview;
    if (!data || g_EquippedWeaponIds[hand] != equip->weaponId)
        return;
    Entity weapon = {0};
    weapon.animSet = ANIMSET_OVL(16 + hand * 2);
    weapon.palette = PAL_UNK_110 + hand * 24;
    weapon.unk5A = 100 + hand * 2;
    s16** frames = data->sprites;
    if (equip->itemCategory == ITEM_SHIELD && data->shield) {
        if (s_Animation != 2 + hand || s_Player.poseTimer < 0)
            return;
        if (equip->weaponId == 29)
            weapon.palette += (SDL_GetTicksNS() / 33333333) % 5;
        int anim = s_Player.ext.player.anim;
        int shield = anim == 7 ? 8 : anim == 8 ? 7 : anim == 13 ? 5 : 0;
        if (shield >= data->shieldCount)
            return;
        AnimationFrame* poses = data->shield[shield];
        int pose = 0;
        while (shield && pose < s_Player.pose && poses[pose].duration > 0 &&
               poses[pose].duration < 0xFFFD)
            pose++;
        if (poses[pose].duration == 0 || poses[pose].duration >= 0xFFFD)
            pose = 0;
        weapon.animCurFrame = poses[pose].pose & 0x1FF;
    } else if (s_Animation == 2 + hand && data->attacks &&
               s_Player.poseTimer >= 0) {
        int variant = equip->unk14 & 0x7F;
        if (variant >= data->attackCount)
            return;
        const WeaponAnimation* anim = &data->attacks[variant];
        int index = s_Player.ext.player.anim - anim->frameStart;
        if (index < 0 || index >= 7)
            return;
        u16* poses = anim->frames[index];
        int pose = 0;
        while (pose < s_Player.pose && poses[pose] != 0xFFFF)
            pose++;
        if (poses[pose] == 0xFFFF)
            return;
        weapon.animCurFrame = poses[pose] & 0x1FF;
        weapon.palette += anim->palette;
        if (data->draBank)
            frames = D_800A3B70[data->draBank];
    } else
        return;
    if (!data->draBank && weapon.animCurFrame >= data->spriteCount)
        return;
    Sprite(r, &weapon, x, y, scale, frames);
}

static void Sword(SDL_Renderer* r, const Entity* entity, int x, int y) {
    if (!(entity->flags & FLAG_HAS_PRIMS) || entity->primIndex < 0 ||
        entity->primIndex >= MAX_PRIM_COUNT)
        return;
    Primitive* first = &g_PrimBuf[entity->primIndex];
    int left = 32767, top = 32767, right = -32768, bottom = -32768;
    for (Primitive* p = first; p; p = p->next) {
        if ((p->drawMode & DRAW_HIDE) ||
            (p->type != PRIM_GT3 && p->type != PRIM_GT4))
            continue;
        left = SDL_min(left, SDL_min(p->x0, SDL_min(p->x1, p->x2)));
        right = SDL_max(right, SDL_max(p->x0, SDL_max(p->x1, p->x2)));
        top = SDL_min(top, SDL_min(p->y0, SDL_min(p->y1, p->y2)));
        bottom = SDL_max(bottom, SDL_max(p->y0, SDL_max(p->y1, p->y2)));
        if (p->type == PRIM_GT4) {
            left = SDL_min(left, p->x3);
            right = SDL_max(right, p->x3);
            top = SDL_min(top, p->y3);
            bottom = SDL_max(bottom, p->y3);
        }
    }
    if (right <= left || bottom <= top)
        return;
    float scale =
        SDL_min(1.5f, SDL_min(48.0f / (right - left), 60.0f / (bottom - top)));
    SDL_Texture* texture = NULL;
    int lastPage = -1, lastClut = -1;
    for (Primitive* p = first; p; p = p->next) {
        if ((p->drawMode & DRAW_HIDE) ||
            (p->type != PRIM_GT3 && p->type != PRIM_GT4))
            continue;
        if (p->tpage != lastPage || p->clut != lastClut) {
            SDL_DestroyTexture(texture);
            texture =
                p->clut < 0x400 ? Page(r, p->tpage, g_ClutIds[p->clut]) : NULL;
            lastPage = p->tpage;
            lastClut = p->clut;
        }
        if (!texture)
            continue;
        SDL_Vertex vertices[4];
        int px[] = {p->x0, p->x1, p->x2, p->x3};
        int py[] = {p->y0, p->y1, p->y2, p->y3};
        int u[] = {p->u0, p->u1, p->u2, p->u3};
        int v[] = {p->v0, p->v1, p->v2, p->v3};
        for (int i = 0; i < 4; i++) {
            vertices[i].position =
                (SDL_FPoint){x + (px[i] - (left + right) / 2) * scale,
                             y + (py[i] - (top + bottom) / 2) * scale};
            vertices[i].tex_coord = (SDL_FPoint){u[i] / 256.0f, v[i] / 256.0f};
            vertices[i].color = (SDL_FColor){1, 1, 1, 1};
        }
        const int indices[] = {0, 1, 2, 1, 3, 2};
        SDL_RenderGeometry(
            r, texture, vertices, 4, indices, p->type == PRIM_GT3 ? 3 : 6);
    }
    SDL_DestroyTexture(texture);
}

typedef struct {
    int priority;
    Primitive* primitive;
    Entity* entity;
} FxLayer;
static int LayerOrder(const void* a, const void* b) {
    return ((const FxLayer*)a)->priority - ((const FxLayer*)b)->priority;
}

static void FxPrimitive(
    SDL_Renderer* r, Primitive* p, float x, float y, float scale) {
    int type = p->type & 15;
    bool texture = type == PRIM_GT4 || type == PRIM_GT3 || type == PRIM_SPRT;
    SDL_Texture* page = texture && p->clut < 0x400
                            ? Page(r, p->tpage, g_ClutIds[p->clut])
                            : NULL;
    if (texture && !page)
        return;
    SDL_BlendMode blend = SDL_BLENDMODE_BLEND;
    float alpha = 1;
    if (p->drawMode & DRAW_TRANSP) {
        int mode =
            ((p->tpage + (p->drawMode & (DRAW_UNK_40 | DRAW_TPAGE2))) >> 5) & 3;
        if (mode == 1 || mode == 3) {
            blend = SDL_BLENDMODE_ADD;
            alpha = mode == 3 ? 0.25f : 1;
        } else
            alpha = 0.5f;
    }
    if (page)
        SDL_SetTextureBlendMode(page, blend);
    SDL_SetRenderDrawBlendMode(r, blend);
    int px[] = {p->x0, p->x1, p->x2, p->x3};
    int py[] = {p->y0, p->y1, p->y2, p->y3};
    int u[] = {p->u0, p->u1, p->u2, p->u3};
    int v[] = {p->v0, p->v1, p->v2, p->v3};
    int red[] = {p->r0, p->r1, p->r2, p->r3};
    int green[] = {p->g0, p->g1, p->g2, p->g3};
    int blue[] = {p->b0, p->b1, p->b2, p->b3};
    if (type == PRIM_TILE || type == PRIM_SPRT) {
        px[1] = px[3] = p->x0 + (type == PRIM_TILE ? p->u0 : p->u1);
        px[2] = px[0];
        py[1] = py[0];
        py[2] = py[3] = p->y0 + (type == PRIM_TILE ? p->v0 : p->v1);
        for (int i = 1; i < 4; i++) {
            red[i] = red[0];
            green[i] = green[0];
            blue[i] = blue[0];
        }
        if (type == PRIM_SPRT) {
            u[1] = u[3] = p->u0 + p->u1;
            u[2] = u[0];
            v[1] = v[0];
            v[2] = v[3] = p->v0 + p->v1;
        }
    }
    if (type == PRIM_LINE_G2) {
        SDL_SetRenderDrawColor(r, p->r0, p->g0, p->b0, alpha * 255);
        SDL_RenderLine(r, x + px[0] * scale, y + py[0] * scale,
                       x + px[1] * scale, y + py[1] * scale);
    } else if (type == PRIM_TILE || type == PRIM_SPRT || type == PRIM_G4 ||
               type == PRIM_GT3 || type == PRIM_GT4) {
        SDL_Vertex vertices[4];
        for (int i = 0; i < 4; i++) {
            vertices[i].position =
                (SDL_FPoint){x + px[i] * scale, y + py[i] * scale};
            vertices[i].tex_coord = (SDL_FPoint){u[i] / 256.0f, v[i] / 256.0f};
            float divisor = texture ? 128.0f : 255.0f;
            vertices[i].color = (SDL_FColor){
                SDL_min(1, red[i] / divisor), SDL_min(1, green[i] / divisor),
                SDL_min(1, blue[i] / divisor), alpha};
            if (texture && !(p->drawMode & DRAW_COLORS))
                vertices[i].color = (SDL_FColor){1, 1, 1, alpha};
        }
        const int indices[] = {0, 1, 2, 1, 3, 2};
        SDL_RenderGeometry(
            r, page, vertices, 4, indices, type == PRIM_GT3 ? 3 : 6);
    }
    SDL_DestroyTexture(page);
}

static void DrawWeaponFx(SDL_Renderer* r, int x, int y) {
    FxLayer layers[MAX_PRIM_COUNT + 64];
    int count = 0;
    int left = 108, right = 148, top = 128, bottom = 192;
    for (int i = 0; i < 64; i++) {
        Entity* e = &g_PcFxEntities[i];
        if ((!i || e->entityId) && e->animCurFrame && e->animSet) {
            layers[count++] = (FxLayer){e->zPriority, NULL, e};
            left = SDL_min(left, e->posX.i.hi - 32);
            right = SDL_max(right, e->posX.i.hi + 48);
            top = SDL_min(top, e->posY.i.hi - 48);
            bottom = SDL_max(bottom, e->posY.i.hi + 32);
        }
    }
    for (int i = 0; i < MAX_PRIM_COUNT; i++) {
        Primitive* p = &g_PcFxPrimitives[i];
        if (!p->type || (p->drawMode & DRAW_HIDE) || p->type == PRIM_ENV)
            continue;
        layers[count++] = (FxLayer){p->priority, p, NULL};
        int type = p->type & 15;
        int px[] = {p->x0, p->x1, p->x2, p->x3};
        int py[] = {p->y0, p->y1, p->y2, p->y3};
        int vertices = type == PRIM_GT3 ? 3 : type == PRIM_LINE_G2 ? 2 : 4;
        if (type == PRIM_TILE || type == PRIM_SPRT) {
            px[1] = p->x0 + (type == PRIM_TILE ? p->u0 : p->u1);
            py[1] = p->y0 + (type == PRIM_TILE ? p->v0 : p->v1);
            vertices = 2;
        }
        for (int v = 0; v < vertices; v++) {
            left = SDL_min(left, px[v]);
            right = SDL_max(right, px[v]);
            top = SDL_min(top, py[v]);
            bottom = SDL_max(bottom, py[v]);
        }
    }
    left = SDL_max(left, -32);
    right = SDL_min(right, 288);
    top = SDL_max(top, -32);
    bottom = SDL_min(bottom, 224);
    float scale = SDL_min(2.0f, SDL_min(195.0f / (right - left + 8),
                                        90.0f / (bottom - top + 8)));
    float ox = x + 26 - (left + right) * 0.5f * scale;
    float oy = y + 47 - bottom * scale;
    int activeHand = s_Animation == 3 || s_Animation == 5;
    EquippedHand(r, 1 - activeHand, ox + 128 * scale, oy + 160 * scale, scale);
    qsort(layers, count, sizeof(layers[0]), LayerOrder);
    s_FxPixels = true;
    for (int i = 0; i < count; i++) {
        if (layers[i].primitive)
            FxPrimitive(r, layers[i].primitive, ox, oy, scale);
        else {
            Entity* e = layers[i].entity;
            s16** frames =
                e->animSet & 0x8000
                    ? (s16**)g_PcFxApi.o.spriteBanks[e->animSet & 0x7FFF]
                    : NULL;
            Sprite(r, e, ox + e->posX.i.hi * scale, oy + e->posY.i.hi * scale,
                   scale, frames);
        }
    }
    s_FxPixels = false;
    SDL_SetRenderDrawBlendMode(r, SDL_BLENDMODE_BLEND);
}

void PcInventoryPreviewDraw(SDL_Renderer* r, int x, int y) {
    if (g_PlayableCharacter != PLAYER_ALUCARD) {
        Sprite(r, &PLAYER, x, y, 2, NULL);
        return;
    }
    Uint64 now = SDL_GetTicksNS();
    if (!s_LastTick)
        s_LastTick = now;
    Uint64 elapsed = (now - s_LastTick) * 60 / 1000000000;
    int ticks = SDL_min(elapsed, 6);
    s_LastTick = elapsed > 6 ? now : s_LastTick + ticks * 1000000000ull / 60;
    // The original animation helper writes only through g_CurrentEntity.
    Entity* previous = g_CurrentEntity;
    g_CurrentEntity = &s_Player;
    for (int i = 0; i < ticks; i++) {
        if ((s_Animation < 4 && s_Player.poseTimer == -1 &&
             ++s_AttackWait >= 35) ||
            (s_Animation >= 4 && ++s_EffectAge >= 360))
            StartAnimation();
        PlayAnimation(D_800B0130, D_800B01B8);
        PcWeaponFxStep(&s_Player);
    }
    g_CurrentEntity = previous;
    if (PcWeaponFxActive())
        DrawWeaponFx(r, x, y);
    else {
        EquippedHand(r, 1, x, y, 2);
        EquippedHand(r, 0, x, y, 2);
        Sprite(r, &s_Player, x, y, 2, NULL);
    }
    Entity* familiar = &g_Entities[4];
    if (g_Servant && familiar->entityId >= 0xD0 && familiar->entityId < 0xE0) {
        if (g_Servant == 5)
            Sword(r, familiar, x + 55, y - 35);
        else
            Sprite(r, familiar, x + 55, y - 35, 2, NULL);
    }
}
