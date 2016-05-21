
#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "onlineTv.h"

const int sv = 0;

typedef struct subscriber_s {
    void * listener;
    film_fn callback;
} subscriber_t;

struct OnlineTv_s
{
    int curVideo;
    int videoCount;
    int viewerCount;
    list_t * video;
    list_t * viewer;
    list_t * subscribers;
};

struct video_s
{
    video_type_t type;
    char name[100];
};

struct viewer_s
{
    char name[100];
};

OnlineTv_t onlineTv_new()
{
    OnlineTv_t tv = malloc(sizeof(struct OnlineTv_s));
    tv->viewerCount = 0;
    tv->videoCount = 0;
    tv->curVideo = 0;
    tv->video = list_new();
    tv->viewer = list_new();
    tv->subscribers = list_new();
    return tv;
}

viewer_t viewer_new(OnlineTv_t self, char * name)
{
    viewer_t viw = malloc(sizeof(struct viewer_s));
    strcpy(viw->name, name);
    return viw;
}

video_t video_new(video_type_t type, char * name)
{
    video_t vid = malloc(sizeof(struct video_s));
    vid->type = type;
    strcpy(vid->name, name);
    return vid;
}

void onlineTv_free(OnlineTv_t self)
{
    list_free(self->subscribers);
    list_free(self->video);
    list_free(self->viewer);
    free(self);
}

void viewer_free(viewer_t self)
{
    free(self);
}

void video_free(video_t self)
{
    free(self);
}

void video_add(OnlineTv_t self, video_t video)
{
    list_push_back(self->video, video);
    self->videoCount++;
}

void video_delete(OnlineTv_t self, int num)
{
    if(list_getSize(self->video) == 0)
        return;
    list_remove(self->video, num);
    self->videoCount--;
}

list_t * onlineTv_getVideoList(OnlineTv_t self)
{
    list_t * copy = list_new_copy(self->video);
    return copy;
}

video_t video_getCurVideoInf(OnlineTv_t self)
{
    video_t copy;
    strcpy(copy->name, ((video_t)list_get(self->video, self->curVideo))->name);
    copy->type = ((video_t)list_get(self->video, self->curVideo))->type;
    return copy;
}

char * video_getName(video_t self)
{
    return self->name;
}

char * viewer_getName(viewer_t self)
{
    return self->name;
}

video_type_t video_getType(video_t vid)
{
    return vid->type;
}

void viewer_add(OnlineTv_t self, viewer_t v)
{
    list_push_back(self->viewer, v);
    self->viewerCount++;
}

void viewer_delete(OnlineTv_t self, int num)
{
    list_remove(self->viewer, num);
    self->viewerCount--;
}

int onlineTv_getViewerCount(OnlineTv_t self)
{
    return self->viewerCount;
}

void onlineTv_subscribeFilm(OnlineTv_t self, void * listener, film_fn callback)
{
    subscriber_t * sub = malloc(sizeof(subscriber_t));
    sub->listener = listener;
    sub->callback = callback;
    list_push_back(self->subscribers, sub);
}

void onlineTv_unsubscribeFilm(OnlineTv_t self, void * listener, film_fn callback)
{
    for (int i = 0; i < list_getSize(self->subscribers); i++) {
        subscriber_t * subs = (subscriber_t *)list_get(self->subscribers, i);
        if ((subs->listener == listener) && (subs->callback == callback)) {
            list_remove(self->subscribers, i);
            break;
        }
    }
}

void onlineTv_nexVideo(OnlineTv_t self)
{
    video_t vid = (video_t)list_get(self->video, self->curVideo);
    if(vid->type == FILM)
    {
        for (int i = 0; i < list_getSize(self->subscribers); i++) {
            subscriber_t * sub = (subscriber_t *)list_get(self->subscribers, i);
            sub->callback(sub->listener, self, vid->name);
        }
    }
}




