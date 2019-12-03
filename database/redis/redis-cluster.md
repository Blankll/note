## Redis Cluster

redis单机性能可以达到10万/每秒,redis cluster有效的解决了单机内存,并发,流量的瓶颈问题,达到负载均衡的目的

### 呼唤集群

1. 单机并发量无法满足业务需求
2. 单机内存无法满足业务需求
3. 单机网络带宽无法满足业务需求

### 数据分布

将数据分布到不同节点上,解决单机无法满足内存,并发,带宽等问题

- 顺序分布
- 哈希分布
  - 节点取余
  - 一致性哈希
  - 虚拟槽分区

| 分布方式 | 特点                                                    | 典型产品                                       |
| -------- | ------------------------------------------------------- | ---------------------------------------------- |
| 哈希分布 | 数据分散度高,键值分布业务无关,无法顺序访问,支持批量操作 | 一致性哈希 Memcache, rediscluster,其他缓存产品 |
| 顺序分布 | 数据分散一倾斜,键值业务相关,可顺序访问,不支持批量操作   | BigTable,HBase                                 |

**节点取余**

- 客户端分片:哈希+取余

- 节点伸缩:数据节点关系变化,导致数据迁移

- 迁移数量和添加节点数有关,翻倍扩容可以降低数据迁移的量级

**一致性哈希**

- 客户端分片: 哈希+顺时针(优化取余)
- 节点伸缩:只影响临近节点,单还是有数据迁移
- 翻倍伸缩:保证最小迁移数据和负载均衡

**虚拟槽分区(redis cluster默认方式)**

- 预设虚拟槽:每个槽映射一个数据子集,一般比节点数大
- 良好的哈希函数
- 服务端管理节点,槽和数据:Redis Cluster

### 集群搭建

原生命令安装

1. 配置开启节点

   ```bash
   cluster-enabled yes 
   cluster-config-file nodes-${pott}.conf
   cluster-node-timeout 15000 # 默认就好
   cluster-require-full-coverage yes # 有一个节点宕机,整个集群就不向外提供服务, 最好关闭
   ```

   开启配置号的多个节点

2. meet

   ```bash
   cluster meet ip port
   redis-cli -h 127.0.0.1 -p 7000 cluster meet 127.0.0.1 7001
   redis-cli -h 127.0.0.1 -p 7000 cluster meet 127.0.0.1 7001
   redis-cli -h 127.0.0.1 -p 7000 cluster meet 127.0.0.1 7002
   redis-cli -h 127.0.0.1 -p 7000 cluster meet 127.0.0.1 7003
   redis-cli -h 127.0.0.1 -p 7000 cluster meet 127.0.0.1 7004
   redis-cli -h 127.0.0.1 -p 7000 cluster meet 127.0.0.1 7005
   ```

   

3. 指派槽16384个槽 0~16383

   ```bash
   # 在目标节点上执行命令 根据节点数将16384做一个平均
   # 如下,有6个节点,三个分配slot,其余三个作为备份节点
   redsi-cli -h 127.0.0.1 -p 7000 cluster addslots {0...5461}
   redsi-cli -h 127.0.0.1 -p 7001 cluster addslots {5462...10922}
   redsi-cli -h 127.0.0.1 -p 7002 cluster addslots {10923...16383}
   ```

4. 设置主从

   ```bash
   # redis-cli -p 7000 cluster nodes 查看节点信息
   # redis-cli -p 7000 cluster slots 查看节点主从信息
   # cluster replicate node-id
   redis-cli -h 127.0.0.1 -p 7003 cluster replicate ${node-id-7000} # 将7003作为7000的slave节点
   redis-cli -h 127.0.0.1 -p 7004 cluster replicate ${node-id-7001} 
   redis-cli -h 127.0.0.1 -p 7005 cluster replicate ${node-id-7002} 
   ```

   官方安装工具基于ruby,简化了部署步骤

   cacheclud 可视化集群部署
   
5. redis 5.0后提供了内置的一键部署命令

   ```bash
   # 创建redis-cluster集群
   redis-cli --cluster create ip:port [ip:port] --cluster-replicas 1
   # 动态添加节点从节点
   redis-cli --cluster add-node new_ip:new_port exsist_ip:exsist_port
   # 给新添加的节点进行分片
   redis-cli --cluster reshard exsist_ip:exsist_port
   ```

### 集群伸缩

**集群扩容**

- 准备新节点

- 加入集群 meet

- 迁移槽和数据 

  - 槽迁移计划
  - 迁移数据
  - 添加从节点

  1. 在目标节点执行命令,让目标节点准备导入槽的数据

     ```bash
     cluster setslot {slot} importing {sourceNodeId}
     ```

  2. 在源节点执行命令,让源节点准备迁出槽的数据

     ```bash
     cluster setslot {slot} migrating {targetNodeId}
     ```

  3. 源节点循环执行,每次获取count个属于槽的键

     ```bash
     cluster getkeysinslot {slot} {count}
     ```

  4. 在员节点上执行命令将指定key迁移

     ```bash
     migrate {targetIp} {targetPort} key 0 {timeout}
     ```

  5. 重复步骤34直到槽下所有的键数据迁移到目标节点

  6. 向集群内所有主节点发送命令,通知槽分配给目标节点

     ```bash
     cluster setslot {slot} node {targetNodeId}
     ```

  或者使用官方工具

  ```
  ./redis-trib.rb reshard 127.0.0.1:7000
  ```

  

### 客户端路由

- moved 重定向
- ask重定向
- smart客户端 ``追求性能``
  1. 从集群中选一个可运行节点,使用cluster slots 初始化槽点和节点映射
  2. 将cluster slot的结果集映射到本地,为每个节点创建JedisPool
  3. 准备执行命令

**smart客户端使用**单例



### 集群原理

### 开发运维常见问题

#### 故障恢复

- 资格检查
- 准备选举时间
- 选举投票
- 替换主节点 
  1. 当前从节点取消复制变为主节点(slaveof no one)
  2. 执行clusterDelSlot 撤销故障主节点负责的槽,并执行clusterAddSlot把这些槽分配给自己
  3. 向集群广播自己的pong消息,表明已经替换了故障主节点

#### 带宽消耗

- 官方建议不要超过1000个节点
- ping/pong消息也占带宽
- 消息发送频率:节点发现他与其他节点最后通信时间超过cluster-node-timeout/2时会直接发送ping消息
- 消息数据量:slots槽数组(2kb空间)和整个集群1/10的状态数据(10个节点状态数据约为1kb)
- 节点部署的机器规模:集群分布的机器越多且每台机器划分的节点数越均匀,则集群整体的可用带宽越高

优化

- 避免"大"集群: 避免多个业务使用同一个集群,大业务可以划分出多个集群
- cluster-node-timeout: 带宽和故障转移速度的均衡,不能只考虑一个因素而调整这个参数
- 尽量均匀分配到多机器上

#### pub/sub广播在集群中存在的问题

- 问题: publish会在集群每个节点广播,加重带宽
- 解决: 单独"走"一套redis sentinel,与其他业务集群相分离

#### 集群倾斜

- 数据倾斜: 内存不均

  - 节点和槽的分配不均匀
  - 不同槽对应的键值数差异较大
  - 包含bigkey
  - 内存相关配置不一致

  定期检查配置的一致性

- 请求倾斜

## 缓存的使用与优化

### 缓存的受益与成本

受益

1. 加速读写
2. 降低后端负载:后端服务器如MySQL通过前端缓存降低负载

成本

1. 数据不一致:缓存层和数据层有时间窗口不一致
2. 代码维护成本
3. 运维成本

使用场景

1. 降低后端负载
2. 加速请求响应
3. 大量写合并为批量写:先写到缓存中,在同步到MySQL中

### 缓存更新策略

1. LRU/LFU/FIFO算法删除:如maxmemory-policy
2. 超时剔除: 如expire
3. 主动更新:开发控制生命周期
4. 数据一致性和维护成本的协调

### 缓存粒度控制策略

### 缓存穿透优化

1. 缓存空对象,避免过多击穿缓存去查询数据层
2. 布隆过滤器拦截

### 无底洞问题优化

节点越多,io操作次数增多,更多的机器并不一定意味着更高的性能	

1. 命令本身优化
2. 减少网络通信次数
3. 降低接入成本

### 缓存雪崩优化

### 热点key重建优化

目的

- 减少缓存的次数
- 数据尽可能一致
- 减少潜在危险

解决方案

- 互斥锁(mutex key)
- 永远不过期

