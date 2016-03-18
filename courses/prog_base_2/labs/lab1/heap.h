#ifndef HEAP_H_INCLUDED
#define HEAP_H_INCLUDED

#include "memory.h"

typedef struct heap_s heap_t;

typedef enum
{
    HEAP_FULL,
    HEAP_EMPTY,
    ERROR
} heap_status_t;

heap_t * heap_new();
void heap_delete(heap_t * self);

heap_status_t heap_memAdd(heap_t * hp, int memSize, char * memory);
heap_status_t heap_memDelete(heap_t * hp, int memCount);
heap_status_t heap_memGet(heap_t * hp, int memSize, char * memory, int memCount);
int heap_memGetSize(heap_t * hp, int memCount);

int heap_getCount(heap_t * hp);

int heap_getNum(heap_t * hp);

#endif // HEAP_H_INCLUDED
