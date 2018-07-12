#define MAXSIZE 50
#define QueueElementType int
#define Status int
#define RIGHT 1
#define WRONG 0

typedef struct{
    QueueElementType element[MAXSIZE];//Queue element
    int front;//point to head
    int rear;//point to rear
}SeqQueue;

//basefunction
void InitQueue(SeqQueue *SQ);
Status EnterQueue(SeqQueue *SQ, QueueElementType value);
Status DeleteQueue(SeqQueue *SQ, QueueElementType *delete_value);
