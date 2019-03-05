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

``fread`` 读取文件（可安全用于二进制文件）

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

序列化化以后的数据可以放入文件中，方便其他文件读取和调用

```php
//序列化数据 serialize:
string serialize  (mixed  $value)
// 反序列化 unserialize：
mixed  unserialize  (string $str)
```