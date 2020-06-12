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

### Innodb和MySAM数据存储区别

1. Innodb

   > - 每个表有两个文件, table_name.frm, table_name.ibd
   > - .frm存储表结构, .ibd存储表数据和索引

2. MySAM

   > - 每个表有三个文件, table_name.frm, table_name.MYI, table_name.MYD
   > - .frm存储表结构,  MYI存储索引, MYD存储表数据

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

## MySQL日志

- redolog
- undolog
- binlog
- error_log
- query_log
- slow_log

### MySQL文件

**MyISAM引擎的文件：**

*.MYD:存储表数据记录

*.MYI: 存储表索引信息

*.frm: 存储表结构信息（每一个表有一个同名的文件）

*.log 日志文件

**InnoDB引擎的文件：**

独立表空间: 每个表使用一个表空间文件

- table_name.ibd: 存储表数据和索引(B+Tree组织的数据)

- table_name.frm: 存储表结构信息（每一个表有一个同名的文件）

共享表空间: 

- ibdata1、ibdata2等：系统表空间文件，存储InnoDB系统信息和用户数据库表数据和索引，所有表共用。



MyISAM将表存储在.MYD(存数据信息)和.MYI(存索引信息)中

MySQL的所有存储引擎都会有一个.frm文件,每个表一个文件,记录对应的表结构

## MySQL慢日志

```bash
# 慢日志是否开启
slow_query_log  # default off
# 慢日志文件存储位置
slow_query_log_file
# 慢日志时间阀值
long_query_time
# 修改配置参数
set global slow_query_log = on
```

分析慢查询

1. 查看sql语句出现慢查询原因

   ```sql
   explain sql_context
   ```

   type字段:MySQL找到数据的方式

   >system>const>eq_ref>fulltext>ref_or_null>index_merge>unique_subquery>index_subquery>range>index>all

   extra字段:

   - using filesort: 表示MySQL会对结果使用一个外部索引排序,而不是从表里按索引次序读到相关内容,可能在内存或者磁盘上进行排. MySQL中无法利用索引完成排序的操作称为"文件排序"
   - using temporary: 表示MySQL在对查询结果排序时使用临时表.常见于排序order by 和分组查询group by
