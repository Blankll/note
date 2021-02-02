# function

函数类型：指定函数参数类型，返回值类型

```typescript
function add(x: number, y: number): number {
    return x + y;
}

let myAdd = function(x: number, y: number): number { return x + y; };
//完整的函数类型
let myAdd: (baseValue: number, increment: number) => number =
    function(x: number, y: number): number { return x + y; };
```

## 可选参数和默认参数

使用?标识别可选参数，可选参数必须跟在必须参数后面。默认参数使用=表识，如果没有传递该参数或传递的参数为undefined，参数便赋值为默认值，默认值的参数可以放在任何参数位置。在所有必须参数后面的默认值参数与可选参数一样，在调用函数的时候可以省略。 

## 剩余参数

