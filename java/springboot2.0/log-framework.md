# 日志框架

1. 定制输出目标
2. 日志滚动策略
3. 定制输出格式
4. 携带的上下文信息
5. 运行时选择性输出
6. 灵活配置
7. 高性能

常用的java日志框架:　JUL,JCL LOGJ4,LOG4J2,jbosslogiing

| 日志门面      | 日志实现 |
| ------------- | -------- |
| JCL           | Log4J    |
| SLF4j         | Log4j2   |
| jboss-logging | Logback  |
|               | JUL      |

## logback和SLF4j的使用

springboot自带这两个日志工具，无需添加依赖



```java
package com.lab;

import org.junit.Test;
import org.junit.runner.RunWith;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.test.context.junit4.SpringRunner;

@RunWith(SpringRunner.class)
@SpringBootTest
public class LogTest {
	//需要指定当前类的类名，打印时会打印出类的名称
    private final Logger logger = LoggerFactory.getLogger(LogTest.class);

   @Test
   public void test(){
       logger.debug("debug...");
       logger.info("info...");
       logger.error("errr...");
   }
}
```

通过使用data这个工具，还可以将代码进一步简化

```java
package com.lab;

import org.junit.Test;
import org.junit.runner.RunWith;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.test.context.junit4.SpringRunner;
// 对应的
import lombok.extern.slf4j.Slf4j;

@RunWith(SpringRunner.class)
@SpringBootTest
@Slf4j //这个注解是在lombok中的，使用要先添加lombok
public class LogTest {
   @Test
   public void test(){
       log.debug("debug...");
   }
}
//不过貌似没成功，不知是编译器没有检测到，还是版本问题
//springboot2.0.6下无法使用
```

将日志分开存储,例如error和info的日志分开存储

在application.properties下进行配置

```properties
logging.pattern.console="%d-%message%n"
logging.path=/var/log/tomcat/
logging.file=/var/log/tomcat/lab.log
logging.pattern.level=debug
```

日志分类存储

在resources目录下新建logback-spring.xml文件

```xml
<?xml version="1.0" encodeing="UTF-8"?>
<configuration>
    <!-- 配置项 -->
    <appender name="consoleLog" class="ch.qos.logback.core.ConsoleAppender">
        <layout class="ch.qos.logback.classic.PatternLayout">
            <pattern>
                %d - %message%n
            </pattern>
        </layout>
    </appender>
    <!-- 配置项 -->
    <appender name="fileInfoLog" class="ch.qos.logback.core.rolling.RollingFileAppender">
        <encoder>
            <pattern>
                %message%n
            </pattern>
        </encoder>
        <!-- 滚动策略 -->
        <rollingPolicy class="ch.qos.logback.core.rolling.TimeBasedRollingPolicy">
            <!-- 路径 -->
            <fileNamePattern>/var/log/tomcat/lab/info.%d.log</fileNamePattern>
        </rollingPolicy>
    </appender>
    <!-- 作用域 --> <!-- 表示作用域为整个项目 -->
    <root level="info">
        <appender-ref ref="consoleLog"></appender-ref>
        <appender-ref ref="fileInfoLog"></appender-ref>
    </root>
</configuration>
```

