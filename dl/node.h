#ifndef __NODE_H__
#define __NODE_H__


#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

typedef struct node_s_int node_int;
struct node_s_int{
	int data;	
	node_int* prev;
	node_int* next;	
};

node_int* node_int_init();
int get_node_int_data(node_int* node);
node_int* get_node_int_prev(node_int* node);
node_int* get_node_int_next(node_int* node);
int set_node_int_data(node_int* node, int data);
int set_node_int_prev(node_int* node, node_int* prev);
int set_node_int_next(node_int* node, node_int* next);

#endif
