#ifndef ORDERED_SET_H
#define ORDERED_SET_H

#include <stdio.h>                                          // needed for printf
#include <stdlib.h>                           // needed for alloc, realloc, free

/*
  IMPORTANT!

  As we stick to pure C, we cannot use templates. We will just asume
  some type T was previously defined.
*/

// -----------------------------------------------------------------------------

/*
  OrderedSet represents a set with elements of type T stored in memory
  in an ordered fashion.
*/

typedef struct OrderedSet {
  T* elements;                    // pointer to where the elements are in memory
  long size;                                // the number of elements in the set
  long capacity;                      // the current capacity (allocated memory)
} OrderedSet;

// -----------------------------------------------------------------------------

/*
  Function that creates an OrderedSet with elements of type T with a given
  initial capacity.
*/

OrderedSet* createOrderedSet(long initialCapacity) {

  OrderedSet* newSet = (OrderedSet*) malloc(sizeof(OrderedSet));

  newSet->size = 0;                        // initially, the set is empty
  newSet->capacity = initialCapacity;
  newSet->elements = (T*) malloc(initialCapacity * sizeof(T));

  return newSet;
}

// -----------------------------------------------------------------------------

/*
  Function that checks if an element exists in a given set. As the
  elements of the set are ordered in memory, this function uses binary
  search.

  Function returns 1 if the given element exists in the set, and 0
  otherwise.
*/

short empty(OrderedSet *set){
  return set->size == 0 ? 1 : 0;
}

int contains(OrderedSet* set, const T element) {
  // TODO : Cerința 2
  int first, last;
  first = 0;
  last = set->size - 1;

  while(last >= first) {
      int middle = (last + first)/2;
      if(set->elements[middle] == element) {
        return 1;
      }
      else if(element < set->elements[middle]) {
        last = middle - 1;
      }
      else {
        first = middle + 1;
      }
  }
  return 0;
}

// -----------------------------------------------------------------------------

/*
  Function that adds a new element to a set. If the element was
  already in the set, nothing changes. Otherwise, the element is added
  to the set. In the end, the elements must be in ascending order.
*/

void removeNum(OrderedSet* set, const T newElement) {
	int i, k;

	for(i = 0; i < set->size; i++)
		if(set->elements[i] == newElement)
			k = i;

	for(i = k; i < set->size; i++) {
			set->elements[i] = set->elements[i + 1];
	}
	set->size--;

}

void add(OrderedSet* set, const T newElement) {
  // TODO : Cerința 2
  if(contains(set,newElement))
    return;

  int i = set->size - 1;
  while(set->elements[i] > newElement && i >= 0){
    set->elements[i + 1] = set->elements[i];
    i--;
  }
  set->elements[++i] = newElement;
  set->size++;
}

// -----------------------------------------------------------------------------

/*
  This function takes two ordered sets with elements of type T and it
  returns the addres of a new ordered set representing the union of
  the two
*/

OrderedSet* unionOrderedSets(OrderedSet* s1, OrderedSet* s2) {
  // TODO : Cerința 3
  OrderedSet *unitedSet = createOrderedSet(s1->capacity + s2->capacity);
 	
 	int i;
 	for (i = 0; i < s1->size; i++) {
 		add(unitedSet, s1->elements[i]);
 	}
 	for (i = 0; i < s2->size; i++) {
 		add(unitedSet, s2->elements[i]);
 	}

 	return unitedSet;
}

// -----------------------------------------------------------------------------

/*
  This function takes two ordered sets with elements of type T and it
  returns the addres of a new ordered set representing the
  intersection of the two
*/

OrderedSet* intersectOrderedSets(OrderedSet* s1, OrderedSet* s2) {
  // TODO : Cerința 3
	long min = s2->size;
	if(s1->size < s2->size)
		min = s1->size;

  OrderedSet *intersectedSet = createOrderedSet(min);

  int i;
  for (i = 0; i < s1->size; i++) {
  	if (contains(s2, s1->elements[i]) == 1)
  		add(intersectedSet, s1->elements[i]);
  }

  return intersectedSet;
}

// -----------------------------------------------------------------------------

#endif
