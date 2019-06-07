# PHP内存管理

php7内存接口

```c
void* _emalloc(size);
_efree(ptr);
```

> chunk 2MB大小的内存
>
> page 4KB大小的内存
>
> 1个chunk = 512 **page**

zend_alloc_sizes.h

```c
#define ZEND_MM_CHUNK_SIZE (2 * 1024 * 1024)               /* 2 MB  */                   #define ZEND_MM_PAGE_SIZE  (4 * 1024)                      /* 4 KB  */    
```

内存预分配: 使用mmap分配chunk

内存分类

- Small(30种规格)  size <= 3KB
- 