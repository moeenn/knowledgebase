
#### Files & Directories 

```java
// get current Dir
String pwd = System.getProperty("user.dir");

// get current dir (alternative)
import java.nio.file.Paths;
String pwd = Paths.get("").toAbsolutePath().toString();

// join paths
String pwd = Paths.get("", "build", "out").toAbsolutePath().toString();
```

```java
Path pathFromString = Path.of("/tmp/example");

// preferred because is cross-platform
Path pathFromChunks = Path.of("/", "tmp");
```

```java
Path p = Paths.get("/tmp/test/example");

// check if file exists
boolean exists = Files.exists(p);

// check if path is a directory
boolean isDirectory = Files.isDirectory(p);

// check if path is a file
boolean isFile = Files.isRegularFile(p);
```

```java
Path target = Path.of("/", "tmp", "test", "example.txt");
Path destination = Path.of("/", "tmp", "moved.txt");

try {
  Files.createFile(target);
  Files.move(target, destination);
  
  System.out.printf("target? %b\n", Files.exists(target)); // false
  System.out.printf("destination? %b\n", Files.exists(destination)); // true
} catch (Exception ex) {
  System.out.println(ex.getMessage());
}
```

```java
Path dir = Path.of("/", "tmp", "test");

try (DirectoryStream<Path> files = Files.newDirectoryStream(dir)) {
  files.forEach(System.out::println);
} catch (Exception ex) {
  System.out.println(ex.getMessage());
}
```


---

#### Reading from file

