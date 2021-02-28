# redis持久化

## RDB(redis database)

快照，通过命令将redis内存中的数据完整的备份到硬盘的二进制文件中

恢复时（如重启） 将二进制文件加载到redis内存中

同时二进制文件也是一个redis数据复制的媒介 



触发机制

- save（同步）

- bgsave（异步）子进程执行

- 自动（频率太高会影响性能）

  ```bash
  save 900 1     # 900秒内数据发生一次修改时写入
  save 300 10    # 300秒内数据发生10次修改时写入
  save 60 10000  # 60秒内数据发生10000次修改时写入
  dbfilename dump.rdb
  dir ./  # 日志文件等存储路径
  stop-writes-on-bgsave-error yes # 写入发生错误时停止写入
  rdbcompression yes # 是否采用压缩格式
  rdbchecksum yes # 是否进行校验和检验
  ```

- 全量复制

- debug reload 

- shutdown



  最佳实践

- 关闭自动的save

  

- 集群中可以通过ip或者端口等对rdb文件进行区分

  ```bash
  dbfilename dump-${port}.rdb
  dir /bigdiskpath # 指定特定的保存地址
  stop-writes-on-bgsave-error yes # 建议开启 默认开启
  rdbcompression yes # 建议开启 默认开启
  rdbchecksum yes # 建议开启 默认开启
  ```

缺点：

- 耗时耗性能
- 不可控，容易丢失数据



## AOF(append only file)

写日志: 以独立日志的方式记录每次写命令,重启时再重新执行AOF文件中的命令达到恢复数据的目的

aof先写入到磁盘缓冲区中，然后再刷新到硬盘中

AOF三种策略

- always  每一条命令都刷新到硬盘中
- everysec 每秒刷新一次数据到硬盘 中
- no 根据操作系统的缓冲区情况来确定，缓冲区满时自动刷新到硬盘中

aof重写作用:去除无效命令,压缩空间,提高恢复速度

- 减少硬盘占用量
- 加速恢复速度

命令

``bgrewriteaof`` fork出子进程异步``aof``重写  将redis内存中的数据对aof文件进行回溯

如果当前进程正在执行bgsave操作,重写命令延迟到bgsave完成之后在执行

自动重写配置策略

```bash
# 配置策略
auto-aof-rewrite-min-size # 重写需要的最小尺寸 default 64MB
auto-aof-rewrite-percentage # aof增长率 default 100

# 统计策略
aof_current_size # aof当前尺寸
aof_base_size # aof上次启动和重写的尺寸
```

aof日志配置

```bash
appendonly yes
appendfilename "appendonly-${port}.aof"
appendfsync everysec
dir /bigdiskpath
no-appendfsync-on-rewrite yes
```

RDB 与 AOF

| 命令       | RDB    | AOF          |
| ---------- | ------ | ------------ |
| 启动优先级 | 低     | 高           |
| 体积       | 小     | 大           |
| 恢复速度   | 快     | 慢           |
| 数据安全性 | 丢数据 | 根据策略决定 |
| 轻重       | 重     | 轻           |

最佳策略

小分片

### 持久化流程

- AOF持久化开启且存在AOF文件时优先加载AOF文件
- AOF关闭或AOF文件不存在时加载RDB文件
- 加载AOF/RDB文件成功后,Redis启动成功
- AOF/RDB文件存在错误时,Redis启动失败并打印错误信息

## redis复制原理与优化

主从复制：备份，读写分离 

**生产环境中不要在一台主机上配置多个redis节点**

一主一从

一主多从

数据流向是单向的，只能从master流向slave

设置

redis主从

在1127.0.0.1::6380上执行命令 ``slaveof 127.0.0.1:6379`` 将6380设置为6379的slave节点

在1127.0.0.1::6380上执行命令 ``slaveof no one``取消主从关系

修改redis配置

```bash
slaveof ip port # 配置为目标节点的slave节点
slave-read-only yes # 从节点只做数据读取
```

**复制偏移量:**通过对比master和slave的偏移量判断数据是否一致

- 参与复制的主从节点都会维护自身复制偏移量
- master处理完写入命令后将命令的字节长度做累加记录在info replication 的master_repl_offset中
- slave每秒上报自身复制偏移量给master,master会保存slave的复制偏移量
- slave收到master发送的命令后会累加自身能的偏移量,记录在info replication 的slave_repl_offset中

