# java线程池

java.uitl.concurrent.ThreadPoolExecutor类是线程池中最核心的一个类

```java
public class ThreadPoolExecutor extends AbstractExecutorService {
    //.....
    public ThreadPoolExecutor(int corePoolSize,int maximumPoolSize,long keepAliveTime,TimeUnit unit,
            BlockingQueue<Runnable> workQueue);
 
    public ThreadPoolExecutor(int corePoolSize,int maximumPoolSize,long keepAliveTime,TimeUnit unit,
            BlockingQueue<Runnable> workQueue,ThreadFactory threadFactory);
 
    public ThreadPoolExecutor(int corePoolSize,int maximumPoolSize,long keepAliveTime,TimeUnit unit,
            BlockingQueue<Runnable> workQueue,RejectedExecutionHandler handler);
 
    public ThreadPoolExecutor(int corePoolSize,int maximumPoolSize,long keepAliveTime,TimeUnit unit,
        BlockingQueue<Runnable> workQueue,ThreadFactory threadFactory,RejectedExecutionHandler handler);
    //...
}
```

其中参数意义如下：

- corePoolSize： 线程核心池大小

- maximumPoolSize:  线程池最大线程数大小

- keepAliveTime: 线程池中非核心线程空闲的存活时间大小

- unit 线程空闲存活时间单位,有7种取值

  >TimeUnit.DAYS;                           //天
  >TimeUnit.HOURS;                       //小时
  >TimeUnit.MINUTES;                    //分钟
  >TimeUnit.SECONDS;                   //秒
  >TimeUnit.MILLISECONDS;         //毫秒
  >TimeUnit.MICROSECONDS;       //微妙
  >TimeUnit.NANOSECONDS;        //纳秒

- workQueue: 存放任务的阻塞队列

- threadFactory: 用于设置创建线程的工厂，可以给创建的线程设置有意义的名字，可方便排查问题。

- handler: 线城池的饱和策略事件，主要为四种策略

  > 1. AbortPolicy: 抛出一个异常，默认策略
  > 2. DiscardPolicy：直接丢弃任务
  > 3. DiscardOldestPolicy： 丢弃队列中最老的(即队列最前面)任务，尝试执行当前任务(重复此过程)
  > 4. CallerRunsPolicy： 交给线程池调用所在的线程进行处理

在创建了线程池之后，默认情况下线程池中并没有任何线程，在任务到来时才创建线程去执行任务，或者创建后调用``prestartAllCoreThreads()``[创建所有核心池线程]或者``prestartCoreThread()``[创建一个核心池线程]方法创建线程



![ThreadPoolExecutor uml](../statics/java/ThreadPoolExecutor-uml.png)