#ifndef ONLINETV_H_INCLUDED
#define ONLINETV_H_INCLUDED

#include"list.h"

typedef struct OnlineTv_s * OnlineTv_t;
typedef struct viewer_s * viewer_t;
typedef struct video_s * video_t;

typedef enum
{
    FILM,
    ADVERT
} video_type_t;

typedef void (*film_fn)(
    void * listener,
    OnlineTv_t * sender, char * name);

OnlineTv_t onlineTv_new();
viewer_t viewer_new(OnlineTv_t self, char * name);
video_t video_new(video_type_t type, char * name);
void onlineTv_free(OnlineTv_t self);
void viewer_free(viewer_t self);
void video_free(video_t self);

void video_add(OnlineTv_t self, video_t video);
void video_delete(OnlineTv_t self, int num);
list_t * onlineTv_getVideoList(OnlineTv_t self);
video_t video_getCurVideoInf(OnlineTv_t self);
char * video_getName(video_t self);
video_type_t video_getType(video_t vid);
void viewer_add(OnlineTv_t self, viewer_t v);
void viewer_delete(OnlineTv_t self, int num);
char * viewer_getName(viewer_t self);
int onlineTv_getViewerCount(OnlineTv_t self);
void onlineTv_subscribeFilm(OnlineTv_t self, void * listener, film_fn callback);
void onlineTv_unsubscribeFilm(OnlineTv_t self, void * listener, film_fn callback);
void onlineTv_nexVideo(OnlineTv_t self);

#endif // ONLINETV_H_INCLUDED
