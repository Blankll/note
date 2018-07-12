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
