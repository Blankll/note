# 高可用

增加系统冗余,保证发生系统不可用时可以尽快恢复

- 利用SUN共享存储或DRDB磁盘复制解决MySQL单点故障
- 利用多写集群来解决MySQL单点故障 - pxc



## MMM multi master replication manager

监控和管理MySQL的主主复制拓扑,并在主服务器失效时,进行主和主备服务器之间的主从切换和故障转移等工作

MMM监控MySQL主从复制健康情况

