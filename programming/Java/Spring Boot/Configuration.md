## Reading `.env` files

The following dependency is required before environment variables can be read in the application.

```xml
<dependency>
	<groupId>me.paulschwarz</groupId>
	<artifactId>spring-dotenv</artifactId>
	<version>4.0.0</version>
</dependency>
```

**Note**: The `.env` file will be located at the root of the project (i.e. next to the `pom.xml`file).




Add the following lines to the `resources/application.properties` file.

#### Default server port

```
server.port=5000
```


#### Connect to PostgreSQL

```
spring.datasource.url=jdbc:postgresql://localhost:5432/dev
spring.datasource.username=devuser
spring.datasource.password=devpass
spring.jpa.hibernate.ddl-auto=create-drop
spring.datasource.driver-class-name=org.postgresql.Driver
```


