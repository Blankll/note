# PostgreSQL

<font color="red">PostgreSQL is not similar to MySQL</font>

create database

```sql
CREATE DATABASE test;
-- drop db
drop database test;
DROP DATABASE IF EXISTS test;
```

create a user

```sql
create user username with password 'password';
-- drop user
DROP USER username;
drop user if exists username;
```

grant privileges

```sql
grant all privileges on database dbname to username;
-- revoke privileges
revoke all privileges on database dbname from username;
```

update password

```sql
ALTER USER user_name WITH PASSWORD 'new_password';
```

show table

```sql
select * from information_schema.tables where table_schema='public';
SELECT * FROM pg_catalog.pg_tables where schemaname = 'public';
```

create table

```sql
create table users(
	id serial not null primary key,
	username CHAR(30) not null,
	birthday DATE default NULL
);
```

