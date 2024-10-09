# 用ServerlessInsight构建一个全栈Serverless应用



Serverless让开发和运维从繁琐复杂的集群运维，扩缩容以及系统环境兼容性差异中解脱出来，从0到接近无限的毫秒级扩缩容能力不仅可以应对突发的流量，也可以让计算资源的到最大程度的利用，在性价比上对中小企业也是一个十分诱人的选择，ServerlessInsight全栈全生命周期的Serverless开源框架，可以让你快速的0到一构建个全栈Serverless应用且通过基础设施即代码的方式让你同时获得与生俱来的灾难恢复能力，让我么来看看如何创建一个简单的应用程序，该应用程序将在浏览器中显示“Hello World”。这里以阿里云为例子。

## 工具安装

前提条件是您已经安装了Node.js(Node.js >= 18.x)和npm。如果没有，请参考[Node.js](https://nodejs.org/en/download/)下载安装。

1. 安装ServerlessInsight CLI

    ```bash
    npm install -g @geek-fun/serverlessinsight
    ```
2. 执行`si --version`查看工具是否安装成功,如果安装成功，将会显示版本号。

## 配置供应商密钥(阿里云)

ServerlessInsight需要获得目标云厂商的访问权限包括云供应商的基础设施即代码服务的全部权限以及根据您的业务涉及到的Serverless服务的相应权限。
将对应的秘钥export到全局环境变量中，如阿里云的`ALIYUN_ACCESS_KEY_ID`, `ALIYUN_ACCESS_KEY_SECRET`以及服务部署的目标区域
`ALIYUN_REGION`。

![阿里云AccessKey生成示意](/aliyun-access-key.png)

> 请您务必妥善保管您的秘钥信息，不要通过任何方式（e.g. GitHub）将AccessKey 公开到外部渠道，以避免被他人利用而造成 安全威胁 。
> 强烈建议您遵循 阿里云安全最佳实践 ，使用 RAM 子用户AccessKey来进行 API 调用。ServerlessInsight不会保存任何供应商秘钥信息！

## 初始化项目

ServerlessInsight不强制要求项目的目录结构，但是我们建议您按照如下的目录结构组织您的项目(以ts项目为例):

```
hello-world-proj/
├── artifacts/
│   └── hello-world-proj.zip
├── scripts/
│   └── package.sh
├── src/
├── tests/
├── README.md
├── package.json
├── package-lock.json
├── tsconfig.json
|── Dockerfile
└── serverlessinsight.yml
```

其中`src`目录存放应用程序代码，`tests`目录存放测试代码，`scripts`目录存放自动化脚本如打包脚本，`artifacts`目录存放打包后的应用程序代码。

1. 配置`serverlessinsight.yml`声明资源
   创建`serverlessinsight.yml`,并将以下内容复制到文件中:

    ```yaml
    version: 0.1
    provider: aliyun
   
    vars:
      region: cn-hangzhou
   
    stages:
      dev:
        region: ${vars.region}
   
    service: hello-world-api
   
    tags:
      owner: geek-fun
   
    functions:
      hello_world_fn:
        fc_name: hello-world-fn
        runtime: nodejs14
        handler: index.handler
        code: artifacts/hello-world-api.zip
        memory: 512
        timeout: 10
        environment:
          NODE_ENV: prod
   
    events:
      gateway_event:
         type: API_GATEWAY
         name: insight-poc-gateway
         triggers:
            - method: GET
              path: /api/*
              backend:  hello-world-fn
    ```

2. 编写应用程序代码
   在`src`目录下创建`index.ts`文件，并将以下内容复制到文件中:

     ```typescript
     export async function handler(event: any, context: any) {
        return {
          statusCode: 200,
          body: JSON.stringify({
            message: 'Hello World!',
          }),
        };
     }
     ```

3. 打包应用程序
    - 在`Dockerfile`文件中添加以下内容:
    ```dockerfile
    FROM node:18.20.3-buster-slim@sha256:95fb3cf1d1ab1834c0fd65cdd2246198662460ae8f982a6cfab187889dd54bbe AS builder
    WORKDIR /app
    
   ENV NODE_ENV=development
   COPY ./package.json .
   COPY ./package-lock.json .
   RUN npm install
   COPY ./tsconfig.json .
   COPY ./src ./src
   RUN npm run build
    
   FROM node:18.20.3-buster-slim@sha256:95fb3cf1d1ab1834c0fd65cdd2246198662460ae8f982a6cfab187889dd54bbe
   WORKDIR /app
    
   ENV NODE_ENV=production
   COPY --from=builder /app/dist .
   COPY ./package.json .
   COPY ./package-lock.json .
   RUN npm install
   ```
   该Dockerfile文件中定义了两个阶段，第一个阶段用于构建应用程序，第二个阶段用于运行应用程序，目的是仅保留必要的执行文件，最大程度减小包的体积。

    - 在`scripts`目录下创建`package.sh`文件，并将以下内容复制到文件中:
   ```bash
   #!/bin/bash -eux
   set -o pipefail
   
   cd "$(dirname "$0")/.." || exit
   
   mkdir -p "artifacts"
   rm -rf ./dist ./artifacts/*
   
   IMAGE_NAME="hello-world-api"
   docker build -t "${IMAGE_NAME}" .
   
   docker run --rm \
   -v "$(pwd)"/dist:/dist \
   --name "${IMAGE_NAME}-package" "${IMAGE_NAME}:latest" \
   sh -c "cp -r /app/. /dist"
   
   cd dist && zip -r -D "../artifacts/${IMAGE_NAME}.zip" ./*
   ```
   然后执行`chmod +x scripts/package.sh`赋予脚本执行权限，执行`./scripts/package.sh`打包应用程序，完成后我们应当在
   `artifacts`目录下看到用以部署的`hello-world-api.zip`项目压缩文件。

## 部署服务

在部署服务之前，可以通过命令`si validate`检查`serverlessinsight.yml`文件中的配置项是否正确可用。
通过后执行如下命令部署服务到云提供商的环境中:

```bash
si deploy --stage dev <stackName>
```

stackName是部署的服务在云提供商的资源栈名称，部署成功后，您将会看到如下输出:

```bash
Deploying service hello-world-api to stage dev
Service hello-world-api deployed successfully
```

## 清理资源

如果应用程序不再需要，可以通过以下命令清理资源:

```bash
si destory --stage dev <stackName>
```

<span style="color: red;">
**注意:** 删除资源栈会删除所有申明的资源导致服务完全不可用且丢失有状态资源的数据，请确保相关数据、内容已备份或确认不再需要后执行该操作
</span>
