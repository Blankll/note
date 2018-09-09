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

