#ifndef LIST_QUEUE_H
#define LIST_QUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define TYPE int

typedef struct Node
{
	TYPE data;
	struct Node* next;
}Node;

typedef struct ListQueue
{
	Node* front;
	Node* rear;
	size_t cnt;
}ListQueue;

ListQueue* create_list_queue(void);

bool empty_list_queue(ListQueue* queue);

void push_list_queue(ListQueue* queue,TYPE data);

bool pop_list_queue(ListQueue* queue);

TYPE front_list_queue(ListQueue* queue);

TYPE rear_list_queue(ListQueue* queue);

size_t size_list_queue(ListQueue* queue);

void destroy_list_queue(ListQueue* queue);

#endif//LIST_QUEUE_H
