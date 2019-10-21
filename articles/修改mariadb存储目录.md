# 修改mariadb数据存储目录

## 实验配置信息

- os: Ubuntu-18.04LTS-x64
- db-version: MariaDB-10.1.41-x64

在默认情况下，mysql和Mariadb的数据库文件会存储在``/var/lib/mysql``目录下，很多时候可以直接使用，但是对于一些数据量比较大或者数据比较重要的线上系统中，很多都需要将数据存储在通过raid等组建的大容量且有恢复能力的磁盘阵列中，所以这段时间买来个某破产nas，然后用4块60块钱500G的西数蓝盘来组建了raid5磁盘阵列，然后将MySQL的数据目录更改到raid磁盘挂载的目录下，具体步骤如下：

假设我们的raid5磁盘阵列挂载在了/data/raid5目录下，注意，这里的数据盘最好不要挂在某个用户的home目录下，本人之前就是这么做的，结果mariadb无法启动老是permission denied，任由我 add user到MySQL的group里面去还是add MySQL 到用户的group里面都错误，其实也可以理解，数据盘应该是不关联登陆用户的，所以放在某个用户的目录下也是不妥的。有的人可能会说777不就行了嘛，但是在正式系统中，权限最好还是不要随便给，所以直接将raid盘挂在/目录下的一个文件目录下比较省心。操作流程如下：

1. 将/var/lib/mysql 目录的所有内容复制到/data/raid5目录下，``sudo cp -a /var/lib/mysql /data/raid5/``， -a的作用是保留原有的权限信息，同样也是保证更改目录后MySQL对应的目录和文件的权限和更改前一致，总之权限不要随便乱改，即复制后的目录结构为``/data/raid5/mysql``

   ```bash
   # /data/raid5/mysql
   ├── aria_log.00000001
   ├── aria_log_control
   ├── debian-10.1.flag
   ├── ibdata1
   ├── ib_logfile0
   ├── ib_logfile1
   ├── multi-master.info
   ├── mysql
   ├── mysql_upgrade_info
   ├── performance_schema
   ├── prophet
   └── tc.log
   ```

2. 将原来的文件目录更名为mysql.old。这并不是必须的，只是这样可以确保我们数据最后读取的是/data/raid/mysql下面的内容，同时可以备份数据库的初始化文件

3. 配置数据库配置文件。我们刚刚仅仅是拷贝了数据库需要使用的文件，但数据库并不知道我们希望它读取/data/raid5/mysql下的内容，需要进行一定的配置，安装好mariadb后配置文件默认存放在``/etc/mysql``中，目录结构如下

   ```bash
   /etc/mysql/
   ├── conf.d
   │   ├── mysql.cnf
   │   └── mysqldump.cnf
   ├── debian.cnf
   ├── debian-start
   ├── mariadb.cnf
   ├── mariadb.conf.d
   │   ├── 50-client.cnf
   │   ├── 50-mysql-clients.cnf
   │   ├── 50-mysqld_safe.cnf
   │   ├── 50-server.cnf
   │   └── 50-server.cnf.backup
   ├── my.cnf -> /etc/alternatives/my.cnf
   └── my.cnf.fallback
   ```

   MySQL会最先读取 ``/etc/my.cnf > /etc/mysql/my.cnf > /usr/etc/my.cnf > ~/.my.cnf ``

   我们一般配置都会在/etc/mysql目录下的配置文件中进行，在比较新的MySQL版本中，``/etc/mysql/my.cnf``中的配置内容其实很少(其实我也不晓得老版本是不是和新的不一样)，主要是去载入conf.d目录下的内容，如果是mariadb则也会载入mariadb的配置内容，如果安装的是maraidb则他的配置文件在mariadb.cnf，主要也是载入在mariadb.conf.d目录下的配置文件，我们常见的与服务有关的配置[mysqld]则默认是写在``mariadb.conf.d/50-server.cnf``中，这里配置了数据目录，日志位置, 内存配置等，其实，在我安装的这个版本中，my.cnf 和 mariadb.cnf内容是完全一样的，就是加载``/etc/mysql/conf.d/``, ``/etc/mysql/mariadb.conf.d/``这两个目录下的配置内容，我们既然使用了mariadb就在``mariadb.conf.d/50-server.cnf``这个文件中进行配置，修改``datadir``这一项即可

   ````bash
   # 将datadir配置指向之前拷贝好的raid磁盘目录下
   basedir  = /data/raid5/mysql
   ````

4. 重启MySQL服务，加载最新的配置

   ```bash
   sudo service mysql restart
   ```

不出意外，我们的MySQL数据库的数据存储目录就已经更改到了目标磁盘上。至于raid5其实也很简单，等过两天再写如何组建raid5磁盘阵列。