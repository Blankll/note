# RESTFUL

## restful服务设计原则

- 以模型的方式返回全部资源数据[基于资源，数据通常都应该返回，即便当前业务并没有使用到该数据]
- 与业务无关，与模型本身无关的字段可以省略
- 以尽量简洁的数据结构和最优的数据库操作性能为目标对资源和业务需求进行平衡
- 开放接口无法得知业务的具体需求，所以可以以restful的形式返回数据
- 非开放接口可以结合具体的业务需求进行取舍改进
- 不能照搬理论和原则


php构造方法的重载

```php
    public function __construct()
    {
        $param_num = func_num_args();
        if(0 == $param_num) return;
        $params = func_get_args();
        if(1 != count($params)) throw new Exception('message参数错误');
        if(count($params) == count($params, 1))
             call_user_func_array(array($this, 'construct1'), $params);
        else call_user_func_array(array($this, 'construct2'), $params);
    }
    
    public function construct1($message)
    {
        $this->message = $message;
    }
    public function construct2($params = [])
    {
        if(!is_array($params)) throw new Exception('message参数错误');
        if(array_key_exists('code')) $this->code = $params['code'];
        if(array_key_exists('message')) $this->message = $params['message'];
        if(array_key_exists('error_code')) $this->error_code = $params['error_code'];
    }
```

# RESTFUL最佳实践

## HTTP动词[幂等性， 资源安全性]

1. ``POST``：创建
2. ``PUT``：更新
3. ``GET``：查询
4. ``DELETE``：删除

  ## 状态码

``404``：资源未找到

``400``：参数错误

``200``：GET(查询操作)请求执行成功

``201``[^1]：POST(创建资源)请求成功

``202``：PUT(更新资源)成功

``401``：未授权(没有几访问接口权限)

``403``：当前资源禁止访问(请求本身有访问权限)

``500``：服务器未知错误



TP5指定返回的状态码[该类继承自Think\Exception]

```php
return json(new SuccessMessage("用户地址操作成功"),201);
```





[^1]: 网站中原意为请求成功发送，但服务器暂时未处理 