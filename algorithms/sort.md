# sort

- 插入排序类
  - 直接插入排序
  - 希尔排序
- 选择排序类
  - 简单选择排序
  - 堆排序
- 交换排序类
  - 冒泡排序
  - 快速排序



## 插入排序类

### 直接插入排序

插入值时，所有的这个值后面的元素都要向后移动一位，为待插入的值留初级一个空间

```c
/************************************************
 * 插入排序
 * 通过嵌套循环，在最外层循环内设置一个哨兵，将哨兵的值
 * 插入到顺序中
 * 
 * **********************************************/
void insertion_sort(int collection[], int length)
{
    int i, j;
    for(i = 1; i < length; i++)
    {
        int tmp = collection[i]; // 暂存
        for(j = i - 1; j >= 0 && collection[j] > tmp; j--) collection[j + 1] = collection[j];　// 向后移动元素，知道前一个元素小于自己
        collection[j + 1] = tmp;　//前一个元素小于自己时将暂存元素插入到当前位置。
    }
}
```

### 希尔排序

```c
void shell_sort(int collection[], int length)
{
    int i, j, tmp;
    int gap = length;
    do
    {
        gap = gap / 3 + 1;
        for(i = gap; i < length; i++)
        {
            if(collection[i - gap] > collection[i])
            {
                tmp = collection[i];
                for(j = i - gap; j >= 0 && collection[j] > tmp; j -= gap) collection[j + gap] = collection[j];
                collection[j + gap] = tmp;
            }
        }
    }while(gap > 1);
}
```

## 选择类排序

### 简单选择排序

通过两层循环，每次找出剩余元素中最小元素的下标，将最小元素与外层循环当前元素进行替换。

```c
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
```



### 堆排序



## 交换排序类

### 冒泡排序

用嵌套循环，每一次内循环比较当前元素的值和前一个元素的值，如果反序则交换。

优化：flag－flag用于标记循环时元素是否发生交换，如果在一次循环中没有发生任何交换，则说明元素已经是顺序的，无需再进行循环了。

```c
void bubble_sort(int collection[], int length)
{
    int i, j;
    static int time = 1;
    status flag = TRUE;　//优化部分，设置一个标志记录是否发生了交换
    for(i = 0; i < length && flag; i++)
    {
        flage = FALSE;//设置为FALSE
        for(j = length - 1; j > i; j--)
        {
            if(collection[j - 1] > collection[j])
            {
                swap(collection, j - 1, j);
                flag = TRUE;//发生了交换，改为true
                time++;
            }
        }
    }
    printf("loop time: %d\n", time);

}
// 交换元素
void swap(int collection[], int x, int y)
{
    int tmp = collection[x];
    collection[x] = collection[y];
    collection[y] = tmp;
}
```



### 快速排序

快速排序使用递归分治的思想，对于一个待排列的集合，根据选出的标兵值，通过两个遍历(从low向high，从high向low),当low == high时结束遍历，遍历到的值如果大于标兵的值，就将标兵的值与遍历到的值进行交换，继续向下遍历，直到low == high时，标兵值左边的值都小于标兵值，标兵值右边的值都大于标兵值，再对标兵值左侧和标兵值进行递归，最终完成排序。

```c
/*************************************************
* 递归调用排序
* number 待排序的数组
* low 开始位置下标　start 0
* high 结束位置下标 
*
**************************************************/
void quik_sort(int number[], int low, int high)
{
    int point;
    if(low >= high) return;
    if(low < high)
    {
        point = partition(number, low, high);
        // 左递归
        quik_sort(number, low, point - 1);
        // 右递归
        quik_sort(number, point + 1, high);
    }
}
/*******************************************
 * 切分number,找出一个标兵值，将low 到high中的值进行
 * 交换排序，大于标兵值的放在标兵值的右边，小于标兵值
 * 的放在左边
 * 
 * ****************************************/
int partition(int number[], int low, int high)
{
    int point = number[low];
    while(low < high)
    {
        while(low < high && number[high] >= point) high--;
        swap(number, low, high);
        while(low < high && number[low] <= point) low++;
        swap(number, low, high);
    }

    return low; // now low == high
}
// 交换
void swap(int number[], int low, int high)
{
    int tmp = number[low];
    number[low] = number[high];
    number[high] = tmp;
}
```

