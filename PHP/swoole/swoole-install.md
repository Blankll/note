# swoole 源码安装

1. 下载源代码，解压，
2. 运行phpize
3. ./configure --with-php-config=php的config文件
4. 在php.ini中添加extension=swoole.so

./configure --with-php-config=/usr/local/php
/bin/php-config --enable-openssl --enable-swoole-debug --enable-sockets --enable-http2 --enable-async-redis

## redis 源码安装

https://segmentfault.com/a/1190000003084917

## swoole重新编译加载异步redis

1. 进入之前解压好的源代码文件
2. ./configure --with-php-config=php的config文件　--enable-redis
3. make clean 清除上次编译产生的object文件
4. make -j
5. make install
6. php --ri swoole

