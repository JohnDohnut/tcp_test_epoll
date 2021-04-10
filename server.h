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
#define MAX_EVENTS 64
#define MAX_CLIENTS 128
#define LOCALHOST "127.0.0.1"
#define PORT 8000



#endif
