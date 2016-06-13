#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "blog.h"

struct blog_s
{
    List_t users;
    int size;
};

struct post_s
{
    int id;
    char post[100];
    List_t comments;
};

struct user_s
{
    int id;
    char login[100];
    char password[100];
    List_t posts;
};

blog_t blog_new()
{
    blog_t blog = malloc(sizeof(struct blog_s));
    blog->size = 0;
    return blog;
}

void blog_delete(blog_t self)
{
    free(self);
}

user_t user_new(blog_t self)
{
    user_t user = malloc(sizeof(struct user_s));
    user->id = self->size;
    self->size++;
    List_add(self->users, 0, user);
    return user;
}

void user_delete(user_t self)
{
    free(self);
}

post_t post_new()
{
    post_t post = malloc(sizeof(struct post_s));
}

void post_delete(post_t self)
{
    free(self);
}

user_t user_reg(blog_t self, char * login, char * password)
{
    user_t user = user_new(self);
    strcpy(user->login, login);
    strcpy(user->password, password);
    return user;
}

int user_getSelfId(user_t self)
{
    return self->id;
}

void user_changePass(user_t self, char * newPass)
{
    strcpy(self->password, newPass);
}

void user_changeLog(user_t self, char * newLog)
{
    strcpy(self->login, newLog);
}

void user_addPost(user_t self, post_t post)
{
    List_add(self->posts, 0, post);
}

List_t user_getPosts(user_t self)
{
    return self->posts;
}

void user_deletePost(user_t self, int id)
{
    int size = List_getSize(self->posts);
    for(int i = 0; i< size;i++)
    {
        if(((post_t)(List_get(self->posts, i, NULL)))->id == id)
            List_remove(self->posts, i, NULL);
    }
}

void post_addComment(user_t self, int id, char * comm)
{
    int size = List_getSize(self->posts);
    post_t post;
    for(int i = 0; i< size;i++)
    {
        if(((post_t)(List_get(self->posts, i, NULL)))->id == id)
            {
                post = List_get(self->posts, i, NULL);
                List_add(post->comments, 0, comm);
            }
    }
}


