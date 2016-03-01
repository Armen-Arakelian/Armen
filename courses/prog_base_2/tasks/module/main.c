#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

int main()
{
    town tw, tw1, tw2, peeked;
    list_status_t *popStatus, *peekStatus;
    list_status_t putStatus;
    strcmp(tw.name, "city 0");
    strcmp(tw1.name, "city 1");
    strcmp(tw2.name, "city 2");
    tw.place.x = 5;
    tw.place.y = 5;
    tw1.place.x = 10;
    tw1.place.y = 10;
    tw2.place.x = 11;
    tw2.place.y = 11;
    list_t *ls;
    ls = list_new();
    putStatus = list_put(ls, tw, 5);
    if(putStatus == LIST_FULL)
        printf("List is full");
    if (putStatus == ERROR)
    {
        printf("Invalid index");
        return EXIT_FAILURE;
    }
    putStatus = list_put(ls, tw1, 0);
    if(putStatus == LIST_FULL)
        printf("List is full");
    if (putStatus == ERROR)
    {
        printf("Invalid index");
        return EXIT_FAILURE;
    }
    putStatus = list_put(ls, tw1, 4);
    if(putStatus == LIST_FULL)
        printf("List is full");
    if (putStatus == ERROR)
    {
        printf("Invalid index");
        return EXIT_FAILURE;
    }
    putStatus = list_put(ls, tw2, 4);
    if(putStatus == LIST_FULL)
        printf("List is full");
    if (putStatus == ERROR)
    {
        printf("Invalid index");
        return EXIT_FAILURE;
    }
    list_pop(ls, 2, popStatus);
    if (*popStatus == LIST_EMPTY)
    {
        printf("List is empty");
    }
    if(*popStatus == ERROR)
    {
        printf("Invalid index");
        return EXIT_FAILURE;
    }
    list_print(ls);
    peeked = list_peek(ls, 1, peekStatus);
    if(*peekStatus == LIST_EMPTY)
        printf("List is empty");
    if (*peekStatus == ERROR)
    {
        printf("Invalid index");
        return EXIT_FAILURE;
    }
    printf("\nPeeked %d %d", peeked.place.x, peeked.place.y);
    int c1 = 1, c2 = 2;
    double dis = distacnce(ls, c1, c2);
    if(!dis)
        printf("\nInvalid index");
    else
    printf("\nDistance between %d and %d is %f", c1, c2, dis);
    printf("\nCount %d", (list_getCount(ls)+1));
    list_delete(ls);
    return 0;
}
