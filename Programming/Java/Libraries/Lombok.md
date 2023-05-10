##### Class without Lombok
```java
public class Customer {
  private Long id;
  private String name;
  private String email;
  private String password;

  /* all args constructor */
  public Customer(Long id, String name, String email, String password) {
    this.id = id;
    this.name = name;
    this.email = email;
    this.password = password;
  }

  /* getters and setters for all member variables */
  public Long getId() {
    return id;
  }

  public void setId(Long id) {
    this.id = id;
  }

  public String getName() {
    return name;
  }

  public void setName(String name) {
    this.name = name;
  }

  public String getEmail() {
    return email;
  }

  public void setEmail(String email) {
    this.email = email;
  }  

  public String getPassword() {
    return password;
  }

  public void setPassword(String password) {
    this.password = password;
  }

  @Override
  public String toString() {
    return "Customer [id=" + id + ", name=" + name + ", email=" + email + ", password=" + password + "]";
  }  
}
```


##### Using Lombok
```java
import lombok.AllArgsConstructor;
import lombok.EqualsAndHashCode;
import lombok.Getter;
import lombok.Setter;
import lombok.ToString;

@ToString
@AllArgsConstructor
@EqualsAndHashCode
public class Customer {
  @Getter @Setter private Long id;
  @Getter @Setter private String name;
  @Getter @Setter private String email;
  @Getter @Setter private String password;
}
```


##### Even further code reduction
```java
import lombok.Data;

@Data
public class Customer {
  private Long id;
  private String name;
  private String email;
  private String password;
}
```
