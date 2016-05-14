#ifndef USER_H_INCLUDED
#define USER_H_INCLUDED

#include "event.h"
#include "automata.h"

typedef struct player_s * player_t;
typedef struct press_s * press_t;
typedef struct administration_s * administration_t;

player_t user_newPlayer(const char * name);
press_t user_newPress(const char * name);
administration_t user_newAdministration(const char * name);

reaction_fn user_getCallbackAlmostWin(player_t self);
reaction_fn user_getCallbackWin(player_t self);
reaction_fn user_getCallbackJackpotPlayer(player_t self);
reaction_fn user_getCallbackJackpotPress(press_t self);
reaction_fn user_getCallbackJackpotAdministration(administration_t self);

#endif // USER_H_INCLUDED
