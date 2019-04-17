# Vue

## 初始化vue项目

```bash
## 1安装vue-cli
sudo npm install --global vue-cli
## 初始化
vue init webpack name
```



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

   

   ### 在项目中使用stylus

   1. npm install stylus --save
   2. npm install stylus-loader --save
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

### axios全局拦截器

```javascript
// 请求拦截
axios.interceptors.request.use(function(config){
	return config;
});
// 响应拦截
axios.interceptors.response.use(function(response){
    return response;
});
```




## vue的事件监听

```javascript
var example2 = new Vue({
  el: '#example-2',
  data: {
    name: 'Vue.js'
  },
  // 在 `methods` 对象中定义方法
  methods: {
    greet: function (event) {
      // `this` 在方法里指向当前 Vue 实例
      alert('Hello ' + this.name + '!')
      // `event` 是原生 DOM 事件
      if (event) {
        alert(event.target.tagName)
      }
    }
  }
})
```

### vue-router路由传参

```javascript
// 路由
bookInfo (id) {
  this.$router.push({ path: '/book/info/' + id })
}
// 接收路由参数
data () {
   return {
      id: this.$route.params.id,
   }
}
```

方法2

```javascript
bookSelect (book) {
      console.log(book)
      this.$router.push({ path: '/bookinfo', query: { id: book.id }})
    }
data () {
    return {
      id: this.$route.query.id
    }
  }
```



## vuex

1. 安装vuex

2. npm install vuex --save

3. 重启服务器

4. 引入vuex
   1. 在src下创建stroe目录
   2. 在store目录下创建index.js文件     

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

5. 在main.js中引入

       ```javascript
      import store from './store'
         ...
         new Vue({
             el:'#app',
             router,
             store,
             ...
         })
       ```

6. 使用

  - 动作 actions

    actions相当于定义了一系列操作mutaions的动作

    actions
    在actions中定义提供给前端调用的action

    ```javascript
    import Vue from 'vue'
    import Vuex from 'vuex'
    
    Vue.use(Vuex)
    
    export default new Vuex.Store(
        state: {
        city: '上海'
        },
        actions: {
            changeCity (context, city) {
                context.commit('changeCity', city)
            }
        },
    // 创建mutations
            mutations: {
                changeCity (state, city) {
                    state.city = city
                }
            }
    )
    ```

    在前端需要通过调用dispatch来调用actions的方法，进而使得actions中获取状态或者是通过commit更改状态

    **综上，组件调用actions，actions调用mutations，mutations改变state**

    ```javascript
    // 在vue中调用
    methods: {
        handleCityClick (city) {
          // changeCity 派发一个changeCity的action， 传递的参数为city
          this.$store.dispatch('changeCity', city)
    }
    }
    ```

    mutations中不能存在异步操作而actions中可以存在，如果不涉及复复杂操作或者异步操作，也可以不经过actions，直接在前端调用mutations的方法来获取或更新状态

    ```javascript
    // 在前端直接调用mutations中的方法
    this.$store.commit('changeCity', city)
    ```

    

  - 创建状态 state

  - mutations

  - getters

  

  mutations 有一个固有参数 state，接收的是 Vuex 中的 state 对象

  action 也有一个固有参数 context，但是 **context 是 state 的父级**，包含  state、getters

  ### vuex高级操作

  修改项目结构

  可以将state，mutations，actions对象分别新建state.js, mutations.js, actions.js将对象分别定义在这三个模块中，然后在store/index.js中将他们引入

  ```javascript
  import Vue from 'vue'
  import Vuex from 'vuex'
  import state from './state'
  import actions from './actions'
  import mutations from './mutations'
  
  Vue.use(Vuex)
  
  export default new Vuex.Store({
      state:state,
      actions: actions,
  	// 创建mutations
     mutations: mutations
  })
  ```

  

  以上key与value的值相同，可以进一步简化

  ```javascript
  import Vue from 'vue'
  import Vuex from 'vuex'
  import state from './state'
  import actions from './actions'
  import mutations from './mutations'
  
  Vue.use(Vuex)
  
  export default new Vuex.Store({
      state,
      actions,
     mutations
  })
  ```

  这样就可以将数据分块进行处理避免代码混乱,提高可维护性

  子啊视图中直接使用state数据

  ```vue
  <div>
    {{this.$store.state.city}}
  </div>
  ```

  可以使用展开运算符简化上述操作

  ```js
  import { mapState } from 'vuex'
  export default {
      name: 'HomeHeader',
      computed: {
          // 将state中的状态city映射到computed的city属性中, 调用时就相当于调用vue的computed属性一样
          ...mapState(['city'])
      }
  }
  ```

  若要在computed中使用不同的属性名字进行映射，可以使用如下方法

  ```javascript
  import { mapState } from 'vuex'
  export default {
      name: 'HomeHeader',
      computed: {
          // 将state中的状态city映射到computed的currentCity属性中, 调用时就可以通过currentCity来获得city的状态
          ...mapState({
              currentCity: 'city'
          })
      }
  }
  ```

  同样可以通过使用展开运算符来映射mutations

  ```javascript
  
      import { mapMutations } from 'vuex'
      export default {
          name: 'HomeHeader',
          methods: {
              // 将changeCity的mutation映射到methods中，方法名称同样为changeCity
              ...mapMutations(['changeCity'])
          }
      }
  
  ```

  在前端调用mutation时就可以将``this.$store.commit('changeCity', city)`` 直接向调用``this.changeCity(city)``来调用mutations中定义的方法

  getters类似于computed方法，可以将状态进行一定计算后将结果返回给前端

  ```javascript
  import { mapState, mapGetters } from 'vuex'
  export default {
      name: 'HomeHeader',
      computed: {
          // 将state中的状态city映射到computed的currentCity属性中, 调用时就可以通过currentCity来获得city的状态
          ...mapState({
              currentCity: 'city'
          }),
          // 同样的，在前端中就可以直接像调用computed属性一样使用了，
          ...mapGetters(['doubleCity'])
      }
  }
  ```

  ### module

  复杂vuex分模块