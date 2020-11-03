# shell basic

$0 脚本名称

$1 传入的第一个参数

$2 传入的第二个参数，以此类推

$@ 传入的所有参数

$* 传入的所有参数



```bash
# 取一个命令执行后的值
datestr=$(date "+%Y-%m-%d %H:%M:%S")
echo $datestr
# -n 取消改行输出的回车
echo -n $datestr
```

列表截取操作

```bash
# 以空格为分界截取列，取每一行的第二列
cut -d' ' -f2 filename
```

重定向

```BASH
grep something file.list 2>/dev/null
```

STDIN 0

STDOUT 1

STDERR 2



tips

```bash
alias ipi='ipconfig getifaddr en0'
```

