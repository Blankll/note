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

使用两层循环，第一层从左到右遍历未排序元素，第二层循环查找当前第一个未排序元素在已排序元素中因处于的位置，向右移动已排序元素，插入当前元素到应处位置，以此往复。插入值时，所有的这个值后面的元素都要向后移动一位，为待插入的值留初级一个空间

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

其实就是基于插入排序，在插入排序的外层先进行粗略的排序，让集合局部有序，这样可以大大减少插入排序移动已排序元素的移动频率。

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

通过两层循环，每次找出剩余元素(还未进行排序)中最小元素的下标，将最小元素与外层循环当前元素(即还未进行排序的第一个元素)进行替换。

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

1. 堆构造成堆有序
2. 每次将根节点(堆中最大元素所在)与堆的最后一个节点交换，堆长度减一
3. 将交换后的根节点下沉排序，排序完成后根节点元素为余堆的最大元素，重复动作2,3直到余堆长度为一，
4. 余堆长度为1时，原堆长的数组已有序

```java

/**
 * 基于堆的优先队列
 * @param <Key>
 */
public class MaxPQ<Key extends Comparable<Key>>{
    private Key[] pq;
    private int N = 0;

    /**
     * 创建一个优先队列
     * @param maxN 队列的大小
     */
    public MaxPQ(int maxN) {
        pq = (Key[]) new Comparable[maxN + 1];
    }
    /**
     * 向优先队列中插入一个元素
     * @param v
     */
    public void insert(Key v) {
        pq[++N] = v;
        swim(N);
    }
    /**
     * 删除并返回最大元素
     * @return Key 删除的最大元素
     */
    public Key delMax() {
        Key max = pq[1];
        pq[1] = pq[N];
        pq[N--] = null; // 防止对象游离
        sink(1); // 下沉排序元素

        return max;
    }
    /**
     * 大于父节点的子节点上浮
     * @param k　子节点下标
     */
    private void swim(int k) {
        // 比较子节点是否大于父节点
        while(k > 1 && less(k/2, k)) {
            exch(k/2, k);
            k /= 2;
        }
    }
    /**
     * 小于子节点的父节点下沉
     * @param k 父节点下标
     */
    private void sink(int k) {
        sink(pq, k, N);
    }
    private void sink(Comparable<Key>[] a, int k, int n) {
        // 2*k 子节点下标
        while(2*k <= n) {
            int j = 2 * k;
            if(j < n && less(j, j+1)) j++; // 寻找最大子节点
            if(!less(k, j)) break; // 比较父节点与最大子节点大小
            exch(k, j);
            k = j;
        }
    }
    public void sort(Comparable[] a) {
        int n = a.length;
        // 从倒数第二层开始，向下下沉元素
        for(int k = n / 2; k >= 1; k--) {
            sink(a, k, n); // 任意序的堆排序成堆有序 最终使得本层元素都大于子层元素
        }
        while(n > 1) {
            exch(a, 1, n--); // 将堆有序最大值与最小值交换，堆大小减一
            sink(a, 1, n); // 最小值下沉找到对应的位置,or重新找出堆剩余元素最大值
        }

    }
    public boolean isEmpty() {
        return N == 0;
    }
    public int size() {
        return N;
    }
    private boolean less(int i, int j) {
        return pq[i].compareTo(pq[j]) < 0;
    }
    private void exch(int i, int j) {
        Key t = pq[i];
        pq[i] = pq[j];
        pq[j] = t;
    }
    
}
```





## 交换排序类

### 冒泡排序

用嵌套循环，每一次内循环比较当前元素的值和前一个元素的值，如果反序则交换。与选择排序一样最终到已排序位置的元素，都是未排序元素中最小的元素。

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
            // 比较前一个元素与当前元素的大小
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



### 归并排序

1. 将待排序的数组通过递归均等切分，直到切分为每个单元只有一个元素
2. 将已均分的元素进行合并，在合并过程中比较元素的大小，将其有序排列

所以，归并排序的排序其实是发生在合并的过程中的。



C实现

```c
#include<stdio.h>
#define MAX 100
typedef int ElemType;
void merge(ElemType sr[], ElemType tr[], int start, int mid, int end);
void merg_sort(ElemType sr[], ElemType tr[], int start, int end);

int main(void)
{
    int length = 16;
    int i;
    // 源集合
    ElemType sr[] = {16,7,13,10,9,15,3,2,5,8,12,1,11,4,6,14};
    // 结果集
    ElemType tr[length];
    merg_sort(sr, tr, 0, length-1);
    for(i = 0; i < length; i++) printf("%d\t", tr[i]);
    printf("\n");

    return 0;
}

/**
 * 归并排序
 * @param ElemType[] sr 待排序集合
 * @param ElemType[] tr 排序结果集合
 * @param int start 开始位置
 * @param int end 结束位置 
 */
void merg_sort(ElemType sr[], ElemType tr[], int start, int end)
{
    int mid;
    /**
     * 暂存空间将本次递归的排序结果保存在其中
     */ 
    ElemType tr2[MAX + 1];
    if(start == end)
    {
        tr[start] = sr[end];
        return;
    }

    mid = (start + end) / 2;
    // 递归排序左侧的数据
    merg_sort(sr, tr2, start, mid);
    // 递归排序右侧的数据
    merg_sort(sr, tr2, mid+1, end);
    // 合并左右两侧的数据
    merge(tr2, tr, start, mid, end);
}


void merge(ElemType sr[], ElemType tr[], int start, int mid, int end)
{
    int i, j, k;
    for(i = start, j = mid+1; start <= mid && j <= end; i++)
    {
        if(sr[start] > sr[j]) tr[i] = sr[j++];
        else tr[i] = sr[start++];
    }
    // 比较归并完成后将剩余元素存入已排序的数组尾部
    if(start <= mid)
    {
        for(k = 0; k <= mid-start; k++) tr[i+k] = sr[start+k];
    }
    if(i <= end)
    {
        for(k = 0; k <= end-j; k++) tr[i+k] = sr[j+k];
    }
}
```

Java实现

```java
public class Merge {
    private static Comparable[] aux;
    public static void sort(Comparable[] a) {
        aux = new Comparable[a.length];
        sort(a, 0, a.length -1);
    }
    public static void sort(Comparable[] a, int start, int end) {
        if(start >= end) return;
        int mid = (start + end) / 2;
        // 排序左侧数据
        sort(a, start, mid);
        // 排序右侧数据
        sort(a, mid+1, end);
        // 合并结果
        merge(a,start, mid, end);
    }
    public static void merge(Comparable[] a, int start, int mid, int end) {
        int i = start;
        int j = mid + 1;
        // 拷贝数组到成员变量中
        for(int k = start; k <= end; k++) { aux[k] = a[k]; }
        // 将拷贝的成员变量数组进行排序，结果放入传入的原数组中
        for(int k = start; k <= end; k++) {
            // 待归并的两个数组归并完毕时，将剩余元素放入归并后的数组尾部 i已经完毕
            if(i > mid) { a[k] = aux[j++]; }
            // j已完毕, 将i剩余数组成员拷贝到已排序数组中
            else if(j > end) { a[k] = aux[i++]; }
            else if(less(aux[j], aux[i])) { a[k] = aux[j++]; }
            else { a[k] = aux[i++]; }
        }
    }
}
```

