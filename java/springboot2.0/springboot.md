# springboot

## 创建springboot应用





### 启动spring 项目

mvn spring-boot:run



## 注解

@controller: 处理http请求

@RestController: Spring4之后的注解，@ResponseBody + @Controller

@RequestMapping:  配置url映射

## url参数

@PathVariable 获取url中的数据　``/paht/1/name``

@RequestParam 获取请求参数  `` /path?id=1``

@GetMaping 组合注解



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

## spring表单验证

