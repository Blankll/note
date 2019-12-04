## Redis Sentinel

添加setinel节点监控redis节点,setinel节点之间也会互相监控,通过监控判断节点是否可达,不可达时选举出新的setinel主节点完成自动故障转移



1. 多个sentinel发现并确认master有问题
2. 选举出一个sentinel作为领导
3. 选出一个slave作为master
4. 通知其余slave成为新的master的slave
5. 通知客户端主从变化
6. 等待老的master复活成为新master的slave

安装与配置

1. 配置主从节点
2. 配置开启sentinel监控主节点（sentinel是特殊的redis）
3. 实际应该为多台实例 

sentinel主要配置

```bash
port ${port} # sentinel 的端口
dir "/opt/oft/redis/data" # sentinel工作目录
logfile "${port}.log" # sentinel的日志文件
sentinel monitor mymaster 127.0.0.1 7000 2 # 2表示有多少个sentinel发现master有问题时切换master
sentinel down-after-milliseconds mymaster 30000 # 测试ping master的时间间隔
sentinel parallel-syncs mymaster 1 # 每次复制一个
sentinelfailover-timeout mymaster 180000
```

example

master

```bash
port 7000
daemonize yes
pidfile /var/run/redis-7000.pid
logfile "7000.log"
dir "/opt/soft/redis/redis/data/"

```

slave 1

```bash
port 7001
daemonize yes
pidfile /var/run/redis-7001.pid
logfile "7001.log"
dir "/opt/soft/redis/redis/data/"
slaveof 127.0.0.1 7000

```

slave 2

```bash
port 7002
daemonize yes
pidfile /var/run/redis-7002.pid
logfile "7002.log"
dir "/opt/soft/redis/redis/data/"
slaveof 127.0.0.1 7000

```

sentinel 监控master

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

启动sentinel

```bash
redis-sentinal redis-sentinel-26379.conf

```

生成与slave个数相同的监控slave的sentinel

cat redis-sentinel-26700.conf | grep -v "#" | grep -v "^$" >  sentinel.conf

slave 1 sentinel

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

slave2 sentinel

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

jedis连接

```java
JedisSentinelPool sentinelPool = new JedisSentinelPool(masterName, sentinelSet, poolConfig, timeout);

Jedis jedis = null;
try {
	jedis = redisSentinelPool.getResource();
    // jedis command
} catch(Exception e) {
} finally {
    jedis.close(); // 归还到连接池，并不一定是关闭连接
}

```

redis sentinel失败判定``三个定时任务``

1. 每10秒每个sentinel对master和slave执行info
   - 发现slave节点
   - 确认主从关系
2. 每2秒每个sentinel通过master节点的channel交换信息（pub/sub）
   - 通过``__sentinel__:hello``频道进行交互
   - 交互对节点的“看法”和自身信息
3. 每一秒每个sentinel对其他sentinel和redis执行ping

领导者选举

原因 只有一个sentinel节点完成故障转移

选举 通过sentinel is-master-down-by-addr 命令来希望成为领导者

1. 每个做主观下线的sentinel节点向其他sentinel节点发送命令，要求将他设置为领导者
2. 收到命令的sentinel节点如果没有同意通过其他sentinel节点发送的命令，那么将同意该请求，否则拒绝
3. 如果sentinel节点发现自己的票数已将超过sentinel集合半数且超过quorum，那么将成为领导者
4. 如果此过程有多个sentinel节点成为了领导者，那么将等待一段时间重新进行选举

故障转移（sentinel领导者选举完成）

1. 从slave节点中选举出一个合适的节点作为新的master节点
2. 对选出的节点执行slaveof no one 命令使其成为master
3. 向剩余的slave节点发送命令，让其他节点成为新master节点的slave节点，复制规则和parallel-syncs参数有关
4. 将原来的master节点配置为slave并保持关注，恢复时重新去复制新master节点数据

选择合适的slave节点

1. 选择slave-priority（slave节点优先级）最高的节点，如果存在则返回，如果不存在则继续
2. 选择复制偏移量最大的slave节点（复制最完整），如果存在则返回，如果不存在则继续
3. 选择runid最小的slave节点