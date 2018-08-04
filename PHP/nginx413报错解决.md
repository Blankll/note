# nginx413报错解决

今天，其实是好几次都是在上传文件和图片时会发生４１３报错或者图片上传失败，总结一下：

报413是因为上传的图片或文件太大，而nginx的默认上传大小是１MB,所以，首先要更改nginx的配置项，配置文件路径一般为``/etc/nginx/nginx.conf``

```shell
http {

        ##
        # Basic Settings
        ##

        sendfile on;
        tcp_nopush on;
        tcp_nodelay on;
        keepalive_timeout 65;
        types_hash_max_size 2048;
        # server_tokens off;
        
        # server_names_hash_bucket_size 64;
        # server_name_in_redirect off;

        include /etc/nginx/mime.types;
        default_type application/octet-stream;

        ##
        # SSL Settings
        ##
		......
}
```

默认可能没有`` client_max_body_size``的选项，所以在http其中的大括号内添加

```shell
client_max_body_size 20M;
```

然后重启nginx，在终端运行``sudo service nginx restart``这样413应该就不会在出现了

但这样不一定就可以上传成功，图片还可能超过php-fpm设置的上限,修改配置，目录下的php7.0-fpm(版本不一样要改，路径与自己安装时设置的路径有关),如ubuntu下7.0的默认安装在``/etc/php/7.0/fpm``下，修改该目录下的两个设置：

```shell
upload_max_filesize = 20M  
post_max_size = 20M
```

保存后重启php-fpm　``service php7.0-fpm rstart``

这样就可以正常上传大文件了，

### 但是

文件上传的体积一定要考虑到服务器自身的存储空间和带宽，以及用户的带宽，如果服务器带宽本来就小，上传大文件的用户体验是很差的，如果是上传图片，用户浏览图片加载速度太慢也十分影响使用体验。