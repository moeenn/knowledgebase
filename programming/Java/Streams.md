```java
package com.sandbox;

public enum Gender {
  MALE,
  FEMALE,
}
```

```java
package com.sandbox;

public class Person {
  private String name;
  private Integer age;
  private Gender gender;

  public Person(String name, Integer age, Gender gender) {
    this.name = name;
    this.age = age;
    this.gender = gender;
  }

  public String getName() {
    return name;
  }

  public Integer getAge() {
    return age;
  }

  public Gender getGender() {
    return gender;
  }  

  @Override
  public String toString() {
    return "Person [name=" + name + ", age=" + age + ", gender=" + gender + "]";
  }  
}
```

```java
package com.sandbox;

import java.util.List;
import java.util.stream.Collectors;
import java.util.Comparator;
import java.util.Optional;
import java.util.Map;

public class Main {
  public static void main(String[] args) {
    List<Person> people = getPeople();

    filter(people);
    sort(people);
    allMatch(people);
    anyMatch(people);
    noneMatch(people);
    max(people);
    group(people);
  }

  private static List<Person> getPeople() {
	// generate immutable list
    return List.of(
        new Person("Alice", 23, Gender.FEMALE),
        new Person("Bob", 36, Gender.MALE),
        new Person("Charlie", 28, Gender.MALE),
        new Person("Donna", 30, Gender.FEMALE),
        new Person("Elliot", 20, Gender.MALE),
        new Person("Femke", 47, Gender.FEMALE));
  }

  private static void filter(List<Person> people) {
    List<Person> females = people
        .stream()
        .filter(p -> p.getGender().equals(Gender.FEMALE))
        .collect(Collectors.toList());

    females.forEach(System.out::println);
  }

  private static void sort(List<Person> people) {
    List<Person> sortedByAge = people
        .stream()
        .sorted(Comparator.comparing(Person::getAge).reversed())
        .collect(Collectors.toList());

    sortedByAge.forEach(System.out::println);
  }

  private static void allMatch(List<Person> people) {
    boolean allOlderThanFive = people
        .stream()
        .allMatch(p -> p.getAge() > 5);

    System.out.println(allOlderThanFive);
  }

  private static void anyMatch(List<Person> people) {
    boolean anyOlderThanForty = people
        .stream()
        .anyMatch(p -> p.getAge() > 40);

    System.out.println(anyOlderThanForty);
  }

  private static void noneMatch(List<Person> people) {
    boolean notHaveAnderson = people
        .stream()
        .noneMatch(p -> p.getName().equals("Anderson"));

    System.out.println(notHaveAnderson);
  }

  private static void max(List<Person> people) {
    Optional<Person> maxAge = people
        .stream()
        .max(Comparator.comparing(Person::getAge));

    System.out.println(maxAge);
  }

  private static void group(List<Person> people) {
    Map<Gender, List<Person>> groups = people
        .stream()
        .collect(Collectors.groupingBy(Person::getGender));

    System.out.println(groups);
  }
}
```
