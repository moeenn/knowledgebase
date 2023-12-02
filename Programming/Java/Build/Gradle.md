#### Installation

```bash
$ sdk install gradle
```

#### Project structure 

```
- sandbox/
  - .gitignore
  - build.gradle
  - target/
  - src/
    - main/
      - java/
        - com/
          - sandbox/
            - Main.java
            - Calculator.java
    - test/
      - java/
        - com/
          - sandbox/
            - CalculatorTest.java
```

```bash
# make directory structure for code files
$ mkdir -p ./src/main/java/com/sandbox

# make directory structure for test files
$ mkdir -p ./src/test/java/com/sandbox
```


**Note**: `gradle` will generally give better performance than `maven` because `gradle` can spawn a background daemon which keeps the `jvm` alive. This way we don't have to startup the `jvm` every time we execute our code.


#### `build.gradle`file

```groovy
plugins {
    id 'java'
    id 'application'
}

application {
    mainClass = 'com.sandbox.Main'
}

repositories { 
    mavenCentral() 
}

jar {
    archiveVersion =  '0.0.1'
    archiveBaseName = 'com.sandbox'
    manifest {
        attributes['Main-Class'] = 'com.sandbox.Main'
    }
}

testing {
    suites {
        test {
            useJUnitJupiter('5.9.3')
        }
    }
}

dependencies {
    testImplementation 'org.junit.jupiter:junit-jupiter-api:5.9.3'
    testRuntimeOnly 'org.junit.jupiter:junit-jupiter-engine:5.9.3'
}
```

**Note**: Ensure that the version of `junit` is same across the entire `build.gradle` file.

```gitignore
.gradle
.vscode
bin
build
*.class
```


#### Project Code

```java
package com.sandbox;

public class Main {
	public static void main(String[] args) {
		System.out.println("Hello there");
	}
}
```

```java
package com.sandbox;

public class Calculator {
  public int add(int a, int b) {
    return a + b;
  }
}
```

```java
package com.sandbox;

import static org.junit.jupiter.api.Assertions.assertEquals;

import org.junit.jupiter.api.Test;

public class CalculatorTest {
  private final Calculator calculator = new Calculator();

  @Test
  public void testAdd() {
    int result = this.calculator.add(10, 20);
    assertEquals(result, 30);
  }
}
```

#### Commands

```bash
# quickly run the project
# use -q flag for quiet
# use -t flag for live reload build 
$ gradle run

# run tests
$ gradle test

# check and compile project classes
$ gradle build

# generate output jar (in ./build/libs/)
$ gradle jar

# execute jar file 
$ java -jar ./build/libs/com.sandbox-0.0.1.jar

# list gradle background daemon details
$ gradle --status

# kill gradle daemons
$ gradle --stop
```

