## CORS(Cross-Origin Resource Sharing) 

同源策略规定了如果两个 url 的协议、域名、端口中有任何一个不等，就认定它们跨源了。

跨源的结果：

- 不能获取 Cookie、LocalStorage、IndexedDB；

- 不能获取 dom 节点；

- 不能进行一般的 Ajax 通信；

CORS 分为简单请求以及非简单请求。

- 简单请求： `POST`、`GET`、`HEAD` 

- 非简单请求 `PUT`、`DELETE`



可以在 chrome 的 Network 中看到多了一次 `Request Method` 为 `OPTIONS` 的请求

非简单请求会在请求进行时提前进行一次OPTIONS请求，通常称之为预请求，只有预请求得到浏览器设置的`Access-Control-Allow-Methods:Method`返回头，浏览器才会进行真正的非简单请求。

## vue中的CORS解决方案

## 开发环境中使用proxyTable

在开发环境中，可以使用proxyTable通过node.js来进行路由重定向

在`/config/index.js`中的dev项中添加路由重定向规则

```javascript
dev: {
    // Paths
    assetsSubDirectory: 'static',
    assetsPublicPath: '/',
    proxyTable: {
      '/api': {
        // 请求的目标
        target: 'http://127.0.0.1',
        pathRewrite: {
          '^/api': ''　// 将api替换为'',此时　请求地址为/api/login就会被替换为http://127.0.0.1/login
        }
      }
    },
	...
  },
```

但是在上线打包之后就没有办法使用这种方式了

### 上线时通过nginx反向代理实现CORS跨域请求

在上线后，无法使用proxyTable,此时，我们可以通过nginx来将uri以api开头的请求重定向到接口所在的服务器。

```bash
location /api {
                add_header 'Access-Control-Allow-Origin' '*';
                # 末尾不加/会将匹配的/api也加在后面，即代理后的uri和请求的uri一致
                # 末尾加/就会将匹配到的/api去除，重定向后的uri为本次请求的uri去掉/api
                proxy_pass http://apitrans.geekfun.club/;
        }
```

## 解决上线后刷新路由失效404问题

在上线后会出现刷新时直接报404错误的问题，查了才知道，在使用histroy的历史模式时用户刷新后直接访问对应的路由，而上线部署的是静态文件,nginx直接区访问路由对应的静态资源肯定是找不到对应的数据的，所以需要对nginx进行小小的配置。

> `vue-router` 默认 hash 模式 —— 使用 URL 的 hash 来模拟一个完整的 URL，于是当 URL 改变时，页面不会重新加载。

> **history 模式**，这种模式充分利用 `history.pushState` API 来完成 URL 跳转而无须重新加载页面。



在服务端增加一个覆盖所有情况的候选资源：如果 URL 匹配不到任何静态资源，则应该返回同一个 `index.html` 页面，这个页面就是你 app 依赖的页面。

```shell
# file_name three
server {
        listen 80;
        server_name three.domain.com;

        root /var/www/html/trans;
        index index.html index.js;
        # 通过定位静态文件位置，可以结局vue.js history模式下刷新路由失效问题
        location / {
                try_files $uri $uri/ /index.html;
        }
}
```

这样就可以解决刷新404的问题了。