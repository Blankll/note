# centos安装MySQL

在ubuntu下安装MySQL，mariadb都是十分方便，也可能是我比较经常使用ubuntu所以才这么觉得，今天帮个同学在centos上安装发现和ubuntu还是有一些差异，特意记录一下，说不定以后还要用到，所以就以一个ubuntu用户的角度来看看如何进行MySQL的安装

## 卸载旧版本

系统中可能会有旧版本的MySQL或者mariadb源存在或者本地已安装MySQL，所以需要先卸载和清除源，确保安装时不会产生冲突。

```bash
# 查看已安装的MySQL
yum list installed | grep mysql
# 卸载查询得到的MySQL
yum -y remove mysql-5.1.73-8.el6_8.x86_64 #根据上一个命令得到的版本进行删除
# 查看是否删除完毕，如果没有输出就表示已经删除完成
rpm -qa|grep mysql
# 查看系统中的MySQL源
yum list | grep mysql
# 删除旧版本的MySQL数据等内容，不删除可能导致新版本启动失败
sudo rm -rf /var/lib/mysql/*
```

## 添加MySQL仓库

由于Oracle的原因，现在好多发行版的默认数据库都设置成了mariadb，centos直接删除了MySQL源，所以直接yum MySQL是不行的，需要先添加MySQL的源。

```bash
# 更新操作
sudo yum update
# 添加源
cd /etc/yum.repos.d
wget http://dev.mysql.com/get/mysql57-community-release-el7-10.noarch.rpm
yum -y install mysql57-community-release-el7-10.noarch.rpm
```

以上的源是MySQL5.7，如果用户需要别的版本，也可以到``https://dev.mysql.com/downloads/repo/yum/``下载其他版本的源

## 安装MySQL

```bash
yum -y install mysql-community-server
```

## 启动MySQL

```bash
systemctl start  mysqld.service
## 其他参考命令
systemctl start  mysqld.service # 启动
systemctl status  mysqld.service # 查看状态
systemctl stop  mysqld.service # 停止
systemctl restart  mysqld.service # 重启
```



## root密码

MySQL会在第一次启动时生成一个随机的root@localhost的密码，记录在/var/log/mysqld.log中，我们可以通过如下命令获得密码

```bash
grep "password" /var/log/mysqld.log
```

当前的密码只是暂时的，用户需要使用该密码第一次登录MySQL时更改root用户的密码

```bash
# 登录MySQL，提示输入密码时输入查询到的密码
mysql -uroot -p
# 修改密码
ALTER USER 'root'@'localhost' IDENTIFIED BY 'new password';
```

在修改密码的过程中可能会遇到因为密码太简单而设置失败的错误，此时就有两个策略，修改密码使其满足或者更改MySQL的密码设置要求，我们是比较赞同设置比较复杂的密码，保证数据库安全的，如果要修该密码设置要求，可以进行如下操作：

```bash
set global validate_password_policy=0;
set global validate_password_length=1;
```

这样只要密码长度大于等于1就可以设置成功

这样就可以进行密码修改了。

