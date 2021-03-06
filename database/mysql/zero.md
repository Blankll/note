# MySQL

DML（data manipulation language）： 
它们是SELECT、UPDATE、INSERT、DELETE，就象它的名字一样，这4条命令是用来对数据库里的数据进行操作的语言 
DDL（data definition language）： 
DDL比DML要多，主要的命令有CREATE、ALTER、DROP等，DDL主要是用在定义或改变表（TABLE）的结构，数据类型，表之间的链接和约束等初始化工作上，他们大多在建立表时使用 
DCL（Data Control Language）： 

## 一，mysql基础；

```bash
mysql_secure_installation
```

mysql 关闭密码长度规则校验

```bash
set global validate_password_policy=0;
set global validate_password_length=0;
```

mysql会在安装过程中自动生成一个初始化密码,默认在/var/log/mysqld.log中

```bash
grep "password" /var/log/mysqld.log
```

初始密码在第一次登录之后就会失效,所以登录后要重新设置密码

```mysql
-- 在登录MySQL之后执行
set password for 'root'@'localhost'=password('password'); 
-- 也可以用这个
ALTER USER 'root'@'localhost' IDENTIFIED BY 'new password';
```

## 登录

在mariadb10.0中,root的默认登录方式变为auth_socket, 登录命令为``mysql -S /var/run/mysqld/mysqld.sock``,可以免除密码输入

```sql
SELECT user, host, plugin, default_role FROM mysql.user;
```



表名：
字段：

2，数据库种类：关系型数据库

​			     菲关系型数据库

##二，MySQL常用命令；

1. 登录：mysql [-h 主机/ip] -u 用户名 -p (密码) 回车
2. 退出：exit；
3. mysql常用命令

```sql
查看当前时间： select now（）；
打印当前日期： select curtdate();
打印当前时间： select curttime();
查看当前用户： select user();
查看所有用户: select user,host from mysql.user;
常看MySQL版本： select version();
查看配置值: show variables like '%%';
查看系统状态: show status like '%%';
-- 修改配置参数
set global slow_query_log = on
```
创建用户

```sql
CREATE USER 'dog'@'localhost' IDENTIFIED BY '123456';
CREATE USER 'pig'@'%' IDENTIFIED BY '123456';
flush privileges;
```

授权

```sql
--授权格式--
GRANT privileges ON databasename.tablename TO 'username'@'host'
GRANT SELECT, INSERT ON test.user TO 'pig'@'%';
GRANT ALL ON *.* TO 'pig'@'%';
--使被授权的用户同样可以将拥有的权限授权给其他用户--
GRANT privileges ON databasename.tablename TO 'username'@'host' WITH GRANT OPTION;
flush privileges;
```

设置用户密码

```sql
SET PASSWORD FOR  'username'@'host' = PASSWORD('newpassword');
--设置当前登录用户的密码--
SET PASSWORD = PASSWORD("newpassword");
```

撤销用户权限

```sql
REVOKE privilege ON databasename.tablename FROM 'username'@'host';
```

删除用户

```sql
DROP USER 'username'@'host';
```

设置用户权限以后，最好再加上一条flush privileges,刷新缓存立马生效；

mariadb默认关闭远程连接，需要更改配置文件

```sql
--/etc/mysql/mariadb.conf.d/50-server.cnf--
bind-address = 0.0.0.0
```



## MySQL备份与还原

### mysqldump备份数据

```sql
-- 导出所有数据库
mysqldump -uroot -p --all-databases
-- 导出特定数据库
mysqldump -h132.72.192.432 -P3307 -uroot -p8888 htgl > bak.sql;
-- 备份数据库表
mysqldump -hhostname -uusername -ppassword databasename  specific_table1   specific_table2 > backupfile.sql
```

### 恢复导出的数据

```sql
-- 非登录状态下导入数据
mysql -h ip -u username -p password db1 <tb1tb2.sql
-- 登录到数据库中恢复数据
mysql> use translate
source ~/translate/sql.sql;
```
### mysql 修改存储目录 


## 三，数据表和数据类型；

###1. 实用命令：

1. show databases;

   information_schema 日志信息
   mysql：mysql系统库
   test：测试库

2. 创建数据库：create database 数据库名称;

```mysql
CREATE DATABASE demo;
CREATE DATABASE `csdn` DEFAULT CHARSET utf8mb4 COLLATE utf8mb4_general_ci;
```
3. 删除数据库：drop database 数据库名称;

```mysql
drop database demo;
```
4. 使用数据库：use 数据库名称；

```mysql
use demo;
```
###2. 数据表

查看数据库中的表:

```mysql
show tables;
```

查看表结构：

```mysql
desc 表名称；
```

表创建

```  mysql
-- ---------------------------------------------
-- 翻译表　与单词表一对多 上面要有一个空格
-- UNSIGNED要放到INT等类型的后面
-- PRIMARY KEY　要放到AUTO_INCREMENT后面，不放好像也不报错，但有些时候又出错
-- ---------------------------------------------
CREATE TABLE `translations` (
    `id` INT(11) UNSIGNED NOT NULL PRIMARY KEY AUTO_INCREMENT COMMENT '翻译id',
    `word_id` INT(11) UNSIGNED NOT NULL COMMENT '所属单词的id',
    `trans` VARCHAR(100) NOT NULL COMMENT '翻译',
    `property_id` TINYINT(4) UNSIGNED DEFAULT NULL COMMENT '词性',
    `create_time` TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP COMMENT '创建时间',
    `update_time` TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP COMMENT '更新时间',
    CONSTRAINT property_key FOREIGN KEY(`property_id`) REFERENCES properties(`id`),
    CONSTRAINT word_train_key FOREIGN KEY(`word_id`) REFERENCES words(`id`)
)ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;
```

表删除

```mysql
DROP TABLE  tbl_name;
DROP TABLE IF EXISTS tbl_name;
```

记录基本操作

```mysql
-- 表数据查看
select * from 表名称;
-- 数据修改
update 表名称 set 字段=值,字段=值..... where id=num;
update stu set stuName="zhangssan",stuAge =20 where id=3;
-- 数据删除
delete from 表名称 where id=3;
注意：删除后主键id没有自动更新；
-- 数据查询
select 字段列表 from 表名称 [where条件][order by 字段 asc|desc][limit 起始位置 长度][group by 字段名称（分组）] 

```

查询操作

```mysql
	1-select 字段列表 from 表名称；
	 select stuNum，stuName from student；
	 注意：可以给字段名称或者表名称起别名
	 select stuNum as stn，stuName as sn from student as sd；
	 查找所有字段
	 select * from student；
	2-order by 排序 asc 什序 desc 降序
	select * from student order by id desc；
	3-limit 起始位置，长度； 截取记录
	4-group by 分组：
	select * from books by bTypeid 按照类型id分组。
	分组以后，每组中的记录都会取一条。
	5-where条件
	比较符号： > < >= <=
	select * from books where id>100; 字段值进行比较；
	逻辑运算
	与 或  and or
	select * from books where id>100 and id<150;
	模糊搜索：字符串中含有某个关键字，就能找到
	like"%关键字%" %表示任意字符串；
				  _表示任意一个字符
	select * from books where bName like "%网站%";
	范围
		连续范围
		[not]between..and..;
		select * from books where id between 100 and 110;
								  id>=100 and id<=110;
		非连续范围
		[not]in(值..)   [not] in(值..)不是这些数的其他数
		select * from books where id in(100,103,110);
		                    where id=100 or id=103 or id=110;
		select * from books where id not in(100,103,110);
		                    where id!=100 or id!=103 or id!=110;
```



### 修改表名

```sql
ALTER  TABLE table_name RENAME TO new_table_name
```

### 字段操作

```sql
-- 增加一个默认字段
ALTER TABLE table_name ADD COLUMN name constrant;
-- 修改一个字段 修改时如果不带完整性约束条件，原有的约束条件将丢失
ALTER TABLE table_name MODIFY name constrant;
ALTER TABLE tb_name MODIFY 字段名称 字段类型 [完整性约束条件]
-- 修改字段名称
ALTER TABLE table_name CHANGE old_name new_name contrant;
-- ALTER TABLE 表名 CHANGE 原字段名 新字段名 字段类型 约束条件
ALTER TABLE table_name CHANGE old_name new_name CHAR(32) NOT NULL DEFAULT '123';
-- 删除一个字段
ALTER TABLE table_name DROP COLUMN name;
```

## 约束条件操作

```sql
-- 修改自增长的值
-- ALTER TABLE tb_name AUTO_INCREMENT=值
ALTER TABLE table_name AUTO_INCREMENT=100;
-- 修改表的存储引擎
-- ALTER TABLE tb_name ENGINE=存储引擎名称
ALTER TABLE table_name ENGINE=MyISAM;
ALTER TABLE table_name ENGINE=INNODB;

-- 添加唯一性约束
-- ALTER TABLE tb_name ADD [CONSTANT [symbol]] UNIQUE [INDEX | KEY] [索引名称](字段名称,...)
-- username添加唯一性约束，如果没有指定索引名称，系统会以字段名建立索引
ALTER TABLE user12 ADD UNIQUE(username);
-- car添加唯一性约束
ALTER TABLE user12 ADD CONSTRAINT symbol UNIQUE KEY uni_card(card);

-- test,test1添加联合unique
ALTER TABLE user12 ADD CONSTRAINT symbol UNIQUE INDEX mulUni_test_test1(test, test1);

-- 删除外键约束
ALTER TABLE shares DROP FOREIGN KEY `share_user_key`;
-- 添加外键约束
ALTER TABLE shares ADD CONSTRAINT `share_user_key` FOREIGN KEY(`user_id`) REFERENCES users(`id`);

-- 删除唯一
-- ALTER TABLE tb_name DROP {INDEX|KEY} index_name;
-- 删除刚刚添加的唯一索引
ALTER TABLE user12 DROP INDEX username;
ALTER TABLE user12 DROP KEY uni_card;
ALTER TABLE user12 DROP KEY mulUni_test_test1;

-- 修改表的存储引擎
-- ALTER TABLE tb_name ENGINE=存储引擎名称
ALTER TABLE user12 ENGINE=MyISAM;
ALTER TABLE user12 ENGINE=INNODB;
```

### 联合约束

```sql
-- 在建表时添加
UNIQUE KEY `resource_name` (`resource_name`,`resource_type`)
-- 在已存在的表上添加
ALTER TABLE jw_resource ADD UNIQUE KEY(resource_name, resource_type);
-- 唯一键约束添加后，在建表的元数据中，默认的唯一键约束名称为第一列的名称。
-- 查看表约束
show index from jw_resource;
-- 删除约束
ALTER TABLE jw_resource DROP INDEX `resource_name`;
-- 唯一键约束添加后，实际上建立了一个索引，将该索引删除后，就等于删除了联合唯一约束。
```



### 外键关联

外键约束对子表的含义: 　如果在父表中找不到候选键,则不允许在子表上进行insert/update 

外键约束对父表的含义: 　在父表上进行update/delete在子表中有一条或多条对应匹配行的候选键时,父表的行为取决于在定义子表的外键时指定的on update/on delete子句

InnoDB支持５种方式： CASCAD ，NO ACTION ，Restrict  ，SET NULL  

#### CASCADE

在父表上update/delete记录时，同步update/delete掉子表的匹配记录 

#### SET NULL

在父表上update/delete记录时，将子表上匹配记录的列设为null ,注意子表的外键列不能为not null

#### NO ACTION 

如果子表中有匹配的记录,则不允许对父表对应候选键进行update/delete操作 

#### RESTRICT

同　NO ACTION,当取值为No Action或者Restrict时在父表中删除对应记录，首先检测子表是否有对应的关联，如果有则阻止删除。

<font  color=red>代码在创建表上面有</font>

###3. 数据类型：

1. 整型

   `` tinyint ``1字节 有符号 (-128-127) 无符号（0~255）如表示年龄；

   ``smallint`` 2字节 有符号 (-32768-32767) 无符号(0~65535)；

   ``mediumint`` 

   ``int`` 4字节 有符号 (-2147483648-2147483647) 无符号 (0~4294967295)；
   ``BIGINT`` 8字节 特别大

   都可以和属性``UNSIGNED``使用，

   长度： 可以为整数类型指定宽度，如INT(11)， 对大多数应用是没有意义的，它不会限制值的合法范围，只会影响显示字符的个数。如INT(3)可以存储1234，如果存储12，且设置了zerofill 会显示012，补齐3位，默认并不开启。

2. bool

3. 浮点型：

   ``float``4字节 日常生活中的小数的存储；缺点：易丢失精度；
   ``double`` 8字节 宏观大数字；也有可能丢失精度；
   ``DECIMAL[m,d]`` 精度小数 m 总位数 d 小数点后边的位数，用于存储精确的小数；

4. 字符串：

   ``char（位数）`` 定长字符，补空格进行填充
   ``varchar（位数）`` 变长字符，用于存储可变长度字符串，比定长更节省空间，VARCHAR使用1个或2个额外字节记录字符串长度，列长度小于255byte时使用1byte记录，大于255byte时使用2byte额外字节记录。
   ``text ``65535个字符
   ``MEDIUMBLOB`` 2的 24次方字符
   ``enum（val1,val2,val3）`` 枚举只能选里面的值；

5. 日期时间

   ``date ``日期
   ``time ``时间
   ``datetime ``日期和时间

   ``timestamp``时间戳

尽量避免使用BLOB/TEXT类型，查询会使用临时表，导致严重的性能开销。

枚举尽量避免使用常量，以免稀混。

utf-8每个汉字占用3个字节

gbk每个汉字占用2个字节

**4.0版本以下**，varchar(100)，指的是**100字节**，如果存放UTF8汉字时，只能存33个（每个汉字3字节） 

**5.0版本以上**，varchar(100)，指的是**100字符**，无论存放的是数字、字母还是UTF8汉字（每个汉字3字节），都可以存放100个。

 MySql 5.5 之前，UTF8 编码只支持1-3个字节，只支持BMP这部分的unicode编码区，BMP基本就是 0000 ~ FFFF 这一区。

 从MySQL 5.5 开始，可支持4个字节UTF编码utf8mb4，一个字符最多能有4字节，所以能支持更多的字符集。

一个varchar存汉字需要使用三个字节在utf8和utf8mb4编码表的情况下。
2. 如果需要存储emoji表情的需求，新表的默认编码方式应该写为utf8mb4。另外提一点在最新发布的mysql8.0里面，默认编码方式已经是utf8mb4了。

3. 在utf8和utf8mb4中 varchar(n)这个n是字符，所见即所得，一个a是一个字符一个😄也是一个字符 不过就是a这个字符是1个字节 哈这个字符是3个字节 而😄这个字符是4个字节表示罢了

4. 字符类型若为utf8，每个字符最多占3个字节，最大长度不能超过21845。 
   　　对于英文比较多的论坛 ，使用GBK则每个字符占用2个字节，而使用UTF－8英文却只占一个字节。 
      　　若定义的时候超过上述限制，则varchar字段会被强行转为text类型，并产生warning。 

5.  Mysql 5中

   非空CHAR的最大总长度是255【字节】；非空VARCHAR的最大总长度是65533【字节】。

    可空CHAR的最大总长度是254【字节】；可空VARCHAR的最大总长度是65532【字节】。

## mysql大小写问题

MySQL在Linux下数据库名、表名、列名、别名大小写规则是这样的：

　　1、数据库名与表名是严格区分大小写的；

　　2、表的别名是严格区分大小写的；

　　3、列名与列的别名在所有的情况下均是忽略大小写的；

​      4、字段内容默认情况下是大小写不敏感的。

mysql中控制数据库名和表名的大小写敏感由参数lower_case_table_names控制，为0时表示区分大小写，为1时，表示将名字转化为小写后存储，不区分大小写。

查看当前是否区分大小写

```sql
show variables like '%case%';
```

查看MySQL数据文件存储位置

```sql
show global variables like "%datadir%";
-- 默认在/var/lib/mysql/ 
```

## MySQL删除与重装

删除已安装的MySQL

```bash
apt-get remove mysql-*
apt-get autoremove --purge mysql-server
# 再用dpkg --list|grep mysql查看，还剩什么就卸载什么
# 最后清楚残留数据：
dpkg -l |grep ^rc|awk '{print $2}' |sudo xargs dpkg -P
```

**存储过程** 

为以后的使用而保存的一条或者多条MySQL语句集合

存储过程就是有业务逻辑和流程的集合

可以在存储过程中创建表，更新数据，删除等