##### `CMakeLists.txt` 

```txt
cmake_minimum_required (VERSION 3.5)

set (PROJECT_NAME "sandbox")
project (${PROJECT_NAME})
set (CMAKE_CXX_STANDARD 20)

# Create symlink to compile_commands.json at project root for IDE to pick it up
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
if (PROJECT_IS_TOP_LEVEL AND UNIX)
    execute_process(
        COMMAND ${CMAKE_COMMAND} -E create_symlink
            ${CMAKE_BINARY_DIR}/compile_commands.json
            ${CMAKE_CURRENT_SOURCE_DIR}/compile_commands.json
    )
endif()

# auto-detect source files in directory
file (GLOB_RECURSE SRC_FILES "${PROJECT_SOURCE_DIR}/src/*.cpp")
add_executable (${PROJECT_NAME} ${SRC_FILES})

target_compile_options(${PROJECT_NAME} PUBLIC -Wextra -Werror -Wall -Wpedantic -O3)
target_link_libraries (${PROJECT_NAME} m) # m means -lm i.e. math library
```

**Note**: Inside `add_executable` we call also list out all required source files.

```txt
add_executable(
  ${project_name}
  ${source_dir}/main.cpp
  ${source_dir}/libs/colors/colors.cpp
)
```

---

#### Building projects

##### Debug build

```bash
$ cmake -S . -B build -D CMAKE_BUILD_TYPE=Debug
$ make -C ./build 
$ ./build/[binary-name]
```


##### Release build

```bash
$ cmake -S . -B build -D CMAKE_BUILD_TYPE=Release
$ make -C ./build 
$ ./build/[binary-name]
```


##### Alternate approach

```bash
$ mkdir -p build
$ cd ./build
$ cmake 
$ ./[binary-name]
```


---

#### `.gitignore` file

```
.cache
compile_commands.json
build/*
.DS_Store
```