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

## docker 守护进程

status docker 查看docker守护进程

sudo service docker start、restart 

docer启动配种文件  /etc/default/docker

ps -ef | grep docker

## image

1. docker rmi 删除镜像 一个一个的删除标签，删除完标签后，images也会被删除
2. docker rmi 删除镜像 一个一个的删除标签，删除完标签后，images也会被删除
3. docker rmi id 就会删除镜像，同时删除镜像对应的所有标签
4. dicker inspect 查看镜像的详细信息
5. docker tage 原来的镜像名 新镜像名 docker镜像重命名
6. docker rmi name 删除镜像

## 导入导出镜像

-a autthor

-m message

-p 不暂停运行的容器提交容器镜像

docker commit -a author -m smd name repository/images

docker build     --用docker file来构建镜像

## container => image

docker commit -m  ""   -a  ""   容器ID（可以简写）或容器名称 镜像名称:版本 　将现有容器打包成镜像

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


docker run --name mariadb -p 33061:3306 -p 8011:8011 -v /home/ubuntu/mariadbdata:/var/lib/mysql --privileged -v /home/ubuntu/mariadbcnf:/etc/mysql/conf.d --privileged -e MYSQL_ROOT_PASSWORD=password  -d mariadb:latest
```

```bash
docker run -it -d -p 8000:80 -p 33060:3306 -v /home/ubuntu/dev/translation/translate-backend/translate:/var/www/html --privileged --name translate-backend translate:v1 /bin/bash
```

```bash
docker run -d -it -p 8000:80 -p 33060:3306 -p 63790:6379 -p 8811:8811 -v /home/blank/code/translation/translate-backend:/var/www/html --privileged --name translate-dev translate:v2
```



### container => image

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

导入镜像

```bash
docker import image.tar
docker import可以重新指定镜像的名字，docker load不可以
docker save image > /home/image.tar.gz 导出镜像

docker load < /home/image.tar.gz 导入镜像

docker rmi images 删除镜像
```

###  save和export的区别

- save和export都能导出镜像包
- save 将container commit后的image 导出成压缩文件
- export可以直接将containner直接导出成压缩文件
- docker load用来载入镜像包，docker import用来载入容器包，但两者都会恢复为镜像；
- docker load不能对载入的镜像重命名，而docker import可以为镜像指定新名称。
- docker load不能载入容器包。

## 获取和推送镜像

docker search 查找镜像 或去docker  hub

推送镜像： docker push repository/imagename



## container

docker run -it -p 8000:80  -d image --name name  /bin/bash P(大写) 随机映射宿主机端口和容器端口

>  -d：启动守护式容器
>
> 守护式进程启动，--name为容器命名
>
>  -p -P 容器的端口映射
>
> -p: 指定映射端口 -p host:container
>
> -P 

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

docker top  name 查看运行中容器的情况

docker port web 查看web容器的端口映射

docker inspect web 查看容器的ip地址 

docker exec  在启动的容器中运行新的进程

docker stop docker kill 停止守护式进程容器



## tips

docker 下MySQL报错: No directory, logging in with HOME=/ 且数据库无法重启成功

```bash
usermod -d /var/lib/mysql/ mysql
service mysql start # 此时可以成功启动了
```

