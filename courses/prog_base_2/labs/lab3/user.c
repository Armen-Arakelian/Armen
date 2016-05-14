#include <stdio.h>
#include <stdlib.h>

#include "event.h"
#include "user.h"
#include "automata.h"

struct player_s
{
    char name[100];
    char reaction[100];
};

struct press_s
{
    char name[100];
    char reaction[100];
};

struct administration_s
{
    char name[100];
    char reaction[100];
};

player_t user_newPlayer(const char * name)
{
    player_t self = malloc(sizeof(struct player_s));
    strcpy(self->name, name);
    return self;
}

press_t user_newPress(const char * name)
{
    press_t self = malloc(sizeof(struct press_s));
    strcpy(self->name, name);
    return self;
}

administration_t user_newAdministration(const char * name)
{
    administration_t self = malloc(sizeof(struct administration_s));
    strcpy(self->name, name);
    return self;
}

void user_freePlayer(player_t self)
{
    free(self);
}

void user_freePress(press_t self)
{
    free(self);
}

void user_freeAdministration(administration_t self)
{
    free(self);
}

static void user_playerReaction1(automata_t sender, void * receiver)
{
    player_t pl = (player_t)receiver;
    strcpy(pl->reaction, "is near to win");
    printf("Player %s %s\n", pl->name, pl->reaction);
}

static void user_playerReaction2(automata_t sender, void * receiver)
{
    player_t pl = (player_t)receiver;
    strcpy(pl->reaction, "win!!!!!");
    printf("Player %s %s\n", pl->name, pl->reaction);
}

static void user_playerReaction3(automata_t sender, void * receiver)
{
    player_t pl = (player_t)receiver;
    strcpy(pl->reaction, "win JACKPOT!!!!!");
    printf("Player %s %s\n", pl->name, pl->reaction);
}

static void user_pressReaction(automata_t sender, void * receiver)
{
    press_t pr = (press_t)receiver;
    strcpy(pr->reaction, "press knows that the Jackpot has been won");
    printf("%s %s\n", pr->name, pr->reaction);
}

static void user_administrationReaction(automata_t sender, void * receiver)
{
    administration_t ad = (administration_t)receiver;
    strcpy(ad->reaction, "administration knows that the Jackpot has been won");
    printf("%s %s\n", ad->name, ad->reaction);
}

reaction_fn user_getCallbackAlmostWin(player_t self)
{
    return user_playerReaction1;
}

reaction_fn user_getCallbackWin(player_t self)
{
    return user_playerReaction2;
}

reaction_fn user_getCallbackJackpotPlayer(player_t self)
{
    return user_playerReaction3;
}

reaction_fn user_getCallbackJackpotPress(press_t self)
{
    return user_pressReaction;
}

reaction_fn user_getCallbackJackpotAdministration(administration_t self)
{
    return user_administrationReaction;
}
