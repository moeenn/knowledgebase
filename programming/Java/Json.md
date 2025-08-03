```xml
<dependency>
  <groupId>com.fasterxml.jackson.core</groupId>
  <artifactId>jackson-databind</artifactId>
  <version>2.18.0</version>
</dependency>

<!-- for handling optional data -->
<dependency>
  <groupId>com.fasterxml.jackson.datatype</groupId>
  <artifactId>jackson-datatype-jdk8</artifactId>
  <version>2.18.0</version>
</dependency>
```


---

#### Parse JSON

```java
package com.sandbox;

import com.fasterxml.jackson.annotation.JsonIgnoreProperties;
import com.fasterxml.jackson.annotation.JsonProperty;

/** 
 * if JsonIgnoreProperties annotation is not present, jackson will throw errors
 * in case any unknown properties are present in json. This annotation silences that
 * error.
 */
@JsonIgnoreProperties(ignoreUnknown = true)
public class UserResponse {
	/** Map json key "user_id" to "userId" field. */
    @JsonProperty("user_id")
    private int userId;

    @JsonProperty("full_name")
    private String fullName;

    private String email;

    /** this enum will be validated automatically. */
    private UserRole role;

	/** 0/1 in json will automatically be casted to boolean here. */
	private boolean isAdmin;

	@JsonFormat(shape = JsonFormat.Shape.STRING, pattern = "yyyy-MM-dd HH:mm:ss", timezone = "Asia/Karachi")
	private Date createdAt;

    /** default constructor is required for read-in from Jackson */
    public UserResponse() {
    }

    public int getUserId() {
        return userId;
    }

    public void setUserId(int userId) {
        this.userId = userId;
    }

    public String getEmail() {
        return email;
    }

    /** setters will be used by Jackson. */
    public void setEmail(String email) {
        this.email = email;
    }

    public String getFullName() {
        return fullName;
    }

    public void setFullName(String fullName) {
        this.fullName = fullName;
    }

	public void setIsAdmin(boolean isAdmin) {
		this.isAdmin = isAdmin;
	}

    public UserRole getRole() {
        return role;
    }

    public void setRole(UserRole role) {
        this.role = role;
    }

	public void setCreatedAt(Date createdAt) {
		this.createdAt = createdAt;
	}

    @Override
    public String toString() {
        return "UserResponse [userId=" + userId + ", fullName=" + fullName + ", email=" + email + ", role=" + role + ", createdAt=" + createdAt + "]";
    }
}
```

```java
package com.sandbox;

import com.fasterxml.jackson.databind.ObjectMapper;

public class Main {
    private static void run() throws Exception {
        String rawJson = """
                {
                    "user_id": 10,
                    "email": "admin@site.com",
                    "full_name": "Admin",
                    "role": "Admin",
                    "isAdmin": 1,
                    "createdAt": "2025-08-03 20:06:11"
                }
                        """;

        ObjectMapper mapper = new ObjectMapper();
        UserResponse res = mapper.readValue(rawJson, UserResponse.class);
        System.out.println(res);
    }

    public static void main(String[] args) {
        try {
            Main.run();
        } catch (Exception ex) {
            System.err.printf("error: %s\n", ex.getMessage());
            System.exit(1);
        }
    }
}
```


##### Handling optional values

```java
import com.fasterxml.jackson.datatype.jdk8.Jdk8Module;

ObjectMapper mapper = new ObjectMapper();
mapper.registerModule(new Jdk8Module());
```

**Note**: With the above change, Jackson will be able to read JSON values into `Optional<T>` class fields.


---


#### Writing JSON

```java
UserResponse resp = new UserResponse() {
    {
        setName("John Doe");
        setEmail(Optional.of("admin@site.com"));
    }
};

ObjectMapper mapper = new ObjectMapper();
mapper.registerModule(new Jdk8Module());

String json = mapper.writeValueAsString(resp);
```