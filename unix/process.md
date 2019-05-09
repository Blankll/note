# process

ps aux

a 所有信息

x 不依赖终端的进程



kill 发送信号给进程

kill -l 查看支持的信号

1-31 用户执行的信号

kill -9 无条件杀死一个进程

1，lsof -i:端口号

2，netstat -tunlp|grep 端口号

这两个命令都可以查看端口被什么进程占用。



## wait waitpid 进程回收

wait -阻塞等待回收进程

> pid_t wait(int* status) 成功返回回收进程的id，失败返回-1 每一次调用只会回收一个子进程

## pipe

```c
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main(void)
{
   int fd[2];
   int pip = pipe(fd);
   if(pip == -1)
   {
       printf("create pipe failed\n");
       exit(1);
   }

  pid_t pid = fork();
  if(-1 == pid)
  {
      printf("create new process faild\n");
     exit(1);
  }

  // father process write message to pipe
 if(0 < pid)
 {
       // close read side
      close(fd[0]);
      // stdout > pipe write side
      dup2(fd[1], STDOUT_FILENO);
      execlp("ps", "ps", "aux", NULL);
  }
  // child process read message from pipe
  if(0 == pid)
  {
      // close write side
      close(fd[1]);
      // stdin > pipe read side
      dup2(fd[0], STDIN_FILENO);
      execlp("grep", "grep", "bash", NULL);
  }
  printf("pipe [0]%d\n", fd[0]);
  printf("pipe [1]%d\n", fd[1]);

  close(fd[0]);
  close(fd[1]);

  return 0;
}
```

### 终止进程

```c
exit(int num);
kill(getpid(), SIGKILL);
raise(SIGKILL);
abort();
```

