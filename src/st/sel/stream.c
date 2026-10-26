// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sel.h"

// BSS
static s32 D_801BC300[16]; // unused
static s32 D_801BC340;
static s32 g_StreamDiskIsReady;
static s32 D_801BC348;
static s32 D_801BC34C;

// Check if CD data is ready as long as its not related to reading the position
// of the laser. The status is cached in the `g_StreamDiskIsReady` global.
//
// returns:
//     0 - disk isn't ready for a request
//     1 - disk is ready
s32 StreamDiskIsReady() {
    u8 res[8];
    int ret;

    // if CD data isn't ready
    if (CdSync(CdlNop, res) == CdlNoIntr) {
        return g_StreamDiskIsReady = 0;
    }

    ret = CdLastCom();
    if (ret >= CdlGetlocL && ret <= CdlGetlocP ||
        !(res[0] & CdlStatShellOpen)) {
        // clear the command
        CdControlF(CdlNop, NULL);
        return g_StreamDiskIsReady = 0;
    }

    return g_StreamDiskIsReady = 1;
}

u_long* StreamNext(DECENV* dec) {
    u_long* addr;
    StHEADER* sector;
    int* rewindSwitch;
    int count;

    count = 0x40000;
    while (StGetNext(&addr, &sector)) {
        if (--count == 0) {
            dec->isdone = 1;
            return 0;
        }
    }

    rewindSwitch = g_StreamRewindSwitch;
    if (sector->frameCount >= *g_StreamEndFrame) {
        *rewindSwitch = 1;
    }

    g_StreamWidth = sector->width;
    g_StreamHeight = sector->height;
    dec->rect[0].w = dec->rect[1].w = count = g_StreamWidth * 3 / 2;
    dec->rect[0].h = dec->rect[1].h = g_StreamHeight;
    dec->slice.h = g_StreamHeight;
    return addr;
}

void StreamNextVlc(DECENV* dec) {
    const int WAIT_TIME = 4;
    int count = WAIT_TIME;
    u_long* next;

    while ((next = StreamNext(dec)) == 0) {
        if (--count == 0) {
            return;
        }
    }

    D_801BC340++;
    dec->vlcid = dec->vlcid ? 0 : 1;
    DecDCTvlc(next, dec->vlcbuf[dec->vlcid]);
    StFreeRing(next);
}

void func_801B9924(void) {
    volatile u32 pad[4]; // FAKE
    SetDispMask(0);
    func_801B18F4();
}

void func_801B994C(DECENV* dec, s32 unused) {
    volatile s32 retries = 0x40000;

    while (dec->isdone == 0) {
        if (--retries == 0) {
            dec->isdone = 1;
            dec->rectid = dec->rectid ? 0 : 1;
            dec->slice.x = (s16)(u16)dec->rect[dec->rectid].x;
            dec->slice.y = (s16)(u16)dec->rect[dec->rectid].y;
        }
    }
    dec->isdone = 0;
}

void func_801B99E4(void) {
    RECT rect;

    if (g_StreamDiskIsReady & 1) {
        return;
    }

    if ((*g_StreamIsRGB24 == 1) && D_8003C908) {
        StCdInterrupt();
        D_8003C908 = false;
    }

    rect = g_StreamEnv.dec.slice;
    LoadImage(&g_StreamEnv.dec.slice,
              (u_long*)g_StreamEnv.dec.imgbuf[g_StreamEnv.dec.imgid]);
    g_StreamEnv.dec.imgid = g_StreamEnv.dec.imgid == 0;
    g_StreamEnv.dec.slice.x = g_StreamEnv.dec.slice.x + g_StreamEnv.dec.slice.w;
    if (g_StreamEnv.dec.slice.x <
        g_StreamEnv.dec.rect[g_StreamEnv.dec.rectid].x +
            g_StreamEnv.dec.rect[g_StreamEnv.dec.rectid].w) {
        DecDCTout(g_StreamEnv.dec.imgbuf[g_StreamEnv.dec.imgid],
                  (g_StreamEnv.dec.slice.w * g_StreamEnv.dec.slice.h) / 2);
        return;
    }
    g_StreamEnv.dec.rectid = g_StreamEnv.dec.rectid == 0;
    g_StreamEnv.dec.slice.x = g_StreamEnv.dec.rect[g_StreamEnv.dec.rectid].x;
    g_StreamEnv.dec.slice.y = g_StreamEnv.dec.rect[g_StreamEnv.dec.rectid].y;
    g_StreamEnv.dec.isdone = 1;
}

void func_801B9B7C(DECENV* env, s16 x0, s16 y0, s16 x1, s32 y1) {
    s16 bitsPerPixel;
    s16 width;

    env->vlcbuf[0] = (void*)0x8013C000;
    env->vlcbuf[1] = (void*)0x8015E000;
    env->imgbuf[0] = (u16*)D_801D104C;
    env->vlcid = 0;
    env->imgbuf[1] = (u16*)&D_801D104C[0xb40];
    env->imgid = 0;
    env->rectid = 0;
    env->isdone = 0;

    if (*g_StreamIsRGB24 == 1) {
        width = 480;
        bitsPerPixel = 24;
    } else {
        width = 320;
        bitsPerPixel = 16;
    }

    env->rect[0] = (RECT){
        .x = x0,
        .y = y0,
        .w = width,
        .h = 240,
    };
    env->rect[1] = (RECT){
        .x = x1,
        .y = y1,
        .w = width,
        .h = 240,
    };
    env->slice = (RECT){
        .x = x0,
        .y = y0,
        .w = bitsPerPixel,
        .h = 240,
    };
}

void func_801B9C18(void* unused, void (*callback)()) {
    const int START_FRAME = 1;

    s32* s0 = g_StreamRewindSwitch;
    DecDCTReset(0);
    *s0 = 0;
    DecDCToutCallback(callback);
    StSetRing(
        (u_long*)&((StreamControl*)((u8*)s0 - 0x10))->frameBuffer.ring[0], 40);
    StSetStream(*g_StreamIsRGB24, START_FRAME, -1, NULL, NULL);
}

// Play the selected stream, fading audio on skip and retrying after disc
// errors.
void func_801B9C80(void) {
    s32 state;
    // !FAKE: The empty barrier preserves the original argument scheduling.
    register DECENV* decoderEnv __asm__("$4");
    register s32 decoderX __asm__("$5");
    register s32 decoderY __asm__("$6");
    u8 status[8];
    s32 errorOne;
    s32* errorBuffer;
    s32 one;
    s32* buffer;

    s32 frameWidth;
    DISPENV* display;
    StreamInfo* stream;
    CdlLOC* location;
    s16 volume;
    s32 skip;

    skip = 0;
    if (D_8003C728 == 0) {
        return;
    }
restart:
    volume = 127;
    GsClearVcount();
    decoderEnv = &g_StreamEnv.dec;
    decoderX = 0;
    decoderY = 0;
    __asm__ volatile("" : : "r"(decoderEnv), "r"(decoderX), "r"(decoderY));
    stream = g_Streams[g_CurrentStream];
    *g_StreamEndFrame = (s16)stream->frameCount;
    D_801BD03C = (*g_StreamIsRGB24 = (s16)stream->isRGB24) | 2;
    func_801B9B7C(decoderEnv, decoderX, decoderY, 0, 256);
    location = &((StreamControl*)g_StreamEndFrame)->location;
    CdIntToPos(stream->cdOffset, location);
    SsSetSerialVol(0, 127, 127);
    SsSetSerialAttr(0, 0, 1);
    func_801B9924();
    DrawSync(0);
    func_801B9C18(location, func_801B99E4);
    D_801BC340 = 0;
    D_801BC348 = 0;
    CdControlF(CdlSeekL, (u8*)location);
    VSync(0);
    if (StreamDiskIsReady()) {
        goto discError;
    }
    do {
        while (!CdControl(CdlSetloc, (u8*)&D_801BD040, NULL)) {
        }
        if (StreamDiskIsReady()) {
            goto discError;
        }
        if (++D_801BC348 > 32) {
            D_8003C728 = 3;
            goto discError;
        retryPlayback:
            func_801B9924();
            D_8003C728 = 1;
            goto restart;
        }
    } while (!CdRead2(0x1C0));
    StreamNextVlc(&g_StreamEnv.dec);
    one = 1;
    buffer = (s32*)&g_StreamImageBuffer;
    display = (DISPENV*)&g_StreamEnv.disp;
    while (true) {
        GsClearVcount();
        DecDCTin(g_StreamEnv.dec.vlcbuf[g_StreamEnv.dec.vlcid], D_801BD03C);
        DecDCTout(g_StreamEnv.dec.imgbuf[g_StreamEnv.dec.imgid],
                  g_StreamEnv.dec.slice.w * g_StreamEnv.dec.slice.h / 2);
        StreamNextVlc(&g_StreamEnv.dec);
        func_801B994C(&g_StreamEnv.dec, 0);
        VSync(0);
        if (skip) {
            volume -= 32;
            if (volume <= 0) {
                volume = 0;
                SsSetSerialVol(0, 0, 0);
                SsSetSerialAttr(0, 0, 0);
                *g_StreamRewindSwitch = one;
            }
            SsSetSerialVol(0, volume, volume);
        }
        *buffer = ((DECENV*)&g_StreamEnv)->rectid == 0;
        SetDefDispEnv(
            (DISPENV*)display, g_StreamEnv.dec.rect[*buffer].x,
            g_StreamEnv.dec.rect[*buffer].y, g_StreamEnv.dec.rect[*buffer].w,
            g_StreamEnv.dec.rect[*buffer].h);
        SetDefDrawEnv(
            &g_StreamEnv.draw, g_StreamEnv.dec.rect[*buffer].x,
            g_StreamEnv.dec.rect[*buffer].y, g_StreamEnv.dec.rect[*buffer].w,
            g_StreamEnv.dec.rect[*buffer].h);
        if (((StreamControl*)((u8*)buffer - 0x14))->isRGB24[0] == one) {
            frameWidth = display->disp.w * 2 / 3;
            ((volatile StreamEnv*)&g_StreamEnv)->disp.isrgb24 = one;
            display->disp.w = frameWidth;
        }
        PutDispEnv((DISPENV*)display);
        PutDrawEnv(&g_StreamEnv.draw);
        SetDispMask(1);
        if (StreamDiskIsReady()) {
            goto discError;
        }
        if (((StreamControl*)((u8*)buffer - 0x14))->rewind[0] == one) {
            break;
        }
        if (PadRead(1) & (PAD_START | PAD_CROSS)) {
            skip = 1;
        }
    }
    D_8003C728 = 0;
    if (StreamDiskIsReady()) {
        LOBU(D_8006C384.x) = 1;
        goto discError;
    }
    CdControlF(CdlPause, NULL);
    D_801BC348 = 0;
    DecDCToutCallback(NULL);
    StSetStream(1, -1, -1, NULL, NULL);
    StUnSetRing();
    func_801B18F4();
    DrawSync(0);
    func_801B19F4();
    PutDispEnv(&g_CurrentBuffer->disp);
    PutDrawEnv(&g_CurrentBuffer->draw);
    VSync(0);
    VSync(0);
    return;

discError:
    DecDCToutCallback(NULL);
    StSetStream(1, -1, -1, NULL, NULL);
    StClearRing();
    StUnSetRing();
    g_StreamEnv.rect.x = 480;
    g_StreamEnv.rect.y = 0;
    g_StreamEnv.rect.w = 480;
    D_801BC34C = 0;
    g_StreamEnv.rect.h = 240;
    MoveImage(&g_StreamEnv.dec.rect[g_StreamImageBuffer.index], 480, 0);
    DrawSync(0);
    if (D_8003C728 == 3) {
        D_801BC34C = D_8003C728;
    }
    errorOne = 1;
    errorBuffer = (s32*)&g_StreamImageBuffer;
    display = (DISPENV*)&g_StreamEnv.disp;
    while (true) {
        g_StreamEnv.unkFC++;
        state = D_801BC34C;
        if (state == errorOne) {
            goto retryState1;
        }
        if (state < 2) {
            if (state == 0) {
                goto retryState0;
            }
        } else {
            if (state == 2) {
                goto retryState2;
            }
        }
        goto retryStateDone;
    retryState0:
        CdControl(CdlNop, NULL, status);
        if (!(status[0] & CdlStatShellOpen)) {
            CdControlF(CdlGetTN, NULL);
            D_801BC34C++;
        }
        goto retryStateDone;
    retryState1:
        if ((CdSync(1, status) ^ CdlComplete) == 0) {
            D_801BC34C++;
        }
        if (!(status[0] & CdlStatStandby)) {
            D_801BC34C = 0;
        }
        if (status[0] & CdlStatShellOpen) {
            D_801BC34C = 0;
        }
        goto retryStateDone;
    retryState2:
        CdControl(CdlNop, NULL, status);
        if (status[0] & CdlStatShellOpen) {
            D_801BC34C = 0;
        }
    retryStateDone:
        VSync(0);
        if ((PadRead(1) & PAD_START) && (D_801BC34C >= 2)) {
            goto retryPlayback;
        }
        *errorBuffer = (*errorBuffer + 1) & 1;
        SetDefDispEnv((DISPENV*)display, g_StreamEnv.dec.rect[*errorBuffer].x,
                      g_StreamEnv.dec.rect[*errorBuffer].y,
                      g_StreamEnv.dec.rect[*errorBuffer].w,
                      g_StreamEnv.dec.rect[*errorBuffer].h);
        SetDefDrawEnv(
            &g_StreamEnv.draw, g_StreamEnv.dec.rect[(*errorBuffer + 1) & 1].x,
            g_StreamEnv.dec.rect[(*errorBuffer + 1) & 1].y,
            g_StreamEnv.dec.rect[(*errorBuffer + 1) & 1].w,
            g_StreamEnv.dec.rect[(*errorBuffer + 1) & 1].h);
        if (((StreamControl*)((u8*)errorBuffer - 0x14))->isRGB24[0] ==
            errorOne) {
            frameWidth = display->disp.w * 2 / 3;
            ((volatile StreamEnv*)&g_StreamEnv)->disp.isrgb24 = errorOne;
            display->disp.w = frameWidth;
        }
        PutDispEnv((DISPENV*)display);
        PutDrawEnv(&g_StreamEnv.draw);
        SetDispMask(1);
        MoveImage(&((StreamEnv*)((u8*)display - 0x38))->rect,
                  g_StreamEnv.dec.rect[(*errorBuffer + 1) & 1].x,
                  g_StreamEnv.dec.rect[(*errorBuffer + 1) & 1].y);
    }
}
