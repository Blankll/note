



三目运算符

```php
<?php
$a = 12;
$b = 13;
$c = $a > $b ? "a is bigger than b" : "a is smaller than b";
?>
```

数学函数

```php
  max mixed max(number $arg1, number $arg2,,,,); //求以组数据的最大值；
  min mixed min（number $arg1, number $arg2,,,); //求一组数据的最小值；
  ceil float ceil(float $value); //进一取整；小数部分去掉，整数+1；
  floor float floor（float $value); //舍去取整，小数部分去除，整数取本身；
  round float round（float $var); //四舍五入；
  rand int rand（int $min, int $max); //在min和max之间产生一个随机数；
  mt_rand int mt_rand(int $min, int $max); //生成更好的随机数 提高效率；
```

日期函数

```php
//时间戳：从1970.1.1 0点到现在的秒数；
time() int time(void); //返回当前的Unix时间戳；
date string date(日期格式【时间戳】); //格式化一个本地时间/日期 --将时间戳转换成标准格式；
/*            
格式：
    Y--年
    m--月
    d--日
    H--时
    i--分
    s--秒
*/
strtotime(string $time); // 将标准格式转换成时间戳；
// example
$dt = time();           //获取当前时间戳
echo $dt,"<br />";
$ds = date("Y-m-d");   //将时间戳转换成标准时间格式
echo $ds,"<br />";
echo date("Y-m-d H:i:s"),"<br />";  //将时间戳转换成标准时间格式
$da = "2017-4-4 8:30";   //获取一个任意标准时间
$dd = strtotime($da);    //将标准格式转换成时间戳；
echo $dd;
```

字符串函数

```php
int strlen(string $string); // 获取字符串长度；
string strtolower(string $str); //将字符串转化为全小写
strng strtoupper(string $str); //将字符串转化为全大写；
string ucfirst(string $str); //字符串中首字母大写；
string ucworlds(string $str); //每个单词首字母大写；
string strrev(string $str); //反转字符串；
string trim(string $str); //去掉字符串开始和结尾的空格；
mixed str_replace(mixed $search, mixed $replace, mixed $subject);
/*
替换
  mixed $search；需要替换的内容；
  mixed $replace：替换目标内容；
  mixed $subject：待替换的文本；
*/
int strpos(string $haystack, mixed $needle); //查找字符首次出现的位置；
/*
  string $haystack： 查找作用域；
  mixed $needle：查找的内容；
*/
string substr(string $sting, int $start ，[int $length]); //截取字符串；
/*
  int $start：开始截取的位置；
  int $length;截取字符的个数；
  start若为负则从末端开始计，最后一个字符位置是-1，向前依次减小。
  length若为正数表示从start开始的长度，
  若为负数表示从末端略去的字符长度，例如-2表示从末尾开始略去两个字符。
*/
$rest = substr("abcdef", -1);    // 返回 "f"
$rest = substr("abcdef", -2);    // 返回 "ef"
$rest = substr("abcdef", -3, 1); // 返回 "d"

string md5(string $str); //加密字符串；
void unset(mixed $var1,mixed $var2...); //释放变量；
```

  validating过滤器： 

  1.用于验证用户输入。 

  2.严格的格式规则。（比如 URL 或 E-Mail 验证）  

  3.如果成功则返回预期的类型，失败则返回 false。 

  sanitizing过滤器： 

  1.用于允许或禁止字符串中指定的字符。 

  2.无数据格式规则。 

  3.始终返回字符串。

数组

定义：变量存储的有序序列；

- 索引数组：下标为数字的数组 ``$brr = aarry(123, "zhangsan", "man", "china");``
- 关联数组; 下标为字符串的数组``$crr = aarry("one" => "china", "two" => "us");``

数组函数

```php
void print_r(); //打印变量信息---打印出下标和对应的值；
int count(array $arr); //打印数组的元素的个数；
array explode(string $separator, $string $sting); //使用一个字符串分割另一个字符串；返回的是一个数组；
string join(string $flag, array $arr); //返回flag链接arr所组成的函数；implode 别名
array_values(array $input); //返回数组中所有的值组成新的索引数组；
array array_keys(array $input); //返回数组中所有的下标组成新的索引数组；
mixed array_pop(array &$array); //删除数组的最后一个元素并返回最后一个元素的值；

void list(mixed $varname, mixed $...); //把数组中的值赋给对应的变量；
/*
对关联无效，对索引有效；
  next：下一个元素；
  prev：上一个元素；
  end：最后一个元素；
*/
bool in_array(mixed $needle, array $haystack); //检查数组中是否含有某个值；
array array_reverse(array $array); //反转数组；
```

二维数组：

```php
// 定义：
$frr = array(
	array("alen", 15, "man"),
	array("bob", 16, "man"),
	array("cici", 17, "woman"),
	array("david", 18, "man"),
	array("eson", 29. "man"),
);
// 输出：
echo $frr[0][1];
// foreach循环：PHP专为数组设定的循环--用于遍历数组；
foreach($arr as $key => $var)
{
	// do something
}
// $key 依次遍历数组的下标；
// $var 依次遍历数组的值；
```

数组函数

```php
$x=array(1,3,2,3,7,8,9,7,3); 
$y= array_count_values($x) //统计$x数组中所有值出现的次数,得出一个新的数组$y,
// $y的键为$x数组中的值,键为$x数组的值出现的次数
$y = [1=>1,3=>3,2=>1,7=>2,8=>1,9=>1];
```

如果不设置cookie结束时间，他会在关闭浏览器的时候销毁～

print只能打印一个，echo可以打印多个，通过逗号隔开，都是语言结构

printf与C语言一类似， sprintf会返回结果，而不是直接输出

print_r, var_dump都是打印整个结构，但是print_r在null等就会输出空白

serialize，unserialize 序列化和反序列化



当  HTTP POST 请求的 Content-Type 是 *application/x-www-form-urlencoded* 或 *multipart/form-data* 时，会将变量以关联数组形式传入当前脚本。