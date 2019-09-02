

# 本地化

## 时区

那是因为自 PHP5.0 开始，用PHP获取系统时间时，时间比当前时间少 8 个小时。原因是 PHP.ini 中没有设置 timezone 时，PHP 是使用的 UTC 时间，所以在中国时间要少 8 小时。因此你的时间都要 -8，所以代码是没问题的。

解决办法：

1.在PHP.ini文件中修改设置。

```ini
[Date]
; Defines the default timezone used by the date functions
date.timezone = Asia/Shanghai
```

