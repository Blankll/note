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



### MySQL事务

```bash  
show variables like '%iso%' # 查看数据库事务级别
set sesstion_tx isolation='read-commited'; # 设置事务隔离级别
```

- atomicity 要么全部完成,要么全部失败
- consistency  从一种一致性状态转移到另一种一致性状态,如转账过期中总额始终一致
- isolation 一个事务对数据库中数据的修改,在未提交前对其他事务不可见
- durability 事务一旦提交,修改的数据就会永久保存到数据库中

MySQL4种事务类型

- read-uncommitted 未提交读 修改未提交的数据可以被其他数据读取到(会产生脏读)
- rea- commited 已提交读(oracle, sqlserver默认) 一个事务从开始到commit前的数据修改对其他事务是不可见的(但是同一个事务中多次读取同一个记录结果可能不一致,也就是不可重复读)
- repeatable-read 可重复读 在同一个事务中多次读取同一个记录的结果是一致的(innodb默认)
-  serializable 可串行化

大事务

定义: 运行时间比较长,操作的数据比较多

风险: 

- 锁定的数据多,造成大量的阻塞和锁超时

- 回滚锁需要的时间长,可能比执行事务花费的时间还要长

- 执行时间长,容易造成主从延迟

策略

- 避免一次处理太多数据
- 移除不必要在事务中的select操作,保证事务中只有必要的写操作



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

