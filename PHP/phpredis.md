## 安装PHP Redis 扩展包

```bash
unzip phpredis-develop.zip
cd phpredis-develop

# 生成扩展配置
/usr/local/php/bin/phpize

# 编译Redis
./configure --with-php-config=/usr/local/php/bin/php-config
make
make install

# 我的返回
Installing shared extensions:     /usr/lib/php/20170718/
```

## 配置PHP支持redis

编辑php.ini文件

```bash
vim /usr/local/php/etc/php.ini
# 找到fpm的配置文件，默认在/etc/php/7.x/fpm/php.ini下面
vim /etc/php/7.x/fpm/php.ini
# 增加扩展到php
extension = redis.so
```

重新启动php-fpm

```bash
/etc/init.d/php-fpm restart
```

在php测试下是否成功

​                            

```php
<?php
$redis = new Redis();
$redis->connect('192.168.25.129', 6379);
$redis->set('key', 'test');
echo $redis->get('key');
```