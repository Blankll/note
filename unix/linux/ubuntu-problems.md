ubuntu无法更新

>  Could not get lock /var/lib/apt/lists/lock - open (11: Resource temporarily unavailable)

```bash
ps aux | grep -i apt
```

找到进程id

```bash
kill process_id
```

