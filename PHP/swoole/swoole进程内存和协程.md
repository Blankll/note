# swoole进程内存和协程

## process

```php
$process = new swoole_process(function(swoole_process $pro) {
    //child process todo
});
//create a child process
$pid = $process->start();
```

进程相关命令

ps aft | grep file

ps aux |grep file

pstree -p p_id

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