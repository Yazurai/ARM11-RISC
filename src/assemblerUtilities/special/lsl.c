#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "../encodingFunctions.h"
#include "../assemblerUtilities.h"
#include "../../assemble.h"
#include "../../database/masks.h"

void lsl(FILE *writeFile, char *args) {
    //Extract the arguments of the instruction
    char *rn = strtok(args, " r,");
    uint8_t rnV = strtol(rn, NULL, 0);
    char *expression = strtok(NULL, "#");
    uint8_t expressionV = strtol(expression, NULL, 0);

    //Hard code move lsl
    uint32_t encoded = 0;
    encoded |= LSL_MASK;
    encoded |= expressionV << SR_MASK_AMOUNT_OFFSET;
    encoded |= rnV;

    //Write the instruction to the binary file
    write(writeFile, encoded);
}

