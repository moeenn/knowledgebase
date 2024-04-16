```java
package com.sandbox;

public interface ISubscriber {
  String getId();
  void update();
}
```

```java
package com.sandbox;

public interface IPublisher {
  void addSubscriber(ISubscriber subscriber);
  void removeSubscriber(ISubscriber subscriber);
  void notifySubscribers();
}
```

```java
package com.sandbox;

import java.util.UUID;

public class TestSubscriber implements ISubscriber {  
  private String id;

  public TestSubscriber() {
    this.id = UUID.randomUUID().toString();
  }

  @Override
  public String getId() {
    return this.id;
  }

  @Override
  public void update() {
    System.out.printf("%s: subscriber has received a message\n", this.id);
  }
}
```

```java
package com.sandbox;

import java.util.ArrayList;
import java.util.List;

public class TestPublisher implements IPublisher {
  private List<ISubscriber> subscribers;

  public TestPublisher() {
    this.subscribers = new ArrayList<>();
  }

  @Override
  public void addSubscriber(ISubscriber subscriber) {
    this.subscribers.add(subscriber);
  }

  @Override
  public void removeSubscriber(ISubscriber subscriber) {
    this.subscribers.removeIf(sub -> sub.getId().equals(subscriber.getId()));
  }

  @Override
  public void notifySubscribers() {
    this.subscribers.stream().forEach(sub -> sub.update());
  }
}
```

```java
package com.sandbox;

public class Main {
  public static void main(String[] args) {
    TestPublisher publisher = new TestPublisher();

    TestSubscriber subOne = new TestSubscriber();
    TestSubscriber subTwo = new TestSubscriber();
    TestSubscriber subThree = new TestSubscriber();

    publisher.addSubscriber(subOne);
    publisher.addSubscriber(subTwo);
    publisher.addSubscriber(subThree);
    publisher.notifySubscribers();

    publisher.removeSubscriber(subTwo);
    publisher.notifySubscribers();
  }
}
```