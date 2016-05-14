#ifndef EVENT_H_INCLUDED
#define EVENT_H_INCLUDED

typedef struct event_s
{
    void * receiver;
    void * callback;
} event_t;

#endif // EVENT_H_INCLUDED
