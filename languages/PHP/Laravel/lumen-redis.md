1. 安装依赖

   ```bash
    composer require predis/predis
    composer require illuminate/redis
   ```

2. 引入redis

在目录bootstrap/app.php添加如下注册信息

```php
$app->register(Illuminate\Redis\RedisServiceProvider::class);
```



3. 启用redis辅助函数 去掉bootstrap/app.php中以下调用的注释

    ```php
    $app->withFacades();
    $app->withEloquent();
    ```

    

4. 在evn中配置连接信息

    ```conf
    REDIS_HOST=127.0.0.1
    REDIS_PORT=6379
    ```

5. 使用

   ```php
   use Illuminate\Support\Facades\Redis;
   
   Redis::setex($token, env('EXPIRE_IN'), json_encode($value));
   $value = Redis::get($token);
   if(!$value) throw new InternalException('token对应的用户不存在');
   $value = json_decode($value);
   $result['id'] = $value->{'id'};
   $result['scope'] = $value->{'scope'};
   Redis::del($token);
   ```

   
