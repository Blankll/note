# scrapy

## installation

Ubuntu里默认python为2.7, 利用alternatives机制更改py3为默认

```bash
sudo update-alternatives --install /usr/bin/python python /usr/bin/python2 100 
sudo update-alternatives --install /usr/bin/python python /usr/bin/python3 150
```

### 安装scrapy

```bash
pip3 install -i https://pypi.douban.com/simple/ scrapy
```

创建scrapy项目

```bash
 scrapy startproject ArticleSpider
```

查看scrapy模板

```bash
scrapy genspider --list
```

创建crawl模板项目

```
scrapy genspider -t crawl lagou www.lagou.com
```

errors: 

```bash
pip install --upgrade setuptools

easy_install -U pip

python -m pip install --upgrade pip
```





## scrapy 目录

- scrapy.cfg项目配置
- settings.py 项目的配置，包括中间件的配置等
- middlewares中间件
- items
- spider文件夹：具体存放爬虫文件，继承了scrapy的类都会被执行



运行scrapy项目

命令行启动

·.py中

```python
import sys
import os
sys.path.append(os.path.dirname(os.path.abspath(__file__)))
execute(['scrapy', 'crawl'])
```



### 使用scrapy shell模式

```bash
scrapy shell https://www.lagou.com/jobs/6463106.html?show=b1ab3f3570a749449de79ea696b0d414
```

### scrapy 图片自动下载

在settings的 ITEM_PIPLINES中加入scrapy自带的/scrapy/piplines/images

```python
#settings.py
ITEM_PIPELINES = {
   'scrapy.pipelines.images.ImagesPipeline': 1,
}
```

配置image的字段名称：要下载图片保存的字段名称

```python
#settings.py
IMAGEs_URLS_FIELD = 'image_url'
# 保存路径
project_dir = os.path.abspath(os.path.dirname(__file__))
IMAGES_STORE = os.path.join(project_dir, 'images')
```



### 使用fake useragent代理

- 安装

  ```bash
  sudo pip install -i https://pypi.douban.com/simple/ fake-useragent
  ```

  

- 配置

  在settings中配置useragent的模式以及开启中间件

  ```python
  # 设置代理模式,随机
  RANDOM_UA_TYPE='random'
  
  # 开启中间件
  DOWNLOADER_MIDDLEWARES = {
      #'spider.middlewares.SpiderDownloaderMiddleware': 543,
      'spider.middlewares.RandomUserAgentMiddlware': 543
  }
  ```

  

- middleware

  ```python
  from fake_useragent import UserAgent
  
  class RandomUserAgentMiddlware(object):
      # 随机跟换user-agent
      def __init__(self, crawler):
          super(RandomUserAgentMiddlware, self).__init__()
          self.ua = UserAgent()
          self.ua_type = crawler.settings.get('RANDOM_UA_TYPE', 'random')
  
      @classmethod
      def from_crawler(cls, crawler):
          return cls(crawler)
  
      def process_request(self, request, spider):
          def get_ua():
              # 获取ua类中的方法,反射
              return getattr(self.ua, self.ua_type)
          ua = get_ua()
          request.headers.s
  ```

### item_loader

配置解析项，复用解析方式



### 配置ip代理

- 爬取西刺IP数据,保存到数据库中

- 写一个middleware修改代理 

  ```python
  class RandomProxyMiddleware(object):
      # 动态ip代理设置
      def process_request(self, request, spider):
          request.meta['proxy'] = proxy.get_random_ip()
  ```



## 数据收集

统计status_code数据的次数



scrapy-crawlera 付费的代理插件

tor 洋葱浏览器 经过洋葱浏览器多层代理 比较安全

## 爬虫url去重

1. 将url保存到数据库中
2. 将访问过的url保存到set中，只需要O(1)的代价就可以查询url(缺点是占用内存 - 1亿url可能占用9G)
3. md5加密压缩url保存到set中
4. 用bitmap方法，将访问过的url通过hash函数映射到某一位
5. bloomfilter方法对bitmap进行改进，多重hash函数降低冲突



## 字符串编码

1. 计算机只能处理数字，文本转换为数字才能处理，8bit == 1byte, 一个byte最大可以表示的数字就是255
2. 英文一个字节就可以处理所有的字符，ascii(1byte)美国人的编码标准
3. 汉字太多，255完全不够，就有了GB2312，编码标准越多，乱码就会发生
4. unicode将所有的语言统一到一套编码中(2BYTE) assic前面补零就ok了，但是更占空间
5. utf-8(可变长度编码),把英文存储在一个byte中，汉字存储在3个byte中，特别生僻的变成4-8byte，动态节省存储空间
6. 由于utf8的长度不固定，在内存操作时不方便，所以在utf8内容读入内存时自动转换为Unicode，在保存写入到文件中时以uft-8的格式保存数据

处理流程

- 

- pipeline的值越小，越先进入这个pipline中



## Crawl spider

爬取网站最常用的一个模板,将spider进行了进一步的封装

```bash
# 创建crawl spider模板
scrapy genspider -t crawl lagou www.lagou.com
```

```python
import scrapy
from scrapy.spiders import CrawlSpider, Rule
from scrapy.linkextractors import LinkExtractor

class MySpider(CrawlSpider):
    name = 'example.com'
    allowed_domains = ['example.com']
    start_urls = ['http://www.example.com']
	# 存放多个rule的实例,指向link的分析
    rules = (
        # Extract links matching 'category.php' (but not matching 'subsection.php')
        # and follow links from them (since no callback means follow=True by default).
        Rule(LinkExtractor(allow=('category\.php', ), deny=('subsection\.php', ))),

        # Extract links matching 'item.php' and parse them with the spider's method parse_item
        Rule(LinkExtractor(allow=('item\.php', )), callback='parse_item'),
    )

    def parse_item(self, response):
        # 解析内容
        self.logger.info('Hi, this is an item page! %s', response.url)
        item = scrapy.Item()
        item['id'] = response.xpath('//td[@id="item_id"]/text()').re(r'ID: (\d+)')
        item['name'] = response.xpath('//td[@id="item_name"]/text()').get()
        item['description'] = response.xpath('//td[@id="item_description"]/text()').get()
        item['link_text'] = response.meta['link_text']
        return item
```



## scrapy redis使用

- 下载 https://github.com/rmax/scrapy-redis 源码
- 拷贝src下的源码到项目目录



## 反爬虫策略

- cookie禁用

  配置settings.py文件中的``COOKIES_ENABLED = False``

- 自动限速

  ```python
  AUTOTHROTTLE_ENABLED = True
  # The initial download delay
  AUTOTHROTTLE_START_DELAY = 5
  # The maximum download delay to be set in case of high latencies
  AUTOTHROTTLE_MAX_DELAY = 120
  DOWNLOAD_DELAY = 10
  ```

### 自定义配置

在需要进行自定义配置的spider类中添加:

```python
custom_settings = {
	'COOKIES_ENABLED': Tue # 自定义配置内容
}
```

