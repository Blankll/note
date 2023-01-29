# Kafka 

kafka是一个分布式的基于发布订阅模式的消息队列，主要用于大数据实时处理领域

Data is kept only for a limited time defualt is 1 week

## Topics

a particular stream of data(like a table in a database without constraints)

a topic cannot be queried

topics are immutable, once data is written to a partion, it cannot be changed

## Partitions

topices are split in partitions, messages in each partition are ordered,it gets an incremental id wich called offset

message is assigned randomly to a partition unless a key is provided



## Serializer

Kafka only accepts bytes as input & output, there are the common serializers

- String
- Int, Float
- Avro
- Protobuf

