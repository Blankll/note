#include"head.h"

//stack initialize
void InitStack(SeqStack *S)
{
    //Create a empty Stack
    S->top = -1;
}

//Push element to Stack
Status Push(SeqStack *S,StackElementType value)
{
    if(S->top == Stack_Size - 1) return WRONG;
    S->top++;
    S->elem[S->top] = value;
    return RIGHT;
}
//Pop the element from Stack
Status Pop(SeqStack *S,StackElementType *value)
{
    if(S->top == -1) return WRONG;
    *value = S->elem[S->top];
    S->top--;
    return RIGHT;
}
//GET top Stack value
Status GetTop(SeqStack *S,StackElementType *value)
{
    if(S->top == -1) return WRONG;
    *value = S->elem[S->top];
    return RIGHT;
}
void display_option()
{
    printf("option 0: Exit system\n");
    printf("option 1: Initialize Stack\n");
    printf("option 2: Push element into Stack\n");
    printf("option 3: Pop the top element from Stack\n");
    printf("option 4: display the top element value\n");
}
