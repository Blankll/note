# netty

- 构建一对主从线程
- 构建服务器启动类
- 为服务器设置channel
- 设置处理从线程池的助手类初始化器
- 监听启动和关闭服务器

1. 每一个channel由多个handler共同组成pipeline



## netty channel的生命周期

```java
	@Override
	public void channelRegistered(ChannelHandlerContext ctx) throws Exception {
		// TODO Auto-generated method stub
		System.out.println("channel注册");
		super.channelRegistered(ctx);
	}

	@Override
	public void channelUnregistered(ChannelHandlerContext ctx) throws Exception {
		// TODO Auto-generated method stub
		System.out.println("channel移除");
		super.channelUnregistered(ctx);
	}

	@Override
	public void channelActive(ChannelHandlerContext ctx) throws Exception {
		// TODO Auto-generated method stub
		System.out.println("channel活跃状态");
		super.channelActive(ctx);
	}

	@Override
	public void channelInactive(ChannelHandlerContext ctx) throws Exception {
		// TODO Auto-generated method stub
		System.out.println("channel客户端与服务器端断开");
		super.channelInactive(ctx);
	}

	@Override
	public void channelReadComplete(ChannelHandlerContext ctx) throws Exception {
		// TODO Auto-generated method stub
		System.out.println("channel读取完毕");
		super.channelReadComplete(ctx);
	}

	@Override
	public void userEventTriggered(ChannelHandlerContext ctx, Object evt) throws Exception {
		// TODO Auto-generated method stub
		System.out.println("用户事件触发");
		super.userEventTriggered(ctx, evt);
	}

	@Override
	public void channelWritabilityChanged(ChannelHandlerContext ctx) throws Exception {
		// TODO Auto-generated method stub
		System.out.println("channel可写事件被更改");
		super.channelWritabilityChanged(ctx);
	}

	@Override
	public void exceptionCaught(ChannelHandlerContext ctx, Throwable cause) throws Exception {
		// TODO Auto-generated method stub
		System.out.println("channel发生异常时执行，捕获到异常");
		super.exceptionCaught(ctx, cause);
	}

	@Override
	public void handlerAdded(ChannelHandlerContext ctx) throws Exception {
		// TODO Auto-generated method stub
		System.out.println("channel助手类添加");
		super.handlerAdded(ctx);
	}

	@Override
	public void handlerRemoved(ChannelHandlerContext ctx) throws Exception {
		// TODO Auto-generated method stub
		System.out.println("channel助手类移除");
		super.handlerRemoved(ctx);
	}
```

