// SPDX-License-Identifier: AGPL-3.0-or-later
#ifndef SEL_STREAM_H
#define SEL_STREAM_H

#include <game.h>

typedef struct {
    s32 index; // Displayed rectangle, followed by the 40-sector CD ring.
    u32 ring[0x5000];
} StreamBuffer;

typedef struct {
    /* 0x00 */ u32 endFrame[1];
    /* 0x04 */ u32 isRGB24[1];
    /* 0x08 */ u32 flags;
    /* 0x0C */ CdlLOC location;
    /* 0x10 */ s32 rewind[1];
    /* 0x14 */ StreamBuffer frameBuffer;
} StreamControl;

#endif
