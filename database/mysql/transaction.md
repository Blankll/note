# Transaction

事务：一个最小的不可再分的工作单元

事务的四大特性

- Atomicity 原子性   事务是最小单位，不可再分
- Consistency 一致性   事务要求所有的DML语句操作的时候，必须保证同时成功或者同时失败 从一种一致性状态转移到另一种一致性状态,如转账过期中总额始终一致
- Isolation 隔离性   一个事务对数据库中数据的修改,在未提交前对其他事务不可见
- Durability 永久性  事务一旦提交,修改的数据就会永久保存到数据库中

事务会产生的问题

- dirty read 脏读
- non-repeatable read 不可重复读
- phantom read 幻读

SQL标准事务隔离级别

- read uncommitted 读未提交： 一个事务还没提交时，它做的变更就能被别的事务看到。
- read committed 读提交：一个事务提交之后，它做的变更才会被其他事务看到。
- repeatable read 可重复读：一个事务执行过程中看到的数据，总是跟这个事务在启动时看到的数据是一致的。在可重复读隔离级别下，未提交变更对其他事务也是不可见的。
- serializable 串行化 ：对于同一行记录，“写”会加“写锁”，“读”会加“读锁”。

Oracle 数据库默认的事务隔离级别是**读提交[read committed]**

MySQL 数据库默认的事务隔离级别是**可重复读[Repeatable Read]**

```bash
show variables like 'transaction_isolation';# 查看数据库事务级别
set sesstion_tx isolation='read-commited';  # 设置事务隔离级别
```

MySQL 5.5 及以前的版本，回滚日志是跟数据字典一起放在 ibdata 文件里的



### 大事务

定义: 运行时间比较长,操作的数据比较多

风险: 

- 锁定的数据多,造成大量的阻塞和锁超时
- 回滚锁需要的时间长,可能比执行事务花费的时间还要长
- 执行时间长,容易造成主从延迟

策略

- 避免一次处理太多数据
- 移除不必要在事务中的select操作,保证事务中只有必要的写操作

