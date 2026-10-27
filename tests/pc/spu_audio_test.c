// SPDX-License-Identifier: AGPL-3.0-or-later
#ifdef NDEBUG
#undef NDEBUG
#endif
#include <assert.h>
#include <libspu.h>
#include <psyz.h>
#include <stdio.h>
#include <string.h>

static void CheckVoices(unsigned char flags, int ended) {
    unsigned char block[16];
    short samples[512 * 2];
    char status[24];
    memset(block, 0x11, sizeof(block));
    block[0] = 0;
    block[1] = flags;
    Psyz_SpuMemWrite(0x1000, block, sizeof(block));
    for (int i = 0; i < 24; i++) {
        unsigned reg = i * 16;
        Psyz_SpuWrite(reg, 0x1000);
        Psyz_SpuWrite(reg + 2, 0x1000);
        Psyz_SpuWrite(reg + 4, 0x1000);
        Psyz_SpuWrite(reg + 6, 0x200);
        Psyz_SpuWrite(reg + 8, 0x00FF);
        Psyz_SpuWrite(reg + 10, 0);
        Psyz_SpuWrite(reg + 14, 0x200);
    }
    SpuSetKey(SPU_ON, 0xFFFFFF);
    Psyz_SpuPullSamples(samples, 512);
    if (ended) {
        SpuSetKey(SPU_OFF, 0xFFFFFF);
    }
    SpuGetAllKeysStatus(status);
    for (int i = 0; i < 24; i++) {
        if (ended) {
            assert(Psyz_SpuRead(i * 16 + 12) == 0);
            assert(status[i] == SPU_OFF);
        } else {
            assert(Psyz_SpuRead(i * 16 + 12) > 0);
            assert(status[i] == SPU_ON);
        }
    }
}

int main(void) {
    Psyz_SpuInit();
    Psyz_SpuWrite(0x1AA, 0xC000);
    CheckVoices(1, 1);
    CheckVoices(3, 0);
    short mixed[512 * 2];
    Psyz_SpuWrite(0x180, 0x3FFF);
    Psyz_SpuWrite(0x182, 0x3FFF);
    Psyz_SpuSetMixVolume(0, 100);
    Psyz_SpuPullSamples(mixed, 512);
    for (unsigned i = 0; i < 1024; i++)
        assert(mixed[i] == 0);
    Psyz_SpuSetMixVolume(100, 100);
    Psyz_SpuPullSamples(mixed, 512);
    int audible = 0;
    for (unsigned i = 0; i < 1024; i++)
        audible |= mixed[i] != 0;
    assert(audible);
    CheckVoices(1, 1);
    puts(
        "Finished samples release all 24 voices; looping voices survive: PASS");
    return 0;
}
