```text
password_hash() – 对密码加密.
password_verify() – 验证已经加密的密码，检验其hash字串是否一致.
password_needs_rehash() – 给密码重新加密.
password_get_info() – 返回加密算法的名称和一些相关信息.
```

Password Hashing API是PHP 5.5之后才有的新特性，它主要是提供下面几个函数供我们使用：

现在PHP的官方都是推荐这种方式来加密用户的密码，很多流行的框架比如Laravel就是用的这种加密方式。

这里使用password_hash()你完全可以不提供盐值(salt)和 消耗值 (cost)，你可以将后者理解为一种性能的消耗值，cost越大，加密算法越复杂，消耗的内存也就越大。当然，如果你需要指定对应的盐值和消耗值，你可以这样写：

```php
options = [
'salt' => custom_function_for_salt(), //write your own code to generate a suitable salt
'cost' => 12 // the default cost is 10 ];
$hash = password_hash($password, PASSWORD_DEFAULT, $options);
```



密码加密过后，我们需要对密码进行验证，以此来判断用户输入的密码是否正确：

```php
if (password_verify(password, hash)) {
// Pass }
else {
// Invalid
}
```

