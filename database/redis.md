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
  - 字符串类型
  - 哈希类型
  - 列表类型
  - 集合类型
  - 有序集合类型
  - BitMap
  - HyperLogLog 超小内存唯一值计数
  - GEO 地理信息定位
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

1. ``O(n)``keys  计算所有的键
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





## 上线与踩坑

解决redis connection refused: connect遇到的坑

- redis.conf配置文件中 注释 bind 127.0.0.1

- ecs上开放访问的端口