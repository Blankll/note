# node

## ubuntu 升级node

```bash
sudo npm install -g n
sudo n latest # 安装官方最新版本
sudo n stable # 安装官方稳定版本
sudo n lts # 安装官方最新LTS版本
```

## module 和 module.export的区别
    1. module.exports 初始值为一个空对象 {}
    2. exports 是指向的 module.exports 的引用
    3. require() 返回的是 module.exports 而不是 exports

