# mybates

## springboot 集成mybates

### 导入依赖

在pom文件中添加``mybatis-spring-boot-start``依赖，该包拥有自动装配的特点

```xml
<dependency>
	<groupId>org.mybatis.spring.boot</groupId>
    <artifactId>mybatis-spring-boot-starter</artifactId>
    <version>2.0.0</version>
</dependency>
```



添加数据库连接的配置

```properties
spring.datasource.url=jdbc:mysql://localhost:3306/dbname?useUnicode=true&characterEncoding=UTF-8&zeroDateTimeBehavior=convertToNull&allowMultiQueries=true&useSSL=false
spring.datasource.username=username
spring.datasource.password=password
# 如果使用xml配置的方式需要配置mapper对应的xml文件的路径，若使用注解的方式则可以不用管
mybatis.mapper-locations=classpath:com/location/mapper/*.xml
#mybatis.mapper-locations=classpath:mapper/*.xml        #这种方式需要自己在resources目录下创建mapper目录然后存放xml
# 驼峰命名规范 如：数据库字段是  order_id 那么 实体字段就要写成 orderId
mybatis.configuration.map-underscore-to-camel-case=true
```

如果使用xml配置的方式，maven项目在编译时，置导入``java package -> *.java``, 所以需要配置一下让xml文件也导入到编译后的包中

```xml
<build>
    <resources>
        <resource>
            <directory>src/main/resources</directory>
        </resource>
        <resource>
            <directory>src/main/java</directory>
            <includes>
                <include>**/*.xml</include>
            </includes>
            <filtering>true</filtering>
        </resource>
    </resources>
    <plugins>
        <plugin>
            <groupId>org.springframework.boot</groupId>
            <artifactId>spring-boot-maven-plugin</artifactId>
        </plugin>
    </plugins>
</build>
```

## 业务规范

一个table对应一个entity 和一个mapper, entity是数据库表与对象的映射，同时对应一个mapper interface, mapper中添加我们需要的CURD操作，相当于model层，通过注解或者XML配置，在service层中定义一个autowired就可以进行对数据库的操作了.

```java
@Autowired
private FacultyMapper facultyMapper;
```

这里idea可能会报错，不用理会，他脑子抽了而已。

命名规范

``enetity`` 就叫数据库名称单数

``mapper`` 数据库名称单数 + Mapper  ``interface``

所以，套路就是

- 一个table: 

  ```mysql
  CREATE TABLE `faculties` (
    `id` int(10) unsigned NOT NULL AUTO_INCREMENT COMMENT '学院主键',
    `name` char(100) NOT NULL COMMENT '学院名称',
    `english` char(100) DEFAULT NULL COMMENT '学院英文名称',
    `desc` text COMMENT '学院简介',
    `desc_en` text COMMENT '学院简介en',
    `profile_uri` char(120) DEFAULT NULL COMMENT '学院图标',
    `create_time` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP COMMENT '创建时间',
    `update_time` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP COMMENT '更新时间',
    PRIMARY KEY (`id`),
    UNIQUE KEY `name` (`name`)
  ) ENGINE=InnoDB AUTO_INCREMENT=140 DEFAULT CHARSET=utf8mb4 COMMENT='学院信息表'
  ```

- 一个entity

  ```java
  package com.seven.ynnu.zce.school.entities;
  
  
  import java.io.Serializable;
  import java.sql.Timestamp;
  
  import lombok.Data;
  
  /**
   * @Auther: Blank
   * @Description: com.seven.ynnuzce.pojos
   * @Date: 2/8/19
   * @Version: 1.0
   */
  @Data
  public class Faculty implements Serializable {
      private Long id;
      private String name;
      private String english;
      private String desc;
      private String descEn;
      private String profileUri;
      private Timestamp createTime; //创建时间
      private Timestamp updateTime; //更新时间
  
  
  }
  ```

- 一个mapper

  ```java
  package com.seven.ynnu.zce.school.mappers;
  
  import com.seven.ynnu.zce.school.entities.Faculty;
  import org.apache.ibatis.annotations.*;
  
  import java.util.List;
  
  /**
   * @Auther: Blank
   * @Description: com.seven.ynnu.zce.school.mapers
   * @Date: 2/11/19
   * @Version: 1.0
   */
  
  @Mapper
  public interface FacultyMapper {
      @Select("SELECT * FROM faculties WHERE name = #{name}")
      Faculty findByName(@Param("name") String name);
  
      @Select("SELECT * FROM faculties")
      List<Faculty> findAllFaculty();
  
      @Insert("INSERT INTO faculties(`name`, `english`, `desc`, `desc_en`, `profile_uri`) VALUES(#{name}, #{english}, #{desc}, #{descEn}, #{profile_uri});")
      @Options(useGeneratedKeys = true, keyColumn = "id", keyProperty = "id")
      Long create(Faculty faculty);
  
      @Insert("INSERT IGNORE INTO faculties(`name`, `english`, `desc`, `desc_en`, `profile_uri`) VALUES(#{name}, #{english}, #{desc}, #{descEn}, #{profileUri});")
      @Options(useGeneratedKeys = true, keyColumn = "id", keyProperty = "id")
      Long createIgnore(Faculty faculty);
  
  }
  ```

  

## springboot 和mybatis多数据源配置

上面都是一些常规操作，下面来看看多数据源配置的问题

有时候我们需要进行多数据库操作,在同一个数据库中同时使用两个不同的数据库，这两个数据库可以是同一个实例上的不同数据库，也可以时不同实例上的数据库，甚至是不同的数据库

多数据库实例就需要多个数据源，所以我们每一个数据库对应一个连接池，每一个连接池一个数据源

### 配置两个连接池

- DataSource One

  ```java
  package com.seven.ynnu.zce.datasource;
  
  import org.apache.ibatis.session.SqlSessionFactory;
  import org.mybatis.spring.SqlSessionFactoryBean;
  import org.mybatis.spring.annotation.MapperScan;
  import org.springframework.beans.factory.annotation.Qualifier;
  import org.springframework.boot.context.properties.ConfigurationProperties;
  import org.springframework.boot.jdbc.DataSourceBuilder;
  import org.springframework.context.annotation.Bean;
  import org.springframework.context.annotation.Configuration;
  import org.springframework.context.annotation.Primary;
  import org.springframework.jdbc.datasource.DataSourceTransactionManager;
  
  import javax.sql.DataSource;
  
  /**
   * MULTI DATA SOURCE SETTING
   * @Auther: Blank
   * @Description: com.seven.ynnu.zce.datasource
   * @Date: 2/11/19
   * @Version: 1.0
   */
  
  
  @Configuration
  @MapperScan(basePackages = "com.seven.ynnu.zce.school.mappers")
  public class SchoolDataSource {
      public static final String DATA_SOURCE = "school";
      public static final String TRANSCATION_MANAGER = "schoolmanager";
      public static final String SQLSESSION_FACTORY = "schoolfactory";
  
      @Bean(name = DATA_SOURCE)
      @ConfigurationProperties(prefix = "spring.datasource.school")
      @Primary
      public DataSource dataSource() {
          return DataSourceBuilder.create().build();
      }
  
      @Bean(name = TRANSCATION_MANAGER)
      @Primary
      public DataSourceTransactionManager dataSourceTransactionManager(@Qualifier(DATA_SOURCE) DataSource ds) {
          return new DataSourceTransactionManager(ds);
      }
  
      @Bean(name = SQLSESSION_FACTORY)
      @Primary
      public SqlSessionFactory sqlSessionFactory(@Qualifier(DATA_SOURCE) DataSource ds) throws Exception {
          SqlSessionFactoryBean bean = new SqlSessionFactoryBean();
          bean.setDataSource(ds);
          return bean.getObject();
      }
  }
  ```

  

- DataSource Two

  ```java
  package com.seven.ynnu.zce.datasource;
  
  import org.apache.ibatis.session.SqlSessionFactory;
  import org.mybatis.spring.SqlSessionFactoryBean;
  import org.mybatis.spring.annotation.MapperScan;
  import org.springframework.beans.factory.annotation.Qualifier;
  import org.springframework.boot.context.properties.ConfigurationProperties;
  import org.springframework.boot.jdbc.DataSourceBuilder;
  import org.springframework.context.annotation.Bean;
  import org.springframework.context.annotation.Configuration;
  import org.springframework.jdbc.datasource.DataSourceTransactionManager;
  
  import javax.sql.DataSource;
  
  import static com.seven.ynnu.zce.datasource.SchoolDataSource.SQLSESSION_FACTORY;
  
  /**
   * @Auther: Blank
   * @Description: com.seven.ynnu.zce.datasource
   * @Date: 2/11/19
   * @Version: 1.0
   */
  @Configuration
  @MapperScan(basePackages = "com.seven.ynnu.zce.zongce.mappers", sqlSessionFactoryRef = SQLSESSION_FACTORY)
  public class ZongceDataSource {
      public static final String DATA_SOURCE = "zongce";
      public static final String TRANSCATION_MANAGER = "zongcemanager";
      public static final String SQLSESSION_FACTORY = "zongcefactory";
  
      @Bean(name = DATA_SOURCE)
      @ConfigurationProperties(prefix = "spring.datasource.zongce")
      public DataSource dataSource() {
          return DataSourceBuilder.create().build();
      }
  
      @Bean(name = TRANSCATION_MANAGER)
      public DataSourceTransactionManager dataSourceTransactionManager(@Qualifier(DATA_SOURCE) DataSource ds) {
          return new DataSourceTransactionManager(ds);
      }
  
      @Bean(name = SQLSESSION_FACTORY)
      public SqlSessionFactory sqlSessionFactory(@Qualifier(DATA_SOURCE) DataSource ds) throws Exception {
          SqlSessionFactoryBean bean = new SqlSessionFactoryBean();
          bean.setDataSource(ds);
          return bean.getObject();
      }
  }
  ```

  

  tips: 

  ``@MapperScan(basePackages = "com.seven.ynnu.zce.zongce.mappers", sqlSessionFactoryRef = SQLSESSION_FACTORY)``
  basePackages: 指定扫描的包,用于区分不同数据源下的Mapper. 这样就可以通过不同的mapper对应自己的数据库
  sqlSessionFactoryRef: 指定包下使用的SqlSessionFactory,即数据源

- 配置数据库连接信息

  在springboot的配置信息中将原来的单数据库配置进行更改，变成两个，分别对应不同的数据库，与DataSource中的``@ConfigurationProperties(prefix = "spring.datasource.zongce")``相对应，根据不同的配置文件加载数据库连接池

  ```properties
  spring.datasource.school.jdbc-url=jdbc:mysql://localhost:3306/school?useUnicode=true&characterEncoding=UTF-8&zeroDateTimeBehavior=convertToNull&allowMultiQueries=true&useSSL=false
  spring.datasource.school.driver-class-name=com.mysql.jdbc.Driver
  spring.datasource.school.username=username
  spring.datasource.school.password=password
  # 注意注意 XML配置时才会用到, 注解时用不到
  mybatis.mapper-locations=classpath:com/mapper/*.xml
  #mybatis.mapper-locations=classpath:mapper/*.xml        #这种方式需要自己在resources目录下创建mapper目录然后存放xml
  mybatis.type-aliases-package=com.seven.ynnu.zce.school.mappers
  # 驼峰命名规范 如：数据库字段是  order_id 那么 实体字段就要写成 orderId
  mybatis.configuration.map-underscore-to-camel-case=true
  
  
  
  spring.datasource.zongce.jdbc-url=jdbc:mysql://localhost:3306/zongce?useUnicode=true&characterEncoding=UTF-8&zeroDateTimeBehavior=convertToNull&allowMultiQueries=true&useSSL=false
  spring.datasource.zongce.driver-class-name=com.mysql.jdbc.Driver
  spring.datasource.zongce.username=username
  spring.datasource.zongce.password=password
  ```

  ### 坑

  1. 配置文件要有两个地方要注意

     ```properties
     spring.datasource.zongce.driver-class-name=com.mysql.jdbc.Driver
     spring.datasource.zongce.jdbc-url=jdbc:mysql://localhost:3306/zongce?useUnicode=true&characterEncoding=UTF-8&zeroDateTimeBehavior=convertToNull&allowMultiQueries=true&useSSL=false
     ```

     这里我把驼峰命名改成了-命名法，不这么稿会报错，我也没研究出来为什么，先这么注释着

  2. 连接url使用如下的mariadb是不行的，我还没试是因为mariadb和mysql混用的问题还是mariadb不支持这个东西，后面在研究，总之先全部弄成mysql就可以用了

     ```properties
     spring.datasource.zongce.jdbc-url=jdbc:mysql://localhost:3306/zongce?useUnicode=true&characterEncoding=UTF-8&zeroDateTimeBehavior=convertToNull&allowMultiQueries=true&useSSL=false
     ```

  3. mapper接口中不能有重载的方法(OVERLOADING), 否则会报下面的错误，所以每一个方法参数都是唯一的.

     ```bash
     Mapped Statements collection already contains value for ...
     ```

     


## mybatis批量插入数据

```java
Insert({
 "<script>",
 "insert into table_name(column1, column2, column3) values ",
 "<foreach collection='testLists' item='item' index='index' separator=','>",
 "(#{item.实体属性1}, #{item.实体属性2}, #{item.实体属性3})",
 "</foreach>",
 "</script>"
})
int insertCollectList(@Param(value="testLists") List<Test> testLists);
```



> collection： 指定要遍历的集合（三种情况 list，array，map） ！！！！在这种使用注解sql的情况下，这里请填写mapper方法中集合的名称
>    
> item：将当前遍历出的元素赋值给指定的变量 （相当于for循环中的i）
> separator:每个元素之间的分隔符 
> index:索引。遍历list的时候是index就是索引，item就是当前值 
>
> {变量名}就能取出变量的值也就是当前遍历出的元素