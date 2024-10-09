# Elasticsearch Scripting - Painless

通常情况下ElasticSearch 查询 - Query DSL 已经可以满足绝大部分的查询场景，但对于一些复杂的动态查询或需要对文档中的字段做解构等复杂匹配时Scripting功能就能很好的实现这一功能了。Painless是elasticsearch专门为elasticsearch场景下设计的脚本语言， 具有安全，简单且高性能的特点。

## 如何使用Painless

我们首先来看一下Painless的标准格式：

```json
  "script": {
    "lang":   "...",
    "source" | "id": "...",
    "params": { ... }
  }
```

**lang**: 用来定义该script所使用的语言，默认为Painles。

> lang 还原生支持`expression`， `mustache`以及通过插件支持`java`， 但`Painless`作为官方默认选项提供了更好的支持以及性能表现。

**source/id**：指定source或id来声明要执行的脚本。

> scripting 可以通过`PUT _scripts` 编译存储在Elasticsearch中，通过id直接使用

**params**：用来传递source中用到的参数，通过参数进行变量传递可以减少脚本编译次数从而提升执行效率



## 使用案例

### 用Painless脚本操作查询结果

首先先创建一个简单的document：

```json
PUT my-index-000001/_doc/1
{
  "my_field": 5
}
```

然后让我们通过使用script来拿到my_field * 2 的查询结果：

```json
GET my-index-000001/_search
{
  "script_fields": {
    "my_doubled_field": {
      "script": { 
        "source": "doc['my_field'].value * params['multiplier']", 
        "params": {
          "multiplier": 2
        }
      }
    }
  }
}
```

仔细阅读上面的query，script中的source语句使用`doc['my_field'].value` 来读取document中`my_field`字段的值，同时通过`params['multiplier']`读取传入的参数，这样做的好处是入参的改变不会导致source脚本的重新编译，从而提升性能。

最终我们就可以得到如下的结果：

-TBC dockit screenshot

### 用Painless脚本更新document

可以在`_update`api中使用script来使用Painless进行字段的动态更新，如我们可以给一个array类型的tags字段通过update语句添加一个新的tag

```json
// 首先添加一个sample数据
PUT my-index-000001/_doc/1
{
  "counter" : 1,
  "tags" : ["red"]
}
// 通过更新添加一个新的tag
POST my-index-000001/_update/1
{
  "script": {
    "source": "ctx._source.tags.add(params['tag'])",
    "lang": "painless",
    "params": {
      "tag": "blue"
    }
  }
}
```



### 用Painless脚本解构数据

当一个字段中包含复合内容时，如一条未解析的直接存储的日志，一条iot设备上传的状态数据等，我们可以在插入前进行解析，也可以通过脚本在查询时进行解构获取或操作目标数据段。

Elasticsearch提供了两个方法对数据进行解构：

1. Grok: 一种正则表达式的方言，构建与正则表达式之上但提供了更加符合Elasticsearch下的抽象
2. Dissect：通过解析字段的格式，基于分隔符对一条符合内容进行解构拆分从而获得所需要的数据







### 用语法糖简化Painless脚本



## 最佳实践







refer: https://www.elastic.co/guide/en/elasticsearch/reference/current/scripting-field-extraction.html
