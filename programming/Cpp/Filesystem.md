```cpp
#include <filesystem>
#include <iostream>

int main() {
  const char* path = "./bin";
  bool flag = std::filesystem::is_directory(path);

  std::cout << std::boolalpha 
            << "[exists] " << flag << "\n";
}
```

**Note**: The `std::filesystem` requires C++17 and above.

The namespace may become tedious to type, we can define an alias for the namespace

```cpp
namespace fs = std::filesystem;
...
fs::is_directory(path)
```

Reference: [Link](https://en.cppreference.com/w/cpp/filesystem)


---

#### Usage

```cpp
// Check if path is a directory
std::filesystem::is_directory(path)


// get content of a directory
const char* path = "./src";

for (const auto& item : std::filesystem::directory_iterator(path)) {
  std::cout << item.path() << '\n';
}


// Get content of directory and all its sub-directories
const char* path = "./src";

for (const auto& item : std::filesystem::recursive_directory_iterator(path)) {
  std::cout << item.path() << '\n';
}


// create new directory
std::filesystem::create_directory(path)


// copy content of a directory
const char* path = "./example/01";
const char* target = "./example/02";

std::filesystem::copy(
  path, 
  target, 
  std::filesystem::copy_options::recursive
);


// rename file or directory
const char* in = "./example/01";
const char* out = "./example/02";

std::filesystem::rename(in, out);


// delete file or empty directory
const char* in = "./example/02";
std::filesystem::remove(in);

// Note: This is nice because it will throw if the directory is not empty. If we // don’t care, we can remove a directory with all its content recursively using // the following 

std::filesystem::remove_all(in);
```