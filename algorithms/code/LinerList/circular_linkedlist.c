#include<stdio.h>
#include<stdlib.h>

#define TRUE 1
#define FALSE 0
#define ERROR -1
#define ERROR_HAPEN(str) {printf("%s\n", str); exit(0);}
typedef int ElemType;
typedef int status;

typedef struct DulNode {
    ElemType data;
    struct DulNode* next;
}DulNode;
typedef DulNode* CircularLinkedList;

status circ_list_init(CircularLinkedList *L);
status circ_list_create_head(CircularLinkedList L, ElemType collection[], int length);
status circ_list_create_tail(CircularLinkedList L, ElemType collection[], int length);
status circ_list_insert(CircularLinkedList L, ElemType value, int index);
status circ_list_delete(CircularLinkedList L, ElemType *value, int index);
void circ_list_print(CircularLinkedList L);
status circ_list_clear(CircularLinkedList L);
status circ_list_destroy(CircularLinkedList *L);


int main(void)
{
    CircularLinkedList L;
    ElemType collection[] = {1,2,3,4,5,6,7};
    int length = 7;
    ElemType value;
    circ_list_init(&L);
    circ_list_create_head(L, collection,length);
    circ_list_print(L);
    circ_list_insert(L, 8, 7);
    circ_list_print(L);
    circ_list_delete(L, &value, 8);
    circ_list_print(L);
    circ_list_clear(L);
    circ_list_destroy(&L);

    return 0;
}

status circ_list_init(CircularLinkedList *L)
{
    *L = (CircularLinkedList)malloc(sizeof(DulNode));
    if(*L == NULL) ERROR_HAPEN("malloc fail")
    (*L)->data = -1;
    (*L)->next = *L;

    return TRUE;
}
status circ_list_create_head(CircularLinkedList L, ElemType collection[], int length)
{
    DulNode* node;
    int i;
    for(i = 0; i < length; i++)
    {
        node = (DulNode*)malloc(sizeof(DulNode));
        if(node == NULL) ERROR_HAPEN("malloc fail")

        node->data = collection[i];
        node->next = L->next;
        L->next = node;
    }

    return TRUE;
}
status circ_list_create_tail(CircularLinkedList L, ElemType collection[], int length)
{
    DulNode* current, *node;
    int i;
    for(current = L; current->next != L; current = current->next);
    for(i = 0; i < length; i++)
    {
        node = (DulNode*)malloc(sizeof(DulNode));
        if(node == NULL) ERROR_HAPEN("malloc fail")
        node->next = current->next;
        current->next = node;
    } 

    return TRUE;
}
status circ_list_insert(CircularLinkedList L, ElemType value, int index)
{
    DulNode* target, *node;
    int i;
    for(i = 1, target = L; i < index && target->next != L; i++, target = target->next);
    node = (DulNode*)malloc(sizeof(DulNode));
    if(node == NULL) ERROR_HAPEN("malloc fail")

    node->data = value;
    node->next = target->next;
    target->next = node;

    return TRUE;
}
status circ_list_delete(CircularLinkedList L, ElemType *value, int index)
{
    DulNode* pre, *target;
    int i;
    for(i = 1, pre = L; i < index && pre->next != NULL; i++, pre = pre->next);
    if(i < index) return FALSE;

    target = pre->next;
    pre->next = target->next;
    free(target);

    return TRUE;    
}
status circ_list_clear(CircularLinkedList L)
{
    DulNode *node, *cursor;
    for(cursor = L->next; cursor != L; node = cursor, cursor = cursor->next, free(node));
    return TRUE;
}
status circ_list_destroy(CircularLinkedList *L)
{
    circ_list_clear(*L);
    free(*L);
    *L = NULL;

    return TRUE;
}
void circ_list_print(CircularLinkedList L)
{
    DulNode* cursor;
    for(cursor = L->next; cursor != L; cursor = cursor->next) printf("%d\t", cursor->data);
    printf("\n");
}