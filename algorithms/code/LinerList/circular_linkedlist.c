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
typedef DulNode* DulLinkedList;

status dul_list_init(DulLinkedList *L);
status dul_list_create_head(DulLinkedList L, ElemType collection[], int length);
status dul_list_create_tail(DulLinkedList L, ElemType collection[], int length);

int main(void)
{

}

status dul_list_init(DulLinkedList *L)
{
    *L = (DulLinkedList*)malloc(sizeof(DulNode));
    if(*L == NULL) ERROR_HAPEN("malloc fail")
    (*L)->data = -1;
    (*L)->next = *L;

    return TRUE;
}
status dul_list_create_head(DulLinkedList L, ElemType collection[], int length)
{
    DulNode* node;
    int i;
    for(i = 0; i < length; i++)
    {
        node = (DulNode*)malloc(sizeof(DulNode));
        if(node == NULL) ERROR_HAPEN("malloc fail")

        node->next = L->next;
        L->next = node;

        return TRUE;
    }
}
status dul_list_create_tail(DulLinkedList L, ElemType collection[], int length)
{
    DulNode* current;
    
}