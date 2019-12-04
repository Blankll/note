# 构建Redis 集群

在redis中，主要有三种方式构建高性能的分布式redis服务，master-slave读写分离的模式，Redis Setinel模式以及Redis3.2之后的Redis Cluster，他们之间各有优劣，在实际业务中需要根据具体的需求进行选择。下文将简述三种模式以及具体的搭建步骤。

## Redis 读写分离

​	这种模式与Mysql的主从复制读写分离类似，在redis中，数据以RDB和AOF的形式进行持久化存储，RDB是以二进制数据格式保存redis内存数据到磁盘进行持久化的默认存储形式，在Redis1.1版本之后添加了AOF(Append Only File)以日志的形式记录Redis的写操作，弥补RDB数据一致性缺陷。但在redis集群中，slave并不像MySQL一样基于日志进行master与slave之间的数据复制，而是slave直接复制master内存中的数据。

Redis 读写分离集群的主要优势在于可以进行对master节点的备份，在master节点发生宕机时将salve升级为主节点继续提供服务，同时可以通过将读操作分散到save节点上实现读写分离，减轻master的压力。

要构建读写分离的Redis数据库集群，我们需要先下载Redis的执行文件，可以直接在[Redis官网下载](https://redis.io/),也可以在Redis的GitHub仓库下载源代码，进行编译安装[Redis GitHub](https://github.com/antirez/redis)

```bash
# 通过git下载Redis源代码
git clone git@github.com:antirez/redis.git
# 下载所需要的依赖
sudo apt-get install gcc g++ make
sudo chmod -R +x redis
cd redis
make distclean
make
make test
# 安装到指定的目录
make PREFIX=target_dir install
```

安装完成后，会在安装目录中生成一个bin目录，存放了所有redis的可执行文件，将redis源码中的redis.conf拷贝到用户自定义的一个目录中，修改对应的配置，在本例中，我们将建立一个master，两个slave架构的主从复制集群。

集群信息如下：

| name   | ip        | port |
| ------ | --------- | ---- |
| master | 127.0.0.1 | 6379 |
| slave1 | 127.0.0.1 | 6380 |
| slave2 | 127.0.0.1 | 6381 |

### 配置文件

redis源码中提供了默认的配置文件，我们只需要将其拷贝到目标目录中，修改对应的项目即可

- master config文件

  ```bash
  # redis-6379.conf
  # 注释bind，否则只有本机可访问
  #bind 127.0.0.1
  # 修改为no且注释bind后所有ip都可访问
  protected-mode no 
  # 当前节点监听端口
  port 6379
  # 以服务进程启动，不卡死shell界面
  daemonize yes
  # pid文件路径
  pidfile /var/run/redis-6379.pid
  # log文件名
  logfile "7000.log"
  # rdb备份决策，rdb是较重的操作，可以选择关闭
  # save 900 1
  # save 300 10
  # save 60 10000
  # rdb文件路径
  dbfilename dump-6379.rdb
  # 日志文件，数据文件存放目录，可以选择磁盘相对较大的地方来保存
  dir /data/md0/redis/redis-replication/
  # 启用aof日志进行持久化
  appendonly yes
  # aof文件名称
  appendfilename "appendonly-6379.aof"
  # aof刷新策略
  appendfsync everysec
  ```

- slave1

  ```bash
  # redis-6380.conf
  # 注释bind，否则只有本机可访问
  #bind 127.0.0.1
  # 修改为no且注释bind后所有ip都可访问
  protected-mode no 
  # 当前节点监听端口
  port 6380
  # 以服务进程启动，不卡死shell界面
  daemonize yes
  # pid文件路径
  pidfile /var/run/redis-6379.pid
  # log文件名
  logfile "6380.log"
  # rdb备份决策，rdb是较重的操作，可以选择关闭
  # save 900 1
  # save 300 10
  # save 60 10000
  # rdb文件路径
  dbfilename dump-6380.rdb
  # 日志文件，数据文件存放目录，可以选择磁盘相对较大的地方来保存
  dir /data/md0/redis/redis-replication/
  # 启用aof日志进行持久化
  appendonly yes
  # aof文件名称
  appendfilename "appendonly-6380.aof"
  # aof刷新策略
  appendfsync everysec
  # master ip和端口，slave会同步该节点的数据
  slaveof 127.0.0.1 6379
  ```

- slave2

  ```bash
  # redis-6381.conf
  # 注释bind，否则只有本机可访问
  #bind 127.0.0.1
  # 修改为no且注释bind后所有ip都可访问
  protected-mode no 
  # 当前节点监听端口
  port 6381
  # 以服务进程启动，不卡死shell界面
  daemonize yes
  # pid文件路径
  pidfile /var/run/redis-6381.pid
  # log文件名
  logfile "6381.log"
  # rdb备份决策，rdb是较重的操作，可以选择关闭
  # save 900 1
  # save 300 10
  # save 60 10000
  # rdb文件路径
  dbfilename dump-6381.rdb
  # 日志文件，数据文件存放目录，可以选择磁盘相对较大的地方来保存
  dir /data/md0/redis/redis-replication/
  # 启用aof日志进行持久化
  appendonly yes
  # aof文件名称
  appendfilename "appendonly-6381.aof"
  # aof刷新策略
  appendfsync everysec
  # master ip和端口，slave会同步该节点的数据
  slaveof 127.0.0.1 6379
  ```

以上配置文件中，我们省略了rdb备份，因为在很多情况下，rdb的写入可能会过于平凡，且rdb在持久化的过程中通过fork来完成，属于较重的操作，生产环境中可以根据业务需要选择开启或关闭。

启动redis

```bash
/dir_redis/bin/redis-server /dir_config/6379.conf # 启动master
/dir_redis/bin/redis-server /dir_config/6379.conf # 启动slave1
/dir_redis/bin/redis-server /dir_config/6379.conf # 启动slave2
```

此时并可以通过像redis中插入数据，测试同步是否正常！



## Redis Setinel

Redis读写分离的集群在运维上存在着比较大的问题，当主节点宕机时，集群无法自动实现故障转移，必须手动进行如下的故障转移操作：

1. 取消slave的主从关系

   ```bash
   # 在所有slave上执行如下命令
   slaveof no one
   ```

2. 选取一个slave作为master

   ```bash
   # 在其他slave上执行slaveof命令
   slaveof ip port
   ```

在生产环境中这样的操作几乎是不可接受的，因此setinel模式便孕育而生，他的操作流程基本与以上的手动故障转移类似，只是进行了自动转移，无需人为操作。

Redis Setinel模式在主从复制的基础上添加对每一个节点进行监听的setinel节点监控redis节点,setinel节点之间也会互相监控,通过监控判断节点是否可达,不可达时选举出新的setinel主节点完成自动故障转移。

构建流程如下：

1. 建立三个redis节点并启动，1master + 2slave [参考主从复制节点建立方式即可]

2. 为每一个redis节点添加setinel节点

   复制redis源码文件下的sentinel.conf，修改下列配置项：

   master``redis-sentinel-26379.conf``

   ```bash
   port 26379 # sentinel 的端口
   daemonize yes
   pidfile /var/run/redis-sentinel-26379.pid
   logfile "26379.log"
   dir /opt/oft/redis/data/ # sentinel工作目录
   sentinel monitor mymaster 127.0.0.1 7000 2  # 2表示有多少个sentinel发现master有问题时切换master
   sentinel down-after-milliseconds mymaster 30000 # 测试ping master的时间间隔
   sentinel parallel-syncs mymaster 1 # 每次复制一个
   sentinel failover-timeout mymaster 180000
   sentinel deny-scripts-reconfig yes
   ```

   slave1``redis-sentinel-26380.conf``

   ```bash
   port 26380 # sentinel 的端口
   daemonize yes
   pidfile /var/run/redis-sentinel-26380.pid
   logfile "26700.log"
   dir /opt/oft/redis/data/ # sentinel工作目录
   sentinel monitor mymaster 127.0.0.1 7000 2  # 2表示有多少个sentinel发现master有问题时切换master
   sentinel down-after-milliseconds mymaster 30000 # 测试ping master的时间间隔
   sentinel parallel-syncs mymaster 1 # 每次复制一个
   sentinel failover-timeout mymaster 180000
   sentinel deny-scripts-reconfig yes
   ```

   slave2``redis-sentinel-26381.conf``

   ```bash
   port 26381 # sentinel 的端口
   daemonize yes
   pidfile /var/run/redis-sentinel-26381.pid
   logfile "26381.log"
   dir /opt/oft/redis/data/ # sentinel工作目录
   sentinel monitor mymaster 127.0.0.1 7000 2  # 2表示有多少个sentinel发现master有问题时切换master
   sentinel down-after-milliseconds mymaster 30000 # 测试ping master的时间间隔
   sentinel parallel-syncs mymaster 1 # 每次复制一个
   sentinel failover-timeout mymaster 180000
   sentinel deny-scripts-reconfig yes
   ```

3. 启动setinel节点[确保redis主从节点已经正常运行]

   ```bash
   /dir_redis/bin/redis-setinel /dir_config/redis-sentinel-26379.conf # 启动master setinel
   /dir_redis/bin/redis-setinel /dir_config/redis-sentinel-26380.conf # 启动slave1 setinel
   /dir_redis/bin/redis-setinel /dir_config/redis-sentinel-26381.conf # 启动slave2 setinel
   ```

   