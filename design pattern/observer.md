# observer



```java
package study.seven.concurrency.desginpartten.observer;

/**
 * @Auther: Blank
 * @Description: study.seven.concurrency.desginpartten.observer
 * @Date: 1/14/19
 * @Version: 1.0
 */
public abstract class ObserverOne {
    protected SubjectOne subject;
    protected String name;

    public ObserverOne(SubjectOne subject, String name) {
        this.subject = subject;
        this.name = name;
    }
    public abstract void update();
}
```

```java
package study.seven.concurrency.desginpartten.observer;

/**
 * @Auther: Blank
 * @Description: study.seven.concurrency.desginpartten.observer
 * @Date: 1/14/19
 * @Version: 1.0
 */
public class OneBinaryObserver extends ObserverOne{
    public OneBinaryObserver(SubjectOne subject, String name) {
        super(subject, name);
    }

    @Override
    public void update() {
        System.out.println("Binary String:" + Integer.toBinaryString(subject.getState()));
    }
}
```

subject

```java
package study.seven.concurrency.desginpartten.observer;

/**
 * @Auther: Blank
 * @Description: study.seven.concurrency.desginpartten.observer
 * @Date: 1/14/19
 * @Version: 1.0
 */
public class OneOctalObserver extends ObserverOne {
    public OneOctalObserver(SubjectOne subject, String name) {
        super(subject, name);
    }

    @Override
    public void update() {
        System.out.println("Ocatal String: " + Integer.toOctalString(subject.getState()));
    }
}
```

```java
package study.seven.concurrency.desginpartten.observer;

import java.util.ArrayList;
import java.util.List;

/**
 * @Auther: Blank
 * @Description: study.seven.concurrency.desginpartten.observer
 * @Date: 1/14/19
 * @Version: 1.0
 */
public class SubjectOne {
    private List<ObserverOne> observers = new ArrayList<>();

    private int state;

    public int getState() {
        return this.state;
    }
    public void setState(int state) {
        if(state == this.state) return;
        this.state = state;
        notifyAllObserver();
    }

    public boolean attach(ObserverOne observer) {
        return this.observers.add(observer);
    }
    public boolean detach(ObserverOne observer) {
        return this.observers.remove(observer);
    }

    public void notifyAllObserver() {
        this.observers.stream().forEach(ObserverOne::update);
    }
}
```

client

```java
package study.seven.concurrency.desginpartten.observer;

/**
 * @Auther: Blank
 * @Description: study.seven.concurrency.desginpartten.observer
 * @Date: 1/14/19
 * @Version: 1.0
 */
public class ObserverOneClient {
    public static void main(String[] args) {
        final SubjectOne subject = new SubjectOne();

        subject.attach(new OneBinaryObserver(subject, "binary observer"));
        subject.attach(new OneOctalObserver(subject, "octal observer"));

        System.out.println("======================");
        subject.setState(10);
        System.out.println("======================");
        subject.setState(20);
        System.out.println("======================");
        subject.setState(20);

    }
}
```

