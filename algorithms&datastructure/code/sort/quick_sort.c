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