## aop

添加依赖

```xml
<dependency>
	<groupId>org.springframework.boot</groupId>
    <artifactId>spring-boot-start-aop</artifactId>
</dependency>
```

建立处理文件

建立class

```java
package com.lab.aspects;

import org.aspectj.lang.annotation.After;
import org.aspectj.lang.annotation.Aspect;
import org.aspectj.lang.annotation.Before;
import org.springframework.stereotype.Component;

@Aspect
@Component
public class HttpAspect {
    @Before("execution(public * com.lab.controllers.*.*(..))")
    public void log() {
        System.out.println(1111);
    }
    @After("excution(public * com.lab.controllers.*.*(..))")
    public void afterLog(){
        System.out.println(222);
    }
}

```

## 全局日志处理

```java
package com.lab.aspects;

import javax.servlet.http.HttpServletRequest;

import org.aspectj.lang.annotation.After;
import org.aspectj.lang.annotation.Aspect;
import org.aspectj.lang.annotation.Before;
import org.aspectj.lang.annotation.Pointcut;
import org.springframework.stereotype.Component;
import org.springframework.web.context.request.RequestContextHolder;
import org.springframework.web.context.request.ServletRequestAttributes;

@Aspect
@Component
public class HttpAspect {
    //指定在这个切面上进行log操作
    @Pointcut("execution(public * com.lab.controllers.*.*(..))")
    public void log() { }

    // 指定在切面方法执行之前进行的操作
    @Before("log()")
    public void beforeLog(){
        // 获取请求信息
        ServletRequestAttributes attributes = (ServletRequestAttributes) RequestContextHolder.getRequestAttributes();
        HttpServletRequest request = attributes.getRequest();
        
        System.out.println(111);
    }
    // 指定在切面方法执行之后进行的操作
    @After("log()")
    public void afterLog(){
        System.out.println(222);
    }
}
```



## 全局异常处理

restful的返回格式应当保持一致

spring会对RuntimeException进行事务回滚，而Exception不会对事务进行回滚。

1. 在项目中定义handle

   ```java
   package com.lab.exceptions;
   
   import com.lab.https.Result;
   import com.lab.utils.ResultUtil;
   
   import org.springframework.web.bind.annotation.ControllerAdvice;
   import org.springframework.web.bind.annotation.ExceptionHandler;
   import org.springframework.web.bind.annotation.ResponseBody;
   
   @ControllerAdvice
   public class ExceptionHandle{
       @ExceptionHandler(Exception.class)
       @ResponseBody
       public Result handle(Exception e){
           return ResultUtil.failure(4000, e.getMessage());
       }
   }
   ```

   通过对捕获到的exception进行分析，根据不同的继承类选择不同的异常返回机制

   可以在异常发生时写入日志

   将异常的code和message通过枚举进行统一管理