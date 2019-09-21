## api网关 api-gateway

1. 在工程中新建子模块,为springboot工程

2. 在pom文件中导入dubbo和zookeeper客户端依赖

   ```xml
   <dependency>
      <groupId>com.alibaba.spring.boot</groupId>
      <artifactId>dubbo-spring-boot-starter</artifactId>
      <version>2.0.0</version>
   </dependency>
   <dependency>
      <groupId>com.101tec</groupId>
      <artifactId>zkclient</artifactId>
      <version>0.10</version>
   </dependency>
   ```

3. 配置yaml的文件

   ```yaml
   spring:
     application:
       name: meeting-gateway
     dubbo:
       server: true
       registery: zookeeper://localhost:2181
   ```

4. 在springboot入口类中添加``@EnableDubboConfiguration``注解

   ```java
   @SpringBootApplication(scanBasePackages = {"com.stylefeng.guns"})
   @EnableDubboConfiguration
   public class GunsRestApplication {
   
       public static void main(String[] args) {
           SpringApplication.run(GunsRestApplication.class, args);
       }
   }
   ```

5. 编写测试类

   ```java
   import com.alibaba.dubbo.config.annotation.Service;
   import com.stylefeng.guns.api.user.UserAPI;
   import org.springframework.stereotype.Component;
   
   @Component
   @Service(interfaceClass = UserAPI.class)
   public class UserImpl implements UserAPI {
   
       @Override
       public boolean isLogin(String username, String password) {
           return true;
       }
   }
   ```

   

6. 启动程序和zookeeper

   ```bash
   zookeeper-3.4.10/bin$ ./zkServer.sh start
   ```

7. 抽离业务接口

   使得各个子工程引用同一个接口定义

   - 新建一个子模块,空工程即可,不需要其他依赖,仅仅只是用来定义接口

     ```xml
     <?xml version="1.0" encoding="UTF-8"?>
     <project xmlns="http://maven.apache.org/POM/4.0.0" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
              xsi:schemaLocation="http://maven.apache.org/POM/4.0.0 http://maven.apache.org/xsd/maven-4.0.0.xsd">
         <modelVersion>4.0.0</modelVersion>
     
         <groupId>com.stylefeng.guns</groupId>
         <artifactId>guns-api</artifactId>
         <version>0.0.1</version>
         <packaging>jar</packaging>
     
         <name>guns-api</name>
         <description>guns api</description>
     
         <parent>
             <groupId>com.stylefeng</groupId>
             <artifactId>guns-parent</artifactId>
             <version>1.0.0</version>
             <relativePath>../pom.xml</relativePath>
         </parent>
     
         <dependencies>
         </dependencies>
     
         <build>
             <resources>
                 <resource>
                     <directory>src/main/resources</directory>
                 </resource>
             </resources>
         </build>
     </project>
     ```

     

   - 将他进行maven install安装到maven本地仓库中

   - 在父模块中声明

     ```xml
     <dependency>
         <groupId>com.stylefeng</groupId>
         <artifactId>guns-api</artifactId>
         <version>${guns.version}</version>
     </dependency>
     ```

   - 在要实现接口的模块总引用,如gateway

     ```xml
     <dependency>
         <groupId>com.stylefeng.guns</groupId>
         <artifactId>guns-api</artifactId>
         <version>0.0.1</version>
         <scope>compile</scope>
     </dependency>
     ```





## dubbo 启动检查

服务启动过程中验证服务提供者的可用性

尽量不要取消启动检查

取消服务检查 => 谁引用配置谁

```java
@Reference(interfaceClass = UserAPI.class, check = false)
private UserAPI userAPI;
```



## dubbo 负载均衡

dubbo默认提供4种负载均衡策略



| 策略名称          | 策略描述                                                  |
| ----------------- | --------------------------------------------------------- |
| Random            | **随机**, 按权重设置随机概率                              |
| RoundRobin        | **轮寻**, 按公约后的权重设置轮寻比率                      |
| LeastActive       | **最少活跃调用数**, 相同活跃的随机,活跃数值调用前后计数差 |
| ConsistentHashmap | **一致性Hash**,相同参数的请求总是发到同一提供者           |



## dubbo 多协议支持

服务之间的通信协议

dubbo支持多种协议RMI,Hessian,HTTP,Redis,Memcached等

|          | dubbo                                                      | RMI                                              | Hessian                                               |
| -------- | ---------------------------------------------------------- | ------------------------------------------------ | ----------------------------------------------------- |
| 连接数   | 单连接                                                     | 多连接                                           | 多连接                                                |
| 连接方式 | 长连接                                                     | 短连接                                           | 短连接                                                |
| 传输协议 | TCP协议                                                    | TCP协议                                          | HTTP协议                                              |
| 传输方式 | NIO异步传输                                                | 同步传输                                         | 同步传输                                              |
| 适用场景 | 1. 数据包较小(单数据包在100k左右) 2. 消费者个数多3常规方式 | 1.数据包大小不一致,2. 消费者和服务提供者相差不大 | 1. 数据包大小不一致 2. 消费者和服务提供者数量相差不大 |



## 业务限流

- 漏桶法
- 令牌 桶

## dubbo 分布式事务

- 两段式事务

- 三段式事务

- 基于XA的分布式事务

- 基于消息的最终一致性方案

- TCC编程式补偿事务(try-confirm-cancel)

基于消息事务是强一致性事务,会存在资源浪费

TCC事务是柔性事务,在try的阶段对资源做预留

TCC事务在确认或取消阶段释放资源

与基于消息的事务相比,TCC的时效性更好

GTS,DTX,TCC-Transaction



1. 需要在提供分布式事务支持的接口上添加@Compensable
2. 在对应的接口实现上添加@Compensable(confirmMethod="", cancelMethod="", transactionContextEditor= DubboTransactionContextEditor.class)
3. 实现对应的confirmMethod,cancelMethod, 这两个方法必须与接口实现方法在同一个类中
4. 主事务业务实现差不多时才调用子事务



- 分布式事务中,不要轻易在业务层捕获所有异常

### 幂等性

f(f(x)) = f(x), 使用相同参数对同一资源重复调用某个接口的结果与调用一次的结果相同