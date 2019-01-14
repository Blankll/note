# concurrency design partten

## singleton

1. hungry man mode

   ```java
   package study.seven.concurrency.desginpartten;
   
   /**
    * desc singleton hungry man style(this patten is no problem with thread safety)
    * @Auther: Blank
    * @Description: study.seven.concurrency.desginpatten
    * @Date: 1/13/19
    * @Version: 1.0
    */
   public class SingletonObjectOne {
       private final static SingletonObjectOne instance = new SingletonObjectOne();
   
       private SingletonObjectOne() {}
   
       public static SingletonObjectOne getInstance() {
           return instance;
       }
   }
   ```

2. lazy man mode

   >  lazy mode in multithread enveriment may due to null point exception, because of when a thread create instance at first time but before this thread initlaize all of properties which construct defined, it's time slice is out, and next thread use check find that instance had created and simply return it, when tuse the uninitliazed property, that's gana be throw null point exception.
   >
   > soltion add volatile with instance property
   >
   >

   ```java
   package study.seven.concurrency.desginpartten;
   
   /**
    * desc singleton with lazy man style(double check for thread safety)
    * @Auther: Blank
    * @Description: study.seven.concurrency.desginpartten
    * @Date: 1/13/19
    * @Version: 1.0
    */
   public class SingletonObjectTwo {
       private static SingletonObjectTwo instance;
   
       private SingletonObjectTwo() {};
   
       public static SingletonObjectTwo getInstance() {
           // if no instance locked to create instance at first invoke
           if(null == instance) {
               synchronized(SingletonObjectTwo.class) {
                   // for thread safety
                   if(null == instance) {
                       instance = new SingletonObjectTwo();
                   }
               }
           }
   
           return instance;
       }
   }
   ```

3. singleton with a efficiency, elegant and thread safety solution

   ```java
   package study.seven.concurrency.desginpartten;
   
   /**
    * singleton with a efficiency elegant and thread safety solution
    * @Auther: Blank
    * @Description: study.seven.concurrency.desginpartten
    * @Date: 1/13/19
    * @Version: 1.0
    */
   public class SingletonObjectFour {
       private SingletonObjectFour() {}
   
       private static class instanceHolder {
           // jvm run static only one time
           private final static SingletonObjectFour instance = new SingletonObjectFour();
       }
   
       public static SingletonObjectFour getInstance() {
           return instanceHolder.instance;
       }
   }
   ```

4. use enum property

   ```java
   package study.seven.concurrency.desginpartten.singleton;
   
   /**
    * desc enum is thread safety and it's construct will only invoke one time
    * @Auther: Blank
    * @Description: study.seven.concurrency.desginpartten.singleton
    * @Date: 1/13/19
    * @Version: 1.0
    */
   public class SingletonObjectFive {
       private SingletonObjectFive() {}
   
       private enum Singleton {
           INSTANCE;
           private final SingletonObjectFive instance;
   
           Singleton() {
               instance = new SingletonObjectFive();
           }
           public SingletonObjectFive getInstance() {
               return instance;
           }
       }
   
       public SingletonObjectFive getInstance() {
           return Singleton.INSTANCE.getInstance();
       }
   }
   ```

