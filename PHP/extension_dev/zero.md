# zero

SAPI: server application programing interface

zend_value:

```c
typedef union _zend_value {
	zend_long         lval;				/* long value */
	double            dval;				/* double value */
	zend_refcounted  *counted;
	zend_string      *str;
	zend_array       *arr;
	zend_object      *obj;
	zend_resource    *res;
	zend_reference   *ref;
	zend_ast_ref     *ast;
	zval             *zv;
	void             *ptr;
	zend_class_entry *ce;
	zend_function    *func;
	struct {
		uint32_t w1;
		uint32_t w2;
	} ww;
} zend_value;
```

zval

```c
typedef struct _zval_struct     zval;

struct _zval_struct {
	zend_value        value;			/* value */
	union {
		struct {
			ZEND_ENDIAN_LOHI_3(
				zend_uchar    type,			/* active type */
				zend_uchar    type_flags,
				union {
					uint16_t  call_info;    /* call info for EX(This) */
					uint16_t  extra;        /* not further specified */
				} u)
		} v;
		uint32_t type_info;
	} u1;
	union {
		uint32_t     next;                 /* hash collision chain */
		uint32_t     cache_slot;           /* cache slot (for RECV_INIT) */
		uint32_t     opline_num;           /* opline number (for FAST_CALL) */
		uint32_t     lineno;               /* line number (for ast nodes) */
		uint32_t     num_args;             /* arguments number for EX(This) */
		uint32_t     fe_pos;               /* foreach position */
		uint32_t     fe_iter_idx;          /* foreach iterator index */
		uint32_t     access_flags;         /* class constant access flags */
		uint32_t     property_guard;       /* single property guard */
		uint32_t     constant_flags;       /* constant flags */
		uint32_t     extra;                /* not further specified */
	} u2;
};
```



PHP内部类型：内部类型是对外无感知的，只在内部使用

```c
#define IS_INDIRECT          //间接zval
#define IS_PTR　　　　　　　　　//指针zval
#define _IS_ERROR　　　　　　　//内部使用的错误
```

PHP执行过程中将局部变量存储在zend_execute_data相邻的内存中，静态变量存在_zend_op_array.static_variables中，局部变量在函数执行结束后被销毁，静态变量不会被销毁。

全局变量的结构中有zend_canstants的HashRable,类和对象中的constants_tableHashTble用来存放类中定义的常量，常量可引用，可可拷贝，但是不能被回收。

PHP7中复杂类型的引用计数都维护在各个结构体头部的gc中。

### PHP7字符串

```c
struct _zend_string {
	zend_refcounted_h gc;
	zend_ulong        h;                /* hash value */
	size_t            len;             //8字节，字符串的长度
	char              val[1];          //柔性数组，占１字节，字符串的存储位置
};
```

柔性数组：

在C99 中，结构中的最后一个元素允许是未知大小的数组，这就叫做柔性数组(flexible array)成员(也叫伸缩性数组成员。柔性数组成员只作为一个符号地址存在，而且必须是结构体的最后一个成员。

柔性数组成员不仅可以用于字符数组，还可以是元素为其它类型的数组。包含柔性数组成员的结构用malloc ()函数进行内存的动态分配，**并且分配的内存应该大于结构的大小，以适应柔性数组的预期大小**。

```c
typedef struct test {
    int a;
    double b;
    char c[0];
};
//给结构体分配内存
test *stp_test = (test*)malloc(sizeof(test) + 100*sizeof(char));
// 释放内存
free(stp_test);
```

内存对齐规则

1. 结构体变量的首地址是有效对齐值（对齐单位），的整数倍。
2. 结构体第一个成员偏移量为０，之后的每个结构体成员相对于结构体首地址的offset都是对齐单位的整数倍，如有需要编译器会在成员之间加上填充字节。
3. 结构体的总大小为对齐单位的整数倍如有需要编译器会在最末一个成员之后加上填充字节。
4. 结构体内类型相同的连续元素将在连续的空间内，和数组一样。

```c
struct
{
    int i;    // 4个字节
    char c1;  // 1个字节
    char c2;  // 1个字节
}x1;

struct
{
    char c1;  // 1个字节
    int i;    // 4个字节
    char c2;  // 1个字节
}x2;

struct
{
    char c1;  // 1个字节
    char c2;  // 1个字节
    int i;    // 4个字节
}x3;

int main()
{
    printf("%d\n",sizeof(x1));  // 输出8
    printf("%d\n",sizeof(x2));  // 输出12
    printf("%d\n",sizeof(x3));  // 输出8
    return 0;
}
```

### zend_string_api

提供对字符串操作的函数集合，字符串的扩容、截断、初始化、销毁、判等、计算哈希值等。

```c

ZEND_API extern zend_new_interned_string_func_t zend_new_interned_string;
ZEND_API extern zend_string_init_interned_func_t zend_string_init_interned;

ZEND_API zend_ulong ZEND_FASTCALL zend_string_hash_func(zend_string *str);
ZEND_API zend_ulong ZEND_FASTCALL zend_hash_func(const char *str, size_t len);
ZEND_API zend_string* ZEND_FASTCALL zend_interned_string_find_permanent(zend_string *str);

ZEND_API void zend_interned_strings_init(void);
ZEND_API void zend_interned_strings_dtor(void);
ZEND_API void zend_interned_strings_activate(void);
ZEND_API void zend_interned_strings_deactivate(void);
ZEND_API void zend_interned_strings_set_request_storage_handlers(zend_new_interned_string_func_t handler, zend_string_init_interned_func_t init_handler);
ZEND_API void zend_interned_strings_set_permanent_storage_copy_handlers(zend_string_copy_storage_func_t copy_handler, zend_string_copy_storage_func_t restore_handler);
ZEND_API void zend_interned_strings_switch_storage(zend_bool request);

ZEND_API extern zend_string  *zend_empty_string;
ZEND_API extern zend_string  *zend_one_char_string[256];
ZEND_API extern zend_string **zend_known_strings;
```

