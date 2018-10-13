#include<stdio.h>
#define status int
#define TRUE 1
#define FALSE 0

void bubble_sort(int collection[], int length);
void swap(int collection[], int x, int y);

int main(void)
{
    int collection[9] = {2,1,3,7,9,6,7,8,9};
    int length = 9;
    int i;

    bubble_sort(collection, length);
    for(i = 0; i < length; i++) printf("%d\t", collection[i]);
    printf("\n");

    return 0;
}
void bubble_sort(int collection[], int length)
{
    int i, j;
    static int time = 1;
    status flag = TRUE;
    for(i = 0; i < length && flag; i++)
    {
        flag = FALSE;
        for(j = length - 1; j > i; j--)
        {
            if(collection[j - 1] > collection[j])
            {
                swap(collection, j - 1, j);
                flag = TRUE;
                time++;
            }
        }
    }
    printf("loop time: %d\n", time);

}
void swap(int collection[], int x, int y)
{
    int tmp = collection[x];
    collection[x] = collection[y];
    collection[y] = tmp;
}