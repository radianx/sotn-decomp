// SPDX-License-Identifier: AGPL-3.0-or-later
#include "pc.h"
#include <stdint.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

static uint32_t Read32(const unsigned char* p) {
    return p[0] | (uint32_t)p[1] << 8 | (uint32_t)p[2] << 16 |
           (uint32_t)p[3] << 24;
}

static bool ReadSector(FILE* f, uint32_t sector, unsigned char* data) {
    uint64_t offset = (uint64_t)sector * 2352 + 24;
    return offset <= LONG_MAX && !fseek(f, (long)offset, SEEK_SET) &&
           fread(data, 1, 2048, f) == 2048;
}

bool PcValidateDisc(const char* cuePath) {
    char line[1024], track[512] = "", full[1024];
    FILE* cue = fopen(cuePath, "r");
    if (!cue) {
        ERRORF("Cannot open disc CUE: %s", cuePath);
        return false;
    }
    bool mode2 = false;
    while (fgets(line, sizeof(line), cue)) {
        char* p = line;
        while (isspace((unsigned char)*p))
            p++;
        if (sscanf(p, "FILE \"%511[^\"]\" BINARY", track) == 1)
            continue;
        if (strstr(p, "TRACK 01 MODE2/2352")) {
            mode2 = true;
            break;
        }
    }
    fclose(cue);
    if (!mode2 || !track[0]) {
        ERRORF("Expected a US SotN CUE with TRACK 01 MODE2/2352");
        return false;
    }
    const char* slash = strrchr(cuePath, '/');
    const char* backslash = strrchr(cuePath, '\\');
    if (backslash && (!slash || backslash > slash))
        slash = backslash;
    int prefix = slash ? (int)(slash - cuePath + 1) : 0;
    int n =
        track[0] == '/' || (strlen(track) > 1 && track[1] == ':')
            ? snprintf(full, sizeof(full), "%s", track)
            : snprintf(full, sizeof(full), "%.*s%s", prefix, cuePath, track);
    if (n < 0 || n >= sizeof(full))
        return false;
    FILE* bin = fopen(full, "rb");
    if (!bin) {
        ERRORF("Disc track is missing: %s", full);
        return false;
    }
    unsigned char sector[2048];
    bool valid = false, found = false;
    if (!ReadSector(bin, 16, sector) || sector[0] != 1 ||
        memcmp(sector + 1, "CD001", 5) || sector[6] != 1 || sector[156] < 34) {
        ERRORF("Disc has no valid ISO9660 primary descriptor");
        goto cleanup;
    }
    uint32_t root = Read32(sector + 158), size = Read32(sector + 166);
    if (!size || size > 1024 * 1024)
        goto cleanup;
    for (uint32_t offset = 0; offset < size; offset += 2048) {
        if (root > UINT32_MAX - offset / 2048 ||
            !ReadSector(bin, root + offset / 2048, sector))
            goto cleanup;
        for (unsigned pos = 0; pos < 2048 && offset + pos < size;) {
            unsigned length = sector[pos];
            if (!length)
                break;
            if (length < 34 || pos + length > 2048)
                goto cleanup;
            unsigned nameLength = sector[pos + 32];
            if (33 + nameLength > length)
                goto cleanup;
            if (nameLength == 13 &&
                !memcmp(sector + pos + 33, "SLUS_000.67;1", 13))
                found = true;
            pos += length;
        }
    }
    valid = found;
    if (!valid)
        ERRORF("This port requires the US disc (SLUS_000.67); wrong region or "
               "game");
cleanup:
    fclose(bin);
    return valid;
}
