# CMS

## 微信模板消息

1. 支付后，可以发送3条模板消息，7天内有效，通过prepay_id来标识
2. 提交表单声明要发送模板消息，可以发送一条

### 流程

1. 获取access_token





## CMS跨域

1. 在thinkPHP的``application/api``目录下创建目录``behavior``

2. 编写CORS类

   ```php
   <?php
   
   namespace app\api\behavior;
   
   class CORS {
       public function appInit(&$params)
       {
           header('Access-Control-Allow-Origin: *');
           header('Access-Control-Allow-Headers: token, Origin, X-Requested-With, Content-Type, Accept');
           header('Access-Control-Allow-Methods: GET, POST');
           if(request()->isOptions()) exit();
       }
   }
   ```

3. 在``application/tags.php``中注册行为

   ```php
   <?php
   
   // 应用行为扩展定义文件
   return [
       // 应用初始化
       'app_init'     => [
           'app\api\behavior\CORS'
       ],
       // ...
   ];
   
   ```

   