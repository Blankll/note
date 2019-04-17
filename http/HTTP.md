---
typora-copy-images-to: ./
---

# HTTP

![](C:\Users\blank\Desktop\http/http.png)

http创建一个tcp连接 

http2.0tcp连接支持并发![标](C:\Users\blank\Desktop\http/无标题.png)

wireshark网络抓包工具

https://www.wireshark.org/

tcp三次握手

client:  [SYN] Seq => server

sever : [SYN ACK] Seq => client

client: [ACK] Seq => server

### URN 永久统一资源定位符



在资源移动之后还能找到

## HTTP  报文

### REQUEST

1. 首行 GET /test/hi-there.text HTTP/1.0     方法 资源地址  HTTP版本
2. HEADER
3. BODY

（希望这么做，HTTP协议没有强约束）

### RESPONSE

1. 首行 HTTP/1.0 200 OK   http版本 状态码，
2. HEADER
3. BODY

## CORS

### 允许方法

1. GET
2. HEAD
3. POST

### 允许的content-type

1. text/plain
2. multipart/form-data
3. application/x-www-form-urlencoded

### 预请求



## 请求状态码

- 1×× 信息类状态码 表示接收请求正在处理

- 2×× 请求成功状态码 表示请求正常处理完毕
  - 200 ok 请求正常处理
  - 204 请求正常处理，但返回结果不包含实体数据（不返回内容）
  - 206 返回部分的内容

- 3×× 重定向 需要进行附加操作以完成请求
  - 301 永久性重定向
  - 302 临时性重定向
  - 303 请求的资源存在另一个uri，应使用get方法定向获取请求资源
  - 304 发送的请求不满足需求
  - 307临时重定向302

- 4×× 客户端错误 服务器无法处理请求
  - 400 请求报文中存在语法错误，需修改请求的内容
  - 401 请求需要认证信息 Unauthrization
  - 403 请求资源被服务器拒绝 permissionded
  - 404 找不到请求的资源
- 5×× 服务器错误状态码 服务器处理请求时出错
  - 500 服务器错误
  - 503 服务器超负载

### http协议的工作原理

客户端发送请求给服务器，创建一个TCP连接，指定端口号，默认为80，连接到服务器，服务器监听浏览器请求，一旦监听到客户端请求，分析请求类型后，服务器会向客户端返回状态信息和数据内容

## http协议常见的请求/响应头

- Content-Type 与请求实体对应的MIME信息
- Accept 指定客户端能接受的内容
- Origin 最初的请求来源，主要用于post请求
- Cookie http请求发起时客户端发送给服务端的值
- Cache-Control 指定请求和响应的缓存机制
- User-Agent 用户信息 如浏览器信息
- Referrer 上级请求路径
- X-Forwarded-For 请求端的真实ip
- Access-Control-Allow-Origin 允许特定的域名进行访问
- Last-Modified 请求资源的最后响应时间

## https

HTTPS是一种基于SSL/TLS的http协议，所有的HTTP数据都是在SSL/TLS西药封装之上进行传输的。

HTTPS协议在HTTP协议的基础上，添加了SSL/TLS握手以及数据加密传输，也属于应用层协议。

## 常见的网络协议和端口

- FTP 文件传输协议 ``21``
- Telnet 远程登录协议``23``
- SMTP 简单邮件传输协议 ``25``
- POP3 邮件接收协议 ``110``
- HTTP 超文本传输协议 ``80``
- HTTPS ``443``
- DNS 域名解析协议 ``53``