# docker

依赖于linux内核特性： Namespace和ControlGroups

1. 将应用程序自动部署到容器
2. 简单轻量的建模方式
3. 职责逻辑分离
4. 快速高效的开发生命周期
5. 面向服务的架构
6. 开发，测试，部署服务
7. 创建隔离的运行环境
8. 搭建测试环境，集群部署测试

## docker的基本组成

docker client

docker Daemon

docker Image

docker Container

docker Registry

## docker安装

###将当前用户添加到docker用户组中

1. sudo groupadd docker
2. sudo gpasswd -a blank docker
3. sudo service docker restart
4. 注销当前用户重新登录

