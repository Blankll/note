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

