#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "tableUtilities/symbolTable.h"
#include "database/messages.h"
#include "assemblerUtilities/assemblerUtilities.h"

uint32_t pc = 8; //Used to store the pc value (starts from offset 8 bytes due to the pipeline)
struct symbolTableStruct symbolTable; //This holds a mapping from the labels to their respective address

uint32_t constantAddress = 0; //Holds the base address at which the constants will be concated
uint32_t constantList[500] = {0}; //Holds the list of constants to be added at the end of the binary file
uint32_t constantCount = 0; //Holds the size of said array

int main(int argc, char **argv) {
    if (argc < 2) {
        printf(MSG_ERR_NOT_ENOUGH_ARG);
        return EXIT_FAILURE;
    }

    FILE *readFile;
    char readFileName[25];
    strcpy(readFileName, argv[1]);
    strcat(readFileName, ".s");
    readFile = fopen(readFileName, "r");
    if (readFile == NULL) {
        printf(MSG_ERR_FOPEN);
        return EXIT_FAILURE;
    }

    FILE *writeFile;
    char writeFileName[25];
    strcpy(writeFileName, argv[1]);
    writeFile = fopen(writeFileName, "wb");
    if (writeFile == NULL) {
        printf(MSG_ERR_FOPEN);
        return EXIT_FAILURE;
    }

    tableInit(&symbolTable); //We initialize and allocate memory for the label map table

    passThrough(readFile, writeFile, true); //First pass through

    if (!fseek(readFile, 0, SEEK_SET) == 0) { //reset
        printf(MSG_ERR_FILE_READ);
    }

    passThrough(readFile, writeFile, false); //Second pass through

    //Add the constants to the end of the binary file
    for (uint16_t j = 0; j < constantCount; j++) {
        write(writeFile, constantList[j]);
    }

    //Cleanup the streams and allocated memory
    clear(&symbolTable);
    fclose(readFile);
    fclose(writeFile);
    return EXIT_SUCCESS;
}
