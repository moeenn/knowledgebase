
#### Imports

```java
import java.time.LocalDate;
import java.time.LocalTime;
import java.time.LocalDateTime;
import java.time.Month;
import java.time.DateTimeException;
```

```java
// current date
LocalDate now = LocalDate.now();

// current time
LocalTime nowTime = LocalTime.now();

// current date time
LocalDateTime nowDateTime = LocalDateTime.now();
```

```java
// create date from numbers: format (year, month, day)
LocalDate dateFromNums = LocalDate.of(2023, 10, 1);
LocalDate dateFromNumsWithEnum = LocalDate.of(2023, Month.FEBRUARY, 1);

// format (hour, minutes, seconds)
LocalTime timeFromNums = LocalTime.of(23, 10, 30);

// format (year, month, day, hour, minutes, seconds)  
LocalDateTime dateTimeFromNums = LocalDateTime.of(2023, 10, 1, 10, 15, 30);
```

```java
// parse date from string
try {
	LocalDate parsedDate = LocalDate.parse("2023-10-01");
	System.out.println(parsedDate);
} catch (DateTimeException ex) {
	System.out.printf("Failed to parse date: %s\n", ex.getMessage());
}

// parse time from string
try {
	LocalTime parsedTime = LocalTime.parse("13:15");
	System.out.println(parsedTime);
} catch (DateTimeException ex) {
	System.out.printf("Failed to parse date: %s\n", ex.getMessage());
}

// parse date time from string
try {  
  LocalDateTime parsedDateTime = LocalDateTime.parse("2024-02-10T05:30:15");  
  System.out.println(parsedDateTime);  
} catch (DateTimeParseException ex) {  
  System.out.printf("parse error: %s\n", ex.getMessage());  
}
```

```java
LocalDate now = LocalDate.now();
LocalDate future = now.plus(Period.ofDays(5));

Period p = Period.between(now, future);
System.out.println(p.getDays()); // 5
```