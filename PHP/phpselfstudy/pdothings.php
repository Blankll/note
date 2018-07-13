<?php
try {
  $sdn = "mysql:dbname=test;host=127.0.0.1";
  $name = "root";
  $pwd = "root";
  $db = new PDO($sdn,$name,$pwd);
  $db->setAttribute(PDO::ATTR_ERRMODE,PDO::ERRMODE_EXCEPTION);
} catch (PDOException $e) {
  echo "错误信息：".$e->getMessage()."<br />";
  echo "错误文件：".$e->getFile()."<br />";
  echo "错误行：".$e->getLine()."<br />";
  echo "错误码：".$e->getCode()."<br />";

}
try {
  //第一步：关闭自动提交；
  $db->setAttribute(PDO::ATTR_AUTOCOMMIT,0);
  //第二步：开启事物；
  $db->beginTransaction();
  //第三步：执行子流程；
  //如果子流程有失败的，则整个事务都失败；
  //当所有的子流程都成功时，事务才成功；
  $sql = "UPDATE cash SET c_money = c_money - 50 WHERE c_name = 'zhangshan'";
  $affectedRow = $db->exec($sql);
  if(!$affectedRow)
  {
    throw new PDOException("转出失败");

  }
  $sql = "UPDATE cash SET c_money = c_money + 50 WHERE c_name = 'lisi'";
  $affectedRow = $db->exec($sql);
  if(!$affectedRow)
  {
    throw new PDOException("转入失败");
  }
  //事务成功：提交事务；
  $db->commit();
  echo "汇款成功";

} catch (PDOException $e) {
  $db->rollback();
  echo "错误信息：".$e->getMessage()."<br />";
  echo "错误文件：".$e->getFile()."<br />";
  echo "错误行：".$e->getLine()."<br />";
  echo "错误码：".$e->getCode()."<br />";

}
//第四步：开启自动提交；
//无论成功与否，都要在最后开启自动提交；
$db->setAttribute(PDO::ATTR_AUTOCOMMIT,1);



 ?>
