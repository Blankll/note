# input

## read from console

```shell
read variable_name
read -p "information" variable_name
```

If not provide any variable for read it will store to the default variable `$REPLY`



## command line argument

`$0`  name of the **shell** or **shell** script.

`$1` first argument

`$2`  second argument

`$#` argument count

`$@` all argument

`$*` all argument

`$?`

notice: if number bigger than 9, need to write: `${10}`

