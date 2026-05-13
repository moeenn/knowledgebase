```java
public interface ITransport {
  String deliver();
}
```

```java
public class Boat implements ITransport {
  private final String name;

  public Boat(String name) {
    this.name = name;
  }

  @Override
  public String deliver() {
    return String.format("Delivery through boat %s\n", this.name);
  }
}
```

```java
public class Truck implements ITransport {
  private final String name;

  public Truck(String name) {
    this.name = name;
  }

  @Override
  public String deliver() {
    return String.format("Delivery through truck %s\n", this.name);
  }
}
```

```java
public enum DeliveryMethod {
  BOAT,
  TRUCK,
}
```

```java
public class LogisticsManager {
  private ITransport transport;

  public void identifyTransport(DeliveryMethod method, String name) {
    switch (method) {
      case BOAT:
        this.transport = new Boat(name);
        break;

      case TRUCK:
        this.transport = new Truck(name);
        break;
    }
  }

  public String makeDelivery() {
    return this.transport.deliver();
  }
}
```

```java
import static org.junit.jupiter.api.Assertions.assertTrue;
import org.junit.jupiter.api.Test;

public class LogisticsManagerTest {
  private LogisticsManager manager;

  public LogisticsManagerTest() {
    this.manager = new LogisticsManager();
  }

  @Test
  public void testMakeDelivery() {
    String name = "Boat one";
    this.manager.identifyTransport(DeliveryMethod.BOAT, name);

    String result = manager.makeDelivery();
    assertTrue(result.contains(name));
  }
}
```

```java
public class Main {
  public static void main(String[] args) {
    LogisticsManager manager = new LogisticsManager();
    manager.identifyTransport(DeliveryMethod.TRUCK, "Truck One");

    String result = manager.makeDelivery();
    System.out.println(result);
  }
}
```