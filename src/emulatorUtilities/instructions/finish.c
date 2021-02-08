#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include "../../database/messages.h"
#include "../../emulate.h"
#include "../../database/masks.h"
#include "emulatorInstructions.h"
#include "../emulatorUtilities.h"
#include "../initialize.h"

//This is the all zero function, which ends execution and prints out the current state
void finish(void) {
    printf("Registers:\n");
    for (int i = 0; i < 13; i++) {
        printf("$%-3i: %10d (0x%08x)\n", i, (int32_t) gRegisters[i], (int32_t) gRegisters[i]);
    }
    printf("PC  : %10d (0x%08x)\n", (int32_t) PC, (int32_t) PC);
    printf("CPSR: %10d (0x%08x)\n", getCPSR(), getCPSR());
    printf("Non-zero memory:\n");
    for (int i = 0; i < MEMORY_SIZE; i += 4) {
        int32_t word = getMemoryWord(i, false);
        if (word != 0) {
            printf("0x%08x: 0x%08x\n", i, word);
        }
    }
    canFinish = true;
}
