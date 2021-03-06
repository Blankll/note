# JVM-GC

GC作为一个自动的过程，不需要在代码中显示地启动垃圾回收过程。System.gc()和Runtime.gc()用来请求JVM启动垃圾回收。

在Java程序中不能显式的分配和注销缓存，因为这些事情JVM都帮我们做了，那就是GC。

堆中对象回收条件

- 对象没有引用

- 作用域发生未捕获异常

- 程序在作用域正常执行完毕

- 程序执行System.exit()

- 程序发生意外终止(线程被杀死等)


判断对象是否存活:

- 引用计数(Reference Counting)

  > 实现简单,效率高,但是存在循环引用问题

- 可达性分析(Reachability Analysis)

  > 以根对象为起始节点,根据引用关系向下搜索,如果某个对象到GCRoots间没有任何引用链(Reference Chain),说明此对象不再会被使用

可作为GCRoots的对象:

- 虚拟机栈(栈帧中的本地变量表)中引用的对象,如各个线程被调用的方法堆栈中使用到的参数,局部变量,零时变量等
- 在方法区中静态属性引用的对象,如java类的引用类型静态变量
- 在本地方法栈中native方法引用的对象
- java虚拟机内部的引用,如基本数据类型对应的Class对象,常驻异常对象,系统类加载器等
- 所有被同步锁(synchronized)持有的对象
- 反应java虚拟机内部情况的JMXBean, JVMTI中注册的回调,本地代码缓存等

对象死亡:宣布一个对象死亡,至少要经历两次标记过程:

- 对象在进行可达性分析后发现没有与GCRoots相连接的引用链则会被第一次标记
- 随后进行一次筛选,没有必要执行和已经执行过finnalize的对象直接回收, 需要执行的放入F-Queue中由虚拟机去执行然后回收
- 任何一个对象的finalize方法 只会被系统自动调用一次

方法区回收; 主要回收废弃的常量,不再使用的类型

废弃常量:没有任何一个字符串对象引用常量池中的字符串,该字符串就可以被回收

不再使用的类型:

- 类的所有实例都已经被回收,即java堆中不存在该类及其任何派生子类的实例
- 加载该类的类加载器已经被回收
- 该类对应的java.lang.Class对象没有任何地方被引用, 无法在任何地方通过反射访问该类的方法

## java引用

jdk1.2以后将引用分为了: 强引用(Strongly Reference), 软引用(Soft Reference), 弱引用(Weak Reference)和虚引用(Weak Reference)

- 强引用(Strongly Reference): 在代码中普遍存在的引用赋值,无论任何情况,只要强引用关系还存在, 垃圾收集器就不会回收被引用的对象
- 软引用(Soft Reference): 有用但非必要对象, 在系统将要发生内存异常前将软引用对象列入回收范围中进行二次回收,回收完成后若内存依旧不足则抛出内存溢出异常
- 弱引用(Weak Reference):强度弱于软引用的非必须对象,必定在下一次的回收过程中被回收
- 虚引用(Weak Reference): 最弱的一种引用关系, 为一个对象设置虚引用关联的唯一目的只是为了能在这个对象被收集器回收时收到一个系统通知

jvm堆

- 新域:存储所有新生成的对象
- 旧域:新域中的对象,经过了一定次数的GC循环后,被移入旧域
- 永久域: 存储类和方法对象,从配置的角度看,这个域是独立的,不包括在JVM堆内.默认为4M



## 垃圾收集算法

<font color="red">**标记-复制, 标记-清除, 标记-整理**</font>

