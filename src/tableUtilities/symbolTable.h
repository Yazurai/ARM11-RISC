#ifndef ARM11_06_SYMBOLTABLE_H
#define ARM11_06_SYMBOLTABLE_H

#include <stdbool.h>
#include <stdint.h>

struct symbolTableStruct {
    struct symbolTableElem *first;
    struct symbolTableElem *last;
    uint16_t length;
};

uint32_t getSize(struct symbolTableStruct *ptr);

void tableInit(struct symbolTableStruct *ptr);

void tableAdd(struct symbolTableStruct *ptr, char *key, uint32_t value);

uint32_t *tableLookup(struct symbolTableStruct *ptr, char *key);

void clear(struct symbolTableStruct *ptr);

#endif //ARM11_06_SYMBOLTABLE_H
