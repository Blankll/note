# class

`call_user_function_ex`方法用于调用函数和方法。

```c
call_user_function_ex(EG(function_table), NULL, fun, &retval, 1, args, 0, NULL);
```



- 第一个参数：方法表。通常情况下，写 EG(function_table) 更多信息查看 [http://www.bo56.com/php7源码分析之cg和eg/](http://www.bo56.com/php7%E6%BA%90%E7%A0%81%E5%88%86%E6%9E%90%E4%B9%8Bcg%E5%92%8Ceg/)
- 第二个参数：对象。如果不是调用对象的方法，而是调用函数，填写NULL
- 第三个参数：方法名。
- 第四个参数：返回值。
- 第五个参数：参数个数。
- 第六个参数：参数值。是一个zval数组。
- 第七个参数：参数是否进行分离操作。详细的，你可以搜索下 PHP 参数分离。查看相关文章
- 第八个参数：符号表。一般情况写设置为NULL即可。

创建对象变量的一般步骤

```c
	/* 创建对象变量 */
	zend_class_entry*   ce;
	zend_string*        class_name;
	class_name = zend_string_init("demo", 4, 0);
	ce = zend_fetch_class(class_name, ZEND_FETCH_CLASS_AUTO);
	object_init_ex(&val_value, ce);
	zend_set_local_var_str("obj", 3, &val_value, 0);
	zend_string_release(&class_name);
	ZVAL_NULL(&var_value);
```

