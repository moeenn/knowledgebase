
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


