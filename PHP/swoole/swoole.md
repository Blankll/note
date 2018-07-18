# swoole

## tcp服务

1. server端

   ```php
    <?php
     2 //创建Server对象,监听127.0.0.1:8000端口
     3 $serv = new swoole_server("127.0.0.1", 8000);
     4 //监听连接进入事件
       /**
        * $fd　客户端连接的唯一标识
        * $reactor_id 进程id 
        */
     5 $serv->on('connect', function ($serv, $fd, $reactor_id) {
     6     echo "client connect\n";
     7 });
     8 
     9 //监听数据接收事件
       /**
        * $fd　客户端连接的唯一标识
        * $from_id 进程id
        */
    10 $serv->on('receive', function ($serv, $fd, $from_id, $data){
    11     $serv->send($fd, 'Server'.$data);
    12 });
    13 
    14 //监听连接关闭事件
    15 $serv->on('close', function ($serv, $fd) {
    16     echo "client: closed\n";
    17 });
   ?>
   ```

2. 启动服务 php file.php

3. 测试

   > netstat -anp | grep port
   >
   > telnet 127.0.0.1 8000

4. ps aft |grep tcpserv.php 查看程序占用的进程情况　



## http服务

http通讯只能由客户端发起，服务器无法主动给客户端发送消息

1. http服务端

   ```php
   <?php
   $http = new swoole_http_server('0.0.0.0',8000);
   $http->set([
   	# 是否支持静态资源
   	'enable_static' => true,
   	# 静态资源加载根目录
   	'document_root' => '/home/source'
   ]);
   $http->on('request', function($request, $response) {
   	$response->end("<h1>http server</h1>");
   });
   
   $http->start();
   ?>
   ```



## Swoole WebSocket

websocket 是基于TCP的一种新的网络协议，实现了浏览器与服务器的全双工(full-duplex)通讯－允许服务器主动发送消息给客户端。

- webSoket建立在TCP协议之上，
- 持久化的网络通讯协议
- 性能开销小，效率高

