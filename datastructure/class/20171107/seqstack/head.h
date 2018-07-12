#include<stdio.h>
#include<stdlib.h>
#define Stack_Size 50
#define StackElementType int
#define Status int
#define RIGHT 1
#define WRONG 0
typedef struct{
    StackElementType elem[Stack_Size];
    int top;
}SeqStack;

//base function
void InitStack(SeqStack *S);
Status Push(SeqStack *S,StackElementType value);
Status Pop(SeqStack *S,StackElementType *value);
Status GetTop(SeqStack *S,StackElementType *value);
//option
void display_option();
void option_two(SeqStack *S);
void option_three(SeqStack *S);
void option_four(SeqStack *S);
