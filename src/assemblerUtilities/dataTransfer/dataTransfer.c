#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "../encodingFunctions.h"
#include "../assemblerUtilities.h"
#include "../../database/mnemonics.h"
#include "../../assemble.h"
#include "../../database/masks.h"

void transfer(FILE *writeFile, char *args, enum mnemonic transferType) {
    uint8_t type = 4; // 0: expression, 1: preindexed offseted 2: preindexed 3: postindexed offseted
    bool shouldWrite = true; //This holds whether we need to write the encoded : we dont when we use mov

    //extract the arguments from the instruction
    char *rd = strtok(args, " r,");
    uint8_t rdV = strtol(rd, NULL, 0);

    char *scndArg = strtok(NULL, " ,");
    char *thrdArg = strtok(NULL, " ,#]");

    if (scndArg[0] == '=' && transferType == LDR) { //check if it starts with an '=' -> it's an expression
        type = 0;
    } else {
        if (scndArg[strlen(scndArg) - 1] == ']') { //check if there's only a register
            if (thrdArg == NULL) { //check if there's a third argument, if not then it's only a register
                type = 2;
            } else {
                type = 3;
            }
        } else { //if there's no bracket it means there's an expression
            type = 1;
        }
    }

    uint32_t encoded = 0; //Holds the final binary instruction in an uint32
    char *constant; //The constant of the expression - text format
    int32_t constantV = 0; //The constant of the expression - number format

    uint32_t rnV = 0;
    int32_t offsetV = 0;
    bool pBit = false;

    switch (type) {
        case 0: //Expression
            constant = strtok(scndArg, "="); //Read in the constant
            constantV = strtol(constant, NULL, 0);
            if (constantV < 0xff) { //If constant is less than 0xff then mov can be used
                char movLine[512] = ""; //Use string concatenation to build up the arguments for mov

                strcat(movLine, "r");
                strcat(movLine, rd);
                strcat(movLine, ", #");
                strcat(movLine, constant);

                comparingMov(writeFile, movLine, MOV); //final format: "r0, #expression"
                shouldWrite = false;
            } else { //Otherwise store the constant and put the offset in the encoded binary instruction
                constantList[constantCount] = constantV; //Store the constant in the constantList global array
                uint32_t constAdd = constantAddress + constantCount * 4; //Calculate the address of the 4 byte word
                constantCount++;

                rnV = 15;
                offsetV = constAdd - pc;
                pBit = true;
            }
            break;
        case 2: //preindexed
            rnV = strtol(strtok(scndArg, "[r]"), NULL, 0);
            offsetV = 0;
            pBit = true;
            //encoded |= 0x1 << DT_MASK_IMM_OFFSET; //imm code
            break;
        case 1: //preindexed offseted
            rnV = strtol(strtok(scndArg, "[r"), NULL, 0);
            if (thrdArg[0] == 'r') {
                offsetV = strtol(strtok(thrdArg, "r"), NULL, 0);
                encoded |= 0x1 << DT_MASK_IMM_OFFSET; //imm code
            } else {
                offsetV = strtol(thrdArg, NULL, 0);
            }
            pBit = true;
            break;
        case 3: //postindexed offseted
            rnV = strtol(strtok(scndArg, "[r]"), NULL, 0);
            if (thrdArg[0] == 'r') {
                offsetV = strtol(strtok(thrdArg, "r"), NULL, 0);
                encoded |= 0x1 << DT_MASK_IMM_OFFSET; //imm code
            } else {
                offsetV = strtol(thrdArg, NULL, 0);
            }
            pBit = false;
            break;
    }

    //Build up the rest of the universal encoded instruction
    encoded |= 0xe << COND_OFFSET; //condition
    encoded |= DT_MASK; //01 code
    if (offsetV >= 0) {
        encoded |= 0x1 << DT_MASK_UP_OFFSET; //up bit
    } else {
        offsetV = offsetV * -1;
    }
    if (transferType == LDR) {
        encoded |= 0x1 << DT_MASK_LS_OFFSET; //l bit
    }
    encoded |= rdV << DT_MASK_RD_OFFSET; //rd
    encoded |= rnV << DT_MASK_RN_OFFSET; //rn
    encoded |= offsetV; //offset
    encoded |= pBit << DT_MASK_INDEXING_OFFSET; //p bit

    //Store the binary instruction in the binary file
    if (shouldWrite) {
        write(writeFile, encoded);
    }
}
