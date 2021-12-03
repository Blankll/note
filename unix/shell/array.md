http://www.linuxjournal.com/content/bash-arrays

${arr[*]} # All of the items in the array
${!arr[*]} # All of the indexes in the array
${#arr[*]} # Number of items in the array
${#arr[0]} # Length of item zero

for index in ${!array[*]}
do
printf “%4d: %s\n” $index ${array[$index]}
done





Process text line by line:

```shell
echo 'src/database/entity/Callback.ts
        src/database/entity/Errorcodes.ts
        src/database/entity/Errorlog.ts
        src/database/entity/FlywaySchemaHistory.ts
        src/database/entity/Procexecutiontime.ts' | while read -r a; do echo $a; done
```

