# php debug

安装时添加 --enable-debug关闭系统编译优化

```bash
gdb dir/bin/php # 调试php程序
b ZEND_ECHO_SPEC_CV_HANDLER # 打断点
r dir/script.php # 运行要调试的代码
n # 下一步
p # 打印对应的参数
c # 下一个断点处
```

