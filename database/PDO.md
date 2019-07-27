#PDO

1. 通过参数形式连接数据库
2. 通过URI的形式连接数据库``在php.ini中配置``
3. 通过配置文件连接数据库

### 1 通过参数连接

```php

try{
  //dsn data soruce name 数据源
  //$dsn 数据库驱动："mysql:dbname=数据库名;host=数据库地址";
  $dsn = 'mysql:dbname=test;host=127.0.0.1';
  //$user 数据库用户名
  $user = 'root';
  //$pwd 数据库密码
  $pwd = 'root';
  //实例化PDO对象
  //第一个参数： 数据库驱动；
  //第二个参数： 数据库用户名；
  //第三个参数： 数据库密码；
  //第四个参数： 模式设置配置数据[可选参数]
  $db = new PDO($dsn,$user,$pwd, [$options]);
  //设置错误处理模式 推荐为抛出异常模式
  $db->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
  //设置是否关闭自动提交功能；
//  $db->setAttribute(PDO::ATTR_AUTOCOMMIT,0);
  //设置结果集返回格式；
//  $db->setAttribute(PDO::ATTR_DEFAULT_FETCH_MODE,PDO::FETCH_ASSOC);
  var_dump($db);
  echo "<hr />";
  $sql = "SELECT *FROM student";
  $stmit = $db->query($sql);
  foreach ($stmit as $k) {
    echo "{$k['s_id']}--{$k['s_name']}--{$k['s_score']}--";
    echo "{$k['s_sex']}--{$k['s_age']}<br />";
  }catch(PDOException $e)
{
  echo "错误信息：".$e->getMessage()."<br />";
  echo "错误文件：".$e->getFile()."<br />";
  echo "错误行：".$e->getLine()."<br />";
  echo "错误码：".$e->getCode()."<br />";
}
```

建立pdo连接时

```php
try{
  $dsn = 'name';
  $user = 'root';
  $pwd = 'root';
  $options = [];
  
  $db = new PDO($dsn,$user,$pwd, [$options]);
  }
```



##2通过URI的形式连接数据库 

在php.ini中配置

```php
pdo.dsn.name="mysql:host=127.0.0.1;dbname=dbname"
```

## PDO对象方法

``exec()`` 执行一条SQL语句， 并返回受影响的行数[create，select时返回0]，

``query()``  执行一条SQL语句， 返回一个PDOStatement对象[query 也可以进行数据插入]

```PHP
try{
  $dsn = 'name';
  $user = 'root';
  $pwd = 'root';
  
  $pdo = new PDO($dsn,$user,$pwd);
  $sql = "SELECT * FROM table*;
  $result = $pdo->query($sql);
  foreach($reult as $item) print_r($item);
 
  }
```



``prepare()``  准备要执行的SQL语句， 返回PDOStatement对象

``execute()``  

```php
 $pdo = new PDO($dsn,$user,$pwd);
 $sql = "SELECT * FROM table";
 $stmt = $pdo->prepare($sql);
 $result = $stmt->execute();
 $row = $stmt->fetc(PDO::FETCH_ASSOC);
```



``quote()``  返回添加引号的字符串，将特殊字符加引号，  用于SQL语句中[可用于过滤数据，防止SQL注入]

```php
$pdo->quote($param);
$sql = "select * from table where something = {$param}";
```



``lastInsertId（）``  返回最后插入行的id  插入操作才能返回，update无效

``setAttribute()``  设置数据库连接属性

``getAttribute()``  得到数据库连接的属性

## PDOStatement对象方法

`errorCode()`    获取跟数据库句柄上一次操作相关的SQLSTATE，语句有错时exec不报PDOEexception，返回false，可以通过pdo->errorCode()和errorInfo()获取出错信息

``errorInfo()``  获取跟数据库句柄上一次操作的错误信息 return   ``array``

arr 0=> SQLSTATE 1 => CODE 2 => INFO

``rowCount()``  返回上一个SQL语句影响的行数

> PDOStatement 对象的方法， 对于select操作返回结果集中记录的条数，
>
> 对于INSERT， UPDATE， DELETE 返回受影响的记录的条数，

``fetch()``  从结果集中获取一行``PDOStatement``对象的方法

``fetchAll()``  返回一个结果集中所有行的数组``PDOStatement``对象的方法

``setFetchMode()``  为语句设置默认的获取模式

``fetchColumn()``  从结果集中的下一行返回单独的一列

``fetchObject()``  获取下一行并作为一个对象返回

``bindParam()``  绑定一个参数到指定的变量名

``bindValue()``  把一个值绑定到一个参数 

``bool PDOStatement::nextRowset( void)`` 返回多个结果集中的下一个结果集 

### PDOStatement

```php
 PDOStatement implements Traversable {
    /* 属性 */
    readonly string $queryString;
    /* 方法 */
    bool bindColumn ( mixed $column , mixed &$param [, int $type [, int $maxlen [, mixed     $driverdata ]]] )
    bool bindParam ( mixed $parameter , mixed &$variable [, int $data_type =                 PDO::PARAM_STR [, int $length [, mixed $driver_options ]]] )
    bool bindValue ( mixed $parameter , mixed $value [, int $data_type = PDO::PARAM_STR     ] )
    bool closeCursor ( void )
    int columnCount ( void )
    bool debugDumpParams ( void )
    string errorCode ( void )
    array errorInfo ( void )
    bool execute ([ array $input_parameters ] )
    mixed fetch ([ int $fetch_style [, int $cursor_orientation = PDO::FETCH_ORI_NEXT [,     int $cursor_offset = 0 ]]] )
    array fetchAll ([ int $fetch_style [, mixed $fetch_argument [, array $ctor_args =       array() ]]] )
    string fetchColumn ([ int $column_number = 0 ] )
    mixed fetchObject ([ string $class_name = "stdClass" [, array $ctor_args ]] )
    mixed getAttribute ( int $attribute )
    array getColumnMeta ( int $column )
    bool nextRowset ( void )
    int rowCount ( void )
    bool setAttribute ( int $attribute , mixed $value )
    bool setFetchMode ( int $mode )
}
```

### PDO

```php
 PDO {
    __construct ( string $dsn [, string $username [, string $password [, array 		         $driver_options ]]] )
    bool beginTransaction ( void )
    bool commit ( void )
    mixed errorCode ( void )
    public array errorInfo ( void )
    int exec ( string $statement )
    mixed getAttribute ( int $attribute )
    static array getAvailableDrivers ( void )
    bool inTransaction ( void )
    string lastInsertId ([ string $name = NULL ] )
    public PDOStatement prepare ( string $statement [, array $driver_options = array() ] 	)
    public PDOStatement query ( string $statement )
    public string quote ( string $string [, int $parameter_type = PDO::PARAM_STR ] )
    bool rollBack ( void )
    bool setAttribute ( int $attribute , mixed $value )
}
```



### php EOF

Heredoc技术。可用来输出大段的html和javascript脚本

1.PHP定界符的作用就是按照原样，包括换行格式什么的，输出在其内部的东西；  
2.在PHP定界符中的任何特殊字符都不需要转义；  
3.PHP定界符中的PHP变量会被正常的用其值来替换。  

```php
    $name = 'BLANK';
    //下面<<<EOT后面不能有空格
    print <<<EOT
            <html>
            <head>
            <meta http-equiv="Content-Type" content="text/html; charset=gb2312" />
            <title>Untitled Document</title>
            </head>
            <body>
            <!--12321-->
            Hello,{$name}!
            Hello,$name!
            </body>
            </html>
EOT; //注意末尾的结束符必须靠边，其前面不能有空格

/*
1.以<<<End开始标记开始，以End结束标记结束，**结束标记必须顶头写**，不能有缩进和空格，且在结束标记末尾要有分号 。

2.开始标记和开始标记相同，比如常用大写的EOT、EOD、EOF来表示，但是不只限于那几个，只要保证开始标记和结束标记不在正文中出现即可。

3.位于开始标记和结束标记之间的变量可以被正常解析，但是函数则不可以。在heredoc中，变量不需要用连接符.或,来拼接
4. heredoc常用在输出包含大量HTML语法d文档的时候
*/
$out = 
<<<EOF
    <a href="javascript:edit('asd', 'aaa')">编辑</a> |

    <font color="#ccc">删除</font>

    <a href="javascript:confirmurl('?m=admin&posid=12')">删除</a> |

    <font color="red">启用</font></a> |  

    <a href="javascript:preview('3','ds')"><font color="green">演示</font></a>
EOF;

echo $out;

//EOF 和EOT没区别
```



PDO错误处理模式

> PDO::ATTR_ERRMODE--异常处理
>   1, PDO::ERRMODE_SILENT： 静默模式，不发出警告，默认模式；
>   2, PDO::ERRMODE_WARNING： 警告模式；
>   3, PDO::ERRMODE_EXCEPTION： 抛出异常；

PDO::ATTR_AUTOCOMMIT 自动提交， 默认开启

>  1,0 --关闭自动提交；
>   2,1 --开启自动提交；

PDO::ATTR_DEFAULT_FETCH_MODE  返回格式

>  1,PDO::FETCH_ASSOC： 返回关联数组；
>  2,PDO::FETCH_NUM： 返回索引数组；
>  3,PDO::FETCH_BOTH： 既返回索引数组，又返回关联数组,默认；
>  4,PDO::FETCH_OBJ： 返回对象； 

PDO::ATTR_PERSISTENT 持久化连接

>true 开启持久化连接
>
>false 关闭持久化连接
>
>如果想使用持久连接，必须在传递给 PDO 构造函数的驱动选项数组中设置 **PDO::ATTR_PERSISTENT** 。如果是在对象初始化之后用 [PDO::setAttribute()](http://php.net/manual/zh/pdo.setattribute.php) 设置此属性，则驱动程序将不会使用持久连接

PDO::ATTR_CASE 自动大小写转化

PDO::ATTR_TIMEOUT 连接超时时间

PDO::ATTR_ORACLE_NULLS 返回空字符串转换为null

```php

<?php

/*
PDO::ATTR_ERRMODE--异常处理
  1, PDO::ERRMODE_SILENT： 沉默的，不发出警告；
  2, PDO::ERRMODE_WARNING： 发出警告；
  3, PDO::ERRMODE_EXCEPTION： 抛出异常；
PDO::ATTR_AUTOCOMMIT--自动提交
  1,0 --关闭自动提交；
  2,1 --开启自动提交；
PDO::ATTR_DEFAULT_FETCH_MODE--返回格式
  1,PDO::FETCH_ASSOC： 返回关联数组；
  2,PDO::FETCH_NUM： 返回索引数组；
  3,PDO::FETCH_BOTH： 既返回索引数组，又返回关联数组,默认；
  4,PDO::FETCH_OBJ： 返回对象；

setAttribute()--设置PDO的行为属性；
getAttribute()--得到PDO的行为属性；

exec()--执行有影响行数的语句
  有影响函数的语句多是增删改，就是对表的结构或内容进行修改的语句；
  返回值：返回影响函数；
query()--执行有结果集的语句
  多用于执行查询；
  返回值：returns a PDOStatement object, or FALSE  on failure
  PDO的预处理对象；

PDO预处理
  prepare()
  bindParam()--绑定参数
    第一个参数：占位符序号（从1开始）；
    第二个参数：绑定的变量；
    第三个参数：变量的类型（一般不用写）；
  execute()--执行预处理语句
  可以直接传参数，
  fetch()--提取一条数据时使用；
  fetchAll()--提取多条数据时；
  bindColumn()--把查询的结果集绑定到一个变量上；
  rowCount()--可以得到查询时结果集的数量或者增删改时影响函数；
*/
//php信息；
//phpinfo();



try{
  //$dsn 数据库驱动："mysql:dbname=数据库名;host=数据库地址";
  $dsn = 'mysql:dbname=test;host=127.0.0.1';
  //$user 数据库用户名
  $user = 'root';
  //$pwd 数据库密码
  $pwd = 'root';
  //实例化PDO对象
  //第一个参数： 数据库驱动；
  //第二个参数： 数据库用户名；
  //第三个参数： 数据库密码；
  $db = new PDO($dsn,$user,$pwd);
  //设置错误处理模式 推荐为抛出异常模式
  $db->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
  //设置是否关闭自动提交功能；
//  $db->setAttribute(PDO::ATTR_AUTOCOMMIT,0);
  //设置结果集返回格式；
//  $db->setAttribute(PDO::ATTR_DEFAULT_FETCH_MODE,PDO::FETCH_ASSOC);
  var_dump($db);
  echo "<hr />";
  $sql = "SELECT *FROM student";
  $stmit = $db->query($sql);
  foreach ($stmit as $k) {
    echo "{$k['s_id']}--{$k['s_name']}--{$k['s_score']}--";
    echo "{$k['s_sex']}--{$k['s_age']}<br />";
  }
//添加
  // $add_name = "llsss";
  // $add_pwd = 123;
  // $add_score = 58;
  // $add_sex = 1;
  // $add_age =21;
  // $sql_add = "INSERT INTO student(s_name,s_password,s_score,s_sex,s_age)
  //           VALUES('{$add_name}','{$add_pwd}','{$add_score}','{$add_sex}','{$add_age}')";
  // $affected = $db->exec($sql_add);
  // var_dump($affected);
  //?是占位符；
  // $sqladd = "INSERT INTO student (s_name,s_password,s_score,s_sex,s_age) VALUES(?,?,?,?,?)";
  //prepare():准备语句；
  // $stmt = $db->prepa,ere($sqladd);
  //绑定参数；
  // $stmt->bindParam(1,$s_name);
  // $stmt->bindParam(2,$s_password);
  // $stmt->bindParam(3,$s_score);
  // $stmt->bindParam(4,$s_sex);
  // $stmt->bindParam(5,$s_age);
  //
  // $s_name = "fanteb";
  // $s_password = "007";
  // $s_score = 75;
  // $s_sex = 1;
  // $s_age = 21;
  //执行预处理语句；
  // $stmt->execute();//返回值为bool
  // $stmt->execute(array("dsss","008",66,2,20));

  $sqls = "SELECT *FROM student";
  $stmt = $db->prepare($sqls);
  $stmt->execute($_GET);
  // $getone = $stmt->fetch(PDO::FETCH_ASSOC);
  // var_dump($getone);
  // $getall = $stmt->fetchAll(PDO::FETCH_ASSOC);
  // var_dump($getall);
  // var_dump($stmt->rowCount());
  $stmt->bindColumn(1,$s_id);
  $stmt->bindColumn(2,$s_name);
  $stmt->bindColumn(3,$s_password);
  $stmt->bindColumn(4,$s_score);
  $stmt->bindColumn(5,$s_sex);
  $stmt->bindColumn(6,$age);
  $getonel = $stmt->fetch(PDO::FETCH_ASSOC);
  echo "<hr />".$s_name;

}catch(PDOException $e)
{
  echo "错误信息：".$e->getMessage()."<br />";
  echo "错误文件：".$e->getFile()."<br />";
  echo "错误行：".$e->getLine()."<br />";
  echo "错误码：".$e->getCode()."<br />";
}


 ?>
```

## PDO预处理

  ``prepare()``
  ``bindParam()``  绑定参数

  第一个参数：占位符序号（从1开始）；
  第二个参数：绑定的变量；
  第三个参数：变量的类型（一般不用写）；

  ``execute()``  执行预处理语句， 可以直接传参数，
  ``fetch() `` 提取一条数据时使用；**执行fetch之前一定要先执行execute(),**
  fetchAll()  提取多条数据时；
  ``bindColumn()``  把查询的结果集绑定到一个变量上；
  ``rowCount()``  可以得到查询时结果集的数量或者增删改时影响函数；

1. :name 的占位符形式

   ```php
   //bool execute ([ array $input_parameters ] )
   try{
       $pdo = new PDO($dsn, $dbname, $password);
       $sql = "sSELECT * FROM user WHERE username=:username AND password=:password";
       $stmt = $pdo->prepare($sql);
       $stmt->execute([':username' => $username, ':password' => $password]);
   }
   ```
   占位符只能用在条件判断上，不能用在表名这些上

   执行fetch要先执行execute()

   ```php
   $sql_find = "SELECT `name`, `flag_url` FROM ".self::$table." WHERE `id` = ?";
   $stm = self::$link->prepare($sql_find);
   // 不能用在表名上
   // $stm->bindParam(1, self::$table);
   $stm->bindParam(1, $id);
   $stm->execute();
   return $stm->fetch();
   ```

2. ？号占位符

   ```php
   //bool execute ([ array $input_parameters ] )
   try{
       $pdo = new PDO($dsn, $dbname, $password);
       $sql = "sSELECT * FROM user WHERE username=? AND password=?";
       $stmt = $pdo->prepare($sql);
       $stmt->execute([$username, $password]);
   }
   
   ```
   
3. 绑定参数类型

   ```php
   $stm->bindParam(2, $pageinfo->size, PDO::PARAM_INT);
   $stm->bindParam(3, $ofset_num, PDO::PARAM_INT);
   $stm->execute();
   ```

   


## SQL注入

> 单引号内部的变量不会执行
>
> 双引号会执行

```php
public function SQL_PREPARE_DATA($Name, $Data, $DataType){
        if(!self::$IsInit){
            return array("Status"=>"STATUS_SQL_NEED_INIT", "Data"=>"");
        }

        //检查名称, 无条件信任 $Name 部分，自己做死谁都拦不住 = =
        if(!is_string($Name)){
            return array("Status"=>"STATUS_SQL_EXCEPTION_INVALID_ARGUMENT", "Data"=>"");
        }

        //如果是数字类型
        if ($DataType === self::DATA_TYPE_INT_VAL || $DataType === self::DATA_TYPE_FLOAT_VAL){
            $TrimedData = trim(trim($Data), " \f\n\r\t\v\0\x0B"); //部分版本默认没有 \f, 造成is_numeric绕过，清除两次确保清除干净
            if(is_numeric($TrimedData)){ //清除完了再判断是不是数字
                if($DataType === self::DATA_TYPE_FLOAT_VAL){ //浮点数，特殊处理
                    $CleanData = floatval($Data);//加上引号，防止奇葩错误
                    return array("Status"=>"STATUS_SUCCESS", "Data"=>(array("K"=>$Name, "V"=>$CleanData)));
                } else { //十六进制，八进制之类的进到这里处理
                    $CleanData = intval($Data);
                    return array("Status"=>"STATUS_SUCCESS", "Data"=>(array("K"=>$Name, "V"=>$CleanData)));
                }
            } else {
                return array("Status"=>"STATUS_SQL_EXCEPTION_INVALID_ARGUMENT", "Data"=>"");
            }
        }

        if ($DataType === self::DATA_TYPE_STRING_VAL) { //字符串类型
            $CleanData = self::$dbh->quote($Data);//用PDO::quote()来加引号
            return array("Status"=>"STATUS_SUCCESS", "Data"=>(array("K"=>$Name, "V"=>$CleanData)));
        }

        if ($DataType === self::DATA_TYPE_BOOL_VAL) { //布尔，直接强制转换
            $CleanData = $Data ? 1 : 0;
            return array("Status"=>"STATUS_SUCCESS", "Data"=>(array("K"=>$Name, "V"=>$CleanData)));
        }
        return array("Status"=>"STATUS_SQL_EXCEPTION_INVALID_ARGUMENT", "Data"=>"");
    }
```



## 常见攻击方式

一般说来，在Web安全领域，常见的攻击方式大概有以下几种：

1. SQL注入攻击
2. 跨站脚本攻击 - XSS
3. 跨站伪造请求攻击 - CSRF
4. 文件上传漏洞攻击
5. 分布式拒绝服务攻击 - DDOS

对于PHP程序+MySQL构架的程序，在动态的SQL语句中，使用单引号把变量包含起来配合addslashes函数是应对SQL注入攻击的有效手段，但这做的还不够，变量类型一定要与字段类型相匹配才可以。

1. 检查变量数据类型和格式

   只要是有固定格式的变量，在SQL语句执行前，应该严格按照固定格式去检查，确保变量是我们预想的格式

2. 过滤特殊符号,特殊字符转义

   对于无法确定固定格式的变量，一定要进行特殊符号过滤或转义处理。以PHP为例，通常是采用addslashes函数，它会在指定的预定义字符前添加反斜杠转义，这些预定义的字符是：单引号 (') 双引号 (") 反斜杠 (\) NULL。

3. 绑定变量，使用预编译语句

   **实际上，绑定变量使用预编译语句是预防SQL注入的最佳方式**，使用预编译的SQL语句语义不会发生改变，在SQL语句中，变量用问号?表示，黑客即使本事再大，也无法改变SQL语句的结构。

   ```sql
   -- user/delete?id=1
   DELETE FROM user WHERE id = 1;
   -- user/delete?id=1 or 1=1
   DELETE FROM user WHERE id = i OR 1 = 1;
   ```

   

###小结

1. 不要随意开启生产环境中Webserver的错误显示。
2. 永远不要信任来自用户端的变量输入，有固定格式的变量一定要严格检查对应的格式，没有固定格式的变量需要对引号等特殊字符进行必要的过滤转义。
3. 使用预编译绑定变量的SQL语句。
4. 做好数据库帐号权限管理。
5. 严格加密处理用户的机密信息。



## PDO事务

### function

``beginTransaction()``  启动一个事务

``commit()``  提交一个事务

``rollBack()``  回滚一个事务

``inTransaction()``  检测是否在一个事务内

**事务支持四大特性（ACID）**：原子性（Atomicity）、一致性（Consistency）、隔离性（Isolation）以及持久性（Durability）

==**innodb支持事务，MyISAM不支持事务**==

```php
try{
    $options = ['PDO::ATTR_ERRMODE' => PDO::ERRMODE_EXCEPTION];
    $pdo = new PDO($dsn, $dbname, $password, $options);
    //开启事务
    $pdo->beginTransaction();
    //数据库操作1
    $sql1 = "UPDATE table SET cloum = new_value WHERE ";
    $pdo->exec($sql1);
    //数据库操作2
    $sql2 = "UPDATE table SET cloum = new_value WHERE ";
    $pdo->exec($sql2);
    //提交事务
    $pdo->commit()
}catch(PDOException $e)
{
    //操作失败，事务回滚
    $pdo->rollBack();
}
```

## PDO效率

连接： 与原生mysql连接相差10倍左右

插入： 与原生插入相差差不多相同