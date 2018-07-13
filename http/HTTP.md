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

