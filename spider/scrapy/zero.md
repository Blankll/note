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



### 使用scrapy shell模式

```bash
scrapy shell https://www.lagou.com/jobs/6463106.html?show=b1ab3f3570a749449de79ea696b0d414
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

### 配置ip代理



## crwal spider

爬取网站最常用的一个模板,将spider进行了进一步的封装

```python
import scrapy
from scrapy.spiders import CrawlSpider, Rule
from scrapy.linkextractors import LinkExtractor

class MySpider(CrawlSpider):
    name = 'example.com'
    allowed_domains = ['example.com']
    start_urls = ['http://www.example.com']

    rules = (
        # Extract links matching 'category.php' (but not matching 'subsection.php')
        # and follow links from them (since no callback means follow=True by default).
        Rule(LinkExtractor(allow=('category\.php', ), deny=('subsection\.php', ))),

        # Extract links matching 'item.php' and parse them with the spider's method parse_item
        Rule(LinkExtractor(allow=('item\.php', )), callback='parse_item'),
    )

    def parse_item(self, response):
        self.logger.info('Hi, this is an item page! %s', response.url)
        item = scrapy.Item()
        item['id'] = response.xpath('//td[@id="item_id"]/text()').re(r'ID: (\d+)')
        item['name'] = response.xpath('//td[@id="item_name"]/text()').get()
        item['description'] = response.xpath('//td[@id="item_description"]/text()').get()
        item['link_text'] = response.meta['link_text']
        return item
```

