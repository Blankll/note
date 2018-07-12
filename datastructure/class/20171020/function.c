#include<stdio.h>
#include<stdlib.h>
#include "head.h"

//initliaze a linklist
void InitCLinkList(LinkList *CL)
{
    *CL = (LinkList)malloc(sizeof(Node));
    (*CL)->next = *CL;    //piont to it's self
}
void CreateCLinkListFromTail(LinkList CL)
{
    int length;
    ElementType value;
    int i = 0;
    Node* s, *real;
    real = CL;
    printf("Enter how many Node you want to insert: ");
    scanf("%d",&length);
    while (i < length)
    {
        i++;
        s = (LinkList)malloc(sizeof(Node));
        printf("Enter the NO.%d Node value : ",i);
        scanf("%d",&value);
        s->data = value;
        s->next = real->next;
        real->next = s;
        real = s;
    }
}

void display(LinkList CL)
{
    Node *p;
    int i;
    for(p = CL->next, i = 1; p != CL; p = p->next, i++)
        printf("Node NO.%d :----->value: %d\n", i, p->data);
}

void destroy_list(LinkList CL)
{
    Node* s;
    if(CL->next == CL)
    {
        free(CL);
        return;
    }
    //1,使s指向头结点后的第一个结点
    //2，使头结点指向第二个结点
    //3，free s指向的第一个结点
    //4，free 头结点
    for(s = CL->next; CL->next != CL; CL->next = s->next, free(s), s = CL->next);
    free(s);//free the head Node
}
LinkList merge_1(LinkList LA, LinkList LB)
{
  Node *p;
  Node *q;
  for(p = LA; p->next != LA; p = p->next);
  for(q = LB; q->next != LB; q = q->next);
  //1,使LB的尾指针指向LA的头节点
  //2,使LA的尾指针指向LB的第一个节点
  //3,释放LB的头节点
  q->next = LA;
  p->next = LB->next;
  free(LB);
  return LA;
}
LinkList merge_2(LinkList RA, LinkList RB)
{
  Node *p;
  //1,LA的尾节点next指向LB的第一个节点
  //2,释放LB头节点
  //3,LB的尾节点next指向LA的头节点
  p = RA->next;//头节点
  RA->next = RB->next->next;
  free(RB->next);
  RB->next = p;
  return RB;//返回新链表尾节点
}
void option_one()
{
    LinkList one;
    InitCLinkList(&one);
    CreateCLinkListFromTail(one);
    display(one);
    destroy_list(one);
}
