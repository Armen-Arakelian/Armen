#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "heap.h"

static struct memory_s
{
    void * mem;
    int memSize;
};

mem_status_t memory_setChar(memory_t * memPoint, int memSize, char * memory)
{
    memPoint->mem = malloc(memSize);
    memcpy((char *)memPoint->mem, memory, memSize);
    memPoint->memSize = memSize;
    return MEM_OK;
}

mem_status_t memory_setInt(memory_t * memPoint, int memSize, int * memory)
{
    memPoint->mem = malloc(memSize);
    memcpy((int *)memPoint->mem, memory, memSize);
    memPoint->memSize = memSize;
    return MEM_OK;
}


mem_status_t memory_getChar(memory_t * memPoint, int memSize, char * memory)
{
    memcpy(memory, (char *)memPoint->mem, memSize);
    return HEAP_OK;
}

mem_status_t memory_getInt(memory_t * memPoint, int memSize, int * memory)
{
    memcpy(memory, (int *)memPoint->mem, memSize);
    return HEAP_OK;
}

int memory_getSize(memory_t * memPoint)
{
    return memPoint->memSize;
}

int memory_getStrSize()
{
    return sizeof(struct memory_s);
}





