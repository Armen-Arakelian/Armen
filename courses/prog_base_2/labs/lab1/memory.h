#ifndef MEMORY_H_INCLUDED
#define MEMORY_H_INCLUDED

typedef struct
{
    void * mem;
    int memSize;
} memory_t;

void memory_add(memory_t * self, int memSize, char * memory);
void memory_delete(memory_t * self);
void memory_set(memory_t * self, int memSize, char * memory, int memCount);
void memory_get(memory_t * self, int memSize, char * memory);
int memory_getSize(memory_t * self);

#endif // MEMORY_H_INCLUDED
