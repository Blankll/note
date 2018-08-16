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

 