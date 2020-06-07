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

### 定义对象关联

```java
package com.lab.dataobjects;

import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;
import javax.validation.constraints.Min;

@Entity // 与数据表关联
public class Girl{
    @Id // primary key
    @GeneratedValue(strategy = GenerationType.AUTO) // id自增
    private Integer id;
    private String name;
    @Min(value=18, message="年龄小于18")
    private Integer age;

}
```

jpa的默认数据表类名与数据表名相对应product_master 对应类ProductMaster,也可以通过注解

@Table(name="product_master")来指定。

### 建立dao

在工程的目录下建立一个dao目录或repositories目录

```java
// 对应数据库关系模型中的类名　primary key的类型
public interface ProductCategoryRepository extends JpaRepository<ProductCategory, Integer>{

}
```

在进行数据更新时，思路是先找出待更新的目标记录，进行跟新，如果时间没有进行手动输入，将不会在数据库中自动更新跟新时间，因为只有在时间输入为空时才会默认获取当前时间，所以需要在对象关联中加入动态更新的注解。

```java
package com.lab.dataobjects;

import java.util.Date;

import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.Id;

import org.hibernate.annotations.DynamicUpdate;

import lombok.Data;
@Entity
@DynamicUpdate // 动态更新更新时间
@Data
public class ProductCategory {
    /**分类id自增 */
    @Id
    @GeneratedValue
    private Integer categoryId;
    /**分类名称 */
    private String categoryName;
    /**类目编号 */
    private Integer categoryType;
    /**时间 */
    private Date createTime;
    private Date updateTime;
}
```

**开发流程dao-> service -> controller**