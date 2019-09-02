# Liner List

线性表：　零个或多个数据元素的有限序列

## sequence list

顺序表：以一个结构体存储，结构体中定长的数组存放数据，length存放当前数组存放元素的个数。

```c
#define MAX_SIZE = 20

typedef int ElemType;
typedef struct {
    ElemType data[MAX_SIZE];
    int length;
}seqlist;
```

- data 数据存储空间，　
- MAX_SIZE　顺序表的最大存储容量
- length 顺序表当前存储长度

## link list

链表　每一个节点中保存节点的数据和指向下一个节点的指针

头指针：整个链表的开始，一般以链表的名称作为头指针的名称，是一个指向链表节点的链表节点结构体指针。指向头节点。

头节点：单链表中存储第一个节点前的节点，data可以存储链表长度，也可以什么都不存储。next指向第一个节点。

**头指针指向头节点，头节点next指向链表第一个节点**
## LinkedList
```c
#define ElemType int

typedef struct Node {
    ElemType data;
    Node* next;
}Node;
typedef Node* LinkList;
```
- head.h
```c
#define ElementType int
#define RIGHT 1
#define WRONG 0

typedef struct Node{
    ElementType data;
    struct Node *next;
}Node;
typedef struct Node* LinkList;


void InitCLinkList(LinkList *CL);//initliaze a Clinklist
void CreateCLinkListFromTail(LinkList CL);//CREATE From tail
void display(LinkList CL);//show the list on the screen
void destroy_list(LinkList CL);//desdtroy the list
LinkList merge_1(LinkList LA, LinkList LB);
LinkList merge_2(LinkList RA, LinkList RB);


void option_one();
```
- function.c
```c
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
```
- main.c
```c
#include<stdio.h>
#include<stdlib.h>
#include "head.h"

int main(void)
{
    option_one();

    return 0;
}
```

## dubble linked list

- head.h
```c
#define ElementType int
#define RIGHT 1
#define WRONG 0

typedef struct Node{
    struct Node *prior;
    ElementType data;
    struct Node *next;
}DNode;
typedef struct Node* DoubleList;

void InitDoubleList(DoubleList *DL);
void CreateDoubleListFromTail(DoubleList DL);
void display(DoubleList DL);
void destroy_list(DoubleList DL);
```
- function.c
```c
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
```
- main.c
```c
#include<stdio.h>
#include<stdlib.h>
#include "head.h"

int main(void)
{
    DoubleList one;
    InitDoubleList(&one);
    CreateDoubleListFromTail(one);
    display(one);
    destroy_list(one);
}
```


