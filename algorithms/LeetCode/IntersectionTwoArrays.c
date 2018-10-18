/*******************************************************************
 * Intersection of Two Arrays
 * Given two arrays, write a function to compute their intersection.
 * Input: nums1 = [1,2,2,1], nums2 = [2,2]
 * Output: [2]
 * Each element in the result must be unique.
 * The result can be in any order.
 ******************************************************************/
#include<stdio.h>
#include<stdlib.h>

int* intersection(int* nums1, int nums1Size, int* nums2, int nums2Size, int* returnSize);

int main(void)
{

    return 0;
}

/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* intersection(int* nums1, int nums1Size, int* nums2, int nums2Size, int* returnSize)
{
    int element = 0;
    int result_length;
    int length = nums1Size < nums2Size ? nums1Size : nums2Size;
    int result[length];
    int i, j;
    if(nums1Size < nums2Size)
    {
        make_unque(nums1, nums1Size, result_length, result);
    }
    
    else make_unque(nums2, nums2Size, result_length, result);

    for(i = 0; i < )

}
void make_unque(int * collection[], int length, int *result_length, int result[])
{
    int i, j;
    int *result_length = 0;
    for(i = 0; i < length; i++)
    {
        int time = 0;
        for(j = 0; j < *result_length; j++)
        {
            if(collection[i] == result[j])
            {
                time++;
                break;
            }
        }
        if(time == 0) result[*result_length++] = collection[i];
    }
   
}