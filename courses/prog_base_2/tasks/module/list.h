#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED

#define MAX_LIST_SIZE 10

typedef enum
{
    LIST_EMPTY,
    LIST_FULL,
    LIST_OK,
    ERROR
} list_status_t;

typedef struct coord
{
    int x, y;
} coord;

typedef struct town
{
  coord place;
  char name[100];
} town;

typedef struct list_s list_t;

list_t * list_new();
void list_delete(list_t * self);

list_status_t list_put(list_t * self, town tw, int pos);
town list_pop(list_t *self, int pos, list_status_t *status);
town list_peek(list_t *self, int pos, list_status_t *status);
double distacnce(list_t *self, int c1, int c2);

int list_getCount(list_t *self);
town list_getTown(list_t *self, int pos);
void list_setTown(list_t *self, town newTown, int pos);

void list_print(list_t *self);


#endif // LIST_H_INCLUDED
