  **open_basedir** **可将用户访问文件的活动范围限制在指定的区域** ，通常是其家目录的路径，也   可用符号 "." 来代表当前目录。注意用open_basedir 指定的限制实际上是前缀 , 而不是目录名。   举例来说 : 若 "open_basedir = /dir/user", 那么目录 "/dir/user" 和 "/dir/user1"都是   可以访问的。所以如果要将访问限制在仅为指定的目录，请用斜线结束路径名。例如设置成 : "open_basedir = /dir/user/"  

​    

  **register_globals** **的意思就是注册为全局变量** ，所以当 On 的时候，传递过来的值会被直接的注册为全局变量直接使用，而 Off 的时候，我们需要到特定的数组里去得到它。 1.PHP  [4.2.0 ](http://www.php.net/releases/4_2_0.php)  版开始配置文件中    **register_globals**  的默认值从  on  改为  off  了，虽然你可以设置它为 On ，但是当你无法控制服务器的时候，你的代码的兼容性就成为一个大问题，所以，你最好从现在就开始用 Off 的风格开始编程。 2. **当** **register_globals** **打开以后，各种变量都被注入代码，例如来自**  **HTML**  **表单的请求变量。再加上**  **PHP**  **在使用变量之前是无需进行初始化的，这就使得更容易写出不安全的代码。** 当打开时，人们使用变量时确实不知道变量是哪里来的，只能想当然。但是 **register_globals**  的关闭改变了这种代码内部变量和客户端发送的变量混杂在一起的糟糕情况。 

​    

  **disable_functions** **限制程序使用一些可以直接执行系统命令的函数** ，如 system ， exec ， passthru ， shell_exec ， proc_open 等等。所以如果想保证服务器的安全，请将这个函数加到 disable_functions 里或者将安全模式打开吧 

​    

  file_uploads ， PHP 文件上传功能记录 file_uploads 指令决定是否启用，默认值： On 。 