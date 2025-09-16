
#### Installation

###### Option #1
Java and its build tool-chains can be installed using the OS package managers. Following is an example.

```bash
$ sudo apt-get install default-jdk libeclipse-jdt-core-java
```

###### Option #2 (Recommended) 
The above option works but it is not very flexible. A much better option is to use `sdkman` to install specific versions of java and build tools / packages / CLIs.

```bash
# installing sdkman (**NOTE** Always check their website for the latest command)
$ curl -s "https://get.sdkman.io" | bash

# list out different version of java available
$ sdk list java

# install java specific version
$ sdk install java 21-ms

# set default version of java
$ sdk use java 21-ms
```
