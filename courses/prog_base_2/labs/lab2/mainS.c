#include <stdlib.h>
#include <stdio.h>

#include "queue.h"

#define MAX_QUEUE_SIZE 100

struct queue_s {
    int array[MAX_QUEUE_SIZE];
    int head;
    int tail;
};

queue_t * queue_new(void) {
    queue_t * q = malloc(sizeof(struct queue_s));
    q->head = 0;
    q->tail = 0;
    return q;
}

void queue_free(queue_t * self) {
    free(self);
}

int queue_getSize(queue_t * self) {
    return self->tail-1;
}

void queue_enqueue(queue_t * self, int val) {
    if(self->tail-1 == MAX_QUEUE_SIZE)
        return;
    self->array[self->tail] = val;
    self->tail++;
}

int queue_dequeue(queue_t * self) {
    if (self->tail > 0) {
        int val = self->array[self->head];
        int size = queue_getSize(self);
        for(int i = 1; i<size; i++)
        {
            self->array[i-1] = self->array[i];
        }
        self->tail--;
        return val;
    }
    return 0;
}

int queue_peek(queue_t * self) {
    if (self->tail > 0) {
        int val = self->array[self->tail - 1];
        return val;
    }
    return 0;
}

int queue_sum(queue_t * self)
{
    int sum = 0;
    int size = queue_getSize(self);
    for(int i = 0; i<=size; i++)
    {
        sum += self->array[i];
    }
    return sum;
}

void queue_print(queue_t * self) {
    for(int i = 0; i < self->tail; i++) {
        printf("%d ", self->array[i]);
    }
}
