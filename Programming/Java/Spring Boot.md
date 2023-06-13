The default boilerplate for the application can be generated using the `Spring-Initializr` website [Link](https://start.spring.io/). Use the following settings.

```
Project: Maven
Language: Java
Spring Boot: 2.7.12
Java: 11

Dependencies: [
	"Spring Web",
	"Validation",
	"Lombok", 
	"Spring Data JPA", 
	"PostgreSQL Driver"
]
```

To download all the dependencies run the following command.

```bash
$ mvn clean package
```

To start the application, use the following command.

```bash
$ mvn spring-boot:run
```

We can also clear build caches and do a clean run

```bash
$ mvn clean spring-boot:run
```

