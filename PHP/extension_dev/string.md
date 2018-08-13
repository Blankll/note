# String

PHP源码为了实现对字符串的管理，会给字符串分类，利用zend_string结构体中的gc,u,flages字段，分为以下几种：

1. 临时的普通字符串，标记为0；
2. 内部字符串，标记为：IS_STR_PERSISTENT|IS_STR_INTERNED
3. PHP已知字符串，标记为：IS_STR_PERSISTENT|IS_STR_INTERNED|IS_STR_PERMANENT

- IS_STR_PERSISTENT

  PHP已知字符串，PHP代码中的字面量、标识符等字符串。

- IS_STR_INTERNED

  PHP代码中你所写的及所看到的任何字符串在底层存储时都会被打上IS_STR_INTERNED标签