#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include "../../database/messages.h"
#include "../../emulate.h"
#include "../../database/masks.h"
#include "emulatorInstructions.h"
#include "../emulatorUtilities.h"
#include "../initialize.h"

//Executes a branching instruction
void branch(void) {
    if (checkCond()) {
        //8 bits to achieve the right sign and 6 bits to achieve the 2 bit left shift
        int32_t offset = (0xffffff & decodedInstr) << 8;
        offset = offset >> 6;
        //Check if the offset is legal, if it is then execute it
        if (PC + offset < 0 || PC + offset >= HIGHEST_WORD_ADDRESS) {
            printf(MSG_ERR_INVALID_ADDRESS, decodedInstr);
        } else {
            PC += offset;
        }

        //reset the fetch-decode-execute pipeline
        hasDecoded = false;
        hasFetched = false;
    }
}
