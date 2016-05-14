#include <stdio.h>
#include <stdlib.h>

#include "event.h"
#include "list.h"
#include "automata.h"

struct automata_s
{
    list_t * event_almostWin;
    list_t * event_win;
    list_t * event_jackpot;
};

automata_t automata_new()
{
    automata_t self = malloc(sizeof(struct automata_s));
    self->event_almostWin = list_new();
    self->event_win = list_new();
    self->event_jackpot = list_new();
    return self;
}

void automata_free(automata_t self)
{
    int count1 = list_getCount(self->event_almostWin);
    int count2 = list_getCount(self->event_win);
    int count3 = list_getCount(self->event_jackpot);

    for (int i = 0; i < count1; i++) {
        event_t * ev = list_pop_back(self->event_almostWin);
        free(ev);
    }
    for (int i = 0; i < count2; i++) {
        event_t * ev = list_pop_back(self->event_win);
        free(ev);
    }
    for (int i = 0; i < count3; i++) {
        event_t * ev = list_pop_back(self->event_jackpot);
        free(ev);
    }
    list_free(self->event_almostWin);
    list_free(self->event_win);
    list_free(self->event_jackpot);
    free(self);
}


void automata_subscribeAlmostWin(automata_t self, void * receiver, reaction_fn callback)
{
    event_t * sb = malloc(sizeof(struct event_s));
    sb->receiver = receiver;
    sb->callback = callback;
    list_push_back(self->event_almostWin, sb);
}

void automata_subscribeWin(automata_t self, void * receiver, reaction_fn callback)
{
    event_t * sb = malloc(sizeof(struct event_s));
    sb->receiver = receiver;
    sb->callback = callback;
    list_push_back(self->event_win, sb);
}

void automata_subscribeJackpot(automata_t self, void * receiver, reaction_fn callback)
{
    event_t * sb = malloc(sizeof(struct event_s));
    sb->receiver = receiver;
    sb->callback = callback;
    list_push_back(self->event_jackpot, sb);
}

void automata_sendMessage(automata_t self, list_t * list)
{
    for (int i = 0;i<list_getCount(list); i++)
    {
        event_t * ev = list_getEl(list, i);
        if (NULL != ev->callback)
        {
            reaction_fn fn = ev->callback;
            fn(self, ev->receiver);
        }
}
}

void automata_run(automata_t  self)
{
    int arr[3];
    for(int i = 0;i<3;i++)
    {
        arr[i] = rand() % 10;
    }
    printf("%d %d %d\n", arr[1], arr[2], arr[3]);
    if(arr[1] == arr[2] && arr[2] == arr[3] && arr[1] != 7)
        automata_sendMessage(self, self->event_win);
    else
        if(arr[1] == arr[2] || arr[2] == arr[3] || arr[1] == arr[3])
            automata_sendMessage(self, self->event_almostWin);

    if(arr[1] == 7 && arr[2] == 7 && arr[3] == 7)
        automata_sendMessage(self, self->event_jackpot);
}


