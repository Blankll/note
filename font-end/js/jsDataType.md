# js Data Type

**值类型(基本类型)**:字符串(string), 数字(Number)，布尔值(Boolean)，对空(Null)，未定义(Undefined)，symbol(ES6)

**引用数据类型**：对象(Object)，数组(Array)，函数(Function)

JavaScript 拥有动态类型。这意味着相同的变量可用作不同的类型：

```javascript
var x;               // x 为 undefined
x = 5;           // 现在 x 为数字
x = "John";      // 现在 x 为字符串
```

不要创建 String 对象。它会拖慢执行速度，并可能产生其他副作用：

```javascript
var x = "John";             
var y = new String("John");
(x === y) // 结果为 false，因为 x 是字符串，y 是对象
```

=== 绝对等于（值和类型均相等）

 在JavaScript中，数组是一种特殊的对象类型。 因此 typeof [1,2,3,4] 
返回 object。  

用 typeof 检测 null 返回是object。



在 JavaScript 中有 5 种不同的数据类型：

- string
- number
- boolean
- object
- function

3 种对象类型：

- Object
- Date
- Array

 2 个不包含任何值的数据类型：

- null
- undefined

JavaScript 中，变量可以在使用后声明，也就是变量可以先使用再声明。

只有声明的变量会提升，初始化的不会。

```javascript
pre = 100;
var pre;
console.log(pre) // now pre eq 100
```

在 JavaScript 中, 函数是对象。JavaScript 函数有它的属性和方法。

构造函数中 **this** 关键字没有任何的值, **this** 的值在函数调用实例化对象(new object)时创建。

经过代码验证, 发现其中的奥妙在于：

```javascript
var add = (function () {
    var counter = 0;
    return function () {return counter += 1;}
})();
```

注意: 为什么上面这段代码没有直接写的 function add (){...} 而是把function赋值给了变量add呢?

我们通常会想当然的认为每次调用 add() 都会重走一遍add()中的代码块, 但其实不然。

注意add方法中的return, 它return的并不是1,2,3这样的数值,而是return了一个方法,并且把这个方法赋值给了add变量。

那么在这个function自运行一遍之后,其实最后赋值给add的是return counter += 1 这段代码。

所以后面每次调用add() 其实都是在调用return counter += 1。

 闭包会持有父方法的局部变量并且不会随父方法销毁而销毁, 所以这个counter其实就是来自于第一次function执行时创建的变量。

## HTMLCollection 与 NodeList 的区别

[HTMLCollection](http://www.runoob.com/js/js-htmldom-collections.html) 是 HTML 元素的集合。

NodeList 是一个文档节点的集合。

NodeList 与 HTMLCollection 有很多类似的地方。 

NodeList 与 HTMLCollection 都与数组对象有点类似，可以使用索引 (0, 1, 2, 3, 4, ...) 来获取元素。

NodeList 与 HTMLCollection 都有 length 属性。

HTMLCollection 元素可以通过 name，id 或索引来获取。

NodeList 只能通过索引来获取。

只有 NodeList 对象有包含属性节点和文本节点。