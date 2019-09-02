#include<stdio.h>
void swap(int collection[], int x, int y);
void simpleselect_sort(int collection[], int length);
/***************************************************
 * 简单选择排序
 * 通过两层循环，每次找出剩余元素中最小元素的下标，将最小元素与
 * 外层循环当前元素进行替换。
 * 
 ***************************************************/
int main(void)
{
    int collection[6] = {5,2,4,6,1,3};
    int length = 6;
    int i;
    simpleselect_sort(collection, length);
    for(i = 0; i < length; i++) printf("%d\t", collection[i]);
    printf("\n");

    return 0;
}

void simpleselect_sort(int collection[], int length)
{
    int i, j, min;
    for(i = 0; i < length; i++)
    {
        min = i;
        for(j = i + 1; i < length; i++)
        {
            if(collection[j] > collection[min]) min = j;
        }
        if(min != i) swap(collection, min, i);
    }
}

void swap(int collection[], int x, int y)
{
    int tmp = collection[x];
    collection[x] = collection[y];
    collection[y] = tmp;
}