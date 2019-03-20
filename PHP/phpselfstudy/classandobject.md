# PHP类与对象

final---用于类、方法前。 
final类---不可被继承。 
final方法---不可被覆盖

php和Java不同，Java中类属性是可以用final修饰表示的是常量，PHP不能，因为PHP的常量只能用define定义

## static 

static 关键字用来定义静态属性和方法，同时static 也可以定义静态变量以及后期静态绑定

静态属性不能通过一个类已实例化的对象来访问（但静态方法可以）。

为了兼容 PHP 4，如果没有指定[访问控制](http://php.net/manual/zh/language.oop5.visibility.php)，属性和方法默认为公有。