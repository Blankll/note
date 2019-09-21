# redis

Redis是用C语言开发的一个开源，高性能的键值对的数据库，通过提供多种键值数据类型，来适应不同场景下的存储需求！

1. 纯内存
2. 非阻塞IO
3. 避免线程切换和竞态消耗
4. 一次只运行一条命do令
5. 拒绝长慢命令 keys , flushall，  flushdb，  slow，  lua，  script，  mutil/exec，  opreate，  big value(collection)，

**Redis应用场景：** 

1. 缓存 
2. 任务队列 聊天室，秒杀，任务队列（list结构，pop(弹出),push（插入））消息队列
3. 应用排行榜 ，计数器转发，like，播放次数等
4. 实时系统
5. 网站访问统计 
6. 数据过期处理 
7. 分布式集群架构中的Session 分离

## NoSQL--not only sql

- High performance
- Huge Storage
- High Scalability && High Availability

### 分类

1. 键值存储
2. 列存储
3. 文档数据库[mongodb]
4. 图形数据库

## redis安装配置

sudo apt-get install redis-server

预装软件： gcc tcl[一门语言，redis的特定组件使用它来编写]

启用daemon 将配置文件 /etc/redis/redis.conf中的daemonize no 改为daemonize yes 启用后端加载

## phpredis 

https://segmentfault.com/a/1190000003084917

## swoole重新编译加载异步redis

1. 进入之前解压好的源代码文件
2. ./configure --with-php-config=php的config文件　--enable-redis
3. make clean 清除上次编译产生的object文件
4. make -j
5. make install
6. php --ri swoole



启动redis ``redis-server``

```bash
/etc/init.d/redis-server stop
/etc/init.d/redis-server start
/etc/init.d/redis-server restart
```





单实例

连接池

## redis特性

- 数度快 
  - 10w OPSC语言实现5w行，
  -  数据存储在内存中
  - 单线程


- 持久化 断电不丢失数据
  - redis将所有数据保存在内存中，对数据的更新将异步的保存到磁盘上
  - rdb， aof
- 多种数据结构
  - ``string``字符串类型
  - ``hash``哈希类型
  - ``list``列表类型
  - ``set``集合类型
  - ``zset``有序集合类型
  - BitMap
  - HyperLogLog 超小内存唯一值计数
  - GEO 地理信息定位
  - stream(redis5)
- 支持多种语言
- 功能丰富
- 简单
- 主从复 制
- 高可用，分布式

## redis源码

``redis-check-aof``  AOF文件修复工具 

``redis-check-dump``  RDB文件检索工具

``redis-sentinel``  Sentinel服务器（2.8以后）

## redis的启动

1. 最简启动

2. 动态参数启动

3. 配置文件启动

   生产环境建议选择配置启动

   单机多实例配置文件可以用端口进行区分

```shell
redis-cli -h 10.10.79.150 -p 6384
```

## redis 客户端返回值

1. 状态回复
2. 错误回复
3. 整数回复
4. 字符串回复
5. 多行字符串回复 多行操作时

## redis基本配置

1. daemonize 是否时守护进程(yes|no) 默认为no
2. port redis对外端口， 默认6379, 单机多实例时通过不同的端口区分实例
3. logfile redis系统日志 定义文件名
4. dir redis工作目录 文件路径

## redis通用命令

1. ``O(n)``keys *  计算所有的键
2. ``O(1)``dbsize 计算key的总数
3. ``O(1)``exists key 查看key是否存在(0|1)
4. ``O(1)``del key 删除key(0|1)
5. ``O(1)``expire key seconds 设置过期时间秒级
6. ``O(1)``ttl key 查看key剩余的过期时间
  
   - 返回-1时表示key存在，并且没有过期时间
   - 返回-2表示key已经不存在了
7. ``O(1)``persist key 去掉key的过期时间
8. ``O(1)``type key 查看key的数据类型 返回key的类型
   - string 
   
     ``简单的键值对``
   
   - hash
   
     Redis hash 是一个string类型的field和value的映射表，hash特别适合用于存储对象。``键值对，值又是一个简单的键值对`
   
   - list
   
     Redis列表是简单的字符串列表，按照插入顺序排序。你可以添加一个元素到列表的头部（左边）或者尾部（右边）``如同队列``有序可重复
   
   - set
   
     Set 是 String 类型的无序集合。集合成员是唯一,集合中不能出现重复的数据。
   
   - zset
   
     有序集合，根据score排序，member不可重复，score可重复
   
     ```bash
     ZADD key score1 member1 [score2 member2]
     ```
   
   - none



## 单线程





## redis数据结构

### 字符串

所有的key都是string

``get key``

``set key value``  不管key是否存在，都设置 O(1)

``setnx key value``  key不 存在，才设置   O(1)

``set key value xx``  key存在，才设置     O(1)

``incr key`` key自增1, 如果key不存在， 自增后get(key) = 1  O(1)

``decr key``  key 自减少1,如果key不存在， 自减后get(key) = -1  O(1)

``incrby key k``  key自增k，如果key不存在，自增后get(key) = k  O(1)

``decrby key k``  key自减k，如果key不存在，自减后get(key) = -k  O(1)



``mget key1 value1 key2 value2 ...`` 批量获取key，原子操作   O(n)

``mset key1 value1 key2 value2 ....``  批量设置key-value    O(n)



``getset key newvalue``  set key new value and return the old value   O(1)

``  append key value``  将value追加到旧的value后面     O(1)

``strlen  key``   返回字符串长度， 注意中文中文一个字就占用2个字节      O(1)

``incrbyfloat key vlaue``  增加key对应值value  O(1)

``getrange key start end``   获取字符串指定下标所有的值    O(1)

``setrange key index value``  设置指定下标所索引应的值   O(1)



### hash

``hget key field``  获取hash key对应的field的value      O(1)

``hset key field value``  设置hash key对应field的value   O(1)

``hsetnx key field value``  key 对应的field不 存在，才设置field和value   O(1)

``hdel key field``  删除hash key对应field的value      O(1)

``hgetall key ``  获取key对应的所有field的value         O(n)

``hexists key field``  检测hash key是否有field   O(1)

``hlen key``  获取hash key field 的数量    O(1)



``hmget key field1, field2 .....``  批量获取hash key的一批field对应的值    O(n)

``hmset key field1 value1 field2 value2  ...``  批量设置 hash key的一批field value     O(n)

``hgetall key``  返回hash key对应的所有的field和value   单线程数度较慢 谨慎使用   O(n)

``hvals key``  返回hash key对应所有field的value     O(n)

``hkeys key``  返回hash key对应所有的field      O(n)

``hincrby key field value``  key field 对应的值自增value       O(1)

``hincrbyfloat key field value``  hincrby 的float版本       O(1)



缺点 只能对一个key设置过期时间，无法对key下的field设置过期时间



## list

有序， 可重复 左右两边进行插入和弹出

索引下标从左往右时从0开始， 从右往左时从-1开始



``rpush key value1 value2 ......``  从列表右端插入值    O(1～n)

``lpush key value1 value2 value3 ....``  从列表左端插入值 O(1～n)

``linsert key before|after value new Value``  在list指定的值前|后 插入newValue  O(n)

``lpop key``  从列表左侧弹出一个item    O(1)

``rpop key`` 从列表右侧弹出一个item     O(1)

``lrem key count value``  根据count值，从列表中删除所有value相等的项     O(n)

> count > 0 从左到右，删除最多count个value相等的项
>
> count < 0 从右到左，删除最多Math.abs(count)个value相等的项
>
> count = 0 删除所有value相等的项 

``ltrim key start end``  按照索引范围修剪列表  保留索引为start到end的值，索引下标从0开始 [范围外的删除]

``lrange key start end``  获取列表指定索引范围所有item     O(n)

> lrange lista -3 -1
>
> 搜索时索引要从左索引开始。右索引结束，lrange lista -1 -3 这样时错误的

``lindex key index``  获取列表指定索引的item   O(n)

``llen key``  获取列表的长度   O(1)

``lset key index newValue``  设置列表指定嗯索引值为newValue



1. **LPUSH +  LPOP = Stack**
2. **LPUSH +RPOP = Queue**
3. **LPUSH + LTRIM = Capped Collection**
4. **LPUSH + BRPOP = Message Queue**



## Set

无序，无重复， 可以进行集合间操作

###set内api

``sadd key element``  向集合key中添加lelement(可以多个) 如果element存在，添加失败    O(1~n)

``srem key element``  将集合key中的element(可以多个)删除  O(1~n)

``scard key``  计算集合中元素个数

``sismember key element`` 检测element是否在集合中

> 1 存在
>
> 0 不存在

``srandmember key coount``  从集合中随机抽出count个元素

``spop key `` 从集合中随机弹出一个元素[delete] 返回弹出元素的 element[也就是值]

``smembers key`` 弹出集合中的所有元素==大叔据可能阻塞，小心使用，scanf==



### set间api

``sdiff key1 key2`` 获取key1和key2间的差集

``sinter key1 key2``  获取key1与key2间的交集

``sunion key1 key2``  获取key1与key2间的并集

``sdiff|sinter|sunion + store destkey key1 key2``  将集合运算后的结果保存在destkey中，再次查询时可以直接查询destkey 

> sunionstore unionab seta setb



TIPS

SADD = Tagging

SPOP/SRANDMEMBER = Random item

SADD + SINTER = SocialGraph





## zset

有序集合 key index value 无重复元素



``zadd key score element``  添加score 和element相互对应的元素    O(logN)

> score element可以是多对
>
> element不可重复， score可以重复

``zrem key element ``   删除元素    O(1)

> 可以是多个element

``zincrby key incre element ``   增加元素的score值 incre     O(1)

``zcard key``   返回元素的总个数     O(1)

``zrank key element``  以升序的方式排列score值并返回element的名次，从1开始  O(n)

``zrange key start  end``   获取列表指定索引范围所有element 按score升序排列     O(log(N)+m)

> lrange lista -3 -1
>
> 搜索时索引要从左索引开始。右索引结束，lrange lista -1 -3 这样时错误的
>
> zrange key start  end withscores  同时显示score

``zcount key minScore maxScore``  返回有序集合内在指定分数范围内的个数     O(log(N)+m)

``zremrangebyrank key start end``  神奈川指定排名内的升序元素     O(log(N)+m)

``zremrangebyscore key minScore maxScore``  删除指定分数内的升序元素       O(log(N)+m)

``zrevrank``

``zrevrange``

``zrevrangebyscore``



``zinterstore``

``zunionstore``



```bash
info replication # 查看分片信息
```



## 慢查询

- redis查询声明周期

  1. 发送命令
  2. 排队
  3. 执行命令
  4. 返回结果

  慢查询发生在执行命令阶段（命令的执行周期很长）

  客户端超发生不一定是因为慢查询导致

- 两个关于慢查询的配置

  - slowlog-max-len 慢查询队列长度(默认128)
  - slowlog-log-slower-than 慢查询阈值(单位：微秒， 默认10000)
  - 支持动态配置



## pipeline

将命令进行批量打包发送到服务器端 ，在结果依次返回

```java
Jedis jedis = new Jedis("127.0.0.1", 6379);
// 独立执行，>= 50s
for(int i = 0; i < 10000; i++) {
    jedis.hset("hashkey:" + i, "filed" + i, "value" + i);
}
// pipeline ~= 0.7s
for(int i = 0; i < 100; i++) {
	Pipeline pipeline = jedis.pipelined();
    for(int j = i * 100; j < (i+1) * 100; j++) {
        pipeline.hset("hashkey:" + j, "field" + j, "value" + j);
    }
}
```

pipeline是一个非原子操作，返回结果顺序返回

注意每次pipeline携带的数据量

pipeline只能作用在一个Redis节点上



## 发布订阅

- 发布者publisher
- 订阅者 subscriber
- 频道channel



发布者和订阅者都是客户端

发布者发布消息之后，每一个订阅者都会收到消息

每一个订阅者可以订阅多个频道

订阅者只能收到订阅成功发布者发布之后的消息，无法收到之前的消息

### API

- ``publish channel message`` 发布命令 返回订阅者个数
- ``subscribe [channel]`` 订阅一个或多个频道
- ``unsubscribe [channel]`` 取消订阅 一个或多个
- ``psubscribe [pattern] ``订阅模式，满足正则匹配的就订阅
- ``punsubscribe [patten]`` 退订指定的模式
- ``pubsub channels`` 列出至少有一个订阅者的频道
- ``pubsub numsub [channel]`` 列出给定频道的订阅者数量

## 消息队列

消息发布者发布消息，消息订阅者争夺消息，消息发布者和订阅者都是cli

拿list来阻塞实现的

## Bitmap

操作bit

### API

- ``setbit key offset value`` 给位图指定索引设置值(0 1) 索引从高位开始
- ``getbit key offset`` 获取位图指定索引的值
- ``bitcount key [start end]`` 获取位图指定范围位值为1的数量
- ``bitop op destkey key [key]`` 做多个bitmap的``and交集`` ``or并集``  ``not非`` ``xor异或``操作并将结果保存在``destkey``中
- ``bitpos key targetBit [start] [end]`` 获取``targetBit`` 在位图指定范围内第一次出现的offset的值



可以每一个bit保存一位用户是否在线的状态，再用户在线统计中可以大大节省内存空间

## HyperLogLog

基于HyperLogLog算法，用极小的空间完成独立数量统计

### API

- ``pfadd key element [element]`` 添加元素
- ``pfcount key [key]`` 计算HyperLogLog的独立总数
- ``pfmerge destkey sourcekey [sourcekey]`` 合并多个HyperLogLog

错误概率0.81%



## GEO since3.2+

计算地理位置相关信息，基于zset实现

### API

- ``geo key longitude latitude member [longitude latitude member] `` 添加地理位置信息

- ``geopos key member [member ...]`` 获取地理位置信息

- ``geodist key member1 member2 [unit] `` 获取地理位置的距离

  > unit m 米， km 千米 mi 英里 ft 尺

- ``georadius`` 算出指定范围内的地理信息（很复杂，自己Google）

- ``zrem key member`` 删除

### Stream

- xadd key ID field string 创建一个stream
- ``xlen`` 返回记录数量
- ``xdel`` 删除一个id
- ``xrange key start end`` start起始id end 结束id
- xread [COUNT count] [BLOCK milliseconds] STREAMS key [key] [id]
- xgroup create key group_name id
- xreadgroup group group_name consumer STREAMS key id[>]

```bash
xadd one * name string
xlen key
xdel key id
```



# redis持久化

## RDB

快照，通过命令将redis内存中的数据完整的备份到硬盘的二进制文件中

恢复时（如重启） 将二进制文件加载到redis内存中

同时二进制文件也是一个redis数据复制的媒介 



触发机制

- save（同步）

- bgsave（异步）子进程执行

- 自动（频率太高会影响性能）

  ```bash
  save 900 1
  save 300 10
  save 60 10000
  dbfilename dump.rdb
  dir ./  # 日志文件等存储路径
  stop-writes-on-bgsave-error yes # 写入发生错误时停止写入
  rdbcompression yes # 是否采用压缩格式
  rdbchecksum yes # 是否进行校验和检验
  ```

- 全量复制

- debug reload 

- shutdown



  最佳实践

- 关闭自动的save

- 集群中可以通过ip或者端口等对rdb文件进行区分

  ```bash
  dbfilename dump-${port}.rdb
  dir /bigdiskpath # 指定特定的保存地址
  stop-writes-on-bgsave-error yes # 建议开启 默认开启
  rdbcompression yes # 建议开启 默认开启
  rdbchecksum yes # 建议开启 默认开启
  ```

缺点：

- 耗时耗性能
- 不可控，容易丢失数据



## AOF

写日志

日志记录redis命令，宕机时通过读取aof文件载入到内存中恢复数据

aof先写入到磁盘缓冲区中，然后再刷新到硬盘中

AOF三种策略

- always  每一条命令都刷新到硬盘中
- everysec 每秒刷新一次数据到硬盘 中
- no 根据操作系统的缓冲区情况来确定，缓冲区满时自动刷新到硬盘中

aof重写作用

- 减少硬盘占用量
- 加速恢复速度

命令

``bgrewriteaof`` fork出子进程异步``aof``重写  将redis内存中的数据对aof文件进行回溯

自动重写配置策略

```bash
# 配置策略
auto-aof-rewrite-min-size # 重写需要的最小尺寸
auto-aof-rewrite-percentage # aof增长率
# 统计策略
aof_current_size # aof当前尺寸
aof_base_size # aof上次启动和重写的尺寸
```

配置

```bash
appendonly yes
appendfilename "appendonly-${port}.aof"
appendfsync everysec
dir /bigdiskpath
no-appendfsync-on-rewrite yes
```

RDB 与 AOF

| 命令       | RDB    | AOF          |
| ---------- | ------ | ------------ |
| 启动优先级 | 低     | 高           |
| 体积       | 小     | 大           |
| 恢复速度   | 快     | 慢           |
| 数据安全性 | 丢数据 | 根据策略决定 |
| 轻重       | 重     | 轻           |

最佳策略

小分片



## redis复制原理与优化

主从复制：备份，读写分离 

**生产环境中不要在一台主机上配置多个redis节点**

一主一从

一主多从

数据流向是单向的，只能从master流向slave

设置

redis主从

在1127.0.0.1::6380上执行命令 ``slaveof 127.0.0.1:6379`` 将6380设置为6379的slave节点

在1127.0.0.1::6380上执行命令 ``slaveof no one``取消主从关系

修改redis配置

```bash
slave of ip port # 配置为目标节点的slave节点
slave-read-only yes # 从节点只做数据读取
```



## Redis Sentinel

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
dir /opt/oft/redis/data/ # sentinel工作目录
logfile "26379.log" # sentinel的日志文件
sentinel monitor mymaster 127.0.0.1 7000 2 # 2表示有多少个sentinel发现master有问题时切换master
sentinel down-after-milliseconds mymaster 30000 # 测试ping master的时间间隔
sentinel parallel-syncs mymaster 1 # 每次复制一个
sentinelfailover-timeout mymaster 180000

```

启动sentinel

```bash
redis-sentinal redis-sentinel-26379.conf

```

生成与slave个数相同的监控slave的sentinel

slave 1 sentinel

```bash
port 26380 # sentinel 的端口
daemonize yes
dir /opt/oft/redis/data/ # sentinel工作目录
logfile "26380.log" # sentinel的日志文件
sentinel monitor mymaster 127.0.0.1 7000 2 # 2表示有多少个sentinel发现master有问题时切换master
sentinel down-after-milliseconds mymaster 30000 # 测试ping master的时间间隔
sentinel parallel-syncs mymaster 1 # 每次复制一个
sentinelfailover-timeout mymaster 180000

```

slave2 sentinel

```bash
port 26381 # sentinel 的端口
daemonize yes
dir /opt/oft/redis/data/ # sentinel工作目录
logfile "26381.log" # sentinel的日志文件
sentinel monitor mymaster 127.0.0.1 7000 2 # 2表示有多少个sentinel发现master有问题时切换master
sentinel down-after-milliseconds mymaster 30000 # 测试ping master的时间间隔
sentinel parallel-syncs mymaster 1 # 每次复制一个
sentinelfailover-timeout mymaster 180000

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



## Redis Cluster

redis单机性能可以达到10万/每秒

### 呼唤集群

1. 单机并发量无法满足业务需求
2. 单机内存无法满足业务需求
3. 单机网络带宽无法满足业务需求

### 数据分布

将数据分布到不同节点上,解决单机无法满足内存,并发,带宽等问题

- 顺序分布
- 哈希分布
  - 节点取余
  - 一致性哈希
  - 虚拟槽分区

| 分布方式 | 特点                                                    | 典型产品                                       |
| -------- | ------------------------------------------------------- | ---------------------------------------------- |
| 哈希分布 | 数据分散度高,键值分布业务无关,无法顺序访问,支持批量操作 | 一致性哈希 Memcache, rediscluster,其他缓存产品 |
| 顺序分布 | 数据分散一倾斜,键值业务相关,可顺序访问,不支持批量操作   | BigTable,HBase                                 |

**节点取余**

- 客户端分片:哈希+取余

- 节点伸缩:数据节点关系变化,导致数据迁移

- 迁移数量和添加节点数有关,翻倍扩容可以降低数据迁移的量级

**一致性哈希**

- 客户端分片: 哈希+顺时针(优化取余)
- 节点伸缩:只影响临近节点,单还是有数据迁移
- 翻倍伸缩:保证最小迁移数据和负载均衡

**虚拟槽分区(redis cluster默认方式)**

- 预设虚拟槽:每个槽映射一个数据子集,一般比节点数大
- 良好的哈希函数
- 服务端管理节点,槽和数据:Redis Cluster

### 集群搭建

原生命令安装

1. 配置开启节点

   ```bash
   cluster-enabled yes 
   cluster-config-file nodes-${pott}.conf
   cluster-node-timeout 15000 # 默认就好
   cluster-require-full-coverage yes # 有一个节点宕机,整个集群就不向外提供服务, 最好关闭
   ```

   开启配置号的多个节点

2. meet

   ```bash
   cluster meet ip port
   redis-cli -h 127.0.0.1 -p 7000 cluster meet 127.0.0.1 7001
   redis-cli -h 127.0.0.1 -p 7000 cluster meet 127.0.0.1 7001
   redis-cli -h 127.0.0.1 -p 7000 cluster meet 127.0.0.1 7002
   redis-cli -h 127.0.0.1 -p 7000 cluster meet 127.0.0.1 7003
   redis-cli -h 127.0.0.1 -p 7000 cluster meet 127.0.0.1 7004
   redis-cli -h 127.0.0.1 -p 7000 cluster meet 127.0.0.1 7005
   ```

   

3. 指派槽16384个槽 0~16383

   ```bash
   # 在目标节点上执行命令 根据节点数将16384做一个平均
   # 如下,有6个节点,三个分配slot,其余三个作为备份节点
   redsi-cli -h 127.0.0.1 -p 7000 cluster addslots {0...5461}
   redsi-cli -h 127.0.0.1 -p 7001 cluster addslots {5462...10922}
   redsi-cli -h 127.0.0.1 -p 7002 cluster addslots {10923...16383}
   ```

4. 设置主从

   ```bash
   # redis-cli -p 7000 cluster nodes 查看节点信息
   # redis-cli -p 7000 cluster slots 查看节点主从信息
   # cluster replicate node-id
   redis-cli -h 127.0.0.1 -p 7003 cluster replicate ${node-id-7000} # 将7003作为7000的slave节点
   redis-cli -h 127.0.0.1 -p 7004 cluster replicate ${node-id-7001} 
   redis-cli -h 127.0.0.1 -p 7005 cluster replicate ${node-id-7002} 
   ```

   官方安装工具基于ruby,简化了部署步骤

   cacheclud 可视化集群部署

### 集群伸缩

**集群扩容**

- 准备新节点

- 加入集群 meet

- 迁移槽和数据 

  - 槽迁移计划
  - 迁移数据
  - 添加从节点

  1. 在目标节点执行命令,让目标节点准备导入槽的数据

     ```bash
     cluster setslot {slot} importing {sourceNodeId}
     ```

  2. 在源节点执行命令,让源节点准备迁出槽的数据

     ```bash
     cluster setslot {slot} migrating {targetNodeId}
     ```

  3. 源节点循环执行,每次获取count个属于槽的键

     ```bash
     cluster getkeysinslot {slot} {count}
     ```

  4. 在员节点上执行命令将指定key迁移

     ```bash
     migrate {targetIp} {targetPort} key 0 {timeout}
     ```

  5. 重复步骤34直到槽下所有的键数据迁移到目标节点

  6. 向集群内所有主节点发送命令,通知槽分配给目标节点

     ```bash
     cluster setslot {slot} node {targetNodeId}
     ```

  或者使用官方工具

  ```
  ./redis-trib.rb reshard 127.0.0.1:7000
  ```

  

### 客户端路由

- moved 重定向
- ask重定向
- smart客户端 ``追求性能``
  1. 从集群中选一个可运行节点,使用cluster slots 初始化槽点和节点映射
  2. 将cluster slot的结果集映射到本地,为每个节点创建JedisPool
  3. 准备执行命令

**smart客户端使用**单例



### 集群原理

### 开发运维常见问题

#### 故障恢复

- 资格检查
- 准备选举时间
- 选举投票
- 替换主节点 
  1. 当前从节点取消复制变为主节点(slaveof no one)
  2. 执行clusterDelSlot 撤销故障主节点负责的槽,并执行clusterAddSlot把这些槽分配给自己
  3. 向集群广播自己的pong消息,表明已经替换了故障主节点

#### 带宽消耗

- 官方建议不要超过1000个节点
- ping/pong消息也占带宽
- 消息发送频率:节点发现他与其他节点最后通信时间超过cluster-node-timeout/2时会直接发送ping消息
- 消息数据量:slots槽数组(2kb空间)和整个集群1/10的状态数据(10个节点状态数据约为1kb)
- 节点部署的机器规模:集群分布的机器越多且每台机器划分的节点数越均匀,则集群整体的可用带宽越高

优化

- 避免"大"集群: 避免多个业务使用同一个集群,大业务可以划分出多个集群
- cluster-node-timeout: 带宽和故障转移速度的均衡,不能只考虑一个因素而调整这个参数
- 尽量均匀分配到多机器上

#### pub/sub广播在集群中存在的问题

- 问题: publish会在集群每个节点广播,加重带宽
- 解决: 单独"走"一套redis sentinel,与其他业务集群相分离

#### 集群倾斜

- 数据倾斜: 内存不均

  - 节点和槽的分配不均匀
  - 不同槽对应的键值数差异较大
  - 包含bigkey
  - 内存相关配置不一致

  定期检查配置的一致性

- 请求倾斜

## 缓存的使用与优化

### 缓存的受益与成本

受益

1. 加速读写
2. 降低后端负载:后端服务器如MySQL通过前端缓存降低负载

成本

1. 数据不一致:缓存层和数据层有时间窗口不一致
2. 代码维护成本
3. 运维成本

使用场景

1. 降低后端负载
2. 加速请求响应
3. 大量写合并为批量写:先写到缓存中,在同步到MySQL中

### 缓存更新策略

1. LRU/LFU/FIFO算法删除:如maxmemory-policy
2. 超时剔除: 如expire
3. 主动更新:开发控制生命周期
4. 数据一致性和维护成本的协调

### 缓存粒度控制策略

### 缓存穿透优化

1. 缓存空对象,避免过多击穿缓存去查询数据层
2. 布隆过滤器拦截

### 无底洞问题优化

节点越多,io操作次数增多,更多的机器并不一定意味着更高的性能	

1. 命令本身优化
2. 减少网络通信次数
3. 降低接入成本

### 缓存雪崩优化

### 热点key重建优化

目的

- 减少缓存的次数
- 数据尽可能一致
- 减少潜在危险

解决方案

- 互斥锁(mutex key)
- 永远不过期



## 上线与踩坑

解决redis connection refused: connect遇到的坑

- redis.conf配置文件中 注释 bind 127.0.0.1

- ecs上开放访问的端口