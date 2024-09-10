# Elasticsearch 入门实践 - 使用场景

本章我们将具体介绍Elasticsearch是什么，可以做什么，在哪些场景下需要使用或者说适合使用Elasticsearch，以及行业内的一些应用案例。

## 什么是Elasticsearch

简而言之，**Elasticsearch** 是一个数据库，和MySQL一样用于存储数据，但不同之处在于Elasticsearch是一个NoSQL的分布式数据库、它基于 RESTful API对数据库进行操作， Elasticsearch的核心是基于Apache Lucene的搜索和分析引擎，通常用于处理大规模数据的实时搜索、日志和分析。它是 Elastic Stack（也称为 ELK Stack：Elasticsearch、Logstash、Kibana）的核心组成部分。

## 为什么需要Elasticsearch

现如今有太多的数据库，如人们耳熟能详的MySQL，PostgreSQL，MongoDB，Redis等，为什么我们要学习或者说需要Elasticsearch呢？

我们来看一下Elasticsearch有哪些特点：

1. **全文搜索**：Elasticsearch 基于Apache Lucene，使用倒排索引(Inverted index)的方式索引和存储数据，相比于传统关系型数据库的B/b+Tree 天然的对全文搜索有更好的支持，同时Elasticsearch通过Query DSL，Painless, ESQL等提供了强大的全文搜索功能，可以处理复杂的查询，并快速返回匹配结果。

2. **分布式架构**：Elasticsearch天生为大型分布式应用而生，一个Elasticsearch集群由不同的节点(node)组成，node 分为主节点(Master Node)， 数据节点(Data Node)，数据插入节点(Ingest node)， 机器学习节点(Machine learning node)，交换节点(Transform node)等，并将数据拆分到不同的分片中存储且分片又分为主分片和副本分片，从而实现数据的高可用以及横向自动集群伸缩能力。

3. **实时数据处理**：基于Apache Lucene， Elasticsearch能够实时索引和搜索数据，使用户可以在数据生成后立即进行查询和分析。

4. **强大的分析功能**：Elasticsearch使用Query DSL来定义搜索语句而不是SQL，相比于SQL，Query DSL支持复杂的数据分析和聚合操作，可以进行复杂条件的数据分析和检索，适合如全文本内容搜索，海量日志分析包括审计日志，以及指标监控等各种需要复杂分析逻辑的场景中。

5. **RESTful API**：相较于传统关系型数据库的TCP连接配合SQL查询，Elasticsearch使用简介明了的 HTTP 接口，且请求接口均遵循了RESTful规范，通过 JSON 格式的数据进行查询和管理操作。

从上面的特性可以明显看出，Elasticsearch就是为了海量数据的复杂检索而设计的，因此很好的弥补了关系型数据库对全文索引，模糊搜索的功能欠缺已经性能瓶颈等弱点，同样的我们也可以从而得出，相比于关系型数据库，Elasticsearch会产生一定的数据冗余已经一致性的不完备，所以它并不能取代关系系数据库在关键强一致业务中的地位，他们是相辅相成的关系。

## Elasticsearch适合什么样的场景

从上面Elasticsearch的特性出发，可以看到Elasticsearch非常适合于要实时处理和查询的大数据领域。其具体场景包括：

### 1. **系统观测**

系统观测数据具有实时性高，数据量大，搜索条件严格等特点，非常契合Elasticsearch的设计初衷，Elasticsearch非常适合于存储该类型的数据，常应用于应用监控（APM），日志存储及管理，服务监控，安全信息和事件管理（SIEM）等

### 2. **网站和应用搜索服务**

Elasticsearch的全文检索非常适合文本内容搜索匹配，排序和个性化推荐等，常应用于应用于电商内容搜索，内容管理系统（CMS），企业内部搜索，法律和金融文档搜索，学术论文搜索等。

### 3. **数据分析**

得益于Elasticsearch的Query DSL对复杂搜索的以及分析算法的支持，Elasticsearch也适用于商业数据分析领域，如销售数据分析，运营分析和社交媒体的分析统计，数据仪表板，报表生成以及物联网（IoT）数据分析等。基于分析数据的结果，可以衍生出个性化推荐以及相似项搜索等功能。

### 4. **地理位置搜索**

Elasticsearch提供了完善的地理信息数据类型以及检索方法包括Geopoint，Geoshape，Point以及shape等，可以很好的支撑如本地服务搜索，导航和路线规划业务场景。

### 5. **人工智能领域**

2023年的AI热将人工智能推向了新的高度，Elasticsearch同样也引入了如向量数据库，Eland等对NLP领域的支持。

## 谁在使用Elasticsearch

那么都有哪些公司企业在使用Elasticsearch呢，其实非常的多，如需要涉及到搜索业务的百度，淘宝等，还有由于支撑系统观测的如我们所知的美团，小米等。
