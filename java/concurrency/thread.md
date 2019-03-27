# Thread

## 线程创建

创建一个类，继承Thread类，重写run(),在run中填写业务逻辑，然后在需要使用的地方new 这个类，调用对象的start方法，就会执行run方法。

```java
package study.seven.concurrency;

public class ThreadImpl extends Thread {
    @Override
    public void run() {
        System.out.println("this is my run");
    }
}
```



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

匿名内部类实现Runnable接口

```java
package study.seven.concurrency;

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

## 线程生命周期

new 

Runnable

Waiting

Timed waiting

Terminated

## 线程安全



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

