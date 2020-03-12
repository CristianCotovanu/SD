#ifndef _DOUBLE_LINKED_LIST_H_
#define _DOUBLE_LINKED_LIST_H_
#include <stdlib.h>
/*
  IMPORTANT!

  As we stick to pure C, we cannot use templates. We will just asume
  some type T was previously defined.
*/

// -----------------------------------------------------------------------------
/**
 *  Linked list representation -- R2 Curs2 (Slide 8)
 */
typedef struct ListNode{
	Item elem; // Stored node value
	struct ListNode* next; // link to next node
	struct ListNode* prev; // link to prev node
} ListNode;

/**
 *  Double linked list representation -- desen Curs 3 (Slide 19)
 */
typedef struct List{
	ListNode* first; // link to the first node
	ListNode* last; // link to the last node
}List;
// -----------------------------------------------------------------------------

/**
 * Create a new (empty)  list  -- Silde-urile 13/14 Curs 2
 *  [input]: None
 *  [output]: List*
 */
List* createList(void){
	List* t;
	t = (List*)malloc(sizeof(List));
	t->first = NULL;
	t->last = NULL;

		return t;
}
// -----------------------------------------------------------------------------

/**
 * Determines if the list is empty
 *  [input]: List*
 *  [output]: 1 - empty/ 0 - not empty
 */
int isEmpty(List *list){
	// TODO: Cerinta 1b
	if(list->first == NULL)
		return 1;
	return 0;
}
// -----------------------------------------------------------------------------


/**
 * Determines if a list contains a specified element
 *  [input]: List*, Item
 *  [output]: int (1 - contains/ 0 - not contains)
 */
int contains(List *list, Item elem){
	// TDOO: Cerinta 1c
	ListNode* u;
	u = list->first;
	while(u != NULL) {
		if(u->elem == elem)
		return 1;
		u = u->next;		
	}
	return 0;
}
// -----------------------------------------------------------------------------


/**
 * Insert a new element in the list at the specified position.
 * Note: Position numbering starts with the position at index zero
 *  [input]: List*, Item, int
 *  [output]: void */
int length(List *list){
	// Guard against young player errors
	if(list == NULL) return 0;

 	ListNode* u = list->first;
	// TODO: Cerinta 1f
	int len = 0;
	while(u != NULL) {
		len++;
		u = u->next;
	}
	return len;
}

void insertAt(List* list, Item elem, int pos){
	// Guard against young player errors
	if(list == NULL) return;

	// TODO: Cerinta 1d
	
	if(pos < 0 || pos > length(list)) {
		return;
	}
	ListNode* u, *t = (ListNode*)malloc(sizeof(ListNode));
	u = list->first;
	t->elem = elem;
	t->next = NULL;
	t->prev = NULL;
	if(u == NULL && pos == 0) {
		t->next == NULL;
		t->prev == NULL;
		list->first = list->last = t;
		return;
	}
	if (pos == 0) {
		t->prev = NULL;
		t->next = u;
		u->prev = t;
		list->first = t;
		return;
	}
	if (pos == length(list)) {
		t->next = NULL;
		t->prev = list->last;
		list->last->next = t;
		list->last = t;
		return;
	}
	int i;
	for(i = 0; i < pos && u != NULL; i++) {
		u = u->next;
	}
	t->prev = u->prev;
	t->next = u;
	u->prev->next = t;
	u->prev = t;
	return;

}
// -----------------------------------------------------------------------------


/**
 * Delete the first element instance form a list.
 *  [input]: List*, Item
 *  [output]: void
 */
void deleteOnce(List *list, Item elem){
	// Guard against young player errors
	if(list == NULL) return;

	//TODO: Cerinta 1e
	ListNode *u;
	u = list->first;
	/*if(u->next == NULL && u->elem == elem) {
		list->first = NULL;
		list->last = NULL;
		free(u);
		return;
	}*/
	/*int i;
	for(i = 0; i < length(list); i++) {
		if (u->elem == elem)
		u = u->next;
			break;
	}*/
	while (u != NULL) {
		if (u->elem == elem)
			break;
		u = u->next;
	}
	if( u != NULL ){
	/*if(u->prev == NULL) {
		list->first = u->next;
		u->next->prev = NULL;
		free(u);
		return;
	}
	if(u->next == NULL) {
		list->last == u->prev;
		u->prev->next == NULL;
		free(u);
		return;
	}
	u->next->prev = u->prev;
	u->prev->next = u->next;
	*///free(u);
		if (u->next != NULL) {
			u->next->prev = u->prev;
		}
		if(u->prev != NULL) {
			u->prev->next = u->next;
		}
		if (u == list->first) {
			list->first = u->next;
		}	
		if(u == list->last) {
			list->last = u->prev;
		}
	}
	return;
}
// -----------------------------------------------------------------------------


/**
 * Compute list length
 *  [input]: List*
 *  [output]: int
 */

// -----------------------------------------------------------------------------



/**
 * Destroy a list.
 *  [input]: List*
 *  [output]: void
 */
void destroyList(List* list){
	// Guard against young player errors
	if(list == NULL) return;

	//TODO: Cerinta 1g
	ListNode* u, *aux;
	u = list->first;
	while(u != NULL) {
		aux = u;
		u = u->next;
		free(aux);
	}
	list->first = list->last = NULL;
	free(list);
}
// -----------------------------------------------------------------------------


#endif //_DOUBLE_LINKED_LIST_H_
