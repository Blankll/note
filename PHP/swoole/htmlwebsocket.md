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

