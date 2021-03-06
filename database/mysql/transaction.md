# Transaction

## MySQL日志

- **binlog(归档日志)**<font color="red">Server层日志</font>: MySQL服务层产生的日志，常用来进行数据恢复、数据库复制，常见的MySQL主从架构就是采用slave同步master的binlog实现数据复制
- **redo log(重做日志)**<font color="red">Innodb引擎日志</font>: 记录了数据操作在物理层面的修改，mysql中使用了大量缓存，修改操作时会直接修改内存，而不是立刻修改磁盘，事务进行中时会不断的产生redo log，在事务提交时进行一次flush操作，保存到磁盘中。当数据库或主机失效重启时，会根据redo log进行数据的恢复，如果redo log中有事务提交，则进行事务提交修改数据。
- Undo Log:  除了记录redo log外，当进行数据修改时还会记录undo log，undo log用于数据的撤回操作，它记录了修改的反向操作，比如，插入对应删除，修改对应修改为原来的数据，通过undo log可以实现事务回滚，并且可以根据undo log回溯到某个特定的版本的数据，实现MVCC

更新记录时，InnoDB 引擎会先把记录写到 redo log中，并更新内存，这个时候更新就算完成了。同时，InnoDB 引擎会在适当的时候，将该操作记录更新到磁盘磁盘中，该操作通常在系统占用较低时进行。

InnoDB 的 redo log 是固定大小的

crash-safe: InnoDB在发生异常重启时借助redo log保证之前提交的数据不会丢失的能力称为crash-safe

事务：一个最小的不可再分的工作单元，MySQL 中，事务支持是在引擎层实现的

MySQL 是一个支持多引擎的系统，但并不是所有的引擎都支持事务。比如 MySQL 原生的 MyISAM 引擎不支持事务。

事务的四大特性

- Atomicity (原子性): 事务是最小单位，不可再分
- Consistency (一致性):   事务要求所有的DML语句操作的时候，必须保证同时成功或者同时失败 从一种一致性状态转移到另一种一致性状态,如转账过期中总额始终一致
- Isolation (隔离性):   一个事务对数据库中数据的修改,在未提交前对其他事务不可见
- Durability (永久性):  事务一旦提交,修改的数据就会永久保存到数据库中

事务会产生的问题

- dirty read (脏读): 事务一个正在对一条记录进行修改，在完成并提交前事务二也来读取该条记录，事务二读取了事务一修改但未提交的数据，如果事务一回滚，那么事务二读取到的数据就成了“脏”数据。
- non-repeatable read (不可重复读): 一个事务在读取某些数据后的某个时间再次读取之前读取过的数据，发现读出的数据已经发生了改变或者删除，这种现象称为“不可重复读”
- phantom read (幻读): 一个事务按相同的查询条件重新读取以前检索过的数据，发现其他事务插入了满足查询条件的新数据，这种现象称为“幻读”

SQL标准事务隔离级别<font color="red">`` 隔离性``</font>

- read uncommitted 读未提交： 一个事务还没提交时，它做的变更就能被别的事务看到。
- read committed 读提交：一个事务提交之后，它做的变更才会被其他事务看到。
- repeatable read 可重复读：一个事务执行过程中看到的数据，总是跟这个事务在启动时看到的数据是一致的。在可重复读隔离级别下，未提交变更对其他事务也是不可见的。
- serializable 串行化 ：对于同一行记录，“写”会加“写锁”，“读”会加“读锁”。

Oracle 数据库默认的事务隔离级别是**读提交[read committed]**

SQL Server数据库默认的事务隔离级别是**读提交[read committed]**

MySQL 数据库默认的事务隔离级别是**可重复读[Repeatable Read]**

```bash
show variables like 'transaction_isolation';# 查看数据库事务级别
set sesstion_tx isolation='read-commited';  # 设置事务隔离级别
```

MySQL 5.5 及以前的版本，回滚日志是跟数据字典一起放在 ibdata 文件里的

## 事务隔离

- 读未提交        <font color="red">`` 脏读``</font>
- 读提交   <font color="red">`` 不可重复读``</font>、     <font color="red">`` 幻读``</font> 
- 可重复读   <font color="red">`` 间隙锁``</font> 、       <font color="red">`` 默认``</font> 、  <font color="red">`` 死锁``</font> 、    <font color="red">`` 多版本``</font> 
- 串行化

### 大事务

定义: 运行时间比较长,操作的数据比较多

风险: 

- 锁定的数据多,造成大量的阻塞和锁超时
- 回滚锁需要的时间长,可能比执行事务花费的时间还要长
- 执行时间长,容易造成主从延迟

策略

- 避免一次处理太多数据
- 移除不必要在事务中的select操作,保证事务中只有必要的写操作



## MVCC

MVCC(**Multi Version Concurrency Control**): 多版本并发控制，**与MVCC相对的，是基于锁的并发控制，Lock-Based Concurrency Control)。**

**MVCC最大的优势：读不加锁，读写不冲突。在读多写少的OLTP应用中，读写不冲突是非常重要的，极大的增加了系统的并发性能**

- innodb实现了基于多版本的并发控制协议MVCC
- MVCC最大的好处是读不加锁，读写不冲突
- 现阶段几乎所有的RDBMS都支持MVCC
- 在MVCC并发控制中，读操作可以分为两类：快照读(snapshot read)、当前读(current read)
- <font color="red">MVCC只在READ COMMITED和REPEATABLE READ两个隔离级别下工作</font>



DB_ROW_ID: 隐含id,6byte，由innodb自动产生。

> 如果未声明主键，InnoDB 会自动生成一个隐藏主键，因此会出现这个列。另外，每条记录的头信息（record header）里都有一个专门的 `bit`（`deleted_flag`）来表示当前记录是否已经被删除

DB_TRX_ID: 事务id，6byte，每处理一个事务，值自动加一。

> InnoDB中每个事务有一个唯一的事务ID叫做 transaction id。在事务开始时向InnoDB事务系统申请得到，是按申请顺序严格递增的
>
> 每行数据是有多个版本的，每次事务更新数据时都会生成一个新的数据版本，并且把transaction id赋值给这个数据行的DB_TRX_ID

DB_ROLL_PT: 回滚指针，7byte，指向当前记录的ROLLBACK SEGMENT 的undolog记录，通过这个指针获得之前版本的数据。该行记录上所有旧版本在 `undolog` 中都通过链表的形式组织

MVCC流程：

1. 假设操作为insert，可以认为DB_ROW_ID为1，其他两个字段为空



一个数据版本对于一个事务视图来说，除了自己的更新总是可见以外，有三种情况：

1. 版本未提交，不可见；
2. 版本已提交，但是是在视图创建后提交的，不可见；
3. 版本已提交，而且是在视图创建前提交的，可见。

更新数据都是先读后写的，而这个读，只能读当前的值，称为“当前读”（current read）。

事务的可重复读能力是通过一致性读（consistent read）来实现，而事务更新数据的时候，只能用当前读，如果当前记录的行锁被其他事务占用，会进入锁等待。