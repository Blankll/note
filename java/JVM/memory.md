# JVM运行时数据区

java虚拟机在执行java程序的过程中会把它所管理的内存划分为若干不同的数据区域

java虚拟机运行时的数据区域

![jvm memory](../../statics/java/jvm-memory.png)



**程序计数器(Program Counter Register):** 当前线程所执行的字节码的行号指示器, 通过改变计数器的值来选取下一条需要执行的字节码指令

> 执行java方法时: 记录正在执行的虚拟机字节码指令地址
>
> 执行Native方法: 计数器的值为空

**java虚拟机栈(Java Virtual Machine Stacks):** 描述java方法执行的内存模型:每个方法被执行时创建一个栈帧(Stack frame), 用于存储局部变量表,操作栈,动态链接,方法出口等信息

> 局部变量表存放编译期间可知的各种基本数据类型[^1],对象引用,returnAddress[^2]类型
>
> 局部变量表所需的内存空间在编译期间完成分配,在方法执行期间不会改变局部变量表的大小

**本地方法栈(Native Method Stacks)**: 为虚拟机使用到的native方法服务,HotSpot直接把本地方法栈和虚拟机栈合二为一

**java堆(Java Heap):** 一块被所有线程共享的内存区域,在虚拟机启动时创建,唯一目的就是存放对象实例



[^1]: boolean, byte, char, short, int, float, long, double
[^2]: 直线一条字节码指令地址