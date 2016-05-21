#include <stdio.h>
#include <stdlib.h>

#include "OnlineTv.h"
#include"list.h"

void hiFilm(void * listener,
    OnlineTv_t * sender, char * name)
{
    printf("\tHi film!\n");
    printf("%s", name);
}

void byeFilm(void * listener,
    OnlineTv_t * sender, char * name)
{
    printf("\tBye film!\n");
    printf("%s", name);
}

int main()
{
    OnlineTv_t tv = onlineTv_new();
    video_t vid = video_new(FILM, "A");
    video_t v1 = video_new(ADVERT, "B");
    video_t v2 = video_new(FILM, "C");
    video_add(tv, vid);
    video_add(tv, v1);
    video_add(tv, v2);
    onlineTv_subscribeFilm(tv, NULL, hiFilm);
    onlineTv_nexVideo(tv);
    return 0;
}
