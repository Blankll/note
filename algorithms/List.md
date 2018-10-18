# Liner List

线性表：　零个或多个数据元素的有限序列

## sequence list

```c
#define MAX_SIZE = 20

typedef int ElemType;
typedef struct {
    ElemType data[MAX_SIZE];
    int length;
}seqlist;
```

- data 数据存储空间，　
- MAX_SIZE　顺序表的最大存储容量
- length 顺序表当前存储长度

