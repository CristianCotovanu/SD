#ifndef __HEAP_H__
#define __HEAP_H__

#include <stdlib.h>
#include <math.h>

/* We assume there is a defined primitive type Item. */
typedef struct {
	int prior; // Item priority
	Item data; // Item d
}ItemType;

typedef struct heap{
	long maxHeapSize; // capacity
	long size; // number of elements
	ItemType *elem; // array of elements
} PriQueue, *APriQueue;


PriQueue* makeQueue(int maxHeapSize){
	PriQueue *Q = (PriQueue*) calloc(1,sizeof(PriQueue));
	Q->maxHeapSize = maxHeapSize;
	Q->elem = (ItemType*) calloc(maxHeapSize,sizeof(ItemType));
	Q->size = 0;
	return Q;
}

int getLeftChild(int i){
	return 2*(i + 1) - 1;
}

int getRightChild(int i) {
	return 2*(i + 1);
}

int getParent(int i) {
	return (i - 1)/2;
}

ItemType getMax(APriQueue h) {
	return h->elem[0];
}

void siftUp(APriQueue h, int idx) {
	int k = idx;
	while ( k != 0 ){
		if( h->elem[getParent(k)].prior < h->elem[k].prior ){
			ItemType aux = h->elem[getParent(k)];
			h->elem[getParent(k)] = h->elem[k];
			h->elem[k] = aux;
			k = getParent(k);
		}
		else{
			k = 0;
		}
	}
}


void insert(PriQueue *h, ItemType x) {
	if( h->size + 1 > h->maxHeapSize ){
		h->elem = (ItemType*) realloc(h->elem,(h->maxHeapSize+1)*sizeof(ItemType));
		h->maxHeapSize++;
	}
	h->elem[h->size++] = x;
	siftUp(h,h->size - 1);
}

void siftDown(APriQueue h, int idx){
	int k;
	int s = idx;
	do{
		k = s;
		if ( getLeftChild(k) < h->size){
			if( h->elem[s].prior < h->elem[getLeftChild(k)].prior )
				s = getLeftChild(k);
			if( getRightChild(k) < h->size && 
						h->elem[s].prior < h->elem[getRightChild(k)].prior){
				s = getRightChild(k);
			}
		}
		if (k != s){
			ItemType aux = h->elem[k];
			h->elem[k] = h->elem[s];
			h->elem[s] = aux;

		}
	}while( k != s );
}

void removeMax(APriQueue h) {
	if (h->size > 0){
		h->elem[0] = h->elem[h->size - 1];
		h->size--;
		siftDown(h,0);
	}
}

void freeQueue(APriQueue h){
	free(h->elem);
	free(h);
}

#endif

