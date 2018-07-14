# 数据库集群搭建

常见的MySQL集群方案

1. Replication 速度快，弱一致性 单向异步复制
2. PXC(Percona XtraDB Cluster)速度慢，强一致性 多向同步复制

## PXC搭建流程

docker 中pxc无法映射目录文件，必须使用 docker卷

1. 下载或导入本地镜像

   ```shell
   --拉取镜像 
   docker pull percona/percona-xtradb-cluster
   --本地导入
   docker load < /home/file.tar.gz
   ```

2.  给PXC集群实例创建Docker内部网络 ``提高安全性``

   ```shell
   docker network create name
   ```

3. 创建docker卷

   ```shell
   docker volume create --name v1
   ```

4. 创建PXC集群主容器

   ```
   docker run -d -p 3306:3306 
   -e MYSQL_ROOT_PASSWORD=password
   -e CLUSTER_NAME=NAME
   -e XTRABACKUP_PASSWORD=xtrapassword
   -v v1:/var/lib/mysql 
   --privileged --name = node1 --net=net1 --ip 172.18.0.2 pxc
   ```

5. 创建集群节点 ``要等待主容器中的MySQL实例初始化完成之后才能创建其他集群节点``

   ```
   //节点2
   docker run -d -p 3307:3306 
   -e MYSQL_ROOT_PASSWORD=password
   -e CLUSTER_NAME=NAME
   -e XTRABACKUP_PASSWORD=xtrapassword
   -e CLUSTER_JJOIN=node1
   -v v2:/var/lib/mysql 
   --privileged --name = node2 --net=net1 --ip 172.18.0.3 pxc
   //节点3
   docker run -d -p 3308:3306 
   -e MYSQL_ROOT_PASSWORD=password
   -e CLUSTER_NAME=NAME
   -e XTRABACKUP_PASSWORD=xtrapassword
   -e CLUSTER_JJOIN=node1
   -v v3:/var/lib/mysql 
   --privileged --name = node3 --net=net1 --ip 172.18.0.4 pxc
   以此类推
   ```

   

## 数据库负载均衡[Paproxy]

1. 安装paproxy镜像

   ```shell
   docker pull haproxy
   ```

2. 创建Haproxy配置文件

   - 在宿主机创建一个文件，用于Haproxy配置文件

     > touch /home/solft/haproxy.cfg

   - 通过目录映射将宿主机配置文件映射到容器中

     > https://zhangge.net/5125.html

     编辑配置文件

     ```shell
     global
     	#工作目录
     	chroot /usr/local/etc/haproxy
     	#日志文件，使用rsyslog服务中local5日志设备（/var/log/local5），等级info
     	log 127.0.0.1 local5 info
     	#守护进程运行
     	daemon
     
     defaults
     	log	global
     	mode	http
     	#日志格式
     	option	httplog
     	#日志中不记录负载均衡的心跳检测记录
     	option	dontlognull
         #连接超时（毫秒）
     	timeout connect 5000
         #客户端超时（毫秒）
     	timeout client  50000
     	#服务器超时（毫秒）
         timeout server  50000
     
     #监控界面	
     listen  admin_stats
     	#监控界面的访问的IP和端口
     	bind  0.0.0.0:8888
     	#访问协议
         mode        http
     	#URI相对地址
         stats uri   /dbs
     	#统计报告格式
         stats realm     Global\ statistics
     	#登陆帐户信息
         stats auth  admin:abc123456
     #数据库负载均衡
     listen  proxy-mysql
     	#访问的IP和端口
     	bind  0.0.0.0:3306  
         #网络协议
     	mode  tcp
     	#负载均衡算法（轮询算法）
     	#轮询算法：roundrobin
     	#权重算法：static-rr
     	#最少连接算法：leastconn
     	#请求源IP算法：source 
         balance  roundrobin
     	#日志格式
         option  tcplog
     	#在MySQL中创建一个没有权限的haproxy用户，密码为空。Haproxy使用这个账户对MySQL数据库心跳检测
         option  mysql-check user haproxy
         server  MySQL_1 172.18.0.2:3306 check weight 1 maxconn 2000  
         server  MySQL_2 172.18.0.3:3306 check weight 1 maxconn 2000  
     	server  MySQL_3 172.18.0.4:3306 check weight 1 maxconn 2000 
     	server  MySQL_4 172.18.0.5:3306 check weight 1 maxconn 2000
     	server  MySQL_5 172.18.0.6:3306 check weight 1 maxconn 2000
     	#使用keepalive检测死链
         option  tcpka  
     ```

3. 创建Haproxy容器

   ```shell
   #create contianer
   # 3306向外提供服务；8888后台监控画面
   docker run -it -d -p 4001:8888 -p 4002:3306
   -v /home/soft/haproxy:usr/local/haproxy --name haproxy1 --privileged --net=net1 haproxy#最后这个是镜像的名字
   #进入容器
   docker exec -it h1 /bin/bash
   #在容器内执行如下命令，制定配置文件
   haproxy -f /usr/local/etc/haproxy/haproxy.cfg
   ```

4. 进入haproxy监控 ``浏览器 宿主机IP：4001/dbs``

   缺点：haproxy是单节点部署的，但凡有一个数据库节点宕机，这一整个节点都将无法使用

  解决方案：双机热备冗余

## Haproxy双机热备冗余

``虚拟ip`` Linux可以在一个网卡中设置多个ip地址，将ip地址分配给对应的多个程序

keepalived 抢占虚拟ip，抢到IP的为主服务器，没抢到的就变成备用服务器，两个服务器之间进行心跳检测，如果主服务器没有回应心跳检测，就备用服务器抢占IP成为主服务器。

### 双机热备实现步骤

1. 安装keepalived

   - keepalived必须要安装在haproxy所在的容器之中

   ```bash
   # 进入容器执行
   apt-get update
   apt-get install keepalived
   ```

   - keepalived 配置文件``/etc/keepalived/leepalived.conf``

     ```
     
     ```

     