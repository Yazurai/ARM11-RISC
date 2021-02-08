#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "../emulate.h"
#include "../database/messages.h"
#include "initialize.h"

bool copy(uint8_t *ram, char *file_name) {
    FILE *bin;
    bin = fopen(file_name, "rb");
    if (bin == NULL) {
        printf(MSG_ERR_FOPEN);
    }
    fseek(bin, 0, SEEK_END);
    uint32_t size = ftell(bin);
    if (size > MEMORY_SIZE) {
        printf(MSG_ERR_FILE_EX_MEMORY, MEMORY_SIZE, size);
        return false;
    }
    fseek(bin, 0, SEEK_SET);
    size_t read = fread(ram, 1, size, bin);
    if (ferror(bin)) {
        printf(MSG_ERR_FILE_READ);
        fclose(bin);
        return false;
    }
    fclose(bin);
    return true;
}
