# swoole异步TCP

1. 建立TCP服务器
2. 设置异步进程工作数
3. 投递异步任务

```php
<?php
// create tcp server
$serv = new swoole_server('0.0.0.0', 8811);
// set async process number
$serv->set(['task_work_num' => 4]);
// send async work

$serv->on('receive', function($sev, $fd, $from_id, $data) {
    $task_id = $sev->task($data);
    echo "async id ".$task_id.PHP_EOL;
});

// deal with async work
$serv->on('task', function($sev, $task_id, $from_id, $data){
    echo "execute async id".$task_id.PHP_EOL;
    $sev->finish("$data->ok");
});

// finish work
$serv->on('finish', function($sev, $task_id, $data){
    echo "work finished\n";
});

$serv->start();
```

