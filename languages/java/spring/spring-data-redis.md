# springboot操作redis

1. 添加依赖

   ```xml
   <dependency>
   	<groupId>org.springframework.boot</groupId>
       <artifactId>spring-boot-starter-data-redis</artifactId>
   </dependency>
   ```

2. 使用spring自带的template

   格式为temlate.opsFor[redis的数据结构]Value().[操作方式，都是redis的命令]

   ```java
   stringRedisTemplate.opsForValue().set("seven", "blank");
   String result = stringRedisTemplate.opsForValue().get("seven");
   
   stringRedisTemplate.opsForList() [List]
   stringRedisTemplate.opsForSet() [Set]
   stringRedisTemplate.opsForHash() [Hash]
   stringRedisTemplate.opsForZSet() [ZSet]
   
   ```

3. 自定义序列化方案

   在config的包下(自己建一个包保存配置的bean)

   ```java
   package com.seven.ynnu.zce.configs;
   
   import com.seven.ynnu.zce.zongce.pojos.TokenItem;
   import org.springframework.context.annotation.Bean;
   import org.springframework.context.annotation.Configuration;
   import org.springframework.data.redis.connection.RedisConnectionFactory;
   import org.springframework.data.redis.core.RedisTemplate;
   import org.springframework.data.redis.serializer.Jackson2JsonRedisSerializer;
   
   /**
    * @Auther: Blank
    * @Description: com.seven.ynnu.zce.configs
    * @Date: 2/18/19
    * @Version: 1.0
    */
   @Configuration
   public class RedisSerializerConfig {
       // admin login token serializer strategy
       @Bean
       public RedisTemplate<String, TokenItem> redisAdminTokenItemTemplate(RedisConnectionFactory redisConnectionFactory) {
           RedisTemplate<String, TokenItem> template = new RedisTemplate<>();
           template.setConnectionFactory(redisConnectionFactory);
           Jackson2JsonRedisSerializer<TokenItem> serializer = new Jackson2JsonRedisSerializer<TokenItem>(TokenItem.class);
           template.setDefaultSerializer(serializer);
   
           return template;
       }
   }
   ```

   