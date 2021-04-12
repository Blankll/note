# shell basic

$0 脚本名称

$1 传入的第一个参数

$2 传入的第二个参数，以此类推

$@ 传入的所有参数

$* 传入的所有参数

$? 上一个命令执行返回值



```bash
# 取一个命令执行后的值
datestr=$(date "+%Y-%m-%d %H:%M:%S")
echo $datestr
# -n 取消改行输出的回车
echo -n $datestr
```

列表截取操作

```bash
# 以空格为分界截取列，取每一行的第二列
cut -d' ' -f2 filename
```

重定向

```BASH
grep something file.list 2>/dev/null
```

STDIN 0

STDOUT 1

STDERR 2

`>` create a new file(overwrite old content)

`>>` append the content

`<` provide the input

`&>` both success and error content

`1> success_file.txt  2> error_file.txt` store into different file

`1> filename.txt 2>&1` both store in the single file same with(&>)

`|` send the standard output of one command to another command as standard input

tips

```bash
alias ipi='ipconfig getifaddr en0'
```



## read file content

cat, less, more 

### grep

grep [options] "string/pattern" file/files

`-i` ignore case sensitive

`-w` match complete word

`-v` display the lines which are not having given string or test

`-o` to print/display only the matched parts from matched lines

`-n` to display the matched line numbers

`-c` display the count of matched line

`-A` To display N lines after match(grep -A 3 "string" file)

`-B` To display N lines before match

`-C` to display N lines around match

`-f` takes search string/pattern from a file, one per line

> grep string_file.txt search_file.txt

`-e` search for multi string/parttern

> grep -e string_1 -e string_2 search_file.txt

`-E` extend regrex

> - `xy|pq` matches for xy or pq
> - `^xyz` matches for the lines which are starting with "xyz"
> - `xyz$` matches for the lines which are ending with "xyz"
> - `^$` matches for the lines which are empty
> - `\ `escape special symbole
> - `t..s` matches for start t to s
> - `\b` match the empty string at the edge of word
> - `?` The preceding character is optional and will be matched, at most, once
> - `*` the preceding character will be matched zero or more times
> - `+` the preceding character will be matched one or more times
> - `[xyz]` matches for the lines which are having x or y or z
> - `[a-d]` mathces for the a or b or c or d
> - `[a-dx-z]` matches for a,b,c,d, x,y,z
> - `{n}` the preceding string matched exactly n time
> - `{n,m}` the preceding string matched exactly n or m time
> - `{n,} `the preceding string matched n or more times



### cut

extract parts of each line from a file, it is based on:

- Byte position
- character position
- Fields based on delimiter(by default delimiter is the tab)

`-b` delimiter by bytes

`-c `delimiter by characters

`-d `define the delimiter

`-f` pick fields

`--output-delimiter=''` define out put delimiter

`-s `pick only matched delimiter string line



### awk

```bash
awk [options] '[selection_criteria] {action}' input_file
# selection criteria: pattern/condition
# action: a logic to perform action on each row
```

`-F script_file` specify a field separator(default separator is tab and space)

`-f file` specify a file that contains awk script

`-v var=value` declare a variable



### tr

tr short for translate to translate or delete given set of characters from the input

```bash
tr [options] [SET1] [SET2] <inputFile
```

Sets for translation:

- [:lower:]
- [a-z]
- [:upper:]
- [A-Z]
- [:digit:]
- [0-9]
- [:space:] match for space, tab and new line

options

- `-d` deletes given sets of characters

### tee

used to display the output and also store it into a file

Options 

- `-a` append mode

### comment

```bash
# comment content
<< COMMENT
coment content
COMMENT
: '
comment content
'
```

enhance shell by:

- variables
- Filters like grep, cut, awk and sed
- Conditional statements
- loops
- funtions
- Job scheduling and many more

