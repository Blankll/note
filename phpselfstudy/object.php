<?php
/*
PHP面向对象;Pbject Oriented Programming
	封装，继承，多态
命名空间：namespace

封装性：
  封装的修饰符，public（公有的），private（私有的），protected（受保护的）；
  var   不确定封装方法时用var，待最后确定后在替换var
魔术方法__set():
  触发条件：在类外部在对私有的或受保护的成员属性进行赋值时会自动调用；
  第一个参数：要赋值的成员属性名
  第二个参数：要付的值；
  作用：更好的对程序进行控制；
魔术方法__get():
  触发条件：在类的外部直接获取私有的或受保护的成员属性的值时自动调用；
  参数：要访问的成员属性名；
  作用：可以得到私有的或受保护的成员属性，也可以对返回的结果进行控制；
魔术方法__isset():
  触发条件：在类的外部用函数isset()判断私有的或受保护的成员属性时被自动调用；
  参数：判断的成员属性名；
  作用：可以按需求去返回false或true；
魔术方法：__unset():
  unset没有返回；
  触发条件：在类的外部用函数unset()释放私有的或受保护的成员属性时被自动调用；
  参数：要释放的成员属性名称；
  作用：可以按需求控制成员属性的释放操作；
魔术方法：__clone():
  触发条件：在克隆对象时被自动调用；
  作用：可以对新对象的成员属性进行赋值；
魔术方法__toString():
  触发条件：直接echo或print对象时被自动调用；
  作用：可以直接返回字符串或用于调用流程处理；
魔术方法:__call():
  触发条件：在调用一个不存在的方法时被自动调用；
  第一个参数：调用的方法名；
  第二个参数：调用方法时传的参数列表（数组）；
魔术方法：__autoload():
  触发条件：在实例化对象时如果类不存在就被自动调用；
  参数：实例化的类名；
  作用：可以自动引入类文件；
串行化：serialize():
 作用：可以串行化数组也可以串行化对象，串行化对象只串行了成员属性；
魔术方法：__sleep()：
  触发条件：在串行化对象时被自动调用；
  返回一个数组，数组的值就是要串行化的成员属性名；
反串行化：unserialize():
魔术方法__wakeup():
  触发条件：在反串行化对象时被自动调用；
  作用：可以把发生改变的成员属性进行重新赋值操作；

抽象方法抽象类
  抽象方法：类中的方法没有方法体，直接用分号结束，的方法叫抽象方法；
  抽象方法必须用abstract来定义；
  public abstract function say();
  包含抽象方法的类也必须是抽象类，要用关键字abstract来声明；
  抽象类的特点
    不能实例化，也不能new成对象；
    若想使用抽象类，必须定义一个类去继承这个抽象类
    并定义覆盖父类的抽象方法（实现所有的抽象方法）
    抽象类中可以包含有方法体的普通方法；

接口interface：
  用interface声明；
  解控中可以声明常量也可以声明抽象方法；
  接口中的方法都是抽象方法，不需要用abstract来修饰；
  接口不能实例化，需要用一个类去实现它（implement）；
  一个类可以实现多接口（解决了PHP单继承的问题）；

多态性：
  在父类中定义的属性或行为在被子类继承之后，可以具有不同的数据类型或行为；

继承性：
  PHP只支持单继承，一个类只能继承一个父类，但一个类可以被不同的子类继承；
  PHP具有多层继承性；
  访问类型的控制：
      private：只能在该类中访问；
      protected：可以在该类和子类中访问；
      public(默认)：可以在该类，子类和类的外部访问；
  重载：--访问父类中的方法用在子类中；
    parent；访问父类中的成员属性或方法；
    将父类中已实现的方法载入子类中；
  重写：--声明一个与父类中的方法同名的方法；
    对父类中的方法进行重写；


面向对象常用函数
  class_exists()--检查类是否已定义；
     bool class_exists  ( string $class_name  [, bool $autoload  = true ] )；
    第一个参数：要判断的类名；
    第二个参数：如果设置为true，则会自动去调用__autoload()方法进行自动加载；
 get_class_methods()--返回有类的方法名组成的数组；
    如果是私有的或者是受保护的成员方法在类外部函数就不会被得到；
    参数可以传类名也可以传对象；
 get_class():--返回对象的类名；
  返回对象实例$obj所属类的名字，如果不是一个对象则返回FALSE；
 get_object_vars()--返回由对象属性组成的关联数组；
  在类的外部只能得到共有的成员属性；
 get_parent_class()--得到类或对象的父类名；
  参数：可以是类名也可以是对象；
is_a()--判断对象是否由一个类或这个类的子类实例化来的；
 第一个参数：要判断的参数；
 第二个参数：要判断的类名；
 返回值;boolean;
method_exists()--判断成员方法是否存在于一个类或对象中；
  第一个参数：类名或对象命名（类名要要“”）；
  第二个参数：成员方法名（用“”）；
  返回值：boolean；
property_exists()--判断成员属性是否存在；
  第一个参数：类名或对象名（类名要要“”）；
  第二个参数：要判断的成员属性名（用“”）；
  返回值：boolean；



*/
class hello{
  public function say()
  {
    echo "hello,php";
  }
}
$one = new hello();
$one->say();
echo "<hr />";

class person{
  public $name;
  private $age;
  protected $sex;

//私有的成员方法不能在类的外部直接访问
  private function getName()
  {
    return $this->name;
  }
//受保护的成员方法不能在类的外部直接访问
  protected function getAge()
  {
    return $this->age;
  }
//公有的成员方法可以在类的外部直接访问
  public function getSex()
  {
    return $this->sex;
  }

//get()
public function __get($name)
{
  return $this->$name;
}
//set()
public function __set($name,$value)
{
  $this->$name = $value;
}
//unset()
public function __unset($name)
{
  unset($this->$name);
}
public function __clone()
{
  //变化的成员属性重新赋值；
  $this->name = "lisi";
  $this->age = 20;
}
}

$p_one = new person();
echo $p_one->name."<br />";//公有的可以在类的外部直接访问
echo $p_one->age."<br />";//私有的不能在类的外部直接访问
echo $p_one->sex."<br />";//受保护的不能在类的外部直接访问

echo $p_one->getName()."<br />";//公有的能在类的外部直接访问
echo $p_one->getAge()."<br />";//受保护的不能在类的外部直接访问
echo $p_one->getSex()."<br />";//私有的不能在类的外部直接访问
$p_two = clone $p_one;
 ?>
