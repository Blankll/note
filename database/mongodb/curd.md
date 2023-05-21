# MongoDB | 概念及基础CRUD

MongoDB是一个开源, 高性能, 无模式的文档型数据库, 当初的设计就是用于简化开发和方便扩展, 是NoSQL数据库产品中的一种.是最 像关系型数据库（MySQL）的非关系型数据库. 它支持的数据结构非常松散, 是一种类似于 JSON 的 格式叫BSON, 所以它既可以存储比较复杂的数据类型, 又相当的灵活. MongoDB中的记录是一个文档, 它是一个由字段和值对（ﬁeld:value）组成的数据结构.MongoDB文档类似于JSON对象, 即一个文档认 为就是一个对象.字段的数据类型是字符型, 它的值除了使用基本的一些类型外, 还可以包括其他文档, 普通数组和文档数组.

## 1. MongoDB 相关概念

**"最像关系型数据库的 NoSQL 数据库"**. MongoDB 中的记录是一个文档, 是一个 key-value pair. 字段的数据类型是字符型, 值除了使用基本的一些类型以外, 还包括其它文档, 普通数组以及文档数组

### 1.2 MongoDB 的特点

#### 1.2.1 高性能

MongoDB 提供高性能的数据持久化

- 嵌入式数据模型的支持<u>减少了数据库系统上的 I/O 活动</u>
- 索引支持更快的查询, 并且可以包含来自嵌入式文档和数组的键 (文本索引解决搜索的需求, TTL 索引解决历史数据自动过期的需求, 地理位置索引可以用于构件各种 O2O 应用)
- mmapv1, wiredtiger, mongorocks (rocksdb) in-memory 等多引擎支持满足各种场景需求
- Gridfs 解决文件存储需求


#### 1.2.2 高可用

MongoDB 的复制工具称作**副本集** (replica set) 可以提供自动<u>故障转移和数据冗余</u>


#### 1.2.3 高扩展

水平扩展是其核心功能一部分

分片将数据分布在一组集群的机器上 (海量数据存储, 服务能力水平扩展)

MongoDB 支持基于**片键**创建数据区域, 在一个平衡的集群当中, MongoDB 将一个区域所覆盖的读写**只定向**到该区域的那些片

#### 1.2.4 其他

MongoDB支持丰富的查询语言, 支持读和写操作(CRUD), 比如数据聚合, 文本搜索和地理空间查询等. 无模式（动态模式）, 灵活的文档模型

### 1.3 业务场景

MongoDB 相比于SQL数据库更适用于**高并发, 高性能, 高可用**的场景

- High Performance: 对<u>数据库的高并发读写</u>的要求
- High Storage: 对<u>海量数据的高效率存储和访问</u>的需求
- High Scalability && High Available: 对数据的<u>高扩展性和高可用性</u>的需求

适合MongoDB 的应用场景

1. 数据量大， TB 甚至 PB 级别数据存储
2. 写入操作频繁， 2000 - 3000 以上的读写QPS，需要能快速水平扩展
3. 价值较低的数据, 对**事务性**要求不高，
4. 应用不需要复杂 JOIN 支持
5. 新应用, 需求和数据模型变更频繁, 快速迭代开发
6. 应用需要 `99.999%` 高可用
7. 应用需要大量的地理位置查询, 文本查询

对于这样的场景, 更适合用 MongoDB 来实现数据存储

### 1.4 MongoDB 核心概念


MongoDB 数据模型是面向<u>文档</u>的, 所谓文档就是一种类似于 JSON 的结构, 简单理解 MongoDB 这个数据库中存在的是各种各样的 JSON（BSON）

| SQL         | MongoDB                      |
| ----------- | ---------------------------- |
| database    | database                     |
| Table       | Collection                   |
| Row         | Document                     |
| column      | Field                        |
| Index       | Index                        |
| Primary key | primary key(_id)             |
| Table join  | N/A (or DBRefsnot recommend) |
| Reference   | Embedded document            |


在 MongoDB 中, 数据库和集合都不需要手动创建, 当我们创建文档时, 如果文档所在的集合或者数据库不存在, **则会自动创建数据库或者集合**


### 数据库 (databases) 管理语法

| 操作                                            | 语法                             |
| ----------------------------------------------- | -------------------------------- |
| 查看所有数据库                                  | `show dbs;` 或 `show databases;` |
| 查看当前数据库                                  | `db;`                            |
| 切换到某数据库 (**若数据库不存在则创建数据库**) | `use <db_name>;`                 |
| 删除当前数据库                                  | `db.dropDatabase();`             |


### 集合 (collection) 管理语法

| 操作         | 语法                                        |
| ------------ | ------------------------------------------- |
| 查看所有集合 | `show collections;`                         |
| 创建集合     | `db.createCollection("<collection_name>");` |
| 删除集合     | `db.<collection_name>.drop()`               |

### 1.3. data type

- string
- id
- boolean
- array
- int
- float
- null
- undefined
- BSON

## 2. 基本常用命令

### 2.1 数据库操作

Mongodb默认有3个保留数据库: `admin`, `local`, `config`

- **admin**: 从权限角度考虑, 这是 `root` 数据库, 如果将一个用户添加到这个数据库, 这个用户自动继承所有数据库的权限, 一些特定的服务器端命令也只能从这个数据库运行, 比如列出所有的数据库或者关闭服务器
- **local**: 数据永远不会被复制, 可以用来存储限于本地的单台服务器的集合 (部署集群, 分片等)
- **config**: Mongo 用于分片设置时, `config` 数据库在内部使用, 用来保存分片的相关信息

>```sh
>$ show dbs
>$ use mongoTutorial
>$ show dbs
>```
>

当使用 `use usersdb` 的时候. 此时`usersdb` 只存在内存中, 当 `usersdb` 中存在一个 collection 之后, mongo 才会将这个数据库持久化到硬盘之中.

### 2.2 文档基本 CRUD


#### 2.2.1 创建 Create

> Create or insert operations add new [documents](https://docs.mongodb.com/manual/core/document/#bson-document-format) to a [collection](https://docs.mongodb.com/manual/core/databases-and-collections/#collections). If the collection does **not** currently exist, insert operations will create the collection automatically.

- 使用 `db.<collection_name>.insertOne()` 向集合中添加*一个文档*, 参数一个 json 格式的文档
- 使用 `db.<collection_name>.insertMany()` 向集合中添加*多个文档*, 参数为 json 文档数组

```javascript
db.collection.insert({
  <document or array of documents>,
  writeConcern: <document>,
  ordered: <boolean>
})

// 向集合中添加一个文档
db.collection.insertOne(
   { item: "canvas", qty: 100, tags: ["cotton"], size: { h: 28, w: 35.5, uom: "cm" } }
)
// 向集合中添加多个文档
db.collection.insertMany([
   { item: "journal", qty: 25, tags: ["blank", "red"], size: { h: 14, w: 21, uom: "cm" } },
   { item: "mat", qty: 85, tags: ["gray"], size: { h: 27.9, w: 35.5, uom: "cm" } },
   { item: "mousepad", qty: 25, tags: ["gel", "blue"], size: { h: 19, w: 22.85, uom: "cm" } }
])
```

注：当我们向 `collection` 中插入 `document` 文档时, 如果没有给文档指定 `_id` 属性, 那么数据库会为文档自动添加 `_id` field, 并且值类型是 `ObjectId(blablabla)`, 就是文档的唯一标识, 类似于 relational database 里的 `primary key`， 我们也可以传入`_id`字段手动指定，此时需要确保`_id`的值在collection范围内唯一.

mongo 中的数字, 默认情况下是 double 类型, 如果要存整型, 必须使用函数 `NumberInt(整型数字)`, 否则取出来就有问题了

如果某条数据插入失败, 将会终止插入, 但已经插入成功的数据**不会回滚掉**.

#### 2.2.2 查询 Read

- 使用 `db.<collection_name>.find()` 方法对集合进行查询, 接受一个 json 格式的查询条件. 返回的是一个**数组**
- `db.<collection_name>.findOne()` 查询集合中符合条件的<u>第一个</u>文档, 返回的是一个**对象**


可以使用 `$in` 操作符表示*范围查询*

```javascript
//`$in` 操作符表示*范围查询*
db.collection.find( { status: { $in: [ "A", "D" ] } } ) 
//多个查询条件用逗号分隔, 表示 `AND` 的关系 SELECT * FROM inventory WHERE status = "A" AND qty < 30
db.collection.find( { status: "A", qty: { $lt: 30 } } ) 
// 使用 `$or` 操作符表示后边数组中的条件是OR的关系 SELECT * FROM inventory WHERE status = "A" OR qty < 30
db.collection.find( { $or: [ { status: "A" }, { qty: { $lt: 30 } } ] } ) 
// 正则表达式
db.<collection_name>.find({ content : /once/ })
// 在 terminal 中可以用 `pretty()` 来格式化输出帮助阅读
db.collection.find().pretty() 
```

#### 2.2.3 创建索引

```javascript
// 创建Compound Index
db.<collection_name>.createIndex({ userid : 1, username : -1 })
// 创建text index
db.collection.createIndex({{ title : 'text' }})

// 文本搜索 将通过index检索，提高速度
db.collection.find({
  $text : { $search : "\"Post O\""}
}).pretty()
```



#### 2.2.4 更新 Update

- 使用 `db.<collection_name>.updateOne(<filter>, <update>, <options>)` 方法修改一个匹配 `<filter>` 条件的文档
- 使用 `db.<collection_name>.updateMany(<filter>, <update>, <options>)` 方法修改所有匹配 `<filter>` 条件的文档
- 使用 `db.<collection_name>.replaceOne(<filter>, <update>, <options>)` 方法**替换**一个匹配 `<filter>` 条件的文档
- `db.<collection_name>.update(查询对象, 新对象)` 默认情况下会使用<u>新对象替换旧对象</u>

如果需要修改指定的属性, 而不是替换需要用修改操作符 `$set` 和`$unset`来进行修改

```javascript
// 仅更新size.uom 和status的值
db.collection.updateOne(
    { item: "paper" },
    {
        $set: { "size.uom": "cm", status: "P" },
        $currentDate: { lastModified: true }
    }
)
// 替换整个document,_id不变
db.collection.replaceOne(
    { item: "paper" },
    { item: "paper", instock: [ { warehouse: "A", qty: 60 }, { warehouse: "B", qty: 40 } ] }
)

// 默认会修改第一条
db.collection.update({ userid: "30", { $set {username: "guest"} } })

// 修改所有符合条件的数据
db.collection.update( { userid: "30", { $set {username: "guest"} } }, {multi: true} )
// likeNum++
db.collection.update({ _id: "3", {$inc: {likeNum: NumberInt(1)}} })
```

##### 常用修改操作符

| 操作符                                                       | 描述                                     |
| :----------------------------------------------------------- | :--------------------------------------- |
| [`$currentDate`](https://docs.mongodb.com/manual/reference/operator/update/currentDate/#up._S_currentDate) | 设置指定的fields的值为当前时间           |
| [`$inc`](https://docs.mongodb.com/manual/reference/operator/update/inc/#up._S_inc) | 对字段自增指定的值                       |
| [`$min`](https://docs.mongodb.com/manual/reference/operator/update/min/#up._S_min) | 仅在 $min < 字段值 < $max 才进行更新操作 |
| [`$max`](https://docs.mongodb.com/manual/reference/operator/update/max/#up._S_max) | 仅在 $min < 字段值 < $max 才进行更新操作 |
| [`$mul`](https://docs.mongodb.com/manual/reference/operator/update/mul/#up._S_mul) | 对字段乘以指定的值                       |
| [`$rename`](https://docs.mongodb.com/manual/reference/operator/update/rename/#up._S_rename) | 重命名字段                               |
| [`$set`](https://docs.mongodb.com/manual/reference/operator/update/set/#up._S_set) | 将字段设置为指定的值                     |
| [`$setOnInsert`](https://docs.mongodb.com/manual/reference/operator/update/setOnInsert/#up._S_setOnInsert) | 如果更新导致插入文档，则设置字段的值。   |
| [`$unset`](https://docs.mongodb.com/manual/reference/operator/update/unset/#up._S_unset) | 删除指定的字段                           |

#### 2.2.5 删除 Delete

- 使用 `db.collection.deleteMany()` 方法删除<u>所有</u>匹配的文档.
- 使用 `db.collection.deleteOne()` 方法删除<u>单个</u>匹配的文档.
- `db.collection.drop()`  删除整个collection
- `db.dropDatabase()` 删除真个数据库

```javascript
db.collection.deleteMany( { qty : { $lt : 50 } } )
```

### 2.3 文档排序和投影 (sort & projection)

使用`aggregate`对检索的文档进行排序，统计，map, 过滤等操作

在查询文档内容的时候, 默认是按照 `_id` 进行排序

我们可以用 `$sort` 更改文档排序规则`-1`为递增，`1`为递减

我们可以对文档进行“投影”(projection)以此指定返回的字段`1` 为返回 `0`为不返回

#### 2.3.1 条件操作符

| 操作符 | 描述          |
| ------ | ------------- |
| $gt    | `>` 大于      |
| $lt    | `<` 小于      |
| $gte   | `>=` 大于等于 |
| $lte   | `<= `小于等于 |
| $ne    | `!= `不等于   |
| $in    | 包含操作符    |
| $nin   | 不包含操作符  |

```javascript
{ $sort: { <field1>: <sort order>, <field2>: <sort order> ... } }

db.collection.aggregate(
   [
      // ascending on posts and descending on age
     { $sort : { age : -1, posts: 1 } }
    
   ]
)
 // 当添加limit的属性是，MongoDB只需要检索top limit的数据集，可以提升性能
 db.collection.find().sort({ title : -1 }).limit(2).pretty()
 // 仅返回username,和_id
  db.collection.find( {}, {username: 1} )
 // 仅返回age
 db.collection.find( {}, {age: 1, _id: 0} )
 
 //比较操作符
db.collection.find({ "field" : { $gt: value }}) // 大于: field > value
db.collection.find({ "field" : { $lt: value }}) // 小于: field < value
db.collection.find({ "field" : { $gte: value }}) // 大于等于: field >= value
db.collection.find({ "field" : { $lte: value }}) // 小于等于: field <= value
db.collection.find({ "field" : { $ne: value }}) // 不等于: field != value
 // 包含查询
 db.comment.find({userid:{$in:["1003","1004"]}}) //包含
 db.comment.find({userid:{$nin:["1003","1004"]}}) // 不包含
```

## 3. MongoDB 的索引

mongodb的索引与关系型数据库类似，每个collection在创建时会默添加一个unique index 即 `_id`， 且这个index是不可以删除的,MongoDB 使用的是 B Tree, MySQL 使用的是 B+ Tree。

当查询条件和查询的投影仅包含索引字段时, MongoDB 直接从索引返回结果而无需回表, 十分高效

index 一旦创建将无法更改，而要创建一个新的然后再drop掉老的index

可以使用以下命令操作index:

- `db.collection.createIndex( <key and index type specification>, <options> )` 创建index
- `db.collection.getIndexes()`查询创建的index
- `db.collection.dropIndex(<key and index type specification>)` 删除index

#### 3.1 Index Types

Mongodb 支持多种索引，以下为各个类型索引的简介:

| 索引名称            | 简介                                                         |
| ------------------- | ------------------------------------------------------------ |
| Single Field        | 单字段的 升序/降序 索引                                      |
| Compound Index      | 复合索引                                                     |
| Multikey Index      | 数组值索引，可以给一个字段值为数组的字段中的一个或多个字段进行索引 |
| Geospatial Index    | 地理坐标索引，提供了`2d indexes(平面几何)` 和`2dsphere indexes(球面几何)` |
| Text Search Indexes | 支持文本搜索的索引,类似于elasticsearch                       |
| Hashed Indexes      | HASH索引，提供最快的值查询，但不支持范围查询                 |
| Clustered Indexes   | clustered collections支持的index                             |

#### 3.2 Index Properties

可以给index添加不同的属性：

- `Unique Indexes`: 被index的字段在collection内唯一，任何重复的值插入都会被拒绝
- `Partial Indexes`: 仅index满足filter的document,可以节省index的磁盘占用
- `Sparse Indexes`: 仅index目标index字段有值的document,也是可以节省存储和提高索引效率
- `TTL Indexes`: 可以指定时间删除collection中的document
- `Hidden Indexes`： 可以将一个原有的index hidden,以测试删除index的影响

默认 `_id` 索引： MongoDB 在创建集合的过程中, 在 `_id` 字段上创建一个唯一的索引, 默认名字为 `_id` , 该索引可防止客户端插入两个具有相同值的文 档, 不能在 `_id` 字段上删除此索引. 

索引创建语法

```javascript
/**
 * @param keys: {doc_filed:[1|-1]}
 *   doc_filed: 为目标索引字段名
 *   value:     指定索引排序规则
 *     1: 指定升序创建索引
 *    -1: 指定降序创建索引
 * @param options
 *   background:         boolean  建立索过程会阻塞其他数据库操作，background可以指定后台进行异步索引, default=false
 *   unique:             boolean  指定是否建立唯一索引， default=false
 *   name:               string   指定索引名称，default=<field_name>_<sort_identifier>
 *   sparse              boolean  仅在字段存在值时对字段进行索引(使用该索引查询时将过滤该字段无值的document)
 *   expireAfterSeconds: integer  ttl index, 设置集合存在的时间
 *   v:                  index version 索引版本号
 *   weights:            document      索引权重1~99999，该索引相对其他索引字段的得分权重 
 *   default_language:   string        文本索引时指定分词规则，默认为英语
 *   language_override:  string        文本索引时指定包含在文档中的字段名，默认为language
 */
db.collection.createIndex(keys, options)
```

#### 3.3  执行计划

分析查询性能 (Analyze Query Performance) 通常使用执行计划 (解释计划 - Explain Plan) 来查看查询的情况

```shell
$ db.<collection_name>.find( query, options ).explain(options)
db.collection.find({userId: 123}).explain();
```



**尾巴：**这一周听闻coolshell的博主左耳朵耗子离世，百感交集，人生在世，能带走什么，又能留下什么呢，或许他的文章是他存在过的证据，那么百年之后，什么又是我存在过的证据呢？



## References

- https://docs.mongodb.com/
- https://mongoosejs.com/docs/guides.html
- https://docs.mongodb.com/manual/crud/
- https://www.bilibili.com/video/av59604756
- https://www.bilibili.com/video/BV1bJ411x7mq
- https://www.youtube.com/watch?v=-56x56UppqQ