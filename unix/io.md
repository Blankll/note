# IO

同步：进行一个调用时，在没有得到结果之前，该调用会一直等待调用结束再执行后续操作。

异步：当一个异步过程调用发出后，调用立即返回并在没有得到结果之前，就可以继续执行后续操作。调用完成后会通过状态，通知，回调通知调用者

阻塞：阻塞调用是指调用结果返回之前，当前线程会被挂起。调用线程只有在得到结果之后才会返回。

非阻塞：非阻塞调用指在不能立刻得到结果之前，该调用不会阻塞当前线程。

select/poll/epoll

select发生在内核

### 流程

- 先构建一张有关文件描述符的列表,将要监听的文件描述符添加到该表中
- 调用函数,监听表中的文件描述符,直到描述符表中的一些I/O进行操作时,函数返回
- 函数为阻塞函数
- 函数对文件描述符的检测操作是由内核完成的
- 返回有多少(epoll哪些)描述符进行了i/o操作



## select

```c
int select(int nfds, fd_set* readfds, fd_set* writefds, fd_set* exceptfds, struct timeval* timeout);
```

>nfds:  待检测文件描述符中max(fd)+1 不清楚可以传1024 => ``fd_set``在内核中通过数组实现,且长度为1024
>
>readfds: 读操作集合(io多路转接多发生在读的被动行为中)
>
>writefds: 写操作集合 多数时候传NULL即可
>
>exceptfds: 异常集合
>
>timeout: 超时时间
>
>	- 可以用来设置是否阻塞,传NULL则为永久阻塞,当检测到文件描述符发生变化时返回
>	- timeval和为0时非阻塞,直接返回
>
>```c
>struct timeval {
>	long tv_sec;// 秒
>	long tv_usec; // 微秒
>}; // result = 秒+微秒 两个都要赋值,不用的赋为0
>```

### 文件描述符操作函数

```c
void FD_ZERO(fd_set* set); // 清空全部--标志位全部设置为0
void FD_CLR(int fd, fd_set* set); // 从集合中删除某一项 -- 标志位设为0
void FD_SET(int fd, fd_set* set); // 添加描述符到集合中 -- 标志位设为1
int FD_ISSET(int fd, fd_set* set); // 检测描述符是否存在 -- 检测标志位是否为1 返回标志位值6
```

## select 的缺点

- 每次调用select,都需要把fd集合从用户态拷贝到内核态,fd的数量很大时开销较大
- 每次调用select都需要在内核遍历传递进来的所有fd,fd数量很大时开销也很大
- select支持的文件描述符最大只是1024

## poll

```c
int poll(struct pollfd* fd, nfds_t nfds, int timeout);
struct pollfd {
    int fd; // 文件描述符
    short events; // 等待的事件
    short revents; // 实际发生的事件,内核给出的反馈
};
```

> fd 数组的地址(传的是struct pollfd数组)
>
> nfds 数组支持的最大长度,数组中最后一个使用的元素下标+1, 内核会轮询检测fd数组的每一个文件描述符
>
> tmeout
>
> - -1 永久阻塞
> - 0 调用完成立即返回
> - \> 0 等待的时长 (毫秒)



## epoll

- 生成一个epoll专用的文件描述符

  ```c
  int epoll_create(int size);
  ```

  > size epoll上能关注的最大描述符数量(超过会自动扩展)

- epoll操作 控制epoll文件描述事件,可以注册,修改删除

  ```c
  int epool_ctl(int epfd, int op, int fd, struct epoll_event* event);
  struct epoll_event {
      uint32_t events;
      epoll_data_t data;
  };
  typedef union epoll_data {
      void* ptr;
      int fd;
      uint32_t u32;
      uint64_t u64;
  }epoll_data_t;
  ```

  > - epfd: epoll_create生成的epoll专用的描述符
  > - op
  >   - EPOLL_CTL_ADD 注册
  >   - EPOLL_CTL_MOD 修改
  >   - EPOLL_CTL_DEL 删除
  > - fd 关联的文件描述符
  > - event 告诉内核要监听的事件
  >   - EPOLLIN 读
  >   - EPOLLOUT 写
  >   - EPOLLERR 异常

- epoll_wait等待io事件发生

  ```c
  int epoll_wait(int epfd, struct epoll_event* events, int maxevent, int timeout);
  ```

  > epfd 要检测的句柄
  >
  > events 用于回传待处理事件的数组 **是数组**
  >
  > maxevents 告诉内核events的大小
  >
  > timeout 设置超时时间
  >
  > - -1 永久阻塞
  > - 0 立即返回
  > - \> 0 等待指定时间后返回
  >

### epoll三种工作模式

- 水平触发模式

  - 只要放到对应的缓冲区有数据

  - epoll_wait就返回

  - 返回的次数与客户端发送数据的次数没有关系,因为每次读取的大小可能小于缓冲区存在数据的大小,然后就会往回在调用epoll_wait去检测,这样做使得epoll_wait的调用次数增大,影响性能

    ```c
    #include<stdio.h>
    #include<unistd.h>
    #include<stdlib.h>
    #include<sys/types.h>
    #include<sys/stat.h>
    #include<string.h>
    #include<arpa/inet.h>
    #include<sys/epoll.h>
    
    
    int main(int argc, const char* argv[])
    {
        if(argc < 2)
        {
            printf("eg; ./a.out port\n");
            exit(1);
        }
    
        struct sockaddr_in serv_addr;
        socklen_t serv_len = sizeof(serv_addr);
        int port = atoi(argv[1]);
    
        // 创建套接字
        int lfd = socket(AF_INET, SOCK_STREAM, 0);
        // 初始化
        memset(&serv_addr, 0, serv_len);
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
        serv_addr.sin_port = htons(port);
        // 绑定ip和端口
        bind(lfd, (struct sockaddr*)&serv_addr, serv_len);
        // 设置同时监听最大个数
        listen(lfd, 36);
        printf("start listen...\n");
    
        struct sockaddr_in cli_addr;
        socklen_t cli_len = sizeof(cli_addr);
        // 创建epoll根节点
        int epfd = epoll_create(2000);
        // 初始化epoll树
        struct epoll_event ev;
        ev.events = EPOLLIN;
        ev.data.fd = lfd;
        epoll_ctl(epfd, EPOLL_CTL_ADD, lfd, &ev);
        // 创建epoll扫描树
        struct epoll_event res_evs[2000];
        while(1)
        {
            // 使用epoll通知内核文件fd,委托内核进行文件io检测
            int ret = epoll_wait(epfd, res_evs, sizeof(res_evs)/ sizeof(res_evs[0]), -1);
            // 遍历返回结果
            for(int i = 0; i < ret; i++)
            {
                int fd = res_evs[i].data.fd;
                // 判断是否有新连接
                if(fd == lfd)
                {
                    // 接受连接请求
                    int cfd = accept(lfd, (struct sockaddr*)&cli_addr, &cli_len);
                    if(-1 == cfd)
                    {
                        printf("accept err\n");
                        exit(1);
                    }
                    // 将新的连接请求挂载到epoll的扫描树上
                    struct epoll_event acc_ev;
                    acc_ev.events = EPOLLIN;
                    acc_ev.data.fd = cfd;
                    epoll_ctl(epfd, EPOLL_CTL_ADD, cfd, &acc_ev);
                    // 打印连接的信息
                    char ip[64] = {0};
                    printf("new client ip: %s\t port %d\n", 
                            inet_ntop(AF_INET, &cli_addr.sin_addr.s_addr, ip, sizeof(ip)),
                            ntohs(cli_addr.sin_port));
                }
                else
                {
                    // 处理已连接的客户端发送的数据
                    if(!res_evs[i].events & EPOLLIN) continue;
                    // 读取数据
                    char buf[1024];
                    int len = recv(fd, buf, sizeof(buf), 0);
                    if(-1 == len)
                    {
                        printf("recv err\n");
                        exit(1);
                    }
                    if(0 == len)
                    {
                        printf("client close connection\n");
                        // 将fd从epoll的扫描树上去除
                        ret = epoll_ctl(epfd, EPOLL_CTL_DEL, fd, NULL);
                        if(-1 == ret)
                        {
                            printf("epoll_ctl del err\n");
                            exit(1);
                        }
                        close(fd);
                    }
                    else
                    {
                        printf("recv: %s\n", buf);
                        write(fd, buf, len);
                    }
                }
            }
        }
    
    
        close(lfd);
    
        return 0;
    
    }
    ```

- 边沿触发模式ET

  - 客户端给server发数据
    - 发一次数据,server的epoll_wait就返回一次
    - 不在乎数据是否读完,所以数据大于接收的大小时就会读不完,
    - 解决办法就是设置fd为非阻塞,使得recv可以持续读取,这就是边沿非阻塞

- 边沿非阻塞触发

  - 效率最高

  - 设置非阻塞

    - open()
      - 设置flags O_WDRW |O_NONBLOCK
      - 终端文件 /dev/tty
    - fcntl
      - int flag = fcntl(fd, F_GETFL);
      - flag |= O_NONBLOCK;
      - fcntl(fd, F_SETFL, flag);

  - 将缓冲区中的数据全部读出

    循环读取recv



查看文件描述符上限 ``cat/vim /proc/sys/fs/file-max``

在设置时不可以超过上述文件中规定的文件上限

通过配置文件修改文件描述符上限

- 查看当前配置 ``ulimit -a``
- 修改文件描述符上限 ``vim /etc/security/limits.conf``