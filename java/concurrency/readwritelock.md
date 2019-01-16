# ReadWriteLock

when multithread read and write same shared resources, if there's a thread reading this resources, othere thread that want to read this resources can access right now, but the thread that want to write shared resources need to wait until read finish; and when a thread is writing this resouces both read and write need wait until this thread finished writing the shared resources.

example code

lock

```java
package study.seven.concurrency.readwritelock;

/**
 * @Auther: Blank
 * @Description: study.seven.concurrency.readwritelock
 * @Date: 1/15/19
 * @Version: 1.0
 */
public class ReadWriteLock {
    private int readingReaders = 0;
    private int waitingReaders = 0;
    private int writingWriters = 0;
    private int waitingWriters = 0;
    private boolean writerPriority;

    public ReadWriteLock() {
        this(true);
    }
    public ReadWriteLock(boolean writerPriority) {
        this.writerPriority = writerPriority;
    }

    public synchronized void readLock() throws InterruptedException{
        this.waitingReaders++;
        try {
            while(writingWriters > 0 || (writerPriority && waitingWriters > 0)) {
                this.wait();
            }
            this.readingReaders++;
        }finally {
            this.waitingReaders--;
        }
    }
    public synchronized void readUnlock() {
        this.readingReaders--;
        this.notifyAll();
    }

    public synchronized void writeLock() throws InterruptedException{
        this.waitingWriters++;
        try {
            while(readingReaders > 0 || writingWriters > 0) {
                this.wait();
            }
            this.writingWriters++;
        }finally {
            this.waitingWriters--;
        }
    }

    public synchronized void writeUnlock() {
        this.writingWriters--;
        this.notifyAll();
    }
}
```

shared Resources

```java
package study.seven.concurrency.readwritelock;

/**
 * @Auther: Blank
 * @Description: study.seven.concurrency.readwritelock
 * @Date: 1/15/19
 * @Version: 1.0
 */
public class SharedData {
    private final char[] buffer;
    private final ReadWriteLock lock = new ReadWriteLock();

    public SharedData(int size) {
        this.buffer = new char[size];
        for(int i = 0; i < size; i++) {
            buffer[i] = '*';
        }
    }

    public char[] read() throws InterruptedException {
        try {
            lock.readLock();

            return this.doRead();
        }finally {
            lock.readUnlock();
        }
    }

    public void write(char data) throws InterruptedException {
        try {
            lock.writeLock();
            this.doWrite(data);
        }finally {
            lock.writeUnlock();
        }
    }

    private void doWrite(char data) {
        for (int i = 0; i < buffer.length; i++) {
            buffer[i] = data;
        }
        try {
            Thread.sleep(2000);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }

    private char[] doRead() {
        char[] newBuffer = new char[buffer.length];

        for(int i = 0; i < buffer.length; i++) {
            newBuffer[i] = buffer[i];
        }
        try {
            Thread.sleep(2000);

        } catch (InterruptedException e) {
            e.printStackTrace();
        }finally {
            return newBuffer;
        }
    }

}
```

write worker

```java
package study.seven.concurrency.readwritelock;

import java.util.Random;

/**
 * @Auther: Blank
 * @Description: study.seven.concurrency.readwritelock
 * @Date: 1/15/19
 * @Version: 1.0
 */
public class WriteWorker extends Thread {

    private static final Random random = new Random(System.currentTimeMillis());

    private final SharedData sharedData;
    private final String filler;
    private  int index = 0;

    public WriteWorker(SharedData data, String filler) {
        this.sharedData = data;
        this.filler = filler;
    }

    @Override
    public void run() {
            try {
                while(true) {
                    char c = nextChar();
                    sharedData.write(c);
                    Thread.sleep(random.nextInt(1000));
                    System.out.println("thread [" + Thread.currentThread().getName() + "]" + " writes:" + c);
                }
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
    }

    private char nextChar() {
        char c = filler.charAt(index++);
        if(index > filler.length()) {
            index = 0;
        }

        return c;
    }
}
```

read worker

```java
package study.seven.concurrency.readwritelock;

/**
 * @Auther: Blank
 * @Description: study.seven.concurrency.readwritelock
 * @Date: 1/15/19
 * @Version: 1.0
 */
public class ReaderWorker extends Thread {
    private final SharedData sharedData;

    public ReaderWorker(SharedData data) {
        this.sharedData = data;
    }

    @Override
    public void run() {
        try {
            while(true) {
                char[] readBuffer = sharedData.read();
                System.out.println("thread [" + Thread.currentThread().getName() + "]" + " reads:"
                        + String.valueOf(readBuffer));
            }
        }catch (InterruptedException e) {
            e.printStackTrace();
        }
    }
}
```

client

```java
package study.seven.concurrency.readwritelock;

/**
 * @Auther: Blank
 * @Description: study.seven.concurrency.readwritelock
 * @Date: 1/15/19
 * @Version: 1.0
 */
public class ReadWriteLockClient {
    public static void main(String[] args) {
        final SharedData sharedData = new SharedData(100);

        new ReaderWorker(sharedData).start();
        new ReaderWorker(sharedData).start();
        new ReaderWorker(sharedData).start();
        new ReaderWorker(sharedData).start();
        new ReaderWorker(sharedData).start();

        new WriteWorker(sharedData, "newrightework").start();
        new WriteWorker(sharedData, "lswrightework").start();
        new WriteWorker(sharedData, "whwrightework").start();
        new WriteWorker(sharedData, "dswghtewosdfl").start();
    }
}
```

stringbuffer thread safety

StringBuilder thread unsafety