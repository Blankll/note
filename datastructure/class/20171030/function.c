#include<stdio.h>
#include<stdlib.h>
#include"head.h"

void InitDoubleList(DoubleList *DL)
{
    *DL = (DoubleList)malloc(sizeof(DNode));
    (*DL)->next = (*DL)->prior = (*DL);
}
void CreateDoubleListFromTail(DoubleList DL)
{
    int number;
    ElementType value;
    int i;
    DNode *s, *tmp;
    printf("Enter how many Node you want insert:");
    scanf("%d",&number);
    for(i = 0, tmp = DL; i < number; i++, tmp = tmp->next)
    {
        s = (DoubleList)malloc(sizeof(DNode));
        printf("Emter the NO.%d value: ", i+1);
        scanf("%d",&value);
        s->data = value;
        s->next = DL;
        tmp->next = s;
        s->prior = tmp;
        DL->prior = s;
    }
}
void display(DoubleList DL)
{
    DNode *s;
    int i;
    for(s = DL->next, i = 1; s != DL; s = s->next, i++)
        printf("NO.%d----->value: %d\n",i, s->data);
}

void destroy_list(DoubleList DL)
{
    DNode *s,*tmp;
    if(DL->next == DL) return;
    s = DL->next;
    for(tmp = s; s != DL; s = s->next, free(tmp), tmp = s);
    free(DL);
}
