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

```c
#define ElemType int

typedef struct Node {
    ElemType data;
    Node* next;
}Node;
typedef Node* LinkList;
```



