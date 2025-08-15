
```xml
<dependencies>
  <dependency>
    <groupId>jakarta.validation</groupId>
    <artifactId>jakarta.validation-api</artifactId>
    <version>3.1.1</version>
  </dependency>
  <dependency>
    <groupId>org.hibernate.validator</groupId>
    <artifactId>hibernate-validator</artifactId>
    <version>8.0.1.Final</version> 
  </dependency>
  <dependency>
    <groupId>org.glassfish</groupId>
    <artifactId>jakarta.el</artifactId>
    <version>4.0.2</version>
  </dependency>    
</dependencies>
```


```java
package com.sandbox;

import java.util.Date;

import jakarta.validation.Valid;
import jakarta.validation.constraints.Email;
import jakarta.validation.constraints.Max;
import jakarta.validation.constraints.Min;
import jakarta.validation.constraints.NotBlank;
import jakarta.validation.constraints.PastOrPresent;
import jakarta.validation.constraints.Size;
import org.hibernate.validator.constraints.UUID;

@Valid
public class User {
    @NotBlank
    @UUID
    String id;

    @NotBlank
    @Email
    String email;

    @NotBlank
    @Size(min = 3, max = 20) // For strings.
    String name;

    @NotBlank
    @Size(min = 8)
    String password;

    @Min(18) // For numbers.
    @Max(60)
    int age;

    @PastOrPresent
    Date createdAt;

    public User() {
    }

    public User(String id, String email, String name, String password, int age, Date createdAt) {
        this.id = id;
        this.email = email;
        this.name = name;
        this.password = password;
        this.age = age;
        this.createdAt = createdAt;
    }

    public String getId() {
        return id;
    }

    public String getEmail() {
        return email;
    }

    public String getName() {
        return name;
    }

    public String getPassword() {
        return password;
    }

    public int getAge() {
        return age;
    }

    public Date getCreatedAt() {
        return createdAt;
    }

    public void setId(String id) {
        this.id = id;
    }

    public void setEmail(String email) {
        this.email = email;
    }

    public void setName(String name) {
        this.name = name;
    }

    public void setPassword(String password) {
        this.password = password;
    }

    public void setAge(int age) {
        this.age = age;
    }

    public void setCreatedAt(Date createdAt) {
        this.createdAt = createdAt;
    }

    @Override
    public String toString() {
        return "User [id=" + id + ", email=" + email + ", name=" + name + ", age=" + age + ", createdAt=" + createdAt
                + "]";
    }
}
```

```java
package com.sandbox;

import java.util.Date;
import java.util.Set;
import java.util.UUID;
import jakarta.validation.ConstraintViolation;
import jakarta.validation.Validation;
import jakarta.validation.Validator;

public class Main {
    private static Validator validator = Validation.buildDefaultValidatorFactory().getValidator();

    public static void main(String[] args) {
        var user = new User() {
            {
                setId(UUID.randomUUID().toString());
                setEmail("admin@site.com");
                setName("Mr. Admin");
                setPassword("password123");
                setAge(18);
                setCreatedAt(new Date());
            }
        };

        Set<ConstraintViolation<User>> errors = validator.validate(user);
        for (ConstraintViolation<User> err : errors) {
            System.out.printf("%s - %s\n", err.getPropertyPath(), err.getMessage());
        }
    }
}
```