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

    