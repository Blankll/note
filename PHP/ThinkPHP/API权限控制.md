# API权限控制

在api开发中不存在用户登录概念，通过令牌进行用户身份验证



1. 验证Token是否合法
2. 验证Token是否将有效
3. 匹配Token组对应的Auth权限


##权限获取流程

[获取令牌]

[访问接口]

[基于微信的身份认证体系]



service层： 位于model层之上，将比较复杂的业务写在service层中，粒度细且较为简单的业务写在model层之中

model层除了处理业务之外，还有ORM模型的实现功能，service可以理解为model的业务分层，将与ORM无关的操作且业务比较复杂性较高的部分写在service中

### 在微信中获取用户数据

``code``[^1]: 登录凭证，进而获取用户登录态信息

``openid``: 唯一标识

``session_key``: 会话密钥，用户数据的加解密需要依赖会话密钥完成

调用微信的api地址，获取``openid ``和``session_key``

### 微信获取用户信息流程

1. 小程序客户端通过``wx.login(OBJECT)``函数获取``code``

2. 小程序通过调用开发者开发的接口将``code``码发送到服务器端

3. 服务器调用微信官方接口，将``appid``,``secret``,``js_code[code]``,``grant_type``发送给这个接口

   > 接口地址：https://api.weixin.qq.com/sns/jscode2session?appid=APPID&secret=SECRET&js_code=JSCODE&grant_type=authorization_code

4. 微信服务器将``openid``和``session_key``返回给服务器

5. 小程序端调用``wx.checkSession``可以查看当前是否处于登录状态[处于登录状态或者是登录失效]

###TP5编写公共函数

**在application/common.php**中编写的所有函数可以在框架内直接调用

### 实现Token身份权限体系

1. 配置小程序[在.env中或在application目录下建一个extra文件下编写配置文件]```appid``` ```appsecret``` ```login_url``` 
2. 通过body的raw传递通过wx.login获取的login参数参数[json]格式，[小程序调用wxrequest]
3. 服务器端将调用微信官方接口，获取openid和session_key;
4. 检测openid是否已存在与项目数据库中，如果不存在就将该openid插入数据库中
5. 生成令牌，准备缓存数据，
6. 将缓存数据存入缓存中，
7. 将令牌发送给客户端

**TP5默认缓存文件位置 /runtime/cache中**

[^1]: 有效期五分钟 

