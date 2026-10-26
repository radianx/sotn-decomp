// SPDX-License-Identifier: AGPL-3.0-or-later
#ifdef NDEBUG
#undef NDEBUG
#endif
#include <assert.h>
#include <libcd.h>
#include <psyz.h>
#include <stdio.h>
#include <string.h>

static void WriteDisc(void) {
    unsigned char sector[2352];
    FILE* bin = fopen("pc_cd_audio_test.bin", "wbx");
    assert(bin);
    for (int i = 0; i < 64; i++) {
        memset(sector, 0, sizeof(sector));
        memset(sector + 1, 0xFF, 10);
        sector[15] = 2;
        sector[16] = (i == 0 || i == 48) ? 1 : 2;
        sector[17] = 0;
        sector[18] = 0x64;
        sector[19] = 1;
        memcpy(sector + 20, sector + 16, 4);
        for (int b = 0; b < 18; b++) {
            memset(sector + 24 + b * 128 + 16, 0x11, 112);
        }
        assert(fwrite(sector, 1, sizeof(sector), bin) == sizeof(sector));
    }
    assert(fclose(bin) == 0);
    FILE* cue = fopen("pc_cd_audio_test.cue", "wx");
    assert(cue);
    assert(fputs("FILE \"pc_cd_audio_test.bin\" BINARY\n"
                 " TRACK 01 MODE2/2352\n INDEX 01 00:00:00\n", cue) >= 0);
    assert(fclose(cue) == 0);
}

static void CheckGap(int doubleSpeed) {
    short samples[8192 * 2] = {0};
    short later[24000 * 2];
    unsigned char mode = CdlModeRT | CdlModeSF;
    unsigned char filter[] = {1, 0};
    unsigned char result[8];
    CdlLOC start;
    if (doubleSpeed) {
        mode |= CdlModeSpeed;
    }
    CdControlB(CdlSetmode, &mode, NULL);
    Psyz_AudioPause();
    CdControlB(CdlSetfilter, filter, NULL);
    CdIntToPos(0, &start);
    CdControlB(CdlSetloc, (unsigned char*)&start, NULL);
    CdControlB(CdlReadN, NULL, NULL);
    assert(Psyz_CdPullSamples(samples, 8192) == 8192);
    assert(samples[100 * 2] != 0);
    // A later clip reusing the filter must retain its physical disc timing.
    for (int i = 3000; i < 8192; i++) {
        assert(samples[i * 2] == 0);
        assert(samples[i * 2 + 1] == 0);
    }
    CdControlB(CdlGetlocL, NULL, result);
    int sector = (result[2] >> 4) * 10 + (result[2] & 15);
    assert(sector < 48);
    int remaining = 48 * (doubleSpeed ? 294 : 588) + 64 + 1 - 8192;
    assert(Psyz_CdPullSamples(later, remaining) == (size_t)remaining);
    assert(later[(remaining - 1) * 2] != 0);
    CdControlB(CdlPause, NULL, NULL);
    assert(Psyz_CdPullSamples(samples, 8192) == 0);
}

int main(void) {
    WriteDisc();
    assert(Psyz_CdSetDiskPath("pc_cd_audio_test.cue") == 0);
    Psyz_CdShellOpen(0);
    CdReset(1);
    CheckGap(1);
    CheckGap(0);
    CdControlB(CdlStop, NULL, NULL);
    Psyz_AudioDestroy();
    assert(remove("pc_cd_audio_test.bin") == 0);
    assert(remove("pc_cd_audio_test.cue") == 0);
    puts("XA clips preserve filtered-sector gaps at both drive speeds: PASS");
    return 0;
}
