# php系统内置函数

## php超全局变量

```php
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
```

## 系统预定义常量

```php
// 系统常量
PHP_OS; //操作系统；
PHP_VERSION; // PHP版本；
PHP_ASPI; //PHP运行方式；
// 魔术常量
__FILE__; // 当前文件的物理路径
__LINE__; // 当前行号
__DIR__; // 当前目录
__FUNCTION__; // 当前函数
__CLASS__; // 当前类名
__TRAIT__; // 当前trait
__METHOD__; // 当前方法
__NAMESPACE__;　// 当前命名空间
```