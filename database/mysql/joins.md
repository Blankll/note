### 7种join

1. 内连接 [两表都要存在的记录]

   ```sql
   SELECT * FROM tablea a INNER JOIN tableb b ON a.key = b.key;
   ```

2. 左连接[左表存在的记录]

   ```sql
   SELECT * FROM tablea a LEFT JOIN tableb b ON a.key = b.key;
   ```

3. 右连接[右表存在的记录]

   ```sql
   SELECT * FROM tablea a RIGHT JOIN tableb b ON a.key = b.key;
   ```

4. 全连接[左表或右表存在的记录]

   ```sql
   SELECT * FROM tablea a FULL OUTER JOIN tableb b ON a.key = b.key;
   ```

5. 左表独自存在的[右表不存在该记录时对应的右表的字段为NULL]

   ```sql
   SELECT * FROM tablea LEFT JOIN tableb ON a.key = b.key WHERE b.key IS NULL
   ```

6. 右表独自存在的

   ```sql
   SELECT * FROM tablea a RIGHT JOIN tableb b ON a.key = b.key WHERE a.key IS NULL
   ```

7. 左表和右表各自存在的

   ```sql
   SELECT * FROM tablea a LEFT JOIN tableb b ON a.key = b.key WHERE b.key IS NULL
   UNION 
   SELECT * FROM tablea a RIGHT JOIN tableb b ON a.key = b.key WHERE a.key IS NULL
   ```



默认的join操作和inner join操作结构一致



  WHERE语句在GROUP BY语句之前；SQL会在分组之前计算WHERE语句。   

  HAVING语句在GROUP BY语句之后；SQL会在分组之后计算HAVING语句。 