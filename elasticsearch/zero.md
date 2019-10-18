# elasticsearch

1. **集群:**  一个或者多个节点组织在一起
2. **节点:**  一个节点是集群中的一个服务器,由一个名字来标识,默认是一个随机的漫画角色的名字
3. **分片:**  将索引划分为多份的能力,允许水平分割和扩展容量,多个分片响应请求,提高性能和吞吐量
4. **副本:**  创建分片的一份或多份的能力, 在一个节点失败时副本可以替换



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