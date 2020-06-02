# juc

## AQS

AbstractQueuedSynchronizer：抽象队列同步器，AQS定义了一套多线程访问共享资源的同步器框架，许多同步类实现都依赖于它，如常用的ReentrantLock/Semaphore/CountDownLatch...。

AQS维护了一个volatile int state（代表共享资源）和一个FIFO线程等待队列（多线程争用资源被阻塞时会进入此队列）。

CLH：Craig、Landin and Hagersten队列，是单向链表，AQS中的队列是CLH变体的虚拟双向队列（FIFO），AQS是通过将每条请求共享资源的线程封装成一个节点来实现锁的分配。

![aqs](../statics/java/aqs.png)

AQS两种资源共享方式：

- Exclusive： 独占，只有一个线程能执行，如ReentrantLock；
- Share： 共享，多个线程可同时执行，如Semaphore/CountDownLatch；

自定义的这些同步器在实现时只需要去实现共享资源state获取与释放方式即可，AQS底层已经实现了线程等待队列的维护。

自定义同步器实现方式：

- isHeldExclusiv(): 该线程是否正在独占资源，只有用到condition才需要取实现它
- tryAcquire(int): 独占方式，尝试获取资源，成功返回true，否则返回false
- tryRelease(int): 独占方式，尝试释放资源，成功返回true，否则返回false
- tryAcquireShared(int): 共享方式，尝试获取资源，返回剩余可用资源数
- tryReleaseShared(int)：共享方式，尝试释放资源，释放成功且允许唤醒后续等待节点放回true，否则返回false

自定义实现：

1. ReentrantLock(可重入锁)

   - 初始化state为0，表示未锁定状态
   - 线程A LOCK时会调用tryAcquire独占该锁且state+=1
   - 线程A未释放锁前其他线程tryAcquire都会失败
   - 释放锁前，A线程可以重复获取该锁，state会累加(注意获取几次就要释放几次)
   - 直到线程A unlock且state为0时其他线程才有机会获得该锁

2. CountDownLatch

   - 任务分为N个子线程执行，state也初始化为N，
   - N个子线程可能是并行执行
   - 每个子线程执行完毕后countDown()一次，state CAS减一
   - 当state到0时，unpark()调用主线程，调用主线程从wait()函数返回，继续执行后续动作


参考文章：http://www.cnblogs.com/waterystone/p/4920797.html



## CAS

Compare-And-Swap：由cpu指令保证操作原子性

内存位置实际值V，预期值A，目标设置值B，CAS操作就是当A的值等于V时将V值设置为目标值B且这个过程是一个原子操作

Unsafe是CAS的核心类。java无法直接访问底层操作系统，而是通过本地native方法来访问，JVM提供了一个后门，JDK的Unsafe类，他提供了硬件级别的原子操作。

Unsafe对象中的valueOffset表示变量值在内存中的偏移地址，Unsafe就是根据内存偏移地址来直接获取变量在内存中的位置和值，从而实现CAS

CAS的应用：

- 乐观锁
- ConcurrentHashMap
- 原子类

CAS存在的问题：

- ABA问题
- 自旋时间过长

## Lock

### 公平锁和非公平锁

```java
// 公平锁
ReentrantLock lock = new ReentrantLock(true);
// 非公平锁
ReentrantLock lock = new ReentrantLock();
```

公平锁和非公平锁的对比

|          | 优势                                                   | 劣势               |
| -------- | ------------------------------------------------------ | ------------------ |
| 公平锁   | 各线程公平平等，每个线程在等待一段时间后，总有执行机会 | 更慢，吞吐量更小   |
| 非公平锁 | 更快，吞吐量更大                                       | 有可能产生线程饥饿 |

## 共享锁和排他锁

共享锁：如读锁

排他锁：如读写锁中的写锁



### 读写锁

ReentrantReadWriteLock

- 插队：不允许读锁插队，写锁总是可以插队，非公平锁，读锁可以在队列头节点为非写锁时插队
- 升降级： 允许降级不允许升级



### 锁的升级&降级

ReentrantReadWriteLock：可以降级(即从写锁降为读锁)，不可升级

### 自旋&阻塞

自旋：在目标锁被占用时进行自旋等待，不释放cpu执行权限，从而避免线程切换带来的开销，对于线程执行时间短的应用有优势，对于执行时间较长的程序，自旋会耗费处理器资源

- 在java1.5即以上的java.util.concurrent中的atmoic包下的类基本都是自旋锁的实现
- AtomicInteger自旋锁的实现原理是CAS，AtomicInteger中调用unsafe进行自增操作的源码中的do-while循环就是一个自旋操作，如果在修改过程中遇到其他线程竞争导致没有修改成功，就在while里死循环，直至修改成功。

阻塞：在目标锁被占用时放弃CPU执行权限，将自己阻塞挂起，等待线程其他线程释放目标锁时被唤醒



### JVM锁优化

- 自旋自适应：jvm根据自旋锁的效率判断是否进行自旋操作还是直接挂起线程
- 锁消除：对无需加锁而用户却加锁的环境下JVM将锁消除
- 锁粗化：减少反复的加锁解锁，加多个加锁解锁合并为一个加锁解锁，即增大代码块区间。



## 原子类



AtomicInteger加载Unsafe工具，用来直接操作内存数据

AtomicIntegerFieldUpdater:对普通变量进行升级

使用场景：

- 对外部依赖的class中的非原子性field进行原子性升级
- 偶尔需要使用一个原子get-set操作

```java
public class IntegerUpdater implements Runnable{
    static Candidate tom;
    static Candidate peter;
    // 升级的类和字段, 其实是利用了反射
    public static AtomicIntegerFieldUpdater<Candidate> scoreUpdater = AtomicIntegerFieldUpdater.
            newUpdater(Candidate.class, "score");
    public static void main(String[] args) throws InterruptedException {
        tom = new Candidate();
        peter = new Candidate();
        IntegerUpdater updater = new IntegerUpdater();
        Thread t1 = new Thread(updater);
        Thread t2 = new Thread(updater);
        t1.start();
        t2.start();
        t1.join();
        t2.join();
        System.out.println("original:" + peter.score);
        System.out.println("updater:" + tom.score);
    }

    @Override
    public void run() {
        for (int i = 0; i < 10000; i++) {
            peter.score++;
            scoreUpdater.getAndIncrement(tom);
        }
    }
}

class Candidate {
    // 变量不能为静态
    volatile int score;
}
```



Adder

- java8中引入

- 高并发下LongAdder比AtomicLong效率高[空间换时间]

- 在竞争激烈时，LongAdder将不同线程对应到不同的Cell上进行修改，降低冲突概率提高并发性[多段锁的理念]

- AtomicLong基于CAS，在高并发&多线程下有自旋开销

- LongAdder引入 了分段累加的概念

  - base变量：在竞争不激烈时直接以CAS模式在base变量上进行累加

  - ceil[]数组：在竞争激烈时各个线程分别累加到自己的槽ceil[i]中[空间换时间]

  - sum：求和过程中并没有加锁，在sum过程中进行操作可能造成结果不正确

    ```java
    public long sum() {
        Cell[] cs = cells;
        long sum = base;
        // 是否进行了分段累加
        if (cs != null) {
            for (Cell c : cs)
                if (c != null)
                    sum += c.value;
        }
        return sum;
    }
    ```




## 栈封闭

把变量写在线程内部

方法中的局部变量存储在线程私有的栈空间中，不会被其他线程访问到，所以是线程安全的，这就是“栈封闭”技术，是“线程封闭”技术的一种情况



```java
String a = "string2"; // 堆内存中
final String b = "string"; // 方法区运行时常量池中
String d = "string"; // 堆内存中
String c = b + 2; // 堆内存中已经有 string2字符串，指向这个字符串 # 这里的b如同宏替换
String e = d + 2; // 运行时确定，在堆上生成对象， hashcode不一样
System.out.println((a == c)); // true
System.out.println((a == e)); // false
```



## 并发容器

- ConcurrentHashMap : 线程安全版的Hashmap
- CopyOnWriteArrayList： 线程安全的List
- CopyOnWriteArraySet： 线程安全的Set
- BlockinQueue： 接口，阻塞队列，常用于数据共享通道
- ConcurrentLinkedQueue： 高效的非阻塞并发队列，相当于一个线程安全的LinkedList
- ConcurrentSkipListMap： 使用跳表的数据结构进行快速查找

### ConcurrentHashMap

1.7的ConcurrentHashMap

- 最外层是多个segment，每个segment的底层数据结构月HashMap类似，仍然是数组和链表组成的拉链法
- 每个segment独立上ReentrantLock锁，每个segment之间互不影响，提高了并发效率
- 默认0-15共16个segment，所以最多可以同时支持16个线程并发写，可以在初始化时设置其他默认值，但是一旦初始化后不可再扩容segment

1.8的ConcurrentHashMap

- 同HashMap一样是node+链表+红黑树的结构
- CAS+synchronized保证并发安全
- 使用8为为使用红黑树的分界是以泊松分布概率计算得到的

### CopyOnWriteArrayList

- 代替Vector和SynchronizedList
- 读取无锁，写入不会阻塞读取操作，只有写入和写入之间需要进行同步等待
- 可以在迭代过程中进行修改
- 在已经生成iterator后进行对LIST的修改在iterator中不可见，所以并非实时的
- 使用了ReentrantLock

# 并发流程控制

让线程间相互配合，完成目标任务

并发流程控制工具类

| class          | effect                                                       | desc                                                         |
| -------------- | ------------------------------------------------------------ | ------------------------------------------------------------ |
| Semaphore      | 信号量，通过控制“许可证”的数量保证线程之间的配合             | 线程只有在拿到“许可证”后才能继续运行，相比于其他同步器更灵活 |
| CyclicBarrier  | 栅栏，线程会等待，直到足够多的线程达到了事先规定的数目后进行下一步动作 | 适用于线程之间相互等待处理结果就绪的场景                     |
| Phaser         | 类似CyclicBarrier，计数可变                                  | java7加入                                                    |
| CountDownLatch | 门闩，类型CyclicBarrier，数量递减到0时触发动作               | 不可重复使用                                                 |
| Exchanger      | 让两个线程在合适时交换对象                                   | 使用场景：当两个线程工作在同一个类的不同实例上时，用于交换数据 |
| Condition      | 可以控制线程的等待和唤醒                                     | Object.wait()的升级版                                        |



## Semaphore

信号量用于控制有限资源的使用，维护一个“许可证”计数，线程可以获取“许可证”，也可以释放许可证，许可证为0时线程获取许可证需要等待，直到另外一个线程释放了许可证

- 初始化Semaphore(int permits, boolean fair)时指定许可证数量
- 在需要获取许可证的地方调用acquire()或者aquireUniterruptibly()方法
- 使用完成时调用release()来释放信号量

```java
static Semaphore semaphore = new Semaphore(3, true);

public static void main(String[] args) {
    ExecutorService service = Executors.newFixedThreadPool(50);
    for (int i = 0; i < 100; i++) {
        Runnable runnable = () -> {
            try {
                semaphore.acquire();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            System.out.println(Thread.currentThread().getName() + ": 取得信号量");
            try {
                Thread.sleep(2000);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            System.out.println(Thread.currentThread().getName() + ": 释放信号量");
            semaphore.release();
        };
        service.submit(runnable);
    }
    service.shutdown();
}
```

## CyclicBarrier

循环栅栏，线程达到预定数量后执行预定任务，同时各个线程也会执行自身await之后的逻辑，CyclicBarrier是可重用的

```java
CyclicBarrier barrier = new CyclicBarrier(5, () -> {
    System.out.println("线程数量满足预期");
});
Runnable runnable = () -> {
    System.out.println(Thread.currentThread().getName() + " 前往集合点");
    try {
        Thread.sleep((long) (Math.random() * 10000));
        System.out.println(Thread.currentThread().getName() + " 到达集合点，等待其他线程到达");
        barrier.await();
        // barrier条件满足后执行
        System.out.println(Thread.currentThread().getName() + " 集合点满足条件后继续后续逻辑");
    } catch (InterruptedException | BrokenBarrierException e) {
        e.printStackTrace();
    }
};
public static void main(String[] args) {
    CyclicTest test = new CyclicTest();
    for (int i = 0; i < 100; i++) {
        new Thread(test.runnable).start();
    }
}
```

## CountDownLatch

倒数门闩，人满了拼团成功，CountDownLatch递减到0后不可重用

- CountDownLatch (int count): 构造函数，参数count为需要倒数的数值
- await(): 调用该方法的线程会被挂起，直到count递减为0才继续执行 
- countDown(): 将count值减1，count为0时唤醒等待线程

```java
public void contTest () {
        final CountDownLatch latch = new CountDownLatch(1);
        ExecutorService service = Executors.newFixedThreadPool(5);
        for (int i = 0; i < 5; i++) {
            Runnable runnable = new Runnable() {
                @Override
                public void run() {
                    System.out.println(Thread.currentThread().getName() + ": 准备完毕，等待发令");
                    try {
                        latch.await();
                        System.out.println(Thread.currentThread().getName() + ": 起跑");
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                }
            };
            service.submit(runnable);
        }
        try {
            Thread.sleep(5000);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        System.out.println("发令！");
        latch.countDown();
    }
```

## Condition

又称条件对象，作用如下：

- 线程在需要等待某个条件的时候执行condition.await()方法，线程一旦执行该方法就会进入阻塞状态

- 其他线程通过condition.signal()方法时jvm会唤醒等待这个condition的线程，使线程的状态从阻塞变为就绪态(runnable)

- signal()与signalAll()区别

  > - signal()是公平的，只会唤醒等待时间最长的线程
  > - signalAll()会唤醒所有正在等待的线程

- 和Object.awati()一样，await方法会自动释放持有的Lock锁，不需要自己手动释放

- 和Object.awati()一样，调用await时必须持有锁，否则会抛出异常

```java
private int queueSize = 10;
private PriorityQueue<String> queue = new PriorityQueue<>(queueSize);
private Lock lock = new ReentrantLock();
private Condition notFull = lock.newCondition();
private Condition notEmpty = lock.newCondition();
Runnable consumer = () -> {
    while (true) {
        try {
            lock.lock();
            while (queue.size() == 0) {
                System.out.println("[消费者] " + Thread.currentThread().getName() + " 队列为空，等待数据");
                try {
                    notEmpty.await();
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
            String data = queue.poll();
            notFull.signalAll();
            System.out.println("[消费者] " + Thread.currentThread().getName() + " 消费数据： " + data);
        } finally {
            lock.unlock();
        }
    }
};
Runnable produce = () -> {
    while (true) {
        try {
            lock.lock();
            while (queue.size() == queueSize) {
                System.out.println("[生产者] " + Thread.currentThread().getName() + " 队列已满，等待空余");
                try {
                    notFull.await();
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
            String data = "data-" + System.currentTimeMillis();
            queue.offer(data);
            notEmpty.signalAll();
            System.out.println("[生产者] " + Thread.currentThread().getName() + " 生产数据：" + data);
        } finally {
            lock.unlock();
        }
    }
};
public static void main(String[] args) {
    CondittionCp cp = new CondittionCp();
    new Thread(cp.produce).start();
    new Thread(cp.consumer).start();
}
```



## Future&Callable

Future相当于一个存储器,他存储call()任务的结果，call的执行时间取决于call方法的执行情况，无法提前确定。

利用Future.get()来获取Callable接口返回的执行结果，通过Future.isDone()来判断任务是否执行完成，以及取消任务，获取任务的结果等等

在call()方法未执行完毕前调用Future.get()方法会使得调用线程被阻塞，直到call()方法返回了结果后Future.get()方法得到结果同时使得调用线程切换为runnable状态