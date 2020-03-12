#ifndef TREEMAP_H_
#define TREEMAP_H_

#include <stdlib.h>

#define MAX(a, b) (((a) >= (b))?(a):(b))

//-------------------------------------------------------------------------

typedef struct node {
    void *elem; // Node key
    void *info; // Node satellite information
    struct node *pt; // Parent link
    struct node *lt; // left child link
    struct node *rt; // right child link
    struct node *next; // next link in the list of duplicates
    struct node *prev; // prev link in the list of duplicates
    struct node *end; // pointer to the end of the duplicates list
    long height;
} TreeNode;

typedef struct TTree {
    TreeNode *root; // pointer to the root of the tree
    void *(*createElement)(void *); // create element method
    void (*destroyElement)(void *); // destroy element method
    void *(*createInfo)(void *); // create info method
    void (*destroyInfo)(void *); // destroy info method
    int (*compare)(void *, void *); // comparison method between elements
    long size;
} TTree;

int avlGetBalance(TreeNode *x);

void avlFixUp(TTree *tree, TreeNode *y);


//Functii auxiliare pentru debugging
void print_tree(TreeNode *t, int tabs) {
    if (t == NULL) {
        return;
    }
    for (int i = 0; i < tabs; i++) {
        printf("\t");
    }
    printf("%d\n", *((int *) t->elem));
    print_tree(t->lt, tabs + 1);
    print_tree(t->rt, tabs + 1);
}

void print_list_aux(TreeNode *t) {
    while (t != NULL) {
        if (t->elem != NULL)
            printf("%d->", *((int *) t->elem));
        t = t->next;
    }
    printf("\n");
}

void print_list(TreeNode *t) {
    while (t != NULL && t->lt != NULL)
        t = t->lt;
    print_list_aux(t);
}

TTree *createTree(void *(*createElement)(void *), void (*destroyElement)(void *),
                  void *(*createInfo)(void *), void (*destroyInfo)(void *),
                  int compare(void *, void *)) {
    TTree *my_tree = calloc(1, sizeof(TTree));
    my_tree->compare = compare;
    my_tree->createInfo = createInfo;
    my_tree->createElement = createElement;
    my_tree->destroyElement = destroyElement;
    my_tree->destroyInfo = destroyInfo;
    return my_tree;
}

int isEmpty(TTree *tree) {
    return (tree->root == NULL);
}


TreeNode *search(TTree *tree, TreeNode *x, void *elem) {
    TreeNode *aux = x;
    while (aux != NULL) {
        if (tree->compare(aux->elem, elem) == 0) {
            return aux;
        }
        if (tree->compare(aux->elem, elem) > 0) {
            aux = aux->lt;
        } else {
            aux = aux->rt;
        }
    }
    return NULL;
}


TreeNode *minimum(TreeNode *x) {
    //Gaseste ultimul nod din subarborele stang
    while (x->lt != NULL) {
        x = x->lt;
    }
    return x;
}

TreeNode *maximum(TreeNode *x) {
    //Gaseste ultimul nod din subarborele drept
    while (x->rt != NULL) {
        x = x->rt;
    }
    return x;
}

TreeNode *successor(TreeNode *x) {
    TreeNode *aux = x;
    if (x == NULL)
        return NULL;
    if (aux->rt != NULL) {
        return minimum(aux->rt);
    } else {
        while (aux->pt != NULL) {
            if (aux->pt->lt == aux)
                return aux->pt;
            else
                aux = aux->pt;
        }
    }
    return NULL;
}

TreeNode *predecessor(TreeNode *x) {
    TreeNode *aux = x;
    if (x == NULL)
        return NULL;
    if (aux->lt != NULL) {
        return maximum(aux->lt);
    } else {
        while (aux->pt != NULL) {
            if (aux->pt->rt == aux)
                return aux->pt;
            else
                aux = aux->pt;
        }
    }
    return NULL;
}

void updateHeight(TreeNode *x) {
    int leftHeight = 0;
    int rightHeight = 0;
    if (x != NULL) {
        if (x->lt != NULL) leftHeight = x->lt->height;
        if (x->rt != NULL) rightHeight = x->rt->height;
        x->height = MAX(leftHeight, rightHeight) + 1;
    }
}

void avlRotateLeft(TTree *tree, TreeNode *x) {
    TreeNode *aux = x->rt;

    aux->pt = x->pt;
    //Daca exista subarbore stang
    if (aux->lt != NULL) {
        aux->lt->pt = x;
        x->rt = aux->lt;
    } else {
        x->rt = NULL;
    }
    //Daca nodul x este root
    if (x == tree->root) {
        tree->root = aux;
    } else {
        //Copil de dreapta
        if (x->pt->rt == x) {
            x->pt->rt = aux;
        } else {
            //Copil de stanga
            x->pt->lt = aux;
        }
    }
    aux->lt = x;
    x->pt = aux;
    updateHeight(x);
    updateHeight(aux);
}

void avlRotateRight(TTree *tree, TreeNode *y) {
    TreeNode *aux = y->lt;

    aux->pt = y->pt;
    //Daca exista subarbore drept
    if (aux->rt != NULL) {
        aux->rt->pt = y;
        y->lt = aux->rt;
    } else {
        y->lt = NULL;
    }
    //Daca nodul y este root
    if (y == tree->root) {
        tree->root = aux;
    } else {
        //Copil de dreapta
        if (y->pt->rt == y) {
            y->pt->rt = aux;
        } else {
            //Copil de stanga
            y->pt->lt = aux;
        }
    }
    aux->rt = y;
    y->pt = aux;
    updateHeight(y);
    updateHeight(aux);
}

/* Get AVL balance factor for node x */
int avlGetBalance(TreeNode *x) {
    //Presupunem ca sunt 0, nu exista subarbori pentru nodul X
    int left_h = 0, right_h = 0;
    if (x == NULL) {
        return 0;
    }
    //Daca x are subarbore drept, modificam inaltimea pe dreapta
    if (x->rt != NULL) {
        right_h = x->rt->height;
    }
    //Daca x are subarbore stang, modificam inaltimea pe stanga
    if (x->lt != NULL) {
        left_h = x->lt->height;
    }
    return left_h - right_h;
}

TreeNode *createTreeNode(TTree *tree, void *value, void *info) {
    // Allocate node
    TreeNode *newNode = (TreeNode *) malloc(sizeof(TreeNode));

    // Set its element field
    newNode->elem = tree->createElement(value);

    //Set its info
    newNode->info = tree->createInfo(info);

    // Set its tree links
    newNode->pt = newNode->rt = newNode->lt = NULL;

    // Set its list links
    newNode->next = newNode->prev = newNode->end = NULL;
    /*
     *  The height of a new node is 1,
     *  while the height of NULL is 0
     */
    newNode->height = 1;

    return newNode;
}

void destroyTreeNode(TTree *tree, TreeNode *node) {
    // Check arguments
    if (tree == NULL || node == NULL) return;

    // Use object methods to de-alocate node fields
    tree->destroyElement(node->elem);
    tree->destroyInfo(node->info);

    // De-allocate the node
    free(node);
}

void avlFixUp(TTree *tree, TreeNode *y) {
    int balance = avlGetBalance(y);
    if (y->lt != NULL && y->lt->lt != NULL && balance > 1
        && tree->compare(y->lt->lt->elem, y->lt->elem) < 0) {
        avlRotateRight(tree, y);
        return;
    }
    if (y->rt != NULL && y->rt->rt != NULL) {
        if (balance < -1 && tree->compare(y->rt->rt->elem, y->rt->elem) > 0) {
            avlRotateLeft(tree, y);
            return;
        }
    }
    if (y->rt != NULL && y->rt->lt != NULL) {
        if (balance < -1 && tree->compare(y->rt->lt->elem, y->rt->elem) < 0) {
            avlRotateRight(tree, y->rt);
            avlRotateLeft(tree, y);
            return;
        }
    }
    if (y->lt != NULL && y->lt->rt != NULL) {
        if (balance > 1 && tree->compare(y->lt->rt->elem, y->lt->elem) > 0) {
            avlRotateLeft(tree, y->lt);
            avlRotateRight(tree, y);
            return;
        }
    }
}

void insert(TTree *tree, void *elem, void *info) {
    //Nu exista un tree
    if (tree == NULL) {
        return;
    }
    TreeNode *my_node = createTreeNode(tree, elem, info);
    my_node->end = my_node;
    //Arbore gol, nodul devine radacina
    if (tree->root == NULL) {
        tree->root = my_node;
        tree->size = 1;
        return;
    }

    TreeNode *aux, *prev = NULL;
    aux = tree->root;
    //Se gaseste locul de insertie
    while (aux != NULL) {
        prev = aux;
        if (tree->compare(aux->elem, elem) < 0) {
            aux = aux->rt;
        } else if (tree->compare(aux->elem, elem) > 0) {
            aux = aux->lt;
        } else {
            aux = prev;
            //Nodul cu 'elem' deja exista => se va adauga in lista cu duplicate
            my_node->next = aux->end->next;
            my_node->prev = aux->end;
            aux->end->next = my_node;
            //Daca nu este ultimul nod din arbore
            if (my_node->next != NULL) {
                my_node->next->prev = my_node;
            }
            aux->end = my_node;
            return;
        }
    }
    //Copil de stanga
    if (tree->compare(prev->elem, elem) > 0) {
        TreeNode *pred = predecessor(prev);
        TreeNode *succ = prev;
        my_node->pt = prev;
        prev->lt = my_node;

        if (pred != NULL) {
            my_node->prev = pred->end;
            pred->end->next = my_node;
        }
        if (succ != NULL) {
            my_node->end->next = succ;
            succ->prev = my_node;
        }
        tree->size++;
        updateHeight(prev);
    } else {
        //Copil de dreapta
        TreeNode *pred = prev;
        TreeNode *succ = successor(prev);

        my_node->pt = prev;
        prev->rt = my_node;

        if (pred != NULL) {
            my_node->prev = pred->end;
            pred->end->next = my_node;
        }
        if (succ != NULL) {
            my_node->next = succ;
            succ->prev = my_node;
        }
        tree->size++;
        updateHeight(prev);
    }
    //Rebalansare arbore
    if (tree->root != NULL) {
        TreeNode *max, *min;
        min = minimum(tree->root);
        max = maximum(tree->root);
        while (min != NULL) {
            avlFixUp(tree, min);
            min = min->pt;
        }
        while (max != NULL) {
            avlFixUp(tree, max);
            max = max->pt;
        }
    }
}

void delete(TTree *tree, void *elem) {
    TreeNode *to_delete, *spliced, *child,
            *node = search(tree, tree->root, elem);
    if (node == NULL) {
        return;
    }
    //Caz element duplicat, stergere din lista
    if (node != node->end) {
        if (node->end->next != NULL) {
            node->end->next->prev = node->end->prev;
        }
        if (node->end->prev != NULL) {
            node->end->prev->next = node->end->next;
        }

        to_delete = node->end;
        destroyTreeNode(tree, to_delete);
        tree->size--;
        return;
    }
    if ((node = search(tree, tree->root, elem)) == NULL) {
        return;
    }

    spliced = ((node->lt == NULL) || (node->rt == NULL))
              ? node : successor(node);
    child = (spliced->lt == NULL) ? spliced->rt : spliced->lt;

    if (tree->root == (spliced->pt)) {
        if (tree->compare(spliced->elem, tree->root->elem) == 1) {
            tree->root->rt = child;
        }
        if (tree->compare(spliced->elem, tree->root->elem) == -1) {
            tree->root->lt = child;
        }
        if (child != NULL) {
            child->pt = spliced->pt;
        }
    } else if (spliced->pt != NULL && spliced == spliced->pt->lt) {
        spliced->pt->lt = child;
    } else if (spliced->pt != NULL) {
        spliced->pt->rt = child;
    }

    if (spliced != node) {
        spliced->lt = node->lt;
        spliced->rt = node->rt;
        spliced->pt = node->pt;
        if (node->rt != NULL) {
            node->rt->pt = spliced;
        }
        if (node->lt != NULL) {
            node->lt->pt = spliced;
        }
        if (node->pt != NULL) {
            if (node == node->pt->lt)
                node->pt->lt = spliced;
            else
                node->pt->rt = spliced;
        }
        if (node == tree->root) {
            tree->root = spliced;
        }
        destroyTreeNode(tree, node);
    } else {
        destroyTreeNode(tree, spliced);
    }
    tree->size--;
    if (tree->size == 0) {
        tree->root = NULL;
    }
    if (tree->root != NULL) {
        TreeNode *max, *min;
        min = minimum(tree->root);
        max = maximum(tree->root);
        while (min != NULL) {
            avlFixUp(tree, min);
            min = min->pt;
        }
        while (max != NULL) {
            avlFixUp(tree, max);
            max = max->pt;
        }
    }
}

void Free(TTree *tree, TreeNode *node) {
    if (node != NULL) {
        Free(tree, node->lt);
        Free(tree, node->rt);
        free(node);
    }
}

void destroyTree(TTree *tree) {
    TreeNode *aux = tree->root;
    Free(tree, aux);
    free(tree->root);
    free(tree);
}

#endif /* TREEMAP_H_ */
