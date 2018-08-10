# yaf

## 安装docker环境

1. docker pull ubuntu::latest;
2. docker run -d -p  8001:8001 -p 8000:8000 -p 80:80 imagename  /sbin/bash
3. docker exec -it id /bin/bash

#### 安装类lnmp

1. 在容器中安装wget

2. 安装lnmp

3. wget下载yaf ``wget'http://pecl.php.net/get/yaf-3.0.7.tgz';``

4. 解压 tar zxvf yaf-3.0.7.tgz

5. phpize

6. ./configure --with-php-config=/usr/local/php/bin/php-config

7. make

8. make install`` /usr/local/lib/php/extensions/no-debug-non-zts-20160303/``

9. vim /usr/local/php/etc/php.ini 末尾添加 

   ```shell
   [Yaf]
   extension=yaf.so
   yaf.environ="product" | "develop"
   yaf.use_spl_autoload=1
   yaf.use_namespace=1
   ```

10. 重启服务

11. lnmp vhost add

12. 选择设置规则

    ```bash
    Virtualhost infomation:
    Your domain: yaf.com
    Home Directory: /home/work/yaf
    Rewrite: none
    Enable log: yes
    Create database: no
    Create ftp account: no
    ```

13. 配置文件位于/usr/local/nginx/conf/vhost/yaf.com.conf

## 使用yaf

### 生成Yaf的标准模板

如果在php.ini中关闭了namespace，运行命令: ./yaf_cg project_name，就会在当前目录生成一个output目录，其中会有project_name的项目模板

如果启用了命名空间,则运行命令：./yaf_cg project_name  ''  n

所有请求都在bootstrap中初始化

namespace note 

exceptions

```php
Yaf_Controller_Abstract =>   \Yaf\Controller_Abstract;
Yaf_Route_Static =>    Yaf\Route_Static;
```

查看nat中的DOCKER链

sudo iptables -t nat --list-rules DOCKER

## yaf路由

1. Yaf_Route_Static[默认路由]
2. Yaf_Route_Simple
3. Yaf_Route_Supervar
4. Yaf_Route_Map
5. Yaf_Route_Rewrite
6. Yaf_Route_Regex



yaf_Route_Rewrite 可以很好的实现RESTFUL规范的路由

在Bootstrap中添加路由规则

```php
public function _initRoute(Yaf\Dispatcher $dispatcher)
{
  //在这里注册自己的路由协议，默认使用简单路由
  //创建一个路由协议
  $router = Yaf\Dispatcher::getInstance()->getRouter();
  $route = new Yaf\Route\Rewrite(
  	'user/register/:user_name',
    [
      'controller' => 'user',
      'action' => 'register'
    ]
  );
  //使用路由器装载路由器
  $router->addRoute('product', $route);
}
```



修改表名

```sql
ALTER  T)ABLE table_name RENAME TO new_table_name
```

## api session

登录用户状态保持



##发送邮件

1. 通过composer安装第三方库

   ```shell
   php -r "copy('https://getcomposer.org/installer', 'composer-setup.php');"
   php -r "if (hash_file('SHA384', 'composer-setup.php') === '544e09ee996cdf60ece3804abc52599c22b1f40f4323403c44d44fdfdd586475ca9813a858088ffbc1f233e9b180f061') { echo 'Installer verified'; } else { echo 'Installer corrupt'; unlink('composer-setup.php'); } echo PHP_EOL;"
   php composer-setup.php
   php -r "unlink('composer-setup.php');"
   #install phpMailer
   ./composer.phar require phpmailer/phpmailer
   ##install nette
   ./composer require nette/mail
   ```

   ​

2. 对PHPMailer配置smtp服务

3. 开启PHP sokert 能力支持



收集发出邮件后的效果

方法之一： 发送邮件时在支持html的邮件内容中发送一张用户不可见的图片，同时携带user信息

用户查看图片时就会调用图片，通过服务器上的日志来获取调用信息，便可以收集邮件的查看信息了

## 短信发送

1. 将第三方接口提供的库放在/application/library/thirdPaty/目录下
2. 

###短信发送状态记录

 在短信发送成功后记录短信发送状态 ，将其存入数据库中，以便后期与服务提供商进行费用核对

#### 批量短信通知场景高效发送

## push服务接口

## ip地址转换接口

1. 访问来源统计 地址
2. 小流量线上验证 指定某个特定区域可以访问接口
3. 黑白名单 



## 公共能力抽离

将一些公共的方法抽离出controller，统一放到指定位置。在Yaf中，根目录下有一个library目录，可以将自定义的公共函数，第三方sdk等分类放到library中。


## DAO封装









































**list()** only works on numerical arrays and assumes the numerical indices start at 0.



