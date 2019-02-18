## 定义

```java
public @interface TestAnnotation{
    
}
```

## 使用

```java
@TestAnnotation// 相当于把注解贴到类上
public class Test{
    
}
```

## 元注解

元注解就是注解到自定义的注解上的注解，共有5种元注解标签

＠Retention　保留期，规定注解存活时间

> - RetentionPolicy.SOURCE 注解只在源码阶段保留，在编译器进行编译时它将被丢弃忽视。
> - RetentionPolicy.CLASS 注解只被保留到编译进行的时候，它并不会被加载到 JVM 中。
> - RetentionPolicy.RUNTIME 注解可以保留到程序运行的时候，它会被加载进入到 JVM 中，所以在程序运行时可以获取到它们。

```java
@retention(RetentionPolicy.RUNTIME)
public @interface TestAnnotation{
    
}
```



@Documented　将注解的元素包含到javadoc中

@Target　指定注解使用的场景

> ElementType.ANNOTATION_TYPE 可以给一个注解进行注解
> ElementType.CONSTRUCTOR 可以给构造方法进行注解
> ElementType.FIELD 可以给属性进行注解
> ElementType.LOCAL_VARIABLE 可以给局部变量进行注解
> ElementType.METHOD 可以给方法进行注解
> ElementType.PACKAGE 可以给一个包进行注解
> ElementType.PARAMETER 可以给一个方法内的参数进行注解
>
> ElementType.TYPE 可以给一个类型进行注解，比如类、接口、枚举

@Inherited 被注解的类的子类也拥有父类的注解

@Repeatable　是否可重复

## 注解的属性

注解只有成员变量，没有方法,

```java
@Target(ElementType.Type)
@Retention(RetentionPolicy.RUNTIIME)
public @interface mutlotation{
	int id();　// 方法名是注解属性的名字，返回值类型是属性的类型
    String name（） default "seven"； //可以设置默认值
}
//使用
@mutlotation(id=1,name="Blank")
public class User {
	
}
//如果只有一个属性
@Target(ElementType.Type)
@Retention(RetentionPolicy.RUNTIIME)
public @interface oneAnnotation{
    int idc();
}
// 使用注解时直接将值写在注解中就可以
//使用
public class User {
	@oneAnnotation(533)
    int idcValue; // 现在idcValue的值就是533
}
//如果注解没有任何属性，可以省略()
```

## java中预置的注解

@Deprecated 标记过时的元素

@Override 重写父类的方法

@SuppressWarnings 阻止警告

@SafeVararges 参数安全类型注解

@FunctionalInterface 函数式接口注解

## 注解的提取

```java
@mutlAnnotation(id=2,name="secondone")
public class User{
    // 测试是否使用了注解
    boolean test = User.class.isAnnotationPresent(mutlAnnotation.class);
    if(test){
        //通过反射获取实例
        mutlAnnotation one = User.class.getAnnotation(mutlAnnotation.class);
        // 反射的值
        int id = one.id;
    }
}
```

