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
# OR
$ gradle build

# run the project in development mode.
$ mvn clean spring-boot:run
# OR
$ gradle bootRun

# build for production.
$ mvn package

# running in production.
$ java -jar ./target/[app-name]-[version].jar
```

