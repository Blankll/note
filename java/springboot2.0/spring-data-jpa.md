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
```

## 