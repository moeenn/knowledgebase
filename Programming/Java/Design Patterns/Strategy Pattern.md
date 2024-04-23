```java
public record Location(double lat, double lng) {}
```

```java
public interface RouteStrategy {
  String execute(Location start, Location end);
}
```

```java
public class WalkStrategy implements RouteStrategy {
  @Override
  public String execute(Location start, Location end) {
    return String.format("This is how you walk from %s, to %s", 
        start.toString(), end.toString());
  }
}
```

```java
public class DriveStrategy implements RouteStrategy {
  @Override
  public String execute(Location start, Location end) {
    return String.format("This is how you drive from %s, to %s",
        start.toString(), end.toString());
  }
}
```

```java
public class RouteContext {
  private RouteStrategy strategy;

  public void setStrategy(RouteStrategy strategy) {
    this.strategy = strategy;
  }
  
  public String executeStategy(Location start, Location end) {
    return this.strategy.execute(start, end);
  }
}
```

```java
import static org.junit.jupiter.api.Assertions.assertTrue;
import org.junit.jupiter.api.Test;

public class TestRouteContext {
  private RouteContext context;
  private Location start;
  private Location end;

  public TestRouteContext() {
    this.context = new RouteContext();
    this.start = new Location(30.55, 40.66);
    this.end = new Location(60.22, 70.33);
  }  

  @Test
  public void testWalkStrategy() {
    WalkStrategy strategy = new WalkStrategy();
    this.context.setStrategy(strategy);

    String result = this.context.executeStategy(start, end);
    assertTrue(result.contains("walk"));
  }

  @Test
  public void testDriveStrategy() {
    DriveStrategy strategy = new DriveStrategy();
    this.context.setStrategy(strategy);

    String result = this.context.executeStategy(start, end);
    assertTrue(result.contains("drive"));
  }
}
```