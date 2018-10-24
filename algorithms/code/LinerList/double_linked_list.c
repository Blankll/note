#include<stdio.h>
#include<stdlib.h>
#define ElemType int
#define status int
#define TRUE 1
#define FALSE 0
#define ERROR_HAPEN(str) {printf("%s\n", str); exit(0);}

typedef struct Node{
    struct Node *prev;
    ElemType data;
    struct Node *next;
}DNode;
typedef struct Node* DulLinkedList;
status dul_list_init(DulLinkedList *DL);
status dul_list_create_tail(DulLinkedList DL, ElemType collection[], int length);
void dul_list_print(DulLinkedList DL);
status dul_list_clear(DulLinkedList DL);
status dul_list_destroy(DulLinkedList *DL);

int main(void)
{
    DulLinkedList DL;
    ElemType collection[] = {1,2,3,4,5,6,7};
    int length = 7;
    dul_list_init(&DL);
    dul_list_create_tail(DL, collection, length);
    dul_list_print(DL);
    dul_list_destroy(&DL);

    return 0;
}


status dul_list_init(DulLinkedList *DL)
{
    *DL = (DulLinkedList)malloc(sizeof(DNode));
    if(*DL == NULL) ERROR_HAPEN("malloc fail")
    (*DL)->next = (*DL)->prev = (*DL);

    return TRUE;
}
status dul_list_create_tail(DulLinkedList DL, ElemType collection[], int length)
{
    DNode* current, *node;
    int i;
    for(i = 0, current = DL; i < length; i++, current = current->next)
    {
        node = (DNode*)malloc(sizeof(DNode));
        if(node == NULL) ERROR_HAPEN("malloc fail")
        node->data = collection[i];
        node->next = DL;
        current->next = node;
        node->prev = current;
        DL->prev = node;
    }

    return TRUE;
}
void dul_list_print(DulLinkedList DL)
{
    DNode *s;
    int i;
    for(s = DL->next, i = 1; s != DL; s = s->next, i++)
        printf("NO.%d----->value: %d\n",i, s->data);
}

status dul_list_destroy(DulLinkedList* DL)
{
    dul_list_clear(*DL);
    free(*DL);
    *DL = NULL;

    return TRUE;
}
status dul_list_clear(DulLinkedList DL)
{
    DNode *cursor,*target;
    for(cursor = DL->next; cursor != DL; target = cursor, cursor = cursor->next, free(target));

    return TRUE;
}