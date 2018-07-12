<?php
try {
  $db_dsn = "mysql:host=localhost;dbname=study";
  $db_name = "root";
  $db_pwd = "0707";
  $db = new PDO($db_dsn,$db_name,$db_pwd);
  $db->setAttribute(PDO::ATTR_ERRMODE,PDO:: ERRMODE_EXCEPTION);

  

} catch (PDOException $e) {
  $e->getMessage();
}

 ?>
