#               



useradd与adduser都是创建新的用户

在CentOs下useradd与adduser是没有区别的都是在创建用户，在home下自动创建目录，没有设置密码，需要使用passwd命令修改密码。

而在Ubuntu下useradd与adduser有所不同

1、useradd在使用该命令创建用户是不会在/home下自动创建与用户名同名的用户目录，而且不会自动选择shell版本，也没有设置密码，那么这个用户是不能登录的，需要使用passwd命令修改密码。

2、adduser在使用该命令创建用户是会在/home下自动创建与用户名同名的用户目录，系统shell版本，会在创建时会提示输入密码，更加友好。

 

userdel 删除用户，

userdel只能删除用户，并不会删除相关的目录文件。userdel -r 可以删除用户及相关目录。

