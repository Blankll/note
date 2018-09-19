# socket

## 创建socket

````c
#include<sys/types.h>
#include<sys/socket.h>

int socket(int domain, int type, int protocol);
````

- domain 指定使用的底层协议族

  > TCP/IP => PF_INET | PF_INET6
  >
  > UNIX => PF_UNIX

- type 指定服务类型

  > TCP/IP => SOCKET_STREAM
  >
  > UDP => SOCKET_UGRAM
  >
  > SOCK_NONBLOCK 将创建的socket设置为非阻塞
  >
  > SOCK_CLOEXEC　用fork调用创建子进程时在子进程中关闭这个socket

- protocol 在前两个参数构成的协议集合下再选择一个具体的协议

  > 不过这个值通常都是唯一的，前两个参数已经完全决定了它的值，把他设置为０表示默认即可

**socket系统调用成功时返回一个socket文件描述符,失败返回-1并设置errno**

## 命名socket

创建socket时给定了地址族但并未指定使用哪一个具体socket地址，将一个socket与socket地址绑定称为socket命名。

```c
#include<sys/types.h>
#include<sys/socket.h>

int bind(int sockfd, const struct sockaddr *myaddr, socklen_t addrlen);
```

- 成功时返回０，失败时返回-1并设置errno

  > errno类型
  >
  > EACCES被绑定的地址是受保护的地址，仅超级用户能够访问。
  >
  > EADDRINUSE 被绑定的地址正在使用中。

- sockfd未命名的文件描述符,将myaddr所指的socket地址分配给sockfd

- addrlen　socket地址的长度

## 监听socket

**创建一个监听队列存放待处理的客户端连接**

```c
#include<sys/socket.h>
int listen(int sockfd, int backlog);
```

- sockfd 指定被监听的socket
- backlog提示内核监听队列的最大长度，超出不再受理新连接，发送ECONNREFUSED错误信息，典型数值是５
- listen成功时返回０，失败时返回-1并设置errno

## 接受连接

**从listen队列中接受一个连接**

```c
#include<sys/types.h>
#include<sys/socket.h>
int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
```

- sockfd 执行过listen调用的监听socket
- addr 获取被接受连接的远端socket地址
- addrlen　指定远端socket地址长度

成功时返回一个新的连接socket,该socket唯一的标识这个连接，后续读写这个socket,失败时返回-1并设置errno.

## 关闭连接

```c
#include<unistd.h>
int close(int fd); // 关闭普通文件描述符的系统调用
```

**将fd的引用计数减１，当引用计数为0时才真正关闭该连接**

**一次fork调用默认使父进程中打开的socket的引用计数加1**

```c
#include<sys/socket.h>
int shutdown(int sockfd, int howto);
```

- howto

  > SHUT_RD 关闭socket上读的一半
  >
  > SHUT_WR　关闭socket上写的一半
  >
  > SHUT_RDWR　同时关闭读和写

**成功时返回0,失败时返回-1并设置errno**

