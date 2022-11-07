# elasticsearch

## Elastic Stack

可视化: Kibaba

存储/计算: Elasticsearch

数据抓取: Logstash Beat

解决方案: 搜索,日志分析,指标分析,安全分析

## commander

```bash
/bin/elasticsearch-plugin list # 插件列表显示
/bin/elasticsearch # 启动elasticsearch
```

在浏览器中查看插件列表

在浏览器中访问:``http://localhost:9200/_cat/plugins``

## 本地多实例运行

```bash
bin/elasticsearch -E node.name=node1 -E cluster.name=seven -E path.data=node1_data -d
bin/elasticsearch -E node.name=node2 -E cluster.name=seven -E path.data=node2_data -d
bin/elasticsearch -E node.name=node3 -E cluster.name=seven -E path.data=node3_data -d
```

删除进程:

```bash
ps | grep elasticsearch
kill pid
```

查看集群节点:``http://localhost:9200/cat/nodes``

## kibana

- 在官网下载kibana``https://www.elastic.co/downloads/``

- 解压,然后运行``bin/kibana``
- 浏览器访问``http://localhost:5601``

### kibana插件安装

```bash
bin/kibana-plugin install plugin_location
bin/kibana-plugin list
bin/kibana remove
```



## 在docker中运行elasticsearch





## cerebro

elasticsearch 集群管理工具



## Logstash

- 下载logstash

- 准备logstash.conf配置文件

- 运行:``bin/logstash -f logstash.conf``





## 基本概念

1. **索引** index

   索引是文档的容器,时一类相似文档的集合(必须是小写)

   - index体现了逻辑空间的概念: 每个索引都有自己的mapping定义,用于定义包含的文档的字段名和字段类型
   - shard体现了物理空间的概念: 索引中的数据分散在Shard上
   - Mapping定义文档字段的类型
   - Setting定义不同的数据分布

   

2. **文档**

   elasticsearch是面向文档的,文档是所有可搜索数据的最小单位(类似关系型数据库中的一条记录)

   - 日志文件中的日志项
   - 一张唱片的详细信息
   - 一篇pdf中的具体内容

   文档会被序列化成json格式,保存在elasticsearch中

   - json对象由字段组成
   - 每个字段都有对应的类型(字符串/数值/布尔/日期/二进制/范围类型)

   每个文档都有一个unique id

   - 可以自己指定id
   - 可以通过elasticsearch自动生成

   元数据:用于标注文档的相关信息

   - _index 文档所属的索引名
   - _type 文档所属的类型名
   - _id 文档唯一id
   - _source 文档的原始json数据
   - _version 文档的版本信息
   - _score相关性打分

3. **集群:**  一个或者多个节点组织在一起

4. **节点:**  一个节点是集群中的一个服务器,由一个名字来标识,默认是一个随机的漫画角色的名字(本质上是一个java进程)在生产环境中建议只在一台主机上运行一个节点

   - **Master-eligiblenodes和Master Node:**
     - 每个节点启动后,默认就是一个Master eligible节点 可以设置 node.master: false禁止
     - Master-eligible节点可以参加选主流程,成为master节点
     - 当第一个节点启动时,它将自己选举成master节点
     - 每个节点上都保存了集群的状态,只有master节点才能修改集群的状态信息
     - 集群状态(Cluster state)维护了一个集群中的必要信息
       - 所有节点的信息
       - 所有的索引和其相关的Mapping与Setting信息
       - 分片路由的信息
     - 任意节点都能修改信息会导致数据一致性问题

   - **Data node & Coordinating node**

     - data node: 保存数据的节点,负责保存分片数据,在数据扩展上起到了至关重要的作用
     - coordinating负责接受Client的请求,将请求分发到合适的节点,最终把结果汇集到一起,每个节点默认个都起到了Coordinating node的职责

   - 配置节点类型

     - 开发环境中一个节点可以承担多种角色
     - 生产环境中,应该设置单一的角色节点(dedicated node)

     | 节点类型          | 配置参数    | 默认值                                                   |
     | ----------------- | ----------- | -------------------------------------------------------- |
     | master eligible   | node.master | true                                                     |
     | data              | node.data   | true                                                     |
     | ingest            | node.ingest | true                                                     |
     | coordinating only | 无          | 每个默认节点都是coordinating节点,设置其他类型全部为false |
     | machine learning  | node.ml     | true, (需要 enable xpack)                                |

5. **分片:**  将索引划分为多份的能力,允许水平分割和扩展容量,多个分片响应请求,提高性能和吞吐量
   - 主分片(Primary Shard): 用以解决数据水平扩展问题,可以将数据分布到集群内的所有节点之上
   - 主分片在索引创建时指定,后溪不允许修改,除非Reindex
   - 副本(Replica Shard): 用以解决数据的高可用问题 分片是主分片的拷贝
   - 副本分片数可以动态调整
   - 增加副本数,还可以在一定程度上提高服务的可用性(读取的吞吐)

6. **副本:**  创建分片的一份或多份的能力, 在一个节点失败时副本可以替换



| elasticsearch   | MySQL  |
| --------------- | ------ |
| index(索引)     | 数据库 |
| type(类型)      | 表     |
| documents(文档) | 行     |
| fields          | 列     |

**映射(mapping)** 创建索引时, 预先定义字段的类型以及相关属性

es根据json源数据的基础类型猜测目标字段映射, 将输入的数据转变成可搜索的索引项, **mapping**就是用户自定义的字段的数据类型,告诉es如何索引数据以及是否可以被搜索

作用: 让索引的建立更具细致和完善

类型: 静态映射和动态映射

string类型:text,keyword(string类型在es5开始已经废弃)

数字类型: long,integer, short, byte, double, float

日期类型: date

bool类型: boolean

binary类型: binary(不会被检索)

复杂类型: object, nested

geo类型: geo-point,geo-shape

专业类型: ip, competion