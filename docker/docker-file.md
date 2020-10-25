# Docker file

**FROM** 镜像

**WORKDIR** 指定工作目录，后面的命令都会默认在该目录下执行

**COPY** 复制host文件到image中

**ADD** 源地址可以为host地址也可以是url，如果复制的内容为压缩文件，会将内容进行解压

**RUN** 在image build时执行的命令，每一个run指令都会创建一个镜像的layer

**CMD** 容器运行时执行的命令，该命令执行完成，容器的生命周期变结束，通常会用一个阻塞命令如 tail一个file

**ENTRYPOINT**  类似CMD，　ENTRYPOINT非json则以ENTRYPOINT为准，如果ENTRYPOINT和CMD都是json则ENTRYPOINT + CMD 拼接成shell

如果cmd和entrypoint都每一指定，则继承父镜像的指令，若祖辈都没有指定cmd或entrypoint，则容器无法运行

**EXPOSE** 端口暴露，只将端口暴露给连接的服务，而不暴露给主机。需要在container run的时候指定端口才可以使得host能够访问，如果network为host模式，则会将端口随机绑定到host的端口上

**ENV** 环境变量，在image和container生命周期中存在，也可以在docker run中通过-e指定环境变量

**ARG** 环境参数，只在image构建时存在

**LABLE** key=value 镜像标识，便于查找

**ONBUILD** 其他镜像FROM该镜像时ONBUILD指定的内容会有效

**STOPSIGNAL** 指定特定信号使容器停止

**healthcheck** 容器健康配置

**SHELL** 指定容器运行的shell 默认/bin/sh （如可以修改成/bin/bash)



- 每条保留字指令都必须为大写字母且后面要跟至少一个参数
- 指令从上到下,顺序执行
- \#表示注释
- 每条指令都会创建一个新的镜像层,并对镜像进行提交 

 

> add 拷贝加解压
>
> copy 只拷贝,不解压