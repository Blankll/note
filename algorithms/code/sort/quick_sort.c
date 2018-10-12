
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

void swap(int number[], int low, int high)
{
    int tmp = number[low];
    number[low] = number[high];
    number[high] = tmp;
}