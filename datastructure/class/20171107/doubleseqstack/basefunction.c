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
