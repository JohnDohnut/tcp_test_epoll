 
#include "server.h"
server_t* server_sock_init(){
	server_t* server = malloc(sizeof(server_t));
	if(server<0){
		perror("	|! server init failed...\n");
		return -1;
	}
	memset(server, 0, sizeof(server_t));
	server->addr_len = sizeof(server->server_addr);
	return server;
}
int server_sock_socket(server_t* server){
	if(server == NULL){
		perror("	|! server NULL (socket)\n");
		return -1;
	}	
	if((server->sock = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		perror("sock failed\n");
		return -2;
	}
	return server->sock;

}
int server_set_sock_nonblock(server_t* server){
	if(server == NULL){
		perror("server NULL(set_sock_nonblock)\n");
		return -1;
	}	
	int flag = fcntl(server->sock, F_GETFL, 0);
	if(fcntl(server->sock, F_SETFL, flag|O_NONBLOCK)<0){
		perror("sock set flag failed \n");
		return -2;
	}
	return 0;
}
int server_bind(server_t* server){
	if(server == NULL){
		perror("	|! server NULL (bind)\n");
		return -1;
	}
	server-> addr.sin_family = AF_INET;
	server-> addr.sin_addr.s_addr = INADDR_ANY;
	server-> addr.sin_port = htons(PORT);	
	return 0;
}
int server_listen(server_t* server){
	if(server == NULL){
		perror("	|! server NULL (listen)\n");
		return -1;
	}
	if(listen(server->sock, MAX_CLIENTS)<0){
		perror("	|! server listen failed\n");
		return -2;
	}
	return server->sock;
}

server_t* server_accept(server_t* server){
	server_t* client = malloc(sizeof(server_t));
	client = memset(client, 0, sizeof(server_t));
	if(server == NULL){
		perror("	|! server NULL (accept)\n");
		return -1;
	}
	client->sock = accept(server->sock, (struct sockaddr *)(&(client->addr)), &(client->addr_len));
	if(client-> sock < 0){
		printf("	|! accept failed\n");
		free(client);
		return -2;
	}
	if(client-> sock == EWOULDBLOCK || client-> sock == EAGAIN){	
		printf("	|! nothing to accept\n");
		free(client);
		return 0;
	}
	if(client-> sock > 0){
		printf("	|@ accepted client : %d\n",client->sock);
		return client;
	}
}



	
 
