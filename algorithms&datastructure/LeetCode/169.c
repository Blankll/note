#include<stdio.h>

int counter(int *nums, int num, int low, int high);
int majority_element_rec(int *nums, int low, int high);
int majorityElement(int* nums, int numsSize);

int main(void)
{
    int nums[] = {2,2,1,1,1,2,2};
    int numsSize = 7;

    int result = majorityElement(nums, numsSize);
    printf("%d\n", result);

    return 0;
}
int majorityElement(int* nums, int numsSize)
{
    return majority_element_rec(nums, 0, numsSize-1);
}
int majority_element_rec(int *nums, int low, int high)
{
    if(low == high) return nums[low];

    int middle = (high - low) / 2 + low;
    int left = majority_element_rec(nums, low, middle);
    int right = majority_element_rec(nums, middle+1, high);

    if(left == right) return left;

    int left_count = counter(nums, left, low, high);
    int right_count = counter(nums, right, low, high);

    return left_count > right_count ? left : right;
}

int counter(int *nums, int num, int low, int high)
{
    int count = 0;
    for(; low <= high; low++) if(nums[low] == num) count++;

    return count;
}