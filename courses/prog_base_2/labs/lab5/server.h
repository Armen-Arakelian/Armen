#ifndef SERVER_H_INCLUDED
#define SERVER_H_INCLUDED

typedef struct server_s * server_t;

server_t server_new(int port);
void server_delete(server_t self);

void server_listen(server_t self);


#endif // SERVER_H_INCLUDED
