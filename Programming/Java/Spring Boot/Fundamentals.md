#### Basic configuration 
Application configurations can be made in the `resources/application.properties` file. Here are some common configurations.

```properties
# set the default port on which the server will listen on
server.port=5000

# connect to in-memory H2 database
# ensure spring-data-jpa is included as dependency when using this config
spring.datasource.url=jdbc:h2:mem:testdb
spring.datasource.driverClassName=org.h2.Driver
spring.datasource.username=sa
spring.datasource.password=password
spring.jpa.database-platform=org.hibernate.dialect.H2Dialect
```


