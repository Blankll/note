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