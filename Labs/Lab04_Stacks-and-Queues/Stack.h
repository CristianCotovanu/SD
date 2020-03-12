#ifndef STACK_H_
#define STACK_H_

#include <stdio.h>
#include <stdlib.h>

typedef struct StackNode{
	Item elem;
	struct StackNode *next;
}StackNode;

typedef StackNode TCelSt; // Redenumirea unui nod la notatiile din curs 
typedef StackNode *ACelSt; // Redenumirea unui pointer la nod la notatiile din curs

typedef struct Stack{
	StackNode* head;  // Varful stivei
	long size; // Numarul de elemente din stiva
}Stack;

typedef Stack TStiva; // Redenumirea stivei la notatiile din curs
typedef Stack *ASt;//  // Redenumirea unui pointer la stiva la notatiile din curs

Stack* createStack(void){
	// TODO: Cerinta 1
	Stack* MyStack = malloc(sizeof(Stack));
	MyStack->head = NULL;
	MyStack->size = 0;
	return MyStack;
}

int isStackEmpty(Stack* stack){
	// TODO: Cerinta 1
	if(stack->head == NULL) {
		return 1;
	}
	return 0;
}

void push(Stack *stack, Item elem){
	// TODO: Cerinta 1
	StackNode* q = malloc(sizeof(StackNode)), *p;
	if(q == NULL) {
		printf("Error");
		exit(1);
	}
	q->elem = elem;
	p = stack->head;
	stack->head = q;
	q->next = p;
	stack->size++;
	//q->next = NULL;
}

Item top(Stack *stack){	
	// TODO: Cerinta 1
	return stack->head->elem;
} 

void pop(Stack *stack){
	// TODO: Cerinta 1
	StackNode* q = stack->head;
	stack->head = stack->head->next;
	free(q);
	stack->size--;
	if(stack->size == 0) {
		stack->head == NULL;
	}
}

void destroyStack(Stack *stack){
	// TODO: Cerinta 1
	StackNode* q = stack->head;
	while(stack->size != 0) {
		stack->head = stack->head->next;
		free(q);
		q = stack->head;
		stack->size--;
	}
	free(stack);
}

#endif 
