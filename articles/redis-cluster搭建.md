# 构建Redis 集群

在redis中，主要有三种方式构建高性能的分布式redis服务，master-slave读写分离的模式，S二厅饿了模式以及Redis3.2之后的Redis Cluster，他们之间各有优劣，在实际业务中需要根据具体的需求进行选择。下文将简述三种模式以及具体的搭建步骤。

## Redis 读写分离

​	这种模式与Mysql的主从复制读写分离类似，在redis中，数据以RDB和AOF的形式进行持久化存储，RDB是以二进制数据格式保存redis内存数据到磁盘进行持久化的默认存储形式，在Redis1.1版本之后添加了AOF(Append Only File)以日志的形式记录Redis的写操作，弥补RDB数据一致性缺陷。在Redis的复制中主要通过RDB文件进行Redis实例之间的数据复制。

Redis 读写分离集群的主要优势在于可以进行对master节点的备份，在master节点发生宕机时将salve升级为主节点继续提供服务，同时可以通过将读操作分散到save节点上实现读写分离，减轻master的压力。

要构建读写分离的Redis数据库集群，我们需要先下载Redis的执行文件，可以直接在[Redis官网下载](https://redis.io/),也可以在Redis的GitHub仓库下载源代码，进行编译安装[Redis GitHub](https://github.com/antirez/redis)

```bash
# 通过git下载Redis源代码
git clone git@github.com:antirez/redis.git
```

