# [ab压测工具](http://httpd.apache.org/)

1. **吞吐率（Requests per second）**
   服务器并发处理能力的量化描述，单位是reqs/s，指的是某个并发用户数下单位时间内处理的请求数。某个并发用户数下单位时间内能处理的最大请求数，称之为最大吞吐率。
   计算公式：总请求数 / 处理完成这些请求数所花费的时间，即
   Request per second = Complete requests / Time taken for tests
2. **并发连接数（The number of concurrent connections）**
   某个时刻服务器所接受的请求数目，简单的讲，就是一个会话。
3. **并发用户数（The number of concurrent users，Concurrency Level）**
   要注意区分这个概念和并发连接数之间的区别，一个用户可能同时会产生多个会话，也即连接数。
4. **用户平均请求等待时间（Time per request）**
   处理完成所有请求数所花费的时间/ （总请求数 / 并发用户数），即
   Time per request = Time taken for tests /（ Complete requests / Concurrency Level）
5. **服务器平均请求等待时间（Time per request: across all concurrent requests）**
   计算公式：处理完成所有请求数所花费的时间 / 总请求数，即
   Time taken for / testsComplete requests
   可以看到，它是吞吐率的倒数。
   同时，它也=用户平均请求等待时间/并发用户数，即
   Time per request / Concurrency Level

