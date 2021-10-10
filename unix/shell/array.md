http://www.linuxjournal.com/content/bash-arrays

${arr[*]} # All of the items in the array
${!arr[*]} # All of the indexes in the array
${#arr[*]} # Number of items in the array
${#arr[0]} # Length of item zero

for index in ${!array[*]}
do
printf “%4d: %s\n” $index ${array[$index]}
done

