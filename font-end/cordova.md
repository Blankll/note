# 使用cordova

1. 安装cordova

   ```bash
   npm install -g cordova 
   ```

2. 新建项目

   ```bash
   cordova create MyApp
   ```

3. 添加浏览器环境

   ```bash
   cordova platform add browser
   ```

4. 配置android环境

   - 要配置号java环境，JAVA_HOME

     ```bash
     # use oracle jdk8
     export JAVA_HOME=/usr/lib/jvm/java-8-oracle
     export PATH=$JAVA_HOME/bin:$PATH
     ```

   - 安转android studio

     自行百度，安装完android studio后再安装android sdk, 创建一个空的anroid工程，这个过程中andorid studio会下载gradle, 默认安装在android studio安装目录下面的gradle目录下

   - 配置ANDROID_HOME

     这里要注意ANDROID_HOME目录到Sdk就可以了,同时将platform-tools和tools添加到环境变量中

     ```bash
     export ANDROID_HOME=/home/seven/Android/Sdk
     export PATH=$PATH:/home/seven/Android/Sdk/platform-tools:/home/seven/Android/Sdk/tools
     ```

   - 配置gradle　这个构建工具在android studio安装的时候会被android studio安装创建好项目之后会下载到android studio安装目录下,但是并不会添加到环境变量中，我们无法用命令行执行，所以我们需要手动添加到环境变量中

     ```bash
     # cordova android
     export PATH=$PATH:/opt/google/android-studio/gradle/gradle-4.10.1/bin
     ```

     /opt/下可能没有执行权限, 775一下即可

     使用cordova requirements 查看安装环境是否可以被cordova正确识别和环境是否满足

   - 添加平台　添加要开发的目标平台，ios只能在mac上操作，所以这里直说android

     ```bash
     cordova platform add android
     # 可以查看已添加的平台
     cordova platform ls
     ```

   - 可以写代码了

   - 运行

     ```bash
     cordova run browser
     ```

   - 真机运行

     ```bash
     adb devices
     cordova run android
     ```

   - 打包项目

     ```
     cordova build android
     ```

## 坑

在build的时候可能出现各种错误

- No installed build tools found. Install the Android build tools version 19.1.0 or higher.

  这个错误尝试了各种办法都不行，明明是有的，但就是不行，所以我找到了一个偏方

  ```
  // availableBuildToolsVersions = getAvailableBuildTools()
  // 里面的是sdk的版本
  availableBuildToolsVersions = ['28.0.3','28.0.2','27.0.3'] as String[]
  
  ```

- You have not accepted the license agreements of the following SDK components

  删除原来的android-sdk-licences

  运行

  ```bash
  cho -e "\n8933bad161af4178b1185d1a37fbf41ea5269c55" > "$ANDROID_HOME/licenses/android-sdk-license"
  ```

打包教程 https://www.jianshu.com/p/2e9bebb73d37

- 查看配置

  ```bash
  cordova requirements
  ```

- Androidstudio在更新后会更新gradle但是~/.bashrc文件下的配置并不会更新,需要手动更新配置文件

- 使用 `cordova run android` 运行时，出现错误

  ```bash
  A problem occurred configuring root project 'android'. > Could not resolve all files for configuration ':classpath'. > Could not resolve com.android.tools.build:gradle:3.0.0. Required by: project : > Could not resolve com.android.tools.build:gradle:3.0.0. > Could not get resource 'https://dl.google.com/dl/android/maven2/com/android/tools/build/gradle/3.0.0/gradle-3.0.0.pom'. > Could not HEAD 'https://dl.google.com/dl/android/maven2/com/android/tools/build/gradle/3.0.0/gradle-3.0.0.pom'. > dl.google.com
  ```

  将 `android/build.gradle`  `android/app/build.gradle` `android/CordovaLib/build.gradle`中 的所有 `repositories`改为

  ```bash
  repositories {
      jcenter()
         maven {
             url "http://maven.aliyun.com/nexus/content/groups/public/"
      }
  }
  ```

  