PHP xdebug install

在docker下安装

```bash
RUN apk add autoconf gcc g++ make # 编译xdebug扩展需要的依赖
RUN  pecl install xdebug && docker-php-ext-enable xdebug # 安装以及让php加载xdebug

```

配置php.ini支持在container中远程调试

```bash
# 在php.ini中加入如下配置（3.xx版本，低版本略有不同）
xdebug.mode=debug
xdebug.start_with_request=yes
xdebug.client_host=host.docker.internal
```

vscode config：

```json
{
    "version": "0.2.0",
    "configurations": [
        {
            "name": "debug-docker",
            "type": "php",
            "request": "launch",
            "port": 9003,
            "pathMappings": {
                "/app": "${workspaceFolder}"
            }
        }
    ]
}
```

如果直接在宿主机上运行和调试，可以直接安装xdebug和修改本机php.ini配置文件。