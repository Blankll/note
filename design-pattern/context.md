通过一个单例，将上下文值唯一，同时通过一个

ThreadLocal来存储值，保证线程间的隔离

```java
Context {
    private String name;
    private String cardId;

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getCardId() {
        return cardId;
    }

    public void setCardId(String cardId) {
        this.cardId = cardId;
    }
}
```



```java
public final class ActionContext {
    private static final ThreadLocal<Context> threadLocal = new ThreadLocal<>() {
        @Override
        protected Context initialValue() {
            return new Context();
        }
    };

    private static class ContextHolder {
        private final static ActionContext instance = new ActionContext();
    }

    public static ActionContext getActionContext() {
        return ContextHolder.instance;
    }

    public Context getContext() {
        return threadLocal.get();
    }
}
```



```java
public class QueryFromDBAction {
    public void execute() {
        try {
            Thread.sleep(1000L);
            String name = "Alex " + Thread.currentThread().getName();
            ActionContext.getActionContext().getContext().setName(name);

            System.out.println(name);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }
}
```

```java
public class QueryFromHttpAction {
    public void execute() {
        Context context = ActionContext.getActionContext().getContext();
        String name = context.getName();
        String cardId = getCardId(name);
        context.setCardId(cardId);
    }

    private String getCardId(String name) {
        try {
            Thread.sleep(1000L);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        return "ksdfjdskf" + Thread.currentThread().getName();
    }

}
```





```java
public class ExecutionTask implements Runnable {
    private QueryFromDBAction queryFromDBAction = new QueryFromDBAction();
    private QueryFromHttpAction queryFromHttpAction = new QueryFromHttpAction();
    @Override
    public void run() {
        queryFromDBAction.execute();
        System.out.println("name query successful");
        queryFromHttpAction.execute();
        System.out.println("card id query successful");

        Context context = ActionContext.getActionContext().getContext();
        System.out.println("name: " + context.getName() + "; card id: " + context.getCardId());
    }
}
```



```java
public class Client {
    public static void main(String[] args) {
        IntStream.range(1, 5).forEach(i -> {
            new Thread(new ExecutionTask()).start();
        });
    }
}
```

