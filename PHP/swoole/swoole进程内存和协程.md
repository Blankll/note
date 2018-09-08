# swoole进程内存和协程

## process

```php
$process = new swoole_process(function(swoole_process $pro) {
    //child process todo
});
//create a child process
$pid = $process->start();

```

```php
swoole_process::__construct(callable $function, $redirect_stdin_stdout = false, $pipe_type = 2);
```



- mixed $function 子进程创建成功后执行的函数
- $redirect_stdin_stdout 重定向子进程的输入和输出，启用后，在进程内echo将不是打印到屏幕，而是写入到管道。读取键盘输入将变成从管道中读取，　默认为阻塞读取
- $create_pipe是否创建管道，　启用 \$redirect_stdin_stdout后会忽略用户参数强制开启为true,如果子进程内没有进程间通信，可以设置为false
- 管道类型
  - `0`：不创建管道
  - `1`：创建`SOCK_STREAM`类型管道
  - `2`：创建`SOCK_DGRAM`类型管道
  - 启用`$redirect_stdin_stdout` 后，此选项将忽略用户参数，强制为`1`

进程相关命令

ps aft | grep file

ps aux |grep file

pstree -p p_id

## 进程事件

```php
<?php
$workers = []; // array to save processes
$worker_num = 3; // process number

for($i = 0; $i < $worker_num; $i++)
{
    $process = new swoole_process('doProcess'); //create new sub process
    $pid = $process->start(); // start sub process
    $workers[$pid] = $process; // save to array
}

function doProcess(swoole_process $process)
{
    $process->write("PID:$process->pid"); // wirte info to pipe
    echo '写入信息:'.$process->id.PHP_EOL.$process->callback;
}
// process event, add even to all sub process to execute
foreach($workers as $process)
{
    swoole_event_add($process->pipe, function($pipe) use($process){
        $data = $process->read(); //read inof
        echo "数据:".$data.PHP_EOL;
    });
}
```

## swoole锁机制

swoole_lock类支持5种锁的类型：

1. 文件锁 SWOOLE_FILELOCK
2. 读写锁 SWOOLE_RWLOCK
3. 信号量 SWOOLE_SEM
4. 互斥锁 SWOOLE_MUTEX
5. 自旋锁 SWOOLE_SPINLOCK

```php
<?php

$lock = new swoole_lock(SWOOLE_MUTEX);
echo '创建互斥锁'.PHP_EOL;
$lock->lock();// 开始锁定，主进程
// php中的进程模块
if(pcntl_fork() > 0)
{
    sleep(3);
    $lock->unlock();
}
else
{
    echo '子进程等待锁'.PHP_EOL;
    $lock->lock();
    echo '子进程，获取锁'.PHP_EOL;
    $lock->unlock();
    exit();
}

echo '主进程释放锁'.PHP_EOL;
unset($lock);
```

### swoole 查询dns

```php
swoole_async_dns_lookup('www.baidu.com', function($host, $ip) {
    echo "$host".PHP_EOL;
    echo "$ip".PHP_EOL;
});
```



## 内存

- swoole_table 基于共享内存和锁实现的高性能并发数据结构

  ```php
  // create a swoole table
  $table = new swoole_table(1024);
  $table->column('id', TYPE_INT);
  $table->column('name,' TYPE_STRING, 32);
  $table->column('age', TYPE_INT);
  $table->create();
  
  //insert a data to swoole table
  $table->set('data_keky', ['id' => 1, 'name' => 'seven', 'age' => 18]);
  $table['data_keky'] = ['id' => 1, 'name' => 'seven', 'age' => 18];
  //get data
  $table->get('data_key');
  $table['data_key'];
  ```

  创建的进程生命周期结束后，表和内容也会被销毁



## 协程coroutine

同步的代码实现异步的效果，协程必须在onRequest, 等事件的回调方法中