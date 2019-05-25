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

## linux 防火墙管理

控制互联网和程序访问

## 容器创建于操作

docker run -it -p 8000:80  -d image --name name  /bin/bash P(大写) 随机映射宿主机端口和容器端口

docker run -it --name name -d -p 宿主机端口:容器端口 p(小写) 将指定的宿主机端口映射到容器端口上

docker run -it --name -d -p 8080:80 -p 9001:3306 -v 宿主机目录:容器目录  --privileged  /bin/bash 目录映射 授予权限级别-->容器对挂载目录的权限级别 不写的话默认权限是读写 --privileged :拥有最高权限

docker pause name 暂停容器

docker unpause name 开启容器

docker stop name 停止容器

docker start -i name 启动容器

docker rm name 删除容器

docker rmi name 删除镜像

docker tage 原来的镜像名 新镜像名    docker镜像重命名

docker network create name 创建docker实例内部网络

docker network create --subnet = 172.18.0l0/24 网段/子网掩码24位 

docker network inspect name 查看网段相关信息

docker network rm name 删除指定网段

docker volume create --name name 创建docker卷

docker volume rm name 删除数据卷



container => image

docker commit -m  ""   -a  ""   容器ID（可以简写）  镜像名称 　将现有容器打包成镜像

> -a 作者
>
> -m　提示信息

```shell
 docker run -it -d -p 80:80 -p 3306:3306 -p 6379:6379 -p 8000:8000 -p 8888:8888 -v /home/seven/dev/blog:/var/www/html --privileged --name blog2 ubuntu /bin/bash
```

```bash
docker run -it -d -p 80:80 -p 3306:3306 -p 6379:6379 -p 8811:8811 -v /home/seven/dev/blog2:/var/www/html --privileged --name blog seven/blog /bin/bash
```

```bash
seven@Blank:~$ docker run --name yunjie-mysql -v /home/seven/dev/YunJie3.7.1_for_linux/mysqldocker:/etc/mysql/conf.d --privileged -p 33060:3306 -e MYSQL_ROOT_PASSWORD=0707 -d mysql:5.7
```

```bash
docker run -it -d -p 8000:80 -p 33060:3306 -v /home/ubuntu/dev/translation/translate-backend/translate:/var/www/html --privileged --name translate-backend translate:v1 /bin/bash
```



## 导入导出镜像

container => image

```bash
docker commit -a 'seven' -m 'translate container' ecca74dd9a76 translate:v1
```

image => tar

```bash
docker save image_name > name.tar # 导出镜像,在当前文件夹
docker save translate:v1 > dockertaes.tar
docker save -o target_dir/name.tar image_name:tag # 导出镜像到指定文件夹
docker save -o /home/seven/dockerimages/mytest.tar translate:v1 


docker export -o name.tar container_id
docker export -o /home/seven/dockerimages/port.tar ecca74dd9a76
```

## dockerfile

- 每条保留字指令都必须为大写字母且后面要跟至少一个参数
- 指令从上到下,顺序执行
- \#表示注释
- 每条指令都会创建一个新的镜像层,并对镜像进行提交 

 

> add 拷贝加解压
>
> copy 只拷贝,不解压