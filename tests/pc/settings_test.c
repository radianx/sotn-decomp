// SPDX-License-Identifier: AGPL-3.0-or-later
#ifdef NDEBUG
#undef NDEBUG
#endif
#include "upgrades.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>
int main(void) {
    FILE* owned = fopen("pc_settings_test.ini", "wx");
    assert(owned && !fclose(owned));
    PcSettings original, loaded;
    PcSettingsDefaults(&original);
    assert(!original.reduceFlashes && !original.palette);
    assert(!original.videoFilter && original.filterStrength == 75);
    original.reduceFlashes = 1;
    original.palette = 2;
    original.keys[6] = 44;
    original.buttons[6] = 3;
    original.effectsVolume = 37;
    original.videoFilter = 3;
    original.filterStrength = 85;
    strcpy(original.contentPack, "packs/test");
    assert(PcSettingsSave(&original, "pc_settings_test.ini"));
    PcSettingsDefaults(&loaded);
    assert(PcSettingsLoad(&loaded, "pc_settings_test.ini"));
    assert(!memcmp(&original, &loaded, sizeof(original)));
    const char* invalidFilters[] = {
        "videoFilter=4\n", "videoFilter=-1\n", "filterStrength=101\n",
        "filterStrength=-1\n"};
    for (unsigned i = 0; i < sizeof(invalidFilters) / sizeof(*invalidFilters);
         i++) {
        FILE* invalid = fopen("pc_settings_test.ini", "w");
        assert(invalid);
        fputs(invalidFilters[i], invalid);
        fclose(invalid);
        assert(!PcSettingsLoad(&loaded, "pc_settings_test.ini"));
        assert(!memcmp(&original, &loaded, sizeof(original)));
    }
    FILE* f = fopen("pc_settings_test.ini", "w");
    assert(f);
    fputs("reduceFlashes=0\nmasterVolume=101\n", f);
    fclose(f);
    assert(!PcSettingsLoad(&loaded, "pc_settings_test.ini"));
    assert(!memcmp(&original, &loaded, sizeof(original)));
    assert(remove("pc_settings_test.ini") == 0);
    puts("Settings round trip and invalid-file rollback: PASS");
    return 0;
}
