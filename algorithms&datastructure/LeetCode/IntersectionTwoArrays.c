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
    int nums1[] = {4,9,5};
    int nums2[] = {9,4,9,8,4};
    int nums1Size = 3;
    int nums2Size = 5;
    int returnSize = 0;
    int i;

    int * r = intersection(nums1, nums1Size, nums2, nums2Size, &returnSize);
    for(i = 0; i < returnSize; i++) printf("%d\t", *(r+i));
    printf("\n"); 
    return 0;
}

/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* intersection(int* nums1, int nums1Size, int* nums2, int nums2Size, int* returnSize)
{
   int i, j;
   int length = 0;
   int *result = malloc(nums1Size * sizeof(int));
   for(i = 0; i < nums1Size; i++)
   {
       for(j = 0; j < nums2Size; j++)
       {
           if(nums1[i] == nums2[j])
           {
               result[length++] = nums1[i];
               break;
           }
       }
   }
   int *return_data = malloc(length * sizeof(int));
   int time;
   *returnSize = 0;
   for(i = 0; i < length; i++)
   {
       time = 0;
       for(j = 0; j < *returnSize; j++)
       {
           if(result[i] == return_data[j])
           {
               time++;
               break;
           }
       }
       if(0 == time) return_data[(*returnSize)++] = result[i];
   }
    free(result);
   return return_data;
}