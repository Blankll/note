# Thread

## 实现多线程

<font color="red">实现多线程只有2种方法</font>

1. 继承Thread类 

   创建一个类，继承Thread类，重写run(),在run中填写业务逻辑，然后在需要使用的地方new 这个类，调用对象的start方法，就会执行run方法。

   ```java
   package study.seven.concurrency;
   
   public class ThreadImpl extends Thread {
       @Override
       public void run() {
           System.out.println("this is my run");
       }
   }
   // 匿名内部类实现Runnable接口
   public class CreateThread {
       public static void main(String[] args) {
           // override method
           Thread threadOver = new Thread() {
               @Override
               public void run() {
                   System.out.println("this is created by rewrite thread run function");
               }
           };
           threadOver.start();
       }
   }
   ```

2. 实现Runnable接口

   实现Runnable接口,在新建线程时指定要执行的Runable然后还可以指定新建线程的名字，线程在start时就会执行指定Runable类实现的run方法的逻辑

   ```java
   package study.seven.concurrency;
   
   public class MyRunnable implements Runnable {
       // thread调用同一个实例化本类的对象时，访问的name数据相同，实现了数据共享
       private String name = "seven"
       @Override
       public void run() {
           System.out.println("this is Runnable thread imp");
           for(int i = 0; i < 10; i++) {
               // get current thread
               Thread t = Thread.currentThread();
               // get thread name
               System.out.println(t.getName() + i);
           }
       }
   }
   
   // 匿名内部类实现Runnable接口
   public class CreateThread {
       public static void main(String[] args) {
           System.out.println("hello");
           // thread created by  anonymous inner class
           Runnable runnable = new Runnable() {
               @Override
               public void run() {
                   System.out.println("this is a thread created by anonymous inner class");
               }
           };
           runnable.run();
       }
   }
   
   package study.seven.concurrency;
   
   public class CreateThread {
       public static void main(String[] args) {
           System.out.println("hello");
           Runnable r1 = new MyRunnable();
           // define thread run Runnable and the name of this thread
           Thread thread1 = new Thread(r1, "threadNameOne");
           Thread thread2 = new Thread(r1, "threadNameTwo");
           // thread start and both of them use same varable of name
           thread1.start();
           thread2.start();
           System.out.println("this is end of main");
       }
   }
   ```


Thread类实现了Runnable的Run方法，两者本质都是执行run方法，只是run方法的来源不同:

- Runnable调用target.run()

- Thread直接重写run方法

两种创建线程最终都是构造Thread类：

- 实现Runnable接口的run方法，并把Runnable实例传递给Thread类，Thread类调用run方法最终 调用Runnable实现的run方法

- 继承Thread类，直接重写run方法，最终运行的就是重写的run方法

  ```java
  @override
  public void run() {
      // target 即Runnable实现的实例
      if(target != null) {
          target.run()
      }
  }
  ```

  

## 启动线程

start

- 准备工作

  - 启动新线程检查线程状态
  - 加入线程组

  - 调用start0这个native方法

- 启动新线程，start之后并不意味着线程会立马执行，创建的新线程处于就绪态

- 不能重复执行start

  ```java
  // package java.lang;
  
  public synchronized void start() {
      if (this.threadStatus != 0) {
          throw new IllegalThreadStateException();
      } else {
          this.group.add(this);
          boolean started = false;
  
          try {
              this.start0();
              started = true;
          } finally {
              try {
                  if (!started) {
                      this.group.threadStartFailed(this);
                  }
              } catch (Throwable var8) {
              }
  
          }
  
      }
  }
  
  private native void start0();
  ```

  native方法：c/c++实现

run

```java
// package java.lang;
public void run() {
    if (this.target != null) {
        this.target.run();
    }
}
```



## 停止线程

java中有3种方式终止运行的线程

1. 使用退出标识,使线程正常退出, 也就是run方法执行完后退出
2. 使用stop强制终止线程 不推荐的做法
3. 使用interrupt来通知线程终止

正确的线程停止方式是使用interrupt来通知而不是强制, interrupt并不能马上停止线程

```java
// run方法中检查线程是否收到中断信号
boolean isInter = Thread.currentThread().isInterrupted();
```

线程处于sleep状态下其他线程发送interrupt信号给该线程时线程线程内部会抛出interruptException异常并清除中断状态，通过try catch sleep方法的异常可以对外部的中断信号做处理

stop会导致线程运行中突然停止，kill -9 一样，会造成数据错乱

suspend和resume挂起线程且不释放线程获得的锁

```java
static boolean interrupted(); // 返回当前线程是否中断，同时将线程中断状态设置为false 作用于调用线程
boolean isInterrupted(); // 返回线程是否中断
Thread.interrupt(); // 将线程设置为中断  ->作用于thread对象创建出的线程
```



## 线程生命周期

```java
Thread.getState();// 获取线程生命周期状态
```

- new

  > new出实例，start之前

- Runnable

  > 调用start方法后
  >
  > 对应操作系统中的ready和running

- Blocked

  等待其他线程释放monitor锁

  > synconized 代码块且锁被其他线程占用时

- Waiting

  等待唤醒信号

  > 调用没有设置wait时间的wait方法后
  >
  > Object.wait()
  >
  > Thread.join()
  >
  > LockSupport.park()

- Timed Waiting

  超时后系统自动唤醒，未超时收到notify，notifyAll时也可以被提前唤醒

  > Thread.sleep(time)
  >
  > Object.wait(time)
  >
  > Thread.join(time)
  >
  > LockSupport.parkNanos(time)
  >
  > LockSupport.parkUntil(time)

- Terminated

  - run方法执行完毕后
  - 执行过程中发生未捕获异常后异常终止

![线程生命周期](../../statics/java/6StateOfThread.png)

一般而言，Blocked，waiting，timed_wating都称为阻塞态

## Thread类和Object类



| class  | method                | desc                    |
| ------ | --------------------- | ----------------------- |
| Thread | sleep                 |                         |
| Thread | join                  | 等待其他线程执行完毕    |
| Thread | yield                 | 放弃已经获取到的cpu资源 |
| Thread | currentThread         | 获取当前执行线程的引用  |
| Thread | start，run            | 启动线程                |
| Thread | interrupt             | 中断线程                |
| Thread | stop，suspend，resume | 已废弃的停止线程相关    |
| Object | wait/notify/notifyAll | 线程休眠和唤醒          |

阻塞阶段被唤醒的条件 

   - 另外一个线程调用notify()方法且被唤醒的刚好是当前阻塞的线程
   - 另外一个线程调用notifyAll()方法，所有线程被唤醒
   - 过了wait(long timeout)规定的超时时间，如果传入0则永久等待
   - 等待的过程中收到了interrupt信号

  唤醒阶段
   - notify会随机唤醒，JVM可以有自己的裁量权
   - notify和wait需要在synchronized代码块中执行，否则会抛出异常[必须先拥有monitor]

  遇到中断
   - 抛出interruptException异常同时释放monitor

状态转换特殊状况

- 从Object.wait()状态刚被唤醒时，通常不能立刻抢到monitor锁，使得线程从Waiting进入到Blocked状态，抢到锁后进入Runnable状态
- 如果发生异常，可以直接跳到Terminated状态比如从Waiting直接跳转到Terminated

sleep方法可以让线程进入Waiting状态，并且不占用CPU资源，但是不释放锁，直到规定时间后再执行，休眠期间如果被中断，会抛出异常并清除中断状态



CountDownLatch&CyclicBarrier



yield

- 释放cpu时间片，yield方法的线程处于Runnable状态
- JVM不保证使用yield就释放cpu
- yield释放cpu资源后可以随时被再次调动

## 线程属性

- thread id
  - 全局唯一，不可修改  从1开始递增
- thread name
- daemon
- thread priority
  - java中有10个线程优先级，默认为5
  - 程序设计不应当依赖于优先级
  - java优先级依赖于运行的系统对优先级的处理
  - linux中优先级将会被忽略 => 也就是说,在Linux环境下设置优先级是无效的

## 线程异常

## 多线程利弊

## 线程创建



## 线程安全



## 多线程产生的问题

- 调度： 上下文切换
- 协作：内存同步

###  timer定时器

定时进行某项工作

指定一个定时器要做的任务，写在run 方法中

```java
package study.seven.concurrency;

import java.util.TimerTask;

public class MyTimer extends TimerTask {
    @Override
    public void run() {
        System.out.println("this is timer task");
    }
}
```

调用timer实例的schedule方法，传入我们定义的继承TimerTask类的实例，第二个参数为延时多少毫秒后开始，第三个参数为每隔多长的间隔执行一次定时器的run方法。

```java
package study.seven.concurrency;

import java.util.Timer;

public class TimerTest {
   public static void main(String[] args) {
       Timer timer = new Timer();
       timer.schedule(new MyTimer(), 2000, 3000);
       timer.cancel();// quit timer
   }
}
```

### 线程间的通讯

object.wait()等待

object.notify()通知线程继续执行

```java
package study.seven.concurrency;

import java.util.stream.Stream;

public class ThreadContact {
    private Object lock = new Object();
    private boolean isProduced = false;
    private int i = 100;

    public void produce() {
        synchronized (lock) {
            if(isProduced) {
                try {
                    lock.wait();
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }else {
                i++;
                System.out.println("p->" + i);
                lock.notify();
                isProduced = true;
            }
        }
    }
    public void consume() {
        synchronized (lock) {
            if(isProduced) {
                System.out.println("c->" + i);
                lock.notify();
                isProduced = false;
            }else {
                try {
                    lock.wait();
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
        }
    }
    // jvm没有对notify的目标没有进行定义,导致后面全部都在wait
    public static void main(String[] args) {
        final ThreadContact contact = new ThreadContact();
        Stream.of("p1", "p2").forEach(n ->
            new Thread(() -> {
                while (true) {
                    contact.produce();
                }
            }).start()
        );
        Stream.of("c1", "c2").forEach(n ->
                new Thread(() -> {
                    while (true) {
                        contact.consume();
                    }
                }).start()
        );
    }
}
```

## sleep和wait的区别

1. sleep is the method of thread, but the wait is the method of object.

2. sleep will not release the object monitor(lock),but the wait will release the monitor and add to the object monitor waitiong queue;
3. use sleep not depend ont the monitor,but wait need.
4. the sleep method not need be wakeup, but wait need(notify)

``Runtime.getRuntime().addshutdownHook(new thread(somthing))`` 可以监听线程中断事件，可以在启动的线程中添加业务逻辑，如释放之前申请而没有释放的资源。

kill -9 时没有任何机会执行hook,会强制被杀死。

## 线程运行时异常捕获

```java
public class ThreadException {
    private final static int A = 10;
    private final static int B = 0;

    public static void main(String[] args) {
        Thread t = new Thread(() -> {
            try {
                Thread.sleep(5_000L);
                int result = A / B;
                System.out.println(result);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        });

        // handle thread runtime exception
        t.setUncaughtExceptionHandler((thread, e) -> {
            System.out.println(e);
            System.out.println(thread);
        });

        t.start();
    }
}
```

## Thread group

when java application run，jvm create a thread automaticly to run method of main, and this thread name is ``main`` , the group main blong to is also named ``main``

when any thread created the defalult group this inheretence his father's thread group.

thread group exsample

```java
package study.seven.concurrency;

/**
 * @Auther: Blank
 * @Description: study.seven.concurrency
 * @Date: 1/12/19
 * @Version: 1.0
 */
public class ThreadGroup {

    public static void main(String[] args) {
        java.lang.ThreadGroup threadGroupOne = new java.lang.ThreadGroup("groupOne");
        java.lang.ThreadGroup threadGroupTwo = new java.lang.ThreadGroup("groupTwo");

        Thread threadOne = new Thread(threadGroupOne, "threadOne") {
            @Override
            public void run() {
                System.out.println(getThreadGroup().getName());
                System.out.println(getThreadGroup().getParent());
                try {
                    Thread.sleep(10_000);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
        };
        Thread threadTwo = new Thread(threadGroupTwo, "threadTwo") {
            @Override
            public void run() {
                // thread group can browser brother group's info
                System.out.println("brother info:");
                System.out.println(threadGroupOne.getName());
                Thread[] threads = new Thread[threadGroupOne.activeCount()];
                int num = threadGroupOne.enumerate(threads);
                System.out.println("num:" + num);

            }
        };
        threadOne.start();
        threadTwo.start();
    }
}
```

## ThreadPool

1. thread queue

2. reject strategy: throw exception, abandon synconized, tmp queue
3. init(min) init min number of threads
4. active threads number
5. max of threads number

example of thread pool

```java
package study.seven.concurrency;

import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;

/**
 * @Auther: Blank
 * @Description: study.seven.concurrency
 * @Date: 1/12/19
 * @Version: 1.0
 */
public class ThreadPoolOne {
    // size of thread number
    private final int size;
    // default thread number
    private final static int DEFAULT_SIZE = 10;
    private static volatile int seq = 0;
    // thread name prefix
    private final static String THREAD_PREFIX = "SIMPLE_THREAD_POOL-";
    // task queue to store tasks
    private final static LinkedList<Runnable> TASK_QUEUE = new LinkedList<>();
    // thread group
    private final static java.lang.ThreadGroup GROUP = new java.lang.ThreadGroup("poolGroup");
    // store thread prepare to do thread pool
    private final static List<WorkerThread> THREAD_QUEUE = new ArrayList<>();


    public ThreadPoolOne(int size) {
        this.size = size;
    }
    public ThreadPoolOne() {
        this(DEFAULT_SIZE);
        this.init();
    }
    private void init() {
        // creat default threads into thread pool
        for(int i = 0; i < size; i++) {
            createWorkerThread();
        }
    }

    /**
     * submit task wait to do
     * @param runnable
     */
    public void submit(Runnable runnable) {
        synchronized(TASK_QUEUE) {
            TASK_QUEUE.addLast(runnable);
            TASK_QUEUE.notifyAll();
        }
    }

    private enum TaskState {
        FREE, RUNNING, BLOCKED, DEAD
    }

    // define a self thread to define store thread info, concurrency strategy
    private static class WorkerThread extends Thread {
        // setting thread's default state
        private volatile TaskState taskState = TaskState.FREE;

        /**
         * constructor to define thread name, thread group
         * @param group thread group
         * @param name thread's name
         */
        public WorkerThread(java.lang.ThreadGroup group, String name) {
            // setting thread's name and group
            super(group, name);
        }
        public TaskState getTaskState() {
            return this.taskState;
        }

        @Override
        public void run() {
            OUTER:
            // thread get task to run, except DEAD task(DEAD meanings unable to run)
            while(this.taskState != TaskState.DEAD) {
                Runnable runnable = null;
                // only  one thread can get task at the same time
                synchronized(TASK_QUEUE) {
                    // if task is empty  block here, wait add some task give thread to do
                    while(TASK_QUEUE.isEmpty()) {
                        taskState = TaskState.BLOCKED;
                        try {
                            TASK_QUEUE.wait();
                        } catch (InterruptedException e) {
                            break OUTER;
                        }
                    }
                    // task queue not empty and get task
                    runnable = TASK_QUEUE.removeFirst();
                }

                // run the task
                if(null != runnable) {
                    taskState =TaskState.RUNNING;
                    // run the task's mission
                    runnable.run();
                    taskState = TaskState.FREE;
                }
            }
        }

        public void close() {
            this.taskState = TaskState.DEAD;
        }
    }

    private void createWorkerThread() {
        // create a new WorkerThread
        WorkerThread thread = new WorkerThread(GROUP, THREAD_PREFIX + (seq++));
        // start this task
        thread.start();
        // add current thread to thread queue
        THREAD_QUEUE.add(thread);
    }

    public static void main(String[] args) {
        ThreadPoolOne poolOne = new ThreadPoolOne();
        // add task to TASK_QUEUE
        for(int i = 0; i < 40; i++) {
            poolOne.submit(() -> {
                System.out.println("runnable be serviced by:" + Thread.currentThread().getName() + "START");
                try {
                    // define task's mission here
                    Thread.sleep(10000);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
                System.out.println("runnable be serviced by:" + Thread.currentThread().getName() + "FINISHED");
            });
        }
    }
}
```



interrupt仅仅设置线程状态，并不会中断线程





## tips

实现多线程的两种方法那种更好 -> Runnable更好

1. Runnable结构上更好，业务和线程解耦
2. Runnable可以利用java线程池，而继承Thread类每次都要新建一个线程
3. java不支持多继承而支持多实现，Runnable有更好的扩展性