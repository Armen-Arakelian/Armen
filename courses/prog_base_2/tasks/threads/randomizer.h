#ifndef RANDOMIZER_H_INCLUDED
#define RANDOMIZER_H_INCLUDED

typedef struct randomizer_s randomizer_t;

randomizer_t * randomizer_new(mutex_t * mu, int * number);
void randomizer_delete(randomizer_t * rnd);
void randomizer_join(randomizer_t * rnd);

void randomizer_randomize(randomizer_t * rnd);


void * randomizer(void * args);

#endif // RANDOMIZER_H_INCLUDED
