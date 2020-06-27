

## php nginx的配置example

```bash
location / {
                # First attempt to serve request as file, then
                # as directory, then fall back to displaying a 404.
                try_files $uri $uri/ =404;
        }
        location ~ \.php$ {
        		# 检测是否有文件存在
                try_files $uri /index.php =404;
                # fastcgi_split_path_info分为两个变量，一个成为$fastcgi_script_name的值，另一个成为fastcgi_path_info的值
                fastcgi_split_path_info ^(.+\.php)(/.+)$;
                fastcgi_pass unix:/run/php/php7.0-fpm.sock;
                fastcgi_index index.php;
                fastcgi_param SCRIPT_FILENAME $document_root$fastcgi_script_name;
                include fastcgi_params;
        }
```

`rewrite` 的四个 `flag`：

-  `last` 停止处理当前的 `ngx_http_rewrite_module` 的指令集，并开始搜索与更改后的 URL 相匹配的 location；
-  `break` 停止处理当前的 `ngx_http_rewrite_module` 指令集；
-  `redirect` 返回 302 临时重定向；
-  `permanent` 返回 301 永久重定向。

```bash
location / {
    rewrite ^/test1 /test2;
    # 终止执行后续 rewrite 模块指令，重写后的 url 为 /more/index.html
    rewrite ^/test2 /more/index.html break;  
    rewrite /more/index.html /test4;
    # 因为 proxy_pass 不是 rewrite 模块的指令，所以它不会被 break 终止
    proxy_pass https://www.baidu.com; 
}

# 发送如下请求
# curl 127.0.0.1:8080/test1 
# 代理到 百度产品大全页面： https://www.baidu.com/more/index.html;
```



## 同一个ecs下进行多个服务配置

在/etc/nginx/sites-avilable目录下创建文件，内容如下

配置一个反向代理的服务

```bash
# file_name one
server {
        listen 80;
        server_name domain.com;

        root /var/www/html/trans;
        index index.html index.js;
        location /api {
                add_header 'Access-Control-Allow-Origin' '*';
                #proxy_pass http://one.domain.com;
                # 末尾不加/会将匹配的/api也加在后面，即代理后的uri和请求的uri一致
                # 末尾加/就会将匹配到的/api去除，重定向后的uri为本次请求的uri去掉/api
                proxy_pass http://one.domain.com/;
                #rewrite ^/api(.*) $1 permanent;
        }
}
```

配置一个php-fpm应用

```bash
# file_name two
server {
        listen 80;
        server_name one.domain.com;

        root /var/www/html/seven/public;

        # Add index.php to the list if you are using PHP
        index index.php index.html index.htm;

        location / {
                try_files $uri $uri/ /index.php?$query_string;
        }
        # pass the PHP scripts to FastCGI server listening on 127.0.0.1:9000
        location ~ \.php$ {
                try_files $uri /index.php =404;
                fastcgi_split_path_info ^(.+\.php)(/.+)$;
                #include snippets/fastcgi-php.conf;
                # With php7.0-fpm:
                fastcgi_pass unix:/run/php/php7.0-fpm.sock;
                fastcgi_index index.php;
                fastcgi_param SCRIPT_FILENAME $document_root$fastcgi_script_name;
                include fastcgi_params;
        }
}
```

一个简单的静态资源服务器

```bash
# file_name three
server {
        listen 80;
        server_name three.domain.com;

        root /var/www/html/trans;
        index index.html index.js;
        # 通过定位静态文件位置，可以结局vue.js history模式下刷新路由失效问题
        location / {
                try_files $uri $uri/ /index.html;
        }
}
```

创建符号链接到``/etc/nginx/sites-enabled``目录下(需使用绝对路径)

```bash
ln -s /etc/nginx/sites-available/one /etc/nginx/sites-enabled/
ln -s /etc/nginx/sites-available/two /etc/nginx/sites-enabled/
ln -s /etc/nginx/sites-available/three /etc/nginx/sites-enabled/
```

删除或重命名defalut配置

测试配置，加载配置，重启服务器

```bash
sudo nginx -t
sudo nginx -s reload
sudo service nginx restart
```



nginx重定向的文章https://bjornjohansen.no/nginx-redirect

官方文档http://nginx.org/en/docs/http/ngx_http_fastcgi_module.html#fastcgi_split_path_info



## example1

在一台服务器和只有一个域名,将MySQL,redis,vue的spa程序,api全部放在了一台上面,由于只有一个域名且无法分出子域名,所以采取了vue spa默认使用80端口,请求直接倒过去,如果请求的是待``/api``的接口地址,将他rewrite到另一个端口,如8000,所以可以通过两个nginx的配置文件,在``/etc/nginx/sites/available``下

```nginx
# defalut的nginx配置
# 如果是/api开头,代理到8000端口
server {
        listen 80;

        server_name domain_name;

        root /var/www/html/vuespa;

        # Add index.php to the list if you are using PHP
        index index.html index.js;

        location /api {
                # First attempt to serve request as file, then
                # as directory, then fall back to displaying a 404.
                add_header 'Access-Control-Allow-Origin' '*';
                # 末尾不加/会将匹配的/api也加在后面，即代理后的uri和请求的uri一致
                # 末尾加/就会将匹配到的/api去除，重定向后的uri为本次请求的uri去掉/api
                proxy_pass http://127.0.0.1:8000;
                #rewrite ^/api(.*) $1 permanent;
        }

}
```



```nginx
# api 配置
# 在8000端口监听了一个php的api服务
server {
        listen 8000;

        server_name domain_name;

        root /var/www/html/api;

        # Add index.php to the list if you are using PHP
        index index.php index.html index.htm;

        location / {
                # First attempt to serve request as file, then
                # as directory, then fall back to displaying a 404.
                try_files $uri $uri/ /index.php?$query_string;
        }

        # pass the PHP scripts to FastCGI server listening on 127.0.0.1:9000
        #
        location ~ \.php$ {
                try_files $uri /index.php =404;
                fastcgi_split_path_info ^(.+\.php)(/.+)$;
                #include snippets/fastcgi-php.conf;
                # With php7.2-fpm:
                fastcgi_pass unix:/run/php/php7.2-fpm.sock;
                fastcgi_index index.php;
                fastcgi_param SCRIPT_FILENAME $document_root$fastcgi_script_name;
                include fastcgi_params;
        }
}

```

添加符号链接到``sites-enabled`` 必须使用绝对路径

```bash
ln -s /etc/nginx/sites-available/api /etc/nginx/sites-enabled/
ln -s /etc/nginx/sites-available/default /etc/nginx/sites-enabled/
```

老套路, 测试配置，加载配置，重启服务器

```bash
sudo nginx -t
sudo nginx -s reload
sudo service nginx restart
```

## nginx获取真实客户端地址

在前后端分离的情况下,由于api地址会通过nginx的前端服务器代理到api服务器上,导致默认获取的地址是前端服务器的地址

1. 在前端服务器nginx配置文件下添加:

   ```bash
   location /api { 
           rewrite  ^/api/(.*)$ /api/$1 break;
           proxy_pass   https://***.*********.com;
   }
   proxy_set_header X-Forwarded-For $remote_addr;
   proxy_set_header X-Forwarded-For $proxy_add_x_forwarded_for;
   ```

2. 在nginx的默认配置文件(一般在/etc/niginx/nginx.conf)中配置内存容量:

   ```bash
   http{
   ...
   proxy_headers_hash_max_size 51200;
   proxy_headers_hash_bucket_size 6400;
   ```

3. 重启服务器使得配置生效

   ```bash
   sudo nginx -t
   sudo nginx -s reload
   sudo service nginx restart
   ```

   