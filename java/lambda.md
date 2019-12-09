# Lambda





stream

https://www.ibm.com/developerworks/cn/java/j-lo-java8streamapi/

Model Code as Data 编码及数据，尽可能轻量级的将代码封装为数据

函数式接口是java中只包含一个接口方法的interface

语义化检测注解：@FunctionalInterface

函数式接口中可以包含默认方法和静态接口方法

java.util.function中提供了大量的函数式接口

```java

Predicate<T> // 返回Boolean
Consumer<T> // 消费，不返回结果
Function<T,R> // 处理，传入T类型参数，返回R类型
Suplier<T> // 生成T对象工厂
UnaryOperator<T> // 传入 T类型参数，处理后返回
BinaryOperator<T> // 传入两个t对象，返回一个t对象
```



## Lamda表达式变量捕获

lamda表达式中的this指向所属方法所在的对象

lamda表达式变量优化了匿名内部类的变量捕获机制



在lamda表达式底层构建过程中会将lamda表达式构建为private static 的方法





## stream

中间操作API (intermediate)

- 中间操作结果是一个stream对象

- 可以有一个或多个中间操作

- 中间操作只做操作记录，不具体执行，直到结束操作发生时才执行

- 无状态操作：数据处理时当前操作不受前置操作的影响

  > map/filter/peek/parallel/sequential/unordered

- 有状态操作：数据处理时当前操作受到前置操作的影响

  > distinct/sorted/limit/skip

终结操作 (terminal)

一个stream对象只能有一个terminal操作，一旦发生就会开始执行处理流程，生成处理结果，过程不可逆

- 短路操作(short ciruiting)：当前stream对象必须处理完集合中的所有操作，才能得到结果

  > forEach/forEachOrdered/toArray/reduce/collect/min/max/count/iterator

- 非短路操作： 当前stream一旦满足某个条件就可以得到结果

  > anyMatch/allMatch/noneMatch/findFirst/findAny