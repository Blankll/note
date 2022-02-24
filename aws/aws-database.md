RTO=Recovery Time Objective

Amount of time within which services must be restored ie from start of disaster upto how much time ahead elapsed for services to restore 

RPO=Recovery Point Objective

Amount of dataloss (due to disaster ) that can be tolerated. ie from start of disaster upto how much time back (data loss) can be tolerated

Multi-AZ is using synchronous replication ensuring less than 1s RPO. Read replicas are assynchronous with lag up to 5 minutes in postgresql RDS

No-RDS

## Amazon ElastiCache

Amazon ElastiCache offers fully managed Redis and Memcached. With both [ElastiCache for Redis](https://aws.amazon.com/elasticache/redis/) and [ElastiCache for Memcached](https://aws.amazon.com/elasticache/memcached/) you:

- No longer need to perform management tasks such as hardware provisioning, software patching, setup, configuration, and failure recovery. This allows you to focus on high value application development.
- Have access to monitoring metrics associated with your nodes, enabling you to diagnose and react to issues quickly.
- Can take advantage of cost-efficient and resizable hardware capacity.

Additonally, 

ElastiCache for Memcached features [Auto Discovery](http://docs.aws.amazon.com/AmazonElastiCache/latest/mem-ug/AutoDiscovery.HowAutoDiscoveryWorks.html) which helps developers save time and effort by simplifying the way an application connects to a cluster.

Read the more detailed [comparison between ElastiCache for Redis and Elasticache for Memcached](https://docs.aws.amazon.com/AmazonElastiCache/latest/mem-ug/SelectEngine.html) for further information about differences between the two products.

**ElastiCache for Redis**

Amazon ElastiCache for Redis is a blazing fast in-memory data store that provides sub-millisecond latency to power internet-scale real-time applications. ElastiCache for Redis supports replication, high availability, and cluster sharding right out of the box. ElastiCache for Redis features an enhanced engine which improves on the reliability and efficiency of open source Redis while remaining Redis-compatible so your existing Redis applications work seamlessly without changes. ElastiCache for Redis also features [Online Cluster Resizing](https://aws.amazon.com/elasticache/redis/faqs/#redis-online-cluster-resizing), supports [encryption](https://aws.amazon.com/blogs/security/amazon-elasticache-now-supports-encryption-for-elasticache-for-redis/), and is [HIPAA eligible](https://aws.amazon.com/about-aws/whats-new/2017/11/amazon-elasticache-for-redis-is-now-hipaa-eligible-to-help-you-power-secure-healthcare-applications-with-sub-millisecond-latency/) and [PCI DSS compliant](https://aws.amazon.com/about-aws/whats-new/2018/07/amazon-elasticache-for-redis-is-now-pcidss-compliant/).

**ElastiCache for Memcached** 

Amazon ElastiCache for Memcached is a Memcached-compatible in-memory key-value store service that can be used as a cache or a data store. Amazon ElastiCache for Memcached is a great choice for implementing an in-memory cache to decrease access latency, increase throughput, and ease the load off your relational or NoSQL database. Session stores are easy to create with Amazon ElastiCache for Memcached. Elasticache for Memcached is not HIPAA eligible, so this option is incorrect.

**DynamoDB** 

Amazon DynamoDB is a key-value and document database that delivers single-digit millisecond performance at any scale. It's a fully managed, multi-region, multi-master, durable database with built-in security, backup and restore, and in-memory caching (via DAX) for internet-scale applications. 

**DocumentDB** 

Amazon DocumentDB is a fast, scalable, highly available, and fully managed document database service that supports MongoDB workloads. As a document database, Amazon DocumentDB makes it easy to store, query, and index JSON data.



**Amazon Neptune** 

Amazon Neptune is a fast, reliable, fully managed graph database service that makes it easy to build and run applications that work with highly connected datasets. The core of Amazon Neptune is a purpose-built, high-performance graph database engine optimized for storing billions of relationships and querying the graph with milliseconds latency. Neptune powers graph use cases such as recommendation engines, fraud detection, knowledge graphs, drug discovery, and network security.