# types
静态类型
```typescript
const count: number = 12;
```
## 基础静态类型
**any**: 允许在编译时移除类型检查。更像是一个过渡时期的妥协或者为了保若类型语言的能力。  
**null**: 默认情况下null和undefined是所有类型的子类型。 可以把 null和undefined赋值给任何其他类型的变量(除了never)。  
**undefined**: 目前只发现null和undifined是可以互换的  
null和undefined既是类型，又是值。任何类型(除了never) 的变量的值都可以为null或undifined。所以null类型的变量可以有null和undifined两种值，undefined类型的变量也是同理。但如果使用了`--strictNullChecks`模式，类型为null和undefined的变量的值就只允许是自身对应的值，即null类型变量的值只能为null而不能为undefined。
**never**: never类型是任何类型的子类型，可以作为一个永远不会有返回值或者永远都是抛出异常函数的返回值类型。  
never变量不可以被任何值赋值，但可以被never类型的值赋值，这就进入了一个奇怪的薛定谔：
```typescript
let neverType: never;
let anotherType: never = neverType;
console.log(anotherType); // undefined
```
最后执行的结果是undefined，所以，有内味了是吧，ts终究都是以编译后的js运行，到了js层面，管你never还是ever，没有赋值就是undefined。  
**boolean**: 布尔类型  
**void**: 表示没有任何类型  
**symbol**: ES6中加入的新类型
> Symbol.for()不会每次调用就返回一个新的 Symbol 类型的值，而是会先检查给定的key是否已经存在，如果不存在才会新建一个值。

**number**: 和JavaScript一样，TypeScript里的所有数字都是浮点数。  
**string**: 字符串类型  
**array**: 有两种方法可以定义数组  
```typescript
let list: number[] = [1, 2, 3];
let list: Array<number> = [1, 2, 3];
```
**Tuple**: 表示一个已知长度和类型的数组  
```typescript
let x: [string, number] = ['zero', 1];
```
**enum**：枚举类型  
默认以0开始，或者手动赋值:
```typescript
enum Color {Red, Green, Blue=5}
let c: Color = Color.Green; // c is 1
let d: Color = Color.Blue; // d is 5
```
## 对象类型
object表示非原始类型, 也就是说除了number，string，boolean，symbol类型的值，都可以赋值给object属性。



## 变量申明

在typescript中，变量的申明同JavaScript一样，可以使用var，let，const，解构等方式。在typescript中，如果使用了var，那么也会一样的存在作用域的问题，所以 **关键不在于语言，而在于写代码的你。**
