The default boilerplate for the application can be generated using the `Spring-Initializr` website [Link](https://start.spring.io/). Use the following settings.

```
Project: Gradle
Language: Java
Spring Boot: 2.7.12
Java: 17

Dependencies: [
	"Spring Web",
	"Validation",
	"Spring Data JPA", 
	"PostgreSQL Driver"
]
```

To download all the dependencies run the following command.

```bash
# using gradle 
$ gradle bootJar

# using maven
$ mvn clean package

# running the generated file
$ java -jar ./build/libs/{output}.jar
```

To start the application, use the following command.

```bash
# using gradle
$ gradle bootRun

# using maven
$ mvn spring-boot:run
```

We can also clear build caches and do a clean run

```bash
# using gradle
$ gradle clean; gradle bootRun

# using maven
$ mvn clean spring-boot:run
```
