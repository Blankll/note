# PHP会话控制技术

## cookie

由服务器发送给客户端的片段信息，存储在客户端

## session

保存在服务器端, session_id保存在cookie中，session是基于cookie的

session配置信息

session.auto_start是否自动开启session

session.cookie_domain 存储sessionid的cookie的有效域名

session.save_path session文件在服务器的存储路径

session.use_cookie是否启用sessioncookie

session.save_handlersession存储句柄，可以将session存储到redis等中。

session_set_save_handler 设置session存储