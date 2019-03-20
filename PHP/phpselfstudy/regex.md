# 正则表达式

```php
preg_match("/[0-9]+/","you have 42 magic beans",$captured);
print_r($captured);
echo "<br />";
$ll = preg_match("/[[:<:]]gun[[:>:]]/","gun");
echo $ll;
```



```php
preg_match($pattern, $string, $matches )// 成功返回1,失败返回0
// preg_match_all() 匹配所有函数
//会把匹配成功的字符串存入$matches ，而这里只是echo preg_match的返回值
```

