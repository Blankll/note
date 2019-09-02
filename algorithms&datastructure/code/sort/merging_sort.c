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