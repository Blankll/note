# socket

socket连接是全双工的

## 创建socket

````c
#include<sys/types.h>
#include<sys/socket.h>

int socket(int domain, int type, int protocol);
````

- domain 指定使用的底层协议族

  > TCP/IP => PF_INET | PF_INET6
  >
  > PF_INET
  >
  > PF_INET6
  >
  > UNIX => PF_UNIX

- type 指定服务类型

  > TCP/IP => SOCK_STREAM
  >
  > UDP => SOCK_UGRAM
  >
  > SOCK_NONBLOCK 将创建的socket设置为非阻塞
  >
  > SOCK_CLOEXEC　用fork调用创建子进程时在子进程中关闭这个socket

- protocol 在前两个参数构成的协议集合下再选择一个具体的协议

  > 不过这个值通常都是唯一的，前两个参数已经完全决定了它的值，把他设置为０表示默认即可

**socket系统调用成功时返回一个socket文件描述符,失败返回-1并设置errno**

``地址族`` address family

``协议族`` protocol family

| protocol family | address protocol | description      |
| --------------- | ---------------- | ---------------- |
| PF_UNIX         | AF_UNIX          | UNIX本地域协议族 |
| PF_INET         | AF_INET          | TCP/IPv4协议族   |
| PF_INET6        | AF_INET6         | TCP/IPv６协议族  |

AP_*,PF_*都在bits/socket.h

SOCKET网络中表示socket地址的结构体sockaddr

```c
#include<bits/socket.h>
struct socket sockaddr{
    sa_family_t sa_family; //地址族类型，通常与协议族类型对应
    char sa_data[14];
}
```

tcp/ip协议中有socket_in和socket_in6连个专用socket结构体用于存放IPv4,IPv6地址，

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

## TCP数据读写

### 读取数据

```c
#include<sys/types.h>
#include<sys/socket.h>

ssize_t recv(int sockfd, void* buf, size_t len, int flags);
```

recv读取sockfd上的数据，

- buf 读缓冲区的位置
- flags　通常设置为0

成功时返回实际读取的长度

返回0时表示连接关闭

返回-1时表示出错并设置errno

### 发送数据

```c
#include<sys/types.h>
#include<sys/socket.h>

ssize_t send(int sockfd, const void* buf, size_t len, int flags);
```

send向sockfd上写入数据，

- buf 缓冲区的位置
- len　缓冲区的大小
- flags参数为数据收发提供额外的控制

send成功时返回实际写入的数据长度

send失败时返货-1并设置errno