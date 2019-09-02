# ThinkPHP路由

## 变量的规则

1. 在如下的路由顺序中，第二条路由会发生歧义

```php
Route::get('api/:version/product/:id', 'api/:version.Product/productDetail');
Route::get('api/:version/product/recent', 'api/:version.Product/getRecent');
```

2. 解决办法[通过正则表达式进行参数约束]

```php
Route::get('api/:version/product/:id', 'api/:version.Product/productDetail', [], ['id' => '\d+']);
Route::get('api/:version/product/recent', 'api/:version.Product/getRecent');
```

## 路由分组

分组后的路由性能会比未分组前高一些

```php
//分组前
Route::get('api/:version/product/recent', 'api/:version.Product/getRecent');
Route::get('api/:version/product/by_category', 'api/:version.Product/getAllInCategory');
Route::get('api/:version/product/detail/:id', 'api/:version.Product/productDetail');
//分组后
Route::group('api/:version/product', function(){
    Route::get('/recent', 'api/:version.Product/getRecent');
    Route::get('/by_category', 'api/:version.Product/getAllInCategory');
    Route::get('/detail/:id', 'api/:version.Product/productDetail');
});
```

## 接收客户端提交的post数组（json数组）

```php
$products = input('post.products/a');
```

