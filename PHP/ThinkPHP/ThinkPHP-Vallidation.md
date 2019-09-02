# TP5Vallidate

```php
    /**
     * 验证参数是否为正整数
     *
     * @param $value: 传入的参数
     * @param $rule: 传入规则
     * @param $data: 全部数据（开发者文档上的描述）
     * @param $field: 字段描述
     * @is_numeric: 判断变量是否为数字
     * @is_int: 判断变量是否为整数
     *
     */
     protected function isInt($value, $rule = '', $data = '', $field = '')
     {
         if(is_numeric($value) && is_int($value + 0) && ($value + 0) > 0) return true;
         else //return $field.'参数必须是正整数';
                return false;
     }

```

## 独立验证

```php
            data = ['name' => 'seven', 'email' => 'zilisheng@126.com'];
            $validate = new Validate([
                'name' => 'require|max30',
                'email' => 'require|eamil'
            ]);
            //逐个验证，只要有一个不满足便返回false
            $result = $validate->check($data);
            //全部验证，将所有不满足的信息返回
            $result = $validate->batch()->check($data);
```

## 验证器验证

```php
	$data = ['id' => $id];
    $validate = new IDMustBePostiveInt();
    $result = $validate->batch()->check($data);
    var_dump($result);
```

