# ENGINE

1. MyISAM 不支持外键和事务
2. 表🔒，不适合高并发
3. 性能高， 缓存只缓存索引



Percona xtraDB 在性能和并发性做的更好



# 索引优化

单值索引：只给一张表的某一个字段建一个索引

```sql
--idx_user_name 索引名字 建立索引根据user表的name字段
CREATE INDEX idx_user_name ON user(name);
```

多值索引

```sql
CREATE INDEX idx_user_name_email ON user(name, email);
```

表关联，jion查询太多会严重影响查询性能，要少用

### 7种join

1. 内连接 [两表都要存在的字段]

   ```sql
   SELECT * FROM tablea a INNER JOIN tableb b ON a.key = b.key;
   ```

2. 左连接[左表存在的字段]

   ```sql
   SELECT * FROM tablea a LEFT JOIN tableb b ON a.key = b.key;
   ```

3. 右连接[右表存在的字段]

   ```sql
   SELECT * FROM tablea a RIGHT JOIN tableb b ON a.key = b.key;
   ```

4. 全连接[左表或右表存在的字段]

   ```sql
   SELECT * FROM tablea a FULL OUTER JOIN tableb b ON a.key = b.key;
   ```

5. 左表独自存在的

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

   ​

