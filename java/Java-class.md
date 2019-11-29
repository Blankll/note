# Java局部类，内部类

标签（空格分隔）： 未分类

---
### 局部类：  
​    定义在一个方法中的类；
### 内部类：
​    定义在一个类中的另外一个类；

#### 局部类的特点：

1. 同局部变量一样方法中的内部类  
   - 不能够用public、private、protected、static来修饰;
   - 可以被final或者abstract来修饰；   
2. 可以访问其外部类的成员
3. 不能够访问 该方法的局部变量；除非是final局部变量；

## 匿名类
匿名类（anonymous class）是一种特殊的内部类

#### 匿名类的特点

+ 匿名类没有类名，在定义类的同时就生成该对象的实例；
+ 匿名类是“一次性使用”的类；
+ 不取名字，直接用其父类的名字或者接口的名字；
  - 也就是说该类是父类的子类，或者实现了一个接口；  
  - 编译器生成了xxxx$1之类的名字；

+ 类在定义的同时就创建实例，即类的定义前面有一个new；

  - new 类名或接口名(){.......}

  - 不使用关键词class，也不使用extends 及implements。

+ 在构造对象时使用父类构造方法

  - 不能够定义构造方法，因为匿名类没有名字；

  - 如果new对象时，要带参数，则使用父类的构造方法  

```java
package ynnu.corekava.innerclass;

public class Outer {
	private int size = 5;
	public Object makeTheInner(int localVar){
		final int finalLocalVal = 99;
		return new Object(){//函数返回一个新建匿名类
			public String toString(){
				return ("InnerSize: "+size+"finalLocalVar:"+localVar);
			}
		};
	}
}

```
### 内部类
定义：  

 + 将类的定义class xxx{....}置入一个类的内部即可；
 + 编译器将生成xxx$xxxx这样的class文件；
 + 内部类不能够与外部类同名；   

内部类的使用：

+ 在封装它的类的内部使用内部类，与普通类的使用方式相同
+ 在其它类中使用，类名前要冠以外部类的名字，在用new前面冠以对象变量，
格式：外部类的对象名.new内部类名(参数)；
+ 内部类中可以直接访问外部类的字段及方法，private也可以
+ 如果内部类中有与外部类同名的字段或方法，在内部类中可以用 外部类名.this.字段及方法  调用外部类成员；  this.字段及方法 调用内部类字段及方法； 
+ 内部类与类中的字段、方法一样是外部类的成员，它前面也可以有访问控制符合其他修饰符：

  - 访问控制符：public、protected、默认及private；

  - 注意：外部类只能用public或者默认修饰符；

+ 用static修饰内部类实际上是一种外部类，因为它与外部类的实例无关
+ static内部类在使用时：

  - 实例化static类时，在new前面不需要用对象实例变量；

  - static类中不能访问外部类的非static的字段及方法，即只能访问static成员

  - static方法中不能够访问非static的域及方法，也不能够不带前缀的new一个非static的内部类；

```java
package ynnu.corekava.innerclass;

public class StaticOuter {

	public static void main(String[] args) {
		//实例化内部类(用外部类的对象来创建内部类)
		Outer2  one = new Outer2();
		Outer2.Inner in = one.new Inner();
		//实例化静态内部类(直接用类来实例化静态类)
		Outer2.Inner2 two = new Outer2.Inner2();
	}

}

```

