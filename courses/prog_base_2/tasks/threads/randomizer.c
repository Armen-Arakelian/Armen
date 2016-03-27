#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "thread.h"
#include "mutex.h"
#include "randomizer.h"

struct randomizer_s
{
    thread_t * t;
    mutex_t * mu;
    int * num;
};

randomizer_t * randomizer_new(mutex_t * mu, int * number)
{
    randomizer_t * rnd = malloc(sizeof(struct randomizer_s));
    rnd->mu = mu;
    rnd->t = NULL;
    rnd->num = number;
    return rnd;
}

void randomizer_delete(randomizer_t * rnd)
{
    mutex_free(rnd->mu);
    thread_free(rnd->t);
    free(rnd);
}

void randomizer_join(randomizer_t * rnd)
{
    thread_join(rnd);
}

static void * randomize(void * args)
{
    randomizer_t * rnd = (randomizer_t *)args;
    mutex_lock(rnd->mu);
    srand(time(NULL));
    *rnd->num = rand() % 500 - 255;
    mutex_unlock(rnd->mu);
    return NULL;
}

void randomizer_randomize(randomizer_t * rnd)
{
    if(NULL != rnd->t)
        thread_free(rnd->t);
    rnd->t = thread_create_args(randomize, rnd);
}

