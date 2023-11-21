```java
package com.sandbox;

public interface IContext {
  void setStrategy(IRouteStrategy strategy);
  String executeStrategy(Location start, Location end);
}
```

```java
package com.sandbox;

public class RouteContext implements IContext {
  private IRouteStrategy strategy;

  public void setStrategy(IRouteStrategy strategy) {
    this.strategy = strategy;
  }
  
  @Override
  public String executeStrategy(Location start, Location end) {
    return this.strategy.execute(start, end);
  }  
}
```

```java
package com.sandbox;

public interface IRouteStrategy {
  String execute(Location start, Location end);
}
```

```java
package com.sandbox;

public class WalkStrategy implements IRouteStrategy {
  @Override
  public String execute(Location start, Location end) {
    return String.format("This is how you walk from %s to %s\n", 
	    start.toString(), end.toString());
  }  
}
```

```java
package com.sandbox;

public class DriveStrategy implements IRouteStrategy {
  @Override
  public String execute(Location start, Location end) {
    return String.format("This is how you drive from %s to %s\n",
        start.toString(), end.toString());
  }
}
```

```java
package com.sandbox;

public class Location {
  private final double lat;
  private final double lng;
  
  public Location(double lat, double lng) {
    this.lat = lat;
    this.lng = lng;
  }

  public double getLat() {
    return lat;
  }

  public double getLng() {
    return lng;
  }

  @Override
  public String toString() {
    return "Location [lat=" + lat + ", lng=" + lng + "]";
  }
}
```

```java
package com.sandbox;

import static org.junit.jupiter.api.Assertions.assertTrue;

import org.junit.jupiter.api.Test;

public class RouteContextTest {
  private IContext context;
  private final Location start;
  private final Location end;

  public RouteContextTest() {
    this.context = new RouteContext();
    this.start = new Location(30.44, 40.66);
    this.end = new Location(10.34, 20.67);
  }

  @Test
  void testWalkStrategy() {
    WalkStrategy strategy = new WalkStrategy();
    this.context.setStrategy(strategy);

    String result = this.context.executeStrategy(this.start, this.end);
    assertTrue(result.contains("walk"));
  }

  @Test
  void testDriveStrategy() {
    DriveStrategy strategy = new DriveStrategy();
    this.context.setStrategy(strategy);

    String result = this.context.executeStrategy(this.start, this.end);
    assertTrue(result.contains("drive"));    
  }
}
```

```java
package com.sandbox;

public class Main {
  public static void main(String[] args) {
    RouteContext context = new RouteContext();
    Location start = new Location(30.44, 40.66);
    Location end = new Location(10.34, 20.67);

    WalkStrategy strategy = new WalkStrategy();
    context.setStrategy(strategy);

    String result = context.executeStrategy(start, end);
    System.out.println(result);
  }
}
```
