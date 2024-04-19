
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

  // responsibility one
  public double calculateTotal() {
    return (item.getPrice() * quantity) * item.getDiscount();
  }

  // responsibility two
  public void printInvoice() {
    // TODO
  }

  // responsibility three
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


```java
public class CreditCard {
  public void makePayment(double amount) {
    // 
  }
}
```

```java
public class VisaCard extends CreditCard {
  @Override
  public void makePayment(double amount) {
    // 
  }
}
```

```java
public class MasterCard extends CreditCard {
  @Override
  public void makePayment(double amount) {
    // 
  }  
}
```

In this scenario, `VisaCard` and `MasterCard` are derived from `CreditCard` class. The method `makePayment` must have the same signature in all these classes to ensure these classes can be used interchangeably.


**Note**: Ideally in a scenario such as above, I would always prefer to define `CreditCard` as an `interface` and define `VisaCard` and `MasterCard` as concrete implementations. Inheritance should be avoided as much as possible.  However, scenario may arise where we must use inheritance - here ensuring this principle would make perfect sense.

