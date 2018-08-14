# php带参数的方法的实现

## **zend_parse_parameters**

```c
zend_parse_parameters(ZEND_NUM_ARGS(), "S|z", &type, &value)
```

把传入的参数转换为PHP内核中相应的类型，方便在PHP扩展中使用。

> 第一个参数：ZEND_NUM_ARGS 参数个数
>
> 第二个参数：格式化字符串，指定传入参数与PHP内核类型的转换关系
>
> `S`表示参数是一个字符串。要把传入的参数转换为zend_string类型。
>
>  `|` 表示之后的参数是可选。可以传，也可以不传。
>
>  `z` 表示参数是多种类型。要把传入的参数转换为zval类型。
>
> `!`如果接收了一个PHP语言里的null变量，则直接把其转成C语言里的NULL，而不是封装成`IS_NULL`类型的zval。
>
> `/` 如果传递过来的变量与别的变量共用一个`zval`，而且不是引用，则进行强制分离，新的zval的`is_ref__gc==0, and refcount__gc==1`.

## FAST ZPP

在PHP7中新提供的方式。是为了提高参数解析的性能。

```c
/* 开始　*/
ZEND_PARSE_PARAMETERS_START(1, 2)
/* 传入参数的解析　*/
/* 结束标志　*/
ZEND_PARSE_PARAMETERS_END();
```

> 第一个参数表示必须传的参数；
>
> 第二个参数表示最多传入的参数

## RETURN 

方法的返回值是使用`RETURN_`开头的宏方法进行返回的。常用的宏方法有：

- `RETURN_NULL()`	返回null
- `RETURN_LONG(l)`	返回整型
- `RETURN_DOUBLE(d)` 返回浮点型
- `RETURN_STR(s)`	返回一个字符串。参数是一个zend_string * 指针
- `RETURN_STRING(s)`	返回一个字符串。参数是一个char * 指针
- `RETURN_STRINGL(s, l)` 返回一个字符串。第二个参数是字符串长度。
- `RETURN_EMPTY_STRING()`	返回一个空字符串。
- `RETURN_ARR(r)`	返回一个数组。参数是zend_array *指针。
- `RETURN_OBJ(r)` 返回一个对象。参数是zend_object *指针。
- `RETURN_ZVAL(zv, copy, dtor)` 返回任意类型。参数是 zval *指针。
- `RETURN_FALSE`返回false
- `RETURN_TRUE`	返回true



`ZSTR_`开头的宏方法是`zend_string`结构专属的方法。

数组初始化

```c
zend_hash_init(Z_ARRVAL(value), 0, NULL,(dtor_func_t)say_entry_dtor_persistent, 1);
/* say_entry_dtor_persistent是一个析构函数，用于释放数组的元素。*/
```



`ZEND_HASH_FOREACH_KEY_VAL` 和 `ZEND_HASH_FOREACH_END` 配合使用，实现foreach的效果。

- `zend_hash_exists` 检测指定的key在哈希中是否存在。key为字符串。
- `zend_hash_index_exists` 检测指定的key在哈希中是否存在。key为数字。
- `zend_hash_find`	根据key查找指定的值。key为字符串。
- `zend_hash_index_find` 根据key查找指定的值。key为数字。
- `zend_hash_update`更新指定key的值。key为字符串。
- `zend_hash_index_update` 更新指定key的值。key为数字。

 

 