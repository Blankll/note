<?php
include('pdo.php');
try {
  $sql = "INSERT INTO sign(s_username,s_password) VALUES(?,?)";
  $stmt = $db->prepare($sql);

  // $stmt->bindParam(1,$add_username);
  // $stmt->bindParam(2,$add_password);
  // $add_username = "wanwu";
  // $add_password = 003;
  // $stmt->execute();

  $stmt->execute(array("maoliu",004));

} catch (PDOException $e) {
  $e->getMessage();
}

 ?>
