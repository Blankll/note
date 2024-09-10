# Elasticsearch 入门实践 - 安装

我将开启一个Elasticsearch 入门的系列，带大家入门Elasticsearch，将覆盖安装部署，特性解读，查询剖析，数据管理，集群运维等开发中必备的知识点，让大家可以对Elasticsearch有必要的知识储备，轻松应对未来的大数据开发，但并不会深入源码细节，更加关注怎么去使用Elasticsearch， 如果你正在学习Elasticsearch或者想巩固Elasticsearch的知识，记得持续关注哦！

## Elasticsearch 安装

在开始介绍Elasticsearch概念已经基础查询之前，让我们先来安装Elasticsearch，作为我们的学习前的准备，我将介绍几种不同的方式。

### 1. Docker 极速安装

通过Docker，我们可以快速在本地启动一个Elasticsearch实例作为我们的实验环境，该操作要求提前安装好Docker，安装步骤可以参考[官网](https://docs.docker.com/get-started/introduction/get-docker-desktop/)

1. 在terminal中执行如下命令创建并启动Elasticsearch:

   ```bash
   docker run --name elasticsearch-learn -p 9200:9200 -p 9300:9300 -e "discovery.type=single-node" -e "xpack.security.enabled=false" elasticsearch:8.15.1
   ```
   
   一些有用的Docker 命令
   
   - 停止容器运行：CTR+C/CMD+C 或者执行`docker stop elasticsearch-learn`
   - 启动容器：`docker start elasticsearch-learn`
   - 重新创建容器： 停止容器后执行删除 `docker rm elasticsearch-learn`,暂执行创建命令
   
2. 检测Elasticsearch运行状态，发送一个get请求到端口9200

   ```bash
   curl http://localhost:9200
   ```

   应当返回类似如下的JSON

   ```json
   {
     "name" : "3c3bee97c6b5",
     "cluster_name" : "docker-cluster",
     "cluster_uuid" : "QDkITZCqQQi9XNOT85-OTA",
     "version" : {
       "number" : "8.15.1",
       "build_flavor" : "default",
       "build_type" : "docker",
       "build_hash" : "253e8544a65ad44581194068936f2a5d57c2c051",
       "build_date" : "2024-09-02T22:04:47.310170297Z",
       "build_snapshot" : false,
       "lucene_version" : "9.11.1",
       "minimum_wire_compatibility_version" : "7.17.0",
       "minimum_index_compatibility_version" : "7.0.0"
     },
     "tagline" : "You Know, for Search"
   }
   ```

   

### 2. Docker compose 集群安装

众所周知Elasticsearch是一个分布式查询数据库，天然的为多实例集群而生，具备良好的伸缩性，因此在学习集群管理时，我们需要启动一个Elasticsearch集群来对一些集群相关的概念进行实践，在Docker compose的帮助下，我们可以快速的启动一个集群

1. 创建一个项目文件夹

   ```bash
   mkdir elasticsearch-learn #根据你的偏好自定义文件夹名称即可，这里统一以elasticsearch-learn为例
   ```

2. 创建docker-compose.yaml: 在elasticsearch-learn的根目录下创建`docker-compose.yaml` 并添加以下内容：

   ```yaml
   version: "2.2"
   services:
     setup:
       image: docker.elastic.co/elasticsearch/elasticsearch:${STACK_VERSION}
       volumes:
         - certs:/usr/share/elasticsearch/config/certs
       user: "0"
       command: >
         bash -c '
           if [ x${ELASTIC_PASSWORD} == x ]; then
             echo "Set the ELASTIC_PASSWORD environment variable in the .env file";
             exit 1;
           fi;
           if [ ! -f config/certs/ca.zip ]; then
             echo "Creating CA";
             bin/elasticsearch-certutil ca --silent --pem -out config/certs/ca.zip;
             unzip config/certs/ca.zip -d config/certs;
           fi;
           if [ ! -f config/certs/certs.zip ]; then
             echo "Creating certs";
             echo -ne \
             "instances:\n"\
             "  - name: es01\n"\
             "    dns:\n"\
             "      - es01\n"\
             "      - localhost\n"\
             "    ip:\n"\
             "      - 127.0.0.1\n"\
             "  - name: es02\n"\
             "    dns:\n"\
             "      - es02\n"\
             "      - localhost\n"\
             "    ip:\n"\
             "      - 127.0.0.1\n"\
             "  - name: es03\n"\
             "    dns:\n"\
             "      - es03\n"\
             "      - localhost\n"\
             "    ip:\n"\
             "      - 127.0.0.1\n"\
             > config/certs/instances.yml;
             bin/elasticsearch-certutil cert --silent --pem -out config/certs/certs.zip --in config/certs/instances.yml --ca-cert config/certs/ca/ca.crt --ca-key config/certs/ca/ca.key;
             unzip config/certs/certs.zip -d config/certs;
           fi;
           echo "Setting file permissions"
           chown -R root:root config/certs;
           find . -type d -exec chmod 750 \{\} \;;
           find . -type f -exec chmod 640 \{\} \;;
           echo "Waiting for Elasticsearch availability";
           until curl -s --cacert config/certs/ca/ca.crt https://es01:9200 | grep -q "missing authentication credentials"; do sleep 30; done;
           echo "All done!";
         '
       healthcheck:
         test: ["CMD-SHELL", "[ -f config/certs/es01/es01.crt ]"]
         interval: 1s
         timeout: 5s
         retries: 120
   
     es01:
       depends_on:
         setup:
           condition: service_healthy
       image: docker.elastic.co/elasticsearch/elasticsearch:${STACK_VERSION}
       volumes:
         - certs:/usr/share/elasticsearch/config/certs
         - esdata01:/usr/share/elasticsearch/data
       ports:
         - ${ES_PORT}:9200
       environment:
         - node.name=es01
         - cluster.name=${CLUSTER_NAME}
         - cluster.initial_master_nodes=es01,es02,es03
         - discovery.seed_hosts=es02,es03
         - ELASTIC_PASSWORD=${ELASTIC_PASSWORD}
         - bootstrap.memory_lock=true
         - xpack.security.enabled=true
         - xpack.security.http.ssl.enabled=true
         - xpack.security.http.ssl.key=certs/es01/es01.key
         - xpack.security.http.ssl.certificate=certs/es01/es01.crt
         - xpack.security.http.ssl.certificate_authorities=certs/ca/ca.crt
         - xpack.security.http.ssl.verification_mode=certificate
         - xpack.security.transport.ssl.enabled=true
         - xpack.security.transport.ssl.key=certs/es01/es01.key
         - xpack.security.transport.ssl.certificate=certs/es01/es01.crt
         - xpack.security.transport.ssl.certificate_authorities=certs/ca/ca.crt
         - xpack.security.transport.ssl.verification_mode=certificate
         - xpack.license.self_generated.type=${LICENSE}
       mem_limit: ${MEM_LIMIT}
       ulimits:
         memlock:
           soft: -1
           hard: -1
       healthcheck:
         test:
           [
             "CMD-SHELL",
             "curl -s --cacert config/certs/ca/ca.crt https://localhost:9200 | grep -q 'missing authentication credentials'",
           ]
         interval: 10s
         timeout: 10s
         retries: 120
   
     es02:
       depends_on:
         - es01
       image: docker.elastic.co/elasticsearch/elasticsearch:${STACK_VERSION}
       volumes:
         - certs:/usr/share/elasticsearch/config/certs
         - esdata02:/usr/share/elasticsearch/data
       environment:
         - node.name=es02
         - cluster.name=${CLUSTER_NAME}
         - cluster.initial_master_nodes=es01,es02,es03
         - discovery.seed_hosts=es01,es03
         - bootstrap.memory_lock=true
         - xpack.security.enabled=true
         - xpack.security.http.ssl.enabled=true
         - xpack.security.http.ssl.key=certs/es02/es02.key
         - xpack.security.http.ssl.certificate=certs/es02/es02.crt
         - xpack.security.http.ssl.certificate_authorities=certs/ca/ca.crt
         - xpack.security.http.ssl.verification_mode=certificate
         - xpack.security.transport.ssl.enabled=true
         - xpack.security.transport.ssl.key=certs/es02/es02.key
         - xpack.security.transport.ssl.certificate=certs/es02/es02.crt
         - xpack.security.transport.ssl.certificate_authorities=certs/ca/ca.crt
         - xpack.security.transport.ssl.verification_mode=certificate
         - xpack.license.self_generated.type=${LICENSE}
       mem_limit: ${MEM_LIMIT}
       ulimits:
         memlock:
           soft: -1
           hard: -1
       healthcheck:
         test:
           [
             "CMD-SHELL",
             "curl -s --cacert config/certs/ca/ca.crt https://localhost:9200 | grep -q 'missing authentication credentials'",
           ]
         interval: 10s
         timeout: 10s
         retries: 120
   
     es03:
       depends_on:
         - es02
       image: docker.elastic.co/elasticsearch/elasticsearch:${STACK_VERSION}
       volumes:
         - certs:/usr/share/elasticsearch/config/certs
         - esdata03:/usr/share/elasticsearch/data
       environment:
         - node.name=es03
         - cluster.name=${CLUSTER_NAME}
         - cluster.initial_master_nodes=es01,es02,es03
         - discovery.seed_hosts=es01,es02
         - bootstrap.memory_lock=true
         - xpack.security.enabled=true
         - xpack.security.http.ssl.enabled=true
         - xpack.security.http.ssl.key=certs/es03/es03.key
         - xpack.security.http.ssl.certificate=certs/es03/es03.crt
         - xpack.security.http.ssl.certificate_authorities=certs/ca/ca.crt
         - xpack.security.http.ssl.verification_mode=certificate
         - xpack.security.transport.ssl.enabled=true
         - xpack.security.transport.ssl.key=certs/es03/es03.key
         - xpack.security.transport.ssl.certificate=certs/es03/es03.crt
         - xpack.security.transport.ssl.certificate_authorities=certs/ca/ca.crt
         - xpack.security.transport.ssl.verification_mode=certificate
         - xpack.license.self_generated.type=${LICENSE}
       mem_limit: ${MEM_LIMIT}
       ulimits:
         memlock:
           soft: -1
           hard: -1
       healthcheck:
         test:
           [
             "CMD-SHELL",
             "curl -s --cacert config/certs/ca/ca.crt https://localhost:9200 | grep -q 'missing authentication credentials'",
           ]
         interval: 10s
         timeout: 10s
         retries: 120
   
   volumes:
     certs:
       driver: local
     esdata01:
       driver: local
     esdata02:
       driver: local
     esdata03:
       driver: local
   ```

3. 在elasticsearch-learn的根目录下创建`.env`文件 并添加以下内容：

   ```bas
   # Password for the 'elastic' user (at least 6 characters)
   ELASTIC_PASSWORD=TXWp5R4xwS8k4
   
   # Version of Elastic products
   STACK_VERSION=8.15.1
   
   # Set the cluster name
   CLUSTER_NAME=elasticsearch-learn-cluster-tls
   
   # Set to 'basic' or 'trial' to automatically start the 30-day trial
   LICENSE=basic
   
   # Port to expose Elasticsearch HTTP API to the host
   ES_PORT=9200
   
   # Increase or decrease based on the available host memory (in bytes)
   MEM_LIMIT=1073741824
   
   # Project namespace (defaults to the current folder name if not set)
   COMPOSE_PROJECT_NAME=elasticsearch-learn-cluster-tls
   ```

4. 在 Mac/linux的`/etc/hosts` 或windows的`C:\Windows\System32\drivers\etc\hosts` 文件末尾添加如下内容以开启自定义域名解析

   ```
   127.0.0.1 es01
   ```

5. 执行如下命令启动elasticsearch集群：

   ```bash
   docker compose up
   ```

   一些有用的Docker compose 命令

   - 停止集群容器运行：`docker compose stop`
   - 启动容器(阻塞式)：`docker compose up`
   - 重新创建容器： 停止容器后执行删除 `docker compose rm`,然后重新执行启动命令

6. 待集群启动完成后，执行如下命令查看集群状态

   ```bash
   curl -k --location 'https://es01:9200' \
   --header 'Authorization: Basic ZWxhc3RpYzpUWFdwNVI0eHdTOGs0'
   ```

### 3. 通过安装包安装
注意，此方法要求系统安装了java运行环境，否则无法运行elasticsearch,同时注意下载版本要与系统和cpu架构相匹配
1. 在elasticsearch官网下载软件的压缩包[点击跳转下载](https://www.elastic.co/downloads/elasticsearch)

2. 解压

3. 进入解压后的elasticsearch文件根目录，执行启动命令

   ```bash
   bin/elasticsearch -E xpack.security.enabled=false
   ```

   > 如果是mac，需要先执行`xattr -d -r com.apple.quarantine /Users/blank/Documents/dev/tech-study/elasticsearch-learn/elasticsearch-8.15.1`  允许软件运行，注意将目录地址替换成你的目录地址
   >
   > 这里我们用-E xpack.security.enabled=false关闭了安全配置从而忽略用户名/密码以及https，请不要在生产环境使用该配置

4. 同样的执行`curl http://localhost:9200` 验证服务是否启动


### 4. 通过包管理工具安装
如果仅是为了学习elasticsearch，不建议通过包管理工具安装，它会长期占用储存空间以及端口，更推荐用docker的方式快速安装，同时便于删除和改动，但在生产环境中就另当别论了，如果对此感兴趣，欢迎给我留言，我将在后续写一遍专门针对通过安装包安装的教程。

## 使用DocKit客户端工具连接 Elasticsearch

工欲善其事，必先利其器在后续中我们需要大量编辑/请求elasticsearch查询，用curl的方式检测服务器是否启动是没问题的，但是对于查询操作，我们需要一个如Navicat在SQL中的作用一样的客户端工具帮我们管理连接，执行查询操作等，这里我推荐使用DocKit进行连接,[访问DocKit官网](https://dockit.geekfun.club/)下载安装即可

同时本教程的所有案例，代码都可以在[GitHub中查看](https://github.com/Blankll/elasticsearch-learn)
