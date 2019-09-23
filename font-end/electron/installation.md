# 创建electron vue-cli3项目
- 安装，更新vue-cli3
```bash
vue -V
cnpm uninstall vue-cli -g
cnpm install @vue/cli -g
cnpm update @vue/cli -g
```
- 创建vue-cli3项目
```bash
vue create electron-one
cd electron-one
cnpm install electron --save-dev
```
- 在vue-cli3控制面板中安装``vue-cli-plugin-electron-builder``
- 运行
```bash
cnpm run electron:serve
```
- 打包应用
```bash
cnpm run electron:build
```