#ifndef __SERVER_H__
#define __SERVER_H__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/epoll.h>
#include <errno.h>
#include <memory.h>

#define MAX_BUFFER_LEN 1024;
#define MAX_CLIENTS 128
#define LOCALHOST "127.0.0.1"
#define PORT 8000

typedef struct server_s server_t;
struct server_s{
	int sock;
	struct sockaddr_in addr;
	socklen_t addr_len;
	
};
server_t* server_sock_init();
int server_sock_socket(server_t* server);
int server_set_sock_nonblock(server_t* server);
int server_bind(server_t* server);
int server_listen(server_t* server);
server_t* server_accept(server_t* server);


#endif
