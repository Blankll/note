例如在大多数linux操作系统下一共有如下6个典型的运行级别：

0 停机 
 1 单用户，Does not configure network interfaces, start daemons, or allow non-root logins 
 2 多用户，无网络连接 Does not configure network interfaces or start daemons 
 3 多用户，启动网络连接 Starts the system normally. 
 4 用户自定义 
 5 多用户带图形界面 
 6 重启



/etc/rc0.d Run level 0 
/etc/rc1.d Run level 1 
/etc/rc2.d Run level 2 
/etc/rc3.d Run level 3 
/etc/rc4.d Run level 4 
/etc/rc5.d Run level 5 
/etc/rc6.d Run level 6



ls /etc/rc* 

对于以K开头的文件，系统将终止对应的服务；

对于以S开头的文件，系统将启动对应的服务；

```
Ubuntu默认是在runlevel 2启动
```