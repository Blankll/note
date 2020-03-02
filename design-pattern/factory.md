# 工厂模式



## 简单工厂

由一个工厂对象决定创建出哪一种产品的实例

适用于工厂类负责创建的对象比较少的情况下

工厂类的职责相对过种,新增产品时需要修改工厂类的逻辑,违背了开闭原则



1. 创建一个接口或者abstract类, 这个类中有其他子类需要实现的虚拟方法
2. 当需要扩展具体的业务逻辑时,继承abstract类,实现他的方法
3. 创建一个工厂类, 通过工厂类获取实现了接口或者继承了abstract类的类的实例.返回的引用都为被实现的接口或abstract类

example

1. 创建一个abstract类

   ```java
   package com.seven.designpattern.simplefactory;
   
   public abstract class Animal {
       public abstract void eat();
   }
   ```

   

2. 创建具体的业务扩展类, 继承abstract类

   ```java
   package com.seven.designpattern.simplefactory;
   
   public class CatAnimal extends Animal {
       @Override
       public void eat() {
           System.out.println("cat eat");
       }
   }
   ```

   ```java
   package com.seven.designpattern.simplefactory;
   
   public class PigAnimal extends Animal{
       @Override
       public void eat() {
           System.out.println("pig eat");
       }
   }
   ```

   

3. 创建工厂类

   ```java
   package com.seven.designpattern.simplefactory;
   
   import java.lang.reflect.InvocationTargetException;
   
   public class SimpleFactory {
       /**
        * 通过字符串名称获得对象
        * @param name
        * @return
        */
       public Animal getAnimal(String name) {
           if (name.equalsIgnoreCase("pig")) {
               return new PigAnimal();
           } else if (name.equalsIgnoreCase("cat")) {
               return new CatAnimal();
           } else { return null; }
       }
   
       /**
        * 通过反射获得对象
        * @param cls
        * @return
        */
       public Animal getAnimal(Class cls) {
           Animal animal = null;
           try {
               animal = (Animal)cls.getConstructor().newInstance();
           } catch (InstantiationException e) {
               e.printStackTrace();
           } catch (IllegalAccessException e) {
               e.printStackTrace();
           } catch (InvocationTargetException e) {
               e.printStackTrace();
           } catch (NoSuchMethodException e) {
               e.printStackTrace();
           }
           return animal;
       }
   }
   ```

4. 通过工厂类获取需要的对象

   ```java
   package com.seven.designpattern.simplefactory;
   
   public class TestClass {
       public static void main(String[] args) {
           SimpleFactory animalFactory = new SimpleFactory();
           Animal pig = animalFactory.getAnimal("pig");
           Animal cat = animalFactory.getAnimal("cat");
           Animal pigR = animalFactory.getAnimal(PigAnimal.class);
           Animal catR = animalFactory.getAnimal(CatAnimal.class);
           pig.eat();
           cat.eat();
           pigR.eat();
           catR.eat();
       }
   }
   ```

   

## 工厂方法

定义一个创建对象的接口,但让这个实现接口的类来决定实例化哪个类

工厂方法让类的实例化推迟到子类中进行

1. 创建一个接口或者abstract类, 这个类中有其他子类需要实现的虚拟方法
2. 当需要扩展具体的业务逻辑时,继承abstract类,实现他的方法
3. 创建一个接口或虚拟类,规定工厂生成对象的规范
4. 每个具体class对应一个具体的工厂类,由这个工厂类生成对应的类的对象

example

1. 创建一个abstract类

   ```java
   package com.seven.designpattern.methodfactory;
   
   public abstract class Animal {
       public abstract void eat();
   }
   
   ```

2. 创建对应的具体业务类

   ```java
   package com.seven.designpattern.methodfactory;
   
   public class CatAnimal extends Animal {
       @Override
       public void eat() {
           System.out.println("cat eat");
       }
   }
   
   ```

   ```java
   package com.seven.designpattern.methodfactory;
   
   public class PigAnimal extends Animal {
       @Override
       public void eat() {
           System.out.println("pig eat");
       }
   }
   
   ```

3. 创建一个abstract的工厂类

   ```java
   package com.seven.designpattern.methodfactory;
   
   public abstract class MethodFactory {
       public abstract Animal getAnimal();
   }
   
   ```

4. 为每个具体业务类分别创建一个工厂类

   ```java
   package com.seven.designpattern.methodfactory;
   
   public class CatFactory extends MethodFactory {
       @Override
       public Animal getAnimal() {
           return new CatAnimal();
       }
   }
   
   ```

   ```java
   package com.seven.designpattern.methodfactory;
   
   public class PigFactory extends MethodFactory {
       @Override
       public Animal getAnimal() {
           return new PigAnimal();
       }
   }
   
   ```

   5. 通过对应的工厂类获取需要的对象

      ```java
      package com.seven.designpattern.methodfactory;
      
      public class TestClass {
          public static void main(String[] args) {
              MethodFactory pigFactory = new PigFactory();
              MethodFactory catFactory = new CatFactory();
              Animal pig = pigFactory.getAnimal();
              Animal cat = catFactory.getAnimal();
              pig.eat();
              cat.eat();
          }
      }
      ```

      

## 抽象工厂

抽象工厂提供了一系列相关或相互依赖对象的接口

无需指定具体的类

工厂方法解决了同一产品结构对象的创建,抽象工厂解决了同一产品族的对象创建