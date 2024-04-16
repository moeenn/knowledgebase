#### Todo

- [ ] Exceptions: [Link](https://www.javatpoint.com/exception-handling-in-java)


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

**Note**: If a variable is declared by not initialized, using this variable will result in a compile-time error.


---

#### Classes (i.e. Reference types)

```java
/** file: Main.java */
package com.sandbox;

/**
 * Note: This class contains the entry-point `main` method. Therefore, this 
 * class is called `Universe class`.
 */ 
public class Main {
  public static void main(String... args) {
    // `new` keyword returns a reference to the reference type
    Entity e = new Entity(0, 0);
    try {
      e.move(Entity.Direction.UP);
      e.move(Entity.Direction.LEFT);
    } 
    catch (Exception ex) {
      System.out.println(ex.getMessage());
    }

    System.out.println(e);
  }
}
```

```java
/** file: Direction.java */
package com.sandbox;

public enum Direction {
  UP,
  DOWN,
  LEFT,
  RIGHT,
}
```

```java
/** file: Entity.java */
package com.sandbox;

public class Entity {
  private int x;
  private int y;
  private int step = 20;
  private int lower_bound = 0;
  private int upper_bound = 100;

  public Entity(int x, int y) {
    this.x = x;
    this.y = y;
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

  @Override
  public String toString() {
    return String.format("Entity(x=%d, y=%d)", this.x, this.y);
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
A variable can be declared as `final`. If it is a base type, then it is a constant. If a reference variable is final, then it will always refer to the same object (even if that object changes its internal state).

Entire methods and classes can also be marked as `final`. A `final method` cannot be overridden by a subclass, and a `final class` cannot even be subclassed.


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
import java.util.ArrayList;

public class Main {
  public static void main(String[] args) {    
    ArrayList<Person> people = new ArrayList<>() {
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

#### UUID
UUID can be generated in Java without requiring any third party libraries. 

```java
import java.util.UUID;
...
UUID uuid = UUID.randomUUID();
```



#### TODO

```
https://www.baeldung.com/thread-pool-java-and-guava
https://youtu.be/FTyMsFaTV4I?si
https://www.marcobehler.com/
```

