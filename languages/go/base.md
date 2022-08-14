## go连接数据库

```bash
go get github.com/go-xorm/xorm
go get github.com/go-sql-driver/mysql
```

## gowebsocket

fwebsocket的请求以ws开始

```
ws://127.0.0.1/chart?id=1
```



go fmt格式化代码

go test 运行test

go test -v 显示详细信息

go的test不保证test顺序执行

coroutine

- 轻量级
- 非抢占式多任务处理，由协程主动交出控制权
- 编译/解释 器 /虚拟机层面的多任务
- 多个协程可能在一个或多个线程上运行
- 调度器在合适的点进行切换
- 使用-race来检测数据冲突

 子程序是协程的一个特例

```go
runtime.Gosched() // 主动交出控制权
```



### goroutine可能切换的点

- I/O, select
- channel
- 等待锁
- 函数调用（有时）
- runtime.Gosched() 

### channel

channel是goroutine和goroutine之间的交互



GO语言的并发编程模型基于一篇论文 Communication Sequential Process(CSP)



不要通过共享内存来通信，通过通信来共享内存



