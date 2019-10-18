# MySQL

##一，mysql基础；

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
常看MySQL版本： select version();

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
SET PASSWORD FOR 'username'@'host' = PASSWORD('newpassword');
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



##三，数据表和数据类型；

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
###2. 数据表：

create table 数据表名称（

	列定义
​	列名称 类型 [默认值][auto_increment(自增长)] [主索引 primary key]
​	列名称 类型 [默认值]
​	列名称 类型 [默认值]
​	列名称 类型 [默认值]
​	索引定义；

）

```  mysql
      create table stu(
     	id int(6) UNSIGNED auto_increment primary key,
     	--primary key 主键：确定记录唯一性的字段
     	stuNumber varchar(6),
     	stuName varchar(20),
     	stuAge tinyint(6),
     	stuSex enum("1","2"),
     	stuTel varchar(20)
      );

      create table sign(
      s_id int not null auto_increment primary key,
      s_username varchar(50) not null default '',
      s_password char(32) not null default ''
    );
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

## notice

```sql
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

一个varchar存汉字需要使用三个字段在utf8和utf8mb4编码表的情况下。
2. 如果需要存储emoji表情的需求，新表的默认编码方式应该写为utf8mb4。另外提一点在最新发布的mysql8.0里面，默认编码方式已经是utf8mb4了。

3. 在utf8和utf8mb4中 varchar(n)这个n是字符，所见即所得，一个a是一个字符一个😄也是一个字符 不过就是a这个字符是1个字节 哈这个字符是3个字节 而😄这个字符是4个字节表示罢了

4. 字符类型若为utf8，每个字符最多占3个字节，最大长度不能超过21845。 
   　　对于英文比较多的论坛 ，使用GBK则每个字符占用2个字节，而使用UTF－8英文却只占一个字节。 
      　　若定义的时候超过上述限制，则varchar字段会被强行转为text类型，并产生warning。 

5.  Mysql 5中

   非空CHAR的最大总长度是255【字节】；非空VARCHAR的最大总长度是65533【字节】。

    可空CHAR的最大总长度是254【字节】；可空VARCHAR的最大总长度是65532【字节】。

### 4. 创建表

 学生信息表 stu
  id 排列序号
  学号
  姓名
  年龄
  性别
  手机

```mysql
create table stu(
	id int(6) auto_increment primary key,
	<--primary key 主键：确定记录唯一性的字段-->
	stuNumber varchar(6),
	stuName varchar(20),
	stuAge tinyint(6),
	stuSex enum("1","2"),
	stuTel varchar(20)
 )
```



查看数据库中的表:

```mysql
show tables;
```


查看表结构：

```mysql
desc 表名称；
```



###4. 表操作

1. 

2. 查看

   ```mysql
   select * from 表名称
   ```

3. 修改

   ```mysql
   update 表名称 set 字段=值,字段=值..... where id=num;
   update stu set stuName="zhangssan",stuAge =20 where id=3;
   ```

4. 删除

   ```mysql
   delete from 表名称 where id=3;
   注意：删除后主键id没有自动更新；
   ```

5. 查询

   ```mysql
   select 字段列表 from 表名称 [where条件][order by 字段 asc|desc][limit 起始位置 长度][group by 字段名称（分组）] 
   ```

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

## PHP对数据库的操作[原生连接]

  MySQL函数库--PHP的函数，PHP中用来操作MySQL数据库中的函数
  ###常用函数：

1. mysql_connect("主机名称/IP","用户名","密码"); 

   >    -->建立PHP与数据库的连接；返回资源
   >
   >   @-->错误抑制符
   >   die-->输出（）中的内容，终止程序；


2. mysql_error();返回上一个MySQL操作的文本错误信息；

3. mysql_select_db("数据库名称",$link);选择数据库；

4. mysql_query();向数据库发送一条SQL命令；执行SQL语句；

5. mysql_affected_rows();取得前一条sql返回受影响的行数；insert update delete；

6. mysql_close(); 关闭数据库连接；

7. mysql_fetch_array()从结果集中取得一行作为关联数组，或者数字数组，或者二者兼有；

    mysql_fetch_array(结果集，参数2)：从结果集中返回一条记录；
    MYSQL_ASSOC :关联数组
    MYSQL_NUM :索引数组
    MYSQL_BOTH :混合数组

    ```php
    // mysql_fetch_assoc()
        mysql_fetch_assoc($result) == mysql_fetch_array($result,MYSQL_ASSOC);
    // mysql_fetch_row()
        mysql_fetch_row($result) == mysql_fetch_array($result,MYSQL_NUM);
    ```

8. mysql_num_rows():获取select语句执行后的结果集中记录的条数；

SQL语句：sql语句在PHP中是以字符串的形式存在的；

example:

```php
//连接数据库
$link = @mysql_connect("localhost","root","root") or die("连接错误".mysql_error());
echo $link."<hr />";
//选择数据库
mysql_select_db("test",$link);
//设置编码格式
mysql_query("set names utf8");
// 插入数据
$sql = "INSERT INTO student(s_name,s_password,s_score,s_sex,s_age)
        VALUES('李四','002','77','2','19')";
mysql_query($sql);

//修改数据库表中的信息
$sql = "UPDATE student SET s_name='lisi' WHERE s_id=2";
mysql_query($sql);

//删除数据库中的信息
$sql = "DELETE FROM student WHERE s_id=2";
mysql_query($sql);

//查询数据库中的信息
$sql = "SELECT *FROM student";

//执行查询语句mysql_query()返回资源；
$result = mysql_query(sql);

//查询返回的结果集中记录的条数
count = mysql_num_rows($result);
echo "student表中的信息条数：{$count}<hr />";

//截取一条返回的信息
rs = mysql_fetch_array(result,MYSQL_ASSOC);
print_r($rs);

while($rs = mysql_fetch_array(result,MYSQL_ASSOC))
{
  print_r($rs);
  echo "<br />";
}

echo "<hr />";

//查看受影响的数据条数
echo mysql_affected_rows();

//关闭数据库连接；
mysql_close($link);
```

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



mysql_pconnect() 函数打开一个到 MySQL 服务器的持久连接。  

mysql_pconnect() 和 mysql_connect() 非常相似，虽然只多了一个P, 但有两个主要区别：  

当连接的时候本函数将先尝试寻找一个在同一个主机上用同样的用户名和密码已经打开的（持久）连接，如果找到，则返回此连接标识而不打开新连接。其次，当脚本执行完毕后到 SQL 服务器的连接不会被关闭，**此连接将保持打开以备以** **后使用（** **mysql_close() 不会关闭由 mysql_pconnect() 建立的连接）**  



**存储过程** 

为以后的使用而保存的一条或者多条MySQL语句集合

存储过程就是有业务逻辑和流程的集合

可以在存储过程中创建表，更新数据，删除等