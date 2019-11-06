```python
import re

line = 'bobby123lll'

reg_str = '^b.*?(\d+)'
match_obj = re.match(reg_str, line)
if match_obj:
    print(match_obj.group(1))
else:
    print('match failed')
```