# class

Typescript 中使用class来标明类类型，与其他语言一样拥有成员属性，成员方法，构造方法，继承，访问控制符等面向对象的特性。

## 访问控制

Typescript拥有三种访问控制符，private，protect和public

|         |                          |
| ------- | ------------------------ |
| public  | 可以自由访问，默认修饰符 |
| protect | 类和派生类可访问         |
| private | 类内可访问               |

class并不是duck type式的类型兼容，private和protect的类型必须是来自同一处声明：

```typescript
class Animal {
    private name: string;
    constructor(theName: string) { this.name = theName; }
}
class Employee {
    private name: string;
    constructor(theName: string) { this.name = theName; }
}
let animal = new Animal("Goat");
let employee = new Employee("Bob");
animal = employee; // error
```

## readonly

可以使用 `readonly`关键字将属性设置为只读但必须在声明时或构造函数里被初始化。                

## 参数属性

在构造函数中同时声明并赋值给一个属性

```typescript
class Octopus {
    readonly numberOfLegs: number = 8;
    constructor(private name: string) {
    }
}
```

## 存取器

```typescript
class Employee {
  private readonly passcode = "secret passcode";
  private _fullName: string;

  get fullName(): string {
      return this._fullName;
  }

  set fullName(newName: string) {
      if (this.passcode && this.passcode == "secret passcode") {
          this._fullName = newName;
      }
      else {
          console.log("Error: Unauthorized update of employee!");
      }
  }
}

let employee = new Employee();
employee.fullName = "Bob Smith";
if (employee.fullName) {
  console.log(employee.fullName);
}
```

## 静态属性

通过`static` 来声明静态属性，然后通过类名来访问



## 抽象类

通过`abstract`修饰，与java类似，抽象类可以包含抽象方法，且不能实例化。 	