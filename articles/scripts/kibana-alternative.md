# Kibana平替 Elasticsearch客户端  DocKit 介绍

大家好，今天给大家介绍up开发的一款elasticsearch桌面客户端，让我们摆脱臃肿沉重的Kibana，小于20MB的体积就可以让你获得开发流程中的必备工具链，

## 安装流程



## 连接Elasticserach数据库



## 查询操作



## 集群管理



## 界面配置



## AI集成



今天给大家介绍一款up 开发的
让大家摆脱臃肿的Kibana
小于20兆的体积就可以
让你获得开发流程中的必备工具链
我们可以来看一下安装流程
这个就是我们都DocKit的网站
我会链接在视频下方
我们可以点击download
我们DocKit提供了Mac
Windows和Linux的版本
大家可以选择
点对应的系统
点击下载
我们允许下载哎
就可以看到这里已经下载成功了
我们双击打开
这里会因为没有经过验证而弹出
但不用担心
这个程序是一个开源免费的应用
所以并不会有任何的病毒
所以我们要打开我们的
如果是Mac的话
我们需要打开我们的config
在
Private & security里面
允许这个应用打开
输入我们的一个密码
允许之后
我们再打开
将这个应用拖到我们的应用程序中
然后我们再点击用程序
这时候就可以看到我们的APP了
我们点击确定
这时可能还会有提示我们在
允许一下就可以了
打开之后就可以看到我们的APP了
打开之后
我们来看一下如何连接
Elasticsearch数据库
那么我们可以直接点击新建连接
这里可以输入我们的连接名称
我们的地址
以及如果有用户名或密码
如果没有设置用户名密码
可以选择为空
我们这里已经连接好了我们的数据库
同时你可以在对已连接
的数据库进行更改或者是直接删除
我们双击之后
就可以连接到对应的数据库
这些是一些案例的请求
我们可以直接在Mac上是Command加enter
直接去查询
或者可以点击左侧的这个绿箭头
点击也是一样的效果
我们可以手动来测试一下
我们可以做一个match_all的请求
这是一个sample的index
我们可以看到请求（补全）也是非常完整的
可以做一个query
直接match_all啊
直接command 加 enter
就可以看到我们的请求结果了
在Kibana中一般是JSON的
但是在这里我们可以看到
这是一个JSON5的object
或者说是一个Javascript的object
那么
我们DocKit是对此进行了专门的优化
那
我们可以直接像在Javascript里面写object
一样
来写我们的query语句
让我们不用再烦人的去补全双引号
但是如果你习惯于双引号的这种写法
也是一样支持的
所以他支持的是标准的JSON5协议
所以他支持JSON
包括Javascript object的这种写法
非常的宽泛
同时你可以用auto indent
这里去对它进行一个格式化
如果我们写的比较杂乱
那么可以用auto indent进行一个格式化
同时呢
我们也支持了
在查询语句内加一些comment之类的
这是一个对用户非常友好的功能
它支持两种不同的comment的模式
相信大家都非常熟悉
这两种comment的模式
在别的语编程语言中都会非常的常见
可以看到这样的请求
也是完全没有问题的
这样可以帮助大家在debug的时候
做一些标注
更容易理解
JSON5和comment是DocKit相对于Kibana的一个优点
我认为是对开发者更加友好的
看完查询功能呢
我们来看一下集群管理
我们点击最上面的这个集群manager
就可以看到我们的集群管理
我们在这里可以选择不同的
你保存的集群
我们可以看到cluster的状态
ID版本以及有多少个node,shard等
index等一些信息
如果我们点到index这里
我们可以看到这里列了所有的NODE
node下面我们可以看到它对应的信息
比如说它的内存占用
词盘空间占用
因为我是在本地起的一个cluster
所以它快把分配它的内存都占完了
然后我们还可以看一下这里的shard
我们可以看到每一个index是被对应的
有多少个下的shard被分配到哪里
我们可以看到这里有3个primary
3个primary shard
三个replica shard
所有的都已经assign到对应的NODE上面了
那么我们可以看到
每一个shard在NODE上面的一信息
比如说它有多少个document dial data
它有merge operation等
不同的做了多少操作
这样可以帮助我们在debug的时候
在集群环境中快速的查看它
不同的shard的一个load
或者是不同的一个instance的健康状况
如果我们切换到index
那么我们这里就可以看到
所有列举到的index
我们可以看到它的状态
ID等
也可以在这里对index attach到的alias
做一些操作
比如说我可以把这个alias给它remove掉
或者是我可以把这个alias给switch
给到个另外一个index
那这样它就不在这
它就被assign到另外一个上面了
对
我们可以看这里的template
那这个就是我们的index template
的一个列表
我们可以看到在这里
它的一个列表的情况
同时我们也可以在右上角的这里
可以选择添加template
或者是添加alias
或者是添加index
这里我就不一一操作了
就是以一个可视化的方式进行
对index
alias这些的一些操作
它同样的
也可以在我们的这个编辑器里面完成
只是你需要去写一些查询语句
所以在manager
在这个集群
管理panel里面就会更加的方便
下面我们来说界面配置
我们点击左下角的config按键
我们可以看到
这里我们可以选择不同的样式
比如说我们可以选择我们的theme
这是dark theme
light theme
也可以follow system
比如说现在是晚上
那我如果切换到light theme
那么它就会变成light theme的状态
我们现在就follow system
系统的配置也支持简体中文和英语
可以根据大家的需求
关于GPT的配置呢
我目前支持的是open AI
你可以配置自己的AI
我们已经给你提供了对应的prompt
你也可以自己优化自己的prompt
下面呢是一个prompt network proxy的config
那我们都知道
open ai在国内访问是会有些问题的
所以你可以对它进行一个相应的配置
好当我们选择save和enable的时候
那我们就可以到这个编辑器上
打开右上角的这个AI assistant
你就可以对它像使用ChatGPT一样
去查询对应的语句
比如说你要让它list all document啊
他就会给你给出你的query的sample出来
由于我这里还没有配置
先不演示
AIAssistant 我们只会给他的信息中发送的
你的index和你index的map信息
DocKit并不会
发送任何你数据库中的实际的数据
只会有index name 和mapping
让它能更好地
对你的search的要求进行一个更好的补全
但是他并不会访问你的任何数据
隐私这个是可以放心的
好那这个就是我们的AI的功能
大家知道Kibana在Elasticsearch/Opensearch中
就如同Navicat在SQL中
内存占用也很夸张
很多时候
开发者只是需要快速的调试语句
并不需要如数据集成
性能监控数据源配置这些
在大型项目中
这些都是需要AS code的
不可能直接在上面手动修改
为了使用开发相关的功能
需要加载包括Devops相关的模块
这也是我开发Dock Kit的主要原因之一
如果大家有什么需求或者反馈
都可以在GitHub上提Issue
或者在视频下方留言
欢迎大家积极反馈
一起改进DocKit
相比于Kibana
我们是支持多个connection的
可以看到这里我已经列了3个connection
那么你可以添加更多的connection
这样我们就不需要像Kibana一样
dev起一个container
你要到线上专门开一台instance
去起一个
test或者是给prod的
container或者EC 2的instance
开发的Elasticsearch桌面客户端
DocKit也提供了非常完善的补全
但它太过臃肿
大家好今天给大家介绍一款up
开发的依赖奢侈桌面客户端
让大家摆脱臃肿的提斑了
让你获得开发流程中的必备工具点
这个就是我们都会get的网站
我们都会get提供了Mac
大家可以选择
点对应的系统
我们允许下载
就可以看到
这里已经下载成功了
我们双击打开
但不用担心
这个程序是一个开源免费的应用
所以并不会有任何的病毒
所以我们要打开我们的
如果是Mac的话
我们需要打开我们的config
我们在
provences的security里面允许这个应用打开
将这个应用拖到我们的应用程序中
然后我们再点击应用程序
允许一下就可以了
打开之后就可以看到我们的APP了
打开之后
来设置数据库
那么我们可以直接点击新建连接
如果没有设置
用户名密码
同时
你可以在对已连接的数据库进行更改
或者是直接删除
我们翻击之
后就可以连接到对应的数据库
相比于keep班
我们是支持多个connection的
可以看到这里我已经列了3个connection
那么你可以添加正读稿的connection
这样我们就不需要像Kibana一样
dam起一个container
你要到线上专门开一台instance
去起一个test
或者是给proud的container或EC two的instance
这些是一些案例的请求
我们可以直接在Mac上是command加enter
直接去查询
或者可以点击左侧的这个绿箭头
点击也是一样的效果
包括Kit也提供了非常完善的股权
我们可以手动来测试一下
我们可以做一个match or的请求
这是一个sample的index
我们可以看到请求也是非常完整的
可以做一个query
直接match off啊
直接砍完到enter
在Tebana中一般是Jason的
但是在这里我们可以看到
这是一个Jason five的object
或者说是一个Javascript的object
那么
我们Dope是对此进行了专门的优化
那
我们可以直接像在Javascript里面写object
一样
来写我们的party语句
让我们不用再烦人的去补全我双引号
但是如果你习惯于双引号的这种写法
也是一样支持的
所以它支持的是标准的Jason 5协议
所以它支持Jason
同时你可以用auto indent这里
去对它进行一个格式化
如果我们写的比较杂乱
那么可以用auto inter进行一个
同时
我们也支持了在查询语句内
加一些comment之类的
这是一个对用户非常友好的功能
支持两种不同的comment的模式
我相信大家都非常熟悉
这两种comment的模式
在编程语言中都会非常的常见
你看到这样的请求
也是完全没有问题的
这样可以帮助大家在debug的时候
做一些标注
更容易理解
杰森five和comment
这是
这是Lockheed相对于Kibana的一个优点
我认为是对开发者更加友好的
看完查询功能呢
我们来看一下集群管理
我们点击最上面的这个集manage
就可以看到我们的集群管理
我们在这里可以选择不同的
你保存的集群
我们可以看到class的状态
ID版本以及有多少个NODE的需要字的
如果我们点到index这里
我们可以看到这里列了所有的note
note下面我们可以看到它对应的信息
比如说它的内存占用
词盘空间畅用
因为我是在本地起的一个class
所以它快把分配它的内存都占满了
我们还可以看一下这里的shard
我们可以看到每一个index是被对应的
有多少个shard
shar被分配到哪里
我们可以看到这里有三个primary
三个primary share
三个replica share
所有的都已经在到doing的note上面啊
那么我们可以看到每一个note
share在note上面的一个信息
比如说它有多
少个document叫data
它有word叫operation等
不同的做了多少操作
这样可以帮助我们在debug的时候
在集群环境中快速的查看它
不同的chat的一个load
或者是不同的一个Instant
是一个健康状况
所有列举到的index
我们可以看到它的状态ID等
也可以在这里对index
attach到的alias做一些操作
比如说我可以把这个alias给它remove掉
或者是我可以把这个alias给switch
给格另外一个index
那这样它就不在这
它就被as到另外一个上面了
那这个就是我们的index
template的一个列表
我们可以看到
在这里它的一个列表的情况
同时我们也可以在右上角的这里
或者是添加alias
或者是添加index
这里我就不一一操作了
就是以一个可视化的方式进行
它同样的
也可以在我们的这个编辑器里面完成
只是你需要去写一些查询语句
在这个集群管理panel里面
就会更加的方便
下面我们来说界面配置
我们点击左下角的config按键
我们可以看到这里
我们可以选择不同的样式
比如说我们可以选择我们的SIM
或者是dark SIM
light SIM
也可以follow system
那我如果切换到light SIM
那么它就会变成light SIM的状态
我们现在就follow Systems系统的配置
也支持简体中文和英语
你可以配置自己的AI
下面呢是一个prompt network proxy的config
open a在国内访问是会有些问题的
好当我们选择save和an apple的时候
打开右上角的这个AI assistant
你就可以对它像使用ChatGPT一样
去查询对应的语句
比如说你要让它立志到ordocument啊
他就会给你给出你的query的apple出来
由于我这里还没有配置全部演示
AI assistant
我们只会给他的信息中
发送的你的index和你index APP的信息
locket并不会发送任何你数据库中的
实际的数据
只会有index name和Mapping
让它能更好的对你的设置要求
进行一个更好的补权
但是它并不会访问你的任何数据
隐私这个是可以翻新的
好那这个就是我们的AI的功能
大家知道Kibana在Eli search open search中
就如同nine cat在地位
但它太过臃肿
内存占用也很夸张
很多时候
开发者只是需要快速的调试语句
并不需要如数据集成
性能监控
数据源配置这些
在大型项目
中这些都是需要s code的
为了使用开发相关的功能
需要加载和Devops相关的模块
都可以在get up上提Echo
或者在视频下方留言
欢迎大家积极反馈
一起改进Dot Kit





## EN

Hello everyone, 

today I will introduce an Elasticsearch desktop client that I recentlly workiing on. This tool helps you get rid of the bulky Kibana.

With a size of less than 20 MB, it provides you with the essential toolchain needed in your development workflow.

Let's take a look at the installation process. 

### installation

This is our DocKit website, you can find the link on video the description bellow, 

DocKit provides versions for Mac, Windows, and Linux, 

so you can select the version corresponding to your system and click to download.

Once the download is allowed, you'll see it has been successfully downloaded. 

Double-click to open it. A prompt might appear because it hasn't been verified,

 but don't worry; this is an open-source and free application, so there are no viruses.

If you're using a Mac, you'll might need to go to "system preference," then "Privacy & Security," and allow this app to open. After entering your password to allow it, open DocKit, drag it to your Applications folder, and then run the program.

At this point, you should see our app. Click "OK"; if you see another prompt

### connect to Elasticsearch

Once opened, let's see how to connect to an Elasticsearch database.

You can directly click "New Connection," enter your connection name, address, and username/password if available.

 If there's no username or password set, you can leave it blank.

We’ve already connected to our database. You can modify or delete the connected database as needed. 

Double-click to connect to the corresponding database.

### Query editor

These are some example requests.

On Mac, you can simply press Command and Enter to execute a search directly.

Or, you can click the green arrow on the left side, which will have the same effect.

Let's manually test it. We can make a `match_all` request.

This is a sample index. As we can see, the request completion is very comprehensive.

We can create a query and directly run `match_all`.

Just press Command + Enter to see our query results.

In Kibana, query was writen as JSON, but here we can see it's a JSON5 object, or you could say it's a JavaScript object. 

since DocKit has enable support for writting the query by standard JSON5

We can write our query statements just like writing objects in JavaScript without having to complete those annoying double quotes, which  makes it very flexible.

You can use auto-indent here to format If the code looks cluttered,

Additionally, DocKit also support adding comments within the query statements, which is a very user-friendly feature.

It supports two different comment modes,  just like in majority of programming languages.

You can see these kinds of requests are completely fine. This helps you make annotations when debugging, making things easier to understand.

JSON5 and comments are advantages of DocKit compared to Kibana, and I believe it's more developer-friendly. 



and there are more funcationalies, like cluster manage with visualized way in manage panel, multi luanguange support, 

And you can also integrate OpenAI to wirte queries for you once you confiugred a api key, 

try it out and we are glad to hear any suggestions, new features   from you

Please give a github like if you interst the project as well!, see you next time
