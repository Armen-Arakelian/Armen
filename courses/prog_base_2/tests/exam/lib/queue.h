#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED

typedef struct queue_s queue_t;

queue_t * queue_new(void);
void queue_free(queue_t * self);

int queue_getSize(queue_t * self);
int queue_peek(queue_t * self);
int queue_sum(queue_t * self);

void queue_enqueue(queue_t * self, int val);
int queue_dequeue(queue_t * self);

void queue_print(queue_t * self);

#endif // QUEUE_H_INCLUDED
