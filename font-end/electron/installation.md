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

## 使用serial port
在electron项目中直接``npm install --save serialport``有很大的可能性无法使用，原因在于，electron的node版本和本地运行时node版本可能并不一样，执行安装命令行时匹配的是本地安装的node运行时，所以为了在electron中使用，需要重新编译、

- 安装编译需要的环境windows
    -  python2.7 (必须)  python3 不兼容.
    - 本地安装vs 或者  npm install windows-build-tools -g  推荐后者
    - node-gyp npm install node-pre-gyp -g
    - 进入electron项目根目录
    - npm install --save serialport
    - cnpm install --save-dev electron-rebuild
    - 重新编译 ``.\node_modules\.bin\electron-rebuild.cmd``
- linux下超级简单
    - npm install --save serialport
    - cnpm install --save-dev electron-rebuild
    - 重新编译 ``./node_modules/.bin/electron-rebuild``

- 在vue环境中还需要进一步配置(只针对vuecli3 + electron + vue-cli-plugin-electron-builder)
    在项目的根目录下新建一个文件 ``vue.config.js``
    ```js
    module.exports = {
      pluginOptions: {
        electronBuilder: {
        externals: ['serialport']
        }
      }
    }
    ```
