# 创建electron vue-cli3项目
- 安装，更新vue-cli3
    ```bash
    vue -V
    # 卸载老的vue-cli2.xx
    cnpm uninstall vue-cli -g
    # 安装vue-cli3.xx
    cnpm install @vue/cli -g
    # 更新vue-cli3.xx
    cnpm update @vue/cli -g
    ```
- 安装electron环境
    ```bash
    cnpm install -g electron
    cnpm install -g electron-builder
    ```
    > 不安装electorn-builder会出现`` /d /s /c electron-builder install-app-deps" error, exit code 1`` 的错误

- 创建vue-cli3项目
    ```bash
    vue create electron-one
    cd electron-one
    cnpm install electron --save-dev
    ```
- 在vue-cli3控制面板中安装``vue-cli-plugin-electron-builder``
    ```bash
    vue ui
    ```
- 运行
    ```bash
    cnpm run electron:serve
    ```
- 打包应用
    ```bash
    cnpm run electron:build
    ```