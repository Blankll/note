/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* twoSum(int* nums, int numsSize, int target) {
    int i, j, tmp;
    for(i = 0; i < numsSize - 1; i++)
    {
        tmp = target - *(nums + i);
        for(j = i + 1; j < numsSize; j++)
            if(tmp == *(nums + j))
            {
                int *result = malloc(2 * sizeof(int));
                *(result + 0) = i;
                *(result + 1) = j;
                
                return result;
            }
    }
}