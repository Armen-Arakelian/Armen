#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include <math.h>

static struct list_s
{
    town citys[MAX_LIST_SIZE];
    int count;
};


list_t * list_new()
{
    list_t *ls = malloc(sizeof(struct list_s));
    ls->count = -1;
    return ls;
}

void list_delete(list_t * self)
{
    free(self);
}

list_status_t list_put(list_t * self, town tw, int pos)
{
    if(self->count == MAX_LIST_SIZE)
        return LIST_FULL;
    if(pos<0 || pos>=MAX_LIST_SIZE)
    {
        printf("Invalid index");
        return ERROR;
    }
    if(self->count == -1)
    {
        self->count++;
        self->citys[self->count] = tw;
        return LIST_OK;
    }
    if(pos <= self->count)
    {
        for(int i=self->count;i>=pos;i--)
        {
            self->citys[i+1] = self->citys[i];
        }
        self->citys[pos] = tw;
        self->count++;
        return LIST_OK;
    }
    else
    {
        self->count++;
        self->citys[self->count] = tw;
        return LIST_OK;
    }
}

town list_pop(list_t *self, int pos, list_status_t *status)
{
    town returned;
    if(self->count == -1)
        {
            (*status) = LIST_EMPTY;
        }
    else
    if(pos<0 || pos>=MAX_LIST_SIZE)
    {
        printf("Invalid index");
        *status = ERROR;
    }
    else
    if(pos > self->count)
    {
        printf("\nIt's empty element");
        *status = ERROR;
    }
    else
    {
        returned = self->citys[pos];
        for(int i = 0;i < self->count-pos;i++)
        {
            self->citys[pos+i] = self->citys[pos+i+1];
        }
        self->count--;
    }
    return returned;
}

town list_peek(list_t *self, int pos, list_status_t *status)
{
    town returned;
    if(self->count == -1)
        {
            (*status) = LIST_EMPTY;
        }
    else
    if(pos<0 || pos>=MAX_LIST_SIZE)
    {
        printf("Invalid index");
        *status = ERROR;
    }
    else
    if(pos > self->count)
    {
        printf("\nIt's empty element");
        *status = ERROR;
    }
    else
    {
        returned = self->citys[pos];
    }
    return returned;
}

double distacnce(list_t *self, int c1, int c2)
{
    if(self->count == -1)
        return 0;
    if(c1<0 || c1>=MAX_LIST_SIZE || c2<0 || c2 > MAX_LIST_SIZE)
    {
        printf("Invalid index");
        return 0;
    }
    if(c1 > self->count || c2>self->count)
    {
        printf("\nIt's empty element");
        return 0;
    }
    return sqrt( pow(self->citys[c1].place.x - self->citys[c2].place.x, 2) + pow(self->citys[c1].place.y - self->citys[c2].place.y, 2) );
}

int list_getCount(list_t *self)
{
    return self->count;
}

town list_getTown(list_t *self, int pos)
{
    if(pos<0 || pos>=MAX_LIST_SIZE || pos > self->count)
    {
        printf("Invalid index");
        return;
    }
    return self->citys[pos];
}

void list_setTown(list_t *self, town newTown, int pos)
{
    if(pos<0 || pos>=MAX_LIST_SIZE || pos > self->count)
    {
        printf("Invalid index");
        return;
    }
    self->citys[pos] = newTown;
}

void list_print(list_t *self)
{
    for(int i=0;i<(self->count+1);i++)
    {
        printf("%d  %d  ",  self->citys[i].place.x, self->citys[i].place.y);
        puts("");
    }
}
