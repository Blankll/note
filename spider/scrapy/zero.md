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

