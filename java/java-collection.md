# java集合

集合框架主要包括两种类型的容器，一种是集合（Collection），存储一个元素集合，另一种是图（Map），存储键/值对映射。Collection接口又有 3 种子类型，List、Set 和 Queue，常用的有 具体实现类ArrayList、LinkedList、HashSet、LinkedHashSet、HashMap、LinkedHashMap等.

List,Set,Queue实现了Collection接口

HashMap,TreeMap实现了Map接口

## List接口 java.util.List

1. List接口可以存放任意的数据，而且List接口中的内容是可以重复的
2. List接口常用的子类  

- ArrayList 数组实现（插入删除慢）

- LinkList 双向链表实现（查找慢）
- Vector 线程安全

### 常用操作
- [ ] 判断集合是否为空：boolean isEmpty();
- [ ] 查找指定对象是否存在： int indexOf(Object o);
```java
package cn.ynnu.corejava.collection;

import java.util.ArrayList;
import java.util.List;

public class LIstDemo01 {
	public static void main(String[] args) {
		List<String> lists = null;//声明
		lists = new ArrayList<String>();//引用
		lists.add("a");
		lists.add("b");
		for(int i = 0; i < lists.size(); i++) {
			System.out.println(lists.get(i));
		}
		
	}
}

```
#### 比较
| 比较        | ArrayList     | Vector     |
| ----------- |:-------------:| -----:     |
| 推出时间    | JDK1.2        | JDK1.0     |
| 性能        | 采用异步处理方式，高性能|       采用同步处理方式，低性能|
| 线程安全    |属于非线程安全| 属于线程安全|

## Set接口
1. Set接口中不能加入重复的元素，但是可以排序
2. Set接口中常用的子类

 - 散列存放：HashSet
 - 有序存放：TreeSet  

```java
import java.util.Set;
import java.util.TreeSet;

public class CollectionTest {
    public static void main(String[] args) {
        Set<String> sss = new TreeSet<>();
        sss.add("s");
        sss.add("ss");
        sss.add("sss");
        sss.add("ssss");
        for (String s : sss) {
            System.out.println(s);
        }
    }
}
```



## Iterator接口
- 集合输出的标准操作
- 操作原理： Iterator专门的迭代输出接口，迭代输出就是将元素一个个进行判断，判断其是否有内容，如果有内容则把内容取出
- Collection接口扩展了Iterator接口，所以对于标准类库中的任何集合都可以使用for each循环;
常用操作：isRmputy, indexOf()
```java
package cn.ynnu.corejava.collection;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

public class ListDemo02 {
	public static void main(String[] args) {
		List<String> list = new ArrayList<String>();
		list.add("A");
		list.add("B");
		list.add("C");
		list.add("D");
		list.add("E");
		list.add("F");
		
		Iterator<String> iter = list.iterator();
		while(iter.hasNext()) {
			System.out.println(iter.next());
		}
		
		list.remove(5);//传入下标
		Iterator<String> iter2 = list.iterator();
		while(iter2.hasNext()) {
			System.out.println(iter2.next());
		}
	}
}

```
**注意**： List，Collection，Set都有一个remove方法，
在进行迭代输出时一定不能使用集合自带的remove方法，要用迭代输出自带的remove进行操作;
如果由多个迭代器同时对同一个集合进行操作，如果有一个使用了迭代器的remove方法，也会抛出异常;

## java.util.Map

存放Hash键值对对象 key both unique

实现:

- HashTable 不允许有null值（key和value）线程安全(老)

- HashMap 允许有null值（key 和value都可以）非线程安全

  > 1.8之前，HashMap采用数组+链表实现，使用链表处理冲突，hash值湘潭市时存储在一个链表里,所以,当hash值相等的元素较多时，通过key值依次查找的效率较低。1.8开始,HashMap采用数组+链表+红黑树实现，当链表长度超过阈值（8）时，将链表转换为红黑树，减少了查找时间。

- LinkedHashMap 继承自HashMap,元素既可以按照它们插入的顺序排序，也可以按它们最后一次被访问的顺序排序。

- TreeMap 基于红黑树数据结构的实现，键值可以使用Comparable或Comparator接口来排序。TreeMap继承自AbstractMap，map中的元素都是有序的.因为:

  > TreeMap继承自AbstractMap，同时实现了接口NavigableMap，而接口NavigableMap则继承自SortedMap。SortedMap是Map的子接口，使用它可以确保图中的条目是排好序的。

map的遍历

```java

import java.util.*;
 
public class Test{
     public static void main(String[] args) {
      Map<String, String> map = new HashMap<String, String>();
      map.put("1", "value1");
      map.put("2", "value2");
      map.put("3", "value3");
      
      //第一种：普遍使用，二次取值
      System.out.println("通过Map.keySet遍历key和value：");
      for (String key : map.keySet()) {
       System.out.println("key= "+ key + " and value= " + map.get(key));
      }
      
      //第二种
      System.out.println("通过Map.entrySet使用iterator遍历key和value：");
      Iterator<Map.Entry<String, String>> it = map.entrySet().iterator();
      while (it.hasNext()) {
       Map.Entry<String, String> entry = it.next();
       System.out.println("key= " + entry.getKey() + " and value= " + entry.getValue());
      }
      
      //第三种：推荐，尤其是容量大时
      System.out.println("通过Map.entrySet遍历key和value");
      for (Map.Entry<String, String> entry : map.entrySet()) {
       System.out.println("key= " + entry.getKey() + " and value= " + entry.getValue());
      }
    
      //第四种
      System.out.println("通过Map.values()遍历所有的value，但不能遍历key");
      for (String v : map.values()) {
       System.out.println("value= " + v);
      }
     }
}

```

### HashMap

hashmap的数据结构暴力了初始数组,链表,红黑树

插入数据时使用pos=key%size来进行插入数据

当两个或两个以上的item的key结果相同value不同时(发生冲突),就会挂载在数组初始化位置的链表后

当某个节点后出现过多的链表节点后,就会转换成红黑树以提高效率

数组容量2的倍数; 提高运算速度,增加散列度,降低冲突,减少内存碎片

hash函数: hashcode的高16位与低16位进行异或求摸,增加散列度,降低冲突

插入冲突:通过单链表解决冲突,如果链表长度超过TREEIFY_THRESHOLD(8), 进行单链表和红黑树转换以提高冲突链表查询速度

```java
static final int DEFAULT_INITIAL_CAPACITY = 1 << 4; // aka 16
```

capacity * DEFAULT_LOAD_FACTOR = 扩容阈值

扩容: 扩容条件: 实际节点数大于等于容量的四分之三;会扩容为原大小的两倍

扩容后的排布: 要么是原下标位置,要么是原下标+原容量位置

jdk1.8以前是头插法, jdk1.8开始使用尾插发





Hashtable 是不允许键或值为 null 的，HashMap 的键值则都可以为 null。

ConcurrentHashMap键值都不可以为null

## Queue

队列是一种特殊的线性表，它只允许在表的前端进行删除操作，而在表的后端进行插入操作。

接口Deque是一个扩展自Queue的双端队列，它支持在两端插入和删除元素

PriorityQueue类实现了一个优先队列，

LinkedList类实现了Queue接口，因此我们可以把LinkedList当成Queue来用。

```java
//add()和remove()方法在失败的时候会抛出异常(不推荐)
Queue<String> queue = new LinkedList<String>();
 //添加元素
queue.offer("a");
queue.offer("b");
// 可以循环输出队列中的元素
for(String q : queue){
     System.out.println(q);
}
System.out.println("poll="+queue.poll()); //返回第一个元素，并在队列中删除
System.out.println("element="+queue.element()); //返回第一个元素 
System.out.println("===");
System.out.println("peek="+queue.peek()); //返回第一个元素 
```

  * ArrayBlockingQueue ：一个由数组支持的有界队列。
  * LinkedBlockingQueue ：一个由链接节点支持的可选有界队列。
  * PriorityBlockingQueue ：一个由优先级堆支持的无界优先级队列。优先队列中元素被赋予优先级，拥有高优先级的先被删除
  * DelayQueue ：一个由优先级堆支持的、基于时间的调度队列。
  * SynchronousQueue ：一个利用 BlockingQueue 接口的简单聚集（rendezvous）机制。

## 并发容器

- ConcurrentHashMap