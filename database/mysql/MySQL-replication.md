# MySQL 复制

复制实现了在不同服务器上的数据分别，利用二进制日binlog进行增量复制，不需要太多的带宽，可以通过负载降低数据库的读取压力，

**MySQL5.7之前，一个从库只能有一个主库, 5.7之后支持一从多主架构，**

```bash
show variables lik 'binlog_format' # 查看当前数据库日志格式
set session binlog_format=statement # 设置binlog日志模式
```

![MySQL level](../../statics/database/mysql-level.png)

MySQL日志：

- 服务层日志：
  - binlog(二进制日志)
  - 慢查询日志
  - 通用日志
- MySQL存储引擎日志(Innodb)
  - redolog(重做日志)
  - 回滚日志

MySQL二进制日志

- ``STATEMENT``基于段的格式：binlog_format=STATEMENT(存储Mysql每一个事件执行SQL语句)（5.7之前的日志）

  - 日志记录量相对较小，节约磁盘及网络I/O

  - 必须记录上下文信息，非确定函数无法复制

- ``ROW``基于行的日志格式：binlog_format=ROW(5.7之后的默认)

  - 使MySQL主从复制更加安全

  - 对每一行数据的修改比基于段的复制高效

  - 日志记录较大

    binlog_row_image=[FULL|MINIMAL|NOBLOB]

    - 完全记录整列，包括没有修改的，
    - 只记录修改的数据
    - 不记录未修改的blob数据

- ``MIXED``混合日志格式：binlog_format=MIXED

  - 根据sql语句由系统决定使用何种日志格式

## MySQL复制

- 基于SQL语句的复制(SBR)

  二进制日志格式使用statement格式

- 基于行的复制(RBR)

  二进制日志格式使用row格式

- 混合模式

  根据实际内容在以上两者之间切换



1. master将变更写入二进制日志
2. 从master读取二进制日志吸入到relay_log中
3. slave重放relay_log中的日志



## MySQL主从复制建立

- 在master DB服务器上建立复制日志用户

- 授予REPLICATION SLAVE 权限

  ```BASH
  GRANT REPLICATION SLAVE ON *.* TO 'repl'@'ip';
  ```

- 配置master数据库服务器

  ```bash
  sync_binlog=1
  bin_log = mysql-bin # 二进制日志名称
  server_id = 100 # 在整个复制集群中唯一
  ```

- 配置slave服务器

  ```bash
  bin_log = mysql-bin # 二进制日志名称
  server_id = 101 # 在整个复制集群中唯一
  relay_log = mysql-relay-bin # relay log 的名称 中继日志
  log_slave_update = on # 是否sql线程重放的中继日志记录到slave的binlog中，如果要使用slave作为其他节点的master进行复制（链路复制），必须开启
  read_only= on # 保证从服务器数据只读
  ```

- 初始化从服务器数据

  备份master数据库 mysqldump  --master-data -single-transaction

  xtrabackup --slave-info # innodb下

- slave启动数据同步

  ```bash
  CHANGE MASTER TO 
  MASTER_HOST = 'MASTER_IP', 
  MASTER_USER 'repl',
  MASTER_PASSWORD='repl_password', 
  MASTER_LOG_FILE='mysql_log_file_name',
  MASTER_LOG_POS=4;
  ```

start slave; # 启动
  show processlist; # 显示线程
  ```
  
  


  ```

### 基于GTID复制

GTID全局事务id， GTID=source_id:transaction_id

## MySQL复制拓扑

- 主从复制

  - 不同的业务可以使用不同的从库
  - 将一台从库放到远程IDC，用作灾备恢复
  - 分担主库的读负载

- 主主复制

  - 缺陷较大，插入操作频繁会发生复制中断

  - 最好两个主中所操作的表是不同的表

  - 分开两个表i自增d生成的值

    ```bash
    # 自增id的步长
    auto_increment_increment = 1 | 2
    # id开始位置
    auto_increment_offset = 1 | 2
    ```

- 主备切换

  两个主服务器同一时间只有一台服务器作为主服务器对外提供服务，另外一台服务器处于只读状态并且只作为热备使用，在主库发生故障或者计划性维护时进行主备切换，原来使用的主库成为备库，备库成为新的主库。