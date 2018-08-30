    当转换为 [boolean](http://php.net/manual/zh/language.types.boolean.php) 时，以下值被认为是 **FALSE**：   

-            [布尔](http://php.net/manual/zh/language.types.boolean.php)值 **FALSE** 本身         
-            [整型](http://php.net/manual/zh/language.types.integer.php)值 0（零）         
-            [浮点型](http://php.net/manual/zh/language.types.float.php)值 0.0（零）         
-            空[字符串](http://php.net/manual/zh/language.types.string.php)，以及[字符串](http://php.net/manual/zh/language.types.string.php) "0"         
-            不包括任何元素的[数组](http://php.net/manual/zh/language.types.array.php)         
-            特殊类型 [NULL](http://php.net/manual/zh/language.types.null.php)（包括尚未赋值的变量）         
-            从空标记生成的 [SimpleXML](http://php.net/manual/zh/ref.simplexml.php) 对象         

    所有其它值都被认为是 **TRUE**（包括任何[资源](http://php.net/manual/zh/language.types.resource.php) 和  **NAN**）。   

Warning *-1* 和其它非零值（不论正负）一样，被认为是 **TRUE**！    