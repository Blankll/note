# docker compose

## 环境配置

- 安装docker-compose

  ```bash
  sudo curl -L "https://github.com/docker/compose/releases/download/1.24.1/docker-compose-$(uname -s)-$(uname -m)" -o /usr/local/bin/docker-compose
  
  sudo curl -L "https://github.com/docker/compose/releases/download/1.24.1/docker-compose-$(uname -s)-$(uname -m)" -o /usr/local/bin/docker-compose
  
  sudo chmod +x /usr/local/bin/docker-compose
  
  sudo ln -s /usr/local/bin/docker-compose /usr/bin/docker-compose
  
  docker-compose --version
  ```

- docker-compose需要在当前文件夹下创建docder-compose.yml

- 创建并启动容器:

  ```bash
  docker-compose up
  docker-compose up -d  # 后台启动并运行容器
  ```

- 列出所有compose的容器:

  ```bash
  docker-compose ps
  ```

- 查看docker-compose日志

  ```bash
  docker-compose logs
  docekr-compose logs container-id
  ```

- 构建或重新构建服务,只构建,不运行

  ```bash
  docker-compose build
  ```

- 启动指定服务的容器

  ```bash
  docker-compose start container-name
  ```

- 停止指定服务的容器

  ```bash
  docker-compose rm container-name
  ```

- 通过发送 SIGKILL 信号来停止指定服务的容器

  ```bash
  docker-compose kill container-name
  ```

- 在一个服务上执行一个命令

  ```bash
  docker-compose run web bash
  ```



### docker-compose.yml 属性

-  **version**：指定 docker-compose.yml 文件的写法格式

-  **services**：多个容器集合

-  **build**：配置构建时，Compose 会利用它自动构建镜像，该值可以是一个路径，也可以是一个对象，用于指定 Dockerfile 参数

  ```bash
  build: ./dir
  ---------------
  build:
      context: ./dir
      dockerfile: Dockerfile
      args:
          buildno: 1
  ```

- **command**：覆盖容器启动后默认执行的命令

  ```bash
  command: bundle exec thin -p 3000
  ----------------------------------
  command: [bundle,exec,thin,-p,3000]
  ```

- **dns**：配置 dns 服务器，可以是一个值或列表

  ```bash
  dns: 8.8.8.8
  ------------
  dns:
      - 8.8.8.8
      - 9.9.9.9
  ```

- **dns_search**：配置 DNS 搜索域，可以是一个值或列表

  ```bash
  dns_search: example.com
  ------------------------
  dns_search:
      - dc1.example.com
      - dc2.example.com
  ```

- **environment**：环境变量配置，可以用数组或字典两种方式

  ```bash
       
  
  environment:
      RACK_ENV: development
      SHOW: 'ture'
  -------------------------
  environment:
      - RACK_ENV=development
      - SHOW=ture
  ```

- **nv_file**：从文件中获取环境变量，可以指定一个文件路径或路径列表，其优先级低于 environment 指定的环境变量

  ```bash
  env_file: .env
  ---------------
  env_file:
      - ./common.env
  ```

- **expose**：暴露端口，只将端口暴露给连接的服务，而不暴露给主机

  ```bash
  expose:
      - "3000"
      - "8000"
  ```

- **image**：指定服务所使用的镜像

  ```bash
  image: java
  ```

- **network_mode**：设置网络模式

  ```bash
  network_mode: "bridge"
  network_mode: "host"
  network_mode: "none"
  network_mode: "service:[service name]"
  network_mode: "container:[container name/id]"
  ```

- **ports**：对外暴露的端口定义相当于 docker的-p

  ```bash
  ports:   # 暴露端口信息  - "宿主机端口:容器暴露端口"
  - "8763:8763"
  - "8763:8763"
  ```

- **links**：将指定容器连接到当前连接，可以设置别名，避免ip方式导致的容器重启动态改变的无法连接情况

  ```bash
  links:    # 指定服务名称:别名 
      - docker-compose-eureka-server:compose-eureka
  ```

- **volumes**：卷挂载路径

  ```bash
  volumes:
    - /lib
    - /var
  ```

- **logs**：日志输出信息

  ```bash
  --no-color          单色输出，不显示其他颜.
  -f, --follow        跟踪日志输出，就是可以实时查看日志
  -t, --timestamps    显示时间戳
  --tail              从日志的结尾显示，--tail=200
  ```

### 更新容器

- 当服务的配置发生更改时，可使用 docker-compose up 命令更新配置
- 此时，Compose 会删除旧容器并创建新容器，新容器会以不同的 IP 地址加入网络，名称保持不变，任何指向旧容起的连接都会被关闭，重新找到新容器并连接上去