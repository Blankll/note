# 微信小程序

## wx:for

```xml
<block wx:for="arr">
    <!--
	index是每一项的索引
    item是每一项的成员数据
	-->
	<view>{{index}} => {{item}}</view>
</block>
```

## template

1,创建模板

```xml
<!-- 模板 -->
<!-- 
模板的编写和组件的编写语法没有任何区别
通过<template is="templateName"></template>引入
data 将数据传入模板中
<template is="products" data="{{key:values}}"></template>
-->

<template name="products">
  <view class='products-box'>

    <block wx:for="{{products}}">
    <view class='products-item'>
      <image class='products-image' src='{{item.main_img_url}}'></image>
      <view class='products-item-bottom'>
        <text class='name'>{{item.name}}</text>
        <text class='price'>{{item.price}}</text>
      </view>
    </view>
    </block>
    
  </view>
</template>
```

2. 引入模板

```xml
<!--模板在项目中的相对路径-->
<import src="../tpls/products/products-tpl.wxml" />
```

3. 使用模板

```xml
<!--is 对应模板的 name data 将page下面data中的数据以{{key:value}}的方式传递给模板--> 
<template is="products" data="{{products:productsArr}}"></template>
```

4. 引入模板样式

```css
<!--引入样式的位置是使用该模板对应的page的wxss文件中引入-->
@import "../tpls/products/products-tpl.wxss";
```

## 全局样式

在根目录下新建``app.wxss``文件，在文件中定义的样式可以直接在项目的所有页面中使用，无需再wxss文件中引入他

## 页面跳转

1. 在wxml页面中添加bindtap事件

   ```xml
   <swiper-item class="banner-item" data-id="{{item.key_word}}" bindtap="onProductsItemTap">
   ```

2. 在绑定的方法中使用微信的``navigateTo``方法进行跳转

   ```javascript
     onThemesItemTap: function (event) {
       var id = home.getDataset(event, 'id');
       var name = home.getDataset(event, 'name');
       wx.navigateTo({
           url: '../theme/theme?id=' + id + '&name=' + name
       });
     }
   ```

## 动态设置导航栏标题

在相应wxml对应的js中的``onReady``或时调用系统方法

```javascript
    //根据服务器传来的数据动态设置导航栏标题
    wx.setNavigationBarTitle({
        title: this.data.name,
    });
```

## 路由

小程序有六种路由方式,内部通过栈来实现

- 初始化 新页面入栈
- 打开新页面 现在栈中有两个页面,栈顶为打开的新页面
- 页面重定向 当前页面出栈,新页面入栈
- 页面返回 页面出栈
- tab切换 页面全部出栈,只留下tab页面
- 重加载 全部出栈,只留下重加载的页面

# 微信小程序客户端

1. 在单页目录下编写model文件[类必须有构造方法]

2. 要在其他文件中使用类，必须先将它``export``

3.  要使用一个model的成员变量和成员方法，必须先引入文件，再将其实例化

   ```javascript
   //引入文件
   import{Home} from 'home-model.js';
   //实例化对象
   var home = new Home();
   ```

4. ​

==脚本有错误不一定会影响view显示==

## 客户端数据显示

1. 小程序里没有dom概念，通过数据绑定进行数据渲染
2. 存放到data中的数据都可以在view上访问

## onload和onshow

1. 每个onload在应用生命周期内只执行一次，第一次加载完成之后切换页面，再切回来时不会再执行
2. onshow在每次切换页面时都会执行

# 跳转

1. ``navgateTo``

2. ``switchTab``

   ```javascript
   //跳转到switch栏页面，必须用switchTab
   wx.switchTab({
   	url:'/pages/cart/cart',
   });
   ```