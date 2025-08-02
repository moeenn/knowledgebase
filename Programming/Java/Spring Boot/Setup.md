The default boilerplate for the application can be generated using the `Spring-Initializr` website [Link](https://start.spring.io/). Use the following dependencies.

- Spring web
- Spring Boot DevTools (live reload)
- Validation 
- Spring Data JPA
- PostgreSQL Driver
- Spring REST Docs (OpenAPI documentation)

To download all the dependencies run the following command.

```bash
# using maven
$ mvn install

# running the generated file
$ java -jar ./build/libs/{output}.jar
```

To start the application, use the following command.

```bash
$ mvn clean spring-boot:run
```
