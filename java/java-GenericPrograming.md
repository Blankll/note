# 泛型程序设计Generic programing

##泛型 程序设计Generic programing
意味着编写的代码可以被很多不同类型的对象所重用

通配符类型（wildcard type）
一个泛型类（Generic）就是具有一个或多个类型变量的类
泛型类可以有多个类型变量
```java
package ynnu.corejava.generic;
//引入泛型变量T 放在类的后面
//泛型类可以有多个类型变量
public class Pair<T> {
	private T first;
	private T second;
	public Pair(){
		first = null;
		second = null;
	}
	public Pair(T first, T second){
		this.first = first;
		this.second = second;
	}
	public T getFirst(){return first;}
	public T getSecond(){return second;}
	
	public void setFirst(T first){this.first = first;}
	public void setSecond(T second){this.second = second;}
}

```
类定义中的类型变量指定方法的返回类型及域和局部变量的类型
用具体的类型替换类型变量就可以实例化泛型类型
普通类中可以定义泛型方法

###Java泛型转换事实：
虚拟机中没有泛型，只有普通的类和方法；
所有的类型参数都用他们的限定类型替换；
桥方法被合成来保持多态；
为保持类型安全性，必要时插入强制类型转换；
###约束与局限性

1. 不能用基本类型实例化类型参数
2. 运行时类型查询只适用于原始类型
3. 不能创建参数化类型的数组   
4. 不能实例化类型变量
5. 不能构造范型数组

```java
//不能创建参数化类型的数组   
Pair<String>[] table = new Pair<String>[10];//error
```
```java
//不能实例化类型变量
public Pair(){first = new T();}//error
```
```java

```