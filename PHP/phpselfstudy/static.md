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

