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
  3,PDO::FETCH_BOTH： 既返回索引数组，又返回关联数组；
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
  // $stmt = $db->prepare($sqladd);
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
