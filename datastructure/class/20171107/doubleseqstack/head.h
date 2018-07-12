#include<stdio.h>
#include<stdlib.h>
#define MAX_SIZE 100
#define StackElementType int
#define Status int
#define RIGHT 1
#define WRONG 0

typedef struct{
    StackElementType stack[MAX_SIZE];
    StackElementType top[2];
}DqStack;

void InitStack(DqStack *DS);
Status Push(DqStack *DS, StackElementType value, int i);
