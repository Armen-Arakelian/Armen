#include <stdio.h>
#include <stdlib.h>

#define MAX_MEM_SIZE 100

#include "heap.h"
#include "memory.h"

static struct heap_s
{
    memory_t * memory[MAX_MEM_SIZE];
    int num;
    int count;
};

static int number = 1;

heap_t * heap_new()
{
    heap_t * hp = malloc(sizeof(struct heap_s));
    hp->count = 0;
    hp->num = number;
    number++;
    return hp;
}

void heap_delete(heap_t * self)
{
    number--;
    free(self);
}

heap_status_t heap_memAdd(heap_t * hp, int memSize, char * memory)
{
    if(hp->count == MAX_MEM_SIZE)
        return HEAP_FULL;
    hp->memory[hp->count] = malloc(sizeof(memory_t));
    memory_add(hp->memory[hp->count], memSize, memory);
    (hp->count)++;
}

heap_status_t heap_memDelete(heap_t * hp, int memCount)
{
    if(0 == hp->count)
        return HEAP_EMPTY;
    if(memCount >= hp->count || memCount < 0)
    {
        printf("Invalid index");
        return ERROR;
    }
    memory_delete(hp->memory[memCount]);
    for(int i = 0; i < hp->count - memCount; i++)
    {
        hp->memory[memCount] = hp->memory[memCount+1];
    }
    hp->count--;
}

heap_status_t heap_memSet(heap_t * hp, int memSize, char * memory, int memCount)
{
    if(memCount >= hp->count || memCount < 0)
    {
        printf("Invalid index");
        return ERROR;
    }
    memory_set(hp->memory[memCount], memSize, memory, memCount);
}

heap_status_t heap_memGet(heap_t * hp, int memSize, char * memory, int memCount)
{
    if(memCount >= hp->count || memCount < 0)
    {
        printf("Invalid index");
        return ERROR;
    }
    memory_get(hp->memory[memCount], memSize, memory);
}

int heap_memGetSize(heap_t * hp, int memCount)
{
    if(memCount > hp->count || memCount < 0)
    {
        printf("Invalid index");
        return;
    }
    return memory_getSize(hp->memory[memCount]);
}

int heap_getCount(heap_t * hp)
{
    return hp->count;
}

int heap_getNum(heap_t * hp)
{
    return hp->num;
}
