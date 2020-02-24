## MySQL Theory

1 大表(具体要看机器性能,数据访问频率)

- 数据量达到千万行级别
- 数据量超过了10G

2 大表带来的问题

- 查询慢
- 建立索引需要很长时间
- MySIAM会锁表
- InnoDB会引起主从延迟
- DDL操作需要进行表锁
- 阻塞正常数据库操作

3 大表解决方案

- 分库分表

  - 分表主键的选择

  - 分表后跨分区数据的查询和统计

- 历史数据归档
  - 归档时间点的选择
  - 归档策略



## MySQL性能

对性能有影响的因素

- 服务器硬件
- 服务器OS
- 数据库存储引擎的选择
- 数据库参数配置(超级重要)
- 数据库表结构设计,查询语句



MySQL还不支持多cpu对同一sql的处理

QPS每秒钟处理sql的数量



MySQL在系统上的优化

相关参数``/etc/sysctl.conf``

```bash
net.core.somaxcon=65535
net.core.netdev_max_backlog=65535
net.ipv4.tcp_max_syn_backlog=65535
net.ipv4.tcp_fin_timeout=10
net.ipv4.tcp_tw_reuse=1
net.ipv4.tcp_tw_recycle=1

free -m # 查看系统内存,swap交换
```



## 基准测试

在开发前对数据库服务器进行测试.评估服务器处理能力

TPS 单位时间内所处理的事务数

QPS 单位时间内所处理的查询数

响应时间 平均响应时间, 最小响应时间.最大响应时间,各时间响应时间所占时间比

并发量: 同时处理的查询请求数量 

## MySQL分库分表

- 把一个实例中不同的多个数据库拆分到不同的实例 --- 代码业务要改变
- 把一个数据库中的表分离到不同的数据库中
- 对一个库中的相关表进行水平拆分到不同实例的数据库中

### 数据库分片

- 分区键要能尽量避免跨分片查询的发生
- 分区键要尽可能使各个分片中的数据平均
- 并不是所有的表都需要分片
  - 每个分片中存储一份相同的数据 -- 方便但是存在数据冗余,注意一致性
  - 使用额外的节点统一存储无需分片的表 -- 代码上要该,但是没有数据冗余的问题
- 分片策略
  - 每个分片使用单一数据库,并且数据库名也相同
  - 将多个分片表存储在一个数据库中,并在表名上加入分片后缀
  - 在一个节点中部署多个数据库,每个数据库包含一个分片
- 分片数据分配策略
  - 按分区键的hash值取模来分配分片数据
  - 按分区键的范围来分配分片数据
  - 利用分区键和分片的映射表来分配分片数据
- 全局id生成策略
  - 使用auto_increment_increment和auto_increment_offset参数
  - 全局id表
  - 在redis等缓存服务器中创建全局ID

oneProxyp



## MySQL监控系统

- 对数据库服务可用性监控

  > mysqladmin -umonitor_user -p -h ping
  >
  > 使用程序通过网络建立数据库连接
  >
  > 检测数据库的read_only参数是否为off
  >
  > 建立监控表对表进行curd操作

- 对数据库性能进行监控

  > show variables like 'max_connections';
  >
  > show global status like 'Threads_connected'
  >
  > QPS =  (Queries2 - Queries1)/(uptime_since_flush_status2-uptime_since_flush_status1)
  >
  > TPS = ((Com_insert2+Com_update2+Com_delete2) - (Com_insert1+Com_update1+Com_delete1)) /
  >
  > (uptime_since_flush_status2-uptime_since_flush_status1)

- 对主从复制进行监控

- 对服务器资源监控(如磁盘空间)

- 数据库系统的性能会随着并发处理请求数量的增加而下降