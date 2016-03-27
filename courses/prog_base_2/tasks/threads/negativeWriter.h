#ifndef NEGATIVEWRITER_H_INCLUDED
#define NEGATIVEWRITER_H_INCLUDED

typedef struct negativeWriter_s negativeWriter_t;

negativeWriter_t * negativeWriter_new(mutex_t * mu, int * number);
void negativeWriter_delete(negativeWriter_t * nw);
void negativeWriter_join(negativeWriter_t * nw);

void negativeWriter_negativeWrite(negativeWriter_t * nw);

#endif // NEGATIVEWRITER_H_INCLUDED
