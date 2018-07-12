#include<stdio.h>

#define QueueElementType int
#define Status int
#define RIGHT 1
#define WRONG 0

typedef struct Node{
    QueueElementType data;
    struct Node *next;
}LinkQueueNode;
typedef struct {
    LinkQueueNode* front;
    LinkQueueNode* rear;
}LinkQueue;

//base function
Status InitQueue(LinkQueue *Q);
Status EnterQueue(LinkQueue *Q, QueueElementType value);
Status DeleteQueue(LinkQueue *Q, QueueElementType *delete_value);
Status IsEmpty (LinkQueue *Q);
Status GetHead(LinkQueue *Q, QueueElementType *value);
Status ClearQueue(LinkQueue *Q);
