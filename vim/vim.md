# vim

## 安装vim plug

直接下载到指定目录即可

```
mkdir ~/.vim/autoload/
cd ~/.vim/autoload/
wget https://raw.githubusercontent.com/junegunn/vim-plug/master/plug.vim
```

配置

```
vim ~/.vimrc
```

将要安装的插件写入~/.vimrc，这里以ycm插件为例：

```
" Specify a directory for plugins 
call plug#begin('~/.vim/plugged')
 "以安装ycm插件为例
Plug 'Valloric/YouCompleteMe'
" Initialize plugin system
call plug#end()
```

```
vim ~/.vimrc
```

PlugStatus
PlugInstall

使用vim plug可以方便的管理插件

查看插件类型：
 ：PlugStatus
 安装插件：
 ：PlugInstall
 更新插件：:PlugUpdate
 vim-plug本身更新：:PlugUpgrade