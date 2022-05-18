# cookie

Cookie 由如下字段组成

![cookie](../../statics/cookie.png)

其中 Name cookie的名称

- Value: cookie的值
-  Size：cookie的大小

- 
-  Domain
-  Path
- Expires/Max-Age
-  HttpOnly
-  Secure
-  SameSite
-  SameParty
-  PartitionKey
-  Priority

## Same-origin policy & same-site

Same-origin(同源策略)规定了如果两个URL的`protocol`,`host`,`port`即协议、域名、端口完全相同则为同源，否则就跨源(跨域)了。

跨源的结果：

- 不能获取 Cookie、LocalStorage、IndexedDB；

- 不能获取 dom 节点；

- 不能进行非简单请求；

CORS 分为[Simple requests](https://developer.mozilla.org/en-US/docs/Web/HTTP/CORS#simple_requests)(简单请求)以及非简单请求。

- 简单请求： `POST`、`GET`、`HEAD` 

- 非简单请求 `PUT`、`DELETE`

所以`non-Same-origin`(非同源)的`non-Simple request`(非简单请求)是不被直接允许的，需要进行[CORS preflight](https://developer.mozilla.org/en-US/docs/Glossary/Preflight_request)验证server是否允许origin 访问目标资源。

但node-fetch并不遵循这一套规范：

> https://developer.mozilla.org/en-US/docs/Web/HTTP/CORS
>
> Some requests don't trigger a [CORS preflight](https://developer.mozilla.org/en-US/docs/Glossary/Preflight_request). Those are called *simple requests*, though the [Fetch](https://fetch.spec.whatwg.org/) spec (which defines CORS) doesn't use that term. 

> https://fetch.spec.whatwg.org/#cors-request
>
> A CORS request is an HTTP request that includes an `[`Origin`](https://fetch.spec.whatwg.org/#http-origin)` header. It cannot be reliably identified as participating in the [CORS protocol](https://fetch.spec.whatwg.org/#cors-protocol) as the `[`Origin`](https://fetch.spec.whatwg.org/#http-origin)` header is also included for all [requests](https://fetch.spec.whatwg.org/#concept-request) whose [method](https://fetch.spec.whatwg.org/#concept-request-method) is neither ``GET`` nor ``HEAD``.

所以对于fetch来说，只要不是`GET`, `HEAD`和`OPTION(即preflight its self)`, 都在

**same-site**(同站) 只要两个 URL 的 [eTLD](https://en.wikipedia.org/wiki/Public_Suffix_List#:~:text=Entries%20on%20the%20list%20are,Mozilla%20Public%20License%20(MPL).)(effective top-level domains 有效顶级域名 eg. .com、.co、.uk、.github.io)+1 相同即可，不需要考虑协议和端口。

| Url1                   | Url2                     | is same-site? |
| ---------------------- | ------------------------ | ------------- |
| https://www.taobao.com | https://www.bing.cn      | No            |
| https://www.taobao.com | https://world.taobao.com | Yes           |
|                        |                          |               |







> - Cookies from the same domain are no longer considered to be from the same site if sent using a different scheme (`http:` or `https:`).