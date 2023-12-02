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
```

```bash
$ mkdir -p ./src/main/java/com/sandbox
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

dependencies {
}
```

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


#### Commands

```bash
# quickly run the project
# use -q flag for quiet
# use -t flag for live reload build 
$ gradle run

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

