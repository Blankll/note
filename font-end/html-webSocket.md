# javascript webSocket

开启一个javascript websocket

```javascript
let url = 'http://127.0.0.1/swoolewebsockettest.php';
        let ws = new WebSocket(url);
        ws.onopen = (event) => {
            console.log('connection build');
        };
        ws.onmessage = (event) => {
            console.log('get message from server');
        };
        ws.onclose = (event) => {
            console.log('connection closed');
        };
        ws.onerror = (event) => {
            console.log('get error on websocket processing');
        };
```

websocket一共支持四个消息，onopen, onmessage, onclose和onerror,所有的操作都是采用消息的方式触发，

``onopen``  当js客户端成功连接服务端后触发onopen事件

``onmessage`` 当客户端接收到来自服务器端的消息时触发``event.data``中包含了服务器端发送的数据

``onclose`` 客户端接收到服务器端发送的关闭连接请求时触发

``onerror`` 在连接失败，发送或接收数据失败，以及处理数据失败，都会触发

websocket与http协议一样都是基于TCP的可靠协议，websocket与http都属于应用层协议，websocket在建立握手连接时，数据是通过http协议传输的，连接建立完成后便不再需http参与真正的数据传输。
```javascript
// 这里不用ws会报错
let url = "ws://127.0.0.1:8811";
// 实例化一个websocket对象
let ws = new WebSocket(url);
/**
 * 连接打开触发事件
 */
ws.onopen = (event)=> {
    console.log('connect open');
    //　发送数据个服务器
    ws.send('hello,server, i\'m websocket');
};
/**
 * 接收到服务器端传来数据时触发的事件，
 * 服务器发送的消息在event.data中
 */
ws.onmessage = (event)=> {
    console.log('get message:');
    console.log(event);
};
/**
 * 连接关闭时事件，可以将该事件添加到onmessage事件中，
 * 接收到服务器发送的消息之后便自动关闭连接
 */
ws.onclose = (event)=> {
    console.log('connection closed');
};
/**
 * 当连接过程中发生错误时会触发该事件
 */
ws.onerror = (event)=> {
    console.log('error happend');
    console.log(event);
};
```