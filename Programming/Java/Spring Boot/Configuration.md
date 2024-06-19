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
spring.jpa.properties.hibernate.dialect=org.hibernate.dialect.PostgreSQLDialect
```


#### Connect to `H2` in-memory database

```
spring.datasource.url=jdbc:h2:mem:testdb
spring.datasource.driverClassName=org.h2.Driver
spring.datasource.username=sa
spring.datasource.password=password
spring.jpa.database-platform=org.hibernate.dialect.H2Dialect
```

