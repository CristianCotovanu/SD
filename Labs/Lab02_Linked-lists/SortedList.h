#ifndef SORTED_LIST_H
#define SORTED_LIST_H

#include <stdlib.h>
#include <assert.h>

/*
  IMPORTANT!
  As we stick to pure C, we cannot use templates. We will just asume
  some type T was previously defined.
*/

// -----------------------------------------------------------------------------

typedef struct tag_SortedList {
	T value;
	struct tag_SortedList *next;
} SortedList;

void init(SortedList** list) {
	*list = NULL;
}

int isEmpty(SortedList* list) {
	if(list == NULL) {
		return 1;
	}
	return 0;
}

int contains(SortedList* list, T element) {

	if(list == NULL) {
		return 0;
	}
	while(list != NULL) {
		if(list->value == element) {
			return 1;
		}
		list = list->next;
	}
	return 0;
}

void insert(SortedList** list, T value) {
	SortedList *p = calloc(1,sizeof(SortedList));
    p->value = value;
    if(*list == NULL || p->value < (*list)->value){
      p->next = *list;
      *list = p;
      return;
    }

    SortedList *q;
    for(q = *list; q->next != NULL; q = q->next)
        if(q->next->value > p->value)
          break;
    
    p->next = q->next;
    q->next = p;
  }
	

void deleteOnce(SortedList **list, T value) {
	if(*list == NULL)
    return;

  SortedList *aux;
  if((*list)->value == value){
    aux = *list;
    *list = (*list)->next;
    free(aux);
    return;
  }

  SortedList *q;
  for(q = *list; q->next != NULL; q = q->next){
    if(q->next->value == value)
      break;
  }
  if(q->next != NULL){
    aux = q->next;
    q->next = q->next->next;
    free(aux);
  }
}

long length(SortedList* list) {
	long len = 0;
	while(list != NULL) {
		len++;
		list = list->next;
	}
	return len;
}

T getNth(SortedList* list, long N) {
	long i;
	for(i = 1; i < N; i++) {
		list = list->next;
	}
	return list->value;
}

void freeSortedList(SortedList** list) {
	SortedList* aux;
	while(*list != NULL) {
		aux = *list;
		*list = (*list)->next;
		free(aux);
	}
}

#endif
