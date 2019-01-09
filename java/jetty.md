# Jetty基础



## new server()

1. 初始化线程池-> QueuedThreadPool->execute() -> BlockingQueue

   BlockingQueue存储需要执行的jobs

2. 初始化ServerConnector　NIO ByteChannel

   1. 初始化ScheduledExecuterScheduler
   2. 初始化ByteBufferPool(对象池) ArrayByteBufferPool
   3. 维护ConnectionFactory(创建连接对象的工厂，维护连接)
   4. 取得可用CPU数量
   5. 更新acceptor数量(根据CPU数量生成合适数量的Accept线程等待连接默认1-4个)
   6. 创建acceptor线程组
   7. 初始化ServerConnectorManager

3. 设置port

4. 关联Server和Connector

## server.start()

1. 设置启动状态

2. 启动过程doStart()

   1. 注册ShutdownMonitor 管理器，可以远程关闭Jetty服务器

   2. 获取线程池(new Server时第一步初始化的线程池)

   3. 设置selector数量 (对所有的Connector计算他的selector和acceptor数量)－>累计所有Connector的需求

   4. 计算所需的所有线程数量 = 1 + selectors + acceptors; ``大于200直接中断程序``

   5. 维护Bean 

      1.  启动QueuedThreadPool->doStart()->startThreads

         > start threads创建线程，从jobs中取任务并执行

      2. 启动WebAppContext

   6. 启动Connector

      1. 取得ConnetcionFactory
      2. 创建selector线程并启动
      3. 创建Acceptor线程
      4. 没有Acceptor的情况，使用非阻塞的方法，

3. 启动完毕

## Http request

1. Accept成功
   1. 设置为非阻塞模式
   2. 配置socket
   3. 正式处理-> 选择可用的ManageSelector线程　　
2. 处理请求

