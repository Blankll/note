# response web

##  单位

- 设备像素：物理像素 ppi 

- 逻辑像素：一个或多个物理像素 对应一个逻辑像素

- css像素：dpr = 设备像素/css像素

  设备像素设备管理，逻辑像素自由配置，样式像素依据dpr

## 视口

### 理想是视口：设备厂商定义

```javascript
window.screen.width
```

www.viewportsize.com

### 布局视口: 设备产商定义

```
document.documentElement.clientWidth
```

### 视觉视口

> meta view  标签用来调整视口

#### width属性

- 固定取值：400取值， 不建议固定设置，响应式的弹性会失去
- device-width: width = device-width意味着 布局视口= 理想视口

### user-scalable 

是否允许用户缩放比例

### inital-scal 

用户缩放级别

## 媒体查询

```css
@media [not|only] type [and] (expr) {
    rules
}
```

- type 设备类型

- (expr) 媒介特性

  常见的媒介特性： 

  - width 描述设备显示区域的宽度
  - height 描述设备显示区域的高度
  - orientation 设备方向 portrait|landscape
  - resolution 设备分辨率

## 设计稿

一般用sketch、Photoshop；

 主流的width： 750

### flex布局

http://www.runoob.com/w3cnote/flex-grammar.html

## 预处理

sass、stylus、less

使用参照官方开发者文档

## flexible 方案

解决百分比单位局限性、多设备差异问题

### css 	中的详细单位

- px 任何屏幕下最小可见单位
- em 相对尺寸单位，相对父容器的单位、可能在每个容器中都不一样
- rem 相对于根节点元素的font-size的值

## 测试

远程测试平台：阿里云测试、优测等

多真机同步测试，ghostlab

## 实战

1. 新建项目文件夹，使用npm init初始化项目

2. 规划目录

3. 引入构建工具 gulp 

   1. npm install -g gulp 全局安装 npm install --save-dev gulp 对本项目有效

   2. 在json中引入

      ```json
      //package.json
        "scripts": {
          "test": "echo \"Error: no test specified\" && exit 1",
          "build": "gulp"
        },
      ```

      

   3. 创建配置文件： 在项目根目录下建gulpfile.js

      ```javascript
      var gulp  = require('gulp');
      // 默认任务
      gulp.task('default',function() {
      
      });
      ```

      

4. 代码编写，包括样式清除、确定断点、基础布局

   - 清除默认样式 reset.css

   - 启动本地node服务器 anywhere 如果command not found 就 npm install -g anywhere

   - 引入flexible， 在页面中直接将js代码放上，给定一个fontsize值

     > npm install --save-dev gulp-postcss postcss-px2rem



## 插件

- 自动补全浏览器支持 autoprefix 安装后在gulpfile中配置
-  css压缩 cssnano npm install --save-dev



## 未来新标准

viewport unit 视窗相对单位