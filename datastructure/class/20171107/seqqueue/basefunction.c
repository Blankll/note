#include<stdio.h>
#include"head.h"

//initalize SeqQueue
void InitQueue(SeqQueue *SQ)
{
    SQ->front = SQ->rear = 0;
}
//enter element to SeqQueue
Status EnterQueue(SeqQueue *SQ, QueueElementType value)
{
    //test is full
    if((SQ->rear + 1) % MAXSIZE == SQ->front) return WRONG;
    SQ->element[SQ->rear] = value;//assign value
    SQ->rear = (SQ->rear + 1) % MAXSIZE;//reset rear point
    return RIGHT;
}
Status DeleteQueue(SeqQueue *SQ, QueueElementType *delete_value)
{
    if(SQ->rear == SQ->front) return WRONG;//test is empty
    *delete_value = SQ->element[SQ->front];//get delete value
    SQ->front = (SQ->front + 1) % MAXSIZE;//front point to the next point
    return RIGHT;
}
