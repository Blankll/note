# string

```shell
# define string variable
x=shell
y="shell scripting"
day=$(date)
# displaying thestring variable value
echo $x
echo ${x}
# length of string
xlength=${#x}
# concatenation of string
xyResult=${x}${y}
# convert string into lower case
xL=${x,,}
echo "$x" | tr [A-Z] [a-z]
# convert string into upper case
yU=${y^^}
echo "$y" | tr [a-z] [A-Z]
# replacing the part of string
newY=${y/shell/bash shell}
# slicing the string/sub-string
echo "${y:2:3}"
echo "${y:2}" # all str after index 2 including 2


# append filename after pwd
realpath filename.txt
# get filename in a given string
basename /home/seven/automation/hh.sh
basename /home/seven/automation/hh.sh sh # will move the suffix
# get file path dir
dirname /home/seven/automation/hh.sh # will not incloude the last /
```

