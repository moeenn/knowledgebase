## Reading `.env` files

The following dependency is required before environment variables can be read in the application.

```xml
<dependency>
	<groupId>me.paulschwarz</groupId>
	<artifactId>spring-dotenv</artifactId>
	<version>4.0.0</version>
</dependency>
```

```gradle
implementation 'me.paulschwarz:spring-dotenv:4.0.0'
```

**Note**: The `.env` file will be located at the root of the project.

We will also need to add the following annotation on top of our entry-point class.


```java
import org.springframework.context.annotation.PropertySource;

@SpringBootApplication
@PropertySource(value = "file:.env", ignoreResourceNotFound = true)
public class ApiApplication {
	...
}
```

## Common Condigurations

Add the following lines to the `resources/application.properties` file.

```
# server.
server.port=5000

# database.
spring.datasource.url=jdbc:postgresql://localhost:5432/dev
spring.datasource.username=${DATABASE_USER}
spring.datasource.password=${DABATABSE_PASS}
spring.jpa.hibernate.ddl-auto=validate
spring.datasource.driver-class-name=org.postgresql.Driver
```

