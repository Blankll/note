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
   #执行完毕后的节点都变成了独立的master节点
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


启动后可以操作master测试数据同步是否正常，可以使用kill -9 杀死Redis master 进程，查看日志文件，检查是否发生了自动故障转移。



## Redis Cluster

Redis读写分离服务和Redis Sentinel都只是复制节点数据和故障转移，面对高并发的业务场景，以上两种集群并不能很好的解决单机内存容量不足，,高并发写入与读取，,流量等瓶颈问题，分布式Redis服务的重要性并凸显出来了，Redis Cluster 将数据分布到不同节点上,解决单机无法满足内存,并发,带宽等问题：

1. 单机并发量无法满足业务需求
2. 单机内存无法满足业务需求
3. 单机网络带宽无法满足业务需求

本例中将构建共6个节点的redis cluster集群，3 master， 3 slave：

| node     | ip        | port | slot        |
| -------- | --------- | ---- | ----------- |
| master-1 | 127.0.0.1 | 7100 | 0~5461      |
| master-2 | 127.0.0.1 | 7101 | 5462~10922  |
| master-3 | 127.0.0.1 | 7102 | 10923~16383 |
| slave-1  | 127.0.0.1 | 7103 | 0           |
| slave-2  | 127.0.0.1 | 7104 | 0           |
| slave-3  | 127.0.0.1 | 7105 | 0           |

redis cluster的构建流程如下

1. 构建6个对应的配置文件

   只需将每个节点配置文件ip改为对应节点监听的端口号即可(以作区分，也可以用不同的目录来区别)

   ```bash
   # bind 127.0.0.1
   protected-mode no
   port 7100
   daemonize yes
   pidfile /var/run/redis-7100.pid
   logfile "log-7100.log"
   
   dbfilename dump-7100.rdb
   dir /data/md0/redis/redis-cluster
   replica-read-only yes
   
   appendonly yes
   appendfilename "appendonly-7100.aof"
   appendfsync everysec
   no-appendfsync-on-rewrite no
   
   cluster-enabled yes
   cluster-config-file node-7100.conf
   cluster-require-full-coverage no
   ```

2. 启动redis

   ```bash
   /dir_redis/bin/redis-server /dir_config/redis-7100.conf # 根据配置文件一一启动
   ```

3. 进行meet[每一个redis node之间都是互通的，需要在一个节点上meet集群张的其他所有节点]

   ```bash
   # /dir_redis/bin/redis-cli -p 7100 meet ip port
   /dir_redis/bin/redis-cli -p 7100 cluster meet 127.0.0.1 7101
   /dir_redis/bin/redis-cli -p 7100 cluster meet 127.0.0.1 7102
   /dir_redis/bin/redis-cli -p 7100 cluster meet 127.0.0.1 7103
   /dir_redis/bin/redis-cli -p 7100 cluster meet 127.0.0.1 7104
   /dir_redis/bin/redis-cli -p 7100 cluster meet 127.0.0.1 7105
   ```

   可以通过 cluster info查看集群节点是否meet, 如果正常可以看到``cluster_known_nodes:6``的信息

4. 分配slot(虚拟槽)

   redis通过虚拟槽进行节点数据的hash分配，redis总共分出了16384个槽。集群中的每个节点都保存了槽分配策略，在进行数据查询或操作时可以直接redirect到目标节点，无需像Sentinel那样返回到客户端重定向，做到了客户端无感知。

   ```bash
   # 在目标节点上执行命令 根据节点数将16384做一个平均
   # 如下,有6个节点,三个分配slot,其余三个作为备份节点
   # redsi-cli -h 127.0.0.1 -p 7100 cluster addslots {0...5461}
   # 需要一个一个添加，最好写一个shell脚本循环插入
   redsi-cli -h 127.0.0.1 -p 7100 cluster addslots 0
   redsi-cli -h 127.0.0.1 -p 7100 cluster addslots 1
   # redsi-cli -h 127.0.0.1 -p 7101 cluster addslots {5462...10922}
   # redsi-cli -h 127.0.0.1 -p 7102 cluster addslots {10923...16383}
   ```

   slot分配脚本example

   ```sh
   host=$1
   port=$2
   start=$3
   end=$4
   echo "host: ${host}; port: ${port}; start: ${start}; end: ${end};"
   for slot in `seq ${start} ${end}`
   do
       echo "slot ${slot}"
       /data/md0/redis/redis-5.0.7/bin/redis-cli -h ${host} -p ${port} cluster addslots ${slot}
   done
   ```

   ```bash
   sh ./redis-cluster/cluster-slots.sh 127.0.0.1 7100 0 5461 # 添加slot
   ```

   完成slots分配之后，cluster info查看集群信息，``cluster_state:ok``表明节点构建成功

5. 设置主从

   通过 nodes信息中的 node-id给redis master节点添加slave，同读写分离一样，只做备份

   ```bash
   # redis-cli -p 7000 cluster nodes 查看节点信息
   # redis-cli -p 7000 cluster slots 查看节点主从信息
   # cluster replicate node-id
   redis-cli -h 127.0.0.1 -p 7103 cluster replicate ${node-id-7000} # 将7003作为7000的slave节点
   redis-cli -h 127.0.0.1 -p 7104 cluster replicate ${node-id-7001} 
   redis-cli -h 127.0.0.1 -p 7105 cluster replicate ${node-id-7002} 
   ```

redis官方在5.0之前提供了构建集群的ruby语言编写的构建工具，可以简化以上流程，5.0则通过c原生实现了全新的redis cluster集群构建工具，极大的便利了Redis Cluster集群的构建

notice： 连接时需要加 -c 表示以集群的方式运行，否则只有hash到当前节点时数据才能存储成功

### redis5.0下的 Redis Cluster构建

首先，配置文件同上面的是完全一样的，不同的地方在于不需要再一个一个的 meet以及slot分配，直接使用cluster命令即可。

```bash
# 创建redis-cluster集群
redis-cli --cluster create ip:port [ip:port] --cluster-replicas 1
# 动态添加节点从节点
redis-cli --cluster add-node new_ip:new_port exsist_ip:exsist_port
# 给新添加的节点进行分片
redis-cli --cluster reshard exsist_ip:exsist_port
```

## Redis Cluster 集群伸缩

通过以上案例可以发现redis5自带的cluster构建方式相较于之前的方便太多，所以下面的集群扩缩容以Redis5的cluster命令来进行

### 集群扩容

1. 创建两个redis节点(配置文件参考上文案例)并启动节点，此时节点作为单独的redis节点，与集群还没有半毛钱关系

2. 将节点添加到已有集群中，每次添加新节点后面都要跟着一个该集群中已经存在的节点，嗯，师傅领进门的感觉。

   ```bash
   #  /dir_redis/bin/redis-cli --cluster add-node new_ip:new_port exist_ip:exist_port
    /dir_redis/bin/redis-cli --cluster add-node 127.0.0.1:7106 127.0.0.1:7103
   ```

3. 分配槽给新加入的节点,节点加入cluster之后会成为一个没有slot的master，需要手动给节点分配slot

   ```bash
   /dir_redis/bin/redis-cli --cluster reshard 127.0.0.1:7106
   ```

   执行过程中需要我们选择一下内容：

   1. How many slots do you want to move (from 1 to 16384)?

      > 输入要分配给新加入的节点多少个数据槽，可以16384 除以master数量平均分配一下

   2. What is the receiving node ID? 

      > 输入接受slot的redis节点的node-id，可以提前 cluster nodes一下，忘了就单独开个shell查询一下

   3. Source node #1: 

      > 这里有两个选项：
      >
      > all 从每个有slot的节点中redis自动选出一些slot分配个新加入的节点
      >
      > done 手动选择要加入的节点

      因为懒，所以我选择all，ps：小孩才做选择

   4. Do you want to proceed with the proposed reshard plan (yes/no)? 

      > 是否同意系统做出的节点的选择，yes就完事

   5. 不出意外，到这里，新节点就加入完成了

   6. 加入slave节点(和上面添加节点到集群中一样)

      ```bash
      #/dir_redis/bin/redis-cli --cluster add-node new_ip:new_port exist_ip:exist_port
      /dir_redis/bin/redis-cli --cluster add-node 127.0.0.1:7107 127.0.0.1:7107
      ```

   7. 设置主从关系

      ```bash
      # /dir_redis/bin/redis-cli -p slave_pprt cluster replicate master-node-id
      /dir_redis/bin/redis-cli -p 7107 cluster replicate efb66fbb022f9bbca3b980decbabf316fc2af5b0
      ```

      

### 集群缩容

这里要注意，缩容要保证缩容后内存足够存储集群中的数据

1. 删除从节点

   ```bash
   #/dir_redis/bin/redis-cli --cluster del-node ip:port node-id
   /dir_redis/bin/redis-cli --cluster del-node 127.0.0.1:7107 a2acfd4513e9588e6c0a0025b9511399024bd1af
   ```

2. 将即将删除的master的slot reshard给其他master

   ```bash
   /dir_redis/bin/redis-cli --cluster reshard 127.0.0.1:7106
   ```

   执行过程中需要我们选择一下内容：

   1. How many slots do you want to move (from 1 to 16384)?

      > 输入要移除多少个数据槽，将待删除节点的slot全部移除，输入slot数量

   2. What is the receiving node ID? 

      > 输入接受slot的redis节点的node-id，输入要给的未删除master节点的node-id

   3. Source node #1: 

      > 输入要删除的master的node-id
      >
      > 回车
      >
      > 输入 done

   4. Do you want to proceed with the proposed reshard plan (yes/no)? 

      > 是否同意系统做出的节点的选择，yes就完事

   5. 移除节点

      ```bash
      #/dir_redis/bin/redis-cli --cluster del-node ip:port node-id
      /dir_redis/bin/redis-cli --cluster del-node 127.0.0.1:7107 a2acfd4513e9588e6c0a0025b9511399024bd1af
      ```

      

   6. 不出意外，到这里,删除节点就完成了。

好的，到这里，redis构建集群的几种方式操作流程就介绍完了。