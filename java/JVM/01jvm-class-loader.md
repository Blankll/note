# JVM class loader

java代码中,类的加载,连接与初始化过程都是在程序运行区间完成的,者提供了更大的灵活性,增加了更多的可能性.



jvm结束生命周期

- 执行了System.exit()
- 程序正常执行结束
- 程序执行过程中遇到了异常或者错误而异常终止
- 由于操作系统出现错误导致虚拟机进程终止



## 类的加载,连接与初始化

1. 加载: 查找并加载类的二进制数据

   > 类的加载指的是将类的.class文件中的二进制数据读入内存中,将其放在运行时数据区的方法区中,然后在内存中创建一个java.lang.Class对象(规范并未说明Class对象放在哪里,HotSpot虚拟机将其放在了方法区中)用来封装类在方法区内的数据结构

2. 连接: 将已经读入到内存的类的二进制数据合并到虚拟机的运行时环境中去
   - 验证: 确保被加载的类的正确性
   - 准备: 为类的静态变量分配内存，并将其初始化为默认值
   - 解析: 把类中的符号引用转换为直接引用

3. 初始化: 为类的静态变量赋值为
   1. 假如类还没有被加载和连接,先进行加载和连接
   2. 假如类存在直接父类且父类还未被初始化,先初始化直接父类
   3. 假如类中存在初始化语句,就依次执行这些初始化语句



java程序对类的使用分为两只:

1. 主动使用: ``发生初始化``
   1. 创建类的实例
   2. 访问类或接口的静态变量,或对静态变量赋值
   3. 调用类的静态方法
   4. 反射
   5. 初始化一个类的子类
   6. Java虚拟机启动时被标明为启动类的类(java Test)
   7. jdk1.7开始提供的动态语言支持
2. 被动使用: 除了主动使用的7种情况,其他使用java类的方式都被看做是对类的被动使用,都不会导致类的初始化

所有的java虚拟机实现必须在每个类或接口被java程序"首次主动使用"时才初始化它们

### 类的加载

类的加载指的是将类的.class文件中的二进制数据读入内存中,将其放在运行时数据区的方法区中,然后在内存中创建一个java.lang.Class对象(规范并未说明Class对象放在哪里,HotSpot虚拟机将其放在了方法区中)用来封装类在方法区内的数据结构

.class文件的加载方式

1. 从本地系统中直接加载
2. 通过网络下载.class文件
3. 从zip, jar等归档文件中加载.class文件
4. 从专有数据库中提取.class文件
5. 将java源文件动态编译为.class文件

助记符:

- ldc: 表示将int,float,string类型的常量值从常量池中推送至栈顶
- bipush: 表示将单字节(-128~127)的常量值推送到栈顶
- sipush: 表示将短整形常量值(-32768~32767)推送至栈顶
- iconst_1表示将int类型1推送至栈顶(iconst_1~iconst_5)

**类加载的最终产品就是位于内存中的Class对象**

**Class对象封装了类在方法区内的数据结构,并且向java程序员提供了访问方法区内的数据结构的接口**

```java
import java.util.UUID;

/**
 * @author: Blank
 * @description: com.seven.jvm.classloader
 * 对于静态字段来说,只有直接定义了该字段的类才会被初始化
 * 当一个类初始化时,要求其父类全部都已经初始化完毕
 * -XX:+TraceClassLoading:用于追踪累得加载信息并打印出来
 * 常量在编译期间就会被存入到调用这个常量的方法所在的类的常量池中
 * 本质上,调用常量的类并没有直接引用到定义常量的类,因此并不会触发定义常量的类的初始化
 * 当一个常量值在编译时无法确定(如uuid),那么值就不会被放到调用类的常量池中,
 * 这时在程序运行时,会主动使用这个常量所在的类,这会导致这个类被初始化
 *
 * 对于数组来说,其类型是由jvm在运行时期动态生成,表示为[Lcom...]这种形式,动态生成的类型,其父类型是Object
 * 对于数组来说,JavaDoc经常将构成数组的元素为Component,实际上就是将数组降低一个维度后的类型
 * @date: 3/15/20
 * @version: 1.0
 */
public class ClassLoaderTest {
    public static void main(String[] args) {
        System.out.println(Child.str2);
    }
}

class Parent {
    public static String str = "hello, word";
    static { System.out.println("parent static block"); }

}

class Child extends Parent {
    public static String str2 = "hello, word2";
    public static final String str2f = "hello, word2 f";

    public static final String str3f = UUID.randomUUID().toString();
    static { System.out.println("child static block"); }
}
```



## 类加载器

java有两种类型的类加载器

- java虚拟机自带的加载器

  - 根类加载器|启动类加载器(Bootstrap)

    > 该加载器没有父加载器,它负责加载虚拟机的核心类库,如java.lang*等.
    >
    > 根类加载器从系统属性sun.boot.class.path所指定的目录中加载类库,
    >
    > 根类加载器的实现依赖于底层操作系统,属于虚拟机实现的一部分

  - 扩展类加载器(Extension)

    > Extension的父加载器为Bootsrap. 从java.ext.dirs系统属性所指定的目录中加载类库,或者从jdk的安装目录jre/lib/ext子目录下加载类库,如果把用户创建的jar文件放在这个目录下,也会自动由扩展加载器加载,
    >
    > 扩展类加载器是纯java类,是java.lang.ClassLoader类的子类

  - 系统(应用)类加载器(System)

    > System的父加载器为扩展类加载器,他从环境壁垒classpath或者java.class.path所指定的目录中加载类,他是用户定义的类加载器的默认父加载器,系统类加载器是纯java类,是java.lang.ClassLoader类的子类.

- 用户自定义的类加载器

  - java.lang.ClassLoader的子类
  - 用户可以定制类的加载方式

JVM规范允许类加载器在预料某个类将要被使用时就预先加载它,如果在预先加载的过程中遇到了.class文件缺失或存在错误,类加载器必须等到<font color="red">程序首次主动</font>使用该类时才报错(LinkageError错误)

如果这个类一致没有被程序主动使用,那么类加载器就不会报错

## 类和对象加载流程

1. 类加载

2. 类连接

3. 类初始化

4. 类实例化

   - 为新的对象分配内存
   - 为实例变量赋默认值
   - 为实例变量赋正确的初始值

   java编译器为它编译的每一个类都至少生成一个实例初始化方法,在java的class文件中,这个实例初始化方法被称为<init>, 针对源代码中的每一个类的构造方法,java编译器都产生一个<init>方法