# 	JVM class loader

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
    >
    > 当JVM启动时,一块特殊的机器码会运行,它会加载扩展类加载器与系统类加载器,这块特殊的机器码就是Bootstrap,Bootstrap是特定于平台的机器指令,负责开启整个加载过程,启动类加载器不是java类,而其他加载器都是java类,

  - 扩展类加载器(Extension)

    > Extension的父加载器为Bootsrap. 从java.ext.dirs系统属性所指定的目录中加载类库,或者从jdk的安装目录jre/lib/ext子目录下加载类库,如果把用户创建的jar文件放在这个目录下,也会自动由扩展加载器加载,
    >
    > 扩展类加载器是纯java类,是java.lang.ClassLoader类的子类

  - 应用类加载器(App)

    > App的父加载器为扩展类加载器,他从环境变量classpath或者java.class.path所指定的目录中加载类,他是用户定义的类加载器的默认父加载器,App类加载器是纯java类,是java.lang.ClassLoader类的子类.

- 用户自定义的类加载器

  - java.lang.ClassLoader的子类
  - 用户可以定制类的加载方式

JVM规范允许类加载器在预料某个类将要被使用时就预先加载它,如果在预先加载的过程中遇到了.class文件缺失或存在错误,类加载器必须等到<font color="red">程序首次主动</font>使用该类时才报错(LinkageError错误).如果这个类一直没有被程序主动使用,那么类加载器就不会报错

调用ClassLoader类的loadClass方法加载一个类,并不是对类的主动使用,不会导致初始化

```java
package com.seven.jvm.classloader;
public class LoaderTest {
    public static void main(String[] args) throws ClassNotFoundException {
        ClassLoader loader = ClassLoader.getSystemClassLoader();
        // 不会引发类的初始化
        Class<?> classz = loader.loadClass("com.seven.jvm.classloader.WaitToLoad");
        System.out.println(classz);
        // 会引发类的初始化
        classz = Class.forName("com.seven.jvm.classloader.WaitToLoad");
        System.out.println(classz);
    }
}

class WaitToLoad {
    static { System.out.println("class loaded"); }
}
```

### 自定义类加载器

若有一个类加载器能够成功加载Test类,那么这个类加载器被称为<font color="red">定义类加载器</font>, 所有能成功返回Class对象引用的类加载器(包括定义类加载器)都被称为<font color="red">初始类加载器</font>.

```java
/**
 * @author: Blank
 * @description: com.seven.jvm.classloader
 * 实现一个自定义类加载器
 * @date: 3/19/20
 * @version: 1.0
 */
public class CustomClassLoader extends ClassLoader{
    private String classLoaderName;
    private final String fileExtension = ".class";

    public CustomClassLoader(String classLoaderName) {
        super(); // 默认使用AppClassLoader为该类加载器的父加载器
        this.classLoaderName = classLoaderName;
    }
    public CustomClassLoader(ClassLoader parent, String classLoaderName) {
        super(parent); // 使用指定的ClassLoader为该类加载器的父加载器
        this.classLoaderName = classLoaderName;
    }

    @Override
    protected Class<?> findClass(String name) throws ClassNotFoundException {
        byte[] data = this.loadClassData(name);

        return this.defineClass(name, data, 0, data.length);
    }

    private byte[] loadClassData(String name) {
        InputStream inputStream = null;
        byte[] data = null;
        ByteArrayOutputStream byteArrayOutputStream = null;
        try {
            this.classLoaderName = name.replace(".", "/");
            inputStream = new FileInputStream(new File(name + this.fileExtension));
            byteArrayOutputStream = new ByteArrayOutputStream();
            int character = 0;
            while (-1 != (character = inputStream.read())) {
                byteArrayOutputStream.write(character);
            }
            data = byteArrayOutputStream.toByteArray();
        } catch (IOException e) {
            e.printStackTrace();
        } finally {
            try {
                inputStream.close();
                byteArrayOutputStream.close();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }

        return data;
    }

    public static void main(String[] args) throws Exception {
        CustomClassLoader customClassLoader = new CustomClassLoader("loader1");
        Class<?> clz = customClassLoader.loadClass("com.seven.jvm.classloader.LoaderClassClass");
        Object object = clz.newInstance();
    }
}

class LoaderClassClass {
    static { System.out.println("class loaded"); }
}
```

## 命名空间

- 每个类加载器都有自己的命名空间,命名空间由该加载器及所有父加载器所加载的类组成
- 在同一个命名空间中,不会出现类的完整名字(包括类的包名)相同的两个类
- 在不同的命名空间中,有可能出现类的完整名字(包括类的包名)相同的两个类
- 子加载器所加载的类可以访问父加载器加载的类,父加载器加载的类无法访问子加载器加载的类

**类加载器的双亲委托模型的好处:**

1. 可以确保java核心库的类型安全:所有的java应用至少会引用javalang.Object类,也就是在运行前,java\.lang.Object这个类会被加载到java 虚拟机中;如果这个加载过程是由java应用自己的类加载器来完成的,那么就可能会在jvm中存在多个版本的java.lang.Object类,而这些类之间是互不兼容的,互不可见的.借助java双亲委托机制,java核心类库的加载工作都是由启动类加载器来完成,从而确保java应用使用的都是同一个版本的java核心类库
2. 确保java核心类库所提供的类不会被自定义的类所替代

在运行期,一个java类是由该类的完全限定名(binary name)和用于加载该类的定义类加载器(defining loader)所共同决定的

## 线程上下文类加载器(Context classloader)

线程上下文加载器就是默认为当前线程的current ClassLoader

线程上下文类加载器是从JDK1.2开始引入的,Thread类中的``getContextClassLoader()``与``setContextClassLoader(ClassLoader cls)``分别用来获取和设置上下文类加载器, 如果没有显式的设置的话,线程将继承其父线程的上下文类加载器, Java应用运行时的初始线程的上下文类加载器是系统类加载器

SPI(Service Provider Interface):

父ClassLoader可以使用当前线程Thread.currentThread.getContextLoader()所指定的ClassLoader加载的类,改变父ClassLoader不能使用子ClassLoader或没有父子关系的ClassLoader加载的类的情况,即改变了双亲委托模型.

## 类和对象加载流程

1. 类加载

2. 类连接

3. 类初始化

4. 类实例化

   - 为新的对象分配内存
   - 为实例变量赋默认值
   - 为实例变量赋正确的初始值

   java编译器为它编译的每一个类都至少生成一个实例初始化方法,在java的class文件中,这个实例初始化方法被称为<init>, 针对源代码中的每一个类的构造方法,java编译器都产生一个<init>方法

**双亲委托机制**: 在双亲委托机制中,各个加载器按照父子关系形成了树形结构,除了根加载器无父类加载器之外,其余的类加载器都有且只有一个父加载器

## 类的卸载

由java虚拟机自带的类加载器所加载的类,在虚拟机的生命周期中,始终不会被卸载,即被根类加载器,扩展类加载器,系统类加载器所加载的类,会被加载他的类始终引用他的Class对象,而java虚拟机本身又引用这些类加载器,所以Class对象始终是可触及的.

由用户自定义的类加载器所加载的类是可以被卸载的

### class被GC回收的三个条件

- 该类所有的实例都已经被GC
- 加载该类的ClassLoader实例已经被GC
- 该类的java.lang.Class对象没有任何地方被引用
- GC的时机我们是不可控的，所以我们对Class的卸载也是不可控的