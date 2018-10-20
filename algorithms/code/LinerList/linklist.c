#include<stdio.h>
#include<stdlib.h>

#define TRUE 1
#define FALSE 0
#define ERROR -1
#define ERROR_HAPEN(str) {printf("%s\n", str); exit(0);}
typedef int ElemType;
typedef int status;

typedef struct Node{
    ElemType data;
    struct Node* next;
}Node;
typedef Node* LinkList;


status list_init(LinkList* L);
status list_create_head(LinkList L, ElemType collection[], int length);
status list_create_tail(LinkList L, ElemType collection[], int length);
status list_insert(LinkList L, ElemType value, int index);
status list_delete(LinkList L, ElemType *value, int index);
void list_print(LinkList L);
status list_clear(LinkList L);
status list_destroy(LinkList *L);

int main(void)
{
    LinkList L;
    ElemType collection[5] = {1,2,3,4,5};
    int length = 5;
    list_init(&L);
    list_create_tail(L, collection, length);
    list_print(L);
    list_insert(L,3, 3);
    list_print(L);
    ElemType del_value;
    list_delete(L, &del_value, 4);
    list_print(L);

    list_destroy(&L);

    return 0;
}
status list_init(LinkList* L)
{
    *L = (LinkList) malloc(sizeof(Node));
    (*L)->data = -1;
    (*L)->next = NULL;

    if(*L == NULL) return FALSE;
    else           return TRUE;
}
status list_create_head(LinkList L, int collection[], int length)
{
    Node* node;
    int i;
    for(i = 0; i < length; i++)
    {
        node = (Node*)malloc(sizeof(Node));
        if(node == NULL) ERROR_HAPEN("malloc fail")
        node->data = collection[i];
        node->next = L->next;
        L->next = node;
    }

    return TRUE;
}
status list_create_tail(LinkList L, int collection[], int length)
{
    Node* node, *current;
    int i;
    for(current = L; current->next != NULL; current = current->next);
    for(i = 0; i < length; i++)
    {
        node = (Node*)malloc(sizeof(Node));
        if(node == NULL) ERROR_HAPEN("malloc fail")
        node->data = collection[i];
        node->next = NULL;
        current->next = node;
        current = current->next;
    }

    return TRUE;
}
status list_insert(LinkList L, ElemType value, int index)
{
    Node* current, *node;
    int i;

    for(i = 1, current = L;
        current->next != NULL && i < index;
        i++, current = current->next);
    if(i != index) return FALSE;

    node = (Node*)malloc(sizeof(Node));
    if(node == NULL) ERROR_HAPEN("malloc fail")
    node->data = value;
    node->next = current->next;
    current->next = node;

    return TRUE;
}
status list_delete(LinkList L, ElemType *value, int index)
{
    Node* current, *del;
    int i;
    for(i = 1, current = L; current->next !=NULL && i < index; current = current->next) i++;
    if(i != index) return FALSE;
    
    del = current->next;
    *value = del->data;
    current->next = del->next;
    free(del);
}
status list_clear(LinkList L)
{
    Node *current, *del;
    for(current = L->next;
        current != NULL;
        del = current, current = current->next, free(del));
    
    return TRUE;
}
status list_destroy(LinkList *L)
{
    list_clear(*L);
    free((*L));
    *L = NULL;

    return TRUE;
}
void list_print(LinkList L)
{
    Node* current;
    for(current = L->next; current != NULL; current = current->next)
        printf("%d\t", current->data);
    printf("\n");
}