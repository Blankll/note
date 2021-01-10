# java

JDK与OpenJDK

- JDK JRL协议， OpenJDK GPL  V2协议授权，OpenJDK 可以用于商业环境，JDK在商业使用中需要获得授权
- OpenJDK不包括部署功能(Java Web Start, java控制面板等)
- OpenJDK源代码不完整，部分OracleJDK源代码无法开源
- OpenJDK部分无产权的源代码替换为功能相同的开源源代码
- OpenJDK只包含最精简的JDK
- 不能使用Java商标，java - version显示的是openjdk

**JEP**：([JDK Enhancement Proposals](http://openjdk.java.net/projects/jdk)) java增强体验，JDK的版本变化和新功能将从JEP中选取实现

接口允许定义成员，但必须是**常量**。 抽象类和接口类的无法实例化，任何编译器中直接使用new会报错。 

### JVM

JVM有多种**HotSpot VM**, **J9 VM**, **Zing VM**等,在sun/Oracle和openjdk中默认的都是**HotSpot VM**,HotSpot VM是绝对的主流。HotSpot VM就是Java规范的“参考实现”（RI，Reference Implementation）。把它叫做“标准JVM”完全不为过。

## final

1. final关键字可以用于成员变量、本地变量、方法以及类。
2. final成员变量必须在声明的时候初始化或者在构造器中初始化，否则就会报编译错误。
3. 不能够对final变量再次赋值。
4. 本地变量必须在声明时赋值。
5. **在匿名类中所有变量都必须是final变量**。
6. final方法不能被重写。
7. final类不能被继承。
8. final关键字不同于finally关键字，后者用于异常处理。
9. final关键字容易与finalize()方法搞混，后者是在Object类中定义的方法，是在垃圾回收之前被JVM调用的方法。
10. 接口中声明的所有变量本身是final的。
11. final和abstract这两个关键字是反相关的，final类就不可能是abstract的。
12. final方法在编译阶段绑定，称为静态绑定(static binding)。
13. 没有在声明时初始化final变量的称为空白final变量(blank final variable)，它们必须在构造器中初始化，或者调用this()初始化。不这么做的话，编译器会报错“final变量(变量名)需要进行初始化”。
14. 将类、方法、变量声明为final能够提高性能，这样JVM就有机会进行估计，然后优化。
15. 按照Java代码惯例，final变量就是常量，而且通常常量名要大写。



## abstract & interface

1. abstract类不能与final,static使用。final修饰方法，子类可以调用，但不能覆盖, **abstract类和interface不能被实例化 **

2. 最好不要有private因为私有和抽象放在一起，子类如果想重写父类的私有方法根本继承不过来，也就无法重写 

3. 抽象类中可以有非抽象方法 

4. 抽象类中可以不存在抽象方法，但是抽象方法一定要在类和接口中 

接口方法默认是public abstract的，且实现该接口的类中对应的方法的可见性不能小于接口方法的可见性，因此也只能是public的。

在继承中，重写要求子类不能有比父类更加严格的访问修饰符。这一点和接口相似。
 接口默认方法是public abstract。属性默认public static final。

而抽象类中的抽象方法修饰符可以是public或者protected。

在Java中，类的多继承是不合法，但接口允许多继承。

```java
public interface Hockey extends Sports, Event {...}
```



### StringBuffer（JDK1.0）  

  StringBuffer：字符串变量（Synchronized，即线程安全）。如果要频繁对字符串内容进行修改，出于效率考虑最好使用StringBuffer，如果想转成String类型，可以调用StringBuffer的toString()方法。 

  Java.lang.StringBuffer线程安全的可变字符序列。在任意时间点上它都包含某种特定的字符序列，但通过某些方法调用可以改变该序列的长度和内容。可将字符串缓冲区安全地用于多个线程。 

   StringBuffer 上的主要操作是 append 和 insert    方法，可重载这些方法，以接受任意类型的数据。每个方法都能有效地将给定的数据转换成字符串，然后将该字符串的字符追加或插入到字符串缓冲区中。append    方法始终将这些字符添加到缓冲区的末端；而 insert 方法则在指定的点添加字符。例如，如果 z    引用一个当前内容是“start”的字符串缓冲区对象，则此方法调用 z.append("le")   会使字符串缓冲区包含“startle”，而  z.insert(4, "le")   将更改字符串缓冲区，使之包含“starlet”。 

### StringBuilder（JDK5.0）  

  StringBuilder：字符串变量（非线程安全）。在内部，StringBuilder对象被当作是一个包含字符序列的变长数组。 

   java.lang.StringBuilder是一个可变的字符序列，是JDK5.0新增的。此类提供一个与 StringBuffer 兼容的    API，但不保证同步。该类被设计用作 StringBuffer 的一个简易替换，用在字符串缓冲区被单个线程使用的时候（这种情况很普遍）。 

  其构造方法如下： 

| 构造方法                        | 描述                                                  |
| :------------------------------ | ----------------------------------------------------- |
| StringBuilder()                 | 创建一个容量为16的StringBuilder对象（16个空元素）     |
| StringBuilder(CharSequence cs)  | 创建一个包含cs的StringBuilder对象，末尾附加16个空元素 |
| StringBuilder(int initCapacity) | 创建一个容量为initCapacity的StringBuilder对象         |
| StringBuilder(String s)         | 创建一个包含s的StringBuilder对象，末尾附加16个空元素  |


  在大部分情况下，StringBuilder >   StringBuffer。这主要是由于前者不需要考虑线程安全。 

## java权限控制

| 修饰符    | 内部类 | 同一个包 | 子类 | 任何地方 |
| --------- | ------ | -------- | ---- | -------- |
| priavte   | Yes    |          |      |          |
| default   | Yes    | Yes      |      |          |
| protected | Yes    | Yes      | Yes  |          |
| public    | Yes    | Yes      | Yes  | Yes      |

### java参数传递

1. 真正被传递的是实参 . 形参可以是对象,是对象的时候传递引用.形式参数可被视为local variable。**形参和局部变量一样都不能离开方法**。都只有在方法内才会发生作用，也只有在方法中使用，不会在方法外可见。 

2. **对于形式参数只能用final修饰符**，其它任何修饰符都会引起编译器错误。但是用这个修饰符也有一定的限制，就是在方法中不能对参数做任何修改。   不过一般情况下，一个方法的形参不用final修饰。只有在特殊情况下，那就是：方法内部类。    一个方法内的内部类如果使用了这个方法的参数或者局部变量的话，这个参数或局部变量应该是final。  

3. 形参的值在调用时根据调用者更改，实参则用自身的值更改形参的值（指针、引用皆在此列），也就是说**真正被传递的是实参。** 

4. 方法的参数列表指定要传递给方法什么样的信息，**采用的都是对象的形式**。因此，在参数列表中必须指定每个所传递对象的类型及名字。想JAVA中任何传递对象的场合一样，这里传递的实际上也是引用，并且引用的类型必须正确。--《Thinking   in JAVA》

## override & overload

  **重载(overload)**：只要方法名**一致** , 其他(参数列表、返回值)怎么折腾随便。

 注意: 返回类型不是方法签名的一部分,同一个类中不能有两个名字相同,参数类型也相同返回值却是不同类型值的方法. 

  **重写(overriding)**：只有实现的功能代码**不一致** ，其他的(函数名、参数列表、返回值类型)必须都一致。 

   方法重写的前提： 必须要存在继承的关系。 

   方法的重写: 子父类出了同名的函数，这个我们就称作为方法的重写。 

   什么是时候要使用方法的重写：父类的功能无法满足子类的需求时。 

   方法重写要注意的事项： 

​       1.方法重写时， 方法名与形参列表必须一致。 

​       2.方法重写时，子类的权限修饰符必须要大于或者等于父类的权限修饰符。 

​       3.方法重写时，子类的返回值类型必须要小于或者 等于父类的返回值类型。 

​       4.方法重写时， 子类抛出的异常类型要小于或者等于父类抛出的异常类型。 

​               Exception(最坏) 

​               RuntimeException(小坏) 

   方法的重载：在一个类中 存在两个或者两个 以上的同名函数,称作为方法重载。 

   方法重载的要求 

1. 函数名要一致。 

2. 形参列表不一致（形参的个数或形参 的类型不一致） 

3. 与返回值类型无关。 



### servlet

​    ServletContext对象：servlet容器在启动时会加载web应用，并为每个web应用创建唯一的servlet context对象，可以把ServletContext看成是一个Web应用的[服务器](http://server.chinaitlab.com/)端组件的共享内存，在ServletContext中可以存放共享数据。ServletContext对象是真正的一个全局对象，凡是web容器中的Servlet都可以访问。 

​      整个web应用只有唯一的一个ServletContext对象 

   servletConfig对象：用于封装servlet的配置信息。从一个servlet被实例化后，对任何客户端在任何时候访问有效，但仅对servlet自身有效，一个servlet的ServletConfig对象不能被另一个servlet访问。 





### thread

  A. start()方法来启动线程，真正实现了多线程运行，调用了run()方法；run()方法当作普通方法的方式调用。 

  B. CyclicBarrier让一组线程等待其他线程；CountDownLatch让一组线程等待某个事件发生。 

  C. Callable能够抛出checked exception。 

  D. start()方法让thread进去可运行状态（runnable），等待获取CPU的使用权。 