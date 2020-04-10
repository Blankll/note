# springboot2+下的全局异常处理

全局异常处理,统一错误返回都是一个项目的地基,所谓基础不牢,地动山摇,虽然我也没开发过太多的项目,但是大学这么几年过来,参加的这些中小型的学校项目,公司项目,负责人要么天花乱坠,要么不懂技术,要么就是要看界面效果,导致大量的项目,金絮其外,;败絮其中,作为一个backend coder, 对全局处理的规约,是十分有必要,对项目的可维护性也是十分有帮助的,今天将会分享一下个人在springboot2上的处理方式

1. 定义数据返回格式

   数据返回格式需要在写代码前就应当与前端协商量好,严谨的公司可能会有一套自己的规定,在前端完全分离的项目环境下, 我自己定义的规则如下:

   - 返回数据content-type为application/json, 返回数据内容为json格式
   - 返回数据内容包括三个字段, code, messages, data
   - code为用户自定义的错误代码, 前一位数与返回的httpCode相同, 请求成功时httpCode为200, code为2000
   - messages为返回信息,在请求错误时十分必要,messages是一个列表数据,包含一道多条错误消息
   - data为请求结果返回的数据, 当请求错误或者进行如添加操作等不需要返回数据时返回为null

   综上,数据返回格式如下:

   ```java
   public class Resp<T> {
       private Integer code;
       private List<String> messages = new ArrayList<>();
       private T data;
   
       public void setCode(Integer code){
           this.code = code;
       }
    public Integer getCode(){
           return this.code;
       }
       public void setData(T data){
           this.data = data;
       }
       public T getData(){
           return this.data;
       }
   
       public List<String> getMessages() {
           return messages;
       }
   
       public void setMessages(List<String> messages) {
           this.messages = messages;
       }
   
       public Resp(Integer code, String message, T data) {
           this.code = code;
           this.messages.add(message);
           this.data = data;
       }
   
       public Resp(T data) {
           this(2000, "操作成功", data);
       }
       public Resp(String message, T data) {
           this(2000, message, data);
       }
       public Resp() {
       }
   
       public void addMessage(String message) {
           this.messages.add(message);
       }
   }
   ```
   
   前端收到的json格式:
   
   ```json
   {
       "code": 4000,
       "messages": [
           "error messages"
       ],
       "data": null
   }
   ```
   
2. 通过exceptionhandler进行全局异常捕获

   在进行全局异常捕获时,我们需要分清楚有哪些错误我们需要处理.主要有一下的考量:

   - 前端造成的请求错误,后端需要给前端明确的错误原因(messages)
   - 在500错误在生产环境中需最好不将详细内容发送到前端,以免不轨人员利用

   总的来说,异常主要如下:

   1. 请求参数校验失败
   2. 处理程序抛出的异常, 统一返回内容
   3. 系统的一些错误抛出500, 同时进行日志记录,系统报警等流程

   请求参数校验确保程序在进行逻辑处理时用户传入的参数符合要求,在springboot中分成如下:

   - path varable
   - Request param
   - request body

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

      这里需要注意,有两个javax的@Valid 和springboot的validated 都可以用在上面的参数注解,参数绑定失败将会抛出``MethodArgumentTypeMismatchException``的错误

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
      
      ```
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
   
      个人觉得，路由和传参应该时定死的，传了参你爱要不要，但是你要却不在路由里面指定参数占位符，我觉得时在耍流氓。所以开发时候就测试号，不值得为这种毛病在弄aop,因为后面还有好多情况，自由带来的混乱。

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

      如果如果传了非整形数值会报``MethodArgumentTypeMismatchException``异常[同PathVarable]. 

      总之就是我们有很多不同的方法进行验证，同样也会有很多不同的异常，我们需要处理，不可能直接将这些异常抛给前端，除非，你想和他干一架。待会我再来讨论我找到的统一处理的方法。

   3. RequestBody

      在http body中传递的数据, get请求没有body,所以get请求不可能携带RequestBody.

      

   在处理有多个请求参数校验中,通常通过新建一个类通过注解规定参数校验规则:
   
   ```java
   public class LoginReqeust {
       @NotEmpty(message = "账号不能为空")
       private String ynnuId;
       @NotEmpty(message = "密码不能为空")
       private String password;
   
       public String getYnnuId() {
           return ynnuId;
       }
   
       public void setYnnuId(String ynnuId) {
           this.ynnuId = ynnuId;
       }
   
       public String getPassword() {
           return password;
       }
   
       public void setPassword(String password) {
           this.password = password;
       }
   
   
       public String getYnnu_id() {
           return ynnuId;
       }
   
       public void setYnnu_id(String ynnuId) {
           this.ynnuId = ynnuId;
       }
}
   ```

   在controller中进行验证注入:
   
   ```java
   @PostMapping("login")
public ResponseResult<TokenView> login(@Validated LoginReqeust loginReqeust) {...}
   ```

   上面的验证方式同时有效于RequestParam和RequestBody中的请求参数

   	总结上面的异常情况，我在网上找到了一个总结表
   
   | ConstraintViolationException            | 违反约束avax扩展定义                                         |
   | --------------------------------------- | ------------------------------------------------------------ |
   | BindException                           | 绑定失败如表单对象参数违反约束                               |
   | MethodArgumentNotValidException         | 参数无效如JSON请求参数违反约束                               |
   | MissingServletRequestParameterException | 参数缺失(@Valid @RequestParam(name = "record_id") Long recordId) |
| TypeMismatchException                   | 参数类型不匹配                                               |
   | MethodArgumentTypeMismatchException     | pathVarable参数绑定失败如参数类型不一致                      |

   如果发送了一个请求方方法不匹配的请求，会返回405。前端应当对405进行特定的处理

   总结了springboot下的请求验证构建方法和抛出的异常,就可以通过springboot的exceptionHandler进行拦截了,
   
   ```java
   @ControllerAdvice
   public class ExceptionHandler {
       @Value("${debug}")
       private boolean isDebug;
       /**
        * 内部错误,返回500异常
        * @param  e InternalException
        * @return Resp
        */
       @org.springframework.web.bind.annotation.ExceptionHandler(InternalException.class)
       @ResponseBody
       @ResponseStatus(HttpStatus.INTERNAL_SERVER_ERROR)
       public ResponseEntity<Resp> InternalExceptionHandler(InternalException e) {
           // @TODO LOG ERROR INFO
           String message = isDebug ? e.getMessage() : "系统错误,请联系管理员";
           return  new ResponseEntity(new Resp<String>(5000, e.getMessage(), null), HttpStatus.INTERNAL_SERVER_ERROR);
       }
   
       /**
        * 请求错误,返回错误代码,异常信息
        * @param e ExternalException
        * @return ResponseEntity
        */
       @org.springframework.web.bind.annotation.ExceptionHandler(ExternalException.class)
       @ResponseBody
       public ResponseEntity<Resp> ExternalExceptionHandler(ExternalException e) {
   
           return new ResponseEntity(new Resp<String>(e.getCode(), e.getMessage(), null), e.getStatus());
       }
   
       /**
        * PathVarable 参数绑定失败
        * @param e
        * @return
        */
       @org.springframework.web.bind.annotation.ExceptionHandler(MethodArgumentTypeMismatchException.class)
       public ResponseEntity<Resp> requestBodyValidationFailure(MethodArgumentTypeMismatchException e) {
           Resp result = new Resp();
           result.addMessage(e.getMessage());
           System.err.println("[ERROR] EXCEPTION HANDLER");
           result.setCode(4000);
   
           return new ResponseEntity<>(result, HttpStatus.BAD_REQUEST);
       }
   
       /**
        * request 参数绑定失败
        * @param e Exception
        * @return ResponseEntity
        */
       @org.springframework.web.bind.annotation.ExceptionHandler(BindException.class)
       public ResponseEntity<Resp> requestBodyValidationFailure(BindException e) {
           Resp result = new Resp();
   
           List<FieldError> fieldErrors=e.getBindingResult().getFieldErrors();
           for (FieldError error : fieldErrors){
               // @TODO loger info
               result.addMessage(error.getField()+":"+error.getDefaultMessage());
           }
   
           System.err.println("[ERROR] EXCEPTION HANDLER");
           System.out.println(e);
           result.setCode(4000);
   
           return new ResponseEntity<>(result, HttpStatus.BAD_REQUEST);
       }
   
       /**
        * 默认的全局异常处理,如果之前的都无法捕获,最后会有这个来获取 500异常
        * @param req request
        * @param e Exception
        * @return ResponseEntity<Resp>
        */
       @org.springframework.web.bind.annotation.ExceptionHandler(Throwable.class)
       public ResponseEntity<Resp> defaultHandler(HttpServletRequest req, Exception e) {
           String message = isDebug ? e.getMessage() : "系统错误,请联系管理员";
           // @TODO log
           return  new ResponseEntity(new Resp<String>(5000, message, null), HttpStatus.INTERNAL_SERVER_ERROR);
       }
   
}
   ```
   
   