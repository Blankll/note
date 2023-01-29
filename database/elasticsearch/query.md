# ES Query

Query is the most important functionality for  ES.

## before Query

**create index**

```
PUT /your-index
# create index with mapping
PUT /event-es-index-v1
{
  "mappings": {
    "dynamic": false,
    "properties": {
      "id": {
        "type": "keyword"
      },
      "username": {
        "type": "keyword"
      },
      "title": {
        "type": "text"
      }
    }
  },
  "settings": {
    "index":{
      "refresh_interval": "1s"
    }
  }
}
```

**insert data** 

```
POST /event-es-index-v1/_bulk
{ "index" : { "_id" : "1" } }
{ "id" : "1",  "username": "seven azss","title": "what is a title here", "desc": "a description for a sample document" }
{ "index" : { "_id" : "2" } }
{ "id" : "2",  "username": "eight bez","title": "what is a title here", "desc": "a description for a sample document" }
```

## Query DSL

**list all indexes**

```
GET /_cat/indices
```

### match_all

search all  record，default response row is 10 maximum 10000

```
GET /index/_search
{
  "query": {
    "match_all": {}
  }
}
```

**Options**

- `sort` [list]: to define  sort result based on which field
- `size`[int]: define response row count, default response row is 10 maximum 10000
- `from`[int]: define response start from which matched record, aways use for pagination 
- `_source`[string list]: use to define  fields contains in response

### match

use to define match conditions

**Options**

- `operator`: define match type
  - OR(default): select when any plitted query string words contain in document 
  - AND:  select when all plitted query string words contains in document 
- `minmum_should_match`: define how many plitted query string words should contain in document when using `OR` operator

### match_phrase

查询分析文本并根据分析文本创建一个短语查询。match_phrase会将检索关键词分词，match_phrase的分词结果必须在被检索字段的分词中都包含，且顺序比心相同，且默认必须是连续的

- Slop：查询词条可以相隔多远

```
GET /index/_search
{
  "query": {
    "match_phrase": {
    	"field_name": "str"
    }
  }
}
```



### multi_match

Query same string in mult fields

```
GET /index/_search
{
  "query": {
    "multi_match": {
    	"query": "str"
    	"fields":[
    		"field_1",
    		"field_2"
    	]
    }
  }
}
```



### query_string

### term

### prefix search

### wildcard

### range search

### query by id

### fuzzy search

### bool query



