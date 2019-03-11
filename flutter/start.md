# flutter

```dart
import 'package:flutter/material.dart';

void main() => runApp(new MyApp());


class MyApp extends StatelessWidget {
  @override
  Widget build(BuildContext context) {

    return new MaterialApp(
      title: 'SEVEN',
      home: new Scaffold(
        appBar: new AppBar(
          title: new Text('SEVEN'),
        ),
        body: new Center(
          child: new Text("hello, SEVEN"),
        ),
      ),
    );
  }
}
```

- Scaffold 是 Material library 中提供的一个widget, 它提供了默认的导航栏、标题和包含主屏幕widget树的body属性。widget树可以很复杂。
- widget的主要工作是提供一个build()方法来描述如何根据其他较低级别的widget来显示自己。
- 本示例中的body的widget树中包含了一个Center widget, Center widget又包含一个 Text 子widget。
  Center widget可以将其子widget树对其到屏幕中心。



State*ful* widgets 持有的状态可能在widget生命周期中发生变化. 实现一个 stateful widget 至少需要两个类:

1. 一个 StatefulWidget类。
2. 一个 State类。 StatefulWidget类本身是不变的，但是 State类在widget生命周期中始终存在.