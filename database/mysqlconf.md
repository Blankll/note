# mysql conf



## mysql配置选项表

```
mysql --verbose --help | grep -A 1 'Default options'
```



加载顺序：/etc/my.cnf   /etc/mysql/my.cnf  ~/.my.cnf

以下是my.cnf配置文件参数解释：

[client]
port = 3306 #端口号
socket = /tmp/mysql.sock #socket所在路径
[mysqld]
!include /home/mysql/etc/mysqld.cnf #包含的配置文件 ，把用户名，密码文件单独存放
port = 3306
socket = /tmp/mysql.sock
pid-file = /home/mysql/var/mysql.pid#进程pid
basedir = /home/mysql/#mysql的安装路径
datadir = /home/mysql/var/ #数据文件所在路径
tmpdir = /home/mysql/tmp/#临时文件保存路径
slave-load-tmpdir=/home/mysql/tmp#当slave执行load data infile时用
skip-name-resolve#grant时，必须使用ip不能使用主机名
skip-symbolic-links#不能使用连接文件
skip-external-locking#不指定系统锁定
back_log = 50 #接受队列，对于没建立 tcp 连接的请求队列放入缓存中，队列大小为 back_log，受限制与 OS 参数
max_connections = 1000 #最大并发连接数 ，增大该值需要相应增加允许打开的文件描述符数
max_connect_errors = 10000 #如果某个用户发起的连接 error 超过该数值，则该用户的下次连接将被阻塞
open_files_limit = 10240#打开文件限制
connect-timeout = 10 #连接超时之前的最大秒数
wait-timeout = 28800 #等待关闭连接的时间
interactive-timeout = 28800 #关闭连接之前，允许 interactive_timeout（取代了wait_timeout）秒的不活动时间。
slave-net-timeout = 600#从服务器超过slave_net_timeout 秒没有从主服务器收到数据才通知网络中断
net_read_timeout = 30 #从服务器读取信息的超时
net_write_timeout = 60 #从服务器写入信息的超时
net_retry_count = 10 #如果某个通信端口的读操作中断了，在放弃前重试多次
net_buffer_length = 16384 #包消息缓冲区初始化字节
table_cache = 512 #所有线程打开的表的数目
thread_stack = 192K #每个线程的堆栈大小
thread_cache_size = 20 #线程缓存
thread_concurrency = 8 #同时运行的线程的数据 此处最好为 CPU 个数两倍。
query_cache_size = 256M #查询缓存大小
query_cache_limit = 2M #不缓存查询大于该值的结果
query_cache_min_res_unit = 2K #查询缓存分配的最小块大小
default_table_type = INNODB#默认表存储引擎
default-time-zone = system #服务器时区
character-set-server = utf8 #server 级别字符集
default-storage-engine = InnoDB #默认存储
tmp_table_size = 512M #临时表大小
log-bin = mysql-bin #打开binlog
log-bin-index = mysql-bin.index
relay-log = relay-log
relay_log_index = relay-log.index
log-error = /home/mysql/log/mysql.err#错误文件路径
log_output = FILE #慢查询输出格式
slow_query_log = 1
long-query-time = 1 #慢查询时间 超过 1 秒则为慢查询
slow_query_log_file = /home/mysql/log/slow.log#慢查询存储路径
general_log = 1
general_log_file = /home/mysql/log/mysql.log#一般查询存储路径
max_binlog_size = 1G#最大binlog
max_relay_log_size = 1G#最大relaylog
relay-log-purge = 1 #当不用中继日志时，删除他们。这个操作有 SQL 线程完成
expire_logs_days = 30 #超过 30 天的 binlog 删除
binlog_cache_size = 1M #session 级别
replicate-wild-ignore-table = mysql.% #复制时忽略数据库及表
replicate-wild-ignore-table = test.% #复制时忽略数据库及表
key_buffer_size = 256M#查询排序时所能使用的缓冲区大小
sort_buffer_size = 2M #排序 buffer 大小
read_buffer_size = 2M #读查询操作所能使用的缓冲区大小
join_buffer_size = 8M # join buffer 大小
query_cache_size = 64M#指定 MySQL 查询缓冲区的大小
read_rnd_buffer_size = 8M#随机读缓存大小
innodb_file_per_table#独立表空间
innodb_additional_mem_pool_size = 100M#附加的内存池
innodb_buffer_pool_size = 2G #缓冲池
innodb_data_file_path = ibdata1:1G:autoextend#表空间，自动递增
innodb_file_io_threads = 4 #io 线程数
innodb_thread_concurrency = 16 #并发线程数
innodb_flush_log_at_trx_commit = 1#刷新事务日志到磁盘
innodb_log_buffer_size = 8M #事物日志缓存
innodb_log_file_size = 500M #事物日志大小
innodb_log_files_in_group = 2 #两组事物日志
innodb_log_group_home_dir = /home/mysql/var/#日志组
innodb_max_dirty_pages_pct = 90 #innodb 主线程刷新缓存池中的数据，使脏数据比例小于 90%
innodb_lock_wait_timeout = 50 #InnoDB 事务在被回滚之前可以等待一个锁定的超时秒数
innodb_flush_method = O_DSYNC  # InnoDB 用来刷新日志的方法
innodb_force_recovery=1#导出表空间损坏的表
innodb_fast_shutdown#加速innodb关闭
max_allowed_packet = 64M#最大允许的包大小
[mysql]
default-character-set = utf8
connect-timeout = 3
[mysqld_safe]
open-files-limit  = 8192#可打开文件数量



- sync_binlog 控制MySQL如何向磁盘刷新binlog 默认为0,有操作系统缓存策略进行同步
- max_connections 100 控制允许的最大连接数量