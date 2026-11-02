// SPDX-License-Identifier: AGPL-3.0-or-later
#ifndef PC_SAVES_H
#define PC_SAVES_H
#include <stdbool.h>
void PcSaveNewGame(void);
bool PcSaveCommit(void);
bool PcSaveContinue(void);
unsigned PcSaveClearFlags(void);
#endif
