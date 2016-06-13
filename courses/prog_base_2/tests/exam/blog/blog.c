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
    char post[100];
    List_t coments;
};

struct user_s
{
    int id;
    char login[100];
    char password[100];
    post_t post;
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

user_t user_new()
{
    user_t user = malloc(sizeof(struct user_s));
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

user_t registration(blog_t self, char * login, char * password)
{
    user_t user = user_new();
    strcpy(user->login, login);
    strcpy(user->password, password);
    user->id = self->size;
    self->size++;
    List_add(self->users, 0, NULL);
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
    self->post = post;
}



