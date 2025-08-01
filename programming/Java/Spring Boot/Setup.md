The default boilerplate for the application can be generated using the `Spring-Initializr` website [Link](https://start.spring.io/). Use the following dependencies.

- Spring web
- Spring Boot DevTools
- Validation 
- Spring Data JPA
- PostgreSQL Driver

To download all the dependencies run the following command.

```bash
# using maven
$ mvn install

# running the generated file
$ java -jar ./build/libs/{output}.jar
```

To start the application, use the following command.

```bash
$ mvn spring-boot:run
```

We can also clear build caches and do a clean run

```bash
# using maven
$ mvn clean spring-boot:run
```


