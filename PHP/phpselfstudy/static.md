## 静态方法的特性

1. 静态属性不需要实例化即可调用。因为静态属性存放的位置是在类里，调用方法为"类名::属性名"；
2. 静态方法不需要实例化即可调用。同上 
3. 静态方法不能调用非静态属性。因为非静态属性需要实例化后，存放在对象里； 
4. 静态方法可以调用非静态方法，使用 self 关键词。php里，一个方法被self:: 后，它就自动转变为静态方法； 
5. 调用类的静态函数时不会自动调用类的构造函数

```php
<?php
class Human{
 public static $name = "妹子";
 public $height = 180;
 public $age;
 /**
  * 构造方法
  * 调用静态方法时，不会执行构造方法，只有实例化对象时才会触发构造函数
  */
public function __construct(){
   $this->age = "Corwien";
  echo __LINE__,__FILE__,'<br>'; 
    
}
 /**
  * 静态方法调用静态属性，使用self关键词
  * echo $this->height;//错。静态方法不能调用非静态属性
  * 因为 $this代表实例化对象，而这里是类，不知道 $this 代表哪个对象
  */
 public static function tell(){
 echo self::$name;
 }
 /**
  * 普通方法调用静态属性，同样使用self关键词
  *
  */
 public function say(){
 echo self::$name . "我说话了";
 echo $this->height;
 }
}


$p1 = new Human();
$p1->say(); 
//对象可以访问静态方法
$p1->tell();
//对象访问静态属性。不能这么访问$p1->name
echo $p1::$name;
//因为静态属性的内存位置不在对象里
Human::say();//错。say()方法有$this时出错；没有$this时能出结果
//但php5.4以上会提示

/** 
 * 调用静态方法，不会执行构造方法，只有实例化对象时才会触发构造函数，输出构造方法里的内容。 
 * 调用类的静态函数时不会自动调用类的构造函数。
  */ 
Human::tell();

?>
```

## 变量的作用域和静态变量

如下函数并不会输出5，因为$count是全局变量，函数中无法直接使用全局变量的必须使用global或者``\$GLOBALS['counter']``来引用全局变量。

```PHP
$count = 5;
function get_count()
{
 	echo $count;
}
function get_count()
{
    global $count;
 	echo $count;
}
```

函数中的静态变量仅在局部函数域中存在，但在执行程序离开此作用域时，值并不会消失，所有调用此函数的方法都共享同一个静态变量

static变量只会被赋值一次

默认情况下，函数通过值传递，如果函数要修改变量的值，需要需要传递引用

### 返回引用

标明引用的函数在调用时如果不添加引用符号，还是会以普通的函数来调用，如果添加了引用，则会返回函数返回值的引用。如果函数在声明时不指定为引用函数，那么在调用过程中添加引用符号调用并不会报错，但是依旧只会返回返回值。

```php
function &mgfunc()
{
	static $b = 10;
	return $b;
}
$a = mgfunc();
echo $a.PHP_EOL;
$a = 50;
echo mgfunc().PHP_EOL;
$c = &mgfunc();
echo $c.PHP_EOL;
$c = 100;
echo mgfunc().PHP_EOL;
/*
10
10
10
100
*/
```

