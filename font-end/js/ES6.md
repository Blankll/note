# ES6

js作用域: 

- 全局作用域

  > 生命周期存在于整个程序之内

- 函数作用域

- 块级作用域

  > ES6才出现的概念，必须用let或const声明{}包裹

- 词法作用域

  > 调用离自己最近的变量，如果自己的作用域内没有，就在全局中找

- 动态作用域

  > 作用域基于调用栈



let 和 const是block scope

var是function scope

var声明的变量可以重复定义

let 和const不能在同一个作用域中重复定义

const声明的变量不能重新赋值

const声明的对象的属性值是可以改变的

局部变量在函数执行完毕后销毁。

全局变量在页面关闭后销毁。



```javascript
const person = {
    name: 'blank',
    age: 18
}
person.age = 20
//强制禁止改变属性值
const blank = Object.freeze{ersion}
```

## arrow function

隐式返回

　

函数单独执行的时候this值指向window

箭头函数的作用域是词法作用域，在定义时就确定了作用域，不会随调用方法的作用域而改变

箭头函数没有自己的this值,this值继承自父作用域

## 模板字符串

使用 ``包裹，参数使用${argument}

模板字符串可以进行嵌套

## 新增的字符串函数

.startsWith()

.endsWith()

.includes()

.repeat()