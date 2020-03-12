#include <stdio.h>
#include <stdlib.h>

typedef long T;

#include "OrderedSet.h"

OrderedSet* foo(long a, long b, long num) {

  OrderedSet * newSet = createOrderedSet(b - a); 
  long i;

  for(i = a; i < b; i++) {
    if(i % num == 0)
      add(newSet, i);
  }

  return newSet;
}

void print(OrderedSet *set) {
  int i;

  if(empty(set) == 1) {
    printf("The set is empty\n");
    return;
  }

  for (i = 0; i < set->size; i++) {
    printf("%ld ",  set->elements[i]);
  }
  printf("\n");
}

int main() {
  OrderedSet* a, *b, *U, *I;
  a = foo(4, 25, 3);
  b = foo(5, 30, 4);
  removeNum(a, 6);
  print(a);
  print(b);
  U = unionOrderedSets(a, b);
  I = intersectOrderedSets(a, b);
  print(U);
  print(I);
  free(a);
  free(b);
  free(U);
  free(I);
  return 0;
}