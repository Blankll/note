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