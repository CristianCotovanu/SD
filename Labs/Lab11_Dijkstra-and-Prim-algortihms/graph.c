#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
//#include "heap.h"

typedef int TCost;
#define inf 9999

typedef struct node
{
	int v;
	TCost c;
	struct node *next;
} TNode, *ATNode;

typedef struct
{
	int nn;
	ATNode *adl;
}	TGraphL;


void alloc_list(TGraphL * G, int n)
{
    int i;
    G->nn = n;
	G->adl = (ATNode*) malloc((n+1)*sizeof(ATNode));
	for(i = 0; i < n; i++)
		G->adl[i] = NULL;

}

void free_list(TGraphL *G)
{
    int i;
    ATNode it;
    for(i = 1; i < G->nn; i++){
		it = G->adl[i];
		while(it != NULL){
			ATNode aux = it;
			it = it->next;
			free(aux);
		}
		G->adl[i] = NULL;
	}
	G->nn = 0;
}

void insert_edge_list(TGraphL *G, int v1, int v2, int c)
{
 TNode *t;
 t=(ATNode)malloc(sizeof(TNode));
 t->v = v2; t->c=c; t->next = G->adl[v1]; G->adl[v1]=t;
 t=(ATNode)malloc(sizeof(TNode));
 t->v = v1;  t->c=c; t->next = G->adl[v2]; G->adl[v2]=t;
}

void dijkstra(TGraphL G, int s)
{
    int d[9], m[9], min, k = 0, i, j;
    TNode *aux;
	
	for (i = 0; i < G.nn; i++) {
		d[i] = inf;
		m[i] = 0;
	 	}

    d[s] = 0;
    m[s] = 1;
    int start = 0;
	while (k == 0) {
		k = 1;
		for(j = 0; j < G.nn; j++) {
			if (m[j] == 0) {
				min = j;
				break;
			}
		}
		for (i = 0; i < G.nn; i++) {
			if ( start == 0) {
				start = 1;
				min = s;
			}

			if (m[i] == 0 && d[i] < d[min]) {
				min = i;
			}
		}

		m[min] = 1;
		aux = G.adl[min];
		
		while (aux != NULL) {
			if ((d[min] + aux->c) < d[aux->v]) {
				d[aux->v] = d[min] + aux->c;
			}
			aux = aux->next;
		}

		for (i = 0; i < G.nn; i++) {
			if (m[i] == 0) 
				k = 0;
		}

		printf("%s    %s\n", "Varf", "Drum Minim");
		for (i = 0; i < G.nn; i++) {
			printf("%d	%d\n", i, d[i]);
		}
	}
	printf("\n");
}



void Prim(TGraphL G)
{
        int d[9], m[9], min, k = 0, i, j;
    TNode *aux;
	
	for (i = 0; i < G.nn; i++) {
		d[i] = inf;
		m[i] = 0;
	 	}

	while (k == 0) {
		k = 1;
		for(j = 0; j < G.nn; j++) {
			if (m[j] == 0) {
				min = j;
				break;
			}
		}
		for (i = 0; i < G.nn; i++) {
			if (m[i] == 0 && d[i] < d[min]) {
				min = i;
			}
		}

		m[min] = 1;
		aux = G.adl[min];
		
		while (aux != NULL) {
			if (aux->c < d[aux->v]) {
				d[aux->v] = aux->c;
			}
			aux = aux->next;
		}

		for (i = 0; i < G.nn; i++) {
			if (m[i] == 0) 
				k = 0;
		}

		printf("%s    %s\n", "Varf", "Parinte");
		for (i = 1; i < G.nn; i++) {
			printf("%d	%d\n", i, d[i]);
		}
	}
	printf("\n");
}


int main()
{
    int i,v1,v2,c;
	int V,E;
	TGraphL G;
	ATNode t;
	freopen ("graph.in", "r", stdin);
	scanf ("%d %d", &V, &E);
	alloc_list(&G, V);

	for (i=1; i<=E; i++)
	{
		scanf("%d %d %d", &v1, &v2, &c);
	    insert_edge_list(&G, v1,v2, c);
	}

	for(i=0;i<G.nn;i++)
	{
    printf("%d : ", i);
    for(t = G.adl[i]; t != NULL; t = t->next)
    printf("%d ",t->v);
    printf("\n");
	}

	dijkstra(G,0);
	Prim(G);

	return 0;
}
