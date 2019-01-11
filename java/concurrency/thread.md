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
        // define thread run Runnable and this thread name
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

