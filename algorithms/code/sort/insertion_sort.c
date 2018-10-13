#include<stdio.h>
void insertion_sort(int collection[], int length)
{
    int i, j;
    for(i = 1; i < length; i++)
    {
        int tmp = collection[i];
        for(j = i - 1; j >= 0 && collection[j] > tmp; j--) collection[j + 1] = collection[j];
        collection[j + 1] = tmp;
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