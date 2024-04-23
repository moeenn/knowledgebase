
```java
// get current Dir
String pwd = System.getProperty("user.dir");

// get current dir (alternative)
import java.nio.file.Paths;
String pwd = Paths.get("").toAbsolutePath().toString();

// join paths
String pwd = Paths.get("", "build", "out").toAbsolutePath().toString();
```

