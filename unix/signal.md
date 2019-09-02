# signal

重点前31个信号





## 发送信号的方式

- kill 发送信号给指定进程

  kill(int pid, int sig)

- raise 自己给自己发信号

  int raise(int sig)

- abort

  自己给自己发送异常终止信号

  void abort(void)

- alarm 设置定时器

  每个进程只有一个定时器，

  unsigned int alarm(unsigned int second)

  当时间到达之后，函数发出一个信号：SIGALRM

- setitimer 定时器，实现周期性定时

  ```c
  // 函数原型
  int setitimer(int which, const struct itimerval* new_value, struct itimerval* old_value);
  
  struct itimerval {
      struct timeval it_interval; // 定时器循环周期
      struct timeval it_value; // 第一次触发定时器的时间
  };
  struct timeval {
      time_t tv_sec; /* seconds */
      suseconds_t tv_usec; /* microseconds */
  };
  ```

## 信号集

未决信号集(kenel pcb)

没有被当前进程处理的信号

阻塞信号集(kenel pcb)

将某个信号放到阻塞信号集这个信号就不会被进程处理

阻塞被解除之后，信号被处理，变成递达状态

自定义信号集



信号处理流程

​	信号产生，信号处于未决状态，进程收到信号之后，信号被放入未决信号集，

​	放入未决信号集中的信号等待处理，在处理之前





## deamon

```c
#include<stdio.h>
#include<signal.h>
#include<stdlib.h>
#include<unistd.h>

int main(void)
{
	// create a session
	// let child process become the header of session
	pid_t pid = fork();
	
	// kill father process
	if(pid > 0) exit(1);
	if(pid == 0)
	{
		// make child process become header of session
		// header of session is a deamon
		setsid();
		// keep child process alive
		while(1) sleep(1);
	}

	return 0;
}
```

