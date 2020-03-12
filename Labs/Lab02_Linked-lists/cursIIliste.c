#include <stdio.h>
#include <stdlib.h>

typedef char Item;
typedef struct Node
{
    Item elem;
    struct Node *next;
} Node, *List;

void add(List *lst, Item value)
{
    List aux = (List)malloc(sizeof(Node));
    aux->elem = value;
    aux->next = (*lst);
    (*lst) = aux;
}

void addLast(List *lst, Item value)
{
    List last;

    if ((*lst) == NULL)
    {
        add(lst, value);
    }
    else
    {
        last = (*lst);
        while (last->next != NULL)
        {
            last = last->next;
        }
        last->next = (List)malloc(sizeof(Node));
        last->next->elem = value;
        last->next->next = NULL;
    }
}

void deleteList(List *lst)
{
    List aux = (*lst), aux2;
    while (aux != NULL)
    {
        aux2 = aux->next;
        free(aux);
        aux = aux2;
    }
    (*lst) = NULL;
}

void insert_sorted(List *lst, Item value)
{

    if (((*lst) == NULL) || (*lst)->elem > value)
    {
        add(lst, value);
        return;
    }

    List aux = (*lst), aux2 = (*lst)->next;

    while (aux2 != NULL && aux2->elem < value)
    {
        aux = aux->next;
        aux2 = aux2->next;
    }
    List new_node = (List)malloc(sizeof(Node));
    new_node->elem = value;
    new_node->next = aux2;
    aux->next = new_node;
}

List sorted(List lst)
{
    List new_list = NULL;
    while (lst != NULL) {
        insert_sorted(&new_list, lst->elem);
        lst = lst->next;
    }
    return new_list;
}

void printlist(List lst)
{
    while (lst != NULL)
    {
        printf("%d ", lst->elem);
        lst = lst->next;    
    }
    printf("\n");
}

int length(List lst)
{
    int len = 0;
    while (lst != NULL)
    {
        len += 1;
        lst = lst->next;    
    }
    return len;
}

int main(int argc, char *argv[])
{
    List lst = NULL;
    addLast(&lst, 1);
    addLast(&lst, 2);
    addLast(&lst, 3);
    add(&lst, 4);
    addLast(&lst, 5);
    add(&lst, 6);
    printlist(lst);
    List lst2 = sorted(lst);
    printlist(lst2);
    deleteList(&lst);
    return 0;
}
