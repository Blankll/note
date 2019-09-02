# js study content

``onkeydown`` 事件会在用户按下一个键盘按键时发生。

``toLocaleString`` 对内容根据国家地区做不同的改变，具体去看文档

``location.host`` 可读取或设置当前 URL 的主机名称和端口号。

```javascript
document.write(location.host);
www.runoob.com
```

## js 的 this

### 理解函数执行过程

函数的执行过程分成两部分:

- 一部分用来生成执行上下文环境，确定this的指向、声明变量以及生成作用域链；
- 另一部分则是按顺序逐行执行代码。

> 建立执行上下文阶段(发生在：函数被调用时 && 函数体内的代码执行前 )

#### 详细流程

- 生成变量对象，顺序：创建 arguments 对象 --> 创建function函数声明 --> 创建var变量声明
- 生成作用域链
- 确定this的指向
- 函数执行阶段
- 逐行执行代码，这个阶段会完成变量赋值，函数引用，以及执行其他代码。



直接在<script>中定义的 var变量可以用window对象访问到而let不可以，两个都是在窗口关闭的时候才会被销毁

"闭包"(closure):

- 能够读取其他函数内部变量的函数。
- 函数内的变量的值始终保持在内存中。

JavaScript 中万物皆对象，对象又分为普通对象和函数对象，Object 、Function 是 JS 自带的函数对象

```javascript
// Object 、Function  的typeof都是function
console.log(typeof Object); //function 
console.log(typeof Function); //function  
```

js中实例都有一个constructor(构造函数)属性指向构造它的a函数

```javascript
var o1 = {}; 
var o2 =new Object();
var o3 = new f1();

function f1(){}; 
var f2 = function(){};
var f3 = new Function('str','console.log(str)');

console.log(typeof Object); //function 
console.log(typeof Function); //function  

console.log(typeof f1); //function 
console.log(typeof f2); //function 
console.log(typeof f3); //function   

console.log(typeof o1); //object 
console.log(typeof o2); //object 
console.log(typeof o3); //object
```

原型对象

- js中每定义一个对象都会自动包含一些预定义的属性
- 每个``函数对象``都有一个``prototype``属性指向函数的原型对象
- 每个对象都有``__proto__``属性，但只有函数对象才有 ``prototype``属性
- 默认情况下，所有的原型对象都会自动获得一个constructor(构造函数)属性,这个属性指向prototype属性所在的函数
- ``typeof null == object``是个历史遗留bug

**原型对象主要是用于继承**

```javascript
/**
 * 除Function.prototype是函数对象外,原型对象都是一个普通对象
 */
function Person(){};
console.log(Person.prototype)                     //Person{}
console.log(typeof Person.prototype)              //Object
console.log(typeof Function.prototype)            // Function，这个特殊
console.log(typeof Object.prototype)              // Object
console.log(typeof Function.prototype.prototype)  //undefined
```

## 原型链

```javascript
Person.prototype.constructor == Person;
instance.__proto__ == Person.prototype;
instance.constructor == Person;

Function.prototype.__proto__ === Object.prototype
Object.prototype.__proto__ = null
```

> prototype 是保存着它们所有实例方法的真正所在。换句话所说，诸如 toString()和valuseOf() 等方法实际上都保存在  prototype 名下，只不过是通过各自对象的实例访问罢了。

#### conclusion

- 所有函数对象的``__proto__``都指向``Function.prototype``，它是一个空函数(Empty function)
- 所有对象的``__proto__``都指向其构造器的``prototype``

