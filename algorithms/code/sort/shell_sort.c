#include<stdio.h>

void shell_sort(int collection[], int length);

int main(void)
{
    int collection[6] = {5,2,4,6,1,3};
    int length = 6;
    int i;
    shell_sort(collection, length);
    for(i = 0; i < length; i++) printf("%d\t", collection[i]);
    printf("\n");

    return 0;
}

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