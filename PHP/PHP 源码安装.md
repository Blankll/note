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