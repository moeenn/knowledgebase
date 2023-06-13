
`CMakeLists.txt` 
```txt
cmake_minimum_required (VERSION 3.5)

set (project_name "sandbox")

project(${project_name})
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wextra -Wall -std=c++17")

set (source_dir "${PROJECT_SOURCE_DIR}/src")
set(EXECUTABLE_OUTPUT_PATH "bin")

add_executable(
  ${project_name}
  ${source_dir}/main.cpp
  ${source_dir}/libs/colors/colors.cpp
)
```

Prepare for compilation
```bash
$ cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=1 .
```

Compile program
```bash
$ make
```

`Gitignore` file
```gitignore
CMakeFiles/*
cmake_install.cmake
CMakeCache.txt
Makefile
compile_commands.json
bin
```


---

#### Automatically detect `*.cpp` files

```txt
cmake_minimum_required(VERSION 3.5)

set (project_name "sandbox")
project (${project_name})

set (CMAKE_BUILD_TYPE Debug)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wextra -Werror -Wall -std=c++17 -Wc++17-extensions")
set (source_dir "${PROJECT_SOURCE_DIR}/src/")

file (GLOB source_files "${source_dir}/*.cpp")
add_executable(${project_name} ${source_files})

set(EXECUTABLE_OUTPUT_PATH "bin")
```


---

#### Building C Programs

```txt
cmake_minimum_required(VERSION 2.6.0)

set (project_name "sandbox")
project (${project_name} C)

set (CMAKE_BUILD_TYPE Debug)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wextra -Werror -Wall")

set (source_dir "${PROJECT_SOURCE_DIR}/src/")
set(EXECUTABLE_OUTPUT_PATH "bin")

file (GLOB source_files "${source_dir}/*.c")
add_executable(${project_name} ${source_files})
```

