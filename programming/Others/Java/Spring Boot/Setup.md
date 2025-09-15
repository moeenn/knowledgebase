The default boilerplate for the application can be generated using the `Spring-Initializr` website [Link](https://start.spring.io/). Use the following dependencies.

- Spring web
- Spring Boot DevTools (live reload)
- Validation 
- Spring Data JPA
- PostgreSQL Driver
- Spring REST Docs (OpenAPI documentation)


---

#### Commands

```bash
# download dependencies.
$ mvn dependency:resolve

# run the project in development mode.
$ mvn clean spring-boot:run

# build for production.
$ mvn package

# running in production.
$ java -jar ./target/[app-name]-[version].jar
```

