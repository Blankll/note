# PHP命名空间

## 基于psr-4的composer自动引入

1. 在项目根目录创建composer.json文件

2. 添加自动加载规则

   ```json
   {
       "autoload": {
           "psr-4": {
               "App\\": "app/"
           }
       }
   }
   ```

3. 在跟目录运行composer dump-autoload``composer已安装``