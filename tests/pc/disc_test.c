// SPDX-License-Identifier: AGPL-3.0-or-later
#ifdef NDEBUG
#undef NDEBUG
#endif
#include "pc.h"
#include <assert.h>
#include <stdint.h>
#include <string.h>

static void Write32(unsigned char* p, uint32_t value) {
    for (int i = 0; i < 4; i++)
        p[i] = value >> (i * 8);
}
static void WriteDisc(const char* executable, int malformed) {
    unsigned char sectors[22][2352] = {0};
    unsigned char* pvd = sectors[16] + 24;
    pvd[0] = 1;
    memcpy(pvd + 1, "CD001", 5);
    pvd[6] = 1;
    pvd[156] = 34;
    Write32(pvd + 158, 20);
    Write32(pvd + 166, 2048);
    unsigned char* record = sectors[20] + 24;
    record[0] = 46;
    record[32] = malformed ? 255 : 13;
    memcpy(record + 33, executable, 13);
    if (malformed == 2) {
        record[32] = 13;
        record[46] = 2;
    }
    FILE* f = fopen("pc_disc_test.bin", "wb");
    assert(f);
    assert(fwrite(sectors, 1, sizeof(sectors), f) == sizeof(sectors));
    assert(!fclose(f));
}
int main(void) {
    FILE* owned = fopen("pc_disc_test.bin", "wbx");
    assert(owned && !fclose(owned));
    FILE* cue = fopen("pc_disc_test.cue", "wx");
    assert(cue);
    fputs("FILE \"pc_disc_test.bin\" BINARY\n TRACK 01 MODE2/2352\n INDEX 01 "
          "00:00:00\n",
          cue);
    fclose(cue);
    WriteDisc("SLUS_000.67;1", 0);
    assert(PcValidateDisc("pc_disc_test.cue"));
    WriteDisc("SLPM_860.23;1", 0);
    assert(!PcValidateDisc("pc_disc_test.cue"));
    WriteDisc("SLUS_000.67;1", 2);
    assert(!PcValidateDisc("pc_disc_test.cue"));
    WriteDisc("SLUS_000.67;1", 1);
    assert(!PcValidateDisc("pc_disc_test.cue"));
    assert(!remove("pc_disc_test.bin"));
    assert(!PcValidateDisc("pc_disc_test.cue"));
    assert(!remove("pc_disc_test.cue"));
    puts("Disc validation rejects wrong regions, missing tracks and malformed "
         "records: PASS");
    return 0;
}
