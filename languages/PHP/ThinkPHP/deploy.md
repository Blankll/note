# thinkPHP deploy

thinkPHP 的 nginx配置

```nginx
server {

        listen       80;

        server_name  zerg.geekfun.club;
        root        /var/www/html/zerg/public;
        index       index.php index.html index.htm;

        location / {
            if (!-e $request_filename) {
               rewrite  ^/(.*)$  /index.php/$1  last;
               break;
            }
        }

        location ~ \.php(/|$) {
            fastcgi_pass unix:/run/php/php7.3-fpm.sock;
            fastcgi_index  index.php;
            include        fastcgi.conf;
            set $fastcgi_script_name2 $fastcgi_script_name;
            if ($fastcgi_script_name ~ "^(.+\.php)(/.+)$") {
                set $fastcgi_script_name2 $1;
                set $path_info $2;
            }
            fastcgi_param   PATH_INFO $path_info;
            fastcgi_param   SCRIPT_FILENAME   $document_root$fastcgi_script_name2;
            fastcgi_param   SCRIPT_NAME   $fastcgi_script_name2;
            fastcgi_param  PHP_VALUE  "open_basedir=/var/www/html/zerg/:/tmp/:/proc/";
        }
}
```

## 开发环境php内置服务器启动

```bash
php -S 127.0.0.1:8088 -t public/
```

