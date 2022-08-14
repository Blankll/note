# composer

## 安装composer





## 下载依赖

```bash
composer install # 初次或者再次下载多个依赖
```





## 阿里云composer镜像

- 全局配置

  ```bash
  # 开启阿里云 composer全局配置
  composer config -g repo.packagist composer https://mirrors.aliyun.com/composer/
  # 取消阿里云全局配置
  composer config -g --unset repos.packagist
  ```

- 单项目配置

  ```bash
  # 开启阿里云 composer单项目配置
  composer config repo.packagist composer https://mirrors.aliyun.com/composer/
  # 取消阿里云单项目配置
  composer config --unset repos.packagist
  ```

  