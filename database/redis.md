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



## 上线与踩坑

解决redis connection refused: connect遇到的坑

- redis.conf配置文件中 注释 bind 127.0.0.1

- ecs上开放访问的端口