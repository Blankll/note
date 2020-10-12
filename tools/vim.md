# vim

<shift> + k (K) 跳转到函数的定义

## textObject

commod ``[number]<command>[text object or motion]``

- number 作用在多少个文本对象上
- command 执行的具体命令 如``删除d``, ``修改c``, ``选择v``
- text object or motion 要操作的文本对象范围``i(inner)``, ``a(a word也就是包含前后单词)`` 如``单词w``,``句子s``,``段落p``

## 安装vim plug

- 官方推荐方法

  ```
  $ curl -fLo ~/.vim/autoload/plug.vim --create-dirs https://raw.githubusercontent.com/junegunn/vim-plug/master/plug.vim
  ```

- 直接下载到指定目录即可

  ```
  mkdir ~/.vim/autoload/
  cd ~/.vim/autoload/
  wget https://raw.githubusercontent.com/junegunn/vim-plug/master/plug.vim
  ```


#### 安装插件

要安装插件，先在 Vim 配置文件中声明它们。一般 Vim 的配置文件是 `~/.vimrc`

```
call plug#begin('~/.vim/plugged')
Plug 'itchyny/lightline.vim'
call plug#end()
```

添加后重新加载插件
 `:source ~/.vimrc`
 或者在vim命令中安装：

```
# 检查状态
:PlugStatus
# 安装插件
:PlugInstall
# 更新插件
:PlugUpdate
```

更新插件后，按下 `d` 查看更改。或者， `:PlugDiff`。

#### 审查插件

如果更新的插件无法使用, 可以简单地回滚有问题的插件。输入 `:PlugDiff` 命令，然后按回车键查看上次 `:PlugUpdate`的更改，并在每个段落上按 `X` 将每个插件回滚到更新前的前一个状态。

#### 删除插件

注释掉 vim 配置文件中添加的 `plug` 命令。然后，运行 `:source ~/.vimrc` 或重启 Vim 编辑器。最后，运行以下命令卸载插件：

```
PlugClean #命令将删除 vim 配置文件中所有未声明的插件
```

#### 升级 Vim-plug

要升级vim-plug本身，请输入：
 `:PlugUpgrade`

```
vim ~/.vimrc
```



### vim翻页

Ctrl-f    即 PageDown 翻页。
Crtl-b    即 PageUp 翻页。

```
0  是数目字 0 而不是英文字母 o。或是 Hmoe 键，移至行首，
   （含空白字元）。
^  移至第一个非空白字元
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

/super从上往下搜索super;

?super从下往上搜索super

如果查找特殊字符，如 ^、$、*、/ 和 .，需要在前面加 \ 来转义。

## vim分屏

### 打开文件时分屏

vim -o fileone  filetwo 水平分屏打开两个文件

vim -O fileone  filetwo 垂直分屏打开两个文件

**ctrl + w + j**  切换

**ctrl + w + w** 切换

**ctrl + w + k** 切换

### 在已经打状态添加分屏

- 垂直添加

  :vsplit filename

  :vnew newfilename

- 水平添加

  :split filename

  :new filename

###　切换和尺寸调整

分屏切换
　　ctrl+w 和 w   ``大写时为移动窗口``
　　ctrl+w 和 h(H) 左
　　ctrl+w 和 j(J) 下
　　ctrl+w 和 k(K) 上
　　ctrl+w 和 l(L) 右

改变分屏尺寸
　　ctrl+w 和 < 左
　　ctrl+w 和 > 右
　　ctrl+w 和 + 上
　　ctrl+w 和 - 下
　　ctrl+w 和 = 恢复均等

### 关闭分屏

:only 或者 ctrl+w 和 o取消其它分屏，只保留当前分屏
关闭当前分屏 ctrl+w + c(close) 

只剩最后一个分屏以后推出： ctrl+w 和 q(quit)

## vim插件

- vim-surround

  成对编辑

  - 成双添加 ``<ys textobject text>`` ys 文本编辑对象iw,aw
  - 成双替换 ``<cs oldtext newtext>`` 左括号加内空格,右括号什么都不加
  - 成双删除 ``<ds text>``

- easy-motion

  ``<leader><leader>w` 向后跳转

  ``<leader><leader>b`` 向前跳转

  ``<leader><leader>s word``搜索单词跳转

  ,,个`配置,,

  ```.vimrc
  " 行级跳转
  map <Leader><Leader>j <Plug>(easymotion-j)
  map <Leader><Leader>k <Plug>(easymotion-k)
  " 行内跳转
  map <Leader><leader>h <Plug>(easymotion-linebackward)
  map <Leader><leader>l <Plug>(easymotion-lineforward)
  " 重复上一次动作
  map <Leader><leader>. <Plug>(easymotion-repeat)
  ```

  

- ctrlp

  - 进行文件查找 <c p>
  - ``<ctrl + j/k> `` 进行上下选择
  - ``ctrl + x ``在当前窗口水平分屏打开文件
  - ``ctrl + v`` 同上, 垂直分屏
  - ``ctrl + t`` 在tab中打开

- nerdTree

  - <leader>v 定位当前编辑的文件在文件夹中的位置
  - <leader>g 打开和关闭nerdTree
  
- vim-abolish 装换命名法

  - ``crs ``(coerce snacke_case)转换为下划线
  - ``cru``(UPPER_CASE) 转化为大写
  - ``cr-``(dash-case) 转为-
  - ``cr.`` (dot.case) 转为.
  - ``cr<spance>``转为空格
  - ``crm`` (MixedCase)转换为大骆驼命名
  - ``crc`` (camelCase) 转换为小驼峰命名法

- tagbar代码大纲

  - 安装ctags 

    ```bash
    sudo apt-get install exuberant-ctags
    ```

  - 安装tagbar

    ```
    majutsushi/tagbar.git
    ```

  - ``<leader>t`` togak打开与关闭

- vim-go

- deoplete.nvim 代码补全

## 坑

- airline 显示git branch 必须安装 fugitive这个插件，官方文档里面一个屁都没放，mdzz

- ctrl+s 终止屏幕输出（即停止回显）ctrl+q 恢复屏幕输出，