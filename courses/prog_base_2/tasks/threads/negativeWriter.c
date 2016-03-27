#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "thread.h"
#include "mutex.h"
#include "negativeWriter.h"

struct negativeWriter_s
{
    thread_t * t;
    mutex_t * mu;
    int * num;
};

negativeWriter_t * negativeWriter_new(mutex_t * mu, int * number)
{
    negativeWriter_t * nw = malloc(sizeof(struct negativeWriter_s));
    nw->mu = mu;
    nw->t = NULL;
    nw->num = number;
    return nw;
}

void negativeWriter_delete(negativeWriter_t * nw)
{
    mutex_free(nw->mu);
    thread_free(nw->t);
    free(nw);
}

void negativeWriter_join(negativeWriter_t * nw)
{
    thread_join(nw);
}

static void * negativeWrite(void * args)
{
    negativeWriter_t * nw = (negativeWriter_t *)args;
    mutex_lock(nw->mu);
    if(*nw->num < 0)
        printf("%d  ", *nw->num);
    mutex_unlock(nw->mu);
    return NULL;
}

void negativeWriter_negativeWrite(negativeWriter_t * nw)
{
    if(NULL != nw->t)
        thread_free(nw->t);
    nw->t = thread_create_args(negativeWrite, nw);
}

