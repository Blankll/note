# PHP 源码安装

1. 下载源码包  

2. 解压 tar   xjvf 包名 

3. ./configure

4. apt-get install libxml2-dev

5. make && make install

6. 添加命令路径``~/.bash_profile``

   ```shell 
   alias php=目录/php/bin/php
   ```

7. 运行 source ~/.bash_profile

8. 在PHP安装好后可能没有php.ini文件，查看php.ini文件需要放置的位置 php -i | grep php.ini， 要将源码中的php.ini-development 复制到查到的目录下面，并重命名为php.ini



note 最好加上openssl、zlib这些库

##　openssl支持

1.先源码安装ｏｐｅｎｓｓｌ，下载openssl，解压（安装的默认路径是/usr/local/ssl，如果你想更改目录，请加上–prefix=/yourpath）

make

make install

创建符号链接

- ln -s /usr/local/ssl/bin/openssl /usr/bin/openssl  (将原来的备份即可）
- ln -s /usr/local/ssl/include/openssl /usr/include/openssl

刷新动态库配置 **vim /etc/ld.so.conf**

在文件末尾加入   **/usr/local/ssl/lib** 

动态刷新  **ldconfig**

安装完毕，**openssl version -a** 查看版本

# 安装配置curl

### **./configure –with-ssl=/usr/local/ssl**

（url安装到默认的目录/usr/local，或者youpath)

### make

### make install

### ldconfig

查看版本 curl -V 即可

安装完成后，源码编译安装php，将openssl指向ssl  ``我也不知道为什么要这个样子``

 ./configure --with-openssl=/usr/local/ssl/ 

 

## 添加mbstring扩展

1. 安装``autoconf`

   > ```shell
   > apt-get install autoconf
   > ```

2. 进入到ph源码目录/ext/mbstring,运行

   > phpize

3. 运行　./configure --with-php-config=/usr/local/bin/php-config 

4. make &&make install

 