epoll_t* server_epoll_init(){
	epoll_t* epoll = malloc(sizeof(epoll_t));
	if (epoll < 0){
		perror("	|! epoll init failed\n");
		return -1;
	}
	return epoll;
}
event_t* server_epoll_event_init(epoll_t* epoll int op){
	if(epoll == NULL){
		perror("	|! epoll NULL (event_init)\n");
		return -1;
	}
	if(event<0){
		perror("	|! event_init failed\n");
		return -2;
	}
	if(epoll->epoll_fd < 0){
		perror("	|! epoll invalid(event_init)\n");
		return -3;	
	}
	event_t* event = malloc(sizeof(event_t));
	memset(event, 0, sizeof(event_t));
	event->event.data.fd = epoll->epoll_fd;
	if(op == EPOLLIN){
		event->event.events = EPOLLIN;
	}
	else if(op == EPOLLOUT){
		event->event.events = EPOLLOUT;
	}
	else {
		perror("	|! wrong op (event_init)\n");	
		free(event);
		return -4;
	}
	return event;
}
int server_epoll_create(epoll_t* epoll, int max){
	if(epoll == NULL){
		perror("	|! epoll NULL (epoll_create)\n");
		return -1;
	}
	else if(epoll < 1){
		perror("	|! wrong max number (epoll_create)\n");
		return -1;
	}
	epoll->epoll_fd = epoll_create(MAX_EVENTS);
	if(epoll_fd < 0){
		perror("	|! epoll create failed\n");
		return -2;		
	}
	

}

int server_epoll_add_object(epoll_t* epoll,event_t* event, server_t* object){
	if(epoll == NULL || event == NULL || object == NULL){
		perror("	|! PARAM NULL (epoll_set_event)\n");
		return -1;
	}

	if(epoll_ctl(epoll->epoll_fd, EPOLL_CTL_ADD, object->sock, &(event->event)) < 0){
		perror("	|! epoll_ctl failed\n");
		return -2;
	}
	return 0;
}
int server_epoll_wait(epoll_t* epoll){
	if (epoll == NULL){
		perror("	|! epoll NULL (epoll_wait) \n");
		return -1;
	}
	return epoll_wait(epoll, EPOLL_TIMEOUT);	
}
