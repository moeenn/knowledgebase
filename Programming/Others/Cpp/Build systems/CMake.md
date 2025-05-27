
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
project(sandbox VERSION 1.0.0 LANGUAGES CXX)

# generate the compile_commands.json file.
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
if (PROJECT_IS_TOP_LEVEL AND UNIX)
    execute_process(
        COMMAND ${CMAKE_COMMAND} -E create_symlink
            ${CMAKE_BINARY_DIR}/compile_commands.json
            ${CMAKE_CURRENT_SOURCE_DIR}/compile_commands.json
    )
endif()

file(GLOB_RECURSE SOURCES src/*.cpp)
add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE "include")
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 23)
target_compile_options(${PROJECT_NAME} PUBLIC -Wextra -Werror -Wall -Wpedantic)
target_link_libraries(${PROJECT_NAME} m) # m means -lm (link math)
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