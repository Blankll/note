# PHP的printf

PHP adds its own printf-like functions to replace libc ones and to be used by the internal developer. They will mainly add new formats, play with [*zend_string*](http://www.phpinternalsbook.com/php7/internal_types/strings/zend_strings.html) instead of `char *`

Except the traditional `printf()`, everything else is replaced.

```c
char foo[8]; /* 8-char large buffer */
const char str[] = "Hello world"; /* 12 chars including \0 in count */
int r = snprintf(foo, sizeof(foo), "%s", str);
/* r = 11 here even if only 7 printable chars were written in foo */
/* foo value is now 'H' 'e' 'l' 'l' 'o' ' ' 'w' '\0' */
```

```c
char foo[8]; /* 8-char large buffer */
const char str[] = "Hello world"; /* 12 chars including \0 in count */
int r = slprintf(foo, sizeof(foo), "%s", str);
/* r = 7 here , because 7 printable chars were written in foo */
/* foo value is now 'H' 'e' 'l' 'l' 'o' ' ' 'w' '\0' */
```

```c
char *result;
int r = spprintf(&result, 0, "Here is the date");
/* now use result that contains something like "Here is the date" */
/* spprintf() returns the number of characters that’ve been printed into the result buffer, not counting the final ‘\0’ */
```

**zend_string *strpprintf(size_t max_len, const char *format, ...)**

It means that the `zend_string` is returned to you, and not the number of printed chars as you may expect. You can limit that number though, using the first parameter **(pass 0 to mean infinite)** ; and you must remember that the `zend_string` will be allocated using the Zend Memory Manager, and thus bound to the current request.

```c
zend_string *result;
result = strpprintf(0, "You are using PHP %s", PHP_VERSION);
/* Do something with result */
zend_string_release(result);
```

