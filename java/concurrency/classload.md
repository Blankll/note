# class loader

加载　查找并加载类的二进制文件

链接

​	验证　确保被加载类的正确性

​	准备　为累的静态变量分配内存，并将其初始化为默认值

​	解析　把类中的符号引用转换为直接引用

初始化　为类的静态变量赋予正确的初始值

## 类主动使用分类

new 直接使用

访问某个类或者接口的静态变量，或者对该静态变量进行赋值

调用静态方法

反射某个类

初始化一个子类

启动类 java HelloJava

除此之外的被动使用都不会导致类的初始化

1. 子类调用父类的静态变量，子类不会被初始化

```java
System.out.println(Child.father); 
```

2. 定义引用数组，不会初始化类

3. final修饰的常量在编译期间放到常量池中，通过类调用常量时不会被初始化。(复杂类型在编译期间无法计算得出，会初始化类)



interface 中的变量只能是public,且默认为 public final static

## JVM class loader

BootStrapClassLoader

ExtClassLoader

AppClassLoader

CustmCL



## class被GC回收的三个条件

- 该类所有的实例都已经被GC
- 加载该类的ClassLoader实例已经被GC
- 该类的java.lang.Class对象没有任何地方被引用
- GC的时机我们是不可控的，所以我们对Class的卸载也是不可控的