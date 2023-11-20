
#### Installation
Java and its build toolchains can be installed using the os package managers. Following is an example.

```bash
$ sudo apt-get install default-jdk libeclipse-jdt-core-java maven
```

The above option works but it is not very flexible. A much better option is to use `sdkman` to install specific versions of java and build tools / packages / CLIs.

```bash
# installing sdkman (**NOTE** Always check their website for the latest command)
$ curl -s "https://get.sdkman.io" | bash

# list out different version of java available
$ sdk list java

# install java specific version
$ sdk install java 21-ms

# set default version of java
$ sdk use java 21-ms
```

#### Hello world
```java
public class Main {
  public static void main(String[] args) {
    System.out.println("Hello world");
  }
}
```

```bash
$ javac ./Main.java
$ java Main
```


---

#### Exceptions
```java
/** file: Main.java */
package com.app;

public class Main {
  public static void main(String... args) {
    Entity e = new Entity(0, 0);
    try {
      e.move(Entity.Direction.UP);
      e.move(Entity.Direction.LEFT);
    } 
    catch (Exception ex) {
      System.out.println(ex.getMessage());
    }

    System.out.println(e.serialize());
  }
}
```

```java
/** file: Entity.java */
package com.app;

public class Entity {
  private int x;
  private int y;
  private int step = 20;
  private int lower_bound = 0;
  private int upper_bound = 100;

  public enum Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT,
  }

  public Entity(int x, int y) {
    this.x = x;
    this.y = y;
  }

  // redundant: use toString method instead
  public String serialize() {
    return String.format("Entity(x=%d, y=%d)", this.x, this.y);
  }

  private boolean isWithinBounds() {
    return (this.x > this.lower_bound && this.y > this.lower_bound &&
            this.x < this.upper_bound && this.y < this.upper_bound);
  }

  public void move(Direction d) throws Exception {
    switch (d) {
    case UP:
      this.y += this.step;
      break;

    case DOWN:
      this.y -= this.step;
      break;

    case LEFT:
      this.x -= this.step;
      break;

    case RIGHT:
      this.x += this.step;
      break;
    }

    if (!this.isWithinBounds()) {
      throw new Exception(
          String.format("out of bounds: x: %d, y: %d", this.x, this.y));
    }
  }
}
```


---

#### Generics
```java
package com.app;

import java.util.ArrayList;

public class Main {
  public static void main(String... args) {
    /** cannot call static methods with "this" */
    printIntegers();
    printFloats();
    printDoubles();
    printBooleans();
  }

  private static <T> void print(ArrayList<T> values) {
    for (T v : values) {
      System.out.println(v);
    }
  }

  private static void printIntegers() {
    ArrayList<Integer> nums = new ArrayList() {
      {
        add(30);
        add(40);
        add(60);
      }
    };

    print(nums);
  }

  private static void printFloats() {
    ArrayList<Float> nums = new ArrayList() {
      {
        add(30.00f);
        add(40.45f);
        add(60.70f);
      }
    };

    print(nums);
  }

  private static void printDoubles() {
    ArrayList<Double> nums = new ArrayList() {
      {
        add(30.00d);
        add(40.45d);
        add(60.70d);
      }
    };

    print(nums);
  }

  private static void printBooleans() {
    ArrayList<Boolean> bools = new ArrayList() {
      {
        add(true);
        add(true);
        add(false);
      }
    };

    print(bools);
  }
}
```

- `Integer`, `Float`, `Double`, `Boolean` are called **Reference types**. We cannot pass primitive types to Generic classes.
- In generic method definition, the generic symbol appears before the return type of the method. 


---

#### Optionals
```java
public class Position {
  public int x;
  public int y;

  public Position(int x, int y) {
    this.x = x;
    this.y = y;
  }

  @Override
  public String toString() {
    return "Position [x=" + x + ", y=" + y + "]";
  }
}
```

```java
import java.util.Optional;

public class Entity {
  private Position position;

  public Entity() {
    this.position = new Position(0, 0);
  }

  public Optional<Position> move(Position position) {
    if (position.x < 0 || position.y < 0) {
      return null;
    }

    this.position.x += position.x;
    this.position.y += position.y;

    return Optional.ofNullable(this.position);
  }
}
```

```java
import java.util.Optional;

public class Main {
  public static void main(String[] args) {
    Entity e = new Entity();

    Position moveDelta = new Position(10, 20);
    Optional<Position> currentPosition = e.move(moveDelta);

	/* method one: meh! */
    if (currentPosition.isEmpty()) {
      System.out.println("object was empty");
    }

    if (currentPosition.isPresent()) {
      System.out.println(currentPosition.get());
    }

    /* method two: better option */
    currentPosition.ifPresentOrElse(
        (position) -> System.out.println(position),
        () -> System.out.println("object was empty"));
  }
}
```


---

#### Inheritance
Java doesn’t support Multiple Inheritance. 

```java
/** file: Entity.java */
package com.app;

public class Entity {
  private int x;
  private int y;

  public Entity(int x, int y) {
    this.x = x;
    this.y = y;
  }

  public void speak() {
    System.out.println("Entity spoke");
  }
}
```

```java
/** file: Person.java */
package com.app;

public class Person extends Entity {
  public Person(int x, int y) {
    super(x, y);
  }

  public void speak() {
    System.out.println("Person spoke");
  }
}
```

```java
/** file: Main.java */
package com.app;

public class Main {
  public static void main(String... args) {
    Entity e = new Entity(10, 30);
    Person p = new Person(50, 60);

    e.speak();  /** Entity spoke */
    p.speak();  /** Person spoke */
  }
}
```


---

#### Interfaces
All methods defined inside an interface are, by default, `public` and `abstract`.

```java
/** file: IEntity.java */
package com.app;

interface IEntity {
  void speak();  
}
```

```java
/** file: Person.java */
package com.app;

public class Person implements IEntity {
  public void speak() {
    System.out.println("Person spoke");
  }
}
```

```java
/** file: Main.java */
package com.app;

public class Main {
  public static void main(String... args) {
    Person p = new Person();
    p.speak();
  }
}
```


---

#### Abstract Classes
```java
/* file: Animal.java */
public abstract class Animal {
  private String name;

  public Animal(String name) {
    this.name = name;
  }

  public String getName() {
    return this.name;
  }

  abstract public void makeSound();
}
```

```java
/* file: Cat.java */
public class Cat extends Animal {
  public Cat(String name) {
    super(name);
  }

  @Override
  public void makeSound() {
    System.out.println("meow!");
  }
}
```

```java
/* file: Main.java */
public class Main {
  public static void main(String[] args) {
    Cat c = new Cat("jakarta");
    c.makeSound();
  }
}
```


---

#### UUID
UUID can be generated in Java without requiring any third party libraries. 

```java
import java.util.UUID;
...
UUID uuid = UUID.randomUUID();
```
