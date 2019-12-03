skiplist 用在zset中

redis是单进程单线程运行,但是在redis4.0之后在进程人多不和懒删除的时候,会再启动两个进程去处理操作,防止在进程过长的操作时请求饿死

zset中如果元素少于128个使用的是ziplist结构,如果多余128个,就会转换成skiplist,但一个sikplist存储的zset在元素少于128个时不会直接转存到ziplist而是在对这个zset和另一个zset求交集时检测元素,如果少于128个就会将他转存为ziplist

## ziplist

为了省内存 

使用hash,zset,list中会使用到ziplist

## redis启动流程

- 配置加载和初始化

  > redis服务器基本数据结构和各种参数的初始化

  - redisServer全局变量
  - populateCommandTable 初始化Redis命令列表 -> redisCommandTable
  - redis.conf中加载配置文件(可能会覆盖之前初始化的redisServer中的参数)

- 创建事件循环

  > aeEventLoop的struct来表示,创建一个aeEventLoop并存储到server全局变量中，事件循环依赖I/O多路复用机制

- 监听socket

  - 在同一个主机上使用Unix domain socket来监听
  - 在不同的主机上使用TCP来监听

- 注册timer事件回调
  周期性执行回调函数

  > key回收，主从重连，cluster节点间重连BGSAVE和AOF rewrite的触发执行

- 注册IO事件回调

  > 分析来自客户端的命令请求，指执行命令，返回响应结果

  - acceptTcpHandler
  - acceptUnixHandler

- 初始化后台线程

  > redis创建的额外的线程 bio(Background I/O service)，处理耗时的，可以延迟执行的任务

  - 可以延迟执行的文件关闭操作(unlink)
  - AOF持久化操作fsync调用

- 启动事件循环

  > 启动事件循环，驱动前面注册的timer，io事件不断执行

## 事件循环机制

timer事件和I/O事件是两种截然不同的事件，但需要进行统一调度
![image of redis life cycle](./redis_method_call_hierarchy.png)

