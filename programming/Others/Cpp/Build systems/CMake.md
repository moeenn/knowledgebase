
#### Sample project structure

```
CMakeLists.txt
.gitignore
build/
src/
	main.cpp
	Game/
		Game.cpp
include/
	Game/
		Game.hpp
		
```


---

##### `CMakeLists.txt` 

```txt
cmake_minimum_required(VERSION 3.10)

set(PROJECT nb)
project(${PROJECT})

set(CMAKE_CXX_COMPILER "clang++")
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_compile_options(-Wall -Wextra -pedantic -Werror -O2)

add_executable(${PROJECT} src/main.cpp)
target_include_directories(${PROJECT} PUBLIC "include")
```

```hpp
/// Game.hpp

#pragma once

class Game {
public:
  Game();
  ~Game();
};
```

```cpp
/// Game.cpp

#include "Game/Game.hpp"
#include <iostream>

Game::Game() {
  std::cout << "Running game ...\n";
}

Game::~Game() {
  std::cout << "Exiting ...\n";
}
```

```cpp
/// main.cpp

#include "Game/Game.hpp"

int main() {
  Game g;
}
```

```gitignore
build
bin/*
.cache
```

---

#### Building the projects

```bash
$ mkdir -p build
$ cd ./build
$ cmake .. -D CMAKE_BUILD_TYPE=Debug
$ ./[binary-name]
```

**Note**:
- `-D CMAKE_BUILD_TYPE` is optional.  
- To create a release build use `CMAKE_BUILD_TYPE=Release`.