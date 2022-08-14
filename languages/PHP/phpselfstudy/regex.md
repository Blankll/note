# 正则表达式

```php
preg_match("/[0-9]+/","you have 42 magic beans",$captured);
print_r($captured);
echo "<br />";
$ll = preg_match("/[[:<:]]gun[[:>:]]/","gun");
echo $ll;
```



```php
preg_match($pattern, $string, $matches )// 成功返回1,失败返回0
// preg_match_all() 匹配所有函数
//会把匹配成功的字符串存入$matches ，而这里只是echo preg_match的返回值
```

正则表达式

作用：分割、匹配、查找、替换字符串

## 分割符

 /、取反~

### 通用原子

\d  匹配0~9

\D 匹配除了0~9

\w 数字字母下划线

\W 非数字字母下划线

\s 空白符

\S 除了空白符

### 元字符

``.``  除了换行符之外的其他任意字符

``*`` 匹配0次或者多次

``?``零次或者一次 

``^`` 必须以跟在这个符号后面的字符开头

``$`` 必须以跟在前面的字符作为结束

``+`` 出现一次或者多次

``{n}`` 恰好出现n次

``{n,}`` 大于等于n次

``{n,m}`` 大于等于n，小于等于m

``[]`` 集合，匹配其中的任意字符

``()`` 

``[^]`` 取反

``|`` 或者

[-] 范围

``i`` 忽略大小写

后向引用

```php
$str = '<b>abc<\b>';
$pattern = '/<b>(.*)<\/b>/';
preg_replace($pattern, '\\ 1', $str);// 将前面匹配到的结果返回

```

贪婪模式

默认为贪婪模式

```php
$str = '<b>abc</b><b>bcd</b>';
$pattern = '/<b>.*?<\/b>/'; // 使用?取消贪婪模式
preg_replace_all($pattern, '\\1', $str);
```

## 常见的函数

```php
preg_match();
preg_match_all();
preg_replace();
preg_split();
```

正则中文匹配

UTF-8要使用``u模式修正符``使模式字符串被当成UTF-8，在ANSI(GB2312)环境下，要使用chr将Ascii码转换为字符

