#include<stdio.h>
/************************************************
 * 插入排序
 * 插入排序和选择排序都是当前元素左侧的都是有序的，
 * 选择排序左侧的不会再发生变化
 * 插入排序左侧的元素可能会有新的元素插入，
 * 通过嵌套循环，在最外层循环内设置一个哨兵，哨兵保存当前未排序的第一个元素
 * 通过内层循环，比较当前为排序的第一个元素(哨兵元素)与已排序的哨兵元素是否存在逆序
 * 如果存在逆序，元素后移为哨兵腾出存储空间，直到前一个元素不再与哨兵逆序时，将哨兵
 * 插入到内层循环的当前元素中(内循环每次与哨兵比较发现是逆序的就会将内循环当前元素向后移动一位)
 * 插入到顺序中
 * 
 * **********************************************/
void insertion_sort(int collection[], int length)
{
    int i, j;
    for(i = 1; i < length; i++)
    {
        // 哨兵，暂存未排序的第一个元素
        int flag = collection[i];
        for(j = i; j > 0 && collection[j-1] > flag; j--)
        {
            // 所有元素后移一位，为插入元素腾出空间
            collection[j] = collection[j-1];
        }
        // 前一个元素不再与哨兵逆序，将哨兵保存到内循环的当前元素位置
        collection[j] = flag;
    }
}
int main(void)
{
    int collection[6] = {5,2,4,6,1,3};
    int length = 6;
    int i;
    insertion_sort(collection, length);
    for(i = 0; i < length; i++) printf("%d\t", collection[i]);
    printf("\n");

    return 0;
}