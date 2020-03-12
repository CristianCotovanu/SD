#include <stdio.h>

typedef int T;
#include "SortedList.h"

SortedList* getNaturals(int A, int B) {
  SortedList* nats;
  int i;
  init(&nats);
  for (i = A; i <= B; i++) {
    insert(&nats, i);
  }
  return nats;
}

SortedList* getPrimes(int N) {
  SortedList* nats = getNaturals(2, N);
  SortedList *p = nats;

  while(!isEmpty(p)){
    SortedList *q = p->next,*aux;
    
    while(!isEmpty(q)){
        aux = q->next;
        if(q->value % p->value == 0)
          deleteOnce(&p,q->value);
        q = aux;
    }
    
    p = p->next;
  }
  return nats;

}

void printInts(SortedList* list) {
  while (!isEmpty(list)) {
    printf("%d ", list->value);
    list = list->next;
  }
  printf("\n");
}

int main(int argc, char* argv[]) {
  printInts(getPrimes(100));
  return 0;
}
