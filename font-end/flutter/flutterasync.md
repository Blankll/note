# flutter的线程与异步

dart与一个单线程执行模型，支持Isolate(一种在另一个线程上运行代码的方法),一个事件循环和异步编程，除非自己创建一个Isolate否则所有的dart代码都是运行在ui主线程上，并由event loop驱动，Flutter的event loop和iso中的main loop类似，loop是附加在主线程上的。

dart语言提供异步工具如async/await来实现异步操作

计算密集型的操作最好用Isolate来执行

Isolate时分离的运行线程，且不与主线程共享内存，因此不能访问主线程中的变量，同时也不能使用setState来更新UI，

```dart

import 'dart:convert';
import 'dart:isolate';

loadData() async {
  // 打开ReceivePort以接收传入的消息
  ReceivePort receiveReport = ReceivePort();
  // 创建并生成与当Isolate共享相同代码的Isolate
  await Isolate.spawn(dataLoader, receiveReport.sendPort);
  // 流的第一个元素
  SendPort sendPort =await receiveReport.first;
  // 流的第一个元素被收到后监听会关闭，需要打开一个新的ReceivePort以接受传入的消息
  ReceivePort response =ReceivePort();
  // 统购此发送端口向其对应的ReceivePort发送异步消息
  sendPort.send(
    ['https//jsonplaceholder.typicode.com/posts', response.sendPort]
  );
  // 获取端口发送来的数据
  List message =await response.first;

  setData(() {
    widgets =message;
  });
}
// 这是个独立的线程
// isolate的入口函数，该函数会在新的isolate中调用，isolate.spawn的message参数会作为调用它时的唯一参数
static dataLoader(SendPort sendPort) async {
  // 打开ReceivePort以接收传入的消息
  ReceivePort port =ReceivePort();
  // 通知其他的isolate 本isolate所监听的其他端口
  sendPort.send(port.sendPort);
  // 获取其他端口发送的异步消息，mes => ['https//jsonplaceholder.typicode.com/posts', response.sendPort]
  await for (var msg in port) {
    // 等价于 List msg = await port.first;
    String data =msg[0];
    SendPort replyTo =msg[1];

    String dataURL =data;
    http.Response response =await http.get(dataURL);
    replyTo.send(json.decode(response.body));
  }

}
```



## fluter widget事件监听

1. widget本身支持事件检测
2. 在不支持事件的widget外部包裹一个GestureDetector，这个控件支持多种操作
   - onTapDown 在特定的位置轻触手势接触到了屏幕
   - onTapUp 在特定位置产生了一个轻触手势，并停止接触屏幕
   - onTap 产生了一个轻触手势
   - onTapCancel 触发了onTapDown但没能触发tap
   - onDoubleTap 双机
   - onLongPress常按
   - onVerticalDragStart 接触屏幕垂直移动
   - onVerticalDragUpdate 接触屏幕并继续在垂直方向移动
   - onVerticalDragEnd 之前接触屏幕并水平移动的出点也屏幕分离
3. 