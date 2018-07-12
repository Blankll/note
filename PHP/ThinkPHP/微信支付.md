# 微信支付

## 用户权限控制

有一些接口，入删除接口，不能让所有的用户都访问，因此，对用户进行分组，不同的分组由不同的权限，

而分组的依据就是scope，根据scope权限的值对用户进行分组

本例中，

``scope = 16`` 时表示app用户的权限值，或者说是客户端用户的权限值

``scope=32``时表示CMS(管理员)用户的权限值    



1. tp5下的前置方法

   ```php
   //本类中的方法first在second或third方法被调用时，在second或third法执行之前执行
   protected $beforeActionList = [
     'first' => ['only' => 'second,third']
   ];

   ```

   ## 订单

   难点

   1. 库存检测
   2. 订单支付

###     业务流程

1. 用户在选择商品后，向api提交包含它所选择商品的相关信息
2. api接收到Request之后，检查订单相关商品的库存量
3. 有库存时，把订单数据存入数据库中[下单成功]，向客户端返回消息，提示进行支付
4. 调用支付接口进行支付
5. 再次进行库存量检测
6. 服务器端调用微信支付接口进行支付
7. 微信返回支付结果[异步]
8. 成功：检测库存量
9. 成功：进行库存量扣除

##订单快照



==**在进行数据库操作的时候，最好加一层try-catch捕获可能出现的数据库异常**==

## 使用微信提供的api

1.  在[微信支付](https://pay.weixin.qq.com/wiki/doc/api/jsapi.php?chapter=11_1)中下载微信官方的api

2. 在TP5项目根目录下的extend目录下新建目录，并将下载的sdk解压后放入该目录中

3. 在需要使用sdk的文件中引入sdk文件

   ```php
   //引入类
   use think\Loader;
   //第一个参数 所在的目录.文件名
   //第二个参数 文件所在的目录
   //第三个参数 文件后缀
   //extend/WxPay/WxPay.Api.php
   Loader::import('WxPay.WxPay', EXTEND_PATH, '.Api.php');

   //在要使用类的地方new出来[凡是没有命名空间的类在new时都要加\]
   $wx_order_data = new \WxPayUnifiedOrder();
   ```

   ==凡是带有命名空间的类在extend目录下的类都可以自动被加载==

4.  配置``WxPayConfig``

   1. 配置官方sdk配置项

      ```php
      	/**
      	 * TODO: 修改这里配置为您自己申请的商户信息
      	 * 微信公众号信息配置
      	 * 
      	 * APPID：绑定支付的APPID（必须配置，开户邮件中可查看）
      	 * 
      	 * MCHID：商户号（必须配置，开户邮件中可查看）
      	 * 
      	 * KEY：商户支付密钥，参考开户邮件设置（必须配置，登录商户平台自行设置）
      	 * 设置地址：https://pay.weixin.qq.com/index.php/account/api_cert
      	 * 
      	 * APPSECRET：公众帐号secert（仅JSAPI支付的时候需要配置， 登录公众平台，进入开发者中心可设置），
      	 * 获取地址：https://mp.weixin.qq.com/advanced/advanced?action=dev&t=advanced/dev&token=2005451881&lang=zh_CN
      	 * @var string
      	 */
      	const APPID = 'wx426b3015555a46be';
      	const MCHID = '1900009851';
      	const KEY = '8934e7d15453e97507ef794cf7b0519d';
      	const APPSECRET = '7813490da6f1265e4901ffb80afaa36f';
      ```

      ​

   2. 配置发送预支付订单时回调接口地址`` $wx_order_data->SetNotify_url('');``

      ```php
            /**
             * 生成预订单
             *
             * @param string $order_no 订单号
             * @param double $total_price 订单总价
             * @param object $wx_order_data 生成的预订单
             */
            private function makeWXPreOrder($order_no, $total_price)
            {

                //获取当前用户openid
                $openid = BaseToken::getCurrentTokenValue('openid');
                if(!$openid) throw new TokenException();
                //调用微信sdk
                $wx_order_data = new \WxPayUnifiedOrder();
                //订单号
                $wx_order_data->SetOut_trade_no($order_no);
                //交易类型
                $wx_order_data->SetTrade_type('JSAPI');
                //订单总金额[单位为分]
                $wx_order_data->SetTotal_fee($total_price * 100);
                //商品简要描述
                $wx_order_data->SetBody('零食商贩');
                //openid
                $wx_order_data->SetOpenid($openid);
                //设置回调接收接口
                $wx_order_data->SetNotify_url('');

                return $wx_order_data;
            }
      ```

      ​

   ​

   ​

