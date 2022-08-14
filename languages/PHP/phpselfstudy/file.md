# PHP文件操作

文件函数库
PHP用来操作函数

``fopen``：打开文件或者URL

```php
resource fopen  ( string $filename  , string $mode )
```

> resource：返回一个资源；

``$mode`` 文件操作

>'r'  只读方式打开，将文件指针指向文件头。
>'r+'  读写方式打开，将文件指针指向文件头。
>'w'  写入方式打开，将文件指针指向文件头并将文件大小截为零。如果文件不存在则尝试创建之。
>'w+'  读写方式打开，将文件指针指向文件头并将文件大小截为零。如果文件不存在则尝试创建之。
>'a'  写入方式打开，将文件指针指向文件末尾。如果文件不存在则尝试创建之。
>'a+'  读写方式打开，将文件指针指向文件末尾。如果文件不存在则尝试创建之。
>'x'  创建并以写入方式打开，将文件指针指向文件头。如果文件已存在，则 fopen()  调用失败并返回 FALSE ，并生成一条 E_WARNING  级别的错误信息。如果文件不存在则尝试创建之。这和给 底层的 open(2) 系统调用指定 O_EXCL|O_CREAT 标记是等价的。
>'x+'  创建并以读写方式打开，其他的行为和 'x' 一样。
>'c'  Open the file for writing only. If the file does not exist, it is created. If it exists.
>c+'  Open the file for reading and writing; otherwise it has the same behavior as 'c'.
>
>文件指向文件尾：不会重复创建，插入文件中有内容，光标在末尾；
>
>文件大小截为零:删除原有文件内容，重新写入内容；

``fwrite`` 写入文件（可安全用于二进制文件）

```php
int fwrite  ( resource $handle  , string $string  [, int $length  ] )；
```

``fclose``关闭一个已打开的文件指针

```php
bool fclose  ( resource $handle  )；
```

``fread`` 读取文件（可安全用于二进制文件）最大一次性能读取8k长度的字节数

```php
string fread  ( resource $handle  , int $length  )
```

``filesize ``取得文件大小；

```php
int filesize(string $filename);
```

example

```php
$fileName = "a.text";
$handle = fopen($fileName,"a+");
fwrite($handle, "seven");
$str = fread($handle,5);
echo $str;
fclose($handle)
```

``readfile``不需要PHP预读到内存，直接把文件的处理交由服务器。缺点就是不能控制负载。

文件后缀也是文件名的一部分

```php
int readfile(string $filename);
```

``basename`` 给出一个包含有指向一个文件的全路径的字符串，本函数返回基本的文件名。

```php
 basename ( string $path [, string $suffix ] ) : string
```



序列化化以后的数据可以放入文件中，方便其他文件读取和调用

```php
//序列化数据 serialize:
string serialize  (mixed  $value)
// 反序列化 unserialize：
mixed  unserialize  (string $str)
```





## 文件引入

include/require语句包含并运行指定文件

如果给出路径，则按照文件路径来查找，否则从include_path中查找，如果include_path中也没有，则从调用脚本文件所在的目录和当前工作目录下查找

当一个文件被包含时，其中所包含的代码继承了include所在行的变量范围。``相当于复制粘贴进来``

```php
set_include_path(); //设定默认的包含路径；
string set_include_path(string $new_include_path);//被包含文件遵循相对路径规则；
```



###  include

- include（被包含文件的URL）；
- 若未找到被包含文件或不存在，提示错误是一个警告，继续执行后面的代码；

### require

- require（被包含文件的URL）；
- 若未找到被包含文件或不存在，提示错误是一个致命，停止执行后面的代码；

区别：　

- require 引入的文件有错误时，执行会中断，并返回一个致命错误；
- include 引入的文件有错误时，会继续执行，并返回一个警告（E_WARNING），
- require 一般放在 PHP 文件的最前面，程序在执行前就会先导入要引用的文件；
- include 一般放在程序的流程控制中，当程序执行时碰到才会引用，简化程序的执行流程。

   include_once(被包含文件的URL):如果引入文件重复多次，提示错误是一个警告，
   	继续执行后面的代码；包含重复文件只执行一次；
   	require_once(被包含文件的URL):如果引入文件重复多次，提示错误是一个致命，
   	停止执行后面的代码；包含重复文件只执行一次；