#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include "../assemblerUtilities.h"
#include "../../tableutilities/symbolTable.h"
#include "../../database/mnemonics.h"
#include "../../database/masks.h"
#include "../../assemble.h"

void branch(FILE *writeFile, char *args, enum mnemonic type) {
    //Try to see if the expression is a label
    uint32_t *targetAddress = tableLookup(&symbolTable, args);

    if (targetAddress == NULL) { //If it's not a label, then use the argument as the target address directly
        *targetAddress = strtol(args, NULL, 0);
    }

    int32_t offset = *targetAddress - pc; //Calculate the offset,
    offset = 0xffffff & (offset >> 2);   //and take the 24 lower bits of the shifted part

    uint32_t encoded = 0; //Holds the final encoded instruction

    //sets up the conditional code for each type
    switch (type) {
        case B:
            encoded |= 0xe << COND_OFFSET;
            break;
        case BEQ:
            encoded |= 0x0;
            break;
        case BGE:
            encoded |= 0xa << COND_OFFSET;
            break;
        case BGT:
            encoded |= 0xc << COND_OFFSET;
            break;
        case BLE:
            encoded |= 0xd << COND_OFFSET;
            break;
        case BLT:
            encoded |= 0xb << COND_OFFSET;
            break;
        case BNE:
            encoded |= 0x1 << COND_OFFSET;
            break;
    }

    //Build up the encoded instruction from the rest of the universal parts
    encoded |= B_ENCODE_MASK; //101
    encoded |= offset; //offset

    //Write the contents to the binary file
    write(writeFile, encoded);
}

