



```bash
my.cnf一般在etc/mysql/my.cnf位置。找到后请在以下三部分里添加如下内容： 
[client] 
default-character-set = utf8mb4 
[mysql] 
default-character-set = utf8mb4 
[mysqld] 
character-set-client-handshake = FALSE 
character-set-server = utf8mb4 
collation-server = utf8mb4_unicode_ci 
init_connect='SET NAMES utf8mb4'

SHOW VARIABLES WHERE Variable_name LIKE 'character_set_%' OR Variable_name LIKE 'collation%';
```



```bash
collation_connection 、collation_database 、collation_server是什么没关系，但必须保证：
系统变量 	描述
character_set_client 	(客户端来源数据使用的字符集)
character_set_connection 	(连接层字符集)
character_set_database 	(当前选中数据库的默认字符集)
character_set_results 	(查询结果字符集)
character_set_server 	(默认的内部操作字符集)

这几个变量必须是utf8mb4。
```

