# pointer

## 数组指针(行指针)

指向一个数组的指针。括号优先级高，p是一个指针，指向一个整形的一维数组，长度(步长)为n，p+1要跨过n个整型数据的长度

```c
int (*p)[n];
```

数组指针也称指向一维数组的指针，也称行指针

```c
int a[3][4];
int (*p)[4]; // 定义一个数组指针，指向含有四个整型元素的一维数组
p = a; // 此时p == a[0][]
p++; // p跨过了4个元素，指向a[1][]
```

## 指针数组

存储指针的数组。[]优先级高，先与p结合组成一个数组，再由int *声明为是一个指针，这个数组用于存储n个指针类型的int元素

```c
int *p[n];
```

p++报错，**(p+1) 下一个值地址

```c
int *p[3];
int a[3][4];
for(int i = 0; i < 3; i++) p[i] = a[i]; // 将每行元素首地址赋值给指针数组
```

## 函数指针

是一个指针，指向一个函数

```c
int (*f)(int a, int b);
```

函数指针的函数名是一个指针

```c
#include<stdio.h>
int min(int a, int b);
int max(int a, int b);
int (*func)(int, int);

int main(void)
{
   	int a = 10;
    int b = 9;
    int (*mm)(int, int);
    mm = max;
    func = min;

    int max = (*mm)(a, b);
    int min = (func)(a, b);

    printf("max %d\n", max);
    printf("min %d\n", min);

    return 0;
}

int min(int a, int b)
{
   return a < b ? a : b;
}

int max(int a, int b)
{
    return a > b ? a : b;
}
```



## 指针函数

一个返回值为指针的函数

```c
int* fun(int a, int b);
```

