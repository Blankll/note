# dart基础

## 数据类型

dart内置类型 Number(int, double)、String、Boolean、List、Map、Runes、Symbols

1. 使用var声明变量，申明没有赋值为null

   ```dart
   void main() {
       var a;
       a = 10;
       a = 'hello, world';
   }
   ```

2. 使用const申明常量， const声明的常量必须是编译期常量



?.运算符在左边为null的情况下会阻断右边的调用，??运算符主要的作用是在左侧表达式为null时为其设置默认值

```dart
bool isConnected(a, b) {
    bool outCon = outgoing[a] ?.contains(b) ?? false; //左侧为null，则设置为false
    bool inCon = incomming[a] ?/contains(b) ?? false;
    return outCon || inCon;
}

print(null ?? false); // false
print(false ?? 11); // false
print(true ?? false); // true
```



dart 的future如同js的promise

用then获取结果， catchErr捕获异常

dart的async函数返回一个future

