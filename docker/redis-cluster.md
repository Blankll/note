# redis集群

## 集群方案

1. RedisClusster 官方，无中心节点，客户端与redis节点直连，不需要中间代理层，数据被分片存储 
   - 集群中的数据复制通过主从同步来实现
   - Master节点吧数据分发给Slave节点
   - 主从同步优势在于高可用，Redis节点有冗余设计
   - redis集群已改包含奇数个Master,至少应该有3个master
   - 每个Master节点都应该有Slave节点
2. Codis 中间件产品 存在中心节点
3. Twemproxy 中间件产品 存在中间节点

## 集群配置

1. 安装redis镜像

   ```shell
   docker pull redis
   
   ```

2. 创建docker容器

   ```shell
   docker run -it -d --name r1 -p 5001:6379 --net=net2 --ip 172.19.0.2 redis /bin/bash
   # 运行容器
   docker exec -it r1 /bin/bash
   ```

3. 修改配置文件，开启集群    ``/usr/redis/redis.conf``

   ```shell
   # 修改下列配置
   daemonize yes   # 以后台进程运行
   cluster-enabled yes # 开启集群
   cluster-config-file nodes.conf # 集群配置文件
   cluster-node-timeout 15000 # 超时时间
   appendonly yes # 开启AOF模式 日志功能
   ```

4. 运行redis

   ```shell
   # 进入/usr/redis/src
   ./redis-server ../resi.conf
   ```

5. 依次创建redis节点

6. 安装redis-trib.rb ``基于ruby的redis集群命令行工具``

   ```shell
   cp /usr/redis/src/redis-trib.rb /usr/redis/cluster/
   cd /usr/redis/cluster
   apt-get install ruby
   apt-get install rubygems
   gem install redis
   ```

7. 利用redis-trib.rb创建redis集群

   ```shell
   # 在redis容器内执行
   ./redis-trib.rb create --replicas 1 # 1表示一主一从
   # 这些是已经创建了的redis单节点,6个节点，3主3从
   172.19.0.2:6379
   172.19.0.3:6379
   172.19.0.4:6379
   172.19.0.5:6379
   172.19.0.6:6379
   172.19.0.7:6379
   ```

8. 连接redis集群

   ```shell
   # 进入到redis节点中
   docker exec -it r1 /bin/bash
   # 连接redis集群
   /usr/redis/src/redis-cli -c
   ```

9. 可以进行读写等操作