#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "thread.h"
#include "mutex.h"

#include "randomizer.h"
#include "negativeWriter.h"

int main()
{
    int num;
    mutex_t * mu = mutex_new();
    randomizer_t * rnd1 = randomizer_new(mu, &num);
    randomizer_t * rnd2 = randomizer_new(mu, &num);
    negativeWriter_t * nw1 = negativeWriter_new(mu, &num);
    negativeWriter_t * nw2 = negativeWriter_new(mu, &num);
    randomizer_randomize(rnd1);
    negativeWriter_negativeWrite(nw1);
    randomizer_randomize(rnd2);
    negativeWriter_negativeWrite(nw2);
    randomizer_join(rnd1);
    negativeWriter_join(nw1);
    randomizer_join(rnd2);
    negativeWriter_join(nw2);
    randomizer_delete(rnd1);
    randomizer_delete(rnd2);
    negativeWriter_delete(nw1);
    negativeWriter_delete(nw2);
    mutex_free(mu);
    return 0;
}


