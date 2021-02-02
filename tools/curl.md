# curl

不带任何参数，curl默认发出get请求

```bash
curl https://www.baidu.com
```

-A 指定User-Agent

-H 直接指定

-b 指定发送cookie

```bash
curl -b 'cookie1=one;cookie2=two' https://google.com
curl -b cookies.txt https://www.google.com #携带文件中的cookie信息
```

-c 将服务器设置的cookie存入到文件中

```bash
curl -c cookies.txt https://www.google.com
```

-d 添加request-body参数，使用`-d`参数以后，HTTP 请求会自动加上头`Content-Type : application/x-www-form-urlencoded`

如果指定为get方法则变为request-param

```bash
curl -d'login=emma＆password=123'-X POST https://google.com/login
curl -d '@data.txt' https://google.com/login
```

-e 指定Referer(也可以通过-H实现)

```bash
curl -e 'https://google.com?q=example' https://www.example.com
```

-F发送二进制内容(Content-Type: multipart/form-data)

```bash
curl -F 'file=@photo.png' https://google.com/profile
# 指定MIME类型，文件名
curl -F 'file=@photo.png;;filename=name.png;type=image/png' https://google.com/profile
```

-v，--trace打印传输过程，用于调试

-x参数指定 HTTP 请求的代理

-X 指定 HTTP 请求的方法