#ifndef AUTOMATA_H_INCLUDED
#define AUTOMATA_H_INCLUDED

#include "list.h"

typedef struct automata_s * automata_t;

typedef void (*reaction_fn)(automata_t, void *);

automata_t automata_new();
void automata_free(automata_t self);

void automata_subscribeAlmostWin(automata_t self, void * receiver, reaction_fn callback);
void automata_subscribeWin(automata_t self, void * receiver, reaction_fn callback);
void automata_subscribeJackpot(automata_t self, void * receiver, reaction_fn callback);
void automata_sendMessage(automata_t self, list_t * list);
void automata_run(automata_t  self);

#endif // AUTOMATA_H_INCLUDED
