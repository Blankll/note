死锁代码案例

```java
package com.blank.study.concurrency.threadstudy;

public class DeadLockStudy implements Runnable {
    int flag = 1;
    static Object lockOne = new Object();
    static Object lockTwo = new Object();

    public static void main(String[] args) {
       DeadLockStudy deadLockStudy1 = new DeadLockStudy();
       DeadLockStudy deadLockStudy2 = new DeadLockStudy();
       deadLockStudy1.flag = 1;
       deadLockStudy2.flag= 0;
       new Thread(deadLockStudy1).start();
       new Thread(deadLockStudy2).start();
    }
    @Override
    public void run() {
        System.out.println("flag = " + flag);
        if (flag == 1) {
            synchronized (lockOne) {
                try {
                    Thread.sleep(500);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
                synchronized (lockTwo) {
                    System.out.println("1");
                }
            }
        }
        if (flag == 0) {
            synchronized (lockTwo) {
                try {
                    Thread.sleep(500);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
                synchronized (lockOne) {
                    System.out.println("1");
                }
            }
        }
    }
}
```



## 死锁检查

jstack pid查看死锁信息

ThreadMxBean可以在代码中检测死锁