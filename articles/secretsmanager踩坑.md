# secretsmanager 踩坑记

最近项目上在引入secretsmanger作为RDS密码管理以取代直接将密码放在config中的实现，同时要加入secretsmanger的password auto rotation的功能，看似平平无奇的功能，却着实让人踩了很多坑。

首先来看看secretsmanger是什么呢？顾名思义，就是一个密码管理的serverless的服务，将通常保存在config文件中的敏感数据如密码，用户名保存到secretsmanger中，可以是诸如数据库连接凭证，也可以单纯的存储其它的第三方登录凭证。

> AWS Secrets Manager helps you protect secrets needed to access your applications, services, and IT resources. The service enables you to easily rotate, manage, and retrieve database credentials, API keys, and other secrets throughout their lifecycle.

### 为什么要用secretsmanager

我一直信奉大道至简的理念，如果没有迫切的需求或切实的收益而增加一个依赖或服务，就是徒增(脑)烦恼(残)。所以为什么要加入它呢？

1. 增加安全性：显而易见，敏感信息将不再存储在代码中，同时如果项目也是构建在AWS之上的，那么于其它服务的深度集成也是十分便利的
2. 地区法律或规定的要求：可能受制于地方法律或在项目合同必须对密码进行rotaion等要求
3. 便于多服务下的统一密码管理

那么在没有引入诸如secretsmanager服务之前，我们通常如何管理密码的呢？

1. 纯文本存储

一般的项目有可能直接就将密码存到config中，可能并不加密(真实case，并不是编出来的)，出于安全考虑，这个config一般不会被git trace，当然头铁放进去在天朝也不违法。那这样的安全问题就显而易见，无论是否被git trace，source code泄露或者服务器被偷都会将密码。

但是，这就是烂的设计吗？我觉得不一定，至少分情况：如果一个应用的安全要求并没有太高(如这个博客应用)，这样的设计我认为恰好是合适的,我发了篇文章手动备个份，即便整个被黑了还不是重新部署一下的事情。如果引入我下面举例的实现，安全性提升带来的收益并不与付出与复杂性相等。所以我认为这样的方式也是有其应用场景与价值的。

2. 环境变量载入

   将密码作为环境变量进行载人，在container或主机终止时，密码信息便无法获取，非敏感配置便可以放到config中并加入version control中。这样做就需要在服务或容器或主机启动时主动注入环境变量，如果集成了如github action这样可以支持密码存储的CI/CD工具，那么也可以以比较方便且安全的方式将密码信息注入到环境变量中。但如果手动部署(不要奇怪，即便2022，不是所有项目都前后分离，也不是所有项目都有CI/CD), 那么启动参数将会爆炸。

3. 存储加密密码文本

   在这种方式下我们将敏感信息通过密钥进行加密，在容器&服务启动时将

   