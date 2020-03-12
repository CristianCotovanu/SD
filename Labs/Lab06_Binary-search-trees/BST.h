#ifndef BST_H_
#define BST_H_

#include <stdlib.h>
/*
  IMPORTANT!

  As we stick to pure C, we cannot use templates. We will just assume
  some type T was previously defined.
 */

// -----------------------------------------------------------------------------

/*
 * !!!!ATENTION!!!!
 * 1. This implementation uses two sentinels (dummy nodes) root and nil.
 * 2. The convetion is that we always root the tree at root->l (the left of the root sentinel)
 */

typedef struct BSTNode{
	Item elem;
	struct BSTNode *p; // parent - not really needed, but simplifies implementation.
	struct BSTNode *l; // left child.
	struct BSTNode *r; // right child.
}BSTNode;

typedef struct BSTree{
	long size; // This inintially is 0, and is updated by insert/delete
	BSTNode *root; // The sentinel root (a sentinel not the actual root). The actual root node is root->l !
	BSTNode *nil; // The nil sentinel to avoid checks for NULL
}BSTree;

BSTree* createTree() {
	BSTree* tree = calloc(1, sizeof(BSTree));
	//BSTNode* node = calloc(1, sizeof(BSTNode));
	tree->nil = calloc(1, sizeof(BSTNode));
	tree->root = calloc(1, sizeof(BSTNode));
	tree->nil->p = tree->nil;
	tree->nil->l = tree->nil;
	tree->nil->r = tree->nil;
	tree->root->l = tree->nil;
	tree->root->r = tree->nil;
	tree->root->p = tree->nil;
	return tree;
}

int isEmpty(BSTree* tree) {
	if(tree->root->l == tree->nil)
		return 1;
	return 0;
}

void insert(BSTree* tree, Item element) {
	BSTNode* new_node = calloc(1, sizeof(BSTNode)),
	       * tree_aux = tree->root->l,
	       * parent = tree->nil;
	new_node->elem = element;
	new_node->l = tree->nil;
	new_node->r = tree->nil;

	if (isEmpty(tree) == 1) {
		tree->size++;
		tree->root->l = new_node;
		new_node->p = tree->root;
		return;
	}

	while(tree_aux != tree->nil) {
		parent = tree_aux;
		if(element == tree_aux->elem) {
			free(new_node);
			return;
		}
		if(element > tree_aux->elem) {
			tree_aux = tree_aux->r;
		} else {
			tree_aux = tree_aux->l;
		}
	}

	if(parent->elem > element) {
		//parent->r = tree->nil;
		parent->l = new_node;
		new_node->p = parent;
		tree->size++;
		return;
	} else {
		//parent->l = tree->nil;
		parent->r = new_node;
		new_node->p = parent;
		tree->size++;
		return;
	}
}

BSTNode* search(BSTree* tree, Item element) {
	BSTNode* tree_aux = tree->root->l;

	while(tree_aux != tree->nil) {
		if(tree_aux->elem == element) {
			return tree_aux;
		}
		if(tree_aux->elem > element) {
			tree_aux = tree_aux->l;
		} else {
			tree_aux = tree_aux->r;}
	}
	return NULL;
}

BSTNode* minimum(BSTree* tree, BSTNode* node) {
	BSTNode* aux = node;
	while(aux->l != tree->nil) {
		aux = aux->l;
	}
	return aux;
}

BSTNode* maximum(BSTree* tree, BSTNode* node) {
	BSTNode* aux = node;
	while(aux->r != tree->nil) {
		aux = aux->r;
	}
	return aux;
}

BSTNode* successor(BSTree* tree, BSTNode* node) {
	BSTNode* aux = node;

	if(aux == tree->nil) {
		return NULL;
	}
	if(aux->r != tree->nil) {
		return minimum(tree, aux->r);
	} else {
		while(aux->p != tree->root->l) {
			if (aux->p->l == aux) {
				return aux->p;
			} else {
				aux = aux->p;
			}
		}
	}
	return NULL;

}

BSTNode* predecessor(BSTree* tree, BSTNode* node) {
	BSTNode *aux = node;

	if(aux == tree->nil) {
		return NULL;
	}
	if(aux->l != tree->nil) {
		return maximum(tree, aux->l);
	} else {
		while(aux->p != tree->root->r) {
			if (aux->p->r == aux) {
				return aux->p;
			} else {
				aux = aux->p;
			}
		}
	}
	return NULL;
}

void Free(BSTree* tree,BSTNode* node) {

	if(node != tree->nil) {
		Free(tree, node->l);
		Free(tree, node->r);
		free(node);
	}
}

void destroyTree(BSTree* tree) {
	BSTNode* aux = tree->root->l;
	Free(tree, aux);
	free(tree->nil);
	free(tree->root);
	free(tree);
}

void delete(BSTree* tree, Item elem){
	BSTNode* z; // node to be deleted
	BSTNode* y; // Node that is spliced out
	BSTNode* x; // The child of the sliced out node

	// Needed to maintain a similar interface as in the previous labs
	if( (z = search(tree,elem)) == tree->nil)
		return;

	/*
	 * Note:
	 * Case 1: The node has no children
	 * Case 2: The node has one child
	 * Case 3: The node has two children
	 */

	// Are we in cases 1,2 or in case 3
	y = ( (z->l == tree->nil) || (z->r == tree->nil) ) ? z : successor(tree, z);

	// Set x to the child of y
	x = (y->l == tree->nil) ? y->r : y->l;

	/*
	 * Note:
	 * There is no need to check if x is a valid pointer, we have the sentinels!
	 */
	if (tree->root == (x->p = y->p)) // assignment of y->p to x->p is intentional
		tree->root->l = x;
	else if (y == y->p->l)
		y->p->l = x;
	else
		y->p->r = x;

	if (y != z){

		/*
		 * Note:
		 * The data type T might be a very big structure, thus copying the key
		 * from one node to another might be very inefficient. It is better to
		 * modify the actual links.
		 */

		// y is the node to splice out and x is its child
		y->l = z->l;
		y->r = z->r;
		y->p = z->p;
		z->l->p = z->r->p = y;
		if (z == z->p->l) z->p->l = y;
		else z->p->r = y;
		free(z);
	} else {
		free(y);
	}

	tree->size--;
}

#endif /* BST_H_ */

