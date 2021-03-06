# INDEX索引

 索引是帮助数据库高效获取数据的数据结构

索引的目的在于提高查询效率

排好序的高效索引 条件约束用到索引 where，orderby

from表结构，框架

b树查找![qlinde](C:\Users\blank\Desktop\sqlindex.png)

## 索引的类型

- 二叉查找树

- b-Tree索引

  > - 根节点至少包括两个孩子
  > - 树中每个节点最多含有m个孩子(m>=2)
  > - 除根节点外,其他每个节点至少含有ceil(m/2)个孩子
  > - 所有叶子节点都位于同一层

- b+-Tree索引

  > - 所有叶子节点都位于同一层
  > - 非叶子节点的子树指针与关键字个数相同
  > - 非叶子节点的子树指针p[i],指向关键字值[k[i], k[i+1])的子树
  > - 非叶子节点仅用来索引,数据都保存在叶子节点中
  > - 所有叶子节点均有一个链指针指向下一个叶子节点

- hash索引

  > - MySQL的memory引擎使用了hash索引
  >
  > - innodb的“自适应哈希索引(adaptive hash index)”innodb发现某些索引使用非常频繁时，会在内存中基于B-tree索引再创建一个哈希索引，提高查询速度，这是一个完成自动的内部行为，用户无法干预
  >
  > - innodb不支持hash

b+Tree更适合用来做存储索引

- B+树的磁盘读写代价更低
- B+树的查询效率更加稳定
- B+树有利于进行范围查找(对数据库的扫描)

MySQL下索引分类:

- 主键索引

- 唯一索引

- 组合索引

- 外键索引

- 全文索引

一个表只能有一个主键索引，可以有多个唯一索引

主键索引一定是唯一索引，唯一索引不一定是主键索引

主键可以与外键构成参照完整性约束，防止数据不一致。

组合索引将多个列组合在一起创建索引，可以覆盖多个列

```sql
KEY(a, b, c);
-- 使用联合索引
SELECT * FROM table_name WHERE a = 1 AND b = 2 AND c = 3;
SELECT * FROM table_name WHERE a = 1 AND b = 2;
SELECT * FROM table_name WHERE a = 1;
-- 无法使用联合索引
SELECT * FROM table_name WHERE a = 1 AND c = 3;
SELECT * FROM table_name WHERE b = 2 AND c = 3;
SELECT * FROM table_name WHERE b = 2;
```

外键索引 保证数据的一致性，完整性和实现级联操作

全文索引是MySQL中MyISAM自带的，只能对英文进行全文检索。



复合索引遵循前缀原则

like查询，%在前面就无法使用索引

索引列可以为NULL值

在 MySQL 中，索引是在存储引擎层实现的，所以并没有统一的索引标准，即不同存储引擎的索引的工作方式并不一样。而即使多个存储引擎支持同一种类型的索引，其底层的实现也可能不同

每一个索引在 InnoDB 里面对应一棵 B+ 树。

<font color="red">主键索引的叶子节点存的是整行数据。在 InnoDB 里，主键索引也被称为聚簇索引（clustered index）。</font>

官方自带的逻辑备份工具是 mysqldump。当 mysqldump 使用参数–single-transaction 的时候，导数据之前就会启动一个事务，来确保拿到一致性视图。而由于 MVCC 的支持，这个过程中数据是可以正常更新的

## 密集索引和稀疏索引

InnoDB

- 若一个主键被定义,该主键作为密集索引
- 若没有主键被定义,该表的第一个唯一非空索引作为密集索引
- 若不满足以上条件,innodb内部会生成一个隐藏主键

MySAM中索引都是稀疏索引

