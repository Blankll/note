#include<stdio.h>

#define ElemType int

typedef struct{
    int low;
    int high;
    ElemType sum;
}Maximum;

Maximum max_crossing_subarray(ElemType collection[], int low, int mid, int high);
Maximum maximum_subarray(ElemType collection[], int low, int high);

int main(void)
{
    ElemType collection[] = {13,-3,-25,20,-3,-16,-23,18,20,-7,12,-5,-22,15,-4,7};
    Maximum result;
    result = maximum_subarray(collection, 0, 15);
    int i;
    printf("collection: ");
    for(i = result.low; i <= result.high; i++)
    {
        printf("%d\t", collection[i]);
    }
    printf("\nmax sum: %d\n", result.sum);

    return 0;
}
Maximum max_crossing_subarray(ElemType collection[], int low, int mid, int high)
{
    ElemType index_left = 0;
    ElemType index_right = 0;
    ElemType sum_left = -32768;
    ElemType sum_right = -32768;
    ElemType sum = 0;
    int i;
    Maximum result;
    // left
    for(i = mid; i >= low; i--)
    {
        sum += collection[i];
        if(sum > sum_left)
        {
            sum_left = sum;
            index_left = i;
        }
    }
    // right
    sum = 0;
    for(i = mid + 1; i <= high; i++)
    {
        sum += collection[i];
        if(sum > sum_right)
        {
            sum_right = sum;
            index_right = i;
        }
    }

    result.low = index_left;
    result.high = index_right;
    result.sum = sum_left + sum_right;
    
    return result;
}

Maximum maximum_subarray(ElemType collection[], int low, int high)
{
    Maximum result, left, right, crossing;
    int mid;
    // 终止条件
    if(low == high)
    {
        result.low = low;
        result.high = high;
        result.sum = collection[low];

        return result;
    }
    mid = (low + high) / 2;

    left = maximum_subarray(collection, low, mid);
    right = maximum_subarray(collection, mid+1, high);
    crossing = max_crossing_subarray(collection, low, mid, high);

    if(left.sum > right.sum && left.sum > crossing.sum)
        result = left;
    else if(right.sum > left.sum && right.sum > crossing.sum)
        result = right;
    else
        result = crossing;

    return result;
}