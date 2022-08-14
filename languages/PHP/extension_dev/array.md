# array

PHP数组zend_array对应的是HashTable,是一种通过哈希函数将特定的键映射到特定值的一种数据结构，他维护着键和值一一对应的关系，可以快速根据键索引到值，效率为O(1);

array的结构

```c
typedef struct _zend_array HashTable;

struct _zend_array {
	zend_refcounted_h gc;
	union {
		struct {
			ZEND_ENDIAN_LOHI_4(
				zend_uchar    flags,
				zend_uchar    _unused,
				zend_uchar    nIteratorsCount,
				zend_uchar    _unused2)
		} v;
		uint32_t flags;
	} u;
	uint32_t          nTableMask;
	Bucket           *arData;
	uint32_t          nNumUsed;
	uint32_t          nNumOfElements;
	uint32_t          nTableSize;
	uint32_t          nInternalPointer;
	zend_long         nNextFreeElement;
	dtor_func_t       pDestructor;
};

/*bucket*/
typedef struct _Bucket {
	zval              val;
	zend_ulong        h;                /* hash value (or numeric index)   */
	zend_string      *key;              /* string key or NULL for numerics */
} Bucket;
```

`zend_hash_num_elements`获取数组的元素个数。

`array_init_size(return_value, zend_hash_num_elements(Z_ARRVAL_P(arr)));` 初始化一个数组。在PHP扩展中，我们是通过`return_value`这个变量设置方法的返回值。因此，我们直接修改这个`return_value`变量即可。感兴趣的话，可以把宏方法`PHP_FUNCTION`展开看下。

`ZEND_HASH_FOREACH_KEY_VAL` 和 `ZEND_HASH_FOREACH_END` 配合使用，实现foreach的效果。

- `zend_hash_exists` 检测指定的key在哈希中是否存在。key为字符串。
- `zend_hash_index_exists` 检测指定的key在哈希中是否存在。key为数字。
- `zend_hash_find`	根据key查找指定的值。key为字符串。
- `zend_hash_index_find` 根据key查找指定的值。key为数字。
- `zend_hash_update`更新指定key的值。key为字符串。
- `zend_hash_index_update` 更新指定key的值。key为数字。

**array_init **和**array_init_size **这2个都是宏，具体定义在文件：zend_API.h 中。

```c
#define array_init(arg)			_array_init((arg), 0 ZEND_FILE_LINE_CC)
#define array_init_size(arg, size) _array_init((arg), (size) ZEND_FILE_LINE_CC)
```

_array_init函数定义在zend_API.c文件中。

```c
/* Argument parsing API -- andrei */
ZEND_API int _array_init(zval *arg, uint size ZEND_FILE_LINE_DC) /* {{{ */
{
	ALLOC_HASHTABLE_REL(Z_ARRVAL_P(arg));

	_zend_hash_init(Z_ARRVAL_P(arg), size, NULL, ZVAL_PTR_DTOR, 0 ZEND_FILE_LINE_RELAY_CC);
	Z_TYPE_P(arg) = IS_ARRAY;
	return SUCCESS;
}
```

通过对_array_init函数的分析，可以看到传递给_array_init的arg参数必须是已经初始化了的zval，否则会报段错误。所以array_init和array_init_size的正确用法是：

```c
zval *arr1, *arr2;
MAKE_STD_VAL(arr1);
MAKE_STD_VAL(arr2);

array_init(arr1);
array_init(arr2, 31);
```

## 数组变量创建过程

```c
zval val_value;
zend_string* var_name = NULL;
var_name = zend_string_init("arr", 3, 0);
/* 创建数组变量 */
array_init(&var_value);
/* 添加一个索引item */
add_index_long(&var_value, 0. 1);
/* 添加一个关联型的item */
add_assoc_string_ex(&var_value. "a", 1, "b", 1);
/* 设置本地变量 */
zend_set_local_var(var_name, &val_value, 0);
/* 用完后释放变量 */
zend_string_release(var_name);
ZVAL_NULL(&val_value);
```

void array_init(zval* pzval)

```c
int add_index_long(zval* pzval, ulong index, long value);
int add_index_zval(zval* pzval, ulong index, zval* value);
int add_assoc_long(zval* pzval, const char* key, long value);
int add_assoc_string_ex(zval* pzval, const char* key, uint klen, const char* value);
/* duplicate-是否复制 */
int add_assoc_stringl_ex(zval* pzval, const char* key, uint klen, const char* value, uint vlen, zend_bool duplicate);
int add_assoc_zval_ex(zval* pzval, const char* key, uint klen, zval* value);
```

[更多API](http://php.net/manual/en/internals2.variables.arrays.php)

