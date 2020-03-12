#ifndef QUEUE_H_
#define QUEUE_H_

#include <stdio.h>
#include <stdlib.h>

typedef struct QueueNode{
	Item elem;
	struct QueueNode *next;
}QueueNode;

typedef QueueNode TcelQ;
typedef QueueNode *ACelQ;

typedef struct Queue{
	QueueNode *front;
	QueueNode *rear;
	long size;
}Queue;

typedef Queue TCoada;
typedef Queue *AQ;


Queue* createQueue(void){
	// TODO: Cerinta 2
	Queue* MyQueue = malloc(sizeof(Queue));
	MyQueue->front = MyQueue->rear = NULL;
	MyQueue->size = 0;
	return MyQueue;
} 

int isQueueEmpty(Queue *q){
	// TODO: Cerinta 2
	if(q->rear == NULL) {
		return 1;
	}
	return 0;
}

void enqueue(Queue *q, Item elem){
	// TODO: Cerinta 2
	QueueNode* aux = malloc(sizeof(QueueNode));
	aux->next = NULL;
	aux->elem = elem;
	if(q->rear == NULL || q->front == NULL) {
		q->rear = q->front = aux;
		aux->next = NULL;
		q->size++;
		return;
	}
	QueueNode* t = q->rear;
	q->rear->next = aux;
	q->rear = aux;
	q->size++;
}

Item front(Queue* q){
	// TODO: Cerinta 2
	if(q->front != NULL) {
		return q->front->elem;
	}
	return 0;
}

void dequeue(Queue* q){
	// TODO: Cerinta 2
	if(q->rear == NULL) {
		return;
	}
	QueueNode* p = q->front;
	q->front = q->front->next;
	if(q->front == NULL) {
		q->rear = NULL;
		free(p);
		q->size = 0;
		return;
	}
	q->size--;
	free(p);
}

void destroyQueue(Queue *q){
	// TODO: Cerinta 2
	QueueNode *p;
	
	while(q->size != 0) {
		p = q->front;
		q->front = q->front->next;
		free(p);
		q->size--;
	}
	free(q);
}

#endif
