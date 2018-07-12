# Vue



## vue中的单文件组件与路由

@符号表示src目录

### 页面间的路由跳转

``<router-link></router-link>``

```vue
//to="/list" 在路由中注册的路由地址
<div>
    <div class="home">home</div>
    <router-link to="/list">跳转到列表页</router-link>
</div>
```

### 初始化项目

```css
<meta name="viewport" content="width=device-width,initial-scale=1.0,
    minimum-scal=1.0,maximum=1.0,user-scalable=no">
```

### 引入reset统一不同设备的默认样式

1. 将reset.css保存到src/asset/styles目录下

2. 在main.js中引入css样式，全局作用

   import './assets/styles/reset.css'

## 在项目中引入第三方库

### 案例--解决移动端点击三百毫秒延迟

1. 安装 nmp install fastclick --save

2. 全局使用

   ```javascript
   import Vue from 'vue'
   import App from './App'
   import router from './router'
   import fastClick from 'fastclick'
   import './assets/styles/reset.css'
   import './assets/styles/border.css'

   Vue.config.productionTip = false
   fastClick.attach(document.body)
   /* eslint-disable no-new */
   new Vue({
     el: '#app',
     router,
     render: h => h(App)
   })
   ```

   ### 使用iconfont

   1. 登录iconfont帐号，新建项目
   2. 将所需图标添加到购物车中，在将它添加到项目中，然后下载
   3. 解压文件，然后将字体样式复制到资源文件夹/iconfont目录下
   4. 将iconfont.css赋值到资源文件夹下，即iconfont目录和iconfont.css文件处于同级目录下
   5. 更改iconfont.css引用字体的路径
   6. 删除class
   7. 全局引入iconfont  在main.js中 import './asset/styles/iconfont.css'

   ​

   ### 在项目中使用stylus

   1. npm install stylus --save
   2. nmp install stylus-loader --save
   3. 使用 l在要使用的地芳加lang="stylus"
   4. 局部化 加scoped

   ## 给路径起别名

   在build/目录下的webpack.base.conf.js文件中的resolve对象下的alias下添加

   ```javascript
     resolve: {
       extensions: ['.js', '.vue', '.json'],
       alias: {
         '@': resolve('src'),
         'styles': resolve('src/assets/styles'),
       }
     }
   ```

   但在css中应用时要加～符号

   重新npm run start

   ​

   ##vue中首页轮播的实现

   ### 创建git分支

   ### 轮播

   vue-awesome-swiper

## axios数据请求

1. 安装 npm install axios --save
2. 重启服务

### 设置请求代理

vue项目中只有static目录可以被外部访问

通过设置代理，可以模拟出访问api的效果，代理将请求转发到static的目录中指定的文件

zaiconfig/index.js中设置代理

```javascript
    proxyTable: {
      '/api': {
        target: 'http://localhost:8080',
        pathRewrite: {
          '^/api': '/static/mock'
        }
      }
    },
```

重启服务器





## vuex

1. 安装vuex

2. npm install vuex --save

3. 重启服务器

4. 引入vuex

   > 1. 在src下创建stroe目录
   > 2. 在store目录下创建index.js文件

   ```javascript
   import Vue from 'vue'
   import Vuex from 'vuex'

   Vue.use(Vuex)

   export default new Vuex.Store({
       state: {
           // 共用数据名称
       }
   })
   ```

   ​