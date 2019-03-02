# PHP types

PHP支持10种数据类型

４种原始数据类型

- boolean
- integer
- float double
- string

四种混合类型

- array
- object
- callable
- iterable

两种特殊类型

- resources
- NULL



## PHP超全局变量

```php
<?php
echo 'GLOBALS:';
var_dump($GLOBALS);
echo 'GET:';
var_dump($__GET);
echo 'POST:';
var_dump($__POST);
echo 'REQUEST:';
var_dump($__REQUEST);
echo 'SESSION:';
var_dump($__SESSION);
echo 'COOKIE:';
var_dump($__COOKIE);
echo 'SERVER:';
var_dump($__SERVER);
echo 'FILES:';
var_dump($__FILES);
echo 'ENV:';
var_dump($__ENV);
$SERVER['SERVER_ADDR'];
$SERVER['SERVER_NAME'];
$SERVER['REQUEST_TIME'];
$SERVER['QUERY_STRING'];
?>
```



boolean 使用常量TRUE或FALSE, 不区分大小写

当转换为 [boolean](http://php.net/manual/zh/language.types.boolean.php) 时，以下值被认为是 **FALSE**：

- [布尔](http://php.net/manual/zh/language.types.boolean.php)值 **FALSE** 本身
- [整型](http://php.net/manual/zh/language.types.integer.php)值 0（零）
- [浮点型](http://php.net/manual/zh/language.types.float.php)值 0.0（零）
- 空[字符串](http://php.net/manual/zh/language.types.string.php)，以及[字符串](http://php.net/manual/zh/language.types.string.php) "0"
- 不包括任何元素的[数组](http://php.net/manual/zh/language.types.array.php)
- 特殊类型 [NULL](http://php.net/manual/zh/language.types.null.php)（包括尚未赋值的变量）
- 从空标记生成的 [SimpleXML](http://php.net/manual/zh/ref.simplexml.php) 对象

所有其它值都被认为是 **TRUE**（包括任何[资源](http://php.net/manual/zh/language.types.resource.php) 和 **NAN**）。







## string

单引号

双引号

newdoc和heredoc

- 单引号

  单引号不能解析变量

  单引号不能解析转义字符，只能解析单引号和反斜线本身

  变量和变量、变量和字符串、字符串和字符串中间可以使用.连接

- 双引号

  双引号可以解析变量变量可以被特殊字符和{}包含

  双引号可以解析所有转义字符

  可以使用.来连接

  单引号效率高于双引号

- Newdoc和Heredoc

  Newdoc类似与单引号

  Heredoc类似于双引号

  两者都用来处理大文本

  ```php
  <?php
  $a = <<< EOT
  	$contetn
  	EOT
   $B = <<< 'EOT'
   	$content
   	EOT
      
  ?>
  ```

  

## float

浮点类型不能用于比较运算





unset() 只会取消引用，不会销毁空间







## 常量

定义 const、define

const是语言结构，define是函数，const更高效

define不能定义类的常量，const可以

常量一经定义，不能修改和删除

### 系统预定义常量

```php
<?php
 __FILE__;
__LINE__;
__DIR__;
__FUNCTION__;
__CLASS__;
__TRAIT__;
__METHOD__;
__NAMESPACE__;
 ?>
```