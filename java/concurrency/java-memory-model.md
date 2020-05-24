# java内存模型

- jvm内存结构

  - Method Area (方法区)[运行时数据区在所有线程间共享]
    - 已经加载的static变量
    - 已经加载的类信息
    - 已经加载的常量信息
    - 永久引用
  - Heap (堆)[运行时数据区在所有线程间共享]
    - 实例对象，数组 => 运行时动态分配，失去引用后会被GC回收
  - Java Stack (java栈)[运行时数据区私有]
    - 基本数据类型
    - 对象引用
    - 编译时确定大小，不会再改变
  - Native Method Stack (本地方法栈)[运行时数据区私有]
    - 本地方法相关的栈
  - Program Counter Register (程序计数器)[运行时数据区私有]
    - 保存当前线程所执行的行数等信息

- java内存模型 java memory model

  - jmm是一组规范，目的在于更方便的开发多线程程序
  - volatile synchronized Lock等的原理都是JMM
  - 重排序
  - 可见性
  - 原子性

- java对象模型

  java对象再jvm中的存储结构，即java对象自身的存储模型



## 重排序

在线程1内部的两行代码的实际执行顺序和java文件中的顺序不一致，代码指令并不是严格按照代码语句顺序执行的，他们的顺序被改变， 发生了重排序

## 可见性

cpu有多级缓存，导致读数据过期

volatile将修改刷新到内存中

### hapensBefore

happens-before规则是用来解决可见性问题的：在时间上，如果动作A发生在动作B之前，B保证能看见A，这就是hapens-before

重排序依然可能发生

volatile关键字

- volatile是一种同步机制，比synchronized或者Lock相关类更轻量，使用volatile不会发生上下文切换等开销很大的行为
- 作用：
  - 可见性：读取一个volatile变量之前，需要先使相应的本地缓存失效，这样就必须到主存中读取最新值，写一个volatile属性会立即刷入到主内存中
  - 禁止指令重排序优化：解决单例双重锁乱序问题
- 如果一个变量被修饰成volatile，那么jvm就知道了这个变量可能会被并发修改
- volatile是用来同步的保证线程安全，无法做到synchronized那样的原子保护，volatile仅在很有限的场景下才能发挥作用。
- a++不适用
- 纯赋值场景，不依赖于上下文状态直接赋值，可以保证线程安全
- volatile可以使得long和double的赋值是原子的

synchronized不仅保证了可见性，也保证了原子性

## 原子性

一系列操作，要么全部执行成功，要么全部不执行



- 除了long和double之外的基本类型(int,byte,boolean,char,float)的赋值操作
- 所有引用reference的赋值操作
- java.concurrent.Atomic.*包中所有类的原子操作
- long和double为64bit的值，在32位机器上每次写入32位，要写入两次，在64位的jvm上是原子的
- 原子操作 + 原子操作 != 原子操作 => 全同步的HashMap也不完全安全

