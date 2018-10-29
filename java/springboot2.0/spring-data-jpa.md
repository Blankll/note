jpa java Persistence API 定义了一系列的持久化标准



## 使用spring-boot-jpa

spring-boot-jpa是对hibernate的封装

１．添加依赖

在pom.xml中添加

```xml
<!--jpa依赖-->
<dependency>
	<groupId>org.springframework.boot</groupId>
    <artifactId>spring-boot-starter-data-jpa</artifactId>
</dependency>
<!--mysql组件-->
<dependency>
	<groupId>mysql</groupId>
    <artifactId>mysql-connector-java</artifactId>
</dependency>
<!-- mariadb -->
<dependency>
    <groupId>org.mariadb.jdbc</groupId>
    <artifactId>mariadb-java-client</artifactId>
</dependency>
<!--任选一个数据连接驱动就可以了-->
```

mariadb默认关闭远程连接，需要更改配置文件

```sql
--/etc/mysql/mariadb.conf.d/50-server.cnf--
bind-address = 0.0.0.0
```

在配置文件中配置连接参数

spring.jpa.hibernate.ddl-auto= 

> create:每次服务启动都创建表，如果表存在，则会删除存在的表
>
> update:第一次运行时创建表，如果表已经存在不会再进行创建，数据得以保存
>
> create-drop:应用停止时删除表
>
> none什么都不做
>
> validate:验证表结构是否和定义一致，如果不一致就会报错



```properties
spring.datasource.driver-class-name=org.mariadb.jdbc.Driver
spring.datasource.url=jdbc:mysql://10.10.18.7:3306/lab
spring.datasource.username=lab
spring.datasource.password=password
spring.jpa.hibernate.ddl-auto=update
spring.jpa.show-sql=true
```

id自增策略

```java
@Id // primary key
@GeneratedValue(strategy = GenerationType.AUTO) // id自增
private Integer id;
```



JPA提供的四种标准用法为TABLE,SEQUENCE,IDENTITY,AUTO. 
TABLE：使用一个特定的数据库表格来保存主键。 
SEQUENCE：根据底层数据库的序列来生成主键，条件是数据库支持序列。 
IDENTITY：主键由数据库自动生成（主要是自动增长型）