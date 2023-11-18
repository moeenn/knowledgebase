```
- sandbox/
  - pom.xml
  - target/
  - src/
    - main/
      - java/
        - com/
          - sandbox/
            - Main.java
            - Entity.java
```

```bash
$ mkdir -p ./src/main/java/com/sandbox
```

##### POM File
```xml
<!-- file: pom.xml -->
<project xmlns="http://maven.apache.org/POM/4.0.0" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
  xsi:schemaLocation="http://maven.apache.org/POM/4.0.0 http://maven.apache.org/xsd/maven-4.0.0.xsd">
  <modelVersion>4.0.0</modelVersion>
 
  <groupId>com.sandbox.Main</groupId>
  <artifactId>app</artifactId>
  <version>1.0</version>
 
  <build>
    <plugins>
      <plugin>
        <!-- Build an executable JAR -->
        <groupId>org.apache.maven.plugins</groupId>
        <artifactId>maven-jar-plugin</artifactId>
        <version>3.1.0</version>
        <configuration>
          <archive>
            <manifest>
              <addClasspath>true</addClasspath>
              <classpathPrefix>lib/</classpathPrefix>
              <mainClass>com.sandbox.Main</mainClass>
            </manifest>
          </archive>
        </configuration>
      </plugin>
    </plugins>
  </build>

  <properties>
    <java.version>1.8</java.version>
    <maven.compiler.source>${java.version}</maven.compiler.source>
    <maven.compiler.target>${java.version}</maven.compiler.target>
    <exec.mainClass>com.sandbox.Main</exec.mainClass>
  </properties>
 
  <dependencies>
  </dependencies>
</project>
```


---

#### Project Code
```java
/** file: Main.java */
package com.sandbox;

public class Main {
  public static void main(String[] args) {
    Entity e = new Entity(100, 30);
    System.out.println(e.serialize());
  }
}
```

```java
/** file: Entity.java */
package com.sandbox;

public class Entity {
  private int m_x;
  private int m_y;

  public Entity(int x, int y) {
    m_x = x;
    m_y = y;
  }

  /**
   *  return representation of the object as a string
  */
  public String serialize() {
    return String.format("Entity(x=%d, y=%d)", m_x, m_y);
  }
}
```


#### Commands
```bash
# first run command
$ mvn clean package

# quick run
$ mvn exec:java -q

# compile and run
$ mvn package
$ java -jar target/app-1.0.jar
```

**Note**: Look at `groupId`, `artifactId` and `version` in the `pom.xml` file to find the name of the compiled file.

