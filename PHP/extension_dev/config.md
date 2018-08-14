# config

```c
STD_PHP_INI_BOOLEAN("yaf.use_namespace",   	"0", PHP_INI_SYSTEM, OnUpdateBool, use_namespace, zend_yaf_globals, yaf_globals)
```



`STD_PHP_INI_ENTRY()`用于设置每个配置项的参数。这个宏方法有这么几个参数：

- 第一个参数：配置项在配置文件ini中的名称
- 第二个参数：默认值。当ini文件中不存在这个配置项时，使用这个默认值
- 第三个参数：修改范围。就是设置都在那些场景下可以修改。详细的可以查 PHP_INI_ALL
- 第四个参数：当赋值给全局变量前，会调用的函数。PHP内核已经给出了常用的几个函数。如OnUpdateLong。
- 第五个参数：全局变量的成员名。对应zend_say_globals结构体中的成员。表明读取的值会赋值给这个成员。
- 第六个参数：全局变量的类型。就是上面定义的结构体。
- 第七个参数：全局变量名称。

`SAY_G()`用于读取全局变量的值。