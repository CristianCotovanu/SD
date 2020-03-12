
#ifndef AVLTREE_H_
#define AVLTREE_H_

#include<stdlib.h>

// An AVL tree node
typedef struct AVLNode {
    Item elem;
    int height;
    struct AVLNode *l;
    struct AVLNode *r;
    struct AVLNode *p;

} AVLNode;

typedef struct AVLTree {
    long size;
    AVLNode *root;
    AVLNode *nil;

    int (*comp)(Item a, Item b);
} AVLTree;

AVLTree *avlCreateTree(int (*comp)(Item1, Item1)) {
    AVLTree *newTree = (AVLTree *) malloc(sizeof(AVLTree));
    newTree->comp = comp;
    newTree->nil = (AVLNode *) malloc(sizeof(AVLNode));
    newTree->nil->p = newTree->nil->l = newTree->nil->r = newTree->nil;
    newTree->nil->height = 0;
    newTree->root = (AVLNode *) malloc(sizeof(AVLNode));
    newTree->root->p = newTree->root->l = newTree->root->r = newTree->nil;
    newTree->root->height = 0;
    newTree->size = 0;

    return newTree;
}

int avlIsEmpty(AVLTree *tree) {
    return (tree->root->l == tree->nil);
}

AVLNode *avlNewNode(AVLTree *tree) {
    AVLNode *newNode = (AVLNode *) malloc(sizeof(AVLNode));
    // Initialize the new node to be used in the tree
    newNode->p = newNode->r = newNode->l = tree->nil;
    newNode->height = 1;

    return newNode;
}


// A utility function to get maximum of two integers
int max(int a, int b) {
    return (a > b) ? a : b;
}

// A utility function to right rotate subtree rooted with y
void avlRightRotate(AVLTree *tree, AVLNode *y) {
    AVLNode *parent = y->p, *T = y->l;

    y->l = T->r;
    if (T->r != tree->nil) {
        T->r->p = y;
    }

    y->height = max(y->l->height, y->r->height) + 1;
    T->r = y;
    y->p = T;
    T->height = max(T->l->height, T->r->height) + 1;
    T->p = parent;

    if (parent != tree->root) {

        if (parent->r == y) {
            parent->r = T;
        } else {
            parent->l = T;
        }
    } else {
        tree->root->l = T;
    }
}

// A utility function to left rotate subtree rooted with x
void avlLeftRotate(AVLTree *tree, AVLNode *x) {
    AVLNode *parent = x->p, *T = x->r;
    x->r = T->l;

    if (T->l != tree->nil) {
        T->l->p = x;
    }

    x->height = max(x->l->height, x->r->height) + 1;
    T->l = x;
    x->p = T;
    T->height = max(T->l->height, T->r->height) + 1;
    T->p = parent;

    if (parent != tree->root) {
        if (parent->r == x) {
            parent->r = T;
        } else {
            parent->l = T;
        }
    } else {
        tree->root->l = T;
    }
}

// Get Balance factor of node x
int avlGetBalance(AVLNode *x) {
    if (x == NULL)
        return 0;
    return x->l->height - x->r->height;
}

AVLNode *avlMinimum(AVLTree *tree, AVLNode *x) {
    while (x->l != tree->nil)
        x = x->l;
    return x;
}

AVLNode *avlMaximum(AVLTree *tree, AVLNode *x) {
    while (x->r != tree->nil) {
        x = x->r;
    }
    return x;
}


AVLNode *Insert_aux(AVLTree *tree, AVLNode *inserted_node, Item x) {
    if (inserted_node == tree->nil) {
        AVLNode *new_node = avlNewNode(tree);
        new_node->elem = x;
        tree->size++;
        return new_node;
    } else {
        if (tree->comp(x, inserted_node->elem) <= 0) {
            inserted_node->l = Insert_aux(tree, inserted_node->l, x);
            inserted_node->l->p = inserted_node;
        } else {
            inserted_node->r = Insert_aux(tree, inserted_node->r, x);
            inserted_node->r->p = inserted_node;
        }
    }

    inserted_node->height = (max(inserted_node->l->height, inserted_node->r->height)) + 1;
    int aux_balance = avlGetBalance(inserted_node);

    //Caz dreapta-dreapta
    if (aux_balance < -1 && tree->comp(x, inserted_node->r->elem) > 0) {
        AVLNode *Tr = inserted_node->r;
        avlLeftRotate(tree, inserted_node);
        return Tr;
    } 
    //Caz dreapta-stanga
    else if (aux_balance < -1 && tree->comp(x, inserted_node->r->elem) <= 0) {
        avlRightRotate(tree, inserted_node->r);
        AVLNode *Tr = inserted_node->r;
        avlLeftRotate(tree, inserted_node);
        return Tr;
    }
    //Caz stanga-stanga
    else if (aux_balance > 1 && tree->comp(x, inserted_node->l->elem) <= 0) {
        AVLNode *Tl = inserted_node->l;
        avlRightRotate(tree, inserted_node);
        return Tl;
    }
    //Caz stanga-dreapta
    else if (aux_balance > 1 && tree->comp(x, inserted_node->l->elem) > 0) {
        avlLeftRotate(tree, inserted_node->l);
        AVLNode *Tl = inserted_node->l;
        avlRightRotate(tree, inserted_node);
        return Tl;
    }
    return inserted_node;
}

void avlInsert(struct AVLTree *tree, Item elem) {
    tree->root->l = Insert_aux(tree, tree->root->l, elem);
}

void avlDeleteNode(AVLTree *tree, AVLNode *node) {
    destroyElem(node->elem);
    free(node);
}


void avlDestroyTreeHelper(AVLTree *tree, AVLNode *x) {
    if (x != tree->nil) {
        avlDestroyTreeHelper(tree, x->l);
        avlDestroyTreeHelper(tree, x->r);
        avlDeleteNode(tree, x);
    }
}

void avlDestroyTree(AVLTree *tree) {
    avlDestroyTreeHelper(tree, tree->root->l);
    free(tree->root);
    free(tree->nil);
    free(tree);
}

#endif /* AVLTREE_H_ */
