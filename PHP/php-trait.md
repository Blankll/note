# php trait

1. trait 不能实例化
2. Trait中的方法或属性会覆盖 基类中的同名的方法或属性，而本类会覆盖Trait中同名的属性或方法

```php
trait Dog { 
    public $name="dog";
    public function bark()
    { 
        echo "This is dog"; 
    } 
} 
class Animal { 
    public function eat()
    { 
        echo "This is animal eat"; 
    } 
} 
class Cat extends Animal{
    use Dog;
    public function drive()
    { 
        echo "This is cat drive"; 
    } 
} 
$cat = new Cat(); 
$cat->drive(); 
echo "<br/>"; 
$cat->eat(); 
echo "<br/>"; 
$cat->bark(); 
```



3. 一个类可以组合多个trait,  当不同的trait中有着同名的方法或属性，会产生冲突，可以使用insteadof或as进行解决，insteadof 是进行替代，而as是给它取别名。

```php
trait trait1{
    public function eat()
    { 
        echo "This is trait1 eat"; 
    }
    public function drive()
    { 
        echo "This is trait1 drive"; 
    } 
} 
trait trait2{
    public function eat()
    { 
        echo "This is trait2 eat"; 
    } 
    public function drive()
    { 
        echo "This is trait2 drive"; 
    } 
} 
class cat{ 
    use trait1,trait2{ 
        trait1::eat insteadof trait2; 
        trait1::drive insteadof trait2; 
    } 
} 
class dog{ 
    use trait1,trait2{ 
        trait1::eat insteadof trait2; 
        trait1::drive insteadof trait2; 
        trait2::eat as eaten; 
        trait2::drive as driven; 
    } 
} 
$cat = new cat(); 
$cat->eat(); 
echo "<br/>"; 
$cat->drive(); 
echo "<br/>"; 
echo "<br/>"; 
echo "<br/>"; 
$dog = new dog(); 
$dog->eat(); 
echo "<br/>"; 
$dog->drive(); 
echo "<br/>"; 
$dog->eaten();
echo "<br/>"; 
$dog->driven(); 
```



3. as还可以修改访问控制

https://www.jianshu.com/p/fc053b2d7fd1