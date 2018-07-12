#include<stdio.h>
#include<stdlib.h>
#include "head.h"

int main(void)
{
    DoubleList one;
    InitDoubleList(&one);
    CreateDoubleListFromTail(one);
    display(one);
    destroy_list(one);
}
