We wrap the external interface of a class within another class, adding additional functionality to the methods of the existing class.

```java
package com.sandbox;

public interface IDataSource {
  void writeData(String data);
  String readData();
}
```

```java
package com.sandbox;

public class FileDataSource implements IDataSource {
  private String content;

  public FileDataSource() {
    this.content = "";
  }

  @Override
  public void writeData(String data) {
    this.content = this.content.concat(data);
  }

  @Override
  public String readData() {
    return this.content;
  }
}
```

```java
package com.sandbox;

public class DecoratedFileDataSource implements IDataSource {
  private IDataSource dataSource;

  public DecoratedFileDataSource(IDataSource dataSource) {
    this.dataSource = dataSource;
  }

  @Override
  public void writeData(String data) {
    Logger.log("writing some data to file data source");
    this.dataSource.writeData(data);
  }

  @Override
  public String readData() {
    Logger.log("reading content from file data source");
    return this.dataSource.readData();
  }
}
```

```java
package com.sandbox;

public class Logger {
  public static void log(String message) {
    System.out.printf("[log] %s\n", message);
  }
}
```

```java
package com.sandbox;

import static org.junit.jupiter.api.Assertions.assertEquals;

import org.junit.jupiter.api.Test;

public class DecoratedFileDataSourceTest {
  private IDataSource decoratedSource;

  public DecoratedFileDataSourceTest() {
    FileDataSource fileSource = new FileDataSource();
    this.decoratedSource = new DecoratedFileDataSource(fileSource);
  }

  @Test
  public void testReadAndWrite() {
    String input = "Random content";
    this.decoratedSource.writeData(input);

    String data = this.decoratedSource.readData();
    assertEquals(input, data);
  }
}
```

```java
package com.sandbox;

public class Main {
  public static void main(String[] args) {
    FileDataSource source = new FileDataSource();
    DecoratedFileDataSource decoratedSource = new DecoratedFileDataSource(source);

    decoratedSource.writeData("WRITTEN CONTENT"); 
    String data = decoratedSource.readData();
    System.out.println(data);
  }
}
```
