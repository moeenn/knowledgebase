`jackson` is the standard library for working with `JSON` in Java. To use it, we must add the following dependencies to our project `pom.xml` file.

```xml
<dependencies>
  <dependency>
    <groupId>com.fasterxml.jackson.core</groupId>
    <artifactId>jackson-databind</artifactId>
    <version>2.13.3</version>
  </dependency>

  <dependency>
    <groupId>com.fasterxml.jackson.datatype</groupId>
    <artifactId>jackson-datatype-jdk8</artifactId>
    <version>2.13.3</version>
  </dependency>
</dependencies>
```

**Note**: Ensure the version number of both the dependencies matches.

```gradle
dependencies {
    implementation 'com.fasterxml.jackson.core:jackson-core:2.13.3'
    implementation 'com.fasterxml.jackson.core:jackson-annotations:2.13.3'
    implementation 'com.fasterxml.jackson.core:jackson-databind:2.13.3'
}
```


---

#### Usage

```java
package com.sandbox;

import com.fasterxml.jackson.core.JsonProcessingException;
import com.fasterxml.jackson.databind.ObjectMapper;
import com.fasterxml.jackson.datatype.jdk8.Jdk8Module;

public class JSONManager {
  private ObjectMapper mapper;

  public JSONManager() {
    this.mapper = new ObjectMapper();

    // allow serialization of Optional type
    Jdk8Module module = new Jdk8Module();
    this.mapper.registerModule(module);
  }

  public <T> String serialize(T object) throws JsonProcessingException {
    return this.mapper.writeValueAsString(object);
  }
}
```

```java
package com.sandbox.models;

import java.util.Optional;
import lombok.Data;
import lombok.AllArgsConstructor;

@Data
@AllArgsConstructor
public class User {
  private Long id;
  private String email;
  private UserRole role;
  private Optional<Password> password;
  private Profile profile;
}
```

```java
package com.sandbox.models;

import lombok.AllArgsConstructor;
import lombok.Data;

@Data
@AllArgsConstructor
public class Password {
  private String hash;
}
```

```java
package com.sandbox.models;

public enum UserRole {
  ADMIN,
  CLIENT,
}
```

```java
package com.sandbox.models;

import lombok.AllArgsConstructor;
import lombok.Data;

@Data
@AllArgsConstructor
public class Profile {
  private Long id;
  private String address;
  private String city;
}
```

```java
package com.sandbox;

import java.util.Optional;
import com.fasterxml.jackson.core.JsonProcessingException;
import com.sandbox.models.User;
import com.sandbox.models.UserRole;
import com.sandbox.models.Password;
import com.sandbox.models.Profile;

public class Main {
  public static void main(String[] args) {
    User user = Main.buildUser();
    JSONManager manager = new JSONManager();
    try {
      String json = manager.serialize(user);
      System.out.println(json);
    } catch (JsonProcessingException ex) {
      System.out.println("error" + ex.getMessage());
    }
  }

  private static User buildUser() {
    Password password = new Password("q1w2e3r4");
    Profile profile = new Profile(
      20L,
      "123 Main street",
      "Lahore"
    );

    User user = new User(
      10L, 
      "admin@site.com", 
      UserRole.ADMIN,
      Optional.ofNullable(password),
      profile
    );

    return user;
  }
}
```

