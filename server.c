 
#include "server.h"

int main(int argc, char* argv[]){
	struct sockaddr_in server_addr, client_addr;
	
	int server_sock;
	int client_sock;
	socklen_t addrlen, client_addr;
	int client_socks[MAX_CLIENT];
	memset(client_cocks, 0, sizeof(int) * MAX_CLIENTS);
	/*** sock_init() ***/		
	if((server_sock = socket(AF_INET, SOCK_STREAM, 0) < 0)){
		perror("sock failed\n");
		return -1;
	}
	memset(&server_addr, 0, sizeof(struct sockaddr_in));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = INADDR_ANY;
	server_addr.sin_port = htons(port);
	/*** *** set_socket_nonblock() *** ***/
	int flag;
	flag = fcntl(server_socket, F_GETFL, 0);
	fcntl(server_socket, F_SETFL, flag|O_NONBLOCK);
	/*** *** set_socket_nonblock() *** ***///
	if( bind(serrver_sock, (struct sockaddr*)&(server_addr), sizeof(struct sockaddr)) == -1){
		perror("bind failed\n");
		return -2;	
	}
	/*** sock_init() ***///
	
	/*** epoll init() ***/
	int epoll_fd = epoll_create(MAX_EVENTS);
	if(epoll_fd < 0){
		perror("epoll failed\n");
		close(server_socket);
		return -3;	
	}
	/// init EPOLLIN event struct, add server_socket to EPOLLIN event
	struct epoll_event event;
	event.events = EPOLLIN;
	event.data.fd = server_sock;
	if(epoll_ctl(epoll_fd, EPOLL_CTL_ADD, server_socket, &event) < 0){
		perror("epoll_ctl failed\n");
		close(epoll_fd);
		close(server_socket);
		return -4;		
	}

	struct epoll_event epoll_events[MAX_EVENTS];
	int event_count;	
	/*** epoll_init() ***///
	/*** epoll_handle()***/
	int i;
	while(true){
		
		event_count = epoll_wait(epoll_fd, epoll_events, MAX_EVENTS, -1);
		if(event_count == -1){
			perror("epoll wait error\n");
			return -5;
		}
		for(int i=0; i<event_count;i++){
			if(epoll_events[i].data.fd == server_sock){ /// if server event occurrs, accept();
				client_socket = accept(server_sock, (struct sockaddr*) &client_addr, sizeof(struct sockaddr_in));
				if(client_socket <0){
					perror("accept() failed\n");
					return -6;
				}
				else if(client_socket == EAGAIN || EWOULDBLOCK){
					continue;
				}
				else{
					/// add client to epoll event;

					/// set client_socket nonblock() 
					flag = fcntl(client_socekt, F_GETFL,0);
					if(fcntl(client_socket, F_SETFL, flag|O_NONBLOCK) < 0){
						perror("client set_nonblock() failed\n");
							return -7;					
					}
					/// add client to EPOLL (EPOLLIN event)
					event.data.fd = client_socket;
					if(epoll_ctl(epoll_fd, EPOLL_CTL_ADD, client_socket, &event) < 0){
						perror("epoll_ctl failed\n");
						close(epoll_fd);
						close(client_socket);
						close(server_socket);						
						return -4;		
					}
					
				}
				
			}
		}
	}	
	
	/*** epoll_handle() ***///
	
	
	
}
