# Concurrency

高速缓存在线程并行的情况下，会出现缓存不一致

总线锁

缓存锁(粒度更小)

总线锁和缓存锁由操作系统实现，语言层面无感知.

java中所有的实例域、静态域、数组元素都存储到堆内存中，堆内存数据线程之间共享

局部变量、方法传递的参数、异常处理器参数线程独有

线程之间的通讯有JMM控制(抽象概念)

JVM在操作系统之上屏蔽操作系统特性和差异



synchronized保证原子性(排队执行<轮巡(自寻锁)>)

Volatile保证可见性(排它锁)



## three concept

1. atomic
2. visible
3. ordered

``re-sorted only required the final result coherence``

### JMM solution

1. atomic

2. visible

   use volatile

3. ordered

   **``happens before  relationship``**

   - no re-sort in thread code

   - unlock must happend after lock
   - volatile filed's write opreate priority must over read opreate when read and write happend in same time
   - opreate A before B, B before C => A must before C
   - thread's start method must invoked before run method
   - interrupt opreation must happend before catch
   - any object's initlization must happend before finalize method
   - all thread opreation must happend before thread dead


## wait set

1. all of object have a wait set to store the thread which invoked it's own object wait method and into block state. and free the lock it's get
2. when thread in wait set get notify, they may not exeute immediately
3. thread in wait set wakeuped by notify sequence is random
4. once wait set thread notified, it need to reapply lock, but this thread would start execute the place it waited before instead to start from the place it applied lock, because thread already had it's own execute context.

## volatile

problem: Catche coherence problem

ensure variable's visible

ensure variable's ordered(forbid re-sort)

solution:

1. lock data bus -- synchronized data read and write

   > bus type:  data bus,   address bus,  control bus.

2. Catche coherence protocols -- ensure multithread catche choherence **``java volatile``**

   > Intel - MESI

   - if cpu find variable is shared the time write data to it, cpu would emit a signal to notify other core variable changed and value in it's catche is invalid
   - other cores would access main memory to reread variable's new value when they opreate variable

