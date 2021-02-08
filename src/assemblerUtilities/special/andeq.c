#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include <stdint.h>
#include "../assemblerUtilities.h"

void andeq(FILE *writeFile) {
    //Write an all 0 instruction to the binary file
    write(writeFile, 0);
}

