#### Todo

- [ ] Virtual threads
- [ ] Thread pools [Link](https://www.baeldung.com/thread-pool-java-and-guava)
- [ ] Java interview questions [Link](https://youtu.be/FTyMsFaTV4I?si)
- [ ] Features blog [Link](https://www.marcobehler.com/)
- [ ] Java IO / FS
- [ ] Functional interfaces [Link](https://www.baeldung.com/java-8-functional-interfaces)
- [ ] Java tutorial series [Link](https://www.baeldung.com/get-started-with-java-series)
- [ ] FutureTask [Link](https://www.digitalocean.com/community/tutorials/java-futuretask-example-program)
- [ ] Date time
- [ ] Design patterns
    - [ ] Adapter pattern [Link](https://medium.com/@akshatsharma0610/adapter-design-pattern-in-java-fa20d6df25b8)
    - [ ] Builder pattern
    - [ ] Facade pattern


---

#### Pillars of Object oriented programming

**Abstraction** is the process of hiding unnecessary details of an object’s internal structure. By abstracting an object’s data, its structure and behavior can be kept separate and more easily understood.

**Encapsulation** is the process of wrapping data and related functions into a single unit (object). Encapsulation limits access to object data and methods, preventing their misuse and ensuring their proper functioning.

**Inheritance** is the ability to create a new class (derived class) from an existing one (base class). The child class typically inherits the attributes (members and methods) of the parent class, although it can also redefine them. 

**Polymorphism** is the ability of an object to take on multiple forms. This allows objects of different classes to be used interchangeably, as long as they implement a certain interface. 


---

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

#### Primitive data-types

```java
boolean flag = true;
char grade = 'A';    // a 2-byte character
byte b = 12;	     // signed 8-bit (1-byte) int. Range: -128..127
short s = 24;        // signed 16-bit (2-byte) int. Range: -32,768..32,767
int k = 257;         // signed 4-byte int. Range: -2,147,483,648..2,147,483,647
long l = 890L;       // note the use of ”L” here
float pi = 3.1416F;  // note the use of ”F” here
double e = 2.7182;
```

**Note**: Java doesn't have native unsigned `int`. This functionality can be achieved through external libraries.

**Note**: If a variable is declared by not initialised, using this variable will result in a compile-time error.

**Note**: `final` variables i.e. constants should be named in uppercase, this includes `enum` values. Member variables should be named in camel-case.  


---

#### Classes (i.e. Reference types)

```java
package com.sandbox;

import com.sandbox.modules.Player;
import com.sandbox.modules.Position;
import com.sandbox.modules.Direction;

public class Main {
	public static void main(String[] args) {
		Player p = new Player("Player One", Position.origin());
		p.updatePosition(Direction.RIGHT);
		p.updatePosition(Direction.RIGHT);
		p.updatePosition(Direction.UP);
		System.out.println(p);
	}
}
```

```java
package com.sandbox.modules;

public enum Direction {
  UP,
  DOWN,
  LEFT,
  RIGHT,
}
```

```java
package com.sandbox.modules;

public class Position {
  private int x;
  private int y;

  public Position(int x, int y) {
    this.x = x;
    this.y = y;
  }

  public static Position origin() {
    return new Position(0, 0);
  }

  public int getX() {
    return x;
  }

  public int getY() {
    return y;
  } 

  public void incrementX(int step) {
    this.x += step;
  }

  public void decrementX(int step) {
    this.x -= step;
  } 

  public void incrementY(int step) {
    this.y += step;
  }

  public void decrementY(int step) {
    this.y -= step;
  }

  @Override
  public String toString() {
    return "Position [x=" + x + ", y=" + y + "]";
  }
}
```

```java
package com.sandbox.modules;

public class Player {
  private final String name;
  private Position position;
  private final int step = 10;

  public Player(String name, Position position) {
    this.name = name;
    this.position = position;
  }

  public String getName() {
    return name;
  }

  public Position getPosition() {
    return position;
  }

  public void updatePosition(Direction d) {
    switch (d) {
      case UP:
        position.incrementY(step);
        break;

      case DOWN:
        position.decrementY(step);
        break;

      case LEFT:
        position.decrementX(step);
        break;

      case RIGHT:
        position.incrementX(step);
        break;
    }
  }

  @Override
  public String toString() {
    return "Player [name=" + name + ", position=" + position + "]";
  }
}
```

**Note**: Classes are also called `Reference types` in Java. When we assign an instance of a class to a variable, that variable is called `Reference variable`.  This is because class instance is a memory reference.


##### Pass-by-value and Pass-by-reference
In Java, all method arguments are always copied. In case of reference variables the references are copied (and not the actual object memory).


##### Note on Null safety
Java is a **NOT** a null-safe language. Java compiler allows the following code.

```java
// Point is a custom reference type. All reference types can be null
Point p = null;		
System.out.println(p);
```

```java
// check if variable is null
if (someVal == null) {
    // perform some action with value 
}
```


##### Note on default initialisation

- Numbers are initialised to zero values
- Reference types are initialised to `null`. Notice `String name` in the following example.
- Booleans are initialised to `false`.

```java
package com.sandbox;

public class Entity {
  private int age;
  private String name;
  private boolean isEmployed;  
  private char grade;
  
  @Override
  public String toString() {
    return "Entity [age=" + age + ", name=" + name + ", isEmployed=" + isEmployed + ", grade=" + grade + "]";
  }
}
```

```java
Entity e = new Entity();
System.out.println(e);

// Entity [age=0, name=null, isEmployed=false, grade=]
```


##### References

```java
Counter a = new Counter();
a.increment();

// create alias of a reference variable
Counter b = a;
b.increment();

assert(a.getCount() == 2);
assert(a == b); // true
```


---

#### Access-control modifiers

- `public` 
    - Can be accessed by other classes in the same package
    - Can be accessed by classes outside the package
    - Can be accessed by other derived classes
    
- `protected` 
    - Can be accessed by other classes in the same package 
    - Cannot be accessed by classes outside the package
    - Can be accessed by derived (i.e. child) classes

- `private`
    - Can only be accessed by other methods of the same class


**Note**: If no explicit access control modifier is given, the defined aspect has what is known as **package-private** access level. This allows other classes in the same package to have access, but not any classes or subclasses from other packages.


---

#### Final
A variable can be declared as `final`. If it is a base type, then it is a constant. If a reference variable is final, then it will always refer to the same object (even if that object changes its internal state) (const reference).

Entire methods and classes can also be marked as `final`. A `final method` cannot be overridden by a subclass, and a `final class` cannot even be subclassed (i.e. derived from).


---

#### Constructors

```java
public class Employee {
    private int id;
    private String name;
    private Date startDate;

    // default constructor
    public Employee() {}

    // copy constructor
    public Employee(Employee employee) {
        this.id = employee.id;
        this.name = employee.name; // Strings are immutable, so this is fine
        this.startDate = new Date(employee.startDate.getTime());
    }
}
```


--- 

#### Records

```java
/** records are similar to structs in C/C++ */
public record Person(String name, int age) {
  public void greet() {
    System.out.printf("Hello, %s!\n", name);
  }
}
```

```java
public class Main {
  public static void main(String[] args) {    
    List<Person> people = new ArrayList<>() {
      {
        add(new Person("Player one", 30));
        add(new Person("Player two", 40));
      }
    };

    people.stream().forEach(System.out::println);
  }
}
```


---

#### Runnables

```java
package com.sandbox;

public class Main {
	public static void main(String[] args) {
		Runnable fn = () -> {
			System.out.println("Hello from simple runnable");
		};

		fn.run();
	}
}
```

**Note**: `Runnable` is simply an interface. We can also define classes which implement the `Runnable` interface.

```java
package com.sandbox;

public class Task implements Runnable {
  @Override
  public void run() {
    System.out.println("Hello from custom runnable class");
  }
}
```

```java
package com.sandbox;

public class Main {
	public static void main(String[] args) {
		new Task().run();
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

#### Functional interfaces

```java
@FunctionalInterface
public interface CustomMapCallback<T, E> {
  E map(T value);
}
```

```java
import java.util.ArrayList;
import java.util.List;

public class CustomMap {
  public static <T, E> List<E> map(List<T> items, CustomMapCallback<T, E> callback) {
    List<E> result = new ArrayList<>();
    for (T item : items) {
      result.add(callback.map(item));
    }

    return result;
  }
}
```

```java
import java.util.ArrayList;
import java.util.List;

public class Main {
  public static void main(String[] args) {
    List<Integer> items = new ArrayList<>() {
      {
        add(10);
        add(20);
        add(30);
      }
    };

    List<Integer> result = CustomMap.map(items, (n) -> n * 10);
    System.out.println(result);
  }
}
```

**Note**:  The `FunctionalInterface` annotation enables the compiler to issue warnings or errors in the event that a functional interface is defined inconsistently.

**Note**: The above code is fine, but generally we won't need to define our own functional interfaces. We can update the code as follows.

```java
import java.util.ArrayList;
import java.util.List;
import java.util.function.Function;

public class CustomMap {
  public static <T, E> List<E> map(List<T> items, Function<T, E> callback) {
    List<E> result = new ArrayList<>();
    for (T item : items) {
      result.add(callback.apply(item));
    }

    return result;
  }
}
```


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
      return Optional.empty(); // OR: return null
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
  private final int x;
  private final int y;

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

  @Override
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

**Note**: A class can implement multiple interfaces.


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

  public abstract void makeSound();
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

#### Errors and Exceptions

There are three types in Java
1. Checked exceptions: The classes that directly inherit the `Throwable` class except `RuntimeException` and `Error` are known as checked exceptions. For example, `IOException`, `SQLException`, etc. Checked exceptions are checked at compile-time.
2. Unchecked exceptions: The classes that inherit the `RuntimeException` are known as unchecked exceptions. For example, `ArithmeticException`, `NullPointerException`, `ArrayIndexOutOfBoundsException`, etc. Unchecked exceptions are not checked at compile-time, but they are checked at runtime.
3. Errors: `Error` is irrecoverable. Some example of errors are `OutOfMemoryError`, `VirtualMachineError`, `AssertionError` etc.

```java
public class Operations {
  public int performCalculation(int n) throws ArithmeticException {
    return 10 / n;
  }
}
```

```java
public class Main {
  public static void main(String[] args) {
    Operations op = new Operations();

    try {
      int result = op.performCalculation(2);
      System.out.println(result);
    } catch (ArithmeticException ex) {
      System.out.printf("error: %s\n", ex.getMessage());
    }
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


---

#### Environment variables

```java
package com.sandbox;

public class Env {
  public static String Get(String key) throws Exception {
    String value = System.getenv(key);
    if (value == null) {
      throw new Exception(
          String.format("Env variable not found: '%s'", key));
    }
    return value;
  }

  public static String Get(String key, String fallback) {
    String value = System.getenv(key);
    if (value == null) {
      return fallback;
    }
    return value;
  }
}
```

**Note**: The above example uses method over-loading for defining optional parameters.


---
