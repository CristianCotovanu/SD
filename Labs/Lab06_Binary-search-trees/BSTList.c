typedef long Item; // Valorile din BST
#include "BST.h"
#include "List.h"

typedef BSTNode* Item2; // Elementele cozii sunt noduri din arbore
#include "Queue.h"


BSTree* buildTree(Item *array, long len);

// -----------------------------------------------------------------------------
List* bstToList(BSTree* tree){ 
	//TODO: Cerinta 3
	BSTNode* aux = tree->root->l;
	Queue *q;
	initQueue(&q);
	Node* list;

	enqueue(q, );

}

void printList(List* list){
	//TODO: Cerinta 3
	Node* list;
	/*while(list->next != NULL) {
		printf("%", list->value);
		list = list->next;
	}*/
}
// -----------------------------------------------------------------------------

int main(void){
	Item array[] = {5,3,2,4,7,6,8};

	BSTree *tree = buildTree(array, sizeof(array)/sizeof(Item));	
	List* list = bstToList(tree);
	
	printList(list);

	destroyTree(tree);

	return 0;
}

BSTree* buildTree(Item *array, long len){
	BSTree* newTree = createTree();
	for(int i = 0; i < len; i++){
		insert(newTree,array[i]);
	}
	return newTree;
}
