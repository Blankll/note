

## 构建本地RocketMQ集群

| id   | ip              | desc       |
| ---- | --------------- | ---------- |
| 1    | localhost:9876  | nameserver |
| 2    | localhost:9875  | nameserver |
| 3    | localhost:10911 | master1    |
| 4    | localhost:10910 | master2    |
| 5    | localhost:11011 | slave1     |
| 6    | localhost:11010 | slave2     |

master1

```bash
# vim ~/dev/dubbostudy/rocketmq-all-4.7.0-bin-release/conf/dubbostudy-2m-2s-async/broker-a.properties
# limitations under the License.
brokerClusterName=DubboRocketCluster
brokerName=broker-a
brokerId=0
namesrvAddr=localhost:9876;localhost:9875
# 是否允许brocker自动创建topic,建议线上关闭
autoCreateTopicEnable=true
# 在发送消息时自动创建服务器不存在的topic,默认创建的队列数
defaultTopicQueueNums=4
# 是否允许不容错客人自动创建订阅组,建议线上关闭
autoCreateSubscriptionGroup=true
# brocker服务监听端口
listenPort=10911
# 文件删除时间点,凌晨4点
deleteWhen=04
# 文件保留时间48小时
fileReservedTime=48
# brocker角色
brokerRole=ASYNC_MASTER
# 刷盘方式
flushDiskType=ASYNC_FLUSH
```

slave1

```bash
brokerClusterName=DubboRocketCluster
brokerName=broker-b
brokerId=1
namesrvAddr=localhost:9876;localhost:9875
# 是否允许brocker自动创建topic,建议线上关闭
autoCreateTopicEnable=true
# 在发送消息时自动创建服务器不存在的topic,默认创建的队列数
defaultTopicQueueNums=4
# 是否允许不容错客人自动创建订阅组,建议线上关闭
autoCreateSubscriptionGroup=true
# brocker服务监听端口
listenPort=1011
# 文件删除时间点,凌晨4点
deleteWhen=04
# 文件保留时间48小时
fileReservedTime=48
# brocker角色
brokerRole=SLAVE
# 刷盘方式
flushDiskType=ASYNC_FLUSH
```

master2

```bash
brokerClusterName=DubboRocketCluster
brokerName=broker-b
brokerId=0
namesrvAddr=localhost:9876;localhost:9875
# 是否允许brocker自动创建topic,建议线上关闭
autoCreateTopicEnable=true
# 在发送消息时自动创建服务器不存在的topic,默认创建的队列数
defaultTopicQueueNums=4
# 是否允许不容错客人自动创建订阅组,建议线上关闭
autoCreateSubscriptionGroup=true
# brocker服务监听端口
listenPort=10910
# 文件删除时间点,凌晨4点
deleteWhen=04
# 文件保留时间48小时
fileReservedTime=48
# brocker角色
brokerRole=ASYNC_MASTER
# 刷盘方式
flushDiskType=ASYNC_FLUSH
```

slave2

```bash
brokerClusterName=DubboRocketCluster
brokerName=broker-b
brokerId=1
namesrvAddr=localhost:9876;localhost:9875
# 是否允许brocker自动创建topic,建议线上关闭
autoCreateTopicEnable=true
# 在发送消息时自动创建服务器不存在的topic,默认创建的队列数
defaultTopicQueueNums=4
# 是否允许不容错客人自动创建订阅组,建议线上关闭
autoCreateSubscriptionGroup=true
# brocker服务监听端口
listenPort=1010
# 文件删除时间点,凌晨4点
deleteWhen=04
# 文件保留时间48小时
fileReservedTime=48
# brocker角色
brokerRole=SLAVE
# 刷盘方式
flushDiskType=ASYNC_FLUSH
```

nameserver1

```bash
listenPort=9876
```

nameserver2

```bash
listenPort=9875
```

## 启动服务

进入rocketmq所在目录



1. 启动NameServer

   ```bash
   nohup sh rocketmq/bin/mqnamesrv -c rocketmq/conf/namesrv-1.properties
   nohup sh rocketmq/bin/mqnamesrv -c rocketmq/conf/namesrv-2.properties
   ```

2. 启动broker

   ```bash
   nohup sh rocketmq/bin/mqbroker -c rocketmq/conf/broker-a.properties &
   nohup sh rocketmq/bin/mqbroker -c rocketmq/conf/broker-b.properties &
   ```

3. 启动slave

   ```bash
   nohup sh rocketmq/bin/mqbroker -c rocketmq/conf/broker-a-s.properties &
   nohup sh rocketmq/bin/mqbroker -c rocketmq/conf/broker-b-s.properties &
   ```

4. RocketMQ console

   ```bash
   git clone https://github.com/apache/rocketmq-externals
   cd rocketmq-console
   mvn clean package -Dmaven.test.skip=true
   ```

   注意：打包前在```rocketmq-console```中配置```namesrv```集群地址：

   ```bash
   rocketmq.config.namesrvAddr=192.168.25.135:9876;192.168.25.138:9876
   ```

   启动rocketmq-console

   ```bash
   java -jar rocketmq-console-ng-1.0.0.jar
   ```

   浏览器访问`http://localhost:8080`进入控制台界面  

一个生产者组，代表着一群topic相同的Producer。即一个生产者组是同一类Producer的组合。

一个消费者组，代表着一群topic相同，tag相同（即逻辑相同）的Consumer。   