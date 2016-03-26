#ifndef MEMORY_H_INCLUDED
#define MEMORY_H_INCLUDED

typedef struct memory_s memory_t;

typedef enum
{
    MEM_OK,
    MEM_FULL,
    MEM_EMPTY,
    MEM_ERROR
} mem_status_t;

mem_status_t memory_setChar(memory_t * memPoint, int memSize, char * memory);
mem_status_t memory_setInt(memory_t * memPoint, int memSize, int * memory);
mem_status_t memory_getChar(memory_t * memPoint, int memSize, char * memory);
mem_status_t memory_getInt(memory_t * memPoint, int memSize, int * memory);

int memory_getSize(memory_t * memPoint);

#endif // MEMORY_H_INCLUDED
