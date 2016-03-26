#include <stdio.h>
#include <stdlib.h>

#define MAX_MEM_SIZE 100

#include "heap.h"
#include "memory.h"

int memory_getStrSize();

static struct heap_s
{
    memory_t * memory[MAX_MEM_SIZE];
    int num;
    int count;
};

heap_t * heap_new(int num)
{
    heap_t * hp = malloc(sizeof(struct heap_s));
    hp->count = 0;
    hp->num = num;
    return hp;
}

void heap_delete(heap_t * self)
{
    free(self);
}

memory_t * heap_memAdd(heap_t * hp, heap_status_t * status)
{
    if(hp->count == MAX_MEM_SIZE)
        {
            *status = HEAP_FULL;
            return NULL;
        }
    status = HEAP_OK;
    hp->memory[hp->count] = malloc(memory_getStrSize());
    hp->count++;
    return hp->memory[hp->count-1];
}

heap_status_t heap_memDelete(heap_t * hp, int memCount)
{
    if(0 == hp->count)
        return HEAP_EMPTY;
    if(memCount >= hp->count || memCount < 0)
    {
        printf("Invalid index");
        return HEAP_ERROR;
    }
    for(int i = 0; i < hp->count - memCount; i++)
    {
        hp->memory[memCount] = hp->memory[memCount+1];
    }
    free(hp->memory[hp->count-1]);
    hp->count--;
    return HEAP_OK;
}

int heap_getCount(heap_t * hp)
{
    return hp->count;
}

int heap_getNum(heap_t * hp)
{
    return hp->num;
}
