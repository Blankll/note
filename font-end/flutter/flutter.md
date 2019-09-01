flutter中有两个widget用于在页面之间导航

- Route是一个应用程序抽象的屏幕或页面
- Navigator是管理路由的widget

以上两种widget对应flutter中实现页面导航的有两种选择

- 具体指定一个路由名构成的Map（MaterialApp）
- 直接跳转大奥一个路由。（widgetApp）

```dart
// 路由定义
void main() {
    return App(MaterialApp(
    	home: MyHome(),
        routes: <String, WidgetBuilder> {
            '/a': (BuildContext context) => MyPage(title: 'page A'),
            '/b': (BuildContext context) => MyPage(title: 'page B'),
            '/c': (BuildContext context) => MyPage(title: 'page C'),
        }
    ))
}

// 跳转
Navigator.of(context).pushNamed('/b')
```

直接跳转

```dart
Navigator.push(context, MaterialPageRoute(builder:(BuildContext context) => UserScreen()));
```

获取路由返回的结果

在android中有startActivityForResult来获取跳转页面后返回的结果，Flutter中的Navigator类不仅用来处理Flutter中的路由，还可以用来获取push到栈中的路由pop后返回的结果。

```dart
// 跳转路由等待返回结果
Map coordinates = await Navigator.of(context).pushNamed('/location');
// 路由pop时传递结果
Naviagator.of(context).pop({ 'lat': 132424, "name": 223});
```

url_launcher 跳转到其他app



## Flutter图片控件开发

new Image 用于从ImageProvider获取图像

new Image.asset 使用key从AssetBundle获得图像

new Image.network 从网络URL中获取图片

new Image.file从本地文件中获取图片

new Image.memory 用于从Uint8List获取图像

> 在加载项目中的图片资源时，为了让Image能够根据像素密度自动适配不同分辨率的图片，请使用AssetImage指定图像，并确保在widget树中的Image widget上方存在MaterialApp，WidgetsApp或者MediaQuery窗口widget。

### 加载网络图片

```dart
Image.network('http://imageurl');
```

### 加载静态图片

- 在pubspec.yaml文件中声明图片资源的路径

  ```
  assets:
  	- images/my_image.png
  ```

- 使用AssetImage访问图片

  ```dart
  Image(
  	width: 200.0,
  	height: 200.0,
  	image: AssetImage(my_image.png)
  ),
  Image.asset(
  	width: 200.0,
  	height: 200.0,
  	image: AssetImage(my_image.png)
  ),
  ```

### 加载本地图片

- 绝对路径

  ```dart
  import 'dart:io;
  Image.file(File('/fixed_file_path'));
  ```

- 相对路径

  - 在pubspec.yaml中添加path_provider插件

    ```
    dependencies:
      path_provider: ^0.5.0+1
    ```

  - 安装

    ```
    flutter packages get
    ```

  - 加载相对路径的图片

    ```dart
    import 'dart:io';
    import 'package:path_provider/path_provider.dart';
    FutureBuilder(future: __getLocalFile('Download/Stack.png'),
    	return snapshot.data != null ? Image.file(snapshot.data):Container();
    )
    // 读取sdcard的路径
    Future<File> _getLocalFie(String fileName) async {
    	String dir = (await getExternalStorageDirectory()).path;
        File f = new File('$dir/$fileName');
        return f;
    }
    
    ```

设置palceholder

使用transparent_image插件（从内存中加载placeholder）

cached_network_image配置本地缓存图片

### 移除ListView默认padding

为了适配刘海屏等多终端，flutter的组件默认会带有一定的padding我们可以通过如下方法移除

将要移除的widget元素放在如下控件中

```dart
MediaQuery.removePadding(
	removeTop: rue // 移除上方的padding
    context: context,
    child:ListView(
    ...
    )
)

```

### 监听滚动

NotificationListener,滚动时会调用 onNotification

监听第一个时： scorllNotification.depth == 0



### json转换

```dart
class CommonModel {
  final String icon;
  final String title;
  final String url;

  CommonModel({
    this.icon, this.title, this.url
  })

  factory CommonModel.fromJson(Map<String, dynamic> json) {
    return CommonModel(
      icon: json['icon'],
      title: json['title'],
      url: json['url']
    );
  }
}

```



### shared_preferences

本地存储的插件，有点像localstorage



### 下拉刷新与上拉加载更多

RefreshIndicator