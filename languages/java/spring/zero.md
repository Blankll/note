# springboot

## spring framework核心模块构成

1. spring-core: Spring的基础API模块，如资源管理，泛型处理
2. spring-beans: Spring Bean相关，如依赖查找，依赖注入
3. spring-aop: Spring AOP处理，如动态处理，AOP字节码提升
4. spring-context: 事件驱动，注解驱动，模块驱动
5. spring-expression: Spring表达式语言模块

## 创建springboot应用

### 启动spring 项目

mvn spring-boot:run



## 注解

@controller: 处理http请求

@RestController: Spring4之后的注解，@ResponseBody + @Controller

@RequestMapping:  配置url映射

＠Bean注解将方法返回的对象放入spring的环境,方便其他方法使用

## url参数

@PathVariable 获取url中的数据　``/paht/1/name``

@RequestParam 获取请求参数  `` /path?id=1``

@GetMaping 组合注解



## spring表单验证

