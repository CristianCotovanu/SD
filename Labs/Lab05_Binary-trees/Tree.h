#ifndef TREE_H_D
#define TREE_H_

#include <stdio.h>
#include <stdlib.h>

typedef int Item;

typedef struct Link
  {
    Item  elem;
    struct Link *l;
    struct Link *r;
  } TreeNode;



void Init(TreeNode **t, Item x) {
	*t = calloc(1, sizeof(TreeNode));
   (*t)->elem = x;
   (*t)->l = (*t)->r = NULL;
}
/*
void Insert(TreeNode **t, Item x)
{	
	if(*t == NULL) {
		TreeNode* new_node = (TreeNode*)calloc(1, sizeof(TreeNode));
		new_node->elem = x;
		new_node->l = NULL;
		new_node->r = NULL;
		(*t) = new_node;
	} else if(x > (*t)->elem && (*t)->r == NULL) {
		TreeNode* new_node = (TreeNode*)calloc(1, sizeof(TreeNode));
		if(new_node == NULL) { exit(-1); }
		new_node->elem = x;
		new_node->l = NULL;
		new_node->r = NULL;
		(*t)->r = new_node;
	} else if (x < (*t)->elem && (*t)->l == NULL) {
		TreeNode* new_node = (TreeNode*)calloc(1, sizeof(TreeNode));
		if(new_node == NULL) { exit(-1); }
		new_node->elem = x;
		new_node->l = NULL;
		new_node->r = NULL;
		(*t)->l = new_node;
	} else if(x > (*t)->elem && (*t)->r != NULL) {
		Insert(&((*t)->r), x);
	} else if(x < (*t)->elem && (*t)->l != NULL) {
		Insert(&((*t)->l), x);
	}
}
*/

void Insert(TreeNode **t, Item x) {
	if (*t == NULL) {
		Init(t, x);
		return;
	}
	if ((*t)->elem > x) {
		Insert(&((*t)->l), x);
	} else {
		Insert(&((*t)->r), x);
	}

}

void PrintPostorder(TreeNode *t)
{
	if (t == NULL)
		return;

	PrintPostorder(t->l);
	PrintPostorder(t->r);
	printf("%d ", t->elem);

}

void PrintPreorder(TreeNode *t)
{
	if (t == NULL)
		return;

	printf("%d ", t->elem);
	PrintPreorder(t->l);
	PrintPreorder(t->r);
}

void PrintInorder(TreeNode *t)
{
	if (t == NULL)
		return;

	PrintInorder(t->l);
	printf("%d ", t->elem);
	PrintInorder(t->r);
}

void Free(TreeNode **t)
{
	TreeNode *t1, *t2;
	t1 = (*t)->l;
	t2 = (*t)->r;
	free(*t);
	Free(&t1);
	Free(&t2);
}

int Size(TreeNode* t)
{
	if(t == NULL) {
		return 0;
	} else {
		return 1 + Size(t->r) + Size(t->l);
	}
}

int maxDepth(TreeNode *t)
{	int depthRight, depthLeft;
	if(t == NULL) {
		return 0;
	}
	depthRight = maxDepth(t->r);
	depthLeft = maxDepth(t->l); 
	if(depthRight > depthLeft) {
		return 1 + depthRight;
	} else {
		return 1 + depthLeft;
	}
}

#endif // LINKEDSTACK_H_INCLUDED
