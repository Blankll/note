柔性数组：

在C99 中，结构中的最后一个元素允许是未知大小的数组，这就叫做柔性数组(flexible array)成员(也叫伸缩性数组成员。柔性数组成员只作为一个符号地址存在，而且必须是结构体的最后一个成员。

柔性数组成员不仅可以用于字符数组，还可以是元素为其它类型的数组。包含柔性数组成员的结构用malloc ()函数进行内存的动态分配，**并且分配的内存应该大于结构的大小，以适应柔性数组的预期大小**。

```json
typedef struct test {
    int a;
    double b;
    char c[0]; // 柔性数组
};
//给结构体分配内存
test *stp_test = (test*)malloc(sizeof(test) + 100*sizeof(char));
// 释放内存
free(stp_test);
```

