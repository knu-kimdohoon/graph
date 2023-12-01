#pragma once
#include <malloc.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct queuenode {
	char data;
	struct queuenode* next;
}Node;

typedef struct {
	int count;
	Node* front;
	Node* rear;
}Queue;

Queue* createQueue() {
	Queue* hptr = (Queue*)malloc(sizeof(Queue));
	if (hptr == NULL) {
		printf("failed to create queue\n");
		return NULL;
	}
	hptr->count = 0;
	hptr->front = hptr->rear = NULL;

	return hptr;
}

bool isEmptyQueue(Queue* ptr) {
	if (ptr->count == 0) return true;
	else return false;
}

void enqueue(Queue* ptr, char item) {
	Node* pNewNode = (Node*)malloc(sizeof(Node));
	if (pNewNode == NULL) {
		printf("failed to create node\n");
		return;
	}
	pNewNode->data = item;
	pNewNode->next = NULL;
	if (isEmptyQueue(ptr)) {
		ptr->rear = pNewNode;
		ptr->front = ptr->rear;
	}
	else {
		ptr->rear->next = pNewNode;
		ptr->rear = pNewNode;
	}
	ptr->count++;
}

char dequeue(Queue* ptr) {
	Node* NowFront = NULL;
	char return_val;
	if (isEmptyQueue(ptr)) {
		return '\0';
	}
	else {
		NowFront = ptr->front;
		return_val = ptr->front->data;
		if (ptr->count == 1) {
			ptr->front = ptr->rear = NULL;
		}
		else {
			ptr->front = NowFront->next;
		}
		ptr->count--;
		free(NowFront);
		return return_val;
	}
}

void DestroyQueue(Queue* ptr) {
	Node* temp = NULL;
	while (ptr->count != 0) {
		temp = ptr->front;
		ptr->front = temp->next;
		free(temp);
		ptr->count--;
	}
	free(ptr);
}