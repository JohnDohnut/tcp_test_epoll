#ifndef __EPOLL_H__
#define __EPOLL_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/epoll.h>
#include <errno.h>
#include <memory.h>
#include "server.h"
#define MAX_EVENTS 64
#define EPOLL_TIMEOUT 50

typedef struct epoll_s epoll_t;
struct epoll_s{
	int epoll_fd;	
};

typedef struct event_s event_t;
struct event_s{
	struct epoll_event event;
	struct epoll_event events_buffer[MAX_EVENTS];
}
epoll_t* server_epoll_init();
int server_epoll_create(epoll_t* epoll, int max);
int server_epoll_add_object(epoll_t* epoll, event_t* event, server_t* object);
int server_epoll_wait(epoll_t* epoll);

event_t* server_epoll_event_init(epoll_t* epoll, int op);
#endif
