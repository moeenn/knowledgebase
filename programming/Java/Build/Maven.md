#### Installation

```bash
$ sdk install maven
```


---

#### Commands

```bash
# download and install dependencies
$ mvn dependency:resolve
$ mvn install

# quick run
$ mvn exec:java -q

# compile and run
$ mvn clean compile assembly:single
$ java -jar target/app-1.0.jar

# find dependency updates
$ mvn versions:display-dependency-updates
```

**Note**: Look at `groupId`, `artifactId` and `version` in the `pom.xml` file to find the name of the compiled file.


---

#### Project structure 

```
- sandbox/
  - pom.xml
  - target/  (add to .gitignore)
  - src/
    - main/
      - java/
        - com/
          - sandbox/
            - Sandbox.java
    - test/
	  - java/
	    - com/
		  - sandbox/
		    - SandboxTest.java
```

```bash
$ mkdir -p ./src/main/java/com/sandbox
$ mkdir -p ./src/test/java/com/sandbox
```


---

#### Project Code

```xml
<project xmlns="http://maven.apache.org/POM/4.0.0" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
  xsi:schemaLocation="http://maven.apache.org/POM/4.0.0 http://maven.apache.org/xsd/maven-4.0.0.xsd">
  <modelVersion>4.0.0</modelVersion>

  <groupId>${mainClass}</groupId>
  <artifactId>app</artifactId>
  <version>1.0</version>

  <build>
    <plugins>
      <plugin>
        <artifactId>maven-assembly-plugin</artifactId>
        <configuration>
          <archive>
            <manifest>
              <mainClass>${mainClass}</mainClass>
            </manifest>
          </archive>
          <descriptorRefs>
            <descriptorRef>jar-with-dependencies</descriptorRef>
          </descriptorRefs>
        </configuration>
      </plugin>
    </plugins>
  </build>

  <properties>
    <java.version>21</java.version>
    <mainClass>com.sandbox.Sandbox</mainClass>
    <maven.compiler.source>${java.version}</maven.compiler.source>
    <maven.compiler.target>${java.version}</maven.compiler.target>
    <maven.compiler.release>${java.version}</maven.compiler.release>
    <exec.mainClass>${mainClass}</exec.mainClass>
  </properties>

  <dependencies>
    <dependency>
        <groupId>org.junit.jupiter</groupId>
        <artifactId>junit-jupiter</artifactId>
        <version>5.10.3</version>
        <scope>test</scope>
    </dependency>
  </dependencies>
</project>
```

```java
/** file: Sandbox.java */
package com.sandbox;

public class Sandbox {
  public static void main(String[] args) {
    System.out.println("hello world");
  }
}
```

```java
/** file: SandboxTest.java */
package com.sandbox;

import static org.junit.jupiter.api.Assertions.assertTrue;
import org.junit.jupiter.api.Test;

public class SandboxTest {
  @Test
  public void testExample() {
    assertTrue(true);
  }
}
```

