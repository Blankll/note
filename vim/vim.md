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



### vim翻页

Ctrl-f    即 PageDown 翻页。
Crtl-b    即 PageUp 翻页。

```
0  是数目字 0 而不是英文字母 o。或是 Hmoe 键，移至行首，
   （含空白字元）。
^  移至第一个非空白字元，注意，要 Shift 键。
$  移至行尾，或 End 键。要 Shift 键。
以上两个按键是源自规则表示式（regular expression），在 regexp 中 ^ 是匹配行首，$ 是匹配行尾。
 G  移至档尾（最后一行的第一个非空白字元处）
gg 移至档首（第一行之第一个非空白字元处）
gg 是 vim 的扩充功能，在 elvis 或原始 vi 中可用 1G 来移至档首（是数字 1 不是英文字 l）。
G 之原意是 goto，指移至指定数目行之行首，如不指定数目，则预设是最后一行。
 w  移至次一个字（word）字首。当然是指英文单字。
W  同上，但会忽略一些标点符号。
e  移至前一个字字尾。
E  同上，但会忽略一些标点符号。
b  移至前一个字字首。
B  同上，但会忽略一些标点符号。
H  移至萤幕顶第一个非空白字元。
M  移至萤幕中间第一个非空白字元。
L  移至萤幕底第一个非空白字元。
这和 PageDown，PageUp 不一样，内文内容并未动，只是游标在动而已。
 n| 移至第 n 个字元(栏)处。注意，要用 Shift 键。n 是从头起
   算的。
:n 移至第 n 行行首。或 nG。
```

### vim查找和替换

vim中使用 :s来进行字符的替换和

:s /seven/blank/ 将当前行的第一个seven字符串替换为blank

:s/seven/blank/g 将当前一整行中所有的seven字符串替换为blank

:m,ns/seven/blank/ 将从第m行开始到第n行中每行的第一个seven替换为blank

:m,ns/seven/blank/g 将从第m行开始到第n行中所有的seven替换为blank

:1,$s/seven/blank/ 将文档中的所有行的第一个seven替换为blank

:1,$s/seven/blank/g 将文档中的所有seven替换为blank

如果查找和替换的内容中有/，我们可以使用#或者+来代替/作为分隔查找内容和替换内容的标识

:1,$s#/seven/seven#/blank/blank# 将文档中所有的/seven/seven字符串替换为/blank/blank



使用/和?进行内容的查找

/super从上往下搜索super？super从下往上搜索super

如果查找特殊字符，如 ^、$、*、/ 和 .，需要在前面加 \ 来转义。