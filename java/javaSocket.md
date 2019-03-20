# javaSocket

标签（空格分隔）： 未分类

---
##网络模型
- OSI(Open System Interconnection)：(开放系统互联)参考模型
- TCP/IP参考模型
##网络通讯要素
- IP地址
- 端口号
- 传输协议
       
| OSI参考模型   |     TCP/IP参考模型 |
|---------------|--------------------|
|  应用层       |    应用层
|  表示层       |
|  会话层       |                     |
|  传输层       |    传输层           |
|  网络层       |    网际层           |
|  数据链路层   |  主机至网络层         
|  物理层       |                     |

##TCP和UDP
- UDP
 - 将数据及源和目的封装到数据包中，不需要建立连接；
 - 每个数据包的大小限制在64kb内；
 - 因无需连接，是不可靠协议；
 - 不需要建立连接，速度快；
- TCP
 - 建立连接，形成传输数据的通道；
 - 在连接中进行大量的数据传输；
 - 通过三次握手完成连接，是可靠协议；
 - 必须建立连接，效率较低
##Socket
 Socket: 应用程序中通常通过“套接字”向网络发出请求或者应答网络请求。
###特点
- 通信的两端都有Socket；
- 网络通讯其实就是Socket之间的通讯；
- 数据在两个Socket之间通过IO传输；
  
在java中，Socket和ServerSocket类库位于java.net包中；
ServerSocket用于服务器端；
##建立Socket链接
1，服务器监听
2，客户端发出请求
3，建立链接
4，通信
###Socket的特点
1，Socket基于TCP链接，数据传输有保障；
2，Socket适用于建立长时间的链接；
3，Socket编程通常用于即时通讯；
```java
package com.jkxu.net;

import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;

public class ServerSocketTest {
	public static void main(String[] args){
		//port 1-65535
		try {
			ServerSocket serverSocket = new ServerSocket(888);
			//block
			Socket socket = serverSocket.accept();
			//create connection
			System.out.println("have client conncetion to the 888host");
		} catch (IOException e) {
			
			e.printStackTrace();
		}
	}
}
```





