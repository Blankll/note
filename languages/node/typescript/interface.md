# interface

TypeScript使用了duck type的模式，interface的作用除了如oop中实现依赖抽象而不是实现之外，还可以用于定义类型契约

```typescript
interface LabelledValue {
  label: string;
}

function printLabel(labelledObj: LabelledValue) {
  console.log(labelledObj.label);
}

let myObj = {size: 10, label: "Size 10 Object"};
printLabel(myObj);
```

编译器只检查interface中必须的类型是否存在且类型是否正确，⚠️这里只能传入实参而不能直接传入对象字面量，否则会触发额外属性检查

## 可选属性

使用`option bags` `?` 可以指定interface的类型为optional

```typescript
interface SquareConfig {
  color?: string;
  width: number;
}
```

## 只读属性

使用readonly修饰的属性只能在对象创建是修改值

```typescript
interface Point {
    readonly x: number;
    readonly y: number;
}
let p1: Point = { x: 10, y: 20 };
p1.x = 5; // error!
```

## 额外属性检查

如果我们在对一个interface或type为参数的方法传入一个**对象字面量(object literal)**参数时，会严格检查传入对象字面量的类型，参数数量，而不再是duck type式的匹配,换句话说**Typescript额外属性检查只会在对象字面量场景下触发**。

- 对于可选参数，如果不传入，不做任何报错
- 对于interface或type中未定义的参数(即多传入了参数) 会抛出错误

```typescript
interface Square {
  color: string
  area: number
}
interface SquareConfig {
  color?:string 
  width: number
}
function createSquare(config:SquareConfig):Square {         
  let newSquare = {color: 'white', area: config.width }
  if (config.color) {
    newSquare.color = config.color
  }
  return newSquare
}

let mySquare = createSquare({col:'black',width:100}) // error
let mySquare = createSquare({color:'black',width:100, age: 12}) // error
let mySquare = createSquare({width:100}) // correct
```

总结，传入参数为对象字面量时，对象中只能包必须属性和可选属性.

在翻了typescript的GitHub之后才发现，官方对object其实有一个`freshness`的概念

> - Every object literal is initially considered "fresh".
> - When a fresh object literal is assigned to a variable or passed for a parameter of a non-empty target type, it is an error for the object  literal to specify properties that don't exist in the target type.
> - Freshness disappears in a type assertion or when the type of an object literal is widened.

所以，在官方的定义中，额外属性检测只发生在fresh的object上

sourcecode 

```typescript
function hasExcessProperties(source: FreshObjectLiteralType, target: Type, reportErrors: boolean): boolean {
    if (maybeTypeOfKind(target, TypeFlags.Object) && !(getObjectFlags(target) & ObjectFlags.ObjectLiteralPatternWithComputedProperties)) {
        const isComparingJsxAttributes = !!(source.flags & TypeFlags.JsxAttributes);
        if ((relation === assignableRelation || relation === comparableRelation) &&
            (isTypeSubsetOf(globalObjectType, target) || (!isComparingJsxAttributes && isEmptyObjectType(target)))) {
            return false;
        }
        for (const prop of getPropertiesOfObjectType(source)) {
            if (!isKnownProperty(target, prop.name, isComparingJsxAttributes)) {
                if (reportErrors) {
                    // We know *exactly* where things went wrong when comparing the types.
                    // Use this property as the error node as this will be more helpful in
                    // reasoning about what went wrong.
                    Debug.assert(!!errorNode);
                    if (isJsxAttributes(errorNode) || isJsxOpeningLikeElement(errorNode)) {
                        // JsxAttributes has an object-literal flag and undergo same type-assignablity check as normal object-literal.
                        // However, using an object-literal error message will be very confusing to the users so we give different a message.
                        reportError(Diagnostics.Property_0_does_not_exist_on_type_1, symbolToString(prop), typeToString(target));
                    }
                    else {
                        errorNode = prop.valueDeclaration;
                        if (prop.valueDeclaration) {
                            errorNode = prop.valueDeclaration;
                        }
                        reportError(Diagnostics.Object_literal_may_only_specify_known_properties_and_0_does_not_exist_in_type_1,
                            symbolToString(prop), typeToString(target));
                    }
                }
                return true;
            }
        }
    }
    return false;
}
```



## 函数类型

ts中的接口可以用来描述方法，通过一个匿名的方法描述(可以类比java中的lambda接口):

```typescript
interface SearchFunc {
  (source: string, subString: string): boolean;
}
```

也可以直接将一个**参数个数，类型顺序相同** 的方法赋值给该接口类型的变量：

```typescript
let mySeach: SearchFunc = function(src:string,sub:string):boolean {
  return true;
}
mySeach('a', 'b');
```

## 可索引的类型

Interface 可以让属性通过索引的方式获取：

```typescript
interface StringArray {
  [index: number]: string;
}
let myArray: StringArray;
myArray = ["Bob", "Fred"];
let myStr: string = myArray[0]; // myStr is 'Bob'
```

typscript支持两种索引签名: 字符串和数字。数字索引和字符串索引同时存在时，数字索引的返回值必须是字符串索引返回值类型的子类型。所以这是为什么呢？

回到最初的最初，什么是数组？一段连续的内存空间。回到JavaScript中，arary是伪数组，object和array在node的实现上都是hashmap。

```javascript
let arr = [
  'one',
  'two'
];
let obj = {
  '0': 'one',
  '1': 'two'
}
```

且当使用 `number`来索引时，JavaScript会将它转换成`string`然后再去索引value，所以索引本质上就只有string索引一种。索引的返回值也只能是有继承关系的一种。

```js
// ts
interface dictionary {
    [y: number]: string;
}

const arr: dictionary = {
    2: '2',
    3: '3',
}
// js
var arr = {
    2: '2',
    3: '3'
};

// ts
interface dictionary {
    [y: string]: string;
}

const arr: dictionary = {
    '2': '2',
    '3': '3',
}
// js
var arr = {
    '2': '2',
    '3': '3'
};

var ok = {
    1: new Dog('anccostor', 'dogg'),
    '1': new Animal('animal')
};
console.log(ok[1]);
```



## 类类型

与java中的普通interface一样由class去实现，一个接口可以继承多个接口，创建出多个接口的合成接口。

```typescript
interface Square extends Shape, PenStroke {...}
```

## 接口继承类

接口可以反过来去继承一个类, 它会继承类的成员包括private&protect但不包括实现，这也意味着继承了类的接口只能被被继承类的子类实现。(套娃?)

```typescript
class Control {
    private state: any;
    public reset(val: number): string { return '123'; }
}
interface SelectableControl extends Control {
    select(): void;
}
class ImageSS extends Control implements SelectableControl {
    select() { }
};
const imgs: ImageSS= new ImageSS();
console.log(imgs.reset(1))
```

