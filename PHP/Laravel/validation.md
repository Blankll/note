# Validation

## Laraavel的编辑时数据验证

在对内容进行编辑时，提交的新数据如电话之类的如果修改之后，不能同数据库中的其他电话号码重复，

就要进行唯一性验证，但是哟啊忽略数据库自身的那一行，因为如果数据没有修改，传递的就是原来的电话号码，所以修改在数据库字段中为唯一性的记录时，只需要验证``除自身记录之外``没有重复的数据就可以。

Laravel下的验证方式有多种，这里需要使用Validator进行验证，这样就可以使用Validator自带的ignore方法忽略掉自身记录

```php
use Validator;
use Illuminate\Foundation\Http\FormRequest;
use Illuminate\Validation\Rule;

class ExampleRequest extends FormRequest{
    // 定义规则 数组的形式
    public function rules()
    {
        return [
            'name' => [
                'required',
                'max:30',
                //Rule::unique('admins')->ignore(intval($this->input('id')))
                $this->makeUnique()
            ]
        ]
    }
    /**
     * 使用Validator进行验证，使编辑时验证数据除了自己之外不重复成为可能
     */
    public function notEditValidate()
    {
        $validator = Validator::make($this->all(), $this->rules(), 
                                     $this->messages())->validate();
    }
    /**
     * 编辑时验证唯一性的时候忽略自己的那一行
     */
    private function makeUnique()
    {
        return Rule::unique('admins')->ignore(intval($this->input('id')));
    }
}

```

``Validator::make($data, \$rules, \$messages)->validate()``

- $data冲request中获得的待验证请求数据
- $rules 验证规则
- $messages　自定义错误消息
- validate() 进行验证，如果发生错误，会带着Laravel标准格式的错误消息返回到前一页

``Rule::unique('admins')->ignore(intval($this->input('id')))``

- admins　指定数据所在的数据表

- 所在行的primary key

  > 指定了表和记录之后，验证唯一性时变会验证除了这一行记录之外的表中的所有数据

目前就发现这样的处理逻辑，防止在修改数据时有唯一性约束的字段修改后的内容和其他记录中的内容相同，从而发生冲突。