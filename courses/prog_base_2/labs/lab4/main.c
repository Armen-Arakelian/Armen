#include "server.h"

int main()
{
    lib_init();
	server_t server = server_new(5000);
	server_listen(server);
	server_delete(server);
	lib_free();
    return 0;
}
