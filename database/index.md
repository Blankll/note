# INDEX索引

 索引是帮助数据库高效获取数据的数据结构

索引的目的在于提高查询效率

排好序的高效索引 条件约束用到索引 where，orderby

from表结构，框架

b树查找![qlinde](C:\Users\blank\Desktop\sqlindex.png)



## 索引的类型

主键索引

唯一索引

组合索引

外键索引

全文索引

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



