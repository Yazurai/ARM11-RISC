#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>
#include "symbolTable.h"
#include "../database/messages.h"

struct symbolTableElem {
    char *key;
    uint32_t value;
    struct symbolTableElem *prev;
    struct symbolTableElem *next;
};

uint32_t getSize(struct symbolTableStruct *ptr) {
    return ptr->length;
}

struct symbolTableElem *allocElem() {
    struct symbolTableElem *elem = malloc(sizeof(struct symbolTableElem));
    if (elem == NULL) {
        printf(MSG_ERR_MEMORY_ALLOCATION_NO_DETAIL);
        exit(EXIT_FAILURE);
    }
    elem->key = NULL;
    elem->prev = NULL;
    elem->next = NULL;
    return elem;
}

void tableInit(struct symbolTableStruct *ptr) {
    ptr->length = 0;

    ptr->first = allocElem();
    ptr->last = allocElem();
    ptr->first->key = malloc(sizeof(char));
    ptr->last->key = malloc(sizeof(char));

    ptr->first->prev = NULL;
    ptr->first->next = ptr->last;
    ptr->last->prev = ptr->first;
    ptr->last->next = NULL;
}

void tableAdd(struct symbolTableStruct *ptr, char *key, uint32_t value) {
    struct symbolTableElem *elem = allocElem();
    elem->key = malloc(sizeof(*key));
    strcpy(elem->key, key);
    elem->value = value;

    ptr->last->prev->next = elem;
    elem->prev = ptr->last->prev;

    elem->next = ptr->last;
    ptr->last->prev = elem;

    ptr->length++;
}

uint32_t *tableLookup(struct symbolTableStruct *ptr, char *key) {
    struct symbolTableElem *elem = ptr->first->next;
    while (elem != ptr->last) {
        if (strcmp(elem->key, key) == 0) {
            return &(elem->value);
        }
        elem = elem->next;
    }
    return NULL;
}

void clear(struct symbolTableStruct *ptr) {
    struct symbolTableElem *elem = ptr->first;
    struct symbolTableElem *next;
    do {
        next = elem->next;
        free(elem);
        elem = next;
    } while (elem != ptr->last);
}

