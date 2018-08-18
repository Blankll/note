# MySQL

##一，mysql基础；

表名：
字段：

2，数据库种类：关系型数据库

​                              菲关系型数据库

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
##三，数据表和数据类型；

###1. 实用命令：

1. show databases;

   information_schema 日志信息
   mysql：mysql系统库
   test：测试库

2. 创建数据库：create database 数据库名称;

```mysql
		create database demo;
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

​	列定义
​	列名称 类型 [默认值][auto_increment(自增长)] [主索引 primary key]
​	列名称 类型 [默认值]
​	列名称 类型 [默认值]
​	列名称 类型 [默认值]
​	索引定义；

）

```  mysql
      create table stu(
     	id int(6) auto_increment primary key,
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
    CONSTRAINT property_key FOREIGN KEY(`property_id`) REFERENCES properties(`id`),
    CONSTRAINT word_train_key FOREIGN KEY(`word_id`) REFERENCES words(`id`)
)ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;
```



###3. 数据类型：

1. 整型

   `` tinyint ``1字节 有符号 (-128-127) 无符号（0~255）如表示年龄；

   ``smallint`` 2字节 有符号 (-32768-32767) 无符号(0~65535)；
   ``int`` 4字节 有符号 (-2147483648-2147483647) 无符号 (0~4294967295)；
   ``BIGINT`` 8字节 特别大

2. bool

3. 浮点型：

   ``float``4字节 日常生活中的小数的存储；缺点：易丢失精度；
   ``double`` 8字节 宏观大数字；也有可能丢失精度；
   ``DECIMAL[m,d]`` 精度小数 m 总位数 d 小数点后边的位数；

4. 字符串：

   ``char（位数）`` 定长字符 255
   ``varchar（位数）`` 变长字符 255
   ``text ``65535个字符
   ``MEDIUMBLOB`` 2的 24次方字符
   ``enum（val1,val2,val3）`` 枚举只能选里面的值；

5. 日期时间

   ``date ``日期
   ``time ``时间
   ``datetime ``日期和时间

   ``timestamp``时间戳

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

1. ​

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

   >​    -->建立PHP与数据库的连接；返回资源
   >
   >   @-->错误抑制符
   >   die-->输出（）中的内容，终止程序；


2. mysql_error();返回上一个MySQL操作的文本错误信息；
3. mysql_select_db("数据库名称",$link);选择数据库；
4. mysql_query();向数据库发送一条SQL命令；执行SQL语句；
5. mysql_affected_rows();取得前一条sql返回受影响的行数；insert update delete；
6. mysql_close(); 关闭数据库连接；
7. mysql_fetch_array()从结果集中取得一行作为关联数组，或者数字数组，或者二者兼有；

​    mysql_fetch_array(结果集，参数2)：从结果集中返回一条记录；
    MYSQL_ASSOC :关联数组
    MYSQL_NUM :索引数组
    MYSQL_BOTH :混合数组

8. mysql_fetch_assoc():mysql_fetch_assoc($result) == mysql_fetch_array($result,MYSQL_ASSOC);
9. mysql_fetch_row(): mysql_fetch_row($result) == mysql_fetch_array($result,MYSQL_NUM);
10. mysql_num_rows():获取select语句执行后的结果集中记录的条数；

SQL语句：sql语句在PHP中是以字符串的形式存在的；

```php
//连接数据库

$link = @mysql_connect("localhost","root","root") or die("连接错误".mysql_error());

echo $link."<hr />";

//选择数据库

mysql_select_db("test",$link);

//设置编码格式

mysql_query("set names utf8");

//执行SQL语句 sql语句在PHP中是以字符串的形式存在的；

//增加数据库中的信息

/*

$sql = "INSERT INTO student(s_name,s_password,s_score,s_sex,s_age)

        VALUES('李四','002','77','2','19')";

mysql_query($sql);

*/

//修改数据库表中的信息

/*

$sql = "UPDATE student SET s_name='lisi' WHERE s_id=2";

mysql_query($sql);

*/

//删除数据库中的信息

/*

$sql = "DELETE FROM student WHERE s_id=2";

mysql_query($sql);

*/

//查询数据库中的信息

//查询student表中的所有信息

$sql = "SELECT *FROM student";

//执行查询语句mysql_query()返回资源；

result = mysql_query(sql);

//查询返回的结果集中记录的条数

count = mysql_num_rows(result);

echo "student表中的信息条数：{$count}<hr />";

//截取一条返回的信息

rs = mysql_fetch_array(result,MYSQL_ASSOC);

print_r($rs);

echo "<hr/ >";

//显示部分信息，单双引号效果一致

echo rs['s_id']."==>".rs['s_name']."<br/>";

echo rs["s_id"]."==>".rs["s_score"]."<br/>";

echo "<hr />";

while(rs = mysql_fetch_array(result,MYSQL_ASSOC))

{

  print_r($rs);

  echo "<br />";

}

echo "<hr />";

//查看受影响的数据条数

echo mysql_affected_rows();

//关闭数据库连接；

mysql_close($link);

echo "<hr />";

//正则表达式

preg_match("/[0-9]+/","you have 42 magic beans",$captured);

print_r($captured);

echo "<br />";

$ll = preg_match("/[[:<:]]gun[[:>:]]/","gun");

echo $ll;

```

