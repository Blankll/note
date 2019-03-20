#PHP

Note Code PHPCode

## 1. 三目运算符：
### 代码
```php
$a = 12;
$b = 13;
$c = $a > $b ? "a is bigger than b" : "a is smaller than b";
echo $c;
echo "<br />";
var_dump($c);
```
###  数学函数
```php
  max mixed max(number $arg1, number $arg2,,,,);\\求以组数据的最大值；
  min mixed min（number $arg1, number $arg2,,,）;\\求一组数据的最小值；
  ceil float ceil(float $value);\\进一取整；小数部分去掉，整数+1；
  floor float floor（float $value）;\\舍去取整，小数部分去除，整数取本身；
  round float round（float $var）;\\四舍五入；
  rand int rand（int $min, int $max）;\\在min和max之间产生一个随机数；
  mt_rand int mt_rand(int $min, int $max):生成更好的随机数 提高效率；
```
 
###代码

```php
$number01 = 20;
$number02 = 99.9;
 $m = max($number01,$number02,22,11,33.4);
 echo $m,"<br />";
 $n = min($number01, $number02,22,22,33.4);
 echo $n,"<br />";
 $number02 = ceil($number02);
 echo $number02,"<br />";
 $number03 = floor(22.4);
 echo $number03,"<br />";
```
###2. 日期函数：
            时间戳：从1970.1.1 0点到现在的秒数；

            time() int time(void):返回当前的Unix时间戳；
            date string date(日期格式【时间戳】)：格式化一个本地时间/日期 --将时间戳转换成标准格式；
            格式：
            	Y--年
            	m--月
            	d--日
            	H--时
            	i--分
            	s--秒
            strtotime(string $time) 将标准格式转换成时间戳；


###代码
```php
$dt = time();           //获取当前时间戳
echo $dt,"<br />";
$ds = date("Y-m-d");   //将时间戳转换成标准时间格式
echo $ds,"<br />";
echo date("Y-m-d H:i:s"),"<br />";  //将时间戳转换成标准时间格式
$da = "2017-4-4 8:30";   //获取一个任意标准时间
$dd = strtotime($da);    //将标准格式转换成时间戳；
echo $dd;
```


##字符串：
```php
			strlen int strlen(string $string):获取字符串长度；
			strtolower string strtolower(string $str):将字符串转化为全小写；
			strtoupper:strng strtoupper(string $str):将字符串转化为全大写；
			ucfirst：string ucfirst(string $str):字符串中首字母大写；
			ucwords: string ucworlds(string $str):每个单词首字母大写；
			strrev:  string strrev(string $str):反转字符串；
			trim: string trim(string $str):去掉字符串开始和结尾的空格；
			str_replace: mixed str_replace:(mixed $search, mixed $replace, mixed $subject);
					替换
					mixed $search；需要替换的内容；
					mixed $replace：替换目标内容；
					mixed $subject：替换的作用域；
					
			strpos:int strpos(string $haystack, mixed $needle):查找字符首次出现的位置；
					string $haystack： 查找作用域；
					mixed $needle：查找的内容；
			substr:string substr(string $sting, int $start ，[int $length])：截取字符串；
					int $start：开始截取的位置；
					int $length;截取字符的个数；
			md5： string md5(string $str):加密字符串；
			unset：void unset(mixed $var1,mixed $var2...):释放变量；
```

```php
$var01 = "hello";
$var02 = "world";
$var03 = "HELLO";
$var04 = "WORLD";
$length01 = strlen($var01);
echo $length01,"<br />";
echo strtoupper($var01),"<br />";
$var05 = strtolower($var04);
echo $var05,"<br />";
$var06 = $var01.$var02;
echo $var06,"<br />";
echo strrev($var06),"<br />";
$var07 = str_replace("hello","fuck",$var06);
echo $var07,"<br />";
echo str_replace("fuck","FUCK",$var07),"<br />";
```

##3. 数组：
		数组的定义：变量存储的有序序列；
					索引数组：下标为数字的数组
									直接定义：

									用arry关键字定义：
									$brr = aarry(123, "zhangsan", "man", "china");
					关联数组; 下标为字符串的数组；
									直接定义：
										$crr["one"] = "china";
										$crr["two"] = "us";
										$crr["three"] = "uk";

									用arry关键字定义
					 				$crr = aarry("one" => "china", "two" => "us", "three" => "uk");
		数组函数
				print_r():打印变量信息---打印出下标和对应的值；
				count（）int count(array $arr)：打印数组的元素的个数；
				explode array explode(string $separator, $string $sting):使用一个字符串分割另一个字符串；返回的是一个数组；
				join： string join(string $flag, array $arr);返回flag链接arr所组成的函数；implode 别名
				array_values array_values(array $input): 返回数组中所有的值组成新的索引数组；
				array_keys array array_keys(array $input):返回数组中所有的下标组成新的索引数组；
				array_pop mixed array_pop(array &$array):删除数组的最后一个元素并返回最后一个元素的值；
				list void list(mixed $varname, mixed $...):把数组中的值赋给对应的变量；
						对关联无效，对索引有效；

				next：下一个元素；
				prev：上一个元素；
				end：最后一个元素；

				in_array bool in_array(mixed $needle, array $haystack):检查数组中是否含有某个值；
				array_reverse array array_reverse(array $array):反转数组；
		二维数组：
		   定义：
		   		$frr = array(
						array("alen", 15, "man"),
						array("bob", 16, "man"),
						array("cici", 17, "woman"),
						array("david", 18, "man"),
						array("eson", 29. "man"),
		   		);
		   	输出：
		   	
		   		echo $frr[0][1];
         foreach循环：PHP专为数组设定的循环--用于遍历数组；
   		格式：forearch(数组名称 as $key => $var)
                   		{
                			循环体
                   		}
                   		
   		              $key 依次遍历数组的下标；
   	          $var 依次遍历数组的值；
   	          
####数组

```php
//关联数组
$brr = array("zhangsan", "man", "china");

foreach($brr as $key => $var)
{
	echo $key,"--->",$var,"<br />";
}

//索引数组
$crr["one"] = "china";
$crr["two"] = "us";
$crr["three"] = "uk";
//$drr = aarry("one" => "china", "two" => "us", "three" => "uk");

//二维数组
$frr = array(
			array("alen", 15, "man"),
			array("bob", 16, "man"),
			array("cici", 17, "woman"),
			array("david", 18, "man"),
			array("eson", 29, "man"),
		   		);
print_r($frr);

foreach($frr as $key => $var)
{
	echo $key,"--->",$var,"<br />";
}

echo"<br />------------冒泡排序-------------<br />";

//冒泡排序：

$lrr = array(3,6,14,7,2,20,35);

for($i = 0; $i < count($lrr); $i++)
{
	for($j = $i + 1; $j < count($lrr); $j++)
	{
		if($lrr[i] > $lrr[j])
		{
			$tmp = $lrr[j];
			$lrr[j] = $lrr[i];
			$lrr[i] = $tmp;
		}
	}
}
print_r($lrr);
```
###常量：固定不变的量；
	1系统常量：
			PHP_OS：操作系统；
			PHP_VERSION:PHP版本；
			PHP_ASPI:PHP运行方式；
	2自定义常量：
			$a = 3; ----自定义变量；
			格式：define(“常量名称”，“常量的值”)；
			常量名称习惯全大写；
	3魔术常量：
			__FILE__:当前文件的物理路径；
			__LINE__：当前行号；
			__FUNCTION:当前的函数名；
			__CLASS__:当前的类名；
			__METHOD__当前方法名；


##4. 文件上传：
	move_uploaded_file(零时文件位置，指定的位置)；
	检测文件类型：jpg，png，，，；
	$ext = exploade(".",$uImage["name"]);
	$extName = end($ext);
	if($extName != "jpg" && $extName != "png" && $extName != "gif")
	{
		echo "文件类型不正确，请重新上传"；
		<a href = "index.php">返回</a>
		exit；
	}
```html
<body>

<form action = "up.php" method= "post">
<span>用户名:</span><input type = "text" name = "uName"><br />
<span>头像</span><input type = "file" name = "uImage"><br />
<input type = "submit" value = "提交">
</form>
</body>
```
####函数
		1系统函数：数字 字符串 数组 日期
		2自定义函数：用已有的函数或已有语句等代码封装自己的函数；
		 function 函数名称（参数【= 默认值】，参数【= 默认值】，参数【= 默认值】，。。。）
		 {
			函数体；
			返回值；
		 }
```php
echo "<br />----------无参无返回值-----------<br />";
function echoNum()
{
	for($i = 1;$i <= 5; $i++)
	{
		$sum += $i;
		echo $sum,"<br />";
	}
}

 echo echoNum();
 echo "<br />----------有参无返回值-----------<br />";
 function echoNum1($n)
 {
 	for($i = 1;$i <= $n; $i++)
	{
		$sum += $i;
		echo $sum,"<br />";
	}
 }
echo echoNum1(100);

 echo "<br />----------有参有返回值-----------<br />";
```

#### 文件函数库
			PHP用来操作函数
			1fopen：打开文件或者URL
			resource fopen  ( string $filename  , string $mode )
			resource：返回一个资源；

			'r'  只读方式打开，将文件指针指向文件头。
			'r+'  读写方式打开，将文件指针指向文件头。
			'w'  写入方式打开，将文件指针指向文件头并将文件大小截为零。如果文件不存在则尝试创建之。
			'w+'  读写方式打开，将文件指针指向文件头并将文件大小截为零。如果文件不存在则尝试创建之。
			'a'  写入方式打开，将文件指针指向文件末尾。如果文件不存在则尝试创建之。
			'a+'  读写方式打开，将文件指针指向文件末尾。如果文件不存在则尝试创建之。
			'x'  创建并以写入方式打开，将文件指针指向文件头。如果文件已存在，则 fopen()  调用失败并返回 FALSE ，并生成一条 E_WARNING  级别的错误信息。如果文件不存在则尝试创建之。这和给 底层的 open(2) 系统调用指定 O_EXCL|O_CREAT 标记是等价的。
			'x+'  创建并以读写方式打开，其他的行为和 'x' 一样。
			'c'  Open the file for writing only. If the file does not exist, it is created. If it exists, it is neither truncated (as opposed to 'w'), nor the call to this function fails (as is the case with 'x'). The file pointer is positioned on the beginning of the file. This may be useful if it's desired to get an advisory lock (see flock() ) before attempting to modify the file, as using 'w' could truncate the file before the lock was obtained (if truncation is desired, ftruncate()  can be used after the lock is requested).
			'c+'  Open the file for reading and writing; otherwise it has the same behavior as 'c'.
			文件指向文件尾：不会重复创建，入股文件中有内容，光标在末尾；
			fwrite： 写入文件（可安全用于二进制文件）;
			文件大小截为零:删除原有文件内容，重新写入内容；
			int fwrite  ( resource $handle  , string $string  [, int $length  ] )；
			fclose：关闭一个已打开的文件指针
			bool fclose  ( resource $handle  )；关闭文件；
			fread — 读取文件（可安全用于二进制文件）
			string fread  ( resource $handle  , int $length  )
			fclose：关闭一个已打开的文件指针
			bool fclose  ( resource $handle  )；关闭文件；

			filesize :取得文件大小；
			int filesize(string $filename);
			可以创建的文件：.text, .doc, .html,  .php;
```php
//需要用另外一个文件把PHP创建的文件读出来；


// $fileName = "a.text";
// $handle = fopen($fileName,"a+");
// fwrite($handle, "seven");
// $str = fread($handle,5);
// echo $str;
// fclose($handle);

```
####序列化数据：
		$a = 3;
	序列化化以后的数据可以放入文件中，方便其他文件读取和调用；
		serialize:
			string serialize  ( mixed  $value  )


####反序列化
		unserialize：
		mixed  unserialize  ( string $str  )

```php
// $strs = "abc";
// echo serialize($strs),"<br />";
// $numbers = 7;
// echo serialize($numbrs),"<br />";
// $float = 3.14;
// echo serialize($float),"<br />";
// $bool = true;
// echo serialize($bool),"<br />";

```
###5. 文件包含：
		include：include（被包含文件的URL）；
			若未找到被包含文件或不存在，提示错误是一个警告，继续执行后面的代码；
		require：require（被包含文件的URL）；
			若未找到被包含文件或不存在，提示错误是一个致命，停止执行后面的代码；

		include_once(被包含文件的URL):如果引入文件重复多次，提示错误是一个警告，
		继续执行后面的代码；包含重复文件只执行一次；





