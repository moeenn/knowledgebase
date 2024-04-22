
#### Todo
- [Link](https://www.digitalocean.com/community/conceptual-articles/s-o-l-i-d-the-first-five-principles-of-object-oriented-design)  
- [Link](https://www.freecodecamp.org/news/solid-principles-for-better-software-design/#:~:text=The%20SOLID%20principles%20are%20a,understand%2C%20modify%2C%20and%20extend).


- Single-responsibility
- Open-closed
- Liskov substitution
- Interface segregation
- Dependency inversion


---

#### Single-responsibility principle

- A class must only have a single job
- It must only one reason to change


```java
public interface Invoicable {
  double getPrice();
  double getDiscount();
}
```

```java
public class Marker implements Invoicable {
  private final double price;
  private double discountPercentage;

  public Marker(double price, double discountPercentage) {
    this.price = price;
    this.discountPercentage = discountPercentage;
  }

  public double getPrice() {
    return price;
  }

  public double getDiscount() {
    return price * discountPercentage;
  }  
}
```

```java
public class Invoice {
  private final Invoicable item;
  private final int quantity;

  public Invoice(Invoicable item, int quantity) {
    this.item = item;
    this.quantity = quantity;
  }

  // responsibility # 1
  public double calculateTotal() {
    return (item.getPrice() * quantity) * item.getDiscount();
  }

  // responsibility # 2
  public void printInvoice() {
    // TODO
  }

  // responsibility # 3
  public void saveInvoiceToDB() {
    // TODO
  }
}
```

In the above example, the `Invoice` class has multiple responsibilities. Ideally, we should split these responsibilities into their own dedicated classes.

```java
public class Invoice {
  private final Invoicable item;
  private final int quantity;

  public Invoice(Invoicable item, int quantity) {
    this.item = item;
    this.quantity = quantity;
  }

  public double calculateTotal() {
    return (item.getPrice() * quantity) - item.getDiscount();
  }
}
```

```java
public class InvoicePrinter {
  private final Invoice invoice;

  public InvoicePrinter(Invoice invoice) {
    this.invoice = invoice;
  }

  public void printInvoiceFormatOne() {
    // TODO
  }

  public void printInvoiceFormatTwo() {
    // TODO
  }
}
```

```java
public class InvoiceDAO {
  public void saveInvoiceToDB(Invoice invoice) {
    // TODO
  }
}
```

**Note**: `DAO` stands for Data access object. `DAO` is a pattern that provides an abstract interface to some type of database or other persistence mechanism.


---

#### Open-closed principle

- Objects or entities should be open for extension but closed for modification.
- In practice, this means that we should be able to add new functionality without modifying existing code.

```java
public class PaymentProcessor {
  public void processCreditCard() {
    // 
  }

  public void processPaypal() {
    // 
  }
}
```

The above code violates the Open/Closed principle. Here is how we can fix it.

```java
public interface PaymentProcessor {
  void processPayment();
}
```

```java
public class BankPaymentProcessor implements PaymentProcessor {
  @Override
  public void processPayment() {
    // 
  }
}
```

```java
public class PaypalPaymentProcessor implements PaymentProcessor {
  @Override
  public void processPayment() {
    // 
  }
}
```

This fixes the extensibility problem. Anytime a new payment processor needs to be implemented, we can simply implement it as a concrete implementation of `PaymentProcessor` interface.


---

#### Liskov Substitution principle

Any instance of a derived class should be substitutable for an instance of its base class without affecting the correctness of the program.

Liskov substitution principle goes beyond just method parameters and return types. It is necessary where some code thinks it is calling the methods of a type `T`, and may unknowingly call the methods of a type `S`, where `S extends T`. If this program breaks in a situation where it is provided an instance of derived class of `S`, then there is a LSP violation.

```java
public interface Bike {
  void turnOnEngine();
  void accelerate(double by);
}
```

```java
public class Motorbike implements Bike {
  private boolean engine;
  private double speed;
  
  public Motorbike(boolean engine, double speed) {
    this.engine = engine;
    this.speed = speed;
  }

  @Override
  public void turnOnEngine() {
    this.engine = true;
  }

  @Override
  public void accelerate(double by) {
    this.speed += by;
  }
}
```

```java
// class violating the liskov-substitution principle
public class Bicycle implements Bike {
  private double speed;

  public Bicycle(double speed) {
    this.speed = speed;
  }

  @Override
  public void turnOnEngine() throws AssertionError {
    throw new AssertionError("Bicycle does not have engine");
  }
  
  @Override
  public void accelerate(double by) {
    this.speed += by;
  }
}
```

In this example, `Motorbike` correctly implements the `Bike` interface. However, since `Bicycle` does not have an engine, it cannot correctly implement the interface. This is because `turnOnEngine` method in `Bicycle` can throw an `AssertionError` which means it can break the program if used together with other classes which implement `Bike` interface.


---

#### Interface segregation principle

The Interface Segregation Principle (ISP) focuses on designing interfaces that are specific to their client's needs. It states that no client should be forced to depend on methods it does not use.

```java
public interface Vehicle {
  void startEngine();
  void stopEngine();
  void drive();
  void fly();
}
```

```java
public class Car implements Vehicle {
  @Override
  public void startEngine() {
    // 
  }

  @Override
  public void stopEngine() {
    //
  }

  @Override
  public void drive() {
    // 
  }

  @Override
  public void fly() throws AssertionError {
    throw new AssertionError("Car cannot fly");
  }
}
```

```java
public class Airplane implements Vehicle {
  @Override
  public void startEngine() {
    // 
  }

  @Override
  public void stopEngine() {
    // 
  }

  @Override
  public void drive() throws AssertionError {
    throw new AssertionError("Airplane cannot drive");
  }
  
  @Override
  public void fly() {
    // 
  }
}
```

The `Vehicle` interface violates the ISP, because it defines too many responsibilities. E.g. `Car` class implements this interface but does not need the `fly` method. Similarly, `Airplane` implements the interface but does not need the `drive` method.

```java
public interface Enginable {
  void startEngine();
  void stopEngine();
}
```

```java
public interface Drivable {
  void drive();
}
```

```java
public interface Flyable {
  void fly();
}
```

```java
public class Car implements Enginable, Drivable {
  @Override
  public void startEngine() {
    // 
  }

  @Override
  public void stopEngine() {
    //
  }

  @Override
  public void drive() {
    // 
  }
}
```

```java
public class Airplane implements Enginable, Flyable {
  @Override
  public void startEngine() {
    // 
  }

  @Override
  public void stopEngine() {
    // 
  }

  @Override
  public void fly() {
    // 
  }
}
```


---

#### Dependency Inversion Principle 

