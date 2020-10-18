# Docker file

**FROM** 镜像

**WORKDIR** 指定工作目录，后面的命令都会默认在该目录下执行

**COPY** 复制host文件到image中

**ADD** 源地址可以为host地址也可以是url

**RUN** 在image build时执行的命令

**CMD** 容器运行时执行的命令，该命令执行完成，容器的生命周期变结束，通常会用一个阻塞命令如 tail一个file

**ENTRYPOINT**  类似CMD，　ENTRYPOINT非json则以ENTRYPOINT为准，如果ENTRYPOINT和CMD都是json则ENTRYPOINT + CMD 拼接成shell

**EXPOSE** 端口暴露，需要在container run的时候指定端口才可以使得host能够访问

**ENV** 环境变量，在image和container生命周期中存在

**ARG** 环境参数，只在image构建时存在

**LABLE** key=value 镜像标识，便于查找

**ONBUILD** 其他镜像FROM该镜像时ONBUILD指定的内容会有效

**SHELL** 指定容器运行的shell 默认/bin/sh （如可以修改成/bin/bash)



- 每条保留字指令都必须为大写字母且后面要跟至少一个参数
- 指令从上到下,顺序执行
- \#表示注释
- 每条指令都会创建一个新的镜像层,并对镜像进行提交 

 

> add 拷贝加解压
>
> copy 只拷贝,不解压