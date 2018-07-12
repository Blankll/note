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

