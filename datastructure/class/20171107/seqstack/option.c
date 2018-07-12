#include"head.h"

void option_two(SeqStack *S)
{
    StackElementType value;
    Status result;
    printf("Enter the element value you want Push: ");
    scanf("%d",&value);
    result = Push(S, value);
    if(WRONG == result)
    {
        printf("the Stack is full!\n");
        return;
    }
    if(RIGHT == result)
        printf("Pop successfully!\n");
}

void option_three(SeqStack *S)
{
    Status result;
    StackElementType value;
    result = Pop(S, &value);
    if( WRONG == result)
    {
        printf("Stack is empty!\n");
        return;
    }
    if(RIGHT == result)
        printf("Pop Stack value: %d\n",value);
}
void option_four(SeqStack *S)
{
    Status result;
    StackElementType value;
    result = GetTop(S, &value);
    if(WRONG == result)
        printf("Stack is empty!\n");
    else
        printf("Stack top value: %d\n",value);
}
