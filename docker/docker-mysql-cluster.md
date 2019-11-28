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

1. 安装haproxy镜像

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
     listen  admin_stats # 监控的名称
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
     listen  proxy-mysql #本组负载均衡的名称
     	#访问的IP和端口
     	bind  0.0.0.0:3306　#数据库集群访问入口  
         #网络协议　只能是tcp的
     	mode  tcp
     	#负载均衡算法
     	#轮询算法：roundrobin
     	#权重算法：static-rr
     	#最少连接算法：leastconn
     	#请求源IP算法：source 
         balance  roundrobin #轮询算法
     	#日志格式
         option  tcplog
     	#在MySQL中创建一个没有权限的haproxy用户，密码为空,
     	#Haproxy使用这个账户对MySQL数据库心跳检测
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

     ```shell
     vrrp_instance  VI_1 {
     	#keepalived 的身份 master为主服务器，backup为备份服务器，主服务器要抢占虚拟IP，备份服务器不会抢占虚拟IP，
     	# master服务器在没有抢到IP时会自动降级为slave
         state  MASTER
         # 规定虚拟网卡 eth0为docker的虚拟网卡
         interface  eth0
         # keepalived ID
         virtual_router_id  51
         # 权重，权重越大抢到的几率越大
         priority  100
         # 心跳检测间隔时间， 秒
         advert_int  1
         # 登录数据库服务器进行心跳检测，主从服务器验证方式，主备必须拥有相同的密码
         authentication {
             auth_type  PASS
             auth_pass  123456
         }
         # 虚拟IP
         virtual_ipaddress {
             172.18.0.201
         }
     }
     ```

2. 启动keepalived service keepalived start

3. 将docker虚拟IP映射到局域网内

   - 在宿主机上安装keepalived

     > sudo apt-get update
     > sudo apt-get install keepalived

   - 宿主机的keepalived设置 ``/etc/keepalived/``

     ```shell
     vrrp_instance VI_1 {
         state MASTER
         # 宿主机网卡
         interface ens33
         virtual_router_id 51
         priority 100
         advert_int 1
         authentication {
             auth_type PASS
             auth_pass 1111
         }
         #宿主机虚拟IP ip address
         virtual_ipaddress {
            	192.168.99.150
         }
     }
     
     # 转发IP
     virtual_server 192.168.99.150 8888 {
     	# 心跳检测 每隔3秒
         delay_loop 3
         # 轮训转发
         lb_algo rr 
         # nat模式
         lb_kind NAT
         # 超时时间
         persistence_timeout 50
         # 协议
         protocol TCP
     	# 转发 目标IP
         real_server 172.18.0.201 8888 {
             weight 1
         }
     }
     
     # 数据库
     virtual_server 192.168.99.150 3306 {
     	# 心跳检测 每隔3秒
         delay_loop 3
         # 轮训转发
         lb_algo rr
         # nat模式
         lb_kind NAT
         # 超时时间
         persistence_timeout 50
         # 协议
         protocol TCP
     	# 转发 目标IP
         real_server 172.18.0.201 3306 {
             weight 1
         }
     }
     ```


### 暂停PXC集群

1. 在/etc/sysctl.conf 中添加

   ```
   net.ipv4.ip_forward=1
   ```

2. systemctl restart network

## 热备份数据

LVM Linux自带的备份技术 备份时对数据库枷锁，只能读数据，不能写数据

XtraBackup 不需要锁表 免费的备份方案 percona 全量备份，增量备份 备份过程不会打断事物

全量备份： 备份全部数据 第一次采用全量备份

增量备份： 备份变化的数据， 给予第一次全量备份

### 流程

1. 删除原来的node1节点，重新挂载备份数据卷

   ```shell
   docker stop node1
   docker rm nod1
   docker run -d -p 3306:3306 -e MYSQL_ROOT_PASSWORD=password -e CLUSTER_NAME=pxc -e XTRABACKUP_PASSWORD=xpassword -v v1:/var/lib/mysql -v backup:/data --privileged -e CLUSTER_JOIN=node2 --name=node1 --net=net1 --ip 172.18.0.2 pxc
   ```

2. 在数据库节点中安装XtraBackup因为节点数据都一样的，所以在哪一个节点安装都是可以的

   ```shell
   # 新版本中已经默认安装,直接备份即可
   apt-get update
   apt-get install percona-xtrabackup-24
   # 进行第一次全量备份
   # /data/backup/full 备份的路径
   innobackupex --user=root --password=password /data/backup/full
   ```

3. 数据库可以热备份，但是不能进行热还原，

   - 用空白的MySQL还原数据，再建立pxc集群
   - 还原数据钱要将未提交的事物进行回滚， 还原数据之后重启MySQL

4. 还原数据库

   ```shell
   # 删除数据库数据
   rm -rf /var/lib/mysql/*
   # 回滚未提交数据
   innobackupex --user=root --password=password --apply-back /data/bacup/full/备份了的文件
   # 还原数据
   innobackupex --user=root --password=password --copy-back /data/bacup/full/备份了的文件
   ```



## 使用docker-compose

使用docker-compose可以简化命令行输入,节约部署时间和错误率,一下是部署以上无备份策略的pxc集群案例:

```yml
version: "3"
services:

  mysql-cluster-pxc-node1:
    image: percona/percona-xtradb-cluster
    container_name: mysql-cluster-pxc-node1
    ports:
      - 33061:3306
    volumes:
      - ./mysql-cluster-pxc-data1:/var/lib/mysql:rw
    networks:
      mysql-cluster-pxc:
        ipv4_address: 172.19.0.2
    environment:
      MYSQL_ROOT_PASSWORD: mysql-cluster-pxc&&0707
      CLUSTER_NAME: mysql-cluster-pxc
      XTRABACKUP_PASSWORD: xtrapassword&&0707
      MYSQL_USER: mysql-cluster-pxc
      MYSQL_PASSWORD: mysql-cluster-pxc&0707

  mysql-cluster-pxc-node2:
    depends_on:
      - "mysql-cluster-pxc-node1"
    image: percona/percona-xtradb-cluster
    container_name: mysql-cluster-pxc-node2
    ports:
      - 33062:3306
    volumes:
      - ./mysql-cluster-pxc-data2:/var/lib/mysql:rw
    networks:
      mysql-cluster-pxc:
        ipv4_address: 172.19.0.3
    environment:
      MYSQL_ROOT_PASSWORD: mysql-cluster-pxc&&0707
      CLUSTER_NAME: mysql-cluster-pxc
      XTRABACKUP_PASSWORD: xtrapassword&&0707
      MYSQL_USER: mysql-cluster-pxc
      MYSQL_PASSWORD: mysql-cluster-pxc&0707
      CLUSTER_JJOIN: mysql-cluster-pxc-node1

  mysql-cluster-pxc-node3:
    depends_on:
      - mysql-cluster-pxc-node1
    image: percona/percona-xtradb-cluster
    container_name: mysql-cluster-pxc-node3
    ports:
      - 33063:3306
    volumes:
      - ./mysql-cluster-pxc-data3:/var/lib/mysql:rw
    networks:
      mysql-cluster-pxc:
        ipv4_address: 172.19.0.4
    environment:
      MYSQL_ROOT_PASSWORD: mysql-cluster-pxc&&0707
      CLUSTER_NAME: mysql-cluster-pxc
      XTRABACKUP_PASSWORD: xtrapassword&&0707
      MYSQL_USER: mysql-cluster-pxc
      MYSQL_PASSWORD: mysql-cluster-pxc&0707
      CLUSTER_JJOIN: mysql-cluster-pxc-node1

  mysql-cluster-pxc-node4:
    depends_on:
      - mysql-cluster-pxc-node1
    image: percona/percona-xtradb-cluster
    container_name: mysql-cluster-pxc-node4
    ports:
      - 33064:3306
    volumes:
      - ./mysql-cluster-pxc-data4:/var/lib/mysql:rw
    networks:
      mysql-cluster-pxc:
        ipv4_address: 172.19.0.5
    environment:
      MYSQL_ROOT_PASSWORD: mysql-cluster-pxc&&0707
      CLUSTER_NAME: mysql-cluster-pxc
      XTRABACKUP_PASSWORD: xtrapassword&&0707
      MYSQL_USER: mysql-cluster-pxc
      MYSQL_PASSWORD: mysql-cluster-pxc&0707
      CLUSTER_JJOIN: mysql-cluster-pxc-node1

  mysql-cluster-pxc-node5:
    depends_on:
      - mysql-cluster-pxc-node1
    image: percona/percona-xtradb-cluster
    container_name: mysql-cluster-pxc-node5
    ports:
      - 33065:3306
    volumes:
      - ./mysql-cluster-pxc-data5:/var/lib/mysql:rw
    networks:
      mysql-cluster-pxc:
        ipv4_address: 172.19.0.6
    environment:
      MYSQL_ROOT_PASSWORD: mysql-cluster-pxc&&0707
      CLUSTER_NAME: mysql-cluster-pxc
      XTRABACKUP_PASSWORD: xtrapassword&&0707
      MYSQL_USER: mysql-cluster-pxc
      MYSQL_PASSWORD: mysql-cluster-pxc&0707
      CLUSTER_JJOIN: mysql-cluster-pxc-node1

  mysql-cluster-pxc-haproxy:
    image: haproxy
    container_name: mysql-cluster-pxc-haproxy
    volumes:
      - ./mysql-cluster-pxc-haproxy:/haproxy-override
      - ./mysql-cluster-pxc-haproxy/haproxy.cfg:/usr/local/etc/haproxy/haproxy.cfg
    ports:
      - 4001:4001
      - 4002:3306
    networks:
      mysql-cluster-pxc:
        ipv4_address: 172.19.0.7

networks:
  mysql-cluster-pxc:
    ipam:
      config:
        - subnet: 172.19.0.0/16

```

**notice**

在使用docker-compose的过程中,第二个开始的容器在第一个MySQL容器尚未运行成功就开始运行,使得在第一个MySQL尚未运行时创建的容器MySQL实例都无法启动,所以需要通过commander或重写entrypoint.sh:

参考:https://www.cnblogs.com/wang_yb/p/9400291.html



haproxy 配置文件

```cfg
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
listen  admin_stats # 监控的名称
	#监控界面的访问的IP和端口
	bind  0.0.0.0:4001
	#访问协议
    mode        http
	#URI相对地址
    stats uri   /dbs
	#统计报告格式
    stats realm     Global\ statistics
	#登陆帐户信息
    stats auth  admin:mysql-cluster-pxc-haproxy&0707
#数据库负载均衡
listen  proxy-mysql #本组负载均衡的名称
	#访问的IP和端口
	bind  0.0.0.0:3306　#数据库集群访问入口  
    #网络协议　只能是tcp的
	mode  tcp
	#负载均衡算法
	#轮询算法：roundrobin
	#权重算法：static-rr
	#最少连接算法：leastconn
	#请求源IP算法：source 
    balance  roundrobin #轮询算法
	#日志格式
    option  tcplog
	#在MySQL中创建一个没有权限的haproxy用户，密码为空,
	#Haproxy使用这个账户对MySQL数据库心跳检测
    option  mysql-check user haproxy
    server  MySQL_CLUSTER_PXC_1 172.19.0.2:3306 check weight 1 maxconn 2000  
    server  MySQL_CLUSTER_PXC_2 172.19.0.3:3306 check weight 1 maxconn 2000  
	server  MySQL_CLUSTER_PXC_3 172.19.0.4:3306 check weight 1 maxconn 2000 
	server  MySQL_CLUSTER_PXC_4 172.19.0.5:3306 check weight 1 maxconn 2000
	server  MySQL_CLUSTER_PXC_5 172.19.0.6:3306 check weight 1 maxconn 2000
	#使用keepalive检测死链
    option  tcpka 
```


