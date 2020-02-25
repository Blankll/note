# PHP 源码安装

1. 下载源码包  

2. 解压 tar   xjvf 包名 

3. sudo apt-get install  sudo apt-get install libcurl3-openssl-dev

4. ./configure

   > ./configure --enable-mbstring --with-openssl
   >
   > 他会自己区找openssl的配置
   > --enable-debug关闭系统编译优化

5. apt-get install libxml2-dev

   还有许多扩展需要的库，参照：http://twosee.cn/2018/06/13/Ubuntu-PHP/

6. make && make install

7. 添加命令路径``~/.bash_profile``

   ```shell 
   alias php=目录/php/bin/php
   ```

8. 运行 source ~/.bash_profile

9. 在PHP安装好后可能没有php.ini文件，查看php.ini文件需要放置的位置 php -i | grep php.ini， 要将源码中的php.ini-development 复制到查到的目录下面，并重命名为php.ini



note 最好加上openssl、zlib这些库

##　openssl支持

1. apt-get  install -y libtool perl-core zlib-devel
2. 先源码安装openssl，下载openssl，解压（安装的默认路径是/usr/local/ssl，如果你想更改目录，请加上–prefix=/yourpath）

make

make install

移动文件或删除也可以

- mv /usr/bin/openssl /root/

创建符号链接

- ln -s /usr/local/bin/openssl /usr/bin/openssl

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

## phpize 

源码安装是自带phpize的，但如果用apt-get等来安装是不带phpize的，所以要安apt-get install php-dev

 