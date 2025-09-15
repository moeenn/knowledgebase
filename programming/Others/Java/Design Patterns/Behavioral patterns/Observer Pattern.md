```java
public interface Subscriber {
  String getId();
  String getLastMessage();
  void update();
}
```

```java
public interface Publisher {
  void addSubscriber(Subscriber sub);
  void removeSubscriber(Subscriber sub);
  void notifySubscribers();
}
```

```java
import java.util.UUID;

public class ExampleSubscriber implements Subscriber {
  private final String id;
  private String lastMessage;

  public ExampleSubscriber() {
    this.id = UUID.randomUUID().toString();
  }

  @Override
  public String getId() {
    return this.id;
  }

  @Override
  public String getLastMessage() {
    return this.lastMessage;
  }

  @Override
  public void update() {
    lastMessage = String.format("Message received by sub # %s", this.id);
    System.out.println(lastMessage);
  }
}
```

```java
import java.util.ArrayList;
import java.util.List;

public class ExamplePublisher implements Publisher {
  private List<Subscriber> subscribers;

  public ExamplePublisher() {
    subscribers = new ArrayList<>();
  }

  @Override
  public void addSubscriber(Subscriber sub) {
    subscribers.add(sub);
  }  

  @Override
  public void removeSubscriber(Subscriber sub) {
    subscribers.removeIf(s -> s.getId().equals(sub.getId()));
  }

  @Override
  public void notifySubscribers() {
    subscribers.stream().forEach(s -> s.update());
  }
}
```

```java
import static org.junit.jupiter.api.Assertions.assertNotNull;
import static org.junit.jupiter.api.Assertions.assertNull;
import static org.junit.jupiter.api.Assertions.assertTrue;
import org.junit.jupiter.api.Test;

public class TestExamplePublisher {
  private Publisher pub;
  
  public TestExamplePublisher() {
    pub = new ExamplePublisher();
  }

  @Test
  public void testPublisherPublish() {
    Subscriber sub = new ExampleSubscriber();
    pub.addSubscriber(sub);
    assertNull(sub.getLastMessage());

    pub.notifySubscribers();
    assertTrue(sub.getLastMessage().contains(sub.getId()));
  }

  @Test
  public void testRemoveSubscriber() {
    Subscriber subOne = new ExampleSubscriber();
    Subscriber subTwo = new ExampleSubscriber();
  
    pub.addSubscriber(subOne);
    pub.addSubscriber(subTwo);
    pub.removeSubscriber(subOne);
    pub.notifySubscribers();

    assertNull(subOne.getLastMessage());
    assertNotNull(subTwo.getLastMessage());
  }
}
```