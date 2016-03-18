#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "memory.h"

void memory_add(memory_t * self, int memSize, char * memory)
 {
     self->mem = (char *)malloc(memSize);
     memcpy((char *)self->mem, memory, memSize);
     self->memSize = memSize;
 }

void memory_delete(memory_t * self)
{
    free(self->mem);
    self->memSize = 0;
}

void memory_set(memory_t * self, int memSize, char * memory, int memCount)
{
    free(self->mem);
    memcpy((char *)self->mem, memory, memSize);
    self->memSize = memSize;
}

void memory_get(memory_t * self, int memSize, char * memory)
{
     memcpy((char *)memory, self->mem, memSize);
}

int memory_getSize(memory_t * self)
{
    return self->memSize;
}






