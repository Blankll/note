# ENGINE

## MYISAM <5.5

1. MyISAM 不支持外键和事务
2. 表🔒，不适合高并发
3. 性能高， 缓存只缓存索引
4. 拥有全文索引、压缩、空间函数
5. 不支持崩溃后的安全恢复
6. 数据存储在以myd和myi为后缀的文件中

MyISAM将表存储在.MYD(存数据信息)和.MYI(存索引信息)中

MySQL的所有存储引擎都会有一个.frm文件,每个表一个文件,记录对应的表结构



Percona xtraDB 在性能和并发性做的更好

## InnoDB

通过一些机制和工具支持真正的热备份

支持崩溃后的安全恢复

支持行级锁 

支持事务和外键

表中的数据存储在表空中

```bash
innodb_file_per_table=on
# on 独立表空间 tablename.ibd
# off 系统表空间 ibdataX
# 关闭命令
set global innodb_file_per_table=off;
```



# 索引优化

单值索引：只给一张表的某一个字段建一个索引

```sql
--idx_user_name 索引名字 建立索引根据user表的name字段
CREATE INDEX idx_user_name ON user(name);
```

多值索引

```sql
CREATE INDEX idx_user_name_email ON user(name, email);
```

表关联，jion查询太多会严重影响查询性能，要少用




## LOCK

共享锁和排它锁（读锁和写锁）

锁粒度 表锁行锁（粒度越细，锁开销越大）



## MySQL事务

事务由引擎层实现， 服务器层不管理事务