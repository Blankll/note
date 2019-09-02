#include<stdio.h>
#define status int
#define TRUE 1
#define FALSE 0

void bubble_sort(int collection[], int length);
void swap(int collection[], int x, int y);

int main(void)
{
    int collection[9] = {2,1,3,7,9,6,7,8,9};
    int length = 9;
    int i;

    bubble_sort(collection, length);
    for(i = 0; i < length; i++) printf("%d\t", collection[i]);
    printf("\n");

    return 0;
}
/**
 * 冒泡排序
 * 最外层循环遍历一遍数组，内层循环每次从后往前，
 * 每次单词前元素与前一个元素进行比较，如果当前元素与前一个元素为逆序
 * 将当前元素与他前面的元素交换，直到排序完毕
 * 与选择排序相比，冒泡排序的交换次数增多
 */ 
void bubble_sort(int collection[], int length)
{
    int i, j;
    static int time = 1;
    status flag = TRUE;
    for(i = 0; i < length && flag; i++)
    {
        flag = FALSE;
        for(j = length - 1; j > i; j--)
        {
            if(collection[j - 1] > collection[j])
            {
                swap(collection, j - 1, j);
                /**
                 * 如果遍历一遍之后并没有发生任何交换，
                 * 说明从结尾到i(当前元素)已经是排好序的元素了，不需要再进行排序
                 */ 
                flag = TRUE;
                time++;
            }
        }
    }
    printf("loop time: %d\n", time);

}
void swap(int collection[], int x, int y)
{
    int tmp = collection[x];
    collection[x] = collection[y];
    collection[y] = tmp;
}