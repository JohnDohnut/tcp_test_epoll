#include "client.h"

int main(int argc, char* argv[]){
	
	int client_sock;
	char buffer[MAX_BUFFER_LEN];		
	struct sockaddr_in server_addr;
	memset(&buffer,0,MAX_BUFFER_LEN);
	memset(&server_addr,0,sizeof(struct sockaddr_in));
	
	/***	client_socket()	***/
	client_sock = socket(AF_INET, SOCK_STREAM, 0);
	if(client_sock == -1){
		perror("	|! socket() failed\n");
		return -1;
	}
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
	server_addr.sin_port = htons(PORT);

	if(connect(client_sock, (struct sockaddr*)(&server_addr), sizeof(server_addr)) < 0){
		perror("	|! connection failed\n");
		return -2;	
	}
	else{
		printf("	|@ connected to server\n");
	}
		
	sleep(10);
	close(client_sock);
	return 0;
}
