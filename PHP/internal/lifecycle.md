# PHP生命周期

## cli

php_module_startup 模块舒适化

php_request_startup 请求初始化

php_execute_script   脚本执行

php_request_shutdown 请求关闭

php_module_shutdown  模块关闭



## fpm

- static 模式

  始终保持一个固定的子进程数

- dynamic

  动态控制子进程在start 和 max_children内

- ondemand

  按需,内存第一位,在一定时间范围内杀死空闲进程

主进程会管理子进程,如果子进程被杀死,master会再启子进程,master被杀死依旧可以进行请求处理