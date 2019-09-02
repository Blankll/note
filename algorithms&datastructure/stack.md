# stack
## seq stack
- head.h
```c
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
```
- function.c
```c
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
```
- options.c
```c
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
```
- mian.c
```c
#include"head.h"

int main(void)
{
    int status = 1;
    int option;
    SeqStack one;
    display_option();
    while(0 != status)
    {
        printf("Enter you option: ");
        scanf("%d",&option);
        switch(option)
        {
            /****************************************************
            *option 0: Exit system                              *
            *option 1: Initialize Stack                         *
            *option 2: Push element into Stack                  *
            *option 3: Pop the top element from Stack           *
            *option 4: display the top element value            *
            ****************************************************/
            case 0: status = 0;                                   break;
            case 1: InitStack(&one);                              break;
            case 2: option_two(&one);                             break;
            case 3: option_three(&one);                           break;
            case 4: option_four(&one);                            break;
            default: printf("ENter the right opration code!\n");  break;
        }
    }
    return 0;
}
```
## double seq stack
- head.h
```c
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
```
- function.c
```c
#include"head.h"

//initialize DqStack
void InitStack(DqStack *DS)
{
    DS->top[0] = -1;
    DS->top[1] = MAX_SIZE;
}
Status Push(DqStack *DS, StackElementType value, int i)
{
    if(DS->top[0] + 1 == DS->top[1]) return WRONG;
    switch(i)
    {
        case 0: DS->top[0]++;
                DS->stack[DS->top[0]] = value;break;
        case 1: DS->top[1]--;
                DS->stack[DS->top[1]] = value;break;
        default: return WRONG;
    }
    return RIGHT;
}
Status Pop(DqStack *DS, StackElementType *value, int i)
{
    switch (i)
    {
        case 0: if(DS->top[0] == -1) return WRONG;
                *value = DS->stack[DS->top[0]];
                DS->top[0]--;
                                                            break;
        case 1: if(DS->top[1] == MAX_SIZE) return WRONG;
                *value = DS->stack[DS->top[1]];
                DS->top[1]++;
                                                            break;
        default: return WRONG;                              break;
    }
    return RIGHT;
}
```
- main.c
```c
```

## link stack
- head.h
```c
```
