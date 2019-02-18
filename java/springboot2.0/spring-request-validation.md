# request validation

请求参数验证应该是任何一个web开发流程的重要环节，web framework都会提供相应的解决方案，不知道是因为我先入为主的原因，还是事实就是如此，PHP的web开发框架Laravel的request validation是我用过最好用的参数验证方式了，但是迫于无奈，这段时间必须使用java进行web开发，于是开始上手spring boot，自然，没个框架的上手都是从填坑开始的.....

## 请求的基础知识

sprong boot2的参数验证方式有很多种，自由也带来了混乱，在spring中，将每一个request的参数分为了三种：PathVariable, ReqeustParam和RequestBody

1. PathVariable : 就是请求路径携带的参数

   标准请求样式

   > /api/zongce/admin/2    # 其中2就是请求的参数

   处理方式

   ```java
   @GetMapping("/api/zongce/admin/{id}")
   public String find(@Valid @PathVariable(name = "id") Long id) {
       
        return "get controller";
   }
   ```

   这样就可以正确的获取请求的参数了.

   

   那么，一些意外情况会发生什么呢？　我们在controller中设置相应的处理方法

   ```java
   @GetMapping("/api/zongce/admin")
   public String find(@Valid @PathVariable(name = "id") Long id) {
       return "get controller";
   }
   ```

   以上没有指定任何path的参数，但是我们却要求传入PathVariable,但是编译通过，若果以当前的路由请求，直接500, 如果添加/1则是404, （我以为他会编译不通过)

   ```json
   # /api/zongce/admin
   {
       "timestamp": "2019-02-14T10:20:41.590+0000",
       "status": 500,
       "error": "Internal Server Error",
       "message": "Missing URI template variable 'id' for method parameter of type Long",
       "path": "/api/zongce/admin"
   }
   
   # /api/zongce/admin/1  
   {
       "timestamp": "2019-02-14T10:18:44.944+0000",
       "status": 404,
       "error": "Not Found",
       "message": "No message available",
       "path": "/api/zongce/admin/1"
   }
   ```

   个人觉得，路由和传参应该时定死的，穿了参你爱要不要，但是你要却不在路由里面指定参数占位符，我觉得时在耍流氓。所以开发时候就测试号，不值得为这种毛病在弄aop,因为后面还有好多情况，自由带来的混乱。

2. RequestParam: 拼接在请求路径总?开头的参数

   标准请求样式

   > /api/zongce/admin?id=2

   处理controller

   ```java
   @getMapping("/api/zongce/admin")
   public String  create(@Valid @RequestParam(name = "id")  Long id) {
       return "admin create controller";
   }
   ```

   如果如果传了非整形数值会报``MethodArgumentTypeMismatchException``异常。总之就是我们有很多不同的方法进行验证，同样也会有很多不同的异常，我们需要处理，不可能直接将这些异常抛给前端，除非，你想和他干一架。待会我再来讨论我找到的统一处理的方法。

3. RequestBody













​	总结上面的异常情况，我在网上找到了一个总结表

| ConstraintViolationException            | 违反约束avax扩展定义           |
| --------------------------------------- | ------------------------------ |
| BindException                           | 绑定失败如表单对象参数违反约束 |
| MethodArgumentNotValidException         | 参数无效如JSON请求参数违反约束 |
| MissingServletRequestParameterException | 参数缺失                       |
| TypeMismatchException                   | 参数类型不匹配                 |

还有一个，如果发送了一个请求方方法不匹配的请求，会返回405。

