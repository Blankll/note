# Transaction

事务的四大特性

- Atomicity
- Consistency
- Isolation
- Durability

事务会产生的问题

- dirty read 脏读
- non-repeatable read 不可重复读
- phantom read 幻读

SQL标准事务隔离级别

- read uncommitted 读未提交： 一个事务还没提交时，它做的变更就能被别的事务看到。
- read committed 读提交：一个事务提交之后，它做的变更才会被其他事务看到。
- repeatable read 可重复读：一个事务执行过程中看到的数据，总是跟这个事务在启动时看到的数据是一致的。在可重复读隔离级别下，未提交变更对其他事务也是不可见的。
- serializable 串行化 ：对于同一行记录，“写”会加“写锁”，“读”会加“读锁”。

Oracle 数据库的默认隔离级别其实就是“读提交”

*Mysql默认*的事务隔离级别是可重复读(Repeatable Read)

```bash
show variables like 'transaction_isolation';
```

MySQL 5.5 及以前的版本，回滚日志是跟数据字典一起放在 ibdata 文件里的

