# Arthmetic Operators

Notice: shell script variables are by default treated as strings



Add integer

```shell
a=1
b=2
((sum=a+b))
echo $sum
((a++))
((b--))
```

## bc

```bash
x=1
y=3
bc<<<"$x+$y"
bc<<<"scale=1;$x/$y"
```



## case statement

```shell
case $val in
	opt1)
		statement
		;;
	opt2)
		statement
		;;
	*)
		statement
		;;
esac

```

Example:

```shell
#!/bin/bash
read -p "Enter any character:" character

case $character in
        [0-9])
                echo "you entered single number"
                ;;
        [a-z])
                echo "you entered lower case alph"
                ;;
        [A-Z])
                echo "you entered upper case alph"
                ;;
        *)
                echo "unable to identify your input"
                ;;
esac
```



## test command

a command to judge conditions

### Syntax:

- Test condition
- [ condition ]
- [[ condition ]] (works with bash/ksh/zsh shells)

### Comparison operators

**numbers**

- [[ int1 -eq int2 ]] return true if they are equal else false
- [[ int1 -ne int2 ]] return false if they are equal else true
- [[ int1 -lt int2 ]] return true if int1 is less than  int2 else false
- [[ int1 -le int2 ]] return true if int1 is less than or equal  int2 else false
- [[ int1 -gt int2 ]] return true if int1 is greater than  int2 else false
- [[ int1 -ge int2 ]] return true if int1 is greater than or equal  int2 else false
- [[ ! int1 -le int2 ]] reverse the result

**strings**

- [[ -z str ]] return true if the length of the str is zero else false
- [[ -n str ]] return true if the length of the str is no-zero else false
- [[ str1 == str2 ]] return true if Bothe the strings are equal else false
- [[ str1 != str2 ]] return true if Bothe the strings are not equal else false

**files**

- [[ -d file ]] return true if the file/path is directory else false
- [[ -f file ]] return true if the file/path is a file else false
- [[ -e file ]] return true if the file/path is exists else false
- [[ -r file ]] return true if the file/path is readable else false
- [[ -w file ]] return true if the file/path is writable else false
- [[ -x file ]] return true if the file/path is executable else false





## command chaining operators

semi-colon operator: `cmd1 ; cmd2` run cmd1 and then cmd2, regardless of the success or failure of cmd1

Logical AND operator: `cmd1 && cmd2` run cmd2 only if cmd1 is success

Logical OR operator: `cmd1 || cmd2` run cmd2 only if cmd1 is failed

Logical AND-OR operator: `cmd1 && cmd2 || cmd3` run cmd2 if cmd1 is success else run cmd3



## block code

```shell
# same as ls; pwd; date, it will run independently
{
ls
pwd
date
}
{ ls ; pwd; date; }
```


