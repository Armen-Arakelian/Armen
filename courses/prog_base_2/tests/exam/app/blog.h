#ifndef BLOG_H_INCLUDED
#define BLOG_H_INCLUDED

typedef struct blog_s * blog_t;
typedef struct user_s * user_t;
typedef struct post_s * post_t;

blog_t blog_new();
void blog_delete(blog_t self);
user_t user_new(blog_t self);
void user_delete(user_t self);
post_t post_new();
void post_delete(post_t self);
user_t user_registration(blog_t self, char * login, char * password);
int user_getSelfId(user_t self);
void user_changePass(user_t self, char * newPass);
void user_changeLog(user_t self, char * newLog);
void user_addPost(user_t self, post_t post);
List_t user_getPosts(user_t self);
void user_deletePost(user_t self, int id);
void post_addComment(user_t self, int id, char * comm);

#endif // BLOG_H_INCLUDED
