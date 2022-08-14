# String

PHP源码为了实现对字符串的管理，会给字符串分类，利用zend_string结构体中的gc,u,flages字段，分为以下几种：

1. 临时的普通字符串，标记为0；
2. 内部字符串，标记为：IS_STR_PERSISTENT|IS_STR_INTERNED
3. PHP已知字符串，标记为：IS_STR_PERSISTENT|IS_STR_INTERNED|IS_STR_PERMANENT

- IS_STR_PERSISTENT

  PHP已知字符串，PHP代码中的字面量、标识符等字符串。

- IS_STR_INTERNED

  PHP代码中你所写的及所看到的任何字符串在底层存储时都会被打上IS_STR_INTERNED标签

zend_set_local_var
如果已经存在类型为zend_string的变量名，则使用这个方法创建本地变量

zend_set_local_var_str
如果没有类型为zend_string的变量名，使用此方法创建本地变量

```c
/* 比较s1,s2在length0~length的长度下的字符串，相等返回0 */
ZEND_API int ZEND_FASTCALL zend_binary_strncmp(const char *s1, size_t len1, const char *s2, size_t len2, size_t length);
```

创建字符串变量

```c
	/* 声明zend_string的结构体 */
	zend_string* str = NULL;
	/* 赋值给zend_string的字符串的值 */
	char content[4] = "abc";
	/* 初始化zend_string字符串变量 */
	var_name = zend_string_init("str", 3, 0);
	str = zend_string_init(content, sizeof(content) - 1, 0);
	/* 创建一个zval类型的字符串变量 */
	ZVAL_STR(&var_value, str);
	/*创建本地变量*/
	zend_set_local_var(var_name, &var_value, 0);
	/* 释放zend_string，如果引用数为0，则释放内存 */
	zend_string_release(var_name);
	/* 释放变量 */
	ZVAL_NULL(&var_value);
```

```c
/*
 * 初始化字符串变量
 * *str 存储的值
 * len 存储字符串的长度，不算'\0'
 * persistent 设置是否为静态变量
 * @return zend_string*
 */
static zend_always_inline zend_string *zend_string_init(const char *str, size_t len, int persistent);
```

```c
/*
 *z zval类型,要生成的zval变量
 *s zend_string类型，生成的zval的值
 */
#define ZVAL_STR(z, s)
```

```c
/* 设置本地变量，变量名为zend_string */
int zend_set_local_var(zend_string *name, zval *value, int force);
/* 设置本地变量，变量名为字符串指针 */
int zend_set_local_var_str(const char *name, size_t len, zval *value, int force);
```

