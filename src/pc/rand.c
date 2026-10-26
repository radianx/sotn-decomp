// SPDX-License-Identifier: AGPL-3.0-or-later
#include <stdint.h>

// PS1 BIOS A(2Fh)/A(30h); host libc sequences differ between platforms.
// https://psx-spx.consoledev.net/biosfunctions/#bios-misc-functions
static uint32_t s_RandomSeed = 1;

void srand(unsigned int seed) { s_RandomSeed = seed; }

int rand(void) {
    s_RandomSeed = s_RandomSeed * UINT32_C(0x41C64E6D) + 0x3039;
    return (s_RandomSeed >> 16) & 0x7FFF;
}
