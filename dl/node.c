#include "node.h"


node_int* node_int_init(){
	node_int* node;
	if((node = malloc(sizeof(node_int))) < 0){
		perror("	|! node malloc failed\n");
		return -1;
	}
	memset(node, 0, sizeof(node_int));
	return node;

}

int get_node_int_data(node_int* node){
	if(node == NULL){
		perror("	|! node getter(data) PARAMNULL\n");
		return -2;
	}
	return node->data;
}
node_int* get_node_int_prev(node_int* node){
	if(node == NULL){
		perror("	|! node getter(prev) PARAMNULL\n");
		return -2;
	}
	return node->prev;
}
	
node_int* get_node_int_next(node_int* node){
	if(node == NULL){
		perror("	|! node getter(next) PARAMNULL\n");
		return -2;
	}
	return node->next;
}
int set_node_int_data(node_int* node, int data){
	if(node == NULL){
		perror("	|! node setter(data) PARAMNULL\n");
		return -2;
	}
	node -> data = data;
	return 0;
		
}
int set_node_int_prev(node_int* node, node_int* prev){
	if(node == NULL){
		perror("	|! node setter(prev) PARAMNULL\n");
		return -2;
	}
	if(prev == NULL){
		printf("	|! warning : setter(prev) new prev is NULL\n");
	}
	node->prev = prev;
	return 0;
}
int set_node_int_next(node_int* node, node_int* next){
	if(node == NULL){
		perror("	|! node setter(next) PARAMNULL\n");
		return -2;
	}
	if(next == NULL){
		printf("	|! warning : setter(next) new next is NULL\n");		
	}	
	node->next = next;
	return 0;
}
int main(){
	
	
	node_int* nodes[3];
		
	int i=0;
	for(i=0;i<3;i++){
		nodes[i] = node_int_init();
		nodes[i]->data = i;	
	}
	
	for(i=0;i<3;i++){
		printf("data : %d\n", nodes[i]->data);
	}
	for(i=0;i<3;i++){
		free(nodes[i]);
	}
	
	printf("done\n");	
	return 0;
	
}

