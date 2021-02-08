#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include "database/messages.h"
#include "emulatorUtilities/initialize.h"
#include "database/masks.h"
#include "database/mnemonics.h"
#include "emulate.h"
#include "emulatorUtilities/emulatorUtilities.h"
#include "emulatorUtilities/instructions/emulatorInstructions.h"

uint8_t *ram;
uint32_t gRegisters[NO_OF_REGISTERS] = {0}; //general purpose registers, 4 bytes/register
bool nFlag = false, zFlag = false, cFlag = false, vFlag = false; //top 4 bits of CPSR

bool hasFetched = false; //hasFetched holds whether there's already a fetched instruction and fetchedInstr holds that
uint32_t fetchedInstr = 0;

bool hasDecoded = false; //hasDecoded holds whether there's already a decoded instruction and decodedInstr holds that
uint32_t decodedInstr = 0;
enum mnemonic decodedCode = INVALID;

//The fetch-decode-execute pipeline
bool executeCycle(void) {
    //If there's already a decoded instruction, then execute it
    //Maybe use a function pointer
    if (hasDecoded == 1) {
        switch (decodedCode) {
            case DATAPROCESS:
                dataProcessing();
                break;
            case MULTIPLY:
                multiply();
                break;
            case DATATRANSFER:
                dataTransfer();
                break;
            case BRANCH:
                branch();
                break;
            case ANDEQ:
                finish();
                break;
            default:
                printf(MSG_ERR_INVALID_INSTRUCTION, decodedInstr);
                return false;
        }
    }

    //If there's already a fetched instruction, then decode it (set the appropriate code and copy the instruction) (set the decoded to "true")
    if (hasFetched == 1) {
        decodedInstr = fetchedInstr;
        decodedCode = INVALID;

        decodedCode = ((fetchedInstr & DP_MASK) == 0) ? DATAPROCESS : decodedCode;
        decodedCode = ((fetchedInstr & M_MASK) == M_MASK) ? MULTIPLY : decodedCode;
        decodedCode = ((fetchedInstr & DT_MASK) == DT_MASK) ? DATATRANSFER : decodedCode;
        decodedCode = ((fetchedInstr & B_MASK) == B_MASK) ? BRANCH : decodedCode;
        decodedCode = (fetchedInstr == 0) ? ANDEQ : decodedCode;

        hasDecoded = true;
    }

    //Fetch the next instruction and store it (set the fetched to "true")
    fetchedInstr = getMemoryWord((uint16_t) PC, true);
    hasFetched = true;

    //Increment PC(1 instruction = 4 bytes)
    PC += 4;

    return 0;
}

int main(int argc, char **argv) {
    ram = calloc(MEMORY_SIZE, sizeof(uint8_t));
    if (ram == NULL) {
        printf(MSG_ERR_NOT_ENOUGH_MEMORY);
    }
    if (argc < 2) {
        printf(MSG_ERR_NOT_ENOUGH_ARG);
        return EXIT_SUCCESS;
    }

    copy(ram, argv[1]);

    //Start the fetch-decode-execute cycle until it should stop
    while (!canFinish) {
        executeCycle();
    }

    free(ram);

    return 0;
}
