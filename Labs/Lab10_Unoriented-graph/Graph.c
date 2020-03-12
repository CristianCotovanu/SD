#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "Util.h"
#include "Graph.h"

TGraphL* createGraphAdjList(int numberOfNodes) {
	TGraphL *my_g = calloc(1, sizeof(TGraphL));
	my_g->adl = calloc(numberOfNodes, sizeof(TNode*));
	my_g->nn = numberOfNodes;
	return my_g;
}

void addEdgeList(TGraphL* graph, int v1, int v2) {
	TNode *node_v1 = calloc(1, sizeof(TNode)),
		  *node_v2 = calloc(1, sizeof(TNode));
	node_v1->v = v1;
	node_v2->v = v2;

	node_v1->next = graph->adl[v2];
	graph->adl[v2] = node_v1;

	node_v2->next = graph->adl[v1];
	graph->adl[v1] = node_v2;
}

List* dfsIterative(TGraphL* graph, int s) {
	Stack* my_s = createStack();
	List *my_list = createList();
	int *visited = calloc(graph->nn, sizeof(int)), n;
	TNode* aux;
	n = s;
	visited[s] = 1;
	push(my_s, s);
	while (isStackEmpty(my_s) != 1) {
	    n = top(my_s);
        push(my_list, n);
	    pop(my_s);

		aux = graph->adl[n];
        while(aux != NULL) {
            if (visited[aux->v] != 1) {
                push(my_s, aux->v);
                visited[aux->v] = 1;
            }
            aux = aux->next;
        }
	}
    free(visited);
	return my_list;
}

void dfsRecHelper(TGraphL* graph, int* visited, List* path, int s) {
    visited[s] = 1;
    push(path, s);
    TNode *aux = graph->adl[s];
    while (aux != NULL) {
        if (visited[aux->v] == 0) {
            dfsRecHelper(graph, visited, path, aux->v);
        }
        aux = aux->next;
    }
}

List* dfsRecursive(TGraphL* graph, int s) {
    int *visited = calloc(graph->nn, sizeof(int));
    List *my_l = createList();
    dfsRecHelper(graph, visited, my_l, s);
    return my_l;
}

List* bfs(TGraphL* graph, int s){
    Queue* my_q = createQueue();
    List *my_list = createList();
    int *visited = calloc(graph->nn, sizeof(int)), n;
    TNode* aux;
    n = s;
    visited[s] = 1;
    enqueue(my_q, s);
    while (isQueueEmpty(my_q) != 1) {
        n = front(my_q);
        push(my_list, n);
        dequeue(my_q);
        aux = graph->adl[n];
        while(aux != NULL) {
            if (visited[aux->v] != 1) {
                enqueue(my_q, aux->v);
                visited[aux->v] = 1;
            }
            aux = aux->next;
        }
    }
    free(visited);
    return my_list;
}


void destroyGraphAdjList(TGraphL* graph){
	// TODO: 5
}

void removeEdgeList(TGraphL* graph, int v1, int v2){
	TNode* it = graph->adl[v1];
	TNode* prev = NULL;
	while(it != NULL && it->v != v2){
		prev = it;
		it = it->next;
	}

	if(it == NULL)return;

	if(prev != NULL)
		prev->next = it->next;
	else
		graph->adl[v1] = it->next;
	free(it);

	it = graph->adl[v2];
	prev = NULL;
	while(it != NULL && it->v != v1){
		prev = it;
		it = it->next;
	}
	if(it == NULL) return;
	if(prev != NULL)
		prev->next = it->next;
	else
		graph->adl[v2] = it->next;

	free(it);
}

void removeNodeList(TGraphL* graph, int v){
	for(int i = 0; i < graph->nn;i++){
		removeEdgeList(graph,v,i);
	}
}
