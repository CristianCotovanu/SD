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

typedef struct SortedList {
  T value;
  struct SortedList* next;
} SortedList;

// TODO : Cerința 1 & Cerința 2

void init(SortedList **list){
  *list = NULL;
}

int isEmpty(SortedList *list){
  if(list == NULL)
    return 1;
  return 0;
}

int contains(SortedList *list,T value){
    SortedList *q;
    for(q = list; q != NULL; q = q->next)
      if(q->value == value)
        return 1;
    return 0;
}

void insert(SortedList **list,T value){
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

void deleteOnce(SortedList **list,T value){
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

long length(SortedList *list){
  long cnt = 0;
  while(list != NULL){
    cnt++;
    list = list->next;
  }
  return cnt;
}

T getNth(SortedList *list,long N){
  int i;
  for(i = 0; i < N - 1 && list; i++)
    list = list->next;

  if(!list){
    printf("ERROR::List is too small\n");
    return -1;
  }
  return list->value;
}

void freeSortedList(SortedList **list){
  SortedList *aux;
  while(*list != NULL){
    aux = *list;
    *list = (*list)->next;
    free(aux);
  }
}

#endif
