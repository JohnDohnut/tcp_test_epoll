 
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
	flag = fcntl(server->sock, F_GETFL, 0);
	fcntl(server->sock, F_SETFL, flag|O_NONBLOCK);
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
		return -2
	}
	if(client-> sock == EWOULDBLOCK || client-> sock == EWOULDAGAIN){	
		printf("	|! nothing to accept\n");
		free(client);
		return 0;
	}
	if(client-> sock > 0){
		printf("	|@ accepted client : %d\n",client->sock);
		return client;
	}
}












int main(int argc, char* argv[]){
	struct sockaddr_in server_addr, client_addr;
	int server_sock = -1;
	int client_sock = -1;
	socklen_t server_addrlen, client_addrlen;
	int client_socks[MAX_CLIENTS];
	memset(client_socks, 0, sizeof(int) * MAX_CLIENTS);
	int i;
	client_addrlen = sizeof(client_addr);
	server_addrlen = sizeof(server_addr);	
	
	
	/*** sock_init() ***/		
	server_sock = server_sock_init();
	printf("	|@ Server Socket : %d\n",server_sock); 

	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = INADDR_ANY;
	server_addr.sin_port = htons(PORT);
	/*** *** set_socket_nonblock() *** ***/
	int flag;
	flag = fcntl(server_sock, F_GETFL, 0);
	fcntl(server_sock, F_SETFL, flag|O_NONBLOCK);
	/*** *** set_socket_nonblock() *** ***///
	if( bind(server_sock, (struct sockaddr*)(&server_addr), server_addrlen) < -1){
		perror("bind failed\n");
		return -2;	
	}
	/*** sock_init() ***///
	
	/*** epoll init() ***/
	int epoll_fd = epoll_create(MAX_EVENTS);
	if(epoll_fd < 0){
		perror("epoll failed\n");
		close(server_sock);
		return -3;	
	}
	/// init EPOLLIN event struct, add server_sock to EPOLLIN event
	struct epoll_event event;
	event.events = EPOLLIN;
	event.data.fd = server_sock;
	if(epoll_ctl(epoll_fd, EPOLL_CTL_ADD, server_sock, &event) < 0){
		perror("epoll_ctl failed\n");
		close(epoll_fd);
		close(server_sock);
		return -4;		
	}

	struct epoll_event epoll_events[MAX_EVENTS];
	int event_count;
	if(listen(server_sock, MAX_CLIENTS)<0){
		perror("listen failed\n");
		return -4;
	}
	printf("	|@ listening...\n");
	/*** epoll_init() ***///
	/*** epoll_handle()***/
	int INTERVAL = 0;
	while(1){
		sleep(1);
		
		printf("	|@ loop interval : %d \n", ++INTERVAL);
		event_count = epoll_wait(epoll_fd, epoll_events, MAX_EVENTS, 50);
		printf("	|@ epoll_wait()\n");	
		if(event_count < 0){
			perror("epoll wait error\n");
			return -5;
		}
		else if(event_count == 0){
			printf("	|@ no event\n");
		}
		else{
			printf("	|@ event detected\n");		
			for(i=0; i<event_count;i++){
				if(epoll_events[i].data.fd == server_sock){ /// if server event occurrs, accept();
						printf("	|@ server_sock EPOLLIN\n");
						client_sock = accept(server_sock, (struct sockaddr *)(&client_addr), &client_addrlen);
						if(client_sock <0){
							perror("accept() failed\n");
							return -6;
						}
						else if(client_sock == EAGAIN || client_sock == EWOULDBLOCK){
							printf("	| @ no client to accept\n");
						}
						else{
						/// add client to epoll event;
							printf("	|@ accepted \n");
							/// set client_sock nonblock() 
							flag = fcntl(client_sock, F_GETFL,0);
							if(fcntl(client_sock, F_SETFL, flag|O_NONBLOCK) < 0){
								perror("client set_nonblock() failed\n");
								return -7;					
							}
							/// add client to EPOLL (EPOLLIN event)
							event.data.fd = client_sock;
							if(epoll_ctl(epoll_fd, EPOLL_CTL_ADD, client_sock, &event) < 0){
								perror("epoll_ctl failed\n");
								close(epoll_fd);
								close(client_sock);
								printf("	|! failed to add client event, connection closed\n");
								continue;
		
							}
							printf("	|@ new client no : %d \n",client_sock);
						
						}
							
				}
			}
	
		}
		printf("\n");	
	}
}	
	
	/*** epoll_handle() ***///
	
	
	
 
