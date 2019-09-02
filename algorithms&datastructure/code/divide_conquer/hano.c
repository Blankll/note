#include<stdio.h>

void move(int number, char start, char trans, char target);

int main(void)
{
    int number = 3;
    move(number, 'x', 'y', 'z');

    return 0;
}

void move(int number, char start, char trans, char target)
{
    if(number == 1)
    {
        printf("%c ---> %c\n", start, target);
        return;
    }
    move(number - 1, start, target, trans); // n-1个盘子借助z从x移动到y上
    printf("%c ---> %c\n", start, target); //第n个盘子从x移动到z上
    move(number - 1, trans, start, target); // n-1个盘子借助x从y移动到z上
}